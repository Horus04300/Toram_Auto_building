import {buildWasm} from './build-wasm.mjs';
import {prepareFrontend} from './prepare-frontend.mjs';
import assert from 'node:assert/strict';
import { readdirSync } from 'node:fs';
import { resolve } from 'node:path';
import { spawnSync } from 'node:child_process';
import {
  CHARACTERIZATION_FIXTURES,
  NORMAL_VALUE_FIXTURES
} from './regression-fixtures.mjs';

const root = resolve(import.meta.dirname, '..');
const group = process.argv[2] || 'all';
const validGroups = new Set(['all', 'normal', 'characterization', 'browser']);
assert.ok(validGroups.has(group), '사용법: npm test [-- all|normal|characterization|browser]');

function check(command, args) {
  console.log(`\n[Check] ${command} ${args.join(' ')}`);
  const result = spawnSync(command, args, {cwd:root, windowsHide:true, stdio:'inherit'});
  if (result.error) throw result.error;
  assert.equal(result.status, 0, `검사 실패: ${command} ${args.join(' ')} (${result.signal || result.status})`);
}
const nodeCheck = (path, ...args) => check(process.execPath, [resolve(root, path), ...args]);
if (group === 'browser') {
  await prepareFrontend('web');
  for (const file of ['verify-web-browser', 'verify-session-restore-browser', 'verify-web-parallel']) nodeCheck(`tools/verification/${file}.mjs`);
  console.log('Browser suite: PASS');
  process.exit(0);
}

const allFixtures = [...NORMAL_VALUE_FIXTURES, ...CHARACTERIZATION_FIXTURES];
const discovered = readdirSync(resolve(root, 'tools/tests'), { recursive:true })
  .map(name => 'tests/' + name.replaceAll('\\', '/'))
  .filter(name => /(?:^|\/)test-.*\.mjs$/u.test(name))
  .sort();
assert.equal(new Set(allFixtures).size, allFixtures.length, 'Regression fixture가 두 분류에 중복되면 안 됩니다.');
assert.deepEqual([...allFixtures].sort(), discovered, '새 회귀 테스트는 Regression fixture 분류를 먼저 받아야 합니다.');

const selected = group === 'normal'
  ? NORMAL_VALUE_FIXTURES
  : group === 'characterization'
    ? CHARACTERIZATION_FIXTURES
    : allFixtures;

if (group === 'all') {
  await prepareFrontend('desktop');
  nodeCheck('node_modules/typescript/bin/tsc', '-p', 'tsconfig.json');
  nodeCheck('tools/verification/verify-typescript-boundaries.mjs');
  nodeCheck('tools/verification/verify-es-module-entry.mjs');
} else await buildWasm();

const failures = [];
console.log(`Regression suite: ${group} (${selected.length} fixtures)`);
for (const fixture of selected) {
  console.log(`\n[Regression:${group}] ${fixture}`);
  const result = spawnSync(process.execPath, [resolve(root, 'tools', fixture)], {
    cwd: root,
    stdio: 'inherit'
  });
  if (result.error || result.status !== 0) {
    failures.push(`${fixture}${result.error ? ` (${result.error.message})` : ` (exit ${result.status})`}`);
  }
}

assert.deepEqual(failures, [], `Regression suite 실패:\n${failures.join('\n')}`);
console.log(`\nRegression suite: PASS (${selected.length}/${selected.length})`);
if (group === 'all') {
  nodeCheck('tools/verification/audit-stack-source-links.mjs', '--require-s1');
  for (const manifest of ['engine/Cargo.toml', 'desktop/Cargo.toml']) {
    check('cargo', ['fmt', '--manifest-path', manifest, '--check']);
    check('cargo', ['test', '--locked', '--manifest-path', manifest]);
    check('cargo', ['clippy', '--locked', '--manifest-path', manifest, '--all-targets', '--', '-D', 'warnings']);
  }
  console.log('Project checks: PASS (types, module boundaries, regression, S1, Rust fmt/test/clippy)');
}
