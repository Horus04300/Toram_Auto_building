import {foodCatalog} from '../data/my-room-food.js';
import {buildStore} from '../application/build-draft-store.js';
export function createFoodUi(document) {
  const root=document.defaultView;

  'use strict';
  var catalog = foodCatalog;
  function slots() { return catalog.normalize(buildStore.getBuild().myRoomFood); }
  function guildEnabled() { return buildStore.getBuild().guildFoodBuff !== false; }
  var shortcuts = [
    [['CRIT','CRIT'],['WATK','WATK'],['AMPR','AMPR'],['ELEM_P','속성에 유리']],
    [['MAXHP','Max HP'],['MAXMP','Max MP'],['AGGRO_MINUS','-어그로']],
    [['STR','STR'],['INT','INT'],['VIT','VIT'],['AGI','AGI'],['DEX','DEX']]
  ];
  function selections() { return slots(); }
  function changed() {
    render();
    document.dispatchEvent(new CustomEvent('toram:build-options-changed'));
    document.dispatchEvent(new CustomEvent('toram:persistent-state-changed'));
  }
  function setSlot(index, id, level) {
    var recipe = catalog.get(id);
    if (recipe && slots().some(function (slot, other) { return other !== index && slot && catalog.get(slot.id).group === recipe.group; })) return;
    var next = slots(); next[index] = recipe ? {id:id,level:level} : null;
    buildStore.commitBuild({myRoomFood:catalog.normalize(next)});
    changed();
  }
  function quickSelect(id) {
    var selected = slots().findIndex(function (slot) { return slot && slot.id === id; });
    if (selected >= 0) { setSlot(selected, '', 10); return; }
    var index = slots().indexOf(null), recipe = catalog.get(id);
    if (index < 0 || !recipe || slots().some(function (slot) { return slot && catalog.get(slot.id).group === recipe.group; })) return;
    setSlot(index, id, 10);
  }
  function render() {
    var container = document.getElementById('myRoomFoodSlots'), quick = document.getElementById('myRoomFoodShortcuts');
    if (!container || !quick) return;
    container.replaceChildren(); quick.replaceChildren();
    var guild = document.getElementById('guildFoodBuff');
    if (guild) guild.checked = guildEnabled();
    shortcuts.forEach(function (group) {
      var grid = document.createElement('div'); grid.className = 'food-quick-group';
      group.forEach(function (item) {
      var button = document.createElement('button'); button.type = 'button'; button.className = 'food-quick-btn';
      button.textContent = item[1]; button.dataset.food = item[0];
      var selected = slots().some(function (slot) { return slot && slot.id === item[0]; });
      button.setAttribute('aria-pressed', String(selected));
      button.disabled = !selected && (slots().indexOf(null) < 0 || slots().some(function (slot) { return slot && catalog.get(slot.id).group === catalog.get(item[0]).group; }));
      button.addEventListener('click', function () { quickSelect(item[0]); }); grid.appendChild(button);
      });
      quick.appendChild(grid);
    });
    slots().forEach(function (slot, index) {
      var recipe = slot && catalog.get(slot.id);
      var row = document.createElement('div'); row.className = 'opt-row food-row';
      var effect = document.createElement('div'); effect.className = 'food-effect';
      var select = document.createElement('select'); select.setAttribute('aria-label', '요리 ' + (index + 1) + ' 효과');
      select.appendChild(new Option('요리 효과 선택', ''));
      catalog.recipes.forEach(function (candidate) {
        var label = ({CRIT:'CRIT',AMPR:'AMPR',WATK:'WATK'})[candidate.id] || candidate.effect;
        var option = new Option(label + (candidate.percent ? ' (%)' : ''), candidate.id);
        option.disabled = slots().some(function (other, otherIndex) { return otherIndex !== index && other && catalog.get(other.id).group === candidate.group; });
        select.appendChild(option);
      });
      select.value = slot ? slot.id : '';
      select.addEventListener('change', function () { setSlot(index, select.value, slot ? slot.level : 10); });
      effect.appendChild(select);
      var controls = document.createElement('div'); controls.className = 'food-values';
      var levelLabel = document.createElement('label'); levelLabel.className = 'food-level'; levelLabel.textContent = 'Lv.';
      var level = document.createElement('input'); level.type = 'number'; level.min = '1'; level.max = '10'; level.step = '1';
      level.value = slot ? String(slot.level) : '10'; level.disabled = !slot; level.setAttribute('aria-label', '요리 ' + (index + 1) + ' 레벨');
      level.addEventListener('change', function () { setSlot(index, slot.id, level.value); }); levelLabel.appendChild(level);
      var amount = document.createElement('input'); amount.type = 'text'; amount.readOnly = true; amount.tabIndex = -1; amount.className = 'food-amount';
      amount.setAttribute('aria-label', '요리 ' + (index + 1) + ' 제공량');
      amount.value = recipe ? (recipe.values[slot.level - 1] >= 0 ? '+' : '') + recipe.values[slot.level - 1] + (recipe.percent ? '%' : '') : '—';
      controls.append(levelLabel, amount);
      var clear = document.createElement('button'); clear.type = 'button'; clear.className = 'food-clear'; clear.textContent = '✕'; clear.disabled = !slot;
      clear.setAttribute('aria-label', '요리 ' + (index + 1) + ' 해제'); clear.addEventListener('click', function () { setSlot(index, '', 10); });
      row.append(effect, controls, clear); container.appendChild(row);
    });
  }
  const api = Object.freeze({ getSelections:selections, isGuildEnabled:function () { return guildEnabled(); }, restore:function (value, guild) { buildStore.commitBuild({myRoomFood:catalog.normalize(value),guildFoodBuff:guild !== false}); render(); }, render:render });
  function initialize() {
    var guild = document.getElementById('guildFoodBuff');
    if (guild) guild.addEventListener('change', function () { buildStore.commitBuild({guildFoodBuff:guild.checked}); changed(); });
    render();
  }

initialize(); return api;
}
