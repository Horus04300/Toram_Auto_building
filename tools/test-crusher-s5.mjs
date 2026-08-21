import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window:{}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments:() => ({ Crusher:{} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/crusher.js',
  'assets/js/data/skills/crusher-s5.js',
  'assets/js/skill-effect-engine.js',
  'assets/js/combo-sequence-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });

const E = context.window.ToramSkillEffects;
const Q = context.window.ToramComboSequence;
const ids = Array.from({ length:10 }, (_, index) => `Crusher:${index}`);
const base = (mainType='권갑') => ({ mainType, subType:'없음', level:300, strBase:400, dexBase:300, intBase:100, vitBase:100, agiBase:250, crtBase:50 });
const combat = { STR:450, DEX:330, INT:120, VIT:100, AGI:280, ATK:1000, MATK:400, MAXHP:10000 };
const levels = (value, extra={}) => { context.window.skillSimulatorState.getInvestments = () => ({ Crusher:Object.assign(Object.fromEntries(ids.map(id => [id.slice(8), value])), extra) }); };
const ok = (value, message) => { if (!value) throw new Error(message); };
const close = (actual, expected, message) => ok(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

levels(10);
for (const id of ids) ok(E.profile(id, base(), combat, {}).available, `${id} Lv10 권갑`);
levels(0);
for (const id of ids) ok(!E.profile(id, base(), combat, {}).available, `${id} Lv0`);
levels(0, { 0:10, 1:10, 2:10, 4:10, 6:10, 7:10, 9:10 });
let p = E.profile('Crusher:0', base(), combat, {});
close(p.hits[0].multiplier, 4, '정권 찌르기 Lv10 계수');
ok(p.hits[0].flags.guaranteedCritical, '정권 찌르기 확정 크리티컬');
p = E.profile('Crusher:1', base(), combat, { charging:false, goliathStacks:2, godHandStacks:3 });
close(p.hits[0].multiplier, 25, '골리아스테이크 샷 스택 계수');
p = E.profile('Crusher:1', base(), combat, { charging:true });
ok(p.cost.mp === 500 && p.hits.length === 0, '골리아스테이크 샷 충전 MP와 공격 비표시');
p = E.profile('Crusher:2', base(), combat, {});
close(p.hits[0].constant, 400, '갓 핸드 Lv10 상수');
p = E.profile('Crusher:6', base(), combat, { distance:8 });
close(p.hits[0].multiplier, 16.4, '가이저 슛 장거리 Lv10 계수');
p = E.profile('Crusher:7', base(), combat, {});
close(p.hits[0].multiplier, 2, '콤비네이션 Lv10 계수');
ok(p.hits[0].flags.criticalChanceBonus.op === 'multiply', '콤비네이션 레벨 제곱 크리티컬 보너스 식');
p = E.profile('Crusher:9', base(), combat, { targetBroken:true, godHandStacks:3 });
close(p.hits[0].multiplier, 19, '지오크러셔 Lv10 계수');
ok(p.hits[0].flags.guaranteedCriticalWhen === 'destroyerActive && targetBroken', '지오크러셔 파괴·파괴자 확정 크리티컬 조건');
levels(0, { 4:10, 0:10, 8:10 });
const result = Q.evaluate([{ skillId:'Crusher:4', tag:'none' }, { skillId:'Crusher:0', tag:'none' }], base(), combat, { maxMp:1000 });
ok(result.entries[0].finalMp === 300 && result.entries[1].finalMp === 150, '호흡법 파괴자 Lv10 다음 스킬 MP 반감');
levels(0, { 8:10 });
p = E.profile('Crusher:8', base(), combat, {}, { activeBuffs:{ 'Crusher:8':{ active:true, stacks:1 } } });
ok(p.skill.effects.some(effect => effect.key === 'WATKP'), '파괴자 WATKP 원문 식 보존');
ok(!E.profile('Crusher:0', base('한손검'), combat, {}).available, '크러셔 권갑 전용');

console.log('Crusher S1-S5 calculator-scope regressions: PASS');
