"""Extract auxiliary item tables from saved, decoded Toram cache files.

Uses the reviewed native loader layouts; never opens the game process.
"""

import argparse
import collections
import hashlib
import importlib.util
import json
from pathlib import Path
import struct


def require(value, message):
    if not value:
        raise ValueError(message)


class Reader:
    def __init__(self, data):
        self.data, self.pos = data, 0

    def read(self, fmt):
        size = struct.calcsize("<" + fmt)
        require(self.pos + size <= len(self.data), f"Truncated table at {self.pos}")
        value = struct.unpack_from("<" + fmt, self.data, self.pos)
        self.pos += size
        return value[0] if len(value) == 1 else value

    def count(self, fmt="i", minimum=1):
        value = self.read(fmt)
        require(0 <= value <= (len(self.data) - self.pos) // minimum, "Impossible count")
        return value

    def record(self, start, value):
        return {**value, "decodedOffset": start, "rawRecordHex": self.data[start:self.pos].hex()}

    def finish(self):
        require(self.pos == len(self.data), f"Trailing bytes at {self.pos}")


RANDOM_PREFIX = [
    ("Id", "h"), ("ConditionType1", "B"), ("ConditionVal1", "B"),
    ("ConditionType2", "B"), ("ConditionVal2", "B"), ("ActCount", "h"),
    ("MaxActCount", "h"), ("ActStatus", "B"), ("ReflectionRate", "h"),
    ("EffectTime", "B"), ("CoolDownTime", "B"), ("MaxStack", "h"), ("Flag", "i"),
]
RANDOM_SUFFIX = [
    ("Tier", "B"), ("EffectStatus", "B"), ("EffectReflectionRate", "h"),
    ("StackStatus", "B"), ("StackReflectionRate", "h"),
]
RECIPE_FIELDS = ["RecipeId", "Type", "ReleaseLv", "Price", "Difficulty", "CreateId", "CreateVal", "Category"]
RECIPE_FORMAT = "iBhihihB"
RECREATE_ENUM = "Toram.Common.Operations.Main.Shop.RecreateType"


def parse_random(data):
    reader = Reader(data)
    header = reader.read("i")
    count = reader.count(minimum=68)
    rows = []
    for _ in range(count):
        start = reader.pos
        row = {name: reader.read(fmt) for name, fmt in RANDOM_PREFIX}
        row["caps"] = [{"slot": slot + 1, "capId": reader.read("h"), "rawValue": reader.read("h")}
                       for slot in range(10)]
        row.update({name: reader.read(fmt) for name, fmt in RANDOM_SUFFIX})
        rows.append(reader.record(start, row))
    reader.finish()
    require(len({row["Id"] for row in rows}) == count, "Duplicate random property ID")
    return {"ignoredHeaderInt32": header, "records": rows}


def parse_recipe(data):
    reader = Reader(data)
    count = reader.count(minimum=24)
    rows = []
    for _ in range(count):
        start = reader.pos
        row = dict(zip(RECIPE_FIELDS, reader.read(RECIPE_FORMAT)))
        material_count = reader.count(minimum=8)
        materials = []
        for _ in range(material_count):
            material_start = reader.pos
            material = dict(zip(["RecipeNo", "Lv", "Id", "Val"], reader.read("BBih")))
            materials.append(reader.record(material_start, material))
        row["materials"] = materials
        rows.append(reader.record(start, row))
    reader.finish()
    require(len({row["RecipeId"] for row in rows}) == count, "Duplicate recipe ID")
    return {"records": rows}


def parse_support(data):
    reader = Reader(data)
    count = reader.count(minimum=8)
    groups = []
    for _ in range(count):
        start = reader.pos
        key = reader.read("i")
        items = [{"gameItemId": reader.read("i"), "decodedOffset": reader.pos - 4}
                 for _ in range(reader.count(minimum=4))]
        groups.append(reader.record(start, {"groupKeyRaw": key, "items": items}))
    reader.finish()
    require(len({row["groupKeyRaw"] for row in groups}) == count, "Duplicate support group key")
    return {"groups": groups}


def parse_ng(data):
    reader = Reader(data)
    count = reader.count(minimum=4)
    rows = []
    for _ in range(count):
        start = reader.pos
        rows.append(reader.record(start, {"gameItemId": reader.read("i")}))
    reader.finish()
    return {"records": rows}


def parse_models(data):
    reader = Reader(data)
    count = reader.count("B", minimum=3)
    groups = []
    for _ in range(count):
        start = reader.pos
        group = reader.read("B")
        rows = []
        for _ in range(reader.count("h", minimum=6)):
            record_start = reader.pos
            model, flag = reader.read("ih")
            rows.append(reader.record(record_start, {"modelId": model, "flagRaw": flag}))
        require(len({row["modelId"] for row in rows}) == len(rows), "Duplicate model in group")
        groups.append(reader.record(start, {"groupKeyRaw": group, "records": rows}))
    reader.finish()
    require(len({row["groupKeyRaw"] for row in groups}) == count, "Duplicate model group key")
    return {"groups": groups}


def encode(name, result):
    """Independent structural round trip, excluding all enriched join fields."""
    pack = lambda fmt, *args: struct.pack("<" + fmt, *args)
    if name == "ItemRandomPropertyMaster":
        parts = [pack("ii", result["ignoredHeaderInt32"], len(result["records"]))]
        for row in result["records"]:
            parts.extend(pack(fmt, row[key]) for key, fmt in RANDOM_PREFIX)
            parts.extend(pack("hh", cap["capId"], cap["rawValue"]) for cap in row["caps"])
            parts.extend(pack(fmt, row[key]) for key, fmt in RANDOM_SUFFIX)
    elif name == "RecipeMaster":
        parts = [pack("i", len(result["records"]))]
        for row in result["records"]:
            parts.append(pack(RECIPE_FORMAT, *(row[key] for key in RECIPE_FIELDS)))
            parts.append(pack("i", len(row["materials"])))
            parts.extend(pack("BBih", *(material[key] for key in ["RecipeNo", "Lv", "Id", "Val"]))
                         for material in row["materials"])
    elif name == "ItemCreateSupport":
        parts = [pack("i", len(result["groups"]))]
        for group in result["groups"]:
            parts.append(pack("ii", group["groupKeyRaw"], len(group["items"])))
            parts.extend(pack("i", row["gameItemId"]) for row in group["items"])
    elif name == "NGItem":
        parts = [pack("i", len(result["records"]))]
        parts.extend(pack("i", row["gameItemId"]) for row in result["records"])
    elif name == "EquipModelProperty":
        parts = [pack("B", len(result["groups"]))]
        for group in result["groups"]:
            parts.append(pack("Bh", group["groupKeyRaw"], len(group["records"])))
            parts.extend(pack("ih", row["modelId"], row["flagRaw"]) for row in group["records"])
    else:
        raise ValueError(name)
    return b"".join(parts)


PARSERS = {"ItemRandomPropertyMaster": parse_random, "RecipeMaster": parse_recipe,
           "ItemCreateSupport": parse_support, "NGItem": parse_ng, "EquipModelProperty": parse_models}


def source(path):
    data = path.read_bytes()
    return {"path": str(path.resolve()), "bytes": len(data), "sha256": hashlib.sha256(data).hexdigest()}


def operation_target(row, recreate_types, system_rows, prefix):
    if row["Type"] == 2:
        name = recreate_types.get(row["Category"])
        require(name is not None, f"Unknown appearance category {row['Category']}")
        key = prefix + name
        rows = system_rows.get(key, [])
        require(rows, f"Missing appearance category text {key}")
        texts = {r["text"] for r in rows}
        return {"namespace": "character-appearance-option", "status": "native-namespace-verified",
                "idRaw": row["CreateId"], "categoryId": row["Category"], "categoryEnumName": name,
                "targetIndexRaw": row["CreateId"],
                "categoryText": {"key": key, "rows": rows, "locale": "kr",
                                 "textConsensus": next(iter(texts)) if len(texts) == 1 else None,
                                 "finalUiObserved": False},
                "selectionRule": "RecreateType category selects recipe group; CreateId equals requested appearance option ID",
                "displayIndexNote": "UI display order may use a runtime model list; raw ID is not always displayed ID minus one."}
    require(row["Type"] == 3 and row["Category"] == 0 and row["CreateId"] == 0,
            "Unexpected collection bag recipe namespace")
    require(1 <= row["CreateVal"] <= 50, "Unreviewed collection bag expansion step")
    require(system_rows.get("ItemBagPanelAddCollectSlotTitle"), "Missing collection bag expansion label")
    return {"namespace": "collect-bag-expansion-step", "status": "native-namespace-verified",
            "idRaw": row["CreateId"], "targetExpansionStep": row["CreateVal"],
            "selectionRule": "CreateVal equals GameUserDataManager.CollectItemSlot + 1",
            "placeholderCreateIdIsNotItemId": True,
            "labelText": {"key": "ItemBagPanelAddCollectSlotTitle",
                          "rows": system_rows.get("ItemBagPanelAddCollectSlotTitle", []),
                          "locale": "kr", "finalUiObserved": False},
            "note": "Expansion progression index, not total collection-bag capacity or an item ID."}


def extract(game_root, catalog_path, native_root, bonus_path, destination):
    catalog = json.loads(catalog_path.read_text(encoding="utf-8"))
    require(catalog["cacheVersion"] == "77596232", "Review native loader evidence for a different cache version")
    items = {row["gameItemId"]: row for row in catalog["items"]}
    require(len(items) == len(catalog["items"]), "Duplicate catalog ID")
    bonuses = json.loads(bonus_path.read_text(encoding="utf-8"))["by_id"]
    native_map_path = native_root / "native-map.json"
    native_map = json.loads(native_map_path.read_text(encoding="utf-8"))
    require(native_map["sources"]["metadata"]["sha256"] ==
            "f0cf212a7c7dca1973a401bda6d208549c13f57f0bbdb8782e5d607ed7e8789f", "Unreviewed metadata")
    require(native_map["validation"]["snapshot_digest_matches_capture"], "Invalid native map")
    metadata_spec = importlib.util.spec_from_file_location("item_metadata", Path(__file__).with_name("extract-il2cpp-item-schema.py"))
    metadata_module = importlib.util.module_from_spec(metadata_spec)
    metadata_spec.loader.exec_module(metadata_module)
    metadata_path = Path(native_map["sources"]["metadata"]["path"])
    require(source(metadata_path)["sha256"] == native_map["sources"]["metadata"]["sha256"], "Metadata source changed")
    metadata = metadata_module.Metadata(metadata_path.read_bytes())
    enums = {}
    for index, declaration in enumerate(metadata.types):
        name = metadata.full_name(declaration)
        if name in {"recipeType", "ModelFlag", "AvatarModelFlag", "BodyModelFlag", "OptionModelFlag", RECREATE_ENUM}:
            enums[name] = metadata.schema(index)
    recipe_types = {f["default"]["int32_value"]: f["name"] for f in enums["recipeType"]["fields"]
                    if "int32_value" in f.get("default", {})}
    require(recipe_types == {0: "Smith", 1: "Synthetic", 2: "Recreate", 3: "CollectSlot"}, "Recipe type contract changed")
    recreate_types = {f["default"]["int32_value"]: f["name"] for f in enums[RECREATE_ENUM]["fields"]
                      if "int32_value" in f.get("default", {})}
    tables = {}
    for name, parser in PARSERS.items():
        path = game_root / "cache/BynaryData/77596232" / f"{name}.decoded.bin"
        data = path.read_bytes()
        result = parser(data)
        require(encode(name, result) == data, f"Round-trip mismatch: {name}")
        tables[name] = {"status": "native-loader-layout-verified", "source": source(path),
                        "validation": {"consumedBytes": len(data), "eof": True, "byteExactRoundTrip": True}, **result}

    def reference(ident):
        return {"gameItemId": ident, "masterPresent": ident in items}

    spec = importlib.util.spec_from_file_location("item_assets", Path(__file__).with_name("extract-toram-item-assets.py"))
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    reference_spec = importlib.util.spec_from_file_location("reference_texts", Path(__file__).with_name("extract-toram-item-reference-texts.py"))
    reference_module = importlib.util.module_from_spec(reference_spec)
    reference_spec.loader.exec_module(reference_module)
    text_manifest_path = bonus_path.parent / "item-special-references.json"
    text_manifest = json.loads(text_manifest_path.read_text(encoding="utf-8"))
    system_source = next(row for row in text_manifest["sources"]["textAssets"] if row["name"] == "System_kr")
    system_path = Path(system_source["decoded"]["path"])
    require(source(system_path)["sha256"] == system_source["decoded"]["sha256"], "System text source changed")
    system_rows = collections.defaultdict(list)
    for row in reference_module.parse(system_path.read_bytes(), False, module.Reader):
        system_rows[row["key"]].append(row)
    mapped_path = Path(native_map["sources"]["mapped_image"]["path"])
    require(source(mapped_path)["sha256"] == native_map["sources"]["mapped_image"]["sha256"], "Saved module source changed")
    mapped = mapped_path.read_bytes()
    base = int(native_map["image_base"], 16)
    prefix_reference_rva = 0x7fff62450488 - 0x7fff5f250000
    encoded = struct.unpack_from("<Q", mapped, prefix_reference_rva)[0]
    require(encoded & 1 and encoded >> 29 == 5, "Expected uninitialized StringLiteral metadata usage")
    literal_index = (encoded >> 1) & 0x0FFFFFFF
    size, offset = metadata.records("string_literals", struct.Struct("<II"))[literal_index]
    prefix = metadata.block("literal_data")[offset:offset + size].decode("utf-8")
    require(prefix == "RecreateRecipeType", "Appearance text lookup prefix changed")
    literal_evidence = {"referenceRva": hex(prefix_reference_rva), "encodedUsage": hex(encoded),
                        "stringLiteralIndex": literal_index, "text": prefix,
                        "metadataRange": {"offset": metadata.tables["literal_data"]["offset"] + offset, "bytes": size}}
    mapper_spec = importlib.util.spec_from_file_location("native_mapper", Path(__file__).with_name("map-il2cpp-methods.py"))
    mapper = importlib.util.module_from_spec(mapper_spec)
    mapper_spec.loader.exec_module(mapper)
    bcl_image = next(image for image in metadata.images if metadata.string(image[0]) == "mscorlib.dll")
    bcl_methods = [method for method in metadata.methods if bcl_image[2] <= method[1] < bcl_image[2] + bcl_image[3]]
    bcl_module = mapper.find_module(mapped, base, "mscorlib.dll", max(method[6] & 0xFFFFFF for method in bcl_methods))
    bcl_calls = []
    for method in bcl_methods:
        if metadata.full_name(metadata.types[method[1]]) not in {"System.Enum", "System.String"}:
            continue
        mapping = mapper.pointer_for_token(mapped, base, bcl_module, method[6])
        if mapping["rva"] in {"0x1dfddb0", "0x1c21970"}:
            bcl_calls.append({"class": metadata.full_name(metadata.types[method[1]]), "method": metadata.string(method[0]),
                              "token": hex(method[6]), "module": "mscorlib.dll", **mapping})
    require({(row["class"], row["method"]) for row in bcl_calls} ==
            {("System.Enum", "ToString"), ("System.String", "Concat")}, "Appearance lookup call identities changed")
    text_path = game_root / "cache/GameScene_kr/77596232/ItemRandomProperty_kr.decoded.bin"
    texts = module.parse_text(text_path.read_bytes(), True)
    by_random_id = collections.defaultdict(dict)
    for row in texts:
        by_random_id[row["gameItemId"]][str(row["kind"])] = {
            "text": row["text"], "decodedOffset": row["decodedOffset"]}
    random_ids = {row["Id"] for row in tables["ItemRandomPropertyMaster"]["records"]}
    for row in tables["ItemRandomPropertyMaster"]["records"]:
        row["localizedTextByKind"] = {"kr": by_random_id.get(row["Id"], {})}
        for cap in row["caps"]:
            cap["enumName"] = bonuses.get(str(cap["capId"]))
    tables["ItemRandomPropertyMaster"]["textSource"] = source(text_path)
    tables["ItemRandomPropertyMaster"]["orphanTextIds"] = sorted(set(by_random_id) - random_ids)
    tables["ItemRandomPropertyMaster"]["missingTextIds"] = sorted(random_ids - set(by_random_id))
    tables["ItemRandomPropertyMaster"]["itemAssignment"] = {
        "status": "assignment-not-established-by-this-parser",
        "note": "Matching numerical random-property IDs to item IDs is not a relationship; explicit item cap/instance references require their own trace."}

    recipe_inputs = []
    for row in tables["RecipeMaster"]["records"]:
        row["recipeTypeName"] = recipe_types.get(row["Type"])
        if row["Type"] in (0, 1):
            row["createdItem"] = reference(row["CreateId"])
        else:
            row["operationTarget"] = operation_target(row, recreate_types, system_rows, prefix)
        for material in row["materials"]:
            if material["Lv"] == 0:
                material["reference"] = {"kind": "item", **reference(material["Id"])}
                recipe_inputs.append(material["Id"])
            else:
                material["reference"] = {"kind": "material-point", "materialId": material["Id"],
                                         "levelRaw": material["Lv"]}
    appearance_rows = [row for row in tables["RecipeMaster"]["records"] if row["Type"] == 2]
    slot_rows = [row for row in tables["RecipeMaster"]["records"] if row["Type"] == 3]
    require(len({(r["Category"], r["CreateId"]) for r in appearance_rows}) == len(appearance_rows),
            "Duplicate appearance option key")
    require(sorted(row["CreateVal"] for row in slot_rows) == list(range(1, 51)), "Bag expansion progression changed")
    tables["RecipeMaster"]["operationNamespaceValidation"] = {
        "appearanceRows": len(appearance_rows), "appearanceCategoryCounts": dict(collections.Counter(
            row["operationTarget"]["categoryEnumName"] for row in appearance_rows)),
        "appearanceKeysUnique": True, "appearanceCategoryTextsFound": len(appearance_rows),
        "collectionBagRows": len(slot_rows), "collectionBagStepsExactly1Through50": True,
        "itemReferencesCreatedForOperationRows": 0}
    for row in tables["NGItem"]["records"]:
        row["reference"] = reference(row["gameItemId"])
    for group in tables["ItemCreateSupport"]["groups"]:
        for row in group["items"]:
            row["reference"] = reference(row["gameItemId"])
    # shortcut: exact (type_id, model) joins are exposed as candidates until each caller's type conversion is traced.
    model_candidates = collections.defaultdict(list)
    for item in items.values():
        master = item["master"]
        model_candidates[(master["type_id"], master["model"])].append(item["gameItemId"])
    for group in tables["EquipModelProperty"]["groups"]:
        group["flagEnum"] = {20: "BodyModelFlag", 21: "OptionModelFlag", 25: "AvatarModelFlag",
                             27: "OptionModelFlag"}.get(group["groupKeyRaw"])
        for row in group["records"]:
            row["sameTypeAndModelItemCandidates"] = model_candidates[(group["groupKeyRaw"], row["modelId"])]
    body_group = next((group for group in tables["EquipModelProperty"]["groups"] if group["groupKeyRaw"] == 20), None)
    model_one = next((row for row in body_group["records"] if row["modelId"] == 1), None) if body_group else None
    tables["EquipModelProperty"]["runtimeDerivedEntries"] = []
    if model_one:
        tables["EquipModelProperty"]["runtimeDerivedEntries"].append({
            "groupKeyRaw": 20, "modelId": 0, "copiedFromModelId": 1, "flagRaw": model_one["flagRaw"],
            "source": "MasterModelDataManager.ReadMasterData post-load dictionary assignment",
            "sameTypeAndModelItemCandidates": model_candidates[(20, 0)]})
    tables["EquipModelProperty"]["itemJoinStatus"] = "candidate-exact-key-match-caller-conversions-not-yet-verified"

    opaque_path = game_root / "cache/BynaryData/77596232/ItemDorpData.decoded.bin"
    opaque = opaque_path.read_bytes()
    leading_count = struct.unpack_from("<i", opaque)[0]
    require(leading_count >= 0 and len(opaque) == 4 + leading_count * 13,
            "Reviewed opaque 13-byte partition no longer fits")
    chunks = []
    for index in range(leading_count):
        offset = 4 + index * 13
        candidate = struct.unpack_from("<i", opaque, offset)[0]
        chunks.append({"ordinal": index, "decodedOffset": offset,
                       "rawRecordHex": opaque[offset:offset + 13].hex(),
                       "leadingInt32Candidate": candidate, "candidateMatchesItemMaster": candidate in items})
    require(struct.pack("<i", leading_count) + b"".join(bytes.fromhex(row["rawRecordHex"]) for row in chunks) == opaque,
            "Opaque partition round-trip mismatch")
    tables["ItemDorpData"] = {"status": "unresolved-loader", "source": source(opaque_path),
                              "observedLeadingInt32": leading_count, "uninterpreted13ByteChunks": chunks,
                              "partitionValidation": {"consumedBytes": len(opaque), "eof": True,
                                                      "byteExactRoundTrip": True,
                                                      "candidateIdsMatchingMaster": sum(r["candidateMatchesItemMaster"] for r in chunks)},
                              "note": "13-byte partition and leading integers are observations, not a native-verified schema or item ID/drop-rate semantics."}
    evidence = []
    evidence_names = {"ReadMasterData", "ReadCreateSupportItem", "SetNGItem", "LoadData", ".ctor"}
    index = json.loads((native_root / "pseudocode/index.json").read_text(encoding="utf-8"))
    for row in index:
        if row["name"] not in evidence_names or row["class"] not in {
                "ItemRandomPropertyMaster", "ItemRandomPropertyMasterData", "MasterItemDataManager",
                "ItemTextManager", "RecipeDBDataManager", "RecipeDBData", "RecipeMaterialData", "MasterModelDataManager"}:
            continue
        if row["name"] == ".ctor" and row["class"] not in {"ItemRandomPropertyMasterData", "RecipeDBData", "RecipeMaterialData"}:
            continue
        path = native_root / "pseudocode" / row["pseudocodeFile"]
        evidence.append({"class": row["class"], "method": row["name"], "token": row["token"],
                         "rva": row["rva"], "returnType": row["return_type"], "parameters": row["parameters"],
                         "pseudocodeSha256": source(path)["sha256"], "pseudocode": path.read_text(encoding="utf-8")})
    getter_offsets = []
    for row in native_map["methods"]:
        if row["class"] == "ItemRandomPropertyMasterData" and row["name"].startswith("get_"):
            getter_offsets.append({key: row[key] for key in ["name", "token", "rva", "code_preview_hex"]})
    for name in ["SmithManufacture-CheckManufactureMaterial-7fff5fc8bf20.c"]:
        path = native_root / "pseudocode-extra" / name
        evidence.append({"class": "SmithManufacture", "method": "CheckManufactureMaterial", "rva": "0xa3bf20",
                         "pseudocodeSha256": source(path)["sha256"], "pseudocode": path.read_text(encoding="utf-8")})
    for row in json.loads((native_root / "pseudocode-models/index.json").read_text(encoding="utf-8")):
        path = native_root / "pseudocode-models" / row["pseudocodeFile"]
        evidence.append({"class": row["class"], "method": row["name"], "token": row["token"], "rva": row["rva"],
                         "returnType": row["return_type"], "pseudocodeSha256": source(path)["sha256"],
                         "pseudocode": path.read_text(encoding="utf-8")})
    for folder in ["pseudocode-targets-v2", "pseudocode-namespaces"]:
        for row in json.loads((native_root / folder / "index.json").read_text(encoding="utf-8")):
            if folder == "pseudocode-targets-v2" and row["class"] in {"SmithManufacture", "<selectElementWait>d__76"}:
                continue
            path = native_root / folder / row["pseudocodeFile"]
            require(row["decompileCompleted"], f"Incomplete namespace code: {path.name}")
            evidence.append({"class": row["class"], "method": row["name"], "token": row["token"], "rva": row["rva"],
                             "pseudocodeSha256": source(path)["sha256"], "pseudocode": path.read_text(encoding="utf-8")})
    counts = {
        "itemMaster": len(items), "randomProperties": len(random_ids),
        "randomPropertiesWithText": len(random_ids & set(by_random_id)),
        "recipes": len(tables["RecipeMaster"]["records"]),
        "recipeItemOutputs": sum(r["Type"] in (0, 1) for r in tables["RecipeMaster"]["records"]),
        "recipeOperationTargetsUnresolved": sum(r.get("operationTarget", {}).get("status") == "non-item-namespace-unresolved"
                                                 for r in tables["RecipeMaster"]["records"]),
        "recipeAppearanceTargets": len(appearance_rows), "recipeCollectBagSteps": len(slot_rows),
        "recipeCreatedItemsMissingMaster": sorted({r["CreateId"] for r in tables["RecipeMaster"]["records"]
                                                   if r["Type"] in (0, 1)} - set(items)),
        "recipeItemMaterialReferences": len(recipe_inputs),
        "recipeItemMaterialsMissingMaster": sorted(set(recipe_inputs) - set(items)),
        "recipeMaterialPointReferences": sum(m["Lv"] != 0 for r in tables["RecipeMaster"]["records"] for m in r["materials"]),
        "createSupportGroups": len(tables["ItemCreateSupport"]["groups"]),
        "createSupportItemReferences": sum(len(g["items"]) for g in tables["ItemCreateSupport"]["groups"]),
        "ngItemReferences": len(tables["NGItem"]["records"]),
        "modelGroups": len(tables["EquipModelProperty"]["groups"]),
        "models": sum(len(g["records"]) for g in tables["EquipModelProperty"]["groups"]),
    }
    result = {"schemaVersion": 1, "cacheVersion": catalog["cacheVersion"], "counts": counts,
              "catalogSource": source(catalog_path), "nativeSource": native_map["sources"],
              "evidenceKind": "saved-module-decompilation-and-byte-parser-not-runtime-execution",
              "nativeLoaderEvidence": evidence, "randomFieldGetterEvidence": getter_offsets, "metadataEnums": enums,
              "recipeTargetLookupRule": {"prefixLiteral": literal_evidence, "calls": bcl_calls,
                                         "systemTextSource": source(system_path),
                                         "systemTextBundleSource": text_manifest["sources"]["bundle"],
                                         "sourceManifest": source(text_manifest_path), "finalUiObserved": False},
              "tables": tables,
              "limitations": ["Random-property condition/status enum and flag meanings are retained raw; no combat formulas inferred.",
                              "NGItem membership is a text-manager list, not a claim that possession/trading is prohibited.",
                              "Create-support group keys remain raw; applicability/success formulas are not inferred.",
                              "Model flags are raw; exact type/model joins are candidates pending caller conversion tracing.",
                              "Recipe material-point IDs are not item IDs even when the same integer occurs in ItemMaster.",
                              "Recreate IDs are appearance option indices; CollectSlot CreateVal is an expansion step, not total capacity.",
                              "Appearance category labels are linked; runtime model-list ordering and final UI output remain unobserved.",
                              "ItemDorpData has no verified loader layout and remains opaque."]}
    inputs = [catalog_path, bonus_path, native_map_path, metadata_path, text_path, opaque_path,
              text_manifest_path, system_path, mapped_path]
    inputs.extend(game_root / "cache/BynaryData/77596232" / f"{name}.decoded.bin" for name in PARSERS)
    require(destination.resolve() not in {path.resolve() for path in inputs}, "Output must not replace a source")
    destination.parent.mkdir(parents=True, exist_ok=True)
    destination.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"output": str(destination.resolve()), **counts}, ensure_ascii=False))


def self_test():
    fixtures = {
        "ItemRandomPropertyMaster": {"ignoredHeaderInt32": 0, "records": [
            {**{key: index + 1 for index, (key, _) in enumerate(RANDOM_PREFIX + RANDOM_SUFFIX)},
             "caps": [{"capId": n, "rawValue": -n} for n in range(10)]}]},
        "RecipeMaster": {"records": [dict(zip(RECIPE_FIELDS, [51, 0, 1, 2026, 0, 14108, 1, 0]),
                                              materials=[{"RecipeNo": 1, "Lv": 0, "Id": 80424, "Val": 5},
                                                         {"RecipeNo": 2, "Lv": 1, "Id": 3, "Val": 10}])]},
        "ItemCreateSupport": {"groups": [{"groupKeyRaw": 2, "items": [{"gameItemId": 9101}]}]},
        "NGItem": {"records": [{"gameItemId": 5999}]},
        "EquipModelProperty": {"groups": [{"groupKeyRaw": 20, "records": [{"modelId": 1, "flagRaw": 4096}]}]},
    }
    for name, fixture in fixtures.items():
        data = encode(name, fixture)
        parsed = PARSERS[name](data)
        assert encode(name, parsed) == data
        assert parsed.get("records", parsed.get("groups"))[0]["rawRecordHex"]
        for malformed in [b"", data[:-1], data + b"\0"]:
            try:
                PARSERS[name](malformed)
            except (ValueError, struct.error):
                pass
            else:
                raise AssertionError(f"Accepted malformed {name}")
    assert struct.calcsize("<" + "".join(fmt for _, fmt in RANDOM_PREFIX + RANDOM_SUFFIX)) + 40 == 68
    random = parse_random(encode("ItemRandomPropertyMaster", fixtures["ItemRandomPropertyMaster"]))["records"][0]
    assert random["caps"][9] == {"slot": 10, "capId": 9, "rawValue": -9}
    assert random["Tier"] == fixtures["ItemRandomPropertyMaster"]["records"][0]["Tier"]
    system = {"RecreateRecipeTypeEyeColor": [{"key": "RecreateRecipeTypeEyeColor", "text": "눈동자 색"}],
              "ItemBagPanelAddCollectSlotTitle": [{"key": "ItemBagPanelAddCollectSlotTitle", "text": "수집칸 추가"}]}
    target = operation_target({"Type": 2, "Category": 205, "CreateId": 9}, {205: "EyeColor"}, system, "RecreateRecipeType")
    assert target["namespace"] == "character-appearance-option" and target["targetIndexRaw"] == 9
    assert target["categoryText"]["textConsensus"] == "눈동자 색" and "gameItemId" not in target
    target = operation_target({"Type": 3, "Category": 0, "CreateId": 0, "CreateVal": 50}, {}, system, "")
    assert target["namespace"] == "collect-bag-expansion-step" and target["targetExpansionStep"] == 50
    for invalid in [{"Type": 2, "Category": 999, "CreateId": 1},
                    {"Type": 3, "Category": 0, "CreateId": 1, "CreateVal": 1},
                    {"Type": 3, "Category": 0, "CreateId": 0, "CreateVal": 51}]:
        try:
            operation_target(invalid, {205: "EyeColor"}, system, "RecreateRecipeType")
        except ValueError:
            pass
        else:
            raise AssertionError("Invalid recipe target accepted")
    print("Item relations self-test PASS: five layouts, negative values, bounds, EOF, round trips and separate recipe namespaces")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--self-test", action="store_true")
    parser.add_argument("--game-root", type=Path, default=Path("build/tmp/toram-item-extraction/game-77596232"))
    parser.add_argument("--catalog", type=Path, default=Path("data/sources/toram-items/items.kr.77596232.json"))
    parser.add_argument("--native-root", type=Path, default=Path("build/tmp/toram-item-extraction/code-trace/runtime/relations"))
    parser.add_argument("--bonus", type=Path, default=Path("data/sources/toram-items/bonus-types.json"))
    parser.add_argument("--output", type=Path, default=Path("data/sources/toram-items/item-relations.json"))
    args = parser.parse_args()
    if args.self_test:
        self_test()
    else:
        extract(args.game_root, args.catalog, args.native_root, args.bonus, args.output)
