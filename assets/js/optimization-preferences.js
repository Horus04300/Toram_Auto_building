/* 결과 최적화 환경설정: 거리 판정, Utility 요구조건, 추천 제외 목록을 한 계약으로 저장한다. */
(function (root) {
  'use strict';

  var requirementKeys = ['maxHp', 'maxMp', 'amprBeforeDual', 'normalAttackCrit', 'aspd'];
  var requirementOverrides = {};
  var savedRangeOverride = null;
  var returnFocus = null;
  var resetPending = false;

  function clone(value) { return value === undefined ? undefined : JSON.parse(JSON.stringify(value)); }
  function own(object, key) { return Object.prototype.hasOwnProperty.call(object || {}, key); }
  function normalizeRange(value) { return value === 'SHORT' || value === 'LONG' ? value : null; }
  function normalizeRequirements(value) {
    var source = value && typeof value === 'object' ? value : {}, result = {};
    requirementKeys.forEach(function (key) {
      if (!own(source, key)) return;
      if (source[key] === null) { result[key] = null; return; }
      var number = Number(source[key]);
      if (Number.isFinite(number) && number >= 0) result[key] = number;
    });
    return result;
  }
  function crystaUi() { return root.ToramApp && root.ToramApp.crystaUi || null; }
  function bannedCrystas() {
    var ui = crystaUi();
    return ui && typeof ui.getBannedCrystas === 'function' ? ui.getBannedCrystas() : [];
  }
  function read() {
    return Object.freeze({
      rangeOverride:savedRangeOverride,
      requirements:Object.freeze(clone(requirementOverrides)),
      bannedCrystas:Object.freeze(bannedCrystas().slice())
    });
  }
  function effectiveRequirements(baseContext) {
    var evaluator = root.ToramBuildEvaluator;
    var defaults = evaluator && typeof evaluator.defaultRequirements === 'function' ? evaluator.defaultRequirements(baseContext || {}) : {};
    return Object.assign({}, defaults, clone(requirementOverrides));
  }
  function notifyChanged() {
    document.dispatchEvent(new CustomEvent('toram:optimization-preferences-changed'));
    document.dispatchEvent(new CustomEvent('toram:persistent-state-changed'));
  }
  function rangeControls() {
    return { short:document.getElementById('comboRangeShort'), long:document.getElementById('comboRangeLong'), status:document.getElementById('comboRangeStatus') };
  }
  function renderRangeControls() {
    var controls = rangeControls();
    if (controls.short) controls.short.checked = savedRangeOverride === 'SHORT';
    if (controls.long) controls.long.checked = savedRangeOverride === 'LONG';
    if (controls.status) controls.status.textContent = savedRangeOverride === 'SHORT' ? '근거리 강제 적용' : savedRangeOverride === 'LONG' ? '원거리 강제 적용' : '둘 다 해제: 스킬 기본값';
  }
  function bindRangeControls() {
    var controls = rangeControls();
    if (!controls.short || !controls.long || controls.short.dataset.bound === 'true') { renderRangeControls(); return; }
    controls.short.dataset.bound = controls.long.dataset.bound = 'true';
    [controls.short, controls.long].forEach(function (control) {
      control.addEventListener('change', function () {
        if (control.checked) {
          if (control === controls.short) controls.long.checked = false;
          else controls.short.checked = false;
        }
        savedRangeOverride = controls.short.checked ? 'SHORT' : controls.long.checked ? 'LONG' : null;
        renderRangeControls();
        notifyChanged();
      });
    });
    renderRangeControls();
  }
  function restore(value) {
    var source = value && typeof value === 'object' ? value : {};
    savedRangeOverride = normalizeRange(source.rangeOverride);
    requirementOverrides = normalizeRequirements(source.requirements);
    var ui = crystaUi();
    if (ui && typeof ui.restoreBannedCrystas === 'function') ui.restoreBannedCrystas(Array.isArray(source.bannedCrystas) ? source.bannedCrystas : null);
    renderRangeControls();
  }
  function currentBaseContext() {
    try {
      var application = root.ToramApplication;
      return application && typeof application.CreateCalculationSnapshot === 'function' ? application.CreateCalculationSnapshot().baseContext : {};
    } catch (_) { return {}; }
  }
  function requirementRows() { return Array.prototype.slice.call(document.querySelectorAll('[data-optimization-requirement]')); }
  function renderRequirementEditor(useDefaults) {
    var defaults = root.ToramBuildEvaluator && root.ToramBuildEvaluator.defaultRequirements(currentBaseContext()) || {};
    var editorOverrides = useDefaults ? {} : requirementOverrides;
    var effective = Object.assign({}, defaults, editorOverrides);
    requirementRows().forEach(function (row) {
      var key = row.dataset.optimizationRequirement, enabled = row.querySelector('.optimization-requirement-enabled'), input = row.querySelector('.optimization-requirement-value'), note = row.querySelector('.optimization-requirement-default');
      var value = effective[key], fallback = Number(row.dataset.fallback) || 0;
      enabled.checked = value !== null && value !== undefined;
      input.disabled = !enabled.checked;
      input.value = String(value === null || value === undefined ? fallback : value);
      note.textContent = own(editorOverrides, key) ? '사용자 설정' : (defaults[key] === null || defaults[key] === undefined ? '기본: 제한 없음' : '기본: ' + Number(defaults[key]).toLocaleString());
    });
    var status = document.getElementById('optimizationRequirementsStatus');
    if (status) status.textContent = '';
  }
  function closeRequirements() {
    var overlay = document.getElementById('optimizationRequirementsOverlay');
    if (overlay) overlay.hidden = true;
    if (returnFocus && typeof returnFocus.focus === 'function') returnFocus.focus();
    returnFocus = null;
  }
  function openRequirements() {
    var overlay = document.getElementById('optimizationRequirementsOverlay');
    if (!overlay) return;
    returnFocus = document.activeElement;
    resetPending = false;
    renderRequirementEditor();
    overlay.hidden = false;
    var first = overlay.querySelector('.optimization-requirement-enabled');
    if (first) first.focus();
  }
  function applyRequirementEditor() {
    var next = {}, invalid = null;
    requirementRows().forEach(function (row) {
      var key = row.dataset.optimizationRequirement, enabled = row.querySelector('.optimization-requirement-enabled'), input = row.querySelector('.optimization-requirement-value');
      if (!enabled.checked) { next[key] = null; return; }
      var value = Number(input.value);
      if (!Number.isFinite(value) || value < 0) { invalid = invalid || input; return; }
      next[key] = value;
    });
    if (invalid) {
      var status = document.getElementById('optimizationRequirementsStatus');
      if (status) status.textContent = '요구 수치는 0 이상의 숫자로 입력하세요.';
      invalid.focus();
      return;
    }
    requirementOverrides = resetPending ? {} : next;
    resetPending = false;
    notifyChanged();
    closeRequirements();
  }
  function resetRequirements() {
    resetPending = true;
    renderRequirementEditor(true);
    var status = document.getElementById('optimizationRequirementsStatus');
    if (status) status.textContent = '스킬과 거리 판정에 따른 기본 요구조건으로 복원했습니다.';
  }
  function initialize() {
    var open = document.getElementById('optimizationRequirementsButton');
    var overlay = document.getElementById('optimizationRequirementsOverlay');
    if (open) open.addEventListener('click', openRequirements);
    if (overlay) {
      overlay.querySelector('#optimizationRequirementsClose').addEventListener('click', closeRequirements);
      overlay.querySelector('#optimizationRequirementsCancel').addEventListener('click', closeRequirements);
      overlay.querySelector('#optimizationRequirementsApply').addEventListener('click', applyRequirementEditor);
      overlay.querySelector('#optimizationRequirementsReset').addEventListener('click', resetRequirements);
      overlay.addEventListener('click', function (event) { if (event.target === overlay) closeRequirements(); });
      requirementRows().forEach(function (row) {
        var enabled = row.querySelector('.optimization-requirement-enabled'), input = row.querySelector('.optimization-requirement-value');
        enabled.addEventListener('change', function () { resetPending = false; input.disabled = !enabled.checked; });
        input.addEventListener('input', function () { resetPending = false; });
      });
      document.addEventListener('keydown', function (event) { if (event.key === 'Escape' && !overlay.hidden) closeRequirements(); });
    }
  }

  root.ToramOptimizationPreferences = Object.freeze({ read:read, restore:restore, effectiveRequirements:effectiveRequirements, bindRangeControls:bindRangeControls });
  document.dispatchEvent(new CustomEvent('toram:optimization-preferences-changed'));
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', initialize, { once:true }); else initialize();
}(window));
