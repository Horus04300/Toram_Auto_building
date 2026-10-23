"""Parse an already decoded Toram ItemMaster TextAsset without modifying input.

The 37-byte layout is inferred from all local rows and ItemDBData declarations.
Names/order are derived, not proven by native CreateItemData method bodies.
"""

import argparse
import hashlib
import json
from pathlib import Path
import struct


FIELDS = [
    ("id", "i"), ("sort_id", "i"), ("type_id", "i"), ("price", "i"),
    ("material_level", "B"), ("material_id", "B"), ("process", "h"),
    ("stack", "h"), ("function", "h"), ("stability", "B"),
    ("range_raw", "B"), ("slot_max_raw", "B"), ("potential", "h"),
    ("model", "i"), ("flag_raw", "I"),
]
RECORD = struct.Struct("<" + "".join(fmt for _, fmt in FIELDS))
PROPERTY_RECORD = struct.Struct("<i20h")


def require(condition, message):
    if not condition:
        raise ValueError(message)


def parse(data):
    require(len(data) >= 4, "Missing ItemMaster count")
    count = struct.unpack_from("<I", data)[0]
    require(len(data) == 4 + count * RECORD.size, "ItemMaster row count or EOF mismatch")
    rows = []
    ids = set()
    for i, values in enumerate(RECORD.iter_unpack(data[4:])):
        row = dict(zip((name for name, _ in FIELDS), values))
        require(row["id"] > 0 and row["id"] not in ids, f"Invalid or duplicate item ID at row {i}")
        require(row["sort_id"] >= 0 and 0 <= row["type_id"] <= 32767, f"Invalid item indexes at row {i}")
        offset = 4 + i * RECORD.size
        row["decoded_offset"] = offset
        row["raw_record_hex"] = data[offset:offset + RECORD.size].hex()
        rows.append(row)
        ids.add(row["id"])
    return rows


def parse_properties(data):
    require(len(data) >= 4, "Missing ItemProperties count")
    count = struct.unpack_from("<I", data)[0]
    require(len(data) == 4 + count * PROPERTY_RECORD.size, "ItemProperties row count or EOF mismatch")
    result = {}
    for i, values in enumerate(PROPERTY_RECORD.iter_unpack(data[4:])):
        item_id = values[0]
        require(item_id > 0 and item_id not in result, f"Invalid or duplicate property item ID at row {i}")
        offset = 4 + i * PROPERTY_RECORD.size
        result[item_id] = {
            "id": item_id, "decoded_offset": offset,
            "raw_record_hex": data[offset:offset + PROPERTY_RECORD.size].hex(),
            "caps": [{"slot": j + 1, "cap_id": values[1 + j * 2], "value": values[2 + j * 2]}
                     for j in range(10)],
        }
    return result


def self_test():
    require(RECORD.size == 37, "Layout size")
    values = (10001, 10001, 10, 1, 1, 0, 2, 1, 10, 80, 4, 0, 15, 1, 0x4004)
    fixture = struct.pack("<I", 1) + RECORD.pack(*values)
    row = parse(fixture)[0]
    require(row["id"] == 10001 and row["function"] == 10 and row["stability"] == 80,
            "Weapon fields")
    require(row["potential"] == 15 and row["model"] == 1 and row["flag_raw"] == 0x4004,
            "Tail field ordering")
    for invalid in [b"", fixture[:-1], fixture + b"\0",
                    struct.pack("<I", 2) + fixture[4:] * 2,
                    struct.pack("<I", 1) + RECORD.pack(0, *values[1:])]:
        try:
            parse(invalid)
        except ValueError:
            pass
        else:
            raise AssertionError("Malformed or duplicate ItemMaster accepted")
    properties = struct.pack("<I", 1) + PROPERTY_RECORD.pack(10001, 3, -10, *([0] * 18))
    prop = parse_properties(properties)[10001]
    require(prop["caps"][0] == {"slot": 1, "cap_id": 3, "value": -10}, "Signed property values")
    require(len(prop["caps"]) == 10 and prop["caps"][-1]["value"] == 0, "Preserved empty slots")
    for invalid in [b"", properties[:-1], properties + b"\0",
                    struct.pack("<I", 2) + properties[4:] * 2]:
        try:
            parse_properties(invalid)
        except ValueError:
            pass
        else:
            raise AssertionError("Malformed or duplicate ItemProperties accepted")
    print("ItemMaster/Properties self-test PASS (offsets, EOF, IDs, signed caps and empty slots)")


def extract(source, destination, properties_source=None):
    require(source.resolve() != destination.resolve(), "Output must not overwrite source")
    data = source.read_bytes()
    rows = parse(data)
    offset = 0
    layout = []
    for name, fmt in FIELDS:
        size = struct.calcsize("<" + fmt)
        layout.append({"field": name, "format": fmt, "record_offset": offset, "size": size})
        offset += size
    result = {
        "evidence_kind": "local-static-byte-parser-derived-layout",
        "source": {"path": str(source.resolve()), "sha256": hashlib.sha256(data).hexdigest(), "size": len(data)},
        "row_count": len(rows), "record_size": RECORD.size, "layout": layout,
        "validation": {"exact_eof": True, "unique_positive_ids": True,
                       "minimum_id": min((row["id"] for row in rows), default=None),
                       "maximum_id": max((row["id"] for row in rows), default=None)},
        "limitations": ["Field names/order are derived from ItemDBData metadata and full-file structure; native method bodies were unavailable.",
                        "function, range_raw, slot_max_raw and flag_raw remain raw game values; category-specific semantics are not applied.",
                        "Cap values are raw signed integers, not verified display values; per-cap scaling is unresolved and direct template interpolation is unsafe.",
                        "Names, descriptions and item properties are separate resources, joined by original game ID.",
                        "Local cache contents establish a downloaded snapshot, not current server completeness."],
        "items": rows,
    }
    if properties_source:
        require(properties_source.resolve() != destination.resolve(), "Output must not overwrite properties source")
        properties_data = properties_source.read_bytes()
        properties = parse_properties(properties_data)
        for row in rows:
            row["property_record"] = properties.get(row["id"])
        master_ids = {row["id"] for row in rows}
        result["orphan_properties"] = [value for key, value in properties.items() if key not in master_ids]
        result["properties_source"] = {"path": str(properties_source.resolve()),
                                       "sha256": hashlib.sha256(properties_data).hexdigest(),
                                       "size": len(properties_data)}
        result["properties_layout"] = {"record_size": PROPERTY_RECORD.size,
                                       "format": "i32 itemId + 10 * (i16 capId, i16 signedValue)",
                                       "cap_id_join": "ItemProperty_<locale> original ID; zero slots retained"}
        result["validation"].update({"property_records": len(properties), "properties_exact_eof": True,
                                     "joined_properties": sum(row["property_record"] is not None for row in rows),
                                     "orphan_properties": len(result["orphan_properties"])})
    destination.parent.mkdir(parents=True, exist_ok=True)
    destination.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"output": str(destination.resolve()), "rows": len(rows), **result["validation"]}))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", nargs="?", type=Path)
    parser.add_argument("destination", nargs="?", type=Path)
    parser.add_argument("--self-test", action="store_true")
    parser.add_argument("--properties", type=Path, help="Decoded ItemProperties resource to join by game item ID")
    args = parser.parse_args()
    if args.self_test:
        self_test()
    else:
        if not args.source or not args.destination:
            parser.error("decoded source and destination JSON paths are required")
        extract(args.source, args.destination, args.properties)
