import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
require(resolve(root, 'assets/js/d4-pair-partition.js'));
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));

function pkg(id, stats) {
  return Object.freeze({ id, slot:id.split(':')[0], statDelta:Object.freeze(stats), candidateNames:[id] });
}
function problem(size) {
  const values = Array.from({ length:size }, (_, index) => index + 1);
  return Object.freeze({
    schema:'pair-frontier-fixture',
    baseContext:{ atkType:'PHYS', rangeType:'SHORT' },
    scenarioSnapshot:{ requirements:{} },
    metadata:{},
    diagnostics:[],
    groups:Object.freeze([
      Object.freeze({ id:'weapon', packages:Object.freeze(values.map(value => pkg('weapon:' + value, { A:value, B:size - value }))) }),
      Object.freeze({ id:'armor', packages:Object.freeze(values.map(value => pkg('armor:' + value, { A:size - value, B:value }))) }),
      Object.freeze({ id:'additional', packages:Object.freeze(values.map(value => pkg('additional:' + value, { A:value * 2 }))) }),
      Object.freeze({ id:'special', packages:Object.freeze(values.map(value => pkg('special:' + value, { B:value * 2 }))) })
    ])
  });
}
function evaluateStats(stats) {
  const a = Number(stats.A) || 0;
  const b = Number(stats.B) || 0;
  return {
    damage:{ expected:a * b + a + b },
    offense:{ normalAttackCrit:100 },
    utility:{ maxHp:0, maxMpBeforeBuff:0, amprBeforeDual:0, aspd:0 },
    constraints:{ feasible:true, violations:[] }
  };
}
function solve(input, options={}) {
  return optimizer.optimize(input, Object.assign({
    evaluateStats,
    relevantKeys:['A','B'],
    timeLimitMs:5000,
    pairFrontierMaterializationLimit:16,
    pairSeedPerGroup:3,
    smallBoxEnumerationLimit:128
  }, options));
}

const small = problem(3);
const smallOracle = optimizer.exhaustiveSearch(small, { evaluateStats, relevantKeys:['A','B'] });
const smallSolved = solve(small);
assert.equal(smallSolved.status, 'exact', '작은 Pair Frontier 문제는 exact여야 합니다.');
assert.equal(smallSolved.score, smallOracle.score, 'Pair Frontier 하한을 써도 oracle 최적값과 같아야 합니다.');
assert.equal(smallSolved.bestBuild.id, smallOracle.bestBuild.id, 'Pair Frontier를 써도 동점 ID 규칙을 보존해야 합니다.');
assert.equal(smallSolved.pairFrontierReports.length, 2, '선택 분할의 두 Pair를 모두 측정해야 합니다.');
assert.ok(smallSolved.pairFrontierReports.every(report => report.mode === 'materialized-frontier' && report.frontierComplete), '작은 Pair는 완결 Pareto Frontier로만 축약해야 합니다.');

const smallPairCorrelationAudit = optimizer.verifyPairCorrelationUpperBounds(small, { evaluateStats, relevantKeys:["A","B"], pairCorrelationClustersPerGroup:2 });
assert.equal(smallPairCorrelationAudit.violations.length, 0, "Pair correlation boxes must not underestimate an included completion.");
assert.equal(smallPairCorrelationAudit.checked, 4, "A 2x2 Pair correlation partition must audit four complete boxes.");
const smallCorrelated = solve(small, { enablePairCorrelationBounds:true, pairCorrelationClustersPerGroup:2 });
assert.equal(smallCorrelated.status, "exact", "Partitioned Pair correlation boxes must preserve exact search.");
assert.equal(smallCorrelated.score, smallOracle.score, "Partitioned Pair correlation boxes must preserve the oracle score.");
assert.equal(smallCorrelated.bestBuild.id, smallOracle.bestBuild.id, "Partitioned Pair correlation boxes must preserve deterministic ties.");
assert.equal(smallCorrelated.pairCorrelationReport.scheduledBoxCount, 4, "A 2x2 Pair correlation partition must enter four disjoint root boxes into the queue.");
const smallGuided = solve(small, { enableBoundGuidedSplit:true, boundGuidedSplitLevels:2 });
assert.equal(smallGuided.status, "exact", "Bound-guided splitting must preserve exact search.");
assert.equal(smallGuided.score, smallOracle.score, "Bound-guided splitting must preserve the oracle score.");
assert.equal(smallGuided.bestBuild.id, smallOracle.bestBuild.id, "Bound-guided splitting must preserve deterministic ties.");
const smallStream = solve(small, { enablePairStreamBounds:true, pairStreamPivotKey:"A", pairStreamBucketCount:2 });
assert.equal(smallStream.status, "exact", "Streamed Pair envelopes must preserve exact search.");
assert.equal(smallStream.score, smallOracle.score, "Streamed Pair envelopes must preserve the oracle score.");
assert.equal(smallStream.bestBuild.id, smallOracle.bestBuild.id, "Streamed Pair envelopes must preserve deterministic ties.");
assert.ok(smallStream.pairStreamReport && smallStream.pairStreamReport.pairReports.every(report => report.nonemptyBuckets > 0), "Streamed Pair envelopes must report nonempty safe buckets.");
const large = problem(5);
const largeOracle = optimizer.exhaustiveSearch(large, { evaluateStats, relevantKeys:['A','B'] });
const largeDeferred = solve(large);
assert.equal(largeDeferred.status, 'exact', '기본 큰 Pair 보류도 전체 탐색의 exact를 유지해야 합니다.');
assert.equal(largeDeferred.score, largeOracle.score, '보류 분기는 oracle 최적값을 바꾸면 안 됩니다.');
assert.ok(largeDeferred.pairFrontierReports.every(report => report.mode === 'lazy-deferred' && report.evaluatedCandidateCount === 0), '효과가 검증되지 않은 큰 Pair 시드는 기본으로 평가하면 안 됩니다.');

const largeSolved = solve(large, { enableLazyPairSeeds:true });
assert.equal(largeSolved.status, 'exact', '지연 Pair 시드가 있어도 전체 탐색은 exact를 증명해야 합니다.');
assert.equal(largeSolved.score, largeOracle.score, '지연 Pair 시드는 하한 전용이므로 최적값을 바꾸면 안 됩니다.');
assert.equal(largeSolved.bestBuild.id, largeOracle.bestBuild.id, '지연 Pair 시드도 결정적 동점 결과를 보존해야 합니다.');
assert.ok(largeSolved.pairFrontierReports.every(report => report.mode === 'lazy-seed' && report.frontierInputCount === null), '큰 Pair는 전체 Frontier를 만들지 않고 지연 시드로만 처리해야 합니다.');

console.log('D4 pair frontier: PASS');
