"""Rebuild reviewed player-craftable base-potential maxima, not finished potential."""
from pathlib import Path
import argparse
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
INPUTS = {
    'assets/source-data/toram-items/items.77596232.connected.json': 'aae63f4e2195832623752f2e7501036a65dba6d8cb1a34e68d1b5d611aaa7c66',
    'assets/source-data/toram-items/item-relations.json': '6b9bc6f2ee0447fdd34528f9becd03ecbc13a6437155969f1ce2df6ea3070341',
}
CATEGORIES = {8:'발도검',9:'선풍창',10:'한손검',11:'양손검',12:'활',13:'자동활',14:'지팡이',15:'마도구',16:'권갑',20:'방어구'}


def eligible(recipe, item):
    return recipe['Type'] == 0 and recipe['Difficulty'] > 0 and item['master']['potential'] > 0


def build():
    loaded = {}
    for path, digest in INPUTS.items():
        raw = (ROOT / path).read_bytes()
        assert hashlib.sha256(raw).hexdigest() == digest, f'Unreviewed input: {path}'
        loaded[path] = json.loads(raw)
    catalog = loaded[next(iter(INPUTS))]
    relations = loaded['assets/source-data/toram-items/item-relations.json']
    items = {item['gameItemId']: item for item in catalog['items']}
    recipes = relations['tables']['RecipeMaster']['records']
    candidates = {}
    for recipe in recipes:
        item = items.get(recipe['CreateId'])
        if item and item['master']['type_id'] in CATEGORIES and eligible(recipe, item):
            candidates.setdefault(item['gameItemId'], []).append(recipe)
    profiles = []
    for type_id, label in CATEGORIES.items():
        ids = [identity for identity in candidates if items[identity]['master']['type_id'] == type_id]
        maximum = max(items[identity]['master']['potential'] for identity in ids)
        maxima = []
        for identity in sorted(ids):
            item = items[identity]
            if item['master']['potential'] != maximum:
                continue
            maxima.append({'gameItemId': identity, 'names': item['names'], 'basePotential': maximum,
                           'qualifyingRecipes': [{key: row[key] for key in ('RecipeId','Type','ReleaseLv','Difficulty','Price','CreateId','CreateVal','Category')}
                                                 for row in candidates[identity]]})
        profiles.append({'equipmentType': type_id, 'label': label, 'candidateItemCount': len(ids),
                         'maxBasePotential': maximum, 'items': maxima})
    assert len(profiles) == 10
    assert all(row['maxBasePotential'] == (63 if row['equipmentType'] == 20 else 67) for row in profiles)
    return {'schema':'toram.craftable-base-potential.v1', 'cacheVersion':'77596232', 'inputs':INPUTS,
            'eligibility':'Recipe Type0 Smith + Difficulty>0 + matching ItemDBData.Potential>0',
            'scope':'Known recipe/base-master support; proficiency, event availability and live server craft permissions are not established.',
            'profiles':profiles,
            'finishedPotentialNotNativeVerified':{'localSource':'docs/sources/skills/Smith.txt',
                'baseSkillPercentAtMax':30,
                'localSourceRule':'Careful Creation Lv10 + Expert Creation Lv10 gives base-only +10% +20%, before user-stat bonus.',
                'userStatSource':'docs/statting.md',
                'rounding':'Exact native crafting bonus arithmetic/order is not established by this bounded client investigation.'}}


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    data = (json.dumps(build(), ensure_ascii=False, indent=2) + '\n').encode('utf-8')
    target = HERE / 'base-profiles.json'
    if args.check:
        assert target.read_bytes() == data, 'Stale generated profiles'
    else:
        target.write_bytes(data)
    assert not eligible({'Type':0,'Difficulty':0},{'master':{'potential':67}})
    assert not eligible({'Type':0,'Difficulty':1},{'master':{'potential':0}})
    assert not eligible({'Type':1,'Difficulty':1},{'master':{'potential':67}})
    assert eligible({'Type':0,'Difficulty':320},{'master':{'potential':67}})
    print('PASS: input hashes, Type/Difficulty/potential eligibility, 10 category maxima' + (', regenerated data unchanged' if args.check else ', base-profiles.json written'))
