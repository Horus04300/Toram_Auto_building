import assert from 'node:assert/strict';
import { mkdtemp, readFile, rm, writeFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { availableParallelism, tmpdir } from 'node:os';
import { join, resolve } from 'node:path';
import { spawn } from 'node:child_process';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const fixture = JSON.parse(await readFile(resolve(root, 'tools/fixtures/d4-native-runtime-26min-revenir.json'), 'utf8'));
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const evaluator = require(resolve(root, 'assets/js/build-evaluator.js'));
const compiler = require(resolve(root, 'assets/js/d4-problem-compiler.js'));
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));
const binary = process.env.D4_NATIVE_BINARY || resolve(root, 'src-tauri/target/release/d4_native_parallel.exe');
const configuredCancelAfterMs = Number(process.env.D4_N0_CANCEL_AFTER_MS);
const cancelAfterMs = Number.isFinite(configuredCancelAfterMs) && configuredCancelAfterMs >= 0
  ? Math.floor(configuredCancelAfterMs)
  : 5000;
const threads = Math.max(1, Math.floor(Number(process.env.D4_N0_THREADS) || availableParallelism()));
const lockEtowal = process.env.D4_N0_LOCK_ETOWAL === '1';

function run(command, args) {
  return new Promise((resolvePromise, reject) => {
    const child = spawn(command, args, { cwd:root, stdio:['ignore', 'pipe', 'pipe'] });
    let stdout = '', stderr = '';
    child.stdout.on('data', chunk => { stdout += chunk; });
    child.stderr.on('data', chunk => { stderr += chunk; });
    child.on('error', reject);
    child.on('close', code => code === 0 ? resolvePromise(stdout.trim()) : reject(new Error(`${command} failed (${code}): ${stderr || stdout}`)));
  });
}

const context = { window:{ ToramStatRegistry:registry }, console };
context.window.window = context.window;
vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', context);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'calculator.js' });
const dataContext = {};
vm.createContext(dataContext);
vm.runInContext(`${await readFile(resolve(root, 'assets/js/data/crysta-data.js'), 'utf8')}\nglobalThis.__crystas=crystaDataJson;`, dataContext);
const input = fixture.resolvedExecutionContext;
const scenario = evaluator.createScenarioSnapshot(input.baseContext, { basisName:'루브닐', requirements:input.scenarioRequirements, combo:fixture.rawInput.combo });
const locks = lockEtowal ? [false, false, false, false, false, false, true, false] : input.locks;
const compiled = compiler.compileCrystaProblem({ crystas:dataContext.__crystas, registry, baseContext:input.baseContext, scenarioSnapshot:scenario, currentCrystas:input.currentCrystas, locks, banned:input.banned });
assert.deepEqual(compiled.diagnostics, []);
const adapter = stats => evaluator.evaluateAggregate(input.baseContext, scenario, stats, context.window.ToramCalculationKernel.evaluateContext);
const prepared = optimizer.prepareProblem(compiled, { registry, relevantKeys:optimizer.deriveRelevantKeys(compiled, registry, adapter), pareto:{ maxComparisons:1000000 } });
assert.ok(prepared.metadata.paretoReports.every(report => report.complete));

const temp = await mkdtemp(join(tmpdir(), 'toram-d4-n0-'));
try {
  const inputPath = join(temp, 'input.json'), outputPath = join(temp, 'output.json'), errorPath = join(temp, 'error.txt');
  await writeFile(inputPath, JSON.stringify({ ...prepared, threads, ...(cancelAfterMs > 0 ? { cancelAfterMs } : {}) }));
  const measure = JSON.parse(await run('powershell.exe', ['-NoProfile', '-NonInteractive', '-ExecutionPolicy', 'Bypass', '-File', resolve(root, 'tools/measure-d4-native-p6.ps1'), '-Binary', binary, '-InputPath', inputPath, '-Output', outputPath, '-ErrorOutput', errorPath]));
  const result = JSON.parse(await readFile(outputPath, 'utf8'));
  if (cancelAfterMs > 0) assert.equal(result.status, 'cancelled', 'N0 sampled execution must use explicit cancellation, not claim a UI deadline exists');
  const summary = {
    schema:'toram.d4-native-runtime-n0-measurement.v1', fixture:fixture.id, variant:lockEtowal ? 'locked-etowal' : 'unlocked-etowal', locks, threads, cancelAfterMs:cancelAfterMs || null,
    status:result.status, solverMs:result.elapsedMs, wallMs:measure.wallMs, cpuMs:measure.cpuMs,
    peakWorkingSetBytes:measure.peakWorkingSetBytes, samples:measure.samples || [],
    nativeSchedulerTelemetry:result.scheduler || null,
    nativeProgressAvailable:false, shardThroughputAvailable:false,
    note:'Current bridge/command returns one terminal result. Aggregate scheduler telemetry is available at completion; per-shard throughput and streaming UI progress remain unavailable until N4.'
  };
  if (process.env.D4_N0_REPORT) await writeFile(resolve(root, process.env.D4_N0_REPORT), JSON.stringify(summary, null, 2));
  console.log(JSON.stringify({ ...summary, samples:undefined, sampleCount:summary.samples.length }));
} finally {
  await rm(temp, { recursive:true, force:true });
}
