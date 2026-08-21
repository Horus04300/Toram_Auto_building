/* 콤보 탭 UI: 인게임식 아이콘 체인과 선택 순번 편집기를 제공한다. */
(function () {
  'use strict';
  var storageKey = 'toram.combo-sequence.v1';
  var maxEntries = 8;
  var state = { entries:[], selectedIndex:0 };
  var panel, chain, editor, output, status, mpReadout;
  var appliedHit = null;
  var dragState = { index:null, target:null, after:false, touch:null };

  function definitions() {
    var root = window.TORAM_SKILL_EFFECT_DATA && window.TORAM_SKILL_EFFECT_DATA.skills || [];
    var registry = window.ToramSkillEffectRegistry;
    return root.concat(registry ? registry.all() : []);
  }
  function levelFor(skill) {
    if (!window.skillSimulatorState) return 0;
    var levels = window.skillSimulatorState.getInvestments();
    return Number(levels[skill.treeId] && levels[skill.treeId][skill.skillId]) || 0;
  }
  function availableSkills() {
    var byId = new Map();
    definitions().forEach(function (skill) {
      if (!byId.has(skill.id) && skill.sourceRef && ['attack','buff','utility'].indexOf(skill.kind) >= 0 && levelFor(skill) > 0) byId.set(skill.id, skill);
    });
    var catalog = window.TORAM_SKILL_COMBAT_CATALOG && window.TORAM_SKILL_COMBAT_CATALOG.skills || [];
    return catalog.map(function (item) { return byId.get(item.id); }).filter(Boolean);
  }
  function iconFor(skill) {
    var simulator = window.skillSimulatorState;
    var tree = simulator && simulator.data.trees.find(function (item) { return item.id === skill.treeId; });
    var node = tree && tree.skills.find(function (item) { return item.id === skill.skillId; });
    return node ? node.icon : '';
  }
  function load() {
    try {
      var saved = JSON.parse(window.localStorage.getItem(storageKey) || 'null');
      if (saved && Array.isArray(saved.entries)) {
        state.entries = saved.entries.slice(0, maxEntries).map(function (entry) {
          return { skillId:String(entry.skillId || ''), tag:String(entry.tag || 'none'), includeSpecialAttack:Boolean(entry.includeSpecialAttack), inputs:entry.inputs && typeof entry.inputs === 'object' ? Object.assign({}, entry.inputs) : {} };
        });
      }
    } catch (error) { state.entries = []; }
  }
  function save() {
    try { window.localStorage.setItem(storageKey, JSON.stringify({ entries:state.entries })); } catch (error) { /* 저장 불가 환경 */ }
  }
  function ensureEntries(skills) {
    var ids = new Set(skills.map(function (skill) { return skill.id; }));
    state.entries = state.entries.filter(function (entry) { return ids.has(entry.skillId); });
    if (!state.entries.length && skills.length) state.entries.push({ skillId:skills[0].id, tag:'none', includeSpecialAttack:false, inputs:{} });
    state.selectedIndex = Math.max(0, Math.min(state.selectedIndex, state.entries.length - 1));
  }
  function skillMap(skills) { var map = new Map(); skills.forEach(function (skill) { map.set(skill.id, skill); }); return map; }
  function tagLabel(tag) { return ({none:'없음',consecutive:'연속공격',swift:'신속',smite:'강타'})[tag] || tag; }
  function modifierText(modifiers) {
    var parts = [];
    if (!modifiers) return '없음';
    if (modifiers.mpCostMultiplier !== 1) parts.push('MP ×' + modifiers.mpCostMultiplier);
    if (modifiers.motionSpeed) parts.push('행동속도 +' + modifiers.motionSpeed + '%');
    if (modifiers.damageMultiplier !== 1) parts.push('피해 ×' + modifiers.damageMultiplier.toFixed(2));
    if (modifiers.physicalChaseDamage) parts.push('물리 추격 +' + modifiers.physicalChaseDamage);
    if (modifiers.shortRangeDamagePercent) parts.push('근거리 위력 +' + modifiers.shortRangeDamagePercent + '%');
    if (modifiers.hit) parts.push('명중 +' + modifiers.hit);
    if (modifiers.skillConstant) parts.push('상수 +' + modifiers.skillConstant);
    if (modifiers.castTimeReductionPercent) parts.push('영창 -' + modifiers.castTimeReductionPercent + '%');
    if (modifiers.guaranteedCritical) parts.push('확정 크리');
    return parts.join(', ') || '없음';
  }
  function currentContexts() {
    if (typeof window.getBaseContext !== 'function' || typeof window.simulateWithCrystas !== 'function' || typeof window.getCurrentCrystas !== 'function') throw new Error('기본 계산기가 준비되지 않았습니다.');
    var base = window.getBaseContext();
    if (typeof window.applyPassiveSkillStats === 'function') window.applyPassiveSkillStats(base);
    var calculated = window.simulateWithCrystas(base, window.getCurrentCrystas());
    return {
      base:base,
      combat:{ STR:calculated.finalSTR, INT:calculated.finalINT, VIT:calculated.finalVIT, AGI:calculated.finalAGI, DEX:calculated.finalDEX, CRT:base.crtBase, ATK:calculated.finalATK, MATK:calculated.finalMATK, ASPD:calculated.finalASPD, CSPD:calculated.finalCSPD, STABILITY:calculated.finalStab, WEAPON_ATK:calculated.finalWeaponAttack },
      maxMp:calculated.finalMaxMP,
      activeBuffs:window.ToramActiveBuffs && window.ToramActiveBuffs.getSelections ? window.ToramActiveBuffs.getSelections() : {}
    };
  }
  function applyOneShotStats(modifiers) {
    var container = document.getElementById('buffOpts');
    if (!container) return;
    container.querySelectorAll('.combo-transient-option').forEach(function (node) { node.remove(); });
    if (!modifiers || !modifiers.shortRangeDamagePercent) return;
    var row = document.createElement('div'); row.className = 'opt-row combo-transient-option'; row.hidden = true;
    var type = document.createElement('select'); type.className = 'opt-type'; var option = document.createElement('option'); option.value = 'SRW'; option.selected = true; type.appendChild(option);
    var amount = document.createElement('input'); amount.className = 'opt-val'; amount.value = String(modifiers.shortRangeDamagePercent);
    row.append(type, amount); container.appendChild(row);
  }
  function applyHit(hit, damageMultiplier, modifiers) {
    applyOneShotStats(modifiers);
    var mult = hit.effectiveMultiplier === undefined ? hit.multiplier * damageMultiplier : hit.effectiveMultiplier;
    appliedHit = {
      skillMult:mult,
      skillConst:hit.constant,
      atkType:hit.damageType === 'magic' ? 'MAG' : 'PHYS',
      rangeType:hit.flags && hit.flags.longRange ? 'LONG' : 'SHORT',
      unsheathe:Boolean(hit.flags && hit.flags.unsheathe),
      guaranteedCritical:Boolean(hit.flags && hit.flags.guaranteedCritical)
    };
    status.textContent = '선택한 타격의 계수·상수·공격 유형·발도/치명타 판정을 결과 계산에 반영했습니다.';
  }
  function hitRow(hit, damageMultiplier, label, modifiers) {
    var row = document.createElement('div'); row.className = 'combo-hit-row';
    var mult = hit.effectiveMultiplier === undefined ? hit.multiplier * damageMultiplier : hit.effectiveMultiplier;
    var text = document.createElement('span'); text.textContent = label + ' · ' + hit.count + '타 · 계수 ' + Number(mult.toFixed(4)) + ' · 상수 ' + hit.constant;
    var button = document.createElement('button'); button.type = 'button'; button.className = 'combo-apply-button'; button.textContent = '대미지 입력에 적용';
    button.addEventListener('click', function () { applyHit(hit, damageMultiplier, modifiers); });
    row.append(text, button); return row;
  }
  function effectSummary(entry) {
    return (entry.effects || []).filter(function (effect) { return effect.type === 'stat'; }).map(function (effect) { return effect.key + ' ' + (effect.value >= 0 ? '+' : '') + effect.value; }).join(', ');
  }
  function clearDropMarkers() {
    chain.querySelectorAll('.is-dragging, .is-drop-before, .is-drop-after').forEach(function (node) { node.classList.remove('is-dragging', 'is-drop-before', 'is-drop-after'); });
  }
  function setDropTarget(node, x) {
    clearDropMarkers();
    if (!node || !node.classList.contains('combo-chain-node') || Number(node.dataset.comboIndex) === dragState.index) { dragState.target = null; return; }
    dragState.target = Number(node.dataset.comboIndex);
    dragState.after = x > node.getBoundingClientRect().left + node.getBoundingClientRect().width / 2;
    node.classList.add(dragState.after ? 'is-drop-after' : 'is-drop-before');
  }
  function moveEntry() {
    var from = dragState.index, target = dragState.target, after = dragState.after;
    dragState.index = null; dragState.target = null; dragState.after = false; dragState.touch = null; clearDropMarkers();
    if (!Number.isInteger(from) || !Number.isInteger(target) || from === target) return;
    var item = state.entries.splice(from, 1)[0], destination = target + (after ? 1 : 0);
    if (from < destination) destination -= 1;
    state.entries.splice(destination, 0, item); state.selectedIndex = destination; save(); renderWorkspace();
    status.textContent = (from + 1) + '번째 스킬을 ' + (destination + 1) + '번째로 이동했습니다.';
  }
  function bindReorderEvents(node, index) {
    node.draggable = true; node.dataset.comboIndex = String(index);
    node.addEventListener('dragstart', function (event) { dragState.index = index; node.classList.add('is-dragging'); if (event.dataTransfer) event.dataTransfer.effectAllowed = 'move'; });
    node.addEventListener('dragover', function (event) { event.preventDefault(); setDropTarget(node, event.clientX); });
    node.addEventListener('drop', function (event) { event.preventDefault(); setDropTarget(node, event.clientX); moveEntry(); });
    node.addEventListener('dragend', function () { if (dragState.index !== null) moveEntry(); });
    node.addEventListener('pointerdown', function (event) { if (event.pointerType !== 'mouse') dragState.touch = { id:event.pointerId, index:index, x:event.clientX, y:event.clientY }; });
    node.addEventListener('pointermove', function (event) { var touch = dragState.touch; if (!touch || touch.id !== event.pointerId || Math.hypot(event.clientX - touch.x, event.clientY - touch.y) < 10) return; dragState.index = touch.index; var hit=document.elementFromPoint(event.clientX,event.clientY); setDropTarget(hit && hit.closest('.combo-chain-node'), event.clientX); event.preventDefault(); });
    node.addEventListener('pointerup', function (event) { if (dragState.touch && dragState.touch.id === event.pointerId && dragState.index !== null) { event.preventDefault(); moveEntry(); } });
    node.addEventListener('pointercancel', function () { dragState.touch = null; clearDropMarkers(); });
  }
  function renderChain(skills, result) {
    chain.innerHTML = '';
    var byId = skillMap(skills);
    state.entries.forEach(function (item, index) {
      var skill = byId.get(item.skillId);
      var evaluated = result && result.entries[index];
      var node = document.createElement('button'); node.type = 'button'; node.className = 'combo-chain-node';
      if (state.selectedIndex === index) node.classList.add('is-selected');
      if (evaluated && evaluated.executionStatus === 'canceled') node.classList.add('is-canceled');
      if (evaluated && evaluated.executionStatus === 'skipped') node.classList.add('is-skipped');
      node.setAttribute('aria-label', (index + 1) + '번 ' + (skill ? skill.nameKo : item.skillId));
      var badge = document.createElement('span'); badge.className = 'combo-chain-position'; badge.textContent = String(index + 1);
      var iconShell = document.createElement('span'); iconShell.className = 'combo-chain-icon';
      var image = document.createElement('img'); image.src = encodeURI(skill ? iconFor(skill) : ''); image.alt = ''; iconShell.appendChild(image);
      var name = document.createElement('span'); name.className = 'combo-chain-name'; name.textContent = skill ? skill.nameKo : item.skillId;
      var mp = document.createElement('span'); mp.className = 'combo-chain-mp';
      if (!evaluated) mp.textContent = '';
      else if (evaluated.executionStatus === 'canceled') mp.textContent = '취소 · 필요 ' + evaluated.finalMp;
      else if (evaluated.executionStatus === 'skipped') mp.textContent = '미실행';
      else mp.textContent = '-' + evaluated.finalMp + ' MP · 잔여 ' + evaluated.mpAfter;
      node.append(badge, iconShell, name, mp);
      bindReorderEvents(node, index);
      node.addEventListener('click', function () { state.selectedIndex = index; renderEditor(skills); renderChain(skills, result); });
      chain.appendChild(node);
    });
    var add = document.createElement('button'); add.type = 'button'; add.id = 'comboAddEntry'; add.className = 'combo-chain-add'; add.innerHTML = '<span>＋</span><small>스킬 추가</small>';
    add.disabled = state.entries.length >= maxEntries || !skills.length;
    add.addEventListener('click', function () {
      if (add.disabled) return;
      state.entries.push({ skillId:skills[0].id, tag:'none', includeSpecialAttack:false, inputs:{} });
      state.selectedIndex = state.entries.length - 1;
      renderWorkspace();
    });
    chain.appendChild(add);
  }
  function renderEditor(skills) {
    editor.innerHTML = '';
    var entry = state.entries[state.selectedIndex];
    if (!entry) return;
    var extras = document.createElement('div'); extras.className = 'combo-editor-extras';
    var position = document.createElement('strong'); position.className = 'combo-editor-position'; position.textContent = (state.selectedIndex + 1) + '번째';

    var skillField = document.createElement('label'); skillField.className = 'combo-editor-field combo-editor-skill';
    var skillLabel = document.createElement('span'); skillLabel.textContent = '스킬';
    var skillSelect = document.createElement('select'); skillSelect.className = 'combo-skill-select';
    skills.forEach(function (skill) {
      var option = document.createElement('option'); option.value = skill.id; option.textContent = skill.nameKo + ' Lv.' + levelFor(skill); option.selected = skill.id === entry.skillId; skillSelect.appendChild(option);
    });
    skillSelect.addEventListener('change', function () { entry.skillId = skillSelect.value; entry.includeSpecialAttack = false; save(); renderWorkspace(); });
    skillField.append(skillLabel, skillSelect);

    var tagField = document.createElement('label'); tagField.className = 'combo-editor-field combo-editor-tag';
    var tagLabelNode = document.createElement('span'); tagLabelNode.textContent = '콤보 효과';
    var tagSelect = document.createElement('select'); tagSelect.className = 'combo-tag-select'; tagSelect.disabled = state.selectedIndex === 0;
    ['none','consecutive','swift','smite'].forEach(function (tag) {
      var option = document.createElement('option'); option.value = tag; option.textContent = tagLabel(tag); option.selected = (state.selectedIndex === 0 ? 'none' : entry.tag) === tag; tagSelect.appendChild(option);
    });
    tagSelect.addEventListener('change', function () { entry.tag = tagSelect.value; save(); calculate(); });
    tagField.append(tagLabelNode, tagSelect);

    var definition = definitions().find(function (skill) { return skill.id === entry.skillId; });
    if (definition && Array.isArray(definition.inputs) && definition.inputs.length) {
      entry.inputs = entry.inputs || {};
      definition.inputs.forEach(function (input) {
        var inputField = document.createElement('label'); inputField.className = 'combo-editor-field combo-editor-input';
        var inputLabel = document.createElement('span'); inputLabel.textContent = input.label || input.id;
        var control;
        if (input.type === 'boolean') {
          control = document.createElement('input'); control.type = 'checkbox'; control.checked = Boolean(entry.inputs[input.id]);
          control.addEventListener('change', function () { entry.inputs[input.id] = control.checked; save(); calculate(); });
        } else {
          control = document.createElement('input'); control.type = 'number'; control.step = '1';
          var fallback = input.default && input.default.op === 'value' ? input.default.value : 0;
          control.value = entry.inputs[input.id] === undefined ? fallback : entry.inputs[input.id];
          control.addEventListener('change', function () { entry.inputs[input.id] = Number(control.value) || 0; save(); calculate(); });
        }
        inputField.append(inputLabel, control); extras.appendChild(inputField);
      });
    }
    if (definition && Array.isArray(definition.specialAttacks) && definition.specialAttacks.length) {
      var finish = document.createElement('label'); finish.className = 'combo-finish-toggle';
      var checkbox = document.createElement('input'); checkbox.type = 'checkbox'; checkbox.checked = entry.includeSpecialAttack;
      checkbox.addEventListener('change', function () { entry.includeSpecialAttack = checkbox.checked; save(); calculate(); });
      finish.append(checkbox, document.createTextNode(definition.specialAttacks[0].notes ? '특수 공격 포함' : '특수 공격 포함')); extras.appendChild(finish);
    }
    var remove = document.createElement('button'); remove.type = 'button'; remove.className = 'combo-remove-button'; remove.textContent = '콤보 삭제'; remove.disabled = state.entries.length === 1;
    remove.addEventListener('click', function () { if (remove.disabled) return; state.entries.splice(state.selectedIndex, 1); state.selectedIndex = Math.min(state.selectedIndex, state.entries.length - 1); save(); renderWorkspace(); });
    editor.append(position, skillField, tagField, remove);
    if (extras.childNodes.length) editor.appendChild(extras);
  }
  function renderOutput(result, skills) {
    output.innerHTML = '';
    var summary = document.createElement('div'); summary.className = 'combo-mp-summary' + (result.canceledAt ? ' has-cancel' : '');
    summary.textContent = '최대 MP ' + result.maxMp + ' · ' + (result.canceledAt ? result.canceledAt + '번째 스킬에서 MP 부족으로 취소' : '콤보 종료 후 잔여 MP ' + result.remainingMp);
    output.appendChild(summary);
    var byId = skillMap(skills);
    result.entries.forEach(function (entry) {
      var card = document.createElement('article'); card.className = 'combo-result-card';
      if (entry.executionStatus === 'canceled') card.classList.add('is-canceled');
      else if (entry.executionStatus === 'skipped') card.classList.add('is-skipped');
      else if (!entry.available) card.classList.add('is-unavailable');
      var fallback = byId.get(entry.skillId);
      var title = document.createElement('h4'); title.textContent = entry.position + '. ' + (entry.skill ? entry.skill.nameKo : fallback ? fallback.nameKo : entry.skillId); card.appendChild(title);
      if (entry.executionStatus === 'canceled') {
        var canceled = document.createElement('p'); canceled.className = 'combo-cancel-message'; canceled.textContent = '현재 MP ' + entry.mpBefore + '보다 소모 MP ' + entry.finalMp + '가 많아 이 스킬에서 콤보가 취소됩니다. 이 스킬의 피해·버프는 계산하지 않습니다.'; card.appendChild(canceled); output.appendChild(card); return;
      }
      if (entry.executionStatus === 'skipped') {
        var skipped = document.createElement('p'); skipped.className = 'combo-skip-message'; skipped.textContent = entry.canceledByPosition + '번째 스킬에서 취소되어 계산하지 않습니다.'; card.appendChild(skipped); output.appendChild(card); return;
      }
      if (!entry.available) {
        var error = document.createElement('p'); error.textContent = entry.error || '현재 장비에서 사용할 수 없습니다.'; card.appendChild(error); output.appendChild(card); return;
      }
      var meta = document.createElement('div'); meta.className = 'combo-result-meta';
      meta.innerHTML = '<span>MP <b>' + entry.mpBefore + ' → ' + entry.mpAfter + '</b> (소모 ' + entry.finalMp + (entry.mpRefund ? ' · 회복 ' + entry.mpRefund : '') + ')</span><span>적용된 1회 효과 <b>' + modifierText(entry.appliedNextSkillModifiers) + '</b></span><span>최종 행동속도 보정 <b>+' + entry.motionSpeed + '%</b></span>' + (entry.castTimeSeconds === null ? '' : '<span>영창 <b>' + Number(entry.castTimeSeconds.toFixed(3)) + '초</b></span>');
      card.appendChild(meta);
      entry.hits.forEach(function (hit, index) { card.appendChild(hitRow(hit, entry.damageMultiplier, '공격 ' + (index + 1), entry.appliedNextSkillModifiers)); });
      var stats = effectSummary(entry); if (stats) { var effect = document.createElement('p'); effect.className = 'combo-effect-note'; effect.textContent = '버프 핵심 효과: ' + stats; card.appendChild(effect); }
      if (entry.physicalChaseDamage) { var chase = document.createElement('p'); chase.className = 'combo-effect-note'; chase.textContent = '이 공격에 오라 블레이드 물리 추격 +' + entry.physicalChaseDamage; card.appendChild(chase); }
      if (entry.generatedState) { var generatedState = document.createElement('p'); generatedState.className = 'combo-effect-note'; generatedState.textContent = '획득 상태: ' + entry.generatedState.stateId + ' +' + entry.generatedState.stacks + '스택'; card.appendChild(generatedState); }
      if (entry.specialAttack && entry.specialAttack.available) {
        var special = document.createElement('section'); special.className = 'combo-special-attack';
        var specialTitle = document.createElement('h5'); specialTitle.textContent = '선택 계산: 특수 공격'; special.appendChild(specialTitle);
        entry.specialAttack.hits.forEach(function (hit, index) { special.appendChild(hitRow(hit, 1, '피니시 ' + (index + 1), null)); }); card.appendChild(special);
      }
      var next = document.createElement('p'); next.className = 'combo-next-note'; next.textContent = '다음 스킬에 생성: ' + modifierText(entry.generatedNextSkillModifiers); card.appendChild(next);
      output.appendChild(card);
    });
    if (!result.canceledAt && result.unconsumedNextSkillModifiers.sources.length) {
      var pending = document.createElement('p'); pending.className = 'combo-pending-warning'; pending.textContent = '마지막 스킬 뒤에 소비되지 않은 효과: ' + modifierText(result.unconsumedNextSkillModifiers); output.appendChild(pending);
    }
  }
  function calculate() {
    status.textContent = '';
    var skills = availableSkills();
    try {
      var contexts = currentContexts();
      var result = window.ToramComboSequence.evaluate(state.entries, contexts.base, contexts.combat, { maxMp:contexts.maxMp, activeBuffs:contexts.activeBuffs });
      mpReadout.textContent = '현재 빌드 최대 MP ' + contexts.maxMp;
      renderChain(skills, result);
      renderOutput(result, skills);
    } catch (error) {
      chain.innerHTML = ''; output.innerHTML = '<p class="combo-error">계산할 수 없습니다: ' + error.message + '</p>';
    }
  }
  function renderWorkspace() {
    var skills = availableSkills(); ensureEntries(skills); save();
    if (!skills.length) { chain.innerHTML = '<p class="combo-empty">먼저 스킬 탭에서 계산할 스킬에 포인트를 투자하세요.</p>'; editor.innerHTML = ''; output.innerHTML = ''; return; }
    renderEditor(skills); calculate();
  }
  function initialize() {
    panel = document.getElementById('appTabPanel-combo');
    if (!panel || !window.ToramComboSequence) return;
    panel.innerHTML = '<section class="combo-workspace"><div class="combo-heading"><div><h3>🔗 스킬·콤보 순서 계산</h3><p>아이콘을 눌러 해당 순번의 스킬과 콤보 효과를 편집합니다.</p></div><strong id="comboMpReadout" class="combo-mp-readout"></strong></div><div id="comboChain" class="combo-chain" aria-label="콤보 스킬 순서"></div><div id="comboEntryEditor" class="combo-entry-editor"></div><p class="combo-order-note">최대 MP = 100 + 레벨 + INT × 0.1 + 장비·크리스타·스킬의 최대 MP. MP 부족 시 해당 스킬부터 계산하지 않습니다.</p><div id="comboSequenceStatus" role="status"></div><div id="comboSequenceOutput"></div></section>';
    chain = document.getElementById('comboChain'); editor = document.getElementById('comboEntryEditor'); output = document.getElementById('comboSequenceOutput'); status = document.getElementById('comboSequenceStatus'); mpReadout = document.getElementById('comboMpReadout');
    load(); renderWorkspace();
    document.addEventListener('toram:skill-investments-changed', renderWorkspace);
  }
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', initialize, {once:true}); else initialize();
  window.ToramComboUi = Object.freeze({
    refresh:function () { if (chain) renderWorkspace(); },
    getAppliedHit:function () { return appliedHit ? Object.assign({}, appliedHit) : null; }
  });
}());
