import {statRegistry} from '../calculation/stat-registry.js';
import {buildStore} from '../application/build-draft-store.js';
import { createEquipmentSelection, validateEquipmentSelection, resolveEquipmentOptions, subEquipmentUsesOptions } from '../application/item-catalog.mjs';

export function createEquipmentItemUi(documentRef, catalog) {
  const windowRef = documentRef.defaultView;
  const selectionFor = slot => buildStore.getBuild().equipment?.[slot]?.catalogItem || null;
  function setSelection(slot, selection) {
    const store = buildStore, equipment = store.getBuild().equipment || {}, piece = {...equipment[slot]};
    if (selection) piece.catalogItem = selection; else delete piece.catalogItem;
    store.commitBuild({equipment:{...equipment,[slot]:piece}});
  }
  const containers = { mainWeapon:'wpnOpts', subWeapon:'subOpts', armor:'armOpts', additional:'addOpts', special:'spcOpts' };
  const kinds = { mainWeapon:'weapons', subWeapon:'weapons', armor:'armor', additional:'additional', special:'special' };
  const summaries = {};
  let panel, target, locale, search, results, preview, apply, rows = [], generation = 0, loading = false;
  const node = id => documentRef.getElementById(id);
  const registry = () => statRegistry;
  const context = () => ({ mainType:node('mainWeaponType').value, subType:node('subWeaponType').value, armorType:node('armorType').value,
    activeItemEventTypes:[3,9].filter(type => node(`itemEvent${type}`)?.checked) });
  function text(tag, value) { const element = documentRef.createElement(tag); element.textContent = value; return element; }
  function changed() {
    documentRef.dispatchEvent(new windowRef.CustomEvent('toram:build-options-changed'));
    documentRef.dispatchEvent(new windowRef.CustomEvent('toram:persistent-state-changed'));
  }
  function renderSummary(slot) {
    const box = summaries[slot];
    if (!box) return;
    box.replaceChildren();
    const selection = selectionFor(slot);
    if (!selection) return;
    box.append(text('p', `${selection.name ?? '(이름 없음)'} · #${selection.gameItemId} · ${selection.cacheVersion}`));
    try {
      const options = resolveEquipmentOptions(selection, slot, context(), registry());
      if (slot === 'subWeapon' && !subEquipmentUsesOptions(selection.typeId)) box.append(text('p', '보조 무기 일반 옵션 미적용 · 수동 보정 유지'));
      box.append(text('p', options.map(option => `${option.key} ${option.value > 0 ? '+' : ''}${option.value}${registry().get(option.key).status === 'notModeled' ? ' (계산 미지원·보존)' : ''}`).join(', ') || '현재 조건에서 추가 옵션 없음'));
    } catch (error) { box.append(text('p', error.message)); }
    const clear = text('button', '원본 장비 해제');
    clear.type = 'button';
    clear.addEventListener('click', () => { setSelection(slot,null); renderSummary(slot); changed(); });
    box.append(clear);
  }
  function renderList() {
    generation++;
    apply.disabled = true;
    preview.textContent = '';
    results.replaceChildren();
    const query = search.value.trim().toLocaleLowerCase();
    const filtered = rows.filter(row => `${row.name ?? ''} ${row.id}`.toLocaleLowerCase().includes(query));
    for (const row of filtered) {
      const option = text('option', `${row.name ?? '(이름 없음)'} · #${row.id}`);
      option.value = String(row.id); results.append(option);
    }
    results.selectedIndex = -1;
    preview.textContent = `${filtered.length}개`;
  }
  async function loadList() {
    const current = ++generation, kind = kinds[target.value], language = locale.value;
    loading = true; apply.disabled = true; rows = []; results.replaceChildren(); preview.textContent = '목록을 불러오는 중…';
    try {
      const loaded = await catalog.listItems(kind, language);
      if (current !== generation) return;
      loading = false; rows = loaded; renderList();
    } catch (error) { if (current === generation) { loading = false; preview.textContent = error.message; } }
  }
  async function showItem() {
    const current = ++generation;
    apply.disabled = true;
    if (!results.value) return;
    try {
      const item = await catalog.getItem(Number(results.value), locale.value);
      if (current !== generation) return;
      preview.textContent = `${item.name ?? '(이름 없음)'} · #${item.id} · ${item.cacheVersion}`;
      const selection = createEquipmentSelection(item, target.value, context(), registry());
      const options = resolveEquipmentOptions(selection, target.value, context(), registry());
      if (target.value === 'subWeapon' && !subEquipmentUsesOptions(selection.typeId)) preview.textContent += '\n보조 무기 일반 옵션 미적용 · 수동 보정 유지';
      preview.textContent += '\n' + options.map(option => `${option.key}: ${option.value}${registry().get(option.key).status === 'notModeled' ? ' (계산 미지원·보존)' : ''}`).join(', ');
      apply.disabled = false;
    } catch (error) { if (current === generation) preview.textContent += '\n' + error.message; }
  }
  async function applyItem() {
    const current = ++generation, slot = target.value, id = Number(results.value);
    apply.disabled = true;
    try {
      const item = await catalog.getItem(id, locale.value);
      if (current !== generation) return;
      const selection = createEquipmentSelection(item, slot, context(), registry());
      setSelection(slot,selection);
      renderSummary(slot); changed();
      preview.textContent = `${item.name ?? '#' + id} 옵션 적용 완료 · ATK·안정률·제련은 직접 입력`;
      apply.disabled = false;
    } catch (error) { if (current === generation) preview.textContent = error.message; }
  }
  return Object.freeze({
    getSelection(slot) { return selectionFor(slot); },
    restoreSelection(slot, selection) {
      if (!Object.hasOwn(containers, slot)) {
        if (selection) throw new Error('지원하지 않는 장비 칸입니다.');
        return;
      }
      if (selection) {
        validateEquipmentSelection(selection, registry(), slot);
        setSelection(slot,selection);
      } else setSelection(slot,null);
      renderSummary(slot);
    },
    bind() {
      panel = node('gameItemEquipment');
      if (!panel) return;
      target = node('gameItemTarget'); locale = node('gameItemLocale'); search = node('gameItemSearch');
      results = node('gameItemResults'); preview = node('gameItemPreview'); apply = node('gameItemApply');
      for (const [slot, id] of Object.entries(containers)) {
        summaries[slot] = documentRef.createElement('div');
        summaries[slot].dataset.gameEquipment = slot;
        node(id).before(summaries[slot]); renderSummary(slot);
      }
      node('gameItemLoad').addEventListener('click', loadList);
      target.addEventListener('change', loadList); locale.addEventListener('change', loadList);
      search.addEventListener('input', () => { if (!loading) renderList(); }); results.addEventListener('change', showItem);
      apply.addEventListener('click', applyItem);
      documentRef.addEventListener('change', event => {
        if (!['mainWeaponType','subWeaponType','armorType','itemEvent3','itemEvent9'].includes(event.target.id)) return;
        for (const slot of Object.keys(containers)) renderSummary(slot);
        if (results.value) void showItem();
      });
    }
  });
}
