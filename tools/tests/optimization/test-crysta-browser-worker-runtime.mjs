import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { resolve } from 'node:path';
import vm from 'node:vm';
import { CLASSIC_SCRIPT_PATHS } from '../../../assets/js/classic-script-manifest.mjs';

const root = resolve(import.meta.dirname, '../../..');
const scriptRoot = resolve(root, 'assets/js');
const messages = [];
const context = { console, setTimeout, clearTimeout };
context.self = context;
context.window = context;
context.postMessage = message => messages.push(message);
vm.createContext(context);
context.importScripts = (...names) => {
  for (const name of names) {
    const source = readFileSync(resolve(scriptRoot, 'optimization', name), 'utf8');
    vm.runInContext(source, context, { filename:name });
  }
};

const workerSource = readFileSync(resolve(scriptRoot, 'optimization/solver-worker.js'), 'utf8');
vm.runInContext(workerSource, context, { filename:'optimization/solver-worker.js' });

assert.equal(typeof context.onmessage, 'function', '브라우저 Worker 진입점이 등록돼야 합니다.');
assert.equal(typeof context.ToramCalculationKernel?.evaluateContext, 'function', 'Worker 안에서 기존 계산 커널을 그대로 불러와야 합니다.');
const html = readFileSync(resolve(root, 'index.html'), 'utf8');
const optimizerCore = readFileSync(resolve(scriptRoot, 'optimization-results.js'), 'utf8');
const optimizerUi = readFileSync(resolve(scriptRoot, 'optimizer-ui-controller.js'), 'utf8');
const recommendationApply = readFileSync(resolve(scriptRoot, 'optimization/recommendation-apply.js'), 'utf8');
const optimizerSource = optimizerCore + '\n' + optimizerUi;
const css = readFileSync(resolve(root, 'assets/css/style.css'), 'utf8');
assert.match(html, /id="crystaOptimizationProgress"[\s\S]*id="crystaOptimizationContinue"[\s\S]*id="crystaOptimizationPause"[\s\S]*id="crystaOptimizationCancel"/, '결과 탭에 진행 상태와 정밀 계산·일시정지·취소 버튼이 있어야 합니다.');
assert.match(html, /id="optimizationRecommendationOverview"[\s\S]*id="optimizationRecommendationSummary"/, '결과 탭 첫 화면에는 현재와 추천을 비교하는 요약 영역이 있어야 합니다.');
assert.match(html, /id="optimizationApplyRecommendedCrystas"/, '전역 추천 결과를 장비 입력에 반영하는 버튼이 있어야 합니다.');
assert.match(html, /<details class="final-rec" id="finalRecContainer">/, '전체 추천 옵션은 첫 화면을 차지하지 않도록 접을 수 있어야 합니다.');
assert.match(html, /<details class="result-detail-panel">[\s\S]*현재 세팅 상세 및 전체 옵션/, '현재 세팅의 상세 옵션은 접이식으로 제공해야 합니다.');
assert.match(html, /<details class="result-detail-panel">[\s\S]*옵션 효율 분석/, '옵션 효율 분석은 별도 접이식 영역이어야 합니다.');
assert.ok(CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization/worker-client.js') < CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization-results.js'), 'Worker 클라이언트는 결과 UI보다 먼저 로드돼야 합니다.');
assert.ok(CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization/native-client.js') < CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization-results.js'), '네이티브 CrystaOptimization 클라이언트는 결과 UI보다 먼저 로드돼야 합니다.');
assert.ok(CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization/execution-adapter.js') < CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization-results.js'), 'CrystaOptimization 실행 Adapter는 결과 UI보다 먼저 로드돼야 합니다.');
assert.ok(CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization/recommendation-apply.js') < CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimizer-ui-controller.js'), '추천 크리스타 적용 경계는 최적화 UI 컨트롤러보다 먼저 로드돼야 합니다.');
assert.ok(CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimization-results.js') < CLASSIC_SCRIPT_PATHS.indexOf('assets/js/optimizer-ui-controller.js'), '최적화 UI 컨트롤러는 계산/렌더링 core 뒤에 로드돼야 합니다.');
assert.match(optimizerCore, /runLegacyPerPartOptimization = false/, '기존 부위별 독립 추천 계산은 실행하지 않아야 합니다.');
assert.match(optimizerCore, /launchCrystaOptimizationWorker\(problem, currentEvaluation, locks, version, 30000\)/, '결과 탭은 30초 전역 계산 예산을 시작해야 합니다.');
assert.match(optimizerUi, /ToramCrystaOptimizationExecutionAdapter\.resume\([\s\S]*timeLimitMs:30000/u, 'bounded native 결과는 같은 frontier를 30초 정밀 계산으로 재개해야 합니다.');
assert.match(optimizerCore, /continueButton\.hidden = !\(\(status === 'bounded' \|\| status === 'no-incumbent-yet' \|\| status === 'paused'\) && state\.continuationId\)/, '세션이 없는 종료 결과에는 정밀 계산 재개 버튼을 표시하면 안 됩니다.');
assert.match(optimizerUi, /ToramCrystaOptimizationExecutionAdapter\.pause/, '네이티브 계산은 취소와 구분되는 일시정지를 제공해야 합니다.');
assert.match(optimizerCore, /renderCrystaOptimizationRecommendationOverview/, '전역 추천 결과는 전용 현재↔추천 비교 렌더러를 거쳐야 합니다.');
assert.match(optimizerCore, /lastOptimizationResult/, '적용 가능한 추천 결과는 CrystaOptimization RuntimeState에만 보관해야 합니다.');
assert.match(optimizerUi, /ToramCrystaOptimizationRecommendationApply\.apply/, '최적화 UI는 전용 적용 경계를 통해 추천 크리스타만 장비에 반영해야 합니다.');
assert.match(recommendationApply, /lockInput\.checked[\s\S]*removeLockedName/, '추천 반영은 잠긴 슬롯을 쓰지 않고 추천 결과가 잠긴 크리스타를 포함하는지 확인해야 합니다.');
assert.match(optimizerCore, /최대 HP[\s\S]*최대 MP[\s\S]*공격 MP 회복[\s\S]*ASPD/, '추천 비교에는 HP·MP·공격 MP 회복·속도 유틸리티가 포함돼야 합니다.');
assert.match(optimizerCore, /계산 상세 및 최적화 검증/, '엔진·평가·상한 정보는 일반 추천 화면이 아닌 계산 상세에 둬야 합니다.');
assert.match(optimizerCore, /ToramCrystaOptimizationExecutionAdapter\.execute/, '결과 탭은 단일 CrystaOptimization 실행 Adapter를 통해 실행기를 선택해야 합니다.');
assert.match(optimizerCore, /function optimizationEngineText[\s\S]*rust-native[\s\S]*Rust CPU/u, '결과 UI는 native 엔진을 표시해야 합니다.');
assert.match(optimizerCore, /state\.gpuPolicy[\s\S]*cpu-only\.v1/u, '결과 UI는 GPU 정책을 표시해야 합니다.');
assert.match(optimizerCore, /exact:'전역 최적해를 증명했습니다\.'/u, 'exact 상태를 사용자에게 구분해 표시해야 합니다.');
assert.match(optimizerCore, /bounded:'제한 시간 내 최선 추천을 찾았습니다\.'/u, 'bounded 상태를 사용자에게 구분해 표시해야 합니다.');
assert.match(optimizerCore, /cancelled:'전역 계산을 취소했습니다\.'/u, 'cancelled 상태를 사용자에게 구분해 표시해야 합니다.');
assert.match(optimizerCore, /invalid:'현재 입력에서는 유효한 추천을 만들 수 없습니다\.'/u, 'invalid 상태를 사용자에게 구분해 표시해야 합니다.');
assert.match(css, /\.optimization-progress-track\.is-indeterminate/, '상한이 준비되기 전에는 무한 진행 표시를 사용해야 합니다.');

assert.equal(typeof context.ToramBuildEvaluator?.evaluate, 'function', 'Worker 안에서 BuildEvaluator를 불러와야 합니다.');
assert.equal(typeof context.ToramCrystaOptimizationSourceProfile?.createReplacementProofReport, 'function', 'Worker 안에서 integration Replacement Proof 분석기를 불러와야 합니다.');
assert.equal(typeof context.ToramCrystaOptimizationSourceProfile?.applyProvenDropsForAudit, 'function', 'Worker 안에서 integration 감사용 축소기를 불러와야 합니다.');
assert.equal(typeof context.ToramCrystaOptimizationDynamicMarginal?.createDynamicMarginalProfile, 'function', 'Worker 안에서 S1 동적 한계효용 계측기를 불러와야 합니다.');

assert.equal(typeof context.ToramCrystaOptimizationDynamicSeed?.createDynamicCandidateOrder, 'function', 'Worker 안에서 candidate ordering 결정적 후보 순서 모듈을 불러와야 합니다.');
assert.equal(typeof context.ToramCrystaOptimizationDynamicSeed?.createDynamicSeedPool, 'function', 'Worker 안에서 seed pool 다중 seed pool 모듈을 불러와야 합니다.');
assert.equal(typeof context.ToramCrystaOptimizationDynamicSeed?.createDynamicSeedBuilds, 'function', 'Worker 안에서 seed builds 완성 seed·repair 모듈을 불러와야 합니다.');
assert.equal(typeof context.ToramCrystaOptimizationDynamicSeed?.improveDynamicSeedBuilds, 'function', 'Worker 안에서 local improvement incumbent·국소 개선 모듈을 불러와야 합니다.');
assert.equal(typeof context.ToramCrystaOptimizationGlobalOptimizer?.optimize, 'function', 'Worker 안에서 전역 탐색기를 불러와야 합니다.');
assert.equal(context.DYNAMIC_ACCELERATION_DEFAULTS.enableDynamicSeedIncumbent, true, 'seed acceleration 승인 Worker 기본값은 dynamic seed incumbent를 활성화해야 합니다.');
assert.equal(context.DYNAMIC_ACCELERATION_DEFAULTS.enableDynamicSeedOrdering, true, 'seed acceleration 승인 Worker 기본값은 결정적 후보 순서를 활성화해야 합니다.');

console.log('CrystaOptimization browser Worker runtime: PASS (importScripts, calculator kernel, evaluator, optimizer)');
