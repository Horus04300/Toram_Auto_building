import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const pairs = require(resolve(root, 'assets/js/d4-pair-partition.js'));

function group(id,count) {
  return Object.freeze({ id, packages:Object.freeze(Array.from({ length:count }, (_, index) => Object.freeze({ id:id + '-' + index, statDelta:Object.freeze({}) }))) });
}
function problem(counts) {
  return Object.freeze({ groups:Object.freeze(['weapon','armor','additional','special'].map(id => group(id, counts[id]))) });
}
function supply() {
  return Object.freeze({ utilities:Object.freeze({
    maxMp:Object.freeze({ active:true, residual:10, groupMaximums:Object.freeze([
      Object.freeze({ groupId:'armor', maximum:4 }), Object.freeze({ groupId:'special', maximum:6 })
    ]) }),
    amprBeforeDual:Object.freeze({ active:true, residual:10, groupMaximums:Object.freeze([
      Object.freeze({ groupId:'weapon', maximum:4 }), Object.freeze({ groupId:'additional', maximum:6 })
    ]) })
  }) });
}

const raw = problem({ weapon:100, armor:120, additional:80, special:90 });
const prepared = problem({ weapon:20, armor:18, additional:15, special:16 });
const first = pairs.analyzePairPartitions(raw, supply(), { preparedProblem:prepared, pairMaterializationLimit:250 });
const second = pairs.analyzePairPartitions(raw, supply(), { preparedProblem:prepared, pairMaterializationLimit:250 });

assert.equal(first.status, 'ok', '네 부위가 있으면 Pair 분석이 가능해야 합니다.');
assert.equal(first.policyVersion, 'd4-pair-partition.v1', '정책 버전을 노출해야 합니다.');
assert.deepEqual(first.rawGroupCounts, { weapon:100, armor:120, additional:80, special:90 }, '원시 부위 후보 수를 보존해야 합니다.');
assert.deepEqual(first.preparedGroupCounts, { weapon:20, armor:18, additional:15, special:16 }, 'Pareto 뒤 부위 후보 수를 구분해야 합니다.');
assert.equal(first.selection.id, 'armor-special__weapon-additional', '같은 Pair 안에서 MP·AMPR을 충족하는 분할을 우선해야 합니다.');
assert.equal(first.selection.mode, 'lazy-box', '한 Pair라도 제한을 넘으면 전체 물질화를 허용하면 안 됩니다.');
assert.equal(first.partitions[0].splitUtilityCount, 0, '선택 Pair는 각 활성 Utility를 한쪽 Pair에서 충족해야 합니다.');
assert.equal(first.partitions[0].pairs[0].preparedCandidateCount, 288, 'Pair 후보 수는 Pareto 뒤 두 부위 후보 수의 곱이어야 합니다.');
assert.deepEqual(first, second, '입력 순서와 무관하게 동일 입력은 결정적으로 같은 보고서를 반환해야 합니다.');

const materializable = pairs.analyzePairPartitions(raw, supply(), { preparedProblem:prepared, pairMaterializationLimit:1000 });
assert.equal(materializable.selection.mode, 'materialize', '모든 Pair가 제한 아래면 Gate D 측정을 위해 물질화를 허용해야 합니다.');
assert.equal(materializable.partitions[0].frontierStatus, 'not-measured', 'Gate C는 Frontier 크기를 추정하지 않고 Gate D 측정으로 남겨야 합니다.');

const invalid = pairs.analyzePairPartitions({ groups:[group('weapon', 1)] }, supply());
assert.equal(invalid.status, 'invalid', '필수 부위가 없으면 보수적으로 분석을 거부해야 합니다.');
assert.deepEqual(invalid.missingGroups, ['armor','additional','special'], '누락 부위를 명확히 보고해야 합니다.');

console.log('D4 pair partition: PASS');
