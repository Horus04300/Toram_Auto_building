"""Map v31 metadata tokens to native pointers in an existing x64 module snapshot.

Reads saved files only. No process access or target execution.
CodeGenModule layout: Perfare/Il2CppDumper, Il2Cpp/Il2CppClass.cs.
"""

import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct


spec = importlib.util.spec_from_file_location("item_metadata", Path(__file__).with_name("extract-il2cpp-item-schema.py"))
metadata_module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(metadata_module)
require = metadata_module.require
SELECTED_TYPES = set("""ItemDBData MasterItemDataManager ItemTextManager
ItemPropertyTextManager TextManagerBase TextManagerDataBase UIItemProperty BonusManager
ResourceManager StageLoginDownloader""".split())


def matches(data, needle):
    start = 0
    while True:
        found = data.find(needle, start)
        if found < 0:
            return
        yield found
        start = found + 1


def find_module(data, base, image_name, expected_count):
    candidates = []
    for string_offset in matches(data, image_name.encode("utf-8") + b"\0"):
        name_pointer = base + string_offset
        for offset in matches(data, struct.pack("<Q", name_pointer)):
            if offset % 8 or offset + 24 > len(data):
                continue
            name, count, pointers = struct.unpack_from("<3Q", data, offset)
            table = pointers - base
            if count == expected_count and 0 <= table <= len(data) - count * 8:
                candidates.append({"module_offset": offset, "module_va": base + offset,
                                   "name_offset": string_offset, "name_va": name,
                                   "method_pointer_count": count, "method_pointers_va": pointers,
                                   "method_pointers_offset": table})
    require(len(candidates) == 1, f"Expected one validated module; found {len(candidates)}")
    return candidates[0]


def pointer_for_token(data, base, module, token):
    rid = token & 0xFFFFFF
    require(token >> 24 == 6 and 1 <= rid <= module["method_pointer_count"], "Method token outside module")
    slot = module["method_pointers_offset"] + (rid - 1) * 8
    value = struct.unpack_from("<Q", data, slot)[0]
    inside = value != 0 and base <= value < base + len(data)
    return {"pointer_slot_offset": slot, "pointer_slot_va": hex(base + slot),
            "runtime_va": hex(value) if value else None, "rva": hex(value - base) if inside else None,
            "status": "mapped" if inside else "null-unresolved" if value == 0 else "external-unresolved",
            "code_preview_hex": data[value - base:value - base + 24].hex() if inside else None}


def identity(path, data):
    return {"path": str(path.resolve()), "size": len(data), "sha256": hashlib.sha256(data).hexdigest()}


def extract(metadata_path, mapped_path, capture_path, destination):
    require(destination.resolve() not in {p.resolve() for p in [metadata_path, mapped_path, capture_path]},
            "Output must not overwrite an input")
    metadata_data = metadata_path.read_bytes()
    metadata = metadata_module.Metadata(metadata_data)
    data = mapped_path.read_bytes()
    capture = json.loads(capture_path.read_text(encoding="utf-8"))
    base = int(capture["base"], 16)
    require(len(data) == capture["size"], "Mapped image length differs from capture manifest")
    require(hashlib.sha256(data).hexdigest() == capture["mappedSha256"], "Mapped image SHA256 differs from capture manifest")
    require(capture["completeReadableImage"] and not capture["unreadablePages"], "Incomplete snapshot is unsupported")
    image_name = "Assembly-CSharp.dll"
    image = next(i for i in metadata.images if metadata.string(i[0]) == image_name)
    indexed = [(i, method) for i, method in enumerate(metadata.methods)
               if image[2] <= method[1] < image[2] + image[3]]
    rids = [method[6] & 0xFFFFFF for _, method in indexed]
    require(len(rids) == max(rids) and set(rids) == set(range(1, max(rids) + 1)), "Noncontiguous module method RIDs")
    module = find_module(data, base, image_name, max(rids))
    rows = []
    all_rows = []
    for index, method in indexed:
        cls = metadata.full_name(metadata.types[method[1]])
        name = metadata.string(method[0])
        mapping = pointer_for_token(data, base, module, method[6])
        all_rows.append([cls, name, f"0x{method[6]:08x}", index, mapping["runtime_va"], mapping["rva"], mapping["status"]])
        if cls not in SELECTED_TYPES:
            continue
        row = {"class": cls, "name": name, "method_definition_index": index,
               "token": f"0x{method[6]:08x}", "metadata_declaration_range": metadata.location("methods", index, 36),
               "generic_container_index": method[5], "method_flags_raw": hex(method[7]),
               "parameters": [{"name": metadata.string(p[0]), **metadata.type_ref(p[2])}
                              for p in metadata.parameters[method[4]:method[4] + method[10]]],
               "return_type": metadata.type_ref(method[2]), **mapping}
        rows.append(row)
    result = {"evidence_kind": "saved-runtime-image-plus-metadata-token-map",
              "sources": {"metadata": identity(metadata_path, metadata_data), "mapped_image": identity(mapped_path, data),
                          "capture_manifest": identity(capture_path, capture_path.read_bytes())},
              "layout_source": "https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Il2Cpp/Il2CppClass.cs",
              "image_base": hex(base), "module_name": image_name, "module": module,
              "validation": {"metadata_module_method_count": len(indexed), "maximum_rid": max(rids),
                             "count_equals_max_rid": True, "snapshot_digest_matches_capture": True,
                             "selected_methods": len(rows)},
              "methods": rows,
              "limitations": ["Metadata declaration offsets are not code addresses; only pointer-table values establish native locations.",
                              "NULL pointers remain unresolved; generic or shared implementations are not inferred.",
                              "Mapping establishes saved pointer identity, not observed execution or a call edge.",
                              "The source capture was sequential and non-atomic; no process access was performed by this parser."]}
    destination.parent.mkdir(parents=True, exist_ok=True)
    destination.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    with destination.with_name("all-native-methods.tsv").open("w", encoding="utf-8", newline="") as stream:
        writer = csv.writer(stream, delimiter="\t")
        writer.writerow(["class", "method", "token", "method_definition_index", "runtime_va", "rva", "status"])
        writer.writerows(all_rows)
    print(json.dumps({"output": str(destination.resolve()), **result["validation"]}))


def self_test():
    data = bytearray(0x500)
    base = 0x100000
    data[0x80:0x84] = b"X\0\0\0"
    struct.pack_into("<3Q", data, 0x100, base + 0x80, 2, base + 0x200)
    struct.pack_into("<2Q", data, 0x200, base + 0x350, 0)
    module = find_module(data, base, "X", 2)
    require(pointer_for_token(data, base, module, 0x06000001)["rva"] == "0x350", "RID-to-pointer mapping")
    require(pointer_for_token(data, base, module, 0x06000002)["status"] == "null-unresolved", "NULL pointer handling")
    for count in [1, 3, 1000]:
        try:
            find_module(data, base, "X", count)
        except ValueError:
            pass
        else:
            raise AssertionError("Count mismatch accepted")
    try:
        pointer_for_token(data, base, module, 0x06000003)
    except ValueError:
        pass
    else:
        raise AssertionError("Out-of-range token accepted")
    print("IL2CPP native map self-test PASS (module identity, count, RID, bounds and NULL pointers)")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ["metadata", "mapped", "capture", "destination"]:
        parser.add_argument(name, nargs="?", type=Path)
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        self_test()
    else:
        if not all([args.metadata, args.mapped, args.capture, args.destination]):
            parser.error("metadata, mapped image, capture manifest and destination JSON are required")
        extract(args.metadata, args.mapped, args.capture, args.destination)
