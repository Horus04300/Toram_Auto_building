// Development-only event/count tracing of copied product sources; no timing claims.
import assert from 'node:assert/strict';
import { readFile, writeFile, mkdir, copyFile } from 'node:fs/promises';
import { spawn } from 'node:child_process';
import { resolve } from 'node:path';
import { createHash } from 'node:crypto';
import { parseArgs } from 'node:util';
import { root, loadHeadlessEnvironment, jsSources } from '../support/crysta-headless-environment.mjs';

const { values, positionals } = parseArgs({ allowPositionals:true, options:{
  input:{type:'string',default:'tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json'},
  threads:{type:'string',default:'1'}, 'max-batches':{type:'string',default:'10000'}
} });
const mode = positionals[0] || 'run';
assert.ok(['build','run'].includes(mode));
const threads = Number(values.threads), maxBatches = Number(values['max-batches']);
assert.ok(Number.isInteger(threads) && threads >= 1 && threads <= 64);
assert.ok(Number.isInteger(maxBatches) && maxBatches > 0);
const dir = resolve(root,'src-tauri/target/search-trace'), crate = resolve(dir,'crate');
const rustFiles = ['evaluator.rs','solver.rs','stats.rs','joint_supply.rs','parallel_runtime.rs'];
const sources = Object.fromEntries(await Promise.all(rustFiles.map(async f => [f,
  (await readFile(resolve(root,'src-tauri/src/optimization',f),'utf8')).replaceAll('\r\n','\n')])));
const hash = data => createHash('sha256').update(data).digest('hex');
const hashes = Object.fromEntries(rustFiles.map(f => [f,hash(sources[f])]));
const scriptHash = hash(await readFile(import.meta.filename));
const suffix = process.platform === 'win32' ? '.exe' : '';
await mkdir(dir,{recursive:true});
function replace(source, before, after) {
  assert.equal(source.split(before).length,2,`Unique instrumentation anchor: ${before}`);
  return source.replace(before,after);
}
function editFunction(source, name, edit) {
  const start = source.indexOf(`fn ${name}(`);
  assert.ok(start >= 0,name);
  const end = source.indexOf('\n}\n',start) + 3;
  assert.ok(end > start,name);
  return source.slice(0,start) + edit(source.slice(start,end)) + source.slice(end);
}
function run(command,args,input) {
  return new Promise((yes,no) => {
    const child = spawn(command,args,{cwd:root,windowsHide:true,stdio:['pipe','pipe','pipe']});
    let out='',err='';
    child.stdout.on('data',d => out += d); child.stderr.on('data',d => err += d);
    child.on('error',no);
    child.on('close',code => code === 0 ? yes(out) : no(new Error(`${command} (${code}): ${err}\n${out}`)));
    child.stdin.end(input);
  });
}
const traceModule = `use std::{collections::HashSet,sync::{atomic::{AtomicU64,Ordering},Mutex,LazyLock}};
use serde_json::{Value,json};
const NAMES:[&str;30]=["seedEvaluation","seedRejected","seedFeasible","seedImproved","visited","popBoundRejected","jointProbe","jointRejected","smallBox","split","childCreated","childJointRejected","childBoundEvaluation","childUtilityRejected","childBoundRejected","childSurvived","lookahead","utilityLookahead","partialUtilityProbe","partialUtilityRejected","leafEvaluation","leafRejected","leafBelowBest","leafTieOrAbove","incumbentImproved","smallBoxOutcome","discardedUtilityLookahead","discardedProbeBoundEvaluations","duplicateBoundEvaluation","duplicateCandidateEvaluation"];
static COUNTS:[AtomicU64;30]=[const {AtomicU64::new(0)};30];
static BOUNDS:LazyLock<Mutex<HashSet<[u32;4]>>>=LazyLock::new(||Mutex::new(HashSet::new()));
static CANDIDATES:LazyLock<Mutex<HashSet<String>>>=LazyLock::new(||Mutex::new(HashSet::new()));
static SAMPLES:Mutex<Vec<Value>>=Mutex::new(Vec::new());
pub fn count(i:usize){COUNTS[i].fetch_add(1,Ordering::Relaxed);}
pub fn add(i:usize,n:u64){COUNTS[i].fetch_add(n,Ordering::Relaxed);}
pub fn get(i:usize)->u64{COUNTS[i].load(Ordering::Relaxed)}
pub fn bound_seen(ids:[u32;4]){if !BOUNDS.lock().unwrap().insert(ids){event(28,||json!({"nodes":ids}));}}
pub fn candidate_seen(id:String){if !CANDIDATES.lock().unwrap().insert(id.clone()){event(29,||json!({"id":id}));}}
pub fn event(i:usize,details:impl FnOnce()->Value){let n=COUNTS[i].fetch_add(1,Ordering::Relaxed)+1;
 if n.is_power_of_two(){SAMPLES.lock().unwrap().push(json!({"event":NAMES[i],"occurrence":n,"details":details()}));}}
pub fn counts()->Value{let mut out=serde_json::Map::new();for(i,name)in NAMES.iter().enumerate(){out.insert((*name).into(),COUNTS[i].load(Ordering::Relaxed).into());}Value::Object(out)}
pub fn samples()->Value{json!(*SAMPLES.lock().unwrap())}
`;
const main = `#[path="optimization/evaluator.rs"] mod crysta_native_evaluator;
#[allow(dead_code)] #[path="optimization/solver.rs"] mod crysta_native_solver;
#[allow(dead_code)] #[path="optimization/parallel_runtime.rs"] mod crysta_parallel_runtime;
mod trace;
use std::io::{self,Read};
fn snapshot(session:&crysta_native_solver::NativeSearchSession,batch:usize)->serde_json::Value{
 let mut result=serde_json::to_value(session.snapshot()).unwrap();result.as_object_mut().unwrap().remove("elapsedMs");
 serde_json::json!({"batch":batch,"ready":session.ready_work_count(),"result":result,"counts":trace::counts(),"frontier":session.trace_frontier()})}
fn main()->Result<(),String>{let mut input=String::new();io::stdin().read_to_string(&mut input).map_err(|e|e.to_string())?;
 let problem=serde_json::from_str(&input).map_err(|e|e.to_string())?;
 let args:Vec<String>=std::env::args().collect();let threads=args[1].parse::<usize>().unwrap();let max=args[2].parse::<usize>().unwrap();
 let mut session=crysta_native_solver::NativeSearchSession::new(problem)?;
 let mut batches=vec![snapshot(&session,0)];let mut n=0;let mut peak=session.ready_work_count();
 while !session.is_complete()&&n<max{session.advance_parallel_slice_with_control(threads*crysta_native_solver::SESSION_NODES_PER_WORKER,threads,None,None)?;
 n+=1;peak=peak.max(session.ready_work_count());batches.push(snapshot(&session,n));}
 println!("{}",serde_json::json!({"threads":threads,"batchLimit":max,"peakReady":peak,"batches":batches,"samples":trace::samples(),"counts":trace::counts()}));Ok(())}
`;
const frontierMethod = `
    pub fn trace_frontier(&self) -> Value {
        let mut nodes=Vec::new();
        if let Some(node)=self.heap.peek(){nodes.push(serde_json::json!({"upper":node.upper,"paths":node.clusters.map(|id|self.problem.trees[id].path.clone()),"sizes":node.clusters.map(|id|self.problem.trees[id].size)}));}
        serde_json::json!(nodes)
    }
`;
if (mode === 'build') {
  await mkdir(resolve(crate,'src/optimization'),{recursive:true});
  await writeFile(resolve(crate,'Cargo.toml'),'[package]\nname="crysta-search-trace"\nversion="0.0.0"\nedition="2021"\n[dependencies]\nserde={version="1",features=["derive"]}\nserde_json="1"\nnum-bigint="0.4"\n');
  await copyFile(resolve(root,'src-tauri/Cargo.lock'),resolve(crate,'Cargo.lock'));
  await writeFile(resolve(crate,'src/trace.rs'),traceModule);
  await writeFile(resolve(crate,'src/main.rs'),main);
  let traced = sources['solver.rs'];
  traced = replace(traced,'    pub fn is_complete(&self) -> bool {',frontierMethod+'\n    pub fn is_complete(&self) -> bool {');
  traced = editFunction(traced,'consider_with_extra',s => {
    s = replace(s,'    state.evaluations += 1;','    crate::trace::count(0);\n    crate::trace::candidate_seen(build_id(&problem.groups,selected));\n    state.evaluations += 1;');
    s = replace(s,'        return Ok(());','        crate::trace::count(1);\n        return Ok(());');
    s = replace(s,'    let id = build_id','    crate::trace::count(2);\n    let id = build_id');
    return replace(s,'        state.best_score = summary.optimization_damage_factor;',
      '        crate::trace::event(3,||serde_json::json!({"score":summary.optimization_damage_factor,"id":id,"evaluation":state.evaluations}));\n        state.best_score = summary.optimization_damage_factor;');
  });
  traced = editFunction(traced,'consider_parallel_with_extra',s => {
    s = replace(s,'    counters.count_evaluations();','    crate::trace::count(20);\n    crate::trace::candidate_seen(build_id(&problem.groups,selected));\n    counters.count_evaluations();');
    s = replace(s,'        return Ok(());\n    };',
      '        crate::trace::event(21,||serde_json::json!({"id":build_id(&problem.groups,selected)}));\n        return Ok(());\n    };');
    s = replace(s,'    let accepts = |i, v| requirements.accepts_value(i, v);',
      '    let accepts = |i,v| {let ok=requirements.accepts_value(i,v);if !ok {crate::trace::event(21,||serde_json::json!({"utilityIndex":i,"value":v,"id":build_id(&problem.groups,selected)}));}ok};');
    // Rejection reasons are sampled at the callback; total rejected leaves count once.
    s = s.replace('crate::trace::event(21,||serde_json::json!({"id":build_id(&problem.groups,selected)}));','');
    s = replace(s,'        return Ok(());\n    }\n    let id = build_id',
      '        crate::trace::count(22);\n        return Ok(());\n    }\n    crate::trace::count(23);\n    let id = build_id');
    return replace(s,'        current.best_score = score;',
      '        crate::trace::event(24,||serde_json::json!({"score":score,"previous":current.best_score,"id":id}));\n        current.best_score = score;');
  });
  traced = editFunction(traced,'enumerate_box_parallel',s => {
    s = replace(s,'            counters.count_evaluations();','            crate::trace::count(18);\n            counters.count_evaluations();');
    return replace(s,'                counters.count_pruned_by_constraint();','                crate::trace::count(19);\n                counters.count_pruned_by_constraint();');
  });
  traced = editFunction(traced,'expand_parallel_node_inner',s => {
    s = replace(s,'    counters.count_visited();','    crate::trace::count(4);\n    counters.count_visited();');
    s = replace(s,'        counters.count_pruned_by_bound();\n        return Ok(true);','        crate::trace::count(5);\n        counters.count_pruned_by_bound();\n        return Ok(true);');
    s = replace(s,'    let joint_possible =','    crate::trace::count(6);\n    let joint_possible =');
    s = replace(s,'    if !joint_possible {','    if !joint_possible {\n        crate::trace::count(7);');
    s = replace(s,'        // Scheduling heuristic only;',
      '        crate::trace::event(8,||serde_json::json!({"upper":node.upper,"best":shared_best_score(incumbent),"sizes":node.clusters.map(|id|problem.trees[id].size),"depth":depth}));\n        // Scheduling heuristic only;');
    s = replace(s,'        return enumerate_box_parallel(',
      '        let before=[crate::trace::get(20),crate::trace::get(21),crate::trace::get(22),crate::trace::get(24)];\n        let completed=enumerate_box_parallel(');
    s = replace(s,'            &Stats::new(),\n        );',
      '            &Stats::new(),\n        );\n        crate::trace::event(25,||serde_json::json!({"upper":node.upper,"best":shared_best_score(incumbent),"paths":node.clusters.map(|id|problem.trees[id].path.clone()),"sizes":node.clusters.map(|id|problem.trees[id].size),"evaluated":crate::trace::get(20)-before[0],"rejected":crate::trace::get(21)-before[1],"belowBest":crate::trace::get(22)-before[2],"improvements":crate::trace::get(24)-before[3],"scope":"global counters; exclusive only with one worker"}));\n        return completed;');
    s = replace(s,'    counters.count_splits();','    crate::trace::count(9);\n    counters.count_splits();');
    s = replace(s,'    for child_clusters in child_boxes {','    for child_clusters in child_boxes {\n        crate::trace::count(10);');
    s = replace(s,'            let possible = problem.trees.joint_utilities_possible', '            crate::trace::count(6);\n            let possible = problem.trees.joint_utilities_possible');
    s = replace(s,'            if !possible {','            if !possible {\n                crate::trace::count(11);');
    s = replace(s,'        counters.count_evaluations();','        crate::trace::count(12);\n        crate::trace::bound_seen(child_clusters.map(|id|id.0));\n        counters.count_evaluations();');
    s = replace(s,'        let Some(bound) = evaluate_box(problem, &child_clusters, Some(requirements))? else {\n            counters.count_pruned_by_constraint();','        let Some(bound) = evaluate_box(problem, &child_clusters, Some(requirements))? else {\n            crate::trace::count(13);\n            counters.count_pruned_by_constraint();');
    s = replace(s,'            counters.count_pruned_by_bound();\n        } else {','            crate::trace::count(14);\n            counters.count_pruned_by_bound();\n        } else {\n            crate::trace::event(15,||serde_json::json!({"parentUpper":node.upper,"upper":bound.optimization_damage_factor,"best":shared_best_score(incumbent),"sizes":child_clusters.map(|id|problem.trees[id].size),"paths":child_clusters.map(|id|problem.trees[id].path.clone()),"depth":depth,"stats":box_stats(&problem.trees,&child_clusters),"derivedUpper":problem.trees.supply.as_ref().map(|s|std::array::from_fn::<_,6,_>(|i|s.metric(&child_clusters,SUPPLY_METRICS+i)))}));');
    s = replace(s,'            if should_look_ahead(&problem.trees, &child, best, depth) {','            if should_look_ahead(&problem.trees, &child, best, depth) {\n                crate::trace::count(16);');
    s = replace(s,'            let coverage_count =','            crate::trace::count(17);\n            let coverage_count =');
    s = replace(s,'            let start = children.len();','            let start = children.len();\n            let probe_evaluations=crate::trace::get(12);');
    return replace(s,'                children.truncate(start);',
      '                crate::trace::event(26,||serde_json::json!({"paths":child.clusters.map(|id|problem.trees[id].path.clone()),"evaluations":crate::trace::get(12)-probe_evaluations,"scope":"exclusive only with one worker"}));\n                crate::trace::add(27,crate::trace::get(12)-probe_evaluations);\n                children.truncate(start);');
  });
  for (const variant of ['control','trace']) {
    for (const file of rustFiles) await writeFile(resolve(crate,'src/optimization',file),
      file === 'solver.rs' ? variant === 'trace' ? traced : replace(sources[file],'    pub fn is_complete(&self) -> bool {',frontierMethod+'\n    pub fn is_complete(&self) -> bool {') : sources[file]);
    await run('cargo',['build','--offline','--release','--manifest-path',resolve(crate,'Cargo.toml')]);
    await copyFile(resolve(crate,`target/release/crysta-search-trace${suffix}`),resolve(dir,`${variant}${suffix}`));
    console.log(`Built ${variant}`);
  }
  await writeFile(resolve(dir,'build.json'),JSON.stringify({hashes,scriptHash},null,2));
} else {
  assert.deepEqual(JSON.parse(await readFile(resolve(dir,'build.json'),'utf8')),{hashes,scriptHash},'Rebuild after source/script changes');
  const fixtureText = await readFile(resolve(root,values.input),'utf8'), fixture = JSON.parse(fixtureText);
  const input = fixture.resolvedExecutionContext || fixture;
  const jsHashes = Object.fromEntries(await Promise.all(jsSources.map(async f => [f,hash(await readFile(resolve(root,'assets/js',f)))])));
  let compiled, report;
  const env = await loadHeadlessEnvironment({invoke:async (command,args) => {
    if (command === 'crysta_hardware_profile') return {logicalThreads:threads};
    assert.equal(command,'crysta_optimize_parallel');
    const payload = JSON.stringify(args.problem);
    await writeFile(resolve(dir,'input.json'),payload);
    const runs = {};
    for (const variant of ['control','trace']) {
      runs[variant] = JSON.parse(await run(resolve(dir,variant+suffix),[String(threads),String(maxBatches)],payload));
      await writeFile(resolve(dir,`${variant}-${threads}.json`),JSON.stringify(runs[variant],null,2)+'\n');
      console.log(`${variant}: ${runs[variant].batches.at(-1).result.status}, batches=${runs[variant].batches.length-1}`);
    }
    const control = runs.control.batches.at(-1).result, result = runs.trace.batches.at(-1).result;
    assert.ok(['exact','bounded'].includes(result.status));
    const comparable = threads === 1 || (control.exact && result.exact);
    if (comparable) {
      assert.equal(control.status,result.status); assert.equal(control.score,result.score);
      assert.equal(control.bestBuild.id,result.bestBuild.id);
    }
    if (result.exact) assert.equal(result.upperBound,result.score);
    else assert.ok(result.upperBound >= result.score);
    if (threads === 1) assert.equal(control.upperBound,result.upperBound);
    if (threads === 1) for (const key of ['visitedNodes','evaluations','prunedByBound','prunedByConstraint','enumeratedCompletions']) assert.equal(control[key],result[key],key);
    const c = runs.trace.counts;
    assert.equal(c.visited,result.visitedNodes);
    assert.equal(c.leafEvaluation,result.enumeratedCompletions);
    assert.equal(c.leafRejected+c.leafBelowBest+c.leafTieOrAbove,c.leafEvaluation);
    assert.equal(c.childCreated,c.childJointRejected+c.childUtilityRejected+c.childBoundRejected+c.childSurvived);
    assert.equal(runs.trace.batches[0].result.evaluations+c.childBoundEvaluation+c.partialUtilityProbe+c.leafEvaluation,result.evaluations,'Evaluation accounting (initialization, child bounds, partial utility, leaves)');
    report = {date:'2026-10-11',input:values.input,inputHash:hash(fixtureText),rustSourceHashes:hashes,jsSourceHashes:jsHashes,
      policy:env.client.cachePolicy,threads,batchSize:threads*32,provenance:fixture.provenance,
      requirements:args.problem.scenarioSnapshot.requirements,locks:input.locks,
      rawGroups:compiled.groups.map(g => ({id:g.id,packages:g.packages.length})),
      preparedGroups:args.problem.groups.map(g => ({id:g.id,packages:g.packages.length})),
      stoppingRule:'complete proof or fixed batch count; no deadline',
      sampleRule:'event occurrences 1, 2, 4, 8, ...; aggregate counters count every event',
      checks:{controlResultParity:comparable,serialCountersEqual:threads===1,eventAccounting:true},...runs.trace};
    return result;
  }});
  compiled = env.compile(input);
  assert.deepEqual(Array.from(compiled.diagnostics),[]);
  const normalized = await env.client.optimize(compiled,{}, {timeLimitMs:30000});
  assert.equal(normalized.outcomes.constraints.feasible,true);
  assert.equal(normalized.outcomes.damage.expected,normalized.score);
  report.checks.finalJsEvaluation=true;
  assert.deepEqual(Object.fromEntries(await Promise.all(rustFiles.map(async f => [f,
    hash((await readFile(resolve(root,'src-tauri/src/optimization',f),'utf8')).replaceAll('\r\n','\n'))]))),hashes);
  await writeFile(resolve(dir,`report-${threads}.json`),JSON.stringify(report,null,2)+'\n');
  await writeFile(resolve(dir,`events-${threads}.jsonl`),[...report.batches.map(b => ({event:'batch',...b})),...report.samples].map(e => JSON.stringify(e)).join('\n')+'\n');
  console.log(JSON.stringify({result:report.batches.at(-1).result,counts:report.counts,peakReady:report.peakReady,checks:report.checks}));
  console.log(`Report: ${resolve(dir,`report-${threads}.json`)}`);
}
