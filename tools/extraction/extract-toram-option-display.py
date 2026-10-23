"""Reproduce the reviewed build's option multipliers from saved native evidence.

Reads files only. Deliberately rejects other builds and changed decompiler output;
this is a verified extraction recipe, not a general C or machine-code parser.
"""

import argparse
import hashlib
import json
from pathlib import Path
import re
import struct


MAPPED_SHA = "2baf9dd6ad9f2a32f211c1f97a7ad0b94bf778d689afb054047f9ab621fd370e"
CCTOR_FILE = "BonusManager-_cctor-7fff5fff8f60.c"
CCTOR_SHA = "b01d395c578989b49e488d0e5b124024781857f5b1a72f3e2dbf3df328b50e96"
FLOAT_IDS = {12, 110, 137, 140, 190, *range(166, 176)}
SPECIAL_SIGN_IDS = {48, 188, *range(166, 176)}
CONTEXT_IDS = {65, 189}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def f32(value):
    return struct.unpack("<f", struct.pack("<f", value))[0]


def extract_rules(data, source, base):
    require(digest(data) == MAPPED_SHA, "Unreviewed mapped image")
    require(digest(source) == CCTOR_SHA, "Unreviewed constructor pseudocode")
    code = source.decode("utf-8")
    rules = {}
    for cap_id, multiplier in re.findall(r"FUN_7fff6087cab0\(lVar6,(0x[0-9a-f]+),(\d+),", code):
        rules[int(cap_id, 16)] = {"multiplierFloat32": float(multiplier), "dictionary": "AvatarBonusTimes"}
    require(set(rules) == set(range(180, 189)), "Avatar dictionary entries changed")
    require([rules[i]["multiplierFloat32"] for i in range(180, 189)] == [1, 1, 1, 1, 10, 10, 10, 10, 1],
            "Avatar dictionary values changed")
    alias = re.findall(r"uVar5 = _DAT_([0-9a-f]+);", code)
    require(len(alias) == 1, "Float alias changed")
    matches = re.findall(r"FUN_7fff6088caa0\(lVar6,(0x[0-9a-f]+),(uVar5|_DAT_[0-9a-f]+),", code)
    require(len(matches) == len(FLOAT_IDS), "Float dictionary entry count changed")
    for cap_id, expression in matches:
        cap_id = int(cap_id, 16)
        address = int(alias[0] if expression == "uVar5" else expression[5:], 16)
        offset = address - base
        require(0 <= offset <= len(data) - 4, "Constant outside image")
        raw = data[offset:offset + 4]
        multiplier = struct.unpack("<f", raw)[0]
        nominal = {"00002041": 10, "cdcccc3d": 0.1, "0ad7233c": 0.01}.get(raw.hex())
        require(nominal is not None and cap_id not in rules, "Unexpected or duplicate multiplier")
        rules[cap_id] = {"multiplierFloat32": multiplier, "nominalMultiplier": nominal,
                         "dictionary": "BonusTimes", "constantRva": hex(offset), "constantHexLE": raw.hex()}
    require({i for i, r in rules.items() if r["dictionary"] == "BonusTimes"} == FLOAT_IDS,
            "Float dictionary IDs changed")
    require(data[0x2902b18:0x2902b1c] == bytes.fromhex("0000803f"), "Default multiplier changed")
    return rules


def scaled(raw, multiplier):
    require(isinstance(raw, int) and -32768 <= raw <= 32767, "Not a signed i16 option value")
    return f32(f32(raw) * multiplier)


def write_json(path, value):
    data = (json.dumps(value, ensure_ascii=False, indent=2) + "\n").encode("utf-8")
    require(not path.exists() or path.read_bytes() == data, f"Refusing to replace different output: {path}")
    path.write_bytes(data)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--runtime", type=Path)
    parser.add_argument("--catalog", type=Path)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        assert scaled(100, f32(10)) == 1000
        assert scaled(10, f32(0.1)) == 1
        assert scaled(-32768, f32(0.01)) == f32(-327.68)
        assert scaled(32767, f32(1)) == 32767
        try:
            scaled(32768, 1)
        except ValueError:
            pass
        else:
            raise AssertionError("Out-of-range raw value accepted")
        print("option display self-test PASS")
        return
    require(all([args.runtime, args.catalog, args.output]), "--runtime, --catalog, --output required")
    mapping = json.loads((args.runtime / "native-method-map.json").read_text(encoding="utf-8"))
    data = (args.runtime / "snapshot-1/GameAssembly.mapped.bin").read_bytes()
    source = (args.runtime / "focused-pseudocode-v2" / CCTOR_FILE).read_bytes()
    rules = extract_rules(data, source, int(mapping["image_base"], 16))
    catalog_bytes = args.catalog.read_bytes()
    catalog = json.loads(catalog_bytes)
    require(catalog["bonusEnumSource"]["sha256"] == mapping["sources"]["metadata"]["sha256"],
            "Catalog enum and native metadata differ")
    evidence = {"mappedImageSha256": digest(data), "metadataSha256": catalog["bonusEnumSource"]["sha256"],
                "constructorPseudocodeSha256": digest(source), "catalogSha256": digest(catalog_bytes),
                "cacheVersion": catalog["cacheVersion"]}
    rows, total, modes = [], 0, {}
    for item in catalog["items"]:
        if item["propertyRecord"] is None:
            continue
        options = []
        for cap in item["propertyRecord"]["caps"]:
            cap_id = cap["cap_id"]
            if cap_id <= 0:
                continue
            multiplier = rules.get(cap_id, {}).get("multiplierFloat32", 1.0)
            template = cap["templates"].get("kr")
            mode = ("context-dependent" if cap_id in CONTEXT_IDS else "signed-template-branch"
                    if cap_id in SPECIAL_SIGN_IDS else "ordinary-template" if template else "no-template")
            modes[mode] = modes.get(mode, 0) + 1
            options.append({"slot": cap["slot"], "capId": cap_id, "enumName": cap["enumName"],
                            "rawValue": cap["value"], "multiplierFloat32": multiplier,
                            "scaledValueFloat32": scaled(cap["value"], multiplier),
                            "templateKr": template, "formattingMode": mode})
        total += len(options)
        rows.append({"gameItemId": item["gameItemId"], "nameKr": item["names"].get("kr"), "options": options})
    args.output.mkdir(parents=True, exist_ok=True)
    write_json(args.output / "option-display-rules.json", {
        "authority": "saved-runtime-native-code-and-constant-bytes", "evidence": evidence,
        "defaultMultiplierFloat32": 1.0, "operation": "float32(float32(signed_i16_raw_value) * multiplier)",
        "overrides": [{"capId": i, **r} for i, r in sorted(rules.items())],
        "specialFormattingIds": {"signedTemplate": sorted(SPECIAL_SIGN_IDS), "contextDependent": sorted(CONTEXT_IDS)},
        "limitations": ["Numeric input to UIItemProperty.AddCapProperty, not a combat formula or final rendered string.",
                        "No-template entries may use other item-specific UI paths.",
                        "Color, locale numeric formatting, conditional equipment bonuses and live UI were not reproduced."]})
    write_json(args.output / f"item-options.scaled.kr.{catalog['cacheVersion']}.json", {
        "evidence": evidence, "authority": "derived-input-to-reviewed-option-formatter",
        "counts": {"itemsWithPropertyRecord": len(rows), "options": total, "formattingModes": modes},
        "formattedTextVerified": False, "items": rows})
    print(json.dumps({"items": len(rows), "options": total, "overrides": len(rules), "modes": modes}))


if __name__ == "__main__":
    main()
