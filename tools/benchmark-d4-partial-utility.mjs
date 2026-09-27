import assert from 'node:assert/strict';
import {readFile,writeFile,copyFile} from 'node:fs/promises';
import {spawn} from 'node:child_process';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
import {createRequire} from 'node:module';
import vm from 'node:vm';
import {projectNativeProblem} from './d4-native-payload-helper.mjs';
const compareNativePayload=process.env.D4_COMPARE_NATIVE_PAYLOAD==='1';
const experiment=process.env.D4_EVALUATION_EXPERIMENT||'partial-utility';
assert.match(experiment,/^[a-z0-9-]+$/);
const root=resolve(import.meta.dirname,'..'),dir=resolve(root,'src-tauri/target',experiment);
const require=createRequire(import.meta.url),registry=require('../assets/js/stat-registry.js'),evaluator=require('../assets/js/build-evaluator.js');
const context={window:{ToramStatRegistry:registry},console};context.window.window=context.window;vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};',context);
for(const file of ['calculation-policies.js','calculator.js'])vm.runInContext(await readFile(resolve(root,'assets/js',file),'utf8'),context);
const kernel=context.window.ToramCalculationKernel.evaluateContext;
await copyFile(resolve(root,'src-tauri/target/slow-profile/control.exe'),resolve(dir,'after.exe'));
const hash=b=>createHash('sha256').update(b).digest('hex');
const binaryHashes={};for(const v of ['before','after'])binaryHashes[v]=hash(await readFile(resolve(dir,v+'.exe')));
const runs=[];
const fixtures=(process.env.D4_COMPARE_FIXTURES||'revenir,dual,utility-tight').split(',');
const repeats=Number(process.env.D4_COMPARE_REPEATS||2);
assert.ok(Number.isInteger(repeats)&&repeats>0);
for(const fixture of fixtures)assert.match(fixture,/^[a-z0-9-]+$/);
for(const fixture of fixtures)for(let repeat=1;repeat<=repeats;repeat++)for(const variant of repeat%2===1?['before','after']:['after','before']) {
 const inputBytes=await readFile(resolve(root,'src-tauri/target/regression-audit',fixture+'.json'));
 const originalInput=JSON.parse(inputBytes);
 const input=JSON.stringify({...((compareNativePayload&&variant==='after')?projectNativeProblem(originalInput):originalInput),threads:16});
 await writeFile(resolve(dir,'input.json'),input);
 const measurement=await new Promise((yes,no)=>{
  const p=spawn('powershell.exe',['-NoProfile','-NonInteractive','-ExecutionPolicy','Bypass','-File',resolve(root,'tools/measure-d4-native-p6.ps1'),'-Binary',resolve(dir,variant+'.exe'),'-InputPath',resolve(dir,'input.json'),'-Output',resolve(dir,'output.json'),'-ErrorOutput',resolve(dir,'error.txt')],{cwd:root,env:{...process.env,D4_SESSION_BENCH_MS:'120000'}});
  let out='',err='';p.stdout.on('data',d=>out+=d);p.stderr.on('data',d=>err+=d);p.on('error',no);p.on('close',c=>c===0?yes(JSON.parse(out)):no(new Error(err)));
 });
 const result=JSON.parse(await readFile(resolve(dir,'output.json'),'utf8'));
 assert.equal(result.status,'exact');assert.equal(result.upperBound,result.score);
 const prior=runs.find(r=>r.fixture===fixture);if(prior){assert.equal(result.score,prior.result.score);assert.deepEqual(result.bestBuild,prior.result.bestBuild);}
 const original=JSON.parse(inputBytes),expectedStats={};
 for(let group=0;group<original.groups.length;group++) {
  const selected=original.groups[group].packages.find(p=>p.id===result.bestBuild.packageIds[group]);assert.ok(selected);
  for(const [key,value] of Object.entries(selected.statDelta))expectedStats[key]=(expectedStats[key]??0)+value;
 }
 assert.deepEqual(result.bestBuild.statDelta,expectedStats,'all original selected options must survive result construction');
 const reevaluated=evaluator.evaluateAggregate(original.baseContext,original.scenarioSnapshot,result.bestBuild.statDelta,kernel);
 assert.equal(reevaluated.constraints.feasible,true,'selected raw options must satisfy JS utility goals');
 assert.equal(reevaluated.damage.expected,result.score,'returned raw options must reproduce the native score in JS');
 if(variant==='after')for(const t of result.trace)assert.ok(t.result.upperBound>=result.score);
 const {samples,...metrics}=measurement;
 runs.push({fixture,repeat,variant,inputHash:hash(inputBytes),measurement:metrics,result});
 await writeFile(resolve(root,`docs/verification/d4-${experiment}-measurements.json`),JSON.stringify({date:new Date().toISOString(),binaryHashes,compareNativePayload,runs},null,2)+'\n');
 console.log(`${fixture} ${repeat} ${variant}: ${(result.sessionWallMs/1000).toFixed(3)}s eval=${result.evaluations} leaves=${result.enumeratedCompletions}`);
}
