// Confirmed inputs are usable without a browser. DOM binding is initialized once by the calculator page.
let state = {build:null,scenario:null,request:{selectedSkillId:null,selectedHitId:null,overrides:{}}};
let revision=0, restoring=false, readForm=null, projectForm=null, documentRef=null;
function notifyRevision() { if(documentRef) documentRef.dispatchEvent(new documentRef.defaultView.CustomEvent('toram:calculation-input-changed',{detail:{revision}})); }
  function clone(value) { if (value === null || value === undefined || typeof value !== 'object') return value; if (Array.isArray(value)) return value.map(clone); return Object.keys(value).reduce(function (result, key) { result[key] = clone(value[key]); return result; }, {}); }
  function freeze(value) { if (!value || typeof value !== 'object' || Object.isFrozen(value)) return value; Object.keys(value).forEach(function (key) { freeze(value[key]); }); return Object.freeze(value); }
  function equal(left, right) {
    if (left === right) return true;
    if (!left || !right || typeof left !== 'object' || typeof right !== 'object' || Array.isArray(left) !== Array.isArray(right)) return false;
    var keys = Object.keys(left);
    return keys.length === Object.keys(right).length && keys.every(function (key) { return Object.prototype.hasOwnProperty.call(right,key) && equal(left[key],right[key]); });
  }
  function commit(next) {
    var changed = false;
    Object.keys(next).forEach(function (key) {
      if (!equal(state[key],next[key])) { state[key] = freeze(clone(next[key])); changed = true; }
    });
    if (changed) {
      revision++;
      if (!restoring) notifyRevision();
    }
    return state;
  }
  function commitBuild(patch) { return commit({build:Object.assign({},state.build,patch)}).build; }
  function commitScenario(patch) { return commit({scenario:Object.assign({},state.scenario,patch)}).scenario; }
  function syncFromUi() { if (readForm) commit(readForm()); return read(); }
  function read() { if (!state.build || !state.scenario) throw new Error('계산 입력이 초기화되지 않았습니다.'); return Object.freeze({build:state.build,scenario:state.scenario,request:state.request}); }
  function applyComboHit(hit) { commit({request:hit ? { selectedSkillId:hit.skillId || null, selectedHitId:hit.hitId || null, overrides:{ appliedComboHit:clone(hit) } } : { selectedSkillId:null, selectedHitId:null, overrides:{} }}); }

function restoreSession(session) {
  if(projectForm) return projectForm(session);
  commit({build:session.build,scenario:session.scenario,request:{selectedSkillId:null,selectedHitId:null,overrides:{}}});
}
export const buildStore=Object.freeze({read,syncFromUi,restoreSession,commitBuild,commitScenario,revision:()=>revision,getBuild:()=>state.build||{},getScenario:()=>state.scenario||{}});
export function initializeBuildEditor(document,app) {
  documentRef=document;
  const root=document.defaultView;
  let pending=null;
  var equipmentIds = {
    mainWeapon:{ type:'mainWeaponType', attack:'wpnAtk', refinement:'wpnRefine', stability:'wpnStab', options:'wpnOpts', crystas:['cr_wpn_1','cr_wpn_2'], locks:['lock_wpn_1','lock_wpn_2'] },
    subWeapon:{ type:'subWeaponType', attack:'subAtk', refinement:'subRefine', stability:'subStab', options:'subOpts' },
    armor:{ type:'armorType', options:'armOpts', crystas:['cr_arm_1','cr_arm_2'], locks:['lock_arm_1','lock_arm_2'] },
    additional:{ options:'addOpts', crystas:['cr_add_1','cr_add_2'], locks:['lock_add_1','lock_add_2'] },
    special:{ options:'spcOpts', crystas:['cr_spc_1','cr_spc_2'], locks:['lock_spc_1','lock_spc_2'] }
  };
  var characterIds = { STR:'strBase', INT:'intBase', VIT:'vitBase', AGI:'agiBase', DEX:'dexBase', CRT:'crtBase' };
  var targetIds = { bossLevel:'bossLevel', bossDef:'bossDef', bossMdef:'bossMdef', bossCritResist:'bossCritResist', bossPhysResist:'bossPhysResist', bossMagResist:'bossMagResist', targetElement:'bossElement' };
  var itemEventTypes = [3,9];
  var staticIds = ['charLevel'].concat(Object.values(characterIds), Object.values(targetIds), itemEventTypes.map(function (type) { return 'itemEvent' + type; }));
  Object.values(equipmentIds).forEach(function (spec) { staticIds = staticIds.concat([spec.type,spec.attack,spec.refinement,spec.stability],spec.crystas || [],spec.locks || []).filter(Boolean); });
  function number(value) { var result = Number(value); return Number.isFinite(result) ? result : 0; }
  function element(id) { return document.getElementById(id); }
  function value(id) { var node = element(id); return node ? node.value : ''; }
  function checked(id) { var node = element(id); return Boolean(node && node.checked); }
  function options(id) {
    var container = element(id); if (!container) return [];
    return Array.prototype.slice.call(container.querySelectorAll('.opt-row')).filter(function (row) { return !row.classList.contains('combo-transient-option') && !row.closest('#activeSkillBuffOptions'); }).map(function (row) {
      var key = row.querySelector('.opt-type'), amount = row.querySelector('.opt-val');
      return key && amount ? { key:String(key.value || ''), value:number(amount.value) } : null;
    }).filter(Boolean);
  }
  function equipment(spec) {
    var info = equipmentIds[spec];
    var piece = {
      type:info.type ? (value(info.type) || null) : null,
      attack:info.attack ? number(value(info.attack)) : null,
      refinement:info.refinement ? number(value(info.refinement)) : null,
      stability:info.stability ? number(value(info.stability)) : null,
      options:options(info.options),
      crystas:(info.crystas || []).map(function (id) { return value(id); }),
      lockedCrystaSlots:(info.locks || []).map(checked)
    };
    var selection = state.build && state.build.equipment && state.build.equipment[spec] && state.build.equipment[spec].catalogItem;
    if (selection) piece.catalogItem = selection;
    return piece;
  }
  function buildFromUi() {
    var build = {
      character:{ level:number(value('charLevel')), attributes:Object.fromEntries(Object.entries(characterIds).map(function (entry) { return [entry[0],number(value(entry[1]))]; })) },
      equipment:{ mainWeapon:equipment('mainWeapon'), subWeapon:equipment('subWeapon'), armor:equipment('armor'), additional:equipment('additional'), special:equipment('special') },
      externalOptions:options('buffOpts'),
      myRoomFood:state.build && state.build.myRoomFood || [null,null,null,null,null],
      guildFoodBuff:!state.build || state.build.guildFoodBuff !== false,
      skillLevels:state.build && state.build.skillLevels || {}, activeBuffs:state.build && state.build.activeBuffs || {}, combo:state.build && state.build.combo || []
    };
    var selections = state.build && state.build.consumableBuffs;
    if (selections && selections.length) build.consumableBuffs = selections;
    return build;
  }
  function scenarioFromUi() {
    var preferences = state.scenario && state.scenario.optimizationPreferences || {rangeOverride:null,requirements:{},bannedCrystas:['오로로 콜론']};
    var scenario = { target:Object.fromEntries(Object.entries(targetIds).map(function (entry) { return [entry[0],number(value(entry[1]))]; })), conditions:{}, optimizationPreferences:clone(preferences) };
    scenario.conditions.activeItemEventTypes = itemEventTypes.filter(function (type) { return checked('itemEvent' + type); });
    var selection = state.scenario && state.scenario.bossSelection;
    if (selection) scenario.bossSelection = selection;
    return scenario;
  }
  function write(id, value) { var node = element(id); if (!node || value === undefined || value === null) return; if (node.type === 'checkbox') node.checked = Boolean(value); else node.value = String(value); }
  function restoreOptions(id, options) {
    var container = element(id), ui = app.crystaUi;
    if (!container || !ui) return;
    Array.prototype.slice.call(container.querySelectorAll('.opt-row')).forEach(function (row) { row.remove(); });
    (options || []).forEach(function (option) {
      ui.addOptionRow(id);
      var row = container.lastElementChild, type = row && row.querySelector('.opt-type'), value = row && row.querySelector('.opt-val');
      if (type) type.value = option.key === 'UNSHEATHE' ? 'UNSHEATHEP' : String(option.key || '');
      if (value) value.value = String(option.value === undefined ? 0 : option.value);
      if (type) type.dispatchEvent(new document.defaultView.Event('change', { bubbles:true }));
    });
  }
  function restoreSlot(name, piece) {
    var spec = equipmentIds[name], data = piece || {};
    if (!spec) return;
    if (spec.type) write(spec.type, data.type);
    if (spec.attack) write(spec.attack, data.attack);
    if (spec.refinement) write(spec.refinement, data.refinement);
    if (spec.stability) write(spec.stability, data.stability);
    var items = app.equipmentItems;
    if (items) items.restoreSelection(name, data.catalogItem || null);
    else if (data.catalogItem) throw new Error('게임 장비 복원 기능이 준비되지 않았습니다.');
    (spec.crystas || []).forEach(function (id, index) { write(id, data.crystas && data.crystas[index]); });
    (spec.locks || []).forEach(function (id, index) { write(id, data.lockedCrystaSlots && data.lockedCrystaSlots[index]); });
    restoreOptions(spec.options, data.options);
  }
  function restoreSessionUi(session) {
    if (!session || !session.build) return;
    var build = session.build, target = session.scenario && session.scenario.target || {}, attributes = build.character && build.character.attributes || {};
    var beforeRevision = revision;
    restoring = true;
    try {
      write('charLevel', build.character && build.character.level);
      Object.keys(characterIds).forEach(function (name) { write(characterIds[name], attributes[name]); });
      Object.keys(targetIds).forEach(function (name) { write(targetIds[name], name === 'targetElement' ? target[name] || 0 : target[name]); });
      var activeItemEvents = session.scenario && session.scenario.conditions && session.scenario.conditions.activeItemEventTypes || [];
      itemEventTypes.forEach(function (type) { write('itemEvent' + type, activeItemEvents.indexOf(type) >= 0); });
      var bosses = app.bossTarget;
      if (bosses) bosses.restoreSelection(session.scenario && session.scenario.bossSelection || null);
      else if (session.scenario && session.scenario.bossSelection) throw new Error('보스 대상 복원 기능이 준비되지 않았습니다.');
      restoreSlot('mainWeapon', build.equipment && build.equipment.mainWeapon);
      var ui = app.crystaUi; if (ui) ui.updateSubWeaponList();
      restoreSlot('subWeapon', build.equipment && build.equipment.subWeapon); restoreSlot('armor', build.equipment && build.equipment.armor); restoreSlot('additional', build.equipment && build.equipment.additional); restoreSlot('special', build.equipment && build.equipment.special);
      if (app.skillUi && app.skillUi.restore) app.skillUi.restore(build.skillLevels || {});
      if (app.activeBuffs && app.activeBuffs.restore) app.activeBuffs.restore(build.activeBuffs || {});
      restoreOptions('buffOpts', build.externalOptions);
      var consumables = app.consumableBuffs;
      if (consumables) consumables.restoreSelections(build.consumableBuffs || []);
      else if (build.consumableBuffs && build.consumableBuffs.length) throw new Error('소모품 버프 복원 기능이 준비되지 않았습니다.');
      if (app.myRoomFood) app.myRoomFood.restore(build.myRoomFood, build.guildFoodBuff);
      if (app.comboUi && app.comboUi.restore) app.comboUi.restore(build.combo || []);
      if (app.optimizationPreferences && app.optimizationPreferences.restore) app.optimizationPreferences.restore(session.scenario && session.scenario.optimizationPreferences);
      if (ui) { ui.onSubWeaponChange(); ui.refreshAllCrystaInfo(); }
      var level = element('charLevel'); if (level) level.dispatchEvent(new document.defaultView.Event('input', { bubbles:true }));
    } finally { syncFromUi(); restoring = false; if (revision !== beforeRevision) notifyRevision(); }
  }
  function optionContainer(target) {
    var row = target && target.closest && target.closest('.opt-row');
    return row && row.parentElement && row.parentElement.id;
  }
  function isCalculationInput(target) { return Boolean(target && target.nodeType === 1 && (staticIds.indexOf(target.id) >= 0 || ['wpnOpts','subOpts','armOpts','addOpts','spcOpts','buffOpts'].indexOf(optionContainer(target)) >= 0)); }
  function commitForm(target) {
    if (restoring || !isCalculationInput(target)) return;
    var id = target.id, container = optionContainer(target);
    if (id === 'charLevel' || Object.values(characterIds).indexOf(id) >= 0) {
      commitBuild({character:{level:number(value('charLevel')),attributes:Object.fromEntries(Object.entries(characterIds).map(function (entry) { return [entry[0],number(value(entry[1]))]; }))}});
    } else if (Object.values(targetIds).indexOf(id) >= 0 || itemEventTypes.some(function (type) { return id === 'itemEvent' + type; })) {
      var scenario = scenarioFromUi(); commitScenario({target:scenario.target,conditions:scenario.conditions});
    } else if (container === 'buffOpts') commitBuild({externalOptions:options('buffOpts')});
    else {
      var name = Object.keys(equipmentIds).find(function (name) {
        var info = equipmentIds[name];
        return container === info.options || [info.type,info.attack,info.refinement,info.stability].concat(info.crystas || [],info.locks || []).indexOf(id) >= 0;
      });
      if (name) commitBuild({equipment:Object.assign({},state.build.equipment,{[name]:equipment(name)})});
    }
    notify();
  }
  function notify() { if (restoring || pending !== null) return; pending = root.setTimeout(function () { pending = null; document.dispatchEvent(new document.defaultView.CustomEvent('toram:persistent-state-changed')); }, 0); }
  function initialize() {
    syncFromUi();
    ['input','change'].forEach(function (eventName) { document.addEventListener(eventName, function (event) { commitForm(event.target); }); });
    document.addEventListener('toram:build-options-changed', function () { if (!restoring) syncFromUi(); });
    document.addEventListener('toram:combo-hit-selected', function (event) { applyComboHit(event.detail || null); });
    document.addEventListener('click', function (event) {
      var target = event.target;
      if (target && target.closest && target.closest('.stat-easy-btn, #statusResetBtn')) { commitForm(element('charLevel')); }
    });
  }

  readForm=()=>({build:buildFromUi(),scenario:scenarioFromUi()});
  projectForm=restoreSessionUi;
  initialize();
}
