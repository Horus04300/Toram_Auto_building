// Read-only product audit. Rust layout helpers are injected into an isolated copy.
import assert from 'node:assert/strict';
import {readFile,writeFile,mkdir,copyFile} from 'node:fs/promises';
import {spawnSync} from 'node:child_process';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
import {performance} from 'node:perf_hooks';
const root=resolve(import.meta.dirname,'..'),dir=resolve(root,'src-tauri/target/structure-audit');
await mkdir(resolve(dir,'src/bin'),{recursive:true});
const sourceHashes={},hash=value=>createHash('sha256').update(value).digest('hex');
const files=['d4_native_evaluator.rs','d4_native_solver.rs','d4_native_stats.rs','d4_parallel_runtime.rs','bin/d4_native_parallel.rs'];
for(const file of files){
 let source=(await readFile(resolve(root,'src-tauri/src',file),'utf8')).replaceAll('\r\n','\n');sourceHashes[file]=hash(source);
 if(file==='d4_native_solver.rs')source+=`
pub fn audit_layout() -> serde_json::Value {
 #[allow(dead_code)] struct IndexedWork { upper:f64, nodes:[u32;4] }
 serde_json::json!({"workItem":std::mem::size_of::<WorkItem>(),"indexedWorkProposal":std::mem::size_of::<IndexedWork>(),"treeNode":std::mem::size_of::<TreeNode>(),"nativeStats":std::mem::size_of::<Stats>(),"nativePackage":std::mem::size_of::<NativePackage>(),"preparedContext":std::mem::size_of::<PreparedContext>(),"nodeOutcome":std::mem::size_of::<NodeOutcome>()})
}
`;
 if(file==='bin/d4_native_parallel.rs')source=source.replace('fn main() -> Result<(), String> {','fn main() -> Result<(), String> {\n    println!("{}", d4_native_solver::audit_layout()); return Ok(());');
 await writeFile(resolve(dir,'src',file),source);
}
await writeFile(resolve(dir,'Cargo.toml'),'[package]\nname="d4-structure-audit"\nversion="0.0.0"\nedition="2021"\n[dependencies]\nserde={version="1",features=["derive"]}\nserde_json="1"\n');
await copyFile(resolve(root,'src-tauri/Cargo.lock'),resolve(dir,'Cargo.lock'));
const layoutRun=spawnSync('cargo',['run','--offline','--release','--quiet','--manifest-path',resolve(dir,'Cargo.toml'),'--bin','d4_native_parallel'],{cwd:root,encoding:'utf8'});
assert.equal(layoutRun.status,0,layoutRun.stderr);
const layout=JSON.parse(layoutRun.stdout);
// Expose the actual cache serialization code in a copy, using the ordinary
// Node realm: vm global lookup overhead would distort the per-character hash.
const client=await readFile(resolve(root,'assets/js/d4-native-client.js'),'utf8'),context={};
const anchor='  var client = new NativeParallelClient();';assert.equal(client.split(anchor).length,2);
new Function('window',client.replace(anchor,'  root.auditCacheKey=cacheKey;\n'+anchor))(context);
const wire=[];
for(const fixture of ['revenir','dual','utility-tight']){
 const bytes=await readFile(resolve(root,'src-tauri/target/regression-audit',fixture+'.json')),original=JSON.parse(bytes);
 const compact={baseContext:original.baseContext,scenarioSnapshot:original.scenarioSnapshot,metadata:{modeledKeys:original.metadata?.modeledKeys,initialPackageIds:original.metadata?.initialPackageIds},groups:original.groups.map(g=>({id:g.id,packages:g.packages.map(p=>({id:p.id,statDelta:p.statDelta}))}))};
 const timing={};
 for(const [name,value] of [['original',original],['compactProposal',compact]]){
  const times=[];for(let i=0;i<12;i++){const start=performance.now();context.auditCacheKey(value,{timeLimitMs:30000},{logicalThreads:16});if(i>=2)times.push(performance.now()-start);}
  times.sort((a,b)=>a-b);timing[name]={medianMs:(times[4]+times[5])/2,minMs:times[0],maxMs:times.at(-1)};
 }
 wire.push({fixture,inputHash:hash(bytes),packages:original.groups.reduce((n,g)=>n+g.packages.length,0),originalJsonBytes:Buffer.byteLength(JSON.stringify(original)),compactProposalJsonBytes:Buffer.byteLength(JSON.stringify(compact)),cacheKeyTiming:timing});
}
const profile=JSON.parse(await readFile(resolve(root,'src-tauri/target/slow-profile/structure-audit.json'),'utf8'));
assert.deepEqual(profile.sourceHashes,sourceHashes);
const runs=profile.runs.map(r=>{
 const {profile:p,trace,...result}=r.result;const {samples,...measurement}=r.measurement;
 const categories=p?.categories.map((name,i)=>{
  const t=p.threads.reduce((a,thread)=>({calls:a.calls+thread[1][i].calls,samples:a.samples+thread[1][i].samples,nanos:a.nanos+thread[1][i].nanos}),{calls:0,samples:0,nanos:0});
  return {name,...t,estimatedMs:t.samples?t.nanos/1e6*t.calls/t.samples:0};
 });
 assert.equal(result.status,'exact');const paired=profile.runs.find(x=>x.fixture===r.fixture&&x.variant==='control');assert.equal(result.score,paired.result.score);assert.deepEqual(result.bestBuild,paired.result.bestBuild);assert.equal(result.upperBound,result.score);
 for(const t of trace)assert.ok(t.result.upperBound>=result.score);
 return {fixture:r.fixture,variant:r.variant,threads:r.threads,result,measurement,categories,liveFrontierBytes:result.peakReadyWork*layout.workItem,proposedLiveFrontierBytes:result.peakReadyWork*layout.indexedWorkProposal};
});
for(const file of files)assert.equal(hash((await readFile(resolve(root,'src-tauri/src',file),'utf8')).replaceAll('\r\n','\n')),sourceHashes[file]);
const report={date:new Date().toISOString(),node:process.version,platform:process.platform,arch:process.arch,sourceHashes,layout,wire,runs,notes:'Layout/wire proposals only; no production edits or implementation speedup claim. Profile categories overlap and worker durations are summed, not wall time. One control/profile pair per fixture.'};
await writeFile(resolve(root,'docs/verification/d4-structure-audit-measurements.json'),JSON.stringify(report,null,2)+'\n');
console.log(JSON.stringify({layout,wire,runs:runs.map(r=>({fixture:r.fixture,variant:r.variant,wallMs:r.result.sessionWallMs,peakReady:r.result.peakReadyWork,categories:r.categories?.map(c=>({name:c.name,calls:c.calls,ms:c.estimatedMs}))}))},null,2));
