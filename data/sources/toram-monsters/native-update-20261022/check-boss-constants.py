import hashlib
import json
from pathlib import Path
import re
import struct

root = Path.cwd()
base = root / 'build/tmp/update-pipeline-20261022'
mapping = json.loads((base / 'new-method-map.json').read_text())
mapped = (base / 'snapshot/GameAssembly.mapped.bin').read_bytes()
assert hashlib.sha256(mapped).hexdigest() == mapping['mappedSha256']
image_base = int(mapping['image_base'], 16)
evidence = []
for group in ['native-highraid-target', 'native-guildraid-target']:
    original = root / 'assets/source-data/toram-monsters' / group / 'constants.json'
    for old in json.loads(original.read_text()):
        address = int(old['va'], 16)
        # Each candidate is separately confirmed by explicit new pseudocode references below.
        new_address = address - int('7fff61b52b18',16) + int('7ffe9c049b18',16)
        new_address = {int('7fff61b53a88',16):int('7ffe9c04aa78',16),
                       int('7fff61b53808',16):int('7ffe9c04a7f8',16)}.get(address,new_address)
        old_raw = old.get('rawHex', old.get('hex'))
        size = len(old_raw) // 2
        raw = mapped[new_address-image_base:new_address-image_base+size]
        refs = []
        for row in mapping['methods']:
            if 'toram-monsters' not in row['oldPath']:
                continue
            path = base / 'native-review' / (str(row['oldIndex'])+'.c')
            if path.exists() and format(new_address,'x') in path.read_text():
                refs.append(row['oldIndex'])
        evidence.append({'source':str(original.relative_to(root)), 'oldAddress':old['va'],
                         'newAddress':hex(new_address),'newMappedOffset':new_address-image_base,
                         'oldHex':old_raw,'newHex':raw.hex(),'same':raw.hex()==old_raw,
                         'newValue':struct.unpack('<d' if size==8 else '<f',raw)[0],
                         'newPseudocodeReferences':refs})
out = root / 'assets/source-data/toram-monsters/native-update-20261022/constants.json'
out.write_text(json.dumps({'mappedSha256':mapping['mappedSha256'],'constants':evidence},indent=2)+'\n')
print(json.dumps({'checked':len(evidence),'same':sum(r['same'] for r in evidence),
                  'unreferenced':[r['newAddress'] for r in evidence if not r['newPseudocodeReferences']]},indent=2))
