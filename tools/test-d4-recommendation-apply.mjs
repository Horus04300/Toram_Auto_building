import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const nodes = new Map();
function node(id, value = '', checked = false) {
  const result = { id, value, checked, events:[], dispatchEvent(event) { this.events.push(event.type); return true; } };
  nodes.set(id, result);
  return result;
}
[
  ['cr_wpn_1', '현재 무기 1'], ['cr_wpn_2', '잠긴 무기'], ['cr_arm_1', '현재 방어구 1'], ['cr_arm_2', '현재 방어구 2'],
  ['cr_add_1', '잠긴 추가'], ['cr_add_2', '현재 추가 2'], ['cr_spc_1', '잠긴 특수 1'], ['cr_spc_2', '잠긴 특수 2']
].forEach(([id, value]) => node(id, value));
node('lock_wpn_1'); node('lock_wpn_2', '', true);
node('lock_arm_1'); node('lock_arm_2');
node('lock_add_1', '', true); node('lock_add_2');
node('lock_spc_1', '', true); node('lock_spc_2', '', true);
let refreshes = 0;
class FakeEvent { constructor(type, options) { this.type = type; this.bubbles = options?.bubbles; } }
const documentRef = { getElementById:id => nodes.get(id) || null, defaultView:{ Event:FakeEvent } };
const context = { window:null, document:documentRef, Event:FakeEvent, ToramApp:{ crystaUi:{ refreshAllCrystaInfo() { refreshes++; } } } };
context.window = context;
vm.createContext(context);
vm.runInContext(readFileSync(resolve(root, 'assets/js/d4-recommendation-apply.js'), 'utf8'), context, { filename:'d4-recommendation-apply.js' });

const result = {
  bestBuild:{ packages:[
    { slot:'weapon', candidateNames:['추천 무기', '잠긴 무기'] },
    { slot:'armor', candidateNames:['추천 방어구 1', '추천 방어구 2'] },
    { slot:'additional', candidateNames:['잠긴 추가', '추천 추가'] },
    { slot:'special', candidateNames:['잠긴 특수 1', '잠긴 특수 2'] }
  ] }
};
const applied = context.ToramD4RecommendationApply.apply(result, documentRef);
assert.equal(applied.changed, 4, '잠기지 않은 네 슬롯만 추천 결과로 반영해야 합니다.');
assert.equal(applied.writableSlots, 4, '잠금이 아닌 네 슬롯만 쓰기 대상으로 잡아야 합니다.');
assert.equal(nodes.get('cr_wpn_1').value, '추천 무기');
assert.equal(nodes.get('cr_wpn_2').value, '잠긴 무기', '잠긴 무기 슬롯은 유지해야 합니다.');
assert.equal(nodes.get('cr_arm_1').value, '추천 방어구 1');
assert.equal(nodes.get('cr_arm_2').value, '추천 방어구 2');
assert.equal(nodes.get('cr_add_1').value, '잠긴 추가', '잠긴 추가 슬롯은 유지해야 합니다.');
assert.equal(nodes.get('cr_add_2').value, '추천 추가');
assert.equal(nodes.get('cr_spc_1').value, '잠긴 특수 1');
assert.equal(nodes.get('cr_spc_2').value, '잠긴 특수 2');
assert.equal(nodes.get('lock_wpn_2').checked, true, '적용 과정은 잠금 체크를 변경하면 안 됩니다.');
assert.equal(nodes.get('cr_wpn_1').events.includes('change'), true, '변경된 장비 입력은 BuildDraft 동기화를 위해 change 이벤트를 내보내야 합니다.');
assert.equal(refreshes, 1, '모든 슬롯 적용 뒤 크리스타 정보를 한 번만 새로 고쳐야 합니다.');

assert.throws(() => context.ToramD4RecommendationApply.apply({ bestBuild:{ packages:[{ slot:'weapon', candidateNames:[] }] } }, documentRef), '부위별 추천이 모두 없으면 부분 적용하지 않아야 합니다.');
assert.equal(nodes.get('cr_wpn_1').value, '추천 무기', '검증 오류가 나면 어느 장비 슬롯도 부분 적용하면 안 됩니다.');
// One empty locked slot must not block the other slots or receive writes/events.
nodes.get('cr_wpn_2').value = '';
const emptyLockedResult = structuredClone(result);
emptyLockedResult.bestBuild.packages[0].candidateNames = ['새 추천 무기'];
const emptyApplied = context.ToramD4RecommendationApply.apply(emptyLockedResult, documentRef);
assert.equal(emptyApplied.changed, 1);
assert.equal(emptyApplied.writableSlots, 4);
assert.equal(nodes.get('cr_wpn_1').value, '새 추천 무기');
assert.equal(nodes.get('cr_wpn_2').value, '');
assert.equal(nodes.get('lock_wpn_2').checked, true);
assert.deepEqual(nodes.get('cr_wpn_2').events, []);

// A result that tries to fill an empty locked slot is still rejected atomically.
const overflow = structuredClone(emptyLockedResult);
overflow.bestBuild.packages[0].candidateNames = ['잘못된 추천 1', '잘못된 추천 2'];
assert.throws(() => context.ToramD4RecommendationApply.apply(overflow, documentRef), /잠금 상태/);
assert.equal(nodes.get('cr_wpn_1').value, '새 추천 무기');

// All eight slots locked empty: nothing to copy, and no change events.
const allEmpty = { bestBuild:{ packages:result.bestBuild.packages.map(p => ({ slot:p.slot, candidateNames:[] })) } };
for (const [id, item] of nodes) {
  if (id.startsWith('cr_')) { item.value = ''; item.events = []; }
  else item.checked = true;
}
const noOp = context.ToramD4RecommendationApply.apply(allEmpty, documentRef);
assert.equal(noOp.changed, 0);
assert.equal(noOp.writableSlots, 0);
for (const [id, item] of nodes) {
  if (id.startsWith('cr_')) { assert.equal(item.value, ''); assert.deepEqual(item.events, []); }
  else assert.equal(item.checked, true);
}
console.log('D4 recommendation apply: PASS (filled/empty locks preserved, no-op, atomic capacity validation)');
