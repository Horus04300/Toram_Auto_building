import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import { Worker } from 'node:worker_threads';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const evaluator = require(resolve(root, 'assets/js/build-evaluator.js'));
const compiler = require(resolve(root, 'assets/js/d4-problem-compiler.js'));
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));
const workerClientApi = require(resolve(root, 'assets/js/d4-worker-client.js'));

class NodeWebWorker {
  constructor() {
    this.worker = new Worker(resolve(root, 'tools/d4-node-web-worker-runner.cjs'), { workerData:{ scriptRoot:resolve(root, 'assets/js') } });
    this.worker.on('message', data => { if (this.onmessage) this.onmessage({ data }); });
    this.worker.on('error', error => { if (this.onerror) this.onerror(error); });
  }
  postMessage(message) { this.worker.postMessage(message); }
  terminate() { return this.worker.terminate(); }
}

const calculationContext = { window:{ ToramStatRegistry:registry }, console };
calculationContext.window.window = calculationContext.window;
vm.createContext(calculationContext);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', calculationContext);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), calculationContext, { filename:'calculator.js' });

const baseContext = {
  level:325, strBase:255, intBase:0, vitBase:0, agiBase:0, dexBase:500, crtBase:0,
  mainType:'한손검', wpnAtk:600, wpnRefine:15, wpnStab:80, subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'경량옷',
  bossLevel:325, bossDef:2000, bossMdef:2000, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
  skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'SHORT', optimizationBasisName:'P1 parallel 425 benchmark',
  chkIsUnsheathe:false, chkGuaranteedCrit:false, conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false, spellBurstLevel:0, godspeedWieldLevel:0,
  poisonSources:[], weakenSources:[], targetWeakened:false, attackElement:'none', attackPowerMode:'default', useHigherRangeDamage:false,
  noCritical:false, criticalChanceBonus:0, criticalChanceMultiplier:1, fixedCriticalChance:null, minimumCriticalDamage:0, stabilityBonus:0, physicalPierceSkillBonus:0, magicPierceSkillBonus:0, ignoreDefense:false, ignoreMdef:false, halfMdefIgnored:false,
  strP:0, strF:0, dexP:0, dexF:0, intP:0, intF:0, agiP:0, agiF:0, vitP:0, vitF:0,
  atkP:0, atkF:0, matkP:0, matkF:0, cdmgP:0, cdmgF:0, critP:0, critF:200, srw:0, lrw:0, unsheatheP:0, unsheatheF:0, elemP:0, damageP:0, watkP:0, watkF:0,
  physPierce:0, magPierce:0, aspdF:3000, aspdP:0, cspdF:0, cspdP:0, stability:0, motionSpeed:0, castRed:0,
  maxHpF:20000, maxHpP:0, maxMpF:3000, amprF:200, amprP:0, elementAwakening:false, magicElement:false,
  atkUpSTR:0, atkUpDEX:0, atkUpINT:0,atkUpAGI:0,atkUpVIT:0,matkUpSTR:0,matkUpDEX:0,matkUpINT:0,matkUpAGI:0,matkUpVIT:0,
  preservedStats:{}, statDiagnostics:[], activeBuildConversions:[]
};
const dataContext = {};
vm.createContext(dataContext);
vm.runInContext(`${await readFile(resolve(root, 'assets/js/data/crysta-data.js'), 'utf8')}\nglobalThis.__crystas=crystaDataJson;`, dataContext);
const scenario = evaluator.createScenarioSnapshot(baseContext);
const compiledAt = performance.now();
const problem = compiler.compileCrystaProblem({ crystas:dataContext.__crystas, registry, baseContext, scenarioSnapshot:scenario, currentCrystas:[], locks:[], banned:{ '오로로 콜론':true } });
const compileMs = performance.now() - compiledAt;
const threads = Math.max(1, Math.floor(Number(process.env.D4_PARALLEL_THREADS) || 1));
const timeLimitMs = Math.max(100, Math.floor(Number(process.env.D4_TIME_LIMIT_MS) || 5000));
const shardFactor = Math.max(1, Math.floor(Number(process.env.D4_PARALLEL_SHARD_FACTOR) || 8));
const enableDynamicSeed = process.env.D4_ENABLE_DYNAMIC_SEED === '1';
if (process.env.D4_PARALLEL_PLAN_ONLY === '1') {
  const plannedAt = performance.now();
  const plan = optimizer.createParallelShardPlan(problem, {
    registry, evaluator, kernel:calculationContext.window.ToramCalculationKernel.evaluateContext,
    targetShards:threads * shardFactor, maxParetoComparisons:1000000
  });
  console.log(JSON.stringify({ schema:'d4-parallel-p1-plan.v1', threads, shardFactor, compileMs:Number(compileMs.toFixed(1)), planMs:Number((performance.now() - plannedAt).toFixed(1)), status:plan.status, shards:plan.shards?.length, totalCombinations:plan.totalCombinations }));
  process.exit(0);
}
const client = new workerClientApi.ParallelWorkerClient({ WorkerConstructor:NodeWebWorker, hardwareConcurrency:threads });
const result = await client.optimize(problem, {}, {
  timeLimitMs,
  parallelShardFactor:shardFactor,
  enableDynamicSeedIncumbent:enableDynamicSeed,
  maxParetoComparisons:1000000
});
console.log(JSON.stringify({
  schema:'d4-parallel-p1-benchmark.v1', threads, shardFactor, enableDynamicSeed, compileMs:Number(compileMs.toFixed(1)),
  status:result.status, elapsedMs:result.elapsedMs, workerThreads:result.workerThreads, totalShards:result.totalShards,
  completedShards:result.completedShards, score:result.score, lowerBound:result.lowerBound, upperBound:result.upperBound,
  optimalityGap:result.optimalityGap, evaluations:result.evaluations, visitedNodes:result.visitedNodes, diagnostics:result.diagnostics
}));
