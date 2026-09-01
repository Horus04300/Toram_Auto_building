import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const tsconfig = JSON.parse(await readFile(resolve(root, 'tsconfig.json'), 'utf8'));
const compilerOptions = tsconfig.compilerOptions || {};
assert.equal(compilerOptions.strict, true, 'R1b 타입 검사는 strict여야 합니다.');
assert.equal(compilerOptions.noEmit, true, '기본 타입 검사는 런타임 파일을 출력하면 안 됩니다.');
assert.equal(compilerOptions.allowJs, false, '기존 JavaScript 전체를 검증 대상으로 강제하지 않습니다.');

const sources = [
  'frontend/contracts/boundary-dtos.d.ts',
  'frontend/contracts/boundary-dto-fixtures.ts',
  'frontend/runtime/tauri-build-storage-adapter.ts',
  'frontend/domain/calculation-contracts.ts',
  'frontend/application/ports.ts',
  'frontend/contracts/calculation-contract-fixtures.ts'
];
for (const path of sources) {
  const source = await readFile(resolve(root, path), 'utf8');
  assert.doesNotMatch(source, /\bany\b/u, `${path}: any를 사용하면 안 됩니다.`);
}

const dtoSource = await readFile(resolve(root, sources[0]), 'utf8');
for (const name of ['LegacyBuildSettingsSnapshotDto', 'CalculationRequestDto', 'CalculationResultDto', 'D4OptimizationRequestDto', 'D4OptimizationResultDto', 'LegacyBuildStorageAdapter']) {
  assert.match(dtoSource, new RegExp(`interface ${name}\\b`, 'u'), `${name} DTO가 필요합니다.`);
}

console.log('R1b TypeScript boundary definitions: PASS (strict, no explicit any, build/calculation/storage/D4 DTOs)');
