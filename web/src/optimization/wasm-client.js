export function createWasmClient(root) {
  'use strict';
  var worker = null, key = null, continuation = false, active = null, version = 0, lastResult = null;

  function dispose() {
    var existed = Boolean(worker);
    if (worker) worker.terminate();
    worker = null; key = null; continuation = false; lastResult = null;
    return Promise.resolve(existed);
  }

  function cancel(reason) {
    if (!active) return false;
    var pending = active;
    active = null;
    dispose();
    var result = { status:'cancelled', engine:'rust-wasm', exact:false, bestBuild:null, upperBound:null,
      optimalityGap:null, diagnostics:[{ code:'USER_CANCELLED', message:reason || '계산을 취소했습니다.' }] };
    if (pending.handlers.onComplete) pending.handlers.onComplete(result, { wasm:true, cancelled:true });
    pending.resolve(result);
    return true;
  }

  function run(problem, mode, callbacks, options) {
    var handlers = callbacks || {}, nextKey = problem ? JSON.stringify(problem) : key;
    if (active) cancel('새 추천으로 이전 계산을 취소했습니다.');
    if (worker && nextKey !== key) dispose();
    if (nextKey === key && lastResult && (lastResult.status === 'exact' || mode === 'preview')) {
      return Promise.resolve().then(function () {
        if (handlers.onComplete) handlers.onComplete(lastResult, { wasm:true, cached:true });
        return lastResult;
      });
    }
    var resume = Boolean(worker && continuation);
    if (!resume && !problem) return Promise.reject(new Error('WASM 추천 세션이 만료되었습니다.'));
    if (!resume) {
      dispose(); key = nextKey;
      try { worker = new root.Worker(new URL('./wasm-worker.js',import.meta.url),{type:'module'}); }
      catch (error) { return Promise.reject(error); }
    }
    return new Promise(function (resolve, reject) {
      var pending = active = { resolve:resolve, reject:reject, handlers:handlers, version:++version };
      worker.onmessage = function (event) {
        var message = event.data;
        if (active !== pending || message.version !== pending.version) return;
        if (message.type === 'progress') {
          if (handlers.onProgress) handlers.onProgress(message.progress);
        } else if (message.type === 'result') {
          active = null;
          lastResult = message.result;
          continuation = Boolean(lastResult.continuationId);
          if (handlers.onComplete) handlers.onComplete(lastResult, { wasm:true, resumed:resume });
          resolve(lastResult);
        } else if (message.type === 'error') fail(new Error(message.message));
      };
      function fail(error) {
        if (active !== pending) return;
        active = null; dispose(); reject(error);
      }
      worker.onerror = function (event) { fail(new Error(event.message || 'WASM 추천기를 불러오지 못했습니다.')); };
      if (handlers.onProgress) handlers.onProgress({ status:'running', stage:'preparing', engine:'rust-wasm', native:false, resumable:mode !== 'preview' });
      worker.postMessage({ type:resume ? 'resume' : 'start', version:pending.version, mode:mode,
        problem:resume ? undefined : problem, options:options || {} });
    });
  }

  return Object.freeze({
    preview:function (problem, callbacks, options) { return run(problem, 'preview', callbacks, options); },
    optimize:function (problem, callbacks, options) { return run(problem, 'precise', callbacks, options); },
    resume:function (callbacks, options) { return run(null, 'precise', callbacks, options); },
    cancel:cancel,
    pause:function () { if (!active || !worker) return false; worker.postMessage({ type:'pause' }); return true; },
    disposeContinuation:function () { cancel('추천 세션을 폐기했습니다.'); return dispose(); },
    hasContinuation:function () { return Boolean(worker && continuation); },
    isRunning:function () { return Boolean(active); },
    isAvailable:function () { return typeof root.Worker === 'function' && typeof root.WebAssembly === 'object'; }
  });
}
