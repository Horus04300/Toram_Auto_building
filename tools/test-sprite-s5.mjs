import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window:{}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments:() => ({ Sprite:{} }) };
vm.createContext(context);
for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/sprite.js',
  'assets/js/data/skills/sprite-s5.js',
  'assets/js/skill-effect-engine.js',
  'assets/js/combo-sequence-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });

const E = context.window.ToramSkillEffects;
const Q = context.window.ToramComboSequence;
const ids = Array.from({ length:17 }, (_, index) => `Sprite:${index}`);
const base = (mainType='마도구') => ({ mainType, subType:'없음', level:300, strBase:100, dexBase:300, intBase:100, vitBase:100, agiBase:250, crtBase:50 });
const combat = { STR:120, DEX:330, INT:500, VIT:100, AGI:280, ATK:500, MATK:1200, MAXHP:10000 };
const levels = (value, extra={}) => { context.window.skillSimulatorState.getInvestments = () => ({ Sprite:Object.assign(Object.fromEntries(ids.map(id => [id.slice(7), value])), extra) }); };
const ok = (value, message) => { if (!value) throw new Error(message); };
const close = (actual, expected, message) => ok(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

levels(10);
for (const id of ids) ok(E.profile(id, base(), combat, {}).available, `${id} Lv10 마도구`);
levels(0);
for (const id of ids) ok(!E.profile(id, base(), combat, {}).available, `${id} Lv0`);
levels(0, { 0:10, 2:10, 3:10, 9:10, 10:10, 12:10, 13:10, 14:10, 15:10 });
let p = E.profile('Sprite:2', base(), combat, {});
ok(p.effects[0].value === 1100, '클라인 힐 Lv10 회복식');
p = E.profile('Sprite:3', base(), combat, {});
close(p.castTime.seconds, 5, '리저렉션 Lv10 영창');
const auto = E.specialAttackProfile('Sprite:0', 'autoNormal', base(), combat, {});
ok(auto.hits.length === 1 && auto.hits[0].damageType === 'magic', '오토 디바이스 마법 통상 특수 공격');
const astral = E.specialAttackProfile('Sprite:9', 'astralLance', base(), combat, {});
close(astral.hits[0].multiplier, 7.5, '아스트랄 랜스 Lv10 계수');
p = E.profile('Sprite:10', base(), combat, { sustainBatches:2 });
ok(p.hits[0].count === 5 && p.hits[1].count === 10, '매직 발칸 첫 5타와 유지 타수');
close(p.hits[1].multiplier, 2.6, '매직 발칸 Lv10 2회 유지 계수');
p = E.profile('Sprite:12', base(), Object.assign({}, combat, { WEAPON_ATK:1000 }), {});
close(p.hits[0].multiplier, 12, '이그니션 계수 상한 12');
p = E.profile('Sprite:13', base(), combat, { distance:7, targetAggroed:false });
close(p.hits[0].multiplier, 9, '알데드락 Lv10 기본 INT/DEX 계수');
p = E.profile('Sprite:14', base(), combat, { variant:0 });
ok(p.hits.length === 2 && p.hits.every(hit => hit.flags.guaranteedCritical), '팍티스알름 문 슬래시 분기 2타 확정 크리티컬');
const swords = E.specialAttackProfile('Sprite:15', 'fireSwords', base(), combat, {});
ok(swords.hits[0].count === 5, '슬래시 리퍼 5자루 발사');
ok(!E.profile('Sprite:10', base('지팡이'), combat, {}).available, '스프라이트 마도구 전용');
levels(0, { 4:10, 12:10 });
const result = Q.evaluate([{ skillId:'Sprite:12', tag:'none' }], base(), Object.assign({}, combat, { WEAPON_ATK:500 }), { maxMp:1000, activeBuffs:{ 'Sprite:4':{ active:true, stacks:1 } } });
close(result.entries[0].hits[0].effectiveMultiplier, 12.1, '인핸스 Lv10 활성 피해 배율');

console.log('Sprite S1-S5 calculator-scope regressions: PASS');
