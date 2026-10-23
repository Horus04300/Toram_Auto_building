"""Extract saved Korean skill/system texts and resolve item cap 65/189 references."""
import argparse
import collections
import hashlib
import json
from pathlib import Path
import re
import runpy
import struct
import sys


HERE = Path(__file__).resolve().parent
AVATAR_SKILLS = {0: 1281, 1: 1282, 5: 1285}
AVATAR_SWITCH_SHA256 = "d6f0293333b35c53dce003f4acf4857ece1ba1be91fb43ccb32a2d8d3f58952f"
REFERENCE_METHODS = ["SkillTextManager-Initialize-7fff5f5655b0.c",
                     "SystemTextManager-Initialize-7fff5f568210.c",
                     "SkillManager-GetAvatarSkillId-7fff60307220.c"]
NAME_METHODS = {
    "SkillTextManagerData-CheckNameText-7fff5f563ff0.c": "fd88bb4a3f06dd253f82013732f4ddde23ea208609ef65459e229cd31315b616",
    "SkillTextManagerData-GetName-7fff5f5649d0.c": "3a3a51dde404d7768f593c354a429533df954195890fe856799f2dd1d37bd620",
    "SkillTextManagerData-GetName-7fff5f564a70.c": "b7c75b8aa5baf1e62bafd0ee556afa632fd506a17cd9d13209d93634ec9a38d3",
    "SkillTextManagerData-_cctor-7fff5f564b60.c": "47ea9e001bdf6810f409094204e96c0d5116754acbd5a5e54b5dce3d0a0d4d9a",
}


def require(value, message):
    if not value:
        raise ValueError(message)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def source(path):
    data = path.read_bytes()
    return {"path": path.as_posix(), "bytes": len(data), "sha256": digest(data)}


def parse(data, skill, reader_type):
    reader = reader_type(data)
    count = reader.u32()
    require(count <= len(data) // (6 if skill else 2), "Impossible text record count")
    rows, keys = [], set()
    for _ in range(count):
        offset = reader.pos
        if skill:
            ident = struct.unpack("<i", reader.take(4))[0]
            kind = reader.take(1)[0]
            key = (ident, kind)
            row = {"skillId": ident, "kind": kind}
        else:
            key = reader.string()
            row = {"key": key}
        require(not skill or key not in keys, f"Duplicate skill text key {key}")
        keys.add(key)
        rows.append({**row, "text": reader.string(), "decodedOffset": offset})
    require(reader.pos == len(data), "Trailing text bytes")
    return rows


def derive_skill_name(raw, constants):
    if raw.startswith(constants["skillBracketPrefix"]):
        segments = re.split(r"[\[\]]", raw)
        pairs = [{"key": segments[i], "text": segments[i + 1]} for i in range(1, len(segments) - 2, 2)]
        syntax = "bracket-pairs"
    else:
        segments = raw.split("$")
        pairs = ([{"key": segments[i], "text": segments[i + 1]} for i in range(0, len(segments), 2)]
                 if len(segments) % 2 == 0 else None)
        syntax = "dollar-pairs" if pairs is not None else "raw-name"
    selected = [p["text"] for p in pairs or [] if p["key"] == constants["skillDefaultTag"]]
    duplicate = pairs is not None and len({p["key"] for p in pairs}) != len(pairs)
    name = (raw if pairs is None else selected[0] if selected else constants["skillUnknownName"])
    return {"nativeCodeDerivedName": None if duplicate else name, "nameVariants": pairs,
            "nameSyntax": syntax, "defaultVariantKey": constants["skillDefaultTag"],
            "duplicateVariantKeys": duplicate, "finalUiObserved": False}


def resolve(items, elements, system_rows, skill_rows, templates, name_constants):
    grouped_system = collections.defaultdict(list)
    for row in system_rows:
        grouped_system[row["key"]].append(row)
    system = {key: rows[0] for key, rows in grouped_system.items() if len(rows) == 1}
    skills = collections.defaultdict(dict)
    for row in skill_rows:
        skills[row["skillId"]][row["kind"]] = row
    element_refs, skill_refs = [], []
    for item in items:
        for cap in (item["propertyRecord"] or {}).get("caps", []):
            common = {"gameItemId": item["gameItemId"], "names": item["names"],
                      "slot": cap["slot"], "capId": cap["cap_id"], "rawValue": cap["value"]}
            if cap["cap_id"] == 65:
                enum_name = elements.get(cap["value"])
                text = system.get(enum_name)
                template = templates.get(65)
                element_refs.append({**common, "elementEnumName": enum_name,
                                     "systemTextRow": text, "propertyTemplateRow": template,
                                     "plainTextCandidate": template["text"].format(text["text"])
                                     if text is not None and template is not None else None,
                                     "finalUiVerified": False})
            elif cap["cap_id"] == 189:
                ident = AVATAR_SKILLS.get(cap["value"], 0)
                skill = skills.get(ident, {})
                name = skill.get(0)
                skill_refs.append({**common, "skillId": ident,
                                   "usesNativeDefaultSkillId": cap["value"] not in AVATAR_SKILLS,
                                   "nativeManagerEntryEligible": 0 in skill and 1 in skill,
                                   "skillTextRows": [row for _, row in sorted(skill.items())],
                                   "rawName": name["text"] if name is not None else None,
                                   "nameTextRowFound": name is not None,
                                   "nameContainsMarkup": name is not None and "[" in name["text"],
                                   **(derive_skill_name(name["text"], name_constants) if name is not None else
                                      {"nativeCodeDerivedName": None, "nameVariants": None, "finalUiObserved": False}),
                                   "finalDisplayName": None, "finalUiVerified": False})
    return element_refs, skill_refs


def main(args):
    catalog = json.loads(args.catalog.read_text(encoding="utf-8"))
    metadata_bytes = args.metadata.read_bytes()
    require(digest(metadata_bytes) == catalog["bonusEnumSource"]["sha256"], "Catalog/metadata version mismatch")
    native_sources = [source(args.native / name) for name in REFERENCE_METHODS]
    require(native_sources[-1]["sha256"] == AVATAR_SWITCH_SHA256, "Avatar switch changed; review native code")
    name_sources = []
    for name, expected in NAME_METHODS.items():
        entry = source(args.native.parent / "pseudocode-conditions" / name)
        require(entry["sha256"] == expected, f"Skill name code changed: {name}")
        name_sources.append(entry)
    captured_constants = json.loads(args.constants.read_text(encoding="utf-8"))
    constants = {key: captured_constants["strings"][key] for key in
                 ("skillDefaultTag", "skillBracketPrefix", "skillUnknownName")}
    require(constants == {"skillDefaultTag": "N", "skillBracketPrefix": "[N]", "skillUnknownName": "???"},
            "Reviewed skill constants changed")
    extraction = runpy.run_path(str(HERE / "extract-toram-item-assets.py"))
    metadata = runpy.run_path(str(HERE / "extract-il2cpp-item-schema.py"))["Metadata"](metadata_bytes)
    enum_indices = [i for i, t in enumerate(metadata.types)
                    if metadata.full_name(t) == "ElementType" and t[3] == -1]
    require(len(enum_indices) == 1, "Ambiguous ElementType")
    enum = metadata.schema(enum_indices[0])
    elements = {f["default"]["int32_value"]: f["name"] for f in enum["fields"] if "default" in f}
    bundle_sources = [s for s in catalog["sources"] if Path(s["source"]).parent.parent.name == "GameScene_kr"]
    require(len(bundle_sources) == 1, "Expected one exact Korean item-text bundle")
    bundle_source = bundle_sources[0]
    bundle = Path(bundle_source["source"])
    bundle_bytes = bundle.read_bytes()
    require(digest(bundle_bytes) == bundle_source["sha256"], "Cached bundle differs from catalog snapshot")
    if args.unitypy_path:
        sys.path.insert(0, str(args.unitypy_path))
    import UnityPy
    environment = UnityPy.load(bundle_bytes)
    tables, assets = {}, []
    for obj in environment.objects:
        if obj.type.name != "TextAsset":
            continue
        asset = obj.parse_as_object()
        if asset.m_Name not in ("System_kr", "Skill_kr", "ItemProperty_kr"):
            continue
        require(asset.m_Name not in tables, "Duplicate selected TextAsset")
        raw = asset.m_Script.encode("utf-8", "surrogateescape")
        decoded = extraction["decode"](raw, int(catalog["cacheVersion"], 16))
        raw_path, decoded_path = args.raw_output / f"{asset.m_Name}.bin", args.raw_output / f"{asset.m_Name}.decoded.bin"
        require(args.output.resolve() not in (raw_path.resolve(), decoded_path.resolve()), "Output overlaps raw bytes")
        args.raw_output.mkdir(parents=True, exist_ok=True)
        extraction["write_bytes"](raw_path, raw)
        extraction["write_bytes"](decoded_path, decoded)
        if asset.m_Name == "ItemProperty_kr":
            rows = extraction["parse_text"](decoded, False)
        else:
            rows = parse(decoded, asset.m_Name == "Skill_kr", extraction["Reader"])
        tables[asset.m_Name] = rows
        assets.append({"name": asset.m_Name, "pathId": obj.path_id,
                       "raw": source(raw_path), "decoded": source(decoded_path),
                       "records": len(rows), "allBytesConsumed": True})
    require(digest(bundle.read_bytes()) == bundle_source["sha256"], "Cache changed during extraction")
    require(set(tables) == {"System_kr", "Skill_kr", "ItemProperty_kr"}, "Required text assets absent")
    templates = {r["propertyId"]: r for r in tables["ItemProperty_kr"]}
    element_refs, skill_refs = resolve(catalog["items"], elements, tables["System_kr"], tables["Skill_kr"], templates, constants)
    grouped_system = collections.defaultdict(list)
    for row in tables["System_kr"]:
        grouped_system[row["key"]].append(row)
    system = {key: rows[0] for key, rows in grouped_system.items() if len(rows) == 1}
    result = {"schemaVersion": 1, "authority": "local-game-texts-and-reviewed-native-reference-switch",
              "cacheVersion": catalog["cacheVersion"], "locale": "kr",
              "sources": {"catalog": source(args.catalog), "metadata": source(args.metadata),
                          "bundle": source(bundle), "nativePseudocode": native_sources, "textAssets": assets},
              "skillNameRule": {"nativePseudocode": name_sources, "capturedConstants": source(args.constants),
                                "constants": constants, "defaultLookup": "first static tag, then GetName(key)",
                                "kind": "native-code-derived-name-not-observed-ui"},
              "nativeAvatarSkillRule": {"method": "SkillManager.GetAvatarSkillId", "token": "0x06007a0d",
                                        "rva": "0x10b7220", "rawToSkillId": AVATAR_SKILLS, "defaultSkillId": 0},
              "elementEnum": {"typeDefinitionIndex": enum_indices[0], "declarationRange": enum["range"],
                              "values": [{"value": value, "enumName": name, "systemTextRow": system.get(name)}
                                         for value, name in sorted(elements.items())]},
              "counts": {"systemTextRows": len(tables["System_kr"]), "skillTextRows": len(tables["Skill_kr"]),
                         "skillTextKinds": dict(collections.Counter(r["kind"] for r in tables["Skill_kr"])),
                         "duplicateSystemKeys": sum(len(rows) > 1 for rows in grouped_system.values()),
                         "elementReferences": len(element_refs), "skillReferences": len(skill_refs),
                         "unresolvedElementReferences": sum(r["systemTextRow"] is None for r in element_refs),
                         "unresolvedSkillReferences": sum(not r["nameTextRowFound"] for r in skill_refs)},
              "finalUiObserved": False,
              "elementReferences": element_refs, "avatarSkillReferences": skill_refs,
              "duplicateSystemKeys": {key: rows for key, rows in grouped_system.items() if len(rows) > 1},
              "limitations": ["Skill names/descriptions retain original markup and escaped newlines.",
                              "SkillTextManagerData default name tags are reproduced from code; runtime UI output is unobserved.",
                              "Duplicate skill variant keys remain unresolved instead of assuming dictionary insertion behavior.",
                              "Native SkillTextManager entries require both kind 0 name and kind 1 description; kind 2 is optional.",
                              "Element plain text uses the property template and enum-name System key; final color/layout is not reproduced.",
                              "Missing unused System keys and future avatar values are preserved; native default skill ID is zero.",
                              "Duplicate System rows are preserved; ambiguous keys are not selected by an inferred overwrite rule.",
                              "These are text/ID references, not skill formulas or proof of current server availability."]}
    require(args.output.resolve() not in (args.catalog.resolve(), args.metadata.resolve(), bundle.resolve()), "Output overlaps source")
    extraction["write_json"](args.output, result)
    print(json.dumps(result["counts"]))


def self_test():
    reader = runpy.run_path(str(HERE / "extract-toram-item-assets.py"))["Reader"]
    skill = struct.pack("<IiBB", 1, 1285, 2, 3) + b"[N]"
    assert parse(skill, True, reader)[0] == {"skillId": 1285, "kind": 2, "text": "[N]", "decodedOffset": 4}
    system = struct.pack("<I", 1) + b"\x04Fire\x03" + "불".encode("utf-8")
    assert parse(system, False, reader)[0]["text"] == "불"
    assert len(parse(struct.pack("<I", 2) + system[4:] * 2, False, reader)) == 2
    for bad in (skill[:-1], skill + b"\0", struct.pack("<I", 2) + skill[4:] * 2):
        try:
            parse(bad, True, reader)
        except ValueError:
            pass
        else:
            raise AssertionError("Malformed skill table accepted")
    items = [{"gameItemId": 1, "names": {}, "propertyRecord": {"caps": [
        {"slot": 1, "cap_id": 189, "value": 0}, {"slot": 2, "cap_id": 189, "value": 999},
        {"slot": 3, "cap_id": 65, "value": 999}]}}]
    constants = {"skillDefaultTag": "N", "skillBracketPrefix": "[N]", "skillUnknownName": "???"}
    elements, skills = resolve(items, {}, [], [], {}, constants)
    assert skills[0]["skillId"] == 1281 and skills[1]["skillId"] == 0
    assert not skills[0]["nameTextRowFound"] and skills[0]["finalDisplayName"] is None
    assert elements[0]["plainTextCandidate"] is None
    bracket = derive_skill_name("[N]드래곤 슬레이브[N2]다른 이름[N]", constants)
    assert bracket["nativeCodeDerivedName"] == "드래곤 슬레이브"
    assert bracket["nameVariants"] == [{"key": "N", "text": "드래곤 슬레이브"}, {"key": "N2", "text": "다른 이름"}]
    assert derive_skill_name("익스플로젼", constants)["nameVariants"] is None
    assert derive_skill_name("N$default$N2$other", constants)["nativeCodeDerivedName"] == "default"
    assert derive_skill_name("N2$other", constants)["nativeCodeDerivedName"] == "???"
    assert derive_skill_name("[N]unterminated", constants)["nativeCodeDerivedName"] == "???"
    assert derive_skill_name("N$first$N$second", constants)["nativeCodeDerivedName"] is None
    print("PASS: raw text/EOF, unresolved IDs, bracket/dollar/default skill tags, no observed UI claim")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--catalog", type=Path, default=Path("data/sources/toram-items/items.kr.77596232.json"))
    parser.add_argument("--metadata", type=Path, default=Path("build/tmp/toram-item-extraction/code-trace/runtime/current-source/global-metadata.dat"))
    parser.add_argument("--native", type=Path, default=Path("build/tmp/toram-item-extraction/code-trace/runtime/item-connections/pseudocode"))
    parser.add_argument("--constants", type=Path, default=Path("build/tmp/toram-item-extraction/code-trace/runtime/item-connections/formatter-constants-with-skill.json"))
    parser.add_argument("--raw-output", type=Path, default=Path("build/tmp/toram-item-extraction/code-trace/runtime/item-connections/text-assets"))
    parser.add_argument("--output", type=Path, default=Path("data/sources/toram-items/item-special-references.json"))
    parser.add_argument("--unitypy-path", type=Path, default=Path("build/tmp/toram-item-extraction/python-deps"))
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    self_test() if args.self_test else main(args)
