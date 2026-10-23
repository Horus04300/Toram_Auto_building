"""Reconcile saved survey counts, source hashes and replayable examples."""
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
from experiment import save_example
from native_model import Model, ROOT, SOURCE, verify_evidence
from routes import plan


def read(path):
    return json.loads(path.read_text(encoding='utf8'))


def review(directory, model):
    summary = read(directory/'summary.json')
    rows = [json.loads(line) for line in (directory/'cases.jsonl').read_text(encoding='utf8').splitlines()]
    assert len(rows) == summary['totals']['inputCases']
    for field in ('prefixStatesGenerated', 'negativeSchedulesAttempted', 'completedRoutes', 'uniqueCompletedRoutes'):
        assert sum(row[field] for row in rows) == summary['totals'][field]
    assert sum(row['combined'] > 0 for row in rows) == summary['totals'].get('foundExecutableRoute', 0)
    assert sum(row['combined'] == 0 for row in rows) == summary['totals'].get('noRouteFound', 0)
    assert sum(row['combined'] == 100 for row in rows) == summary['totals'].get('all100Found', 0)
    assert dict(Counter(row['winnerFamily'] for row in rows if row['winnerFamily'])) == summary['winnerFamilies']
    for row in rows:
        for identity, value in {**row['positives'], **row['negatives']}.items():
            model.validate_value(int(identity), value)
        assert 0 <= row['baseline'] <= row['combined'] <= 100
    for name, expected in summary['sources'].items():
        assert hashlib.sha256((SOURCE/name).read_bytes()).hexdigest() == expected, name
    for name, expected in summary['toolHashes'].items():
        paths = (directory/'implementation'/name, Path(__file__).parent/name)
        assert any(path.is_file() and hashlib.sha256(path.read_bytes()).hexdigest() == expected for path in paths), name
    oracle = read(directory/'oracle.json')
    assert len(oracle) == summary['oracle']['cases']
    assert sum(row['edges'] for row in oracle) == summary['oracle']['edges']
    assert all(row['exactWarning'] == row['heuristicWarning'] for row in oracle)
    examples = [row for row in rows if 0 < row['baseline'] < row['combined']]
    if examples:
        selected = max(examples, key=lambda row: row['combined']-row['baseline'])
        positives = {int(i): v for i, v in selected['positives'].items()}
        negatives = {int(i): v for i, v in selected['negatives'].items()}
        routes = plan(model, model.profile(selected['equipmentType'], selected['rounding']), positives, negatives)
        assert routes['best']['combined']['warningPercent'] == selected['combined']
        assert routes['best']['baseline']['warningPercent'] == selected['baseline']
        save_example(model, directory, 'review-positive-baseline-gain', dict(selected, routes=routes))
    traces_checked = 0
    for path in directory.glob('*.json'):
        value = read(path)
        if not isinstance(value, dict):
            continue
        for example in value.get('traces', {}).values():
            assert json.loads(json.dumps(model.replay(example['input']))) == example['trace'], path.name
            traces_checked += 1
    def best(row, *families):
        return max((row['scores'].get(family, 0) for family in families), default=0)
    negative = ('negative-first', 'negative-first-split')
    drain = ('drain', 'drain-split')
    mixed = ('mixed', 'mixed-split')
    return {'inputCases': len(rows), 'uniqueCompletedRoutes': summary['totals']['uniqueCompletedRoutes'],
        'traceReplaysChecked': traces_checked,
        'baselinePositiveImproved': len(examples),
        'pureDrainImprovesOverNegativeFamilies': sum(best(row, *drain) > best(row, *negative) for row in rows),
        'mixedImprovesOverOtherFamilies': sum(best(row, *mixed) > best(row, *negative, *drain) for row in rows),
        'atLeastWarning': {str(p): sum(row['combined'] >= p for row in rows) for p in (80, 90, 95, 99, 100)},
        'frames': {frame: {'cases': sum(row['frame'] == frame for row in rows),
            'atLeast90': sum(row['frame'] == frame and row['combined'] >= 90 for row in rows),
            'bestWarning': max(row['combined'] for row in rows if row['frame'] == frame)}
            for frame in sorted({row['frame'] for row in rows})},
        'positiveBaselineExample': selected if examples else None}


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    args = parser.parse_args()
    model = Model()
    checked = verify_evidence()
    result = {'schema': 'toram.statting-survey-review.v1', 'nativeMethodHashesChecked': checked,
              'main': review(args.directory, model), 'armor': review(args.directory/'armor', model)}
    probe = read(args.directory/'score-probe.json')
    for name, expected in probe['sourceHashes'].items():
        assert hashlib.sha256((ROOT/name).read_bytes()).hexdigest() == expected, name
    result['existingEvaluatorSourceHashesChecked'] = len(probe['sourceHashes'])
    (args.directory/'review.json').write_text(json.dumps(result, ensure_ascii=False, indent=2)+'\n', encoding='utf8')
    print(f"PASS: {result['main']['inputCases']+result['armor']['inputCases']} inputs, source hashes, counts, "
          f"{result['main']['traceReplaysChecked']+result['armor']['traceReplaysChecked']} trace replays")
