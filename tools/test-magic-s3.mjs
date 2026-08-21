import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window:{}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments: () => ({ Magic:{} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js', 'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js', 'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/magic.js', 'assets/js/skill-effect-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });

const effects = context.window.ToramSkillEffects;
const ids = Array.from({ length:24 }, (_, id) => `Magic:${id}`);
const base = (mainType='지팡이') => ({ mainType, subType:'없음', level:300, strBase:100, dexBase:100, intBase:500, vitBase:100, agiBase:100, crtBase:0 });
const combat = { STR:100, DEX:100, INT:600, VIT:100, AGI:100, MAXHP:10000, CSPD:1000, ATK:500, MATK:1200 };
const levels = (value, extra={}) => { context.window.skillSimulatorState.getInvestments = () => ({ Magic:Object.assign(Object.fromEntries(ids.map((id) => [id.slice(6), value])), extra) }); };
const assert = (condition, message) => { if (!condition) throw new Error(message); };
const close = (actual, expected, message) => assert(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

levels(10);
for (const id of ids) assert(effects.profile(id, base(), combat, {}).available === (id !== 'Magic:5'), `${id}: 지팡이 조건 판정`);
assert(effects.profile('Magic:5', base('마도구'), combat, {}).available, '크로노스 시프트: 마도구에서 사용 가능해야 함');
assert(!effects.profile('Magic:14', base('마도구'), combat, {}).available, '매직 나이프: 지팡이 전용이어야 함');
levels(0);
for (const id of ids) assert(!effects.profile(id, base(), combat, {}).available, `${id}: Lv.0에서는 사용 불가`);
levels(0, { 0:10 });
let profile = effects.profile('Magic:0', base(), combat, {});
assert(profile.cost.mp === 100 && profile.hits[0].count === 6, '애로 Lv.10 MP·타수');
close(profile.hits[0].multiplier, 1.5, '애로 지팡이 Lv.10 계수');
levels(0, { 3:10 });
profile = effects.profile('Magic:3', base('마도구'), combat, { consecutive:false });
close(profile.hits[0].multiplier, 5, '임팩트 마도구 Lv.10 계수');
assert(profile.effects.some((effect) => effect.type === 'nextSkillModifier' && effect.value === .5), '임팩트 다음 MP 반감 상태');
levels(0, { 6:10 });
profile = effects.profile('Magic:6', base('지팡이'), combat, { remainingMp:1000 });
close(profile.hits[0].multiplier, 12.5, '레이저 잔여 MP 상한 계수');
levels(0, { 17:10, 20:10 });
profile = effects.profile('Magic:17', base('마도구'), combat, {});
assert(profile.effects[0].value === 350, '차징 마도구 Lv.10 MP 회복');
profile = effects.profile('Magic:20', base('지팡이'), combat, {});
assert(profile.effects[0].value === 1500, '맥시마이저 지팡이 MP 회복');
levels(0, { 23:10 });
profile = effects.profile('Magic:23', base('지팡이'), combat, {});
assert(profile.skill.stackControl.initialStacks.op === 'multiply' && profile.skill.specialAttacks[0].hits[0].constant.value === 300, '이겔 스택·특수 공격 규칙');
console.log('Magic S1-S3 modeled regressions: PASS');