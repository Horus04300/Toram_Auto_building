import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const calls = [];
const context = {
  console,
  window:{
    ToramStatRegistry:{ entries:() => [] },
    ToramCalculationKernel:{ evaluateContext:() => ({}) },
    ToramBuildEvaluator:{
      createScenarioSnapshot:base => ({ requirements:{} }),
      evaluateAggregate:(base, scenario, stats) => ({ calculation:{ damageFactor:Number(stats.DMG || 0) }, utility:{} })
    },
    ToramD4GlobalOptimizer:{
      deriveRelevantKeys:() => ['DMG'],
      prepareProblem:(problem, options) => Object.assign({}, problem, { metadata:{ modeledKeys:options.relevantKeys } })
    },
    __TAURI__:{ core:{ invoke:(command, input) => {
      calls.push({ command, input });
      if (command === 'd4_hardware_profile') return Promise.resolve({ logicalThreads:8 });
      if (command === 'd4_optimize_parallel') return Promise.resolve({ status:'exact', exact:true, score:12, bestBuild:{ id:'a||b||c||d', packageIds:['a','b','c','d'], statDelta:{ DMG:12 } } });
      if (command === 'cancel_d4_optimization') return Promise.resolve(true);
      return Promise.reject(new Error('unexpected command'));
    } } }
  }
};
context.window.window = context.window;
vm.createContext(context);
vm.runInContext(await readFile(resolve(root, 'assets/js/d4-native-client.js'), 'utf8'), context, { filename:'d4-native-client.js' });

const problem = {
  baseContext:{}, scenarioSnapshot:{ requirements:{} },
  groups:['a','b','c','d'].map(id => ({ id, packages:[{ id, statDelta:{ DMG:3 }, candidateNames:[id], slot:id }] }))
};
let completed = null;
const result = await context.window.ToramD4NativeClient.optimize(problem, { onComplete:value => { completed = value; } });
assert.equal(calls[0].command, 'd4_hardware_profile');
assert.equal(calls[1].command, 'd4_optimize_parallel');
assert.deepEqual(calls[1].input.problem.metadata.modeledKeys, ['DMG']);
assert.equal(result.status, 'exact');
assert.equal(result.bestBuild.packages.length, 4);
assert.equal(result.outcomes.calculation.damageFactor, 12);
assert.equal(result.engine, 'rust-native');
assert.equal(result.threadsUsed, 8);
assert.equal(result.gpuPolicy, 'cpu-only.p7');
assert.equal(completed, result);
assert.equal(context.window.ToramD4NativeClient.isRunning(), false);
const cached = await context.window.ToramD4NativeClient.optimize(problem, {});
assert.equal(cached, result, '같은 계산식·엔진·분할·스레드·GPU 정책 cache key는 native 결과를 재사용해야 합니다.');
assert.equal(calls.filter(call => call.command === 'd4_optimize_parallel').length, 1, 'native cache hit은 solver를 다시 호출하지 않아야 합니다.');
assert.equal(context.window.ToramD4NativeClient.cachePolicy.gpuPolicy, 'cpu-only.p7');

console.log('D4 native client: PASS (prepare, policy-versioned cache, native result restoration, Tauri command bridge)');
