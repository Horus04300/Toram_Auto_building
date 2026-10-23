"""Read an already running Toram GameAssembly module with Windows VM_READ only.

Never launches the game, injects code, changes protection, or reads other modules/heaps.
The captured module is a sequential, non-atomic snapshot, not original shipped bytes.
"""
import argparse
import ctypes
from ctypes import wintypes
import datetime
import hashlib
import json
import os
from pathlib import Path
import struct

INSTALL = Path("C:/Asobimo/AsobimoGames/Toram")


def rebuild_pe(memory, base):
    result = bytearray(memory)
    if len(memory) < 512 or memory[:2] != b"MZ":
        raise ValueError("Missing mapped PE header")
    nt = struct.unpack_from("<I", memory, 60)[0]
    if nt + 24 > len(memory) or memory[nt:nt + 4] != b"PE\0\0":
        raise ValueError("Invalid PE signature")
    machine, sections, _, _, _, optional_size, _ = struct.unpack_from("<HHIIIHH", memory, nt + 4)
    optional = nt + 24
    if machine != 0x8664 or struct.unpack_from("<H", memory, optional)[0] != 0x20B:
        raise ValueError("Only x64 PE32+ supported")
    alignment = struct.unpack_from("<I", memory, optional + 36)[0]
    if not alignment or alignment & (alignment - 1) or len(memory) != struct.unpack_from("<I", memory, optional + 56)[0]:
        raise ValueError("Invalid alignment or image size")
    struct.pack_into("<Q", result, optional + 24, base)
    layout = []
    for index in range(sections):
        offset = optional + optional_size + index * 40
        if offset + 40 > len(memory):
            raise ValueError("Truncated section table")
        virtual_size, rva, raw_size, _ = struct.unpack_from("<4I", memory, offset + 8)
        size = (max(virtual_size, raw_size) + alignment - 1) & -alignment
        if rva + size > len(memory):
            raise ValueError("Section extends beyond captured image")
        struct.pack_into("<2I", result, offset + 16, size, rva)
        layout.append({"name": memory[offset:offset + 8].rstrip(b"\0").decode("ascii", "replace"),
                       "rva": rva, "rawOffset": rva, "rawSize": size})
    # The security directory is an original-file offset, not a mapped RVA.
    struct.pack_into("<2I", result, optional + 112 + 4 * 8, 0, 0)
    struct.pack_into("<I", result, optional + 64, 0)
    return bytes(result), layout


def self_test():
    memory = bytearray(8192)
    memory[:2] = b"MZ"
    struct.pack_into("<I", memory, 60, 128)
    memory[128:132] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", memory, 132, 0x8664, 1, 0, 0, 0, 240, 0)
    struct.pack_into("<H", memory, 152, 0x20B)
    struct.pack_into("<I", memory, 152 + 36, 512)
    struct.pack_into("<I", memory, 152 + 56, len(memory))
    memory[392:400] = b".data\0\0\0"
    struct.pack_into("<4I", memory, 400, 64, 4096, 0, 0)
    memory[4096:4100] = b"code"
    original = bytes(memory)
    rebuilt, layout = rebuild_pe(memory, 0x7FF000000000)
    assert bytes(memory) == original and rebuilt[4096:4100] == b"code"
    assert layout[0]["rawOffset"] == 4096 and layout[0]["rawSize"] == 512
    assert struct.unpack_from("<Q", rebuilt, 176)[0] == 0x7FF000000000
    for invalid in (b"", original[:-1], b"NO" + original[2:]):
        try:
            rebuild_pe(invalid, 0)
        except ValueError:
            pass
        else:
            raise AssertionError("Invalid mapped image accepted")
    print("PASS: mapped-image reconstruction, source preservation, invalid-header/size checks")


def capture(pid, output, expected_sha256):
    if os.name != "nt" or ctypes.sizeof(ctypes.c_void_p) != 8 or pid <= 0:
        raise ValueError("A positive PID and 64-bit Windows Python are required")
    if output.exists():
        raise ValueError("Output directory must be new")
    source = INSTALL / "GameAssembly.dll"
    source_hash = hashlib.sha256(source.read_bytes()).hexdigest()
    if source_hash != expected_sha256:
        raise ValueError("Installed module changed; metadata/version must be reviewed before capture")
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
    started = datetime.datetime.now(datetime.timezone.utc).isoformat()
    try:
        buffer = ctypes.create_unicode_buffer(32768)
        length = wintypes.DWORD(len(buffer))
        if not kernel.QueryFullProcessImageNameW(process, 0, buffer, ctypes.byref(length)):
            raise ctypes.WinError(ctypes.get_last_error())
        if Path(buffer.value).resolve() != (INSTALL / "ToramOnline.exe").resolve():
            raise ValueError("PID does not identify the explicitly selected Toram executable")
        modules = (ctypes.c_void_p * 2048)()
        needed = wintypes.DWORD()
        if not kernel.K32EnumProcessModulesEx(process, modules, ctypes.sizeof(modules), ctypes.byref(needed), 3):
            raise ctypes.WinError(ctypes.get_last_error())
        if needed.value > ctypes.sizeof(modules):
            raise ValueError("Module inventory exceeded fixed limit")
        matches = []
        for module in modules[:needed.value // ctypes.sizeof(ctypes.c_void_p)]:
            if kernel.K32GetModuleFileNameExW(process, module, buffer, len(buffer)):
                if Path(buffer.value).resolve() == source.resolve():
                    matches.append(module)
        if len(matches) != 1:
            raise ValueError(f"Expected one selected GameAssembly module, got {len(matches)}")
        base = matches[0]
        def read(offset, size):
            value = ctypes.create_string_buffer(size)
            received = ctypes.c_size_t()
            if not kernel.ReadProcessMemory(process, base + offset, value, size, ctypes.byref(received)) or received.value != size:
                raise ctypes.WinError(ctypes.get_last_error())
            return value.raw
        header = read(0, 4096)
        nt = struct.unpack_from("<I", header, 60)[0]
        size = struct.unpack_from("<I", header, nt + 24 + 56)[0]
        if not 4096 <= size <= 128 * 1024 * 1024:
            raise ValueError("Mapped image size outside selected module budget")
        memory, unreadable = bytearray(size), []
        for offset in range(0, size, 65536):
            count = min(65536, size - offset)
            try:
                memory[offset:offset + count] = read(offset, count)
            except OSError:
                for page in range(offset, offset + count, 4096):
                    page_size = min(4096, size - page)
                    try:
                        memory[page:page + page_size] = read(page, page_size)
                    except OSError as error:
                        unreadable.append({"rva": page, "bytes": page_size, "winerror": error.winerror})
        rebuilt, layout = rebuild_pe(memory, base)
        output.mkdir(parents=True)
        (output / "GameAssembly.mapped.bin").write_bytes(memory)
        (output / "GameAssembly.snapshot.dll").write_bytes(rebuilt)
        report = {"authority": "passive-runtime-module-snapshot", "pid": pid,
                  "executable": str(INSTALL / "ToramOnline.exe"), "module": str(source),
                  "sourceSha256": source_hash, "base": hex(base), "size": size,
                  "startedUtc": started, "finishedUtc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
                  "processAccess": "PROCESS_QUERY_INFORMATION | PROCESS_VM_READ", "unreadablePages": unreadable,
                  "completeReadableImage": not unreadable, "mappedSha256": hashlib.sha256(memory).hexdigest(),
                  "rebuiltSha256": hashlib.sha256(rebuilt).hexdigest(), "sections": layout,
                  "limitations": ["Sequential non-atomic capture of only the selected module; no other modules or heaps read.",
                                  "Uncaptured pages are zeros in derived files and remain explicitly unknown.",
                                  "Rebuilt PE modifies raw section offsets/sizes, image base, security directory and checksum for offline analysis; it is not an executable replacement."]}
        (output / "capture.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        print(json.dumps({"output": str(output.resolve()), "pid": pid, "base": hex(base), "bytes": size,
                          "unreadablePages": len(unreadable), "sha256": report["rebuiltSha256"]}))
    finally:
        kernel.CloseHandle(process)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pid", type=int)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--module-sha256", help="Explicit SHA256 of the reviewed installed module version")
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        self_test()
    elif args.pid is None or args.output is None or not args.module_sha256:
        parser.error("--pid, --output and --module-sha256 are required")
    else:
        capture(args.pid, args.output, args.module_sha256)
