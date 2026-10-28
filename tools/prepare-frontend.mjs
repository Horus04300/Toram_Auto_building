import {spawnSync} from 'node:child_process';
import {buildWasm} from './build-wasm.mjs';
import {syncArtifacts} from './support/build-artifacts.mjs';
import { readFile, readdir, access } from 'node:fs/promises';
import { dirname, resolve, relative, sep } from 'node:path';
import { pathToFileURL } from 'node:url';
import {frontendSourcePath,frontendModuleGraph} from './support/frontend-paths.mjs';
import { readProjectManifest } from './extraction/convert-toram-project-items.mjs';
import { readBossManifest } from './extraction/convert-toram-project-bosses.mjs';

const root = resolve(import.meta.dirname, '..');
const versionToken = '{{APP_VERSION}}';

export async function renderFrontendHtml(target) {
  if (target !== 'desktop' && target !== 'web') throw new Error('Expected desktop or web target.');
  const packageJson = JSON.parse(await readFile(resolve(root, 'package.json'), 'utf8'));
  const html = await readFile(resolve(root, 'web/index.html'), 'utf8');
  if (html.split(versionToken).length !== 4) throw new Error(`Expected three ${versionToken} placeholders.`);
  if (html.split('data-runtime="web"').length !== 2) throw new Error('Expected one web runtime marker.');
  const accountServer = process.env.TORAM_ACCOUNT_SERVER_URL || '';
  if (accountServer && (new URL(accountServer).origin !== accountServer || !/^https:\/\//u.test(accountServer))) {
    throw new Error('TORAM_ACCOUNT_SERVER_URL must be an HTTPS origin without a trailing slash.');
  }
  return html.replaceAll(versionToken, `v${packageJson.version}`).replace('data-runtime="web"', `data-runtime="${target}"`)
    .replace('<meta name="account-server" content="">', `<meta name="account-server" content="${accountServer}">`);
}

export async function prepareFrontend(target) {
  const html=await renderFrontendHtml(target);
  await buildWasm();
  if(target==='desktop') {
    const compiler=spawnSync(process.execPath,[resolve(root,'node_modules/typescript/bin/tsc'),'-p','desktop/tsconfig.json'],{cwd:root,windowsHide:true,stdio:'inherit'});
    if(compiler.error) throw compiler.error;
    if(compiler.status!==0) throw new Error('Desktop adapter compilation failed');
  }
  const outputRoot = resolve(root, `build/${target}`);
  const graph=await frontendModuleGraph(target);
  const files=new Set(['index.html',...graph.files]);
  for (const directory of ['css', 'fonts', 'icons']) {
    const base = resolve(root, 'web/public', directory);
    for (const entry of await readdir(base, { recursive:true, withFileTypes:true })) {
      if (entry.isFile()) files.add('assets/' + relative(resolve(root, 'web/public'), resolve(entry.parentPath, entry.name)).split(sep).join('/'));
    }
  }
  for (const [kind, readManifest] of [['items', readProjectManifest], ['bosses', readBossManifest]]) {
    const directory = resolve(root, 'web/public/game-data', kind);
    try { await access(resolve(directory, 'manifest.json')); }
    catch (error) { if (error.code === 'ENOENT') continue; throw error; }
    const manifest = await readManifest(directory);
    files.add(`assets/game-data/${kind}/manifest.json`);
    for (const path of Object.keys(manifest.files)) files.add(`assets/game-data/${kind}/${path}`);
  }
  files.add('assets/wasm/crysta.js');
  files.add('assets/wasm/crysta_bg.wasm');
  const parallelRoot = resolve(root, 'build/generated/wasm/parallel');
  for (const entry of await readdir(parallelRoot, { recursive:true, withFileTypes:true })) {
    if (entry.isFile()) files.add('assets/wasm/parallel/' + relative(parallelRoot, resolve(entry.parentPath, entry.name)).split(sep).join('/'));
  }
  const written=await syncArtifacts(outputRoot,files,path=>path==='index.html' ? html : graph.rendered.has(path) ? graph.rendered.get(path) : readFile(resolve(root,frontendSourcePath(path))));
  console.log(`Prepared ${target} frontend in build/${target}/ (${written}/${files.size} changed artifacts).`);
  return {files:files.size,written};
}

if (process.argv[1] && import.meta.url === pathToFileURL(resolve(process.argv[1])).href) await prepareFrontend(process.argv[2]);
