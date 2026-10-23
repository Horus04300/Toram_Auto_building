from pathlib import Path
import hashlib
import json
import runpy

here = Path(__file__).resolve().parent
index = json.loads((here / 'index.json').read_text(encoding='utf-8'))
for entry in index['files']:
    raw = (here / entry['file']).read_bytes()
    assert len(raw) == entry['size'] and hashlib.sha256(raw).hexdigest() == entry['sha256'], entry['file']
namespace = runpy.run_path(str(here / 'extract-base-profiles.py'))
expected = (json.dumps(namespace['build'](), ensure_ascii=False, indent=2) + '\n').encode('utf-8')
assert (here / 'base-profiles.json').read_bytes() == expected
assert 'return *(short *)(self + 0x4c);' in (here / 'ItemDBData-get_Potential-7fff600745c0.c').read_text(encoding='utf-8')
print('PASS: retained native/source file hashes, getter identity, recipe filters, 10 base maxima')
