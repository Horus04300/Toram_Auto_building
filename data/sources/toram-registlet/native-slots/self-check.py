"""Check retained slot evidence without game execution or process access."""
import hashlib
import importlib.util
import json
import csv
import struct
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
rules = json.loads((HERE / "slot-rules.json").read_text(encoding="utf-8"))
mapping = json.loads((HERE / "method-map.json").read_text(encoding="utf-8"))
index = json.loads((HERE / "pseudocode/index.json").read_text(encoding="utf-8"))
assert len(index) == len(mapping["methods"]) == 15
assert all(row["decompileCompleted"] for row in index)
for row in index:
    path = HERE / "pseudocode" / row["pseudocodeFile"]
    assert hashlib.sha256(path.read_bytes()).hexdigest() == row["pseudocodeSha256"], path
for source in rules["sources"].values():
    path = ROOT / source["path"]
    assert hashlib.sha256(path.read_bytes()).hexdigest() == source["sha256"], path
assert rules["slotLimit"] == 10 and rules["gemPowderLimit"] == 999999999
assert rules["costArrayLength"] == 9 and rules["initialSlotCount"] is None
assert rules["costIndexExpression"] == "NeedGemPowder[currentSlotCount - 1]"
assert rules["costBindingStatus"] == "verified-runtime-field-name-token-and-metadata-content-hash"
captured = json.loads((HERE / "initializer-capture.json").read_text(encoding="utf-8"))
assert captured["bytesRead"] == sum(row["bytes"] for row in captured["reads"]) == 129
assert [row["bytes"] for row in captured["reads"]] == [24, 8, 32, 65]
initializer = captured["initializer"]
raw = bytes.fromhex(initializer["hex"])
assert initializer == rules["initializer"]
assert bytes.fromhex(captured["reads"][3]["hex"]) == initializer["fieldName"].encode("ascii") + b"\0"
assert struct.unpack_from("<I", bytes.fromhex(captured["reads"][2]["hex"]), 28)[0] == int(initializer["token"], 16)
metadata_bytes = (ROOT / rules["sources"]["metadata"]["path"]).read_bytes()
assert metadata_bytes[initializer["metadataOffset"]:initializer["metadataOffset"] + 36] == raw
assert hashlib.sha256(raw).hexdigest().upper() == initializer["fieldName"]
assert list(struct.unpack("<9i", raw)) == rules["costsByCurrentSlot"] == initializer["values"]
assert rules["costsByCurrentSlot"] == [100, 400, 2000, 7000, 30000, 200000, 500000, 2000000, 7000000]
assert initializer["token"] == "0x400d409" and initializer["fieldIndex"] == 54280
assert rules["totalPowderFromOneToTenSlots"] == sum(rules["costsByCurrentSlot"]) == 9739500
with (HERE / "slot-expansion-costs.csv").open(encoding="utf-8", newline="") as stream:
    csv_steps = [{key: int(value) for key, value in row.items()} for row in csv.DictReader(stream)]
assert csv_steps == rules["expansionSteps"]
total = 0
for current, step in enumerate(csv_steps, 1):
    total += rules["costsByCurrentSlot"][current - 1]
    assert step == {"fromSlots": current, "toSlots": current + 1,
                    "requiredPowder": rules["costsByCurrentSlot"][current - 1],
                    "cumulativePowderFromOneSlot": total}
assert "= 999999999" in (HERE / "pseudocode/20115.c").read_text()
assert "= 10;" in (HERE / "pseudocode/20115.c").read_text()
for method in [65874, 65881]:
    code = (HERE / "pseudocode" / f"{method}.c").read_text()
    assert "(ulonglong)bVar2 - 1" in code and "+ 0x20 + lVar1 * 4" in code
spec = importlib.util.spec_from_file_location("capture", HERE / "capture-constants.py")
capture = importlib.util.module_from_spec(spec)
spec.loader.exec_module(capture)
capture.self_test()
print("PASS: 15 function hashes, four inputs, slot/powder limits, 129-byte initializer binding, nine exact costs, CSV/JSON/cumulative parity, unresolved initial count")
