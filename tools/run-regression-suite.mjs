import assert from 'node:assert/strict';
import { readdirSync } from 'node:fs';
import { resolve } from 'node:path';
import { spawnSync } from 'node:child_process';
import {
  BASELINE_COMMIT,
  CHARACTERIZATION_FIXTURES,
  NORMAL_VALUE_FIXTURES
} from './regression-fixtures.mjs';

const root = resolve(import.meta.dirname, '..');
const group = process.argv[2] || 'all';
const validGroups = new Set(['all', 'normal', 'characterization']);
assert.ok(validGroups.has(group), '사용법: node tools/run-regression-suite.mjs [all|normal|characterization]');

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

const failures = [];
console.log(`Regression baseline ${BASELINE_COMMIT}: ${group} (${selected.length} fixtures)`);
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

assert.deepEqual(failures, [], `Regression baseline 실패:\n${failures.join('\n')}`);
console.log(`\nRegression baseline ${BASELINE_COMMIT}: PASS (${selected.length}/${selected.length})`);
