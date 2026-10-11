/* 최적화 화면의 렌더링·입력·비동기 제어. 계산 조립은 ToramApplication에 남긴다. */
(function (root) {
  'use strict';
  var initialized = false;

  function initialize() {
    if (initialized) return;
    var optimizer = root.ToramApp && root.ToramApp.optimizer;
    var support = optimizer && optimizer.uiSupport;
    if (!support) throw new Error('최적화 Application API가 준비되지 않았습니다.');
    initialized = true;
    populateRefineSelects();
    updateSubWeaponList();
    initAutocomplete();
    renderBanTags();
    addDefaultOptions('wpnOpts');
    addDefaultOptions('armOpts');
    var lastInputSignature = calculationInputSignature();

    var efficiencyTabs = document.getElementById('effTabs');
    if (efficiencyTabs) efficiencyTabs.addEventListener('click', function (event) {
      if (!event.target.classList.contains('eff-tab-btn')) return;
      efficiencyTabs.querySelectorAll('.eff-tab-btn').forEach(function (button) { button.classList.remove('active'); });
      event.target.classList.add('active');
      support.renderMarginalUtility(parseInt(event.target.getAttribute('data-unit'), 10));
    });

    var cancel = document.getElementById('crystaOptimizationCancel');
    if (cancel) cancel.addEventListener('click', function () {
      if (root.ToramCrystaOptimizationExecutionAdapter) root.ToramCrystaOptimizationExecutionAdapter.cancel('사용자가 계산을 취소했습니다.');
    });
    var pause = document.getElementById('crystaOptimizationPause');
    if (pause) pause.addEventListener('click', function () {
      if (root.ToramCrystaOptimizationExecutionAdapter && root.ToramCrystaOptimizationExecutionAdapter.pause()) { pause.disabled = true; pause.textContent = '정지 중…'; }
    });
    var continueButton = document.getElementById('crystaOptimizationContinue');
    if (continueButton) continueButton.addEventListener('click', function () { resumeCrystaOptimization(support, pause); });
    var applyRecommendation = document.getElementById('optimizationApplyRecommendedCrystas');
    if (applyRecommendation) applyRecommendation.addEventListener('click', function () { applyRecommendedCrystas(support, applyRecommendation); });
    var preciseButton = document.getElementById('optimizationRunPreciseOptimization');
    if (preciseButton) preciseButton.addEventListener('click', function () { document.dispatchEvent(new Event('toram:calculate')); });
    // Raw DOM input is not necessarily a calculation edit (file names, search,
    // unapplied requirement drafts). Share the build UI's input classification.
    ['input', 'change'].forEach(function (eventName) {
      document.addEventListener(eventName, function (event) {
        var buildUi = root.ToramBuildStateUi;
        if (buildUi && buildUi.isCalculationInput(event.target)) {
          lastInputSignature = calculationInputSignature();
          discardCrystaOptimizationContinuationForInputChange(support);
        }
      }, true);
    });
    // Committed changes also cover click-only edits and restored/imported builds.
    ['toram:persistent-state-changed', 'toram:skill-investments-changed', 'toram:active-buffs-changed', 'toram:combo-changed', 'toram:combo-hit-selected', 'toram:build-options-changed', 'toram:optimization-preferences-changed'].forEach(function (eventName) {
      document.addEventListener(eventName, function () {
        var signature = calculationInputSignature();
        // Some existing UI refreshes also emit save/change notifications.
        if (signature !== lastInputSignature) discardCrystaOptimizationContinuationForInputChange(support);
        lastInputSignature = signature;
      });
    });
    root.addEventListener('pagehide', disposeCrystaOptimizationWork);
  }

  function calculationInputSignature() {
    var store = root.ToramBuildDraftStore;
    return store ? JSON.stringify(store.syncFromUi()) : null;
  }

  function resumeCrystaOptimization(support, pause) {
    if (root.ToramUpdateInstallCoordinator && root.ToramUpdateInstallCoordinator.isLocked()) return;
    var state = support.runtime();
    if (!state.lastOptimizationRequest || !(root.ToramCrystaOptimizationExecutionAdapter && root.ToramCrystaOptimizationExecutionAdapter.hasContinuation())) return;
    var version = ++state.runVersion;
    support.updateProgress({ stage:'native-resume', status:'running', optimalityGap:null, native:true }, 'running', false);
    document.getElementById('globalEffTextBadge').textContent = '정밀 전역 계산 중…';
    function resumeUntilExact() {
      if (version !== support.runtime().runVersion) return Promise.resolve(null);
      return root.ToramCrystaOptimizationExecutionAdapter.resume({
        onProgress:function (progress) {
          if (version !== support.runtime().runVersion) return;
          if (pause) { pause.disabled = false; pause.textContent = '일시정지'; }
          support.updateProgress(progress, 'running', false);
        },
        onComplete:function (result, metadata) {
          var current = support.runtime();
          if (version === current.runVersion) support.renderGlobalResult(result, current.lastOptimizationRequest.currentEvaluation, current.lastOptimizationRequest.locks, metadata);
        }
      }, { timeLimitMs:30000, progressIntervalMs:32 }).then(function (result) {
        if (version !== support.runtime().runVersion || !result || !result.continuationId || !root.ToramCrystaOptimizationExecutionAdapter.hasContinuation()) return result;
        return result.status === 'bounded' || result.status === 'no-incumbent-yet'
          ? new Promise(function (resolve) { root.setTimeout(resolve, 0); }).then(resumeUntilExact)
          : result;
      });
    }
    resumeUntilExact().catch(function (error) {
      var current = support.runtime();
      if (version !== current.runVersion) return;
      support.renderGlobalResult({ status:'invalid', diagnostics:[{ code:error.code || 'OPTIMIZATION_RESUME_FAILED', message:error.message || '정밀 계산을 이어가지 못했습니다. 새 전역 계산을 시작해 주세요.' }] }, current.lastOptimizationRequest.currentEvaluation, current.lastOptimizationRequest.locks, { native:true });
    });
  }

  function discardCrystaOptimizationContinuationForInputChange(support) {
    var state = support.runtime();
    if (!state.lastOptimizationRequest) return;
    var hadContinuation = Boolean(root.ToramCrystaOptimizationExecutionAdapter && root.ToramCrystaOptimizationExecutionAdapter.hasContinuation && root.ToramCrystaOptimizationExecutionAdapter.hasContinuation());
    var hadResult = Boolean(state.lastOptimizationResult);
    state.lastOptimizationRequest = null;
    state.lastOptimizationResult = null;
    var applyRecommendation = document.getElementById('optimizationApplyRecommendedCrystas');
    if (applyRecommendation) { applyRecommendation.hidden = true; applyRecommendation.disabled = true; }
    state.runVersion++;
    if (root.ToramCrystaOptimizationExecutionAdapter) { root.ToramCrystaOptimizationExecutionAdapter.cancel('입력이 변경되어 보존된 정밀 계산을 폐기합니다.'); root.ToramCrystaOptimizationExecutionAdapter.disposeContinuation(); }
    if (hadContinuation || hadResult) {
      support.updateProgress({ status:'invalid', diagnostics:[{ code:'OPTIMIZATION_CONTINUATION_DISCARDED', message:'입력이 변경되어 이전 정밀 계산 세션을 폐기했습니다. 새 전역 계산을 시작해 주세요.' }] }, 'invalid', false);
      document.getElementById('globalEffTextBadge').textContent = '입력 변경됨';
    }
  }

  function applyRecommendedCrystas(support, button) {
    var state = support.runtime();
    try {
      if (!root.ToramCrystaOptimizationRecommendationApply) throw new Error('추천 크리스타 적용 기능이 준비되지 않았습니다.');
      var applied = root.ToramCrystaOptimizationRecommendationApply.apply(state.lastOptimizationResult);
      button.hidden = true;
      button.disabled = true;
      state.lastOptimizationResult = null;
      window.alert(applied.changed ? '추천 크리스타를 장비에 적용했습니다. 잠금은 그대로 유지됩니다.' : '변경할 수 있는 추천 크리스타가 없습니다. 잠금은 그대로 유지됩니다.');
    } catch (error) {
      window.alert(error && error.message ? error.message : '추천 크리스타를 장비에 적용하지 못했습니다.');
    }
  }

  function disposeCrystaOptimizationWork() {
    if (root.ToramCrystaOptimizationExecutionAdapter) { root.ToramCrystaOptimizationExecutionAdapter.cancel('창이 닫혀 계산을 취소합니다.'); root.ToramCrystaOptimizationExecutionAdapter.disposeContinuation(); }
  }

  root.ToramApp = root.ToramApp || {};
  async function stopForUpdate() {
    var support = root.ToramApp.optimizer.uiSupport;
    var state = support.runtime();
    state.runVersion++;
    var adapter = root.ToramCrystaOptimizationExecutionAdapter;
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
    support.updateProgress({ status:'cancelled' }, 'cancelled', false);
  }
  root.ToramApp.optimizerUi = Object.freeze({ initialize:initialize, stopForUpdate:stopForUpdate });
}(window));
