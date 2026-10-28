import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {createUpdateService} from '../../../build/generated/desktop/update.js';
import {createUpdateCoordinator} from '../../../desktop/adapters/update/update-controller.js';
import {createUpdateUi} from '../../../desktop/adapters/update/ui-controller.js';

const read = path => readFileSync(new URL('../../../' + path, import.meta.url), 'utf8');
const info = { currentVersion:'0.6.3', version:'0.6.4', notes:'<script>bad()</script>', publishedAt:null };
const calls = [];
let response = info, fail = null;
const native = { core:{
  Channel:class { onmessage() {} },
  async invoke(command, args) {
    calls.push(command);
    if (fail) throw fail;
    if (command === 'check_for_update') return response;
    if (command === 'download_update') {
      args.progress.onmessage({ downloaded:20, total:null });
      args.progress.onmessage({ downloaded:NaN, total:100 });
    }
  }
} };
const adapter=tauri=>createUpdateService(tauri?.core);
const service = adapter(native);
assert.deepEqual(JSON.parse(JSON.stringify(await service.check())), info);
response = null;
assert.equal(await service.check(), null);
for (const invalid of [{}, { ...info, version:'0.6.5-beta.1' }, { ...info, notes:{} }]) {
  response = invalid;
  await assert.rejects(service.check(), /정보/);
}
fail = { code:'CHECK', message:'연결 실패' };
await assert.rejects(service.check(), /연결 실패/);
fail = null;
calls.length = 0;
const progress = [];
await service.install(info.version, p => progress.push(p), async () => { calls.push('flush'); });
assert.deepEqual(calls, ['download_update', 'flush', 'install_update']);
assert.equal(progress.length, 1);
calls.length = 0;
await assert.rejects(service.install(info.version, () => {}, async () => { throw new Error('저장 실패'); }), /저장 실패/);
assert.deepEqual(calls, ['download_update']);
calls.length = 0;
fail = { message:'서명 실패' };
await assert.rejects(service.install(info.version, () => {}, async () => { calls.push('flush'); }), /서명 실패/);
assert.deepEqual(calls, ['download_update']);
fail = null;
assert.equal(adapter(undefined).isAvailable(), false);
await assert.rejects(adapter(undefined).check(), /데스크톱/);

const root = { document:{ body:{ inert:false } }, ToramApp:{ optimizerUi:{ getState:()=>({}), stopForUpdate:async () => {} } }, ToramSettingsRepository:{ flushApplicationState:async () => { if (flushFail) throw new Error('저장 실패'); } } };
root.ToramUpdateController=createUpdateCoordinator(root,{optimizer:root.ToramApp.optimizerUi,settingsRepository:root.ToramSettingsRepository});
let checked = 0, installed = 0, rejectCheck = false, allow = true, flushFail = false;
let resolveCheck;
const deps = {
  service:{ isAvailable:() => true, check:async () => {
    checked++;
    if (rejectCheck) throw new Error('offline');
    return response;
  }, install:async (_version, notify, before) => {
    notify({ downloaded:3, total:5 }); await before(); installed++;
  } },
  confirm:async () => allow
};
const controller = root.ToramUpdateController.create(deps);
response = null;
await controller.check(true);
assert.equal(controller.read().visible, false);
rejectCheck = true;
await controller.check(true);
assert.equal(controller.read().phase, 'failed');
assert.equal(controller.read().visible, false);
rejectCheck = false; response = info;
await controller.check(true);
assert.equal(controller.read().phase, 'available');
assert.equal(installed, 0, 'check must never install');
controller.later();
assert.equal(controller.read().visible, false);
await controller.check(false);
allow = false;
await controller.install();
assert.equal(installed, 0, 'declining must preserve running work');
allow = true; flushFail = true;
await controller.install();
assert.equal(controller.read().phase, 'failed');
assert.equal(installed, 0);
flushFail = false;
const phases = [];
controller.subscribe(state => phases.push(state.phase));
await controller.install();
assert.equal(controller.read().phase, 'completed');
assert.equal(installed, 1);
assert.ok(phases.includes('downloading') && phases.includes('installing'));
const unavailable = root.ToramUpdateController.create({ service:adapter(undefined) });
await unavailable.check();
assert.equal(unavailable.read().phase, 'unavailable');
deps.service.check = () => new Promise(resolve => { resolveCheck = resolve; });
const pending = controller.check();
await controller.check();
await controller.install();
resolveCheck(null);
await pending;
assert.equal(installed, 1, 'in-flight checks cannot start installs');
const elements = new Map([...read('web/src/pages/calculator/calculator.html').matchAll(/id="(update[^"]*)"/g)].map(([, id]) => [id, {
  hidden:false, listeners:{}, textContent:'', value:0,
  addEventListener(name, fn) { this.listeners[name] = fn; },
  removeAttribute(name) { delete this[name]; }
}]));
const timers = [];
const uiRoot = {
  ToramUpdateController:root.ToramUpdateController,
  ToramUpdateService:{ isAvailable:() => true, check:async () => info },
  ToramSettingsRepository:{ getUpdateSettings:() => ({ checkOnStartup:true }), setUpdateSettings:() => {} },
  setTimeout:fn => timers.push(fn)
};
createUpdateUi({getElementById:id=>elements.get(id),defaultView:uiRoot},{updateController:uiRoot.ToramUpdateController,settingsRepository:uiRoot.ToramSettingsRepository},uiRoot.ToramUpdateService);

assert.equal(elements.get('updatePanel').hidden, true, 'startup must not immediately show a panel');
timers[0]();
await new Promise(resolve => setImmediate(resolve));
assert.equal(elements.get('updatePanel').hidden, false);
assert.equal(elements.get('updateNotes').textContent, info.notes, 'remote notes stay literal text');
assert.equal(elements.get('updateNotes').innerHTML, undefined);
elements.get('updateLater').listeners.click();
assert.equal(elements.get('updatePanel').hidden, true);
console.log('Updater: PASS (metadata, unavailable, silent startup, notes UI, consent, progress, save/signature failure, retry, concurrency)');

let running = true, paused = false, stops = 0, flushes = 0, installs = 0, allowFirst = false, allowFinal = false, failFinal = false, finalStage = false;
const coordination = {
  document:{ body:{ inert:false } },
  ToramCrystaOptimizationExecutionAdapter:{ isRunning:() => running, hasContinuation:() => paused },
  ToramApp:{ optimizerUi:{ getState:()=>({}), stopForUpdate:async () => { stops++; running = false; paused = false; } } },
  ToramSettingsRepository:{ flushApplicationState:async () => { flushes++; if (failFinal && finalStage) throw new Error('quota'); } }
};
coordination.ToramUpdateController=createUpdateCoordinator(coordination,{execution:coordination.ToramCrystaOptimizationExecutionAdapter,optimizer:coordination.ToramApp.optimizerUi,settingsRepository:coordination.ToramSettingsRepository});
let confirmations = 0;
const coordinated = coordination.ToramUpdateController.create({
  service:{ isAvailable:() => true, check:async () => info, install:async (_version,_notify,before) => {
    assert.equal(coordination.document.body.inert,false,'Download must permit edits');
    paused = true; finalStage = true; await before();
    assert.equal(coordination.document.body.inert,true,'Only final installation stays locked');
    installs++;
  } },
  confirm:async work => { assert.equal(work,true); return ++confirmations % 2 ? allowFirst : allowFinal; }
});
await coordinated.check();
await coordinated.install();
assert.equal(stops,0,'Declined consent must preserve running work');
assert.equal(running,true);
allowFirst = true; confirmations = 0;
await coordinated.install();
assert.equal(coordinated.read().phase,'failed');
assert.equal(installs,0);
assert.equal(paused,true,'New paused work survives declining final consent');
assert.equal(coordination.document.body.inert,false);
allowFinal = true; confirmations = 0; finalStage = false;
await coordinated.install();
assert.equal(coordinated.read().phase,'completed');
assert.equal(installs,1);
assert.equal(flushes,3,'Preflight and final installation each flush current input');
assert.equal(coordination.document.body.inert,false);
failFinal = true; confirmations = 0; finalStage = false;
await coordinated.install();
assert.equal(coordinated.read().phase,'failed');
assert.equal(installs,1,'Failed final save must block installation');
assert.equal(coordination.ToramUpdateController.isLocked(),false);
assert.ok(coordination.ToramUpdateController.epoch() > 0);
console.log('Update workflow: PASS (consent, current/paused work, fresh pre/final saves, download editing, final lock, failure release)');
