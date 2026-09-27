// Compare saved release bridges with identical once-per-second progress sampling.
import assert from 'node:assert/strict';
import {readFile,writeFile} from 'node:fs/promises';
import {spawn} from 'node:child_process';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
const root=resolve(import.meta.dirname,'..'),dir=resolve(root,'src-tauri/target/heap-audit');
const repeats=Number(process.env.D4_HEAP_REPEATS||3);
assert.ok(Number.isInteger(repeats)&&repeats>0,'D4_HEAP_REPEATS must be a positive integer');
const runs=[];
const sha=bytes=>createHash('sha256').update(bytes).digest('hex');
const binaries=Object.fromEntries(await Promise.all(['before','after'].map(async name=>[name,sha(await readFile(resolve(dir,name+'.exe')))])));
const inputHashes={};
for(const fixture of (process.env.D4_HEAP_FIXTURES||'revenir,dual,basic,hp40000,magic').split(',')) {
 assert.match(fixture,/^[a-z0-9-]+$/);
 const source=await readFile(resolve(root,'src-tauri/target/regression-audit',fixture+'.json'),'utf8');
 const problem=JSON.parse(source);inputHashes[fixture]=sha(source);
 for(let repeat=1;repeat<=repeats;repeat++) for(const variant of repeat%2?['before','after']:['after','before']){
  const input=resolve(dir,'input.json'),output=resolve(dir,'output.json');
  await writeFile(input,JSON.stringify({...problem,threads:16}));
  const measurement=JSON.parse(await new Promise((yes,no)=>{
   const p=spawn('powershell.exe',['-NoProfile','-NonInteractive','-ExecutionPolicy','Bypass','-File',resolve(root,'tools/measure-d4-native-p6.ps1'),'-Binary',resolve(dir,variant+'.exe'),'-InputPath',input,'-Output',output,'-ErrorOutput',resolve(dir,'error.txt')],{env:{...process.env,D4_SESSION_BENCH_MS:'120000'},stdio:['ignore','pipe','pipe']});
   let out='',err='';p.stdout.on('data',d=>out+=d);p.stderr.on('data',d=>err+=d);p.on('error',no);p.on('close',c=>c===0?yes(out):no(new Error(err)));
  }));
  const result=JSON.parse(await readFile(output,'utf8'));
  assert.equal(result.status,'exact');assert.equal(result.upperBound,result.score);
  const previous=runs.find(r=>r.fixture===fixture);
  if(previous){assert.equal(result.score,previous.result.score);assert.equal(result.bestBuild.id,previous.result.bestBuild.id);}
  if(problem.auditOracle){assert.equal(result.score,problem.auditOracle.score);assert.equal(result.bestBuild.id,problem.auditOracle.id);}
  const {samples,...metrics}=measurement;
  runs.push({fixture,repeat,variant,threads:16,measurement:{...metrics,cpuMs:Math.max(metrics.cpuMs,...samples.map(s=>s.cpuMs))},result});
  await writeFile(resolve(dir,process.env.D4_HEAP_REPORT||'measurements.json'),JSON.stringify({date:new Date().toISOString(),binaries,inputHashes,runs},null,2));
  console.log(`${fixture} ${repeat} ${variant}: ${result.sessionWallMs.toFixed(1)}ms ${result.score}`);
 }
}
