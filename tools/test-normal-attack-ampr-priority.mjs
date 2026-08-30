import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window:{}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments:() => ({}) };
vm.createContext(context);

for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skills/blade.js',
  'assets/js/data/skills/mononofu-s5.js',
  'assets/js/data/skills/shot.js',
  'assets/js/skill-effect-engine.js'
]) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });

context.BASE_ASPD_MAP = { '한손검':100, '자동활':30 };
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'assets/js/calculator.js' });

const effects = context.window.ToramSkillEffects;
const kernel = context.window.ToramCalculationKernel;
const levels = value => {
  context.window.skillSimulatorState.getInvestments = () => value;
};
const base = overrides => Object.assign({
  level:300, strBase:0, intBase:0, vitBase:100, agiBase:0, dexBase:0, crtBase:0,
  mainType:'자동활', wpnAtk:100, wpnRefine:0, wpnStab:100, subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'일반옷',
  bossLevel:300, bossDef:0, bossMdef:0, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
  skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'LONG', optimizationBasisName:'평타',
  chkIsUnsheathe:false, chkGuaranteedCrit:false, conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false, spellBurstLevel:0, godspeedWieldLevel:0,
  poisonSources:[], weakenSources:[], targetWeakened:false, attackElement:'none', attackPowerMode:'default', useHigherRangeDamage:false,
  noCritical:false, criticalChanceBonus:0, criticalChanceMultiplier:1, fixedCriticalChance:null, minimumCriticalDamage:0,
  stabilityBonus:0, physicalPierceSkillBonus:0, magicPierceSkillBonus:0, ignoreDefense:false, ignoreMdef:false, halfMdefIgnored:false,
  strP:0, strF:0, dexP:0, dexF:0, intP:0, intF:0, agiP:0, agiF:0, vitP:0, vitF:0,
  atkP:0, atkF:0, matkP:0, matkF:0, cdmgP:0, cdmgF:0, critP:0, critF:0, srw:0, lrw:0, unsheatheP:0, unsheatheF:0, elemP:0, damageP:0, watkP:0, watkF:0,
  physPierce:0, magPierce:0, aspdF:0, aspdP:0, cspdF:0, cspdP:0, stability:0, motionSpeed:0, castRed:0,
  maxHpF:0, maxHpP:0, maxMpF:0, amprF:0, amprP:0, elementAwakening:false, magicElement:false,
  atkUpSTR:0, atkUpDEX:0, atkUpINT:0, atkUpAGI:0, atkUpVIT:0, matkUpSTR:0, matkUpDEX:0, matkUpINT:0, matkUpAGI:0, matkUpVIT:0,
  preservedStats:{}, statDiagnostics:[], activeBuildConversions:[]
}, overrides);

levels({ Mononofu:{ 12:10 } });
let profile = effects.normalAttackAmprModifiers(base({}), {}, {}, { activeBuffs:{} });
assert.equal(profile.passive.length, 0, '축지법은 상시 패시브 AMPR에 포함되면 안 됩니다.');
assert.equal(profile.activeCandidates.length, 0, '축지법의 1회성 하프 액티브 AMPR은 D4 후보에서도 제외해야 합니다.');

levels({ Mononofu:{ 16:10 }, Shot:{ 7:10 } });
const activeBuffs = { 'Mononofu:16':{ active:true, stacks:0 }, 'Shot:7':{ active:true, stacks:50 } };
profile = effects.normalAttackAmprModifiers(base({}), {}, {}, { activeBuffs });
assert.deepEqual(Array.from(profile.activeCandidates, item => item.id), ['Mononofu:16','Shot:7'], '괴력난신과 트윈 스톰을 독립 활성 후보로 수집해야 합니다.');
const highBase = kernel.evaluateContext(base({ amprF:26, normalAttackAmprProfile:profile }), []);
assert.equal(highBase.equipmentAndBuffAMPR, 40, '일반 AMPR 단계 결과');
assert.deepEqual(Array.from(highBase.normalAttackAmprActiveCandidates, item => [item.id,item.result]), [['Mononofu:16',65],['Shot:7',80]], '활성 후보를 각각 단독 적용해야 합니다.');
assert.equal(highBase.selectedNormalAttackAmprActive.id, 'Shot:7', '기본 AMPR이 높으면 트윈 스톰 2배가 선택돼야 합니다.');
assert.equal(highBase.amprBeforeDual, 80, '선택된 활성 통상 변화 하나만 최종 AMPR에 반영해야 합니다.');

const lowBase = kernel.evaluateContext(base({ normalAttackAmprProfile:profile }), []);
assert.equal(lowBase.equipmentAndBuffAMPR, 14, '낮은 일반 AMPR 기준값');
assert.equal(lowBase.selectedNormalAttackAmprActive.id, 'Mononofu:16', '기본 AMPR이 낮으면 괴력난신 고정 AMPR이 선택돼야 합니다.');
assert.equal(lowBase.amprBeforeDual, 39, '선택하지 않은 트윈 스톰과 합산하면 안 됩니다.');

levels({ Blade:{ 8:10 }, Mononofu:{ 16:10 } });
const swordBuffs = { 'Blade:8':{ active:true, stacks:11 }, 'Mononofu:16':{ active:true, stacks:0 } };
const swordProfile = effects.normalAttackAmprModifiers(base({ mainType:'한손검' }), {}, {}, { activeBuffs:swordBuffs });
const tied = kernel.evaluateContext(base({ mainType:'한손검', subType:'한손검(듀얼소드)', normalAttackAmprProfile:swordProfile }), []);
assert.equal(tied.selectedNormalAttackAmprActive.id, 'Blade:8', '동률은 안정적인 스킬 ID 순으로 선택해야 합니다.');
assert.equal(tied.amprBeforeDual, 39, '램페이지와 괴력난신 AMPR을 합산하면 안 됩니다.');
assert.equal(tied.finalAMPR, 78, '듀얼소드 2배는 활성 후보 선택 이후 한 번만 적용해야 합니다.');

const directTie = kernel.resolveNormalAttackAmpr(20, { activeCandidates:[
  { id:'Z:1', flat:5, percent:0, multiplier:1 },
  { id:'A:1', flat:5, percent:0, multiplier:1 }
] });
assert.equal(directTie.selectedActive.id, 'A:1', '동일 AMPR 후보의 선택은 입력 순서에 의존하면 안 됩니다.');

console.log('Normal-attack AMPR priority regressions: PASS');
