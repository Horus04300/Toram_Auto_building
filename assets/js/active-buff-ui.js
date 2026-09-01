(function () {
  'use strict';
  var persistedState = {};
  function clone(value) { return JSON.parse(JSON.stringify(value || {})); }
  function savedState() { return clone(persistedState); }
  function saveState(state) {
    persistedState = clone(state);
    if (typeof document.dispatchEvent === 'function' && typeof CustomEvent === 'function') {
      document.dispatchEvent(new CustomEvent('toram:active-buffs-changed'));
      document.dispatchEvent(new CustomEvent('toram:persistent-state-changed'));
    }
  }
  function displayNumber(value) {
    var numeric = Number(value);
    return Number.isFinite(numeric) ? Number(numeric.toFixed(6)) : 0;
  }
  function iconFor(skill) {
    var simulator = window.skillSimulatorState;
    var tree = simulator && simulator.data.trees.find(function (item) { return item.id === skill.treeId; });
    var node = tree && tree.skills.find(function (item) { return item.id === skill.skillId; });
    return node ? node.icon : '';
  }
  function levelFor(skill) {
    var levels = window.skillSimulatorState.getInvestments();
    return Number(levels[skill.treeId] && levels[skill.treeId][skill.skillId]) || 0;
  }
  function effectSkills() {
    var policies = window.ToramCalculationPolicies;
    if (policies && typeof policies.resolveSkillDefinitions === 'function') return policies.resolveSkillDefinitions({ preferStackControl:true });
    var root = window.TORAM_SKILL_EFFECT_DATA && window.TORAM_SKILL_EFFECT_DATA.skills || [];
    var registry = window.ToramSkillEffectRegistry;
    var byId = Object.create(null);
    var orderedIds = [];
    root.concat(registry ? registry.all() : []).forEach(function (skill) {
      if (!skill || !skill.id) return;
      var existing = byId[skill.id];
      if (!existing) {
        byId[skill.id] = skill;
        orderedIds.push(skill.id);
        return;
      }
      // 기본 정의와 스택 보강 정의가 같은 스킬 ID를 공유할 수 있다.
      // 버프 카드는 하나만 표시하고, 스택 조절 정보가 있는 보강 정의를 우선한다.
      if (skill.stackControl && !existing.stackControl) byId[skill.id] = skill;
    });
    return orderedIds.map(function (id) { return byId[id]; });
  }
  function isActiveBuff(skill) { return skill.kind === 'buff' || skill.activeBuff === true; }
  function isDisplayableActiveBuff(skill) {
    if (!isActiveBuff(skill) || !window.ToramSkillEffects) return false;
    var context = contextFor(skill, false, 0, {});
    if (!window.ToramSkillEffects.condition(skill.requirements && skill.requirements.when, context)) return false;
    if (!skill.activeBuffWhen) return true;
    return Boolean(window.ToramSkillEffects.condition(skill.activeBuffWhen, context));
  }
  function displayableBuffSkills() {
    return effectSkills().filter(isDisplayableActiveBuff);
  }
  function settingFor(state, skillId) { return state[skillId]; }
  function enabledFor(state, skillId) {
    var setting = settingFor(state, skillId);
    return setting === true || Boolean(setting && setting.enabled === true);
  }
  function stackConfig(skill, context, allState, includeSelf) {
    var config = skill.stackControl;
    if (!config) return null;
    var evaluate = function (value, fallback) {
      if (value === undefined) return fallback;
      return Math.floor(Number(window.ToramSkillEffects.expression(value, context)) || 0);
    };
    var min = evaluate(config.minStacks, 0);
    var max = Math.max(min, evaluate(config.maxStacks, min));
    if (config.sharedGroup && Number.isFinite(Number(config.sharedMaxBase))) {
      var activeCount = effectSkills().filter(function (candidate) {
        if (!candidate.stackControl || candidate.stackControl.sharedGroup !== config.sharedGroup) return false;
        return enabledFor(allState || {}, candidate.id) || (includeSelf && candidate.id === skill.id);
      }).length;
      max = Math.min(max, Math.max(min, Number(config.sharedMaxBase) - activeCount));
    }
    var initial = Math.min(max, Math.max(min, evaluate(config.initialStacks, min)));
    return { stateId:config.stateId, min:min, max:max, initial:initial, label:config.label || '스택', persistWhenDisabled:Boolean(config.persistWhenDisabled), showWhenDisabled:Boolean(config.showWhenDisabled), applyWhenDisabled:Boolean(config.applyWhenDisabled), resetStacksOnEnable:Boolean(config.resetStacksOnEnable) };
  }
  function engineMainWeapon(value) { return ({ '활':'bow', '자동활':'bowgun', '지팡이':'staff', '마도구':'magicDevice' })[value] || value; }
  function currentCalculationContext() {
    if (!window.ToramApplication || typeof window.ToramApplication.CalculateBuild !== 'function') return null;
    try {
      var result = window.ToramApplication.CalculateBuild();
      var base = result.snapshot.baseContext;
      var calculated = result.calculation;
      var combat = { STR:calculated.finalSTR, INT:calculated.finalINT, VIT:calculated.finalVIT, AGI:calculated.finalAGI, DEX:calculated.finalDEX, CRT:base.crtBase, ATK:calculated.finalATK, MATK:calculated.finalMATK, ASPD:calculated.finalASPD, CSPD:calculated.finalCSPD, STABILITY:calculated.finalStab, WEAPON_ATK:calculated.finalWeaponAttack, MAXMP:calculated.finalMaxMP };
      return {
        baseStats:{ STR:base.strBase, INT:base.intBase, VIT:base.vitBase, AGI:base.agiBase, DEX:base.dexBase, CRT:base.crtBase },
        combatStats:combat,
        buildStats:combat
      };
    } catch (_) { return null; }
  }
  function contextFor(skill, active, stacks, states, calculated) {
    var mainWeapon = document.getElementById('mainWeaponType');
    var subWeapon = document.getElementById('subWeaponType');
    var charLevel = document.getElementById('charLevel');
    var numberValue = function (id) { var node = document.getElementById(id); return Number(node && node.value) || 0; };
    var baseStats = calculated && calculated.baseStats || { STR:numberValue('strBase'), INT:numberValue('intBase'), VIT:numberValue('vitBase'), AGI:numberValue('agiBase'), DEX:numberValue('dexBase'), CRT:numberValue('crtBase') };
    var combatStats = calculated && calculated.combatStats || {};
    return {
      skill:{ level:levelFor(skill) }, player:{ level:Number(charLevel && charLevel.value) || 0 }, buff:{ active:active, stacks:stacks }, states:states || {},
      baseStats:baseStats, combatStats:combatStats, buildStats:calculated && calculated.buildStats || combatStats,
      equipment:{ mainWeapon:engineMainWeapon(mainWeapon ? mainWeapon.value : null), subWeapon:subWeapon ? subWeapon.value : null, subWeaponRefinement:numberValue('subRefine'), subWeaponAttack:numberValue('subAtk'), subWeaponStability:numberValue('subStab') }
    };
  }
  function stackFor(state, skill, config) {
    var setting = settingFor(state, skill.id);
    var value = setting && typeof setting === 'object' ? Number(setting.stacks) : config.initial;
    if (!Number.isFinite(value)) value = config.initial;
    return Math.min(config.max, Math.max(config.min, Math.floor(value)));
  }
  function runtimeStates(state) {
    var states = {};
    effectSkills().forEach(function (skill) {
      var enabled = enabledFor(state, skill.id);
      if (!isDisplayableActiveBuff(skill) || !skill.stackControl || (!enabled && !skill.stackControl.persistWhenDisabled)) return;
      var preliminary = contextFor(skill, enabled, 0, states);
      var config = stackConfig(skill, preliminary, state, true);
      if (!config || !config.stateId) return;
      states[config.stateId] = { active:enabled, stacks:stackFor(state, skill, config), maxStacks:config.max };
    });
    return states;
  }
  function setEnabled(state, skill, enabled) {
    var preliminary = contextFor(skill, enabled, 0, runtimeStates(state));
    var config = stackConfig(skill, preliminary, state, enabled);
    if (!config) { state[skill.id] = enabled; return; }
    var previous = stackFor(state, skill, config);
    var stacks = enabled && config.resetStacksOnEnable ? config.initial : (config.persistWhenDisabled ? previous : config.initial);
    state[skill.id] = { enabled:enabled, stacks:stacks };
  }
  function adjustStack(state, skill, delta) {
    var states = runtimeStates(state);
    var preliminary = contextFor(skill, true, 0, states);
    var config = stackConfig(skill, preliminary, state, true);
    if (!config) return;
    var value = Math.min(config.max, Math.max(config.min, stackFor(state, skill, config) + delta));
    state[skill.id] = { enabled:enabledFor(state, skill.id), stacks:value };
  }
  function syncOptions(active) {
    var container = document.getElementById('buffOpts');
    if (!container) return;
    var proxy = container.querySelector('#activeSkillBuffOptions');
    if (proxy) proxy.remove();
  }
  function render() {
    var panel = document.getElementById('appTabPanel-buffs');
    if (!panel || !window.skillSimulatorState || !window.TORAM_SKILL_EFFECT_DATA) return;
    var section = document.getElementById('activeBuffSkillSection');
    if (!section) { section = document.createElement('section'); section.id = 'activeBuffSkillSection'; section.className = 'equip-card'; panel.insertBefore(section, panel.firstChild); }
    var state = savedState();
    var buffs = displayableBuffSkills().filter(function (skill) { return levelFor(skill) > 0; });
    section.innerHTML = '<h3>✨ 액티브 버프</h3><p style="margin:0 0 10px;color:#5d6d7e;font-size:13px;">파란색은 적용, 회색은 미적용입니다. 스택형 버프는 카드 하단에서 조절합니다.</p>';
    var grid = document.createElement('div'); grid.className = 'active-buff-grid';
    buffs.forEach(function (skill) {
      var enabled = enabledFor(state, skill.id);
      var preliminary = contextFor(skill, enabled, 0, runtimeStates(state));
      var config = stackConfig(skill, preliminary, state, enabled);
      var stacks = config ? stackFor(state, skill, config) : 0;
      var card = document.createElement('div'); card.className = 'active-buff-card' + (config ? ' has-stacks' : '');
      var button = document.createElement('button'); button.type = 'button'; button.className = 'skill-node' + (enabled ? ' is-invested' : '');
      button.style.backgroundImage = 'url("' + encodeURI('assets/icons/skills/icons/' + (enabled ? 'skill_on.png' : 'skill_off.png')) + '")';
      var image = document.createElement('img'); image.className = 'skill-node-icon'; image.src = encodeURI(iconFor(skill)); image.alt = '';
      var name = document.createElement('span'); name.className = 'skill-node-name'; name.textContent = skill.nameKo;
      var label = document.createElement('span'); label.className = 'skill-node-level'; label.textContent = 'Lv.' + levelFor(skill);
      button.append(image, name, label);
      button.addEventListener('click', function () { setEnabled(state, skill, !enabled); saveState(state); render(); });
      card.appendChild(button);
      if (config && (enabled || config.showWhenDisabled)) {
        var controls = document.createElement('div'); controls.className = 'active-buff-stack-controls'; controls.setAttribute('aria-label', skill.nameKo + ' ' + config.label);
        var decrement = document.createElement('button'); decrement.type = 'button'; decrement.textContent = '−'; decrement.disabled = stacks <= config.min; decrement.setAttribute('aria-label', config.label + ' 감소');
        var value = document.createElement('span'); value.textContent = stacks + '/' + config.max; value.title = config.label;
        var increment = document.createElement('button'); increment.type = 'button'; increment.textContent = '+'; increment.disabled = stacks >= config.max; increment.setAttribute('aria-label', config.label + ' 증가');
        decrement.addEventListener('click', function () { adjustStack(state, skill, -1); saveState(state); render(); });
        increment.addEventListener('click', function () { adjustStack(state, skill, 1); saveState(state); render(); });
        controls.append(decrement, value, increment); card.appendChild(controls);
      }
      grid.appendChild(card);
    });
    if (!buffs.length) {
      var empty = document.createElement('p'); empty.className = 'active-buff-empty'; empty.textContent = '습득한 액티브 버프 스킬이 없습니다.'; grid.appendChild(empty);
    }
    section.appendChild(grid); syncOptions(state);
  }
  document.addEventListener('toram:calculate', function () { syncOptions(savedState()); });
  document.addEventListener('change', function (event) { if (event.target && (event.target.id === 'mainWeaponType' || event.target.id === 'subWeaponType')) render(); });
  function activeSelections() {
    var state = savedState(), states = runtimeStates(state), result = {};
    effectSkills().forEach(function (skill) {
      if (!isDisplayableActiveBuff(skill)) return;
      var enabled = enabledFor(state, skill.id);
      var config = stackConfig(skill, contextFor(skill, enabled, 0, states), state, enabled);
      result[skill.id] = { active:enabled, stacks:config ? stackFor(state, skill, config) : 0 };
    });
    return result;
  }
  function restore(selections) {
    persistedState = Object.keys(selections || {}).reduce(function (result, id) {
      var value = selections[id];
      result[id] = { enabled:Boolean(value === true || value && (value.active === true || value.enabled === true)), stacks:Number(value && value.stacks) || 0 };
      return result;
    }, {});
    render();
  }
  window.ToramActiveBuffs = Object.freeze({ render:render, restore:restore, getRuntimeStates:function () { return runtimeStates(savedState()); }, getSelections:activeSelections, getDisplaySkills:displayableBuffSkills });
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', render, { once:true }); else render();
}());
