/* 스테이터스·장비 입력 자동 저장/복원. 브라우저별 localStorage만 사용한다. */
(function () {
  'use strict';
  var storageKey = 'toram-auto-building.build-state.v1';
  var staticIds = [
    'charLevel', 'strBase', 'intBase', 'vitBase', 'agiBase', 'dexBase', 'crtBase',
    'bossLevel', 'bossDef', 'bossMdef', 'bossPhysResist', 'bossMagResist', 'bossCritResist',
    'mainWeaponType', 'wpnAtk', 'wpnRefine', 'wpnStab', 'subWeaponType', 'subAtk', 'subRefine', 'subStab', 'armorType',
    'cr_wpn_1', 'cr_wpn_2', 'cr_arm_1', 'cr_arm_2', 'cr_add_1', 'cr_add_2', 'cr_spc_1', 'cr_spc_2',
    'lock_wpn_1', 'lock_wpn_2', 'lock_arm_1', 'lock_arm_2', 'lock_add_1', 'lock_add_2', 'lock_spc_1', 'lock_spc_2'
  ];
  var optionContainers = ['wpnOpts', 'subOpts', 'armOpts', 'addOpts', 'spcOpts', 'buffOpts'];
  var restoring = false, pendingSave = null;

  function element(id) { return document.getElementById(id); }
  function readControl(control) { return control && control.type === 'checkbox' ? Boolean(control.checked) : (control ? control.value : undefined); }
  function writeControl(control, value) {
    if (!control || value === undefined || value === null) return;
    if (control.type === 'checkbox') control.checked = Boolean(value);
    else control.value = String(value);
  }
  function optionRows(containerId) {
    var container = element(containerId);
    if (!container) return [];
    return Array.prototype.slice.call(container.children).filter(function (child) { return child.classList && child.classList.contains('opt-row'); }).map(function (row) {
      var type = row.querySelector('.opt-type'), value = row.querySelector('.opt-val');
      return type && value ? { type:type.value, value:value.value } : null;
    }).filter(Boolean);
  }
  function snapshot() {
    var controls = {};
    staticIds.forEach(function (id) { controls[id] = readControl(element(id)); });
    var options = {};
    optionContainers.forEach(function (id) { options[id] = optionRows(id); });
    return { controls:controls, options:options, banned:window.bannedCrystas ? Object.keys(window.bannedCrystas) : [] };
  }
  function save() {
    if (restoring) return;
    try { window.localStorage.setItem(storageKey, JSON.stringify(snapshot())); } catch (_) { /* 저장 불가 환경 */ }
  }
  function queueSave() {
    if (restoring || pendingSave !== null) return;
    pendingSave = window.setTimeout(function () { pendingSave = null; save(); }, 0);
  }
  function restoreOptionRows(containerId, rows) {
    var container = element(containerId), ui = window.ToramApp && window.ToramApp.crystaUi;
    if (!container || !ui || !Array.isArray(rows)) return;
    Array.prototype.slice.call(container.children).filter(function (child) { return child.classList && child.classList.contains('opt-row'); }).forEach(function (row) { row.remove(); });
    rows.forEach(function (saved) {
      ui.addOptionRow(containerId);
      var row = container.lastElementChild;
      if (!row) return;
      writeControl(row.querySelector('.opt-type'), saved.type);
      writeControl(row.querySelector('.opt-val'), saved.value);
      row.querySelector('.opt-type').dispatchEvent(new Event('change', { bubbles:true }));
    });
  }
  function restoreBanned(values) {
    if (!Array.isArray(values) || !window.bannedCrystas) return;
    Object.keys(window.bannedCrystas).forEach(function (name) { delete window.bannedCrystas[name]; });
    values.forEach(function (name) { if (typeof name === 'string' && name) window.bannedCrystas[name] = true; });
    if (typeof window.renderBanTags === 'function') window.renderBanTags();
  }
  function restore() {
    var saved;
    try { saved = JSON.parse(window.localStorage.getItem(storageKey) || 'null'); } catch (_) { return; }
    if (!saved || typeof saved !== 'object') return;
    restoring = true;
    try {
      var controls = saved.controls || {}, ui = window.ToramApp && window.ToramApp.crystaUi;
      ['charLevel', 'strBase', 'intBase', 'vitBase', 'agiBase', 'dexBase', 'crtBase', 'bossLevel', 'bossDef', 'bossMdef', 'bossPhysResist', 'bossMagResist', 'bossCritResist', 'mainWeaponType', 'wpnAtk', 'wpnRefine', 'wpnStab', 'armorType'].forEach(function (id) { writeControl(element(id), controls[id]); });
      if (ui) ui.updateSubWeaponList();
      ['subWeaponType', 'subAtk', 'subRefine', 'subStab'].forEach(function (id) { writeControl(element(id), controls[id]); });
      if (ui) ui.onSubWeaponChange();
      ['cr_wpn_1', 'cr_wpn_2', 'cr_arm_1', 'cr_arm_2', 'cr_add_1', 'cr_add_2', 'cr_spc_1', 'cr_spc_2', 'lock_wpn_1', 'lock_wpn_2', 'lock_arm_1', 'lock_arm_2', 'lock_add_1', 'lock_add_2', 'lock_spc_1', 'lock_spc_2'].forEach(function (id) { writeControl(element(id), controls[id]); });
      optionContainers.forEach(function (id) { restoreOptionRows(id, saved.options && saved.options[id]); });
      restoreBanned(saved.banned);
      if (ui) ui.refreshAllCrystaInfo();
      var level = element('charLevel'); if (level) level.dispatchEvent(new Event('input', { bubbles:true }));
    } finally { restoring = false; }
  }
  function isRelevant(target) {
    if (!target || target.nodeType !== 1) return false;
    if (staticIds.indexOf(target.id) >= 0 || target.closest('.opt-row') || target.closest('.autocomplete-items')) return true;
    return Boolean(target.closest('[data-add-option], [data-action="add-ban"], .remove-option-row, .remove-ban-tag, .stat-easy-btn, #statusResetBtn'));
  }
  function initialize() {
    restore();
    document.addEventListener('input', function (event) { if (isRelevant(event.target)) queueSave(); });
    document.addEventListener('change', function (event) { if (isRelevant(event.target)) queueSave(); });
    document.addEventListener('click', function (event) { if (isRelevant(event.target)) queueSave(); });
  }
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', initialize, { once:true });
  else initialize();
}());
