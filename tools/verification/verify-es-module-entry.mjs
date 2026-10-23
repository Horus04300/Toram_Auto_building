import { frontendSourcePath } from '../support/frontend-paths.mjs';
import assert from 'node:assert/strict';
import { access, readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { pathToFileURL } from 'node:url';
import { CLASSIC_SCRIPT_PATHS, WEB_CLASSIC_SCRIPT_PATHS } from '../../web/src/classic-script-manifest.mjs';

const root = resolve(import.meta.dirname, '../..');
const verifyDist = process.argv.includes('--dist');
const verifyWeb = process.argv.includes('--web');
const frontendRoot = verifyWeb ? resolve(root, 'build/web') : verifyDist ? resolve(root, 'build/desktop') : root;
const paths = verifyDist ? CLASSIC_SCRIPT_PATHS : WEB_CLASSIC_SCRIPT_PATHS;
const file = path => resolve(frontendRoot, verifyDist || verifyWeb ? path : frontendSourcePath(path));
const indexPath = resolve(frontendRoot, verifyDist || verifyWeb ? 'index.html' : 'web/index.html');
const html = await readFile(indexPath, 'utf8');
assert.ok(html.includes(`data-runtime="${verifyDist ? 'desktop' : 'web'}"`));
if (verifyDist || verifyWeb) assert.ok(!html.includes('{{APP_VERSION}}'));

assert.match(html, /<script type="module" src="assets\/js\/app-entry\.mjs"><\/script>/u, 'HTML은 단일 ES Module 진입점을 로드해야 합니다.');
assert.equal([...html.matchAll(/<script\b[^>]*\bsrc=/gu)].length, 1, 'HTML에는 legacy classic script 태그가 남아 있으면 안 됩니다.');
for (const path of ['assets/js/app-entry.mjs', 'assets/js/classic-script-manifest.mjs', ...paths]) {
  await access(file(path));
}

async function verifySequentialLoading(baseURI, runtime, expectedPaths) {
  const previousDocument = Object.getOwnPropertyDescriptor(globalThis, 'document');
  const previousFetch = globalThis.fetch;
  globalThis.fetch = async url => ({ok:true,json:async () => String(url).endsWith('manifest.json')
    ? {schema:'toram.project-items.v1',optimizerEligible:true,kinds:{crystas:'crystas.json'}} : {9776:{gameItemId:9776}}});
  const loaded = [];
  const documentRef = {
    baseURI,
    defaultView:{},
    getElementById() { return null; },
    documentElement:{ dataset:{ runtime } },
    createElement(tagName) {
      assert.equal(tagName, 'script', 'legacy loader는 script 요소만 만들어야 합니다.');
      return {};
    },
    head: {
      appendChild(script) {
        loaded.push({ src: script.src, type: script.type, async: script.async });
        script.onload();
      }
    }
  };
  Object.defineProperty(globalThis, 'document', { configurable:true, value:documentRef });
  try {
    const entry = pathToFileURL(file('assets/js/app-entry.mjs')).href + `?runtime=${runtime}&base=${encodeURIComponent(baseURI)}`;
    await import(entry);
    assert.equal(typeof documentRef.defaultView.ToramApp.items.getItem, 'function', 'The application exposes the ID-based item catalog without eager data requests.');
    assert.equal(typeof documentRef.defaultView.ToramApp.bosses.get, 'function', 'The application exposes boss variants without eager data requests.');
  } finally {
    globalThis.fetch = previousFetch;
    if (previousDocument) Object.defineProperty(globalThis, 'document', previousDocument);
    else delete globalThis.document;
  }
  assert.deepEqual(loaded.map(item => item.src), expectedPaths.map(path => new URL(path, baseURI).href), `${baseURI}: ${runtime} script order`);
  assert.ok(loaded.every(item => item.type === 'text/javascript' && item.async === false), `${baseURI}: classic scripts must stay sequential`);
}

await verifySequentialLoading('http://localhost:5173/', 'web', WEB_CLASSIC_SCRIPT_PATHS);
await verifySequentialLoading('https://example.com/calculator/', 'web', WEB_CLASSIC_SCRIPT_PATHS);
await verifySequentialLoading('https://tauri.localhost/', 'desktop', CLASSIC_SCRIPT_PATHS);
assert.equal(new Set(WEB_CLASSIC_SCRIPT_PATHS).size, WEB_CLASSIC_SCRIPT_PATHS.length);
assert.equal(WEB_CLASSIC_SCRIPT_PATHS.at(-1), 'assets/js/ui/ui-bootstrap.js');
assert.ok(WEB_CLASSIC_SCRIPT_PATHS.includes('assets/js/optimization/wasm-client.js'));
for (const path of CLASSIC_SCRIPT_PATHS.filter(path => /native-client|tauri-|\/update-/u.test(path))) {
  assert.ok(!WEB_CLASSIC_SCRIPT_PATHS.includes(path), `Desktop script loaded on web: ${path}`);
}

const workerClient = await readFile(file('assets/js/optimization/wasm-client.js'), 'utf8');
const worker = await readFile(file('assets/js/optimization/wasm-worker.js'), 'utf8');
assert.ok(workerClient.includes("new root.Worker('assets/js/optimization/wasm-worker.js')"));
assert.ok(worker.includes("'candidate-preparation.js'"));
assert.ok(!CLASSIC_SCRIPT_PATHS.some(path => /exact-solver|worker-client|solver-worker|seed-search|marginal-score|pair-partition|source-profile/u.test(path)));
if (verifyDist || verifyWeb) await access(file('assets/wasm/crysta_bg.wasm'));
for (const name of ['exact-solver', 'worker-client', 'solver-worker', 'seed-search', 'marginal-score', 'pair-partition', 'source-profile']) {
  await assert.rejects(access(file(`assets/js/optimization/${name}.js`)), { code:'ENOENT' });
}
console.log('ES Module entry: PASS (Rust-only runtimes; source/deployment, subpath, Native/WASM loading)');
