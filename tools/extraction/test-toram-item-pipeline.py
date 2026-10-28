"""Small failure/recovery and semantic-diff tests; no network, game or third-party runtime."""
import contextlib
import importlib.util
import io
import json
from pathlib import Path
import struct
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch
import catalog_pipeline

spec = importlib.util.spec_from_file_location("item_pipeline", Path(__file__).with_name("update-toram-items.py"))
pipeline = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pipeline)


@contextlib.contextmanager
def test_directory():
    parent = pipeline.ROOT / "build/tmp/toram-item-pipeline-tests"
    parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=parent) as directory:
        assert Path(directory).resolve().is_relative_to(parent.resolve())
        yield directory


def item(ident, name="item", offset=4, value=100):
    return {"gameItemId": ident, "names": {"kr": name}, "descriptions": {},
            "master": {"id": ident, "decoded_offset": offset, "raw_record_hex": "00"},
            "propertyRecord": {"caps": [{"slot": 1, "cap_id": 12, "value": value}]}}


class PipelineTests(unittest.TestCase):
    def test_pointer_write_failure_preserves_latest_and_is_not_a_cache_hit(self):
        with test_directory() as directory:
            root=Path(directory)
            store,install=root/'store',root/'install'
            install.mkdir()
            def report(version):
                return {"status":"ready","identity":{"version":version}}
            with pipeline.SnapshotCapture(store,install) as capture:
                stage=capture.begin('first')
                pipeline.write_json(stage/'data.json',{"value":1})
                capture.publish(report(1))
            before=(store/'latest.json').read_bytes()
            real_atomic=catalog_pipeline.atomic_json
            def fail_latest(path,value):
                if path.name=='latest.json':
                    raise OSError('pointer write failed')
                return real_atomic(path,value)
            with self.assertRaisesRegex(OSError,'pointer write failed'):
                with pipeline.SnapshotCapture(store,install) as capture:
                    capture.begin('second')
                    with patch.object(catalog_pipeline,'atomic_json',side_effect=fail_latest):
                        capture.publish(report(2))
            self.assertEqual((store/'latest.json').read_bytes(),before)
            self.assertFalse((store/'.pipeline.lock').exists())
            with pipeline.SnapshotCapture(store,install) as capture:
                self.assertIsNone(capture.load_state({"version":2}),'An unpublished ready observation must be captured/published again')
                self.assertEqual(capture.load_state({"version":1})[1]['status'],'ready')

    def test_atomic_pointer_failure_cleans_only_its_temporary_file(self):
        with test_directory() as directory:
            path=Path(directory)/'pointer.json'
            path.write_text('{"old":true}',encoding='utf-8')
            with patch.object(Path,'replace',side_effect=OSError('replace failed')):
                with self.assertRaisesRegex(OSError,'replace failed'):
                    pipeline.atomic_json(path,{"new":True})
            self.assertEqual(pipeline.load(path),{"old":True})
            self.assertEqual(list(path.parent.glob('*.tmp')),[])

    def test_semantic_diff_ignores_offsets_and_order(self):
        old = {"items": [item(1), item(2), item(3)]}
        new = {"items": [item(4), item(2, name="translated"), item(1, offset=999)]}
        result = pipeline.compare_items(old, new)
        self.assertEqual(result["addedIds"], [4])
        self.assertEqual(result["removedIds"], [3])
        self.assertEqual(result["unchangedItems"], 1)
        self.assertEqual(list(result["changed"][0]["fields"]), ["names"])

    def test_signed_options_and_duplicate_ids(self):
        old, new = {"items": [item(1)]}, {"items": [item(1, value=-100)]}
        self.assertEqual(pipeline.compare_items(old, new)["changed"][0]["fields"]["caps"]["after"][0]["value"], -100)
        with self.assertRaises(ValueError):
            pipeline.compare_items(old, {"items": [item(1), item(1)]})

    def test_template_and_non_item_resources_are_diffed(self):
        result = pipeline.resource_changes([{"name": "ItemProperty_kr", "decodedSha256": "old"}],
                                           [{"name": "ItemProperty_kr", "decodedSha256": "new"},
                                            {"name": "RecipeMaster", "decodedSha256": "recipe"}])
        self.assertEqual([r["name"] for r in result], ["ItemProperty_kr", "RecipeMaster"])
        changed = pipeline.template_changes({"kr": [{"propertyId": -166, "text": "old"}]},
                                             {"kr": [{"propertyId": -166, "text": "new"}]})
        self.assertEqual(changed, [{"locale": "kr", "propertyId": -166, "before": "old", "after": "new"}])

    def test_store_rejects_traversal(self):
        with test_directory() as directory:
            for relative in ["../outside", str(Path(directory).resolve()), "."]:
                with self.assertRaises(ValueError):
                    pipeline.checked_child(Path(directory), relative)

    def test_reviewed_native_evidence_is_checked(self):
        with test_directory() as directory:
            root = Path(directory)
            evidence = root / "native.c"
            evidence.write_bytes(b"reviewed native function")
            contract = root / "contract.json"
            contract.write_text(json.dumps({"inputs": {}, "evidenceFiles": {
                evidence.relative_to(pipeline.ROOT).as_posix(): pipeline.digest(evidence.read_bytes())}}))
            with patch.object(pipeline, "CONTRACT", contract):
                pipeline.reviewed_inputs()
                evidence.write_bytes(b"changed native function")
                with self.assertRaisesRegex(ValueError, "native evidence changed"):
                    pipeline.reviewed_inputs()

    def test_manifest_required_languages_and_bad_eof(self):
        with self.assertRaises(ValueError):
            pipeline.selected_assets(b"\0" * 11, ["kr"])
        parser = pipeline.module("extract-toram-localizations.py")
        with patch.dict(parser, {"parse_manifest": lambda _: {"groups": []}}):
            with self.assertRaisesRegex(ValueError, "Required language"):
                pipeline.selected_assets(b"", ["kr"])

    def test_raw_catalog_preserves_empty_slots_and_rejects_orphans(self):
        parser = pipeline.module("decode-toram-item-master.py")
        values = (1, 1, 10, 1, 1, 0, 2, 1, 10, 80, 4, 0, 15, 1, 0)
        tables = {"ItemMaster": struct.pack("<I", 1) + parser["RECORD"].pack(*values),
                  "ItemProperties": struct.pack("<I", 1) + parser["PROPERTY_RECORD"].pack(1, 12, -10, *([0] * 18)),
                  "Item_kr": struct.pack("<IiBB", 1, 1, 0, 1) + b"A",
                  "ItemProperty_kr": struct.pack("<I", 0)}
        result = pipeline.raw_catalog(tables, ["kr"], "00000001")
        self.assertEqual(len(result["items"][0]["propertyRecord"]["caps"]), 10)
        self.assertEqual(result["items"][0]["propertyRecord"]["caps"][0]["value"], -10)
        tables["ItemProperties"] = struct.pack("<I", 1) + parser["PROPERTY_RECORD"].pack(2, *([0] * 20))
        with self.assertRaisesRegex(ValueError, "orphan"):
            pipeline.raw_catalog(tables, ["kr"], "00000001")

    def test_offline_branch_does_not_mix_same_named_bundles(self):
        with test_directory() as directory:
            root = Path(directory)
            (root / "GameScene_kr.unity3d").write_bytes(b"older branch")
            (root / "releaseB").mkdir()
            (root / "releaseB/GameScene_kr.unity3d").write_bytes(b"selected branch")
            destination = root / "output"
            destination.mkdir()
            pipeline.retain_bundles(destination, root, "releaseB", [{"asset": "Localize/kr/GameScene_kr", "cacheKey": "00000001"}])
            self.assertEqual((destination / "GameScene_kr.unity3d").read_bytes(), b"selected branch")

    def exercise_run(self, scenario):
        with test_directory() as directory:
            root = Path(directory)
            install = root / "install"
            install.mkdir()
            (install / "code").write_bytes(b"reviewed")
            contract = {"requiredLocales": ["kr"], "unityPyVersion": "fixture", "installation": {"code": pipeline.digest(b"reviewed")},
                        "inputs": {"baseline": {"path": "baseline.json"}}}
            reviewed = {"baseline": {"items": [item(1)]}, "localizations": {"sources": [], "propertyTexts": []}, "relations": {"tables": {}}}
            args = SimpleNamespace(store=root / "store", application="releaseB", install=install,
                                   offline=root, unitypy_path=None, check=False)
            generation = [1]
            def manifest(offline, application, destination):
                data = bytes([generation[0]])
                if destination:
                    destination.write_bytes(data)
                return data, {"mode": "fixture"}
            def select(data, required):
                return [{"asset": "BynaryData", "cacheKey": f"{data[0]:08x}"}], data.hex(), ["kr"]
            def retain(stage, offline, application, assets):
                (stage / "fixture.bundle").write_bytes(b"bundle")
                return [{"sha256": pipeline.digest(b"bundle")}]
            def enrich(catalog, tables, reviewed):
                return {**catalog, "nativeRulesApplied": True}
            with patch.object(pipeline, "reviewed_inputs", return_value=(contract, reviewed)), \
                 patch.object(pipeline, "manifest_source", side_effect=manifest), \
                 patch.object(pipeline, "selected_assets", side_effect=select), \
                 patch.object(pipeline, "retain_bundles", side_effect=retain), \
                 patch.object(pipeline, "parse_bundles", return_value=({}, [], "fixture")), \
                 patch.object(pipeline, "raw_catalog", side_effect=lambda t, l, v: {"cacheVersion": v, "optionTextRows": {}, "items": [item(1), item(2)]}), \
                 patch.object(pipeline, "auxiliary_tables", return_value={}), \
                 patch.object(pipeline, "enrich", side_effect=enrich), \
                 patch.object(pipeline, "connect_auxiliary"), \
                 patch.object(pipeline, "export_project_items"), contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(pipeline.run(args), 0)
                store = args.store / args.application
                initial = (store / "latest.json").read_bytes()
                self.assertEqual(pipeline.run(args), 0)
                self.assertEqual(len(list((store / "snapshots").iterdir())), 1)
                generation[0] = 2
                if scenario == "code-change":
                    (install / "code").write_bytes(b"changed")
                    self.assertEqual(pipeline.run(args), 2)
                    self.assertEqual((store / "latest.json").read_bytes(), initial)
                    self.assertEqual(pipeline.run(args), 2)
                    path, report = pipeline.read_snapshot(store, pipeline.load(store / "observed.json"))
                    self.assertEqual(report["status"], "needs-review")
                    self.assertFalse((path / "items.connected.json").exists())
                    self.assertFalse(pipeline.load(path / "items.raw.json").get("nativeRulesApplied", False))
                elif scenario == "parser-failure":
                    with patch.object(pipeline, "parse_bundles", side_effect=ValueError("bad EOF")):
                        with self.assertRaisesRegex(ValueError, "bad EOF"):
                            pipeline.run(args)
                    self.assertEqual((store / "latest.json").read_bytes(), initial)
                    self.assertEqual(len(list((store / "snapshots").glob("*/failure.json"))), 1)
                elif scenario == "unreviewed-option":
                    with patch.object(pipeline, "enrich", side_effect=ValueError("Unknown cap")):
                        self.assertEqual(pipeline.run(args), 2)
                    self.assertEqual((store / "latest.json").read_bytes(), initial)
                    path, _ = pipeline.read_snapshot(store, pipeline.load(store / "observed.json"))
                    self.assertFalse((path / "items.connected.json").exists())
                    self.assertTrue((path / "items.raw.json").exists())
                elif scenario == "conversion-failure":
                    with patch.object(pipeline, "export_project_items", side_effect=ValueError("Project stat mapping changed")):
                        self.assertEqual(pipeline.run(args), 2)
                    self.assertEqual((store / "latest.json").read_bytes(), initial)
                    path, report = pipeline.read_snapshot(store, pipeline.load(store / "observed.json"))
                    self.assertEqual(report["status"], "needs-review")
                    self.assertFalse((path / "project/manifest.json").exists())
                elif scenario == "manifest-race":
                    calls = []
                    def changing_manifest(offline, application, destination):
                        calls.append(1)
                        return bytes([2 if len(calls) == 1 else 3]), {}
                    with patch.object(pipeline, "manifest_source", side_effect=changing_manifest):
                        with self.assertRaisesRegex(ValueError, "revision changed"):
                            pipeline.run(args)
                    self.assertEqual((store / "latest.json").read_bytes(), initial)
                elif scenario == "tamper":
                    pointer = pipeline.load(store / "latest.json")
                    path, _ = pipeline.read_snapshot(store, pointer)
                    (path / "items.raw.json").write_text("{}")
                    with self.assertRaisesRegex(ValueError, "snapshot changed"):
                        pipeline.read_snapshot(store, pointer)
                elif scenario == "concurrency":
                    (store / ".pipeline.lock").write_text("other run")
                    with self.assertRaises(FileExistsError):
                        pipeline.run(args)
                    self.assertEqual((store / ".pipeline.lock").read_text(), "other run")
                    (store / ".pipeline.lock").unlink()
                self.assertFalse((store / ".pipeline.lock").exists())

    def test_ready_idempotence_and_code_change_quarantine(self):
        self.exercise_run("code-change")

    def test_failed_parser_preserves_latest_and_source(self):
        self.exercise_run("parser-failure")

    def test_unreviewed_option_preserves_raw_and_latest(self):
        self.exercise_run("unreviewed-option")

    def test_mid_download_revision_change_does_not_publish(self):
        self.exercise_run("manifest-race")

    def test_project_conversion_failure_preserves_latest(self):
        self.exercise_run("conversion-failure")

    def test_tampered_snapshot_is_rejected(self):
        self.exercise_run("tamper")

    def test_concurrent_run_does_not_remove_others_lock(self):
        self.exercise_run("concurrency")


def run_tests():
    result = unittest.TextTestRunner(verbosity=2).run(unittest.defaultTestLoader.loadTestsFromTestCase(PipelineTests))
    if not result.wasSuccessful():
        raise SystemExit(1)


if __name__ == "__main__":
    run_tests()
