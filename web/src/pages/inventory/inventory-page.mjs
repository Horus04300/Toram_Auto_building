import { describeInventoryObject, nextInventoryName } from '../../application/inventory-summary.mjs';
import { EQUIPMENT_TYPES, EQUIPMENT_SLOTS } from '../../application/equipment-object.mjs';
import { INVENTORY_TYPES, comboEntries } from '../../application/inventory-objects.mjs';
import { createInventoryMergeUi } from './inventory-merge-ui.mjs';
import { createInventoryNavigation, emptyInventoryFilters } from './inventory-navigation.mjs';
import { createInventoryEquipmentEditor } from './inventory-equipment-editor.mjs';
import { createInventorySkillEditor } from './inventory-skill-editor.mjs';

export function createInventoryUi(documentRef, account, shell, publish) {
  const root = documentRef.defaultView, api = account.inventory;
  const page = documentRef.createElement('main');
  page.id = 'inventoryWorkspace'; page.hidden = true;
  page.innerHTML = `
    <header class="inventory-heading"><div class="inventory-heading-title"><h2>내 인벤토리</h2><span class="inventory-location" aria-label="현재 인벤토리 위치" aria-live="polite"></span></div></header>
    <section class="inventory-guest" hidden><h3>나만의 구성 보관함</h3><p>로그인하면 구성을 저장하고 다른 빌드에도 사용할 수 있습니다.</p><button type="button" data-action="login">Google 로그인</button></section>
    <div class="inventory-member" hidden><a class="inventory-skip" href="#inventoryEntries">분류 건너뛰기</a><button type="button" class="inventory-navigation-toggle" aria-expanded="false"><span class="inventory-navigation-label"></span><b>분류 변경</b></button><div class="inventory-browser skill-bookmark-layout"><nav class="inventory-major-rail skill-category-rail" aria-label="인벤토리 대분류"></nav><nav class="inventory-group-rail skill-tree-rail" aria-label="인벤토리 소분류"></nav><div class="inventory-shelf">
      <div class="inventory-columns"><section class="inventory-list-panel" aria-label="내 구성 목록"><header class="inventory-pane-heading"><h3>내 목록</h3><div class="inventory-list-actions"><button type="button" data-action="create" hidden>새로 만들기</button><button type="button" data-action="save" class="inventory-primary" hidden>저장</button><button type="button" data-action="refresh">새로고침</button></div></header>
<form class="inventory-search"><label class="inventory-search-name">이름 검색<input type="search" name="q" maxlength="80" placeholder="구성 이름"></label><button type="submit">검색</button><span class="inventory-count"></span></form>
      <details class="inventory-capture-toggle"><summary>계산기 구성 담기</summary><form class="inventory-capture"><label class="inventory-capture-slot">가져올 계산기 부위<select name="slot">${Object.entries(account.slots).map(([id, label]) => `<option value="${id}">${label}</option>`).join('')}</select></label><label class="inventory-capture-tree" hidden>가져올 트리<select name="treeId"></select></label><label class="inventory-capture-consumable" hidden>가져올 도핑<select name="consumableId"></select></label><label>새 구성 이름<input name="name" maxlength="80" required placeholder="예: 보스전용 세팅"></label><button type="submit" class="inventory-primary">현재 구성 담기</button></form></details>
<form class="inventory-rename" hidden><input name="name" maxlength="80" required aria-label="구성 이름"></form><div class="inventory-list" id="inventoryEntries" tabindex="-1"></div></section>
      <section class="inventory-detail" aria-label="구성 작업공간"><button type="button" data-action="list">내 목록</button><section class="inventory-create" aria-label="새 장비 입력" hidden></section><section class="inventory-skill-editor" aria-label="스킬 구성 편집" hidden></section><div class="inventory-placeholder"></div><div class="inventory-selected" hidden>
        <div class="inventory-detail-heading"><span class="inventory-slot"></span></div>

        <nav class="inventory-detail-tabs" aria-label="구성 상세 구분"><button type="button" data-detail-tab="summary">요약</button><button type="button" data-detail-tab="options">옵션·구성</button><button type="button" data-detail-tab="source">출처</button></nav><dl class="inventory-summary" data-detail-panel="summary"></dl><div class="inventory-options" data-detail-panel="options" hidden></div><div class="inventory-combo-label" hidden><label>적용·편집할 콤보<select class="inventory-combo-choice" aria-label="적용할 콤보"></select></label><button type="button" data-action="remove-combo">선택 콤보 제거</button></div><p class="inventory-source" data-detail-panel="source" hidden></p>

      </div>        <div class="inventory-actions"><button type="button" data-action="apply" class="inventory-primary">계산기에 적용</button><button type="button" data-action="edit">계산기에서 편집</button><button type="button" data-action="merge">다른 구성과 합치기</button><button type="button" data-action="publish">게시판에 공개</button><button type="button" data-action="remove">삭제</button></div></section></div>
    </div></div></div><div id="inventoryNavigationDialog" class="inventory-navigation-dialog" popover="auto" role="dialog" aria-labelledby="inventoryNavigationTitle"><header><h3 id="inventoryNavigationTitle"></h3><button type="button" aria-label="세부 종류 선택 닫기">×</button></header><nav class="inventory-leaf-rail" aria-label="인벤토리 세부 종류"></nav></div><p class="inventory-status" role="status" aria-live="polite"></p>`;
  const banner = documentRef.createElement('section');
  banner.className = 'inventory-edit-banner'; banner.hidden = true;
  banner.innerHTML = '<strong></strong><span>변경 후 같은 구성에 저장하거나 인벤토리에서 새 구성으로 담으세요.</span><button type="button" data-action="commit">수정 저장</button><button type="button" data-action="return">인벤토리</button><button type="button" data-action="finish">편집 종료</button><p role="status"></p>';
  const find = selector => page.querySelector(selector), button = action => find(`[data-action="${action}"]`);
  const search = find('.inventory-search'), capture = find('.inventory-capture'), rename = find('.inventory-rename');
  let selected = null, editing = null, editingComboId = null, comboChoiceOwner = null, mergeUi, busy = false, listState = null, routePending = false, capturePending = false, focusAfter = null;
  const navigation = createInventoryNavigation(documentRef,page,changes => run(async () => {
    await saveWorkspace();
    page.classList.remove('inventory-show-list'); setUrl(changes); await refresh();
  }));
  const equipmentEditor = createInventoryEquipmentEditor(documentRef,page,root.ToramApp);
  const skillEditor = createInventorySkillEditor(documentRef,find('.inventory-skill-editor'),api,run);
  const drafts = new Map();
  let draftContext = '', navigationData, shownUrl = root.location.href;
  function active() { return shell.active('inventory'); }
  function message(value = '', error = false) { const node = find('.inventory-status'); node.textContent = value; node.classList.toggle('is-error', error); }
  function text(tag, value) { const node = documentRef.createElement(tag); node.textContent = value; return node; }
  function state() {
    const params = new URL(root.location.href).searchParams;
    return { type:params.get('type') || 'equipment', equipmentType:params.get('equipmentType') || '', slot:params.get('slot') || '', treeId:params.get('treeId') || '', skillCategory:params.get('skillCategory') || '', buffGroupId:params.get('buffGroupId') || '', q:params.get('q') || '', page:params.get('page') || '1', selected:params.get('selected') || '' };
  }
  function setUrl(changes, replace = false) {
    const url = new URL(root.location.href);
    for (const [key, value] of Object.entries(changes)) { if (value) url.searchParams.set(key, value); else url.searchParams.delete(key); }
    root.history[replace ? 'replaceState' : 'pushState'](null, '', url);
    shownUrl = url.href;
  }
  async function run(work) {
    if (busy) return;
    busy = true; page.setAttribute('aria-busy', 'true');
    page.querySelectorAll('button,input,select').forEach(node => { node.disabled = true; });
    banner.querySelectorAll('button').forEach(node => { node.disabled = true; });
    message(); banner.querySelector('p').textContent = '';
    try { return await work(); }
    catch (error) {
      if (error.status === 401) { find('.inventory-member').hidden = true; find('.inventory-guest').hidden = false; }
      if (hasUnsavedWorkspace()) root.history.replaceState(null,'',shownUrl);
      message(error.message, true); banner.querySelector('p').textContent = error.message; return false;
    } finally {
      busy = false; page.removeAttribute('aria-busy');
      page.querySelectorAll('button,input,select').forEach(node => { node.disabled = false; });
      banner.querySelectorAll('button').forEach(node => { node.disabled = false; });
      navigation.render(state()); equipmentEditor.refreshControls();
      focusAfter?.focus(); focusAfter = null;
      if (routePending) { routePending = false; if (active()) void run(connect); }
      else if (capturePending) { capturePending = false; if (find('.inventory-capture-toggle').open) void run(prepareCapture); }
    }
  }
  function renderOptions() {
    const box = find('.inventory-options'); box.replaceChildren();
    if (selected.type !== 'equipment') {box.append(text('h3','구성 내용')); for (const row of describe(selected)) box.append(text('p',row)); return;}
    box.append(text('h3','수동 옵션'));
    const options = selected.data.equipment.options;
    if (!options.length) box.append(text('p','등록한 수동 옵션 없음'));
    for (const option of options) box.append(text('p',`${option.key} ${option.value > 0 ? '+' : ''}${option.value}`));
  }
  const describe = describeInventoryObject;
  function hasUnsavedWorkspace() {return skillEditor.isOpen() && skillEditor.isDirty() || equipmentEditor.isOpen() && equipmentEditor.isDirty() || selected && !rename.hidden && rename.elements.name.value !== selected.name;}
  async function prepareCapture() { await root.ToramApp.ensureCalculator(); captureFields(); }
  function captureFields() {
    const type = state().type;
    find('.inventory-capture-slot').hidden = type !== 'equipment'; find('.inventory-capture-tree').hidden = type !== 'skill_tree'; find('.inventory-capture-consumable').hidden = type !== 'consumable';
    navigation.render(state());
    if (!root.ToramApp.calculatorReady) return;
    const trees = capture.elements.treeId, previousTree = trees.value; trees.replaceChildren();
    for (const tree of root.SKILL_TREE_DATA.trees) { const option = text('option',tree.nameKo || tree.id); option.value = tree.id; trees.append(option); }
    if (previousTree) trees.value = previousTree;
    const consumables = capture.elements.consumableId, previousItem = consumables.value; consumables.replaceChildren();
    for (const item of root.ToramApplication.Settings.snapshot('인벤토리').build.consumableBuffs || []) { const option = text('option',item.name || '#' + item.gameItemId); option.value = String(item.gameItemId); consumables.append(option); }
    if (previousItem) consumables.value = previousItem;
  }
  function detailTab() {
    const value = new URL(root.location.href).searchParams.get('detailTab'), current = ['options','source'].includes(value) ? value : 'summary';
    page.querySelectorAll('[data-detail-tab]').forEach(button => button.setAttribute('aria-pressed',String(button.dataset.detailTab === current)));
    page.querySelectorAll('[data-detail-panel]').forEach(node => {node.hidden = node.dataset.detailPanel !== current;});
  }
  function renderDetail() {
    page.classList.toggle('inventory-has-selection', Boolean(selected));
    const current = state(), type = selected?.type || current.type, skill = ['skill_tree','skill_set'].includes(type);
    const creatable = ['equipment','skill_tree','skill_set'].includes(current.type), member = !find('.inventory-member').hidden;
    const context = JSON.stringify([current.type,current.slot,current.equipmentType,current.treeId,current.skillCategory]);
    if (skill && member) {
      if (selected) {if (!skillEditor.isOpen() || skillEditor.record()?.id !== selected.id || skillEditor.record()?.revision !== selected.revision) skillEditor.open(selected,current);}
      else if (!skillEditor.isOpen() || skillEditor.record()?.id || draftContext !== context) {equipmentEditor.close(); skillEditor.open(drafts.get(context),current);}
    } else {
      skillEditor.close();
      if (!selected && current.type === 'equipment' && member && (!equipmentEditor.isOpen() || equipmentEditor.record()?.id || draftContext !== context)) equipmentEditor.open(current,drafts.get(context));
    }
    draftContext = context;
    const working = Boolean(selected) || equipmentEditor.isOpen() || skillEditor.isOpen();
    page.classList.toggle('inventory-has-workspace',working);
    button('create').hidden = button('save').hidden = !creatable || !member;
    find('.inventory-placeholder').hidden = working; find('.inventory-selected').hidden = !selected || skill || equipmentEditor.isOpen();
    find('.inventory-actions').hidden = !selected || skill || equipmentEditor.isOpen();
    if (!selected) return;
    const p = selected.type === 'equipment' ? selected.data.equipment : null, source = p?.catalogItem;
    rename.elements.name.value = selected.name;
    find('.inventory-slot').textContent = account.slots[selected.data.slot] || INVENTORY_TYPES[selected.type];
    const summary = find('.inventory-summary'); summary.replaceChildren();
    if (p) for (const [label, value] of [['종류', p.type || account.slots[selected.data.slot]], ['ATK', p.attack ?? '—'], ['제련', p.refinement ?? '—'], ['안정률', p.stability === null ? '—' : p.stability + '%'], ['크리스타', p.crystas.map((v, i) => (v || '빈 슬롯') + (p.lockedCrystaSlots[i] ? ' (잠금)' : '')).join(' / ') || '없음']]) summary.append(text('dt', label), text('dd', value));
    if (!p) for (const [index,value] of describe(selected).slice(0,3).entries()) summary.append(text('dt',String(index + 1)),text('dd',value));
    renderOptions(); detailTab();
    find('.inventory-source').textContent = source ? `게임 원본: ${source.name || '#' + source.gameItemId} · #${source.gameItemId} · 데이터 ${source.cacheVersion}\n원본 옵션 ${Object.keys(source.stats).length}개 · 조건부 효과 ${source.conditionalStats.length}개 (계산기에서 확인)` : '저장 당시의 독립 구성';
    if (selected.provenance.length) find('.inventory-source').textContent += '\n출처: ' + selected.provenance.map(source => source.kind === 'inventory' ? `내 구성 ${source.objectId.slice(0,8)}` : source.kind === 'release' ? `공개 릴리스 v${source.releaseNumber}` : `#${source.gameItemId} (${source.cacheVersion})`).join(', ');
    for (const source of selected.provenance.filter(source => source.kind === 'release')) {
      const link = text('button',`원본 v${source.releaseNumber} 보기`); link.type = 'button';
      link.addEventListener('click',() => shell.open('board',{params:{post:source.postId,release:source.releaseNumber}})); find('.inventory-source').append(' ',link);
    }
    const combos = comboEntries(selected), choice = find('.inventory-combo-choice'), oldChoice = comboChoiceOwner === selected.id ? choice.value : '';
    comboChoiceOwner = selected.id;
    find('.inventory-combo-label').hidden = selected.type === 'combo' || !combos.length; choice.replaceChildren(text('option','콤보를 선택하세요')); choice.options[0].value = '';
    for (const entry of combos) { const option = text('option',`${entry.combo.name} · ${entry.combo.data.steps.length}칸 (${entry.id})`); option.value = entry.id; choice.append(option); }
    if (combos.length === 1) choice.value = combos[0].id;
    else if (combos.some(entry => entry.id === oldChoice)) choice.value = oldChoice;
    page.querySelectorAll('[data-object-id]').forEach(node => { node.setAttribute('aria-pressed', String(node.dataset.objectId === selected.id)); });
  }
  async function saveWorkspace(create = false) {
    const editor = skillEditor.isOpen() ? skillEditor : equipmentEditor.isOpen() ? equipmentEditor : null;
    if (editor && (editor.isDirty() || create)) {
      const draft = await editor.read(), previous = editor.record();
      if (!previous?.id && !create) {drafts.set(draftContext,draft); editor.saved(draft); return;}
      let saved;
      if (previous?.id) saved = editor.isDirty() ? await api.update({...previous,data:draft.data},draft.name) : previous;
      else {
        const kind = draft.type === 'equipment' ? draft.data.slot === 'mainWeapon' ? '무기' : EQUIPMENT_SLOTS[draft.data.slot].replaceAll(' ','') : INVENTORY_TYPES[draft.type];
        const records = [];
        for (let pageNumber = 1, total = 1; (pageNumber - 1) * 50 < total; pageNumber++) {const result = await api.list({type:draft.type,page:pageNumber,pageSize:50}); total = result.total; records.push(...result.items);}
        saved = await api.register(nextInventoryName(records,kind),draft.type,draft.data);
        drafts.delete(draftContext); setUrl({selected:saved.id,q:null});
      }
      editor.saved(saved); selected = saved;
    }
    if (selected && !rename.hidden && rename.elements.name.value !== selected.name) {
      selected = await api.update(selected,rename.elements.name.value);
      if (skillEditor.isOpen()) skillEditor.saved(selected);
      if (equipmentEditor.isOpen()) equipmentEditor.saved(selected);
    }
    const row = selected && find(`[data-entry-id="${selected.id}"]`);
    if (row) row.querySelector('strong').textContent = selected.name;
  }
  async function refresh() {
    const current = state();
    if (equipmentEditor.isOpen() && equipmentEditor.record()?.id !== current.selected) equipmentEditor.close();
    captureFields(); search.elements.q.value = current.q;
    const { selected:id, ...params } = current;
    listState = await api.list({...params,page:1,pageSize:50});
    const records = new Map(listState.items.map(item => [item.id,item]));
    for (let pageNumber = 2; pageNumber <= Math.ceil(listState.total / 50); pageNumber++) {
      const next = await api.list({...params,page:pageNumber,pageSize:50});
      for (const item of next.items) records.set(item.id,item);
    }
    listState.items = [...records.values()];
    if (current.page !== '1') setUrl({page:null},true);
    const list = find('.inventory-list'); rename.hidden = true; find('.inventory-list-panel').append(rename); list.replaceChildren();
    find('.inventory-count').textContent = `${listState.total} / 200개`;
    for (const record of listState.items) {
      const row = text('div',''); row.className = 'inventory-entry'; row.dataset.entryId = record.id;
      const entry = text('button', ''); entry.type = 'button'; entry.dataset.objectId = record.id;
      entry.append(text('strong', record.name), text('small', `${EQUIPMENT_TYPES[record.equipmentType]?.[0] || account.slots[record.equipmentType] || INVENTORY_TYPES[record.type]}`));
      entry.addEventListener('click', event => {
        if (selected?.id === record.id && event.target.closest('strong')) {void editName(); return;}
        void run(async () => {
        await saveWorkspace();
        page.classList.remove('inventory-show-list'); setUrl({ selected:record.id }); await refresh(); focusAfter = find('.inventory-skill-stage .skill-node') || entry;
        });
      });
      function editName() {return run(async () => {await saveWorkspace(); setUrl({selected:record.id}); await refresh(); find(`[data-entry-id="${record.id}"]`).append(rename); rename.hidden = false; rename.elements.name.value = selected.name; focusAfter = rename.elements.name;});}
      entry.addEventListener('keydown',event => {if (event.key === 'F2') {event.preventDefault(); void editName();}});
      entry.addEventListener('dblclick',() => {void editName();});
      row.append(entry); list.append(row);
    }
    if (!listState.items.length) list.append(text('p', '구성 없음'));
    if (id) {
      try { selected = await api.get(id); }
      catch (error) { if (error.status !== 404) throw error; selected = null; message(error.message, true); }
    } else selected = null;
    renderDetail();
    shownUrl = root.location.href;
  }
  async function connect() {
    const session = await account.session();
    find('.inventory-member').hidden = !session.user; find('.inventory-guest').hidden = Boolean(session.user);
    button('create').hidden = !session.user;
    if (session.user) {
      navigationData ||= (async () => {
        if (!root.SKILL_TREE_DATA) await import('../../data/skill-tree-data.js');
        navigation.setMetadata({trees:root.SKILL_TREE_DATA.trees,buffs:await root.ToramApp.items.listConsumableCategories()});
      })().catch(error => {navigationData = null; throw error;});
      await navigationData; await refresh();
    }
    else { selected = null; renderDetail(); if (!session.configured) message('계정 서버 연결을 준비 중입니다. 계산기의 로컬 저장은 사용할 수 있습니다.'); }
  }
  function goInventory() {
    shell.open('inventory', {skipGuard:true});
  }
  function goCalculator() {
    shell.open('calculator', {skipGuard:true});
  }
  return { bind() {
    shell.calculator.prepend(banner);
    shell.register('inventory',page,{canLeave:() => !busy, beforeLeave:() => busy ? false : run(async () => {await saveWorkspace(); return true;}), enter() { if (busy) routePending = true; else void run(async () => {await saveWorkspace(); await connect();}); }});
    root.setInterval(() => {if (active() && !busy && hasUnsavedWorkspace() && (!skillEditor.isOpen() || skillEditor.canSave())) void run(saveWorkspace);},120_000);
    root.addEventListener('beforeunload',event => {if (hasUnsavedWorkspace() || drafts.size) {event.preventDefault(); event.returnValue = '';}});
    mergeUi = createInventoryMergeUi(documentRef,api,describe,async saved => { setUrl({...emptyInventoryFilters(),type:saved.type,selected:saved.id,q:null}); await refresh(); message('새 구성으로 조립했습니다. 원본은 유지됩니다.'); });
    find('.inventory-capture-toggle').addEventListener('toggle',() => {
      if (find('.inventory-capture-toggle').open) {
        if (busy) capturePending = true; else void run(prepareCapture);
      }
    });
    page.querySelectorAll('[data-detail-tab]').forEach(button => button.addEventListener('click',() => {setUrl({detailTab:button.dataset.detailTab === 'summary' ? null : button.dataset.detailTab}); detailTab();}));
    button('create').addEventListener('click',() => run(async () => {
      await saveWorkspace(); drafts.delete(draftContext); equipmentEditor.close(); skillEditor.close(); selected = null;
      setUrl({selected:null}); page.classList.remove('inventory-show-list'); await refresh();
      focusAfter = find('.inventory-skill-stage .skill-node') || equipmentEditor.form.elements.attack;
    }));
    button('save').addEventListener('click',() => run(async () => {await saveWorkspace(true); await refresh();}));
    equipmentEditor.form.addEventListener('submit',event => {event.preventDefault(); void run(saveWorkspace);});


    button('refresh').addEventListener('click', () => run(async () => { await saveWorkspace(); await connect(); }));
    button('list').addEventListener('click',() => run(async () => {await saveWorkspace(); page.classList.add('inventory-show-list');}));
    button('login').addEventListener('click', () => run(async () => { await account.login(); await connect(); }));
    button('merge').addEventListener('click',() => run(async () => {await saveWorkspace(); mergeUi.open(selected);}));
    button('publish').addEventListener('click',() => run(async () => {await saveWorkspace(); publish(selected);}));
    button('remove-combo').addEventListener('click', () => run(async () => {
      const id = find('.inventory-combo-choice').value;
      if (!id) throw new Error('제거할 콤보를 선택하세요.');
      await saveWorkspace();
      if (!root.confirm('선택한 콤보만 이 구성에서 제거할까요? 다른 콤보와 원본은 유지됩니다.')) return;
      const next = structuredClone(selected), data = next.type === 'build' ? next.data.combos.data : next.data;
      data.entries = data.entries.filter(entry => entry.id !== id);
      selected = await api.update(next,next.name); await refresh(); message('선택한 콤보를 제거했습니다.');
    }));
    documentRef.addEventListener('toram:account-changed', () => {
      drafts.clear(); equipmentEditor.close(); skillEditor.close(); button('create').hidden = true; selected = null; editing = null; banner.hidden = true; find('.inventory-list').replaceChildren(); renderDetail();
      find('.inventory-member').hidden = true; find('.inventory-guest').hidden = false;
      if (busy) routePending = true; else if (active()) run(connect);
    });
    search.addEventListener('submit', event => { event.preventDefault(); run(async () => { await saveWorkspace(); setUrl({ q:search.elements.q.value.trim(), page:null, selected:null }); await refresh(); }); });
    capture.addEventListener('submit', event => { event.preventDefault(); run(async () => {
      await saveWorkspace();
      const created = await api.capture(capture.elements.name.value,state().type,{slot:capture.elements.slot.value,treeId:capture.elements.treeId.value,consumableId:capture.elements.consumableId.value});
      find('.inventory-capture-toggle').open = false;
      setUrl({...emptyInventoryFilters(),type:created.type,selected:created.id,q:null}); await refresh(); message('내 소유의 새 구성으로 저장했습니다.');
    }); });
    rename.addEventListener('submit',event => {event.preventDefault(); void run(async () => {await saveWorkspace(); await refresh();});});
    rename.addEventListener('blur',() => {if (!busy && !rename.hidden) void run(async () => {await saveWorkspace(); await refresh();});},true);
    rename.addEventListener('keydown',event => {if (event.key === 'Escape') {rename.elements.name.value = selected.name; rename.hidden = true;}});
    for (const action of ['apply','edit']) button(action).addEventListener('click', () => run(async () => {
      const comboId = find('.inventory-combo-choice').value, multipleCombos = comboEntries(selected).length > 1;
      if (multipleCombos && !comboId) throw new Error('적용할 콤보를 하나 선택하세요.');
      const scope = (selected.type === 'consumable_set' || selected.type === 'build' && selected.data.consumables ? ' 도핑 세팅은 전체 교체됩니다.' : '')
        + (multipleCombos ? ' 선택한 콤보 하나가 계산기와 기존 JSON 저장에 적용됩니다.' : '');
      await saveWorkspace();
      if (!root.confirm(`“${selected.name}”의 ${INVENTORY_TYPES[selected.type]} 구성을 계산기에 적용할까요?${scope}`)) return;
      if (editing && editing.id !== selected.id && !root.confirm('편집 중인 구성의 연결을 끝내고 선택한 구성을 가져올까요? 아직 저장하지 않은 수정은 원본에 반영되지 않습니다.')) return;
      await api.apply(selected,comboId);
      editing = null; banner.hidden = true;
      if (action === 'edit') { editing = structuredClone(selected); editingComboId = comboId; banner.hidden = false; banner.querySelector('strong').textContent = `${editing.name} · ${INVENTORY_TYPES[editing.type]} 편집 중`; }
      const tab = ({equipment:'equipment',equipment_set:'equipment',status:'stats-target',skill_tree:'skills',skill_set:'skills',consumable:'buffs',consumable_set:'buffs',combo:'combo',combo_set:'combo'})[selected.type] || 'stats-target';
      goCalculator(); documentRef.getElementById('appTabButton-' + tab)?.click();
    }));
    button('remove').addEventListener('click', () => run(async () => {
      if (!root.confirm(`“${selected.name}” 구성을 삭제할까요? 계산기에 적용한 내용은 유지됩니다.`)) return;
      await api.remove(selected); if (editing?.id === selected.id) { editing = null; banner.hidden = true; }
      setUrl({ selected:null, page:null }); await refresh(); message('삭제했습니다.');
    }));
    banner.querySelector('[data-action="commit"]').addEventListener('click', () => run(async () => {
      editing = await api.update(editing, editing.name, true,{comboId:editingComboId}); selected = editing;
      banner.querySelector('p').textContent = '저장 완료'; message('구성 수정을 저장했습니다.');
    }));
    banner.querySelector('[data-action="return"]').addEventListener('click', () => run(goInventory));
    banner.querySelector('[data-action="finish"]').addEventListener('click', () => { if (root.confirm('편집 연결을 끝낼까요? 저장하지 않은 계산기 내용은 현재 세팅에만 남습니다.')) { editing = null; banner.hidden = true; } });
    const url = new URL(root.location.href), returnTo = root.sessionStorage?.getItem('toram.inventory.return');
    if (url.searchParams.get('account') === 'connected' && returnTo) {
      root.sessionStorage.removeItem('toram.inventory.return');
      const destination = new URL(returnTo, url.origin);
      if (destination.origin === url.origin && destination.pathname === '/inventory') root.history.replaceState(null, '', destination);
    }
  } };
}
