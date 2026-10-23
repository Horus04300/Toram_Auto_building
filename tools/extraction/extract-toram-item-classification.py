"""Reproduce reviewed native item classification from a saved catalog and C evidence."""
import argparse
import collections
import hashlib
import json
from pathlib import Path
import runpy


HERE = Path(__file__).resolve().parent
REVIEWED_CODE = {
    "ItemData-get_Function-7fff6007a1c0.c": "72cc3f9481b40685a08ccdb38e83cffc07960e0f42d5a39d7db71a137408f027",
    "ItemData-get_SlotMax-7fff6007a2d0.c": "e837194f57645632aa1be09021f3614f4e8be13d09fb3a88ba03f37118c2fe84",
    "ItemDBData-get_Function-7fff600745b0.c": "3da6608b0aa09d3c2e6429acf774b066d84a6c78cc8ee35e8ddb8aac846c8c2e",
    "ItemDBData-get_Stable-7fff5f597150.c": "4448ee0ae9c2209c29f834cc2be91cbe2da7c4a84fda028fce5ccd5a2cf94434",
    "ItemDBData-get_Range-7fff5f51f680.c": "663a3286f1ddcab2623a9aaa69501b0074d217cb7ab8a6135c9e092465a38ba8",
    "ItemDBData-get_SlotMax-7fff5f5970d0.c": "b772fe4617e6258492b93d88a52553387ae7014b1b8391cb4db206e7cb3b38d9",
    "ItemDBData-get_AvatarCategory-7fff60074550.c": "748689158287f48d8362bdb4275fd6b56081f3b6fd0beacfc796318c7e1fe390",
    "ItemDBData-IsSubWeapon-7fff600742e0.c": "2537d882860c1d72154e172ced507ed4f6ee56a2b519eaf2d7316f80600b5b36",
    "ItemDBData-CheckArmorAbility-7fff60074010.c": "7aa795ed61abfb86fa86f2229f9ac68fc11a94a4c51ce832a127791bdede34a1",
    "ItemDBData-CheckEquipItem-7fff5fd830e0.c": "db37ca88afca4e675c49222e446a83f06919564b4db4904fca528ebda2b59232",
    "ItemDBData-CheckAvatarEquipItem-7fff5fd830b0.c": "7e3f7ba0b82b3148cfe7f8459716cfa77ba7d14da52f377fb4168bcb849d9750",
    "ItemDBData-CheckWeaponItem-7fff60074030.c": "8a5b9fa19a1fe204a219f6c22c3a45e1d04f8ea5863d303e6ab819c4d75ad2f8",
    "ItemDBData-CheckCristaItem-7fff5fd830c0.c": "3cbf1187b5b8c7ebb47d9caac4b0ec14fe47205f57d6e3c4585b49b1b049233c",
    "ItemDBData-CheckPowerUpCristaItem-7fff5fd830f0.c": "4aeace839fffa5e0dace901f1207ba48131037fed4f58a557959fdcc06f66547",
    "ItemDBData-CheckUseItem-7fff5fd83100.c": "b211444cfd8f7b8f740f3ecc551b9cda198a536e95f26960936f9025c0f22f11",
    "ItemManager-GetItemEquipedType-7fff6007bc00.c": "ead7b9c489adda7c87b3e5e4babcd77e856de59794153a9931688449b59de4ff",
    "ItemManager-GetSelectItemEquipType-7fff5f9cb290.c": "113a77cea0e9ed33657d021f37121f2ceea0507e57781112f53d12aef46a9aed",
    "UIItemProperty-WeaponPropertys-7fff5f9d6cc0.c": "2614e797ae6106c6ae7b4671f8bc534288c5cdf66ca295e0cb46d0b538d57a0a",
}


def require(value, message):
    if not value:
        raise ValueError(message)


def source(path):
    data = path.read_bytes()
    return {"path": path.as_posix(), "bytes": len(data), "sha256": hashlib.sha256(data).hexdigest()}


def classify_type(value):
    require(type(value) is int and -(2 ** 31) <= value < 2 ** 31, "Item type must be a signed int32")
    checks = {
        "IsSubWeapon": value == 8 or ((value - 15) & 0xFFFFFFFF) <= 4 or value == 23,
        "CheckEquipItem": 7 <= value < 28,
        "CheckAvatarEquipItem": 25 <= value < 28,
        "CheckWeaponItem": value != 17 and 7 <= value < 20,
        "CheckCristaItem": ((value - 31) & 0xFFFFFFFF) < 6 or 61 <= value < 66,
        "CheckPowerUpCristaItem": 61 <= value < 66,
        "CheckUseItem": value in (5, 30, 50) or value < 3,
    }
    slot = (1 if 7 <= value <= 16 else 2 if value in (17, 18, 19, 23)
            else 3 if value == 20 else 4 if value == 21 else 5 if value == 22 else 0)
    return checks, slot


def packed_avatar_category(high, low):
    require(all(type(value) is int and 0 <= value <= 255 for value in (high, low)), "Expected two unsigned bytes")
    return high * 256 + low


def extract(args):
    extraction = runpy.run_path(str(HERE / "extract-toram-item-assets.py"))
    metadata_type = runpy.run_path(str(HERE / "extract-il2cpp-item-schema.py"))["Metadata"]
    enum_parser = runpy.run_path(str(HERE / "audit-toram-item-references.py"))
    catalog = json.loads(args.catalog.read_text(encoding="utf-8"))
    mapping = json.loads(args.native_map.read_text(encoding="utf-8"))
    metadata_source = source(args.metadata)
    require(metadata_source["sha256"] == catalog["bonusEnumSource"]["sha256"] == mapping["sources"]["metadata"]["sha256"],
            "Catalog, metadata and method map versions differ")
    require(mapping["sources"]["mapped_image"]["sha256"] == "2baf9dd6ad9f2a32f211c1f97a7ad0b94bf778d689afb054047f9ab621fd370e",
            "Unreviewed mapped image")
    index = json.loads((args.native / "index.json").read_text(encoding="utf-8"))
    index_by_file = {row["pseudocodeFile"]: row for row in index}
    mapped_methods = {(r["class"], r["token"]): r for r in mapping["methods"]}
    methods = []
    args.evidence_output.mkdir(parents=True, exist_ok=True)
    for filename, expected in REVIEWED_CODE.items():
        row = index_by_file[filename]
        require(row["decompileCompleted"], f"Incomplete decompilation: {filename}")
        require(source(args.native / filename)["sha256"] == expected, f"Unreviewed native code: {filename}")
        mapped = mapped_methods[(row["class"], row["token"])]
        require(row["rva"] == mapped["rva"] and row["status"] == "mapped", "Native method address mismatch")
        extraction["write_bytes"](args.evidence_output / filename, (args.native / filename).read_bytes())
        methods.append({**mapped, "pseudocodeFile": filename, "pseudocodeSha256": expected,
                        "decompileCompleted": True})
    metadata = metadata_type(args.metadata.read_bytes())
    enums = {}
    for name, owner in [("ItemType", "ItemDBData"), ("EquipType", "ItemDBData"), ("ArmorAbility", "ItemDBData"),
                        ("Toram.Common.Items.ItemType", None)]:
        indices = [i for i, t in enumerate(metadata.types) if metadata.full_name(t) == name
                   and metadata.byval_names.get(t[3]) == owner]
        require(len(indices) == 1, f"Ambiguous enum {owner}.{name}")
        enums[name] = enum_parser["enum_values"](metadata, indices[0])
    legacy = enum_parser["aliases"](enums["ItemType"])
    common = enum_parser["aliases"](enums["Toram.Common.Items.ItemType"])
    slots = enum_parser["aliases"](enums["EquipType"])
    counts = collections.Counter(item["master"]["type_id"] for item in catalog["items"])
    by_type = {}
    for value, count in sorted(counts.items()):
        checks, slot = classify_type(value)
        by_type[str(value)] = {"typeId": value, "count": count,
                               "itemTypeEnumNames": {"legacy": legacy.get(value, []), "common": common.get(value, [])},
                               "nativeChecks": checks,
                               "defaultSelectedEquipSlot": {"value": slot, "enumNames": slots[slot]}}
    avatar_categories = {str(item["gameItemId"]): packed_avatar_category(item["master"]["range_raw"], item["master"]["slot_max_raw"])
                         for item in catalog["items"] if by_type[str(item["master"]["type_id"])]["nativeChecks"]["CheckAvatarEquipItem"]}
    result = {
        "schemaVersion": 1, "authority": "reviewed-saved-native-code-plus-game-enum-constants",
        "cacheVersion": catalog["cacheVersion"], "joinKey": "String(item.master.type_id) -> byType",
        "sources": {"catalog": source(args.catalog), "metadata": metadata_source,
                    "nativeMap": source(args.native_map), "nativeIndex": source(args.native / "index.json"),
                    "snapshotIdentity": mapping["sources"]["mapped_image"]},
        "counts": {"items": sum(counts.values()), "observedTypes": len(counts), "classifiedItems": sum(counts.values()),
                   "avatarCategoryItems": len(avatar_categories),
                   "nativeCheckTrueCounts": {name: sum(row["count"] for row in by_type.values() if row["nativeChecks"][name])
                                             for name in next(iter(by_type.values()))["nativeChecks"]}},
        "byType": by_type, "enums": enums, "nativeMethods": methods,
        "avatarCategoryByItemId": avatar_categories,
        "derivedMasterRules": {"avatarCategoryGetter": {"method": "ItemDBData.get_AvatarCategory", "rva": "0xe24550",
                                                         "expression": "(range_raw << 8) + slot_max_raw",
                                                         "computedForTypes": [25, 26, 27],
                                                         "categoryNames": None}},
        "ruleExpressions": {
            "IsSubWeapon": "type == 8 || (uint32(type - 15) <= 4) || type == 23",
            "CheckEquipItem": "7 <= type && type < 28", "CheckAvatarEquipItem": "25 <= type && type < 28",
            "CheckWeaponItem": "type != 17 && 7 <= type && type < 20",
            "CheckCristaItem": "uint32(type - 31) < 6 || (61 <= type && type < 66)",
            "CheckPowerUpCristaItem": "61 <= type && type < 66",
            "CheckUseItem": "type == 5 || type == 30 || type == 50 || type < 3",
            "GetSelectItemEquipType": {"1": list(range(7, 17)), "2": [17, 18, 19, 23], "3": [20], "4": [21], "5": [22], "default": 0}},
        "dynamicRules": {
            "CheckArmorAbility": {"requires": "ItemData instance, not ItemDBData/master row",
                                  "nullInstanceResult": False, "predicate": "(uint8(instance[0x53]) & 3) == uint8(ArmorAbility)",
                                  "inferredFromMasterFlag": False},
            "GetItemEquipedType": {"requires": "ItemManager instance and inventory UUID, not gameItemId",
                                   "behavior": "First UUID match in current EquipData slots at 0x20,0x24,0x28,0x2c,0x30,0x34 returns 1..6; otherwise 0",
                                   "calledDuringExtraction": False}},
        "masterFieldObservations": {
            "function": {"getter": "signed i16 at ItemDBData+0x3e", "getterConversion": "none", "unit": None,
                         "uiEvidence": "WeaponPropertys boxes instance signed i16 at +0x42 and master signed i16 at +0x3e without scaling in displayed branches; their localized labels are unresolved here"},
            "stability": {"getter": "u8 at ItemDBData+0x40", "getterConversion": "none", "unit": None,
                          "uiEvidence": "WeaponPropertys boxes master byte +0x40 without scaling in one equip branch; the label is unresolved here"},
            "range_raw": {"getter": "u8 at ItemDBData+0x41", "getterConversion": "none", "unit": None,
                          "avatarCompositeRole": "High byte of get_AvatarCategory; not universally a distance",
                          "uiEvidence": "No distance conversion established by the selected getters or display branch"},
            "slot_max_raw": {"getter": "u8 at ItemDBData+0x42", "getterConversion": "none", "unit": None,
                             "avatarCompositeRole": "Low byte of get_AvatarCategory; observed master values 0..27 are not universally slot counts",
                             "instanceRule": "ItemData.get_SlotMax returns 0 for types 17..19, otherwise instance byte +0x44; this does not overwrite master raw byte",
                             "uiEvidence": "WeaponPropertys tests the instance getter while rendering the two instance slot fields"}},
        "limitations": [
            "Native predicates are the named helpers, not a complete equipment compatibility or legality check.",
            "Default selected slot is not the current equipped slot; IsSubWeapon and CheckWeaponItem overlap their default slot groups.",
            "Native equip range includes unknown numeric type 24; no guessed category is assigned to missing enum values.",
            "Legacy ItemDBData enums and Toram.Common enums are separate declarations with preserved aliases.",
            "CheckUseItem includes type 0 and negative values by its signed comparison; extracted master types are nonnegative.",
            "The getter bodies can share native addresses and carry another method's label in Ghidra; metadata token and RVA identify the requested alias.",
            "Armor customization requires an instance byte; no unrecognized master flag bits are decoded by this extraction.",
            "Avatar category IDs are the packed getter values; no category names or account ownership are inferred.",
            "Function as ATK/DEF, distance units, final combat stability formulas and runtime UI strings are not established here.",
            "No process access, game changes, app changes or combat-stat formula changes are performed."]}
    extraction["write_json"](args.output, result)
    extraction["write_json"](args.evidence_output / "index.json", methods)
    print(json.dumps(result["counts"]))


def self_test():
    sub = {8, 15, 16, 17, 18, 19, 23}
    for value in range(-256, 512):
        checks, slot = classify_type(value)
        assert checks["IsSubWeapon"] == (value in sub)
        assert checks["CheckEquipItem"] == (value in range(7, 28))
        assert checks["CheckAvatarEquipItem"] == (value in (25, 26, 27))
        assert checks["CheckWeaponItem"] == (value in set(range(7, 20)) - {17})
        assert checks["CheckCristaItem"] == (value in set(range(31, 37)) | set(range(61, 66)))
        assert checks["CheckUseItem"] == (value < 3 or value in (5, 30, 50))
        assert (slot != 0) == (value in set(range(7, 24)))
    assert classify_type(24)[0]["CheckEquipItem"] and classify_type(24)[1] == 0
    assert classify_type(15)[0]["IsSubWeapon"] and classify_type(15)[1] == 1
    assert packed_avatar_category(255, 27) == 65307 and packed_avatar_category(1, 2) == 258
    for invalid in (-1, 256, True):
        try:
            packed_avatar_category(invalid, 0)
        except ValueError:
            pass
        else:
            raise AssertionError("Invalid packed byte accepted")
    for invalid in (True, 1.5, "10", 2 ** 31, -(2 ** 31) - 1):
        try:
            classify_type(invalid)
        except ValueError:
            pass
        else:
            raise AssertionError("Invalid int32 type accepted")
    print("PASS: native branch boundaries, unsigned ranges, overlapping classes, default slots and int32 validation")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--catalog", type=Path, default=Path("data/sources/toram-items/items.kr.77596232.json"))
    parser.add_argument("--metadata", type=Path, default=Path("build/tmp/toram-item-extraction/code-trace/runtime/current-source/global-metadata.dat"))
    parser.add_argument("--native-map", type=Path, default=Path("build/tmp/toram-item-extraction/code-trace/runtime/item-classification/native-map.json"))
    parser.add_argument("--native", type=Path, default=Path("build/tmp/toram-item-extraction/code-trace/runtime/item-classification/pseudocode-final"))
    parser.add_argument("--evidence-output", type=Path, default=Path("data/sources/toram-items/native-classification"))
    parser.add_argument("--output", type=Path, default=Path("data/sources/toram-items/item-classification-rules.json"))
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    self_test() if args.self_test else extract(args)
