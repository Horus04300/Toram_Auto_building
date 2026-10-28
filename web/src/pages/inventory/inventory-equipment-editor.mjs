import {statRegistry} from '../../calculation/stat-registry.js';
import { EQUIPMENT_SLOTS, EQUIPMENT_TYPES, EQUIPMENT_SLOT_TYPES } from '../../application/equipment-object.mjs';
import { createEquipmentDraft } from '../../application/inventory-equipment-draft.mjs';
import { STAT_LABELS } from '../../application/stat-labels.mjs';

export function createInventoryEquipmentEditor(documentRef,page,app) {
  const root = documentRef.defaultView, panel = page.querySelector('.inventory-create');
  panel.innerHTML = `
    <nav class="inventory-create-tabs" aria-label="장비 입력 구분"><button type="button" data-step="base" aria-pressed="false">종류</button><button type="button" data-step="values" aria-pressed="true">수치</button><button type="button" data-step="options" aria-pressed="false">옵션</button><button type="button" data-step="crystas" aria-pressed="false">크리스타</button></nav>
    <form class="inventory-create-form" novalidate>
      <section data-editor-panel="base" hidden><fieldset><legend>장비 부위</legend><div class="inventory-create-slots"></div></fieldset><fieldset><legend>장비 종류</legend><div class="inventory-create-types"></div></fieldset></section><section data-editor-panel="values"><div class="inventory-create-values"><label>ATK<input name="attack" type="number" step="any" value="0" required></label><label>제련값<input name="refinement" type="number" step="any" value="0" required></label><label>안정률 (%)<input name="stability" type="number" step="any" value="0" required></label></div></section>
      <section data-editor-panel="options" hidden><header><h4>수동 옵션</h4><button type="button" data-create="add-option">옵션 추가</button></header><div class="inventory-create-options"></div></section>
      <section data-editor-panel="crystas" hidden><p class="inventory-create-no-crystas" hidden>보조무기는 크리스타 슬롯을 사용하지 않습니다.</p><div class="inventory-create-crystas">${[0,1].map(index => `<div><label>크리스타 ${index + 1}<input name="crysta${index}" list="inventoryCrystaNames" placeholder="크리스타 이름 또는 게임 ID"></label><label class="inventory-create-lock"><input name="lock${index}" type="checkbox">추천 시 잠금</label></div>`).join('')}<datalist id="inventoryCrystaNames"></datalist></div><p class="inventory-create-crysta-status" role="status"></p></section>
    </form>`;
  const form = panel.querySelector('form'), find = selector => panel.querySelector(selector);
  let slot = 'mainWeapon', type = '한손검', options = [], dirty = false, crystas, record;
  function makeButton(label,selected,handler) {
    const node = documentRef.createElement('button'); node.type = 'button'; node.textContent = label; node.setAttribute('aria-pressed',String(selected)); node.addEventListener('click',() => {handler(); if (!node.isConnected) Array.from(panel.querySelectorAll('button')).find(button => button.textContent === label && button.getClientRects().length)?.focus({preventScroll:true});}); return node;
  }
  function renderTypes() {
    find('.inventory-create-slots').replaceChildren(...Object.entries(EQUIPMENT_SLOTS).map(([id,label]) => makeButton(label,id === slot,() => {slot = id; type = EQUIPMENT_SLOT_TYPES[id][0]; dirty = true; renderTypes();})));
    find('.inventory-create-types').replaceChildren(...EQUIPMENT_SLOT_TYPES[slot].map(value => makeButton(value || EQUIPMENT_SLOTS[slot],value === type,() => {type = value; dirty = true; renderTypes();})));
    const weapon = ['mainWeapon','subWeapon'].includes(slot);
    find('.inventory-create-values').hidden = !weapon;
    for (const key of ['attack','refinement','stability']) form.elements[key].required = weapon;
    find('.inventory-create-crystas').hidden = slot === 'subWeapon'; find('.inventory-create-no-crystas').hidden = slot !== 'subWeapon';
  }
  function renderOptions() {
    const target = find('.inventory-create-options'); target.replaceChildren();
    const keys = statRegistry.entries().filter(definition => !['CAST_RED','DAMAGE_P'].includes(definition.id));
    for (const option of options) {
      const row = documentRef.createElement('div'); row.className = 'inventory-create-option';
      const keyLabel = documentRef.createElement('label'); keyLabel.textContent = '옵션';
      const key = documentRef.createElement('select'); key.setAttribute('aria-label','장비 옵션');
      key.replaceChildren(...keys.map(definition => new root.Option((STAT_LABELS[definition.id] || definition.id) + (definition.status === 'notModeled' ? ' (계산 미반영)' : ''),definition.id))); key.value = option.key;
      key.addEventListener('change',() => {option.key = key.value; dirty = true;}); keyLabel.append(key);
      const valueLabel = documentRef.createElement('label'); valueLabel.textContent = '수치'; const value = documentRef.createElement('input'); value.type = 'number'; value.step = 'any'; value.required = true; value.value = option.value; value.setAttribute('aria-label','장비 옵션 수치');
      value.addEventListener('input',() => {option.value = value.value; dirty = true;}); valueLabel.append(value);
      const remove = documentRef.createElement('button'); remove.type = 'button'; remove.textContent = '제거'; remove.addEventListener('click',() => {options = options.filter(item => item !== option); dirty = true; renderOptions();}); row.append(keyLabel,valueLabel,remove); target.append(row);
    }
    find('[data-create="add-option"]').disabled = options.length >= 100;
  }
  async function loadCrystas() {
    const status = find('.inventory-create-crysta-status');
    try {
      crystas = await app.items.getCrystaCatalog();
      find('datalist').replaceChildren(...Object.values(crystas).filter(item => item.names?.kr).map(item => new root.Option(`#${item.gameItemId}`,item.names.kr)));
      status.textContent = '';
    } catch (error) {status.textContent = error.message;}
  }
  function step(id) {panel.querySelectorAll('[data-step]').forEach(button => button.setAttribute('aria-pressed',String(button.dataset.step === id))); panel.querySelectorAll('[data-editor-panel]').forEach(node => {node.hidden = node.dataset.editorPanel !== id;}); if (id === 'crystas') void loadCrystas();}
  panel.addEventListener('input',() => {dirty = true;});
  for (const button of panel.querySelectorAll('[data-step]')) button.addEventListener('click',() => step(button.dataset.step));
  find('[data-create="add-option"]').addEventListener('click',() => {if (options.length >= 100) return; options.push({key:'ATKP',value:'0'}); dirty = true; renderOptions();});
  function close() {panel.hidden = true; dirty = false; page.classList.remove('inventory-is-creating');}
  return {form,close,record:() => record,saved(value) {record = value; dirty = false;},isOpen:() => !panel.hidden,isDirty:() => dirty,refreshControls() {
    find('[data-create="add-option"]').disabled = options.length >= 100;
  },
    open(state,value) {
      form.reset(); options = structuredClone(value?.data.equipment.options || []); dirty = false; record = value;
      slot = value?.data.slot || state.slot || (['armor','additional','special'].includes(state.equipmentType) ? state.equipmentType : 'mainWeapon');
      type = value?.data.equipment.type ?? EQUIPMENT_SLOT_TYPES[slot].find(value => EQUIPMENT_TYPES[state.equipmentType]?.includes(value)) ?? EQUIPMENT_SLOT_TYPES[slot][0];
      const equipment = value?.data.equipment;
      for (const key of ['attack','refinement','stability']) form.elements[key].value = equipment?.[key] ?? 0;
      for (let index = 0; index < 2; index++) {form.elements['crysta' + index].value = equipment?.crystas[index] || ''; form.elements['lock' + index].checked = equipment?.lockedCrystaSlots[index] || false;}
      renderTypes(); renderOptions(); step('values'); panel.hidden = false; page.classList.add('inventory-is-creating');
    },
    async read() {
      const crystalValues = [form.elements.crysta0.value,form.elements.crysta1.value];
      if (slot !== 'subWeapon' && crystalValues.some(value => value.trim())) crystas = await app.items.getCrystaCatalog();
      const data = createEquipmentDraft({slot,type,attack:form.elements.attack.value,refinement:form.elements.refinement.value,stability:form.elements.stability.value,options,crystas:crystalValues,lockedCrystaSlots:[form.elements.lock0.checked,form.elements.lock1.checked]},statRegistry,crystas);
      if (record?.data.slot === slot && record.data.equipment.type === type && record.data.equipment.catalogItem) data.equipment.catalogItem = structuredClone(record.data.equipment.catalogItem);
      return {name:record?.name || '새 무기',type:'equipment',data};
    }
  };
}
