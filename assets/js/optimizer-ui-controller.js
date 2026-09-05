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

    var efficiencyTabs = document.getElementById('effTabs');
    if (efficiencyTabs) efficiencyTabs.addEventListener('click', function (event) {
      if (!event.target.classList.contains('eff-tab-btn')) return;
      efficiencyTabs.querySelectorAll('.eff-tab-btn').forEach(function (button) { button.classList.remove('active'); });
      event.target.classList.add('active');
      support.renderMarginalUtility(parseInt(event.target.getAttribute('data-unit'), 10));
    });

    var cancel = document.getElementById('d4OptimizationCancel');
    if (cancel) cancel.addEventListener('click', function () {
      if (root.ToramD4ExecutionAdapter) root.ToramD4ExecutionAdapter.cancel('사용자가 계산을 취소했습니다.');
    });
    var pause = document.getElementById('d4OptimizationPause');
    if (pause) pause.addEventListener('click', function () {
      if (root.ToramD4ExecutionAdapter && root.ToramD4ExecutionAdapter.pause()) { pause.disabled = true; pause.textContent = '정지 중…'; }
    });
    var continueButton = document.getElementById('d4OptimizationContinue');
    if (continueButton) continueButton.addEventListener('click', function () { resumeD4(support, pause); });
    var applyRecommendation = document.getElementById('d4ApplyRecommendedCrystas');
    if (applyRecommendation) applyRecommendation.addEventListener('click', function () { applyRecommendedCrystas(support, applyRecommendation); });
    var preciseButton = document.getElementById('d4RunPreciseOptimization');
    if (preciseButton) preciseButton.addEventListener('click', function () { document.dispatchEvent(new Event('toram:calculate')); });
    document.addEventListener('input', function (event) { if (!(event.target && event.target.closest && event.target.closest('#optimizationRequirementsOverlay'))) discardD4ContinuationForInputChange(support); }, true);
    document.addEventListener('change', function (event) { if (!(event.target && event.target.closest && event.target.closest('#optimizationRequirementsOverlay'))) discardD4ContinuationForInputChange(support); }, true);
    document.addEventListener('toram:optimization-preferences-changed', function () { discardD4ContinuationForInputChange(support); });
    root.addEventListener('pagehide', disposeD4Work);
  }

  function resumeD4(support, pause) {
    var state = support.runtime();
    if (!state.lastOptimizationRequest || !(root.ToramD4ExecutionAdapter && root.ToramD4ExecutionAdapter.hasContinuation())) return;
    var version = ++state.runVersion;
    support.updateProgress({ stage:'native-resume', status:'running', optimalityGap:null, native:true }, 'running', false);
    document.getElementById('globalEffTextBadge').textContent = '정밀 전역 계산 중…';
    function resumeUntilExact() {
      return root.ToramD4ExecutionAdapter.resume({
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
        if (version !== support.runtime().runVersion || !result || !result.continuationId || !root.ToramD4ExecutionAdapter.hasContinuation()) return result;
        return result.status === 'bounded' || result.status === 'no-incumbent-yet'
          ? new Promise(function (resolve) { root.setTimeout(resolve, 0); }).then(resumeUntilExact)
          : result;
      });
    }
    resumeUntilExact().catch(function (error) {
      var current = support.runtime();
      if (version !== current.runVersion) return;
      support.renderGlobalResult({ status:'invalid', diagnostics:[{ code:error.code || 'D4_RESUME_FAILED', message:error.message || '정밀 계산을 이어가지 못했습니다. 새 전역 계산을 시작해 주세요.' }] }, current.lastOptimizationRequest.currentEvaluation, current.lastOptimizationRequest.locks, { native:true });
    });
  }

  function discardD4ContinuationForInputChange(support) {
    var state = support.runtime();
    if (!state.lastOptimizationRequest) return;
    var hadContinuation = Boolean(root.ToramD4ExecutionAdapter && root.ToramD4ExecutionAdapter.hasContinuation && root.ToramD4ExecutionAdapter.hasContinuation());
    var hadResult = Boolean(state.lastOptimizationResult);
    state.lastOptimizationRequest = null;
    state.lastOptimizationResult = null;
    var applyRecommendation = document.getElementById('d4ApplyRecommendedCrystas');
    if (applyRecommendation) { applyRecommendation.hidden = true; applyRecommendation.disabled = true; }
    state.runVersion++;
    if (root.ToramD4ExecutionAdapter) { root.ToramD4ExecutionAdapter.cancel('입력이 변경되어 보존된 정밀 계산을 폐기합니다.'); root.ToramD4ExecutionAdapter.disposeContinuation(); }
    if (hadContinuation || hadResult) {
      support.updateProgress({ status:'invalid', diagnostics:[{ code:'D4_CONTINUATION_DISCARDED', message:'입력이 변경되어 이전 정밀 계산 세션을 폐기했습니다. 새 전역 계산을 시작해 주세요.' }] }, 'invalid', false);
      document.getElementById('globalEffTextBadge').textContent = '입력 변경됨';
    }
  }

  function applyRecommendedCrystas(support, button) {
    var state = support.runtime();
    try {
      if (!root.ToramD4RecommendationApply) throw new Error('추천 크리스타 적용 기능이 준비되지 않았습니다.');
      var applied = root.ToramD4RecommendationApply.apply(state.lastOptimizationResult);
      button.hidden = true;
      button.disabled = true;
      state.lastOptimizationResult = null;
      window.alert(applied.changed ? '추천 크리스타를 장비에 적용했습니다. 잠금은 그대로 유지됩니다.' : '변경할 수 있는 추천 크리스타가 없습니다. 잠금은 그대로 유지됩니다.');
    } catch (error) {
      window.alert(error && error.message ? error.message : '추천 크리스타를 장비에 적용하지 못했습니다.');
    }
  }

  function disposeD4Work() {
    if (root.ToramD4ExecutionAdapter) { root.ToramD4ExecutionAdapter.cancel('창이 닫혀 계산을 취소합니다.'); root.ToramD4ExecutionAdapter.disposeContinuation(); }
  }

  root.ToramApp = root.ToramApp || {};
  root.ToramApp.optimizerUi = Object.freeze({ initialize:initialize });
}(window));
