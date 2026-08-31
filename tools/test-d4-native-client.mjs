import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const calls = [];
let boundedMode = false;
let expiredResume = false;
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
    __TAURI__:{ core:{ Channel:function Channel() { this.onmessage = null; }, invoke:(command, input) => {
      calls.push({ command, input });
      if (command === 'd4_hardware_profile') return Promise.resolve({ logicalThreads:8 });
      if (command === 'd4_optimize_parallel') {
        input.progress.onmessage({ stage:'native-search', status:'running', lowerBound:10, upperBound:12, threadsTotal:8, threadsActive:6, readyWorkItems:42 });
        if (boundedMode) return Promise.resolve({ status:'bounded', exact:false, score:10, upperBound:12, evaluations:100, visitedNodes:40, continuationId:'d4c-test', bestBuild:{ id:'a||b||c||d', packageIds:['a','b','c','d'], statDelta:{ DMG:10 } } });
        return Promise.resolve({ status:'exact', exact:true, score:12, bestBuild:{ id:'a||b||c||d', packageIds:['a','b','c','d'], statDelta:{ DMG:12 } } });
      }
      if (command === 'resume_d4_optimization') {
        if (expiredResume) return Promise.reject(new Error('D4 재개 세션이 만료되었거나 존재하지 않습니다.'));
        input.progress.onmessage({ stage:'native-search', status:'running', lowerBound:10, upperBound:11, evaluations:120, visitedNodes:45, threadsTotal:8, threadsActive:8, readyWorkItems:21 });
        return Promise.resolve({ status:'exact', exact:true, score:12, evaluations:150, visitedNodes:60, bestBuild:{ id:'a||b||c||d', packageIds:['a','b','c','d'], statDelta:{ DMG:12 } } });
      }
      if (command === 'dispose_d4_optimization') return Promise.resolve(true);
      if (command === 'cancel_d4_optimization') return Promise.resolve(true);
      if (command === 'pause_d4_optimization') return Promise.resolve(true);
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
let progress = null;
const result = await context.window.ToramD4NativeClient.optimize(problem, { onComplete:value => { completed = value; }, onProgress:value => { progress = value; } });
assert.equal(calls[0].command, 'd4_hardware_profile');
assert.equal(calls[1].command, 'd4_optimize_parallel');
assert.deepEqual(calls[1].input.problem.metadata.modeledKeys, ['DMG']);
assert.equal(calls[1].input.options.progressIntervalMs, 100);
assert.ok(calls[1].input.options.remainingBudgetMs > 0 && calls[1].input.options.remainingBudgetMs <= 30000);
assert.equal(typeof calls[1].input.progress.onmessage, 'function');
assert.equal(progress.readyWorkItems, 42);
assert.equal(progress.threadsUsed, 8);
assert.equal(progress.optimalityGap, 0.2);
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
assert.equal(typeof context.window.ToramD4NativeClient.pause, 'function', 'native client must expose pause separately from destructive cancel');

boundedMode = true;
const continuationProblem = { ...problem, continuationMarker:'n5-resume' };
const bounded = await context.window.ToramD4NativeClient.optimize(continuationProblem, {});
assert.equal(bounded.status, 'bounded');
assert.equal(bounded.continuationId, 'd4c-test');
assert.equal(context.window.ToramD4NativeClient.hasContinuation(), true, 'bounded native result must retain its frontier token');
const nativeCallsBeforeResume = calls.filter(call => call.command === 'd4_optimize_parallel').length;
const resumeProgress = [];
const resumed = await context.window.ToramD4NativeClient.resume({ onProgress:value => resumeProgress.push(value) }, { timeLimitMs:30000 });
assert.equal(resumed.status, 'exact');
assert.equal(resumeProgress[0].evaluations, 100, '정밀 계산 첫 화면은 이전 bounded의 누적 evaluation을 유지해야 합니다.');
assert.equal(resumeProgress.at(-1).evaluations, 120, 'native resume progress는 같은 누적 counter를 이어야 합니다.');
assert.equal(calls.filter(call => call.command === 'd4_optimize_parallel').length, nativeCallsBeforeResume, '정밀 계산은 새 optimize command를 호출하면 안 됩니다.');
const resumeCall = calls.find(call => call.command === 'resume_d4_optimization');
assert.equal(resumeCall.input.continuationId, 'd4c-test');
assert.ok(resumeCall.input.options.remainingBudgetMs > 0 && resumeCall.input.options.remainingBudgetMs <= 30000);
assert.equal(context.window.ToramD4NativeClient.hasContinuation(), false, 'exact 종료 뒤 continuation을 남기면 안 됩니다.');

const expiringProblem = { ...problem, continuationMarker:'n5-expired' };
await context.window.ToramD4NativeClient.optimize(expiringProblem, {});
expiredResume = true;
await assert.rejects(
  () => context.window.ToramD4NativeClient.resume({}, { timeLimitMs:30000 }),
  error => error && error.code === 'D4_CONTINUATION_UNAVAILABLE',
  '만료된 세션은 Worker 재시작으로 대체하지 않고 명시 오류가 되어야 합니다.',
);
assert.equal(context.window.ToramD4NativeClient.hasContinuation(), false);

console.log('D4 native client: PASS (prepare, cache, native result restoration, continuation resume, expiry handling)');
