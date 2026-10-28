import {buildStore} from '../application/build-draft-store.js';
import {skillRegistry} from '../data/skill-effect-registry.js';
import {skillEffects} from '../calculation/skill-effect-engine.js';
import {skillTreeData} from '../data/skill-tree-data.js';
export function createActiveBuffUi(document) {
  const root=document.defaultView;

  'use strict';
  function clone(value) { return JSON.parse(JSON.stringify(value || {})); }
  function savedState() { return Object.fromEntries(Object.entries(buildStore.getBuild().activeBuffs || {}).map(function (entry) { var value=entry[1]; return [entry[0],{enabled:value === true || Boolean(value && value.active),stacks:Number(value && value.stacks)||0}]; })); }
  function saveState(state) {
    buildStore.commitBuild({activeBuffs:Object.fromEntries(Object.entries(state).map(function (entry) {return [entry[0],{active:enabledFor(state,entry[0]),stacks:Number(entry[1] && entry[1].stacks)||0}]; }))});
    if (typeof document.dispatchEvent === 'function' && typeof CustomEvent === 'function') {
      document.dispatchEvent(new CustomEvent('toram:active-buffs-changed'));
      document.dispatchEvent(new CustomEvent('toram:persistent-state-changed'));
    }
  }
  function iconFor(skill) {
    var tree = skillTreeData.trees.find(function (item) { return item.id === skill.treeId; });
    var node = tree && tree.skills.find(function (item) { return item.id === skill.skillId; });
    return node ? node.icon : '';
  }
  function levelFor(skill) {
    var levels = (buildStore.getBuild().skillLevels || {});
    return Number(levels[skill.treeId] && levels[skill.treeId][skill.skillId]) || 0;
  }
  function effectSkills() { return skillRegistry.definitions(); }
  function isActiveBuff(skill) { return skill.kind === 'buff' || skill.activeBuff === true; }
  function isDisplayableActiveBuff(skill) {
    if (!isActiveBuff(skill) || !skillEffects) return false;
    var context = contextFor(skill, false, 0, {});
    if (!skillEffects.condition(skill.requirements && skill.requirements.when, context)) return false;
    if (!skill.activeBuffWhen) return true;
    return Boolean(skillEffects.condition(skill.activeBuffWhen, context));
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
      return Math.floor(Number(skillEffects.expression(value, context)) || 0);
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
  function contextFor(skill, active, stacks, states) {
    var mainWeapon = document.getElementById('mainWeaponType');
    var subWeapon = document.getElementById('subWeaponType');
    var charLevel = document.getElementById('charLevel');
    var numberValue = function (id) { var node = document.getElementById(id); return Number(node && node.value) || 0; };
    var baseStats = { STR:numberValue('strBase'), INT:numberValue('intBase'), VIT:numberValue('vitBase'), AGI:numberValue('agiBase'), DEX:numberValue('dexBase'), CRT:numberValue('crtBase') };
    var combatStats = {};
    return {
      skill:{ level:levelFor(skill) }, player:{ level:Number(charLevel && charLevel.value) || 0 }, buff:{ active:active, stacks:stacks }, states:states || {},
      baseStats:baseStats, combatStats:combatStats, buildStats:combatStats,
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
  function syncOptions() {
    var container = document.getElementById('buffOpts');
    if (!container) return;
    var proxy = container.querySelector('#activeSkillBuffOptions');
    if (proxy) proxy.remove();
  }
  function render() {
    var panel = document.getElementById('appTabPanel-buffs');
    if (!panel) return;
    var section = document.getElementById('activeBuffSkillSection');
    if (!section) { section = document.createElement('section'); section.id = 'activeBuffSkillSection'; section.className = 'equip-card'; panel.insertBefore(section, panel.firstChild); }
    var state = savedState();
    var buffs = displayableBuffSkills().filter(function (skill) { return levelFor(skill) > 0; });
    section.innerHTML = '<h3>✨ 액티브 버프</h3>';
    var grid = document.createElement('div'); grid.className = 'active-buff-grid';
    buffs.forEach(function (skill) {
      var enabled = enabledFor(state, skill.id);
      var preliminary = contextFor(skill, enabled, 0, runtimeStates(state));
      var config = stackConfig(skill, preliminary, state, enabled);
      var stacks = config ? stackFor(state, skill, config) : 0;
      var card = document.createElement('div'); card.className = 'active-buff-card' + (config ? ' has-stacks' : '');
      var button = document.createElement('button'); button.type = 'button'; button.className = 'skill-node' + (enabled ? ' is-invested' : '');
      button.setAttribute('aria-pressed', String(enabled));
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
    section.appendChild(grid); syncOptions();
  }
  document.addEventListener('toram:calculate', syncOptions);
  document.addEventListener('toram:preview', syncOptions);
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
    buildStore.commitBuild({activeBuffs:clone(selections || {})});
    render();
  }
  const api = Object.freeze({ render:render, restore:restore, getRuntimeStates:function () { return runtimeStates(savedState()); }, getSelections:activeSelections, getDisplaySkills:displayableBuffSkills });

render(); return api;
}
