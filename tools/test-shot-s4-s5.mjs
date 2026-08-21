import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window: {}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments: () => ({ Shot: {} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js', 'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-data.js', 'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skills/shot.js', 'assets/js/data/skill-registration-metadata.js',
  'assets/js/data/skill-catalog-registration.js', 'assets/js/skill-effect-engine.js', 'assets/js/combo-sequence-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });

const effects = context.window.ToramSkillEffects;
const ids = Array.from({ length:25 }, (_, id) => `Shot:${id}`);
const base = (mainType = '활', subType = '없음') => ({ mainType, subType, level:300, strBase:400, dexBase:500, intBase:100, vitBase:200, agiBase:300, crtBase:50 });
const combat = { STR:400, DEX:500, INT:100, VIT:200, AGI:300, ATK:1000, MATK:500, AMPR:30 };
const setLevels = (value, extra = {}) => { context.window.skillSimulatorState.getInvestments = () => ({ Shot:Object.assign(Object.fromEntries(ids.map((id) => [id.slice(5), value])), extra) }); };
const assert = (condition, message) => { if (!condition) throw new Error(message); };
const close = (actual, expected, message) => assert(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

setLevels(10);
for (const id of ids) {
  const available = effects.profile(id, base(), combat, {}).available;
  assert(available === !new Set([7, 21]).has(Number(id.slice(5))), `${id}: 활 조건 판정 불일치`);
}
setLevels(10);
for (const id of ids) {
  const available = effects.profile(id, base('자동활'), combat, {}).available;
  assert(available === !new Set([8, 21]).has(Number(id.slice(5))), `${id}: 자동활 조건 판정 불일치`);
}
assert(effects.profile('Shot:21', base('활', '발도검'), combat, {}).available, '무사 궁술: 서브 발도검에서 사용 가능해야 함');
setLevels(0);
for (const id of ids) assert(!effects.profile(id, base(), combat, {}).available, `${id}: Lv.0에서 사용 불가여야 함`);
setLevels(0, { 0:10 });
let profile = effects.profile('Shot:0', base(), combat, {});
close(profile.hits[0].multiplier, 1.75, '파워 슈트 Lv.10 계수');
assert(profile.hits[0].constant === 130, '파워 슈트 Lv.10 상수');
setLevels(0, { 1:10 });
profile = effects.profile('Shot:1', base('자동활'), combat, {});
close(profile.hits[1].multiplier, .75, '윈 휠 자동활 Lv.10 2타 계수');
assert(profile.hits[2].flags.physicalPierceBonus.op === 'add', '윈 휠 3타 관통 규칙');
setLevels(0, { 2:10 });
profile = effects.profile('Shot:2', base(), combat, {});
assert(profile.hits[0].count === 8, '애로 레인 활 Lv.10 8타');
close(profile.hits[0].multiplier, 1.3, '애로 레인 Lv.10 계수');
setLevels(0, { 14:10 });
profile = effects.profile('Shot:14', base(), combat, {});
assert(profile.hits.length === 2 && profile.hits[0].constant === 400 && profile.hits[1].constant === 400, '파라볼라 캐논 포탄·지뢰');
setLevels(0, { 24:10 });
profile = effects.profile('Shot:24', base(), combat, {});
close(profile.hits[0].multiplier, 10.5, '디스트럭트 샷 Lv.10 계수');

setLevels(0, { 0:10, 4:1, 7:10, 9:10 });
profile = effects.profile('Shot:4', base(), combat, { charge:5 });
assert(profile.hits[0].multiplier > 0 && profile.hits[1].count === 1, '크로스 파이어 Lv.1 차지 상한 2');
profile = effects.profile('Shot:0', base('자동활'), combat, {}, { activeBuffs:{ 'Shot:7':{ active:true, stacks:50 } } });
close(profile.hits[0].multiplier, 2.1, '트윈 스톰 50스택 슛 피해 +20%');
const sequence = context.window.ToramComboSequence;
const combo = sequence.evaluate([{ skillId:'Shot:9', tag:'none', inputs:{ recastWhileActive:true } }, { skillId:'Shot:0', tag:'none' }], base(), combat, { maxMp:1000 });
assert(combo.entries[0].finalMp === 400 && combo.entries[0].mpRefund === 200 && combo.entries[0].mpAfter === 800, '퀵 로더 재사용 MP 반환');
assert(combo.entries[1].motionSpeed === 50, '퀵 로더 Lv.10 다음 스킬 행동 속도');
const canceled = sequence.evaluate([{ skillId:'Shot:9', tag:'none', inputs:{ recastWhileActive:true } }, { skillId:'Shot:0', tag:'none' }], base(), combat, { maxMp:300 });
assert(canceled.entries[0].executionStatus === 'canceled', '퀵 로더는 반환 전 400MP 부족 시 취소');
const twinCombo = sequence.evaluate([{ skillId:'Shot:0', tag:'none' }], base('자동활'), combat, { maxMp:1000, activeBuffs:{ 'Shot:7':{ active:true, stacks:50 } } });
close(twinCombo.entries[0].hits[0].effectiveMultiplier, 2.1, '트윈 스톰 활성 피해가 콤보 공격에 반영');
console.log('Shot S4/S5 modeled regressions: PASS');
