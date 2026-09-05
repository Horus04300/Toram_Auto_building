import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const evaluator = require(resolve(root, 'assets/js/build-evaluator.js'));
const compiler = require(resolve(root, 'assets/js/d4-problem-compiler.js'));
const sourceProfile = require(resolve(root, 'assets/js/d4-source-profile.js'));
const dynamicMarginal = require(resolve(root, 'assets/js/d4-dynamic-marginal.js'));
const dynamicSeed = require(resolve(root, 'assets/js/d4-dynamic-seed.js'));
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));

const context = { window:{ ToramStatRegistry:registry }, console };
context.window.window = context.window;
vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', context);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculation-policies.js'), 'utf8'), context, { filename:'calculation-policies.js' });
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'calculator.js' });

function base(overrides={}) {
  return Object.assign({
    level:100, strBase:200, intBase:0, vitBase:0, agiBase:0, dexBase:200, crtBase:0,
    mainType:'한손검', wpnAtk:200, wpnRefine:0, wpnStab:100, subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'경량옷',
    bossLevel:100, bossDef:100, bossMdef:100, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
    skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'SHORT', optimizationBasisName:'Stage 2 fixture',
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
}

function scenario(ctx, requirements={ maxHp:null, maxMp:null, amprBeforeDual:null, normalAttackCrit:null, aspd:null }) {
  return evaluator.createScenarioSnapshot(ctx, { requirements });
}

const syntheticCrystas = [
  { name:'공용 공격', category:'노말', stats:{ ATKP:3 } },
  { name:'무기 구형', category:'무기', stats:{ ATKP:6 } },
  { name:'무기 신형', category:'무기', stats:{ ATKP:12 }, prev:'무기 구형' },
  { name:'무기 분기', category:'무기', stats:{ CDMG:12 }, prev:'무기 구형' },
  { name:'조건부 무기', category:'무기', stats:{ ATKP:4 }, condStats:[{ cond:{ main:'한손검' }, stats:{ SRW:7 } }] },
  { name:'방어 딜HP', category:'방어구', stats:{ ATKP:7, MaxHP:7000 } },
  { name:'방어 순수딜', category:'방어구', stats:{ SRW:10 } },
  { name:'추가 집중속도', category:'추가', stats:{ ASPD_P:80, ATKP:7 } },
  { name:'추가 순수딜', category:'추가', stats:{ CDMG:10 } },
  { name:'특수 집중MP', category:'특수', stats:{ MaxMP:1800, AMPR:70 } },
  { name:'특수 순수딜', category:'특수', stats:{ ATKP:8 } }
];

const syntheticWasFrozen = Object.isFrozen(syntheticCrystas[0]);
const baseContext = base({ maxHpF:10000, maxMpF:1800, amprF:70, aspdF:900, critF:75 });
const compiled = compiler.compileCrystaProblem({
  crystas:syntheticCrystas,
  registry,
  baseContext,
  scenarioSnapshot:scenario(baseContext),
  currentCrystas:[], locks:[]
});
assert.deepEqual(compiled.diagnostics, [], '합성 후보 문제는 진단 없이 컴파일돼야 합니다.');
assert.equal(Object.isFrozen(syntheticCrystas[0]), syntheticWasFrozen, '후보 컴파일러는 호출자가 준 크리스타 객체를 동결하거나 변경하면 안 됩니다.');
assert.ok(compiled.metadata.removedLowerUpgradeCount >= 1, '최적화 후보에서 하위 강화 크리스타를 제거해야 합니다.');
assert.ok(compiled.groups[0].packages.every(item => !item.candidateNames.includes('무기 구형')), '상위 후보가 있으면 하위 강화 후보를 남기지 않아야 합니다.');
assert.ok(compiled.groups[0].packages.every(item => !(item.candidateNames.includes('무기 신형') && item.candidateNames.includes('무기 분기'))), '같은 시작점의 분기 강화는 같은 장비에서 함께 장착할 수 없어야 합니다.');
const conditionalPackage = compiled.groups[0].packages.find(item => item.candidateNames.includes('조건부 무기'));
assert.equal(conditionalPackage.statDelta.SRW, 7, '장비 구조 조건은 후보 생성 때 일반 스탯 벡터로 사전 합산해야 합니다.');
assert.ok(compiled.groups.every(group => group.packages.some(item => item.candidateNames.includes('공용 공격'))), '공용 크리스타는 네 장비 부위에서 각각 후보가 될 수 있어야 합니다.');

const commonOptions = {
  registry,
  evaluator,
  kernel:context.window.ToramCalculationKernel.evaluateContext,
  sourceProfile,
  pareto:{ maxComparisons:500000 }
};
const oracle = optimizer.exhaustiveSearch(compiled, commonOptions);
const greedy = optimizer.findGreedyInitialSolution(compiled, Object.assign({}, commonOptions, { skipParetoPreparation:true }));
assert.equal(greedy.status, 'heuristic', '결과 탭의 빠른 추천은 Greedy 초기해 상태를 반환해야 합니다.');
assert.ok(greedy.bestBuild && greedy.outcomes?.constraints?.feasible, 'Greedy 초기해도 하드 요구조건을 만족해야 합니다.');
assert.equal(greedy.upperBound, null, '빠른 추천은 전역 상한을 계산한 것처럼 표시하면 안 됩니다.');
assert.equal(greedy.optimalityGap, null, '빠른 추천은 최적성 오차를 계산한 것처럼 표시하면 안 됩니다.');
assert.equal(greedy.visitedNodes, 0, '빠른 추천은 branch-and-bound 노드를 방문하지 않아야 합니다.');
assert.ok(greedy.score <= oracle.score, 'Greedy 초기해는 전수조사 최적값을 초과할 수 없습니다.');
const solved = optimizer.optimize(compiled, commonOptions);
assert.equal(solved.status, 'exact', '소형 8슬롯 문제는 전역 최적임을 증명해야 합니다.');
assert.equal(solved.score, oracle.score, '전역 탐색 결과는 원시 전수조사 최적값과 같아야 합니다.');
assert.equal(solved.bestBuild.id, oracle.bestBuild.id, '동점일 때도 결정적인 동일 조합을 선택해야 합니다.');
const dynamicSolved = optimizer.optimize(compiled, Object.assign({}, commonOptions, {
  enableDynamicSeedIncumbent:true,
  dynamicSeed,
  dynamicMarginal,
  dynamicSeedTimeLimitMs:5000,
  dynamicSeedEvaluationLimit:200,
  dynamicSeedLocalEvaluationLimit:200,
  dynamicSeedCartesianLimit:256,
  dynamicSeedBeamWidth:16,
  dynamicSeedLocalStartLimit:2,
  dynamicSeedLocalPassLimit:1,
  dynamicSeedLocalCandidateLimit:3,
  dynamicSeedLocalPairCandidateLimit:2,
  enableDynamicSeedOrdering:true
}));
assert.equal(dynamicSolved.status, 'exact', 'S4 ON small fixture must still prove exactness.');
assert.equal(dynamicSolved.score, oracle.score, 'S4 ON must preserve the exact oracle score.');
assert.equal(dynamicSolved.bestBuild.id, oracle.bestBuild.id, 'S4 ON must preserve exact tie ordering.');
assert.equal(dynamicSolved.dynamicSeedReport?.used, true, 'S4 ON must report merged dynamic seed work.');
assert.equal(dynamicSolved.dynamicSeedReport?.orderingEnabled, true, 'S5 ON must be recorded as an explicit experiment.');
assert.match(dynamicSolved.dynamicSeedReport?.candidateOrderHash || '', /^[0-9a-f]{8}$/, 'S5 must report a deterministic candidate order hash.');
assert.ok(dynamicSolved.seedTelemetry.phases.some(phase => phase.name === 'dynamicSeedIncumbent'), 'S4 ON must record a dynamic seed telemetry phase.');

const orderedPrepared = optimizer.prepareProblem(compiled, commonOptions);
const orderingProfile = dynamicMarginal.createDynamicMarginalProfile(orderedPrepared, commonOptions);
const dynamicCandidateOrder = dynamicSeed.createDynamicCandidateOrder(orderingProfile);
const orderingOracle = optimizer.exhaustiveSearch(orderedPrepared, Object.assign({}, commonOptions, { prepared:true }));
const orderedSolved = optimizer.optimize(orderedPrepared, Object.assign({}, commonOptions, { prepared:true, dynamicCandidateOrder }));
assert.equal(orderedSolved.status, 'exact', 'S5 ordered small fixture must still prove exactness.');
assert.equal(orderedSolved.score, orderingOracle.score, 'S5 order must preserve the exact oracle score.');
assert.equal(orderedSolved.bestBuild.id, orderingOracle.bestBuild.id, 'S5 order must preserve the exact tie ordering.');
assert.equal(orderedSolved.dynamicCandidateOrderHash, dynamicCandidateOrder.orderHash, 'S5 result must identify the order used.');
const permutedPrepared = Object.freeze(Object.assign({}, orderedPrepared, { groups:Object.freeze(orderedPrepared.groups.map(group => Object.freeze(Object.assign({}, group, { packages:Object.freeze([...group.packages].reverse()) })))) }));
const permutedProfile = dynamicMarginal.createDynamicMarginalProfile(permutedPrepared, commonOptions);
const permutedOrder = dynamicSeed.createDynamicCandidateOrder(permutedProfile);
const permutedSolved = optimizer.optimize(permutedPrepared, Object.assign({}, commonOptions, { prepared:true, dynamicCandidateOrder:permutedOrder }));
assert.equal(permutedOrder.orderHash, dynamicCandidateOrder.orderHash, 'S5 candidate order must be invariant to package input permutation.');
assert.equal(permutedSolved.status, 'exact', 'S5 permuted small fixture must still prove exactness.');
assert.equal(permutedSolved.score, orderingOracle.score, 'S5 permutation must preserve the exact oracle score.');
assert.equal(permutedSolved.bestBuild.id, orderingOracle.bestBuild.id, 'S5 permutation must preserve exact tie ordering.');
assert.equal(optimizer.verifyCandidateTreeUpperBounds(orderedPrepared, Object.assign({}, commonOptions, { prepared:true, dynamicCandidateOrder })).violations.length, 0, 'S5 ordered tree upper bounds must remain safe.');
assert.equal(optimizer.verifyEnvelopeMonotonicity(orderedPrepared, Object.assign({}, commonOptions, { prepared:true, dynamicCandidateOrder })).violations.length, 0, 'S5 ordered tree envelope must remain monotonic.');

const boundAudit = optimizer.verifyUpperBounds(compiled, commonOptions);
assert.equal(boundAudit.violations.length, 0, '모든 부분해의 안전 상한은 실제 완성해 점수보다 낮아지면 안 됩니다.');
const envelopeAudit = optimizer.verifyEnvelopeMonotonicity(compiled, commonOptions);
assert.equal(envelopeAudit.violations.length, 0, '상위 envelope는 모든 자식 envelope보다 낮아지면 안 됩니다.');

function pkg(id, slot, stats) { return Object.freeze({ id, slot, statDelta:Object.freeze(stats), evaluatorCandidates:[], candidateNames:[id] }); }
const constrainedBase = base();
const constrainedProblem = Object.freeze({
  schema:compiler.schema,
  baseContext:constrainedBase,
  scenarioSnapshot:evaluator.createScenarioSnapshot(constrainedBase),
  diagnostics:[], metadata:{},
  groups:Object.freeze([
    Object.freeze({ id:'weapon', packages:Object.freeze([pkg('weapon-damage','weapon',{ATKP:20}),pkg('weapon-crit','weapon',{CRIT:75})]) }),
    Object.freeze({ id:'armor', packages:Object.freeze([pkg('armor-damage','armor',{SRW:20}),pkg('armor-hp','armor',{MAXHP:10000})]) }),
    Object.freeze({ id:'additional', packages:Object.freeze([pkg('additional-damage','additional',{CDMG:20}),pkg('additional-speed','additional',{ASPD:800})]) }),
    Object.freeze({ id:'special', packages:Object.freeze([pkg('special-damage','special',{ATKP:20}),pkg('special-resource','special',{MAXMP:1800,AMPR:70})]) })
  ])
});
const constrained = optimizer.optimize(constrainedProblem, commonOptions);
assert.equal(constrained.status, 'exact', 'Utility 경계가 있는 소형 문제도 정확해를 찾아야 합니다.');
assert.deepEqual(constrained.bestBuild.packages.map(item => item.id), ['weapon-crit','armor-hp','additional-speed','special-resource'], '대미지가 더 높아도 기본 hard constraint를 어기는 후보는 제외해야 합니다.');
assert.equal(constrained.outcomes.constraints.feasible, true, '추천 결과는 모든 기본 Utility 요구치를 만족해야 합니다.');

const speedBase = base({ maxHpF:10000, maxMpF:1800, amprF:70, critF:75 });
const speedProblem = Object.freeze({
  schema:compiler.schema, baseContext:speedBase, scenarioSnapshot:evaluator.createScenarioSnapshot(speedBase), diagnostics:[], metadata:{},
  groups:Object.freeze([
    Object.freeze({ id:'additional', packages:Object.freeze([pkg('집중 ASPD','additional',{ASPD:800}),pkg('추가 딜','additional',{ATKP:20})]) }),
    Object.freeze({ id:'weapon', packages:Object.freeze([pkg('분산 ASPD 1','weapon',{ASPD:400}),pkg('무기 딜','weapon',{ATKP:15})]) }),
    Object.freeze({ id:'special', packages:Object.freeze([pkg('분산 ASPD 2','special',{ASPD:400}),pkg('특수 딜','special',{ATKP:15})]) })
  ])
});
const speedSolved = optimizer.optimize(speedProblem, commonOptions);
assert.deepEqual(speedSolved.bestBuild.packages.map(item => item.id), ['집중 ASPD','무기 딜','특수 딜'], 'ASPD는 큰 획득처 하나로 요구량을 채우고 다른 슬롯을 대미지에 쓰는 기회비용을 반영해야 합니다.');

let randomState = 0x5eed1234;
function random() { randomState = (Math.imul(randomState, 1664525) + 1013904223) >>> 0; return randomState / 0x100000000; }
const randomKeys = ['ATKP','SRW','CDMG','CRIT','MAXHP','MAXMP','AMPR','ASPD'];
for (let fixture=0; fixture<20; fixture++) {
  const randomBase = base({ maxHpF:10000, maxMpF:1800, amprF:70, aspdF:900, critF:75 });
  const groups = [];
  for (let groupIndex=0; groupIndex<3; groupIndex++) {
    const packages = [];
    for (let candidateIndex=0; candidateIndex<3; candidateIndex++) {
      const stats = {};
      for (const key of randomKeys) if (random() > 0.55) stats[key] = Math.floor(random() * (key === 'MAXHP' ? 2000 : key === 'MAXMP' || key === 'ASPD' ? 300 : 12));
      packages.push(pkg(`r${fixture}-${groupIndex}-${candidateIndex}`, `g${groupIndex}`, stats));
    }
    groups.push(Object.freeze({ id:`g${groupIndex}`, packages:Object.freeze(packages) }));
  }
  const randomProblem = Object.freeze({ schema:compiler.schema, baseContext:randomBase, scenarioSnapshot:scenario(randomBase), diagnostics:[], metadata:{}, groups:Object.freeze(groups) });
  const randomOracle = optimizer.exhaustiveSearch(randomProblem, commonOptions);
  const randomSolved = optimizer.optimize(randomProblem, commonOptions);
  assert.equal(randomSolved.status, 'exact', `무작위 fixture ${fixture}는 정확해를 증명해야 합니다.`);
  assert.equal(randomSolved.score, randomOracle.score, `무작위 fixture ${fixture}의 solver 점수는 전수조사와 같아야 합니다.`);
  assert.equal(randomSolved.bestBuild.id, randomOracle.bestBuild.id, `무작위 fixture ${fixture}의 동점 순서도 전수조사와 같아야 합니다.`);
  const randomBounds = optimizer.verifyUpperBounds(randomProblem, commonOptions);
  assert.equal(randomBounds.violations.length, 0, `무작위 fixture ${fixture}의 안전 상한 위반은 0건이어야 합니다.`);
  const randomTreeBounds = optimizer.verifyCandidateTreeUpperBounds(randomProblem, commonOptions);
  const randomEnvelope = optimizer.verifyEnvelopeMonotonicity(randomProblem, commonOptions);
  assert.equal(randomEnvelope.violations.length, 0, '무작위 fixture '+fixture+'의 상위 envelope 단조성 위반은 0건이어야 합니다.');
  assert.equal(randomTreeBounds.violations.length, 0, `무작위 fixture ${fixture}의 계층형 후보 상한 위반은 0건이어야 합니다.`);
}

const negativeBase = base({ maxHpF:10000, maxMpF:1800, amprF:70, aspdF:1000, critF:100 });
const negativeProblem = Object.freeze({
  schema:compiler.schema, baseContext:negativeBase, scenarioSnapshot:scenario(negativeBase), diagnostics:[], metadata:{},
  groups:Object.freeze([
    Object.freeze({ id:'weapon', packages:Object.freeze([pkg('음수 공격','weapon',{ATKP:-10,SRW:8}),pkg('양수 공격','weapon',{ATKP:3})]) }),
    Object.freeze({ id:'armor', packages:Object.freeze([pkg('음수 거리','armor',{SRW:-12,CDMG:20}),pkg('양수 거리','armor',{SRW:4})]) })
  ])
});
const negativeOracle = optimizer.exhaustiveSearch(negativeProblem, commonOptions);
const negativeSolved = optimizer.optimize(negativeProblem, commonOptions);
assert.equal(negativeSolved.score, negativeOracle.score, '음수 옵션이 섞인 계층형 탐색도 전수조사 최적값과 같아야 합니다.');
assert.equal(negativeSolved.bestBuild.id, negativeOracle.bestBuild.id, '음수 옵션 문제의 동점 순서도 전수조사와 같아야 합니다.');
assert.equal(optimizer.verifyCandidateTreeUpperBounds(negativeProblem, commonOptions).violations.length, 0, '음수 옵션 후보 상자의 안전 상한 위반은 0건이어야 합니다.');

const fixedResourceBase = base({ maxHpF:10000, maxMpF:1800, amprF:70, aspdF:900, critF:75 });
const fixedResourceProblem = Object.freeze({
  schema:compiler.schema, baseContext:fixedResourceBase, scenarioSnapshot:evaluator.createScenarioSnapshot(fixedResourceBase), diagnostics:[], metadata:{},
  groups:Object.freeze([Object.freeze({ id:'special', packages:Object.freeze([
    pkg('이미 충족된 MP만 추가','special',{MAXMP:500}), pkg('대미지 획득','special',{ATKP:5})
  ]) })])
});
const fixedAdapter = stats => evaluator.evaluate(evaluator.createBuildSnapshot(fixedResourceBase,[{name:'fixed-resource',stats}]),fixedResourceProblem.scenarioSnapshot,context.window.ToramCalculationKernel.evaluateContext);
const relevantAfterFixed = optimizer.deriveRelevantKeys(fixedResourceProblem, registry, fixedAdapter);
assert.ok(!relevantAfterFixed.includes('MAXMP'), '비경쟁 획득량으로 MAXMP 요구치를 안전하게 채운 경우 MAXMP 전용 축은 후보 지배 판정에서 빠져야 합니다.');
assert.equal(optimizer.optimize(fixedResourceProblem, commonOptions).bestBuild.packages[0].id, '대미지 획득', '이미 충족된 Utility만 더 주는 후보보다 남은 슬롯의 대미지 후보를 선택해야 합니다.');


const relevanceStats = {
  ATKP:1, ATK:1, MATKP:1, MATK:1, SRW:1, LRW:1, UNSHEATHEP:1,
  PHYS_PIERCE:1, MAG_PIERCE:1, ATK_UP_STR:1, MATK_UP_INT:1
};
function relevanceKeysFor(ctx) {
  const problem = Object.freeze({
    schema:compiler.schema,
    baseContext:ctx,
    scenarioSnapshot:scenario(ctx),
    diagnostics:[],
    metadata:{},
    groups:Object.freeze([Object.freeze({ id:'relevance', packages:Object.freeze([pkg('관련 축','relevance',relevanceStats)]) })])
  });
  const adapter = stats => evaluator.evaluate(evaluator.createBuildSnapshot(ctx,[{name:'relevance',stats}]),problem.scenarioSnapshot,context.window.ToramCalculationKernel.evaluateContext);
  return optimizer.deriveRelevantKeys(problem, registry, adapter);
}
const physicalShortKeys = relevanceKeysFor(base({ atkType:'PHYS', rangeType:'SHORT' }));
assert.ok(physicalShortKeys.includes('ATKP') && physicalShortKeys.includes('ATK_UP_STR') && physicalShortKeys.includes('PHYS_PIERCE') && physicalShortKeys.includes('SRW'), '물리·근거리 시나리오는 ATK·물리관통·근거리 축을 유지해야 합니다.');
assert.ok(!physicalShortKeys.includes('MATKP') && !physicalShortKeys.includes('MATK_UP_INT') && !physicalShortKeys.includes('MAG_PIERCE') && !physicalShortKeys.includes('LRW') && !physicalShortKeys.includes('UNSHEATHEP'), '물리·근거리·비발도 시나리오는 사용하지 않는 마법·원거리·발도 축을 제외해야 합니다.');
const magicLongKeys = relevanceKeysFor(base({ atkType:'MAG', rangeType:'LONG' }));
assert.ok(magicLongKeys.includes('MATKP') && magicLongKeys.includes('MATK_UP_INT') && magicLongKeys.includes('MAG_PIERCE') && magicLongKeys.includes('LRW'), '마법·원거리 시나리오는 MATK·마법관통·원거리 축을 유지해야 합니다.');
assert.ok(!magicLongKeys.includes('ATKP') && !magicLongKeys.includes('ATK_UP_STR') && !magicLongKeys.includes('PHYS_PIERCE') && !magicLongKeys.includes('SRW'), '마법·원거리 시나리오는 사용하지 않는 물리·근거리 축을 제외해야 합니다.');
const blendedKeys = relevanceKeysFor(base({ atkType:'MAG', rangeType:'SHORT', attackPowerMode:'sum', useHigherRangeDamage:true, chkIsUnsheathe:true }));
assert.ok(['ATKP','MATKP','SRW','LRW','UNSHEATHEP'].every(key => blendedKeys.includes(key)), 'ATK+MATK·높은 거리위력·발도 시나리오는 양쪽 공격축과 거리축·발도축을 모두 유지해야 합니다.');
const conversionKeys = relevanceKeysFor(base({ chkIsUnsheathe:false, activeBuildConversions:[{ conversion:'unsheatheToAtk', value:1 }] }));
assert.ok(conversionKeys.includes('UNSHEATHEP'), '일진강풍 발도→ATK 변환이 있으면 비발도 타격이어도 발도 옵션 축을 유지해야 합니다.');

const unsheatheContext = base({ chkIsUnsheathe:true, bossDef:0 });
const unsheatheScenario = scenario(unsheatheContext);
function evaluateCrystas(crystas) {
  return evaluator.evaluate(evaluator.createBuildSnapshot(unsheatheContext, crystas), unsheatheScenario, context.window.ToramCalculationKernel.evaluateContext);
}
const threePastUnsheathe = evaluateCrystas([1,2,3].map(index => ({ name:'과거 발도 '+index, stats:{ UNSHEATHEP:18 } })));
const fourPastUnsheathe = evaluateCrystas([1,2,3,4].map(index => ({ name:'과거 발도 '+index, stats:{ UNSHEATHEP:18 } })));
const fourthGain = fourPastUnsheathe.damage.expected / threePastUnsheathe.damage.expected - 1;
assert.ok(Math.abs(fourthGain - 0.11668273866923817) < 1e-12, '과거 발도 18% 네 번째의 기회비용 fixture는 원문 변환 후 약 11.67% 증가여야 합니다.');
assert.ok(sourceProfile.deltaLogDamage(threePastUnsheathe.damage.expected, fourPastUnsheathe.damage.expected) > Math.log(1.11), '획득처 비교는 단순 옵션 수치가 아니라 로그 한계 대미지를 사용해야 합니다.');

const axis = sourceProfile.attackEquivalentAxis(4000, 2000, 0);
assert.equal(axis.axisPercentPoint, 50, 'BaseATK 4000·DEF 2000의 공격력 등가축은 50%p여야 합니다.');
assert.equal(sourceProfile.pierceEquivalentAttackPercent(4000, 2000, 10), 5, '같은 조건의 물리관통 10%p는 ATK 5%p 등가여야 합니다.');
const residual = sourceProfile.residualRequirements(constrained.outcomes, constrainedProblem.scenarioSnapshot.requirements);
assert.equal(residual.residual.maxMp, 0, '명시된 현재 획득량으로 요구치를 채우면 해당 Utility 부족분은 0이어야 합니다.');

const crystaSource = await readFile(resolve(root, 'assets/js/data/crysta-data.js'), 'utf8');
const dataContext = {};
vm.createContext(dataContext);
vm.runInContext(`${crystaSource}\nglobalThis.__crystas = crystaDataJson;`, dataContext);
const compileStart = performance.now();
const fullProblem = compiler.compileCrystaProblem({ crystas:dataContext.__crystas, registry, baseContext, scenarioSnapshot:scenario(baseContext), currentCrystas:[], locks:[], banned:{ '오로로 콜론':true } });
const compileMs = performance.now() - compileStart;
assert.equal(fullProblem.diagnostics.length, 0, '실제 425개 크리스타도 미등록 조건·스탯 없이 후보 문제로 컴파일돼야 합니다.');
assert.equal(fullProblem.groups.length, 4, '실제 크리스타 문제는 2슬롯 장비 네 부위로 컴파일돼야 합니다.');
assert.ok(fullProblem.groups.every(group => group.packages.length > 0), '실제 각 부위에 유효한 크리스타 쌍 후보가 있어야 합니다.');

console.log(`D4 global optimizer stage 2 regressions: PASS (oracle ${oracle.evaluations}, solver ${solved.evaluations}, bounds ${boundAudit.checked}, full compile ${compileMs.toFixed(1)}ms)`);
