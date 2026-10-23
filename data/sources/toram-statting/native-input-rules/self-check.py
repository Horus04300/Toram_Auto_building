"""Small checks for retained input-gate evidence; does not execute the game."""
from pathlib import Path
import hashlib
import json
import struct

HERE = Path(__file__).resolve().parent


def occupied(kind, fixed, current, original):
    return (fixed or current + original != 0) and kind != 0


def can_enter(potential, slots, enabled=True):
    return potential > 0 and slots > 0 and enabled


def category_order(categories):
    counts, repeated = {}, {}
    for category in categories:
        counts[category] = counts.get(category, 0) + 1
        if counts[category] == 2:
            repeated[category] = 2
        elif counts[category] > 2:
            repeated[category] += 1
    return list(repeated.items())


def main():
    data = json.loads((HERE / 'index.json').read_text(encoding='utf-8'))
    for method in data['methods']:
        assert method['decompileCompleted']
        raw = (HERE / method['pseudocodeFile']).read_bytes()
        assert hashlib.sha256(raw).hexdigest() == method['pseudocodeSha256']
        assert b'Possible PIC construction' not in raw
    for item in data['sourceFiles']:
        raw = (HERE / item['file']).read_bytes()
        assert len(raw) == item['size'] and hashlib.sha256(raw).hexdigest() == item['sha256']
    assert occupied(40, False, 1, 0)
    assert not occupied(40, False, 0, 0)
    assert occupied(40, True, 0, 0)
    assert not occupied(0, True, 1, 0)
    assert not occupied(40, False, -10, 10)
    assert can_enter(1, 1) and not can_enter(0, 1)
    assert not can_enter(100, 0) and not can_enter(100, 1, False)
    assert can_enter(100, 8 - 7) and not can_enter(100, 8 - 8)
    assert category_order([1, 2, 2, 1, 1, 3, 3]) == [(2, 2), (1, 3), (3, 2)]
    print('PASS: 8 retained input-rule functions, source hashes, zero/fixed occupancy, gate boundaries, second-occurrence category order')


if __name__ == '__main__':
    main()
