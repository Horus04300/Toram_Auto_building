import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {createRequire} from 'node:module';
import {spawnSync} from 'node:child_process';
import {resolve} from 'node:path';
import vm from 'node:vm';
const root=resolve(import.meta.dirname,'..'),require=createRequire(import.meta.url);
const registry=require('../assets/js/stat-registry.js'),evaluator=require('../assets/js/build-evaluator.js'),optimizer=require('../assets/js/d4-global-optimizer.js');
const context={window:{ToramStatRegistry:registry},console};context.window.window=context.window;vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};',context);
for(const name of ['calculation-policies.js','calculator.js'])vm.runInContext(await readFile(resolve(root,'assets/js',name),'utf8'),context);
const kernel=context.window.ToramCalculationKernel.evaluateContext;
const template=JSON.parse(await readFile(resolve(root,'tools/fixtures/d4-synthetic-utility-conflict.json'),'utf8')).baseContext;
const base={...template,level:100,mainType:'한손검',strBase:0,dexBase:0,intBase:0,agiBase:0,vitBase:1,wpnAtk:100,bossDef:0,bossCritResist:0,critF:75,aspdF:800,maxHpF:0,maxMpF:1800,amprF:0};
const empty={maxHp:null,maxMp:null,amprBeforeDual:null,normalAttackCrit:null,aspd:null};
const evaluate=(b,stats={},requirements={})=>evaluator.evaluateAggregate(b,evaluator.createScenarioSnapshot(b,{requirements:{...empty,...requirements}}),stats,kernel);
assert.equal(evaluate(base,{MAXMP:5000},{maxMp:2001}).constraints.feasible,false);
assert.equal(evaluate({...base,godspeedWieldLevel:10},{MAXMP:300},{maxMp:2300}).constraints.feasible,true);
assert.equal(evaluate({...base,godspeedWieldLevel:10},{MAXMP:5000},{maxMp:2301}).constraints.feasible,false);
assert.equal(evaluate(base,{MAXMP:5000,AMPRP:1000},{amprBeforeDual:31}).constraints.feasible,false);
assert.equal(evaluate(base,{MAXMP:5000,AMPRP:-100,AMPR:1},{amprBeforeDual:31}).constraints.feasible,true);
assert.equal(evaluate({...base,bossCritResist:70},{CRIT:70},{normalAttackCrit:100}).constraints.feasible,true);
assert.equal(evaluate({...base,bossCritResist:70},{CRIT:69},{normalAttackCrit:100}).constraints.feasible,false);
assert.equal(evaluate(base,{CRIT:500},{normalAttackCrit:101}).constraints.feasible,false);
assert.equal(evaluate(base,{MOTIONSPEED:50},{aspd:10000}).constraints.feasible,true);
assert.equal(evaluate({...base,aspdF:799},{MOTIONSPEED:50},{aspd:10000}).constraints.feasible,false);
assert.equal(evaluate(base,{ASPD:179,MOTIONSPEED:49},{aspd:10000}).constraints.feasible,false);
assert.equal(evaluate(base,{ASPD:180,MOTIONSPEED:49},{aspd:10000}).constraints.feasible,true);
assert.equal(evaluate(base,{ASPD:50000},{aspd:10001}).constraints.feasible,false);
const stats=[{MAXHP:1000,MAXMP:800,CRIT:40,ASPD:150},{MAXHPP:100,INT:100,CRITP:100,ASPD_P:50,AMPR:6},{ATKP:20,AMPRP:200,MOTIONSPEED:15}];
let cases=0;
for(const contextPatch of [{},{godspeedWieldLevel:10},{bossCritResist:70},{motionSpeed:30},{amprP:500},{amprP:-100},{motionSpeed:-10}]){
 const b={...base,...contextPatch};
 for(const requirements of [empty,{maxHp:5000},{maxHp:4873},{maxMp:2000},{maxMp:2001},{maxMp:2300},{amprBeforeDual:45},{normalAttackCrit:100},{normalAttackCrit:101},{aspd:999},{aspd:1000},{aspd:1001},{aspd:1180},{aspd:10000},{aspd:10001}]){
  const problem={baseContext:b,scenarioSnapshot:evaluator.createScenarioSnapshot(b,{requirements:{...empty,...requirements}}),groups:['weapon','armor','additional','special'].map(id=>({id,packages:stats.map((statDelta,i)=>({id:id+':'+i,statDelta}))})),metadata:{modeledKeys:[...new Set(stats.flatMap(s=>Object.keys(s)))]}};
  const oracle=optimizer.exhaustiveSearch(problem,{prepared:problem,evaluateStats:s=>evaluate(b,s,requirements)});
  const child=spawnSync(resolve(root,'src-tauri/target/release/d4_native_exact.exe'),[],{input:JSON.stringify(problem),encoding:'utf8',timeout:30000});
  assert.equal(child.status,0,child.stderr);const native=JSON.parse(child.stdout);
  assert.equal(native.bestBuild?.id??null,oracle.bestBuild?.id??null,JSON.stringify({contextPatch,requirements}));
  if(oracle.bestBuild){assert.equal(native.score,oracle.score);assert.equal(native.status,'exact');}
  else assert.equal(native.status,'invalid');
  const shared=spawnSync(resolve(root,'src-tauri/target/release/d4_native_parallel.exe'),[],{input:JSON.stringify({...problem,threads:4}),encoding:'utf8',timeout:30000,env:{...process.env,D4_SESSION_BENCH_MS:'30000'}});
  assert.equal(shared.status,0,shared.stderr);const parallel=JSON.parse(shared.stdout);
  assert.equal(parallel.status,native.status);
  assert.equal(parallel.score,native.score);
  assert.equal(parallel.bestBuild?.id??null,native.bestBuild?.id??null);
  const bounds=optimizer.verifyCandidateTreeUpperBounds(problem,{prepared:problem,registry,evaluateStats:s=>evaluate(b,s,requirements)});
  assert.deepEqual(bounds.violations,[]);
  const monotonicity=optimizer.verifyEnvelopeMonotonicity(problem,{prepared:problem,registry,evaluateStats:s=>evaluate(b,s,requirements)});
  assert.deepEqual(monotonicity.violations,[]);
  cases++;
 }
}
console.log(`Utility caps: PASS (13 boundary checks; ${cases} JS exhaustive/serial/shared-session cases, tree bounds and monotonicity)`);
