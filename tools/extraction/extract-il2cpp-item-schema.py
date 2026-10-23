"""Read-only, dependency-free IL2CPP v31 item/localization schema inspection.

Layout reference: https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Il2Cpp/MetadataClass.cs
This is local byte-parser evidence, not a REA engine result or recovered C# body.
"""

import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import struct


TABLES = """string_literals literal_data strings events properties methods
parameter_defaults field_defaults default_data field_marshaled_sizes parameters
fields generic_parameters generic_constraints generic_containers nested_types
interfaces vtable_methods interface_offsets types images assemblies field_refs
referenced_assemblies attribute_data attribute_ranges unresolved_types
unresolved_ranges windows_runtime_names windows_runtime_strings exported_types""".split()
CORE_NAMES = set("""ItemData ItemDBData ItemFlag ItemType EquipType ArmorAbility
ItemManager MasterItemDataManager ItemRandomPropertyData ItemRandomPropertyMaster
ItemRandomPropertyMasterData ItemRandomPropertyManager ItemTextManager
ItemTextManagerData ItemPropertyTextManager ItemRandomPropertyTextManager
ItemRandomPropertyTextManagerData LocalizeManager LocalizeType LocalizeId
AssetBundleManager ResourceManager DownloadManager CacheManager
TextManagerBase TextManagerDataBase TextManagerData TextManager BinaryReader BinaryWriter
BonusManager BonusType UIItemProperty""".split())
TYPE_STRUCT = struct.Struct("<16i8H2I")
METHOD_STRUCT = struct.Struct("<7i4H")


def require(condition, message):
    if not condition:
        raise ValueError(message)


def compressed_int32(data, offset):
    require(0 <= offset < len(data), "Compressed integer out of bounds")
    first = data[offset]
    if first < 0x80:
        encoded, size = first, 1
    elif first < 0xC0:
        size = 2
        require(offset + size <= len(data), "Truncated compressed integer")
        encoded = ((first & 0x7F) << 8) | data[offset + 1]
    elif first < 0xE0:
        size = 4
        require(offset + size <= len(data), "Truncated compressed integer")
        encoded = ((first & 0x3F) << 24) | int.from_bytes(data[offset + 1:offset + 4], "big")
    elif first == 0xF0:
        size = 5
        require(offset + size <= len(data), "Truncated compressed integer")
        encoded = int.from_bytes(data[offset + 1:offset + 5], "little")
    elif first in (0xFE, 0xFF):
        encoded, size = 0xFFFFFFFF - (first == 0xFE), 1
    else:
        raise ValueError("Unsupported compressed integer prefix")
    value = -2147483648 if encoded == 0xFFFFFFFF else (-(encoded >> 1) - 1 if encoded & 1 else encoded >> 1)
    return value, size


class Metadata:
    def __init__(self, data):
        self.data = data
        require(len(data) >= 256, "Truncated metadata header")
        magic, version = struct.unpack_from("<2I", data)
        require(magic == 0xFAB11BAF and version == 31, "Only standard IL2CPP v31 supported")
        self.tables = {}
        for i, name in enumerate(TABLES):
            offset, size = struct.unpack_from("<2I", data, 8 + i * 8)
            require(256 <= offset <= len(data) and size <= len(data) - offset,
                    f"Table out of bounds: {name}")
            self.tables[name] = {"offset": offset, "size": size}
        self.strings = self.block("strings")
        self.types = self.records("types", TYPE_STRUCT)
        self.fields = self.records("fields", struct.Struct("<3I"))
        self.methods = self.records("methods", METHOD_STRUCT)
        self.parameters = self.records("parameters", struct.Struct("<3I"))
        self.defaults = {row[0]: row[1:] for row in self.records("field_defaults", struct.Struct("<3i"))}
        self.images = self.records("images", struct.Struct("<10i"))
        self.byval_names = {t[2]: self.full_name(t) for t in self.types}
        self.validate()

    def block(self, name):
        t = self.tables[name]
        return self.data[t["offset"]:t["offset"] + t["size"]]

    def records(self, name, layout):
        block = self.block(name)
        require(len(block) % layout.size == 0, f"Invalid {name} record size")
        return list(layout.iter_unpack(block))

    def string(self, index):
        require(0 <= index < len(self.strings), "String index out of bounds")
        end = self.strings.find(b"\0", index)
        require(end >= 0, "Unterminated metadata string")
        return self.strings[index:end].decode("utf-8")

    def full_name(self, t):
        return ".".join(filter(None, [self.string(t[1]), self.string(t[0])]))

    def validate(self):
        for i, t in enumerate(self.types):
            self.full_name(t)
            require(t[18] == 0 or 0 <= t[8] <= len(self.fields) - t[18], f"Type {i}: field range")
            require(t[16] == 0 or 0 <= t[9] <= len(self.methods) - t[16], f"Type {i}: method range")
            require(t[25] >> 24 == 2, f"Type {i}: token")
            for j in range(t[9], t[9] + t[16]):
                require(self.methods[j][1] == i, f"Method {j}: declaring type mismatch")
        for i, m in enumerate(self.methods):
            self.string(m[0])
            require(m[10] == 0 or 0 <= m[4] <= len(self.parameters) - m[10], f"Method {i}: parameters")
            require(m[6] >> 24 == 6, f"Method {i}: token")
        for f in self.fields:
            self.string(f[0])
            require(f[2] >> 24 == 4, "Field token")

    def location(self, table, index, size):
        return {"offset": self.tables[table]["offset"] + index * size, "size": size}

    def type_ref(self, index):
        # Attribute-bearing and composite Il2CppType records live in GameAssembly.
        return {"type_index": index, "exact_byval_name": self.byval_names.get(index)}

    def schema(self, i):
        t = self.types[i]
        image = next((self.string(im[0]) for im in self.images if im[2] <= i < im[2] + im[3]), None)
        result = {"type_definition_index": i, "name": self.full_name(t), "image": image,
                  "range": self.location("types", i, TYPE_STRUCT.size), "byval_type_index": t[2],
                  "declaring_type": self.type_ref(t[3]), "parent_type": self.type_ref(t[4]),
                  "is_enum": bool(t[24] & 2), "fields": [], "methods": []}
        for j in range(t[8], t[8] + t[18]):
            f = self.fields[j]
            row = {"field_index": j, "name": self.string(f[0]), **self.type_ref(f[1]),
                   "token": f"0x{f[2]:08x}", "range": self.location("fields", j, 12)}
            default = self.defaults.get(j)
            if default and default[1] >= 0:
                offset = self.tables["default_data"]["offset"] + default[1]
                require(offset < self.tables["default_data"]["offset"] + self.tables["default_data"]["size"],
                        "Default data index out of bounds")
                row["default"] = {"type_index": default[0], "data_index": default[1], "offset": offset,
                                  "preview_hex": self.data[offset:offset + 8].hex()}
                if self.byval_names.get(default[0]) == "System.Int32":
                    value, size = compressed_int32(self.block("default_data"), default[1])
                    row["default"].update({"int32_value": value, "encoded_size": size})
            result["fields"].append(row)
        for j in range(t[9], t[9] + t[16]):
            m = self.methods[j]
            parameters = [{"name": self.string(p[0]), **self.type_ref(p[2])}
                          for p in self.parameters[m[4]:m[4] + m[10]]]
            result["methods"].append({"method_index": j, "name": self.string(m[0]),
                                      "return_type": self.type_ref(m[2]), "parameters": parameters,
                                      "token": f"0x{m[6]:08x}", "range": self.location("methods", j, 36)})
        return result

    def resource_literals(self):
        result = []
        for i, (size, start) in enumerate(self.records("string_literals", struct.Struct("<2I"))):
            require(start <= self.tables["literal_data"]["size"] - size, "Literal out of bounds")
            offset = self.tables["literal_data"]["offset"] + start
            value = self.data[offset:offset + size].decode("utf-8")
            if len(value) < 500 and re.search(r"item|localiz|\.unity3d|CommonAssetBundle|resources/|Version\{", value, re.I):
                result.append({"literal_index": i, "value": value, "range": {"offset": offset, "size": size}})
        return result


def extract(path, output):
    data = path.read_bytes()
    metadata = Metadata(data)
    selected = [i for i, t in enumerate(metadata.types)
                if metadata.string(t[0]) in CORE_NAMES or metadata.string(t[1]).startswith("Toram.Common.Items")]
    schemas = [metadata.schema(i) for i in selected]
    literals = metadata.resource_literals()
    result = {
        "evidence_kind": "local-static-byte-parser",
        "source": {"path": str(path.resolve()), "sha256": hashlib.sha256(data).hexdigest(), "size": len(data)},
        "layout_source": "https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Il2Cpp/MetadataClass.cs",
        "integer_encoding_source": "https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Extensions/BinaryReaderExtensions.cs",
        "metadata_version": 31, "tables": metadata.tables,
        "counts": {"types": len(metadata.types), "fields": len(metadata.fields),
                   "methods": len(metadata.methods), "selected_types": len(schemas), "selected_literals": len(literals)},
        "limitations": ["Declarations only; method bodies, memory offsets, runtime state and item rows are not recovered.",
                        "Unresolved type indices require GameAssembly metadata registration, not a guessed type name.",
                        "Literal presence alone does not connect a string to a method or prove that a URL is active.",
                        "Only exact System.Int32 defaults are decoded; other field-default previews remain raw bytes.",
                        "Bonus enum names establish IDs, not runtime scaling factors or display formatting."],
        "types": schemas, "resource_literals": literals,
    }
    output.mkdir(parents=True, exist_ok=True)
    (output / "item-schema.json").write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    bonus_enum = next((t for t in schemas if t["name"] == "Toram.Common.Bonus.BonusType"), None)
    if bonus_enum:
        values = [{"id": f["default"]["int32_value"], "name": f["name"],
                   "field_range": f["range"], "default_offset": f["default"]["offset"],
                   "default_size": f["default"]["encoded_size"]}
                  for f in bonus_enum["fields"] if "int32_value" in f.get("default", {})]
        bonus_result = {"source": result["source"], "enum": bonus_enum["name"],
                        "type_definition_index": bonus_enum["type_definition_index"],
                        "count": len(values), "values": values,
                        "by_id": {str(v["id"]): v["name"] for v in values},
                        "limitations": ["IDs are decoded metadata constants, not inferred list positions.",
                                        "Runtime scaling and display formatting remain unknown; do not interpolate raw cap values directly into localized templates."]}
        (output / "bonus-types.json").write_text(json.dumps(bonus_result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    with (output / "type-index.tsv").open("w", newline="", encoding="utf-8") as stream:
        writer = csv.writer(stream, delimiter="\t")
        writer.writerow(["index", "name", "byval_type_index", "file_offset", "field_count", "method_count"])
        for i, t in enumerate(metadata.types):
            writer.writerow([i, metadata.full_name(t), t[2], metadata.location("types", i, 88)["offset"], t[18], t[16]])
    print(json.dumps({"output": str(output.resolve()), **result["counts"], "sha256": result["source"]["sha256"]}))


def self_test():
    require(TYPE_STRUCT.size == 88 and METHOD_STRUCT.size == 36, "Record layout size")
    for encoded, expected in [(b"\0", 0), (b"\x03", -2), (bytes.fromhex("80c8"), 100),
                              (bytes.fromhex("c0008000"), 16384),
                              (bytes.fromhex("f000000080"), 1073741824),
                              (b"\xfe", 2147483647), (b"\xff", -2147483648)]:
        require(compressed_int32(encoded, 0) == (expected, len(encoded)), "Compressed integer decoding")
    for encoded in [b"", b"\x80", b"\xc0\0", b"\xf0\0", b"\xe8"]:
        try:
            compressed_int32(encoded, 0)
        except ValueError:
            pass
        else:
            raise AssertionError("Invalid compressed integer accepted")
    for data in [b"", bytes(256), struct.pack("<2I", 0xFAB11BAF, 29) + bytes(248)]:
        try:
            Metadata(data)
        except ValueError:
            pass
        else:
            raise AssertionError("Malformed metadata accepted")
    strings = b"\0T\0field\0method\0parameter\0"
    type_row = [1, 0, 3, -1, -1, -1, -1, 0, 0, 0, -1, -1, -1, -1, -1, -1]
    type_row += [1, 0, 1, 0, 0, 0, 0, 0, 0, 0x02000001]
    blocks = {"strings": strings, "types": TYPE_STRUCT.pack(*type_row),
              "fields": struct.pack("<3I", 3, 3, 0x04000001),
              "methods": METHOD_STRUCT.pack(9, 0, 3, 0, 0, -1, 0x06000001, 0, 0, 0, 1),
              "parameters": struct.pack("<3I", 16, 0x08000001, 3)}
    fixture = bytearray(struct.pack("<2I", 0xFAB11BAF, 31) + bytes(248))
    for i, name in enumerate(TABLES):
        block = blocks.get(name, b"")
        struct.pack_into("<2I", fixture, 8 + i * 8, len(fixture), len(block))
        fixture.extend(block)
    metadata = Metadata(bytes(fixture))
    schema = metadata.schema(0)
    require(schema["name"] == "T" and schema["fields"][0]["name"] == "field", "Type/field decoding")
    require(schema["methods"][0]["name"] == "method", "Method decoding")
    require(schema["methods"][0]["parameters"][0]["name"] == "parameter", "Parameter decoding")
    require(schema["methods"][0]["return_type"]["exact_byval_name"] == "T", "Type index resolution")
    bad_type = metadata.tables["types"]["offset"]
    struct.pack_into("<i", fixture, bad_type + 8 * 4, 2)
    try:
        Metadata(bytes(fixture))
    except ValueError:
        pass
    else:
        raise AssertionError("Out-of-bounds field range accepted")
    print("IL2CPP schema self-test PASS (schema, type linkage, compressed integers, invalid ranges and headers)")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("metadata", type=Path, nargs="?")
    parser.add_argument("output", type=Path, nargs="?")
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        self_test()
    else:
        if not args.metadata or not args.output:
            parser.error("metadata and output paths are required")
        extract(args.metadata, args.output)
