"""Join reviewed item evidence without replacing any raw field or changing the app."""

import argparse
import collections
import hashlib
import json
from pathlib import Path
import runpy
import struct


HERE = Path(__file__).resolve().parent
ASSETS = HERE.parents[1] / "data/sources/toram-items"
RUNTIME = HERE.parents[1] / "build/tmp/toram-item-extraction/code-trace/runtime"
WEAPONS = {96: 23, 97: 10, 98: 11, 99: 12, 100: 13, 101: 14, 102: 15, 103: 16,
           109: 17, 115: 9, 116: 8, 117: 19, 118: 18}
MARKERS = {*WEAPONS, 108, 119, 120}
SIGNED_TEMPLATES = {48, 188, *range(166, 176)}


def require(value, message):
    if not value:
        raise ValueError(message)


def identity(path):
    data = path.read_bytes()
    return {"path": path.as_posix(), "bytes": len(data), "sha256": hashlib.sha256(data).hexdigest()}


def load(path):
    return json.loads(path.read_text(encoding="utf-8"))


def condition_groups(caps):
    groups, assignments = [], {}
    for index, cap in enumerate(caps):
        if cap["cap_id"] not in MARKERS:
            continue
        count = cap["value"]
        require(1 <= count <= 10, "Unexpected condition instruction count")
        # BonusLines excludes empty caps; the UI counts physical slots separately.
        targets = [c for c in caps[index + 1:] if c["cap_id"] > 0][:count]
        ui_targets = caps[index + 1:index + 1 + count]
        require(len(targets) == count, "Truncated conditional group")
        require(all(c["cap_id"] not in MARKERS for c in targets), "Nested markers need native re-review")
        slots = [c["slot"] for c in targets]
        for slot in slots:
            require(slot not in assignments, "Overlapping condition groups need native re-review")
            assignments[slot] = cap["slot"]
        groups.append({"markerSlot": cap["slot"], "capId": cap["cap_id"], "instructionCount": count,
                       "targetSlots": slots, "uiTargetSlots": [c["slot"] for c in ui_targets],
                       "uiScopeMatchesBonusScope": slots == [c["slot"] for c in ui_targets]})
    return groups, assignments


def text_preview(cap_id, value, labels, constants):
    template_id, number = cap_id, value
    if cap_id in SIGNED_TEMPLATES and value < 0 and -cap_id in labels:
        template_id, number = -cap_id, -value
    template = labels.get(template_id)
    if template is None:
        return {"templateId": template_id, "plainTextCandidate": None, "status": "no-option-template"}
    if value < 0 and template_id == cap_id:
        template = template.replace(constants["negativeReplacement"], constants["empty"])
    # shortcut: G7 invariant preview only; compare the actual IL2CPP/UI numeric culture before claiming rendered identity.
    text = template.replace("{0:0.00}", format(number, ".2f"))
    text = text.replace("{0:F1}", format(number, ".1f")).replace("{0}", format(number, ".7g"))
    require("{" not in text and "}" not in text, "Unreviewed option numeric format")
    return {"templateId": template_id, "plainTextCandidate": text,
            "status": "native-template-selection-with-invariant-numeric-preview"}


def self_test():
    def cap(slot, ident, value=0):
        return {"slot": slot, "cap_id": ident, "value": value}
    groups, assignments = condition_groups([cap(1, 97, 2), cap(2, 1), cap(3, 2), cap(4, 3)])
    assert groups[0]["targetSlots"] == [2, 3] and assignments == {2: 1, 3: 1}
    groups, _ = condition_groups([cap(1, 97, 1), cap(2, 0), cap(3, 1)])
    assert groups[0]["targetSlots"] == [3] and not groups[0]["uiScopeMatchesBonusScope"]
    for caps in [[cap(1, 97, 2), cap(2, 1)], [cap(1, 97, 1), cap(2, 108, 1), cap(3, 1)]]:
        try:
            condition_groups(caps)
        except ValueError:
            pass
        else:
            raise AssertionError("Invalid group accepted")
    constants = {"negativeReplacement": "+", "empty": ""}
    labels = {1: "STR+{0}", 166: "ATK UP({0}%)", -166: "ATK DOWN({0}%)",
              137: "Reflect {0:0.00}%", 140: "Delay-{0:F1}s"}
    assert text_preview(166, -2.5, labels, constants)["plainTextCandidate"] == "ATK DOWN(2.5%)"
    assert text_preview(1, -3, labels, constants)["plainTextCandidate"] == "STR-3"
    assert text_preview(137, 1.25, labels, constants)["plainTextCandidate"] == "Reflect 1.25%"
    assert text_preview(140, 0.5, labels, constants)["plainTextCandidate"] == "Delay-0.5s"
    assert text_preview(999, 0, labels, constants)["plainTextCandidate"] is None
    print("PASS: condition counts, empty-slot distinction, invalid/nested groups and negative templates")


def connect(args):
    require(not args.output.exists(), "Output must be new")
    paths = [args.catalog, args.display, args.audit, args.special, args.relations, args.constants,
             args.metadata, args.property_text, args.classification, args.localizations]
    catalog, display, audit, special, relations, captured = [load(p) for p in paths[:6]]
    classification = load(args.classification)
    localizations = load(args.localizations)
    require(all(x["cacheVersion"] == catalog["cacheVersion"] for x in [audit, special, relations, classification, localizations]), "Cache versions differ")
    catalog_hash = identity(args.catalog)["sha256"]
    require(localizations["catalog"]["sha256"] == catalog_hash, "Localization source differs from catalog")
    expected_assets = {a["name"]: a for bundle in catalog["sources"] for a in bundle["assets"]
                       if a["name"] in {"ItemMaster", "ItemProperties"}}
    equivalence = localizations["masterEquivalence"]
    require({e["asset"] for e in equivalence} == set(expected_assets), "Public master equivalence is incomplete")
    for entry in equivalence:
        expected = expected_assets[entry["asset"]]
        require(entry["equalsSelectedCatalogSource"] and entry["rawSha256"] == expected["rawSha256"]
                and entry["decodedSha256"] == expected["decodedSha256"], "Public master bytes differ")
    require(display["evidence"]["catalogSha256"] == catalog_hash, "Display source differs from catalog")
    require(relations["catalogSource"]["sha256"] == catalog_hash, "Relation source differs from catalog")
    metadata_module = runpy.run_path(str(HERE / "extract-il2cpp-item-schema.py"))
    metadata = metadata_module["Metadata"](args.metadata.read_bytes())
    require(identity(args.metadata)["sha256"] == catalog["bonusEnumSource"]["sha256"], "Metadata differs")
    fields = [(i, f) for i, f in enumerate(metadata.fields) if metadata.string(f[0]) == captured["initializerFieldName"]]
    require(len(fields) == 1, "Initializer field not unique")
    index, field = fields[0]
    require(hex(field[2]) == captured["initializerToken"], "Initializer field token mismatch")
    default = metadata.defaults[index]
    offset = metadata.tables["default_data"]["offset"] + default[1]
    raw = metadata.data[offset:offset + 24]
    require(hashlib.sha256(raw).hexdigest() == captured["initializerFieldName"].lower(), "Compiler field hash mismatch")
    intervals = list(struct.unpack("<6i", raw))
    require(intervals == captured["limitList"] == [96, 103, 108, 109, 115, 120], "Condition intervals mismatch")
    parser = runpy.run_path(str(HERE / "extract-toram-item-assets.py"))
    text_rows = parser["parse_text"](args.property_text.read_bytes(), False)
    labels = {r["propertyId"]: r["text"] for r in text_rows}
    localized_items = {row["gameItemId"]: row for row in localizations["items"]}
    require(len(localized_items) == len(localizations["items"]) == len(catalog["items"]), "Localization item count differs")
    localized_properties = {row["propertyId"]: row["templates"] for row in localizations["propertyTexts"]}
    require(all(localized_properties[i]["kr"] == text for i, text in labels.items()), "Public Korean templates differ from local cache")
    locale_labels = {locale: {ident: templates[locale] for ident, templates in localized_properties.items()
                              if locale in templates} for locale in localizations["availableItemLocales"]}
    require({i for i in labels if i < 0} == {-48, -188, *range(-175, -165)}, "Unexpected negative template IDs")
    scaled = {(i["gameItemId"], c["slot"]): c for i in display["items"] for c in i["options"]}
    elements = {(x["gameItemId"], x["slot"]): x for x in special["elementReferences"]}
    skills = {(x["gameItemId"], x["slot"]): x for x in special["avatarSkillReferences"]}
    types = {x["typeId"]: x for x in audit["typeGroups"]}
    flags = {x["rawValue"]: x for x in audit["flagValues"]}
    missing = {x["gameItemId"]: x for x in audit["missingNameItems"]}
    recipes_created, recipes_consumed, support, models = [collections.defaultdict(list) for _ in range(4)]
    for r in relations["tables"]["RecipeMaster"]["records"]:
        ref = {"recipeType": r["Type"], "recipeId": r["RecipeId"]}
        if "createdItem" in r:
            recipes_created[r["CreateId"]].append(ref)
        for material in r["materials"]:
            if material["reference"]["kind"] == "item":
                recipes_consumed[material["Id"]].append({**ref, "materialSlot": material["RecipeNo"]})
    for group in relations["tables"]["ItemCreateSupport"]["groups"]:
        for r in group["items"]:
            support[r["gameItemId"]].append(group["groupKeyRaw"])
    ng = {r["gameItemId"] for r in relations["tables"]["NGItem"]["records"]}
    for group in relations["tables"]["EquipModelProperty"]["groups"]:
        for r in group["records"]:
            for ident in r["sameTypeAndModelItemCandidates"]:
                models[ident].append({"groupKeyRaw": group["groupKeyRaw"], "modelId": r["modelId"], "decodedOffset": r["decodedOffset"]})
    counts = collections.Counter()
    for item in catalog["items"]:
        ident, master = item["gameItemId"], item["master"]
        localized = localized_items[ident]
        require({k: v for k, v in localized["names"].items() if k == "kr"} == item["names"], "Public Korean name differs")
        require({k: v for k, v in localized["descriptions"].items() if k == "kr"} == item["descriptions"], "Public Korean description differs")
        item["names"], item["descriptions"] = localized["names"], localized["descriptions"]
        t, flag = types[master["type_id"]], flags[master["flag_raw"]]
        item["references"] = {
            "itemType": {"legacyEnumNames": t["legacyEnumNames"], "commonEnumNames": t["commonEnumNames"]},
            "flags": {"knownBitAliases": flag["knownBitAliases"], "unresolvedBits": flag["unresolvedBits"]},
            "nameAbsenceAssessment": missing.get(ident, {}).get("assessment"),
            "createdByRecipes": recipes_created[ident], "usedByRecipes": recipes_consumed[ident],
            "createSupportGroupKeysRaw": support[ident], "listedInTextManagerNGItem": ident in ng,
            "modelPropertyCandidates": models[ident], "modelPropertyJoinVerified": False}
        rules = classification["byType"][str(master["type_id"])]
        item["references"]["nativeChecks"] = rules["nativeChecks"]
        item["references"]["defaultSelectedEquipSlot"] = rules["defaultSelectedEquipSlot"]
        if str(ident) in classification["avatarCategoryByItemId"]:
            item["references"]["avatarCategory"] = classification["avatarCategoryByItemId"][str(ident)]
            counts["avatarCategories"] += 1
        if item["propertyRecord"] is None:
            continue
        caps = item["propertyRecord"]["caps"]
        groups, assignments = condition_groups(caps)
        item["propertyRecord"]["conditionGroups"] = groups
        counts["conditionGroups"] += len(groups)
        counts["conditionAffectedOptions"] += len(assignments)
        counts["uiBonusScopeDisagreements"] += sum(not g["uiScopeMatchesBonusScope"] for g in groups)
        for cap in caps:
            cap["templates"] = localized_properties.get(cap["cap_id"], {})
            if cap["cap_id"] <= 0:
                continue
            key = ident, cap["slot"]
            source = scaled[key]
            require((cap["cap_id"], cap["value"]) == (source["capId"], source["rawValue"]), "Raw/derived option mismatch")
            counts["options"] += 1
            cap["role"] = "equipment-condition-marker" if cap["cap_id"] in MARKERS else "option"
            cap["valueKind"] = ("condition-instruction-count" if cap["cap_id"] in MARKERS else
                                "element-enum" if cap["cap_id"] == 65 else
                                "avatar-skill-selector" if cap["cap_id"] == 189 else "bonus-operand")
            cap["conditionMarkerSlot"] = assignments.get(cap["slot"])
            cap["display"] = {"scaledValueFloat32": source["scaledValueFloat32"],
                              "multiplierFloat32": source["multiplierFloat32"], "finalUiVerified": False}
            if key in elements:
                ref = elements[key]
                cap["reference"] = {"kind": "element", "enumName": ref["elementEnumName"], "localizedName": ref["systemTextRow"]["text"]}
                localized_names = localizations["elementTextById"][str(cap["value"])]
                cap["reference"]["localizedNames"] = localized_names
                cap["display"].update({"plainTextCandidate": ref["plainTextCandidate"], "status": "native-code-derived-element-reference"})
                cap["display"]["plainTextCandidates"] = {locale: locale_labels[locale][65].replace("{0}", name)
                                                          for locale, name in localized_names.items()}
                counts["elementReferences"] += 1
            elif key in skills:
                ref = skills[key]
                cap["reference"] = {"kind": "avatar-skill", "skillId": ref["skillId"], "rawName": ref["rawName"],
                                    "resolvedName": ref["nativeCodeDerivedName"], "nameVariants": ref["nameVariants"]}
                names = localizations["avatarSkillNamesById"][str(ref["skillId"])]
                cap["reference"]["resolvedNames"] = names
                cap["reference"]["rawNames"] = localizations["avatarSkillRawNamesById"][str(ref["skillId"])]
                cap["display"].update({"plainTextCandidate": ref["nativeCodeDerivedName"], "status": "native-code-derived-skill-name"})
                cap["display"]["plainTextCandidates"] = names
                counts["skillReferences"] += 1
            else:
                preview = text_preview(cap["cap_id"], source["scaledValueFloat32"], labels, captured["strings"])
                cap["display"].update(preview)
                cap["display"]["plainTextCandidates"] = {
                    locale: text_preview(cap["cap_id"], source["scaledValueFloat32"], table, captured["strings"])["plainTextCandidate"]
                    for locale, table in locale_labels.items()}
                if preview["templateId"] < 0:
                    counts["negativeTemplateSelections"] += 1
                if preview["plainTextCandidate"] is None:
                    counts["withoutOptionTemplate"] += 1
    conditions = []
    names = load(ASSETS / "bonus-types.current.json")["by_id"]
    for ident in sorted(MARKERS):
        if ident in WEAPONS:
            predicate = {"kind": "either-weapon-slot", "weaponType": WEAPONS[ident], "slots": ["main", "sub"]}
        elif ident == 108:
            predicate = {"kind": "both-weapon-slots", "mainWeaponType": 10, "subWeaponType": 10}
        else:
            predicate = {"kind": "body-battle-customize", "rawValue": 1 if ident == 119 else 2}
        conditions.append({"capId": ident, "enumName": names[str(ident)], "textKr": labels.get(ident), "predicate": predicate})
    catalog["schemaVersion"] = 2
    catalog["authority"] = "joined-raw-game-catalog-and-reviewed-native-reference-evidence"
    catalog["connectionSources"] = [identity(p) for p in paths]
    catalog["availableItemLocales"] = localizations["availableItemLocales"]
    catalog["localizedOrphanTexts"] = localizations["orphanItemTexts"]
    catalog["localizationMasterEquivalence"] = localizations["masterEquivalence"]
    catalog["originalKoreanCounts"] = catalog["counts"]
    catalog["counts"] = {"masterItems": len(catalog["items"]), "propertyRecords": len(display["items"]),
                         "itemsWithoutAnyName": sum(not i["names"] for i in catalog["items"]),
                         "byLocale": {locale: {"names": sum(locale in i["names"] for i in catalog["items"]),
                                               "descriptions": sum(locale in i["descriptions"] for i in catalog["items"])}
                                      for locale in catalog["availableItemLocales"]}}
    catalog["connectionCounts"] = dict(counts)
    catalog["relatedData"] = {"relations": "item-relations.json", "classification": "item-classification-rules.json",
                              "localization": "item-localization-links.json", "legacyCrystaCandidates": "crysta-link-audit.json"}
    catalog["conditionRules"] = {"intervals": intervals, "initializerMetadataOffset": offset, "initializerHex": raw.hex(),
                                 "scope": "next rawValue positive-cap bonus instructions", "definitions": conditions}
    catalog["optionTextRowsKr"] = text_rows
    catalog["limitations"] = ["All original master fields, raw records, slots, names and descriptions are retained.",
                              "Plain text is a candidate with invariant G7 numeric preview; final runtime UI/culture is unobserved.",
                              "Conditional scope and equipment predicates are extracted; no app/combat formula is changed.",
                              "Unknown flags/types and model-property candidates remain explicitly unresolved.",
                              "Random property assignment, drop-table chunk meanings and foreign language acquisition are separate evidence."]
    require(counts["options"] == len(scaled) and counts["elementReferences"] == len(elements) and counts["skillReferences"] == len(skills), "Reference coverage incomplete")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(catalog, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(dict(counts)))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--catalog", type=Path, default=ASSETS / "items.kr.77596232.json")
    parser.add_argument("--display", type=Path, default=ASSETS / "item-options.scaled.kr.77596232.json")
    parser.add_argument("--audit", type=Path, default=ASSETS / "item-reference-audit.json")
    parser.add_argument("--special", type=Path, default=ASSETS / "item-special-references.json")
    parser.add_argument("--relations", type=Path, default=ASSETS / "item-relations.json")
    parser.add_argument("--classification", type=Path, default=ASSETS / "item-classification-rules.json")
    parser.add_argument("--localizations", type=Path, default=ASSETS / "item-localization-links.json")
    parser.add_argument("--constants", type=Path, default=ASSETS / "native-connections/formatter-constants.json")
    parser.add_argument("--metadata", type=Path, default=RUNTIME / "current-source/global-metadata.dat")
    parser.add_argument("--property-text", type=Path, default=HERE.parents[1] / "build/tmp/toram-item-extraction/game-77596232/cache/GameScene_kr/77596232/ItemProperty_kr.decoded.bin")
    parser.add_argument("--output", type=Path)
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        self_test()
    elif args.output:
        connect(args)
    else:
        parser.error("--output required")
