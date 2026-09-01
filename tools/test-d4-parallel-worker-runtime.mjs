import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import { Worker } from 'node:worker_threads';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const evaluator = require(resolve(root, 'assets/js/build-evaluator.js'));
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));
const workerClientApi = require(resolve(root, 'assets/js/d4-worker-client.js'));
const calculationContext = { window:{ ToramStatRegistry:registry }, console };
calculationContext.window.window = calculationContext.window;
vm.createContext(calculationContext);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', calculationContext);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculation-policies.js'), 'utf8'), calculationContext, { filename:'calculation-policies.js' });
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), calculationContext, { filename:'calculator.js' });

class NodeWebWorker {
  constructor() {
    this.worker = new Worker(resolve(root, 'tools/d4-node-web-worker-runner.cjs'), { workerData:{ scriptRoot:resolve(root, 'assets/js') } });
    this.worker.on('message', data => { if (this.onmessage) this.onmessage({ data }); });
    this.worker.on('error', error => { if (this.onerror) this.onerror(error); });
  }
  postMessage(message) { this.worker.postMessage(message); }
  terminate() { return this.worker.terminate(); }
}

function base(overrides={}) {
  return Object.assign({
    level:100, strBase:200, intBase:0, vitBase:0, agiBase:0, dexBase:200, crtBase:0,
    mainType:'한손검', wpnAtk:200, wpnRefine:0, wpnStab:100, subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'경량옷',
    bossLevel:100, bossDef:100, bossMdef:100, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
    skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'SHORT', optimizationBasisName:'Parallel worker runtime fixture',
    chkIsUnsheathe:false, chkGuaranteedCrit:false, conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false, spellBurstLevel:0, godspeedWieldLevel:0,
    poisonSources:[], weakenSources:[], targetWeakened:false, attackElement:'none', attackPowerMode:'default', useHigherRangeDamage:false,
    noCritical:false, criticalChanceBonus:0, criticalChanceMultiplier:1, fixedCriticalChance:null, minimumCriticalDamage:0,
    stabilityBonus:0, physicalPierceSkillBonus:0, magicPierceSkillBonus:0, ignoreDefense:false, ignoreMdef:false, halfMdefIgnored:false,
    strP:0, strF:0, dexP:0, dexF:0, intP:0, intF:0, agiP:0, agiF:0, vitP:0, vitF:0,
    atkP:0, atkF:0, matkP:0, matkF:0, cdmgP:0, cdmgF:0, critP:0, critF:75, srw:0, lrw:0, unsheatheP:0, unsheatheF:0, elemP:0, damageP:0, watkP:0, watkF:0,
    physPierce:0, magPierce:0, aspdF:1000, aspdP:0, cspdF:0, cspdP:0, stability:0, motionSpeed:0, castRed:0,
    maxHpF:10000, maxHpP:0, maxMpF:1800, amprF:70, amprP:0, elementAwakening:false, magicElement:false,
    atkUpSTR:0, atkUpDEX:0, atkUpINT:0, atkUpAGI:0, atkUpVIT:0, matkUpSTR:0, matkUpDEX:0, matkUpINT:0, matkUpAGI:0, matkUpVIT:0,
    preservedStats:{}, statDiagnostics:[], activeBuildConversions:[]
  }, overrides);
}
function pkg(id, slot, stats) { return { id, slot, statDelta:stats, evaluatorCandidates:[], candidateNames:[id] }; }

const baseContext = base();
const scenario = evaluator.createScenarioSnapshot(baseContext, { requirements:{ maxHp:null, maxMp:null, amprBeforeDual:null, normalAttackCrit:null, aspd:null } });
const problem = {
  schema:'toram.d4-problem.v1', baseContext, scenarioSnapshot:scenario, diagnostics:[], metadata:{},
  groups:[
    { id:'weapon', packages:[pkg('w0','weapon',{ATKP:1}),pkg('w1','weapon',{ATKP:4}),pkg('w2','weapon',{CDMG:8}),pkg('w3','weapon',{SRW:3})] },
    { id:'armor', packages:[pkg('a0','armor',{ATKP:2}),pkg('a1','armor',{CDMG:12}),pkg('a2','armor',{SRW:5}),pkg('a3','armor',{PHYS_PIERCE:4})] },
    { id:'special', packages:[pkg('s0','special',{ATKP:3}),pkg('s1','special',{CDMG:6}),pkg('s2','special',{SRW:7}),pkg('s3','special',{PHYS_PIERCE:6})] }
  ]
};

const client = new workerClientApi.ParallelWorkerClient({ WorkerConstructor:NodeWebWorker, workerUrl:'ignored-by-node-adapter', hardwareConcurrency:2 });
const progress = [];
const result = await client.optimize(problem, { onProgress:snapshot => progress.push(snapshot) }, {
  timeLimitMs:10000,
  parallelShardFactor:4,
  enableDynamicSeedIncumbent:false,
  maxParetoComparisons:100000
});
const expected = optimizer.optimize(problem, { registry, evaluator, kernel:calculationContext.window.ToramCalculationKernel.evaluateContext, disablePareto:true });
assert.equal(result.status, 'exact', '실제 Worker pool의 모든 작은 shard 완료는 exact여야 합니다.');
assert.equal(result.score, expected.score, '실제 Worker pool 병합 점수는 단일 solver와 같아야 합니다.');
assert.equal(result.bestBuild.id, expected.bestBuild.id, '실제 Worker pool 병합은 동점 build ID 규칙을 보존해야 합니다.');
assert.equal(result.workerThreads, 2, '실제 Worker pool은 주어진 논리 스레드 수를 사용해야 합니다.');
assert.equal(result.totalShards, 8, '실제 Worker pool은 동적 target shard 수를 사용해야 합니다.');
assert.ok(progress.some(snapshot => snapshot.stage === 'parallel-search'), '실제 shard 진행률을 병합해 전달해야 합니다.');
console.log(`D4 parallel Worker runtime: PASS (${result.workerThreads} workers, ${result.totalShards} shards, exact ${result.score})`);
