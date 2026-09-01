import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const calls = [];
let nativeFails = true;
const context = {
  console,
  Promise,
  window:{
    ToramD4NativeClient:{
      isAvailable:() => true,
      optimize:() => { calls.push('native.optimize'); return nativeFails ? Promise.reject(new Error('native start failed')) : Promise.resolve({ status:'exact', engine:'rust-native' }); },
      resume:() => { calls.push('native.resume'); return Promise.resolve({ status:'exact', continuationId:null }); },
      cancel:reason => { calls.push(`native.cancel:${reason}`); return true; },
      pause:() => { calls.push('native.pause'); return true; },
      disposeContinuation:() => { calls.push('native.dispose'); return Promise.resolve(true); },
      hasContinuation:() => true,
      isRunning:() => false
    },
    ToramD4WorkerClient:{
      optimize:() => { calls.push('worker.optimize'); return Promise.resolve({ status:'bounded', engine:'js-worker' }); },
      cancel:reason => { calls.push(`worker.cancel:${reason}`); return true; },
      isRunning:() => false
    }
  }
};
context.window.window = context.window;
vm.createContext(context);
vm.runInContext(await readFile(resolve(root, 'assets/js/d4-execution-adapter.js'), 'utf8'), context, { filename:'d4-execution-adapter.js' });

const adapter = context.window.ToramD4ExecutionAdapter;
assert.equal(adapter.schema, 'toram.d4-execution-adapter.v1');
assert.equal(adapter.isAvailable(), true);

const fallback = await adapter.execute({ id:'fixture' }, {}, { canFallback:() => true });
assert.equal(fallback.engine, 'js-worker', 'native launch failure must use the established Worker fallback');
assert.deepEqual(calls.slice(0, 2), ['native.optimize', 'worker.optimize']);

calls.length = 0;
const stale = await adapter.execute({ id:'stale' }, {}, { canFallback:() => false });
assert.equal(stale, null, 'a stale request must not launch a fallback Worker');
assert.deepEqual(calls, ['native.optimize']);

calls.length = 0;
nativeFails = false;
const native = await adapter.execute({ id:'native' }, {}, {});
assert.equal(native.engine, 'rust-native', 'a completed native result must stay native');
assert.deepEqual(calls, ['native.optimize']);

calls.length = 0;
assert.equal(adapter.pause(), true);
await adapter.resume({}, {});
assert.equal(adapter.cancel('fixture cancel'), true);
await adapter.disposeContinuation();
assert.deepEqual(calls, ['native.pause', 'native.resume', 'native.cancel:fixture cancel', 'worker.cancel:fixture cancel', 'native.dispose']);

console.log('D4 execution adapter: PASS (native preference, Worker fallback, cancellation, pause/resume, continuation disposal)');
