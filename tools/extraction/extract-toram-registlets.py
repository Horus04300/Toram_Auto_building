"""Join retained Registlet master, texts and native evidence; never accesses a game process."""

import argparse
import collections
import csv
import hashlib
import importlib.util
import io
import json
from pathlib import Path
import re
import struct


ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "data/sources/toram-registlet"
LOCALES = ("cnt", "idn", "jp", "kr", "th", "us")


def require(value, message):
    if not value:
        raise ValueError(message)


def load(path):
    return json.loads(path.read_text(encoding="utf-8"))


def sha(data):
    return hashlib.sha256(data).hexdigest()


def verify_refs(value):
    if isinstance(value, dict):
        if "file" in value and "sha256" in value:
            require(sha((ROOT / value["file"]).read_bytes()) == value["sha256"], f"Source reference changed: {value['file']}")
        for child in value.values():
            verify_refs(child)
    elif isinstance(value, list):
        for child in value:
            verify_refs(child)


def f32(value):
    return struct.unpack("<f", struct.pack("<f", value))[0]


def display_rule(ident, base):
    if base == -1:
        return "no-substitution", None
    if ident == 1004:
        return "[L*B, 10*L*B]", lambda lv: [lv * base, 10 * lv * base]
    if ident == 44:
        return "f32(f32(f32(B/100)*L)+1)", lambda lv: f32(f32(f32(base / 100) * lv) + 1)
    if ident in (205, 206, 76, 1031):
        return "f32((L*B)/10)", lambda lv: f32(lv * base / 10)
    if ident in (24, 25, 26, 32):
        return "B-L", lambda lv: base - lv
    if ident in (29, 33, 35, 38, 41):
        return "B+L", lambda lv: base + lv
    if ident == 37:
        return "B-L+1", lambda lv: base - lv + 1
    if ident == 42:
        return "B-100*L+100", lambda lv: base - 100 * lv + 100
    if ident == 207:
        return "trunc((PowerWaveSkillLevel+L)/2)", None
    if ident == 211:
        return "B-10*L+10", lambda lv: base - 10 * lv + 10
    if ident in (1011, 1012, 1013):
        return "100-(L+1)*B", lambda lv: 100 - (lv + 1) * base
    if ident == 1030:
        return "300-L*B", lambda lv: 300 - lv * base
    if ident == 1042:
        return "f32((L*B-1)/10)", lambda lv: f32((lv * base - 1) / 10)
    if ident == 1039:
        return "60-L*B", lambda lv: 60 - lv * base
    if ident == 1045:
        return "(4-L)*B", lambda lv: (4 - lv) * base
    if ident == 1047:
        return "15-L", lambda lv: 15 - lv
    if ident == 1051:
        return "100-L*B", lambda lv: 100 - lv * base
    return "L*B", lambda lv: lv * base


def calls(source, name):
    """Return balanced C call arguments, preserving nested casts and dereferences."""
    for match in re.finditer(re.escape(name) + r"\s*\(", source):
        start = match.end()
        depth, field, args = 0, start, []
        for index in range(start, len(source)):
            char = source[index]
            if char == "(":
                depth += 1
            elif char == ")":
                if depth == 0:
                    args.append(source[field:index].strip())
                    yield match.start(), args
                    break
                depth -= 1
            elif char == "," and depth == 0:
                args.append(source[field:index].strip())
                field = index + 1


def native_records():
    records, by_class = [], collections.defaultdict(list)
    for folder in ("native", "native-extra", "native-consumers", "native-supplement"):
        for entry in load(SOURCE / folder / "index.json"):
            require(entry["decompileCompleted"], f"Incomplete native evidence: {folder}/{entry}")
            path = SOURCE / folder / entry["pseudocodeFile"]
            source = path.read_text(encoding="utf-8")
            record = {"class": entry["class"], "method": entry["name"],
                      "methodDefinitionIndex": entry["method_definition_index"], "token": entry["token"],
                      "runtimeVa": entry["runtime_va"], "rva": entry["rva"],
                      "file": path.relative_to(ROOT).as_posix(), "sha256": sha(path.read_bytes()),
                      "returns": re.findall(r"\breturn\s+([^;]+);", source)}
            if entry.get("assemblyFile"):
                asm = SOURCE / folder / entry["assemblyFile"]
                record.update(assemblyFile=asm.relative_to(ROOT).as_posix(), assemblySha256=sha(asm.read_bytes()))
            records.append(record)
            by_class[entry["class"]].append((record, source))
    return records, by_class


def build():
    provenance = load(SOURCE / "provenance.json")
    for entry in provenance["evidenceFiles"]:
        require(sha((ROOT / entry["file"]).read_bytes()) == entry["sha256"], f"Evidence changed: {entry['file']}")
    master = load(SOURCE / "assets/RegistletMaster.structural.json")
    require(master["version"] == 1 and master["count"] == 166, "Unreviewed master version/count")
    spec = importlib.util.spec_from_file_location("registlet_assets", SOURCE / "assets/extract-assets.py")
    assets = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(assets)
    parsed = assets.parse_master((SOURCE / "assets/RegistletMaster.decoded.bin").read_bytes())
    require(parsed == master, "Master bytes differ from parsed rows")
    records, classes = native_records()
    buffs = {}
    for cls, methods in classes.items():
        if cls not in provenance["bufferClasses"]:
            continue
        getter, source = next((r, text) for r, text in methods if r["method"] == "get_Id")
        match = re.search(r"return\s+(?:\(undefined \*\))?(0x[\da-f]+|\d+);", source)
        require(match is not None, f"Unparsed buffer ID: {cls}")
        ident = int(match[1], 0)
        require(ident not in buffs, f"Duplicate buffer ID: {ident}")
        buffs[ident] = {"class": cls, "idSource": getter,
                        "methods": [r for r, _ in methods if r["method"] != "get_Id"]}
    require(len(buffs) == 163, "Buffer subclass coverage changed")
    consumers, dynamic = collections.defaultdict(list), []
    for cls, methods in classes.items():
        if cls in provenance["bufferClasses"] or cls.startswith("GemCartBuffer"):
            continue
        for record, source in methods:
            for method in ("ContainsBuffer", "GetGemCartBuffer", "GetBufferLevel"):
                for offset, args in calls(source, "GemCartBufferManager_" + method):
                    if len(args) < 2:
                        continue
                    call = {**record, "query": method, "idExpression": args[1],
                            "line": source[:offset].count("\n") + 1}
                    if re.fullmatch(r"0x[\da-f]+|\d+", args[1]):
                        consumers[int(args[1], 0)].append(call)
                    else:
                        dynamic.append(call)
    texts = {}
    for locale in LOCALES:
        rows = load(SOURCE / f"assets/Registlet_{locale}.parsed.json")
        keys = [(r["registletId"], r["kind"]) for r in rows]
        require(len(keys) == len(set(keys)) == 497, "Duplicate/missing localization rows")
        texts[locale] = {(r["registletId"], r["kind"]): r for r in rows}
    combat_document = load(SOURCE / "combat-rules.json")
    verify_refs(combat_document)
    combat = {r["registletId"]: r for r in combat_document["registlets"]}
    require(set(combat) == set(map(int, provenance["catalogIds"])), "Combat rule coverage changed")
    acquisition = load(SOURCE / "acquisition/stages.json")
    verify_refs(acquisition)
    locations = collections.defaultdict(list)
    for stage in acquisition["stages"]:
        if stage["rankPools"] is None:
            continue
        ranks_by_id = collections.defaultdict(list)
        for rank, items in stage["rankPools"].items():
            for item in items:
                if "registletId" in item and rank not in ranks_by_id[item["registletId"]]:
                    ranks_by_id[item["registletId"]].append(rank)
        for ident, ranks in ranks_by_id.items():
            locations[ident].append({"level": stage["level"], "fieldId": stage["fieldId"],
                                     "roomId": stage["roomId"], "ranks": ranks,
                                     "sourceFiles": [ref["file"] for ref in stage["captureSources"]]})
    result = []
    for row in master["rows"]:
        ident = row["registletId"]
        names, descriptions, bases = {}, {}, {}
        source_refs = {}
        for locale in LOCALES:
            table = texts[locale]
            names[locale] = table[ident, 0]["text"]
            descriptions[locale] = table[ident, 1]["text"]
            bases[locale] = int(table.get((ident, 2), {"text": "-1"})["text"])
            source_refs[locale] = {"file": f"data/sources/toram-registlet/assets/Registlet_{locale}.parsed.json",
                                   "rows": {str(kind): table[ident, kind]["decodedOffset"]
                                            for kind in (0, 1, 2) if (ident, kind) in table}}
        require(len(set(bases.values())) == 1, f"BaseValue locale mismatch: {ident}")
        base = bases["kr"]
        expression, calculate = display_rule(ident, base)
        observed_locations = locations.get(ident, [])
        result.append({**row, "nativeEnumName": provenance["gemCartIds"][str(ident)],
                       "names": names, "descriptionTemplates": descriptions, "baseValue": base,
                       "displayRule": {"expression": expression, "variables": {"L": "registlet level", "B": "BaseValue"},
                                       "source": "data/sources/toram-registlet/native/65950.c" if ident == 1004 else "data/sources/toram-registlet/native/65962.c",
                                       "atLevel1": calculate(1) if calculate else None,
                                       "atLevelCap": calculate(row["levelCap"]) if calculate else None,
                                       "scope": "description substitution only; not a combat formula or observed final UI"},
                       "nativeBuffer": buffs.get(ident), "nativeConsumers": consumers.get(ident, []),
                       "combatRules": combat.get(ident),
                       "acquisition": {"contentId": "stoodie-experiment", "stagesFile": "data/sources/toram-registlet/acquisition/stages.json",
                                       "locations": observed_locations, "dropProbability": None,
                                       "capturedStageCount": acquisition["capturedStageCount"],
                                       "status": "observed-stage-rank-lists" if observed_locations else "not-listed-in-observed-stage-lists"},
                       "sourceRefs": {"master": {"file": "data/sources/toram-registlet/assets/RegistletMaster.decoded.bin", "offset": row["decodedOffset"], "bytes": 8},
                                      "texts": source_refs}})
    require(set(r["registletId"] for r in result) == set(map(int, provenance["catalogIds"])), "Catalog ID coverage changed")
    return {"schemaVersion": 1, "checkedDate": "2026-10-29", "authority": "retained-game-assets-and-static-native-code",
            "counts": {"registlets": len(result), "locales": len(LOCALES), "bufferSubclasses": len(buffs),
                       "nativeMethods": len(records)}, "registlets": result,
            "slotExpansion": load(SOURCE / "native-slots/slot-rules.json"),
            "acquisition": acquisition, "dynamicConsumerReferences": dynamic,
            "limitations": ["Native pseudocode is recovered code with shared implementations and unresolved calls, not original C#.",
                            "The producer query and runtime consumer must both be checked before assigning units to a combat value.",
                            "Client data and UI formulas do not prove current server drop rates or account progression.",
                            "Engine, equipment, saved builds and battle simulation are unchanged."]}


def output_bytes(catalog):
    stream = io.StringIO(newline="")
    writer = csv.writer(stream, lineterminator="\n")
    writer.writerow(["id", "enum", "name_kr", "max_lv", "enhance_powder", "base_value", "display_formula", "description_kr", "buffer_class", "native_consumer_count", "acquisition_locations", "acquisition_status"])
    for row in catalog["registlets"]:
        writer.writerow([row["registletId"], row["nativeEnumName"], row["names"]["kr"], row["levelCap"],
                         row["enhancePowder"], row["baseValue"], row["displayRule"]["expression"],
                         row["descriptionTemplates"]["kr"], (row["nativeBuffer"] or {}).get("class", ""),
                         len(row["nativeConsumers"]),
                         "; ".join(f"Lv{place['level']}:{'/'.join(place['ranks'])}" for place in row["acquisition"]["locations"]),
                         row["acquisition"]["status"]])
    return {"catalog.json": (json.dumps(catalog, ensure_ascii=False, indent=2) + "\n").encode("utf-8"),
            "catalog.csv": stream.getvalue().encode("utf-8-sig")}


def self_test():
    for ident, base, lv, expected in [(12, 1, 30, 30), (18, 5, 10, 50), (24, 30, 10, 20),
                                     (29, 10, 10, 20), (37, 100, 2, 99), (42, 1000, 10, 100),
                                     (1004, 2, 10, [20, 200]), (1011, 5, 10, 45), (1030, 100, 2, 100),
                                     (1045, 1, 3, 1), (1047, 1, 10, 5)]:
        assert display_rule(ident, base)[1](lv) == expected, (ident, lv)
    assert display_rule(50, -1) == ("no-substitution", None)
    assert display_rule(207, 1) == ("trunc((PowerWaveSkillLevel+L)/2)", None)
    assert display_rule(1031, 25)[1](1) == 2.5
    assert list(calls("foo(*(x + 4),0x12,(void *)0);", "foo")) == [(0, ["*(x + 4)", "0x12", "(void *)0"])]
    print("registlet extraction self-test PASS (display branches, dynamic input, balanced native call arguments)")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--self-test", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        self_test()
        return
    catalog = build()
    for filename, data in output_bytes(catalog).items():
        path = SOURCE / filename
        if args.check:
            require(path.read_bytes() == data, f"Generated file differs: {path}")
        else:
            path.write_bytes(data)
    print(json.dumps({"check": args.check, **catalog["counts"]}))


if __name__ == "__main__":
    main()
