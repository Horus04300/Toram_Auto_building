import assert from 'node:assert/strict';
import { readFile, writeFile, mkdir } from 'node:fs/promises';
import { spawn, spawnSync } from 'node:child_process';
import { createHash } from 'node:crypto';
import { cpus } from 'node:os';
import { resolve, dirname } from 'node:path';
import { parseArgs } from 'node:util';
import { root, jsSources, loadHeadlessEnvironment } from '../support/crysta-headless-environment.mjs';
import { createHeadlessTransport } from '../support/crysta-headless-transport.mjs';
import { measureComputation } from '../support/crysta-computation-measurement.mjs';

const { values } = parseArgs({ options:{ child:{type:'boolean'}, case:{type:'string'}, disabled:{type:'boolean'},
  repeats:{type:'string',default:'10'}, output:{type:'string',default:'docs/verification/crysta-candidate-projection-measurements.json'} } });
const baseline = JSON.parse(await readFile(resolve(root,'docs/verification/crysta-infeasible-seed-repair-measurements.json'),'utf8'));
const inputs=Object.fromEntries(Object.entries(baseline.inputs).map(([id,entry])=>[id,entry.input.resolvedExecutionContext||entry.input]));
const binary=resolve(root,'src-tauri/target/release/crysta_headless_service'+(process.platform==='win32'?'.exe':''));
const hash=data=>createHash('sha256').update(data).digest('hex');
const sourcePaths=[...jsSources.map(path=>'assets/js/'+path),
  'tools/support/crysta-headless-environment.mjs','tools/support/crysta-headless-transport.mjs',
  'tools/support/crysta-computation-measurement.mjs','tools/benchmarks/benchmark-crysta-candidate-projection.mjs'];
async function hashes(paths) { return Object.fromEntries(await Promise.all(paths.map(async path=>[path,hash((await readFile(resolve(root,path),'utf8')).replaceAll('\r\n','\n'))]))); }
if(values.child) {
  assert.ok(inputs[values.case]);
  const transport=createHeadlessTransport(binary);
  try {
    const env=await loadHeadlessEnvironment(transport.core);
    let rawCounts;
    const client={...env.client,optimize:(problem,callbacks,options)=>env.client.optimize(problem,callbacks,{...options,disableCandidateProjection:Boolean(values.disabled)})};
    const {result,timing}=await measureComputation({client,compile:()=>{
      const input=env.compile(inputs[values.case]);rawCounts=input.groups.map(group=>group.packages.length);return input;
    }});
    assert.equal(result.status,'exact');assert.equal(result.exact,true);assert.equal(timing.cached,false);
    assert.equal(result.outcomes.constraints.feasible,true);assert.equal(result.outcomes.damage.expected,result.score);
    const stats={};
    for(const candidate of result.bestBuild.packages)for(const [key,value] of Object.entries(candidate.statDelta))stats[key]=(stats[key]||0)+value;
    assert.deepEqual(result.bestBuild.statDelta,stats);
    let nativePeakMiB=null;
    if(process.platform==='win32') {
      const memory=spawnSync('powershell.exe',['-NoProfile','-Command',`(Get-Process -Id ${transport.metadata.nativePid}).PeakWorkingSet64`],{windowsHide:true,encoding:'utf8'});
      assert.equal(memory.status,0,memory.stderr);nativePeakMiB=Number(memory.stdout.trim())/1048576;
      assert.ok(Number.isFinite(nativePeakMiB)&&nativePeakMiB>0);
    }
    console.log(JSON.stringify({case:values.case,disabled:Boolean(values.disabled),timing,nativeElapsedMs:result.elapsedMs,
      nativePeakMiB,jsHeapAtResultMiB:process.memoryUsage().heapUsed/1048576,visitedNodes:result.visitedNodes,evaluations:result.evaluations,
      rawCounts,preparedCounts:result.frontierReports.map(report=>report.outputCount),frontierReports:result.frontierReports,
      projection:result.candidateProjectionReport,versions:env.client.cachePolicy,
      best:{id:result.bestBuild.id,packageIds:result.bestBuild.packages.map(candidate=>candidate.id),statDelta:result.bestBuild.statDelta,score:result.score}}));
  } finally { await transport.close(); }
} else {
  const repeats=Number(values.repeats);assert.ok(Number.isInteger(repeats)&&repeats>0&&repeats<=100);
  const stamp=JSON.parse(await readFile(binary+'.measurement.json','utf8'));
  assert.deepEqual(await hashes(Object.keys(stamp.sources)),stamp.sources,'Rebuild the measurement service after Rust changes');
  assert.equal(hash(await readFile(binary)),stamp.binaryHash);
  const sources=await hashes(sourcePaths),output=resolve(root,values.output);
  const report={schema:'toram.crysta-candidate-projection-measurement.v1',date:new Date().toISOString(),
    environment:{node:process.version,platform:process.platform,cpu:cpus()[0]?.model,logicalThreads:cpus().length},
    method:{repeats,freshProcess:true,order:'alternating before/after; same final code and native binary',
      timing:'raw compile through final product-client JS evaluation, UI excluded',nativeMemory:'Windows PeakWorkingSet64 read after result; service still alive',
      jsMemory:'heap at result, not a peak'},binaryHash:stamp.binaryHash,rustSourceHashes:stamp.sources,jsSourceHashes:sources,inputs,runs:[],summary:{}};
  await mkdir(dirname(output),{recursive:true});
  function sample(id,disabled) {
    return new Promise((yes,no)=>{
      const child=spawn(process.execPath,[import.meta.filename,'--child','--case',id,...(disabled?['--disabled']:[])],{cwd:root,windowsHide:true,stdio:['ignore','pipe','pipe']});
      let stdout='',stderr='';
      const timer=setTimeout(()=>{
        if(process.platform==='win32')spawn('taskkill',['/pid',String(child.pid),'/t','/f'],{windowsHide:true,stdio:'ignore'});else child.kill();
        no(new Error('Projection benchmark watchdog expired'));
      },180000);
      child.stdout.on('data',data=>stdout+=data);child.stderr.on('data',data=>stderr+=data);
      child.on('error',error=>{clearTimeout(timer);no(error);});
      child.on('close',code=>{clearTimeout(timer);if(code!==0){no(new Error(stderr||stdout));return;}try{yes(JSON.parse(stdout));}catch(error){no(error);}});
    });
  }
  const mean=values=>values.reduce((sum,value)=>sum+value,0)/values.length;
  function summary(runs) {
    const times=runs.map(run=>run.timing.totalMs).sort((a,b)=>a-b);
    return {preparedCounts:runs[0].preparedCounts,visitedNodes:mean(runs.map(r=>r.visitedNodes)),evaluations:mean(runs.map(r=>r.evaluations)),
      totalMs:mean(times),totalP95Ms:times[Math.ceil(times.length*.95)-1],nativeMs:mean(runs.map(r=>r.nativeElapsedMs)),
      nativePeakMiB:mean(runs.map(r=>r.nativePeakMiB)),jsHeapAtResultMiB:mean(runs.map(r=>r.jsHeapAtResultMiB))};
  }
  for(const id of Object.keys(inputs)) {
    for(let repeat=0;repeat<repeats;repeat++) {
      for(const disabled of repeat%2?[false,true]:[true,false]) {
        const run=await sample(id,disabled);
        const prior=report.runs.find(previous=>previous.case===id);
        if(prior)assert.deepEqual(run.best,prior.best,'Exact score, full combination, raw options and tie ID changed');
        report.runs.push({repeat:repeat+1,...run});
      }
    }
    assert.deepEqual(await hashes(sourcePaths),sources,'Sources changed during measurement');
    const runs=report.runs.filter(run=>run.case===id);
    report.summary[id]={before:summary(runs.filter(r=>r.disabled)),after:summary(runs.filter(r=>!r.disabled))};
    await writeFile(output,JSON.stringify(report,null,2)+'\n');
    console.log(JSON.stringify({case:id,...report.summary[id]}));
  }
  assert.equal(report.runs.length,Object.keys(inputs).length*repeats*2);
}
