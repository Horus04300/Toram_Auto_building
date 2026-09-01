import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';
import { LEGACY_SCRIPT_PATHS } from '../assets/js/legacy-script-manifest.mjs';

const root = resolve(import.meta.dirname, '..');
const html = await readFile(resolve(root, 'index.html'), 'utf8');
const dataScripts = LEGACY_SCRIPT_PATHS.filter(path => path.startsWith('assets/js/data/'));
let investments = { Battle:{ 12:10 }, MagicBlade:{ 6:10 }, Dagger:{ 5:10 } };
const context = { window:{ skillSimulatorState:{ getInvestments:() => investments } }, console };
context.window.window = context.window;
vm.createContext(context);
for (const path of dataScripts) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });
vm.runInContext(await readFile(resolve(root, 'assets/js/skill-effect-engine.js'), 'utf8'), context, { filename:'skill-effect-engine.js' });
for (const path of ['assets/js/stat-registry.js', 'assets/js/calculation-policies.js']) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', context);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'calculator.js' });

const calculatorSource = await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8');
assert.match(calculatorSource, /skillConst:\s*appliedComboHit\s*\?\s*appliedComboHit\.skillConst\s*:\s*0/, 'D1 기본 공격 상수는 0이어야 합니다.');
assert.match(await readFile(resolve(root, 'index.html'), 'utf8'), /\[평타\] 기준 최적화됨/, 'D1 결과 최상단에 평타 최적화 기준을 표시해야 합니다.');
const comboUiSource = await readFile(resolve(root, 'assets/js/combo-ui.js'), 'utf8');
const applicationUseCasesSource = await readFile(resolve(root, 'assets/js/application-use-cases.js'), 'utf8');
assert.match(comboUiSource, /ToramApplication\.ApplyComboHit/, 'D3 콤보 UI는 Application 유스케이스를 통해 타격을 전달해야 합니다.');
assert.match(applicationUseCasesSource, /hitProfile:\{\s*damageType:selected\.damageType[\s\S]*flags:flags\s*\}/, 'D3 Application 유스케이스는 결과 계산기로 타격 객체 전체를 전달해야 합니다.');
const crystaUiSource = await readFile(resolve(root, 'assets/js/crysta-ui.js'), 'utf8');
const optimizerSource = await readFile(resolve(root, 'assets/js/optimizer.js'), 'utf8');
assert.match(crystaUiSource, /function validateCrystaInputs\(\)[\s\S]*!getCrystaByName\(value\)/, 'D6 목록에 없는 크리스타 이름을 검사해야 합니다.');
assert.match(optimizerSource, /validateCrystaInputs[\s\S]*return;[\s\S]*revealResultTab/, 'D6 잘못된 이름은 결과 탭을 열기 전에 계산을 차단해야 합니다.');

const adapted = { atkType:'PHYS', rangeType:'SHORT' };
context.applyAttackProfileToContext(adapted, {
  skillName:'유니온 소드', skillId:'MagicBlade:9',
  hitProfile:{ damageType:'physical', count:1, multiplier:15, constant:500, flags:{ usesAtkPlusMatk:true, forceLongRange:true, physicalPierceBonus:25, guaranteedCritical:true, ignoreDefense:true } }
});
assert.equal(adapted.optimizationBasisName, '유니온 소드', 'D1 선택 스킬 이름을 최적화 기준으로 전달해야 합니다.');
assert.equal(adapted.attackPowerMode, 'sum', 'D3 ATK+MATK 플래그를 공통 어댑터가 해석해야 합니다.');
assert.equal(adapted.rangeType, 'LONG', 'D3 강제 원거리 플래그를 공통 어댑터가 해석해야 합니다.');
assert.equal(adapted.physicalPierceSkillBonus, 25, 'D3 타격 관통 보너스를 전달해야 합니다.');
assert.equal(adapted.chkGuaranteedCrit, true, 'D3 확정 크리티컬을 전달해야 합니다.');
assert.equal(adapted.ignoreDefense, true, 'D3 방어 무시를 전달해야 합니다.');

const effects = context.window.ToramSkillEffects;
assert.ok(effects.learnedAilmentSources('poison').some(source => source.id === 'Dagger:5'), 'D2 중독 가능 스킬 습득을 자동 탐지해야 합니다.');
assert.ok(effects.learnedAilmentSources('weaken').some(source => source.id === 'MagicBlade:6'), 'D5 쇠약 가능 스킬 습득을 자동 탐지해야 합니다.');

function base(overrides={}) {
  return Object.assign({
    level:100, strBase:0, intBase:0, vitBase:0, agiBase:0, dexBase:100, crtBase:0,
    mainType:'한손검', wpnAtk:100, wpnRefine:0, wpnStab:100, subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'일반',
    bossLevel:100, bossDef:600, bossMdef:0, bossCritResist:0, bossPhysResist:20, bossMagResist:40,
    skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'SHORT', chkIsUnsheathe:false, chkGuaranteedCrit:false,
    conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false, spellBurstLevel:0,
    poisonSources:[], weakenSources:[], targetWeakened:false, attackElement:'none', attackPowerMode:'default', useHigherRangeDamage:false,
    noCritical:false, criticalChanceBonus:0, criticalChanceMultiplier:1, fixedCriticalChance:null, minimumCriticalDamage:0,
    stabilityBonus:0, physicalPierceSkillBonus:0, magicPierceSkillBonus:0, ignoreDefense:false, ignoreMdef:false, halfMdefIgnored:false,
    strP:0, strF:0, dexP:0, dexF:0, intP:0, intF:0, agiP:0, agiF:0, vitP:0, vitF:0,
    atkP:0, atkF:0, matkP:0, matkF:0, cdmgP:0, cdmgF:0, critP:0, critF:0, srw:0, lrw:0, unsheatheP:0, unsheatheF:0, elemP:0, damageP:0, watkP:0, watkF:0,
    physPierce:0, magPierce:0, aspdF:0, aspdP:0, cspdF:0, cspdP:0, stability:0, motionSpeed:0, castRed:0, maxMpF:0,
    elementAwakening:false, magicElement:false, atkUpSTR:0, atkUpDEX:0, atkUpINT:0, atkUpAGI:0, atkUpVIT:0,
    matkUpSTR:0, matkUpDEX:0, matkUpINT:0, matkUpAGI:0, matkUpVIT:0
  }, overrides);
}

const poisonResult = context.simulateWithCrystas(base({ poisonSources:effects.learnedAilmentSources('poison') }), []);
const expectedPoison = (poisonResult.finalDEX + (poisonResult.finalATK + poisonResult.finalMATK) * .5) * .7;
assert.equal(poisonResult.poisonDamageProfile.available, true, 'D2 중독 가능 스킬을 배운 경우에만 중독 1회 계산을 활성화해야 합니다.');
assert.ok(Math.abs(poisonResult.poisonDamageProfile.damage - expectedPoison) < 1e-9, 'D2 DEF/MDEF 비율 상한 0.5와 평균 내성을 적용해야 합니다.');
assert.equal(context.simulateWithCrystas(base(), []).poisonDamageProfile.damage, null, 'D2 중독 가능 스킬을 배우지 않으면 중독값을 만들지 않아야 합니다.');

const staffWeakened = context.simulateWithCrystas(base({ atkType:'MAG', mainType:'지팡이', dexBase:0, spellBurstLevel:10, targetWeakened:true }), []);
const swordNotWeak = context.simulateWithCrystas(base({ atkType:'MAG', mainType:'한손검', dexBase:0, spellBurstLevel:10, targetWeakened:true, magicElement:true }), []);
const swordWeak = context.simulateWithCrystas(base({ atkType:'MAG', mainType:'한손검', dexBase:0, spellBurstLevel:10, targetWeakened:true, attackElement:'weakness' }), []);
assert.equal(staffWeakened.finalCrit, 18, 'D5 지팡이는 쇠약 +50%와 스펠 버스트 25%를 합쳐 75% 반영해야 합니다.');
assert.equal(swordNotWeak.finalCrit, 6, 'D5 기타 무기의 마력 속성은 약점 공격이 아니므로 쇠약 +50%를 받지 않아야 합니다.');
assert.equal(swordWeak.finalCrit, 18, 'D5 기타 무기는 실제 약점 속성 공격일 때만 쇠약 +50%를 받아야 합니다.');
const magicCdmgDecimal = context.simulateWithCrystas(base({ atkType:'MAG', strBase:225, spellBurstLevel:1 }), []);
assert.equal(magicCdmgDecimal.finalCDMG, 149, '마법 크뎀은 물리 크뎀 195와 스펠 버스트 Lv1 반영률 52.5%를 곱한 뒤 49로 내림해야 합니다.');
const dualBringerCdmg = context.simulateWithCrystas(base({ atkType:'MAG', strBase:225, intBase:226, subType:'마도구', dualBringerActive:true, dualBringerLevel:10 }), []);
assert.equal(dualBringerCdmg.finalCDMG, 171, '듀얼 브링거 활성·INT>STR이면 쇠약과 무관하게 마법 크뎀 반영률에 25%를 더해야 합니다.');
const dualBringerEqualStats = context.simulateWithCrystas(base({ atkType:'MAG', strBase:225, intBase:225, subType:'마도구', dualBringerActive:true, dualBringerLevel:10 }), []);
assert.equal(dualBringerEqualStats.finalCDMG, 147, '듀얼 브링거 마법 크뎀 보정은 INT가 STR보다 클 때만 적용해야 합니다.');
const layeredDamage = context.simulateWithCrystas(base({ dexBase:0, wpnAtk:1, bossDef:0, bossPhysResist:0, noCritical:true, skillMult:1.5, damageMultiplierLayers:{ skill:1.5, passive:1.1, active:1.1, combo:.9 } }), []);
assert.equal(layeredDamage.damageFactor, 163, '스킬·패시브·거리·버프·콤보의 각 곱연산은 원문 순서에 따라 단계별 내림해야 합니다.');
const conversionMatkFlat = context.simulateWithCrystas(base({ mainType:'한손검', wpnAtk:100, intBase:100, dexBase:0, conversionLevel:10, matkP:100 }), []);
assert.equal(conversionMatkFlat.finalMATK, 1000, '컨버전의 무기·INT 보정은 MATK% 뒤의 MATK(+)로 더해야 합니다.');
const knuckleMatkRatio = context.simulateWithCrystas(base({ mainType:'권갑', wpnAtk:101, intBase:0, dexBase:0 }), []);
assert.equal(knuckleMatkRatio.finalMATK, 150, '권갑은 최종 무기 공격력의 50%를 MATK에 반영해야 합니다.');
const dualSubFloor = context.simulateWithCrystas(base({ mainType:'한손검', subType:'한손검(듀얼소드)', subAtk:101, subRefine:1, watkP:.5, subStab:1, strBase:10, dexBase:0, agiBase:0 }), []);
assert.equal(dualSubFloor.finalSubAtk, 212, '듀얼소드 서브 무기 ATK%·재련 보정은 각각 곱한 뒤 내림해야 합니다.');
assert.equal(dualSubFloor.finalSubStab, 0, '듀얼소드 서브 안정률의 0.5·0.06·0.04배 항은 각각 곱한 뒤 내림해야 합니다.');
const physicalCdmgCap = context.simulateWithCrystas(base({ strBase:250, strF:5, agiBase:0, cdmgP:50, cdmgF:20 }), []);
assert.equal(physicalCdmgCap.finalCDMG, 310, '물리 크뎀은 장비·스킬 STR을 포함해 퍼센트 곱셈 후 내림하고 321의 300 초과분을 절반으로 낮춰 310으로 만들어야 합니다.');


const magicElementResult = context.simulateWithCrystas(base({ intBase:100, magicElement:true }), []);
const elementAwakeningResult = context.simulateWithCrystas(base({ intBase:100, elementAwakening:true }), []);
assert.equal(magicElementResult.ctx.elemP, 10, 'D5 마력 속성은 INT 비례 속성 보너스만 받고 약점 25%는 받지 않아야 합니다.');
assert.equal(elementAwakeningResult.ctx.elemP, 35, 'D5 속성 각성은 INT 보너스와 약점 25%를 모두 받아야 합니다.');
console.log('D-sector regressions: PASS');
