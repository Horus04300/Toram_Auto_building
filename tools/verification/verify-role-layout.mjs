import assert from 'node:assert/strict';
import { existsSync, readFileSync, readdirSync } from 'node:fs';
import { dirname, resolve } from 'node:path';
import { CLASSIC_SCRIPT_PATHS } from '../../web/src/classic-script-manifest.mjs';
import { frontendSourcePath } from '../support/frontend-paths.mjs';
import { posix } from 'node:path';

const root = resolve(import.meta.dirname, '../..');
assert(!existsSync(resolve(root, 'tools/reference')), 'Retired recommendation implementations must stay deleted');
for (const retired of ['assets', 'frontend', 'src-tauri', 'crates', 'index.html']) {
  assert(!existsSync(resolve(root, retired)), `Obsolete source root: ${retired}`);
}
const files = ['web/src', 'desktop/adapters', 'desktop/src', 'engine/src', 'tools'].flatMap(directory =>
  readdirSync(resolve(root, directory), { recursive:true, withFileTypes:true })
    .filter(entry => entry.isFile())
    .map(entry => resolve(entry.parentPath, entry.name)));
for (const file of files) {
  assert.doesNotMatch(file.replaceAll('\\', '/').split('/').at(-1),
    /(?:^d4[-_]|-d4-|(?:^|-)r[0-9]+(?:-|\.)|-stage[0-9]+|-s[345](?:-|\.)|-[np][0-9](?:-|\.))/i,
    `Development-stage filename: ${file}`);
  if (!/\.(?:mjs|cjs|js|ts)$/.test(file)) continue;
  const source = readFileSync(file, 'utf8');
  for (const match of source.matchAll(/(?:from\s*|import\s*\(|require\s*\()(['"])(\.{1,2}\/[^'"\r\n]+)\1/g)) {
    const target = resolve(dirname(file), match[2]);
    const extensions = file.endsWith('.ts') ? ['', '.ts', '.d.ts'] : [''];
    assert(extensions.some(extension => existsSync(target + extension)), `Missing dependency ${match[2]} from ${file}`);
  }
}
assert.equal(new Set(CLASSIC_SCRIPT_PATHS).size, CLASSIC_SCRIPT_PATHS.length);
for (const path of CLASSIC_SCRIPT_PATHS) assert(existsSync(resolve(root, frontendSourcePath(path))), `Missing runtime source: ${path}`);
assert.equal(CLASSIC_SCRIPT_PATHS.at(-1), 'assets/js/ui/ui-bootstrap.js');
const worker = resolve(root, 'web/src/optimization/wasm-worker.js');
const imports = readFileSync(worker, 'utf8').match(/importScripts\(([\s\S]*?)\);/)[1];
for (const [, path] of imports.matchAll(/'([^']+)'/g)) {
  const source = frontendSourcePath(posix.normalize('assets/js/optimization/' + path));
  assert(existsSync(resolve(root, source)), `Missing Worker dependency: ${path}`);
}
assert.equal(readdirSync(resolve(root, 'web/src/data/skills')).filter(name => name.endsWith('.js')).length, 29);
console.log('Role layout: PASS (paths, imports, Worker dependencies, single bootstrap, 29 skill trees)');
