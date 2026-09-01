import assert from 'node:assert/strict';
import { readdirSync } from 'node:fs';
import { resolve } from 'node:path';
import { spawnSync } from 'node:child_process';
import {
  BASELINE_COMMIT,
  CHARACTERIZATION_FIXTURES,
  NORMAL_VALUE_FIXTURES
} from './r0-baseline-fixtures.mjs';

const root = resolve(import.meta.dirname, '..');
const group = process.argv[2] || 'all';
const validGroups = new Set(['all', 'normal', 'characterization']);
assert.ok(validGroups.has(group), '사용법: node tools/test-r0-baseline.mjs [all|normal|characterization]');

const allFixtures = [...NORMAL_VALUE_FIXTURES, ...CHARACTERIZATION_FIXTURES];
const discovered = readdirSync(resolve(root, 'tools'))
  .filter(name => /^test-.*\.mjs$/u.test(name) && name !== 'test-r0-baseline.mjs')
  .sort();
assert.equal(new Set(allFixtures).size, allFixtures.length, 'R0 fixture가 두 분류에 중복되면 안 됩니다.');
assert.deepEqual([...allFixtures].sort(), discovered, '새 회귀 테스트는 R0 fixture 분류를 먼저 받아야 합니다.');

const selected = group === 'normal'
  ? NORMAL_VALUE_FIXTURES
  : group === 'characterization'
    ? CHARACTERIZATION_FIXTURES
    : allFixtures;

const failures = [];
console.log(`R0 baseline ${BASELINE_COMMIT}: ${group} (${selected.length} fixtures)`);
for (const fixture of selected) {
  console.log(`\n[R0:${group}] ${fixture}`);
  const result = spawnSync(process.execPath, [resolve(root, 'tools', fixture)], {
    cwd: root,
    stdio: 'inherit'
  });
  if (result.error || result.status !== 0) {
    failures.push(`${fixture}${result.error ? ` (${result.error.message})` : ` (exit ${result.status})`}`);
  }
}

assert.deepEqual(failures, [], `R0 baseline 실패:\n${failures.join('\n')}`);
console.log(`\nR0 baseline ${BASELINE_COMMIT}: PASS (${selected.length}/${selected.length})`);
