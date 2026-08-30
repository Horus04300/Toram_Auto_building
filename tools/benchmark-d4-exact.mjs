import assert from 'node:assert/strict';
import { spawnSync } from 'node:child_process';
import os from 'node:os';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const fixture = resolve(root, 'tools/test-d4-full-stage3.mjs');

function envPositiveInteger(name, fallback) {
  const value = Number(process.env[name]);
  return Number.isInteger(value) && value > 0 ? value : fallback;
}

function percentile(values, ratio) {
  const ordered = [...values].sort((left, right) => left - right);
  return ordered[Math.min(ordered.length - 1, Math.ceil(ordered.length * ratio) - 1)];
}

function parseOutput(output) {
  const metricsLine = output.split(/\r?\n/).find(line => line.startsWith('D4 full metrics: '));
  const summaryLine = output.split(/\r?\n/).find(line => line.startsWith('D4 full stage 3: PASS '));
  assert.ok(metricsLine && summaryLine, 'full fixture must emit metrics and PASS lines');
  const match = summaryLine.match(/^D4 full stage 3: PASS \((exact|bounded), gap ([\-\d.]+%|-), (\d+) evals, compile ([\d.]+)ms, solve (\d+)ms, progress (\d+)\)$/);
  assert.ok(match, 'unreadable full fixture summary: ' + summaryLine);
  const metrics = JSON.parse(metricsLine.slice('D4 full metrics: '.length));
  const telemetry = metrics.seedTelemetry;
  assert.equal(telemetry && telemetry.schema, 'd4-initial-seed-telemetry.v1', 'full fixture must emit S0 telemetry');
  const phaseByName = new Map((telemetry.phases || []).map(phase => [phase.name, phase]));
  return {
    status: match[1],
    gapPercent: match[2] === '-' ? null : Number(match[2].slice(0, -1)),
    evaluations: Number(match[3]),
    compileMs: Number(match[4]),
    solveMs: Number(match[5]),
    progressSnapshots: Number(match[6]),
    lowerBound: metrics.lowerBound,
    upperBound: metrics.upperBound,
    visitedNodes: metrics.visitedNodes,
    remainingNodes: metrics.remainingNodes,
    seedTelemetry:{
      rawInitial:phaseByName.get('rawInitialComplete') || null,
      heuristicComplete:phaseByName.get('heuristicComplete') || null,
      rootBound:phaseByName.get('rootBound') || null,
      checkpoints:telemetry.checkpoints || []
    }
  };
}

const runCount = envPositiveInteger('D4_BENCH_RUNS', 10);
const timeLimitMs = envPositiveInteger('D4_BENCH_TIME_LIMIT_MS', 10000);
const requireExact = process.env.D4_BENCH_REQUIRE_EXACT === '1';
const maxP95Ms = Number(process.env.D4_BENCH_MAX_P95_MS);
const runs = [];

for (let index = 0; index < runCount; index += 1) {
  const started = performance.now();
  const child = spawnSync(process.execPath, [fixture], {
    cwd: root,
    encoding: 'utf8',
    env: { ...process.env, D4_TIME_LIMIT_MS:String(timeLimitMs) }
  });
  const outerMs = performance.now() - started;
  assert.equal(child.error, undefined, 'benchmark child failed to start');
  assert.equal(child.status, 0, 'benchmark child failed:\n' + (child.stderr || child.stdout));
  const result = parseOutput(child.stdout);
  runs.push({ index:index + 1, outerMs:Number(outerMs.toFixed(1)), coreMs:Number((result.compileMs + result.solveMs).toFixed(1)), ...result });
}

const coreTimes = runs.map(run => run.coreMs);
const outerTimes = runs.map(run => run.outerMs);
const exactRuns = runs.filter(run => run.status === 'exact').length;
const report = {
  schema:'d4-exact-baseline-benchmark.v2',
  fixture:{
    id:'full-425-physical-short-baseline',
    source:'tools/test-d4-full-stage3.mjs',
    scope:'actual 425 crystas; physical short range; no unsheathe; utility already satisfied'
  },
  execution:{
    runCount,
    timeLimitMs,
    freshNodeProcessPerRun:true,
    measuredCore:'fixture compileMs + optimizer solveMs',
    measuredOuter:'fresh child process wall time including Node startup'
  },
  environment:{
    node:process.version,
    platform:process.platform,
    arch:process.arch,
    cpu:os.cpus()[0]?.model || 'unknown',
    logicalCpuCount:os.cpus().length
  },
  summary:{
    exactRuns,
    boundedRuns:runCount - exactRuns,
    coreMs:{ min:Math.min(...coreTimes), p50:percentile(coreTimes, .5), p95:percentile(coreTimes, .95), max:Math.max(...coreTimes) },
    outerMs:{ min:Math.min(...outerTimes), p50:percentile(outerTimes, .5), p95:percentile(outerTimes, .95), max:Math.max(...outerTimes) }
  },
  runs
};

if (requireExact) assert.equal(exactRuns, runCount, 'D4_BENCH_REQUIRE_EXACT=1 requires exact in every cold run');
if (Number.isFinite(maxP95Ms)) assert.ok(report.summary.coreMs.p95 <= maxP95Ms, 'core P95 exceeds the configured limit');
console.log('D4 exact baseline benchmark: ' + JSON.stringify(report));
