import { CATALOG_KINDS, CATALOG_LOCALES, CATALOG_SUBCATEGORIES, CATALOG_BOSS_KINDS, catalogState, catalogPage, itemCatalogContent } from '../../application/catalog-browser.mjs';
import { bossKindLabel, bossActorLabel, createBossSelection, validateBossSelection, resolveBossTarget } from '../../application/boss-target.mjs';
import { createBookmarkButton } from '../../ui/bookmark-button.mjs';

export function createCatalogPage(documentRef,app,shell) {
  const root = documentRef.defaultView, page = documentRef.createElement('main'); page.id = 'catalogWorkspace'; page.hidden = true;
  page.innerHTML = `<header class="catalog-heading"><h2>도감</h2><p>게임 데이터를 찾아보고, 같은 화면에서 상세 정보를 확인하세요.</p></header>
    <button type="button" class="catalog-navigation-toggle" aria-expanded="false"><span class="catalog-navigation-label"></span><b>분류 변경</b></button>
    <div class="catalog-browser"><nav class="catalog-major-rail" aria-label="도감 대분류"></nav><nav class="catalog-kind-rail" aria-label="아이템 분류"></nav><div class="catalog-shelf">
    <form class="catalog-search"><label>언어<select name="locale">${Object.entries(CATALOG_LOCALES).map(([id,label]) => `<option value="${id}">${label}</option>`).join('')}</select></label><label class="catalog-query">이름·ID 검색<input name="q" type="search" maxlength="80" placeholder="이름 또는 게임 ID"></label><button type="submit">검색</button><button type="button" data-action="reset">초기화</button></form>
    <div class="catalog-columns"><section class="catalog-list-panel" aria-label="도감 검색 결과"><h3 class="catalog-pane-heading">목록</h3><div class="catalog-count"></div><div class="catalog-list"></div><nav class="catalog-pagination" aria-label="도감 목록 페이지"><button type="button" data-action="previous">이전</button><span></span><button type="button" data-action="next">다음</button></nav></section>
      <section class="catalog-detail" aria-label="도감 상세" tabindex="0"><div class="catalog-placeholder">목록에서 항목을 선택하세요.</div><article class="catalog-selected" hidden><header><button type="button" data-action="list">목록</button><h3 class="catalog-name"></h3></header>
        <div class="catalog-boss-controls" hidden><label>지역·개체<select name="variant" aria-label="보스 지역·개체"></select></label><label class="catalog-difficulty-label">난이도<select name="difficulty"><option value="-1">Easy</option><option value="0">Normal</option><option value="1">Hard</option><option value="2">Nightmare</option><option value="3">Ultimate</option></select></label><label class="catalog-level-label"><span>입장 레벨</span><input name="level" type="number" min="1" max="32767" step="1"></label><button type="button" data-action="boss-values">수치 보기</button></div>
        <div class="catalog-details"></div>
        <div class="catalog-lineage" hidden><label>크리스타 강화 계보<select aria-label="크리스타 강화 계보"></select></label><button type="button" data-action="lineage">계보 항목 보기</button></div>
      </article></section></div></div></div><div id="catalogNavigationDialog" class="catalog-navigation-dialog" popover="auto" role="dialog" aria-labelledby="catalogNavigationTitle"><header><h3 id="catalogNavigationTitle"></h3><button type="button" aria-label="세부 분류 닫기">×</button></header><nav class="catalog-leaf-rail" aria-label="도감 세부 분류"></nav></div><p class="catalog-status" role="status" aria-live="polite"></p>`;
  const find = selector => page.querySelector(selector), action = name => find(`[data-action="${name}"]`), form = find('.catalog-search');
  const media = root.matchMedia('(max-width:700px)'), lists = new Map();
  let generation = 0, listing = null, selected = null, content = null;
  const node = (tag,text) => {const value = documentRef.createElement(tag); value.textContent = text; return value;};
  const dialog = find('.catalog-navigation-dialog'), toggle = find('.catalog-navigation-toggle');
  let dialogOpener;
  function choose(value) {page.classList.toggle('catalog-choosing-category',value); toggle.setAttribute('aria-expanded',String(value)); toggle.querySelector('b').textContent = value ? '분류 닫기' : '분류 변경';}
  toggle.addEventListener('click',() => choose(!page.classList.contains('catalog-choosing-category')));
  dialog.querySelector('header button').addEventListener('click',() => dialog.hidePopover());
  dialog.addEventListener('toggle',event => {
    if (event.newState !== 'closed') return;
    dialogOpener?.setAttribute('aria-expanded','false');
    if (!dialog.contains(documentRef.activeElement) && documentRef.activeElement !== documentRef.body) return;
    (media.matches && !page.classList.contains('catalog-choosing-category') ? toggle : dialogOpener)?.focus({preventScroll:true});
  });
  root.addEventListener('resize',() => dialog.hidePopover());
  function openCategories(button,kind) {
    dialogOpener = button;
    dialog.querySelector('h3').textContent = `${CATALOG_KINDS[kind]} 분류`;
    const query = state();
    find('.catalog-leaf-rail').replaceChildren(...[['all',`전체 ${CATALOG_KINDS[kind]}`],...Object.entries(CATALOG_SUBCATEGORIES[kind])].map(([id,label]) => {
      const leaf = createBookmarkButton(documentRef,{label,active:query.section === 'items' && query.kind === kind && query.subcategory === id,onClick() {
        choose(false); navigate({section:'items',kind,subcategory:id === 'all' ? null : id,bossKind:null,q:form.elements.q.value.trim(),page:null,selected:null,variant:null,difficulty:null,level:null});
      }});
      leaf.classList.add('catalog-bookmark'); leaf.dataset.subcategory = id; return leaf;
    }));
    const rail = find('.catalog-kind-rail').getBoundingClientRect();
    dialog.style.left = `${Math.min(rail.right,root.innerWidth - 152)}px`; dialog.style.top = `${rail.top}px`; dialog.style.maxHeight = `${Math.min(rail.height,root.innerHeight - rail.top - 8)}px`;
    dialog.showPopover(); button.setAttribute('aria-expanded','true');
    (find('.catalog-leaf-rail .active') || find('.catalog-leaf-rail').firstElementChild)?.focus();
  }
  for (const [key,entries,rail] of [['section',{items:'아이템',bosses:'보스'},'.catalog-major-rail'],['kind',CATALOG_KINDS,'.catalog-kind-rail'],['bossKind',CATALOG_BOSS_KINDS,'.catalog-kind-rail']]) {
    for (const [id,label] of Object.entries(entries)) {
      const button = createBookmarkButton(documentRef,{label,onClick() {
        if (key === 'kind' && CATALOG_SUBCATEGORIES[id]) {openCategories(button,id); return;}
        choose(media.matches && key === 'section');
        navigate({bossKind:null,[key]:id,subcategory:null,q:form.elements.q.value.trim(),page:null,selected:null,variant:null,difficulty:null,level:null});
      }});
      if (key === 'kind' && CATALOG_SUBCATEGORIES[id]) {button.setAttribute('aria-haspopup','dialog'); button.setAttribute('aria-controls',dialog.id); button.setAttribute('aria-expanded','false');}
      button.classList.add('catalog-bookmark'); button.dataset[key] = id; find(rail).append(button);
    }
  }
  function state() {return catalogState(new URL(root.location.href).searchParams);}
  function say(value = '') {find('.catalog-status').textContent = value;}
  function setUrl(changes,replace = false) {
    const url = new URL(root.location.href);
    for (const [key,value] of Object.entries(changes)) {if (value === null || value === '') url.searchParams.delete(key); else url.searchParams.set(key,String(value));}
    root.history[replace ? 'replaceState' : 'pushState'](null,'',url);
  }
  async function listFor(query) {
    const key = `${query.section}:${query.kind}:${query.subcategory}:${query.bossKind}:${query.locale}`;
    if (!lists.has(key)) lists.set(key,(async () => {
      if (query.section === 'bosses') {
        if (query.bossKind === 'event-boss') return [];
        return (await app.bosses.search('',query.locale,query.bossKind === 'all' ? {} : {classification:query.bossKind})).map(item => ({id:item.gameMonsterId,name:item.name}));
      }
      const kinds = query.kind === 'all' ? Object.keys(CATALOG_KINDS).filter(kind => kind !== 'all') : [query.kind];
      const filters = query.subcategory === 'all' ? {} : query.kind === 'weapons' ? {typeId:Number(query.subcategory)} : {category:query.subcategory};
      return (await Promise.all(kinds.map(async kind => (await app.items.listItems(kind,query.locale,filters)).map(item => ({...item,kind}))))).flat().sort((left,right) => left.id - right.id);
    })().catch(error => {lists.delete(key); throw error;}));
    return lists.get(key);
  }
  function renderDetail(query) {
    find('.catalog-placeholder').hidden = Boolean(selected); find('.catalog-selected').hidden = !selected; page.classList.toggle('catalog-has-selection',Boolean(selected));
    if (!selected) return;
    find('.catalog-name').textContent = selected.name ?? '(선택 언어 번역 없음)';
    find('.catalog-boss-controls').hidden = query.section !== 'bosses';
    const target = find('.catalog-details'); target.replaceChildren();
    for (const [key,value] of Object.entries(content)) {
      if (key === 'options') {
        if (!value.length) continue;
        const options = node('div',''); options.className = 'catalog-options';
        for (const option of value) {const line = node('p',option.text); line.className = option.conditional ? 'catalog-conditional' : ''; options.append(line);}
        target.append(options);
      } else if (value) {const line = node('p',value); line.className = `catalog-${key}`; target.append(line);}
    }
    for (const button of page.querySelectorAll('[data-entry-id]')) button.setAttribute('aria-pressed',String(Number(button.dataset.entryId) === query.selected));
  }
  function renderBoss(query,boss) {
    const variants = [...boss.variants].sort((left,right) => Number(left.entry.model === 'unresolved') - Number(right.entry.model === 'unresolved') || left.fieldId - right.fieldId || left.masterId - right.masterId);
    const variant = query.variant ? variants.find(item => item.key === query.variant) : variants[0];
    if (!variant) throw new Error('선택한 보스 개체를 찾을 수 없습니다.');
    let selection = createBossSelection(boss,variant);
    selection = validateBossSelection({...selection,difficulty:variant.entry.model === 'difficulty-select' ? query.difficulty : 0,level:variant.entry.model === 'level-select' && query.level !== null ? query.level : selection.level});
    const resolved = resolveBossTarget(selection), controls = find('.catalog-boss-controls'), variantsSelect = controls.querySelector('[name="variant"]');
    variantsSelect.replaceChildren(...variants.map(item => new root.Option(`${bossKindLabel(item.classification)} · ${item.fieldName ?? '#' + item.fieldId} · ${item.key}`,item.key)));
    variantsSelect.value = variant.key;
    find('.catalog-difficulty-label').hidden = variant.entry.model !== 'difficulty-select'; find('.catalog-level-label').hidden = variant.entry.model !== 'level-select';
    controls.querySelector('[name="difficulty"]').value = String(selection.difficulty);
    const level = controls.querySelector('[name="level"]'); level.value = String(selection.level); level.min = variant.entry.levelParameters?.minLevel ?? 1; level.max = variant.entry.levelParameters?.maxLevel ?? 32767; level.step = variant.entry.levelParameters?.step ?? 1;
    find('.catalog-level-label span').textContent = variant.classification === 'guild-raid-boss' ? '현재 보스 레벨' : '입장 레벨';
    const targetLabels = {bossLevel:'레벨',bossDef:'DEF',bossMdef:'MDEF',bossPhysResist:'물리 내성',bossMagResist:'마법 내성',bossCritResist:'크리티컬 저항'};
    const hp = resolved.details.find(([label]) => label === '본체 HP');
    content = {summary:[bossKindLabel(variant.classification),bossActorLabel(variant.entry.actor),variant.fieldName].filter(Boolean).join(' · '),
      options:[[variant.entry.model === 'unresolved' ? 'HP · 난이도 미확인' : 'HP',hp[1]],...Object.entries(resolved.target).map(([key,value]) => [targetLabels[key],value]),
        ...resolved.details.filter(([label]) => label === '본체 필요 명중' || label.startsWith('관성'))].filter(([,value]) => value !== null && value !== undefined && value !== '').map(([label,value]) => ({text:`${label} : ${value}`})),
      notes:resolved.notes.join('\n')};
    selected = boss; find('.catalog-lineage').hidden = true;
  }
  async function showSelected(query,current) {
    if (query.selected === null) {selected = null; content = null; renderDetail(query); return;}
    if (query.section === 'bosses') {
      const boss = await app.bosses.get(query.selected,query.locale); if (current !== generation) return;
      if (!boss?.variants.length) throw new Error('보스 ID를 찾을 수 없습니다.');
      const variants = query.bossKind === 'all' ? boss.variants : boss.variants.filter(item => item.classification === query.bossKind);
      if (!variants.length) throw new Error('선택한 분류에 해당하는 보스 개체가 없습니다.');
      renderBoss(query,{...boss,variants});
    } else {
      const [item,details] = await Promise.all([app.items.getItem(query.selected,query.locale),app.items.getDetails(query.selected,query.locale)]); if (current !== generation) return;
      selected = item; content = itemCatalogContent(item,details);
      const lineage = find('.catalog-lineage'); lineage.hidden = item.kind !== 'crystas';
      if (item.kind === 'crystas') {
        const entries = await app.items.getCrystaCatalog(); if (current !== generation) return;
        const parents = item.previousId ? [new root.Option(`강화 전 · ${entries[item.previousId]?.names?.[query.locale] ?? '#' + item.previousId} (#${item.previousId})`,item.previousId)] : [];
        const next = Object.values(entries).filter(value => value.previousId === item.id).map(value => new root.Option(`강화 후 · ${value.names[query.locale] ?? '#' + value.gameItemId} (#${value.gameItemId})`,value.gameItemId));
        lineage.querySelector('select').replaceChildren(...parents,...next); lineage.hidden = !parents.length && !next.length;
      }
    }
    if (current === generation) renderDetail(query);
  }
  async function refresh() {
    const current = ++generation; page.setAttribute('aria-busy','true'); say('불러오는 중…');
    try {
      const query = state(); for (const key of ['locale','q']) form.elements[key].value = query[key];
      const label = query.section === 'bosses' ? CATALOG_BOSS_KINDS[query.bossKind] : [CATALOG_KINDS[query.kind],query.subcategory !== 'all' && CATALOG_SUBCATEGORIES[query.kind][query.subcategory]].filter(Boolean).join(' · ');
      find('.catalog-navigation-label').textContent = label;
      find('.catalog-kind-rail').setAttribute('aria-label',query.section === 'bosses' ? '보스 분류' : '아이템 분류');
      for (const button of page.querySelectorAll('.catalog-major-rail button,.catalog-kind-rail button')) {
        if (button.dataset.kind) button.hidden = query.section !== 'items';
        if (button.dataset.bossKind) button.hidden = query.section !== 'bosses';
        const active = button.dataset.section ? button.dataset.section === query.section : button.dataset.bossKind ? button.dataset.bossKind === query.bossKind : button.dataset.kind === query.kind;
        button.classList.toggle('active',active); button.setAttribute('aria-pressed',String(active));
      }
      selected = null; content = null; renderDetail(query);
      const entries = await listFor(query); if (current !== generation) return;
      listing = catalogPage(entries,query,media.matches || root.innerHeight < 820 ? 4 : 6); if (listing.page !== query.page) setUrl({page:listing.page},true);
      find('.catalog-count').textContent = `${listing.total.toLocaleString('ko-KR')}개 · ${label}`;
      const list = find('.catalog-list'); list.replaceChildren();
      for (const item of listing.items) {
        const button = node('button',''); button.type = 'button'; button.dataset.entryId = item.id;
        button.append(node('strong',item.name ?? '(선택 언어 번역 없음)'),node('small',`#${item.id}${item.kind ? ' · ' + CATALOG_KINDS[item.kind] : ''}`));
        button.addEventListener('click',() => navigate({selected:item.id,variant:null,difficulty:null,level:null})); list.append(button);
      }
      if (!listing.items.length) list.append(node('p',query.section === 'bosses' && query.bossKind === 'event-boss' ? '이벤트보스는 기간·맵별 분류를 준비 중입니다.' : '검색 결과가 없습니다. 이름·ID·분류를 바꿔보세요.'));
      find('.catalog-pagination span').textContent = `${listing.page} / ${Math.max(1,Math.ceil(listing.total/listing.pageSize))}`;
      action('previous').disabled = listing.page <= 1; action('next').disabled = listing.page * listing.pageSize >= listing.total;
      await showSelected(query,current); if (current === generation) say('조회 전용 도감입니다. 계산기 입력과 인벤토리는 바뀌지 않습니다.');
    } catch (error) {if (current === generation) {selected = null; content = null; find('.catalog-selected').hidden = true; find('.catalog-placeholder').hidden = false; page.classList.remove('catalog-has-selection'); say(error.message);}}
    finally {if (current === generation) page.removeAttribute('aria-busy');}
  }
  function navigate(changes,replace = false) {dialog.hidePopover(); find('.catalog-detail').scrollTop = 0; setUrl({tab:null,detailPage:null,...changes},replace); void refresh();}
  form.addEventListener('submit',event => {event.preventDefault(); navigate({locale:form.elements.locale.value,q:form.elements.q.value.trim(),page:null,selected:null,variant:null,difficulty:null,level:null});});
  form.elements.locale.addEventListener('change',() => {
    const query = state(); navigate({locale:form.elements.locale.value,q:form.elements.q.value.trim(),page:null,selected:query.selected,variant:null,difficulty:null,level:null});
  });
  action('reset').addEventListener('click',() => {choose(false); navigate({section:'items',kind:null,subcategory:null,bossKind:null,locale:null,q:null,page:null,selected:null,variant:null,difficulty:null,level:null});});
  action('list').addEventListener('click',() => navigate({selected:null,variant:null,difficulty:null,level:null}));
  for (const [direction,delta] of [['previous',-1],['next',1]]) action(direction).addEventListener('click',() => {if (listing) navigate({page:listing.page + delta,selected:null,variant:null,difficulty:null,level:null});});
  find('[name="variant"]').addEventListener('change',event => navigate({variant:event.target.value,difficulty:null,level:null}));
  action('boss-values').addEventListener('click',() => {const controls = find('.catalog-boss-controls'); navigate({difficulty:find('.catalog-difficulty-label').hidden ? null : controls.querySelector('[name="difficulty"]').value,level:find('.catalog-level-label').hidden ? null : controls.querySelector('[name="level"]').value});});
  action('lineage').addEventListener('click',() => navigate({section:'items',kind:'crystas',subcategory:null,bossKind:null,selected:find('.catalog-lineage select').value}));
  media.addEventListener('change',() => choose(false));
  shell.register('catalog',page,{enter() {void refresh();}});
}
