import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import { spawn } from 'node:child_process';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const evaluator = require(resolve(root, 'assets/js/build-evaluator.js'));
const compiler = require(resolve(root, 'assets/js/d4-problem-compiler.js'));
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));

function runNative(problem, binary='d4_native_exact') {
  return new Promise((resolvePromise, reject) => {
    const child = spawn('cargo', ['run', '--release', '--quiet', '--manifest-path', 'src-tauri/Cargo.toml', '--bin', binary], { cwd:root, stdio:['pipe','pipe','pipe'] });
    let stdout = '', stderr = '';
    child.stdout.on('data', chunk => { stdout += chunk; });
    child.stderr.on('data', chunk => { stderr += chunk; });
    child.on('error', reject);
    child.on('close', code => {
      if (code !== 0) return reject(new Error(`native exact exited ${code}: ${stderr}`));
      try { resolvePromise(JSON.parse(stdout)); } catch (error) { reject(new Error(`native exact returned invalid JSON: ${error.message}\n${stdout}\n${stderr}`)); }
    });
    child.stdin.end(JSON.stringify(problem));
  });
}

const context = { window:{ ToramStatRegistry:registry }, console };
context.window.window = context.window;
vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', context);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculation-policies.js'), 'utf8'), context, { filename:'calculation-policies.js' });
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'calculator.js' });
const kernel = context.window.ToramCalculationKernel.evaluateContext;

const small = {
  baseContext:{level:100,strBase:0,intBase:0,vitBase:100,agiBase:0,dexBase:0,crtBase:0,mainType:'한손검',subType:'없음',armorType:'일반옷',wpnAtk:100,wpnRefine:0,wpnStab:100,subAtk:0,subRefine:0,subStab:0,critF:100,atkType:'PHYS',rangeType:'SHORT',bossLevel:100,bossDef:0,bossMdef:0,bossCritResist:0,bossPhysResist:0,bossMagResist:0,skillMult:1,skillConst:0,procDamageModifiers:[],chkIsUnsheathe:false,chkGuaranteedCrit:false,conversionLevel:0,dualBringerLevel:0,dualBringerActive:false,spellBurstLevel:0,targetWeakened:false,attackElement:'none',attackPowerMode:'default',useHigherRangeDamage:false,noCritical:false,criticalChanceBonus:0,criticalChanceMultiplier:1,fixedCriticalChance:null,minimumCriticalDamage:0,stabilityBonus:0,physicalPierceSkillBonus:0,magicPierceSkillBonus:0,ignoreDefense:false,ignoreMdef:false,halfMdefIgnored:false,strP:0,strF:0,dexP:0,dexF:0,intP:0,intF:0,agiP:0,agiF:0,vitP:0,vitF:0,atkP:0,atkF:0,matkP:0,matkF:0,cdmgP:0,cdmgF:0,critP:0,srw:0,lrw:0,unsheatheP:0,unsheatheF:0,elemP:0,damageP:0,watkP:0,watkF:0,baseWpnAtkF:0,physPierce:0,magPierce:0,aspdF:1000,aspdP:0,stability:0,maxHpF:10000,maxHpP:0,maxMpF:2000,amprF:100,amprP:0,elementAwakening:false,magicElement:false,atkUpSTR:0,atkUpDEX:0,atkUpINT:0,atkUpAGI:0,atkUpVIT:0,matkUpSTR:0,matkUpDEX:0,matkUpINT:0,matkUpAGI:0,matkUpVIT:0,activeBuildConversions:[]},
  scenarioSnapshot:{requirements:{maxHp:null,maxMp:null,amprBeforeDual:null,normalAttackCrit:null,aspd:null}},
  groups:[
    {id:'weapon',packages:[{id:'weapon:a',statDelta:{ATKP:1}},{id:'weapon:z',statDelta:{ATKP:1}}]},
    {id:'armor',packages:[{id:'armor:a',statDelta:{SRW:1}},{id:'armor:b',statDelta:{SRW:2}}]},
    {id:'additional',packages:[{id:'additional:a',statDelta:{CRIT:1}},{id:'additional:b',statDelta:{CRIT:2}}]},
    {id:'special',packages:[{id:'special:a',statDelta:{CDMG:1}},{id:'special:b',statDelta:{CDMG:2}}]}
  ]
};
const smallJs = optimizer.exhaustiveSearch(small, { prepared:small, evaluateStats:stats => evaluator.evaluateAggregate(small.baseContext, small.scenarioSnapshot, stats, kernel) });
const smallNative = await runNative(small);
assert.equal(smallNative.status, 'exact');
assert.equal(smallNative.score, smallJs.score, 'small native exact score must equal JS oracle');
assert.equal(smallNative.bestBuild.id, smallJs.bestBuild.id, 'small native exact tie must equal JS oracle');
for (const threads of [1, 2, 16, 64]) {
  const parallel = await runNative({ ...small, threads }, 'd4_native_parallel');
  assert.equal(parallel.status, 'exact', `parallel ${threads}-thread small solver must exhaust its shards`);
  assert.equal(parallel.score, smallJs.score, `parallel ${threads}-thread score must equal JS oracle`);
  assert.equal(parallel.bestBuild.id, smallJs.bestBuild.id, `parallel ${threads}-thread tie must equal JS oracle`);
  assert.equal(parallel.completedShards, parallel.scheduledShards, `parallel ${threads}-thread solver must complete every shard`);
}

if (process.env.D4_P4_REAL !== '1') {
  console.log(`D4 P5 small native exact: PASS (${smallNative.evaluations} evaluations)`);
  process.exit(0);
}

const baseContext = {
  level:325, strBase:255, intBase:0, vitBase:0, agiBase:0, dexBase:500, crtBase:0,
  mainType:'한손검', wpnAtk:600, wpnRefine:15, wpnStab:80, subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'경량옷',
  bossLevel:325, bossDef:2000, bossMdef:2000, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
  skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'SHORT', chkIsUnsheathe:false, chkGuaranteedCrit:false,
  conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false, spellBurstLevel:0, godspeedWieldLevel:0,
  poisonSources:[], weakenSources:[], targetWeakened:false, attackElement:'none', attackPowerMode:'default', useHigherRangeDamage:false,
  noCritical:false, criticalChanceBonus:0, criticalChanceMultiplier:1, fixedCriticalChance:null, minimumCriticalDamage:0, stabilityBonus:0, physicalPierceSkillBonus:0, magicPierceSkillBonus:0, ignoreDefense:false, ignoreMdef:false, halfMdefIgnored:false,
  strP:0,strF:0,dexP:0,dexF:0,intP:0,intF:0,agiP:0,agiF:0,vitP:0,vitF:0,atkP:0,atkF:0,matkP:0,matkF:0,cdmgP:0,cdmgF:0,critP:0,critF:200,srw:0,lrw:0,unsheatheP:0,unsheatheF:0,elemP:0,damageP:0,watkP:0,watkF:0,baseWpnAtkF:0,physPierce:0,magPierce:0,aspdF:3000,aspdP:0,cspdF:0,cspdP:0,stability:0,motionSpeed:0,castRed:0,maxHpF:20000,maxHpP:0,maxMpF:3000,amprF:200,amprP:0,elementAwakening:false,magicElement:false,
  atkUpSTR:0,atkUpDEX:0,atkUpINT:0,atkUpAGI:0,atkUpVIT:0,matkUpSTR:0,matkUpDEX:0,matkUpINT:0,matkUpAGI:0,matkUpVIT:0,preservedStats:{},statDiagnostics:[],activeBuildConversions:[]
};
const dataContext = {};
vm.createContext(dataContext);
vm.runInContext(`${await readFile(resolve(root, 'assets/js/data/crysta-data.js'), 'utf8')}\nglobalThis.__crystas=crystaDataJson;`, dataContext);
const scenario = evaluator.createScenarioSnapshot(baseContext);
const compiled = compiler.compileCrystaProblem({ crystas:dataContext.__crystas, registry, baseContext, scenarioSnapshot:scenario, currentCrystas:[], locks:[], banned:{'오로로 콜론':true} });
const adapter = stats => evaluator.evaluateAggregate(baseContext, scenario, stats, kernel);
const relevantKeys = optimizer.deriveRelevantKeys(compiled, registry, adapter);
const prepared = optimizer.prepareProblem(compiled, { registry, relevantKeys, pareto:{maxComparisons:1000000} });
assert.ok(prepared.metadata.paretoReports.every(report => report.complete), 'P4 real fixture requires completed Pareto preparation');
const native = await runNative(prepared);
assert.equal(native.status, 'exact', 'P4 real native solver must exhaust its candidate tree');
assert.equal(native.score, 14097, 'P4 real native exact score must match the established JS exact fixture');
const requestedThreads = Number(process.env.D4_P5_THREADS) || undefined;
const parallel = await runNative({ ...prepared, threads:requestedThreads }, 'd4_native_parallel');
assert.equal(parallel.status, 'exact', 'P5 real native solver must exhaust every shared-memory shard');
assert.equal(parallel.score, native.score, 'P5 real parallel score must equal the native single-thread exact result');
assert.equal(parallel.bestBuild.id, native.bestBuild.id, 'P5 real parallel tie result must equal the native single-thread exact result');
assert.equal(parallel.completedShards, parallel.scheduledShards, 'P5 real parallel run must complete every scheduled shard');
if (process.env.D4_P4_VERIFY_JS === '1') {
  const jsExact = optimizer.optimize(prepared, {
    prepared,
    registry,
    relevantKeys,
    evaluateStats:adapter,
    smallBoxEnumerationLimit:64,
    splitDimensions:2,
    timeLimitMs:0
  });
  assert.equal(jsExact.status, 'exact', 'P4 comparison must re-run the current JS exact search to exhaustion');
  assert.equal(native.score, jsExact.score, 'P4 native exact score must equal the current JS exact result');
  assert.equal(native.bestBuild.id, jsExact.bestBuild.id, 'P4 native exact tie result must equal the current JS exact result');
}
console.log(`D4 P5 real native exact: PASS (${native.score}, single ${native.elapsedMs}ms, parallel ${parallel.elapsedMs}ms, ${parallel.threadsUsed} threads, ${parallel.scheduledShards} shards)`);
