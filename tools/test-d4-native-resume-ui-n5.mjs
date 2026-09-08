import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const client = await readFile(resolve(root, 'assets/js/d4-native-client.js'), 'utf8');
const optimizerCore = await readFile(resolve(root, 'assets/js/optimizer.js'), 'utf8');
const optimizerUi = await readFile(resolve(root, 'assets/js/optimizer-ui-controller.js'), 'utf8');
const optimizer = optimizerCore + '\n' + optimizerUi;

assert.match(client, /run\('resume_d4_optimization'/, 'native client must invoke the Rust continuation command');
assert.match(client, /pause_d4_optimization/, 'native client must expose a distinct pause command that keeps the frontier');
assert.match(client, /dispose_d4_optimization/, 'native client must release stale continuation sessions');
assert.match(client, /D4_CONTINUATION_UNAVAILABLE/, 'expired native sessions must surface an explicit error');
assert.match(optimizer, /status === 'bounded' \|\| status === 'no-incumbent-yet' \|\| status === 'paused'/, 'all resumable terminal states must expose a continuation control');
assert.match(optimizer, /d4OptimizationPause/, 'native execution must expose an explicit pause button');
const continueStart = optimizer.indexOf("continueButton.addEventListener('click'");
const continueEnd = optimizer.indexOf('function discardD4ContinuationForInputChange', continueStart);
assert.ok(continueStart >= 0 && continueEnd > continueStart, 'continue button handler must remain present');
const continueHandler = optimizer.slice(continueStart, continueEnd);
assert.match(continueHandler, /ToramD4ExecutionAdapter\.resume/, 'continue button must resume rather than launch a new search');
assert.doesNotMatch(continueHandler, /launchD4Worker\(/, 'continue button must not restart d4_optimize_parallel');
assert.match(continueHandler, /resumeUntilExact/, 'one precision action must automatically chain bounded 30-second slices until terminal or paused');
assert.match(optimizer, /discardD4ContinuationForInputChange/, 'input changes must discard stale continuations');
assert.match(optimizer, /pagehide/, 'closing the window must release a stored continuation');

// Execute the actual UI handlers: presentation-only input must keep costly work.
const listeners = new Map(), windowListeners = new Map();
const runtime = { runVersion:0 };
const calculationInput = { build:{ revision:0 }, scenario:{}, request:{} };
let cancellations = 0, disposals = 0;
const badge = {}, applyButton = { addEventListener() {} };
const documentRef = {
  readyState:'loading',
  getElementById(id) { return id === 'globalEffTextBadge' ? badge : id === 'd4ApplyRecommendedCrystas' ? applyButton : null; },
  addEventListener(type, handler) { if (!listeners.has(type)) listeners.set(type, []); listeners.get(type).push(handler); }
};
const context = {
  document:documentRef, window:null,
  addEventListener(type, handler) { windowListeners.set(type, handler); },
  populateRefineSelects() {}, updateSubWeaponList() {}, initAutocomplete() {}, renderBanTags() {}, addDefaultOptions() {},
  ToramApp:{ optimizer:{ uiSupport:{ runtime:() => runtime, updateProgress() {} } } },
  ToramBuildDraftStore:{ syncFromUi:() => calculationInput },
  ToramD4ExecutionAdapter:{ hasContinuation:() => true, cancel() { cancellations++; }, disposeContinuation() { disposals++; } }
};
context.window = context;
vm.createContext(context);
vm.runInContext(await readFile(resolve(root, 'assets/js/build-state-storage.js'), 'utf8'), context);
vm.runInContext(optimizerUi, context);
context.ToramApp.optimizerUi.initialize();
function arm() {
  runtime.lastOptimizationRequest = { problem:{} };
  runtime.lastOptimizationResult = { status:'bounded' };
  applyButton.hidden = false; applyButton.disabled = false;
  cancellations = 0; disposals = 0;
}
function emit(type, id = '', optionRow = false) {
  const target = { id, nodeType:1, closest:selector => optionRow && selector === '.opt-row' ? {} : null };
  for (const handler of listeners.get(type) || []) handler({ target });
}
for (const type of ['input', 'change']) {
  for (const id of ['buildSettingName', 'buildBackupName', 'buildSettingList', 'buildSettingImport', 'banInput', 'skillSearch', 'optimizationRequirementsDraft', 'unrelatedFutureInput']) {
    arm(); const request = runtime.lastOptimizationRequest, result = runtime.lastOptimizationResult, version = runtime.runVersion;
    emit(type, id);
    assert.equal(cancellations, 0, `${type} on ${id} must preserve running work`);
    assert.equal(disposals, 0, `${id} must preserve continuation`);
    assert.equal(runtime.lastOptimizationRequest, request);
    assert.equal(runtime.lastOptimizationResult, result);
    assert.equal(runtime.runVersion, version);
    assert.equal(applyButton.hidden, false);
  }
  for (const id of ['charLevel', 'strBase', 'bossDef', 'mainWeaponType', 'wpnAtk', 'subStab', 'armorType', 'cr_wpn_1', 'lock_spc_2']) {
    arm(); emit(type, id);
    assert.equal(cancellations, 1, `${type} on ${id} must cancel stale work`);
    assert.equal(disposals, 1);
    assert.equal(runtime.lastOptimizationRequest, null);
    assert.equal(runtime.lastOptimizationResult, null);
    assert.equal(applyButton.disabled, true);
    emit(type, id); assert.equal(cancellations, 1, 'duplicate events must not cancel twice');
  }
  arm(); emit(type, '', true); assert.equal(cancellations, 1, 'dynamic option rows affect calculations');
}
for (const type of ['toram:persistent-state-changed', 'toram:skill-investments-changed', 'toram:active-buffs-changed', 'toram:combo-changed', 'toram:combo-hit-selected', 'toram:build-options-changed', 'toram:optimization-preferences-changed']) {
  arm(); emit(type); assert.equal(disposals, 0, `${type} without an input change must preserve work`);
  calculationInput.build.revision++;
  emit(type); assert.equal(disposals, 1, `${type} must invalidate committed input`);
}
for (const part of ['scenario', 'request']) {
  arm(); calculationInput[part].revision = 1;
  emit('toram:optimization-preferences-changed');
  assert.equal(disposals, 1, `${part} changes must invalidate continuation`);
}
arm(); runtime.lastOptimizationResult = null;
emit('input', 'buildSettingName'); assert.equal(cancellations, 0, 'running work without a result must survive file name edits');
emit('input', 'wpnAtk'); assert.equal(cancellations, 1, 'running work must stop for weapon edits');
arm(); windowListeners.get('pagehide')(); assert.equal(disposals, 1, 'page exit must still release work');
arm();
context.ToramD4ExecutionAdapter.isRunning = () => false;
const beforeUpdateVersion = runtime.runVersion;
await context.ToramApp.optimizerUi.stopForUpdate();
assert.equal(cancellations, 1);
assert.equal(disposals, 1);
assert.equal(runtime.runVersion, beforeUpdateVersion + 1);
assert.equal(runtime.lastOptimizationRequest, null);
assert.equal(applyButton.disabled, true);
console.log('D4 native N5 UI continuation: PASS (resume, unrelated input preservation, calculation invalidation, page exit, approved update stop)');
