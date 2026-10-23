/* 기능 단위 UI의 공개 진입점. 기능 간 직접 DOM 호출을 이 경계 밖으로 제한한다. */
(function (root) {
  'use strict';
  var app = root.ToramApp || {};
  root.ToramUiFeatures = Object.freeze({
    build:app.buildUi,
    skills:root.ToramSkillUi,
    buffs:root.ToramActiveBuffs,
    combo:root.ToramComboUi,
    optimizer:app.optimizerUi,
    settings:root.ToramBuildFileUi,
    updates:root.ToramUpdateUi
  });
    var initialized = false;
    function bindUiEvents() {
        if (initialized) return;
        if (!app.buildUi || !app.optimizerUi || !app.optimizer) throw new Error('UI 기능 컨트롤러가 준비되지 않았습니다.');
        initialized = true;
        app.buildUi.bind();
        document.addEventListener('toram:preview', app.optimizer.runPreviewSafe);
        document.addEventListener('toram:calculate', app.optimizer.runCalculationSafe);
        app.optimizerUi.initialize();
    }

    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', bindUiEvents, { once: true });
    } else {
        bindUiEvents();
    }
}(window));
