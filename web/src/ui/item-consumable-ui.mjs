import { createConsumableBuffSelection, resolveConsumableBuffs } from '../application/item-catalog.mjs';

export function createConsumableBuffUi(documentRef, catalog) {
  const windowRef = documentRef.defaultView;
  let selections = [], names = [], generation = 0, loading = false;
  let results, search, locale, preview, apply, selected;
  const node = id => documentRef.getElementById(id);
  const registry = () => windowRef.ToramStatRegistry;
  function text(tag, value) { const element = documentRef.createElement(tag); element.textContent = value; return element; }
  const categoryLabel = item => item.consumableCategory ? (item.consumableCategory.names[locale.value] ?? item.consumableCategory.id) : '';
  function changed() {
    documentRef.dispatchEvent(new windowRef.CustomEvent('toram:build-options-changed'));
    documentRef.dispatchEvent(new windowRef.CustomEvent('toram:persistent-state-changed'));
  }
  function renderSelected() {
    if (!selected) return;
    node('gameConsumableCount').textContent = selections.length ? `(${selections.length}개 적용 중)` : '';
    selected.replaceChildren();
    for (const selection of selections) {
      const row = documentRef.createElement('div');
      row.dataset.consumableId = String(selection.gameItemId);
      row.append(text('p', `${selection.name ?? '(이름 없음)'} · #${selection.gameItemId} · ${selection.durationSeconds}초`));
      row.append(text('p', Object.entries(selection.stats).map(([key, value]) => `${key} ${value > 0 ? '+' : ''}${value}${registry().get(key).status === 'notModeled' ? ' (계산 미지원·보존)' : ''}`).join(', ')));
      const remove = text('button', '버프 해제'); remove.type = 'button';
      remove.addEventListener('click', () => { selections = selections.filter(item => item !== selection); renderSelected(); changed(); });
      row.append(remove); selected.append(row);
    }
  }
  function renderList() {
    generation++; apply.disabled = true; results.replaceChildren();
    const query = search.value.toLocaleLowerCase().replace(/\s+/gu,'');
    for (const item of names.filter(item => `${categoryLabel(item)} ${item.name ?? ''} ${item.id}`.toLocaleLowerCase().replace(/\s+/gu,'').includes(query))) {
      const category = categoryLabel(item);
      const option = text('option', `${category ? '[' + category + '] ' : ''}${item.name ?? '(이름 없음)'} · #${item.id}`);
      option.value = String(item.id); results.append(option);
    }
    results.selectedIndex = -1;
    preview.textContent = `${results.options.length}개`;
  }
  async function loadList() {
    const current = ++generation;
    loading = true; apply.disabled = true; names = []; results.replaceChildren(); preview.textContent = '버프 아이템을 불러오는 중…';
    try {
      const loaded = await catalog.listBuffItems(locale.value);
      if (current !== generation) return;
      loading = false; names = loaded; renderList();
    } catch (error) { if (current === generation) { loading = false; preview.textContent = error.message; } }
  }
  async function showItem() {
    const current = ++generation; apply.disabled = true;
    if (!results.value) return;
    try {
      const item = await catalog.getItem(Number(results.value), locale.value);
      if (current !== generation) return;
      const selection = createConsumableBuffSelection(item, registry());
      const category = categoryLabel(item);
      preview.textContent = `${category ? '[' + category + '] ' : ''}${selection.name ?? '(이름 없음)'} · #${selection.gameItemId} · ${selection.durationSeconds}초\n`
        + Object.entries(selection.stats).map(([key, value]) => `${key}: ${value}${registry().get(key).status === 'notModeled' ? ' (계산 미지원·보존)' : ''}`).join(', ');
      apply.disabled = false;
    } catch (error) { if (current === generation) preview.textContent = error.message; }
  }
  async function applyItem() {
    const current = ++generation; apply.disabled = true;
    try {
      const item = await catalog.getItem(Number(results.value), locale.value);
      if (current !== generation) return;
      const selection = createConsumableBuffSelection(item, registry());
      const next = selections.filter(other => other.buffGroupId !== selection.buffGroupId).concat(selection);
      resolveConsumableBuffs(next, registry());
      selections = next; renderSelected(); changed();
      preview.textContent = `${selection.name ?? '#' + selection.gameItemId} 사용 중으로 적용했습니다.`; apply.disabled = false;
    } catch (error) { if (current === generation) preview.textContent = error.message; }
  }
  return Object.freeze({
    getSelections() { return JSON.parse(JSON.stringify(selections)); },
    restoreSelections(value) {
      resolveConsumableBuffs(value, registry());
      selections = JSON.parse(JSON.stringify(value)); renderSelected();
    },
    bind() {
      if (!node('gameConsumableBuffs')) return;
      results = node('gameConsumableResults'); search = node('gameConsumableSearch'); locale = node('gameConsumableLocale');
      preview = node('gameConsumablePreview'); apply = node('gameConsumableApply'); selected = node('gameConsumableSelected');
      renderSelected();
      node('gameConsumableLoad').addEventListener('click', loadList); locale.addEventListener('change', loadList);
      search.addEventListener('input', () => { if (!loading) renderList(); }); results.addEventListener('change', showItem);
      apply.addEventListener('click', applyItem);
    }
  });
}
