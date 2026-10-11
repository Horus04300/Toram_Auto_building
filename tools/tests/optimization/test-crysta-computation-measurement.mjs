import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import vm from 'node:vm';
import { measureComputation } from '../../support/crysta-computation-measurement.mjs';

// Drive the actual product Native client with a deterministic monotonic clock.
// Setup, transfer, restoration, evaluation, cache bookkeeping and resume must all precede stop.
const source = await readFile(new URL('../../../assets/js/optimization/native-client.js', import.meta.url), 'utf8');
let clock = 100, resumes = 0, evaluations = 0, failure = false;
const tick = ms => { clock += ms; };
const context = { console, window:null,
  ToramStatRegistry:{}, ToramCalculationKernel:{},
  ToramBuildEvaluator:{ evaluateAggregate() { tick(7); evaluations++; return { constraints:{ feasible:true } }; } },
  ToramCrystaOptimizationGlobalOptimizer:{ deriveRelevantKeys() { tick(2); return ['ATK']; }, prepareProblem(problem) { tick(3); return problem; } },
  __TAURI__:{ core:{ Channel:class {}, async invoke(command) {
    await Promise.resolve(); // Include asynchronous delivery, not just the immediate invoke return.
    if (command === 'crysta_hardware_profile') { tick(5); return { logicalThreads:2 }; }
    if (command === 'crysta_optimize_parallel' || command === 'resume_crysta_optimization') {
      tick(11);
      if (failure) throw new Error('bridge failed');
      const resumed = command === 'resume_crysta_optimization';
      if (resumed) resumes++;
      return { status:resumed ? 'exact' : 'bounded', exact:resumed, score:4, upperBound:resumed ? 4 : 8,
        continuationId:resumed ? null : 'd4c-test',
        bestBuild:{ id:'a||b||c||d', packageIds:['a','b','c','d'], statDelta:{ ATK:4 } } };
    }
    if (command === 'dispose_crysta_optimization') return true;
    throw new Error(command);
  } } }
};
context.window = context;
vm.createContext(context);
const loadClient = () => { vm.runInContext(source, context); return context.ToramCrystaOptimizationNativeClient; };
const compile = () => {
  tick(13);
  return { baseContext:{}, scenarioSnapshot:{}, metadata:{},
    groups:['a','b','c','d'].map(id => ({ id, packages:[{ id, statDelta:{ ATK:1 } }] })) };
};
const first = await measureComputation({ compile, client:loadClient(), now:() => clock });
assert.equal(first.result.status, 'exact');
assert.equal(first.result.bestBuild.packages.length, 4, 'Stop after result package restoration');
assert.equal(evaluations, 2, 'Both bounded and final snapshots are reevaluated');
assert.equal(resumes, 1);
assert.equal(first.timing.compileMs, 13);
assert.equal(first.timing.executionAndResultMs, 46); // 2+3+5 + (11+7)*2
assert.equal(first.timing.totalMs, 59, 'One continuous clock includes all preparation and final JS evaluation');
assert.equal(first.timing.slices, 2);
assert.equal(first.timing.cached, false);

const cached = await measureComputation({ compile, client:context.ToramCrystaOptimizationNativeClient, now:() => clock });
assert.equal(cached.timing.cached, true, 'Cached executions must be distinguishable from full search');
assert.equal(cached.timing.totalMs, 23, 'Cache hits still include compiler, prepare and hardware/cache lookup');

const bounded = await measureComputation({ compile, client:loadClient(), now:() => clock, maxDurationMs:1 });
assert.equal(bounded.result.status, 'bounded', 'A duration cap must not label partial work exact');
assert.equal(bounded.timing.slices, 1);
failure = true;
await assert.rejects(measureComputation({ compile, client:loadClient(), now:() => clock }), error => {
  assert.equal(error.measurement.status, 'error');
  assert.equal(error.measurement.totalMs, 34);
  return /bridge failed/.test(error.message);
});
await assert.rejects(measureComputation({ compile() { tick(17); throw new Error('compile failed'); }, client:loadClient(), now:() => clock }), error => {
  assert.equal(error.measurement.totalMs, 17);
  assert.equal(error.measurement.compileMs, null);
  return true;
});
console.log('CrystaOptimization computation timing: PASS (compile, async execution, restoration/evaluation, continuation, cache, errors)');
