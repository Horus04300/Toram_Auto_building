"""Reproduce the retained Stoodie menu; never request account/server data."""
import argparse
import hashlib
import json
from pathlib import Path
import runpy
import struct
import importlib.util

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
LOCALES = ['cnt', 'idn', 'jp', 'kr', 'th', 'us']
OFFSETS = [50517 + 73 * i for i in range(16)]


def digest(data):
    return hashlib.sha256(data).hexdigest()


def menu(data, offset):
    if not 18 <= offset <= len(data) - 25:
        raise ValueError('Menu outside script')
    # Reviewed native 41464: version/flags, int field, byte room, int level,
    # three short coordinates, short rotation, short return value.
    values = struct.unpack_from('<hBBiBi3hhh', data, offset)
    opcode, version, flags, field, room, level, x, y, z, rot, ret = values
    if (opcode, version, flags, ret) != (217, 8, 0, -1):
        raise ValueError('Unreviewed command format')
    if struct.unpack_from('<h', data, offset + 23)[0] != 6:
        raise ValueError('Menu missing following End')
    # Previous Check's true target explicitly points at this instruction.
    if struct.unpack_from('<h', data, offset - 16)[0] != 20 or struct.unpack_from('<i', data, offset - 8)[0] != offset:
        raise ValueError('Missing preceding script branch')
    return {'level': level, 'fieldId': field, 'roomId': room,
            'sourceOffset': offset, 'commandVersion': version,
            'precedingCheckOffset': offset - 16,
            'rawCoordinates': [x, y, z], 'rotation': rot,
            'rawCommandHex': data[offset:offset + 23].hex()}


def captured_pools(document):
    if document['authority'] != 'passive-fixed-current-stoodie-reward-list':
        raise ValueError('Unreviewed reward capture')
    reads = document['reads']
    if not (document['bytesRead'] == sum(r['bytes'] for r in reads) <= 65536):
        raise ValueError('Capture read budget mismatch')
    if any(len(bytes.fromhex(r['hex'])) != r['bytes'] for r in reads):
        raise ValueError('Truncated capture range')
    spec = importlib.util.spec_from_file_location('reward_capture', HERE / 'capture-reward-list.py')
    capture = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(capture)
    if document['moduleSha256'] != capture.MODULE_SHA or document['metadataSha256'] != capture.METADATA_SHA:
        raise ValueError('Capture source version mismatch')
    one = lambda purpose: bytes.fromhex(next(r['hex'] for r in reads if r['purpose'] == purpose))
    if struct.unpack('<i', one('Reward stage field ID'))[0] != document['stage']['fieldId']:
        raise ValueError('Capture stage does not match raw field ID')
    if one('Reward stage room ID')[0] != document['stage']['roomId']:
        raise ValueError('Capture room does not match raw room ID')
    for before, after in [('Current TreasureHuntRoomData', 'Final room stability'),
                          ('Server reward list', 'Final reward stability'),
                          ('Reward stage field ID', 'Final field stability')]:
        if one(before) != one(after):
            raise ValueError('Capture changed during reads')
    pools = {}
    for rank in 'DCBAS':
        items = [capture.reward(bytes.fromhex(r['hex'])) for r in reads if r['purpose'] == rank + ' reward Type/Value']
        array = struct.unpack('<Q', one(rank + ' rank array'))[0]
        count = struct.unpack('<Q', one(rank + ' rank array length'))[0] if array else 0
        if count != len(items) or count > capture.MAX_ARRAY or items != document['rankPools'][rank]:
            raise ValueError('Capture rank differs from raw reward fields')
        pools[rank] = items
    return pools


def extract():
    sources = json.loads((HERE / 'inputs.json').read_text(encoding='utf-8'))
    for record in sources:
        if digest((HERE / record['file']).read_bytes()) != record['sha256']:
            raise ValueError('Retained evidence changed: ' + record['file'])
    data = (HERE / 'script_11600.bin').read_bytes()
    stages = [menu(data, off) for off in OFFSETS]
    parser = runpy.run_path(str(ROOT / 'tools/extraction/extract-toram-monster-data.py'))
    names = {loc: parser['parse_enemy_text']((HERE / f'FieldName_{loc}.bin').read_bytes()) for loc in LOCALES}
    for stage in stages:
        stage['names'] = {loc: names[loc].get(stage['fieldId']) for loc in LOCALES}
        stage['registletIds'] = None
        stage['rankPools'] = None
        stage['dropProbability'] = None
    captures_by_level = {}
    for path in sorted((HERE / 'captures').glob('*.json')):
        document = json.loads(path.read_text(encoding='utf-8'))
        pools = captured_pools(document)
        level = document['stage']['level']
        stage = next(s for s in stages if s['level'] == level)
        if any(stage[k] != document['stage'][k] for k in ['fieldId', 'roomId']):
            raise ValueError('Captured stage is not the reviewed menu destination')
        if level in captures_by_level and stage['rankPools'] != pools:
            raise ValueError('Conflicting captured stage pools; review versions before replacing')
        stage['rankPools'] = pools
        stage['registletIds'] = sorted({r['registletId'] for items in pools.values() for r in items if 'registletId' in r})
        reference = {'file': path.relative_to(ROOT).as_posix(), 'sha256': digest(path.read_bytes()),
                     'capturedUtc': document['capturedUtc'], 'bytesRead': document['bytesRead']}
        stage.setdefault('captureSources', []).append(reference)
        captures_by_level[level] = reference
    assert len({s['level'] for s in stages}) == 16
    assert [s['level'] for s in stages] == [10, 30, 50, 70, 90, 110, 130, 150, 170, 190, 210, 220, 230, 250, 270, 290]
    assert stages[0]['fieldId'] == 3403 and stages[-1]['fieldId'] == 40601
    return {'schema': 'toram.registlet-acquisition.v1',
            'authority': 'retained-assets-static-code-and-passive-opened-stage-reward-lists',
            'application': 'releaseC', 'contentCode': 'TreasureHunt',
            'contentName': '스투디의 실험', 'entryFieldId': 11600,
            'entryFieldNames': {loc: names[loc].get(11600) for loc in LOCALES},
            'stages': stages,
            'perRegistletStageCoverage': 'all-stage-lists-observed' if len(captures_by_level) == 16 else 'partial-stage-lists-observed' if captures_by_level else 'unavailable-server-response-required',
            'capturedStageCount': len(captures_by_level),
            'rewardType': {'GemCart': 23, 'GemPowder': 24},
            'serverDataPath': ['CheckTreasureHuntRoomResponse.ItemData (+0x40)',
                               'TreasureHuntRoomData.itemData (+0xe0)',
                               'UITreasureHuntEnterManager.itemData (+0x198)',
                               'TreasureHuntRewardData.D/ C/ B/ A/ SRankItemList (+0x20/28/30/38/40)'],
            'limitations': ['Stage menus identify acquisition content and stage destinations, not which gem appears at each stage.',
                            'Opened-stage reward candidates are passively captured; unobserved stages remain null. Candidate lists contain no per-item drop probabilities.',
                            'Script branch targets establish instruction boundaries; captured stage lists do not prove eligibility, actual loot rolls or future server availability.',
                            'The version-8 raw coordinate values are preserved; no coordinate unit conversion is asserted.']}


def self_test():
    data = bytearray(100)
    struct.pack_into('<h', data, 24, 20)
    struct.pack_into('<i', data, 32, 40)
    struct.pack_into('<hBBiBi3hhh', data, 40, 217, 8, 0, 3403, 0, 10, 1, 2, 3, 180, -1)
    struct.pack_into('<h', data, 63, 6)
    assert menu(data, 40)['level'] == 10
    for offset, value in [(42, 9), (43, 1), (63, 7), (32, 41)]:
        bad = bytearray(data)
        bad[offset] = value
        try:
            menu(bad, 40)
        except ValueError:
            pass
        else:
            raise AssertionError('Malformed instruction accepted')
    try:
        menu(data[:60], 40)
    except ValueError:
        pass
    else:
        raise AssertionError('Truncated instruction accepted')
    capture = json.loads((HERE / 'captures/level-10.json').read_text(encoding='utf-8'))
    assert captured_pools(capture) == capture['rankPools']
    for case in ['value', 'length', 'stability']:
        bad = json.loads(json.dumps(capture))
        if case == 'value':
            bad['rankPools']['D'][0]['rawValue'] += 1
        elif case == 'length':
            bad['reads'][0]['hex'] = ''
        else:
            next(r for r in bad['reads'] if r['purpose'] == 'Final field stability')['hex'] = '00000000'
        try:
            captured_pools(bad)
        except ValueError:
            pass
        else:
            raise AssertionError('Invalid captured reward accepted: ' + case)


if __name__ == '__main__':
    cli = argparse.ArgumentParser(description=__doc__)
    cli.add_argument('--check', action='store_true')
    cli.add_argument('--self-test', action='store_true')
    args = cli.parse_args()
    self_test()
    if args.self_test:
        print('PASS acquisition format/branch/EOF and captured reward/raw-field/stability self-test')
    else:
        result = json.dumps(extract(), ensure_ascii=False, indent=2) + '\n'
        output = HERE / 'stages.json'
        if args.check:
            assert output.read_text(encoding='utf-8') == result, 'Generated stage manifest differs'
        else:
            output.write_text(result, encoding='utf-8')
        print('PASS 16 Stoodie stages, six locales, source hashes; ' + str(json.loads(result)['capturedStageCount']) + ' captured stage pools; probabilities unknown')
