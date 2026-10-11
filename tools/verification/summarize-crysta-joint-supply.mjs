// Summarize completed cold runs; never compare bounded samples as exact work.
import assert from 'node:assert/strict';
import {readFile,writeFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
import {cpus} from 'node:os';
import {root,jsSources} from '../support/crysta-headless-environment.mjs';
const dir=resolve(root,'src-tauri/target/joint-supply');
const read=async path=>JSON.parse((await readFile(path,'utf8')).replace(/^\uFEFF/u,''));
const hash=value=>createHash('sha256').update(value).digest('hex');
const runs=await read(resolve(dir,'comparisons.json'));
assert.equal(runs.length,100);
const before=await read(resolve(root,'src-tauri/target/dramatic-bound/after-build.json'));
assert.equal(before.binaryHash,hash(await readFile(resolve(dir,'before.exe'))));
const afterFiles=[...Object.keys(before.sources),'src-tauri/src/optimization/joint_supply.rs'];
const after={sources:Object.fromEntries(await Promise.all(afterFiles.map(async path=>[path,hash((await readFile(resolve(root,path),'utf8')).replaceAll('\r\n','\n'))]))),binaryHash:hash(await readFile(resolve(dir,'after.exe')))};
const jsSourceHashes=Object.fromEntries(await Promise.all(jsSources.map(async path=>[path,hash(await readFile(resolve(root,'assets/js',path)))])));
const summary=[];
const mean=values=>values.reduce((a,b)=>a+b,0)/values.length;
for(const fixture of new Set(runs.map(run=>run.fixture))) {
  const rows=runs.filter(run=>run.fixture===fixture),reference=rows[0].sample;
  for(const row of rows) {
    assert.equal(row.sample.status,'exact');assert.equal(row.sample.score,reference.score);
    assert.deepEqual(row.sample.bestBuild,reference.bestBuild);
    assert.equal(row.sample.compiledHash,reference.compiledHash);assert.equal(row.sample.preparedHash,reference.preparedHash);
  }
  const metrics={};
  for(const variant of ['before','after']) {
    const selected=rows.filter(row=>row.variant===variant);assert.equal(selected.length,10);
    const total=selected.map(row=>row.sample.profile.totalMs).sort((a,b)=>a-b);
    metrics[variant]={visitedNodes:mean(selected.map(row=>row.sample.visitedNodes)),evaluations:mean(selected.map(row=>row.sample.evaluations)),
      enumeratedCompletions:mean(selected.map(row=>row.sample.enumeratedCompletions)),totalMs:mean(total),p95TotalMs:total[Math.ceil(total.length*.95)-1],
      nativeMs:mean(selected.map(row=>row.sample.profile.nativeMs)),nativePeakMiB:mean(selected.map(row=>row.nativePeakWorkingSetBytes))/1048576};
  }
  summary.push({fixture,score:reference.score,...metrics,reductionPercent:Object.fromEntries(['visitedNodes','evaluations','totalMs','nativeMs'].map(key=>[key,100*(1-metrics.after[key]/metrics.before[key])])),nativePeakDeltaMiB:metrics.after.nativePeakMiB-metrics.before.nativePeakMiB});
}
const trace=await read(resolve(root,'src-tauri/target/search-trace/report-1.json'));
for(const [file,digest] of Object.entries(trace.rustSourceHashes)) assert.equal(digest,after.sources['src-tauri/src/optimization/'+file]);
const processTrace={inputHash:trace.inputHash,rustSourceHashes:trace.rustSourceHashes,threads:trace.threads,batchLimit:trace.batchLimit,batches:trace.batches.length-1,
  initial:trace.batches[0],final:trace.batches.at(-1),peakReady:trace.peakReady,counts:trace.counts,samples:trace.samples,checks:trace.checks,
  warning:'Instrumentation is process/count evidence, not product timing. Seed improvement counters include temporary ranking states.'};
const inputs={};
for(const [name,path] of Object.entries({'saved-revenir':'tools/fixtures/crysta-saved-sword-shield-revenir-etowal.json','saved-normal':'src-tauri/target/general-upper-bound/saved-normal.json',
  'saved-unlocked':'tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json','old-revenir':'tools/fixtures/crysta-native-runtime-26min-revenir.json','old-locked':'src-tauri/target/constrained-upper-bound/revenir-locked.json'})) {
  const value=await read(resolve(root,path));inputs[name]={path,sha256:hash(await readFile(resolve(root,path))),resolvedExecutionContext:value.resolvedExecutionContext||value};
}
const report={date:new Date().toISOString(),schema:'toram.crysta-joint-supply-bound-measurements.v1',environment:{node:process.version,cpu:cpus()[0].model,threads:16,platform:process.platform},
  method:'Five unchanged raw inputs, 10 fresh Node/Native processes per variant; sequential alternating order. Same current JS. Native-only peak working set sampled every 25ms.',
  policy:{before:'Native v18',after:'Native v19 / evaluator v4',jsClient:'v19 for both variants'},stamps:{before,after},jsSourceHashes,inputs,summary,runs,processTrace};
await writeFile(resolve(root,'docs/verification/crysta-joint-supply-bound-measurements.json'),JSON.stringify(report,null,2)+'\n');
console.log(JSON.stringify(summary,null,2));
