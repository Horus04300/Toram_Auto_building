import { INVENTORY_TYPES } from '../../application/inventory-objects.mjs';

export function createInventoryMergeUi(documentRef, api, describe, onSaved) {
  const root = documentRef.defaultView, dialog = documentRef.createElement('dialog');
  dialog.className = 'inventory-merge-dialog'; dialog.setAttribute('aria-labelledby','inventoryMergeTitle');
  dialog.innerHTML = `<header><h2 id="inventoryMergeTitle">두 구성 합치기</h2><button type="button" data-action="close" aria-label="병합 닫기">×</button></header>
    <p class="inventory-merge-left"></p><section class="inventory-merge-pick"><form class="inventory-merge-search"><label>가져올 종류<select name="type">${Object.entries(INVENTORY_TYPES).filter(([id]) => id !== 'registlet').map(([id,label]) => `<option value="${id}">${label}</option>`).join('')}</select></label><label>이름 검색<input name="q" maxlength="80" type="search"></label><button type="submit">검색</button></form>
    <label>합칠 구성<select class="inventory-merge-source" size="4" aria-label="합칠 구성"></select></label><nav aria-label="합칠 구성 목록 페이지"><button type="button" data-action="previous">이전</button><span class="inventory-merge-page"></span><button type="button" data-action="next">다음</button></nav><button type="button" data-action="preview">충돌 확인</button></section>
    <section class="inventory-merge-review" hidden><div class="inventory-merge-groups"></div><div class="inventory-merge-conflicts"></div><nav aria-label="충돌 페이지"><button type="button" data-action="conflictPrevious">이전 충돌</button><span class="inventory-merge-conflict-page"></span><button type="button" data-action="conflictNext">다음 충돌</button></nav><label>새 구성 이름<input class="inventory-merge-name" maxlength="80" required></label><p class="inventory-merge-result"></p><footer><button type="button" data-action="resolve">선택 적용</button><button type="button" data-action="save" class="inventory-primary">새 구성으로 저장</button></footer></section>
    <p class="inventory-merge-status" role="status" aria-live="polite"></p>`;
  const find = selector => dialog.querySelector(selector), button = action => find(`[data-action="${action}"]`);
  const search = find('form'), source = find('.inventory-merge-source'), name = find('.inventory-merge-name');
  const status = find('.inventory-merge-status');
  let left, right, preview, listing, currentPage = 1, conflictPage = 0, busy = false, requestKey = null, choices = new Map(), whole = new Map(), complete = false;
  function text(tag, value) { const element = documentRef.createElement(tag); element.textContent = value; return element; }
  function controls() {
    button('previous').disabled = busy || currentPage <= 1; button('next').disabled = busy || !listing || currentPage * listing.pageSize >= listing.total;
    button('save').disabled = busy || !complete;
    button('conflictPrevious').disabled = busy || conflictPage <= 0;
    button('conflictNext').disabled = busy || !preview || (conflictPage + 1) * pageSize() >= preview.conflicts.length;
  }
  async function run(work) {
    if (busy) return;
    busy = true; dialog.setAttribute('aria-busy','true'); dialog.querySelectorAll('button:not([data-action="close"]),input,select').forEach(node => {node.disabled = true;}); status.textContent = '';
    try { await work(); } catch (error) { status.textContent = error.message; }
    finally { busy = false; dialog.removeAttribute('aria-busy'); dialog.querySelectorAll('button,input,select').forEach(node => {node.disabled = false;}); renderDisabled(); controls(); }
  }
  async function load() {
    listing = await api.list({type:search.elements.type.value,q:search.elements.q.value,page:currentPage,pageSize:6});
    source.replaceChildren();
    for (const item of listing.items) { const option = text('option',`${item.name}`); option.value = item.id; source.append(option); }
    source.selectedIndex = listing.items.length ? 0 : -1;
    find('.inventory-merge-page').textContent = `${currentPage} / ${Math.max(1,Math.ceil(listing.total / 6))}`;
    if (!listing.items.length) status.textContent = '이 종류에 저장된 구성이 없습니다.';
  }
  function pageSize() { return root.matchMedia('(max-width:650px)').matches ? 1 : 3; }
  function choiceSelect(unit, label, value, group) {
    const field = text('label',label), select = documentRef.createElement('select'); select.dataset.unit = unit;
    for (const [id,title] of [['',group ? '세부 단위로 선택' : '선택하세요'],['left','왼쪽 사용'],['right','오른쪽 사용']]) { const option = text('option',title); option.value = id; select.append(option); }
    select.value = value || ''; select.addEventListener('change', () => { const target = group ? whole : choices; if (select.value) target.set(unit,select.value); else target.delete(unit); complete = false; requestKey = null; renderDisabled(); controls(); find('.inventory-merge-result').textContent = '선택 적용을 눌러 결과를 확인하세요.'; }); field.append(select); return field;
  }
  function renderDisabled() {
    dialog.querySelectorAll('.inventory-merge-conflicts select').forEach(select => { select.disabled = busy || whole.has(select.dataset.unit.split('.')[0]); });
  }
  function renderConflicts() {
    const panel = find('.inventory-merge-conflicts'); panel.replaceChildren();
    const conflicts = preview.conflicts.slice(conflictPage * pageSize(),(conflictPage + 1) * pageSize());
    for (const conflict of conflicts) {
      const card = documentRef.createElement('section'); card.className = 'inventory-conflict';
      card.append(choiceSelect(conflict.unit,conflict.label,choices.get(conflict.unit),false));
      for (const [side,label] of [['left','왼쪽'],['right','오른쪽']]) {
        const value = conflict[side]; card.append(text('p',`${label}: ${value === null ? '비우기' : conflict.unit === 'context' ? '계산 조건·수동 버프·요리 전체' : describe(value).join(' · ')}`));
      }
      panel.append(card);
    }
    find('.inventory-merge-conflict-page').textContent = preview.conflicts.length ? `${conflictPage + 1} / ${Math.ceil(preview.conflicts.length / pageSize())}` : '충돌 없음';
    renderDisabled(); controls();
  }
  function input() {
    const ref = value => ({objectId:value.id,revision:value.revision});
    return {left:ref(left),right:ref(right),name:name.value,choices:[...whole,...[...choices].filter(([unit]) => !whole.has(unit.split('.')[0]))].map(([unit,take]) => ({unit,take}))};
  }
  async function initialPreview() {
    if (!source.value) throw new Error('합칠 구성을 선택하세요.');
    right = await api.get(source.value); choices = new Map(); whole = new Map(); conflictPage = 0; requestKey = null;
    preview = await api.preview(input()); complete = preview.complete;
    find('.inventory-merge-pick').hidden = true; find('.inventory-merge-review').hidden = false;
    find('.inventory-merge-left').textContent = `왼쪽: ${left.name} · 오른쪽: ${right.name}`;
    const groups = find('.inventory-merge-groups'); groups.replaceChildren();
    for (const group of preview.groups) groups.append(choiceSelect(group.unit,group.label,'',true));
    find('.inventory-merge-result').textContent = `${INVENTORY_TYPES[preview.type]}로 조립 · ${preview.conflicts.length}개 충돌${complete ? ' · 저장 가능' : ''}`;
    renderConflicts();
  }
  search.addEventListener('submit', event => { event.preventDefault(); run(async () => {currentPage = 1; await load();}); });
  for (const [action,delta] of [['previous',-1],['next',1]]) button(action).addEventListener('click', () => run(async () => { currentPage += delta; await load(); }));
  for (const [action,delta] of [['conflictPrevious',-1],['conflictNext',1]]) button(action).addEventListener('click', () => { conflictPage += delta; renderConflicts(); });
  button('preview').addEventListener('click', () => run(initialPreview));
  button('resolve').addEventListener('click', () => run(async () => {
    const resolved = await api.preview(input()); complete = resolved.complete;
    find('.inventory-merge-result').textContent = complete ? `${INVENTORY_TYPES[resolved.type]} · 저장 가능. 원본 두 개는 유지됩니다.` : '남은 충돌을 모두 선택하세요.';
  }));
  name.addEventListener('input', () => { requestKey = null; });
  button('save').addEventListener('click', () => run(async () => {
    if (!name.value.trim()) throw new Error('새 구성 이름을 입력하세요.');
    requestKey ||= root.crypto.randomUUID(); const saved = await api.merge(input(),requestKey);
    await onSaved(saved); dialog.close();
  }));
  button('close').addEventListener('click', () => { if (!busy) dialog.close(); });
  dialog.addEventListener('cancel', event => { if (busy) event.preventDefault(); });
  documentRef.body.append(dialog);
  return Object.freeze({open(record) {
    left = structuredClone(record); right = null; currentPage = 1; conflictPage = 0; complete = false; preview = null;
    choices = new Map(); whole = new Map(); requestKey = null; name.value = (left.name + ' 조립').slice(0,80);
    find('.inventory-merge-left').textContent = `왼쪽: ${left.name} · ${INVENTORY_TYPES[left.type]}`;
    find('.inventory-merge-pick').hidden = false; find('.inventory-merge-review').hidden = true;
    search.elements.type.value = left.type; search.elements.q.value = '';
    dialog.showModal(); run(load);
  }});
}
