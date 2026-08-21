import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window: {}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments: () => ({ Wizard: {} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/wizard-s5.js',
  'assets/js/skill-effect-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename: path });

const E = context.window.ToramSkillEffects;
const ids = Array.from({ length: 15 }, (_, index) => `Wizard:${index}`);
const base = (mainType = '지팡이') => ({ mainType, subType: '없음', level: 300, strBase: 100, dexBase: 100, intBase: 100, vitBase: 100, agiBase: 100, crtBase: 50 });
const combat = { STR: 120, DEX: 130, INT: 120, VIT: 100, AGI: 110, ATK: 1000, MATK: 400, MAXHP: 10000 };
const levels = (value, extra = {}) => { context.window.skillSimulatorState.getInvestments = () => ({ Wizard: { ...Object.fromEntries(ids.map(id => [id.slice(7), value])), ...extra } }); };
const ok = (condition, message) => { if (!condition) throw new Error(message); };
const close = (actual, expected, message) => ok(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

const familiarRuntime = { activeBuffs:{ 'Wizard:0':{ active:true, stacks:0 } } };

levels(10);
for (const id of ids.filter(id => id !== 'Wizard:9')) ok(E.profile(id, base(), combat, {}).available, `${id} Lv10 지팡이`);
ok(E.profile('Wizard:9', base('마도구'), combat, {}).available, 'Wizard:9 Lv10 메인 마도구');
levels(0);
for (const id of ids) ok(!E.profile(id, base(), combat, {}).available, `${id} Lv0`);

levels(0, { 0: 10, 1: 10, 2: 10, 3: 10, 4: 10, 6: 10, 8: 10, 11: 10 });
let profile = E.profile('Wizard:0', base(), combat, {});
close(profile.effects.find(effect => effect.key === 'MAXMP').value, 200, '패밀리어 Lv10 최대 MP');
close(profile.effects.find(effect => effect.key === 'MATK').value, 75, '패밀리어 Lv10 레벨 기반 MATK');
profile = E.profile('Wizard:1', base(), combat, {}, familiarRuntime);
close(profile.hits[0].multiplier, 11.5, '라이트닝 Lv10 하이 패밀리어 계수');
ok(profile.cost.mp === 0, '라이트닝 MP 0');
profile = E.profile('Wizard:2', base(), combat, {}, familiarRuntime);
ok(profile.hits[0].count === 6, '블리자드 Lv10 6타');
close(profile.hits[0].multiplier, 2.25, '블리자드 Lv10 하이 패밀리어 계수');
profile = E.profile('Wizard:3', base(), combat, {}, familiarRuntime);
ok(profile.hits[0].count === 3, '메테오 스트라이크 3타');
close(profile.hits[0].multiplier, 22.5, '메테오 스트라이크 Lv10 하이 패밀리어 계수');
profile = E.profile('Wizard:4', base(), combat, { markTriggered: true });
close(profile.hits[0].multiplier, 10, '임페리얼 레이 Lv10 첫타 계수');
close(profile.hits[0].constant, 400, '임페리얼 레이 Lv10 첫타 상수');
close(profile.hits[1].multiplier, 20, '임페리얼 레이 Lv10 후속 계수');
profile = E.profile('Wizard:6', base(), combat, {}, familiarRuntime);
ok(profile.cost.mp === 0, '마나 크리스탈 MP 0');
profile = E.profile('Wizard:11', base(), combat, { manaCrystalPresent: true }, familiarRuntime);
close(profile.hits[0].multiplier, 10, '크리스탈 레이저 Lv10 계수');
close(profile.hits[0].constant, 200, '크리스탈 레이저 상수');
ok(E.profile('Wizard:11', base(), combat, { manaCrystalPresent: false }, familiarRuntime).hits.length === 0, '크리스탈 없으면 레이저 피해 없음');
ok(!E.profile('Wizard:1', base('한손검'), combat, {}, familiarRuntime).available, '위저드 지팡이·마도구 조건');

console.log('Wizard S1-S5 calculator-scope regressions: PASS');
