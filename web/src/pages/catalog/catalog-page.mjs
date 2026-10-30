import { CATALOG_KINDS, CATALOG_LOCALES, CATALOG_SUBCATEGORIES, CATALOG_BOSS_KINDS, CATALOG_REGISTLET_KINDS, catalogState, catalogPage, itemCatalogContent, bossCatalogContent, bossCatalogPhaseLabel } from '../../application/catalog-browser.mjs';
import { bossKindLabel, createBossSelection, validateBossSelection } from '../../application/boss-target.mjs';
import { createBookmarkButton } from '../../ui/bookmark-button.mjs';
import { EQUIPMENT_ICONS, EQUIPMENT_ITEM_ICONS, CRYSTA_ICONS, prependEquipmentIcon } from '../../ui/equipment-icons.mjs';
import { renderRegistletDetails } from '../../ui/registlet-details.mjs';
import { ITEM_MENU_ICON } from '../../ui/game-menu-icons.mjs';
import { createRegistletSelection, registletEffect } from '../../application/registlet-catalog.mjs';

const kindIcons = {all:ITEM_MENU_ICON,weapons:EQUIPMENT_ICONS.sword,armor:EQUIPMENT_ICONS.armor,additional:EQUIPMENT_ICONS.additional,special:EQUIPMENT_ICONS.special,crystas:CRYSTA_ICONS.all};
const itemIcon = item => item.kind === 'crystas' ? CRYSTA_ICONS[item.category] || CRYSTA_ICONS.all : EQUIPMENT_ITEM_ICONS[item.typeId];

export function createCatalogPage(documentRef,app,shell) {
  const root = documentRef.defaultView, page = documentRef.createElement('main'); page.id = 'catalogWorkspace'; page.hidden = true;
  page.innerHTML = `<header class="catalog-heading"><h2>도감</h2><p>게임 데이터를 찾아보고, 같은 화면에서 상세 정보를 확인하세요.</p></header>
    <button type="button" class="catalog-navigation-toggle" aria-expanded="false"><span class="catalog-navigation-label"></span><b>분류 변경</b></button>
    <div class="catalog-browser"><nav class="catalog-major-rail" aria-label="도감 대분류"></nav><nav class="catalog-kind-rail" aria-label="아이템 분류"></nav><div class="catalog-shelf">
    <form class="catalog-search"><label>언어<select name="locale">${Object.entries(CATALOG_LOCALES).map(([id,label]) => `<option value="${id}">${label}</option>`).join('')}</select></label><label class="catalog-query">이름·ID 검색<input name="q" type="search" maxlength="80" placeholder="이름 또는 게임 ID"></label><button type="submit">검색</button><button type="button" data-action="reset">초기화</button></form>
    <div class="catalog-columns"><section class="catalog-list-panel" aria-label="도감 검색 결과"><h3 class="catalog-pane-heading">목록</h3><div class="catalog-count"></div><div class="catalog-list"></div><nav class="catalog-pagination" aria-label="도감 목록 페이지"><button type="button" data-action="previous">이전</button><span></span><button type="button" data-action="next">다음</button></nav></section>
      <section class="catalog-detail" aria-label="도감 상세" tabindex="0"><div class="catalog-placeholder">목록에서 항목을 선택하세요.</div><article class="catalog-selected" hidden><header><button type="button" data-action="list">목록</button><h3 class="catalog-name"></h3></header>
        <div class="catalog-boss-controls" hidden><label>지역<select name="bossRegion" aria-label="보스 지역"></select></label><label class="catalog-phase-label">개체·페이즈<select name="variant" aria-label="보스 개체·페이즈"></select></label><label class="catalog-difficulty-label">난이도<select name="difficulty"><option value="-1">Easy</option><option value="0">Normal</option><option value="1">Hard</option><option value="2">Nightmare</option><option value="3">Ultimate</option></select></label><label class="catalog-level-label"><span>입장 레벨</span><input name="level" type="number" min="1" max="32767" step="1"></label><button type="button" data-action="boss-values">수치 보기</button></div>
        <form class="catalog-registlet-controls" hidden><label>젬 레벨<input name="registletLevel" type="number" min="1" step="1" required></label><label class="catalog-registlet-skill" hidden><span>파워 웨이브 스킬 Lv</span><input name="registletSkillLevel" type="number" min="1" max="10" step="1" value="10" required></label><label class="catalog-registlet-material">동일 재료 젬 Lv<input name="registletMaterialLevel" type="number" min="1" step="1" value="1" required></label><button type="button" data-action="save-registlet">인벤토리에 담기</button><button type="button" data-action="inventory" hidden>인벤토리 보기</button></form>
        <p class="catalog-registlet-error" role="status"></p><div class="catalog-details"></div><div class="catalog-registlet-details" hidden></div>
        <div class="catalog-lineage" hidden><label>크리스타 강화 계보<select aria-label="크리스타 강화 계보"></select></label><button type="button" data-action="lineage">계보 항목 보기</button></div>
      </article></section></div><section class="catalog-slot-page" hidden aria-label="레지스트렛 슬롯 확장 비용"><h3>분말을 통한 슬롯 확장</h3><p>슬롯은 최대 10개입니다. 아래 표는 1슬롯부터 늘릴 때 필요한 분말입니다.</p><table><caption>슬롯 단계별 확장 비용 (단위: 개)</caption><thead><tr><th scope="col">슬롯</th><th scope="col">필요 분말</th><th scope="col">누적 분말</th></tr></thead><tbody></tbody></table></section></div></div><div id="catalogNavigationDialog" class="catalog-navigation-dialog" popover="auto" role="dialog" aria-labelledby="catalogNavigationTitle"><header><h3 id="catalogNavigationTitle"></h3><button type="button" aria-label="세부 분류 닫기">×</button></header><nav class="catalog-leaf-rail" aria-label="도감 세부 분류"></nav></div><p class="catalog-status" role="status" aria-live="polite"></p>`;
  const find = selector => page.querySelector(selector), action = name => find(`[data-action="${name}"]`), form = find('.catalog-search');
  const media = root.matchMedia('(max-width:700px)'), lists = new Map();
  let generation = 0, listing = null, selected = null, content = null, saving = false, savedRegistlet;
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
      const leaf = createBookmarkButton(documentRef,{label,icon:kind === 'crystas' ? CRYSTA_ICONS[id] : id === 'all' ? kindIcons[kind] : EQUIPMENT_ITEM_ICONS[id],active:query.section === 'items' && query.kind === kind && query.subcategory === id,onClick() {
        choose(false); navigate({section:'items',kind,subcategory:id === 'all' ? null : id,bossKind:null,q:form.elements.q.value.trim(),page:null,selected:null,variant:null,difficulty:null,level:null});
      }});
      leaf.classList.add('catalog-bookmark'); leaf.dataset.subcategory = id; return leaf;
    }));
    const rail = find('.catalog-kind-rail').getBoundingClientRect();
    dialog.style.left = `${Math.min(rail.right,root.innerWidth - 152)}px`; dialog.style.top = `${rail.top}px`; dialog.style.maxHeight = `${Math.min(rail.height,root.innerHeight - rail.top - 8)}px`;
    dialog.showPopover(); button.setAttribute('aria-expanded','true');
    (find('.catalog-leaf-rail .active') || find('.catalog-leaf-rail').firstElementChild)?.focus();
  }
  for (const [key,entries,rail] of [['section',{items:'아이템',bosses:'보스',registlets:'레지스트렛'},'.catalog-major-rail'],['kind',CATALOG_KINDS,'.catalog-kind-rail'],['bossKind',CATALOG_BOSS_KINDS,'.catalog-kind-rail'],['registletKind',CATALOG_REGISTLET_KINDS,'.catalog-kind-rail']]) {
    for (const [id,label] of Object.entries(entries)) {
      const button = createBookmarkButton(documentRef,{label,icon:key === 'kind' ? kindIcons[id] : key === 'section' && id === 'items' ? ITEM_MENU_ICON : undefined,onClick() {
        if (key === 'kind' && CATALOG_SUBCATEGORIES[id]) {openCategories(button,id); return;}
        choose(media.matches && key === 'section');
        navigate({bossKind:null,registletKind:null,[key]:id,subcategory:null,q:form.elements.q.value.trim(),page:null,selected:null,variant:null,difficulty:null,level:null});
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
    const key = `${query.section}:${query.kind}:${query.subcategory}:${query.bossKind}:${query.registletKind}:${query.locale}`;
    if (!lists.has(key)) lists.set(key,(async () => {
      if (query.section === 'registlets') return (await app.registlets.list(query.locale)).filter(item => query.registletKind === 'all' || item.category === query.registletKind);
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
    if (query.section === 'items') prependEquipmentIcon(find('.catalog-name'),itemIcon(selected));
    find('.catalog-boss-controls').hidden = query.section !== 'bosses';
    find('.catalog-registlet-controls').hidden = find('.catalog-registlet-details').hidden = query.section !== 'registlets';
    const target = find('.catalog-details'); target.replaceChildren();
    for (const [key,value] of Object.entries(content)) {
      if (key === 'groups') {
        for (const [title,rows] of value) {
          const group = node('section',''); group.className = 'catalog-boss-stat-group';
          const values = node('dl','');
          for (const [label,text] of rows) {const pair = node('div',''); pair.append(node('dt',label),node('dd',text)); values.append(pair);}
          group.append(node('h4',title),values); target.append(group);
        }
      } else if (key === 'options') {
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
    const controls = find('.catalog-boss-controls'), variantsSelect = controls.querySelector('[name="variant"]');
    const regions = [...new Map(variants.map(item => [item.fieldId,item])).values()];
    controls.querySelector('[name="bossRegion"]').replaceChildren(...regions.map(item => new root.Option(`${item.fieldName ?? '지역'} (#${item.fieldId})`,item.fieldId)));
    controls.querySelector('[name="bossRegion"]').value = String(variant.fieldId);
    controls.querySelector('[name="bossRegion"]').parentElement.hidden = regions.length < 2;
    const phases = variants.filter(item => item.fieldId === variant.fieldId);
    variantsSelect.replaceChildren(...phases.map(item => new root.Option(`${bossCatalogPhaseLabel(item,variants)} · ${bossKindLabel(item.classification)} · Lv${item.entry.levelParameters?.baseLevel ?? item.baseStats.level}`,item.key)));
    variantsSelect.value = variant.key;
    find('.catalog-phase-label').hidden = phases.length < 2;
    find('.catalog-difficulty-label').hidden = variant.entry.model !== 'difficulty-select'; find('.catalog-level-label').hidden = variant.entry.model !== 'level-select';
    action('boss-values').hidden = variant.entry.model !== 'level-select';
    controls.querySelector('[name="difficulty"]').value = String(selection.difficulty);
    const level = controls.querySelector('[name="level"]'); level.value = String(selection.level); level.min = variant.entry.levelParameters?.minLevel ?? 1; level.max = variant.entry.levelParameters?.maxLevel ?? 32767; level.step = variant.entry.levelParameters?.step ?? 1;
    find('.catalog-level-label span').textContent = variant.classification === 'guild-raid-boss' ? '현재 보스 레벨' : '입장 레벨';
    content = bossCatalogContent(selection,variants);
    selected = {...boss,variants}; find('.catalog-lineage').hidden = true;
  }
  async function showSelected(query,current) {
    if (query.selected === null) {selected = null; content = null; renderDetail(query); return;}
    if (query.section === 'registlets') {
      const item = await app.registlets.get(query.selected,query.locale); if (current !== generation) return;
      const selection = createRegistletSelection(item,query.level ?? 1,query.locale);
      selected = item;
      const input = find('[name="registletLevel"]'); input.value = selection.level; input.max = item.levelCap;
      find('.catalog-registlet-skill').hidden = ![207,1053].includes(item.id);
      find('.catalog-registlet-skill span').textContent = item.id === 1053 ? '스컬 셰이커 스킬 Lv' : '파워 웨이브 스킬 Lv';
      find('[name="registletSkillLevel"]').disabled = ![207,1053].includes(item.id);
      find('.catalog-registlet-material').hidden = item.levelCap === 1;
      const material = find('[name="registletMaterialLevel"]'); material.max = item.levelCap; material.value = 1; material.disabled = item.levelCap === 1;
      content = {summary:`젬 카트리지 · 최대 Lv${item.levelCap}`,description:''};
      find('.catalog-lineage').hidden = true;
      updateRegistlet(false);
    } else if (query.section === 'bosses') {
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
  function updateRegistlet(updateUrl = true) {
    if (!selected || state().section !== 'registlets') return;
    const level = find('[name="registletLevel"]'), error = find('.catalog-registlet-error');
    savedRegistlet = null; action('inventory').hidden = true;
    try {
      const selection = createRegistletSelection(selected,Number(level.value),state().locale);
      const skillLevel = [207,1053].includes(selected.id) ? Number(find('[name="registletSkillLevel"]').value) : null;
      const materialLevel = Number(find('[name="registletMaterialLevel"]').value);
      const effect = registletEffect(selection,skillLevel);
      content.description = effect.description;
      renderDetail(state());
      renderRegistletDetails(documentRef,find('.catalog-registlet-details'),selected,selection,{effect,materialLevel,locale:state().locale});
      error.textContent = ''; level.removeAttribute('aria-invalid');
      if (updateUrl) setUrl({level:selection.level},true);
    } catch (failure) {
      error.textContent = failure.message; level.setAttribute('aria-invalid','true');
      find('.catalog-registlet-details').replaceChildren();
      const description = find('.catalog-description'); if (description) description.textContent = '';
    }
  }
  async function refresh() {
    const current = ++generation; page.setAttribute('aria-busy','true'); say('불러오는 중…');
    try {
      const query = state(); for (const key of ['locale','q']) form.elements[key].value = query[key];
      const label = query.section === 'registlets' ? `레지스트렛 · ${CATALOG_REGISTLET_KINDS[query.registletKind]}` : query.section === 'bosses' ? CATALOG_BOSS_KINDS[query.bossKind] : [CATALOG_KINDS[query.kind],query.subcategory !== 'all' && CATALOG_SUBCATEGORIES[query.kind][query.subcategory]].filter(Boolean).join(' · ');
      find('.catalog-registlet-error').textContent = '';
      const slotPage = query.section === 'registlets' && query.registletKind === 'slots';
      form.hidden = find('.catalog-columns').hidden = slotPage; find('.catalog-slot-page').hidden = !slotPage;
      savedRegistlet = null; action('inventory').hidden = true;
      find('.catalog-navigation-label').textContent = label;
      find('.catalog-kind-rail').setAttribute('aria-label',query.section === 'registlets' ? '레지스트렛 분류' : query.section === 'bosses' ? '보스 분류' : '아이템 분류');
      for (const button of page.querySelectorAll('.catalog-major-rail button,.catalog-kind-rail button')) {
        if (button.dataset.kind) button.hidden = query.section !== 'items';
        if (button.dataset.bossKind) button.hidden = query.section !== 'bosses';
        if (button.dataset.registletKind) button.hidden = query.section !== 'registlets';
        const active = button.dataset.registletKind ? button.dataset.registletKind === query.registletKind : button.dataset.section ? button.dataset.section === query.section : button.dataset.bossKind ? button.dataset.bossKind === query.bossKind : button.dataset.kind === query.kind;
        button.classList.toggle('active',active); button.setAttribute('aria-pressed',String(active));
      }
      selected = null; content = null; renderDetail(query);
      if (slotPage) {
        const slots = await app.registlets.slots(); if (current !== generation) return;
        let total = 0; const body = find('.catalog-slot-page tbody'); body.replaceChildren();
        slots.costs.forEach((cost,index) => {total += cost; const row = node('tr',''); for (const value of [`${index + 1} → ${index + 2}`,cost.toLocaleString('ko-KR'),total.toLocaleString('ko-KR')]) row.append(node('td',value)); body.append(row);});
        say('레지스트렛 슬롯 확장에 필요한 분말표입니다.'); return;
      }
      const entries = await listFor(query); if (current !== generation) return;
      listing = catalogPage(entries,query,media.matches || root.innerHeight < 820 ? 4 : 6); if (listing.page !== query.page) setUrl({page:listing.page},true);
      find('.catalog-count').textContent = `${listing.total.toLocaleString('ko-KR')}개 · ${label}`;
      const list = find('.catalog-list'); list.replaceChildren();
      for (const item of listing.items) {
        const button = node('button',''); button.type = 'button'; button.dataset.entryId = item.id;
        button.append(node('strong',item.name ?? '(선택 언어 번역 없음)'),node('small',`#${item.id}${item.kind ? ' · ' + CATALOG_KINDS[item.kind] : ''}`));
        if (query.section === 'items') prependEquipmentIcon(button,itemIcon(item));
        button.addEventListener('click',() => navigate({selected:item.id,variant:null,difficulty:null,level:null})); list.append(button);
      }
      if (!listing.items.length) list.append(node('p',query.section === 'bosses' && query.bossKind === 'event-boss' ? '이벤트보스는 기간·맵별 분류를 준비 중입니다.' : '검색 결과가 없습니다. 이름·ID·분류를 바꿔보세요.'));
      find('.catalog-pagination span').textContent = `${listing.page} / ${Math.max(1,Math.ceil(listing.total/listing.pageSize))}`;
      action('previous').disabled = listing.page <= 1; action('next').disabled = listing.page * listing.pageSize >= listing.total;
      await showSelected(query,current); if (current === generation) say(query.section === 'registlets' ? '젬 레벨을 선택해 효과를 확인하고 인벤토리에 담으세요.' : '조회 전용 도감입니다. 계산기 입력과 인벤토리는 바뀌지 않습니다.');
    } catch (error) {if (current === generation) {selected = null; content = null; find('.catalog-selected').hidden = true; find('.catalog-placeholder').hidden = false; page.classList.remove('catalog-has-selection'); say(error.message);}}
    finally {if (current === generation) page.removeAttribute('aria-busy');}
  }
  function navigate(changes,replace = false) {dialog.hidePopover(); find('.catalog-detail').scrollTop = 0; setUrl({tab:null,detailPage:null,...changes},replace); void refresh();}
  form.addEventListener('submit',event => {event.preventDefault(); navigate({locale:form.elements.locale.value,q:form.elements.q.value.trim(),page:null,selected:null,variant:null,difficulty:null,level:null});});
  form.elements.locale.addEventListener('change',() => {
    const query = state(); navigate({locale:form.elements.locale.value,q:form.elements.q.value.trim(),page:null,selected:query.selected,variant:null,difficulty:null,level:null});
  });
  action('reset').addEventListener('click',() => {choose(false); navigate({section:'items',kind:null,subcategory:null,bossKind:null,registletKind:null,locale:null,q:null,page:null,selected:null,variant:null,difficulty:null,level:null});});
  action('list').addEventListener('click',() => navigate({selected:null,variant:null,difficulty:null,level:null}));
  for (const [direction,delta] of [['previous',-1],['next',1]]) action(direction).addEventListener('click',() => {if (listing) navigate({page:listing.page + delta,selected:null,variant:null,difficulty:null,level:null});});
  find('[name="bossRegion"]').addEventListener('change',event => navigate({variant:selected.variants.find(item => item.fieldId === Number(event.target.value)).key,difficulty:null,level:null}));
  find('[name="variant"]').addEventListener('change',event => {
    const query = state(), next = selected.variants.find(item => item.key === event.target.value), parameters = next.entry.levelParameters;
    const level = parameters && query.level >= parameters.minLevel && query.level <= (parameters.maxLevel ?? 32767) && query.level % (parameters.step ?? 1) === 0 ? query.level : null;
    navigate({variant:next.key,difficulty:next.entry.model === 'difficulty-select' ? query.difficulty : null,level});
  });
  find('[name="difficulty"]').addEventListener('change',event => navigate({difficulty:event.target.value}));
  action('boss-values').addEventListener('click',() => {const level = find('[name="level"]'); if (level.reportValidity()) navigate({level:level.value});});
  action('lineage').addEventListener('click',() => navigate({section:'items',kind:'crystas',subcategory:null,bossKind:null,selected:find('.catalog-lineage select').value}));
  find('.catalog-registlet-controls').addEventListener('submit',event => event.preventDefault());
  find('.catalog-registlet-controls').addEventListener('input',() => updateRegistlet());
  action('save-registlet').addEventListener('click',async () => {
    if (saving || !selected || state().section !== 'registlets') return;
    const current = generation, item = selected;
    try {
      if (!find('.catalog-registlet-controls').reportValidity()) return;
      const selection = createRegistletSelection(item,Number(find('[name="registletLevel"]').value),state().locale);
      saving = true; action('save-registlet').disabled = true;
      if (!(await app.account.session()).user) {say('로그인 후 인벤토리에 담을 수 있습니다. 상단의 계정 메뉴에서 로그인하세요.'); return;}
      const saved = await app.account.inventory.register(selection.name,'registlet',{selection});
      if (current === generation && Number(find('[name="registletLevel"]').value) === selection.level) {savedRegistlet = saved; action('inventory').hidden = false; say(`${selection.name} Lv${selection.level}을 인벤토리에 담았습니다.`);}
    } catch (error) {if (current === generation) say(error.message);}
    finally {saving = false; action('save-registlet').disabled = false;}
  });
  action('inventory').addEventListener('click',() => {if (savedRegistlet) shell.open('inventory',{params:{type:'registlet',selected:savedRegistlet.id}});});
  media.addEventListener('change',() => choose(false));
  shell.register('catalog',page,{enter() {void refresh();}});
}
