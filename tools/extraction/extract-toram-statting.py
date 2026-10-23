"""Rebuild the reviewed GrantData catalog; --check verifies without writing.

This parses a pinned native initializer, not arbitrary future game versions.
Re-decompile and review changed code before updating the fingerprints.
"""
import argparse
import csv
import hashlib
import io
import json
from pathlib import Path
import re
import struct

ROOT = Path(__file__).resolve().parents[2]
BASE = Path('data/sources/toram-statting')
INPUTS = {
    str(BASE / 'native-schema/GrantData-_cctor-7fff5fc80d10.c'):
        '8cdf553f62c52a2f2368eef37fe2b4562deb7eeceae8c9625572eb7bb0ed2bcb',
    'data/sources/toram-items/bonus-types.current.json':
        '77f809c636b65201b51d204106e523cdb2a409da187d5128acbcb2cce635fe0b',
    'data/sources/toram-items/item-localization-links.json':
        'da9642f9486911fda6d15f132db288708f3d45ed0eb1850d65416592f386f8cb',
    'data/sources/toram-items/option-display-rules.json':
        '27e661c10bf05c1986c7136c3a90ab8854f5cc0e947f1ac60d8e9d96070fde28',
    'data/sources/toram-items/crysta-link-audit.json':
        '27e9f921093105cb2eb331b99da0601a80f6423ed83629e99938d34ccdba3a0c',
}
CONSTANT_HEX = {
    '7fff61b52b18': '0000803f', '7fff61b52b4c': '0000003f',
    '7fff61b52cc4': 'cdcccc3e', '7fff61b52f48': '3333b33e',
    '7fff61b538b0': '5c8f423e', '7fff61b538b4': 'd7a3303f',
}
FIELDS = ('UsePotential', 'Coefficient', 'MaterialCategory', 'AbilityCategory',
          'Rate', 'BaseMax', 'UpperMax', 'LowerMax', 'OverRate', 'DoubleUse')
MATERIALS = ('Metal', 'Cloth', 'Beast', 'Wood', 'Drug', 'Magic')
CTOR = re.compile(r'Toram_Common_Productions_EnhanceProperties2__ctor\s*'
                  r'\(\(undefined \*\)&\w+,([\s\S]*?)\(undefined \*\)0x0\s*\);')


def parse_initializer(source):
    calls = list(CTOR.finditer(source))
    assert len(calls) == source.count('EnhanceProperties2__ctor') == 73
    boundary = source.index('**(longlong **)(_DAT_7fff62420f50 + 0xb8) = lVar3;')
    rows = []
    for ordinal, call in enumerate(calls):
        args = [part.strip() for part in call[1].strip().rstrip(',').split(',')]
        assert len(args) == 10
        for i, arg in enumerate(args):
            if i != 4:
                args[i] = int(arg, 0)
                continue
            if re.fullmatch(r'rate(?:_\d+)?|fVar2', arg):
                assignments = re.findall(r'\b' + arg + r' = ([^;]+);', source[:call.start()])
                assert assignments, arg
                arg = assignments[-1]
            if arg.startswith('_DAT_'):
                args[i] = struct.unpack('<f', bytes.fromhex(CONSTANT_HEX[arg[5:]]))[0]
            else:
                args[i] = float(arg)
        end = calls[ordinal + 1].start() if ordinal + 1 < len(calls) else len(source)
        adds = re.findall(r'FUN_7fff6087ca00\(lVar3,([^,]+),', source[call.end():end])
        assert len(adds) == 1
        rows.append({'dictionary': 'EnhanceCost' if call.start() < boundary else 'EnhanceElementCost',
                     'id': int(adds[0], 0), 'fields': dict(zip(FIELDS, args)),
                     'initializerLine': source[:call.start()].count('\n') + 1})
    assert len({(r['dictionary'], r['id']) for r in rows}) == 73
    assert sum(r['dictionary'] == 'EnhanceCost' for r in rows) == 67
    return rows


def build():
    evidence = ROOT / BASE / 'native-schema'
    index = json.loads((evidence / 'index.json').read_text(encoding='utf-8'))
    for method in index['methods']:
        if 'pseudocodeFile' in method:
            assert hashlib.sha256((evidence / method['pseudocodeFile']).read_bytes()).hexdigest() == method['pseudocodeSha256']
    for name, key in [('metadata.json', 'metadataSha256'), ('TraceToramStattingSchema.java', 'scriptSha256')]:
        assert hashlib.sha256((evidence / name).read_bytes()).hexdigest() == index[key]
    inputs = {}
    for path, expected in INPUTS.items():
        raw = (ROOT / path).read_bytes()
        assert hashlib.sha256(raw).hexdigest() == expected, f'Unreviewed source change: {path}'
        inputs[path] = raw.decode('utf-8')
    source = inputs[next(iter(INPUTS))]
    rows = parse_initializer(source)
    bonus = json.loads(inputs['data/sources/toram-items/bonus-types.current.json'])
    names = {r['id']: r['name'] for r in bonus['values']}
    texts = json.loads(inputs['data/sources/toram-items/item-localization-links.json'])
    localized = {r['propertyId']: r['templates'] for r in texts['propertyTexts']}
    mapping = json.loads(inputs['data/sources/toram-items/crysta-link-audit.json'])
    stats = {r['capId']: r for r in mapping['statMapping']}
    display = json.loads(inputs['data/sources/toram-items/option-display-rules.json'])
    multipliers = {r['capId']: r['multiplierFloat32'] for r in display['overrides']}
    for row in rows:
        element = row['dictionary'] == 'EnhanceElementCost'
        identity = row['id']
        row['bonusId'] = 65 if element else identity
        row['elementId'] = identity if element else None
        row['enumName'] = names[row['bonusId']]
        row['templates'] = texts['elementTextById'][str(identity)] if element else localized[identity]
        assert set(row['templates']) == {'kr', 'us', 'jp', 'cnt', 'idn', 'th'}
        row['materialName'] = MATERIALS[row['fields']['MaterialCategory']]
        stat = stats.get(row['bonusId']) if not element else None
        row['projectStatId'] = stat['statId'] if stat else None
        row['projectUnit'] = stat['registryUnit'] if stat else None
        row['displayMultiplierFloat32'] = multipliers.get(row['bonusId'], 1.0)
    by_id = {r['id']: r for r in rows if r['dictionary'] == 'EnhanceCost'}
    # Catch reassigned decompiler locals and accidental critical/accuracy category drift.
    assert by_id[21]['fields']['Rate'] == struct.unpack('<f', bytes.fromhex('5c8f423e'))[0]
    assert by_id[52]['fields']['Rate'] == struct.unpack('<f', bytes.fromhex('cdcccc3e'))[0]
    assert by_id[34]['fields']['AbilityCategory'] == by_id[35]['fields']['AbilityCategory'] == 2
    assert by_id[22]['fields']['AbilityCategory'] == by_id[23]['fields']['AbilityCategory'] == 5
    assert {by_id[i]['fields']['AbilityCategory'] for i in (40, 41, 42, 43)} == {8}
    categories = []
    for category in sorted({r['fields']['AbilityCategory'] for r in rows}):
        members = [r for r in rows if r['fields']['AbilityCategory'] == category]
        categories.append({'id': category, 'memberKeys': [f"{r['dictionary']}:{r['id']}" for r in members],
                           'krTemplates': [r['templates']['kr'] for r in members]})
    catalog = {'schema': 'toram.native-statting.v1', 'authority': 'saved-native-static-analysis',
               'metadataSha256': 'f0cf212a7c7dca1973a401bda6d208549c13f57f0bbdb8782e5d607ed7e8789f',
               'inputs': INPUTS, 'floatConstantHexLE': CONSTANT_HEX, 'limitLevelBreakpoint': 210,
               'ordinaryCount': 67, 'elementCount': 6, 'categories': categories, 'options': rows}
    encoded = (json.dumps(catalog, ensure_ascii=False, indent=2) + '\n').encode('utf-8')
    stream = io.StringIO(newline='')
    writer = csv.writer(stream, lineterminator='\n')
    writer.writerow(['dictionary', 'id', 'bonusId', 'elementId', 'enumName', 'kr', 'us',
                     *FIELDS, 'materialName', 'projectStatId', 'projectUnit', 'displayMultiplierFloat32'])
    for row in rows:
        writer.writerow([row['dictionary'], row['id'], row['bonusId'], row['elementId'],
                         row['enumName'], row['templates']['kr'], row['templates']['us'],
                         *row['fields'].values(), row['materialName'], row['projectStatId'],
                         row['projectUnit'], row['displayMultiplierFloat32']])
    return {'catalog.json': encoded, 'catalog.csv': stream.getvalue().encode('utf-8')}


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    for name, data in build().items():
        path = ROOT / BASE / name
        if args.check:
            assert path.read_bytes() == data, f'Stale generated catalog: {path}'
        else:
            path.write_bytes(data)
    print('PASS: 67 ordinary + 6 elemental options, six locales, source hashes, alias/category checks'
          + (', generated files unchanged' if args.check else ', generated catalog.json/catalog.csv'))
