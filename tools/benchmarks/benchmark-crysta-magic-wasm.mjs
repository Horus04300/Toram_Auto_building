import assert from 'node:assert/strict';
import { readFile, writeFile } from 'node:fs/promises';
import { execFile } from 'node:child_process';
import { promisify } from 'node:util';
import { createRequire } from 'node:module';
import { createHash } from 'node:crypto';
import { cpus } from 'node:os';
import { resolve } from 'node:path';
import { createWebDevServer } from '../web-dev.mjs';

const require = createRequire(import.meta.url);
if (!process.env.CODEX_PLAYWRIGHT_PATH) throw new Error('Set CODEX_PLAYWRIGHT_PATH to the installed playwright module.');
const { chromium } = require(process.env.CODEX_PLAYWRIGHT_PATH);
const root = resolve(import.meta.dirname, '../..');
const hash = bytes => createHash('sha256').update(bytes).digest('hex');
const cases = {};
// Native measurements finish before starting Edge so they do not compete for CPU.
for (const id of ['magic-device', 'magic-staff']) {
  const output = `desktop/target/${id}-native-current.json`;
  const { stdout } = await promisify(execFile)(process.execPath, [
    'tools/benchmarks/benchmark-crysta-user-samples.mjs', '--case', id,
    '--repeats', '3', '--max-ms', '30000', '--output', output
  ], { cwd:root, windowsHide:true });
  console.log(stdout.trim());
  const native = JSON.parse(await readFile(resolve(root, output), 'utf8'));
  assert.ok(native.runs.every(run => run.exact && run.status === 'exact'));
  const input = native.inputs[id];
  assert.equal(hash(await readFile(resolve(root, input.provenance.file))), input.provenance.sha256);
  cases[id] = { input, native, wasm:[] };
}

const server = createWebDevServer();
let browser;
try {
  await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));
  browser = await chromium.launch({ channel:'msedge', headless:true });
  const page = await browser.newPage();
  const errors = [];
  page.on('pageerror', error => errors.push(error.message));
  await page.goto(`http://127.0.0.1:${server.address().port}/`);
  await page.waitForFunction(() => window.ToramUiFeatures?.settings);
  assert.equal(await page.evaluate(() => typeof window.ToramCrystaOptimizationNativeClient), 'undefined');
  for (const [id, entry] of Object.entries(cases)) {
    for (let repeat = 1; repeat <= 3; repeat++) {
      const run = await page.evaluate(async input => {
        const adapter = window.ToramCrystaOptimizationExecutionAdapter;
        await adapter.disposeContinuation();
        const started = performance.now();
        const scenarioSnapshot = window.ToramBuildEvaluator.createScenarioSnapshot(input.baseContext, { requirements:input.scenarioRequirements });
        const problem = window.ToramCrystaOptimizationProblemCompiler.compileCrystaProblem({
          registry:window.ToramStatRegistry, crystas:crystaDataJson, baseContext:input.baseContext, scenarioSnapshot,
          currentCrystas:input.currentCrystas, locks:input.locks, banned:input.banned
        });
        const compileMs = performance.now() - started;
        const preview = await adapter.preview(problem);
        const previewFinished = performance.now();
        const result = await adapter.execute(problem, {}, { timeLimitMs:30000 });
        return { totalMs:performance.now() - started, compileMs, previewMs:previewFinished - started - compileMs,
          preciseMs:performance.now() - previewFinished, initialScore:preview.score, initialId:preview.bestBuild?.id,
          previewVisitedNodes:preview.visitedNodes, engine:result.engine, status:result.status, exact:result.exact,
          score:result.score, gap:result.optimalityGap, best:{ id:result.bestBuild?.id, stats:result.bestBuild?.statDelta },
          feasible:result.outcomes?.constraints.feasible, reevaluated:result.outcomes?.damage.expected };
      }, entry.input.resolvedExecutionContext);
      assert.equal(run.engine, 'rust-wasm');
      assert.equal(run.status, 'exact');
      assert.equal(run.exact, true);
      assert.equal(run.gap, 0);
      assert.equal(run.previewVisitedNodes, 0);
      assert.equal(run.feasible, true);
      assert.equal(run.score, run.reevaluated);
      assert.ok(run.score >= run.initialScore);
      assert.equal(run.score, entry.native.runs[0].score);
      assert.deepEqual(run.best, entry.native.runs[0].best);
      entry.wasm.push({ repeat, ...run });
      console.log(JSON.stringify({ case:id, repeat, ...run }));
    }
  }
  assert.deepEqual(errors, []);
  const report = { date:new Date().toISOString(), browser:await browser.version(), node:process.version,
    cpu:cpus()[0].model, logicalThreads:cpus().length,
    wasmSha256:hash(await readFile(resolve(root, 'build/generated/wasm/crysta_bg.wasm'))),
    method:{ repeats:3, boundary:'raw problem compilation through final JS reevaluation; UI rendering excluded',
      native:'fresh Node/Rust process, product default threads',
      wasm:'fresh Worker per run in one isolated Edge context; includes WASM loading and preview, then reuses the session for precise search',
      scope:'Magic:11 cannon1, charge 200%, smite; original requirements, locks and bans preserved; not full combo damage or P95' }, cases };
  await writeFile(resolve(root, 'desktop/target/rust-wasm-magic-comparison.json'), JSON.stringify(report, null, 2) + '\n');
  console.log('Magic Native/WASM comparison: PASS (2 samples x 3 repeats, exact score/build/raw stats and final JS reevaluation)');
} finally {
  if (browser) await browser.close();
  if (server.listening) await new Promise(resolve => server.close(resolve));
}
