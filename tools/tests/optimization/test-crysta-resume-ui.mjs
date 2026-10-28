import assert from 'node:assert/strict';
import {resolve} from 'node:path';

import {buildStore,initializeBuildEditor} from '../../../web/src/application/build-draft-store.js';
import {importWithMocks} from '../../support/import-with-mocks.mjs';
// Execute the actual UI handlers: presentation-only input must keep costly work.
const listeners = new Map(), windowListeners = new Map();
const snapshot = () => context.ToramApp.optimizer.getState();
let reads = 0, optionAmount = 0;
const nodes = new Map(), pending = [], clicks = new Map();
function node(id) {
  if (!nodes.has(id)) nodes.set(id,{id,nodeType:1,value:'0',checked:false,closest:() => null,addEventListener(type,handler) {if(type === 'click') clicks.set(id,handler);},querySelectorAll:() => []});
  return nodes.get(id);
}
const optionRow = {parentElement:{id:'buffOpts'},classList:{contains:() => false},closest:() => null,
  querySelector:selector => ({value:selector === '.opt-type' ? 'ATK' : String(optionAmount)})};
node('buffOpts').querySelectorAll = () => [optionRow];
let cancellations = 0, disposals = 0;
const badge = {}, applyButton = { addEventListener() {} };
const documentRef = {
  readyState:'loading',
  querySelector:() => null,
  getElementById(id) { reads++; return id === 'globalEffTextBadge' ? badge : id === 'optimizationApplyRecommendedCrystas' ? applyButton : node(id); },
  dispatchEvent(event) { emit(event.type); return true; },
  addEventListener(type, handler) { if (!listeners.has(type)) listeners.set(type, []); listeners.get(type).push(handler); }
};
const context = {
  document:documentRef, window:null,
  addEventListener(type, handler) { windowListeners.set(type, handler); },
  initAutocomplete() {}, renderBanTags() {},
  ToramApp:{ optimizationResults:{current() {},preparing() {},progress() {},result() {},marginal() {}} },
  structuredClone,
  cloneCtx:structuredClone,
  ToramApplication:{ CreateCalculationSnapshot:() => ({...context.ToramBuildDraftStore.read(),baseContext:{},crystas:[]}) },
  ToramBuildEvaluator:{createScenarioSnapshot:() => ({}),createBuildSnapshot:() => ({}),evaluate:() => ({calculation:{damageFactor:1}})},
  ToramCrystaOptimizationProblemCompiler:{compileCrystaProblem:() => ({schema:'fixture'})},
  requestAnimationFrame:callback => callback(),
  CustomEvent:class { constructor(type,options) { this.type=type; this.detail=options?.detail; } },
  setTimeout(callback) { pending.push(callback); return pending.length; },
  ToramCrystaOptimizationExecutionAdapter:{ isAvailable:() => true, preview:async () => ({status:'bounded',bestBuild:{packages:[]},outcomes:{}}), hasContinuation:() => true, cancel() { cancellations++; }, disposeContinuation() { disposals++; } }
};
context.window = context;
documentRef.defaultView=context;
context.ToramBuildDraftStore=buildStore;
initializeBuildEditor(documentRef,context.ToramApp);
const {createOptimizerUi}=await importWithMocks(new URL('../../../web/src/ui/optimizer-ui-controller.js',import.meta.url),{
 'crysta-data.js':{crystaCatalog:{items:[]}},
 'application-use-cases.js':{application:context.ToramApplication},
 'build-evaluator.js':{buildEvaluator:context.ToramBuildEvaluator},
 'problem-compiler.js':{problemCompiler:context.ToramCrystaOptimizationProblemCompiler}
});
let validInputs=true,reveals=0;
Object.assign(context.ToramApp,{
 execution:context.ToramCrystaOptimizationExecutionAdapter,
 crystaUi:{initAutocomplete(){},renderBanTags(){},validateCrystaInputs:()=>validInputs},
 tabs:{revealResults() {reveals++;}}
});
context.ToramApp.optimizerUi=context.ToramApp.optimizer=createOptimizerUi(documentRef,context.ToramApp);
context.ToramApp.optimizer.initialize();
validInputs=false;
const beforeInvalid=snapshot().runVersion;
context.ToramApp.optimizer.runPreviewSafe();
assert.equal(reveals,0,'Invalid inputs do not switch to the result tab');
assert.equal(snapshot().runVersion,beforeInvalid,'Invalid inputs do not start work');
validInputs=true;
async function arm() {
  context.ToramApp.optimizer.runPreviewSafe();
  while (pending.length) pending.shift()();
  await Promise.resolve(); await Promise.resolve();
  applyButton.hidden = false; applyButton.disabled = false;
  cancellations = 0; disposals = 0;
}
function emit(type, id = '', isOption = false) {
  const target = id ? node(id) : {id:'',nodeType:1,closest:selector => isOption && selector === '.opt-row' ? optionRow : null};
  for (const handler of listeners.get(type) || []) handler({ target });
}
for (const type of ['input', 'change']) {
  for (const id of ['buildSettingName', 'buildBackupName', 'buildSettingList', 'buildSettingImport', 'banInput', 'skillSearch', 'optimizationRequirementsDraft', 'unrelatedFutureInput']) {
    await arm(); const request = snapshot().lastOptimizationRequest, result = snapshot().lastOptimizationResult, version = snapshot().runVersion;
    const beforeReads = reads, beforeRevision = context.ToramBuildDraftStore.revision();
    emit(type, id);
    assert.equal(reads,beforeReads,'Presentation input must not collect the Build from the DOM');
    assert.equal(context.ToramBuildDraftStore.revision(),beforeRevision);
    assert.equal(cancellations, 0, `${type} on ${id} must preserve running work`);
    assert.equal(disposals, 0, `${id} must preserve continuation`);
    assert.equal(snapshot().lastOptimizationRequest, request);
    assert.deepEqual(snapshot().lastOptimizationResult, result);
    assert.equal(snapshot().runVersion, version);
    assert.equal(applyButton.hidden, false);
  }
  for (const id of ['charLevel', 'strBase', 'bossDef', 'mainWeaponType', 'wpnAtk', 'subStab', 'armorType', 'cr_wpn_1', 'lock_spc_2']) {
    await arm(); node(id).value = String(Number(node(id).value)+1); node(id).checked = !node(id).checked; emit(type, id);
    assert.equal(cancellations, 1, `${type} on ${id} must cancel stale work`);
    assert.equal(disposals, 1);
        assert.equal(snapshot().lastOptimizationResult, null);
    assert.equal(applyButton.disabled, true);
    emit(type, id); assert.equal(cancellations, 1, 'duplicate events must not cancel twice');
  }
  await arm(); optionAmount++; emit(type, '', true); assert.equal(cancellations, 1, 'dynamic option rows affect calculations');
}
for (const type of ['toram:persistent-state-changed', 'toram:skill-investments-changed', 'toram:active-buffs-changed', 'toram:combo-changed', 'toram:build-options-changed', 'toram:optimization-preferences-changed']) {
  await arm(); emit(type); assert.equal(disposals, 0, `${type} without an input change must preserve work`);
}
for (const [type,field,api] of [
  ['toram:skill-investments-changed','skillLevels','commitBuild'],
  ['toram:active-buffs-changed','activeBuffs','commitBuild'],
  ['toram:combo-changed','combo','commitBuild'],
  ['toram:optimization-preferences-changed','optimizationPreferences','commitScenario']
]) {
  await arm(); const value = field === 'combo' ? [{skillId:'fixture'}] : {fixture:1};
  context.ToramBuildDraftStore[api]({[field]:value});
  assert.equal(disposals,1,`${field} commit must invalidate continuation once`);
  context.ToramBuildDraftStore[api]({[field]:value});
  assert.equal(disposals,1,'Repeated same commit must preserve revision');
}
await arm();
emit('input', 'buildSettingName'); assert.equal(cancellations, 0, 'running work without a result must survive file name edits');
node('wpnAtk').value = '100'; emit('input', 'wpnAtk'); assert.equal(cancellations, 1, 'running work must stop for weapon edits');
await arm(); windowListeners.get('pagehide')(); assert.equal(disposals, 1, 'page exit must still release work');
await arm();
context.ToramCrystaOptimizationExecutionAdapter.isRunning = () => false;
const beforeUpdateVersion = snapshot().runVersion;
await context.ToramApp.optimizerUi.stopForUpdate();
assert.equal(cancellations, 1);
assert.equal(disposals, 1);
assert.equal(snapshot().runVersion, beforeUpdateVersion + 1);
assert.equal(applyButton.disabled, true);
// Real continuation callbacks keep one frontier, and stale callbacks never overwrite a newer run.
let resumes = 0;
context.ToramCrystaOptimizationExecutionAdapter.resume = async callbacks => {
  resumes++;
  const result = {status:resumes === 1 ? 'bounded' : 'exact',continuationId:resumes === 1 ? 'same-frontier' : null,bestBuild:{packages:[]},outcomes:{}};
  callbacks.onProgress({status:'running'}); callbacks.onComplete(result,{}); return result;
};
context.setTimeout = callback => {callback(); return 0;};
await arm();
clicks.get('crystaOptimizationContinue')();
for (let i=0;i<12;i++) await Promise.resolve();
assert.equal(resumes,2,'Bounded resume must automatically continue the same frontier');
assert.equal(snapshot().lastOptimizationResult.status,'exact');
const detached = snapshot(); detached.lastOptimizationResult.outcomes.changed = true;
assert.equal(snapshot().lastOptimizationResult.outcomes.changed,undefined,'Diagnostic state cannot mutate the owner');
const completions = [];
context.ToramCrystaOptimizationExecutionAdapter.preview = () => new Promise(resolve => completions.push(resolve));
await arm(); await arm();
completions[1]({status:'heuristic',score:2,bestBuild:{},outcomes:{}});
await Promise.resolve(); await Promise.resolve();
completions[0]({status:'heuristic',score:1,bestBuild:{},outcomes:{}});
await Promise.resolve(); await Promise.resolve();
assert.equal(snapshot().lastOptimizationResult.score,2,'An old response must never replace a newer result');
context.setTimeout = callback => {pending.push(callback);return pending.length;};
const beforePreparation = completions.length;
context.ToramApp.optimizer.runPreviewSafe();
context.ToramBuildDraftStore.commitBuild({character:{level:999,attributes:{}}});
while (pending.length) pending.shift()();
assert.equal(completions.length,beforePreparation,'An input edit must also discard work before asynchronous preparation starts');
assert.equal(snapshot().lastOptimizationResult,null);
console.log('Recommendation lifecycle: PASS (Store revision, unrelated edits, duplicate commits, automatic resume, stale response, preparation cancellation, detached diagnostics, page exit, update stop)');
