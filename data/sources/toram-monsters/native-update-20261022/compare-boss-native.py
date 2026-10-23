import collections
import difflib
import hashlib
import json
from pathlib import Path
import re

root = Path.cwd()
base = root / 'build/tmp/update-pipeline-20261022'
rows = [r for r in json.loads((base / 'native-review/index.json').read_text()) if 'toram-monsters' in r['oldPath']]
out = root / 'assets/source-data/toram-monsters/native-update-20261022'
(out / 'functions').mkdir(parents=True, exist_ok=True)
(out / 'diffs').mkdir(exist_ok=True)
assert out.resolve().is_relative_to((root/'assets/source-data/toram-monsters').resolve())
expected = {r['pseudocodeFile'] for r in rows}
for path in (out/'functions').glob('*.c'):
    if path.name not in expected:
        path.unlink()
for path in (out/'diffs').glob('*.diff'):
    path.unlink()
def normalize(text):
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    text = text[text.index('{'):]
    maps = collections.defaultdict(dict)
    def token(kind, value):
        mapping = maps[kind]
        return kind + str(mapping.setdefault(value, len(mapping)))
    text = re.sub(r'LAB_([0-9a-f]{10,16})', lambda m: token('LABEL', m[1]), text)
    text = re.sub(r'\b((?:thunk_)?FUN_[0-9a-f]+|func_0x[0-9a-f]+)\b', lambda m: token('CALL', m[1]), text)
    text = re.sub(r'_?DAT_([0-9a-f]{10,16})|(?<!\w)0x([0-9a-f]{10,16})', lambda m: token('GLOBAL', m[1] or m[2]), text)
    return '\n'.join(line.rstrip() for line in text.splitlines() if line.strip()) + '\n'

result = []
for row in rows:
    old_path = root / row['oldPath'].replace('\\', '/')
    new_path = base / 'native-review' / row['pseudocodeFile']
    old, new = old_path.read_text(), new_path.read_text()
    (out / 'functions' / row['pseudocodeFile']).write_bytes(new_path.read_bytes())
    a, b = normalize(old), normalize(new)
    diff = list(difflib.unified_diff(a.splitlines(True), b.splitlines(True), fromfile=row['oldPath'], tofile=row['pseudocodeFile'], n=2))
    if diff:
        (out / 'diffs' / (str(row['oldIndex']) + '.diff')).write_text(''.join(diff), encoding='utf-8', newline='\n')
    result.append({**row, 'oldSha256':hashlib.sha256(old_path.read_bytes()).hexdigest(),
                   'newSha256':hashlib.sha256(new_path.read_bytes()).hexdigest(),
                   'normalizedSame': a == b, 'diffLines': len(diff),
                   'reviewLimit':'Normalization removes address identities only; does not prove callee or data semantics.'})
(out / 'index.json').write_text(json.dumps(result, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
print(json.dumps({'total':len(result), 'normalizedSame':sum(r['normalizedSame'] for r in result),
                  'different':[{'id':r['oldIndex'],'path':r['oldPath'].split('\\')[-1],'lines':r['diffLines']} for r in result if not r['normalizedSame']]}, indent=2))
