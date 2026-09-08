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
}(window));
