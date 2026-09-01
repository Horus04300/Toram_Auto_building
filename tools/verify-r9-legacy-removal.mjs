import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { LEGACY_SCRIPT_PATHS } from '../assets/js/legacy-script-manifest.mjs';

const root = resolve(import.meta.dirname, '..');
const read = path => readFile(resolve(root, path), 'utf8');
const calculator = await read('assets/js/calculator.js');
const policies = await read('assets/js/calculation-policies.js');
const crystaUi = await read('assets/js/crysta-ui.js');
const application = await read('assets/js/application-use-cases.js');
const settings = await read('assets/js/settings-repository.js');
const storageAdapter = await read('assets/js/tauri-build-storage-adapter.js');
const executionAdapter = await read('assets/js/d4-execution-adapter.js');
const optimizer = await read('assets/js/optimizer.js');
const optimizerUi = await read('assets/js/optimizer-ui-controller.js');
const worker = await read('assets/js/d4-optimizer-worker.js');

assert.doesNotMatch(calculator, /applyStatLegacy|checkCondition\(/u, '계산기의 구형 stat/조건 fallback을 제거해야 합니다.');
assert.match(calculator, /ToramCalculationPolicies[\s\S]*applyStat/u, '계산기의 stat 적용은 단일 정책을 사용해야 합니다.');
assert.match(calculator, /matchesCrystaCondition/u, '계산기의 크리스타 조건 판정은 단일 정책을 사용해야 합니다.');
assert.doesNotMatch(crystaUi, /function checkCondition/u, '크리스타 UI의 중복 조건 fallback을 제거해야 합니다.');
assert.match(crystaUi, /ToramCalculationPolicies[\s\S]*matchesCrystaCondition/u, '크리스타 UI는 계산 정책의 조건 판정을 사용해야 합니다.');
assert.doesNotMatch(optimizer, /\bcheckCondition\(/u, '최적화 결과 표시도 제거된 checkCondition fallback을 호출하면 안 됩니다.');
assert.match(optimizer, /ToramCalculationPolicies[\s\S]*matchesCrystaCondition/u, '최적화 결과 표시는 계산 정책의 크리스타 조건 판정을 사용해야 합니다.');
assert.doesNotMatch(application, /legacyInput/u, 'Application의 입력 어댑터는 legacy 이름을 남기면 안 됩니다.');
assert.match(application, /kernelInput/u, 'Application은 명시적인 kernel 입력 어댑터를 유지해야 합니다.');
assert.match(policies, /function applyStat/u, '계산 정책은 stat 적용의 유일한 진입점이어야 합니다.');

assert.ok(LEGACY_SCRIPT_PATHS.indexOf('assets/js/calculation-policies.js') < LEGACY_SCRIPT_PATHS.indexOf('assets/js/calculator.js'), '계산 정책은 계산기보다 먼저 로드해야 합니다.');
assert.match(worker, /'stat-registry\.js',[\s\S]*'calculation-policies\.js',[\s\S]*'calculator\.js'/u, 'D4 Worker도 계산 정책을 같은 순서로 로드해야 합니다.');

for (const forbidden of ['toram-auto-build-setting', 'showDirectoryPicker', 'indexedDB']) {
  assert.doesNotMatch(`${settings}\n${storageAdapter}`, new RegExp(forbidden, 'u'), `${forbidden} legacy 저장 경로를 다시 도입하면 안 됩니다.`);
}
assert.match(settings, /SESSION_STORAGE_KEY = 'toram\.auto-build\.application-state\.v2'/u, '마지막 세션은 v2 단일 저장 키만 사용해야 합니다.');
assert.match(settings, /fileAdapter\(\)/u, 'named build는 파일 Repository 경계를 통해야 합니다.');

assert.match(storageAdapter, /ToramSettingsFileRepositoryAdapter/u, 'Tauri 저장 Adapter는 Settings Repository의 실제 파일 Port입니다.');
assert.match(settings, /ToramSettingsFileRepositoryAdapter/u, 'Settings Repository는 현재 Tauri 파일 Adapter를 실제로 사용해야 합니다.');
assert.match(executionAdapter, /ToramD4NativeClient/u, 'D4 실행 Adapter는 Native 구현을 실제로 위임해야 합니다.');
assert.match(executionAdapter, /ToramD4WorkerClient/u, 'D4 실행 Adapter는 Worker 구현을 실제로 위임해야 합니다.');
assert.match(optimizer, /ToramD4ExecutionAdapter\.execute/u, '최적화 core는 D4 실행 Adapter를 실제로 사용해야 합니다.');
assert.match(optimizerUi, /ToramD4ExecutionAdapter\.(?:resume|pause|cancel)/u, '최적화 UI는 D4 실행 Adapter를 실제로 사용해야 합니다.');

console.log('R9 legacy removal verification: PASS (policy-only calculator, single storage path, live adapters retained)');
