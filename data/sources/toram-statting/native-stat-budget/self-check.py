"""Verify the approved app budget and the native allocation constraints offline."""
import hashlib
import json
from pathlib import Path
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
index = json.loads((HERE / 'index.json').read_text(encoding='utf8'))
budget = json.loads((HERE / 'budget.325.json').read_text(encoding='utf8'))
for method in index['methods']:
    assert method['decompileCompleted']
    assert hashlib.sha256((HERE / method['pseudocodeFile']).read_bytes()).hexdigest() == method['pseudocodeSha256']
assert hashlib.sha256((HERE / 'TraceToramStatBudget.java').read_bytes()).hexdigest() == index['scriptSha256']
for entry in index['additionalFiles']:
    assert hashlib.sha256((HERE / entry['file']).read_bytes()).hexdigest() == entry['sha256']
source = ROOT / index['appSource']['path']
assert hashlib.sha256(source.read_bytes()).hexdigest() == index['appSource']['sha256']
script = """const vm=require('node:vm'),fs=require('node:fs');
const c={window:{}};vm.createContext(c);
vm.runInContext(fs.readFileSync(process.argv[1],'utf8'),c);
process.stdout.write(JSON.stringify(c.window.ToramStatusPoints.pointBreakdown(325,325)));"""
actual = json.loads(subprocess.check_output(['node', '-e', script, str(source)], text=True))
assert actual == {key: budget[key] for key in actual if key != 'total'} | {'total': budget['appSumOfFiveBaseStats']}
assert actual['total'] == 840 and budget['nativeSpendableInvestment'] == 840 - 5 == 835
assert index['shortMinHelper']['token'] == '0x06000857'
assert index['shortMinHelper']['runtime_va'] == '0x7fff61011120'
assert index['shortMinHelper']['rawCodeHex'].startswith('663bca660f4ed10fb7c2c3')

def unlocked(a, b):
    return min(a, 255) + min(b, 255) - 2 >= 500

previous = (1, 1)
for state in budget['allocationSequence']:
    a, b = state
    assert 1 <= a <= 510 and 1 <= b <= 510
    assert a + b + 3 <= 840
    if a > 255 and previous[0] <= 255 or b > 255 and previous[1] <= 255:
        assert unlocked(*previous)
    if a > 255 or b > 255:
        assert unlocked(a, b)
    previous = a, b
assert previous == (510, 327)
assert sum(previous) + 3 == 840
assert 510 // 10 == budget['singleStat']['potentialBonus'] == 51
assert (840 - 3) // 20 == budget['pairedStats']['potentialBonus'] == 41
valid = [(a, 837-a) for a in range(1, 511)
         if 1 <= 837-a <= 510 and unlocked(a, 837-a)]
assert valid and max(a+b for a,b in valid) == 837
print('PASS: app API Lv325=840 incl. five minima; native 9 hashes, 255/510/500 caps, legal 835pt allocation, single51/paired41')
