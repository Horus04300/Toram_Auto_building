import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { existsSync, writeFileSync } from 'node:fs';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const context = { window:{}, console };
context.window.window = context.window;
context.window.ToramSkillEffects = {
  profile(id) {
    const cost = Number(id.split(':')[1]);
    return {
      skill:{ id, nameKo:id, treeId:'Test', kind:'attack', combo:{ canStart:true, canReceiveTag:true } },
      available:true,
      cost:{ mp:cost },
      hits:[{ id:'hit', multiplier:1, constant:0, flags:{} }],
      effects:[],
      stateTransitions:[]
    };
  }
};
vm.createContext(context);
for (const path of ['assets/js/data/combo-rule-data.js', 'assets/js/combo-sequence-engine.js']) {
  vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });
}

const Q = context.window.ToramComboSequence;
const base = {};
const combat = { MAXHP:10000 };
const close = (actual, expected, message) => assert.ok(Math.abs(actual - expected) < 1e-9, message + ': expected ' + expected + ', got ' + actual);
const entries = (costs, tags) => costs.map((cost, index) => ({ skillId:'Test:' + cost, tag:tags[index] || 'none' }));

let result = Q.evaluate(entries([100, 300, 200, 200, 200, 200], ['none', 'charge']), base, combat, { maxMp:1000, maxHp:10000 });
assert.equal(result.entries[1].chargeStoredMp, 300, '충전은 태그 스킬의 기본 MP를 저장해야 합니다.');
assert.equal(result.entries[2].storedMpUsed, 200, '충전 MP는 다음 스킬 비용에 먼저 사용해야 합니다.');
close(result.entries[2].damageMultiplier, .2, '충전 직후 스킬에는 80% 피해 감소를 적용해야 합니다.');
close(result.entries[3].damageMultiplier, .4, '충전 두 번째 후속 스킬에는 60% 피해 감소를 적용해야 합니다.');
close(result.entries[4].damageMultiplier, .6, '충전 세 번째 후속 스킬에는 40% 피해 감소를 적용해야 합니다.');
close(result.entries[5].damageMultiplier, .8, '충전 네 번째 후속 스킬에는 20% 피해 감소를 적용해야 합니다.');

result = Q.evaluate(entries([100, 300, 100], ['none', 'charge']), base, combat, { maxMp:1000, maxHp:10000 });
assert.equal(result.chargeSettlementMp, 200, '콤보 종료 시 남은 충전 MP를 정산해야 합니다.');
assert.equal(result.remainingMp, 700, '충전 잔여 MP 정산은 최종 잔여 MP에 반영해야 합니다.');

result = Q.evaluate(entries([100, 300, 100, 100], ['none', 'charge', 'charge']), base, combat, { maxMp:1000, maxHp:10000 });
assert.equal(result.entries[2].discardedStoredMp, 300, '새 충전은 이전 저장 MP를 덮어써야 합니다.');
assert.equal(result.entries[3].damageMultiplier, .1, '겹친 충전 피해 감소는 공통 최저 10% 상한을 적용해야 합니다.');

result = Q.evaluate(entries([100, 500], ['none', 'tenacity']), base, combat, { maxMp:300, maxHp:10000 });
assert.equal(result.canceledAt, null, '집념은 MP 부족으로 취소되기 전에 HP 대체를 적용해야 합니다.');
assert.equal(result.entries[1].mpAfter, 0, '집념은 남은 MP를 먼저 모두 사용해야 합니다.');
assert.equal(result.entries[1].hpCost, 3000, '집념은 부족한 300 MP를 최대 HP의 30%로 전환해야 합니다.');

result = Q.evaluate(entries([100, 100], ['none', 'mindsEye']), base, combat, { maxMp:1000, maxHp:10000 });
assert.equal(result.entries[1].absoluteHit, true, '심안은 절대 명중을 결과에 기록해야 합니다.');
assert.equal(result.entries[1].hitBonus, 20, '심안은 콤보 위치당 명중 +10을 적용해야 합니다.');
assert.equal(result.entries[1].hits[0].flags.guaranteedHit, true, '심안 절대 명중은 타격 플래그에 연결해야 합니다.');
assert.equal(result.entries[1].hits[0].flags.hitBonus, 20, '심안 명중 보정은 타격 플래그에 연결해야 합니다.');

console.log('Combo charge, tenacity, and mind\'s eye regressions: PASS');
