import assert from 'node:assert/strict';
import {request} from 'node:http';
import {access,mkdir,readFile,readdir,writeFile,mkdtemp,symlink,unlink} from 'node:fs/promises';
import {resolve} from 'node:path';
import {renderFrontendHtml,prepareFrontend} from '../../prepare-frontend.mjs';
import {createWebDevServer} from '../../web-dev.mjs';
import {frontendModuleGraph} from '../../support/frontend-paths.mjs';
import {readBossManifest} from '../../extraction/convert-toram-project-bosses.mjs';
import {buildWasm} from '../../build-wasm.mjs';
import {syncArtifacts} from '../../support/build-artifacts.mjs';

for (const target of ['web', 'desktop']) {
  const html = await renderFrontendHtml(target);
  assert.ok(html.includes(`data-runtime="${target}"`));
  assert.ok(!html.includes('{{APP_VERSION}}'));
  assert.match(html,/id="homeWorkspace"/u);
  assert.doesNotMatch(html,/id="charLevel"/u,'The platform entry must not embed calculator inputs');
}
const safety=await mkdtemp(resolve('build/tmp/artifact-safety-'));
const owned=resolve(safety,'owned'),outside=resolve(safety,'outside'),link=resolve(owned,'linked');
await mkdir(owned);await mkdir(outside);
await symlink(outside,link,process.platform==='win32'?'junction':'dir');
try {
  await assert.rejects(syncArtifacts(owned,new Set(['linked/leak.txt']),()=>''),/must be real/);
  await assert.rejects(access(resolve(outside,'leak.txt')),{code:'ENOENT'});
} finally {await unlink(link);}
await assert.rejects(syncArtifacts(owned,new Set(['../outside/leak.txt']),()=>''),/Invalid artifact path/);
await assert.rejects(renderFrontendHtml('../outside'), /target/);

const root = resolve(import.meta.dirname, '../../..');
const iconData = await readFile(resolve(root, 'web/src/data/skill-tree-data.js'), 'utf8');
const icons = [...iconData.matchAll(/"icon"\s*:\s*"([^"]+)"/gu)].map(match => match[1]);
const graphs={web:await frontendModuleGraph('web'),desktop:await frontendModuleGraph('desktop')};
for (const [target,directory] of [['web','build/web'],['desktop','build/desktop']]) {
  const scripts=[...graphs[target].files];
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
  assert.equal((await prepareFrontend(target)).written,0,'An unchanged deployment does not rewrite generated artifacts');
  assert.deepEqual((await readdir(output)).sort(), ['assets', 'index.html']);
  for (const path of [...scripts, ...icons, 'assets/js/optimization/wasm-worker.js', 'assets/wasm/crysta.js',
    'assets/wasm/crysta_bg.wasm', 'assets/wasm/parallel/crysta.js', 'assets/wasm/parallel/crysta_bg.wasm',
    'assets/fonts/OFL.txt', 'assets/icons/skills/icons/skill_on.png', 'assets/icons/skills/icons/skill_off.png']) {
    await access(resolve(output, path));
  }
  for (const path of ['data/sources', 'assets/game-data/ui', 'assets/js/calculator.js', 'assets/js/contracts/boundary-dtos.d.ts', 'desktop/adapters/saved-build-storage.ts']) {
    await assert.rejects(access(resolve(output, path)), { code:'ENOENT' });
  }
  for (const path of ['assets/game-data/items/manifest.json', 'assets/js/application/item-catalog.mjs', 'assets/js/ui/item-equipment-ui.mjs']) await access(resolve(output, path));
  await access(resolve(output, 'assets/js/application/boss-catalog.mjs'));
  await readBossManifest(resolve(output, 'assets/game-data/bosses'));
  for (const path of [...graphs.desktop.files].filter(path => !scripts.includes(path))) {
    await assert.rejects(access(resolve(output, path)), { code:'ENOENT' });
  }
}
await access(resolve(root, 'data/sources/game-icon-skill-match-candidates.json'));
assert.equal((await buildWasm()).generated,false,'Unchanged verified WASM bindings are reused');
const gluePath=resolve(root,'build/generated/wasm/crysta.js'), glue=await readFile(gluePath);
await writeFile(gluePath,'corrupt generated binding');
assert.equal((await buildWasm()).generated,true,'A stamp cannot hide corrupted generated output');
assert.deepEqual(await readFile(gluePath),glue);
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
  const inventory = await get('/inventory?type=equipment&equipmentType=sword');
  assert.equal((await get('/calculator')).status,200);
  assert.equal((await get('/board?post=example&release=1')).status,200);
  assert.equal((await get('/catalog?section=items&selected=22001')).status,200);
  for (const path of ['/assets/js/application/catalog-browser.mjs','/assets/js/pages/catalog/catalog-page.mjs','/assets/css/catalog.css']) assert.equal((await get(path)).status,200,path);
  const calculator = await get('/assets/pages/calculator.html');
  assert.equal(calculator.status,200); assert.match(calculator.headers['content-type'],/text\/html/u);
  assert.match(calculator.body,/id="charLevel"/u); assert.doesNotMatch(calculator.body,/<script\b/u);
  for (const path of ['/assets/js/pages/calculator/calculator-page.mjs','/assets/js/application/stat-labels.mjs','/assets/js/calculation/stat-registry.js']) assert.equal((await get(path)).status,200,path);
  for (const path of ['/assets/js/application/inventory-summary.mjs','/assets/js/pages/board/board-page.mjs','/assets/js/pages/board/publish-dialog.mjs','/assets/css/board.css']) assert.equal((await get(path)).status,200,path);
  for (const path of ['/assets/js/layout/platform-shell.mjs','/assets/js/pages/home/home-page.mjs','/assets/js/pages/inventory/inventory-page.mjs','/assets/js/pages/inventory/inventory-merge-ui.mjs','/assets/css/home.css','/assets/css/platform.css']) assert.equal((await get(path)).status,200,path);
  assert.equal(inventory.status, 200);
  assert.match(inventory.body, /inventory.css/);
  assert.equal(index.status, 200);
  assert.match(index.headers['content-type'], /text\/html/);
  assert.match(index.body, /data-runtime="web"/);
  assert.equal(index.headers['cache-control'], 'no-store');
  assert.equal(index.headers['cross-origin-opener-policy'], 'same-origin');
  assert.equal(index.headers['cross-origin-embedder-policy'], 'require-corp');
  const entry = await get('/assets/js/app-entry.mjs?test=1');
  assert.equal(entry.status, 200);
  assert.equal(entry.headers['content-type'], 'text/javascript');
  assert.match(entry.body, /ensureCalculator/);
  const worker = await get('/assets/js/optimization/wasm-worker.js');
  assert.equal(worker.status, 200);
  assert.doesNotMatch(worker.body,/importScripts/);
  assert.match(worker.headers['content-type'],/javascript/u);
  assert.equal((await get('/assets/css/style.css')).headers['content-type'], 'text/css');
  assert.equal((await get('/assets/fonts/PretendardVariable.woff2')).headers['content-type'], 'font/woff2');
  assert.equal((await get('/index.html', 'HEAD')).body, '');
  assert.equal((await get('/assets/js/app-entry.mjs', 'HEAD')).body, '');
  for (const path of ['/package.json', '/.git/config', '/web/src/contracts/boundary-dtos.d.ts', '/desktop/tauri.conf.json',
    '/engine/src/solver.rs', '/data/sources/skill-effect-source-links.json', '/assets/js/optimization/native-client.js',
    '/assets/js/contracts/boundary-dtos.d.ts', '/server/account-server.mjs', '/assets/missing.js', '/api/inventory/missing', '/inventory/unknown', '/assets/../package.json',
    '/assets/%2e%2e%5cpackage.json', '/assets/%2e%2e%2fpackage.json', '/assets/C:%5cWindows%5cwin.ini']) {
    assert.equal((await get(path)).status, 404, `Must not expose ${path}`);
  }
  assert.equal((await get('/assets/%ZZ')).status, 400);
  assert.equal((await get('/', 'POST')).status, 405);
  console.log('Web runtime: PASS (target HTML, source/Worker/font serving, HEAD, no cache, traversal/private path rejection)');
} finally {
  await new Promise(resolve => server.close(resolve));
}
