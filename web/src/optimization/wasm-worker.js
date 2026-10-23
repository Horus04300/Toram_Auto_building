'use strict';
self.window = self;
const BASE_ASPD_MAP = { '한손검':100, '양손검':50, '활':75, '자동활':30, '지팡이':60, '마도구':90, '권갑':120, '선풍창':25, '발도검':200, '맨손':1000 };
importScripts('../calculation/stat-registry.js', '../calculation/calculation-policies.js', '../calculation/calculator.js', '../calculation/build-evaluator.js',
  'candidate-preparation.js', 'rust-bridge.js', '../../wasm/crysta.js');

const ready = wasm_bindgen({ module_or_path:new URL('../../wasm/crysta_bg.wasm', self.location.href) });
let session, setup, version = 0, paused = false, started = 0, budget = 0, published = 0;
const bridge = self.ToramCrystaOptimizationRustBridge;

function snapshot(preview) {
  const result = JSON.parse(session.snapshot());
  if (preview && result.bestBuild) {
    result.status = 'heuristic'; result.exact = false; result.upperBound = null;
  }
  const normalized = bridge.normalize(setup.problem, setup.evaluate, result, { logicalThreads:1 });
  return Object.assign(normalized, {
    engine:'rust-wasm', schema:'toram.crysta-wasm-result.v1', native:false, resumable:true,
    continuationId:session.is_complete() ? null : 'wasm-session',
    optimalityGap:preview ? null : normalized.optimalityGap
  });
}

function sendResult(preview, status) {
  const result = snapshot(preview);
  if (status) result.status = status;
  self.postMessage({ type:'result', version, result });
}

function tick(expectedVersion) {
  if (version !== expectedVersion) return;
  try {
    if (paused) { sendResult(false, 'paused'); return; }
    const end = Math.min(started + budget, performance.now() + 16);
    while (!session.is_complete() && performance.now() < end) session.step(1);
    if (session.is_complete() || performance.now() - started >= budget) { sendResult(false); return; }
    if (performance.now() - published >= 100) {
      published = performance.now();
      self.postMessage({ type:'progress', version, progress:Object.assign(snapshot(false), { status:'running', stage:'wasm-search' }) });
    }
    setTimeout(() => tick(expectedVersion), 0);
  } catch (error) { self.postMessage({ type:'error', version, message:String(error.message || error) }); }
}

self.onmessage = async function (event) {
  const message = event.data;
  if (message.type === 'pause') { paused = true; return; }
  const expectedVersion = version = message.version;
  started = performance.now();
  budget = Math.max(1, Math.min(30000, Number(message.options && message.options.timeLimitMs) || 30000));
  paused = false;
  try {
    await ready;
    if (version !== expectedVersion) return;
    if (message.type === 'start') {
      setup = bridge.prepare(message.problem, message.options || {});
      session = new wasm_bindgen.SearchSession(JSON.stringify(bridge.projectProblem(setup.problem)));
    } else if (message.type !== 'resume' || !session) throw new Error('WASM 추천 세션이 없습니다. 새 계산을 시작하세요.');
    if (message.mode === 'preview') { sendResult(true); return; }
    published = 0;
    tick(expectedVersion);
  } catch (error) { self.postMessage({ type:'error', version, message:String(error.message || error) }); }
};
