"""Manually snapshot public per-field monster masters and publish reviewed boss data.

No game execution, process access, accounts, scheduling or user-setting writes.
"""
import argparse
from collections import Counter
import datetime
import json
from pathlib import Path
import re
import runpy
import shutil
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
from catalog_pipeline import module, require, digest, load, write_json, atomic_json, checked_child, installation_identity, manifest_source, resource_changes, read_snapshot, SnapshotCapture
ASSETS = ROOT / "data/sources/toram-monsters"


def selected_assets(data, required_locales):
    parser = module("extract-toram-localizations.py")
    manifest = parser["parse_manifest"](data)
    fields = [g for g in manifest["groups"] if g["assetNameTemplate"] == "FieldScript/FieldScript_{0}"]
    require(len(fields) == 1 and fields[0]["flagRaw"] == 0, "Unreviewed FieldScript bundle selection")
    rows = fields[0]["rows"]
    ids = [r["formatArgument"] for r in rows]
    require(len(ids) == len(set(ids)), "Duplicate FieldScript manifest IDs")
    assets = [{"asset": f"FieldScript/FieldScript_{r['formatArgument']}", "flagRaw": 0, **r} for r in rows]
    locales = sorted(m.group(1) for g in manifest["groups"]
                     if (m := re.fullmatch(r"Localize/([a-z]+)/GameScene_\1", g["assetNameTemplate"])))
    require(set(required_locales) <= set(locales), "Required Enemy localization disappeared")
    assets += [parser["single_asset"](manifest, "BynaryData")]
    assets += [parser["single_asset"](manifest, f"Localize/{locale}/GameScene_{locale}") for locale in locales]
    assets.sort(key=lambda a: a["asset"])
    coverage = {"scope": "all-manifest-field-script-groups", "manifestGroupCount": len(ids), "groupIds": sorted(ids)}
    return assets, digest(json.dumps(assets, sort_keys=True).encode()), locales, coverage


def retain_bundles(stage, store, offline, application, assets):
    """Cache by branch, asset and revision; verify bytes before reusing any download."""
    parser = module("extract-toram-localizations.py")
    records = []
    cache = store / "bundle-cache"
    cache.mkdir(exist_ok=True)
    for asset in assets:
        filename = asset["asset"].rsplit("/", 1)[-1] + ".unity3d"
        destination = stage / filename
        url = f"{parser['PUBLIC_BASE']}{application}/{asset['asset']}.unity3d"
        key = digest(json.dumps([application, asset], sort_keys=True).encode())
        index = cache / (key + ".json")
        if index.is_file():
            record = load(index)
            cached = checked_child(cache, record["blob"])
            require(digest(cached.read_bytes()) == record["sha256"], "Cached bundle changed: " + filename)
            shutil.copyfile(cached, destination)
            record = {**record, "mode": "verified-cache"}
        else:
            if offline:
                branch = offline / application / filename
                source = branch if branch.is_file() else offline / filename
                data = source.read_bytes()
                destination.write_bytes(data)
                record = {"url": url, "mode": "offline", "input": str(source.resolve()),
                          "sha256": digest(data), "bytes": len(data)}
            else:
                record = parser["get_public"](url, destination)
            require(destination.read_bytes().startswith(b"UnityFS\0"), "Unreviewed Unity bundle: " + filename)
            record["blob"] = record["sha256"] + ".unity3d"
            blob = checked_child(cache, record["blob"])
            if blob.exists():
                require(digest(blob.read_bytes()) == record["sha256"], "Cached content hash mismatch")
            else:
                shutil.copyfile(destination, blob)
            write_json(index, record)
        records.append({**asset, **record, "file": filename})
        print(f"Retained {len(records)}/{len(assets)}: {asset['asset']}", file=sys.stderr, flush=True)
    return records


def compare_records(before, after):
    def semantic(value):
        if isinstance(value, dict):
            return {k: semantic(v) for k, v in value.items()
                    if k not in ("sourceSha256", "decodedOffset", "rawRecordHex", "classificationEvidence")}
        if isinstance(value, list):
            return [semantic(v) for v in value]
        return value
    old = {r["key"]: semantic(r) for r in before}
    new = {r["key"]: semantic(r) for r in after}
    require(len(old) == len(before) and len(new) == len(after), "Duplicate monster variant key")
    return {"addedKeys": sorted(new.keys() - old.keys()), "removedKeys": sorted(old.keys() - new.keys()),
            "changedKeys": sorted(k for k in old.keys() & new.keys() if old[k] != new[k]),
            "unchanged": sum(old[k] == new[k] for k in old.keys() & new.keys())}


def parse_bundles(source, records, unitypy_path):
    if unitypy_path:
        sys.path.insert(0, str(unitypy_path.resolve()))
    import UnityPy
    game = module("extract-toram-item-assets.py")
    parser = module("extract-toram-monster-data.py")
    inspector = module("extract-toram-field-bundle.py")
    decoded = source / "decoded"
    decoded.mkdir(exist_ok=True)
    names, field_names, fields, evidence, high_raid = {}, {}, [], [], None
    field_ids = set()
    for record in records:
        data = (source / record["file"]).read_bytes()
        if record["flagRaw"] == 1:
            if record["asset"] == "BynaryData":
                for obj in UnityPy.load(data).objects:
                    if obj.type.name != "TextAsset":
                        continue
                    asset = obj.parse_as_object()
                    if asset.m_Name != "HighRaidBossMaster":
                        continue
                    require(high_raid is None, "Duplicate HighRaidBossMaster")
                    raw = asset.m_Script.encode("utf-8", "surrogateescape")
                    plain = game["decode"](raw, int(record["cacheKey"], 16))
                    (decoded / "HighRaidBossMaster.bin").write_bytes(plain)
                    high_raid = {"sha256": digest(plain), "records": parser["parse_high_raid_bosses"](plain)}
                    evidence.append({"name": "HighRaidBossMaster", "bundle": record["file"],
                                     "rawSha256": digest(raw), "decodedSha256": digest(plain), "bytes": len(plain)})
                require(high_raid is not None, "Missing HighRaidBossMaster")
                continue
            locale = record["asset"].rsplit("_", 1)[1]
            found = set()
            for obj in UnityPy.load(data).objects:
                if obj.type.name != "TextAsset":
                    continue
                asset = obj.parse_as_object()
                if asset.m_Name not in (f"Enemy_{locale}", f"FieldName_{locale}"):
                    continue
                require(asset.m_Name not in found, "Duplicate monster localization TextAsset")
                found.add(asset.m_Name)
                raw = asset.m_Script.encode("utf-8", "surrogateescape")
                plain = game["decode"](raw, int(record["cacheKey"], 16))
                (decoded / (asset.m_Name + ".bin")).write_bytes(plain)
                rows = parser["parse_enemy_text"](plain)
                require(rows, "Empty monster localization table")
                (names if asset.m_Name.startswith("Enemy_") else field_names)[locale] = rows
                evidence.append({"name": asset.m_Name, "bundle": record["file"], "rawSha256": digest(raw),
                                 "decodedSha256": digest(plain), "bytes": len(plain)})
            require(found == {f"Enemy_{locale}", f"FieldName_{locale}"}, "Required Enemy/FieldName TextAsset missing")
            continue
        inspection = inspector["inspect_bundle"](data, record["cacheKey"])
        for info in inspection["mapInfos"]:
            match = re.fullmatch(r"mapInfo_(\d+)", info["gameObjectName"] or "")
            require(match, "Unreviewed MapInfo field identity")
            field_id = int(match[1])
            require(field_id not in field_ids and field_id // 1000 == record["formatArgument"], "Duplicate or misplaced MapInfo")
            field_ids.add(field_id)
            db = info["mobDb"]
            script = info.get("fieldScriptAsset")
            info["bossMenus"] = []
            if script:
                script_bytes = script.pop("data")
                (decoded / f"script_{field_id}.bin").write_bytes(script_bytes)
                try:
                    entries = parser["boss_menu_entries"](script_bytes)
                    info["bossMenus"] = entries["menus"]
                    info["invalidScriptEntryOffsets"] = entries["invalidEntryOffsets"]
                except ValueError as error:
                    info["scriptParseError"] = str(error)
            if db:
                plain = db.pop("bytes")
                (decoded / f"mob_{field_id}.bin").write_bytes(plain)
                try:
                    master = parser["parse_mob_db"](plain, field_id)
                except ValueError as error:
                    master = {"parseError": str(error), "sha256": digest(plain), "bytes": len(plain)}
            else:
                master = None
            fields.append({"fieldId": field_id, "bundle": record["file"], "mapInfo": info, "master": master})
        evidence.append({"name": record["asset"], "bundle": record["file"],
                         "decodedSha256": inspection["decodedSha256"], "wrapper": inspection["wrapper"],
                         "mapInfoCount": len(inspection["mapInfos"]), "noMapInfo": inspection["noMapInfo"]})
    require(high_raid is not None, "Missing boss classification master")
    registry = ASSETS / "guild-raid-bosses.json"
    guild_raid = {**load(registry), "sha256": digest(registry.read_bytes())}
    require(guild_raid["schema"] == "toram.reviewed-guild-raid-routes.v1", "Unreviewed GuildRaid identity registry")
    return {"fields": sorted(fields, key=lambda f: f["fieldId"]), "names": names, "fieldNames": field_names,
            "highRaid": high_raid, "guildRaid": guild_raid}, evidence, UnityPy.__version__


def raw_catalog(tables, revision, coverage):
    rows = []
    rejected = []
    for field in tables["fields"]:
        master = field["master"]
        if not master:
            continue
        if "parseError" in master:
            rejected.append({"fieldId": field["fieldId"], **master})
            continue
        for raw in master["monsters"]:
            ident = raw["uuid"]
            rows.append({"key": f"{field['fieldId']}:{raw['id']}", "gameMonsterId": ident,
                         "masterId": raw["id"], "fieldId": field["fieldId"], "raw": raw,
                         "names": {locale: values.get(ident, values.get(str(ident))) for locale, values in tables["names"].items()},
                         "sourceSha256": master["sha256"]})
    require(rows and len({r["key"] for r in rows}) == len(rows), "Empty/duplicate monster variants")
    catalog = {"schema": "toram.raw-monsters.v1", "revision": revision, "coverage": coverage,
            "monsters": sorted(rows, key=lambda r: (r["fieldId"], r["masterId"])),
            "fields": tables["fields"],
            "names": {locale: {str(k): v for k, v in rows.items()} for locale, rows in tables["names"].items()},
            "fieldNames": {locale: {str(k): v for k, v in rows.items()} for locale, rows in tables["fieldNames"].items()},
            "highRaid": tables.get("highRaid", {"sha256": None, "records": []}),
            "guildRaid": tables.get("guildRaid", {"routes": []}), "rejectedFields": rejected}
    classify_monsters(catalog)
    return catalog


def classify_monsters(catalog):
    by_key = {row["key"]: row for row in catalog["monsters"]}
    guild = {}
    catalog["unresolvedGuildRaidReferences"] = []
    registry = catalog.get("guildRaid", {"routes": []})
    for route in registry["routes"]:
        for actor in route["actors"]:
            pending, visited = [(actor["masterId"], [actor["masterId"]])], set()
            while pending:
                master_id, path = pending.pop()
                if master_id in visited:
                    continue
                visited.add(master_id)
                key = f"{route['fieldId']}:{master_id}"
                row = by_key.get(key)
                if (row is None or row["gameMonsterId"] != route["gameMonsterId"]
                        or row["raw"].get("roomId") != route["roomId"]
                        or row["raw"].get("elementRaw") != route["elementRaw"]
                        or row["raw"].get("model") != actor["modelId"] or not row["raw"]["flagRaw"] & 4):
                    catalog["unresolvedGuildRaidReferences"].append({"key": key, "route": route, "actor": actor})
                    continue
                require(key not in guild, "Overlapping GuildRaid actor/phase identities")
                guild[key] = {"kind": "reviewed-guild-raid-route", "registrySha256": registry["sha256"],
                              "identificationSource": registry["identificationSource"], "route": route,
                              "actor": actor, "phasePath": path}
                pending.extend((mode["targetMonsterId"], path + [mode["targetMonsterId"]])
                               for mode in row["raw"].get("modes", []))
    raids = {}
    catalog["unresolvedHighRaidReferences"] = []
    for record in catalog["highRaid"]["records"]:
        key = f"{record['fieldId']}:{record['monsterId']}"
        if key not in by_key or by_key[key]["gameMonsterId"] != record["monsterUuid"]:
            catalog["unresolvedHighRaidReferences"].append(record)
            continue
        raids[(record["fieldId"], record["roomId"], record["monsterUuid"])] = record
    fields = {field["fieldId"]: field for field in catalog["fields"]}
    menus = {}
    for field in catalog["fields"]:
        info = field.get("mapInfo", {})
        for menu in info.get("bossMenus", []):
            menus.setdefault((menu["fieldId"], menu["roomId"]), []).append({"kind": "BossMenu-entry",
                "sourceFieldId": field["fieldId"], "scriptSha256": info["fieldScriptAsset"]["sha256"], **menu})
    for row in catalog["monsters"]:
        raw = row["raw"]
        row["classification"], row["classificationEvidence"] = "unresolved", []
        if not raw["flagRaw"] & 4:
            row["classification"] = "normal-monster"
            continue
        raid = raids.get((row["fieldId"], raw.get("roomId", 0), row["gameMonsterId"]))
        info = fields[row["fieldId"]].get("mapInfo", {})
        pops = [pop for pop in info.get("popMobs", []) if pop["tree"]["monsterDatabaseID"] == row["masterId"]
                and f"mmo_{raw.get('roomId', 0)}" in pop["ancestorGameObjectNames"]]
        entry = menus.get((row["fieldId"], raw.get("roomId", 0)))
        if row["key"] in guild:
            row["classification"], row["classificationEvidence"] = "guild-raid-boss", [guild[row["key"]]]
        elif raid:
            row["classification"] = "high-raid-boss"
            row["classificationEvidence"] = [{"kind": "HighRaidBossMaster", "sourceSha256": catalog["highRaid"]["sha256"],
                "record": {k: v for k, v in raid.items() if k != "rewards"}}]
        elif raw["flagRaw"] & 16:
            row["classification"] = "dungeon-boss"
            row["classificationEvidence"] = [{"kind": "MobMultiFlag.Dungeon", "mask": 16}]
        elif pops:
            row["classification"] = "field-boss"
            row["classificationEvidence"] = [{"kind": "serialized-mmo-pop", "mapInfoPathId": info["pathId"],
                "popPathIds": [pop["pathId"] for pop in pops], "room": f"mmo_{raw.get('roomId', 0)}"}]
        elif entry:
            row["classification"], row["classificationEvidence"] = "entry-boss", entry


def reviewed_contract():
    path = HERE / "toram-boss-pipeline-contract.json"
    contract = load(path)
    for relative, expected in contract["evidenceFiles"].items():
        require(digest(checked_child(ROOT, relative).read_bytes()) == expected,
                "Boss native evidence changed; review contract: " + relative)
    return contract, digest(path.read_bytes())


def run(args):
    contract, contract_hash = reviewed_contract()
    with SnapshotCapture(args.store / args.application,args.install) as capture:
        store=capture.store
        data, manifest_record=manifest_source(args.offline,args.application,capture.manifest_path)
        assets, selection, locales, coverage = selected_assets(data, contract["requiredLocales"])
        installation, reasons = installation_identity(args.install, contract)
        tool_names = ["update-toram-bosses.py", "extract-toram-monster-data.py", "extract-toram-field-bundle.py",
                      "extract-toram-item-assets.py", "extract-toram-localizations.py", "catalog_pipeline.py",
                      "convert-toram-project-bosses.mjs", "project-catalog-store.mjs"]
        identity = {"selection": selection, "installation": installation, "contract": contract_hash,
                    "tools": {name: digest((HERE / name).read_bytes()) for name in tool_names}}
        match=capture.load_state(identity)
        old_path,old_report=capture.latest_path,capture.latest_report
        if match:
            _,observed_report=match
            status="unchanged" if observed_report["status"]=="ready" else "needs-review"
            print(json.dumps({"status":status,"counts":observed_report["counts"],"reviewReasons":observed_report["reviewReasons"]}))
            return 0 if status=="unchanged" else 2
        if args.check:
            print(json.dumps({"status": "needs-review" if reasons else "update-available", "coverage": coverage, "reviewReasons": reasons}))
            return 2 if reasons else 0
        stage=capture.begin(selection[:16])
        source = stage / "source"
        source.mkdir()
        (source / "manifest.bytes").write_bytes(data)
        records = retain_bundles(source, store, args.offline, args.application, assets)
        tables, evidence, runtime = parse_bundles(source, records, args.unitypy_path)
        require(runtime == contract["unityPyVersion"], "UnityPy version changed; review runtime")
        catalog = raw_catalog(tables, selection, coverage)
        catalog["contractSha256"] = contract_hash
        write_json(stage / "monsters.raw.json", catalog)
        before = load(old_path / "monsters.raw.json") if old_path else {"monsters": [], "names": {}, "fieldNames": {}}
        delta = compare_records(before["monsters"], catalog["monsters"])
        delta["localizationChanged"] = before["names"] != catalog["names"] or before["fieldNames"] != catalog["fieldNames"]
        delta["resourceChanges"] = resource_changes(old_report["textAssets"] if old_report else [], evidence)
        write_json(stage / "delta.json", delta)
        for failure in catalog["rejectedFields"]:
            if contract["knownRejectedFields"].get(str(failure["fieldId"])) != failure:
                reasons.append(f"Unreviewed monster master: field {failure['fieldId']}: {failure['parseError']}")
        for record in catalog["unresolvedHighRaidReferences"]:
            if contract.get("knownUnresolvedHighRaidRecords", {}).get(str(record["no"])) != record:
                reasons.append(f"Unreviewed HighRaid map/monster reference: {record['no']}")
        for record in catalog["unresolvedGuildRaidReferences"]:
            reasons.append(f"Reviewed GuildRaid identity no longer matches: {record['key']}")
        for field in catalog["fields"]:
            info = field.get("mapInfo", {})
            if "scriptParseError" in info:
                reasons.append(f"Unreviewed field script: {field['fieldId']}: {info['scriptParseError']}")
            if info.get("invalidScriptEntryOffsets"):
                issue = {"sha256": info["fieldScriptAsset"]["sha256"], "invalidEntryOffsets": info["invalidScriptEntryOffsets"]}
                if contract.get("knownScriptIssues", {}).get(str(field["fieldId"])) != issue:
                    reasons.append(f"Unreviewed field script entry offsets: {field['fieldId']}")
        if not reasons:
            result = subprocess.run(["node", str(HERE / "convert-toram-project-bosses.mjs"), "--input",
                                     str(stage / "monsters.raw.json"), "--output", str(stage / "project")],
                                    capture_output=True, text=True, encoding="utf-8", errors="replace")
            if result.returncode:
                reasons.append("Boss project conversion: " + result.stderr[-1600:])
        current, _ = manifest_source(args.offline, args.application, source / "manifest-after.bytes")
        require(selected_assets(current, contract["requiredLocales"])[1] == selection,
                "Boss resource revisions changed during capture; retry")
        require(installation_identity(args.install, contract)[0] == installation,
                "Installation changed during capture; retry")
        counts = {"variants": len(catalog["monsters"]), "monsterIds": len({r["gameMonsterId"] for r in catalog["monsters"]}),
                  "bossVariants": sum(bool(r["raw"]["flagRaw"] & 4) for r in catalog["monsters"]),
                  "maps": len(tables["fields"]), "rejectedFields": len(catalog["rejectedFields"]),
                  "added": len(delta["addedKeys"]), "changed": len(delta["changedKeys"]), "removed": len(delta["removedKeys"])}
        counts["classifications"] = dict(sorted(Counter(r["classification"] for r in catalog["monsters"] if r["raw"]["flagRaw"] & 4).items()))
        report = {"schemaVersion": 1, "status": "needs-review" if reasons else "ready", "reviewReasons": reasons,
                  "capturedUtc": datetime.datetime.now(datetime.timezone.utc).isoformat(), "identity": identity,
                  "application": args.application, "revision": selection, "coverage": coverage,
                  "activeServerReleaseObserved": False, "manifest": manifest_record, "bundles": records,
                  "textAssets": evidence, "counts": counts,
                  }
        capture.publish(report)
        print(json.dumps({"status":report["status"],"snapshot":str(stage),"counts":counts,"reviewReasons":reasons}))
        return 2 if reasons else 0



def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--application", choices=[f"release{c}" for c in "ABCDEF"], default="releaseC")
    parser.add_argument("--store", type=Path, default=ASSETS / "pipeline")
    parser.add_argument("--install", type=Path, default=Path("C:/Asobimo/AsobimoGames/Toram"))
    parser.add_argument("--offline", type=Path, help="Retained source directory with manifest.bytes and all selected bundles")
    parser.add_argument("--unitypy-path", type=Path, default=ROOT / "build/tmp/toram-item-extraction/python-deps")
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        module("test-toram-boss-pipeline.py")["run_tests"]()
        return 0
    try:
        return run(args)
    except (ValueError, OSError, ImportError) as error:
        print(json.dumps({"status": "failed", "error": str(error)}), file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
