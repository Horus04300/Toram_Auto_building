"""Audit saved Toram item joins against decoded bytes and metadata; no game access."""
import argparse
import collections
import csv
import hashlib
import json
from pathlib import Path
import runpy
import struct
import sys


HERE = Path(__file__).resolve().parent


def require(value, message):
    if not value:
        raise ValueError(message)


def identity(path):
    data = path.read_bytes()
    return {"path": path.as_posix(), "bytes": len(data), "sha256": hashlib.sha256(data).hexdigest()}


def enum_values(metadata, index):
    schema = metadata.schema(index)
    require(schema["is_enum"], f"Type {index} is not an enum")
    values = []
    for field in schema["fields"]:
        default = field.get("default")
        if default is None:
            continue
        type_name = metadata.byval_names.get(default["type_index"])
        if type_name == "System.Int32":
            value, size = default["int32_value"], default["encoded_size"]
        elif type_name == "System.Int16":
            value, size = struct.unpack_from("<h", metadata.data, default["offset"])[0], 2
        else:
            raise ValueError(f"Unsupported enum underlying type: {type_name}")
        values.append({"name": field["name"], "value": value, "defaultOffset": default["offset"],
                       "defaultBytes": metadata.data[default["offset"]:default["offset"] + size].hex()})
    return {"name": schema["name"], "declaringType": schema["declaring_type"]["exact_byval_name"],
            "image": schema["image"], "typeDefinitionIndex": index,
            "typeRange": schema["range"], "values": values}


def aliases(enum):
    result = collections.defaultdict(list)
    for entry in enum["values"]:
        result[entry["value"]].append(entry["name"])
    return dict(result)


def missing_item(item, text_rows):
    ident = item["gameItemId"]
    rows = [r for r in text_rows if r["gameItemId"] == ident]
    desc = next((r["text"] for r in rows if r["kind"] == 1), None)
    # These are evidence categories, never replacement item names or playability judgments.
    if desc is not None and desc.startswith("GMイベント用"):
        assessment = "explicit-GM-event-description-name-absent"
    elif (item["master"]["type_id"] == 5 and 90000 <= ident <= 94015
          and ident // 1000 in (90, 91, 92, 93, 94) and ident % 1000 < 16
          and item["master"]["model"] == ident - 20000):
        assessment = "regular-unnamed-box-series-internal-or-placeholder-candidate-only"
    else:
        assessment = "unresolved-name-absent-no-internal-status-proven"
    return {"gameItemId": ident, "typeId": item["master"]["type_id"],
            "model": item["master"]["model"], "masterDecodedOffset": item["master"]["decoded_offset"],
            "hasPropertyRecord": item["propertyRecord"] is not None,
            "nameRowPresent": any(r["kind"] == 0 for r in rows),
            "descriptionRowPresent": desc is not None, "descriptionText": desc,
            "textRows": rows, "assessment": assessment, "replacementName": None}


def audit(args):
    catalog = json.loads(args.catalog.read_text(encoding="utf-8"))
    version = catalog["cacheVersion"]
    parser = runpy.run_path(str(HERE / "extract-toram-item-assets.py"))
    master_parser = runpy.run_path(str(HERE / "decode-toram-item-master.py"))
    metadata_type = runpy.run_path(str(HERE / "extract-il2cpp-item-schema.py"))["Metadata"]
    metadata = metadata_type(args.metadata.read_bytes())
    by_name = {metadata.full_name(t): i for i, t in enumerate(metadata.types)}
    names = ["ItemType", "Toram.Common.Items.ItemType", "EquipType", "Toram.Common.Items.EquipType",
             "ItemFlag", "ElementType", "Toram.Common.Items.MaterialType"]
    enums = []
    for name in names:
        owner = "ItemDBData" if name in ("ItemType", "EquipType", "ItemFlag") else None
        candidates = [i for i, t in enumerate(metadata.types) if metadata.full_name(t) == name
                      and metadata.byval_names.get(t[3]) == owner]
        require(len(candidates) == 1, f"Ambiguous enum identity: {owner}.{name}")
        enums.append(enum_values(metadata, candidates[0]))
    enum_index = {e["name"]: e for e in enums}
    require(enums[0]["name"] == "ItemType" and enums[2]["name"] == "EquipType", "Enum identity mismatch")
    binary = args.cache / "cache/BynaryData" / version
    master_path, property_path = binary / "ItemMaster.decoded.bin", binary / "ItemProperties.decoded.bin"
    master = master_parser["parse"](master_path.read_bytes())
    properties = master_parser["parse_properties"](property_path.read_bytes())
    text_path = args.cache / "cache/GameScene_kr" / version / "Item_kr.decoded.bin"
    text = parser["parse_text"](text_path.read_bytes(), True)
    items = catalog["items"]
    require(master == [i["master"] for i in items], "Catalog master differs from decoded source")
    require(len(items) == len({i["gameItemId"] for i in items}), "Duplicate catalog IDs")
    for item in items:
        prop = item["propertyRecord"]
        source = properties.get(item["gameItemId"])
        require((source is None) == (prop is None), "Property join mismatch")
        if source is not None:
            require(source["raw_record_hex"] == prop["raw_record_hex"], "Property bytes mismatch")
    joined, orphans = parser["join_items"](master, properties, {"kr": text}, {}, {})
    require(orphans == catalog["orphanTexts"], "Orphan rows differ from decoded source")
    require(all(a["names"] == b["names"] and a["descriptions"] == b["descriptions"]
                for a, b in zip(items, joined)), "Catalog text join mismatch")
    missing = [missing_item(i, text) for i in items if not i["names"]]
    missing_ids, orphan_ids = {r["gameItemId"] for r in missing}, {r["gameItemId"] for r in orphans}
    history = []
    for path in sorted((args.cache / "cache").glob("*/*/Item_kr.decoded.bin")):
        rows = parser["parse_text"](path.read_bytes(), True)
        history.append({**identity(path), "kind": "localized-item-text", "version": path.parent.name,
                        "recordCount": len(rows), "allBytesConsumed": True,
                        "missingNameIdsFound": sorted({r["gameItemId"] for r in rows
                                                       if r["kind"] == 0 and r["gameItemId"] in missing_ids})})
    for path in sorted((args.cache / "cache/BynaryData").glob("*/ItemMaster.decoded.bin")):
        rows = master_parser["parse"](path.read_bytes())
        history.append({**identity(path), "kind": "item-master", "version": path.parent.name,
                        "recordCount": len(rows), "allBytesConsumed": True,
                        "orphanTextIdsFound": sorted({r["id"] for r in rows} & orphan_ids)})
    groups = collections.defaultdict(list)
    for item in items:
        groups[item["master"]["type_id"]].append(item["gameItemId"])
    legacy, common = aliases(enums[0]), aliases(enums[1])
    types = [{"typeId": key, "legacyEnumNames": legacy.get(key, []), "commonEnumNames": common.get(key, []),
              "count": len(ids), "gameItemIds": ids} for key, ids in sorted(groups.items())]
    refs = []
    elements = aliases(enum_index["ElementType"])
    for cap_id in (65, 189):
        for item in items:
            for cap in (item["propertyRecord"] or {}).get("caps", []):
                if cap["cap_id"] == cap_id:
                    refs.append({"gameItemId": item["gameItemId"], "slot": cap["slot"],
                                 "capId": cap_id, "rawValue": cap["value"],
                                 "elementEnumNames": elements.get(cap["value"], []) if cap_id == 65 else None,
                                 "skillId": None})
    flags = aliases(enum_index["ItemFlag"])
    mask = sum(value for value in flags if value and value & (value - 1) == 0)
    flag_counts = collections.Counter(i["master"]["flag_raw"] for i in items)
    flag_rows = [{"rawValue": raw, "count": count,
                  "knownBitAliases": [{"value": bit, "names": names} for bit, names in flags.items()
                                      if bit and bit & (bit - 1) == 0 and raw & bit],
                  "unresolvedBits": raw & ~mask} for raw, count in sorted(flag_counts.items())]
    resources = None
    if args.resources:
        if args.unitypy_path:
            sys.path.insert(0, str(args.unitypy_path))
        import UnityPy
        before = identity(args.resources)
        environment = UnityPy.load(str(args.resources))
        assets = []
        for obj in environment.objects:
            if obj.type.name == "TextAsset":
                asset = obj.parse_as_object()
                data = asset.m_Script.encode("utf-8", "surrogateescape")
                assets.append({"name": asset.m_Name, "pathId": obj.path_id, "bytes": len(data),
                               "sha256": hashlib.sha256(data).hexdigest()})
        require(before == identity(args.resources), "Installed resources changed during read")
        resources = {"source": before, "textAssets": assets,
                     "itemTextAssets": [a for a in assets if a["name"].startswith("Item_")]}
    wanted = {"ItemDBData": ["get_AvatarCategory", "IsSubWeapon", "CheckArmorAbility", "CheckEquipItem",
                             "CheckAvatarEquipItem", "CheckWeaponItem", "CheckCristaItem", "CheckPowerUpCristaItem"],
              "ItemManager": ["GetItemEquipedType", "GetSelectItemEquipType"],
              "SkillManager": ["GetAvatarSkillId", "IsAvatarSkill", "UpdateAvatarSkill"],
              "SkillTextManager": ["Get", "GetSkillName"], "MasterSkillDataManager": ["GetSkillMaster"]}
    method_pointers = {r["token"]: r for r in csv.DictReader(args.methods.open(encoding="utf-8"), delimiter="\t")}
    methods = []
    for class_name, method_names in wanted.items():
        for method in metadata.schema(by_name[class_name])["methods"]:
            if method["name"] in method_names:
                pointer = method_pointers.get(method["token"], {})
                methods.append({"class": class_name, "method": method["name"], "token": method["token"],
                                "rva": pointer.get("rva"), "parameters": method["parameters"],
                                "evidence": "metadata-declaration-and-saved-native-pointer-only"})
    result = {"schemaVersion": 1, "authority": "saved-local-byte-reference-audit", "cacheVersion": version,
              "sources": [identity(p) for p in [args.catalog, args.metadata, master_path, property_path, text_path, args.methods]],
              "counts": {"items": len(items), "missingNames": len(missing),
                         "missingAllTextIds": sum(not r["textRows"] for r in missing),
                         "orphanTextRows": len(orphans), "orphanTextIds": len(orphan_ids),
                         "unknownItemTypeIds": [r["typeId"] for r in types if not r["legacyEnumNames"] and not r["commonEnumNames"]],
                         "itemsWithUnresolvedFlagBits": sum(r["count"] for r in flag_rows if r["unresolvedBits"])},
              "validation": {"masterMatchesDecodedSource": True, "propertyHexMatchesDecodedSource": True,
                             "textJoinsMatchDecodedSource": True, "sourceParsersConsumeEntireFiles": True},
              "enums": enums, "typeGroups": types, "flagValues": flag_rows, "missingNameItems": missing,
              "orphanTexts": orphans, "historicalCoverage": history, "installedResources": resources,
              "specialPropertyReferences": refs, "relatedNativeMethods": methods,
              "limitations": ["Missing rows are proven only within listed local snapshots, not every game language or server release.",
                              "Empty descriptions are preserved separately from absent description rows.",
                              "GM labels and regular unnamed series do not prove deletion, availability, or a replacement name.",
                              "ItemType aliases and same-valued legacy/common enum constants are retained; type 200 is unresolved.",
                              "EquipType declares slots but a type-to-slot rule is not inferred from enum number equality.",
                              "ElementType names are metadata constants; cap 65 UI context and cap 189 skill conversion need native confirmation.",
                              "ItemFlag value 1 has two names; high unknown bits are not discarded or interpreted as ordinary flags.",
                              "No app/calculation changes, process access, network requests, or skill formulas are performed."]}
    require(args.output.resolve() not in {p.resolve() for p in [args.catalog, args.metadata, args.methods]}, "Output overlaps source")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(result["counts"]))


def self_test():
    class Int16Metadata:
        data = bytes.fromhex("f9ff")
        byval_names = {1: "System.Int16"}

        def schema(self, index):
            return {"is_enum": True, "name": "Example", "image": "Example.dll", "range": {},
                    "declaring_type": {"exact_byval_name": None},
                    "fields": [{"name": "Negative", "default": {"type_index": 1, "offset": 0}}]}

    assert enum_values(Int16Metadata(), 0)["values"][0]["value"] == -7
    enum = {"values": [{"value": 1, "name": "A"}, {"value": 1, "name": "Alias"}]}
    assert aliases(enum) == {1: ["A", "Alias"]}
    item = {"gameItemId": 90015, "master": {"type_id": 5, "model": 70015, "decoded_offset": 4}, "propertyRecord": None}
    assert missing_item(item, [])["descriptionText"] is None
    row = {"gameItemId": 90015, "kind": 1, "text": "", "decodedOffset": 4}
    assert missing_item(item, [row])["descriptionText"] == ""
    assert missing_item(item, [row])["replacementName"] is None
    row["text"] = "GMイベント用(test)"
    assert missing_item(item, [row])["assessment"].startswith("explicit-GM")
    print("PASS: signed Int16 enums, aliases, absent versus empty text, no invented names")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--catalog", type=Path, default=Path("data/sources/toram-items/items.kr.77596232.json"))
    parser.add_argument("--cache", type=Path, default=Path("build/tmp/toram-item-extraction/game-77596232"))
    parser.add_argument("--metadata", type=Path, default=Path("build/tmp/toram-item-extraction/code-trace/runtime/current-source/global-metadata.dat"))
    parser.add_argument("--methods", type=Path, default=Path("build/tmp/toram-item-extraction/code-trace/runtime/all-native-methods.tsv"))
    parser.add_argument("--output", type=Path, default=Path("data/sources/toram-items/item-reference-audit.json"))
    parser.add_argument("--resources", type=Path)
    parser.add_argument("--unitypy-path", type=Path)
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    self_test() if args.self_test else audit(args)
