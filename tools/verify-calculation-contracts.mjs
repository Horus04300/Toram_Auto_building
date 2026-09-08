import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const contracts = await readFile(resolve(root, 'frontend/domain/calculation-contracts.ts'), 'utf8');
const ports = await readFile(resolve(root, 'frontend/application/ports.ts'), 'utf8');
const forbiddenReferences = /\b(window|document|HTMLElement|localStorage|__TAURI__|Worker|JSON)\b/u;
const withoutComments = source => source.replace(/\/\*[\s\S]*?\*\//gu, '').replace(/\/\/[^\r\n]*/gu, '');

assert.doesNotMatch(withoutComments(contracts), forbiddenReferences, '계산 계약은 UI·DOM·Tauri·저장 형식에 의존하면 안 됩니다.');
assert.doesNotMatch(withoutComments(ports), forbiddenReferences, 'Port는 UI·DOM·Tauri·저장 형식에 의존하면 안 됩니다.');
for (const name of ['BuildDraft', 'CalculationSnapshot', 'CalculationResult']) {
  assert.match(contracts, new RegExp(`interface ${name}\\b`, 'u'), `${name} 계약이 필요합니다.`);
}
assert.match(ports, /interface SettingsRepository\b/u, 'SettingsRepository Port가 필요합니다.');
assert.match(ports, /interface OptimizationRunner\b/u, 'OptimizationRunner Port가 필요합니다.');
assert.doesNotMatch(ports, /CalculationGateway/u, '계산 커널을 위한 Gateway를 추가하면 안 됩니다.');

assert.match(ports, /interface UpdateService\b/u, 'UpdateService는 계산 입력과 분리된 외부 Port여야 합니다.');
console.log('R2 calculation contracts: PASS (pure contracts, SettingsRepository, OptimizationRunner, UpdateService)');
