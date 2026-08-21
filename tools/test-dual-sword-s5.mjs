import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window:{}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments:() => ({ DualSword:{} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/dual-sword.js',
  'assets/js/data/skills/dual-sword-s5.js',
  'assets/js/skill-effect-engine.js',
  'assets/js/combo-sequence-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });

const E = context.window.ToramSkillEffects;
const Q = context.window.ToramComboSequence;
const ids = Array.from({ length:21 }, (_, index) => `DualSword:${index}`);
const base = (mainType='한손검', subType='한손검(듀얼소드)') => ({ mainType, subType, level:300, strBase:400, dexBase:300, intBase:100, vitBase:100, agiBase:250, crtBase:50 });
const combat = { STR:450, DEX:330, INT:120, VIT:100, AGI:280, ATK:1000, MATK:400, MAXHP:10000 };
const levels = (value, extra={}) => { context.window.skillSimulatorState.getInvestments = () => ({ DualSword:Object.assign(Object.fromEntries(ids.map(id => [id.slice(10), value])), extra) }); };
const ok = (value, message) => { if (!value) throw new Error(message); };
const close = (actual, expected, message) => ok(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

levels(10);
for (const id of ids) ok(E.profile(id, base(), combat, {}).available, `${id} Lv10 쌍검`);
levels(0);
for (const id of ids) ok(!E.profile(id, base(), combat, {}).available, `${id} Lv0`);

levels(0, { 1:10 });
let p = E.profile('DualSword:1', base(), combat, {});
close(p.hits[0].multiplier, 2.5, '트윈 슬래쉬 Lv10 계수');
close(p.hits[0].constant, 200, '트윈 슬래쉬 Lv10 상수');
ok(!E.profile('DualSword:1', base('한손검', '없음'), combat, {}).available, '트윈 슬래쉬 쌍검 전용');

levels(0, { 2:10, 9:10, 10:10 });
p = E.profile('DualSword:2', base(), combat, {});
ok(p.hits[1].count === 3, '에어 슬라이드 토네이도 3타');
p = E.profile('DualSword:9', base(), combat, {});
ok(p.hits[1].count === 5, '루나 디재스터 후속 5타');
p = E.profile('DualSword:10', base(), combat, {});
ok(p.hits.length === 2 && p.hits.every(hit => hit.flags.guaranteedCritical), '트윈 버스터 블레이드 2타 확정 크리티컬');

levels(0, { 7:1, 1:10 });
let result = Q.evaluate([{ skillId:'DualSword:7', tag:'none' }, { skillId:'DualSword:1', tag:'none' }], base(), combat, { maxMp:1000 });
ok(result.entries[0].finalMp === 400, '돌아 들어가기 Lv1 MP 400');
ok(result.entries[1].hits[0].flags.guaranteedCritical, '돌아 들어가기 다음 스킬 확정 크리티컬');
levels(0, { 7:7 });
ok(E.profile('DualSword:7', base(), combat, {}).cost.mp === 200, '돌아 들어가기 Lv7 MP 200');

levels(0, { 16:10, 17:10 });
p = E.profile('DualSword:16', base(), combat, {}, { activeBuffs:{ 'DualSword:16':{ active:true, stacks:3 } } });
ok(p.skill.stackModel.hardCap === null, '세이버 오라 고정 최대 스택 없음');
p = E.profile('DualSword:17', base(), combat, {}, { activeBuffs:{ 'DualSword:17':{ active:true, stacks:3 } } });
ok(p.effects.some(effect => effect.key === 'CRIT' && effect.value === 100), '아크 세이버 Lv10 크리티컬 보정');

console.log('DualSword S1-S5 calculator-scope regressions: PASS');
