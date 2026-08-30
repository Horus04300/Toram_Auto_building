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
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));
const pairs = require(resolve(root, 'assets/js/d4-pair-partition.js'));

const context = { window:{ ToramStatRegistry:registry }, console };
context.window.window = context.window;
vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', context);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'calculator.js' });

const baseContext = {
  level:325, strBase:255, intBase:0, vitBase:0, agiBase:0, dexBase:500, crtBase:0,
  mainType:'한손검', wpnAtk:600, wpnRefine:15, wpnStab:80, subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'경량옷',
  bossLevel:325, bossDef:2000, bossMdef:2000, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
  skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'SHORT', optimizationBasisName:'SupplyDifficulty fixture',
  chkIsUnsheathe:false, chkGuaranteedCrit:false, conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false, spellBurstLevel:0, godspeedWieldLevel:0,
  poisonSources:[], weakenSources:[], targetWeakened:false, attackElement:'none', attackPowerMode:'default', useHigherRangeDamage:false,
  noCritical:false, criticalChanceBonus:0, criticalChanceMultiplier:1, fixedCriticalChance:null, minimumCriticalDamage:0, stabilityBonus:0, physicalPierceSkillBonus:0, magicPierceSkillBonus:0, ignoreDefense:false, ignoreMdef:false, halfMdefIgnored:false,
  strP:0, strF:0, dexP:0, dexF:0, intP:0, intF:0, agiP:0, agiF:0, vitP:0, vitF:0,
  atkP:0, atkF:0, matkP:0, matkF:0, cdmgP:0, cdmgF:0, critP:0, critF:0, srw:0, lrw:0, unsheatheP:0, unsheatheF:0, elemP:0, damageP:0, watkP:0, watkF:0,
  physPierce:0, magPierce:0, aspdF:0, aspdP:0, cspdF:0, cspdP:0, stability:0, motionSpeed:0, castRed:0,
  maxHpF:0, maxHpP:0, maxMpF:0, amprF:0, amprP:0, elementAwakening:false, magicElement:false,
  atkUpSTR:0, atkUpDEX:0, atkUpINT:0, atkUpAGI:0, atkUpVIT:0, matkUpSTR:0, matkUpDEX:0, matkUpINT:0, matkUpAGI:0, matkUpVIT:0,
  preservedStats:{}, statDiagnostics:[], activeBuildConversions:[]
};

const dataContext = {};
vm.createContext(dataContext);
vm.runInContext((await readFile(resolve(root, 'assets/js/data/crysta-data.js'), 'utf8')) + '\nglobalThis.__crystas=crystaDataJson;', dataContext);
const scenario = evaluator.createScenarioSnapshot(baseContext);
const problem = compiler.compileCrystaProblem({ crystas:dataContext.__crystas, registry, baseContext, scenarioSnapshot:scenario, currentCrystas:[], locks:[], banned:{ '오로로 콜론':true } });
const kernel = context.window.ToramCalculationKernel.evaluateContext;
const evaluateStats = stats => evaluator.evaluate(evaluator.createBuildSnapshot(baseContext,[{ name:'supply', stats }]), scenario, kernel);
const started = performance.now();
const report = sourceProfile.analyzeSupplyDifficulty(problem, evaluateStats);
const relevantKeys = optimizer.deriveRelevantKeys(problem, registry, evaluateStats);
const prepared = optimizer.prepareProblem(problem, { registry, relevantKeys, pareto:{ maxComparisons:1000000 } });
const pairReport = pairs.analyzePairPartitions(problem, report, { preparedProblem:prepared, pairMaterializationLimit:250000 });
const elapsedMs = performance.now() - started;
const partitions = pairReport.partitions.map(item => ({
  id:item.id, mode:item.mode, splitUtilityCount:item.splitUtilityCount, singleSideCoverageScore:item.singleSideCoverageScore,
  maxPreparedPairCandidates:item.maxPreparedPairCandidates, totalPreparedPairCandidates:item.totalPreparedPairCandidates,
  maxRawPairCandidates:item.maxRawPairCandidates, totalRawPairCandidates:item.totalRawPairCandidates, frontierStatus:item.frontierStatus
}));
if (process.env.D4_PAIR_PROFILE === '1' && pairReport.selection) {
  const partition = pairReport.partitions.find(item => item.id === pairReport.selection.id);
  const comparisonLimit = Number(process.env.D4_PAIR_PROFILE_MAX_COMPARISONS) > 0 ? Number(process.env.D4_PAIR_PROFILE_MAX_COMPARISONS) : 1000000;
  const profiles = [];
  for (const pair of partition.pairs || []) {
    const left = prepared.groups.find(group => group.id === pair.groups[0]);
    const right = prepared.groups.find(group => group.id === pair.groups[1]);
    const materializedStarted = performance.now();
    const entries = [];
    for (const leftPackage of left.packages) for (const rightPackage of right.packages) entries.push({ id:String(leftPackage.id) + '||' + String(rightPackage.id), statDelta:optimizer.addStats(leftPackage.statDelta, rightPackage.statDelta) });
    const materializedMs = performance.now() - materializedStarted;
    const paretoStarted = performance.now();
    const frontier = optimizer.strictParetoFrontier(entries, relevantKeys, { maxComparisons:comparisonLimit });
    const paretoMs = performance.now() - paretoStarted;
    profiles.push({ pairId:pair.id, inputCount:entries.length, materializedMs:Number(materializedMs.toFixed(1)), paretoMs:Number(paretoMs.toFixed(1)), outputCount:frontier.outputCount, duplicateCount:frontier.duplicateCount, comparisons:frontier.comparisons, complete:frontier.complete });
  }
  console.log('D4 pair profiles: ' + JSON.stringify({ comparisonLimit, profiles }));
}

if (Number(process.env.D4_PAIR_STREAM_BUCKETS) > 1 && pairReport.selection) {
  const bucketCount = Math.floor(Number(process.env.D4_PAIR_STREAM_BUCKETS));
  const pivotKey = process.env.D4_PAIR_STREAM_KEY || 'CRIT';
  const partition = pairReport.partitions.find(item => item.id === pairReport.selection.id);
  const profiles = [];
  for (const pair of partition.pairs || []) {
    const left = prepared.groups.find(group => group.id === pair.groups[0]);
    const right = prepared.groups.find(group => group.id === pair.groups[1]);
    const vectors = group => group.packages.map(item => relevantKeys.map(key => Number(item.statDelta[key]) || 0));
    const leftVectors = vectors(left), rightVectors = vectors(right);
    const pivotIndex = relevantKeys.indexOf(pivotKey);
    if (pivotIndex < 0) throw new Error('Unknown stream pivot key: ' + pivotKey);
    let low = Infinity, high = -Infinity;
    for (const vector of leftVectors) for (const other of rightVectors) { const value = vector[pivotIndex] + other[pivotIndex]; if (value < low) low = value; if (value > high) high = value; }
    const envelopes = Array.from({ length:bucketCount }, () => Array(relevantKeys.length).fill(-Infinity));
    const counts = Array(bucketCount).fill(0);
    const started = performance.now();
    const span = high - low;
    for (const vector of leftVectors) for (const other of rightVectors) {
      const value = vector[pivotIndex] + other[pivotIndex];
      const bucket = span <= 0 ? 0 : Math.min(bucketCount - 1, Math.floor((value - low) / span * bucketCount));
      counts[bucket]++;
      const envelope = envelopes[bucket];
      for (let keyIndex = 0; keyIndex < envelope.length; keyIndex++) { const total = vector[keyIndex] + other[keyIndex]; if (total > envelope[keyIndex]) envelope[keyIndex] = total; }
    }
    profiles.push({ pairId:pair.id, inputCount:leftVectors.length * rightVectors.length, pivotKey, pivotRange:[low, high], bucketCount, nonemptyBuckets:counts.filter(count => count > 0).length, elapsedMs:Number((performance.now() - started).toFixed(1)), counts });
  }
  console.log('D4 pair stream buckets: ' + JSON.stringify({ profiles }));
}

console.log('D4 pair partitions: ' + JSON.stringify({ policyVersion:pairReport.policyVersion, elapsedMs:Number(elapsedMs.toFixed(1)), rawGroupCounts:pairReport.rawGroupCounts, preparedGroupCounts:pairReport.preparedGroupCounts, selection:pairReport.selection, partitions }));
