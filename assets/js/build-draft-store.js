/* R4 상태 경계: 계산 가능한 영속 빌드, UI 상태, 실행 상태를 분리한다. */
(function (root) {
  'use strict';
  var equipmentIds = {
    mainWeapon:{ type:'mainWeaponType', attack:'wpnAtk', refinement:'wpnRefine', stability:'wpnStab', options:'wpnOpts', crystas:['cr_wpn_1','cr_wpn_2'], locks:['lock_wpn_1','lock_wpn_2'] },
    subWeapon:{ type:'subWeaponType', attack:'subAtk', refinement:'subRefine', stability:'subStab', options:'subOpts' },
    armor:{ type:'armorType', options:'armOpts', crystas:['cr_arm_1','cr_arm_2'], locks:['lock_arm_1','lock_arm_2'] },
    additional:{ options:'addOpts', crystas:['cr_add_1','cr_add_2'], locks:['lock_add_1','lock_add_2'] },
    special:{ options:'spcOpts', crystas:['cr_spc_1','cr_spc_2'], locks:['lock_spc_1','lock_spc_2'] }
  };
  var state = { build:null, scenario:null, request:{ selectedSkillId:null, selectedHitId:null, overrides:{} } };
  var uiState = { combo:{ selectedIndex:0 } };
  var runtimeState = { d4:{ runVersion:0, lastOptimizationRequest:null, lastOptimizationResult:null, lastOutcome:null }, calculationQueued:false };

  function clone(value) { if (value === null || value === undefined || typeof value !== 'object') return value; if (Array.isArray(value)) return value.map(clone); return Object.keys(value).reduce(function (result, key) { result[key] = clone(value[key]); return result; }, {}); }
  function freeze(value) { if (!value || typeof value !== 'object' || Object.isFrozen(value)) return value; Object.keys(value).forEach(function (key) { freeze(value[key]); }); return Object.freeze(value); }
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
    return {
      type:info.type ? (value(info.type) || null) : null,
      attack:info.attack ? number(value(info.attack)) : null,
      refinement:info.refinement ? number(value(info.refinement)) : null,
      stability:info.stability ? number(value(info.stability)) : null,
      options:options(info.options),
      crystas:(info.crystas || []).map(function (id) { return value(id); }),
      lockedCrystaSlots:(info.locks || []).map(checked)
    };
  }
  function skillLevels() { var simulator = root.skillSimulatorState; return simulator && typeof simulator.getInvestments === 'function' ? simulator.getInvestments() : {}; }
  function activeBuffs() { var buffs = root.ToramActiveBuffs; return buffs && typeof buffs.getSelections === 'function' ? buffs.getSelections() : {}; }
  function comboEntries() { var combo = root.ToramComboUi; return combo && typeof combo.getEntries === 'function' ? combo.getEntries() : []; }
  function buildFromUi() {
    return {
      character:{ level:number(value('charLevel')), attributes:{ STR:number(value('strBase')), INT:number(value('intBase')), VIT:number(value('vitBase')), AGI:number(value('agiBase')), DEX:number(value('dexBase')), CRT:number(value('crtBase')) } },
      equipment:{ mainWeapon:equipment('mainWeapon'), subWeapon:equipment('subWeapon'), armor:equipment('armor'), additional:equipment('additional'), special:equipment('special') },
      externalOptions:options('buffOpts'),
      myRoomFood:root.ToramMyRoomFood ? root.ToramMyRoomFood.getSelections() : [null,null,null,null,null],
      guildFoodBuff:root.ToramMyRoomFood ? root.ToramMyRoomFood.isGuildEnabled() : true,
      skillLevels:skillLevels(), activeBuffs:activeBuffs(), combo:comboEntries()
    };
  }
  function scenarioFromUi() {
    var preferences = root.ToramOptimizationPreferences && typeof root.ToramOptimizationPreferences.read === 'function' ? root.ToramOptimizationPreferences.read() : { rangeOverride:null, requirements:{}, bannedCrystas:[] };
    return { target:{ bossLevel:number(value('bossLevel')), bossDef:number(value('bossDef')), bossMdef:number(value('bossMdef')), bossCritResist:number(value('bossCritResist')), bossPhysResist:number(value('bossPhysResist')), bossMagResist:number(value('bossMagResist')) }, conditions:{}, optimizationPreferences:clone(preferences) };
  }
  function setBuild(build) { state.build = freeze(clone(build)); return state.build; }
  function setScenario(scenario) { state.scenario = freeze(clone(scenario)); return state.scenario; }
  function setRequest(request) { state.request = freeze(clone(request || { selectedSkillId:null, selectedHitId:null, overrides:{} })); return state.request; }
  function syncFromUi() { setBuild(buildFromUi()); setScenario(scenarioFromUi()); return read(); }
  function read() { if (!state.build || !state.scenario) syncFromUi(); return freeze({ build:state.build, scenario:state.scenario, request:state.request }); }
  function setUiState(next) { uiState = Object.assign({}, uiState, clone(next || {})); return freeze(clone(uiState)); }
  function getUiState() { return freeze(clone(uiState)); }
  function updateRuntime(next) { runtimeState = Object.assign({}, runtimeState, clone(next || {})); return runtimeState; }
  function getRuntimeState() { return runtimeState; }
  function applyComboHit(hit) { setRequest(hit ? { selectedSkillId:hit.skillId || null, selectedHitId:hit.hitId || null, overrides:{ appliedComboHit:clone(hit) } } : { selectedSkillId:null, selectedHitId:null, overrides:{} }); }
  function initialize() {
    syncFromUi();
    ['input','change'].forEach(function (eventName) { document.addEventListener(eventName, function () { syncFromUi(); }, true); });
    document.addEventListener('toram:skill-investments-changed', syncFromUi);
    document.addEventListener('toram:active-buffs-changed', syncFromUi);
    document.addEventListener('toram:combo-changed', syncFromUi);
    document.addEventListener('toram:build-options-changed', syncFromUi);
    document.addEventListener('toram:optimization-preferences-changed', syncFromUi);
    document.addEventListener('toram:combo-hit-selected', function (event) { applyComboHit(event.detail || null); });
  }
  root.ToramBuildDraftStore = Object.freeze({ read:read, syncFromUi:syncFromUi, setBuild:setBuild, setScenario:setScenario, setRequest:setRequest });
  root.ToramUiState = Object.freeze({ get:getUiState, set:setUiState });
  root.ToramRuntimeState = Object.freeze({ get:getRuntimeState, update:updateRuntime });
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', initialize, { once:true }); else initialize();
}(typeof window !== 'undefined' ? window : globalThis));
