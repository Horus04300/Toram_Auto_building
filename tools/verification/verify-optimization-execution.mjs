import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { CLASSIC_SCRIPT_PATHS } from '../../web/src/classic-script-manifest.mjs';

const root = resolve(import.meta.dirname, '../..');
const read = path => readFile(resolve(root, path), 'utf8');
const ports = await read('web/src/application/ports.ts');
const adapter = await read('web/src/optimization/execution-adapter.js');
const optimizer = await read('web/src/ui/optimization-results.js');
const optimizerUi = await read('web/src/ui/optimizer-ui-controller.js');

for (const name of ['OptimizationProblem', 'OptimizationProgress', 'OptimizationResult', 'OptimizationRunner']) {
  assert.match(ports, new RegExp(`interface ${name}\\b`, 'u'), `${name} 계약이 필요합니다.`);
}
assert.match(ports, /pause\?\(\): void/u, '일시정지는 실행 제어 계약으로 명시해야 합니다.');
assert.match(ports, /resume\?\(/u, '재개는 실행 제어 계약으로 명시해야 합니다.');
assert.match(ports, /disposeContinuation\?\(/u, '계속 실행 세션 폐기는 실행 제어 계약으로 명시해야 합니다.');
assert.doesNotMatch(ports, /CalculationGateway/u, '계산 커널 Gateway를 추가하면 안 됩니다.');
assert.match(adapter, /ToramCrystaOptimizationNativeClient/u);
assert.match(adapter, /ToramCrystaOptimizationWasmClient/u);
assert.match(adapter, /client\.preview/u);
assert.match(adapter, /client\.resume/u);
assert.doesNotMatch(adapter, /ToramCrystaOptimizationWorkerClient|canFallback/u, 'Retired JS search must not be a fallback');
assert.doesNotMatch(adapter, /prepareProblem|deriveRelevantKeys|sort\(/u, '실행 Adapter는 문제 컴파일·탐색·정렬을 소유하면 안 됩니다.');
assert.match(optimizer, /ToramCrystaOptimizationExecutionAdapter\.execute/u, '최적화 core는 실행 Adapter를 통해 실행해야 합니다.');
assert.doesNotMatch(optimizer, /ToramCrystaOptimization(?:Native|Worker)Client/u, '최적화 core는 구체 실행기 클라이언트를 직접 참조하면 안 됩니다.');
assert.match(optimizerUi, /ToramCrystaOptimizationExecutionAdapter\.(?:resume|pause|cancel)/u, '최적화 UI는 실행 Adapter만 제어해야 합니다.');
assert.doesNotMatch(optimizerUi, /ToramCrystaOptimization(?:Native|Worker)Client/u, '최적화 UI는 구체 실행기 클라이언트를 직접 참조하면 안 됩니다.');
assert.ok(CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization/wasm-client.js') < CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization/execution-adapter.js'));
assert.ok(CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization/native-client.js') < CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization/execution-adapter.js'));
assert.ok(CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization/execution-adapter.js') < CLASSIC_SCRIPT_PATHS.indexOf('assets/js/ui/optimization-results.js'));

console.log('Execution CrystaOptimization execution boundary verification: PASS (contracts, adapter-only UI/core, unchanged execution delegation)');
