// UI-independent baseline: raw resolved input -> compile -> product Native client/service -> JS result.
import assert from 'node:assert/strict';
import { readFile, writeFile, mkdir } from 'node:fs/promises';
import { spawn } from 'node:child_process';
import { createHash } from 'node:crypto';
import { cpus } from 'node:os';
import { resolve, dirname } from 'node:path';
import { parseArgs } from 'node:util';
import { root, jsSources, loadHeadlessEnvironment } from '../support/crysta-headless-environment.mjs';
import { createHeadlessTransport } from '../support/crysta-headless-transport.mjs';
import { measureComputation } from '../support/crysta-computation-measurement.mjs';

const { values, positionals } = parseArgs({ allowPositionals:true, options:{
  input:{ type:'string', default:'tools/fixtures/crysta-native-runtime-26min-revenir.json' },
  repeats:{ type:'string', default:'3' }, output:{ type:'string', default:'desktop/target/computation-benchmark/latest.json' },
  'max-ms':{ type:'string', default:'120000' }, 'slice-ms':{ type:'string', default:'30000' }
} });
const mode = positionals[0] || 'run';
assert.ok(['build','run','child'].includes(mode), 'Use build or run');
const repeats = Number(values.repeats), maxDurationMs = Number(values['max-ms']), sliceMs = Number(values['slice-ms']);
assert.ok(Number.isInteger(repeats) && repeats > 0 && repeats <= 100);
assert.ok(Number.isFinite(maxDurationMs) && maxDurationMs > 0 && maxDurationMs <= 3600000);
assert.ok(Number.isInteger(sliceMs) && sliceMs > 0 && sliceMs <= 30000);
const binary = resolve(root, 'desktop/target/release/crysta_headless_service' + (process.platform === 'win32' ? '.exe' : ''));
const buildStamp = binary + '.measurement.json';
const rustSources = ['desktop/Cargo.toml','desktop/Cargo.lock','desktop/build.rs',
  'engine/Cargo.toml','engine/Cargo.lock','engine/src/lib.rs',
  ...['evaluator.rs','solver.rs','stats.rs','joint_supply.rs'].map(f => 'engine/src/' + f),
  ...['optimization/parallel_runtime.rs','optimization/service.rs','bin/crysta_headless_service.rs'].map(f => 'desktop/src/' + f)];
const hash = text => createHash('sha256').update(text).digest('hex');
async function sourceHashes(paths) {
  return Object.fromEntries(await Promise.all(paths.map(async file => [file, hash((await readFile(resolve(root, file), 'utf8')).replaceAll('\r\n','\n'))])));
}
function run(command, args, timeout) {
  return new Promise((yes, no) => {
    const child = spawn(command, args, { cwd:root, windowsHide:true, stdio:['ignore','pipe','pipe'] });
    let out = '', err = '';
    const timer = setTimeout(() => {
      // Kill the owned process tree so a watchdog never leaves a native search behind.
      if (process.platform === 'win32') spawn('taskkill', ['/pid', String(child.pid), '/t', '/f'], { windowsHide:true, stdio:'ignore' });
      else child.kill();
      no(new Error(`Measurement watchdog expired: ${err}`));
    }, timeout);
    child.stdout.on('data', data => { out += data; });
    child.stderr.on('data', data => { err = (err + data).slice(-32000); });
    child.on('error', error => { clearTimeout(timer); no(error); });
    child.on('close', code => { clearTimeout(timer); code === 0 ? yes(out) : no(new Error(`${command} exited ${code}: ${err || out}`)); });
  });
}

if (mode === 'build') {
  const sources = await sourceHashes(rustSources);
  await run('cargo', ['build','--offline','--release','--manifest-path','desktop/Cargo.toml','--bin','crysta_headless_service'], 600000);
  assert.deepEqual(await sourceHashes(rustSources), sources, 'Sources changed during the build');
  await writeFile(buildStamp, JSON.stringify({ sources, binaryHash:hash(await readFile(binary)) }, null, 2) + '\n');
  console.log(`Built ${binary}`);
} else if (mode === 'child') {
  const fixture = JSON.parse(await readFile(resolve(root, values.input), 'utf8'));
  const input = fixture.resolvedExecutionContext || fixture;
  assert.ok(input.baseContext, 'Input must contain raw baseContext, not prepared groups');
  assert.equal(input.groups, undefined, 'Precompiled inputs would omit JS preparation');
  const transport = createHeadlessTransport(binary);
  try {
    const env = await loadHeadlessEnvironment(transport.core);
    const { result, timing } = await measureComputation({
      compile:() => env.compile(input), client:env.client, maxDurationMs, sliceMs
    });
    // Correctness/report work is outside the fixed result-generation boundary.
    assert.equal(timing.cached, false, 'Each sample must be a fresh client/process');
    if (result.bestBuild) {
      assert.equal(result.outcomes?.constraints?.feasible, true, 'Returned recommendation fails JS constraints');
      assert.equal(result.outcomes.damage.expected, result.score, 'Native score differs from final JS evaluation');
      const stats = {};
      for (const selected of result.bestBuild.packages) for (const [key, value] of Object.entries(selected.statDelta)) stats[key] = (stats[key] || 0) + value;
      assert.deepEqual(result.bestBuild.statDelta, stats, 'Returned raw options differ from the restored packages');
    }
    if (result.exact) assert.equal(result.upperBound, result.lowerBound);
    console.log(JSON.stringify({ timing, ...transport.metadata, status:result.status, exact:result.exact,
      score:result.score, upperBound:result.upperBound, bestBuild:result.bestBuild,
      nativeElapsedMs:result.elapsedMs, versions:env.client.cachePolicy,
      validForComparison:result.status === 'exact' && result.exact === true }));
  } catch (error) {
    console.log(JSON.stringify({ status:'error', validForComparison:false, error:error.message, timing:error.measurement || null }));
  } finally { await transport.close(); }
} else {
  const stamp = JSON.parse(await readFile(buildStamp, 'utf8').catch(() => { throw new Error('Run npm run bench:optimization:build first'); }));
  const currentSources = await sourceHashes(rustSources);
  assert.deepEqual(currentSources, stamp.sources, 'Rust changed: rebuild the measurement service');
  assert.equal(hash(await readFile(binary)), stamp.binaryHash, 'Binary changed: rebuild the measurement stamp');
  const inputPath = resolve(root, values.input), outputPath = resolve(root, values.output);
  assert.notEqual(inputPath, outputPath, 'Do not overwrite the input fixture');
  const measuredJsPaths = [...jsSources.map(f => 'web/src/' + f),
    'tools/support/crysta-catalog-source.mjs','web/public/game-data/items/manifest.json',
    'tools/support/crysta-headless-environment.mjs','tools/support/crysta-headless-transport.mjs','tools/support/crysta-computation-measurement.mjs','tools/benchmarks/benchmark-crysta-computation.mjs'];
  const jsHashes = await sourceHashes(measuredJsPaths), inputHash = hash(await readFile(inputPath));
  const report = { schema:'toram.crysta-computation-benchmark.v1', date:new Date().toISOString(),
    boundary:'raw-resolved-input-to-final-js-result', transport:'stdio-json-lines', cache:'fresh-process-per-sample',
    input:values.input, inputHash, binaryHash:stamp.binaryHash, rustSourceHashes:currentSources, jsSourceHashes:jsHashes,
    environment:{ node:process.version, platform:process.platform, arch:process.arch, cpu:cpus()[0]?.model },
    options:{ repeats, maxDurationMs, sliceMs }, runs:[] };
  await mkdir(dirname(outputPath), { recursive:true });
  for (let repeat = 1; repeat <= repeats; repeat++) {
    const sample = JSON.parse(await run(process.execPath, [import.meta.filename, 'child', '--input', inputPath,
      '--max-ms', String(maxDurationMs), '--slice-ms', String(sliceMs)], maxDurationMs + sliceMs + 60000));
    assert.deepEqual(await sourceHashes(measuredJsPaths), jsHashes, 'JS changed during measurement');
    assert.equal(hash(await readFile(inputPath)), inputHash, 'Input changed during measurement');
    const prior = report.runs.find(r => r.validForComparison);
    if (prior && sample.validForComparison) {
      assert.equal(sample.score, prior.score);
      assert.deepEqual(sample.bestBuild, prior.bestBuild, 'Exact selected build changed across repetitions');
    }
    report.runs.push({ repeat, ...sample });
    const times = report.runs.filter(r => r.validForComparison).map(r => r.timing.totalMs).sort((a,b) => a-b);
    report.summary = times.length ? { completedExact:times.length,
      meanMs:times.reduce((a,b) => a+b, 0)/times.length,
      medianMs:(times[Math.floor((times.length-1)/2)]+times[Math.floor(times.length/2)])/2,
      minMs:times[0], maxMs:times.at(-1) } : null;
    await writeFile(outputPath, JSON.stringify(report, null, 2) + '\n');
    console.log(`${repeat}/${repeats}: ${sample.status}, total=${sample.timing?.totalMs?.toFixed(2) ?? '-'}ms`);
    if (!sample.validForComparison) { process.exitCode = 1; break; }
  }
  assert.deepEqual(await sourceHashes(rustSources), currentSources, 'Rust changed during measurement');
  console.log(JSON.stringify(report.summary));
  console.log(`Report: ${outputPath}`);
}
