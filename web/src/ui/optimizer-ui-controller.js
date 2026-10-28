import {buildStore} from '../application/build-draft-store.js';
import {application} from '../application/application-use-cases.js';
import {buildEvaluator} from '../calculation/build-evaluator.js';
import {statRegistry} from '../calculation/stat-registry.js';
import {problemCompiler} from '../optimization/problem-compiler.js';
import {crystaCatalog} from '../data/crysta-data.js';
import {cloneCtx} from '../calculation/calculator.js';
export function createOptimizerUi(document,app) {
  const root=document.defaultView;

  'use strict';
  var initialized = false, calculationQueued = false;
  var state = {runVersion:0,lastOptimizationRequest:null,lastOptimizationResult:null,lastOutcome:null,efficiency:null};
  function optimizationRuntime() { return state; }

  function initialize() {
    if (initialized) return;
    if (!app.optimizationResults) throw new Error('최적화 Application API가 준비되지 않았습니다.');
    initialized = true;
    app.crystaUi.initAutocomplete();
    app.crystaUi.renderBanTags();

    var efficiencyTabs = document.getElementById('effTabs');
    if (efficiencyTabs) efficiencyTabs.addEventListener('click', function (event) {
      if (!event.target.classList.contains('eff-tab-btn')) return;
      efficiencyTabs.querySelectorAll('.eff-tab-btn').forEach(function (button) { button.classList.remove('active'); });
      event.target.classList.add('active');
      renderMarginalUtility(parseInt(event.target.getAttribute('data-unit'), 10));
    });

    var cancel = document.getElementById('crystaOptimizationCancel');
    if (cancel) cancel.addEventListener('click', function () {
      if (app.execution) app.execution.cancel('사용자가 계산을 취소했습니다.');
    });
    var pause = document.getElementById('crystaOptimizationPause');
    if (pause) pause.addEventListener('click', function () {
      if (app.execution && app.execution.pause()) { pause.disabled = true; pause.textContent = '정지 중…'; }
    });
    var continueButton = document.getElementById('crystaOptimizationContinue');
    if (continueButton) continueButton.addEventListener('click', function () { resumeCrystaOptimization(pause); });
    var applyRecommendation = document.getElementById('optimizationApplyRecommendedCrystas');
    if (applyRecommendation) applyRecommendation.addEventListener('click', function () { applyRecommendedCrystas(applyRecommendation); });
    var preciseButton = document.getElementById('optimizationRunPreciseOptimization');
    if (preciseButton) preciseButton.addEventListener('click', function () { document.dispatchEvent(new Event('toram:calculate')); });
    document.addEventListener('toram:calculation-input-changed', function () { discardCrystaOptimizationContinuationForInputChange(); });
    root.addEventListener('pagehide', disposeCrystaOptimizationWork);
  }

  function resumeCrystaOptimization(pause) {
    if (app.updateController && app.updateController.isLocked()) return;
    var state = optimizationRuntime();
    if (!state.lastOptimizationRequest || !(app.execution && app.execution.hasContinuation())) return;
    var version = ++state.runVersion;
    updateCrystaOptimizationProgress({ stage:'resuming', status:'running', optimalityGap:null, resumable:true }, 'running', false);
    document.getElementById('globalEffTextBadge').textContent = '정밀 전역 계산 중…';
    function resumeUntilExact() {
      if (version !== optimizationRuntime().runVersion) return Promise.resolve(null);
      return app.execution.resume({
        onProgress:function (progress) {
          if (version !== optimizationRuntime().runVersion) return;
          if (pause) { pause.disabled = false; pause.textContent = '일시정지'; }
          updateCrystaOptimizationProgress(progress, 'running', false);
        },
        onComplete:function (result, metadata) {
          var current = optimizationRuntime();
          if (version === current.runVersion) acceptResult(result, current.lastOptimizationRequest.currentEvaluation, current.lastOptimizationRequest.locks, metadata);
        }
      }, { timeLimitMs:30000, progressIntervalMs:32 }).then(function (result) {
        if (version !== optimizationRuntime().runVersion || !result || !result.continuationId || !app.execution.hasContinuation()) return result;
        return result.status === 'bounded' || result.status === 'no-incumbent-yet'
          ? new Promise(function (resolve) { root.setTimeout(resolve, 0); }).then(resumeUntilExact)
          : result;
      });
    }
    resumeUntilExact().catch(function (error) {
      var current = optimizationRuntime();
      if (version !== current.runVersion) return;
      acceptResult({ status:'invalid', diagnostics:[{ code:error.code || 'OPTIMIZATION_RESUME_FAILED', message:error.message || '정밀 계산을 이어가지 못했습니다. 새 전역 계산을 시작해 주세요.' }] }, current.lastOptimizationRequest.currentEvaluation, current.lastOptimizationRequest.locks, { native:true });
    });
  }

  function discardCrystaOptimizationContinuationForInputChange() {
    var state = optimizationRuntime();
    if (!state.lastOptimizationRequest) return;
    var hadContinuation = Boolean(app.execution && app.execution.hasContinuation && app.execution.hasContinuation());
    var hadResult = Boolean(state.lastOptimizationResult);
    state.lastOptimizationRequest = null;
    state.lastOptimizationResult = null;
    var applyRecommendation = document.getElementById('optimizationApplyRecommendedCrystas');
    if (applyRecommendation) { applyRecommendation.hidden = true; applyRecommendation.disabled = true; }
    state.runVersion++;
    if (app.execution) { app.execution.cancel('입력이 변경되어 보존된 정밀 계산을 폐기합니다.'); app.execution.disposeContinuation(); }
    if (hadContinuation || hadResult) {
      updateCrystaOptimizationProgress({ status:'invalid', diagnostics:[{ code:'OPTIMIZATION_CONTINUATION_DISCARDED', message:'입력이 변경되어 이전 정밀 계산 세션을 폐기했습니다. 새 전역 계산을 시작해 주세요.' }] }, 'invalid', false);
      document.getElementById('globalEffTextBadge').textContent = '입력 변경됨';
    }
  }

  function applyRecommendedCrystas(button) {
    var state = optimizationRuntime();
    try {
      if (!app.recommendationApply) throw new Error('추천 크리스타 적용 기능이 준비되지 않았습니다.');
      var applied = app.recommendationApply.apply(state.lastOptimizationResult);
      button.hidden = true;
      button.disabled = true;
      state.lastOptimizationResult = null;
      root.alert(applied.changed ? '추천 크리스타를 장비에 적용했습니다. 잠금은 그대로 유지됩니다.' : '변경할 수 있는 추천 크리스타가 없습니다. 잠금은 그대로 유지됩니다.');
    } catch (error) {
      root.alert(error && error.message ? error.message : '추천 크리스타를 장비에 적용하지 못했습니다.');
    }
  }

  function disposeCrystaOptimizationWork() {
    if (app.execution) { app.execution.cancel('창이 닫혀 계산을 취소합니다.'); app.execution.disposeContinuation(); }
  }


  async function stopForUpdate() {
    var state = optimizationRuntime();
    state.runVersion++;
    var adapter = app.execution;
    if (adapter) {
      adapter.cancel('사용자 승인에 따라 업데이트를 위해 계산을 종료합니다.');
      var deadline = Date.now() + 10000;
      while (adapter.isRunning()) {
        if (Date.now() >= deadline) throw new Error('계산 종료를 확인하지 못했습니다. 잠시 후 업데이트를 다시 시도해 주세요.');
        await new Promise(function (resolve) { root.setTimeout(resolve, 50); });
      }
      await adapter.disposeContinuation();
    }
    state.lastOptimizationRequest = null;
    state.lastOptimizationResult = null;
    var apply = document.getElementById('optimizationApplyRecommendedCrystas');
    if (apply) { apply.hidden = true; apply.disabled = true; }
    updateCrystaOptimizationProgress({ status:'cancelled' }, 'cancelled', false);
  }
function queueCalculation(mode) {
            var updater = app.updateController;
            if (updater && updater.isLocked()) return;
            var updateEpoch = updater ? updater.epoch() : 0;
            if (!app.crystaUi.validateCrystaInputs()) return;
            app.tabs.revealResults();
            if (calculationQueued) return;
            calculationQueued = true;
            var execute = function () {
                calculationQueued = false;
                if (updater && (updater.isLocked() || updateEpoch !== updater.epoch())) return;
                try { runCalculation(mode); }
                catch(e) { console.error(e); alert('계산 실행 중 오류가 발생했습니다.\n\n(내부 에러: ' + e.message + ')'); }
            };
            // 탭 전환을 먼저 그린 다음 비용이 큰 크리스타 최적화를 수행한다.
            if (typeof root.requestAnimationFrame === 'function') root.requestAnimationFrame(execute);
            else root.setTimeout(execute, 0);
        }

function runCalculationSafe() { queueCalculation('precise'); }

function runPreviewSafe() { queueCalculation('preview'); }

function resultDamageScore(result) { return result.optimizationDamageFactor === undefined ? result.damageFactor : result.optimizationDamageFactor; }

function evaluateCrystaOptimizationBuild(baseCtx, crystas, scenarioSnapshot) {
            var buildSnapshot = buildEvaluator.createBuildSnapshot(baseCtx, crystas, { source:'current-ui' });
            var scenario = scenarioSnapshot || buildEvaluator.createScenarioSnapshot(baseCtx);
            return buildEvaluator.evaluate(buildSnapshot, scenario);
        }

function runCalculation(mode) {
            if (!application || typeof application.CreateCalculationSnapshot !== 'function') throw new Error('계산 유스케이스가 준비되지 않았습니다.');
            var calculationSnapshot = application.CreateCalculationSnapshot();
            var baseCtx = calculationSnapshot.baseContext;
            var preferences = app.optimizationPreferences;
            var requirements = preferences && typeof preferences.effectiveRequirements === 'function' ? preferences.effectiveRequirements(baseCtx) : undefined;
            var scenarioSnapshot = buildEvaluator ? buildEvaluator.createScenarioSnapshot(baseCtx, { requirements:requirements }) : null;

  var currentCrystas = calculationSnapshot.crystas;
  var currentEvaluation = evaluateCrystaOptimizationBuild(baseCtx,currentCrystas,scenarioSnapshot);
  state.lastOutcome = currentEvaluation;
  var locks = ['mainWeapon','armor','additional','special'].flatMap(function (slot) { return calculationSnapshot.build.equipment[slot].lockedCrystaSlots; });
  app.optimizationResults.current(calculationSnapshot,currentEvaluation,locks,mode);
  state.efficiency = {baseCtx:baseCtx,curCrystas:currentCrystas,curBaseDF:resultDamageScore(currentEvaluation.calculation),scenarioSnapshot:scenarioSnapshot};
  var activeTab = document.querySelector('.eff-tab-btn.active');
  renderMarginalUtility(activeTab ? parseInt(activeTab.getAttribute('data-unit'),10) : 1);
  startOptimization(mode,baseCtx,scenarioSnapshot,currentCrystas,locks,currentEvaluation);
}

function launchCrystaOptimizationWorker(problem, currentEvaluation, locks, version, timeLimitMs) {
            var callbacks = {
                onProgress:function (progress) { if (version === optimizationRuntime().runVersion) updateCrystaOptimizationProgress(progress, 'running', false); },
                onComplete:function (result, metadata) { if (version === optimizationRuntime().runVersion) acceptResult(result, currentEvaluation, locks, metadata); }
            };
            var options = { timeLimitMs:timeLimitMs, progressIntervalMs:32, maxParetoComparisons:1000000 };
            return app.execution.execute(problem, callbacks, options);
        }

function startOptimization(mode,baseCtx,scenarioSnapshot,currentCrystas,locks,currentEvaluation) {
  var version = ++state.runVersion, preview = mode !== 'precise';
  var adapter = app.execution;
  if (adapter) adapter.cancel('새 계산을 시작합니다.');
  state.lastOptimizationResult = null;
  // Install the request before yielding so an input edit can cancel preparation too.
  state.lastOptimizationRequest = {mode:mode,currentEvaluation:currentEvaluation,currentCrystas:currentCrystas.slice(),locks:locks.slice()};
  app.optimizationResults.preparing(mode);
  if (!preview) updateCrystaOptimizationProgress({stage:'preparing',status:'running',elapsedMs:0,evaluations:0,visitedNodes:0,optimalityGap:null},'running',false);
  root.setTimeout(function () {
    if (version !== state.runVersion) return;
    try {
      if (!adapter || !adapter.isAvailable()) throw new Error('CrystaOptimization 최적화 실행기가 연결되지 않았습니다.');
      var problem = compileCrystaOptimizationGlobalCrystaProblem(baseCtx,scenarioSnapshot,currentCrystas,locks);
      state.lastOptimizationRequest.problem = problem;
      var work = preview ? adapter.preview(problem,{},{}).then(function (result) { if (version === state.runVersion) acceptResult(result,currentEvaluation,locks,{preview:true}); })
        : launchCrystaOptimizationWorker(problem,currentEvaluation,locks,version,30000);
      work.catch(function (error) { if (version === state.runVersion) acceptResult({status:'invalid',diagnostics:[{code:preview ? 'PREVIEW_FAILED' : 'START_FAILED',message:error.message}]},currentEvaluation,locks,{preview:preview}); });
    } catch (error) {
      if (version === state.runVersion) acceptResult({status:'invalid',diagnostics:[{code:preview ? 'PREVIEW_FAILED' : 'START_FAILED',message:error.message}]},currentEvaluation,locks,{preview:preview});
    }
  },0);
}

function renderMarginalUtility(unit) {
            if (!state.efficiency) return;
            var baseCtx = state.efficiency.baseCtx;
            var curCrystas = state.efficiency.curCrystas;
            var curBaseDF = state.efficiency.curBaseDF;

            var u = unit || 1; // 1, 5, 10 단위

            var isMag = baseCtx.atkType === 'MAG';
            var pierceKey = isMag ? 'MAG_PIERCE' : 'PHYS_PIERCE';
            var pierceLabel = isMag ? '마법관통 %p (+' + u + '%)' : '물리관통 %p (+' + u + '%)';
            var rangeKey = baseCtx.rangeType === 'SHORT' ? 'SRW' : 'LRW';
            var rangeLabel = baseCtx.rangeType === 'SHORT' ? '근거리위력 %p (+' + u + '%)' : '원거리위력 %p (+' + u + '%)';

            var targets = [
                { key: 'ATKP', label: 'ATK %p (+' + u + '%)' },
                { key: 'ATK', label: 'ATK 깡공 (+' + u + ')' },
                { key: 'MATKP', label: 'MATK %p (+' + u + '%)' },
                { key: 'MATK', label: 'MATK 깡공 (+' + u + ')' },
                { key: 'CDMG_P', label: '크리티컬데미지 %p (+' + u + '%)' },
                { key: 'CDMG', label: '크리티컬데미지 (+' + u + ')' },
                { key: 'CRIT_P', label: '크리티컬확률 %p (+' + u + '%)' },
                { key: 'CRIT', label: '크리티컬확률 (+' + u + ')' },
                { key: 'STRP', label: 'STR %p (+' + u + '%)' },
                { key: 'DEXP', label: 'DEX %p (+' + u + '%)' },
                { key: 'INTP', label: 'INT %p (+' + u + '%)' },
                { key: 'WATKP', label: '무기ATK %p (+' + u + '%)' },
                { key: 'WATK', label: '무기ATK (+' + u + ')' },
                { key: pierceKey, label: pierceLabel },
                { key: rangeKey, label: rangeLabel },
                { key: 'ELEM_P', label: '속성에 유리 %p (+' + u + '%)' },
                { key: 'STABILITY', label: '안정률 %p (+' + u + '%)' }
            ];
            var usesUnsheathe = Boolean(baseCtx.chkIsUnsheathe || (baseCtx.activeBuildConversions || []).some(function(effect) { return effect && effect.conversion === 'unsheatheToAtk'; }));
            if (usesUnsheathe) {
                targets.push({ key: 'UNSHEATHEP', label: '발도위력 %p (+' + u + '%)' });
                targets.push({ key: 'UNSHEATHE', label: '발도위력 + (+' + u + ')' });
            }

            var keyMap = {
                'ATKP':'atkP', 'ATK':'atkF', 'MATKP':'matkP', 'MATK':'matkF',
                'CDMG_P':'cdmgP', 'CDMG':'cdmgF', 'CRIT_P':'critP', 'CRIT':'critF',
                'STRP':'strP', 'DEXP':'dexP', 'INTP':'intP',
                'WATKP':'watkP', 'WATK':'watkF', 'STABILITY':'stability', 'ELEM_P':'elemP',
                'PHYS_PIERCE':'physPierce', 'MAG_PIERCE':'magPierce', 'SRW':'srw', 'LRW':'lrw', 'UNSHEATHEP':'unsheatheP', 'UNSHEATHE':'unsheatheF'
            };

            var results = [];
            for(var i=0; i<targets.length; i++) {
                var t = targets[i];
                var testCtx = cloneCtx(baseCtx);
                testCtx[keyMap[t.key]] += u; // 1단위가 아닌 선택된 단위(u)만큼 더하기

                var testRes = evaluateCrystaOptimizationBuild(testCtx, curCrystas, state.efficiency.scenarioSnapshot).calculation;
                var gain = (curBaseDF && curBaseDF > 0) ? ((resultDamageScore(testRes) - curBaseDF) / curBaseDF * 100) : 0;

                if (gain >= 0.001) {
                    results.push({ label: t.label, gain: gain });
                }
            }

            app.optimizationResults.marginal(results);
        }

function compileCrystaOptimizationGlobalCrystaProblem(baseContext, scenarioSnapshot, currentCrystas, locks, options) {
    if (!problemCompiler) throw new Error('CrystaOptimization 전역 후보 컴파일러가 연결되지 않았습니다.');
    var settings = options || {};
    return problemCompiler.compileCrystaProblem({
        crystas: crystaCatalog.items, registry:statRegistry,
        baseContext:baseContext, scenarioSnapshot:scenarioSnapshot, currentCrystas:currentCrystas || [], locks:locks || [],
        banned:settings.banned || Object.fromEntries((buildStore.getScenario().optimizationPreferences.bannedCrystas || []).map(function (name) { return [name,true]; })), excluded:settings.excluded || [],
        keepLowerUpgrades:Boolean(settings.keepLowerUpgrades)
    });
}

function updateCrystaOptimizationProgress(progress,status,fromCache) {
  state.executionStatus = status || progress && progress.status || 'running';
  app.optimizationResults.progress(progress,status,fromCache);
}
function acceptResult(result,currentEvaluation,locks,metadata) {
  state.lastOptimizationResult = result && result.status !== 'cancelled' && result.bestBuild && result.outcomes ? result : null;
  state.executionStatus = result && result.status || 'invalid';
  app.optimizationResults.result(result,currentEvaluation,locks,metadata,state.lastOptimizationRequest && state.lastOptimizationRequest.currentCrystas || []);
}
  function getState() {
    return Object.freeze(structuredClone({runVersion:state.runVersion,calculationQueued:calculationQueued,executionStatus:state.executionStatus,lastOptimizationResult:state.lastOptimizationResult,lastOutcome:state.lastOutcome}));
  }
  return Object.freeze({initialize:initialize,stopForUpdate:stopForUpdate,runCalculationSafe:runCalculationSafe,runPreviewSafe:runPreviewSafe,compileGlobalCrystaProblem:compileCrystaOptimizationGlobalCrystaProblem,getState:getState});


}
