"""Boundary replays for every ordinary, non-selector GrantData option."""
import argparse
from collections import Counter
import json
from pathlib import Path
from native_model import Model, SPECIAL, max_magnitude, verify_evidence


def run(output):
    model = Model()
    verify_evidence()
    counts, covered, samples = Counter(), set(), []
    for equipment in model.bases:
        for rounding in (('combined-floor',) if equipment == 20 else ('combined-floor', 'separate-floor')):
            profile = model.profile(equipment, rounding)
            for identity, row in model.rows.items():
                if identity in SPECIAL:
                    continue
                f = row['fields']
                for sign in (1, -1):
                    if sign < 0 and f['LowerMax'] == 0:
                        continue
                    maximum = max_magnitude(f, sign > 0)
                    values = sorted({1, min(maximum, max(1, f['BaseMax'])), maximum})
                    for magnitude in values:
                        value = sign*magnitude
                        for split in (False, True):
                            state, potential = {}, profile['startingPotential']
                            history = []
                            for next_value in ([value] if not split else range(sign, value+sign, sign)):
                                state, potential, rate, trace = model.transition(profile, state, potential, {identity: next_value}, True)
                                history.append(trace)
                                counts['transitions'] += 1
                                if rate < 100 or potential < 1:
                                    counts['riskOrBlockedTerminal'] += 1
                                    break
                            counts['paths'] += 1
                            counts['reachedTarget'] += state[identity] == value
                            counts['all100'] += all(t['warningPercent'] == 100 for t in history)
                            covered.add(identity)
                            if equipment == 10 and rounding == 'combined-floor' and magnitude == maximum:
                                samples.append({'bonusId': identity, 'sign': sign, 'split': split,
                                                'target': value, 'reached': state[identity],
                                                'actionCount': len(history), 'finalPotential': potential,
                                                'lastWarningPercent': rate})
    result = {'schema': 'toram.statting-catalog-boundary-sweep.v1', 'totals': dict(counts),
              'coveredOrdinaryIds': sorted(covered), 'coveredCount': len(covered),
              'excludedSpecialIds': sorted(SPECIAL),
              'scope': 'legal cap/breakpoint operand inputs, from reference max-source profiles; stops at the first risky/blocked action rather than executing impossible continuations',
              'startingPotentialNativeVerified': False, 'samples': samples}
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(result, ensure_ascii=False, indent=2)+'\n', encoding='utf8')
    print(json.dumps({k: v for k, v in result.items() if k != 'samples'}, ensure_ascii=False))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    run(parser.parse_args().output)
