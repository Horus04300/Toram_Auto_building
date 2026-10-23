import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import vm from 'node:vm';

const calls = [], workers = [];
let nativeAvailable = true, nativeFails = false;
class FakeWorker {
  constructor(url) { this.url = url; this.messages = []; workers.push(this); }
  postMessage(message) { this.messages.push(message); }
  terminate() { this.terminated = true; }
  result(result, version = this.messages.filter(message => message.version).at(-1).version) {
    this.onmessage({ data:{ type:'result', version, result } });
  }
}
const root = { console, Worker:FakeWorker, WebAssembly:{},
  ToramCrystaOptimizationNativeClient:{
    isAvailable:() => nativeAvailable, isRunning:() => false, hasContinuation:() => false,
    optimize:async () => { calls.push('native'); if (nativeFails) throw new Error('native failed'); return { status:'exact', engine:'rust-native' }; },
    cancel:() => false, pause:() => false, disposeContinuation:async () => false
  }
};
root.window = root;
const context = vm.createContext(root);
for (const file of ['wasm-client.js','execution-adapter.js']) {
  vm.runInContext(await readFile(new URL('../../../web/src/optimization/' + file, import.meta.url), 'utf8'), context);
}
const adapter = root.ToramCrystaOptimizationExecutionAdapter;
assert.equal(adapter.schema, 'toram.crysta-execution-adapter.v2');
assert.equal((await adapter.execute({})).engine, 'rust-native');
nativeFails = true;
await assert.rejects(adapter.execute({}), /native failed/);
assert.equal(workers.length, 0, 'native errors must not silently start another solver');
nativeAvailable = false;
const problem = { id:'fixture' };
const preview = adapter.preview(problem);
assert.equal(workers.length, 1);
const worker = workers[0];
assert.equal(worker.url, 'assets/js/optimization/wasm-worker.js');
assert.equal(worker.messages[0].mode, 'preview');
worker.result({ status:'heuristic', engine:'rust-wasm', continuationId:'wasm-session' });
assert.equal((await preview).status, 'heuristic');
assert.equal(adapter.hasContinuation(), true);
const precise = adapter.execute(problem);
assert.equal(workers.length, 1, 'precision must reuse the preview session');
assert.equal(worker.messages.at(-1).type, 'resume');
const preciseVersion = worker.messages.at(-1).version;
assert.equal(adapter.pause(), true);
assert.equal(worker.messages.at(-1).type, 'pause');
worker.result({ status:'paused', continuationId:'wasm-session' }, preciseVersion);
assert.equal((await precise).status, 'paused');
assert.equal(adapter.hasContinuation(), true);
const resumed = adapter.resume();
worker.result({ status:'exact', engine:'rust-wasm', exact:true, continuationId:null });
assert.equal((await resumed).status, 'exact');
assert.equal(adapter.hasContinuation(), false);
assert.equal((await adapter.execute(problem)).status, 'exact');
assert.equal(workers.length, 1, 'unchanged exact result can be reused');
await adapter.disposeContinuation();
assert.equal(worker.terminated, true);
const pending = adapter.execute({ id:'new' });
assert.equal(adapter.isRunning(), true);
assert.equal(adapter.cancel('test'), true);
const cancelled = await pending;
assert.equal(cancelled.status, 'cancelled');
assert.equal(cancelled.upperBound, null);
assert.equal(adapter.hasContinuation(), false);
assert.equal(adapter.isRunning(), false);
const failed = adapter.execute({ id:'error' });
workers.at(-1).onerror({ message:'wasm load failed' });
await assert.rejects(failed, /wasm load failed/);
assert.equal(adapter.isRunning(), false);
assert.equal(workers.at(-1).terminated, true);
console.log('Rust execution: PASS (Native preference, errors without JS fallback, WASM preview reuse, pause/resume, exact cache, cancellation, failed-load cleanup)');
