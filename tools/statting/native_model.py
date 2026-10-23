"""Offline reconstruction of retained statting arithmetic, never game access.

Crafting's final rounding is not established: the two starting profiles are
explicit source-model sensitivity cases, not claimed server-generated maxima.
"""
from collections import Counter
import hashlib
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / 'data/sources/toram-statting'
LEVEL, TEC, SLOTS = 325, 255, 8
SPECIAL = {12, 22, 24, 26, 28, 30, 32, 65}
SINGLE = {11, 13, 14, 16, 20}
f32 = lambda x: struct.unpack('<f', struct.pack('<f', x))[0]


def require(condition, message):
    if not condition:
        raise ValueError(message)


def div0(a, b):
    return (abs(a) // b) * (-1 if a < 0 else 1)


def max_magnitude(fields, positive):
    # Three grant skills at Lv10: the native skill factor is exactly 1.
    base, scale = fields['BaseMax'], fields['OverRate']
    increase = int(f32(fields['Rate'] * f32(LEVEL // 10 - 20))) * scale
    limit = (fields['UpperMax' if positive else 'LowerMax'] - base) * scale + base
    return max(1, min(base + increase, limit))


def row_cost(old, delta, fields, weapon):
    c, t, s = fields['UsePotential'], fields['BaseMax'], fields['OverRate']
    if fields['DoubleUse'] == (2 if weapon else 1):
        c *= 2
    y = old + delta
    if delta >= 0:
        a = min(delta, -t-old) if old < -t else 0
        r = delta-a
        b = min(r, y-t) if y > t else 0
        result = c * (div0(a, s)+r-b+2*div0(b, s))
    else:
        a = max(delta, t-old) if old > t else 0
        r = delta-a
        b = max(r, y+t) if y < -t else 0
        score = f32(f32(f32(div0(b, s))*f32(.5))+f32(div0(a, s)-b+r))
        refund = f32(f32(f32(TEC)/f32(1000))+f32(.05))
        result = int(f32(f32(refund*score)*f32(c)))
    require(-32768 <= result <= 32767, 'unsupported row overflow')
    return result


def multiplier(categories):
    # Native dictionary gets a category on its SECOND occurrence.
    seen, duplicates = Counter(), {}
    for category in categories:
        seen[category] += 1
        if seen[category] >= 2:
            duplicates[category] = seen[category]
    value = f32(1)
    for count in duplicates.values():
        value = f32(value + f32(f32(count*count)*f32(.05)))
    return value


def warning_rate(current, cost, base):
    a = f32(f32(100)/f32(max(base, current)))
    b = f32(a*f32(cost-current))
    c = f32(b*f32(2.3))
    integer = max(0, int(f32(f32(160)-c)))
    return min(100, integer), integer


class Model:
    def __init__(self):
        self.catalog = json.loads((SOURCE/'catalog.json').read_text(encoding='utf8'))
        self.rows = {r['id']: r for r in self.catalog['options'] if r['dictionary'] == 'EnhanceCost'}
        self.bases = {p['equipmentType']: p for p in json.loads(
            (SOURCE/'native-crafting/base-profiles.json').read_text(encoding='utf8'))['profiles']}
        self.budget = json.loads((SOURCE/'native-stat-budget/budget.325.json').read_text(encoding='utf8'))
        require(self.budget['appSumOfFiveBaseStats'] == 840, 'unreviewed crafter budget')
        self.cost_cache, self.factor_cache = {}, {}

    def profile(self, equipment_type, rounding='combined-floor'):
        require(type(equipment_type) is int and equipment_type in self.bases, 'unsupported crafting category')
        require(rounding in ('combined-floor', 'separate-floor'), 'unknown crafting rounding model')
        entry = self.bases[equipment_type]
        base = entry['maxBasePotential']
        bonus = self.budget['singleStat' if equipment_type in SINGLE else 'pairedStats']['potentialBonus']
        increase = base*30//100 if rounding == 'combined-floor' else base*10//100+base*20//100
        return {'equipmentType': equipment_type, 'label': entry['label'], 'basePotential': base,
                'startingPotential': base+increase+bonus, 'craftStatBonus': bonus,
                'craftingRoundingModel': rounding, 'startingPotentialNativeVerified': False,
                'gameItemIds': [r['gameItemId'] for r in entry['items']],
                'statterLevel': LEVEL, 'statterTEC': TEC, 'grantSkills': [10, 10, 10],
                'crafterAppStatBudget': 840, 'slotPenalty': 'excluded from reference profile'}

    def validate_value(self, identity, value):
        require(type(identity) is int and identity in self.rows and identity not in SPECIAL,
                f'unsupported option {identity}: special conversions are outside this experiment')
        require(type(value) is int and value != 0, 'values must be nonzero integers in native operand units')
        f = self.rows[identity]['fields']
        require(value > 0 or f['LowerMax'] > 0, 'negative direction not in master domain')
        require(abs(value) <= max_magnitude(f, value > 0), f'Lv325 cap exceeded: {identity}={value}')

    def transition(self, profile, options, potential, updates, detail=False):
        require(type(potential) is int and potential >= 1, 'cannot start from exhausted potential')
        require(len(options) < SLOTS, 'cannot re-enter with all usable slots occupied')
        require(bool(updates), 'empty action')
        final = dict(options)
        total, rows = 0, []
        for identity, value in updates.items():
            self.validate_value(identity, value)
            old = options.get(identity, 0)
            require(value != old, 'no-op option in action')
            require(old == 0 or (old > 0) == (value > 0), 'sign crossing requires separate UI evidence')
            key = (profile['equipmentType'] != 20, identity, old, value)
            if key not in self.cost_cache:
                self.cost_cache[key] = row_cost(old, value-old, self.rows[identity]['fields'], key[0])
            amount = self.cost_cache[key]
            total += amount
            require(-32768 <= total <= 32767, 'unsupported accumulated overflow')
            final[identity] = value
            if detail:
                rows.append({'bonusId': identity, 'old': old, 'new': value, 'delta': value-old, 'cost': amount})
        require(len(final) <= SLOTS, 'usable slot limit exceeded')
        types = tuple(final)
        if types not in self.factor_cache:
            self.factor_cache[types] = multiplier(self.rows[i]['fields']['AbilityCategory'] for i in types)
        factor = self.factor_cache[types]
        cost = int(f32(f32(total)*factor))
        require(-32768 <= cost <= 32767, 'unsupported final cost overflow')
        after = potential-cost
        require(-32768 <= after <= 32767, 'unsupported potential overflow')
        rate, raw = warning_rate(potential, cost, profile['basePotential'])
        if detail:
            return final, after, rate, {'beforePotential': potential, 'afterPotential': after,
                'rowCosts': rows, 'rowCostSum': total, 'multiplierFloat32': factor,
                'totalCost': cost, 'warningPercent': rate, 'warningIntegerBeforeUpperBound': raw,
                'categoryCounts': dict(Counter(self.rows[i]['fields']['AbilityCategory'] for i in final)),
                'optionsAfter': [{'bonusId': i, 'value': v} for i, v in final.items()]}
        return final, after, rate

    def replay(self, request):
        require(set(request) <= {'schema', 'equipmentType', 'craftingRoundingModel', 'steps'}, 'unknown input field')
        require(request.get('schema') == 'toram.statting-input.v1', 'unsupported input schema')
        profile = self.profile(request['equipmentType'], request.get('craftingRoundingModel', 'combined-floor'))
        require('startingPotential' not in request, 'starting potential is derived from the reference profile')
        require(type(request.get('steps')) is list and request['steps'], 'steps required')
        state, potential, trace = {}, profile['startingPotential'], []
        for step in request['steps']:
            require(type(step) is list and step, 'an action must contain option changes')
            updates = {}
            for row in step:
                require(set(row) == {'bonusId', 'value'}, 'option fields must be bonusId and value')
                require(row['bonusId'] not in updates, 'duplicate option in one action')
                updates[row['bonusId']] = row['value']
            state, potential, rate, record = self.transition(profile, state, potential, updates, True)
            trace.append(record)
        return {'schema': 'toram.statting-trace.v1', 'profile': profile, 'steps': trace,
                'prefixAll100': all(r['warningPercent'] == 100 for r in trace[:-1]),
                'finalWarningPercent': rate, 'serverOutcomesSimulated': False}


def verify_evidence():
    checked = 0
    for directory in ('native-schema', 'native-penalty', 'native-success', 'native-input-rules'):
        index = json.loads((SOURCE/directory/'index.json').read_text(encoding='utf8'))
        for entry in index['methods']:
            if entry.get('pseudocodeFile'):
                raw = (SOURCE/directory/entry['pseudocodeFile']).read_bytes()
                require(hashlib.sha256(raw).hexdigest() == entry['pseudocodeSha256'], 'native evidence changed')
                checked += 1
    for entry in json.loads((SOURCE/'native-potential/index.json').read_text(encoding='utf8'))['files']:
        require(hashlib.sha256((SOURCE/'native-potential'/entry['file']).read_bytes()).hexdigest() == entry['sha256'],
                'potential evidence changed')
    for manifest in ('catalog.json', 'native-crafting/base-profiles.json'):
        for name, expected in json.loads((SOURCE/manifest).read_text(encoding='utf8'))['inputs'].items():
            require(hashlib.sha256((ROOT/name).read_bytes()).hexdigest() == expected, 'source input changed')
    return checked
