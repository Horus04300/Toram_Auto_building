"""Offline capture/publication gates; no network or game process."""
import contextlib
import io
import json
from pathlib import Path
import runpy
import struct
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

p = runpy.run_path(str(Path(__file__).with_name("update-toram-bosses.py")))


def tables():
    row = {"id": 10, "uuid": 540, "flagRaw": 4, "level": 195, "def": 429}
    return {"fields": [{"fieldId": 23000, "master": {"sha256": "a" * 64, "monsters": [row]}}],
            "names": {"kr": {540: "기드론"}}, "fieldNames": {"kr": {23000: "와지로 가도"}}}


class BossPipelineTests(unittest.TestCase):
    def setUp(self):
        parent = p["ROOT"] / "build/tmp/boss-pipeline-tests"
        parent.mkdir(parents=True, exist_ok=True)
        self.directory = tempfile.TemporaryDirectory(dir=parent)
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.args = SimpleNamespace(store=self.root / "store", application="releaseB", install=self.root / "game",
                                    offline=self.root, unitypy_path=None, check=False)
        self.contract = {"requiredLocales": ["kr"], "installation": {}, "unityPyVersion": "test", "knownRejectedFields": {}}
        self.coverage = {"scope": "all-manifest-field-script-groups"}

    @contextlib.contextmanager
    def mocked_run(self, source=None, reasons=None):
        namespace = p["run"].__globals__
        common = namespace
        def manifest(offline, application, destination):
            destination.write_bytes(b"manifest")
            return b"manifest", {"sha256": p["digest"](b"manifest")}
        def convert(*args, **kwargs):
            stage = Path(args[0][-1]); stage.mkdir()
            (stage / "manifest.json").write_text("{}", encoding="utf-8")
            return SimpleNamespace(returncode=0, stderr="")
        with patch.dict(namespace, {"reviewed_contract": lambda: (self.contract, "contract"),
             "selected_assets": lambda *args: ([], "revision", ["kr"], self.coverage),
             "retain_bundles": lambda *args: [],
             "parse_bundles": lambda *args: (source or tables(), [], "test")}), \
             patch.dict(common, {"manifest_source": manifest, "installation_identity": lambda *args: ({}, reasons or [])}), \
             patch.object(namespace["subprocess"], "run", side_effect=convert), contextlib.redirect_stdout(io.StringIO()):
            yield namespace

    def pointer(self):
        return self.args.store / "releaseB/latest.json"

    def test_check_reports_installation_review_without_capture_or_publication(self):
        self.args.check = True
        for reasons, expected, code in [([], "update-available", 0), (["Native code changed"], "needs-review", 2)]:
            with self.subTest(status=expected), self.mocked_run(reasons=reasons) as namespace:
                with patch.dict(namespace, {"retain_bundles": lambda *args: self.fail("Check must not capture bundles")}), \
                     contextlib.redirect_stdout(io.StringIO()) as output:
                    self.assertEqual(p["run"](self.args), code)
                status = json.loads(output.getvalue())
                self.assertEqual(status["status"], expected)
                self.assertEqual(status["reviewReasons"], reasons)
                self.assertFalse(self.pointer().exists())
                self.assertFalse((self.args.store / "releaseB/observed.json").exists())
                self.assertFalse((self.args.store / "releaseB/snapshots").exists())

    def test_ready_idempotent_and_native_change_quarantine(self):
        with self.mocked_run():
            self.assertEqual(p["run"](self.args), 0)
            before = self.pointer().read_bytes()
            self.assertEqual(p["run"](self.args), 0)
            self.assertEqual(self.pointer().read_bytes(), before)
        # Change the reviewed identity as a new extraction would observe.
        with self.mocked_run(reasons=["Native code changed"]) as namespace:
            namespace["installation_identity"] = lambda *args: ({"GameAssembly.dll": "new"}, ["Native code changed"])
            self.assertEqual(p["run"](self.args), 2)
            self.assertEqual(self.pointer().read_bytes(), before)

    def test_unknown_parse_failure_keeps_raw_and_previous_latest(self):
        with self.mocked_run():
            p["run"](self.args)
        before = self.pointer().read_bytes()
        bad = tables()
        bad["fields"].append({"fieldId": 9, "master": {"parseError": "new format", "sha256": "b" * 64, "bytes": 3}})
        with self.mocked_run(bad) as namespace:
            namespace["installation_identity"] = lambda *args: ({"revision": "changed"}, [])
            self.assertEqual(p["run"](self.args), 2)
        self.assertEqual(self.pointer().read_bytes(), before)
        observed = p["load"](self.args.store / "releaseB/observed.json")
        snapshot, report = p["read_snapshot"](self.args.store / "releaseB", observed)
        self.assertEqual(report["status"], "needs-review")
        self.assertEqual(p["load"](snapshot / "monsters.raw.json")["rejectedFields"][0]["fieldId"], 9)

    def test_capture_failure_and_revision_race_preserve_latest(self):
        with self.mocked_run():
            p["run"](self.args)
        before = self.pointer().read_bytes()
        with self.mocked_run() as namespace:
            calls = [([], "new", ["kr"], self.coverage), ([], "raced", ["kr"], self.coverage)]
            namespace["selected_assets"] = lambda *args: calls.pop(0)
            with self.assertRaisesRegex(ValueError, "revisions changed"):
                p["run"](self.args)
        self.assertEqual(self.pointer().read_bytes(), before)
        self.assertTrue(list(self.args.store.rglob("failure.json")))

    def test_existing_lock_and_tampered_snapshot(self):
        store = self.args.store / "releaseB"
        store.mkdir(parents=True)
        lock = store / ".pipeline.lock"; lock.write_text("other", encoding="ascii")
        with self.mocked_run(), self.assertRaises(FileExistsError):
            p["run"](self.args)
        self.assertEqual(lock.read_text(), "other")
        lock.unlink()
        with self.mocked_run():
            p["run"](self.args)
            pointer = p["load"](self.pointer())
            snapshot, _ = p["read_snapshot"](store, pointer)
            (snapshot / "monsters.raw.json").write_text("tampered", encoding="ascii")
            with self.assertRaisesRegex(ValueError, "snapshot changed"):
                p["run"](self.args)

    def test_variant_diff_preserves_phases_and_negative_values(self):
        a = [{"key": "1:1", "gameMonsterId": 5, "def": -10}, {"key": "2:1", "gameMonsterId": 5}]
        b = [{"key": "1:1", "gameMonsterId": 5, "def": -11}, {"key": "1:2", "gameMonsterId": 5}]
        self.assertEqual(p["compare_records"](a, b), {"addedKeys": ["1:2"], "removedKeys": ["2:1"], "changedKeys": ["1:1"], "unchanged": 0})
        with self.assertRaisesRegex(ValueError, "Duplicate"):
            p["compare_records"]([], b + b)
        self.assertEqual(p["compare_records"](
            [{"key": "1:1", "sourceSha256": "old", "raw": {"def": -5, "decodedOffset": 4, "rawRecordHex": "aa"}}],
            [{"key": "1:1", "sourceSha256": "new", "raw": {"def": -5, "decodedOffset": 40, "rawRecordHex": "bb"}}])['unchanged'], 1)

    def test_classification_requires_exact_positive_route(self):
        def row(field, ident, uuid, flag=4):
            return {"key": f"{field}:{ident}", "fieldId": field, "masterId": ident, "gameMonsterId": uuid,
                    "raw": {"flagRaw": flag, "roomId": 0}}
        rows = [row(1, 10, 540), row(2, 1, 888), row(3, 1, 1001), row(4, 1, 540), row(5, 1, 44, 20)]
        catalog = {"monsters": rows, "fields": [{"fieldId": n, "mapInfo": {
            "pathId": n, "popMobs": ([{"pathId": 9,"tree":{"monsterDatabaseID":10},"ancestorGameObjectNames":["mmo_0"]}] if n==1 else []),
            "bossMenus": ([{"fieldId": 2, "roomId": 0, "eventId": 3, "offset": 20}] if n==4 else []),
            "fieldScriptAsset": {"sha256": "s"}}} for n in range(1,6)],
            "highRaid": {"sha256": "r", "records": [{"no": 7,"fieldId": 3,"roomId": 0,"monsterId": 1,"monsterUuid": 1001}]}}
        p["classify_monsters"](catalog)
        self.assertEqual([row["classification"] for row in rows], ["field-boss","entry-boss","high-raid-boss","unresolved","dungeon-boss"])
        catalog["highRaid"]["records"][0]["monsterUuid"] = 999
        p["classify_monsters"](catalog)
        self.assertEqual(rows[2]["classification"], "unresolved")
        self.assertEqual(len(catalog["unresolvedHighRaidReferences"]), 1)

    def test_reviewed_quest_check_routes_find_colon_menu(self):
        parse = p["module"]("extract-toram-monster-data.py")["boss_menu_entries"]
        fixture = (struct.pack("<Bhi", 16, 1, 7) + struct.pack("<hBBi", 38, 0, 0, 3)
                   + struct.pack("<hBBiii", 20, 0, 0, 0, 31, 40)
                   + struct.pack("<hBBiB", 130, 14, 0, 3300, 0) + struct.pack("<h", 6))
        menu = parse(fixture)["menus"][0]
        self.assertEqual((menu["fieldId"], menu["roomId"], menu["offset"]), (3300, 0, 31))
        self.assertEqual([edge["opcode"] for edge in menu["controlFlow"]], [38, 20])
        cycle = bytearray(fixture); struct.pack_into("<ii", cycle, 23, 15, 15)
        self.assertEqual(parse(cycle)["menus"], [])
        invalid = bytearray(fixture); struct.pack_into("<i", invalid, 23, 10000)
        with self.assertRaisesRegex(ValueError, "branch target"):
            parse(invalid)
        for opcode, first, flags in [(999, 0, 0), (38, 1, 0), (20, 0, 128), (20, 0, 1)]:
            unknown = bytearray(fixture); struct.pack_into("<hBB", unknown, 7, opcode, first, flags)
            self.assertEqual(parse(unknown)["menus"], [], "Never search an unknown/dynamic instruction payload")
        with self.assertRaises(ValueError):
            parse(fixture[:24])
        source = p["ASSETS"] / "native-entry-flow/script_3300.bin"
        menus = parse(source.read_bytes())["menus"]
        self.assertEqual([(row["eventId"], row["offset"], row["fieldId"], row["roomId"]) for row in menus],
                         [(10, 5719, 3300, 0)])

    def test_unreviewed_script_and_raid_reference_do_not_publish(self):
        with self.mocked_run():
            p["run"](self.args)
        before = self.pointer().read_bytes()
        changed = tables()
        issue = {"sha256": "script", "invalidEntryOffsets": [{"eventId": 9, "offset": 100}]}
        changed["fields"][0]["mapInfo"] = {"fieldScriptAsset": {"sha256": "script"},
                                           "invalidScriptEntryOffsets": issue["invalidEntryOffsets"]}
        raid = {"no": 9, "fieldId": 999, "roomId": 0, "monsterId": 1, "monsterUuid": 99}
        changed["highRaid"] = {"sha256": "r", "records": [raid]}
        with self.mocked_run(changed) as namespace:
            namespace["installation_identity"] = lambda *args: ({"revision": "new"}, [])
            self.assertEqual(p["run"](self.args), 2)
        self.assertEqual(self.pointer().read_bytes(), before)
        self.contract["knownScriptIssues"] = {"23000": issue}
        self.contract["knownUnresolvedHighRaidRecords"] = {"9": raid}
        with self.mocked_run(changed) as namespace:
            namespace["reviewed_contract"] = lambda: (self.contract, "reviewed")
            self.assertEqual(p["run"](self.args), 0)

    def test_guild_raid_actor_modes_and_reviewed_identity_gate(self):
        def row(ident, uuid=1195, model=1015601, modes=None):
            return {"key": f"100500:{ident}", "fieldId": 100500, "masterId": ident, "gameMonsterId": uuid,
                    "raw": {"flagRaw": 4, "roomId": 0, "elementRaw": 5, "model": model, "modes": modes or []}}
        registry = {"sha256": "r", "identificationSource": "reviewed user identification", "routes": [
            {"fieldId": 100500, "roomId": 0, "gameMonsterId": 1195, "elementRaw": 5,
             "actors": [{"masterId": 1, "modelId": 1015601, "identity": "male"},
                        {"masterId": 2, "modelId": 1015602, "identity": "female"}]}]}
        rows = [row(1, modes=[{"targetMonsterId": 101}]), row(101),
                row(2, model=1015602, modes=[{"targetMonsterId": 102}]), row(102, model=1015602), row(1001, uuid=917)]
        catalog = {"monsters": rows, "fields": [{"fieldId": 100500, "mapInfo": {}}],
                   "highRaid": {"records": []}, "guildRaid": registry}
        p["classify_monsters"](catalog)
        self.assertEqual([r["classification"] for r in rows], ["guild-raid-boss"] * 4 + ["unresolved"])
        self.assertEqual(rows[1]["classificationEvidence"][0]["phasePath"], [1, 101])
        self.assertEqual(rows[3]["classificationEvidence"][0]["actor"]["identity"], "female")
        self.assertEqual(catalog["unresolvedGuildRaidReferences"], [])
        rows[0]["raw"]["model"] = 999
        p["classify_monsters"](catalog)
        self.assertEqual(rows[0]["classification"], "unresolved")
        self.assertEqual(len(catalog["unresolvedGuildRaidReferences"]), 1)
        with self.mocked_run():
            p["run"](self.args)
        before = self.pointer().read_bytes()
        bad = tables()
        bad["guildRaid"] = registry
        with self.mocked_run(bad) as namespace:
            namespace["installation_identity"] = lambda *args: ({"revision": "new"}, [])
            self.assertEqual(p["run"](self.args), 2)
        self.assertEqual(self.pointer().read_bytes(), before, "A stale reviewed guild identity must not advance latest.")

    def test_escape_and_cached_bundle_tamper(self):
        with self.assertRaises(ValueError):
            p["checked_child"](self.root, "../escape")
        stage = self.root / "source"; stage.mkdir()
        store = self.root / "cache"; store.mkdir()
        asset = {"asset": "FieldScript/FieldScript_1", "cacheKey": "00000001"}
        (stage / "FieldScript_1.unity3d").write_bytes(b"UnityFS\0test")
        with contextlib.redirect_stderr(io.StringIO()):
            first = p["retain_bundles"](stage, store, stage, "releaseB", [asset])
        blob = store / "bundle-cache" / first[0]["blob"]
        blob.write_bytes(b"bad")
        with self.assertRaisesRegex(ValueError, "Cached bundle changed"):
            p["retain_bundles"](stage, store, stage, "releaseB", [asset])


def run_tests():
    suite = unittest.defaultTestLoader.loadTestsFromTestCase(BossPipelineTests)
    result = unittest.TextTestRunner(verbosity=2).run(suite)
    if not result.wasSuccessful():
        raise SystemExit(1)


if __name__ == "__main__":
    run_tests()
