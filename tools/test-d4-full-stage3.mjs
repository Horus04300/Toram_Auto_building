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
const pairPartition = require(resolve(root, 'assets/js/d4-pair-partition.js'));
const dynamicMarginal = require(resolve(root, 'assets/js/d4-dynamic-marginal.js'));
const dynamicSeed = require(resolve(root, 'assets/js/d4-dynamic-seed.js'));
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));

const context = { window:{ ToramStatRegistry:registry }, console };
context.window.window = context.window;
vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', context);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'calculator.js' });

const baseContext = {
  level:325, strBase:255, intBase:0, vitBase:0, agiBase:0, dexBase:500, crtBase:0,
  mainType:'한손검', wpnAtk:600, wpnRefine:15, wpnStab:80, subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'경량옷',
  bossLevel:325, bossDef:2000, bossMdef:2000, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
  skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'SHORT', optimizationBasisName:'전체 후보 성능 회귀',
  chkIsUnsheathe:false, chkGuaranteedCrit:false, conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false, spellBurstLevel:0, godspeedWieldLevel:0,
  poisonSources:[], weakenSources:[], targetWeakened:false, attackElement:'none', attackPowerMode:'default', useHigherRangeDamage:false,
  noCritical:false, criticalChanceBonus:0, criticalChanceMultiplier:1, fixedCriticalChance:null, minimumCriticalDamage:0, stabilityBonus:0, physicalPierceSkillBonus:0, magicPierceSkillBonus:0, ignoreDefense:false, ignoreMdef:false, halfMdefIgnored:false,
  strP:0, strF:0, dexP:0, dexF:0, intP:0, intF:0, agiP:0, agiF:0, vitP:0, vitF:0,
  atkP:0, atkF:0, matkP:0, matkF:0, cdmgP:0, cdmgF:0, critP:0, critF:200, srw:0, lrw:0, unsheatheP:0, unsheatheF:0, elemP:0, damageP:0, watkP:0, watkF:0,
  physPierce:0, magPierce:0, aspdF:3000, aspdP:0, cspdF:0, cspdP:0, stability:0, motionSpeed:0, castRed:0,
  maxHpF:20000, maxHpP:0, maxMpF:3000, amprF:200, amprP:0, elementAwakening:false, magicElement:false,
  atkUpSTR:0, atkUpDEX:0, atkUpINT:0, atkUpAGI:0, atkUpVIT:0, matkUpSTR:0, matkUpDEX:0, matkUpINT:0, matkUpAGI:0, matkUpVIT:0,
  preservedStats:{}, statDiagnostics:[], activeBuildConversions:[]
};

const dataContext = {};
vm.createContext(dataContext);
vm.runInContext(`${await readFile(resolve(root, 'assets/js/data/crysta-data.js'), 'utf8')}\nglobalThis.__crystas=crystaDataJson;`, dataContext);
const scenario = evaluator.createScenarioSnapshot(baseContext);
const compileStarted = performance.now();
const problem = compiler.compileCrystaProblem({ crystas:dataContext.__crystas, registry, baseContext, scenarioSnapshot:scenario, currentCrystas:[], locks:[], banned:{ '오로로 콜론':true } });
const proofReductionEnabled = process.env.D4_ENABLE_PROVEN_DROP_AUDIT === '1';
let optimizationProblem = problem;
let proofReductionReport = null;
if (proofReductionEnabled) {
  const preparedForProof = optimizer.prepareProblem(problem, { registry, pareto:{ maxComparisons:1000000 } });
  const proofAdapter = stats => evaluator.evaluateAggregate(baseContext, preparedForProof.scenarioSnapshot, stats, context.window.ToramCalculationKernel.evaluateContext);
  proofReductionReport = sourceProfile.createReplacementProofReport(preparedForProof, proofAdapter, { maxComparisons:5000000 });
  assert.equal(proofReductionReport.complete, true, 'S7 proof-reduction audit must finish its proof scan.');
  optimizationProblem = sourceProfile.applyProvenDropsForAudit(problem, proofReductionReport);
}
const compileMs = performance.now() - compileStarted;
if (process.env.D4_AUDIT_ENVELOPE === '1') {
  const envelopeAudit = optimizer.verifyEnvelopeMonotonicity(problem, { registry, evaluator, kernel:context.window.ToramCalculationKernel.evaluateContext, pareto:{ maxComparisons:1000000 } });
  console.log('D4 envelope monotonicity: ' + JSON.stringify({ checked:envelopeAudit.checked, violations:envelopeAudit.violations.length, samples:envelopeAudit.violations.slice(0, 3) }));
}
let progressCount = 0;
const timeLimitMs = Number(process.env.D4_TIME_LIMIT_MS) > 0 ? Number(process.env.D4_TIME_LIMIT_MS) : 5000;
const dynamicSeedEnabled = process.env.D4_ENABLE_DYNAMIC_SEED === '1';
const result = optimizer.optimize(optimizationProblem, {
  registry,
  evaluator,
  kernel:context.window.ToramCalculationKernel.evaluateContext,
  sourceProfile,
  pareto:{ maxComparisons:1000000 },
  smallBoxEnumerationLimit:process.env.D4_SMALL_BOX_LIMIT === undefined ? 64 : Number(process.env.D4_SMALL_BOX_LIMIT),
  splitDimensions:process.env.D4_SPLIT_DIMENSIONS === undefined ? 2 : Number(process.env.D4_SPLIT_DIMENSIONS),
  enablePairCorrelationBounds:process.env.D4_ENABLE_PAIR_CORRELATION === '1',
  pairCorrelationClustersPerGroup:process.env.D4_PAIR_CORRELATION_CLUSTERS === undefined ? undefined : Number(process.env.D4_PAIR_CORRELATION_CLUSTERS),
  enableBoundGuidedSplit:process.env.D4_ENABLE_BOUND_GUIDED_SPLIT === "1",
  boundGuidedSplitLevels:process.env.D4_BOUND_GUIDED_SPLIT_LEVELS === undefined ? undefined : Number(process.env.D4_BOUND_GUIDED_SPLIT_LEVELS),
  enablePairStreamBounds:process.env.D4_ENABLE_PAIR_STREAM === "1",
  pairStreamPivotKey:process.env.D4_PAIR_STREAM_KEY === undefined ? undefined : process.env.D4_PAIR_STREAM_KEY,
  pairStreamBucketCount:process.env.D4_PAIR_STREAM_BUCKETS === undefined ? undefined : Number(process.env.D4_PAIR_STREAM_BUCKETS),
  enableDynamicSeedIncumbent:dynamicSeedEnabled,
  dynamicSeed:dynamicSeedEnabled ? dynamicSeed : undefined,
  dynamicMarginal:dynamicSeedEnabled ? dynamicMarginal : undefined,
  enableDynamicSeedOrdering:dynamicSeedEnabled && process.env.D4_ENABLE_DYNAMIC_ORDER !== '0',
  dynamicSeedTimeLimitMs:dynamicSeedEnabled ? (Number(process.env.D4_DYNAMIC_SEED_TIME_MS) || 1500) : undefined,
  dynamicSeedEvaluationLimit:dynamicSeedEnabled ? (Number(process.env.D4_DYNAMIC_SEED_EVALUATIONS) || 10000) : undefined,
  dynamicSeedLocalEvaluationLimit:dynamicSeedEnabled ? 1000 : undefined,
  dynamicSeedCartesianLimit:dynamicSeedEnabled ? 64 : undefined,
  dynamicSeedBeamWidth:dynamicSeedEnabled ? 32 : undefined,
  dynamicSeedRepairInputLimit:dynamicSeedEnabled ? 2 : undefined,
  dynamicSeedRepairPerGroupLimit:dynamicSeedEnabled ? 4 : undefined,
  dynamicSeedRepairPairLimit:dynamicSeedEnabled ? 3 : undefined,
  dynamicSeedLocalStartLimit:dynamicSeedEnabled ? 2 : undefined,
  dynamicSeedLocalPassLimit:dynamicSeedEnabled ? 1 : undefined,
  dynamicSeedLocalCandidateLimit:dynamicSeedEnabled ? 4 : undefined,
  dynamicSeedLocalPairCandidateLimit:dynamicSeedEnabled ? 2 : undefined,
  timeLimitMs,
  collectSearchProfile:process.env.D4_COLLECT_SEARCH_PROFILE === '1',
  progressIntervalMs:32,
  onProgress:() => progressCount++
});

assert.ok(['exact','bounded'].includes(result.status), '425개 실제 후보는 5초 안에 exact 또는 gap이 있는 bounded 결과를 반환해야 합니다.');
assert.ok(result.bestBuild && result.outcomes && result.outcomes.constraints.feasible, '시간 제한 결과에도 Utility를 만족하는 유효 추천이 있어야 합니다.');
assert.ok(result.status === 'exact' || Number.isFinite(result.optimalityGap), 'bounded 결과는 인증된 최적성 gap을 포함해야 합니다.');
assert.ok(progressCount >= 2, '실제 전체 후보 탐색도 진행 스냅샷을 전달해야 합니다.');
assert.ok(result.elapsedMs < timeLimitMs + 2500, '자동 탐색은 정리 비용을 포함해 설정 시간 예산을 과도하게 초과하면 안 됩니다.');
assert.ok(result.firstFeasibleMs < 500, '실제 전체 후보에서도 첫 유효 추천은 500ms 안에 확보해야 합니다.');
assert.ok(result.lowerBound >= 13500, '실제 후보 초기해와 탐색 결과는 고정 성능 기준 13500 이상이어야 합니다.');
assert.ok(result.optimalityGap <= .75, '실제 후보 5초 인증 gap은 75% 이하여야 합니다.');
assert.ok(result.boundTreeNodes > 0, '계층형 후보 상한 트리가 실제 탐색에 구성돼야 합니다.');
if (dynamicSeedEnabled) { assert.equal(result.dynamicSeedReport?.used, true, 'S4 실험 ON은 실제 후보에서 dynamic seed incumbent 보고서를 반환해야 합니다.'); assert.equal(result.dynamicSeedReport?.orderingEnabled, process.env.D4_ENABLE_DYNAMIC_ORDER !== '0', 'S5 실험 ON 여부는 report에 명시해야 합니다.'); if (process.env.D4_ENABLE_DYNAMIC_ORDER !== '0') assert.match(result.dynamicSeedReport?.candidateOrderHash || '', /^[0-9a-f]{8}$/, 'S5는 실제 후보에도 결정적 순서 hash를 반환해야 합니다.'); }
if (process.env.D4_COLLECT_SEARCH_PROFILE === '1') { const profile=result.searchProfile; assert.equal(profile?.schema, 'd4-search-profile.v1', 'Gate F 계측 ON은 검색 profile을 반환해야 합니다.'); const counted=Object.entries(profile.counters || {}).filter(([key]) => key.startsWith('evaluate:')).reduce((total, [,value]) => total + Number(value), 0); assert.equal(counted, result.evaluations, 'Gate F 평가 분류 합계는 전체 평가 횟수와 일치해야 합니다.'); assert.ok(Number(profile.sections?.['evaluate:bound']) > 0, 'Gate F 실제 fixture는 상한 평가 비용을 계측해야 합니다.'); }
assert.ok(result.frontierReports.every(report => report.complete), '실제 후보 Pareto 축약은 부위별 100만 비교 안에 완결돼야 합니다.');
assert.equal(result.seedTelemetry && result.seedTelemetry.schema, 'd4-initial-seed-telemetry.v1', 'S0은 초기해 계측 계약을 반환해야 합니다.');
const seedPhases = new Map(result.seedTelemetry.phases.map(phase => [phase.name, phase]));
['rawInitial:utility','rawInitial:damage','preparedInitial:utility','preparedInitial:damage','coordinateSearch','pairLowerBound','heuristicComplete','rootBound'].forEach(name => assert.ok(seedPhases.has(name), 'S0은 '+name+' 단계를 기록해야 합니다.'));
const rootTelemetry = seedPhases.get('rootBound');
assert.equal(rootTelemetry.evaluations >= result.heuristicEvaluations, true, 'root 상한은 heuristic 완료 뒤에 계측해야 합니다.');
assert.ok(Number.isFinite(rootTelemetry.lowerBound) && Number.isFinite(rootTelemetry.upperBound), 'root 계측에는 실제 LB와 안전 UB가 있어야 합니다.');
assert.deepEqual(result.seedTelemetry.checkpointTargetsMs, [100,500,1000,5000,10000], 'S0 기본 checkpoint 시각은 기준선 비교에 고정해야 합니다.');
assert.ok([100,500,1000,5000].every(target => result.seedTelemetry.checkpoints.some(sample => sample.targetElapsedMs === target)), '실제 425개 5초 실행은 경과 checkpoint를 모두 기록해야 합니다.');
console.log("D4 full metrics: " + JSON.stringify({lowerBound:result.lowerBound,upperBound:result.upperBound,visitedNodes:result.visitedNodes,remainingNodes:result.remainingNodes,prunedByBound:result.prunedByBound,prunedByConstraint:result.prunedByConstraint,enumeratedBoxes:result.enumeratedBoxes,enumeratedCompletions:result.enumeratedCompletions,firstFeasibleMs:result.firstFeasibleMs,heuristicEvaluations:result.heuristicEvaluations,boundTreeNodes:result.boundTreeNodes,boundFrontierHead:result.boundFrontierHead,frontiers:result.frontierReports,searchProfile:result.searchProfile,proofReduction:proofReductionReport&&{reportHash:proofReductionReport.reportHash,provenDropCount:proofReductionReport.provenDrops.length,complete:proofReductionReport.complete},seedTelemetry:result.seedTelemetry}));
console.log(`D4 full stage 3: PASS (${result.status}, gap ${result.optimalityGap === null ? '-' : (result.optimalityGap * 100).toFixed(3) + '%'}, ${result.evaluations} evals, compile ${compileMs.toFixed(1)}ms, solve ${result.elapsedMs}ms, progress ${progressCount})`);
