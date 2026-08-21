import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window: {}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments: () => ({ Priest: {} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/priest-s5.js',
  'assets/js/skill-effect-engine.js',
  'assets/js/combo-sequence-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename: path });

const E = context.window.ToramSkillEffects;
const Q = context.window.ToramComboSequence;
const ids = Array.from({ length: 15 }, (_, index) => `Priest:${index}`);
const base = (mainType = '지팡이', subType = '방패') => ({
  mainType, subType, level: 300,
  strBase: 100, dexBase: 100, intBase: 100, vitBase: 100, agiBase: 100, crtBase: 50
});
const combat = { STR: 120, DEX: 130, INT: 120, VIT: 100, AGI: 110, ATK: 1000, MATK: 400, MAXHP: 10000 };
const levels = (value, extra = {}) => {
  context.window.skillSimulatorState.getInvestments = () => ({ Priest: { ...Object.fromEntries(ids.map(id => [id.slice(7), value])), ...extra } });
};
const ok = (condition, message) => { if (!condition) throw new Error(message); };
const close = (actual, expected, message) => ok(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

levels(10);
for (const id of ids) ok(E.profile(id, base(), combat, {}).available, `${id} Lv10 지팡이+방패`);
levels(0);
for (const id of ids) ok(!E.profile(id, base(), combat, {}).available, `${id} Lv0`);

levels(0, { 1: 10, 5: 10, 6: 10, 7: 10, 8: 10, 10: 10, 11: 10, 13: 10, 14: 10 });
let profile = E.profile('Priest:1', base(), combat, {});
close(profile.effects.find(effect => effect.key === 'DEF_P').value, 200, '글로리아 Lv10 DEF%');
profile = E.profile('Priest:8', base(), combat, {});
close(profile.effects.find(effect => effect.key === 'MATKP').value, 10, '프리엘 Lv10 MATK%');
profile = E.profile('Priest:7', base(), combat, {});
close(profile.effects.find(effect => effect.key === 'MATKP').value, -5, '에테르 코드 Lv10 MATK% 페널티');
profile = E.profile('Priest:5', base(), combat, {});
close(profile.hits[0].multiplier, 1, '홀리 피스트 Lv10 지팡이 물리 계수');
close(profile.hits[1].multiplier, 3.2, '홀리 피스트 Lv10 지팡이 마법 계수');
close(profile.hits[0].constant, 100, '홀리 피스트 Lv10 상수');
profile = E.profile('Priest:6', base(), combat, {});
close(profile.hits[0].multiplier, 7.5, '홀리 라이트 Lv10 지팡이 계수');
ok(profile.cost.mp === 200, '홀리 라이트 MP');
profile = E.profile('Priest:10', base(), combat, {});
close(profile.hits[0].multiplier, 3.2, '로드 스터프 Lv10 계수');
close(profile.hits[0].constant, 100, '로드 스터프 상수');
profile = E.profile('Priest:11', base(), combat, { targetDark: false });
close(profile.hits[0].multiplier, 2.45, '엑소시즘 Lv10 기본 계수');
close(profile.hits[0].constant, 100, '엑소시즘 Lv10 기본 상수');
profile = E.profile('Priest:11', base(), combat, { targetDark: true });
close(profile.hits[0].multiplier, 6.45, '엑소시즘 Lv10 어둠 강화 계수');
close(profile.hits[0].constant, 200, '엑소시즘 Lv10 어둠 강화 상수');
profile = E.profile('Priest:13', base(), combat, { nemesisActive: true, nemesisStacks: 10 });
close(profile.hits[0].multiplier, 11.2, '네메시스 방패 STR 보정 계수');
close(profile.hits[0].constant, 600, '네메시스 Lv10 물리 상수');
ok(profile.hits[1].count === 10, '네메시스 신벌 스택 마법진 타수');
close(profile.hits[1].multiplier, 5.6, '네메시스 마법진 계수');
ok(!E.profile('Priest:10', base('한손검', '없음'), combat, {}).available, '로드 스터프 지팡이 전용');
ok(!E.profile('Priest:12', base('양손검', '없음'), combat, {}).available, '홀리 바이블 무기 조건');
let result = Q.evaluate([{ skillId: 'Priest:11', inputs: { targetDark: true }, tag: 'none' }, { skillId: 'Priest:5', tag: 'none' }], base(), combat, { maxMp: 1000 });
ok(result.entries[1].finalMp === 50, '엑소시즘 다음 스킬 MP 반감');
result = Q.evaluate([{ skillId: 'Priest:14', tag: 'none' }, { skillId: 'Priest:6', tag: 'none' }], base(), combat, { maxMp: 1000 });
ok(result.entries[1].finalMp === 100, '홀리 그레이스 다음 스킬 MP 반감');

console.log('Priest S1-S5 calculator-scope regressions: PASS');
