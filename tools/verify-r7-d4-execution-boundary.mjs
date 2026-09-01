import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { LEGACY_SCRIPT_PATHS } from '../assets/js/legacy-script-manifest.mjs';

const root = resolve(import.meta.dirname, '..');
const read = path => readFile(resolve(root, path), 'utf8');
const ports = await read('frontend/application/ports.ts');
const adapter = await read('assets/js/d4-execution-adapter.js');
const optimizer = await read('assets/js/optimizer.js');
const optimizerUi = await read('assets/js/optimizer-ui-controller.js');

for (const name of ['OptimizationProblem', 'OptimizationProgress', 'OptimizationResult', 'OptimizationRunner']) {
  assert.match(ports, new RegExp(`interface ${name}\\b`, 'u'), `${name} 계약이 필요합니다.`);
}
assert.match(ports, /pause\?\(\): void/u, '일시정지는 실행 제어 계약으로 명시해야 합니다.');
assert.match(ports, /resume\?\(/u, '재개는 실행 제어 계약으로 명시해야 합니다.');
assert.match(ports, /disposeContinuation\?\(/u, '계속 실행 세션 폐기는 실행 제어 계약으로 명시해야 합니다.');
assert.doesNotMatch(ports, /CalculationGateway/u, '계산 커널 Gateway를 추가하면 안 됩니다.');
assert.match(adapter, /native\.optimize[\s\S]*worker\.optimize/u, 'Native 실패 시 기존 Worker fallback을 유지해야 합니다.');
assert.match(adapter, /canFallback/, 'stale 요청은 Worker fallback을 시작하지 않아야 합니다.');
assert.match(adapter, /native\.resume/, '재개는 Native continuation에 위임해야 합니다.');
assert.match(adapter, /native\.pause/, '일시정지는 Native continuation에 위임해야 합니다.');
assert.match(adapter, /native\.disposeContinuation/, '세션 폐기는 Native continuation에 위임해야 합니다.');
assert.doesNotMatch(adapter, /prepareProblem|deriveRelevantKeys|sort\(/u, '실행 Adapter는 문제 컴파일·탐색·정렬을 소유하면 안 됩니다.');
assert.match(optimizer, /ToramD4ExecutionAdapter\.execute/u, '최적화 core는 실행 Adapter를 통해 실행해야 합니다.');
assert.doesNotMatch(optimizer, /ToramD4(?:Native|Worker)Client/u, '최적화 core는 구체 실행기 클라이언트를 직접 참조하면 안 됩니다.');
assert.match(optimizerUi, /ToramD4ExecutionAdapter\.(?:resume|pause|cancel)/u, '최적화 UI는 실행 Adapter만 제어해야 합니다.');
assert.doesNotMatch(optimizerUi, /ToramD4(?:Native|Worker)Client/u, '최적화 UI는 구체 실행기 클라이언트를 직접 참조하면 안 됩니다.');
assert.ok(LEGACY_SCRIPT_PATHS.indexOf('assets/js/d4-worker-client.js') < LEGACY_SCRIPT_PATHS.indexOf('assets/js/d4-execution-adapter.js'));
assert.ok(LEGACY_SCRIPT_PATHS.indexOf('assets/js/d4-native-client.js') < LEGACY_SCRIPT_PATHS.indexOf('assets/js/d4-execution-adapter.js'));
assert.ok(LEGACY_SCRIPT_PATHS.indexOf('assets/js/d4-execution-adapter.js') < LEGACY_SCRIPT_PATHS.indexOf('assets/js/optimizer.js'));

console.log('R7 D4 execution boundary verification: PASS (contracts, adapter-only UI/core, unchanged execution delegation)');
