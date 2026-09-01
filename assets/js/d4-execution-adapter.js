/* D4의 실행 선택과 제어만 담당한다. 탐색 알고리즘·후보·상한에는 관여하지 않는다. */
(function (root) {
  'use strict';

  var SCHEMA = 'toram.d4-execution-adapter.v1';

  function workerClient() { return root.ToramD4WorkerClient || null; }
  function nativeClient() { return root.ToramD4NativeClient || null; }

  function unavailableError() {
    return new Error('D4 최적화 실행기를 사용할 수 없습니다.');
  }

  // Native preparation/invocation failures retain the established browser
  // Worker fallback. A completed native result is never replaced or sorted.
  function execute(problem, callbacks, options) {
    var native = nativeClient();
    var worker = workerClient();
    if (native && native.isAvailable()) {
      return native.optimize(problem, callbacks, options).catch(function (error) {
        if (options && typeof options.canFallback === 'function' && !options.canFallback()) return null;
        if (worker && typeof worker.optimize === 'function') return worker.optimize(problem, callbacks, options);
        throw error;
      });
    }
    if (worker && typeof worker.optimize === 'function') return worker.optimize(problem, callbacks, options);
    return Promise.reject(unavailableError());
  }

  function resume(callbacks, options) {
    var native = nativeClient();
    if (!native || !native.isAvailable() || !native.hasContinuation()) return Promise.reject(unavailableError());
    return native.resume(callbacks, options);
  }

  function cancel(reason) {
    var native = nativeClient();
    var worker = workerClient();
    var cancelled = false;
    if (native && typeof native.cancel === 'function') cancelled = native.cancel(reason) || cancelled;
    if (worker && typeof worker.cancel === 'function') cancelled = worker.cancel(reason) || cancelled;
    return cancelled;
  }

  function pause() {
    var native = nativeClient();
    return Boolean(native && typeof native.pause === 'function' && native.pause());
  }

  function disposeContinuation() {
    var native = nativeClient();
    return native && typeof native.disposeContinuation === 'function' ? native.disposeContinuation() : Promise.resolve(false);
  }

  function hasContinuation() {
    var native = nativeClient();
    return Boolean(native && typeof native.hasContinuation === 'function' && native.hasContinuation());
  }

  function isAvailable() {
    var native = nativeClient();
    var worker = workerClient();
    return Boolean((native && native.isAvailable && native.isAvailable()) || (worker && typeof worker.optimize === 'function'));
  }

  function isRunning() {
    var native = nativeClient();
    var worker = workerClient();
    return Boolean((native && native.isRunning && native.isRunning()) || (worker && worker.isRunning && worker.isRunning()));
  }

  root.ToramD4ExecutionAdapter = Object.freeze({
    schema:SCHEMA,
    execute:execute,
    resume:resume,
    cancel:cancel,
    pause:pause,
    disposeContinuation:disposeContinuation,
    hasContinuation:hasContinuation,
    isAvailable:isAvailable,
    isRunning:isRunning
  });
}(typeof window !== 'undefined' ? window : globalThis));
