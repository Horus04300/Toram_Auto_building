/* 빌드 입력 UI의 이벤트 경계. 계산은 ToramApplication을 통해서만 요청한다. */
(function (root) {
  'use strict';
  var initialized = false;

  function bind() {
    if (initialized) return;
    var app = root.ToramApp = root.ToramApp || {};
    var crystaUi = app.crystaUi;
    if (!crystaUi) throw new Error('빌드 입력 UI가 준비되지 않았습니다.');
    initialized = true;
    document.querySelectorAll('[data-add-option]').forEach(function (button) {
      button.addEventListener('click', function () { crystaUi.addOptionRow(button.dataset.addOption); });
    });
    document.querySelector('[data-action="add-ban"]').addEventListener('click', crystaUi.addBanTag);
    document.querySelector('[data-action="main-weapon-change"]').addEventListener('change', function () {
      crystaUi.updateSubWeaponList();
      crystaUi.refreshAllCrystaInfo();
    });
    document.querySelector('[data-action="sub-weapon-change"]').addEventListener('change', crystaUi.onSubWeaponChange);
    document.querySelector('[data-action="armor-change"]').addEventListener('change', crystaUi.refreshAllCrystaInfo);
  }

  root.ToramApp = root.ToramApp || {};
  root.ToramApp.buildUi = Object.freeze({ bind:bind });
}(window));
