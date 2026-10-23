import assert from 'node:assert/strict';
import { request } from 'node:http';
import { access, mkdir, readFile, readdir, writeFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { renderFrontendHtml, prepareFrontend } from '../../prepare-frontend.mjs';
import { createWebDevServer } from '../../web-dev.mjs';
import { CLASSIC_SCRIPT_PATHS, WEB_CLASSIC_SCRIPT_PATHS } from '../../../web/src/classic-script-manifest.mjs';
import { readBossManifest } from '../../extraction/convert-toram-project-bosses.mjs';

for (const target of ['web', 'desktop']) {
  const html = await renderFrontendHtml(target);
  assert.ok(html.includes(`data-runtime="${target}"`));
  assert.ok(!html.includes('{{APP_VERSION}}'));
}
await assert.rejects(renderFrontendHtml('../outside'), /target/);

const root = resolve(import.meta.dirname, '../../..');
const iconData = await readFile(resolve(root, 'web/src/data/skill-tree-data.js'), 'utf8');
const icons = [...iconData.matchAll(/"icon"\s*:\s*"([^"]+)"/gu)].map(match => match[1]);
for (const [target, directory, scripts] of [['web','build/web',WEB_CLASSIC_SCRIPT_PATHS], ['desktop','build/desktop',CLASSIC_SCRIPT_PATHS]]) {
  const output = resolve(root, directory);
  if (target === 'desktop') {
    const config = JSON.parse(await readFile(resolve(root, 'desktop/tauri.conf.json'), 'utf8'));
    assert.equal(resolve(root, 'desktop', config.build.frontendDist), output, 'Tauri must embed the generated desktop frontend');
  }
  await mkdir(resolve(output, 'data/sources'), { recursive:true });
  await writeFile(resolve(output, 'data/sources/stale-build-probe.txt'), 'obsolete deployment file');
  await mkdir(resolve(output, 'obsolete-build-folder'), { recursive:true });
  await writeFile(resolve(output, 'obsolete-build-folder/probe.txt'), 'obsolete root artifact');
  await prepareFrontend(target);
  assert.deepEqual((await readdir(output)).sort(), ['assets', 'index.html']);
  for (const path of [...scripts, ...icons, 'assets/js/optimization/wasm-worker.js', 'assets/wasm/crysta.js',
    'assets/wasm/crysta_bg.wasm', 'assets/fonts/OFL.txt', 'assets/icons/skills/icons/skill_on.png', 'assets/icons/skills/icons/skill_off.png']) {
    await access(resolve(output, path));
  }
  for (const path of ['data/sources', 'assets/game-data/ui', 'assets/js/calculator.js', 'assets/js/application/ports.ts', 'desktop/adapters/saved-build-storage.ts']) {
    await assert.rejects(access(resolve(output, path)), { code:'ENOENT' });
  }
  for (const path of ['assets/game-data/items/manifest.json', 'assets/js/application/item-catalog.mjs', 'assets/js/ui/item-equipment-ui.mjs']) await access(resolve(output, path));
  await access(resolve(output, 'assets/js/application/boss-catalog.mjs'));
  await readBossManifest(resolve(output, 'assets/game-data/bosses'));
  for (const path of CLASSIC_SCRIPT_PATHS.filter(path => !scripts.includes(path))) {
    await assert.rejects(access(resolve(output, path)), { code:'ENOENT' });
  }
}
await access(resolve(root, 'data/sources/game-icon-skill-match-candidates.json'));
await access(resolve(root, 'data/sources/game-ui/manifest.csv'));

const server = createWebDevServer();
await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));
function get(path, method = 'GET') {
  return new Promise((resolve, reject) => {
    const req = request({ hostname:'127.0.0.1', port:server.address().port, path, method }, res => {
      const chunks = [];
      res.on('data', chunk => chunks.push(chunk));
      res.on('end', () => resolve({ status:res.statusCode, headers:res.headers, body:Buffer.concat(chunks).toString() }));
    });
    req.on('error', reject);
    req.end();
  });
}
try {
  const index = await get('/');
  assert.equal(index.status, 200);
  assert.match(index.headers['content-type'], /text\/html/);
  assert.match(index.body, /data-runtime="web"/);
  assert.equal(index.headers['cache-control'], 'no-store');
  const entry = await get('/assets/js/app-entry.mjs?test=1');
  assert.equal(entry.status, 200);
  assert.equal(entry.headers['content-type'], 'text/javascript');
  assert.match(entry.body, /WEB_CLASSIC_SCRIPT_PATHS/);
  const worker = await get('/assets/js/optimization/wasm-worker.js');
  assert.equal(worker.status, 200);
  assert.match(worker.body, /importScripts/);
  assert.equal((await get('/assets/css/style.css')).headers['content-type'], 'text/css');
  assert.equal((await get('/assets/fonts/PretendardVariable.woff2')).headers['content-type'], 'font/woff2');
  assert.equal((await get('/index.html', 'HEAD')).body, '');
  assert.equal((await get('/assets/js/app-entry.mjs', 'HEAD')).body, '');
  for (const path of ['/package.json', '/.git/config', '/web/src/contracts/boundary-dtos.d.ts', '/desktop/tauri.conf.json',
    '/engine/src/solver.rs', '/data/sources/skill-effect-source-links.json', '/assets/js/optimization/native-client.js',
    '/assets/js/application/ports.ts', '/tools/reference/optimization/exact-solver.js', '/assets/missing.js', '/assets/../package.json',
    '/assets/%2e%2e%5cpackage.json', '/assets/%2e%2e%2fpackage.json', '/assets/C:%5cWindows%5cwin.ini']) {
    assert.equal((await get(path)).status, 404, `Must not expose ${path}`);
  }
  assert.equal((await get('/assets/%ZZ')).status, 400);
  assert.equal((await get('/', 'POST')).status, 405);
  console.log('Web runtime: PASS (target HTML, source/Worker/font serving, HEAD, no cache, traversal/private path rejection)');
} finally {
  await new Promise(resolve => server.close(resolve));
}
