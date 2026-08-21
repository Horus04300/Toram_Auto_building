import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window:{}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments:() => ({ Assassin:{} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/assassin.js',
  'assets/js/data/skills/assassin-s5.js',
  'assets/js/skill-effect-engine.js',
  'assets/js/combo-sequence-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });

const E = context.window.ToramSkillEffects;
const Q = context.window.ToramComboSequence;
const ids = Array.from({ length:15 }, (_, index) => `Assassin:${index}`);
const base = (mainType='한손검', subType='단검') => ({ mainType, subType, subAtk:200, level:300, strBase:100, dexBase:300, intBase:100, vitBase:100, agiBase:250, crtBase:50 });
const combat = { STR:120, DEX:330, INT:150, VIT:100, AGI:280, ATK:1000, MATK:400, MAXHP:10000 };
const levels = (value, extra={}) => { context.window.skillSimulatorState.getInvestments = () => ({ Assassin:Object.assign(Object.fromEntries(ids.map(id => [id.slice(9), value])), extra) }); };
const ok = (value, message) => { if (!value) throw new Error(message); };
const close = (actual, expected, message) => ok(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

levels(10);
for (const id of ids) ok(E.profile(id, base(), combat, {}).available, `${id} Lv10 한손검+단검`);
levels(0);
for (const id of ids) ok(!E.profile(id, base(), combat, {}).available, `${id} Lv0`);
levels(0, { 0:10, 1:10, 2:10, 3:10, 4:10, 5:10, 7:10, 8:10, 12:10, 13:10 });
let p = E.profile('Assassin:0', base(), combat, { position:2, backstepEmpowered:true });
close(p.hits[0].multiplier, 8, '어쌔신 스탭 뒤·강화 계수');
close(p.hits[0].constant, 300, '어쌔신 스탭 Lv10 상수');
levels(0, { 2:10, 4:0 });
p = E.profile('Assassin:2', base(), combat, { spentMp:2000 });
close(p.hits[0].multiplier, 21, '퓨네빈테 Lv10 MP 2000 계수');
close(p.hits[0].constant, 1000, '퓨네빈테 Lv10 상수');
levels(10);
p = E.profile('Assassin:5', base(), combat, {});
ok(p.stateTransitions[0].durationSeconds === 60, '이베이션 Lv10 단검 지속시간 60초');
p = E.profile('Assassin:8', base(), combat, {});
ok(p.stateTransitions[0].maxStacks === 20, '쉐도우 워크 Lv10 스택 상한 20');
const shadow = E.specialAttackProfile('Assassin:8', 'shadowAvoid', base(), combat, {}, { buff:{ stacks:5 } });
close(shadow.hits[0].multiplier, 5, '쉐도우 워크 Lv10 5스택 avoid 계수');
p = E.profile('Assassin:12', base(), combat, { poisonStacks:2, selfPoisoned:false });
ok(p.effects[0].value === 5320 && p.effects[1].value === 200, '베놈 스내치 독+2 회복');
p = E.profile('Assassin:13', base(), combat, { venomSnatchStacks:2 });
close(p.hits[0].multiplier, 10.3, '데스 리셉션 한손검·단검 Lv10 계수');
close(p.hits[1].multiplier, 5.15, '데스 리셉션 주변 계수');
ok(!E.profile('Assassin:2', base('한손검', '없음'), combat, {}).available, '퓨네빈테 단검/인술 두루마리 전용');
levels(0, { 0:10, 1:10 });
let result = Q.evaluate([{ skillId:'Assassin:1', inputs:{ retreatedAtLeast3m:true }, tag:'none' }, { skillId:'Assassin:5', tag:'none' }, { skillId:'Assassin:0', inputs:{ position:0 }, tag:'none' }], base(), combat, { maxMp:1000 });
close(result.entries[2].hits[0].effectiveMultiplier, 2.4, '백스텝 강화는 중간 비공격 스킬을 지나 다음 어쌔신 스탭에만 적용');
result = Q.evaluate([{ skillId:'Assassin:1', inputs:{ retreatedAtLeast3m:false }, tag:'none' }, { skillId:'Assassin:0', inputs:{ position:0 }, tag:'none' }], base(), combat, { maxMp:1000 });
close(result.entries[1].hits[0].effectiveMultiplier, 1.6, '3m 미만 백스텝은 어쌔신 스탭을 강화하지 않음');

console.log('Assassin S1-S5 calculator-scope regressions: PASS');
