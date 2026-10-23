from pathlib import Path
import hashlib
import json

root = Path(__file__).resolve().parent
index = json.loads((root / 'index.json').read_text(encoding='utf-8'))
assert len(index['methods']) == 14
for row in index['files']:
    data = (root / row['file']).read_bytes()
    assert len(data) == row['size']
    assert hashlib.sha256(data).hexdigest() == row['sha256']
for method in index['methods']:
    assert method['decompileCompleted']
    assert hashlib.sha256((root / method['pseudocodeFile']).read_bytes()).hexdigest() == method['pseudocodeSha256']
for base, bonus, combined, separate in [(67, 51, 138, 137), (67, 41, 128, 127), (63, 51, 132, 132)]:
    assert base * 130 // 100 + bonus == combined
    assert base + base * 10 // 100 + base * 20 // 100 + bonus == separate
print('PASS: 14 selected native methods, all retained map/script/file hashes, source-model sensitivity arithmetic')
