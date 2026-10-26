import assert from 'node:assert/strict';
import { createServer } from 'node:http';
import { readFile, writeFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { extname, resolve, sep } from 'node:path';
import { loadHeadlessEnvironment } from '../support/crysta-headless-environment.mjs';
import { exhaustiveSearch } from '../support/crysta-exhaustive-oracle.mjs';

const require = createRequire(import.meta.url);
if (!process.env.CODEX_PLAYWRIGHT_PATH) throw new Error('Set CODEX_PLAYWRIGHT_PATH to the installed playwright module.');
const { chromium } = require(process.env.CODEX_PLAYWRIGHT_PATH);
const root = resolve(import.meta.dirname, '../../build/web');
const mime = { '.html':'text/html', '.js':'text/javascript', '.mjs':'text/javascript', '.css':'text/css', '.svg':'image/svg+xml', '.woff2':'font/woff2', '.png':'image/png', '.wasm':'application/wasm' };
let hardware = 1;
const server = createServer(async (req, res) => {
  try {
    const url = new URL(req.url, 'http://localhost');
    if (url.pathname.startsWith('/parallel/')) {
      res.setHeader('Cross-Origin-Opener-Policy', 'same-origin');
      res.setHeader('Cross-Origin-Embedder-Policy', 'require-corp');
    }
    const path = resolve(root, url.pathname.replace(/^\/(parallel|single)\//u, '') || 'index.html');
    if (!path.startsWith(root + sep)) throw new Error('path');
    let content = await readFile(path);
    if (path.endsWith(`optimization${sep}wasm-worker.js`)) content = `Object.defineProperty(navigator, 'hardwareConcurrency', { value:${hardware} });\n` + content;
    res.setHeader('Content-Type', mime[extname(path)] || 'application/octet-stream');
    res.end(content);
  } catch { res.writeHead(404); res.end(); }
});
const env = await loadHeadlessEnvironment();
const fixture = JSON.parse(await readFile(new URL('../fixtures/crysta-native-runtime-26min-revenir.json', import.meta.url), 'utf8'));
const problem = env.compile(fixture.resolvedExecutionContext);
const measurements = [];
const bridge = env.context.ToramCrystaOptimizationRustBridge;
const cases = Array.from({ length:12 }, (_, i) => {
  const baseContext = { ...fixture.resolvedExecutionContext.baseContext,
    mainType:['한손검','활','지팡이','이도류'][i % 4], atkType:i % 3 ? 'PHYS' : 'MAG' };
  const input = { schema:'toram.crysta-problem.v1', baseContext,
    scenarioSnapshot:env.evaluator.createScenarioSnapshot(baseContext, {
      requirements:{ maxHp:i % 4 === 0 ? 1e9 : null, maxMp:i % 4 === 1 ? 2300 : null,
        amprBeforeDual:null, normalAttackCrit:null, aspd:null }
    }), groups:['weapon','armor','additional','special'].map((id, group) => ({ id,
      packages:[0,1,2].map(j => ({ id:id + '-' + j, statDelta:i === 11 ? {} : {
        ATKP:(i + group + (i % 2 ? Math.min(j, 1) : j)) % 11, MATKP:j * 3, MAXMP:j * 100,
        MAXHP:j % 2 ? -100 : 200, CRIT:j * 5, CDMG:j * 2, ASPD:j * 40,
        ATK_UP_VIT:group === 3 ? j * 25 : 0, MATK_UP_AGI:group === 3 ? j * 200 : 0
      }, candidateNames:[], evaluatorCandidates:[] })) })) };
  const oracle = exhaustiveSearch(input, { prepared:true, evaluateStats:bridge.evaluate(input) });
  return { raw:JSON.stringify(bridge.projectProblem(bridge.prepare(input, {}).problem)),
    expected:{ status:oracle.status, score:oracle.score, id:oracle.bestBuild?.id ?? null } };
});
let browser;
try {
  await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));
  browser = await chromium.launch({ channel:'chrome', headless:true });
  for (const count of [1, 2, 4, 8, 16]) {
    hardware = count;
    const page = await browser.newPage();
    await page.goto(`http://127.0.0.1:${server.address().port}/parallel/?view=calculator`);
    await page.waitForFunction(() => window.ToramCrystaOptimizationWasmClient);
    for (let repeat = 0; repeat < 3; repeat++) {
      const measured = await page.evaluate(async problem => {
        const client = window.ToramCrystaOptimizationWasmClient;
        await client.disposeContinuation();
        const started = performance.now();
        const preview = await client.preview(problem);
        if (preview.visitedNodes !== 0) throw new Error('Preview searched precision nodes');
        const preciseStarted = performance.now();
        const result = await client.optimize(problem, {}, { timeLimitMs:10000 });
        return { threads:result.threadsUsed, previewMs:preciseStarted - started, preciseMs:performance.now() - preciseStarted,
          elapsedMs:result.elapsedMs, score:result.score, id:result.bestBuild?.id, status:result.status,
          upper:result.upperBound, gap:result.optimalityGap, visited:result.visitedNodes };
      }, problem);
      assert.equal(measured.status, 'exact');
      assert.equal(measured.threads, count);
      assert.equal(measured.upper, measured.score);
      assert.equal(measured.gap, 0);
      if (measurements.length) {
        assert.equal(measured.score, measurements[0].score);
        assert.equal(measured.id, measurements[0].id);
      }
      measurements.push(measured);
      console.log('WASM threads: ' + JSON.stringify(measured));
    }
    const closed = Promise.all(page.workers().map(worker => new Promise(resolve => worker.once('close', resolve))));
    await page.evaluate(() => window.ToramCrystaOptimizationWasmClient.disposeContinuation());
    await Promise.race([closed, new Promise((_, reject) => setTimeout(() => reject(new Error('Orphaned WASM pool after dispose')), 3000))]);
    assert.equal(page.workers().length, 0);
    await page.close();
  }
  hardware = 4;
  const page = await browser.newPage();
  await page.goto(`http://127.0.0.1:${server.address().port}/parallel/?view=calculator`);
  await page.waitForFunction(() => window.ToramCrystaOptimizationWasmClient);
  const controls = await page.evaluate(async problem => {
    const client = window.ToramCrystaOptimizationWasmClient;
    await client.preview(problem);
    const bounded = await client.optimize(problem, {}, { timeLimitMs:1 });
    await new Promise(resolve => setTimeout(resolve, 200));
    const pending = client.resume({}, { timeLimitMs:10000 });
    client.pause();
    const paused = await pending;
    const exact = await client.resume({}, { timeLimitMs:10000 });
    await client.disposeContinuation();
    await client.preview(problem);
    const cancelled = client.optimize(problem, { onProgress(progress) {
      if (progress.threadsUsed > 1 && progress.visitedNodes > 0) client.cancel();
    } }, { timeLimitMs:10000 });
    const cancelledResult = await cancelled;
    return { bounded, paused, exact, cancelledResult };
  }, problem);
  assert.equal(controls.bounded.status, 'bounded');
  assert.ok(controls.bounded.upperBound >= controls.exact.score);
  assert.equal(controls.paused.status, 'paused');
  assert.equal(controls.exact.status, 'exact');
  assert.equal(controls.exact.bestBuild.id, measurements[0].id);
  assert.equal(controls.cancelledResult.status, 'cancelled');
  assert.equal(controls.cancelledResult.exact, false);
  assert.equal(controls.cancelledResult.upperBound, null);
  // A single pool exercises every supported job count without 64 separate pool startups.
  const memory = await page.evaluate(async cases => {
    const moduleURL = new URL('assets/wasm/parallel/crysta.js', location.href).href;
    const script = `onmessage = async ({data:cases}) => {
      try {
        const wasm = await import(${JSON.stringify(moduleURL)});
        const exports = await wasm.default();
        const initialBytes = exports.memory.buffer.byteLength;
        await wasm.initThreadPool(64);
        for (let threads = 1; threads <= 64; threads++) for (const row of cases) {
          const session = new wasm.SearchSession(row.raw);
          try {
            if (JSON.parse(session.snapshot()).visitedNodes !== 0) throw new Error('Preview explored nodes');
            let steps = 0;
            while (!session.is_complete()) {
              session.step_parallel(256, threads);
              if (++steps > 10000) throw new Error('Oracle did not terminate');
            }
            const result = JSON.parse(session.snapshot());
            if (result.status !== row.expected.status || result.score !== row.expected.score ||
              (result.bestBuild?.id ?? null) !== row.expected.id) throw new Error('Oracle mismatch at threads=' + threads);
            if (result.exact && result.upperBound !== result.score) throw new Error('Exact upper mismatch');
          } finally { session.free(); }
        }
        postMessage({ initialBytes, finalBytes:exports.memory.buffer.byteLength,
          shared:exports.memory.buffer instanceof SharedArrayBuffer, comparisons:cases.length * 64 });
      } catch (error) { postMessage({ error:String(error.stack || error) }); }
    };`;
    const url = URL.createObjectURL(new Blob([script], { type:'text/javascript' }));
    const worker = new Worker(url);
    try {
      return await new Promise((resolve, reject) => {
        worker.onmessage = ({data}) => data.error ? reject(new Error(data.error)) : resolve(data);
        worker.onerror = event => reject(new Error(event.message));
        worker.postMessage(cases);
      });
    } finally { worker.terminate(); URL.revokeObjectURL(url); }
  }, cases);
  assert.equal(memory.shared, true);
  assert.equal(memory.comparisons, 768);
  await page.close();
  const fallback = await browser.newPage();
  await fallback.goto(`http://127.0.0.1:${server.address().port}/single/?view=calculator`);
  await fallback.waitForFunction(() => window.ToramCrystaOptimizationWasmClient);
  assert.equal(await fallback.evaluate(() => crossOriginIsolated), false);
  const single = await fallback.evaluate(problem => window.ToramCrystaOptimizationWasmClient.optimize(problem, {}, { timeLimitMs:10000 }), problem);
  assert.equal(single.threadsUsed, 1);
  assert.equal(single.status, 'exact');
  assert.equal(single.bestBuild.id, measurements[0].id);
  await fallback.close();
  console.log('WASM parallel: PASS ' + JSON.stringify({ memory, controls:'deadline/pause/resume/cancel, pool cleanup, non-isolated fallback' }));
  await writeFile(new URL('../../build/tmp/wasm-parallel-measurements.json', import.meta.url), JSON.stringify({ browser:await browser.version(), measurements, memory }, null, 2) + '\n');
} finally {
  await browser?.close();
  if (server.listening) await new Promise(resolve => server.close(resolve));
}
