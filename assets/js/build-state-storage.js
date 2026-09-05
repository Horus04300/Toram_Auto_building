/* R6 빌드 UI 어댑터. 저장은 ToramSettingsRepository만 담당한다. */
(function (root) {
  'use strict';
  var staticIds = ['charLevel','strBase','intBase','vitBase','agiBase','dexBase','crtBase','bossLevel','bossDef','bossMdef','bossPhysResist','bossMagResist','bossCritResist','mainWeaponType','wpnAtk','wpnRefine','wpnStab','subWeaponType','subAtk','subRefine','subStab','armorType','cr_wpn_1','cr_wpn_2','cr_arm_1','cr_arm_2','cr_add_1','cr_add_2','cr_spc_1','cr_spc_2','lock_wpn_1','lock_wpn_2','lock_arm_1','lock_arm_2','lock_add_1','lock_add_2','lock_spc_1','lock_spc_2'];
  var slotSpecs = {
    mainWeapon:{ type:'mainWeaponType', attack:'wpnAtk', refinement:'wpnRefine', stability:'wpnStab', options:'wpnOpts', crystas:['cr_wpn_1','cr_wpn_2'], locks:['lock_wpn_1','lock_wpn_2'] },
    subWeapon:{ type:'subWeaponType', attack:'subAtk', refinement:'subRefine', stability:'subStab', options:'subOpts' },
    armor:{ type:'armorType', options:'armOpts', crystas:['cr_arm_1','cr_arm_2'], locks:['lock_arm_1','lock_arm_2'] },
    additional:{ options:'addOpts', crystas:['cr_add_1','cr_add_2'], locks:['lock_add_1','lock_add_2'] },
    special:{ options:'spcOpts', crystas:['cr_spc_1','cr_spc_2'], locks:['lock_spc_1','lock_spc_2'] }
  };
  var restoring = false, pending = null;
  function element(id) { return document.getElementById(id); }
  function write(id, value) { var node = element(id); if (!node || value === undefined || value === null) return; if (node.type === 'checkbox') node.checked = Boolean(value); else node.value = String(value); }
  function restoreOptions(id, options) {
    var container = element(id), ui = root.ToramApp && root.ToramApp.crystaUi;
    if (!container || !ui) return;
    Array.prototype.slice.call(container.querySelectorAll('.opt-row')).forEach(function (row) { row.remove(); });
    (options || []).forEach(function (option) {
      ui.addOptionRow(id);
      var row = container.lastElementChild, type = row && row.querySelector('.opt-type'), value = row && row.querySelector('.opt-val');
      if (type) type.value = option.key === 'UNSHEATHE' ? 'UNSHEATHEP' : String(option.key || '');
      if (value) value.value = String(option.value === undefined ? 0 : option.value);
      if (type) type.dispatchEvent(new Event('change', { bubbles:true }));
    });
  }
  function restoreSlot(name, piece) {
    var spec = slotSpecs[name], data = piece || {};
    if (!spec) return;
    if (spec.type) write(spec.type, data.type);
    if (spec.attack) write(spec.attack, data.attack);
    if (spec.refinement) write(spec.refinement, data.refinement);
    if (spec.stability) write(spec.stability, data.stability);
    (spec.crystas || []).forEach(function (id, index) { write(id, data.crystas && data.crystas[index]); });
    (spec.locks || []).forEach(function (id, index) { write(id, data.lockedCrystaSlots && data.lockedCrystaSlots[index]); });
    restoreOptions(spec.options, data.options);
  }
  function restoreSession(session) {
    if (!session || !session.build) return;
    var build = session.build, target = session.scenario && session.scenario.target || {}, attributes = build.character && build.character.attributes || {};
    restoring = true;
    try {
      write('charLevel', build.character && build.character.level);
      ['STR','INT','VIT','AGI','DEX','CRT'].forEach(function (name) { write(name.toLowerCase() + 'Base', attributes[name]); });
      ['bossLevel','bossDef','bossMdef','bossPhysResist','bossMagResist','bossCritResist'].forEach(function (id) { write(id, target[id]); });
      restoreSlot('mainWeapon', build.equipment && build.equipment.mainWeapon);
      var ui = root.ToramApp && root.ToramApp.crystaUi; if (ui) ui.updateSubWeaponList();
      restoreSlot('subWeapon', build.equipment && build.equipment.subWeapon); restoreSlot('armor', build.equipment && build.equipment.armor); restoreSlot('additional', build.equipment && build.equipment.additional); restoreSlot('special', build.equipment && build.equipment.special);
      if (root.ToramSkillUi && root.ToramSkillUi.restore) root.ToramSkillUi.restore(build.skillLevels || {});
      if (root.ToramActiveBuffs && root.ToramActiveBuffs.restore) root.ToramActiveBuffs.restore(build.activeBuffs || {});
      restoreOptions('buffOpts', build.externalOptions);
      if (root.ToramComboUi && root.ToramComboUi.restore) root.ToramComboUi.restore(build.combo || []);
      if (root.ToramOptimizationPreferences && root.ToramOptimizationPreferences.restore) root.ToramOptimizationPreferences.restore(session.scenario && session.scenario.optimizationPreferences);
      if (ui) { ui.onSubWeaponChange(); ui.refreshAllCrystaInfo(); }
      var level = element('charLevel'); if (level) level.dispatchEvent(new Event('input', { bubbles:true }));
    } finally { restoring = false; if (root.ToramBuildDraftStore) root.ToramBuildDraftStore.syncFromUi(); }
  }
  function relevant(target) { if (!target || target.nodeType !== 1) return false; if (staticIds.indexOf(target.id) >= 0 || target.closest('.opt-row') || target.closest('.autocomplete-items')) return true; return Boolean(target.closest('[data-add-option], [data-action="add-ban"], .remove-option-row, .remove-ban-tag, .stat-easy-btn, #statusResetBtn')); }
  function notify() { if (restoring || pending !== null) return; pending = root.setTimeout(function () { pending = null; document.dispatchEvent(new CustomEvent('toram:persistent-state-changed')); }, 0); }
  function initialize() { ['input','change','click'].forEach(function (type) { document.addEventListener(type, function (event) { if (relevant(event.target)) notify(); }); }); }
  root.ToramBuildStateUi = Object.freeze({ restoreSession:restoreSession });
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', initialize, { once:true }); else initialize();
}(window));
