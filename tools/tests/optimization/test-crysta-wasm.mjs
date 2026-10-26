import { exhaustiveSearch } from '../../support/crysta-exhaustive-oracle.mjs';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { loadWasmModule } from '../../support/crysta-wasm-module.mjs';
import { loadHeadlessEnvironment } from '../../support/crysta-headless-environment.mjs';

const wasm = await loadWasmModule();
const env = await loadHeadlessEnvironment();
const fixture = JSON.parse(await readFile(new URL('../../fixtures/crysta-native-runtime-26min-revenir.json', import.meta.url), 'utf8'));
const base = fixture.resolvedExecutionContext.baseContext;
const bridge = env.context.ToramCrystaOptimizationRustBridge;
assert.throws(() => new wasm.SearchSession('invalid'));
assert.throws(() => new wasm.SearchSession(JSON.stringify({ baseContext:{}, groups:[] })));
let comparisons = 0;
for (let i = 0; i < 40; i++) {
  const baseContext = { ...base, atkType:i % 2 ? 'MAG' : 'PHYS', attackPowerMode:'default', ignoreMdef:i % 3 === 0 };
  const requirements = { maxHp:i % 5 === 0 ? 1000000000 : null, maxMp:null, amprBeforeDual:null, normalAttackCrit:null, aspd:null };
  const problem = { schema:'toram.crysta-problem.v1', baseContext,
    scenarioSnapshot:env.evaluator.createScenarioSnapshot(baseContext, { requirements }),
    groups:['weapon','armor','additional','special'].map((id, group) => ({ id, packages:[0,1,2].map(j => ({
      id:id + '-' + j, statDelta:{ ATKP:(i + group + j) % 13, MATKP:(i + group * j) % 9,
        CDMG:j * 2, MAXHP:j % 2 ? -100 : 100, CRIT:5 * j, ASPD:j * 50,
        ATK_UP_VIT:group === 3 ? j * (i % 2 ? 50 : 25) : 0,
        MATK_UP_VIT:group === 3 ? j * (i % 2 ? 25 : 50) : 0 }, candidateNames:[], evaluatorCandidates:[]
    })) })) };
  const setup = bridge.prepare(problem, {});
  const session = new wasm.SearchSession(JSON.stringify(bridge.projectProblem(setup.problem)));
  try {
    const initial = JSON.parse(session.snapshot());
    assert.equal(initial.visitedNodes, 0, 'preview must not explore precision nodes');
    let steps = 0;
    while (!session.is_complete()) {
      session.step(1);
      assert.ok(++steps < 10000, 'small oracle must terminate');
    }
    const result = JSON.parse(session.snapshot());
    const oracle = exhaustiveSearch(problem, { prepared:true, evaluateStats:bridge.evaluate(problem) });
    assert.equal(result.status, oracle.status);
    assert.equal(result.score, oracle.score);
    assert.equal(result.bestBuild?.id, oracle.bestBuild?.id);
    if (result.bestBuild) {
      assert.equal(setup.evaluate(result.bestBuild.statDelta).damage.expected, result.score);
      assert.equal(result.upperBound, result.score);
      assert.equal(result.exact, true);
    }
    comparisons++;
  } finally { session.free(); }
}
console.log(`Rust WASM: PASS (${comparisons} raw exhaustive score/ID cases, physical/magic, infeasible utility, ties, JS final evaluation, resumable slices)`);
