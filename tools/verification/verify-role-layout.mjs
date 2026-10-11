import assert from 'node:assert/strict';
import { existsSync, readFileSync, readdirSync } from 'node:fs';
import { dirname, resolve } from 'node:path';
import { CLASSIC_SCRIPT_PATHS } from '../../assets/js/classic-script-manifest.mjs';

const root = resolve(import.meta.dirname, '../..');
const files = ['assets/js', 'frontend', 'src-tauri/src', 'tools'].flatMap(directory =>
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
assert.equal(CLASSIC_SCRIPT_PATHS.at(-1), 'assets/js/ui-bootstrap.js');
const worker = resolve(root, 'assets/js/optimization/solver-worker.js');
const imports = readFileSync(worker, 'utf8').match(/importScripts\(([\s\S]*?)\);/)[1];
for (const [, path] of imports.matchAll(/'([^']+)'/g)) assert(existsSync(resolve(dirname(worker), path)), `Missing Worker dependency: ${path}`);
assert.equal(readdirSync(resolve(root, 'assets/js/data/skills')).filter(name => name.endsWith('.js')).length, 29);
console.log('Role layout: PASS (paths, imports, Worker dependencies, single bootstrap, 29 skill trees)');
