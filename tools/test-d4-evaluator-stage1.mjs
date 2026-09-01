import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const evaluator = require(resolve(root, 'assets/js/build-evaluator.js'));

const crystaSource = await readFile(resolve(root, 'assets/js/data/crysta-data.js'), 'utf8');
const dataContext = {};
vm.createContext(dataContext);
vm.runInContext(`${crystaSource}\nglobalThis.__crystas = crystaDataJson;`, dataContext);
const crystaKeys = registry.collectCrystaKeys(dataContext.__crystas);
const audit = registry.auditKeys(crystaKeys);
assert.equal(crystaKeys.length, 87, '현재 크리스타 데이터의 스탯 키는 87종이어야 합니다.');
assert.deepEqual(audit.unknown, [], '크리스타 스탯 키가 StatRegistry에서 조용히 누락되면 안 됩니다.');
assert.ok(audit.modeled.includes('MAXHP') && audit.modeled.includes('AMPRP'), 'D4 Utility 키가 계산 대상으로 등록돼야 합니다.');
assert.ok(audit.preserved.includes('DROP_RATE'), '1차 D4 범위 밖 키도 삭제하지 않고 보존해야 합니다.');

const context = { window:{ ToramStatRegistry:registry }, console };
context.window.window = context.window;
vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', context);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculation-policies.js'), 'utf8'), context, { filename:'calculation-policies.js' });
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'calculator.js' });

function base(overrides={}) {
  return Object.assign({
    level:100, strBase:0, intBase:0, vitBase:100, agiBase:0, dexBase:0, crtBase:0,
    mainType:'한손검', wpnAtk:100, wpnRefine:0, wpnStab:100, subType:'한손검(듀얼소드)', subAtk:0, subRefine:0, subStab:0, armorType:'일반옷',
    bossLevel:100, bossDef:0, bossMdef:0, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
    skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'SHORT', optimizationBasisName:'테스트 스킬',
    chkIsUnsheathe:false, chkGuaranteedCrit:true, conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false, spellBurstLevel:0, godspeedWieldLevel:0,
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
}

const utilityCrysta = { name:'Utility fixture', stats:{ MaxHP:1000, MaxHPP:10, MaxMP:1800, AMPRP:100, AMPR:40, ASPD_P:100, ASPD:600, CRIT:75, DROP_RATE:1 } };
const baseInput = base();
const original = JSON.stringify(baseInput);
const build = evaluator.createBuildSnapshot(baseInput, [utilityCrysta]);
const scenario = evaluator.createScenarioSnapshot(baseInput, { requirements:{ maxHp:5000 } });
const outcome = evaluator.evaluate(build, scenario, context.window.ToramCalculationKernel.evaluateContext);

assert.equal(JSON.stringify(baseInput), original, 'BuildEvaluator는 호출자의 입력 객체를 변경하면 안 됩니다.');
assert.ok(Object.isFrozen(build) && Object.isFrozen(build.baseContext), 'BuildSnapshot은 평가 중 변경할 수 없게 고정돼야 합니다.');
assert.equal(outcome.utility.maxHp, 5590, 'MAXHP는 기준 HP에 MAXHP%를 적용한 뒤 고정 MAXHP를 더해야 합니다.');
assert.equal(outcome.utility.maxMpBeforeBuff, 2000, 'MAXMP 공식과 고정 MAXMP를 적용해야 합니다.');
assert.equal(outcome.utility.baseAmpr, 30, '기본 AMPR은 floor(10 + MAXMP/100)이어야 합니다.');
assert.equal(outcome.utility.amprBeforeDual, 100, 'AMPR% 적용 시 버린 뒤 고정 AMPR을 더해야 합니다.');
assert.equal(outcome.utility.finalAmpr, 200, '듀얼소드는 최종 AMPR만 2배로 표시해야 합니다.');
assert.equal(outcome.utility.aspd, 1000, 'ASPD% 적용 뒤 고정 ASPD를 더해야 합니다.');
assert.equal(outcome.offense.normalAttackCrit, 100, '선택 스킬 확정 크리티컬과 별개로 평타 크리티컬률을 반환해야 합니다.');
assert.equal(outcome.constraints.feasible, true, 'fixture는 모든 D4 기본 Utility 경계를 만족해야 합니다.');
assert.equal(outcome.calculation.ctx.preservedStats.DROP_RATE, 1, '현재 범위 밖 스탯도 계산 컨텍스트에 보존돼야 합니다.');
const aggregateOutcome = evaluator.evaluateAggregate(baseInput, scenario, utilityCrysta.stats, context.window.ToramCalculationKernel.evaluateContext);
assert.deepEqual(aggregateOutcome.damage, outcome.damage, '고속 집계 평가의 대미지는 전체 BuildSnapshot 평가와 같아야 합니다.');
assert.deepEqual(aggregateOutcome.offense, outcome.offense, '고속 집계 평가의 공격 지표는 전체 평가와 같아야 합니다.');
assert.deepEqual(aggregateOutcome.utility, outcome.utility, '고속 집계 평가의 Utility는 전체 평가와 같아야 합니다.');
assert.deepEqual(aggregateOutcome.constraints, outcome.constraints, '고속 집계 평가의 hard constraint 판정은 전체 평가와 같아야 합니다.');
assert.equal(aggregateOutcome.calculation.ctx.preservedStats.DROP_RATE, 1, '고속 집계 평가도 범위 밖 스탯을 보존해야 합니다.');
assert.equal(JSON.stringify(baseInput), original, '고속 집계 평가도 호출자의 기본 컨텍스트를 변경하면 안 됩니다.');
const aggregateSummary = evaluator.evaluateAggregateSummary(baseInput, scenario, utilityCrysta.stats, context.window.ToramCalculationKernel.evaluateContext);
assert.equal(aggregateSummary.damage.expected, outcome.damage.expected, '경량 상한 평가의 점수는 전체 평가와 같아야 합니다.');
assert.equal(aggregateSummary.constraints.feasible, outcome.constraints.feasible, '경량 상한 평가의 hard constraint 판정은 전체 평가와 같아야 합니다.');
assert.equal(JSON.stringify(baseInput), original, '경량 상한 평가도 호출자의 기본 컨텍스트를 변경하면 안 됩니다.');

const longRangeDefaults = evaluator.defaultRequirements(base({ rangeType:'LONG', godspeedWieldLevel:10 }));
assert.equal(longRangeDefaults.maxHp, null, '원거리 기본 빌드는 MAXHP 최소 조건이 없어야 합니다.');
assert.equal(longRangeDefaults.maxMp, 2300, '신속의 수도 Lv.10은 버프 전 MAXMP 2300을 요구해야 합니다.');

const invalidBuild = evaluator.createBuildSnapshot(base(), [{ name:'unknown', stats:{ NOT_A_REAL_STAT:1 } }]);
const invalid = evaluator.evaluate(invalidBuild, evaluator.createScenarioSnapshot(base(), { requirements:{ maxHp:null, maxMp:null, amprBeforeDual:null, normalAttackCrit:null, aspd:null } }), context.window.ToramCalculationKernel.evaluateContext);
assert.equal(invalid.constraints.feasible, false, '알 수 없는 스탯 키가 있으면 최적화 입력을 유효하다고 처리하면 안 됩니다.');
assert.equal(invalid.diagnostics[0].key, 'NOT_A_REAL_STAT', '누락된 스탯 키 이름을 진단에 보존해야 합니다.');

const evaluatorSource = await readFile(resolve(root, 'assets/js/build-evaluator.js'), 'utf8');
assert.doesNotMatch(evaluatorSource, /\bdocument\b|localStorage/, 'BuildEvaluator 내부에서 DOM이나 localStorage를 읽으면 안 됩니다.');

console.log('D4 evaluator stage 1 regressions: PASS');
