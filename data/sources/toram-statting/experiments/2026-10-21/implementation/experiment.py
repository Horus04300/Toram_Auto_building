"""Reproducible route survey and small-domain exhaustive oracle comparisons."""
import argparse
from collections import Counter
import csv
import hashlib
import json
from pathlib import Path
import random
import time
from native_model import Model, SOURCE, SPECIAL, max_magnitude, verify_evidence
from routes import exhaustive, plan

FRAMES = {
    'atk-crit-stat': ((18, 43, 42, 40, 6), (34, 36, 25)),
    'matk-crit-stat': ((20, 43, 42, 40, 7), (34, 36, 23)),
    'atk-dte-crit': ((18, 53, 43, 42, 40), (34, 36, 25)),
    'atk-four-crit': ((18, 43, 42, 40, 41), (34, 36, 25)),
    'atk-dte-stat': ((18, 53, 6), (34, 36, 25)),
    'matk-dte-stat': ((20, 53, 7), (34, 36, 23)),
}


def allowed_frames(equipment):
    if equipment == 20:
        return tuple(FRAMES)
    if equipment in (14, 15):
        return ('matk-crit-stat', 'matk-dte-stat')
    return ('atk-crit-stat', 'atk-dte-crit', 'atk-four-crit', 'atk-dte-stat')


def targets(model, frame, count, rng):
    positive_ids, negative_ids = FRAMES[frame]
    seen = set()
    for sample in range(count):
        positives, negatives = {}, {}
        for identity in positive_ids:
            fields = model.rows[identity]['fields']
            maximum = max_magnitude(fields, True)
            if sample == 0:
                value = maximum
            elif sample == 1:
                value = min(maximum, max(1, fields['BaseMax']))
            else:
                value = rng.randint(max(1, min(maximum, fields['BaseMax'])-2), maximum)
            positives[identity] = value
        for identity in negative_ids:
            fields = model.rows[identity]['fields']
            maximum = max_magnitude(fields, False)
            value = min(maximum, fields['BaseMax']) if sample % 3 == 1 else maximum
            negatives[identity] = -value
        key = (tuple(positives.items()), tuple(negatives.items()))
        if key not in seen:
            seen.add(key)
            yield positives, negatives


def score(results, key):
    return results.get(key, {}).get('warningPercent', 0)


def save_example(model, out, name, case):
    if not case:
        return
    traces = {}
    for family in ('baseline', 'negative-first', 'negative-first-split', 'drain', 'drain-split', 'mixed', 'mixed-split', 'combined'):
        route = case['routes']['best'].get(family)
        if not route:
            continue
        request = {'schema': 'toram.statting-input.v1', 'equipmentType': case['equipmentType'],
                   'craftingRoundingModel': case['rounding'],
                   'steps': [[{'bonusId': i, 'value': v} for i, v in action.items()] for action in route['steps']]}
        trace = model.replay(request)
        assert trace['prefixAll100']
        assert trace['finalWarningPercent'] == route['warningPercent']
        traces[family] = {'input': request, 'trace': trace}
    (out/f'{name}.json').write_text(json.dumps({'case': case, 'traces': traces}, ensure_ascii=False, indent=2)+'\n', encoding='utf8')


def run(output, samples, seed):
    output.mkdir(parents=True, exist_ok=True)
    model = Model()
    checked = verify_evidence()
    rng = random.Random(seed)
    started = time.perf_counter()
    totals = Counter()
    families = Counter()
    gains = Counter()
    sensitivity = {}
    examples = {}
    rows = []
    used_options = set()
    for equipment in model.bases:
        roundings = ('combined-floor',) if equipment == 20 else ('combined-floor', 'separate-floor')
        for frame in allowed_frames(equipment):
            cases = list(targets(model, frame, samples, rng))
            for positives, negatives in cases:
                used_options.update(positives)
                used_options.update(negatives)
                for rounding in roundings:
                    profile = model.profile(equipment, rounding)
                    result = plan(model, profile, positives, negatives)
                    totals['inputCases'] += 1
                    for key in ('prefixStatesGenerated', 'negativeSchedulesAttempted', 'completedRoutes', 'uniqueCompletedRoutes'):
                        totals[key] += result[key]
                    best = result['best']
                    baseline, combined = score(best, 'baseline'), score(best, 'combined')
                    if 'combined' in best:
                        winner = best['combined']
                        families[winner['family']] += 1
                        totals['foundExecutableRoute'] += 1
                        totals['all100Found'] += combined == 100
                    else:
                        totals['noRouteFound'] += 1
                    gains['betterThanBaseline'] += combined > baseline
                    gains['baselineEqual'] += combined == baseline
                    gains['negativeOrderingImproves'] += score(best, 'negative-first') > baseline
                    gains['splitWithoutDrainImproves'] += score(best, 'negative-first-split') > score(best, 'negative-first')
                    gains['drainAddsImprovement'] += combined > max(score(best, 'negative-first'), score(best, 'negative-first-split'))
                    gains['mixedAddsImprovement'] += max(score(best, 'mixed'), score(best, 'mixed-split')) > max(
                        score(best, 'negative-first'), score(best, 'negative-first-split'), score(best, 'drain'), score(best, 'drain-split'))
                    case = {'equipmentType': equipment, 'rounding': rounding, 'frame': frame,
                            'profile': profile, 'positives': positives, 'negatives': negatives, 'routes': result}
                    gain = combined-baseline
                    if gain > examples.get('largest-gain', ({}, -1))[1]:
                        examples['largest-gain'] = (case, gain)
                    if combined == 100 and baseline < 100 and 'certainty-upgrade' not in examples:
                        examples['certainty-upgrade'] = (case, gain)
                    if combined == baseline and baseline > 0 and 'simple-sufficient' not in examples:
                        examples['simple-sufficient'] = (case, gain)
                    if best.get('combined', {}).get('family') == 'drain-split' and combined > baseline and 'drain-split' not in examples:
                        examples['drain-split'] = (case, gain)
                    if gains['mixedAddsImprovement'] and best.get('combined', {}).get('family', '').startswith('mixed') and 'mixed-gain' not in examples:
                        examples['mixed-gain'] = (case, gain)
                    row = {'equipmentType': equipment, 'rounding': rounding, 'frame': frame,
                           'positives': positives, 'negatives': negatives,
                           'baseline': baseline, 'combined': combined,
                           'winnerFamily': best.get('combined', {}).get('family'),
                           'actions': len(best.get('combined', {}).get('steps', [])),
                           **{key: result[key] for key in result if key != 'best'},
                           'scores': {key: score(best, key) for key in best}}
                    rows.append(row)
                    pair = (equipment, frame, tuple(positives.items()), tuple(negatives.items()))
                    sensitivity.setdefault(pair, {})[rounding] = combined
            print(json.dumps({'progressEquipment': equipment, 'frame': frame, 'cases': totals['inputCases'],
                              'uniqueCompletedRoutes': totals['uniqueCompletedRoutes'],
                              'elapsedSeconds': round(time.perf_counter()-started, 3)}), flush=True)

    oracle_results = []
    for equipment in (10, 11, 20):
        for a, b, n in ((4, 3, 10), (5, 4, 12), (6, 4, 16), (6, 5, 16)):
            profile = model.profile(equipment)
            target = {21: a, 51: b, 34: -n}
            exact = exhaustive(model, profile, target)
            heuristic = plan(model, profile, {21: a, 51: b}, {34: -n})
            expected = exact['best']['warningPercent']
            actual = score(heuristic['best'], 'combined')
            assert actual <= expected
            oracle_results.append({'equipmentType': equipment, 'target': target, 'exactWarning': expected,
                'heuristicWarning': actual, 'differencePercentPoints': expected-actual,
                'states': exact['states'], 'edges': exact['edges'], 'scope': exact['scope']})
            if expected > actual:
                save_example(model, output, 'oracle-miss', {'equipmentType': equipment, 'rounding': 'combined-floor',
                    'target': target, 'exact': exact, 'routes': heuristic})
    pairs = [v for v in sensitivity.values() if len(v) == 2]
    summary = {'schema': 'toram.statting-survey.v1', 'seed': seed, 'samplesPerCategoryFrame': samples,
        'scope': 'fixed legal targets in declared frames; monotone nonzero ordinary options; no crafting RNG, reversal, or battle-score optimization',
        'startingPotentialStatus': 'source-model combined-floor and separate-floor sensitivity; native final crafting arithmetic remains unknown',
        'nativeWarningModel': 'retained client pre-start warning only, not server outcome probability',
        'nativeMethodHashesChecked': checked, 'totals': dict(totals), 'winnerFamilies': dict(families),
        'comparisons': dict(gains), 'supportedSurveyOptionIds': sorted(used_options),
        'excludedSpecialIds': sorted(SPECIAL),
        'sensitivity': {'pairedCases': len(pairs),
            'differentWarningScores': sum(v['combined-floor'] != v['separate-floor'] for v in pairs),
            'maxWarningDifferencePoints': max((abs(v['combined-floor']-v['separate-floor']) for v in pairs), default=0)},
        'oracle': {'cases': len(oracle_results), 'edges': sum(v['edges'] for v in oracle_results),
                   'matches': sum(v['differencePercentPoints'] == 0 for v in oracle_results),
                   'maxDifferencePoints': max(v['differencePercentPoints'] for v in oracle_results)},
        'elapsedSeconds': time.perf_counter()-started,
        'sources': {str(path.relative_to(SOURCE)): hashlib.sha256(path.read_bytes()).hexdigest()
                    for path in (SOURCE/'catalog.json', SOURCE/'native-crafting/base-profiles.json',
                                 SOURCE/'native-stat-budget/budget.325.json', SOURCE/'native-success/index.json')},
        'toolHashes': {path.name: hashlib.sha256(path.read_bytes()).hexdigest() for path in Path(__file__).parent.glob('*.py')}}
    (output/'summary.json').write_text(json.dumps(summary, ensure_ascii=False, indent=2)+'\n', encoding='utf8')
    (output/'cases.jsonl').write_text(''.join(json.dumps(row, ensure_ascii=False)+'\n' for row in rows), encoding='utf8')
    (output/'oracle.json').write_text(json.dumps(oracle_results, ensure_ascii=False, indent=2)+'\n', encoding='utf8')
    for name, (case, _) in examples.items():
        save_example(model, output, name, case)
    print(json.dumps(summary, ensure_ascii=False, indent=2), flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--samples', type=int, default=24)
    parser.add_argument('--seed', type=int, default=20261021)
    args = parser.parse_args()
    if not 2 <= args.samples <= 1000:
        parser.error('--samples must be2..1000')
    run(args.output, args.samples, args.seed)
