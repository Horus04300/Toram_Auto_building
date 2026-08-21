import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window: {}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments: () => ({ Hunter: {} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/hunter-s5.js',
  'assets/js/skill-effect-engine.js',
  'assets/js/combo-sequence-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename: path });

const E = context.window.ToramSkillEffects;
const Q = context.window.ToramComboSequence;
const ids = Array.from({ length: 17 }, (_, index) => `Hunter:${index}`);
const base = (mainType = '활', subType = '화살') => ({
  mainType, subType, level: 300,
  strBase: 100, dexBase: 100, intBase: 100, vitBase: 100, agiBase: 100, crtBase: 50
});
const combat = { STR: 120, DEX: 130, INT: 120, VIT: 100, AGI: 110, ATK: 1000, MATK: 400, MAXHP: 10000 };
const levels = (value, extra = {}) => { context.window.skillSimulatorState.getInvestments = () => ({ Hunter: { ...Object.fromEntries(ids.map(id => [id.slice(7), value])), ...extra } }); };
const ok = (condition, message) => { if (!condition) throw new Error(message); };
const close = (actual, expected, message) => ok(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

levels(10);
for (const id of ids.filter(id => !['Hunter:14', 'Hunter:15', 'Hunter:16'].includes(id))) ok(E.profile(id, base(), combat, {}).available, `${id} Lv10 활+화살`);
for (const id of ['Hunter:14', 'Hunter:15', 'Hunter:16']) ok(E.profile(id, base('자동활', '방패'), combat, {}).available, `${id} Lv10 자동활+방패`);
levels(0);
for (const id of ids) ok(!E.profile(id, base('자동활', '방패'), combat, {}).available, `${id} Lv0`);

levels(0, { 0: 10, 1: 10, 2: 10, 3: 10, 5: 10, 7: 10, 10: 10, 12: 10, 13: 10, 14: 10, 15: 10 });
let profile = E.profile('Hunter:0', base(), combat, {});
close(profile.hits[0].multiplier, 2, '킥 백 Lv10 계수');
profile = E.profile('Hunter:1', base(), combat, { targetSleeping: true });
close(profile.hits[0].multiplier, 6.6, '슬리프 애로 Lv10 화살·수면 계수');
close(profile.hits[0].constant, 200, '슬리프 애로 Lv10 상수');
profile = E.profile('Hunter:2', base(), combat, {});
close(profile.effects.find(effect => effect.key === 'WATKP').value, 5, '선라이즈 애로 Lv10 무기 ATK%');
profile = E.profile('Hunter:3', base(), combat, {});
ok(profile.hits[0].count === 3, '새틀라이트 애로 Lv10 3타');
close(profile.hits[0].multiplier, 11.3, '새틀라이트 애로 Lv10 화살 계수');
profile = E.profile('Hunter:5', base(), combat, {});
close(profile.hits[0].multiplier, 0.75, '베놈 트랩 Lv10 화살 계수');
close(profile.hits[0].constant, 100, '베놈 트랩 Lv10 상수');
profile = E.profile('Hunter:7', base(), combat, {});
close(profile.hits[0].multiplier, 10, '익스플로시브 Lv10 화살 계수');
profile = E.profile('Hunter:10', base(), combat, {});
ok(profile.hits[0].count === 3, '호밍 샷 Lv10 3타');
close(profile.hits[0].multiplier, 1, '호밍 샷 Lv10 계수');
profile = E.profile('Hunter:12', base(), combat, {});
close(profile.hits[0].multiplier, 1.65, '사이클론 애로 Lv10 화살 계수');
profile = E.profile('Hunter:13', base(), combat, { distance: 8 });
ok(profile.hits.length === 3, '버티컬 에어 8m 3타');
close(profile.hits[0].multiplier, 7.5, '버티컬 에어 1타 계수');
close(profile.hits[2].multiplier, 2.5, '버티컬 에어 3타 계수');
const changes = E.passiveStatChanges(base('자동활', '방패'));
close(changes.find(change => change.source.id === 'Hunter:14').value, 25, '보우건 헌터 Lv10 무기 ATK%');
profile = E.profile('Hunter:15', base('자동활', '단검'), combat, {});
close(profile.hits[0].multiplier, 11.1, '멀티풀 헌터 단검 계수');
let result = Q.evaluate([{ skillId: 'Hunter:15', tag: 'none' }, { skillId: 'Hunter:0', tag: 'none' }], base('자동활', '단검'), combat, { maxMp: 1000 });
ok(result.entries[1].finalMp === 50, '울프 어솔트 다음 스킬 MP 반감');
ok(!E.profile('Hunter:12', base('자동활', '화살'), combat, {}).available, '사이클론 애로 활 전용');
ok(!E.profile('Hunter:14', base('자동활', '화살'), combat, {}).available, '보우건 헌터 화살 제외');

console.log('Hunter S1-S5 calculator-scope regressions: PASS');
