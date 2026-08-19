(function () {
  'use strict';
  var storageKey = 'toram-auto-active-buffs-v1';
  function savedState() { try { return JSON.parse(window.localStorage.getItem(storageKey) || '{}'); } catch (_) { return {}; } }
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
  function syncOptions(active) {
    var container = document.getElementById('buffOpts');
    if (!container || !window.TORAM_SKILL_EFFECT_DATA || !window.ToramSkillEffects) return;
    var proxy = container.querySelector('#activeSkillBuffOptions');
    if (!proxy) { proxy = document.createElement('div'); proxy.id = 'activeSkillBuffOptions'; proxy.hidden = true; container.appendChild(proxy); }
    proxy.innerHTML = '';
    effectSkills().filter(function (skill) { return isActiveBuff(skill) && active[skill.id] && levelFor(skill) > 0; }).forEach(function (skill) {
      var mainWeapon = document.getElementById('mainWeaponType');
      var context = { skill: { level: levelFor(skill) }, buff: { active: true }, equipment: { mainWeapon: mainWeapon ? mainWeapon.value : null } };
      skill.effects.forEach(function (effect) {
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
    section.innerHTML = '<h3>✨ 액티브 버프</h3><p style="margin:0 0 10px;color:#5d6d7e;font-size:13px;">파란색은 적용, 회색은 미적용입니다.</p>';
    var grid = document.createElement('div'); grid.style.cssText = 'display:grid;grid-template-columns:repeat(auto-fill,minmax(92px,1fr));gap:8px;';
    buffs.forEach(function (skill) {
      var enabled = state[skill.id] === true;
      var button = document.createElement('button'); button.type = 'button'; button.className = 'skill-node' + (enabled ? ' is-invested' : '');
      button.style.cssText = 'position:relative;min-height:90px;grid-column:auto;grid-row:auto;background-image:url("' + encodeURI('assets/icons/skills/icons/' + (enabled ? 'skill_on.png' : 'skill_off.png')) + '");';
      var image = document.createElement('img'); image.className = 'skill-node-icon'; image.src = encodeURI(iconFor(skill)); image.alt = '';
      var name = document.createElement('span'); name.className = 'skill-node-name'; name.textContent = skill.nameKo;
      var label = document.createElement('span'); label.className = 'skill-node-level'; label.textContent = 'Lv.' + levelFor(skill);
      button.append(image, name, label);
      button.addEventListener('click', function () { state[skill.id] = !enabled; window.localStorage.setItem(storageKey, JSON.stringify(state)); render(); });
      grid.appendChild(button);
    });
    if (!buffs.length) {
      var empty = document.createElement('p');
      empty.style.cssText = 'grid-column:1 / -1;margin:8px 0;color:#5d6d7e;';
      empty.textContent = '습득한 액티브 버프 스킬이 없습니다.';
      grid.appendChild(empty);
    }
    section.appendChild(grid); syncOptions(state);
  }
  document.addEventListener('toram:calculate', function () { syncOptions(savedState()); });
  window.ToramActiveBuffs = Object.freeze({ render: render });
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', render, { once: true }); else render();
}());