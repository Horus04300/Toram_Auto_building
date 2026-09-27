// Development-only instrumentation of copied Rust; production sources stay untouched.
import assert from 'node:assert/strict';
import {readFile,writeFile,mkdir,copyFile} from 'node:fs/promises';
import {spawn} from 'node:child_process';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
const root=resolve(import.meta.dirname,'..'),dir=resolve(root,'src-tauri/target/slow-profile');
await mkdir(dir,{recursive:true});
function run(cmd,args,env={}) {return new Promise((yes,no)=>{
  const p=spawn(cmd,args,{cwd:root,env:{...process.env,...env},stdio:['ignore','pipe','pipe']});
  let out='',err='';p.stdout.on('data',d=>out+=d);p.stderr.on('data',d=>err+=d);
  p.on('error',no);p.on('close',c=>c===0?yes(out):no(new Error(`${cmd}: ${c}\n${err}\n${out}`)));
});}
function replace(s,a,b){assert.equal(s.split(a).length,2,`unique anchor: ${a}`);return s.replace(a,b);}
const files=['d4_native_evaluator.rs','d4_native_solver.rs','d4_native_stats.rs','d4_parallel_runtime.rs','bin/d4_native_parallel.rs'];
const sources=Object.fromEntries(await Promise.all(files.map(async f=>[f,(await readFile(resolve(root,'src-tauri/src',f),'utf8')).replaceAll('\r\n','\n')])));
const hashes=Object.fromEntries(files.map(f=>[f,createHash('sha256').update(sources[f]).digest('hex')]));
if(process.argv[2]==='build'){
 const crate=resolve(dir,'crate');await mkdir(resolve(crate,'src/bin'),{recursive:true});
 await writeFile(resolve(crate,'Cargo.toml'),'[package]\nname="d4-slow-profile"\nversion="0.0.0"\nedition="2021"\n[dependencies]\nserde={version="1",features=["derive"]}\nserde_json="1"\n');
 await copyFile(resolve(root,'src-tauri/Cargo.lock'),resolve(crate,'Cargo.lock'));
 await writeFile(resolve(crate,'src/profile.rs'),`use std::{cell::RefCell,sync::Mutex,time::Instant};
#[derive(Clone,Copy,Default,serde::Serialize)]
struct Counter {calls:u64,samples:u64,nanos:u64}
thread_local! {static LOCAL:RefCell<[Counter;10]>=RefCell::new([Counter::default();10]);}
static RECORDS:Mutex<Vec<(String,[Counter;10])>>=Mutex::new(Vec::new());
pub struct Span(usize,Option<Instant>);
pub fn enter(i:usize)->Span {
 let sampled=LOCAL.with(|c|{let mut c=c.borrow_mut();c[i].calls+=1;(2..6).contains(&i) || c[i].calls%1024==1});
 Span(i,sampled.then(Instant::now))
}
impl Drop for Span {fn drop(&mut self){if let Some(t)=self.1 {let n=t.elapsed().as_nanos() as u64;LOCAL.with(|c|{let mut c=c.borrow_mut();c[self.0].samples+=1;c[self.0].nanos+=n;});}}}
pub fn count(i:usize){LOCAL.with(|c|c.borrow_mut()[i].calls+=1);}
pub struct Flush;
impl Drop for Flush {fn drop(&mut self){flush();}}
pub fn flush(){LOCAL.with(|c| {let mut c=c.borrow_mut();RECORDS.lock().unwrap().push((format!("{:?}",std::thread::current().id()),*c));*c=[Counter::default();10];});}
pub fn result()->serde_json::Value {flush();serde_json::json!({"categories":["evaluator","boxStats","workerJob","poolRun","frontierPop","frontierMerge","leafRejected","leafAccepted","utilityStage","damageStage"],"sampleEvery":1024,"threads":*RECORDS.lock().unwrap()})}
`);
 for(const variant of ['control','profile']){
  let solver=sources['d4_native_solver.rs'],evaluator=sources['d4_native_evaluator.rs'],bridge=sources['bin/d4_native_parallel.rs'];
  // Same sparse progress snapshots in both binaries allow an overhead comparison.
  bridge=replace(bridge,'let mut batches = 0_u64;','let mut batches = 0_u64;\n        let mut peak_ready=0;\n        let mut trace=Vec::new();\n        let mut next_trace=0.0;');
  bridge=replace(bridge,'            batches += 1;',`            batches += 1;
            peak_ready=peak_ready.max(session.ready_work_count());
            let ms=started.elapsed().as_secs_f64()*1000.0;
            if ms>=next_trace {trace.push(serde_json::json!({"ms":ms,"ready":session.ready_work_count(),"result":session.snapshot()}));next_trace=ms+1000.0;}`);
  bridge=replace(bridge,'        println!("{}", output);','        output["peakReadyWork"]=serde_json::json!(peak_ready);\n        output["trace"]=serde_json::json!(trace);\n        drop(session);\n        println!("{}", output);');
  if(variant==='profile'){
   bridge=replace(bridge,'use serde::Deserialize;','#[path="../profile.rs"]\nmod profile;\nuse serde::Deserialize;');
   bridge=replace(bridge,'        drop(session);','        drop(session);\n        output["profile"]=profile::result();');
   evaluator=replace(evaluator,'    let plan = base.evaluation_plan().unwrap_or_else(|| {','    let _profile=crate::profile::enter(0);\n    let plan = base.evaluation_plan().unwrap_or_else(|| {');
   evaluator=replace(evaluator,'    let vit = stat_total(base, stats, "vitBase", "vitP", "vitF", "VITP", "VIT");','    let utility_span=crate::profile::enter(8);\n    let vit = stat_total(base, stats, "vitBase", "vitP", "vitF", "VITP", "VIT");');
   evaluator=replace(evaluator,'    let mut atk_p = number(base, "atkP") + stat(stats, "ATKP");','    drop(utility_span);\n    let _damage_span=crate::profile::enter(9);\n    let mut atk_p = number(base, "atkP") + stat(stats, "ATKP");');
   solver=replace(solver,'fn box_stats(trees: &TreeArena, clusters: &[NodeId; GROUP_COUNT]) -> Stats {','fn box_stats(trees: &TreeArena, clusters: &[NodeId; GROUP_COUNT]) -> Stats {\n    let _profile=crate::profile::enter(1);');
   solver=replace(solver,'                .spawn(move || loop {','                .spawn(move || { let _flush=crate::profile::Flush; loop {');
   solver=replace(solver,'                })\n                .map_err(|error| format!("D4 worker creation failed: {error}"))?;','                }})\n                .map_err(|error| format!("D4 worker creation failed: {error}"))?;');
   solver=replace(solver,'                    let batch = &job.batch;','                    let job_span=crate::profile::enter(2);\n                    let batch = &job.batch;');
   solver=replace(solver,'                    drop(job.batch);','                    drop(job.batch);\n                    drop(job_span);');
   solver=replace(solver,'        results.clear();','        let _profile=crate::profile::enter(3);\n        results.clear();');
   solver=replace(solver,'        nodes.extend((0..batch_size).filter_map(|_| self.heap.pop()));','        { let _profile=crate::profile::enter(4);\n        nodes.extend((0..batch_size).filter_map(|_| self.heap.pop())); }');
   solver=replace(solver,'            for (node, outcome) in nodes.drain(..).zip(self.batch_outcomes.drain(..)) {','            let merge_span=crate::profile::enter(5);\n            for (node, outcome) in nodes.drain(..).zip(self.batch_outcomes.drain(..)) {');
   solver=replace(solver,'            let state = incumbent','            drop(merge_span);\n            let state = incumbent');
   solver=replace(solver,'    })?\n    else {\n        return Ok(());\n    };\n    let score = summary.optimization_damage_factor;',
    '    })?\n    else {\n        crate::profile::count(6);\n        return Ok(());\n    };\n    crate::profile::count(7);\n    let score = summary.optimization_damage_factor;');
  }
  for(const f of files)await writeFile(resolve(crate,'src',f),f==='d4_native_solver.rs'?solver:f==='d4_native_evaluator.rs'?evaluator:f==='bin/d4_native_parallel.rs'?bridge:sources[f]);
  await run('cargo',['build','--offline','--release','--manifest-path',resolve(crate,'Cargo.toml'),'--bin','d4_native_parallel']);
  await copyFile(resolve(crate,'target/release/d4_native_parallel.exe'),resolve(dir,variant+'.exe'));console.log('built '+variant);
 }
 await writeFile(resolve(dir,'source-hashes.json'),JSON.stringify(hashes,null,2));
}else if(process.argv[2]==='run'){
 assert.deepEqual(hashes,JSON.parse(await readFile(resolve(dir,'source-hashes.json'),'utf8')),'rebuild after source changes');
 const runs=[], fixtures=(process.env.D4_PROFILE_FIXTURES||'revenir,dual').split(',');
 const threadCounts=(process.env.D4_PROFILE_THREADS||'8,16').split(',').map(Number);
 const repeats=Number(process.env.D4_PROFILE_REPEATS||1), budget=process.env.D4_PROFILE_BUDGET||'30000';
 assert.ok(threadCounts.every(n=>Number.isInteger(n)&&n>0&&n<=64));
 assert.ok(Number.isInteger(repeats)&&repeats>0&&Number(budget)>0);
 for(const fixture of fixtures){assert.match(fixture,/^[a-z0-9-]+$/);
  const problem=JSON.parse(await readFile(resolve(root,'src-tauri/target/regression-audit',fixture+'.json'),'utf8'));
  for(const threads of threadCounts)for(let repeat=1;repeat<=repeats;repeat++)for(const variant of (repeat%2?['control','profile']:['profile','control'])){
   const input=resolve(dir,'input.json'),output=resolve(dir,'output.json');await writeFile(input,JSON.stringify({...problem,threads}));
   const measurement=JSON.parse(await run('powershell.exe',['-NoProfile','-NonInteractive','-ExecutionPolicy','Bypass','-File',resolve(root,'tools/measure-d4-native-p6.ps1'),'-Binary',resolve(dir,variant+'.exe'),'-InputPath',input,'-Output',output,'-ErrorOutput',resolve(dir,'error.txt')],{D4_SESSION_BENCH_MS:budget}));
   const result=JSON.parse(await readFile(output,'utf8'));assert.ok(['exact','bounded'].includes(result.status));
   if(problem.auditOracle){assert.equal(result.status,'exact');assert.equal(result.score,problem.auditOracle.score);assert.equal(result.bestBuild?.id,problem.auditOracle.id);}
   const previous=runs.find(r=>r.fixture===fixture&&r.result.exact);if(previous&&result.exact){assert.equal(result.score,previous.result.score);assert.equal(result.bestBuild?.id,previous.result.bestBuild?.id);assert.equal(result.upperBound,result.score);}
   runs.push({fixture,threads,repeat,variant,packages:problem.groups.map(g=>g.packages.length),measurement,result});
   await writeFile(resolve(dir,process.env.D4_PROFILE_REPORT||'measurements.json'),JSON.stringify({date:new Date().toISOString(),budgetMs:Number(budget),sourceHashes:hashes,runs},null,2));
   console.log(`${fixture} ${threads} ${repeat} ${variant}: ${result.status} ${result.sessionWallMs.toFixed(1)}ms score=${result.score} upper=${result.upperBound} evals=${result.evaluations}`);
  }
 }
}else if(process.argv[2]==='report'){
 const runs=[];
 for(const phase of ['measurements','complete','oracle']){
  const data=JSON.parse(await readFile(resolve(dir,phase+'.json'),'utf8'));
  assert.deepEqual(data.sourceHashes,hashes);
  for(const r of data.runs){
   const {samples,...measurement}=r.measurement;
   const cpuMs=Math.max(measurement.cpuMs,...samples.map(s=>s.cpuMs));
   const {profile,trace,...result}=r.result;
   const categories=profile?.categories.map((name,i)=>{
    const totals=profile.threads.reduce((a,t)=>({calls:a.calls+t[1][i].calls,samples:a.samples+t[1][i].samples,nanos:a.nanos+t[1][i].nanos}),{calls:0,samples:0,nanos:0});
    return {name,...totals,estimatedMs:totals.samples?totals.nanos/1e6*totals.calls/totals.samples:0};
   });
   runs.push({...r,phase,measurement:{...measurement,cpuMs,sampleCount:samples.length,averageCpuCores:cpuMs/measurement.wallMs},result,
    trace:trace.map(t=>({ms:t.ms,ready:t.ready,score:t.result.score,upperBound:t.result.upperBound,evaluations:t.result.evaluations})),profile:profile?{...profile,categories}:undefined});
  }
 }
 for(const r of runs){
  const exact=runs.find(x=>x.fixture===r.fixture&&x.result.exact)?.result;
  assert.ok(exact,`no exact reference for ${r.fixture}`);
  assert.ok(r.result.score===null||r.result.score<=exact.score);
  assert.ok(r.result.upperBound>=exact.score,'bounded result must cover verified optimum');
  if(r.result.exact){assert.equal(r.result.score,exact.score);assert.equal(r.result.bestBuild?.id,exact.bestBuild?.id);assert.equal(r.result.upperBound,exact.score);}
 }
 const inputHashes={};for(const name of new Set(runs.map(r=>r.fixture)))inputHashes[name]=createHash('sha256').update(await readFile(resolve(root,'src-tauri/target/regression-audit',name+'.json'))).digest('hex');
 const output=resolve(root,'docs/verification/d4-slow-input-profile-measurements.json');
 await writeFile(output,JSON.stringify({measuredDate:'2026-09-23',sourceHashes:hashes,inputHashes,notes:'Exploratory 30s run: Revenir 16 control partially overlapped JS oracle preparation. Complete and oracle phases ran without concurrent builds/tests. Timing categories are inclusive as described in d4-slow-input-profile.md.',runs},null,2));
 console.log(output);
}else throw new Error('Use build, run, or report; prepare inputs with benchmark-d4-native-p6.mjs export first.');
