"""Check retained evidence and small native-rule reconstructions, without game access."""
from collections import Counter
import hashlib
import json
import math
from pathlib import Path
import struct


HERE = Path(__file__).resolve().parent


def f32(value):
    return struct.unpack("<f", struct.pack("<f", value))[0]


def category_multiplier(properties, excluded=0):
    counts = Counter(row["category"] for row in properties
                     if row["type"] != 0 and row["type"] != excluded)
    result = f32(1)
    for count in counts.values():
        if count >= 2:
            result = f32(result + f32(f32(count * count) * f32(0.05)))
    return result


def max_magnitude(fields, level, skills, upper, cap_id):
    a, b, c = (max(0, value) for value in skills)
    factor = f32(f32(f32(f32(a * 3) + f32(10)) + f32(b * 3)) + f32(c * 3))
    factor = f32(factor / f32(100))
    base, scale = fields["BaseMax"], fields["OverRate"]
    if level < 210:
        return max(1, min(math.trunc(f32(factor * f32(base))), math.trunc(level / 10), base))
    count = max(0, math.trunc(level / 10) - 20)
    increment = math.trunc(f32(fields["Rate"] * f32(count))) * scale
    hard_limit = (fields["UpperMax" if upper else "LowerMax"] - base) * scale + base
    value = min(math.trunc(f32(f32(increment + base) * factor)), hard_limit)
    if cap_id in (12, 22, 24, 26, 28, 30, 32) and value > base:
        value = base + math.trunc((value - base) / scale)
    return max(1, value)


def usable_slots(skill366, skill367):
    return 3 + math.floor(f32(f32(skill366 + 2) * f32(0.3))) + math.floor(
        f32(f32(skill367 + 4) * f32(0.2)))


def success_skill_bonus(a, b, c):
    return max(0, a) + (10 + b if b > 0 else 0) + (20 + c if c > 0 else 0)


def main():
    index = json.loads((HERE / "index.json").read_text(encoding="utf-8"))
    for method in index["methods"]:
        assert method["decompileCompleted"]
        data = (HERE / method["pseudocodeFile"]).read_bytes()
        assert hashlib.sha256(data).hexdigest() == method["pseudocodeSha256"]
        assert b"Possible PIC construction" not in data
        assert b"Removing unreachable block" not in data
    assert hashlib.sha256((HERE / "TraceToramPenalty.java").read_bytes()).hexdigest() == index["scriptSha256"]
    for value in index["constants"].values():
        assert struct.unpack("<f", bytes.fromhex(value["hexLE"]))[0] == value["float32"]
    assert next(x for x in index["mathHelpers"] if x["name"] == "Floor")["wrapperJumpTarget"] == "0x7fff5f4a7774"

    rows = [{"type": i + 1, "value": v, "category": c}
            for i, (v, c) in enumerate(((1, 1), (-2, 1), (0, 1), (5, 2), (6, 2)))]
    assert category_multiplier(rows[:1]) == 1
    assert category_multiplier(rows[:2]) == f32(1.2)
    assert category_multiplier(rows[:3]) == f32(1.45)
    assert category_multiplier(rows) == f32(f32(1.45) + f32(0.2))
    assert math.trunc(f32(f32(20) * category_multiplier(rows))) == 33
    assert math.trunc(f32(f32(-20) * category_multiplier(rows))) == -33
    assert category_multiplier(rows[:3], excluded=3) == f32(1.2)
    assert category_multiplier(rows + [{"type": 0, "value": 7, "category": 1}]) == category_multiplier(rows)
    assert math.trunc(f32(f32(1 + 1) * category_multiplier(rows[:2]))) == 2
    assert sum(math.trunc(f32(f32(1) * category_multiplier(rows[:2]))) for _ in range(2)) == 2
    assert math.trunc(f32(f32(2 + 2) * category_multiplier(rows[:2]))) == 4
    assert math.trunc(f32(f32(3 + 3) * category_multiplier(rows[:2]))) == 7
    assert sum(math.trunc(f32(f32(3) * category_multiplier(rows[:2]))) for _ in range(2)) == 6
    assert [usable_slots(n, 0) - 3 for n in range(1, 11)] == [0, 1, 1, 1, 2, 2, 2, 3, 3, 3]
    assert [usable_slots(0, n) - 3 for n in range(1, 11)] == [1, 1, 1, 1, 1, 2, 2, 2, 2, 2]
    assert usable_slots(0, 0) == 3 and usable_slots(10, 10) == 8
    assert success_skill_bonus(10, 10, 10) == 60
    assert success_skill_bonus(1, 1, 1) == 33
    assert success_skill_bonus(-1, -1, -1) == 0

    catalog_path = HERE.parent / "catalog.json"
    catalog = json.loads(catalog_path.read_text(encoding="utf-8"))
    ordinary = {row["id"]: row for row in catalog["options"] if row["dictionary"] == "EnhanceCost"}
    assert len(ordinary) == 67
    assert max_magnitude(ordinary[1]["fields"], 209, (10, 10, 10), True, 1) == 20
    assert max_magnitude(ordinary[1]["fields"], 210, (10, 10, 10), True, 1) == 21
    assert max_magnitude(ordinary[1]["fields"], 300, (10, 10, 10), True, 1) == 30
    assert max_magnitude(ordinary[1]["fields"], 300, (0, 0, 0), True, 1) == 3
    assert max_magnitude(ordinary[1]["fields"], 1, (0, 0, 0), True, 1) == 1
    examples = []
    for cap_id in (1, 6, 12, 17, 18, 22, 24, 49, 50, 110):
        row = ordinary[cap_id]
        up = max_magnitude(row["fields"], 300, (10, 10, 10), True, cap_id)
        down = max_magnitude(row["fields"], 300, (10, 10, 10), False, cap_id)
        examples.append({"bonusId": cap_id, "projectStatId": row["projectStatId"],
                         "upperSelectorMagnitude": up, "lowerSelectorMagnitude": down})
    (HERE / "cap-examples.json").write_text(json.dumps({
        "sourceCatalogSha256": hashlib.sha256(catalog_path.read_bytes()).hexdigest(),
        "characterLevel": 300, "skillLevelsByNativeId": {"365": 10, "366": 10, "367": 10},
        "scope": "Normalized getEnhanceMax selector limits; not raw grant operands or final display values. UI conversion and grant execution are separate.",
        "examples": examples}, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"PASS: {len(index['methods'])} native hashes, constants, counting/sign/zero/exclusion, aggregate truncation, slots, level209/210/300, skill bonus; cap-examples.json written")


if __name__ == "__main__":
    main()
