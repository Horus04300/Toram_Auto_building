// Compare before/after checkpoints using isolated bridges.
import assert from 'node:assert/strict';
import {readFile,writeFile,mkdir,copyFile} from 'node:fs/promises';
import {spawnSync} from 'node:child_process';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
const experiment=process.env.D4_EVALUATION_EXPERIMENT||'indexed-tree';
assert.match(experiment,/^[a-z0-9-]+$/);
const root=resolve(import.meta.dirname,'..'),dir=resolve(root,`src-tauri/target/${experiment}/checkpoint`);
await mkdir(resolve(dir,'src'),{recursive:true});
await writeFile(resolve(dir,'Cargo.toml'),'[package]\nname="d4-checkpoint-compat"\nversion="0.0.0"\nedition="2021"\n[dependencies]\nserde={version="1",features=["derive"]}\nserde_json="1"\n');
await copyFile(resolve(root,'src-tauri/Cargo.lock'),resolve(dir,'Cargo.lock'));
await writeFile(resolve(dir,'src/main.rs'),`
#[allow(dead_code)] mod d4_native_evaluator;
#[allow(dead_code)] mod d4_native_solver;
#[allow(dead_code)] mod d4_parallel_runtime;
use std::io::{self,Read};
use d4_native_solver::{NativeProblem,NativeSearchSession,NativeSearchCheckpoint};
fn main()->Result<(),String>{
 let mut input=String::new();io::stdin().read_to_string(&mut input).unwrap();
 let export=std::env::args().nth(1).as_deref()==Some("export");
 let mut session=if export {NativeSearchSession::new(serde_json::from_str::<NativeProblem>(&input).unwrap())?}
 else {NativeSearchSession::from_checkpoint(serde_json::from_str::<NativeSearchCheckpoint>(&input).unwrap())?};
 if export {session.run_slice(3)?;println!("{}",serde_json::to_string(&session.checkpoint()?).unwrap());}
 else {while !session.is_complete(){session.run_parallel_slice(128,4)?;}println!("{}",serde_json::to_string(&session.snapshot()).unwrap());}
 Ok(())
}
`);
const files=['d4_native_evaluator.rs','d4_native_solver.rs','d4_native_stats.rs','d4_parallel_runtime.rs'];
const hash=s=>createHash('sha256').update(s.replaceAll('\r\n','\n')).digest('hex');
const beforeHashes=JSON.parse(await readFile(resolve(dir,'../before-source-hashes.json'),'utf8'));
const hashes={before:{},after:{}};
for(const variant of ['before','after']){
 for(const file of files){
  const path=variant==='before'&&file==='d4_native_solver.rs'?resolve(dir,'../before.rs'):resolve(root,'src-tauri/src',file);
  const source=await readFile(path,'utf8');hashes[variant][file]=hash(source);
  if(variant==='before')assert.equal(hashes[variant][file],beforeHashes[file]);
  await writeFile(resolve(dir,'src',file),source);
 }
 const built=spawnSync('cargo',['build','--offline','--release','--manifest-path',resolve(dir,'Cargo.toml')],{cwd:root,encoding:'utf8'});assert.equal(built.status,0,built.stderr);
 await copyFile(resolve(dir,'target/release/d4-checkpoint-compat.exe'),resolve(dir,variant+'.exe'));
}
const original=JSON.parse(await readFile(resolve(root,'src-tauri/target/regression-audit/revenir.json'),'utf8'));
// All equal damage forces nonempty frontier and lexical ties through resume.
const problem={...original,metadata:{modeledKeys:['ATKP']},scenarioSnapshot:{requirements:{maxHp:null,maxMp:null,amprBeforeDual:null,normalAttackCrit:null,aspd:null}},groups:original.groups.map((g,index)=>({id:g.id,packages:Array.from({length:8},(_,i)=>({id:index+':'+i,statDelta:{ATKP:1,DROP_RATE:i,PHYS_RES:-2}}))}))};
function run(variant,mode,input){const r=spawnSync(resolve(dir,variant+'.exe'),[mode],{input:JSON.stringify(input),encoding:'utf8'});assert.equal(r.status,0,r.stderr);return JSON.parse(r.stdout);}
const checkpoints={};for(const variant of ['before','after']){const c=run(variant,'export',problem);assert.ok(c.frontier.length>0);delete c.elapsedMs;checkpoints[variant]=c;}
assert.deepEqual(checkpoints.after,checkpoints.before,'wire checkpoint must preserve the exact frontier and counters');
let expected;const results=[];
for(const source of ['before','after'])for(const destination of ['before','after']){
 const result=run(destination,'import',{...checkpoints[source],elapsedMs:0});assert.equal(result.status,'exact');delete result.elapsedMs;
 const semantic={score:result.score,bestBuild:result.bestBuild,upperBound:result.upperBound};if(expected)assert.deepEqual(semantic,expected);else expected=semantic;
 results.push({source,destination,result});
}
await writeFile(resolve(root,`docs/verification/d4-${experiment}-checkpoint.json`),JSON.stringify({date:new Date().toISOString(),hashes,checkpoint:checkpoints.after,results},null,2)+'\n');
console.log(`${experiment} checkpoint: PASS (identical partial wire state; 4 cross-version resumes, exact score and full build)`);
