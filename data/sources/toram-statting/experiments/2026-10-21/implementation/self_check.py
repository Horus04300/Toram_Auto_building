"""Small native arithmetic, replay validation and exact-domain cross checks."""
import contextlib
import io
import json
import runpy
from native_model import Model, SOURCE, f32, max_magnitude, multiplier, row_cost, warning_rate, verify_evidence
from routes import exhaustive, plan


def rejected(work):
    try:
        work()
    except ValueError:
        return
    raise AssertionError('invalid input was accepted')


def main():
    checked = verify_evidence()
    with contextlib.redirect_stdout(io.StringIO()):
        reference = runpy.run_path(str(SOURCE/'native-potential/self-check.py'))
    cap_reference = runpy.run_path(str(SOURCE/'native-penalty/self-check.py'))
    model = Model()
    cases = 0
    for identity, record in model.rows.items():
        if identity in (12, 22, 24, 26, 28, 30, 32):
            continue
        fields = record['fields']
        for positive in (False, True):
            assert max_magnitude(fields, positive) == cap_reference['max_magnitude'](fields, 325, (10, 10, 10), positive, identity)
        for old in (-fields['BaseMax']-1, -1, 0, 1, fields['BaseMax']+1):
            for delta in (-7, -1, 0, 1, 7):
                for weapon in (False, True):
                    cost = fields['UsePotential'] * (2 if fields['DoubleUse'] == (2 if weapon else 1) else 1)
                    assert row_cost(old, delta, fields, weapon) == reference['potential'](
                        old, delta, cost, fields['BaseMax'], fields['OverRate'], 255)
                    cases += 1
    assert multiplier([8, 8]) == f32(1.2)
    assert multiplier([8, 8, 8]) == f32(1.45)
    assert multiplier([8, 8, 8, 5, 5]) == f32(f32(1.45)+f32(.2))
    assert warning_rate(100, 100, 67)[0] == 100
    assert warning_rate(363, 458, 67)[0] == 99
    assert warning_rate(20, 50, 67)[0] == 57
    profile = model.profile(10)
    assert profile['startingPotential'] == 128
    assert model.profile(11)['startingPotential'] == 138
    assert model.profile(20)['startingPotential'] == 132
    assert model.profile(10, 'separate-floor')['startingPotential'] == 127
    request = {'schema': 'toram.statting-input.v1', 'equipmentType': 10,
               'steps': [[{'bonusId': 34, 'value': -30}, {'bonusId': 36, 'value': -15}],
                         [{'bonusId': 40, 'value': 20}, {'bonusId': 42, 'value': 23}]]}
    replay = model.replay(request)
    assert replay['prefixAll100'] and replay['finalWarningPercent'] == 100
    rejected(lambda: model.replay(dict(request, startingPotential=999)))
    rejected(lambda: model.validate_value(40, 33))
    rejected(lambda: model.validate_value(40, 0))
    rejected(lambda: model.validate_value(40, 1.5))
    rejected(lambda: model.validate_value(40, True))
    rejected(lambda: model.validate_value(30, 30))
    rejected(lambda: model.transition(profile, {}, 0, {40: 1}))
    full = {1: 1, 2: 1, 3: 1, 4: 1, 5: 1, 6: 1, 7: 1, 8: 1}
    rejected(lambda: model.transition(profile, full, 100, {1: 2}))
    rejected(lambda: model.transition(profile, {40: 1}, 100, {40: -1}))
    for target in ({21: 4, 51: 3, 34: -10}, {21: 5, 51: 4, 34: -12}):
        oracle = exhaustive(model, profile, target)
        actual = plan(model, profile, {i: v for i, v in target.items() if v > 0}, {i: v for i, v in target.items() if v < 0})
        score = actual['best'].get('combined', {}).get('warningPercent', 0)
        assert score == oracle['best']['warningPercent']
        if actual['best']:
            best = actual['best']['combined']
            trace = model.replay({'schema': 'toram.statting-input.v1', 'equipmentType': 10,
                'steps': [[{'bonusId': i, 'value': v} for i, v in action.items()] for action in best['steps']]})
            assert trace['prefixAll100'] and trace['finalWarningPercent'] == score
    print(f'PASS: {checked} retained method hashes, {cases} row translations, caps, 20/45/65%, native warning examples, invalid inputs, exact-oracle bounds and replay')


if __name__ == '__main__':
    main()
