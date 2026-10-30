"""Read the current Stoodie reward list through reviewed fixed references only.

Does not launch, inject, call game functions, write to the game, or read player data.
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

ROOT = Path(__file__).resolve().parents[4]
HERE = Path(__file__).resolve().parent
INSTALL = Path("C:/Asobimo/AsobimoGames/Toram")
MODULE_SHA = "c0f666aa071136bfae7ada61135ba01fc2907c3987945a86cce5909c6011fbff"
METADATA_SHA = "c5cb57c13fb2f4ba9258b8cf155ee866a8f67eee30f32d043e1fd854bba2eec9"
ROOT_CONTEXT_RVA = 0x3215480
MAX_ARRAY = 256
MAX_READ_BYTES = 65536


def require(value, message):
    if not value:
        raise ValueError(message)


def reward(raw):
    require(len(raw) == 8, "Expected Type/padding/Value fields")
    kind, value = raw[0], struct.unpack_from("<i", raw, 4)[0]
    result = {"rewardType": kind, "rawValue": value}
    if kind == 23:
        result["registletId"] = struct.unpack("<h", struct.pack("<H", value & 0xffff))[0]
    return result


def capture(pid, destination):
    require(os.name == "nt" and ctypes.sizeof(ctypes.c_void_p) == 8 and pid > 0, "64-bit Windows and positive PID required")
    require(not destination.exists(), "Capture destination must be new")
    require(hashlib.sha256((INSTALL / "GameAssembly.dll").read_bytes()).hexdigest() == MODULE_SHA, "Unreviewed module")
    require(hashlib.sha256((INSTALL / "ToramOnline_Data/il2cpp_data/Metadata/global-metadata.dat").read_bytes()).hexdigest() == METADATA_SHA, "Unreviewed metadata")
    kernel = ctypes.WinDLL("kernel32", use_last_error=True)
    kernel.OpenProcess.argtypes = [wintypes.DWORD, wintypes.BOOL, wintypes.DWORD]
    kernel.OpenProcess.restype = wintypes.HANDLE
    kernel.CloseHandle.argtypes = [wintypes.HANDLE]
    kernel.QueryFullProcessImageNameW.argtypes = [wintypes.HANDLE, wintypes.DWORD, wintypes.LPWSTR, ctypes.POINTER(wintypes.DWORD)]
    kernel.K32EnumProcessModulesEx.argtypes = [wintypes.HANDLE, ctypes.POINTER(ctypes.c_void_p), wintypes.DWORD, ctypes.POINTER(wintypes.DWORD), wintypes.DWORD]
    kernel.K32GetModuleFileNameExW.argtypes = [wintypes.HANDLE, ctypes.c_void_p, wintypes.LPWSTR, wintypes.DWORD]
    kernel.ReadProcessMemory.argtypes = [wintypes.HANDLE, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t)]
    handle = kernel.OpenProcess(0x0400 | 0x0010, False, pid)
    if not handle:
        raise ctypes.WinError(ctypes.get_last_error())
    reads = []
    try:
        buffer = ctypes.create_unicode_buffer(32768)
        length = wintypes.DWORD(len(buffer))
        require(kernel.QueryFullProcessImageNameW(handle, 0, buffer, ctypes.byref(length)), "Cannot identify process")
        require(Path(buffer.value).resolve() == (INSTALL / "ToramOnline.exe").resolve(), "Wrong process")
        modules = (ctypes.c_void_p * 2048)()
        needed = wintypes.DWORD()
        require(kernel.K32EnumProcessModulesEx(handle, modules, ctypes.sizeof(modules), ctypes.byref(needed), 3), "Cannot enumerate modules")
        require(needed.value <= ctypes.sizeof(modules), "Module inventory overflow")
        matches = [address for address in modules[:needed.value // 8]
                   if kernel.K32GetModuleFileNameExW(handle, address, buffer, len(buffer))
                   and Path(buffer.value).resolve() == (INSTALL / "GameAssembly.dll").resolve()]
        require(len(matches) == 1, "Module is not unique")
        base = matches[0]

        def read(address, size, purpose):
            require(65536 <= address < 2**47 and 0 < size <= 2048, "Read range outside admitted bounds")
            require(sum(r["bytes"] for r in reads) + size <= MAX_READ_BYTES, "Read budget exceeded")
            data = ctypes.create_string_buffer(size)
            received = ctypes.c_size_t()
            if not kernel.ReadProcessMemory(handle, address, data, size, ctypes.byref(received)) or received.value != size:
                raise ctypes.WinError(ctypes.get_last_error())
            reads.append({"address": hex(address), "bytes": size, "purpose": purpose, "hex": data.raw.hex()})
            return data.raw

        def ptr(address, purpose, nullable=False):
            value = struct.unpack("<Q", read(address, 8, purpose))[0]
            require((nullable and value == 0) or (65536 <= value < 2**47 and value % 8 == 0), "Unresolved/invalid pointer: " + purpose)
            return value

        checked_types = {}

        def object_type(address, expected):
            cls = ptr(address, expected + " object type")
            if cls in checked_types:
                require(checked_types[cls] == expected, "Object type changed")
                return
            name = struct.unpack("<Q", read(cls + 0x10, 8, expected + " class name pointer"))[0]
            require(read(name, len(expected) + 1, expected + " class name") == expected.encode("ascii") + b"\0", "Unexpected object type: " + expected)
            checked_types[cls] = expected

        mapping = json.loads((HERE / "method-map.json").read_text(encoding="utf-8"))
        # Validate the fixed root's response writer, not an arbitrary live address.
        witness = next(r for r in mapping["methods"] if r["method_definition_index"] == 43938)
        expected = bytes.fromhex(witness["code_preview_hex"])
        require(read(base + int(witness["rva"], 16), len(expected), "OnCheckTreasureHuntRoom code identity") == expected, "Runtime code differs")
        context = ptr(base + ROOT_CONTEXT_RVA, "RoomManager singleton method context")
        cls = ptr(context + 0x20, "Singleton context class")
        require(read(cls + 0x135, 1, "Generic context initialized flag")[0] & 1, "Generic context is not initialized")
        rgctx = ptr(cls + 0xc0, "Singleton generic context")
        singleton_cls = ptr(rgctx + 0x10, "Closed singleton class")
        require(read(singleton_cls + 0x135, 1, "Singleton class initialized flag")[0] & 1, "Singleton class not initialized")
        static_fields = ptr(singleton_cls + 0xb8, "Singleton static fields")
        manager = ptr(static_fields, "RoomManager instance")
        object_type(manager, "RoomManager")
        room = ptr(manager + 0x28, "Current TreasureHuntRoomData")
        object_type(room, "TreasureHuntRoomData")
        field_id = struct.unpack("<i", read(room + 0x38, 4, "Reward stage field ID"))[0]
        room_id = read(room + 0x3c, 1, "Reward stage room ID")[0]
        stages = json.loads((HERE / "stages.json").read_text(encoding="utf-8"))["stages"]
        matched = [r for r in stages if r["fieldId"] == field_id and r["roomId"] == room_id]
        require(len(matched) == 1, "Loaded room is not one reviewed Stoodie stage")
        rewards = ptr(room + 0xe0, "Server reward list")
        object_type(rewards, "TreasureHuntRewardData")
        pools = {}
        for index, rank in enumerate("DCBAS"):
            array = ptr(rewards + 0x20 + index * 8, rank + " rank array", nullable=True)
            items = []
            if array:
                count = struct.unpack("<Q", read(array + 0x18, 8, rank + " rank array length"))[0]
                require(count <= MAX_ARRAY, "Reward array exceeds reviewed bound")
                pointers = struct.unpack("<" + "Q" * count, read(array + 0x20, count * 8, rank + " rank pointers")) if count else ()
                for item in pointers:
                    require(65536 <= item < 2**47 and item % 8 == 0, "Invalid reward pointer")
                    object_type(item, "RewardData")
                    items.append(reward(read(item + 0x20, 8, rank + " reward Type/Value")))
            pools[rank] = items
        require(ptr(manager + 0x28, "Final room stability") == room, "Stage changed during capture")
        require(ptr(room + 0xe0, "Final reward stability") == rewards, "Reward list changed during capture")
        require(struct.unpack("<i", read(room + 0x38, 4, "Final field stability"))[0] == field_id, "Field changed during capture")
        report = {"schemaVersion": 1, "authority": "passive-fixed-current-stoodie-reward-list", "pid": pid,
                  "capturedUtc": datetime.datetime.now(datetime.timezone.utc).isoformat(), "moduleBase": hex(base),
                  "moduleSha256": MODULE_SHA, "metadataSha256": METADATA_SHA,
                  "stage": {k: matched[0][k] for k in ("level", "fieldId", "roomId", "names")}, "rankPools": pools,
                  "bytesRead": sum(r["bytes"] for r in reads), "readBudget": MAX_READ_BYTES, "reads": reads,
                  "limitations": ["Only the currently opened stage is observed.", "A displayed candidate list does not provide item probabilities.", "Sequential reads with root stability checks, not an atomic snapshot.", "No player data, writes, injection, game function calls, gameplay or purchases."]}
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        print(json.dumps({"output": str(destination), "level": report["stage"]["level"], "bytesRead": report["bytesRead"],
                          "registletIds": sorted({r["registletId"] for items in pools.values() for r in items if "registletId" in r})}))
    finally:
        kernel.CloseHandle(handle)


def self_test():
    assert reward(bytes([23, 0, 0, 0]) + struct.pack("<i", 12))["registletId"] == 12
    assert reward(bytes([23, 0, 0, 0]) + struct.pack("<i", 0x1000c))["registletId"] == 12
    assert "registletId" not in reward(bytes([24, 0, 0, 0]) + struct.pack("<i", 1))
    try:
        reward(b"\0" * 7)
    except ValueError:
        pass
    else:
        raise AssertionError("Truncated reward accepted")
    print("reward capture self-test PASS (layout, native low16 ID projection, type isolation, truncation)")


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
