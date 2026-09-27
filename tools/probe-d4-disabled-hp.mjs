// Isolated candidate experiment. Never modifies product Rust sources.
import assert from 'node:assert/strict';
import {readFile,writeFile,mkdir,copyFile} from 'node:fs/promises';
import {spawn} from 'node:child_process';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
const root=resolve(import.meta.dirname,'..'),dir=resolve(root,'src-tauri/target/disabled-hp-probe'),crate=resolve(dir,'crate');
const hash=b=>createHash('sha256').update(b).digest('hex');
const files=['d4_native_evaluator.rs','d4_native_solver.rs','d4_native_stats.rs','d4_parallel_runtime.rs','bin/d4_native_parallel.rs'];
const sources=Object.fromEntries(await Promise.all(files.map(async f=>[f,(await readFile(resolve(root,'src-tauri/src',f),'utf8')).replaceAll('\r\n','\n')])));
const sourceHashes=Object.fromEntries(Object.entries(sources).map(([f,s])=>[f,hash(s)]));
const run=(cmd,args,env={})=>new Promise((yes,no)=>{
 const p=spawn(cmd,args,{cwd:root,env:{...process.env,...env}});let out='',err='';
 p.stdout.on('data',d=>out+=d);p.stderr.on('data',d=>err+=d);p.on('error',no);p.on('close',c=>c===0?yes(out):no(new Error(err+out)));
});
function replace(s,a,b){assert.equal(s.split(a).length,2,'unique anchor: '+a);return s.replace(a,b);}
if(process.argv[2]==='build'){
 await mkdir(resolve(crate,'src/bin'),{recursive:true});
 await writeFile(resolve(crate,'Cargo.toml'),'[package]\nname="d4-disabled-hp-probe"\nversion="0.0.0"\nedition="2021"\n[dependencies]\nserde={version="1",features=["derive"]}\nserde_json="1"\n');
 await copyFile(resolve(root,'src-tauri/Cargo.lock'),resolve(crate,'Cargo.lock'));
 for(const variant of ['control','skip-hp']){
  let evaluator=sources['d4_native_evaluator.rs'];
  if(variant==='skip-hp'){
   evaluator=replace(evaluator,'    weapon: WeaponKind,','    skip_hp_probe: bool,\n    weapon: WeaponKind,');
   evaluator=replace(evaluator,'            weapon: WeaponKind::from_name(main),','            skip_hp_probe: flag(base, "_skipHpProbe"),\n            weapon: WeaponKind::from_name(main),');
   const start=evaluator.indexOf('    let vit = stat_total(base, stats, "vitBase"'),end=evaluator.indexOf('    if !accepts(0, max_hp)',start);
   assert.ok(start>0&&end>start);
   const vit='    let vit = stat_total(base, stats, "vitBase", "vitP", "vitF", "VITP", "VIT");\n';
   let hp=evaluator.slice(start,end).replace(vit,'').replace('    let level = number(base, "level");\n','').replace('    let max_hp =','    ');
   assert.ok(hp.endsWith('as i64;\n'));hp=hp.slice(0,-2)+'\n';
   evaluator=evaluator.slice(0,start)+vit+'    let level = number(base, "level");\n    let max_hp = if !RAW_AMPR && plan.skip_hp_probe {0} else {\n'+hp+'    };\n'+evaluator.slice(end);
  }
  for(const f of files)await writeFile(resolve(crate,'src',f),f==='d4_native_evaluator.rs'?evaluator:sources[f]);
  await run('cargo',['build','--offline','--release','--manifest-path',resolve(crate,'Cargo.toml'),'--bin','d4_native_parallel']);
  await copyFile(resolve(crate,'target/release/d4_native_parallel.exe'),resolve(dir,variant+'.exe'));
  console.log('built '+variant);
 }
 await writeFile(resolve(dir,'source-hashes.json'),JSON.stringify(sourceHashes,null,2));
}else if(['run','projection'].includes(process.argv[2])){
 assert.deepEqual(sourceHashes,JSON.parse(await readFile(resolve(dir,'source-hashes.json'),'utf8')));
 const runs=[],projection=process.argv[2]==='projection',candidate=projection?'projected':'skip-hp';
 const dense=JSON.parse(sources['d4_native_stats.rs'].match(/const KEYS: \[&str; 36\] = (\[[\s\S]*?\]);/)[1].replace(/,\s*\]/,']'));
 const used=new Set([...dense,'MOTIONSPEED']);
 for(const fixture of projection?['revenir','dual','utility-tight']:['revenir','utility-tight'])for(let repeat=1;repeat<=2;repeat++)for(const variant of repeat===1?['control',candidate]:[candidate,'control']){
  const bytes=await readFile(resolve(root,'src-tauri/target/regression-audit',fixture+'.json'));
  const problem=JSON.parse(bytes);problem.threads=16;
  if(!projection){assert.equal(problem.scenarioSnapshot.requirements.maxHp,null,'probe requires disabled HP target');problem.baseContext._skipHpProbe=true;}
  if(projection){
   assert.ok(problem.metadata.modeledKeys.every(k=>used.has(k)),'keep every tree coordinate');
   if(variant==='projected')for(const group of problem.groups)for(const pkg of group.packages)pkg.statDelta=Object.fromEntries(Object.entries(pkg.statDelta).filter(([k])=>used.has(k)));
  }
  await writeFile(resolve(dir,'input.json'),JSON.stringify(problem));
  const measurement=JSON.parse(await run('powershell.exe',['-NoProfile','-NonInteractive','-ExecutionPolicy','Bypass','-File',resolve(root,'tools/measure-d4-native-p6.ps1'),'-Binary',resolve(dir,(projection?'control':variant)+'.exe'),'-InputPath',resolve(dir,'input.json'),'-Output',resolve(dir,'output.json'),'-ErrorOutput',resolve(dir,'error.txt')],{D4_SESSION_BENCH_MS:'120000'}));
  const result=JSON.parse(await readFile(resolve(dir,'output.json'),'utf8'));
  assert.equal(result.status,'exact');assert.equal(result.upperBound,result.score);
  const prior=runs.find(r=>r.fixture===fixture);if(prior){assert.equal(result.score,prior.result.score);assert.equal(result.bestBuild.id,prior.result.bestBuild.id);}
  const {samples,...metrics}=measurement;
  runs.push({fixture,repeat,variant,inputHash:hash(bytes),executedInputHash:hash(JSON.stringify(problem)),measurement:metrics,result});
  await writeFile(resolve(root,`docs/verification/d4-${projection?'stat-projection':'disabled-hp'}-probe-measurements.json`),JSON.stringify({date:new Date().toISOString(),sourceHashes,runs},null,2)+'\n');
  console.log(`${fixture} ${repeat} ${variant}: ${(result.sessionWallMs/1000).toFixed(3)}s eval=${result.evaluations}`);
 }
}else throw new Error('use build, run, or projection');
