import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window: {}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments: () => ({ Shield: {} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/shield-s5.js',
  'assets/js/skill-effect-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename: path });

const E = context.window.ToramSkillEffects;
const ids = Array.from({ length: 13 }, (_, index) => `Shield:${index}`);
const base = (subType = '방패', subRefine = 5) => ({
  mainType: '한손검', subType, subRefine, level: 300,
  strBase: 100, dexBase: 100, intBase: 100, vitBase: 100, agiBase: 100, crtBase: 50
});
const combat = { STR: 120, DEX: 130, INT: 120, VIT: 100, AGI: 110, ATK: 1000, MATK: 400, MAXHP: 10000 };
const levels = (value, extra = {}) => {
  context.window.skillSimulatorState.getInvestments = () => ({ Shield: { ...Object.fromEntries(ids.map(id => [id.slice(7), value])), ...extra } });
};
const ok = (condition, message) => { if (!condition) throw new Error(message); };
const close = (actual, expected, message) => ok(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

levels(10);
for (const id of ids) ok(E.profile(id, base(), combat, id === 'Shield:9' ? { dualShieldActive: true } : {}).available, `${id} Lv10 방패`);
levels(0);
for (const id of ids) ok(!E.profile(id, base(), combat, {}).available, `${id} Lv0`);

levels(0, { 1: 10, 2: 10, 6: 10, 9: 10, 10: 10, 11: 10 });
let profile = E.profile('Shield:1', base(), combat, {});
ok(profile.cost.mp === 100, '실드 배쉬 MP');
close(profile.hits[0].multiplier, 0.15, '실드 배쉬 Lv10 계수');
close(profile.hits[0].constant, 100, '실드 배쉬 Lv10 상수');
profile = E.profile('Shield:2', base(), combat, { stunSuccess: false });
close(profile.hits[0].multiplier, 1.5, '실드 캐논 Lv10 기본 계수');
close(profile.hits[0].constant, 200, '실드 캐논 Lv10 기본 상수');
profile = E.profile('Shield:2', base('방패', 5), combat, { stunSuccess: true });
close(profile.hits[0].multiplier, 7.5, '실드 캐논 기절·제련 강화 계수');
close(profile.hits[0].constant, 200 + 100 * 5 / 3, '실드 캐논 기절·제련 강화 상수');
profile = E.profile('Shield:6', base('방패', 5), combat, { tumbleSuccess: true });
close(profile.hits[0].multiplier, 2, '실드 어퍼컷 넘어짐 강화 계수');
profile = E.profile('Shield:9', base('방패', 5), combat, { dualShieldActive: true, targetIncapacitated: true });
ok(profile.hits[0].count === 2, '벨라겔룸 2타');
close(profile.hits[0].multiplier, 11.25, '벨라겔룸 Lv10 행동 불능 강화 계수');
close(profile.hits[0].constant, 200 + 100 * 2, '벨라겔룸 Lv10 행동 불능 강화 상수');
ok(E.profile('Shield:10', base(), combat, {}).cost.mp === 100, '프로텍션 방패 MP 보너스');
ok(E.profile('Shield:10', base('없음'), combat, {}).cost.mp === 300, '프로텍션 비방패 MP');
ok(!E.profile('Shield:1', base('없음'), combat, {}).available, '방패 전용 스킬 차단');
ok(!E.profile('Shield:9', base(), combat, {}).available, '벨라겔룸 듀얼 실드 상태 필요');
ok(!E.profile('Shield:9', base(), combat, {}).available, '벨라겔룸 듀얼 실드 상태 필요');

console.log('Shield S1-S5 calculator-scope regressions: PASS');
