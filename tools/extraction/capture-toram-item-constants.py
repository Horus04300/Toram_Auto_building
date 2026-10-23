"""Read only the reviewed item's formatter constants from a running Toram process.

Follows fixed native references to BonusManager.limitList, its compiler field name,
formatter literals and public asset URL components. No injection, writes or player data.
"""

import argparse
import ctypes
from ctypes import wintypes
import datetime
import hashlib
import json
import os
from pathlib import Path
import re
import struct


INSTALL = Path("C:/Asobimo/AsobimoGames/Toram")
MODULE_SHA = "a3faf7156734768a3ff7349d4b94de029b68b823d974bf52f92bbc77f93f46dd"
OLD_BASE = 0x7fff5f250000
STRINGS = {"negativeReplacement": 0x7fff6241a898, "empty": 0x7fff623f7f60,
           "positiveColor": 0x7fff624263c8, "negativeColor": 0x7fff62425428,
           "zeroColor": 0x7fff6241c668, "colorFormat": 0x7fff62401c80,
           "skillDefaultTag": 0x7fff624727d0, "skillBracketPrefix": 0x7fff62421fc8,
           "skillUnknownName": 0x7fff624408b0, "platformCode": 0x7fff6243aa20,
           "versionFilePrefix1": 0x7fff624405a0, "versionFilePrefix2": 0x7fff6245b758,
           "commonAssetBundleName": 0x7fff62410400, "localizePrefix1": 0x7fff62446cb0,
           "localizePrefix2": 0x7fff624255f0, "localizePrefix3": 0x7fff624252d0,
           "languageFileSuffix": 0x7fff6242d448, "assetBundleUrlFormat": 0x7fff62401a10,
           "downloadPathDefault": 0x7fff62478020, "downloadPathRelease": 0x7fff62477f50,
           "downloadPathAlternative": 0x7fff62477e80, "downloadSuffixDefault": 0x7fff624428e8,
           "applicationPath1": 0x7fff62442b38, "applicationPath2": 0x7fff62442cc0,
           "applicationPath3": 0x7fff62442f08, "applicationPath4": 0x7fff62443090,
           "applicationPath5": 0x7fff62443218, "applicationPathDefault": 0x7fff624429b0}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def int_array(header, payload):
    require(len(header) == 32, "Invalid array header")
    count = struct.unpack_from("<Q", header, 24)[0]
    require(count == 6 and len(payload) == count * 4, "Unexpected limitList length")
    values = list(struct.unpack("<6i", payload))
    require(all(0 < values[i] <= values[i + 1] <= 32767 for i in range(0, 6, 2)), "Invalid ID intervals")
    return values


def string_value(header, payload):
    require(len(header) == 20, "Invalid string header")
    size = struct.unpack_from("<i", header, 16)[0]
    require(0 <= size <= 128 and len(payload) == size * 2, "Invalid string size")
    return payload.decode("utf-16-le")


def self_test():
    array = bytes(24) + struct.pack("<Q", 6)
    assert int_array(array, struct.pack("<6i", 1, 2, 10, 20, 30, 30)) == [1, 2, 10, 20, 30, 30]
    text = "돌진+".encode("utf-16-le")
    assert string_value(bytes(16) + struct.pack("<i", 3), text) == "돌진+"
    for call in [lambda: int_array(bytes(32), b""), lambda: string_value(bytes(16) + struct.pack("<i", -1), b"")]:
        try:
            call()
        except ValueError:
            pass
        else:
            raise AssertionError("Malformed data accepted")
    print("PASS: fixed array intervals, UTF-16 strings and invalid lengths")


def capture(pid, output):
    require(os.name == "nt" and ctypes.sizeof(ctypes.c_void_p) == 8 and pid > 0, "64-bit Windows and positive PID required")
    require(not output.exists(), "Output must be new")
    require(hashlib.sha256((INSTALL / "GameAssembly.dll").read_bytes()).hexdigest() == MODULE_SHA, "Unreviewed installed module")
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
    records, total = [], 0
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
        for module in modules[:needed.value // 8]:
            if kernel.K32GetModuleFileNameExW(process, module, buffer, len(buffer)) and Path(buffer.value).resolve() == (INSTALL / "GameAssembly.dll").resolve():
                matches.append(module)
        require(len(matches) == 1, "Selected module is not unique")
        base = matches[0]

        def read(address, size, purpose):
            nonlocal total
            require(65536 <= address < 2**47 and 0 <= size <= 1024 and total + size <= 16384, "Read exceeds fixed budget")
            if not size:
                return b""
            value = ctypes.create_string_buffer(size)
            received = ctypes.c_size_t()
            if not kernel.ReadProcessMemory(process, address, value, size, ctypes.byref(received)) or received.value != size:
                raise ctypes.WinError(ctypes.get_last_error())
            total += size
            records.append({"address": hex(address), "bytes": size, "purpose": purpose, "hex": value.raw.hex()})
            return value.raw

        def ptr(address, purpose):
            value = struct.unpack("<Q", read(address, 8, purpose))[0]
            require(65536 <= value < 2**47 and value % 8 == 0, "Uninitialized or invalid pointer")
            return value

        def anchor(old_address):
            return base + old_address - OLD_BASE

        expected = bytes.fromhex("40534883ec20803d41fa5e02008bd9752b488d0d30a44502")
        require(read(base + 0xda5e00, len(expected), "GetBonusTime code identity") == expected, "Live code differs from reviewed snapshot")
        klass = ptr(anchor(0x7fff62450248), "BonusManager TypeInfo reference")
        static = ptr(klass + 0xb8, "BonusManager static_fields")
        array = ptr(static + 0x10, "BonusManager.limitList")
        header = read(array, 32, "limitList array header")
        require(struct.unpack_from("<Q", header, 24)[0] == 6, "Unexpected limitList layout")
        values = int_array(header, read(array + 32, 24, "limitList six int32 values"))
        field = ptr(anchor(0x7fff6244c0e0), "limitList initializer RuntimeFieldHandle")
        field_info = read(field, 32, "Initializer FieldInfo")
        name_ptr = struct.unpack_from("<Q", field_info)[0]
        name = read(name_ptr, 65, "Compiler SHA256 field name").split(b"\0")[0].decode("ascii")
        require(re.fullmatch(r"[0-9A-F]{64}", name) is not None, "Unexpected initializer field name")
        strings = {}
        for label, old in STRINGS.items():
            obj = ptr(anchor(old), label + " literal reference")
            header = read(obj, 20, label + " string header")
            length = struct.unpack_from("<i", header, 16)[0]
            require(0 <= length <= 128, "Unexpected literal length")
            strings[label] = string_value(header, read(obj + 20, length * 2, label + " UTF-16"))
        report = {"authority": "passive-targeted-item-formatter-constants", "pid": pid, "moduleBase": hex(base),
                  "moduleSha256": MODULE_SHA, "capturedUtc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
                  "processAccess": "PROCESS_QUERY_INFORMATION | PROCESS_VM_READ", "bytesRead": total,
                  "limitList": values, "initializerFieldName": name, "initializerToken": hex(struct.unpack_from("<I", field_info, 28)[0]),
                  "strings": strings, "reads": records,
                  "limitations": ["Sequential read of the fixed references only; not an atomic snapshot or general heap dump.",
                                  "No player inventory, account information, function execution or target modification."]}
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        print(json.dumps({"output": str(output), "limitList": values, "bytesRead": total}, ensure_ascii=False))
    finally:
        kernel.CloseHandle(process)


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
