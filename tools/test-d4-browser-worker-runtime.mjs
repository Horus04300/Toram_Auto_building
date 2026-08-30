import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const scriptRoot = resolve(root, 'assets/js');
const messages = [];
const context = { console, setTimeout, clearTimeout };
context.self = context;
context.window = context;
context.postMessage = message => messages.push(message);
vm.createContext(context);
context.importScripts = (...names) => {
  for (const name of names) {
    const source = readFileSync(resolve(scriptRoot, name), 'utf8');
    vm.runInContext(source, context, { filename:name });
  }
};

const workerSource = readFileSync(resolve(scriptRoot, 'd4-optimizer-worker.js'), 'utf8');
vm.runInContext(workerSource, context, { filename:'d4-optimizer-worker.js' });

assert.equal(typeof context.onmessage, 'function', '브라우저 Worker 진입점이 등록돼야 합니다.');
assert.equal(typeof context.ToramCalculationKernel?.evaluateContext, 'function', 'Worker 안에서 기존 계산 커널을 그대로 불러와야 합니다.');
const html = readFileSync(resolve(root, 'index.html'), 'utf8');
const optimizerUi = readFileSync(resolve(scriptRoot, 'optimizer.js'), 'utf8');
const css = readFileSync(resolve(root, 'assets/css/style.css'), 'utf8');
assert.match(html, /id="d4OptimizationProgress"[\s\S]*id="d4OptimizationContinue"[\s\S]*id="d4OptimizationCancel"/, '결과 탭에 진행 상태와 정밀 계산·취소 버튼이 있어야 합니다.');
assert.ok(html.indexOf('src="assets/js/d4-worker-client.js"') < html.indexOf('src="assets/js/optimizer.js"'), 'Worker 클라이언트는 결과 UI보다 먼저 로드돼야 합니다.');
assert.ok(html.indexOf('src="assets/js/d4-native-client.js"') < html.indexOf('src="assets/js/optimizer.js"'), '네이티브 D4 클라이언트는 결과 UI보다 먼저 로드돼야 합니다.');
assert.match(optimizerUi, /runLegacyPerPartOptimization = false/, '기존 부위별 독립 추천 계산은 실행하지 않아야 합니다.');
assert.match(optimizerUi, /launchD4Worker\(problem, currentEvaluation, locks, version, 5000\)/, '결과 탭은 5초 전역 Worker 계산을 시작해야 합니다.');
assert.match(optimizerUi, /launchD4Worker\(d4LastOptimizationRequest\.problem[\s\S]*30000\)/, 'bounded 결과는 30초 정밀 계산을 다시 시작할 수 있어야 합니다.');
assert.match(optimizerUi, /ToramD4NativeClient\.optimize[\s\S]*ToramD4WorkerClient\.optimize/, '데스크톱 네이티브 경로 실패 시 Worker fallback을 유지해야 합니다.');
assert.match(optimizerUi, /function d4EngineText[\s\S]*rust-native[\s\S]*Rust CPU/u, '결과 UI는 native 엔진을 표시해야 합니다.');
assert.match(optimizerUi, /state\.gpuPolicy[\s\S]*cpu-only\.p7/u, '결과 UI는 GPU 정책을 표시해야 합니다.');
assert.match(optimizerUi, /exact:'전역 최적해를 증명했습니다\.'/u, 'exact 상태를 사용자에게 구분해 표시해야 합니다.');
assert.match(optimizerUi, /bounded:'제한 시간 내 최선 추천을 찾았습니다\.'/u, 'bounded 상태를 사용자에게 구분해 표시해야 합니다.');
assert.match(optimizerUi, /cancelled:'전역 계산을 취소했습니다\.'/u, 'cancelled 상태를 사용자에게 구분해 표시해야 합니다.');
assert.match(optimizerUi, /invalid:'현재 입력에서는 유효한 추천을 만들 수 없습니다\.'/u, 'invalid 상태를 사용자에게 구분해 표시해야 합니다.');
assert.match(css, /\.d4-progress-track\.is-indeterminate/, '상한이 준비되기 전에는 무한 진행 표시를 사용해야 합니다.');

assert.equal(typeof context.ToramBuildEvaluator?.evaluate, 'function', 'Worker 안에서 BuildEvaluator를 불러와야 합니다.');
assert.equal(typeof context.ToramD4SourceProfile?.createReplacementProofReport, 'function', 'Worker 안에서 S6 Replacement Proof 분석기를 불러와야 합니다.');
assert.equal(typeof context.ToramD4SourceProfile?.applyProvenDropsForAudit, 'function', 'Worker 안에서 S6 감사용 축소기를 불러와야 합니다.');
assert.equal(typeof context.ToramD4DynamicMarginal?.createDynamicMarginalProfile, 'function', 'Worker 안에서 S1 동적 한계효용 계측기를 불러와야 합니다.');

assert.equal(typeof context.ToramD4DynamicSeed?.createDynamicCandidateOrder, 'function', 'Worker 안에서 S5 결정적 후보 순서 모듈을 불러와야 합니다.');
assert.equal(typeof context.ToramD4DynamicSeed?.createDynamicSeedPool, 'function', 'Worker 안에서 S2 다중 seed pool 모듈을 불러와야 합니다.');
assert.equal(typeof context.ToramD4DynamicSeed?.createDynamicSeedBuilds, 'function', 'Worker 안에서 S3 완성 seed·repair 모듈을 불러와야 합니다.');
assert.equal(typeof context.ToramD4DynamicSeed?.improveDynamicSeedBuilds, 'function', 'Worker 안에서 S4 incumbent·국소 개선 모듈을 불러와야 합니다.');
assert.equal(typeof context.ToramD4GlobalOptimizer?.optimize, 'function', 'Worker 안에서 전역 탐색기를 불러와야 합니다.');
assert.equal(context.DYNAMIC_ACCELERATION_DEFAULTS.enableDynamicSeedIncumbent, true, 'S7 승인 Worker 기본값은 dynamic seed incumbent를 활성화해야 합니다.');
assert.equal(context.DYNAMIC_ACCELERATION_DEFAULTS.enableDynamicSeedOrdering, true, 'S7 승인 Worker 기본값은 결정적 후보 순서를 활성화해야 합니다.');

console.log('D4 browser Worker runtime: PASS (importScripts, calculator kernel, evaluator, optimizer)');
