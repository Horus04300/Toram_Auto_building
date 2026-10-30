"""Read the fixed Registlet initializer FieldInfo from an already running game.

No launch, injection, target writes, function execution, or player data reads.
"""
import argparse
import ctypes
from ctypes import wintypes
import datetime
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import re
import struct

ROOT = Path(__file__).resolve().parents[4]
INSTALL = Path("C:/Asobimo/AsobimoGames/Toram")
MODULE_SHA = "c0f666aa071136bfae7ada61135ba01fc2907c3987945a86cce5909c6011fbff"
METADATA_SHA = "c5cb57c13fb2f4ba9258b8cf155ee866a8f67eee30f32d043e1fd854bba2eec9"
REFERENCE_RVA = 0x31f0e10


def require(condition, message):
    if not condition:
        raise ValueError(message)


def initializer(raw, metadata):
    require(len(raw) == 65 and raw[-1] == 0, "Expected 64-byte compiler hash and NUL")
    name = raw[:-1].decode("ascii")
    require(re.fullmatch("[0-9A-F]{64}", name), "Invalid compiler field hash")
    fields = []
    for index, row in enumerate(metadata.fields):
        if metadata.string(row[0]) == name:
            fields.append(index)
    require(len(fields) == 1, "Compiler field is missing or ambiguous")
    index = fields[0]
    default = metadata.defaults.get(index)
    require(default and default[1] >= 0, "Compiler field has no initialized bytes")
    type_name = metadata.byval_names.get(default[0])
    require(type_name == "__StaticArrayInitTypeSize=36", "Expected nine Int32 initializer")
    offset = metadata.tables["default_data"]["offset"] + default[1]
    data = metadata.data[offset:offset + 36]
    require(hashlib.sha256(data).hexdigest().upper() == name, "Compiler field content hash mismatch")
    return {"fieldIndex": index, "fieldName": name, "token": hex(metadata.fields[index][2]),
            "metadataOffset": offset, "bytes": 36, "hex": data.hex(),
            "values": list(struct.unpack("<9i", data))}


def capture(pid, output):
    require(os.name == "nt" and ctypes.sizeof(ctypes.c_void_p) == 8 and pid > 0, "64-bit Windows and positive PID required")
    require(not output.exists(), "Output must be new")
    module = (INSTALL / "GameAssembly.dll").read_bytes()
    metadata_bytes = (INSTALL / "ToramOnline_Data/il2cpp_data/Metadata/global-metadata.dat").read_bytes()
    require(hashlib.sha256(module).hexdigest() == MODULE_SHA, "Unreviewed installed module")
    require(hashlib.sha256(metadata_bytes).hexdigest() == METADATA_SHA, "Unreviewed installed metadata")
    spec = importlib.util.spec_from_file_location("metadata", ROOT / "tools/extraction/extract-il2cpp-item-schema.py")
    parser = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(parser)
    metadata = parser.Metadata(metadata_bytes)
    kernel = ctypes.WinDLL("kernel32", use_last_error=True)
    kernel.OpenProcess.argtypes = [wintypes.DWORD, wintypes.BOOL, wintypes.DWORD]
    kernel.OpenProcess.restype = wintypes.HANDLE
    kernel.CloseHandle.argtypes = [wintypes.HANDLE]
    kernel.QueryFullProcessImageNameW.argtypes = [wintypes.HANDLE, wintypes.DWORD, wintypes.LPWSTR, ctypes.POINTER(wintypes.DWORD)]
    kernel.K32EnumProcessModulesEx.argtypes = [wintypes.HANDLE, ctypes.POINTER(ctypes.c_void_p), wintypes.DWORD, ctypes.POINTER(wintypes.DWORD), wintypes.DWORD]
    kernel.K32GetModuleFileNameExW.argtypes = [wintypes.HANDLE, ctypes.c_void_p, wintypes.LPWSTR, wintypes.DWORD]
    kernel.ReadProcessMemory.argtypes = [wintypes.HANDLE, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t)]
    process = kernel.OpenProcess(0x0400 | 0x0010, False, pid)
    if not process:
        raise ctypes.WinError(ctypes.get_last_error())
    records = []
    try:
        buffer = ctypes.create_unicode_buffer(32768)
        length = wintypes.DWORD(len(buffer))
        require(kernel.QueryFullProcessImageNameW(process, 0, buffer, ctypes.byref(length)), "Cannot identify executable")
        require(Path(buffer.value).resolve() == (INSTALL / "ToramOnline.exe").resolve(), "Wrong target executable")
        modules = (ctypes.c_void_p * 2048)()
        needed = wintypes.DWORD()
        require(kernel.K32EnumProcessModulesEx(process, modules, ctypes.sizeof(modules), ctypes.byref(needed), 3), "Cannot enumerate modules")
        require(needed.value <= ctypes.sizeof(modules), "Module inventory overflow")
        matches = []
        for item in modules[:needed.value // 8]:
            if kernel.K32GetModuleFileNameExW(process, item, buffer, len(buffer)) and Path(buffer.value).resolve() == (INSTALL / "GameAssembly.dll").resolve():
                matches.append(item)
        require(len(matches) == 1, "Selected module is not unique")
        base = matches[0]

        def read(address, size, purpose):
            require(65536 <= address < 2**47 and 0 < size <= 65 and sum(row["bytes"] for row in records) + size <= 129, "Fixed read budget exceeded")
            data = ctypes.create_string_buffer(size)
            received = ctypes.c_size_t()
            if not kernel.ReadProcessMemory(process, address, data, size, ctypes.byref(received)) or received.value != size:
                raise ctypes.WinError(ctypes.get_last_error())
            records.append({"address": hex(address), "bytes": size, "purpose": purpose, "hex": data.raw.hex()})
            return data.raw

        def ptr(address, purpose):
            value = struct.unpack("<Q", read(address, 8, purpose))[0]
            require(65536 <= value < 2**47 and value % 8 == 0, "Initializer is unresolved or invalid")
            return value

        methods = json.loads(Path(__file__).with_name("method-map.json").read_text(encoding="utf-8"))["methods"]
        ctor = next(row for row in methods if row["class"] == "RegistletManager" and row["name"] == ".ctor")
        expected = bytes.fromhex(ctor["code_preview_hex"])
        require(read(base + int(ctor["rva"], 16), len(expected), "RegistletManager constructor code identity") == expected, "Live constructor differs from reviewed snapshot")
        field = ptr(base + REFERENCE_RVA, "NeedGemPowder initializer RuntimeFieldHandle")
        info = read(field, 32, "Initializer FieldInfo")
        name_ptr = struct.unpack_from("<Q", info)[0]
        value = initializer(read(name_ptr, 65, "Compiler field hash"), metadata)
        require(struct.unpack_from("<I", info, 28)[0] == int(value["token"], 16), "FieldInfo token differs from metadata")
        report = {"authority": "passive-fixed-registlet-initializer", "pid": pid, "moduleBase": hex(base),
                  "moduleSha256": MODULE_SHA, "metadataSha256": METADATA_SHA,
                  "capturedUtc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
                  "processAccess": "PROCESS_QUERY_INFORMATION | PROCESS_VM_READ", "bytesRead": sum(row["bytes"] for row in records),
                  "referenceRva": hex(REFERENCE_RVA), "initializer": value, "reads": records,
                  "limitations": ["Sequential fixed-reference read, not an atomic snapshot.", "No player data, target writes, injection, function execution, or gameplay."]}
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        print(json.dumps({"output": str(output), "values": value["values"], "bytesRead": report["bytesRead"]}))
    finally:
        kernel.CloseHandle(process)


def self_test():
    class Fixture:
        fields = [(0, 1, 0x04000001)]
        defaults = {0: (2, 0)}
        byval_names = {2: "__StaticArrayInitTypeSize=36"}
        tables = {"default_data": {"offset": 0}}
        data = struct.pack("<9i", *range(1, 10))
        def string(self, index):
            return hashlib.sha256(self.data).hexdigest().upper()
    fixture = Fixture()
    name = fixture.string(0).encode("ascii") + b"\0"
    assert initializer(name, fixture)["values"] == list(range(1, 10))
    for bad in [name[:-1], b"Z" * 64 + b"\0", b"0" * 64 + b"\0"]:
        try:
            initializer(bad, fixture)
        except ValueError:
            pass
        else:
            raise AssertionError("Invalid initializer accepted")
    print("PASS: initializer name, type/length, field identity, SHA-256, nine Int32 values")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pid", type=int)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        self_test()
    elif args.pid and args.output:
        capture(args.pid, args.output)
    else:
        parser.error("--pid and --output are required")
