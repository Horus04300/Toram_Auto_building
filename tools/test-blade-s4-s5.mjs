import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window: {}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments: () => ({ Blade: {} }) };
vm.createContext(context);

for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skills/blade.js',
  'assets/js/data/skill-registration-metadata.js',
  'assets/js/data/skill-catalog-registration.js',
  'assets/js/skill-effect-engine.js',
  'assets/js/combo-sequence-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename: path });

const effects = context.window.ToramSkillEffects;
const sequence = context.window.ToramComboSequence;
const ids = Array.from({ length: 24 }, (_, id) => `Blade:${id}`);
const restricted = new Set([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 22, 23]);
const base = (mainType = '양손검', level = 300) => ({ mainType, subType: '없음', level, strBase: 400, dexBase: 400, intBase: 100, vitBase: 300, agiBase: 300, crtBase: 50 });
const combat = { STR: 400, DEX: 400, INT: 100, VIT: 300, AGI: 300, ATK: 1000, MATK: 500, ASPD: 1000, CSPD: 1000 };
const setLevels = (value, extra = {}) => { context.window.skillSimulatorState.getInvestments = () => ({ Blade: Object.assign(Object.fromEntries(ids.map((id) => [id.split(':')[1], value])), extra) }); };
const assert = (condition, message) => { if (!condition) throw new Error(message); };
const close = (actual, expected, message) => assert(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

// 각 스킬: 정상 Lv.10 / 경계 Lv.0 / 무기 조건 변경.
setLevels(10);
for (const id of ids) assert(effects.profile(id, base(), combat, {}).available, `${id}: Lv.10 양손검에서 사용 가능해야 함`);
setLevels(0);
for (const id of ids) assert(!effects.profile(id, base(), combat, {}).available, `${id}: Lv.0에서 사용 불가여야 함`);
setLevels(10);
for (const id of ids) {
  const available = effects.profile(id, base('활'), combat, {}).available;
  assert(available === !restricted.has(Number(id.split(':')[1])), `${id}: 활 조건 판정 불일치`);
}

// 원문에서 확정한 대표 공식·효과 회귀.
setLevels(0, { 0: 10 });
close(effects.profile('Blade:0', base(), { VIT: 300 }, {}).hits[0].multiplier, 9, '해머 다운 Lv.10 계수');
setLevels(0, { 1: 10 });
const cleave = effects.profile('Blade:1', base(), { STR: 400, VIT: 300 }, { targetsHit: 4 }).hits[0];
close(cleave.multiplier, 8.5, '클리브 어택 4대상 계수');
assert(cleave.constant === 600, '클리브 어택 상수');
setLevels(0, { 17: 10, 19: 10 });
const mastery = effects.profile('Blade:0', base(), { VIT: 300 }, {});
setLevels(0, { 0: 10, 19: 10 });
const masteryHit = effects.profile('Blade:0', base(), { VIT: 300 }, {}).hits[0];
close(masteryHit.multiplier, 10.8, '장인의 검술 Lv.10 블레이드 피해 배율');
assert(masteryHit.passiveDamageModifiers.some((item) => item.source === '장인의 검술'), '장인의 검술 출처 표시');
setLevels(0, { 5: 10, 7: 10, 23: 10 });
const triggerCombo = sequence.evaluate([{ skillId: 'Blade:7', tag: 'none' }, { skillId: 'Blade:5', tag: 'none' }], base(), combat, { maxMp: 1000 });
assert(triggerCombo.entries[1].motionSpeed === 50, '트리거 슬래시 다음 스킬 행동 속도');
const firstAttackCombo = sequence.evaluate([{ skillId: 'Blade:23', tag: 'none' }, { skillId: 'Blade:7', tag: 'none' }], base(), combat, { maxMp: 1000 });
assert(firstAttackCombo.entries[1].finalMp === 100, '퍼스트 어택 Lv.10 MP 반감');
const canceled = sequence.evaluate([{ skillId: 'Blade:7', tag: 'none' }, { skillId: 'Blade:5', tag: 'none' }], base(), combat, { maxMp: 200 });
assert(canceled.entries[1].executionStatus === 'canceled', 'MP 부족 스킬 취소');

console.log('Blade S4/S5 modeled regressions: PASS');
