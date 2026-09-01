import assert from 'node:assert/strict';
import { access, readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { pathToFileURL } from 'node:url';
import { LEGACY_SCRIPT_PATHS } from '../assets/js/legacy-script-manifest.mjs';

const root = resolve(import.meta.dirname, '..');
const verifyDist = process.argv.includes('--dist');
const frontendRoot = verifyDist ? resolve(root, 'dist') : root;
const indexPath = resolve(frontendRoot, 'index.html');
const html = await readFile(indexPath, 'utf8');

assert.match(html, /<script type="module" src="assets\/js\/app-entry\.mjs"><\/script>/u, 'HTML은 단일 ES Module 진입점을 로드해야 합니다.');
assert.equal([...html.matchAll(/<script\b[^>]*\bsrc=/gu)].length, 1, 'HTML에는 legacy classic script 태그가 남아 있으면 안 됩니다.');
for (const path of ['assets/js/app-entry.mjs', 'assets/js/legacy-script-manifest.mjs', ...LEGACY_SCRIPT_PATHS]) {
  await access(resolve(frontendRoot, path));
}

async function verifySequentialLoading(baseURI) {
  const previousDocument = Object.getOwnPropertyDescriptor(globalThis, 'document');
  const loaded = [];
  const documentRef = {
    baseURI,
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
    const entry = pathToFileURL(resolve(root, 'assets/js/app-entry.mjs')).href + `?r1a=${encodeURIComponent(baseURI)}`;
    await import(entry);
  } finally {
    if (previousDocument) Object.defineProperty(globalThis, 'document', previousDocument);
    else delete globalThis.document;
  }
  assert.deepEqual(loaded.map(item => item.src), LEGACY_SCRIPT_PATHS.map(path => new URL(path, baseURI).href), `${baseURI}: legacy script order`);
  assert.ok(loaded.every(item => item.type === 'text/javascript' && item.async === false), `${baseURI}: legacy scripts must stay classic and sequential`);
}

await verifySequentialLoading('http://localhost:1420/');
await verifySequentialLoading('https://tauri.localhost/');

const workerClient = await readFile(resolve(root, 'assets/js/d4-worker-client.js'), 'utf8');
const worker = await readFile(resolve(root, 'assets/js/d4-optimizer-worker.js'), 'utf8');
assert.match(workerClient, /var WORKER_URL = 'assets\/js\/d4-optimizer-worker\.js';/u, 'browser/Tauri Worker URL을 유지해야 합니다.');
assert.match(worker, /importScripts\([\s\S]*'stat-registry\.js'[\s\S]*'d4-global-optimizer\.js'/u, 'Worker의 classic importScripts 경계를 유지해야 합니다.');

console.log(`R1a ES Module entry: PASS (${verifyDist ? 'dist' : 'source'}, ${LEGACY_SCRIPT_PATHS.length} legacy scripts, browser + Tauri URL paths)`);
