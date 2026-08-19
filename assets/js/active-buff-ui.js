(function () {
  'use strict';
  var storageKey = 'toram-auto-active-buffs-v1';
  function savedState() { try { return JSON.parse(window.localStorage.getItem(storageKey) || '{}'); } catch (_) { return {}; } }
  function saveState(state) { window.localStorage.setItem(storageKey, JSON.stringify(state)); }
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
    var root = window.TORAM_SKILL_EFFECT_DATA && window.TORAM_SKILL_EFFECT_DATA.skills || [];
    var registry = window.ToramSkillEffectRegistry;
    return root.concat(registry ? registry.all() : []);
  }
  function isActiveBuff(skill) { return skill.kind === 'buff' || skill.activeBuff === true; }
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
  function contextFor(skill, active, stacks, states) {
    var mainWeapon = document.getElementById('mainWeaponType');
    var subWeapon = document.getElementById('subWeaponType');
    return { skill:{ level:levelFor(skill) }, buff:{ active:active, stacks:stacks }, states:states || {}, equipment:{ mainWeapon:mainWeapon ? mainWeapon.value : null, subWeapon:subWeapon ? subWeapon.value : null } };
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
      if (!isActiveBuff(skill) || !skill.stackControl || (!enabled && !skill.stackControl.persistWhenDisabled)) return;
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
    if (!container || !window.TORAM_SKILL_EFFECT_DATA || !window.ToramSkillEffects) return;
    var proxy = container.querySelector('#activeSkillBuffOptions');
    if (!proxy) { proxy = document.createElement('div'); proxy.id = 'activeSkillBuffOptions'; proxy.hidden = true; container.appendChild(proxy); }
    proxy.innerHTML = '';
    var states = runtimeStates(active);
    effectSkills().filter(function (skill) {
      return isActiveBuff(skill) && levelFor(skill) > 0 && (enabledFor(active, skill.id) || (skill.stackControl && skill.stackControl.applyWhenDisabled));
    }).forEach(function (skill) {
      var enabled = enabledFor(active, skill.id);
      var config = stackConfig(skill, contextFor(skill, enabled, 0, states), active, true);
      var stacks = config ? stackFor(active, skill, config) : 0;
      var context = contextFor(skill, enabled, stacks, states);
      (enabled ? skill.effects : (skill.inactiveEffects || [])).forEach(function (effect) {
        var isGlobalDamageBuff = effect.type === 'damageMultiplier' && effect.target === 'attack';
        if ((effect.type !== 'stat' && !isGlobalDamageBuff) || !window.ToramSkillEffects.condition(effect.when, context)) return;
        var row = document.createElement('div'); row.className = 'opt-row';
        var type = document.createElement('select'); type.className = 'opt-type';
        var option = document.createElement('option'); option.value = isGlobalDamageBuff ? 'DAMAGE_P' : effect.key; option.selected = true; type.appendChild(option);
        var amount = document.createElement('input'); amount.className = 'opt-val';
        var resolvedValue = window.ToramSkillEffects.expression(effect.value, context);
        amount.value = String(isGlobalDamageBuff ? (resolvedValue - 1) * 100 : resolvedValue);
        row.append(type, amount); proxy.appendChild(row);
      });
    });
  }
  function render() {
    var panel = document.getElementById('appTabPanel-buffs');
    if (!panel || !window.skillSimulatorState || !window.TORAM_SKILL_EFFECT_DATA) return;
    var section = document.getElementById('activeBuffSkillSection');
    if (!section) { section = document.createElement('section'); section.id = 'activeBuffSkillSection'; section.className = 'equip-card'; panel.insertBefore(section, panel.firstChild); }
    var state = savedState();
    var buffs = effectSkills().filter(function (skill) { return isActiveBuff(skill) && levelFor(skill) > 0; });
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
  window.ToramActiveBuffs = Object.freeze({ render:render, getRuntimeStates:function () { return runtimeStates(savedState()); } });
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', render, { once:true }); else render();
}());