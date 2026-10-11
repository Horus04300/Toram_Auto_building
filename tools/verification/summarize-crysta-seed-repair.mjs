import assert from 'node:assert/strict';
import {readFile,writeFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
import {cpus} from 'node:os';
import {root,jsSources} from '../support/crysta-headless-environment.mjs';
const dir=resolve(root,'src-tauri/target/seed-repair');
const read=async path=>JSON.parse((await readFile(path,'utf8')).replace(/^\uFEFF/u,''));
const hash=bytes=>createHash('sha256').update(bytes).digest('hex');
const rustHash=async path=>hash((await readFile(resolve(root,path),'utf8')).replaceAll('\r\n','\n'));
const runs=await read(resolve(dir,'comparisons.json'));
assert.equal(runs.length,140);
const previous=await read(resolve(root,'docs/verification/crysta-joint-supply-bound-measurements.json'));
const before=previous.stamps.after;
assert.equal(before.binaryHash,hash(await readFile(resolve(dir,'before.exe'))));
assert.equal(before.sources['src-tauri/src/optimization/solver.rs'],await rustHash('src-tauri/target/kanayogan-analysis/before-seed-repair-solver.rs'));
const after={sources:Object.fromEntries(await Promise.all(Object.keys(before.sources).map(async path=>[path,await rustHash(path)]))),binaryHash:hash(await readFile(resolve(dir,'after.exe')))};
for(const [path,digest] of Object.entries(before.sources)) if(!path.endsWith('/solver.rs')) assert.equal(after.sources[path],digest,path);
const summary=[];
const mean=values=>values.reduce((a,b)=>a+b,0)/values.length;
for(const fixture of new Set(runs.map(run=>run.fixture))) {
  const rows=runs.filter(run=>run.fixture===fixture),reference=rows[0].sample;
  for(const {sample} of rows) {
    assert.equal(sample.status,'exact');assert.equal(sample.score,reference.score);
    assert.deepEqual(sample.bestBuild,reference.bestBuild);
    assert.equal(sample.compiledHash,reference.compiledHash);assert.equal(sample.preparedHash,reference.preparedHash);
  }
  const metrics={};
  for(const variant of ['before','after']) {
    const selected=rows.filter(row=>row.variant===variant);assert.equal(selected.length,10);
    const total=selected.map(row=>row.sample.profile.totalMs).sort((a,b)=>a-b);
    metrics[variant]={visitedNodes:mean(selected.map(row=>row.sample.visitedNodes)),evaluations:mean(selected.map(row=>row.sample.evaluations)),
      totalMs:mean(total),p95TotalMs:total.at(-1),nativeMs:mean(selected.map(row=>row.sample.profile.nativeMs)),
      nativePeakMiB:mean(selected.map(row=>row.nativePeakWorkingSetBytes))/1048576};
  }
  summary.push({fixture,score:reference.score,...metrics,reductionPercent:Object.fromEntries(['visitedNodes','evaluations','totalMs','nativeMs'].map(key=>[key,100*(1-metrics.after[key]/metrics.before[key])])),nativePeakDeltaMiB:metrics.after.nativePeakMiB-metrics.before.nativePeakMiB});
}
const traces={};
for(const variant of ['allowed','banned']) {
  const trace=await read(resolve(dir,`trace-${variant}.json`));
  assert.ok(Object.values(trace.checks).every(Boolean));
  for(const [file,digest] of Object.entries(trace.rustSourceHashes)) assert.equal(digest,after.sources['src-tauri/src/optimization/'+file]);
  traces[variant]={inputHash:trace.inputHash,initial:trace.batches[0],final:trace.batches.at(-1),counts:trace.counts,peakReady:trace.peakReady,checks:trace.checks};
}
const paths={'current-allowed':'src-tauri/target/kanayogan-analysis/current-allowed.json','current-banned':'src-tauri/target/kanayogan-analysis/current-banned.json',
  'saved-revenir':'tools/fixtures/crysta-saved-sword-shield-revenir-etowal.json','saved-normal':'src-tauri/target/general-upper-bound/saved-normal.json',
  'saved-unlocked':'tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json','old-revenir':'tools/fixtures/crysta-native-runtime-26min-revenir.json','old-locked':'src-tauri/target/constrained-upper-bound/revenir-locked.json'};
const inputs=Object.fromEntries(await Promise.all(Object.entries(paths).map(async ([name,path])=>[name,{path,sha256:hash(await readFile(resolve(root,path))),input:await read(resolve(root,path))}])));
const report={date:'2026-10-11',schema:'toram.crysta-infeasible-seed-repair-measurements.v1',environment:{cpu:cpus()[0].model,node:process.version,platform:process.platform,logicalThreads:16},
  method:'Seven unchanged inputs, 10 fresh processes per variant; sequential alternating order; no concurrent tests or builds. UI excluded, Native peak sampled every 25ms.',
  versions:{before:'Native v19',after:'Native v20',jsClient:'v20 for both variants'},stamps:{before,after},
  jsSourceHashes:Object.fromEntries(await Promise.all(jsSources.map(async path=>[path,hash(await readFile(resolve(root,'assets/js',path)))]))),inputs,summary,runs,traces};
await writeFile(resolve(root,'docs/verification/crysta-infeasible-seed-repair-measurements.json'),JSON.stringify(report,null,2)+'\n');
console.log(JSON.stringify(summary,null,2));
