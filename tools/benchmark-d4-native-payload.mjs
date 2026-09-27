// Measure the production projection, JSON serialization and Rust deserialization.
// Native CLI comparisons do not measure WebView/Tauri IPC latency.
import assert from 'node:assert/strict';
import {readFile,writeFile,mkdir,copyFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {spawnSync} from 'node:child_process';
import {createHash} from 'node:crypto';
import {performance} from 'node:perf_hooks';
import {projectNativeProblem} from './d4-native-payload-helper.mjs';

const root=resolve(import.meta.dirname,'..'),dir=resolve(root,'src-tauri/target/native-payload');
await mkdir(resolve(dir,'src'),{recursive:true});
const hash=s=>createHash('sha256').update(s).digest('hex');
const sourceHashes={};
for(const file of ['d4_native_evaluator.rs','d4_native_solver.rs','d4_native_stats.rs','d4_parallel_runtime.rs']) {
 const source=(await readFile(resolve(root,'src-tauri/src',file),'utf8')).replaceAll('\r\n','\n');
 sourceHashes[file]=hash(source);await writeFile(resolve(dir,'src',file),source);
}
const clientSource=await readFile(resolve(root,'assets/js/d4-native-client.js'),'utf8');
sourceHashes['d4-native-client.js']=hash(clientSource.replaceAll('\r\n','\n'));
await writeFile(resolve(dir,'Cargo.toml'),'[package]\nname="d4-payload-check"\nversion="0.0.0"\nedition="2021"\n[dependencies]\nserde={version="1",features=["derive"]}\nserde_json="1"\n');
await copyFile(resolve(root,'src-tauri/Cargo.lock'),resolve(dir,'Cargo.lock'));
await writeFile(resolve(dir,'src/main.rs'),`
#[allow(dead_code)] mod d4_native_evaluator;
#[allow(dead_code)] mod d4_native_solver;
#[allow(dead_code)] mod d4_parallel_runtime;
use std::{io::{self,Read},time::Instant,hint::black_box};
use d4_native_solver::NativeProblem;
fn main() {
 let mut text=String::new();io::stdin().read_to_string(&mut text).unwrap();
 let inputs:[String;2]=serde_json::from_str(&text).unwrap();
 let values:Vec<_>=inputs.iter().map(|s| serde_json::to_value(serde_json::from_str::<NativeProblem>(s).unwrap()).unwrap()).collect();
 assert_eq!(values[0],values[1],"NativeProblem must consume identical values");
 let mut times=[Vec::new(),Vec::new()];
 for repeat in 0..22 { for i in if repeat%2==0 {[0,1]} else {[1,0]} {
  let start=Instant::now();let parsed=serde_json::from_str::<NativeProblem>(black_box(&inputs[i])).unwrap();
  let ms=start.elapsed().as_secs_f64()*1000.0;black_box(&parsed);
  if repeat>=2 {times[i].push(ms);}
 }}
 println!("{}",serde_json::json!({"nativeValuesEqual":true,"parseMs":times}));
}
`);
const build=spawnSync('cargo',['build','--offline','--release','--manifest-path',resolve(dir,'Cargo.toml')],{encoding:'utf8'});
assert.equal(build.status,0,build.stderr);
const median=a=>{const s=[...a].sort((x,y)=>x-y);return (s[(s.length-1)>>1]+s[s.length>>1])/2;};
const fixtures=[];
for(const fixture of ['revenir','dual','utility-tight']) {
 const bytes=await readFile(resolve(root,'src-tauri/target/regression-audit',fixture+'.json'));
 const original=JSON.parse(bytes),compact=projectNativeProblem(original);
 const json=[JSON.stringify(original),JSON.stringify(compact)];
 assert.deepEqual(compact.groups.map(g=>g.packages.map(p=>p.statDelta)),original.groups.map(g=>g.packages.map(p=>p.statDelta)));
 const serializationMs=[[],[]];
 for(let repeat=0;repeat<22;repeat++)for(const i of repeat%2?[1,0]:[0,1]) {
  const start=performance.now();
  const encoded=JSON.stringify(i===0?original:projectNativeProblem(original));
  const elapsed=performance.now()-start;
  assert.equal(encoded,json[i]);if(repeat>=2)serializationMs[i].push(elapsed);
 }
 const rust=spawnSync(resolve(dir,'target/release/d4-payload-check.exe'),{input:JSON.stringify(json),encoding:'utf8',maxBuffer:8*1024*1024});
 assert.equal(rust.status,0,rust.stderr);
 const parsed=JSON.parse(rust.stdout);
 fixtures.push({fixture,inputHash:hash(bytes),bytes:json.map(s=>Buffer.byteLength(s)),serializationMs,serializationMedianMs:serializationMs.map(median),...parsed,parseMedianMs:parsed.parseMs.map(median)});
 console.log(JSON.stringify(fixtures.at(-1)));
}
await writeFile(resolve(root,'docs/verification/d4-native-payload-serialization.json'),JSON.stringify({date:new Date().toISOString(),node:process.version,platform:process.platform,arch:process.arch,sourceHashes,notes:'20 alternating samples after 2 warmups; same Node realm. Compact serialization includes projection. Rust timing excludes stdin, parse of the outer harness and destruction. Not WebView IPC or end-to-end solver timing.',fixtures},null,2)+'\n');
