// Archived, rejected experiment: requires target/shared-problem/{before,after}.rs.
// Isolated before/after pool creation audit. Counts allocation requests on the
// calling thread only; not live bytes, OS thread stacks or whole-process memory.
import assert from 'node:assert/strict';
import {readFile,writeFile,mkdir,copyFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {spawnSync} from 'node:child_process';
import {createHash} from 'node:crypto';
import {projectNativeProblem} from './d4-native-payload-helper.mjs';
const root=resolve(import.meta.dirname,'..'),dir=resolve(root,'src-tauri/target/shared-problem/pool-audit');
await mkdir(resolve(dir,'src'),{recursive:true});
await writeFile(resolve(dir,'Cargo.toml'),'[package]\nname="d4-pool-audit"\nversion="0.0.0"\nedition="2021"\n[dependencies]\nserde={version="1",features=["derive"]}\nserde_json="1"\n');
await copyFile(resolve(root,'src-tauri/Cargo.lock'),resolve(dir,'Cargo.lock'));
await writeFile(resolve(dir,'src/main.rs'),`
#[allow(dead_code)] mod d4_native_evaluator;
#[allow(dead_code)] mod d4_native_solver;
#[allow(dead_code)] mod d4_parallel_runtime;
use std::{alloc::{GlobalAlloc,Layout,System},cell::Cell,io::{self,Read}};
thread_local! {static COUNTS:Cell<(bool,usize,usize)>=const {Cell::new((false,0,0))};}
struct Counting;
fn count(bytes:usize){let _=COUNTS.try_with(|c|{let (active,n,b)=c.get();if active {c.set((true,n+1,b+bytes));}});}
unsafe impl GlobalAlloc for Counting {
 unsafe fn alloc(&self,l:Layout)->*mut u8{count(l.size());System.alloc(l)}
 unsafe fn alloc_zeroed(&self,l:Layout)->*mut u8{count(l.size());System.alloc_zeroed(l)}
 unsafe fn realloc(&self,p:*mut u8,l:Layout,n:usize)->*mut u8{count(n);System.realloc(p,l,n)}
 unsafe fn dealloc(&self,p:*mut u8,l:Layout){System.dealloc(p,l)}
}
#[global_allocator] static ALLOC:Counting=Counting;
pub fn begin(){COUNTS.with(|c|c.set((true,0,0)));}
pub fn finish()->(usize,usize){COUNTS.with(|c|{let (_,n,b)=c.replace((false,0,0));(n,b)})}
fn main(){let mut text=String::new();io::stdin().read_to_string(&mut text).unwrap();
 println!("{}",d4_native_solver::audit_pool_creation(serde_json::from_str(&text).unwrap()));}
`);
const files=['d4_native_evaluator.rs','d4_native_solver.rs','d4_native_stats.rs','d4_parallel_runtime.rs'];
const hash=s=>createHash('sha256').update(s.replaceAll('\r\n','\n')).digest('hex');
const beforeHashes=JSON.parse(await readFile(resolve(dir,'../before-source-hashes.json'),'utf8'));
const hashes={before:{},after:{}};
for(const variant of ['before','after']) {
 for(const file of files){
  let source=await readFile(file==='d4_native_solver.rs'?resolve(dir,`../${variant}.rs`):resolve(root,'src-tauri/src',file),'utf8');
  hashes[variant][file]=hash(source);
  if(variant==='before')assert.equal(hashes[variant][file],beforeHashes[file]);
  if(file==='d4_native_solver.rs')source+=`
pub fn audit_pool_creation(problem:NativeProblem)->serde_json::Value {
 let session=NativeSearchSession::new(problem).unwrap();let mut samples=Vec::new();
 for repeat in 0..10 {
  crate::begin();let start=Instant::now();
  let pool=NodePool::new(&session.problem,session.requirements,16).unwrap();
  let ms=start.elapsed().as_secs_f64()*1000.0;let (calls,bytes)=crate::finish();drop(pool);
  if repeat>=2 {samples.push(serde_json::json!({"ms":ms,"calls":calls,"requestedBytes":bytes}));}
 }
 serde_json::json!({"samples":samples})
}
`;
  await writeFile(resolve(dir,'src',file),source);
 }
 const build=spawnSync('cargo',['build','--offline','--release','--manifest-path',resolve(dir,'Cargo.toml')],{encoding:'utf8'});
 assert.equal(build.status,0,build.stderr);
 await copyFile(resolve(dir,'target/release/d4-pool-audit.exe'),resolve(dir,variant+'.exe'));
}
if(process.argv[2]==='build') {console.log('pool audit built');process.exit(0);}
const runs=[];
for(const fixture of ['revenir','dual','utility-tight']) {
 const bytes=await readFile(resolve(root,'src-tauri/target/regression-audit',fixture+'.json'),'utf8');
 const problem=projectNativeProblem(JSON.parse(bytes));
 for(const variant of ['before','after']) {
  const r=spawnSync(resolve(dir,variant+'.exe'),{input:JSON.stringify(problem),encoding:'utf8'});
  assert.equal(r.status,0,r.stderr);runs.push({fixture,variant,inputHash:hash(bytes),...JSON.parse(r.stdout)});
 }
}
const median=a=>{const s=[...a].sort((x,y)=>x-y);return (s[3]+s[4])/2;};
const summary=runs.map(r=>({fixture:r.fixture,variant:r.variant,medianMs:median(r.samples.map(s=>s.ms)),medianCalls:median(r.samples.map(s=>s.calls)),medianRequestedBytes:median(r.samples.map(s=>s.requestedBytes))}));
await writeFile(resolve(root,'docs/verification/d4-shared-problem-pool.json'),JSON.stringify({date:new Date().toISOString(),hashes,threads:16,warmups:2,repeats:8,notes:'Calling-thread allocation/reallocation requests during pool construction only; includes thread launch scaffolding, excludes worker-thread allocations and native OS stacks. Requested bytes are not retained/live memory.',summary,runs},null,2)+'\n');
console.log(JSON.stringify(summary,null,2));
