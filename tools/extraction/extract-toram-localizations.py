"""Extract public game-localization bundles tied to the selected item master.

Reads retained files by default. --download only GETs the code-derived public
release manifest and its named BynaryData/GameScene assets. No account API,
game execution, settings change or process access.
"""

import argparse
import collections
import datetime
import importlib.util
import json
from pathlib import Path
import re
import struct
import sys
import time
import urllib.request


ROOT = Path(__file__).resolve().parents[2]
PUBLIC_BASE = "https://toram-jp.akamaized.net/resources/windows/"
MANIFEST_NAME = "RevisionInfoBinary.bytes"
spec = importlib.util.spec_from_file_location("game_items", Path(__file__).with_name("extract-toram-item-assets.py"))
game = importlib.util.module_from_spec(spec)
spec.loader.exec_module(game)


def require(condition, message):
    if not condition:
        raise ValueError(message)


def revision_cache_key(revision):
    # AssetDecrypt XORs the Int32 key as big-endian words; the cache decoder takes key bytes as LE.
    return f"{int.from_bytes((revision & 0xffffffff).to_bytes(4, 'big'), 'little'):08x}"


def parse_manifest(data):
    reader = game.Reader(data)
    marker = reader.take(1)[0]
    declared_size = struct.unpack("<q", reader.take(8))[0]
    require(declared_size == len(data), "Manifest declared size mismatch")
    group_count = struct.unpack("<h", reader.take(2))[0]
    require(0 < group_count <= len(data) // 6, "Impossible manifest group count")
    groups = []
    for _ in range(group_count):
        offset = reader.pos
        template = reader.string()
        flag = reader.take(1)[0]
        count = reader.i32()
        require(0 <= count <= (len(data) - reader.pos) // 12, "Impossible revision row count")
        rows = []
        for _ in range(count):
            index, revision, extra = struct.unpack("<iii", reader.take(12))
            rows.append({"formatArgument": index, "revisionSignedInt32": revision,
                         "cacheKey": revision_cache_key(revision), "extraRaw": extra})
        groups.append({"decodedOffset": offset, "assetNameTemplate": template, "flagRaw": flag, "rows": rows})
    require(reader.pos == len(data), "Trailing manifest bytes")
    return {"markerRaw": marker, "declaredBytes": declared_size, "groupCount": group_count,
            "rowCount": sum(len(group["rows"]) for group in groups), "groups": groups}


def single_asset(manifest, name):
    groups = [group for group in manifest["groups"] if group["assetNameTemplate"] == name]
    require(len(groups) == 1 and len(groups[0]["rows"]) == 1, f"Missing/ambiguous manifest asset: {name}")
    group = groups[0]
    require(group["rows"][0]["formatArgument"] == 0 and group["flagRaw"] == 1, f"Unreviewed bundle flag/row: {name}")
    return {"asset": name, "flagRaw": group["flagRaw"], **group["rows"][0]}


def skill_rows_preserving_duplicates(data, parser):
    try:
        return parser(data, True, game.Reader)
    except ValueError as error:
        if not str(error).startswith("Duplicate skill text key "):
            raise
    # Some public non-Korean tables contain duplicate keys; retain every row without choosing an overwrite rule.
    reader = game.Reader(data)
    count = reader.u32()
    require(count <= len(data) // 6, "Impossible skill row count")
    rows = []
    for _ in range(count):
        offset = reader.pos
        ident, kind = reader.i32(), reader.take(1)[0]
        rows.append({"skillId": ident, "kind": kind, "text": reader.string(), "decodedOffset": offset})
    require(reader.pos == len(data), "Trailing skill bytes")
    return rows


def audit_template_formats(rows):
    counts = collections.Counter()
    unusual = []
    non_plain = []
    for row in rows:
        for locale, text in row["templates"].items():
            tokens = re.findall(r"\{([^{}]*)\}", text)
            counts.update(tokens)
            for token in tokens:
                if token != "0":
                    non_plain.append({"propertyId": row["propertyId"], "locale": locale, "token": token})
                if token not in ("0", "0:0.00", "0:F1"):
                    unusual.append({"propertyId": row["propertyId"], "locale": locale, "text": text, "token": token})
            remaining = re.sub(r"\{[^{}]*\}", "", text)
            if "{" in remaining or "}" in remaining:
                unusual.append({"propertyId": row["propertyId"], "locale": locale, "text": text, "error": "unbalanced-brace"})
    return {"templateCount": sum(len(row["templates"]) for row in rows), "placeholderCounts": dict(counts),
            "nonPlainFormats": non_plain, "unsupportedOrMalformed": unusual}


def write_bytes(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    require(not path.exists() or path.read_bytes() == data, f"Different retained artifact exists: {path}; choose a new downloads directory")
    path.write_bytes(data)


def get_public(url, destination):
    require(url.startswith(PUBLIC_BASE) and ".." not in url, "Only the reviewed public asset base is allowed")
    with urllib.request.urlopen(url, timeout=30) as response:
        require(response.status == 200 and response.url == url, f"Unexpected HTTP response: {url}")
        data = response.read(32 * 1024 * 1024 + 1)
        require(len(data) <= 32 * 1024 * 1024, "Public asset exceeds read budget")
        record = {"url": url, "status": response.status, "bytes": len(data), "sha256": game.sha256(data),
                  "fetchedUtc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
                  "headers": dict(response.headers)}
    write_bytes(destination, data)
    return record


def extract(args):
    downloads = args.downloads.resolve()
    branch = downloads / args.application
    branch.mkdir(parents=True, exist_ok=True)
    manifest_path = downloads / (MANIFEST_NAME if args.application == "releaseA" else f"RevisionInfoBinary.{args.application}.bytes")
    requests = []
    if args.download:
        requests.append(get_public(f"{PUBLIC_BASE}{args.application}/{MANIFEST_NAME}", manifest_path))
    manifest_bytes = manifest_path.read_bytes()
    manifest = parse_manifest(manifest_bytes)
    catalog_bytes = args.catalog.read_bytes()
    catalog = json.loads(catalog_bytes)
    reference_path = ROOT / "data/sources/toram-items/item-special-references.json"
    reference_bytes = reference_path.read_bytes()
    references = json.loads(reference_bytes)
    require(references["sources"]["metadata"]["sha256"] == catalog["bonusEnumSource"]["sha256"], "Special-reference metadata differs from catalog")
    reference_spec = importlib.util.spec_from_file_location("item_references", Path(__file__).with_name("extract-toram-item-reference-texts.py"))
    reference_parser = importlib.util.module_from_spec(reference_spec)
    reference_spec.loader.exec_module(reference_parser)
    elements = {row["value"]: row["enumName"] for row in references["elementEnum"]["values"]}
    used_elements = {cap["value"] for item in catalog["items"] for cap in (item["propertyRecord"] or {}).get("caps", []) if cap["cap_id"] == 65}
    require(used_elements <= elements.keys(), "Unresolved item element enum")
    avatar_ids = set(reference_parser.AVATAR_SKILLS.values())
    require({int(key): value for key, value in references["nativeAvatarSkillRule"]["rawToSkillId"].items()} == reference_parser.AVATAR_SKILLS,
            "Avatar skill mapping differs from reviewed reference")
    name_constants = references["skillNameRule"]["constants"]
    require(name_constants == {"skillDefaultTag": "N", "skillBracketPrefix": "[N]", "skillUnknownName": "???"}, "Skill name constants changed")
    binary_asset = single_asset(manifest, "BynaryData")
    require(binary_asset["cacheKey"] == catalog["cacheVersion"], "Public manifest BynaryData differs from selected local master revision")
    locales = sorted(re.fullmatch(r"Localize/([a-z]+)/GameScene_\1", group["assetNameTemplate"]).group(1)
                     for group in manifest["groups"] if re.fullmatch(r"Localize/([a-z]+)/GameScene_\1", group["assetNameTemplate"]))
    require(locales and len(locales) == len(set(locales)), "No unique GameScene locales")
    assets = [binary_asset] + [single_asset(manifest, f"Localize/{locale}/GameScene_{locale}") for locale in locales]
    if args.download:
        for asset in assets:
            filename = asset["asset"].rsplit("/", 1)[-1] + ".unity3d"
            requests.append(get_public(f"{PUBLIC_BASE}{args.application}/{asset['asset']}.unity3d", branch / filename))
            time.sleep(0.4)
        (branch / "python-http-requests.json").write_text(json.dumps(requests, indent=2) + "\n", encoding="utf-8")
    if args.unitypy_path:
        sys.path.insert(0, str(args.unitypy_path.resolve()))
    import UnityPy
    expected_assets = {asset["name"]: asset for source in catalog["sources"] for asset in source["assets"]}
    known_master_ids = {item["gameItemId"] for item in catalog["items"]}
    require(len(known_master_ids) == len(catalog["items"]), "Duplicate catalog master IDs")
    links = {ident: {"gameItemId": ident, "names": {}, "descriptions": {}} for ident in known_master_ids}
    property_links, orphans, sources, master_checks, locale_counts = {}, [], [], [], {}
    element_texts = {str(ident): {} for ident in sorted(used_elements)}
    avatar_names, avatar_raw_names, special_diagnostics = {str(ident): {} for ident in sorted(avatar_ids)}, {str(ident): {} for ident in sorted(avatar_ids)}, []
    for asset in assets:
        name = asset["asset"].rsplit("/", 1)[-1]
        bundle_path = branch / f"{name}.unity3d"
        bundle_bytes = bundle_path.read_bytes()
        require(bundle_bytes.startswith(b"UnityFS\0"), f"Not a directly readable UnityFS bundle: {name}")
        is_master = name == "BynaryData"
        locale = None if is_master else name.removeprefix("GameScene_")
        environment = UnityPy.load(bundle_bytes)
        text_sources = []
        found_item = found_property = False
        for obj in environment.objects:
            if obj.type.name != "TextAsset":
                continue
            value = obj.parse_as_object()
            asset_name = value.m_Name
            if is_master and asset_name not in ("ItemMaster", "ItemProperties"):
                continue
            require(re.fullmatch(r"[A-Za-z0-9_.-]+", asset_name) is not None, f"Unsafe TextAsset name: {asset_name}")
            raw = value.m_Script.encode("utf-8", "surrogateescape")
            decoded = game.decode(raw, int(asset["cacheKey"], 16))
            relative = Path("extracted") / args.application / name / f"{asset_name}.bin"
            write_bytes(downloads / relative, raw)
            write_bytes((downloads / relative).with_suffix(".decoded.bin"), decoded)
            text_source = {"name": asset_name, "pathId": obj.path_id, "rawFile": relative.as_posix(),
                           "decodedFile": relative.with_suffix(".decoded.bin").as_posix(), "rawBytes": len(raw),
                           "rawSha256": game.sha256(raw), "decodedSha256": game.sha256(decoded), "textFormatParsed": False}
            if is_master:
                expected = expected_assets[asset_name]
                require(text_source["rawSha256"] == expected["rawSha256"] and text_source["decodedSha256"] == expected["decodedSha256"],
                        f"Public and cached {asset_name} differ")
                master_checks.append({"asset": asset_name, "rawSha256": text_source["rawSha256"],
                                      "decodedSha256": text_source["decodedSha256"], "equalsSelectedCatalogSource": True})
            elif asset_name in (f"Item_{locale}", f"ItemProperty_{locale}"):
                has_kind = asset_name == f"Item_{locale}"
                rows = game.parse_text(decoded, has_kind)
                text_source.update({"textFormatParsed": True, "rows": len(rows), "allBytesConsumed": True,
                                    "negativeIds": sum(row.get("propertyId", row.get("gameItemId", 0)) < 0 for row in rows)})
                if has_kind:
                    found_item = True
                    locale_counts[locale] = {"textRows": len(rows), "names": 0, "descriptions": 0, "orphanTextRows": 0}
                    for row in rows:
                        ident = row["gameItemId"]
                        if ident not in links:
                            orphans.append({"locale": locale, **row})
                            locale_counts[locale]["orphanTextRows"] += 1
                            continue
                        field = "names" if row["kind"] == 0 else "descriptions"
                        links[ident][field][locale] = row["text"]
                        locale_counts[locale][field] += 1
                else:
                    found_property = True
                    for row in rows:
                        prop = property_links.setdefault(row["propertyId"], {"propertyId": row["propertyId"], "templates": {}})
                        require(locale not in prop["templates"], "Duplicate locale/property ID")
                        prop["templates"][locale] = row["text"]
                parsed_path = (downloads / relative).with_suffix(".parsed.json")
                write_bytes(parsed_path, (json.dumps(rows, ensure_ascii=False, indent=2) + "\n").encode())
            elif asset_name == f"System_{locale}":
                rows = reference_parser.parse(decoded, False, game.Reader)
                grouped = collections.defaultdict(list)
                for row in rows:
                    grouped[row["key"]].append(row)
                for ident in used_elements:
                    candidates = grouped.get(elements[ident], [])
                    require(len(candidates) == 1, f"Missing/ambiguous element text {locale}/{ident}")
                    element_texts[str(ident)][locale] = candidates[0]["text"]
                text_source.update({"textFormatParsed": True, "rows": len(rows), "allBytesConsumed": True,
                                    "duplicateKeys": sum(len(values) > 1 for values in grouped.values())})
                write_bytes((downloads / relative).with_suffix(".parsed.json"), (json.dumps(rows, ensure_ascii=False, indent=2) + "\n").encode())
            elif asset_name == f"Skill_{locale}":
                rows = skill_rows_preserving_duplicates(decoded, reference_parser.parse)
                by_key = collections.defaultdict(list)
                for row in rows:
                    by_key[(row["skillId"], row["kind"])].append(row)
                for ident in avatar_ids:
                    require((ident, 0) in by_key and (ident, 1) in by_key, f"Incomplete native skill entry {locale}/{ident}")
                    if len(by_key[(ident, 0)]) != 1 or len(by_key[(ident, 1)]) != 1:
                        avatar_raw_names[str(ident)][locale] = None
                        avatar_names[str(ident)][locale] = None
                        special_diagnostics.append({"locale": locale, "skillId": ident, "reason": "duplicate native name/description rows; overwrite behavior unresolved",
                                                    "rows": by_key[(ident, 0)] + by_key[(ident, 1)]})
                        continue
                    raw_name = by_key[(ident, 0)][0]["text"]
                    derived = reference_parser.derive_skill_name(raw_name, name_constants)
                    avatar_raw_names[str(ident)][locale] = raw_name
                    avatar_names[str(ident)][locale] = derived["nativeCodeDerivedName"]
                    special_diagnostics.append({"locale": locale, "skillId": ident, "rawNameDecodedOffset": by_key[(ident, 0)][0]["decodedOffset"], **derived})
                text_source.update({"textFormatParsed": True, "rows": len(rows), "allBytesConsumed": True,
                                    "kindCounts": dict(collections.Counter(row["kind"] for row in rows)),
                                    "duplicateSkillKeys": [{"skillId": key[0], "kind": key[1], "count": len(values)} for key, values in by_key.items() if len(values) > 1]})
                write_bytes((downloads / relative).with_suffix(".parsed.json"), (json.dumps(rows, ensure_ascii=False, indent=2) + "\n").encode())
            text_sources.append(text_source)
        if not is_master:
            require(found_item and found_property, f"Missing required item tables in locale {locale}")
        sources.append({**asset, "url": f"{PUBLIC_BASE}{args.application}/{asset['asset']}.unity3d", "bundleFile": str(bundle_path),
                        "bundleBytes": len(bundle_bytes), "bundleSha256": game.sha256(bundle_bytes), "textAssets": text_sources})
    require(len(master_checks) == 2, "Master/property equivalence was not established")
    conflicts_kr = []
    for item in catalog["items"]:
        for field in ("names", "descriptions"):
            before = item[field].get("kr")
            after = links[item["gameItemId"]][field].get("kr")
            if before != after:
                conflicts_kr.append({"gameItemId": item["gameItemId"], "field": field, "cacheText": before, "publicText": after})
    require(not conflicts_kr, "Public Korean text differs from selected catalog; do not silently combine revisions")
    report = {
        "schemaVersion": 1, "authority": "public-static-game-assets-and-native-loader-code", "cacheVersion": catalog["cacheVersion"],
        "applicationPath": args.application, "activeServerReleaseObserved": False, "availableItemLocales": locales,
        "metadataLocaleTagsNotPresentInManifest": sorted(set(["jp", "us", "kr", "cns", "cnt", "fr", "th", "idn", "esp", "prt"]) - set(locales)),
        "catalog": {"path": str(args.catalog), "sha256": game.sha256(catalog_bytes)},
        "manifest": {"url": f"{PUBLIC_BASE}{args.application}/{MANIFEST_NAME}", "file": str(manifest_path), "sha256": game.sha256(manifest_bytes),
                     "bytes": len(manifest_bytes), "groupCount": manifest["groupCount"], "rowCount": manifest["rowCount"], "allBytesConsumed": True},
        "decoder": "Native AssetDecrypt uses Int32 revision as BE key bytes. Existing cache decoder reused with byte-swapped revision; strict UTF-8/count/EOF and duplicate-key checks applied to item tables.",
        "masterEquivalence": master_checks, "sources": sources,
        "counts": {"masterItems": len(links), "locales": len(locales), "perLocale": locale_counts,
                   "propertyIds": len(property_links), "negativePropertyIds": sum(ident < 0 for ident in property_links),
                   "orphanTextRows": len(orphans), "koreanCatalogConflicts": len(conflicts_kr)},
        "items": [links[ident] for ident in sorted(links)], "propertyTexts": [property_links[ident] for ident in sorted(property_links)],
        "templateFormatAudit": audit_template_formats(property_links.values()),
        "elementTextById": element_texts, "avatarSkillNamesById": avatar_names, "avatarSkillRawNamesById": avatar_raw_names,
        "specialTextEvidence": {"references": {"path": str(reference_path), "sha256": game.sha256(reference_bytes)},
                                "parser": {"path": str(Path(reference_parser.__file__)), "sha256": game.sha256(Path(reference_parser.__file__).read_bytes())},
                                "nameConstants": name_constants, "elementEnumNamesById": {str(ident): elements[ident] for ident in sorted(used_elements)},
                                "skillNamesAreNativeCodeDerived": True, "finalUiObserved": False, "skillNameDiagnostics": special_diagnostics},
        "orphanItemTexts": orphans,
        "limitations": ["The public releaseB manifest agrees with the selected cache master; the currently active server/application path was not observed.",
                        "Labels are joined by game integer IDs; Coryn names and site IDs are not used for localization identity.",
                        "System/Skill parse the reviewed native layouts; other TextAssets remain original/decoded bytes. Uninterpreted skill kinds are preserved without assigning semantics.",
                        "Avatar skill names reproduce the reviewed default N-tag lookup; final runtime UI/color/layout remains unobserved.",
                        "Property templates include signed negative IDs; final UI formatting and combat/statting formulas are separate.",
                        "Only GameScene locale tags actually enumerated by this manifest were requested; absent tags were not guessed."]
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    (branch / "parsed-manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"output": str(args.output), **report["counts"]}))


def self_test():
    body = b"\x00" + b"\x00" * 8 + struct.pack("<h", 1) + b"\x0aBynaryData\x01" + struct.pack("<iiii", 1, 0, 845306231, 50)
    data = body[:1] + struct.pack("<q", len(body)) + body[9:]
    parsed = parse_manifest(data)
    assert single_asset(parsed, "BynaryData")["cacheKey"] == "77596232"
    for bad in (data[:-1], data + b"x", data[:10]):
        try:
            parse_manifest(bad)
        except (ValueError, struct.error):
            pass
        else:
            raise AssertionError("Malformed manifest accepted")
    assert game.parse_text(struct.pack("<IiB", 1, -48, 3) + b"{0}", False)[0]["propertyId"] == -48
    assert audit_template_formats([{"propertyId": 140, "templates": {"us": "-{0:F1}s"}}])["unsupportedOrMalformed"] == []
    assert len(audit_template_formats([{"propertyId": 1, "templates": {"us": "{1}", "kr": "{"}}])["unsupportedOrMalformed"]) == 2
    def duplicate_parser(data, skill, reader):
        raise ValueError("Duplicate skill text key (1, 0)")
    duplicate_data = struct.pack("<I", 2) + (struct.pack("<iB", 1, 0) + b"\x01N") * 2
    assert len(skill_rows_preserving_duplicates(duplicate_data, duplicate_parser)) == 2
    try:
        skill_rows_preserving_duplicates(duplicate_data[:-1], duplicate_parser)
    except ValueError:
        pass
    else:
        raise AssertionError("Truncated duplicate skill table accepted")
    print("localization extraction self-test PASS (manifest bounds/EOF, revision byte order, signed IDs, duplicate skill rows, template formats)")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--downloads", type=Path, default=ROOT / "build/tmp/toram-item-extraction/game/downloads/localizations")
    parser.add_argument("--application", choices=[f"release{letter}" for letter in "ABCDEF"], default="releaseB")
    parser.add_argument("--catalog", type=Path, default=ROOT / "data/sources/toram-items/items.kr.77596232.json")
    parser.add_argument("--output", type=Path, default=ROOT / "data/sources/toram-items/item-localization-links.json")
    parser.add_argument("--unitypy-path", type=Path, default=ROOT / "build/tmp/toram-item-extraction/python-deps")
    parser.add_argument("--download", action="store_true")
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    self_test() if args.self_test else extract(args)


if __name__ == "__main__":
    main()
