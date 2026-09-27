import assert from 'node:assert/strict';
import {readFile,writeFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
import os from 'node:os';
const root=resolve(import.meta.dirname,'..');
const read=async p=>JSON.parse(await readFile(resolve(root,p),'utf8'));
const inputs=await read('docs/verification/d4-utility-conflict-inputs.json');
const runs=[];let sourceHashes;
for(const phase of ['complete','leaves','oracle']){
 const data=await read(`src-tauri/target/slow-profile/utility-${phase}.json`);
 if(sourceHashes)assert.deepEqual(data.sourceHashes,sourceHashes);sourceHashes=data.sourceHashes;
 for(const r of data.runs){
  const {samples,...measurement}=r.measurement,{trace,profile,...result}=r.result;
  assert.equal(result.status,'exact');assert.equal(result.upperBound,result.score);
  const previous=runs.find(x=>x.fixture===r.fixture);if(previous){assert.equal(result.score,previous.result.score);assert.equal(result.bestBuild.id,previous.result.bestBuild.id);}
  const metrics=profile?.categories.map((name,i)=>{
   const c=profile.threads.reduce((a,t)=>({calls:a.calls+t[1][i].calls,samples:a.samples+t[1][i].samples,nanos:a.nanos+t[1][i].nanos}),{calls:0,samples:0,nanos:0});
   return {name,...c,estimatedMs:c.samples?c.nanos/1e6*c.calls/c.samples:null};
  });
  if(phase==='leaves'&&profile){assert.equal(metrics[6].calls+metrics[7].calls,result.enumeratedCompletions);}
  runs.push({...r,phase,measurement:{...measurement,sampleCount:samples.length},result,trace:trace.map(t=>({ms:t.ms,ready:t.ready,score:t.result.score,upperBound:t.result.upperBound,evaluations:t.result.evaluations})),profile:profile?{...profile,metrics}:undefined});
 }
}
const median=a=>a.sort((a,b)=>a-b)[Math.floor(a.length/2)];
const summary=[];let groupsHash;
for(const level of ['loose','medium','tight']){
 const p=await read(`src-tauri/target/regression-audit/utility-${level}.json`);
 const hash=createHash('sha256').update(JSON.stringify(p.groups)).digest('hex');
 assert.equal(hash,inputs.groupsHash);if(groupsHash)assert.equal(hash,groupsHash);groupsHash=hash;
 const control=runs.filter(r=>r.phase==='complete'&&r.fixture===`utility-${level}`&&r.variant==='control');
 const leaf=runs.find(r=>r.phase==='leaves'&&r.fixture===`utility-${level}`&&r.variant==='profile');
 summary.push({level,medianMs:median(control.map(r=>r.result.sessionWallMs)),evaluations:median(control.map(r=>r.result.evaluations)),enumerated:control[0].result.enumeratedCompletions,peakReady:Math.max(...control.map(r=>r.result.peakReadyWork)),rejectedLeaves:leaf.profile.metrics[6].calls,acceptedLeaves:leaf.profile.metrics[7].calls});
}
for(const [name,hash] of Object.entries(sourceHashes))assert.equal(createHash('sha256').update((await readFile(resolve(root,'src-tauri/src',name),'utf8')).replaceAll('\r\n','\n')).digest('hex'),hash);
await writeFile(resolve(root,'docs/verification/d4-utility-conflict-measurements.json'),JSON.stringify({date:new Date().toISOString(),environment:{cpu:os.cpus()[0].model,logical:os.cpus().length,os:os.release(),node:process.version},sourceHashes,groupsHash,inputs,summary,runs},null,2)+'\n');
console.log(JSON.stringify(summary,null,2));
