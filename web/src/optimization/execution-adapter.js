export function createExecutionAdapter(nativeRuntime,wasmRuntime) {
  'use strict';
  function nativeClient() { return nativeRuntime; }
  function wasmClient() { return wasmRuntime; }
  function unavailable() { return new Error('Rust 추천기를 사용할 수 없습니다. 페이지를 새로고침하거나 앱을 다시 실행해 주세요.'); }
  function runtime() {
    var native = nativeClient();
    return native && native.isAvailable() ? native : wasmClient();
  }
  function resumable() {
    var native = nativeClient();
    return native && native.hasContinuation() ? native : wasmClient();
  }
  function execute(problem, callbacks, options) {
    var client = runtime();
    if (!client || !client.isAvailable()) return Promise.reject(unavailable());
    if (client === nativeClient() && wasmClient()) wasmClient().disposeContinuation();
    return client.optimize(problem, callbacks, options);
  }
  function preview(problem, callbacks, options) {
    var client = wasmClient(), native = nativeClient();
    if (!client || !client.isAvailable()) return Promise.reject(unavailable());
    if (native) native.disposeContinuation();
    return client.preview(problem, callbacks, options);
  }
  function resume(callbacks, options) {
    var client = resumable();
    return client && client.hasContinuation() ? client.resume(callbacks, options) : Promise.reject(unavailable());
  }
  function cancel(reason) {
    var native = nativeClient(), wasm = wasmClient();
    var stopped = Boolean(native && native.cancel(reason));
    return Boolean(wasm && wasm.cancel(reason)) || stopped;
  }
  function pause() {
    var client = runtime();
    return Boolean(client && client.pause());
  }
  function disposeContinuation() {
    return Promise.all([nativeClient(), wasmClient()].filter(Boolean).map(function (client) { return client.disposeContinuation(); })).then(function (results) { return results.some(Boolean); });
  }
  function hasContinuation() {
    return [nativeClient(), wasmClient()].some(function (client) { return client && client.hasContinuation(); });
  }
  function isAvailable() { var client = runtime(); return Boolean(client && client.isAvailable()); }
  function isRunning() { return [nativeClient(), wasmClient()].some(function (client) { return client && client.isRunning(); }); }
  return Object.freeze({ schema:'toram.crysta-execution-adapter.v2',
    execute:execute, preview:preview, resume:resume, cancel:cancel, pause:pause,
    disposeContinuation:disposeContinuation, hasContinuation:hasContinuation, isAvailable:isAvailable, isRunning:isRunning });
}
