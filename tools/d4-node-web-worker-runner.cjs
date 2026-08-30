const { parentPort, workerData } = require('node:worker_threads');
const { readFileSync } = require('node:fs');
const { resolve } = require('node:path');
const vm = require('node:vm');

// Node 회귀에서 브라우저 Worker의 importScripts/onmessage 계약을 그대로 실행한다.
const scriptRoot = workerData.scriptRoot;
const context = { console, setTimeout, clearTimeout, performance };
context.self = context;
context.window = context;
context.postMessage = message => parentPort.postMessage(message);
vm.createContext(context);
context.importScripts = (...names) => {
  for (const name of names) {
    const source = readFileSync(resolve(scriptRoot, name), 'utf8');
    vm.runInContext(source, context, { filename:name });
  }
};
vm.runInContext(readFileSync(resolve(scriptRoot, 'd4-optimizer-worker.js'), 'utf8'), context, { filename:'d4-optimizer-worker.js' });
parentPort.on('message', data => context.onmessage({ data }));
