import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const investments = {
  Battle: { 1:10, 3:10 },
  Blade: { 6:10, 16:10, 19:10 },
  Support: { 6:10 },
  Knight: { 14:10 },
  Test: { 0:10 }
};
const context = { window:{}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments:() => investments };
vm.createContext(context);

for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/battle.js',
  'assets/js/data/skills/blade.js',
  'assets/js/data/skills/support.js',
  'assets/js/data/skills/knight.js',
  'assets/js/data/skills/knight-s5.js'
]) {
  vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });
}

context.window.ToramSkillEffectRegistry.register('Test', [{
  id:'Test:0', treeId:'Test', skillId:0, nameKo:'테스트 마법', kind:'attack',
  source:'test', dataStatus:'verified', sourceRef:{ file:'test', anchor:'magic' },
  attacks:[{ id:'main', damageType:'magic', count:{ op:'value', value:1 }, multiplier:{ op:'value', value:1 }, constant:{ op:'value', value:0 }, flags:{} }]
}]);

vm.runInContext(await readFile(resolve(root, 'assets/js/skill-effect-engine.js'), 'utf8'), context, { filename:'skill-effect-engine.js' });
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', context);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'calculator.js' });

const E = context.window.ToramSkillEffects;
const physicalBase = { level:300, mainType:'양손검', subType:'없음', armorType:'일반' };
const physicalHit = E.profile('Blade:6', physicalBase, {}, {}, {}).hits[0];
assert.ok(physicalHit.passiveDamageModifiers.some(item => item.source === '장인의 검술' && Math.abs(item.value - 1.2) < 1e-9), '장인의 검술 20%는 블레이드 확정 배율로 적용');
assert.deepEqual(JSON.parse(JSON.stringify(physicalHit.procDamageModifiers)), [{ source:'강타', level:10, chancePercent:10, multiplier:1.2, target:'physical' }], '물리 타격에는 강타 Lv.10 확률·발동 배율 전달');

const magicHit = E.profile('Test:0', { level:300, mainType:'지팡이', subType:'없음', armorType:'일반' }, {}, {}, {}).hits[0];
assert.deepEqual(JSON.parse(JSON.stringify(magicHit.procDamageModifiers)), [{ source:'집중', level:10, chancePercent:10, multiplier:1.2, target:'magic' }], '마법 타격에는 집중 Lv.10 확률·발동 배율 전달');

const calculatorBase = {
  level:100, strBase:0, intBase:0, vitBase:0, agiBase:0, dexBase:0, crtBase:0,
  mainType:'양손검', wpnAtk:100, wpnRefine:0, wpnStab:100,
  subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'일반',
  bossLevel:0, bossDef:0, bossMdef:0, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
  skillMult:physicalHit.multiplier, skillConst:0, procDamageModifiers:physicalHit.procDamageModifiers,
  atkType:'PHYS', rangeType:'SHORT', chkIsUnsheathe:false, chkGuaranteedCrit:false,
  conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false,
  strP:0, strF:0, dexP:0, dexF:0, intP:0, intF:0, agiP:0, agiF:0, vitP:0, vitF:0,
  atkP:0, atkF:0, matkP:0, matkF:0, cdmgP:0, cdmgF:0, critP:0, critF:0,
  srw:0, lrw:0, unsheatheP:0, unsheatheF:0, elemP:0, damageP:0, watkP:0, watkF:0,
  physPierce:0, magPierce:0, aspdF:0, aspdP:0, cspdF:0, cspdP:0,
  stability:0, motionSpeed:0, castRed:0, maxMpF:0, elementAwakening:false, magicElement:false,
  atkUpSTR:0, atkUpDEX:0, atkUpINT:0, atkUpAGI:0, atkUpVIT:0,
  matkUpSTR:0, matkUpDEX:0, matkUpINT:0, matkUpAGI:0, matkUpVIT:0
};
const calculated = context.simulateWithCrystas(calculatorBase, []);
assert.ok(Math.abs(calculated.procTriggeredDamageFactor / calculated.damageFactor - 1.2) < 1e-9, '강타 발동 시 기존 확정 계산에 1.2배 곱연산');
assert.ok(Math.abs(calculated.procExpectedDamageFactor / calculated.damageFactor - 1.02) < 1e-9, '10% 확률 1.2배의 기대 배율은 1.02배');
const activeRuntime = { activeBuffs:{ 'Blade:16':{ active:true, stacks:0 }, 'Support:6':{ active:true, stacks:0 }, 'Knight:14':{ active:true, stacks:0 } } };
const activeHit = E.profile('Blade:6', { level:300, mainType:'한손검', subType:'방패', subRefine:15, armorType:'일반' }, {}, {}, activeRuntime).hits[0];
const embeddedPercent = Number(activeHit.passiveDamageModifiers.filter(item => item.stackGroup === 'activeGlobalDamage').reduce((sum, item) => sum + (item.value - 1) * 100, 0).toFixed(6));
assert.equal(embeddedPercent, 55, '오라 블레이드 20% + 브레이브 오라 20% + 나이트 플레지 15%는 같은 계열 55%');

const deduplicatedActiveDamage = context.removeEmbeddedActiveGlobalDamage({ damageP:55 }, { embeddedActiveGlobalDamagePercent:55 });
assert.equal(deduplicatedActiveDamage.damageP, 0, '콤보 계수에 내장된 전역 액티브 대미지는 결과 옵션에서 중복 적용하지 않음');
assert.equal(calculated.damageFactor < calculated.procExpectedDamageFactor && calculated.procExpectedDamageFactor < calculated.procTriggeredDamageFactor, true, '미적용 기본값 < 확률 기대값 < 발동값 세 결과를 모두 보존');

assert.equal(calculated.optimizationDamageFactor, calculated.procExpectedDamageFactor, '빌드 최적화 점수는 확률 기대 대미지 사용');

console.log('Probabilistic passive damage result regressions: PASS');
