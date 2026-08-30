import assert from 'node:assert/strict';
import { spawnSync } from 'node:child_process';
import { writeFileSync } from 'node:fs';
import os from 'node:os';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const fixture = resolve(root, 'tools/test-d4-full-stage3.mjs');

function positiveInteger(name, fallback) {
  const value = Number(process.env[name]);
  return Number.isInteger(value) && value > 0 ? value : fallback;
}

function percentile(values, ratio) {
  const ordered = [...values].sort((left, right) => left - right);
  return ordered[Math.min(ordered.length - 1, Math.ceil(ordered.length * ratio) - 1)];
}

function parseRun(output) {
  const metricsLine = output.split(/\r?\n/).find(line => line.startsWith('D4 full metrics: '));
  const summaryLine = output.split(/\r?\n/).find(line => line.startsWith('D4 full stage 3: PASS '));
  assert.ok(metricsLine && summaryLine, 'S7 child must emit fixture metrics and PASS summary');
  const summary = summaryLine.match(/^D4 full stage 3: PASS \((exact|bounded), gap ([\-\d.]+%|-), (\d+) evals, compile ([\d.]+)ms, solve (\d+)ms, progress (\d+)\)$/);
  assert.ok(summary, 'unreadable S7 fixture summary: ' + summaryLine);
  const metrics = JSON.parse(metricsLine.slice('D4 full metrics: '.length));
  const dynamicPhase = (metrics.seedTelemetry?.phases || []).find(phase => phase.name === 'dynamicSeedIncumbent');
  return {
    status:summary[1], gapPercent:summary[2] === '-' ? null : Number(summary[2].slice(0, -1)), evaluations:Number(summary[3]),
    compileMs:Number(summary[4]), solveMs:Number(summary[5]), progressSnapshots:Number(summary[6]),
    lowerBound:metrics.lowerBound, upperBound:metrics.upperBound, visitedNodes:metrics.visitedNodes,
    dynamicSeed:dynamicPhase?.dynamicSeed || null, proofReduction:metrics.proofReduction || null
  };
}

const runCount = positiveInteger('D4_S7_RUNS', 10);
const timeLimitMs = positiveInteger('D4_S7_TIME_LIMIT_MS', 10000);
const variants = [
  { id:'off', label:'OFF', env:{} },
  { id:'seedOnly', label:'seed-only', env:{ D4_ENABLE_DYNAMIC_SEED:'1', D4_ENABLE_DYNAMIC_ORDER:'0' } },
  { id:'seedOrdering', label:'seed+ordering', env:{ D4_ENABLE_DYNAMIC_SEED:'1', D4_ENABLE_DYNAMIC_ORDER:'1' } },
  { id:'seedOrderingProofAudit', label:'seed+ordering+proof-audit', env:{ D4_ENABLE_DYNAMIC_SEED:'1', D4_ENABLE_DYNAMIC_ORDER:'1', D4_ENABLE_PROVEN_DROP_AUDIT:'1' } }
];

const reports = variants.map(variant => {
  const runs = [];
  for (let index = 0; index < runCount; index += 1) {
    const started = performance.now();
    const child = spawnSync(process.execPath, [fixture], {
      cwd:root, encoding:'utf8',
      env:{ ...process.env, ...variant.env, D4_TIME_LIMIT_MS:String(timeLimitMs), D4_DYNAMIC_SEED_TIME_MS:String(Number(process.env.D4_S7_DYNAMIC_SEED_TIME_MS) || 1500) }
    });
    const outerMs = performance.now() - started;
    assert.equal(child.error, undefined, variant.id + ' child failed to start');
    assert.equal(child.status, 0, variant.id + ' child failed:\n' + (child.stderr || child.stdout));
    const parsed = parseRun(child.stdout);
    runs.push({ index:index + 1, outerMs:Number(outerMs.toFixed(1)), coreMs:Number((parsed.compileMs + parsed.solveMs).toFixed(1)), ...parsed });
  }
  const core = runs.map(run => run.coreMs), outer = runs.map(run => run.outerMs), gaps = runs.map(run => run.gapPercent).filter(Number.isFinite), exactRuns = runs.filter(run => run.status === 'exact').length;
  return {
    id:variant.id, label:variant.label, exactRuns, boundedRuns:runCount - exactRuns,
    summary:{ coreMs:{ min:Math.min(...core), p50:percentile(core,.5), p95:percentile(core,.95), max:Math.max(...core) }, outerMs:{ min:Math.min(...outer), p50:percentile(outer,.5), p95:percentile(outer,.95), max:Math.max(...outer) }, gapPercent:gaps.length?{ min:Math.min(...gaps), p50:percentile(gaps,.5), p95:percentile(gaps,.95), max:Math.max(...gaps) }:null },
    proofReduction:runs[0]?.proofReduction || null,
    runs
  };
});

const baseline = reports.find(report => report.id === 'off');
const candidates = reports.filter(report => report.id !== 'off').map(report => ({
  id:report.id,
  exactRatioImproved:report.exactRuns > baseline.exactRuns,
  p95CoreImproved:report.summary.coreMs.p95 < baseline.summary.coreMs.p95,
  gapNotWorse:!report.summary.gapPercent || !baseline.summary.gapPercent || report.summary.gapPercent.p95 <= baseline.summary.gapPercent.p95,
  eligible:((report.exactRuns > baseline.exactRuns) || (report.summary.coreMs.p95 < baseline.summary.coreMs.p95)) && (!report.summary.gapPercent || !baseline.summary.gapPercent || report.summary.gapPercent.p95 <= baseline.summary.gapPercent.p95)
}));
const promoted = candidates.filter(candidate => candidate.eligible).map(candidate => candidate.id);
const report = {
  schema:'d4-s7-approval-benchmark.v1',
  fixture:{ id:'full-425-physical-short', source:'tools/test-d4-full-stage3.mjs', scope:'actual 425 crystas; physical short range; fixed scenario' },
  execution:{ runCount, timeLimitMs, freshNodeProcessPerRun:true, measuredCore:'fixture compile/preparation + optimizer solve', measuredOuter:'fresh child process wall time including Node startup' },
  environment:{ node:process.version, platform:process.platform, arch:process.arch, cpu:os.cpus()[0]?.model || 'unknown', logicalCpuCount:os.cpus().length },
  reports,
  decision:{ promoted, defaultWorkerMode:promoted.length ? 'requires explicit follow-up integration decision' : 'off', reason:promoted.length ? 'one or more variants met the S7 measured eligibility condition; enabling it still requires an explicit integration decision.' : 'no variant simultaneously improved exact ratio or P95 core time without worsening P95 certified gap.' }
};

if (process.env.D4_S7_REPORT_PATH) writeFileSync(process.env.D4_S7_REPORT_PATH, JSON.stringify(report, null, 2), 'utf8');
console.log('D4 S7 approval benchmark: ' + JSON.stringify(report));
