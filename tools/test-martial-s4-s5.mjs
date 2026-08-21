import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window: {}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments: () => ({ Martial: {} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js', 'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-data.js', 'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skills/martial.js', 'assets/js/data/skill-registration-metadata.js',
  'assets/js/data/skill-catalog-registration.js', 'assets/js/skill-effect-engine.js', 'assets/js/combo-sequence-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename: path });

const effects = context.window.ToramSkillEffects;
const ids = Array.from({ length: 22 }, (_, index) => `Martial:${index}`);
const restricted = new Set([5, 6, 11, 12, 13, 14, 15, 16, 18, 19, 20, 21]);
const base = (mainType = '권갑') => ({ mainType, subType: '없음', level: 300, strBase: 400, dexBase: 300, intBase: 100, vitBase: 200, agiBase: 500, crtBase: 50 });
const combat = { STR: 400, DEX: 300, INT: 100, VIT: 200, AGI: 500, AMPR: 30, ATK: 1000, ASPD: 1000 };
const setLevels = (value, extra = {}) => { context.window.skillSimulatorState.getInvestments = () => ({ Martial: Object.assign(Object.fromEntries(ids.map((id) => [id.split(':')[1], value])), extra) }); };
const assert = (condition, message) => { if (!condition) throw new Error(message); };
const close = (actual, expected, message) => assert(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

setLevels(10);
for (const id of ids) assert(effects.profile(id, base(), combat, {}).available, `${id}: Lv.10 권갑에서 사용 가능해야 함`);
setLevels(0);
for (const id of ids) assert(!effects.profile(id, base(), combat, {}).available, `${id}: Lv.0에서 사용 불가여야 함`);
setLevels(10);
for (const id of ids) assert(effects.profile(id, base('활'), combat, {}).available === !restricted.has(Number(id.split(':')[1])), `${id}: 활 조건 판정 불일치`);

setLevels(0, { 0: 10 });
let profile = effects.profile('Martial:0', base(), combat, {});
close(profile.hits[0].multiplier, 1.5, '스매시 권갑 Lv.10 계수');
assert(profile.hits[0].constant === 125, '스매시 권갑 Lv.10 상수');
setLevels(0, { 2: 10 });
profile = effects.profile('Martial:2', base(), combat, { targetDefenseDelta: 250 });
close(profile.hits[0].multiplier, 7, '셸 브레이크 방어 차 250 계수');
assert(profile.hits[0].constant === 800, '셸 브레이크 방어 차 250 상수');
setLevels(0, { 3: 10 });
profile = effects.profile('Martial:3', base(), combat, { targetBroken: true });
assert(profile.hits.length === 2 && profile.hits[1].flags.guaranteedCritical, '헤비 스매시 파괴 추가타');
setLevels(0, { 4: 10 });
profile = effects.profile('Martial:4', base(), combat, {});
close(profile.hits[0].multiplier, 17.5, '채리엇 권갑 Lv.10 계수');
assert(profile.hits[0].constant === 500, '채리엇 권갑 Lv.10 상수');
setLevels(0, { 9: 10 });
profile = effects.profile('Martial:9', base(), combat, {});
assert(profile.hits.length === 3 && profile.hits[2].flags.criticalChanceBonus.op === 'add', '트라이 어츠 3타 크리티컬 보너스 규칙');
setLevels(0, { 15: 10, 16: 10 });
const changes = effects.passiveStatChanges(base());
assert(changes.some((item) => item.key === 'WATKP' && item.value === 30), '머셜 마스터리 WATKP');
assert(changes.some((item) => item.key === 'ASPD' && item.value === 100), '체술 단련 고정 ASPD');

setLevels(0, { 0: 10, 11: 10 });
profile = effects.profile('Martial:0', base(), combat, {}, { activeBuffs:{ 'Martial:11':{ active:true, stacks:0 } } });
close(profile.hits[0].multiplier, 1.95, '아수라 ON 마셜 피해 배율');
assert(profile.hits[0].constant === 325, '아수라 ON 전역 상수');
assert(profile.cost.mp === 100, '아수라는 마셜 MP 비용을 늘리지 않음');
setLevels(0, { 0: 10, 14: 10, 21: 10 });
const sequence = context.window.ToramComboSequence;
let combo = sequence.evaluate([{ skillId:'Martial:14', tag:'none' }, { skillId:'Martial:0', tag:'none' }, { skillId:'Martial:0', tag:'none' }], base(), combat, { maxMp:1000 });
assert(combo.entries[1].appliedNextSkillModifiers.shortRangeDamagePercent === 10, '플래시 아트 다음 스킬 근거리 위력');
assert(combo.entries[2].appliedNextSkillModifiers.shortRangeDamagePercent === 0, '플래시 아트 효과는 1회 후 소멸');
combo = sequence.evaluate([{ skillId:'Martial:21', tag:'none' }, { skillId:'Martial:0', tag:'none' }, { skillId:'Martial:0', tag:'none' }], base(), combat, { maxMp:1000 });
assert(combo.entries[1].appliedNextSkillModifiers.hit === 100, '슬라이딩 Lv.10 다음 스킬 명중');
assert(combo.entries[2].appliedNextSkillModifiers.hit === 0, '슬라이딩 효과는 1회 후 소멸');
setLevels(0, { 10: 10 });
profile = effects.profile('Martial:10', base(), combat, {}, { buff:{ active:true } });
assert(profile.effects.some((item) => item.key === 'MOTION_SPEED_P' && item.value === 10), '러시 권갑 Lv.10 활성 행동 속도');
console.log('Martial S4/S5 modeled regressions: PASS');
