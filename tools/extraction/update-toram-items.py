"""Snapshot public Toram item assets, compare game IDs, and gate reviewed enrichment.

No game execution/process access, app-data mutation, or scheduled/background work.
"""
import argparse
import collections
import copy
import datetime
import hashlib
import json
from pathlib import Path
import re
import runpy
import subprocess
import sys
import uuid

ROOT = Path(__file__).resolve().parents[2]
HERE = Path(__file__).resolve().parent
ASSETS = ROOT / "data/sources/toram-items"
CONTRACT = HERE / "toram-item-pipeline-contract.json"
MODULES = {}


def module(name):
    if name not in MODULES:
        MODULES[name] = runpy.run_path(str(HERE / name))
    return MODULES[name]


def require(value, message):
    if not value:
        raise ValueError(message)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def load(path):
    return json.loads(path.read_text(encoding="utf-8"))


def write_json(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(value, stream, ensure_ascii=False, indent=2, allow_nan=False)
        stream.write("\n")


def atomic_json(path, value):
    temporary = path.with_name(path.name + "." + uuid.uuid4().hex + ".tmp")
    write_json(temporary, value)
    temporary.replace(path)


def checked_child(root, relative):
    if root == ROOT and relative.startswith("assets/source-data/"):
        relative = "data/sources/" + relative[len("assets/source-data/"):]
    require(not Path(relative).is_absolute(), "Absolute artifact path")
    target = (root / relative).resolve()
    require(target.is_relative_to(root.resolve()) and target != root.resolve(), "Artifact escapes its store")
    return target


def reviewed_inputs():
    contract = load(CONTRACT)
    for relative, expected in contract.get("evidenceFiles", {}).items():
        require(digest(checked_child(ROOT, relative).read_bytes()) == expected,
                "Reviewed native evidence changed: " + relative)
    values = {}
    for name, record in contract["inputs"].items():
        path = checked_child(ROOT, record["path"])
        data = path.read_bytes()
        require(digest(data) == record["sha256"], f"Reviewed input changed: {name}; review and update the contract")
        values[name] = json.loads(data)
    return contract, values


def installation_identity(install, contract):
    observed, reasons = {}, []
    for relative, expected in contract["installation"].items():
        path = install / relative
        observed[relative] = digest(path.read_bytes()) if path.is_file() else None
        if observed[relative] != expected:
            reasons.append(f"Installation requires code review: {relative}")
    return observed, reasons


def manifest_source(offline, application, destination):
    localization = module("extract-toram-localizations.py")
    url = f"{localization['PUBLIC_BASE']}{application}/{localization['MANIFEST_NAME']}"
    if offline:
        filename = (localization["MANIFEST_NAME"] if application == "releaseA"
                    else f"RevisionInfoBinary.{application}.bytes")
        path = offline / "manifest.bytes" if (offline / "manifest.bytes").is_file() else offline / filename
        data = path.read_bytes()
        if destination:
            destination.write_bytes(data)
        return data, {"url": url, "sha256": digest(data), "input": str(path.resolve()), "mode": "offline"}
    record = localization["get_public"](url, destination)
    return destination.read_bytes(), record


def selected_assets(data, required_locales):
    parser = module("extract-toram-localizations.py")
    manifest = parser["parse_manifest"](data)
    locales = sorted(match.group(1) for group in manifest["groups"]
                     if (match := re.fullmatch(r"Localize/([a-z]+)/GameScene_\1", group["assetNameTemplate"])))
    require(set(required_locales) <= set(locales), "Required language bundle disappeared from manifest")
    names = ["BynaryData"] + [f"Localize/{locale}/GameScene_{locale}" for locale in locales]
    assets = [parser["single_asset"](manifest, name) for name in names]
    return assets, digest(json.dumps(assets, sort_keys=True).encode()), locales


def retain_bundles(stage, offline, application, assets):
    parser = module("extract-toram-localizations.py")
    records = []
    for asset in assets:
        filename = asset["asset"].rsplit("/", 1)[-1] + ".unity3d"
        destination = stage / filename
        url = f"{parser['PUBLIC_BASE']}{application}/{asset['asset']}.unity3d"
        if offline:
            branch = offline / application / filename
            path = branch if branch.is_file() else offline / filename
            data = path.read_bytes()
            destination.write_bytes(data)
            record = {"url": url, "mode": "offline", "input": str(path.resolve()), "sha256": digest(data), "bytes": len(data)}
        else:
            record = parser["get_public"](url, destination)
        records.append({**asset, **record, "file": filename})
    return records


def parse_bundles(stage, records, unitypy_path):
    if unitypy_path:
        sys.path.insert(0, str(unitypy_path.resolve()))
    import UnityPy
    game = module("extract-toram-item-assets.py")
    wanted = {"ItemMaster", "ItemProperties", "ItemDorpData", *module("extract-toram-item-relations.py")["PARSERS"]}
    tables, evidence = {}, []
    for record in records:
        data = (stage / record["file"]).read_bytes()
        require(data.startswith(b"UnityFS\0"), "Unreviewed bundle wrapper")
        short_name = record["asset"].rsplit("/", 1)[-1]
        locale = short_name.removeprefix("GameScene_") if short_name != "BynaryData" else None
        names = {f"{name}_{locale}" for name in ["Item", "ItemProperty", "System", "Skill", "ItemRandomProperty"]} if locale else wanted
        for obj in UnityPy.load(data).objects:
            if obj.type.name != "TextAsset":
                continue
            value = obj.parse_as_object()
            name = value.m_Name
            if name not in names:
                continue
            require(name not in tables and re.fullmatch(r"[A-Za-z0-9_]+", name), "Duplicate/unsafe TextAsset")
            raw = value.m_Script.encode("utf-8", "surrogateescape")
            decoded = game["decode"](raw, int(record["cacheKey"], 16))
            tables[name] = decoded
            folder = stage / "decoded"
            folder.mkdir(exist_ok=True)
            (folder / f"{name}.bin").write_bytes(decoded)
            evidence.append({"name": name, "bundle": record["file"], "cacheKey": record["cacheKey"],
                             "rawSha256": digest(raw), "decodedSha256": digest(decoded), "bytes": len(decoded)})
        require(names <= set(tables), f"Required TextAssets missing in {short_name}: {sorted(names - set(tables))}")
    return tables, evidence, UnityPy.__version__


def raw_catalog(tables, locales, version):
    game = module("extract-toram-item-assets.py")
    parser = module("decode-toram-item-master.py")
    master = parser["parse"](tables["ItemMaster"])
    properties = parser["parse_properties"](tables["ItemProperties"])
    require(master and set(properties) <= {r["id"] for r in master}, "Empty master or orphan property IDs")
    text = {locale: game["parse_text"](tables[f"Item_{locale}"], True) for locale in locales}
    labels = {locale: game["parse_text"](tables[f"ItemProperty_{locale}"], False) for locale in locales}
    require(all(rows and any(r["kind"] == 0 for r in rows) for rows in text.values()), "Empty item language table")
    items, orphans = game["join_items"](master, properties, text, labels, {})
    # Raw records stay independent of an older build's enum interpretation.
    for item in items:
        for cap in (item["propertyRecord"] or {}).get("caps", []):
            cap.pop("enumName")
    return {"schemaVersion": 1, "cacheVersion": version, "availableItemLocales": locales,
            "authority": "public-resource-bytes-under-reviewed-structural-parser",
            "items": items, "orphanTexts": orphans,
            "optionTextRows": labels, "nativeRulesApplied": False}


def item_projection(item):
    master = {k: v for k, v in item["master"].items() if k not in {"decoded_offset", "raw_record_hex"}}
    caps = (item["propertyRecord"] or {}).get("caps")
    return {"names": item["names"], "descriptions": item["descriptions"], "master": master,
            "caps": [{k: cap[k] for k in ["slot", "cap_id", "value"]} for cap in caps] if caps is not None else None}


def compare_items(before, after):
    old = {row["gameItemId"]: row for row in before["items"]}
    new = {row["gameItemId"]: row for row in after["items"]}
    require(len(old) == len(before["items"]) and len(new) == len(after["items"]), "Duplicate diff ID")
    changes = []
    for ident in sorted(old.keys() & new.keys()):
        a, b = item_projection(old[ident]), item_projection(new[ident])
        fields = {key: {"before": a[key], "after": b[key]} for key in a if a[key] != b[key]}
        if fields:
            changes.append({"gameItemId": ident, "fields": fields})
    return {"addedIds": sorted(new.keys() - old.keys()), "removedIds": sorted(old.keys() - new.keys()),
            "changed": changes, "unchangedItems": len(old.keys() & new.keys()) - len(changes)}


def enrich(catalog, tables, reviewed):
    result = copy.deepcopy(catalog)
    result["schemaVersion"], result["nativeRulesApplied"] = 2, True
    game = module("extract-toram-item-assets.py")
    connection = module("connect-toram-item-data.py")
    reference = module("extract-toram-item-reference-texts.py")
    localization = module("extract-toram-localizations.py")
    classification = module("extract-toram-item-classification.py")
    display = module("extract-toram-option-display.py")
    names = reviewed["bonus"]["by_id"]
    multipliers = {r["capId"]: r["multiplierFloat32"] for r in reviewed["display"]["overrides"]}
    special = reviewed["special"]
    elements = {r["value"]: r["enumName"] for r in special["elementEnum"]["values"]}
    labels = {locale: {r["propertyId"]: r["text"] for r in rows} for locale, rows in catalog["optionTextRows"].items()}
    formats = localization["audit_template_formats"]([
        {"propertyId": ident, "templates": {locale: text}} for locale, rows in labels.items() for ident, text in rows.items()])
    require(not formats["unsupportedOrMalformed"], "Unreviewed option template format")
    systems, skills = {}, {}
    for locale in catalog["availableItemLocales"]:
        grouped = collections.defaultdict(list)
        for row in reference["parse"](tables[f"System_{locale}"], False, game["Reader"]):
            grouped[row["key"]].append(row["text"])
        systems[locale] = grouped
        grouped = collections.defaultdict(list)
        for row in localization["skill_rows_preserving_duplicates"](tables[f"Skill_{locale}"], reference["parse"]):
            grouped[(row["skillId"], row["kind"])].append(row["text"])
        skills[locale] = grouped
    for item in result["items"]:
        checks, slot = classification["classify_type"](item["master"]["type_id"])
        item["references"] = {"nativeChecks": checks, "defaultSelectedEquipSlotValue": slot}
        if checks["CheckAvatarEquipItem"]:
            item["references"]["avatarCategory"] = classification["packed_avatar_category"](item["master"]["range_raw"], item["master"]["slot_max_raw"])
        record = item["propertyRecord"]
        if record is None:
            continue
        record["conditionGroups"], assignments = connection["condition_groups"](record["caps"])
        require(all(g["uiScopeMatchesBonusScope"] for g in record["conditionGroups"]), "Condition UI/bonus scope changed")
        for cap in record["caps"]:
            ident = cap["cap_id"]
            require(str(ident) in names, f"Unknown bonus cap ID {ident}")
            cap["enumName"] = names[str(ident)]
            if ident <= 0:
                require(ident == 0, "Unexpected negative cap ID")
                continue
            multiplier = multipliers.get(ident, reviewed["display"]["defaultMultiplierFloat32"])
            number = display["scaled"](cap["value"], multiplier)
            cap["role"] = "equipment-condition-marker" if ident in connection["MARKERS"] else "option"
            cap["valueKind"] = ("condition-instruction-count" if ident in connection["MARKERS"] else
                                "element-enum" if ident == 65 else "avatar-skill-selector" if ident == 189 else "bonus-operand")
            cap["conditionMarkerSlot"] = assignments.get(cap["slot"])
            rendered = {}
            for locale, table in labels.items():
                if ident == 65:
                    key = elements.get(cap["value"])
                    require(key and len(systems[locale][key]) == 1 and 65 in table, "Unresolved element reference")
                    rendered[locale] = table[65].replace("{0}", systems[locale][key][0])
                elif ident == 189:
                    skill = reference["AVATAR_SKILLS"].get(cap["value"])
                    require(skill and all(len(skills[locale][(skill, kind)]) == 1 for kind in [0, 1]), "Unresolved avatar skill")
                    name = reference["derive_skill_name"](skills[locale][(skill, 0)][0], special["skillNameRule"]["constants"])
                    require(name["nativeCodeDerivedName"] is not None, "Duplicate avatar skill name variant")
                    rendered[locale] = name["nativeCodeDerivedName"]
                else:
                    rendered[locale] = connection["text_preview"](ident, number, table, reviewed["constants"]["strings"])["plainTextCandidate"]
            cap["display"] = {"multiplierFloat32": multiplier, "scaledValueFloat32": number,
                              "plainTextCandidates": rendered, "finalUiVerified": False}
            if ident in (65, 189):
                cap["reference"] = ({"kind": "element", "enumName": elements[cap["value"]]} if ident == 65
                                    else {"kind": "avatar-skill", "skillId": reference["AVATAR_SKILLS"][cap["value"]]})
    return result


def auxiliary_tables(tables):
    relations = module("extract-toram-item-relations.py")
    result = {}
    for name, parser in relations["PARSERS"].items():
        parsed = parser(tables[name])
        require(relations["encode"](name, parsed) == tables[name], f"Auxiliary round trip failed: {name}")
        result[name] = parsed
    # shortcut: unresolved drop semantics stay raw; upgrade only with a verified loader.
    result["ItemDorpData"] = {"status": "uninterpreted", "rawDecodedHex": tables["ItemDorpData"].hex()}
    return result


def connect_auxiliary(catalog, auxiliary, tables, reviewed):
    relations = module("extract-toram-item-relations.py")
    reference = module("extract-toram-item-reference-texts.py")
    game = module("extract-toram-item-assets.py")
    items = {i["gameItemId"]: i for i in catalog["items"]}
    random_names = {}
    for locale in catalog["availableItemLocales"]:
        random_names[locale] = collections.defaultdict(dict)
        for row in game["parse_text"](tables[f"ItemRandomProperty_{locale}"], True):
            random_names[locale][row["gameItemId"]][str(row["kind"])] = row["text"]
    for row in auxiliary["ItemRandomPropertyMaster"]["records"]:
        row["localizedTextByKind"] = {locale: names.get(row["Id"], {}) for locale, names in random_names.items()}
        for cap in row["caps"]:
            require(str(cap["capId"]) in reviewed["bonus"]["by_id"], "Unknown random-property bonus cap")
            cap["enumName"] = reviewed["bonus"]["by_id"][str(cap["capId"])]
    for item in items.values():
        item["references"].update({"createdByRecipes": [], "usedByRecipes": [], "createSupportGroupKeysRaw": [],
                                   "listedInTextManagerNGItem": False, "modelPropertyCandidates": [], "modelPropertyJoinVerified": False})
    system = collections.defaultdict(list)
    for row in reference["parse"](tables["System_kr"], False, game["Reader"]):
        system[row["key"]].append(row)
    recreate = reviewed["relations"]["metadataEnums"][relations["RECREATE_ENUM"]]
    recreate_types = {f["default"]["int32_value"]: f["name"] for f in recreate["fields"] if "default" in f}
    for recipe in auxiliary["RecipeMaster"]["records"]:
        ref = {"recipeType": recipe["Type"], "recipeId": recipe["RecipeId"]}
        if recipe["Type"] in (0, 1):
            require(recipe["CreateId"] in items, "Recipe output missing from master")
            items[recipe["CreateId"]]["references"]["createdByRecipes"].append(ref)
        else:
            recipe["operationTarget"] = relations["operation_target"](recipe, recreate_types, system, "RecreateRecipeType")
        for material in recipe["materials"]:
            if material["Lv"] == 0:
                require(material["Id"] in items, "Recipe item material missing from master")
                items[material["Id"]]["references"]["usedByRecipes"].append({**ref, "materialSlot": material["RecipeNo"]})
    for group in auxiliary["ItemCreateSupport"]["groups"]:
        for row in group["items"]:
            require(row["gameItemId"] in items, "Create support item missing from master")
            items[row["gameItemId"]]["references"]["createSupportGroupKeysRaw"].append(group["groupKeyRaw"])
    for row in auxiliary["NGItem"]["records"]:
        require(row["gameItemId"] in items, "NG item missing from master")
        items[row["gameItemId"]]["references"]["listedInTextManagerNGItem"] = True
    by_model = collections.defaultdict(list)
    for item in items.values():
        by_model[(item["master"]["type_id"], item["master"]["model"])].append(item)
    for group in auxiliary["EquipModelProperty"]["groups"]:
        for row in group["records"]:
            for item in by_model[(group["groupKeyRaw"], row["modelId"])]:
                item["references"]["modelPropertyCandidates"].append({"groupKeyRaw": group["groupKeyRaw"], "modelId": row["modelId"]})


def resource_changes(before, after):
    old = {r["name"]: r["decodedSha256"] for r in before}
    new = {r["name"]: r["decodedSha256"] for r in after}
    return [{"name": name, "beforeSha256": old.get(name), "afterSha256": new.get(name)}
            for name in sorted(old.keys() | new.keys()) if old.get(name) != new.get(name)]


def template_changes(before, after):
    old = {(locale, row["propertyId"]): row["text"] for locale, rows in before.items() for row in rows}
    new = {(locale, row["propertyId"]): row["text"] for locale, rows in after.items() for row in rows}
    return [{"locale": key[0], "propertyId": key[1], "before": old.get(key), "after": new.get(key)}
            for key in sorted(old.keys() | new.keys()) if old.get(key) != new.get(key)]


def read_snapshot(store, pointer):
    path = checked_child(store, pointer["snapshot"])
    require(digest((path / "report.json").read_bytes()) == pointer["reportSha256"], "Stored report changed")
    report = load(path / "report.json")
    for name, expected in report["outputHashes"].items():
        require(digest(checked_child(path, name).read_bytes()) == expected, f"Stored snapshot changed: {name}")
    return path, report


def export_project_items(stage):
    command = ["node", str(HERE / "convert-toram-project-items.mjs"), "--input", str(stage / "items.connected.json"),
               "--output", str(stage / "project")]
    result = subprocess.run(command, capture_output=True, text=True, encoding="utf-8", errors="replace")
    require(result.returncode == 0, "Project conversion needs review: " + result.stderr[-1600:])


def run(args):
    contract, reviewed = reviewed_inputs()
    store = (args.store / args.application).resolve()
    require(not store.is_relative_to(args.install.resolve()), "Store must not be inside the game installation")
    store.mkdir(parents=True, exist_ok=True)
    lock = store / ".pipeline.lock"
    with lock.open("x", encoding="ascii") as stream:
        stream.write(str(uuid.uuid4()))
    stage = None
    try:
        temporary = checked_child(store, ".manifest-" + uuid.uuid4().hex + ".bytes")
        try:
            data, manifest_record = manifest_source(args.offline, args.application, temporary)
        finally:
            temporary.unlink(missing_ok=True)
        assets, selection, locales = selected_assets(data, contract["requiredLocales"])
        observed, reasons = installation_identity(args.install, contract)
        identity = {"selection": selection, "installation": observed, "contractSha256": digest(CONTRACT.read_bytes()),
                    "tools": {p.name: digest(p.read_bytes()) for p in sorted(HERE.glob("*.py"))},
                    "projectConversion": {str(p.relative_to(ROOT)): digest(p.read_bytes()) for p in [
                        HERE / "convert-toram-project-items.mjs", HERE / "project-catalog-store.mjs", ROOT / "web/src/application/item-catalog.mjs",
                        ROOT / "web/src/calculation/stat-registry.js"]}}
        previous = load(store / "latest.json") if (store / "latest.json").is_file() else None
        observation = load(store / "observed.json") if (store / "observed.json").is_file() else previous
        for pointer in [previous, observation]:
            if not pointer:
                continue
            _, observed_report = read_snapshot(store, pointer)
            if observed_report["identity"] == identity:
                status = "unchanged" if observed_report["status"] == "ready" else "needs-review"
                print(json.dumps({"status": status, "snapshot": pointer["snapshot"], "reviewReasons": observed_report["reviewReasons"]}))
                return 2 if status == "needs-review" else 0
        if args.check:
            print(json.dumps({"status": "update-available" if not reasons else "needs-review", "identity": identity,
                              "reviewReasons": reasons, "cacheVersion": assets[0]["cacheKey"], "locales": locales}))
            return 2 if reasons else 0
        stage = checked_child(store, "snapshots/" + assets[0]["cacheKey"] + "-" + uuid.uuid4().hex)
        stage.mkdir(parents=True)
        sources = stage / "source"
        sources.mkdir()
        (sources / "manifest.bytes").write_bytes(data)
        records = retain_bundles(sources, args.offline, args.application, assets)
        tables, evidence, unity_version = parse_bundles(sources, records, args.unitypy_path)
        require(unity_version == contract["unityPyVersion"], "UnityPy version changed; review the extraction runtime")
        catalog = raw_catalog(tables, locales, assets[0]["cacheKey"])
        write_json(stage / "items.raw.json", catalog)
        before = load(read_snapshot(store, previous)[0] / "items.raw.json") if previous else reviewed["baseline"]
        delta = compare_items(before, catalog)
        old_templates = before.get("optionTextRows")
        if old_templates is None:
            old_templates = collections.defaultdict(list)
            for row in reviewed["localizations"]["propertyTexts"]:
                for locale, text in row["templates"].items():
                    old_templates[locale].append({"propertyId": row["propertyId"], "text": text})
        delta["optionTemplateChanges"] = template_changes(old_templates, catalog["optionTextRows"])
        delta["baseline"] = previous["snapshot"] if previous else contract["inputs"]["baseline"]
        if previous:
            old_evidence = read_snapshot(store, previous)[1]["textAssets"]
        else:
            old_evidence = [r for bundle in reviewed["localizations"]["sources"] for r in bundle["textAssets"]]
            old_evidence += [{"name": name, "decodedSha256": table["source"]["sha256"]}
                             for name, table in reviewed["relations"]["tables"].items()]
        selected_names = {r["name"] for r in evidence}
        delta["resourceChanges"] = resource_changes([r for r in old_evidence if r["name"] in selected_names], evidence)
        write_json(stage / "delta.json", delta)
        enriched = None
        try:
            auxiliary = auxiliary_tables(tables)
            write_json(stage / "auxiliary.raw.json", auxiliary)
            if not reasons:
                enriched = enrich(catalog, tables, reviewed)
                connect_auxiliary(enriched, auxiliary, tables, reviewed)
                write_json(stage / "items.connected.json", enriched)
                write_json(stage / "auxiliary.connected.json", auxiliary)
                export_project_items(stage)
        except ValueError as error:
            enriched = None
            reasons.append(str(error))
        added = set(delta["addedIds"])
        write_json(stage / "added-items.json", [i for i in (enriched or catalog)["items"] if i["gameItemId"] in added])
        if args.offline:
            current, _ = manifest_source(args.offline, args.application, None)
        else:
            current, _ = manifest_source(None, args.application, sources / "manifest-after.bytes")
        require(selected_assets(current, contract["requiredLocales"])[1] == selection, "Resource revision changed during capture; retry")
        require(installation_identity(args.install, contract)[0] == observed, "Installation changed during capture; retry")
        report = {"schemaVersion": 1, "status": "needs-review" if reasons else "ready", "reviewReasons": reasons,
                  "capturedUtc": datetime.datetime.now(datetime.timezone.utc).isoformat(), "identity": identity,
                  "application": args.application, "cacheVersion": catalog["cacheVersion"], "activeServerReleaseObserved": False,
                  "manifest": manifest_record, "bundles": records, "textAssets": evidence, "unityPyVersion": unity_version,
                  "counts": {"items": len(catalog["items"]), "added": len(added), "changed": len(delta["changed"]),
                             "removed": len(delta["removedIds"]), "locales": len(locales)},
                  "itemSchema": "toram-item-pipeline-v1 (separate from the historical connected catalog schema)",
                  "limitations": ["Connected fields use the reviewed native contract only when local binary and metadata hashes match.",
                                  "Auxiliary tables are fresh raw records, not stale item relationships from the baseline.",
                                  "Final UI and app/combat calculations are unverified. Baseline Coryn IDs are never treated as game IDs."],
                  "outputHashes": {p.relative_to(stage).as_posix(): digest(p.read_bytes()) for p in stage.rglob("*") if p.is_file()}}
        write_json(stage / "report.json", report)
        destination = stage
        stage = None
        pointer = {"snapshot": destination.relative_to(store).as_posix(), "reportSha256": digest((destination / "report.json").read_bytes())}
        if not reasons:
            atomic_json(store / "latest.json", pointer)
        atomic_json(store / "observed.json", pointer)
        print(json.dumps({"status": report["status"], "snapshot": str(destination), "counts": report["counts"], "reviewReasons": reasons}))
        return 2 if reasons else 0
    except Exception as error:
        if stage is not None:
            write_json(stage / "failure.json", {"status": "failed", "error": str(error), "latestUnchanged": True})
        raise
    finally:
        lock.unlink()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--application", choices=[f"release{c}" for c in "ABCDEF"], default="releaseC")
    parser.add_argument("--store", type=Path, default=ASSETS / "pipeline")
    parser.add_argument("--install", type=Path, default=Path("C:/Asobimo/AsobimoGames/Toram"))
    parser.add_argument("--offline", type=Path, help="Retained source folder or existing localization download root")
    parser.add_argument("--unitypy-path", type=Path, default=ROOT / "build/tmp/toram-item-extraction/python-deps")
    parser.add_argument("--check", action="store_true", help="Compare manifest revisions without downloading bundles")
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        runpy.run_path(str(HERE / "test-toram-item-pipeline.py"))["run_tests"]()
        return 0
    try:
        return run(args)
    except (ValueError, OSError, ImportError) as error:
        print(json.dumps({"status": "failed", "error": str(error)}), file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
