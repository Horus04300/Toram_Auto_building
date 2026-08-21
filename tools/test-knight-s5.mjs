import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window:{}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments:() => ({ Knight:{} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/knight.js',
  'assets/js/data/skills/knight-s5.js',
  'assets/js/skill-effect-engine.js',
  'assets/js/combo-sequence-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });

const E = context.window.ToramSkillEffects;
const Q = context.window.ToramComboSequence;
const ids = Array.from({ length:15 }, (_, index) => `Knight:${index}`);
const base = (mainType='한손검', subType='방패', subRefine=5) => ({ mainType, subType, subRefine, level:300, strBase:400, dexBase:300, intBase:100, vitBase:100, agiBase:250, crtBase:50 });
const combat = { STR:450, DEX:330, INT:120, VIT:450, AGI:280, ATK:1000, MATK:400, MAXHP:10000 };
const levels = (value, extra={}) => { context.window.skillSimulatorState.getInvestments = () => ({ Knight:Object.assign(Object.fromEntries(ids.map(id => [id.slice(7), value])), extra) }); };
const ok = (value, message) => { if (!value) throw new Error(message); };
const close = (actual, expected, message) => ok(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

levels(10);
for (const id of ids) ok(E.profile(id, base(), combat, {}).available, `${id} Lv10 한손검+방패`);
levels(0);
for (const id of ids) ok(!E.profile(id, base(), combat, {}).available, `${id} Lv0`);
levels(0, { 0:10, 5:6, 6:10, 7:10, 8:10, 9:10, 11:10, 14:10 });
let p = E.profile('Knight:0', base(), combat, {});
close(p.hits[0].multiplier, 7.5, '어솔트 어택 Lv10 방패·나이트 윌 계수');
close(p.hits[0].constant, 100, '어솔트 어택 Lv10 방패 상수');
p = E.profile('Knight:5', base(), combat, {});
ok(p.cost.mp === 300, '프로보크 Lv6 MP 300');
p = E.profile('Knight:6', base(), combat, { targetAggroSelf:true });
close(p.hits[0].multiplier, 10.05, '레이지 소드 Lv10 방패·나이트 윌 계수');
close(p.hits[0].constant, 200, '레이지 소드 Lv10 상수');
p = E.profile('Knight:7', base(), combat, {});
close(p.hits[0].multiplier, 19.5, '바인드 스트라이크 Lv10 방패·나이트 윌 계수');
close(p.hits[0].constant, 300, '바인드 스트라이크 Lv10 방패 상수');
p = E.profile('Knight:11', base(), combat, { consumedStacks:2 });
ok(p.hits[0].count === 3, '루브닐 소비 2스택 3타');
close(p.hits[0].multiplier, 12, '루브닐 Lv10 기본 DEX 계수');
ok(!E.profile('Knight:2', base('한손검', '없음'), combat, {}).available, 'P 디펜스 방패 전용');
ok(!E.profile('Knight:9', base('양손검', '없음'), combat, {}).available, '블링크 소드 한손검 전용');
levels(0, { 6:10, 0:10 });
let result = Q.evaluate([{ skillId:'Knight:6', inputs:{ targetAggroSelf:true }, tag:'none' }, { skillId:'Knight:0', tag:'none' }], base(), combat, { maxMp:1000 });
ok(result.entries[1].finalMp === 50, '레이지 소드 다음 스킬 MP 반감');
levels(0, { 0:10, 14:10 });
result = Q.evaluate([{ skillId:'Knight:0', tag:'none' }], base('한손검', '방패', 5), combat, { maxMp:1000, activeBuffs:{ 'Knight:14':{ active:true, stacks:1 } } });
close(result.entries[0].hits[0].effectiveMultiplier, 1.575, '나이트 플레지 방패 제련 +5% 피해 배율');
result = Q.evaluate([{ skillId:'Knight:0', tag:'none' }], base('한손검', '방패', 0), combat, { maxMp:1000, activeBuffs:{ 'Knight:14':{ active:true, stacks:1 } } });
close(result.entries[0].hits[0].effectiveMultiplier, 1.545, '나이트 플레지 Lv10 최소 +3% 피해 배율');

console.log('Knight S1-S5 calculator-scope regressions: PASS');
