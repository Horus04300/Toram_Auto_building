import {statRegistry as registry} from '../../../web/src/calculation/stat-registry.js';
import {buildEvaluator as evaluator} from '../../../web/src/calculation/build-evaluator.js';
import {problemCompiler as compiler} from '../../../web/src/optimization/problem-compiler.js';
import {candidatePreparation as candidates} from '../../../web/src/optimization/candidate-preparation.js';
import {calculationKernel} from '../../../web/src/calculation/calculator.js';
import {exhaustiveSearch} from '../../support/crysta-exhaustive-oracle.mjs';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {spawn} from 'node:child_process';
import {projectNativeProblem} from '../../support/crysta-native-payload-helper.mjs';
import {loadSavedBuildEnvironment} from '../../support/saved-build-headless-environment.mjs';
import {loadHeadlessEnvironment} from '../../support/crysta-headless-environment.mjs';

const root = resolve(import.meta.dirname, '../../..');

function runNative(problem, binary='crysta_native_exact', session=false) {
  return new Promise((resolvePromise, reject) => {
    const child = spawn('cargo', ['run', '--release', '--quiet', '--manifest-path', 'engine/Cargo.toml', '--bin', binary], { cwd:root, stdio:['pipe','pipe','pipe'], env:{...process.env, ...(session ? {OPTIMIZATION_SESSION_BENCH_MS:'30000'} : {})} });
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
const kernel = calculationKernel.evaluateContext;

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
const smallJs = exhaustiveSearch(small, { prepared:small, evaluateStats:stats => evaluator.evaluateAggregate(small.baseContext, small.scenarioSnapshot, stats, kernel) });
const smallNative = await runNative(small);
const smallCompact = await runNative(projectNativeProblem(small));
assert.equal(smallCompact.status, smallNative.status);
assert.equal(smallCompact.score, smallNative.score);
assert.deepEqual(smallCompact.bestBuild, smallNative.bestBuild);
assert.equal(smallNative.status, 'exact');
assert.equal(smallNative.score, smallJs.score, 'small native exact score must equal JS oracle');
assert.equal(smallNative.bestBuild.id, smallJs.bestBuild.id, 'small native exact tie must equal JS oracle');
for (const threads of [1, 2, 16, 64]) {
  const parallel = await runNative({ ...small, threads }, 'crysta_native_parallel');
  assert.equal(parallel.status, 'exact', `parallel ${threads}-thread small solver must exhaust its shards`);
  assert.equal(parallel.score, smallJs.score, `parallel ${threads}-thread score must equal JS oracle`);
  assert.equal(parallel.bestBuild.id, smallJs.bestBuild.id, `parallel ${threads}-thread tie must equal JS oracle`);
  assert.equal(parallel.completedShards, parallel.scheduledShards, `parallel ${threads}-thread solver must complete every shard`);
}

if (process.env.OPTIMIZATION_REAL_CANDIDATES !== '1') {
  // Native/JS parity alone cannot detect a buff omitted by Application.
  const savedEnv = await loadSavedBuildEnvironment();
  const savedText = await readFile(resolve(root, 'samples/미완성 서포터 세팅 (톱스타 포툼 없음) - oo o.json'), 'utf8');
  const sample = savedEnv.ToramSettingsRepository.parseSavedBuild(savedText);
  const original = JSON.stringify(sample);
  savedEnv.skillSimulatorState = { getInvestments:() => sample.build.skillLevels };
  const env = await loadHeadlessEnvironment({});
  const slots = ['mainWeapon','armor','additional','special'];
  for (const active of [true,false]) {
    sample.build.activeBuffs['Magic:22'].active = active;
    const current = savedEnv.ToramApplication.CalculateBuild(sample);
    assert.equal(current.snapshot.baseContext.motionSpeed, active ? 25 : 0);
    assert.equal(current.calculation.finalASPD,6999);
    assert.equal(current.calculation.finalMotionSpeed,active ? 50 : 37);
    const input = {baseContext:current.snapshot.baseContext,
      scenarioRequirements:sample.scenario.optimizationPreferences.requirements,
      currentCrystas:slots.flatMap(slot=>sample.build.equipment[slot].crystas),
      locks:slots.flatMap(slot=>sample.build.equipment[slot].lockedCrystaSlots),
      banned:Object.fromEntries(sample.scenario.optimizationPreferences.bannedCrystas.map(name=>[name,true]))};
    assert.equal(input.locks.filter(Boolean).length,7);
    assert.equal(input.scenarioRequirements.aspd,10000);
    assert.equal(input.scenarioRequirements.maxMp,2000);
    const problem = env.compile(input);
    assert.equal(problem.groups[0].packages[0].statDelta.MOTIONSPEED,3);
    assert.equal(problem.groups[1].packages[0].statDelta.MOTIONSPEED,1);
    const oracle = exhaustiveSearch(problem,{prepared:true,
      evaluateStats:stats=>env.evaluator.evaluateAggregate(problem.baseContext,problem.scenarioSnapshot,stats,env.kernel.evaluateContext)});
    assert.equal(oracle.evaluations,problem.groups.reduce((count,group)=>count*group.packages.length,1),'Oracle must enumerate every live-catalog completion of the unlocked slot');
    assert.equal(oracle.status,active ? 'exact' : 'invalid');
    if(active) assert.equal(oracle.outcomes.utility.motionSpeed,50);
    for (const [binary,session] of [['crysta_native_exact',false],['crysta_native_parallel',true]]) {
      const native = await runNative({...problem,threads:8},binary,session);
      assert.equal(native.status,oracle.status);
      assert.equal(native.score,oracle.score);
      assert.equal(native.bestBuild?.id,oracle.bestBuild?.id);
    }
  }
  sample.build.activeBuffs['Magic:22'].active = true;
  assert.equal(JSON.stringify(sample),original,'Preserve supplied build and original requirements');
  for (const patch of [{},{atkType:'MAG',mainType:'지팡이',subType:'마도구',attackPowerMode:'sum'},
    {subType:'한손검(듀얼소드)',subAtk:400,subStab:80,attackPowerMode:'higher'}]) {
    const future={...small,baseContext:{...small.baseContext,...patch,strBase:327,intBase:320,agiBase:300,dexBase:400,vitBase:50,
      cspdF:0,cspdP:0,castRed:0,motionSpeed:0,bossDef:800,bossMdef:800,aspdF:1000,critF:100},
      scenarioSnapshot:{requirements:{maxHp:10000,maxMp:2000,amprBeforeDual:100,normalAttackCrit:100,aspd:4000}},
      groups:small.groups.map((group,g)=>({...group,packages:Array.from({length:3},(_,p)=>({id:`future-${g}-${p}`,statDelta:{
        ATKP:p===0?17:0,ATK:p===1?130:0,PHYS_PIERCE:p===2?17:0,MATKP:p===0?13:0,MATK:p===1?150:0,MAG_PIERCE:p===2?19:0,
        STRP:p*3,STR:7-p*3,AGIP:9-p*2,AGI:p*7,INTP:p*2,INT:5-p*2,DEXP:3,DEX:p,VITP:p,VIT:3-p,
        WATKP:p*3,WATK:11-p,CDMGP:p*5,CDMG:17-p*2,CRITP:p*3,CRIT:9-p*2,
        ASPD_P:p*9,ASPD:300-p*100,MOTIONSPEED:3-p,CSPD_P:p*7,CSPD:300-p*100,CAST_RED:7-p,
        MAXHPP:p*3,MAXHP:300-p*100,MAXMP:100-p*30,AMPR:7-p,AMPRP:p*2,UNSHEATHEP:p*3,UNSHEATHE:11-p,
        SRW:11-p*3,LRW:p*7,STABILITY:3-p,ELEM_P:p,DAMAGE_P:p,
        ELEM_AWAKENING:p===1?1:0,MAGIC_ELEMENT:p===2?1:0,
        ...Object.fromEntries(['ATK','MATK'].flatMap(kind=>['STR','DEX','AGI','INT','VIT'].map(stat=>[`${kind}_UP_${stat}`,p*1.7])))
      }}))}))};
    const oracle=exhaustiveSearch(future,{prepared:future,evaluateStats:stats=>evaluator.evaluateAggregate(future.baseContext,future.scenarioSnapshot,stats,kernel)});
    assert.ok(oracle.bestBuild,'future supply fixture must have a feasible optimum');
    const serial=await runNative(future);
    assert.equal(serial.score,oracle.score);assert.equal(serial.bestBuild.id,oracle.bestBuild.id);
    for(const threads of [1,8,64]) {
      const result=await runNative({...future,threads},'crysta_native_parallel',true);
      assert.equal(result.status,'exact');assert.equal(result.score,oracle.score);assert.equal(result.bestBuild.id,oracle.bestBuild.id);
    }
  }
  // Joint AMPR/critical supply is active here (unlike utility-rich fixtures).
  // The independent JS exhaustive solver never uses the native support cut.
  for (const contextOverrides of [{}, {atkType:'MAG',mainType:'지팡이',intBase:200}, {mainType:'발도검',chkIsUnsheathe:true}, {subType:'한손검',subAtk:100,subStab:80}]) {
    const joint = {...small, baseContext:{...small.baseContext, ...contextOverrides, critF:0, amprF:0},
      scenarioSnapshot:{requirements:{maxHp:null,maxMp:null,amprBeforeDual:66,normalAttackCrit:100,aspd:null}},
      groups:small.groups.map((group,g) => ({...group, packages:Array.from({length:8},(_,i) => {
        const n = Math.floor(i/2);
        return {id:`${g}-${i}`,statDelta:{AMPR:n*9-3,CRIT:42-n*15,CRITP:i%2 ? 0 : -20,MAXMP:g%2 ? 100 : -100,ATKP:n*7-4,MATKP:n*7-4,SRW:9-n*4,LRW:9-n*4,CDMG:n*3-7}};
      })}))};
    const oracle = exhaustiveSearch(joint,{prepared:joint,evaluateStats:stats => evaluator.evaluateAggregate(joint.baseContext,joint.scenarioSnapshot,stats,kernel)});
    assert.ok(oracle.bestBuild, 'joint fixture must have a feasible optimum');
    for (const threads of [1,8,64]) {
      const native = await runNative({...joint,threads},'crysta_native_parallel',true);
      assert.equal(native.status,'exact');
      assert.equal(native.score,oracle.score);
      assert.equal(native.bestBuild.id,oracle.bestBuild.id);
    }
  }
  for (const contextOverrides of [{}, {atkType:'MAG',mainType:'지팡이',intBase:200}, {mainType:'발도검',chkIsUnsheathe:true}, {subType:'한손검',subAtk:100,subStab:80}]) {
    const signed = {...small,baseContext:{...small.baseContext,...contextOverrides},groups:small.groups.map((group,index) => ({...group,packages:Array.from({length:4},(_,i) => ({id:`${index}-${i}`,statDelta:{ATKP:-12+i*3,MATKP:-12+i*3,SRW:6-i*3,MAXMP:-100-i*20,ASPD:-50-i*10}}))}))};
    const signedOracle = exhaustiveSearch(signed,{prepared:signed,evaluateStats:stats => evaluator.evaluateAggregate(signed.baseContext,signed.scenarioSnapshot,stats,kernel)});
    for (const threads of [1,8,64]) {
      const native = await runNative({...signed,threads},'crysta_native_parallel');
      assert.equal(native.status,'exact');
      assert.equal(native.score,signedOracle.score);
      assert.equal(native.bestBuild.id,signedOracle.bestBuild.id);
    }
  }
  // Search vectors may omit these extras, but every selected raw option must
  // survive serial, parallel and resumable result construction unchanged.
  for (const patch of [{}, {atkType:'MAG',mainType:'지팡이',intBase:200,conversionActive:true,conversionLevel:10,dualBringerActive:true,dualBringerLevel:10}, {subType:'한손검(듀얼소드)',subAtk:100,subStab:80,skillStats:[{stat:'totalVIT',target:'const',ratio:0.5}]}]) {
    const problem = {...small,baseContext:{...small.baseContext,...patch},
      scenarioSnapshot:{requirements:{maxHp:10000,maxMp:2000,amprBeforeDual:100,normalAttackCrit:100,aspd:10000}},
      groups:small.groups.map((group,index)=>({...group,packages:Array.from({length:4},(_,i)=>({id:`${index}-${i}`,statDelta:{ATKP:i*3,MATKP:i*3,MAXHP:-i*100,MAXMP:-i*20,VITP:i,MOTIONSPEED:15-i,DROP_RATE:2+i,PHYS_RES:-3.25,EXP:37+i}}))}))};
    const evaluateStats=stats=>evaluator.evaluateAggregate(problem.baseContext,problem.scenarioSnapshot,stats,kernel);
    const oracle=exhaustiveSearch(problem,{prepared:problem,evaluateStats});
    assert.ok(oracle.bestBuild);
    for (const [binary,session] of [['crysta_native_exact',false],['crysta_native_parallel',false],['crysta_native_parallel',true]]) {
      const native=await runNative({...problem,threads:4},binary,session);
      assert.equal(native.status,'exact');
      assert.equal(native.score,oracle.score);
      assert.equal(native.bestBuild.id,oracle.bestBuild.id);
      const expected={};
      for(let group=0;group<4;group++) {
        const selected=problem.groups[group].packages.find(p=>p.id===native.bestBuild.packageIds[group]);
        assert.ok(selected);
        for(const [key,value] of Object.entries(selected.statDelta))expected[key]=(expected[key]??0)+value;
      }
      assert.deepEqual(native.bestBuild.statDelta,expected);
      const reevaluated=evaluateStats(native.bestBuild.statDelta);
      assert.equal(reevaluated.constraints.feasible,true);
      assert.equal(reevaluated.damage.expected,native.score);
    }
  }
  console.log(`CrystaOptimization native parallel small native exact: PASS (${smallNative.evaluations} evaluations)`);
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
dataContext.__crystas=(await loadSavedBuildEnvironment()).ToramCrystaCatalog.items;
const scenario = evaluator.createScenarioSnapshot(baseContext);
const compiled = compiler.compileCrystaProblem({ crystas:dataContext.__crystas, registry, baseContext, scenarioSnapshot:scenario, currentCrystas:[], locks:[], banned:{'오로로 콜론':true} });
const adapter = stats => evaluator.evaluateAggregate(baseContext, scenario, stats, kernel);
const relevantKeys = candidates.deriveRelevantKeys(compiled, registry, adapter);
const prepared = candidates.prepareProblem(compiled, { registry, relevantKeys, pareto:{maxComparisons:1000000} });
assert.ok(prepared.metadata.paretoReports.every(report => report.complete), 'native exact real fixture requires completed Pareto preparation');
const native = await runNative(prepared);
const compactNative = await runNative(projectNativeProblem(prepared));
assert.equal(compactNative.status, native.status);
assert.equal(compactNative.score, native.score);
assert.equal(compactNative.upperBound, native.upperBound);
assert.deepEqual(compactNative.bestBuild, native.bestBuild, 'compact IPC must preserve the complete selected raw options and lexical tie');
assert.equal(native.status, 'exact', 'native exact real native solver must exhaust its candidate tree');
assert.equal(native.score, 14097, 'native exact real native exact score must match the established JS exact fixture');
const requestedThreads = Number(process.env.OPTIMIZATION_EXACT_THREADS) || undefined;
const parallel = await runNative({ ...prepared, threads:requestedThreads }, 'crysta_native_parallel');
assert.equal(parallel.status, 'exact', 'native parallel real native solver must exhaust every shared-memory shard');
assert.equal(parallel.score, native.score, 'native parallel real parallel score must equal the native single-thread exact result');
assert.equal(parallel.bestBuild.id, native.bestBuild.id, 'native parallel real parallel tie result must equal the native single-thread exact result');
assert.equal(parallel.completedShards, parallel.scheduledShards, 'native parallel real parallel run must complete every scheduled shard');
console.log(`CrystaOptimization native parallel real native exact: PASS (${native.score}, single ${native.elapsedMs}ms, parallel ${parallel.elapsedMs}ms, ${parallel.threadsUsed} threads, ${parallel.scheduledShards} shards)`);
