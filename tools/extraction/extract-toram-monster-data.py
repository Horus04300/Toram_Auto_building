"""Pure readers for retained MapInfo.mobDb and Enemy localization TextAssets.

Field order follows the reviewed native readers, not a guessed fixed row size.
No game process access, downloading, difficulty scaling or combat simulation.
"""

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct


_spec = importlib.util.spec_from_file_location(
    "toram_asset_reader", Path(__file__).with_name("extract-toram-item-assets.py"))
_assets = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_assets)


class Reader(_assets.Reader):
    def value(self, fmt):
        return struct.unpack("<" + fmt, self.take(struct.calcsize("<" + fmt)))[0]

    def count(self, minimum_size=1):
        count = self.i32()
        if count < 0 or count > (len(self.data) - self.pos) // minimum_size:
            raise ValueError(f"Impossible count {count} at {self.pos - 4}")
        return count


def fields(reader, layout):
    return {name: reader.value(fmt) for name, fmt in layout}


STATUS_PREFIX = [
    ("id", "i"), ("uuid", "i"), ("roomId", "B"),
]
STATUS_FIELDS = [
    ("level", "h"), ("exp", "i"), ("maxHp", "i"),
    ("expDefNormal", "B"), ("expDefSkill", "B"), ("expDefMagic", "B"),
    ("necessaryHit", "h"), ("def", "h"), ("mdef", "h"),
    ("cutAttack", "h"), ("cutMagicAttack", "h"), ("guard", "h"), ("avoid", "h"),
    ("flagRaw", "I"), ("elementRaw", "B"), ("model", "i"), ("sizeRaw", "B"),
    ("scaleRaw", "h"), ("color1", "i"), ("color2", "i"), ("color3", "i"),
    ("moveSpeedRaw", "h"), ("personaRaw", "B"), ("personaValue", "h"),
]
ACTION_FIELDS = [
    ("attack", "i"), ("stable", "B"), ("range", "B"), ("delayRaw", "B"),
    ("elementRaw", "B"), ("critical", "B"), ("criticalDamage", "h"),
    ("flee", "h"), ("effect", "h"), ("effectGrant", "B"), ("effectTime", "h"),
    ("typeRaw", "h"), ("motion", "B"), ("startSoundTimingRaw", "B"),
    ("startSoundEffect", "h"), ("attackSoundTimingRaw", "B"),
    ("attackSoundEffect", "h"), ("hitEffectId", "h"), ("hitEffectMotionNo", "B"),
]
MODE_FIELDS = [
    ("modeId", "B"), ("triggerRaw", "h"), ("value", "i"), ("targetMonsterId", "i"),
    ("auraModel", "i"), ("auraMotion", "B"), ("auraColor", "i"),
    ("ignitionModel", "i"), ("ignitionMotion", "B"), ("ignitionColor", "i"),
    ("flagRaw", "I"), ("combo", "h"),
]


def action_pattern(reader, version):
    start = reader.pos
    row = {"commandId": reader.value("h" if version < -2 else "B")}
    row.update(fields(reader, ACTION_FIELDS))
    row["combo"] = reader.value("h" if version < -2 else "B")
    row["values"] = [reader.value("h") for _ in range(10)]
    row["probability"] = reader.value("h")
    if version < -3:
        row["commonFlagRaw"] = reader.value("h")
    if version <= -5:
        row["values"].extend(reader.value("h") for _ in range(10))
    row["rawRecordHex"] = reader.data[start:reader.pos].hex()
    return row


def status_master(reader, version):
    start = reader.pos
    row = fields(reader, STATUS_PREFIX)
    row["nameRaw"] = reader.string()
    row.update(fields(reader, STATUS_FIELDS))
    row["actions"] = [action_pattern(reader, version) for _ in range(reader.count())]
    row["parts"] = [fields(reader, [("partId", "B"), ("value", "i")])
                    for _ in range(reader.count(5))]
    row["modes"] = [fields(reader, MODE_FIELDS) for _ in range(reader.count(35))]
    row["properties"] = []
    if version < -1:
        for _ in range(reader.count(23)):
            row["properties"].append({"uid": reader.value("B"),
                                      "typeRaw": reader.value("h"),
                                      "values": [reader.i32() for _ in range(5)]})
    row["decodedOffset"] = start
    row["rawRecordHex"] = reader.data[start:reader.pos].hex()
    return row


def parse_mob_db(data, expected_field_id=None):
    reader = Reader(data)
    version = reader.i32()
    field_id = reader.i32() if version < 1 else version
    if expected_field_id is not None and field_id != expected_field_id:
        raise ValueError(f"Mob DB field ID {field_id} differs from {expected_field_id}")
    rows = [status_master(reader, version) for _ in range(reader.count())]
    ids = [row["id"] for row in rows]
    if len(set(ids)) != len(ids):
        raise ValueError("Duplicate per-field MobStatusMaster ID")
    drops = []
    if version < 0:
        for _ in range(reader.count(8)):
            key = reader.i32()
            pairs = [fields(reader, [("value", "i"), ("unusedRaw", "i")])
                     for _ in range(reader.count(8))]
            drops.append({"key": key, "pairs": pairs})
    if reader.pos != len(data):
        raise ValueError(f"Trailing Mob DB bytes: {len(data) - reader.pos}")
    return {"version": version, "fieldId": field_id, "monsters": rows, "drops": drops,
            "sha256": hashlib.sha256(data).hexdigest(), "bytes": len(data)}


def parse_enemy_text(data):
    reader = Reader(data)
    rows = {}
    for _ in range(reader.count(5)):
        ident = reader.i32()
        if ident in rows:
            raise ValueError(f"Duplicate Enemy text ID {ident}")
        rows[ident] = reader.string()
    if reader.pos != len(data):
        raise ValueError("Trailing Enemy text bytes")
    return rows


def parse_high_raid_bosses(data):
    reader = Reader(data)
    version = reader.value("B")
    if version != 0:
        raise ValueError("Unreviewed HighRaidBossMaster version")
    rows = []
    for _ in range(reader.count(21)):
        row = fields(reader, [("no", "B"), ("fieldId", "i"), ("roomId", "B"), ("raidFlag", "B"),
                              ("monsterId", "i"), ("monsterUuid", "i"), ("baseLevel", "h"), ("minLevel", "h")])
        count = reader.value("h")
        if count < 0 or count > (len(data) - reader.pos) // 15:
            raise ValueError("Impossible HighRaid reward count")
        row["rewards"] = [fields(reader, [("rewardNo", "B"), ("cost", "i"), ("typeRaw", "B"),
                                         ("value", "i"), ("num", "i"), ("flagRaw", "B")]) for _ in range(count)]
        rows.append(row)
    if reader.pos != len(data) or len({row["no"] for row in rows}) != len(rows):
        raise ValueError("Trailing/duplicate HighRaidBossMaster data")
    return rows


def boss_menu_entries(data):
    """Follow event roots and reviewed v16 quest/check edges; stop at unknown instructions."""
    reader = Reader(data)
    version, count = reader.value("B"), reader.value("h")
    if count < 0 or count > (len(data) - reader.pos) // 4:
        raise ValueError("Impossible field script event count")
    offsets = [reader.i32() for _ in range(count)]
    header_end = reader.pos
    menus, invalid = [], []
    for event_id, offset in enumerate(offsets):
        if offset == -1:
            continue
        if not header_end <= offset <= len(data) - 2:
            invalid.append({"eventId": event_id, "offset": offset})
            continue
        pending, visited = [(offset, [])], set()
        while pending:
            position, path = pending.pop()
            if position == -1 or position in visited:
                continue
            if not header_end <= position <= len(data) - 2:
                raise ValueError("Invalid reviewed field script branch target")
            visited.add(position)
            reader.pos = position
            opcode = reader.value("h")
            if version == 16 and opcode in (20, 38):
                first, flags = reader.value("B"), reader.value("B")
                # ReadInt(work-value) has a different operand format; do not guess its size.
                if (opcode == 38 and first & 1) or (opcode == 20 and
                        (flags & 128 or flags & 15 not in (0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14))):
                    continue
                reader.i32()
                targets = [reader.i32(), reader.i32()] if opcode == 20 else [reader.pos]
                edge = {"offset": position, "opcode": opcode, "targets": targets}
                pending.extend((target, path + [edge]) for target in reversed(targets))
                continue
            if opcode != 130:
                continue
            command_version = version
            if version >= 15:
                command_version = reader.value("B")
                prefix_byte_raw = reader.value("B")
                field_id = reader.i32()
            else:
                prefix_byte_raw = None
                field_id = reader.value("h") if version < 14 else reader.i32()
            room_id = reader.value("B")
            menu = {"eventId": event_id, "offset": position, "opcode": opcode, "scriptVersion": version,
                    "commandVersion": command_version, "prefixByteRaw": prefix_byte_raw,
                    "fieldId": field_id, "roomId": room_id}
            if path:
                menu.update({"entryOffset": offset, "controlFlow": path})
            menus.append(menu)
    return {"menus": menus, "invalidEntryOffsets": invalid}


def parse_tables(tables, locales):
    """Join by native UUID; preserve each field/local-ID variant and failed table."""
    names = {locale: parse_enemy_text(data) for locale, data in locales.items()}
    monsters, table_headers, rejected = {}, {}, []
    for source_asset, data in sorted(tables.items()):
        try:
            table = parse_mob_db(data)
        except (ValueError, struct.error) as error:
            rejected.append({"sourceAsset": source_asset, "sha256": hashlib.sha256(data).hexdigest(),
                             "bytes": len(data), "reason": str(error)})
            continue
        table_headers[source_asset] = {key: value for key, value in table.items() if key != "monsters"}
        for row in table["monsters"]:
            key = f"{table['fieldId']}:{row['id']}"
            if key in monsters:
                if monsters[key]["raw"] != row:
                    raise ValueError(f"Conflicting Mob DB variant {key}")
                monsters[key]["sourceAssets"].append(source_asset)
                continue
            monsters[key] = {"key": key, "gameMonsterId": row["uuid"],
                             "fieldId": table["fieldId"], "masterId": row["id"],
                             "names": {locale: texts.get(row["uuid"]) for locale, texts in names.items()},
                             "raw": row, "sourceAssets": [source_asset]}
    linked_ids = {row["gameMonsterId"] for row in monsters.values()}
    return {"schemaVersion": 1, "monsters": list(monsters.values()), "tables": table_headers,
            "rejectedTables": rejected,
            "localization": {locale: {"count": len(texts),
                                      "orphanTextIds": sorted(set(texts) - linked_ids)}
                             for locale, texts in names.items()}}


def self_test():
    raid_row = struct.pack("<BiBBiihh", 7, 101100, 0, 0, 1, 1001, 290, 290)
    raid_row += struct.pack("<hBiBiiB", 1, 2, 100, 1, 2000, 3, 0)
    raid = bytes([0]) + struct.pack("<i", 1) + raid_row
    assert parse_high_raid_bosses(raid)[0]["monsterUuid"] == 1001
    assert parse_high_raid_bosses(raid)[0]["rewards"][0]["value"] == 2000
    for invalid in [raid[:-1], raid + b"x", bytes([1]) + raid[1:], bytes([0]) + struct.pack("<i", 2) + raid_row * 2]:
        try:
            parse_high_raid_bosses(invalid)
        except ValueError:
            pass
        else:
            raise AssertionError("Invalid HighRaid master accepted")
    for version in [13, 14, 16]:
        header = struct.pack("<Bhi", version, 1, 7)
        target = struct.pack("<h", 42) if version < 14 else struct.pack("<i", 42)
        if version >= 15:
            target = bytes([14, 0]) + target
        result = boss_menu_entries(header + struct.pack("<h", 130) + target + bytes([2]))
        assert result["menus"][0]["fieldId"] == 42 and result["menus"][0]["roomId"] == 2
        assert boss_menu_entries(header + struct.pack("<h", 6) + struct.pack("<h", 130) + target + bytes([2]))["menus"] == []
    assert boss_menu_entries(struct.pack("<Bhi", 16, 1, 7))["invalidEntryOffsets"] == [{"eventId": 0, "offset": 7}]
    try:
        boss_menu_entries(struct.pack("<Bh", 16, -1))
    except ValueError:
        pass
    else:
        raise AssertionError("Invalid script event count accepted")
    def make(version):
        prefix = struct.pack("<i", version)
        if version < 1:
            prefix += struct.pack("<i", 42)
        row = struct.pack("<iiBB", 1001, 501, 2, 1) + b"x"
        values = {name: 0 for name, _ in STATUS_FIELDS}
        values.update({"level": 285, "maxHp": 123456789, "def": 3850, "mdef": 4200,
                       "cutAttack": -10, "flagRaw": 4})
        row += b"".join(struct.pack("<" + fmt, values[name]) for name, fmt in STATUS_FIELDS)
        row += struct.pack("<iii", 0, 0, 0)
        if version < -1:
            row += struct.pack("<iBh5i", 1, 3, 7, -10, 2, 3, 4, 5)
        return prefix + struct.pack("<i", 1) + row + (struct.pack("<i", 0) if version < 0 else b"")
    for version in [42, -1, -2, -3, -4, -5]:
        fixture = make(version)
        parsed = parse_mob_db(fixture, 42)
        row = parsed["monsters"][0]
        assert row["def"] == 3850 and row["cutAttack"] == -10 and row["maxHp"] == 123456789
        assert row["properties"] == ([] if version >= -1 else
               [{"uid": 3, "typeRaw": 7, "values": [-10, 2, 3, 4, 5]}])
        for invalid in [fixture[:-1], fixture + b"x", b"", struct.pack("<iii", -5, 42, -1)]:
            try:
                parse_mob_db(invalid)
            except (ValueError, struct.error):
                pass
            else:
                raise AssertionError("Malformed Mob DB accepted")
    assert parse_enemy_text(struct.pack("<iiB", 1, 1001, 7) + b"Altadar") == {1001: "Altadar"}
    text = struct.pack("<iiB", 1, 501, 7) + b"Altadar"
    catalog = parse_tables({"a": make(-4), "b": make(-4), "bad": b"x"}, {"us": text})
    assert len(catalog["monsters"]) == 1 and catalog["monsters"][0]["key"] == "42:1001"
    assert catalog["monsters"][0]["gameMonsterId"] == 501
    assert catalog["monsters"][0]["names"] == {"us": "Altadar"}
    assert catalog["monsters"][0]["sourceAssets"] == ["a", "b"]
    assert len(catalog["rejectedTables"]) == 1
    for version, size in [(42, 54), (-2, 54), (-3, 56), (-4, 58), (-5, 78)]:
        fixture = (struct.pack("<h", 300) if version < -2 else bytes([99])) + bytes(30)
        fixture += (struct.pack("<h", 301) if version < -2 else bytes([98]))
        fixture += struct.pack("<11h", *range(-10, 1))
        if version < -3:
            fixture += struct.pack("<h", 123)
        if version <= -5:
            fixture += struct.pack("<10h", *range(10, 20))
        assert len(fixture) == size
        reader = Reader(fixture)
        action = action_pattern(reader, version)
        assert reader.pos == size and action["commandId"] == (300 if version < -2 else 99)
        assert action["combo"] == (301 if version < -2 else 98)
        assert action["values"][:10] == list(range(-10, 0))
        if version <= -5:
            assert action["values"][10:] == list(range(10, 20))
        try:
            action_pattern(Reader(fixture[:-1]), version)
        except ValueError:
            pass
        else:
            raise AssertionError("Truncated variable action accepted")
    bad_text = struct.pack("<iiB", 2, 1001, 1) + b"x" + struct.pack("<iB", 1001, 1) + b"y"
    for invalid in [bad_text, bad_text[:-1], bad_text + b"x"]:
        try:
            parse_enemy_text(invalid)
        except ValueError:
            pass
        else:
            raise AssertionError("Duplicate or malformed Enemy text accepted")
    print("Monster parser self-test PASS (versions, signed stats, variable actions, properties, counts and exact EOF)")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--self-test", action="store_true")
    parser.add_argument("--mob-db", type=Path)
    parser.add_argument("--field-id", type=int)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    if args.self_test:
        self_test()
    else:
        if not args.mob_db or not args.output:
            parser.error("--mob-db and --output required")
        if args.mob_db.resolve() == args.output.resolve():
            parser.error("Output must not replace input")
        result = parse_mob_db(args.mob_db.read_bytes(), args.field_id)
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
