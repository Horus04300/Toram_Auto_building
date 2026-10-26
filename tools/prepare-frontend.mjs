import { copyFile, mkdir, readFile, writeFile, readdir, access, unlink, rmdir, realpath, lstat } from 'node:fs/promises';
import { dirname, resolve, relative, sep } from 'node:path';
import { pathToFileURL } from 'node:url';
import { CLASSIC_SCRIPT_PATHS, WEB_CLASSIC_SCRIPT_PATHS } from '../web/src/classic-script-manifest.mjs';
import { frontendSourcePath, FRONTEND_MODULE_PATHS, FRONTEND_PAGE_PATHS } from './support/frontend-paths.mjs';
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

async function pruneDeploymentFiles(directory, outputRoot, files) {
  for (const entry of await readdir(directory, { withFileTypes:true })) {
    const path = resolve(directory, entry.name);
    if (entry.isSymbolicLink()) throw new Error(`Deployment must not contain symlinks: ${path}`);
    if (entry.isDirectory()) {
      await pruneDeploymentFiles(path, outputRoot, files);
      if ((await readdir(path)).length === 0) await rmdir(path);
    } else if (entry.isFile() && !files.has(relative(outputRoot, path).split(sep).join('/'))) await unlink(path);
  }
}

export async function prepareFrontend(target) {
  const html = await renderFrontendHtml(target);
  const outputRoot = resolve(root, `build/${target}`);
  const files = new Set(['index.html', ...(target === 'desktop' ? CLASSIC_SCRIPT_PATHS : WEB_CLASSIC_SCRIPT_PATHS), ...FRONTEND_MODULE_PATHS, ...FRONTEND_PAGE_PATHS]);
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
  await mkdir(outputRoot, { recursive:true });
  if (await realpath(outputRoot) !== outputRoot) throw new Error('Frontend output must be a real directory.');
  for (const path of files) {
    const output = resolve(outputRoot, path);
    if (!output.startsWith(outputRoot + sep)) throw new Error(`Invalid deployment path: ${path}`);
    await mkdir(dirname(output), { recursive:true });
    if (await realpath(dirname(output)) !== dirname(output)) throw new Error(`Deployment directory must be real: ${output}`);
    try { if (!(await lstat(output)).isFile()) throw new Error(`Deployment target must be a regular file: ${output}`); }
    catch (error) { if (error.code !== 'ENOENT') throw error; }
    if (path === 'index.html') await writeFile(output, html, 'utf8');
    else await copyFile(resolve(root, frontendSourcePath(path)), output);
  }
  await pruneDeploymentFiles(outputRoot, outputRoot, files);
  console.log(`Prepared ${target} frontend in build/${target}/.`);
}

if (process.argv[1] && import.meta.url === pathToFileURL(resolve(process.argv[1])).href) await prepareFrontend(process.argv[2]);
