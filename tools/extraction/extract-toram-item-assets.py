"""Read-only Toram Unity cache extraction. Requires UnityPy 1.25.4.

Names/IDs come from game bytes; cache modification time does not prove an active release.
"""
import argparse
import collections
import hashlib
import json
import os
from pathlib import Path
import runpy
import struct
import sys


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def decode(data, version):
    key = version.to_bytes(4, "little")
    end = len(data) // 4 * 4
    return bytes(data[i] ^ (data[i - 4] if i >= 4 else 0) ^ key[i % 4]
                 for i in range(end)) + data[end:]


class Reader:
    def __init__(self, data):
        self.data, self.pos = data, 0

    def take(self, count):
        if count < 0 or self.pos + count > len(self.data):
            raise ValueError(f"Truncated data at {self.pos}, requested {count}")
        start = self.pos
        self.pos += count
        return self.data[start:self.pos]

    def u32(self):
        return struct.unpack("<I", self.take(4))[0]

    def i32(self):
        return struct.unpack("<i", self.take(4))[0]

    def string(self):
        size = 0
        for shift in range(0, 35, 7):
            value = self.take(1)[0]
            if shift == 28 and value > 7:
                raise ValueError("Invalid BinaryReader string length")
            size |= (value & 127) << shift
            if value < 128:
                return self.take(size).decode("utf-8", errors="strict")
        raise ValueError("Invalid string length")


def parse_text(data, has_kind):
    reader = Reader(data)
    count = reader.u32()
    if count > len(data) // (6 if has_kind else 5):
        raise ValueError("Impossible record count")
    rows, seen = [], set()
    for _ in range(count):
        offset = reader.pos
        ident = reader.i32()
        kind = reader.take(1)[0] if has_kind else None
        key = (ident, kind)
        if key in seen:
            raise ValueError(f"Duplicate text key {key}")
        seen.add(key)
        row = {"gameItemId" if has_kind else "propertyId": ident,
               "text": reader.string(), "decodedOffset": offset}
        if has_kind:
            if kind not in (0, 1):
                raise ValueError(f"Unknown item text kind {kind}")
            row["kind"] = kind
        rows.append(row)
    if reader.pos != len(data):
        raise ValueError(f"Trailing bytes: {len(data) - reader.pos}")
    return rows


def write_json(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    write_bytes(path, (json.dumps(value, ensure_ascii=False, indent=2) + "\n").encode("utf-8"))


def write_bytes(path, data):
    if path.exists() and path.read_bytes() != data:
        raise ValueError(f"Refusing to overwrite different output: {path}")
    path.write_bytes(data)


def join_items(master, properties, text_tables, property_tables, bonus_names):
    items = {row["id"]: {"gameItemId": row["id"], "names": {}, "descriptions": {},
                         "master": row, "propertyRecord": properties.get(row["id"])} for row in master}
    orphans = []
    for locale, rows in text_tables.items():
        for row in rows:
            if row["gameItemId"] not in items:
                orphans.append({"locale": locale, **row})
                continue
            target = items[row["gameItemId"]]
            target["names" if row["kind"] == 0 else "descriptions"][locale] = row["text"]
    labels = {locale: {row["propertyId"]: row["text"] for row in rows}
              for locale, rows in property_tables.items()}
    for item in items.values():
        if item["propertyRecord"] is not None:
            for cap in item["propertyRecord"]["caps"]:
                cap["enumName"] = bonus_names.get(str(cap["cap_id"]))
                cap["templates"] = {locale: table[cap["cap_id"]] for locale, table in labels.items()
                                    if cap["cap_id"] in table}
    return list(items.values()), orphans


def self_test():
    original = struct.pack("<IIBB", 1, 1000, 0, 6) + "리바".encode()
    version = 0xE8E43F32
    key = version.to_bytes(4, "little")
    for tail in (b"", b"x", b"xy", b"xyz"):
        payload, encrypted = original + tail, bytearray()
        for i, value in enumerate(payload):
            encrypted.append(value ^ (encrypted[i - 4] if i >= 4 else 0) ^ key[i % 4]
                             if i < len(payload) // 4 * 4 else value)
        assert decode(encrypted, version) == payload
    assert parse_text(original, True)[0]["text"] == "리바"
    negative_label = struct.pack("<IiB", 1, -166, 3) + b"{0}"
    assert parse_text(negative_label, False)[0]["propertyId"] == -166
    for bad in (original[:-1], original + b"\0", struct.pack("<I", 999)):
        try:
            parse_text(bad, True)
        except ValueError:
            pass
        else:
            raise AssertionError("Malformed table accepted")
    joined, orphans = join_items([{"id": 1000}], {1000: {"caps": [{"cap_id": 1, "value": -10}]}},
                                {"kr": [{"gameItemId": 1000, "kind": 0, "text": "리바"},
                                        {"gameItemId": 9999, "kind": 0, "text": "missing"}]},
                                {"kr": [{"propertyId": 1, "text": "STR+{0}"}]}, {"1": "bStr"})
    assert joined[0]["names"] == {"kr": "리바"} and len(orphans) == 1
    assert joined[0]["propertyRecord"]["caps"][0]["value"] == -10
    assert joined[0]["propertyRecord"]["caps"][0]["enumName"] == "bStr"
    print("PASS: feedback decode, UTF-8, count/truncation/trailing-byte validation")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cache", type=Path, default=Path(os.environ["USERPROFILE"]) /
                        "AppData/LocalLow/Unity/Asobimo,Inc_ToramOnline")
    parser.add_argument("--install", type=Path, default=Path("C:/Asobimo/AsobimoGames/Toram"))
    parser.add_argument("--output", type=Path, default=Path("build/tmp/toram-item-extraction/game"))
    parser.add_argument("--unitypy-path", type=Path)
    parser.add_argument("--version", required=False, help="Exact 8-digit cached version; required for parsing")
    parser.add_argument("--name", action="append", default=[])
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        self_test()
        return
    if args.unitypy_path:
        sys.path.insert(0, str(args.unitypy_path.resolve()))
    import UnityPy
    if not args.cache.is_dir():
        raise ValueError(f"Cache directory absent: {args.cache}")
    args.output.mkdir(parents=True, exist_ok=True)
    manifest, parsed, text_tables, property_tables = [], [], {}, {}
    needles = args.name or ["리바이타", "Revita", "リバイタ", "Myco Hat", "루브닐"]
    hits = []
    def scan(data, source, stage):
        for name in needles:
            for encoding in ("utf-8", "utf-16-le"):
                needle = name.encode(encoding)
                start, offsets = 0, []
                while (offset := data.find(needle, start)) >= 0:
                    offsets.append(offset)
                    start = offset + len(needle)
                if offsets:
                    hits.append({"source": source, "stage": stage, "name": name,
                                 "encoding": encoding, "count": len(offsets), "offsets": offsets[:20]})
    relevant = {"ItemMaster", "ItemProperties", "ItemDorpData", "ItemRandomPropertyMaster",
                "ItemCreateSupport", "NGItem", "RecipeMaster", "EquipModelProperty"}
    bundle_dirs = [p for p in args.cache.iterdir()
                   if p.is_dir() and (p.name == "BynaryData" or p.name.startswith("GameScene_"))]
    for folder in sorted(bundle_dirs):
        for source in sorted(folder.glob("*/__data")):
            before = source.read_bytes()
            version = int(source.parent.name, 16)
            if version > 0xFFFFFFFF:
                raise ValueError(f"Unrecognized cache version: {source.parent.name}")
            key = f"{version:08x}"
            environment = UnityPy.load(before)
            assets = []
            for obj in environment.objects:
                if obj.type.name != "TextAsset":
                    continue
                asset = obj.parse_as_object()
                name = asset.m_Name
                if name not in relevant and not name.startswith(("Item_", "ItemProperty_", "ItemRandomProperty_")):
                    continue
                if not name.replace("_", "").isalnum():
                    raise ValueError(f"Unsafe asset name {name!r}")
                raw = asset.m_Script.encode("utf-8", "surrogateescape")
                decoded = decode(raw, version)
                relative = Path("cache") / folder.name / key / f"{name}.bin"
                destination = args.output / relative
                destination.parent.mkdir(parents=True, exist_ok=True)
                write_bytes(destination, raw)
                write_bytes(destination.with_suffix(".decoded.bin"), decoded)
                assets.append({"name": name, "pathId": obj.path_id, "bytes": len(raw),
                               "rawSha256": sha256(raw), "decodedSha256": sha256(decoded),
                               "file": relative.as_posix()})
                scan(raw, relative.as_posix(), "raw-TextAsset")
                scan(decoded, relative.as_posix(), "decoded-TextAsset")
                if key == args.version and name.startswith(("Item_", "ItemProperty_", "ItemRandomProperty_")):
                    rows = parse_text(decoded, not name.startswith("ItemProperty_"))
                    write_json(args.output / "parsed" / f"{name}.{key}.json", rows)
                    locale = name.rsplit("_", 1)[1]
                    if name.startswith("Item_"):
                        text_tables[locale] = rows
                    elif name.startswith("ItemProperty_"):
                        property_tables[locale] = rows
                    parsed.append({"asset": name, "version": key, "records": len(rows),
                                   "uniqueIds": len({r.get("gameItemId", r.get("propertyId")) for r in rows}),
                                   "kindCounts": dict(collections.Counter(r.get("kind") for r in rows)),
                                   "allBytesConsumed": True})
            if sha256(source.read_bytes()) != sha256(before):
                raise ValueError(f"Cache changed during extraction: {source}")
            manifest.append({"source": str(source), "version": key, "bytes": len(before),
                             "sha256": sha256(before), "mtimeNs": source.stat().st_mtime_ns, "assets": assets})
    for relative in ("ToramOnline.exe", "GameAssembly.dll", "ToramOnline_Data/resources.assets",
                     "ToramOnline_Data/il2cpp_data/Metadata/global-metadata.dat"):
        source = args.install / relative
        data = source.read_bytes()
        scan(data, relative, "installed-bytes")
    write_json(args.output / "manifest.json", {"unityPyVersion": UnityPy.__version__,
               "selectedVersion": args.version, "selectionAuthority": "explicit-cache-version-not-live-release",
               "decoder": "Complete u32 words: plain[i] = cipher[i] XOR cipher[i-4] (or 0) XOR versionLE[i%4]; trailing 0..3 bytes unchanged",
               "bundles": manifest, "parsedTables": parsed})
    write_json(args.output / "string-search.json", {"queries": needles,
               "coverage": "Selected item TextAssets, four named installed artifacts; offsets are file/decoded bytes",
               "hits": hits})
    if args.version and not parsed:
        raise ValueError("Requested localization version not found")
    if args.version:
        master_parser = runpy.run_path(str(Path(__file__).with_name("decode-toram-item-master.py")))
        binary_dir = args.output / "cache/BynaryData" / args.version
        master = master_parser["parse"]((binary_dir / "ItemMaster.decoded.bin").read_bytes())
        properties = master_parser["parse_properties"]((binary_dir / "ItemProperties.decoded.bin").read_bytes())
        metadata_path = args.install / "ToramOnline_Data/il2cpp_data/Metadata/global-metadata.dat"
        metadata_bytes = metadata_path.read_bytes()
        metadata_parser = runpy.run_path(str(Path(__file__).with_name("extract-il2cpp-item-schema.py")))
        metadata = metadata_parser["Metadata"](metadata_bytes)
        enum_index = next(i for i, t in enumerate(metadata.types)
                          if metadata.full_name(t) == "Toram.Common.Bonus.BonusType")
        enum_schema = metadata.schema(enum_index)
        bonus_names = {str(field["default"]["int32_value"]): field["name"]
                       for field in enum_schema["fields"] if "int32_value" in field.get("default", {})}
        items, orphan_texts = join_items(master, properties, text_tables, property_tables, bonus_names)
        missing_properties = sorted(set(properties) - {row["gameItemId"] for row in items})
        if missing_properties:
            raise ValueError(f"Properties without master: {missing_properties}")
        selected_sources = [entry for entry in manifest if entry["version"] == args.version]
        catalog = {"schemaVersion": 1, "cacheVersion": args.version,
                   "authority": "local-game-cache-static-extraction",
                   "availableItemLocales": sorted(text_tables), "sources": selected_sources,
                   "bonusEnumSource": {"sha256": sha256(metadata_bytes), "typeDefinitionIndex": enum_index,
                                       "enum": enum_schema["name"], "count": len(bonus_names)},
                   "propertyValueMeaning": "Raw signed i16 before BonusManager.GetBonusTime/UIItemProperty formatting; enum names do not establish display scaling.",
                   "limitations": ["Cache version is not proof of active/latest server release.",
                                    "This parser validates metadata and complete byte layout; native-code confirmation is recorded separately.",
                                    "Raw function/range/slot/flag values have no category-specific unit conversion.",
                                    "Raw cap values must not be interpolated directly into templates; this extractor does not apply display scaling.",
                                    "Empty property slots and unlabeled cap IDs are preserved; Coryn site IDs are separate."],
                   "counts": {"masterItems": len(items), "propertyRecords": len(properties),
                              "orphanTextRecords": len(orphan_texts),
                              "missingTextIds": sum(not item["names"] and not item["descriptions"] for item in items)},
                   "orphanTexts": orphan_texts, "items": items}
        write_json(args.output / f"items.{args.version}.json", catalog)
        print(json.dumps({"catalog": catalog["counts"], "locales": sorted(text_tables)}))
    print(json.dumps({"bundles": len(manifest), "parsed": parsed, "searchHitGroups": len(hits)}))


if __name__ == "__main__":
    main()
