// Summarize fresh profile runs without replacing the pre-policy measurements.
import assert from 'node:assert/strict';
import {readFile, writeFile} from 'node:fs/promises';
import {createHash} from 'node:crypto';
import {resolve} from 'node:path';
const root=resolve(import.meta.dirname,'..');
const experiment=process.env.D4_SUMMARY_EXPERIMENT||'post-utility';
assert.match(experiment,/^[a-z0-9-]+$/);
const data=JSON.parse(await readFile(resolve(root,`src-tauri/target/slow-profile/${experiment}-complete.json`),'utf8'));
const hashes={};
for(const [file,expected] of Object.entries(data.sourceHashes)) {
  const source=(await readFile(resolve(root,'src-tauri/src',file),'utf8')).replaceAll('\r\n','\n');
  assert.equal(createHash('sha256').update(source).digest('hex'),expected,'stale source: '+file);
}
const runs=[],certificateIssues=[];
for(const run of data.runs) {
  const {result,measurement}=run;
  assert.equal(result.status,'exact');
  assert.equal(result.upperBound,result.score);
  const prior=runs.find(r=>r.fixture===run.fixture);
  if(prior) {
    assert.equal(result.score,prior.result.score);
    assert.equal(result.bestBuild.id,prior.result.bestBuild.id);
  }
  for(const snapshot of result.trace) {
    assert.ok(snapshot.result.score===null||snapshot.result.score<=result.score);
    if(snapshot.result.upperBound<result.score) certificateIssues.push({fixture:run.fixture,variant:run.variant,
      repeat:run.repeat,ms:snapshot.ms,score:snapshot.result.score,upperBound:snapshot.result.upperBound,exactScore:result.score});
    // Report raw certificate defects, never silently replace the recorded bound.
    assert.ok(Math.max(snapshot.result.score??-Infinity,snapshot.result.upperBound)>=result.score);
  }
  const {samples,...metrics}=measurement;
  const cpuMs=Math.max(measurement.cpuMs,...samples.map(s=>s.cpuMs));
  const {profile,trace,...summary}=result;
  const categories=profile?.categories.map((name,i)=>{
    const t=profile.threads.reduce((a,t)=>({calls:a.calls+t[1][i].calls,samples:a.samples+t[1][i].samples,nanos:a.nanos+t[1][i].nanos}),{calls:0,samples:0,nanos:0});
    return {name,...t,estimatedMs:t.samples?t.nanos/1e6*t.calls/t.samples:0};
  });
  hashes[run.fixture]=createHash('sha256').update(await readFile(resolve(root,'src-tauri/target/regression-audit',run.fixture+'.json'))).digest('hex');
  runs.push({...run,measurement:{...metrics,cpuMs,averageCpuCores:cpuMs/metrics.wallMs},result:summary,
    trace:trace.map(t=>({ms:t.ms,ready:t.ready,score:t.result.score,upperBound:t.result.upperBound})),
    profile:profile?{sampleEvery:profile.sampleEvery,categories}:undefined});
  const category=n=>categories?.find(c=>c.name===n);
  const rejected=category('leafRejected')?.calls,accepted=category('leafAccepted')?.calls;
  console.log(JSON.stringify({fixture:run.fixture,repeat:run.repeat,variant:run.variant,seconds:result.sessionWallMs/1000,
    evaluations:result.evaluations,peakReady:result.peakReadyWork,
    popMs:category('frontierPop')?.estimatedMs,mergeMs:category('frontierMerge')?.estimatedMs,
    poolMs:category('poolRun')?.estimatedMs,evaluatorMs:category('evaluator')?.estimatedMs,
    boxStatsMs:category('boxStats')?.estimatedMs,workerMs:category('workerJob')?.estimatedMs,
    utilityMs:category('utilityStage')?.estimatedMs,damageMs:category('damageStage')?.estimatedMs,damageCalls:category('damageStage')?.calls,
    rejected,accepted,rejectPercent:rejected===undefined?undefined:100*rejected/(rejected+accepted),
    cpuCores:cpuMs/metrics.wallMs}));
}
assert.equal(runs.length,12);
await writeFile(resolve(root,`docs/verification/d4-${experiment}-profile-measurements.json`),JSON.stringify({date:data.date,
  budgetMs:data.budgetMs,sourceHashes:data.sourceHashes,inputHashes:hashes,certificateIssues,
  notes:'Two sequential fresh-process control/profile repeats per input, current utility policy. Inclusive worker timings are not additive with evaluator/boxStats or wall time. Prepared inputs; excludes JS candidate preparation and app UI.',runs},null,2)+'\n');
