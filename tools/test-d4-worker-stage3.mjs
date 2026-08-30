import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));
const workerClientApi = require(resolve(root, 'assets/js/d4-worker-client.js'));

function pkg(id, slot, score) {
  return Object.freeze({ id, slot, statDelta:Object.freeze({ ATKP:score }), candidateNames:[id], evaluatorCandidates:[] });
}

function outcome(stats) {
  const score = Number(stats.ATKP) || 0;
  return { damage:{ expected:score }, constraints:{ feasible:true, violations:[] } };
}

const smallProblem = Object.freeze({
  schema:'toram.d4-crysta-problem.v1', baseContext:{}, scenarioSnapshot:{ requirements:{} }, diagnostics:[], metadata:{},
  groups:Object.freeze([
    Object.freeze({ id:'weapon', packages:Object.freeze([pkg('w1','weapon',1), pkg('w2','weapon',2)]) }),
    Object.freeze({ id:'armor', packages:Object.freeze([pkg('a1','armor',3), pkg('a2','armor',4)]) }),
    Object.freeze({ id:'additional', packages:Object.freeze([pkg('d1','additional',5), pkg('d2','additional',6)]) })
  ])
});

const progress = [];
const exact = optimizer.optimize(smallProblem, {
  evaluateStats:outcome,
  relevantKeys:['ATKP'],
  onProgress:snapshot => progress.push(snapshot),
  progressIntervalMs:1
});
assert.equal(exact.status, 'exact', '작은 문제는 Worker용 진행 콜백을 사용해도 정확해여야 합니다.');
assert.equal(exact.score, 12, '각 그룹의 최고 후보를 합친 전역 점수가 나와야 합니다.');
assert.ok(progress.length >= 2, '탐색 시작과 완료 진행 스냅샷을 전달해야 합니다.');
assert.equal(progress.at(-1).stage, 'exact', '마지막 진행 스냅샷은 exact 상태여야 합니다.');

let cancelChecks = 0;
const cancelled = optimizer.optimize(smallProblem, {
  evaluateStats:outcome,
  relevantKeys:['ATKP'],
  shouldCancel:() => ++cancelChecks >= 1
});
assert.equal(cancelled.status, 'cancelled', '취소 토큰은 cancelled 상태를 반환해야 합니다.');
assert.ok(cancelled.bestBuild, '취소되더라도 빠른 초기 유효해를 보존해야 합니다.');

let workerCount = 0;
const workerMessages = [];
class FakeWorker {
  constructor() { workerCount++; this.terminated = false; }
  postMessage(message) {
    workerMessages.push(message);
    queueMicrotask(() => this.onmessage({ data:{ type:'progress', version:message.version, progress:{ status:'running', evaluations:3 } } }));
    queueMicrotask(() => this.onmessage({ data:{ type:'result', version:message.version, result:{ status:'exact', score:12, bestBuild:{ id:'cached' }, evaluations:8, optimalityGap:0 } } }));
  }
  terminate() { this.terminated = true; }
}

const client = new workerClientApi.WorkerClient({ WorkerConstructor:FakeWorker, workerUrl:'fake-worker.js' });
let progressSeen = 0;
const first = await client.optimize(smallProblem, { onProgress:() => progressSeen++ });
assert.equal(first.status, 'exact', 'Worker 결과를 클라이언트가 전달해야 합니다.');
assert.equal(progressSeen, 1, 'Worker 진행 메시지를 UI 콜백에 전달해야 합니다.');
assert.equal(workerMessages[0].options.enableDynamicSeedIncumbent, true, 'S7 approved Worker default must enable the dynamic seed incumbent.');
assert.equal(workerMessages[0].options.enableDynamicSeedOrdering, true, 'S7 approved Worker default must enable deterministic split tie ordering.');
assert.equal(workerMessages[0].options.dynamicSeedTimeLimitMs, 1500, 'S7 default must preserve the measured seed time budget.');
const second = await client.optimize(smallProblem);
assert.equal(second.status, 'exact', '같은 스냅샷은 캐시 결과를 반환해야 합니다.');
assert.equal(workerCount, 1, '같은 문제의 두 번째 실행은 Worker를 다시 만들지 않아야 합니다.');
const precise = await client.optimize(smallProblem, {}, { timeLimitMs:30000 });
assert.equal(precise.status, 'exact', '정밀 계산도 정상 결과를 반환해야 합니다.');
assert.equal(workerCount, 2, '서로 다른 시간 예산은 같은 캐시 항목으로 취급하면 안 됩니다.');

class SilentWorker {
  postMessage() {}
  terminate() { this.terminated = true; }
}
const cancellingClient = new workerClientApi.WorkerClient({ WorkerConstructor:SilentWorker });
const pending = cancellingClient.optimize(smallProblem);
assert.equal(cancellingClient.cancel('test cancel'), true, '실행 중 Worker는 취소할 수 있어야 합니다.');
assert.equal((await pending).status, 'cancelled', 'Worker 종료 결과는 cancelled 상태여야 합니다.');

assert.equal(workerClientApi.problemCacheKey(smallProblem), workerClientApi.problemCacheKey(smallProblem), '캐시 키는 결정적이어야 합니다.');
const hardwareProfile = await workerClientApi.getParallelHardwareProfile();
assert.equal(hardwareProfile.schema, 'toram.d4-hardware-profile.v1', 'P3 하드웨어 profile은 고정 schema를 반환해야 합니다.');
assert.ok(hardwareProfile.logicalThreads >= 1, 'P3 하드웨어 profile은 최소 하나의 논리 스레드를 반환해야 합니다.');
assert.ok(hardwareProfile.initialShardTarget >= hardwareProfile.logicalThreads, 'P3 shard 목표는 감지된 스레드 수보다 작으면 안 됩니다.');
let parallelWorkerCount = 0;
const parallelMessages = [];
class FakeParallelWorker {
  constructor() { parallelWorkerCount++; this.terminated = false; }
  postMessage(message) {
    parallelMessages.push(message);
    if (message.type === 'prepare-parallel') {
      const plan = { schema:optimizer.parallelShardSchema, status:'ready', shards:[
        { id:'p0', upper:12 }, { id:'p1', upper:12 }, { id:'p2', upper:12 }, { id:'p3', upper:12 }
      ] };
      queueMicrotask(() => this.onmessage({ data:{ type:'parallel-plan', version:message.version, plan } }));
      return;
    }
    if (message.type === 'parallel-init') {
      queueMicrotask(() => this.onmessage({ data:{ type:'parallel-ready', version:message.version } }));
      return;
    }
    if (message.type === 'optimize-parallel-shard') {
      const shardId = message.shardId;
      queueMicrotask(() => this.onmessage({ data:{ type:'parallel-shard-progress', version:message.version, shardId, progress:{ status:'running', lowerBound:10, upperBound:12, evaluations:3, visitedNodes:1 } } }));
      queueMicrotask(() => this.onmessage({ data:{ type:'parallel-shard-result', version:message.version, shardId, result:{ status:'exact', score:12, lowerBound:12, upperBound:12, bestBuild:{ id:`best-${shardId}` }, evaluations:8, visitedNodes:2, elapsedMs:1 } } }));
      return;
    }
    if (message.type === 'merge-parallel') {
      queueMicrotask(() => this.onmessage({ data:{ type:'parallel-result', version:message.version, result:{ status:'exact', score:12, lowerBound:12, upperBound:12, bestBuild:{ id:'best-p0' }, evaluations:32, visitedNodes:8, optimalityGap:0 } } }));
    }
  }
  terminate() { this.terminated = true; }
}

const parallelClient = new workerClientApi.ParallelWorkerClient({ WorkerConstructor:FakeParallelWorker, workerUrl:'fake-parallel-worker.js', hardwareConcurrency:2 });
let parallelProgressSeen = 0;
const parallel = await parallelClient.optimize(smallProblem, { onProgress:() => parallelProgressSeen++ }, { timeLimitMs:1000, parallelShardFactor:2 });
assert.equal(parallel.status, 'exact', 'P1 Worker pool은 planner·shard 결과를 병합해 완료 결과를 반환해야 합니다.');
assert.equal(parallel.workerThreads, 2, 'P1 Worker pool은 감지된 논리 스레드 수만큼 shard Worker를 사용해야 합니다.');
assert.equal(parallel.totalShards, 4, 'P1 Worker pool은 스레드 수와 shard factor를 곱한 작업 단위를 사용해야 합니다.');
assert.ok(parallelProgressSeen > 0, 'P1 Worker pool은 병합 진행 상태를 UI에 전달해야 합니다.');
assert.equal(parallelWorkerCount, 3, 'P1 실행은 planner 하나와 감지된 수의 shard Worker를 만들어야 합니다.');
assert.ok(parallelMessages.some(message => message.type === 'prepare-parallel' && message.targetShards === 4), 'planner는 동적으로 계산한 target shard 수를 받아야 합니다.');
assert.equal(workerClientApi.resolveParallelWorkerCount({ hardwareConcurrency:7 }), 7, '명시된 하드웨어 프로필은 동적으로 Worker 수에 반영해야 합니다.');

class SilentParallelWorker {
  postMessage() {}
  terminate() { this.terminated = true; }
}
const cancellingParallelClient = new workerClientApi.ParallelWorkerClient({ WorkerConstructor:SilentParallelWorker, hardwareConcurrency:4 });
const pendingParallel = cancellingParallelClient.optimize(smallProblem);
assert.equal(cancellingParallelClient.cancel('parallel test cancel'), true, 'P1 Worker pool도 실행 중 전체 Worker를 취소할 수 있어야 합니다.');
assert.equal((await pendingParallel).status, 'cancelled', 'P1 Worker pool 취소는 cancelled 결과를 반환해야 합니다.');
console.log('D4 Worker stage 3 regressions: PASS (progress, cancellation, cache, deterministic key)');
