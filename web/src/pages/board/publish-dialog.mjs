import { INVENTORY_TYPES } from '../../application/inventory-objects.mjs';

export function createPublishDialog(documentRef,account,onPublished) {
  const root = documentRef.defaultView, dialog = documentRef.createElement('dialog'); dialog.className = 'publish-dialog'; dialog.setAttribute('aria-labelledby','publishTitle');
  dialog.innerHTML = `<header><h2 id="publishTitle">구성 공개</h2><button type="button" class="publish-close" aria-label="공개 창 닫기">닫기</button></header>
    <p>선택한 구성만 공개 버전으로 고정합니다. 개인 원본을 수정해도 공개본은 바뀌지 않습니다.</p>
    <details class="publish-picker"><summary>내 인벤토리에서 원본 선택</summary><form class="publish-search"><label>종류<select name="type">${Object.entries(INVENTORY_TYPES).map(([id,label]) => `<option value="${id}">${label}</option>`).join('')}</select></label><label>이름 검색<input name="q" maxlength="80"></label><button>검색</button></form><div class="publish-sources"></div><nav class="publish-pagination" aria-label="공개 원본 목록"><button type="button" data-action="previous">이전</button><span></span><button type="button" data-action="next">다음</button></nav></details>
    <div class="publish-selected"><strong>공개할 원본을 선택하세요.</strong><button type="button" class="publish-refresh">원본·게시글 새로고침</button></div>
    <form class="publish-form"><label>공개 범위<select name="scope"><option value="whole">구성 전체</option></select></label>
      <div class="publish-post-fields"><label>게시글 제목<input name="title" maxlength="80" required></label><label>소개<textarea name="description" maxlength="4000" rows="2"></textarea></label><label>태그 (쉼표로 구분, 최대 10개)<input name="tags" maxlength="250"></label></div>
      <div class="publish-release-fields"><label>버전 이름<input name="releaseName" maxlength="80" required></label><label>게임 버전 (선택)<input name="gameVersion" maxlength="80" placeholder="모르면 비워 두세요"></label></div><label>변경 설명<textarea name="changeNotes" maxlength="2000" rows="2"></textarea></label><button class="board-primary" type="submit">공개하기</button></form><p class="publish-status" role="status" aria-live="polite"></p>`;
  documentRef.body.append(dialog);
  const find = selector => dialog.querySelector(selector), form = find('.publish-form'), search = find('.publish-search');
  let selected, post, list, page = 1, busy = false, requestKey, fingerprint, opener;
  const say = message => { find('.publish-status').textContent = message; };
  async function run(work) {
    if (busy) return; busy = true; dialog.setAttribute('aria-busy','true'); say('');
    dialog.querySelectorAll('button,input,select,textarea').forEach(node => {node.disabled = true;});
    try { await work(); } catch (error) { say(error.message); }
    finally {
      busy = false; dialog.removeAttribute('aria-busy'); dialog.querySelectorAll('button,input,select,textarea').forEach(node => {node.disabled = false;});
      find('[data-action="previous"]').disabled = page <= 1; find('[data-action="next"]').disabled = !list || page * list.pageSize >= list.total;
    }
  }
  function renderSelected() {
    find('.publish-selected strong').textContent = selected ? `${selected.name} · ${INVENTORY_TYPES[selected.type]} · 수정 ${selected.revision}` : '공개할 원본을 선택하세요.';
    form.elements.scope.replaceChildren(new root.Option('구성 전체','whole'));
    if (selected?.type === 'build') for (const [key,label] of [['status','스테이터스만'],['equipment','장비 세팅만'],['skills','스킬셋만'],['consumables','도핑 세팅만'],['combos','콤보 목록만']]) {
      if (selected.data[key]) form.elements.scope.append(new root.Option(label,key));
    }
  }
  async function refreshList() {
    list = await account.inventory.list({type:search.elements.type.value,q:search.elements.q.value,page});
    const target = find('.publish-sources'); target.replaceChildren();
    for (const item of list.items) {
      const button = documentRef.createElement('button'); button.type = 'button'; button.textContent = `${item.name} · 수정 ${item.revision}`;
      button.addEventListener('click',() => run(async () => { selected = await account.inventory.get(item.id); renderSelected(); find('.publish-picker').open = false; })); target.append(button);
    }
    if (!list.items.length) target.textContent = '보관한 구성이 없습니다. 계산기 구성부터 인벤토리에 담으세요.';
    find('.publish-pagination span').textContent = `${page} / ${Math.max(1,Math.ceil(list.total/list.pageSize))}`;
  }
  search.addEventListener('submit',event => { event.preventDefault(); void run(async () => {page = 1; await refreshList();}); });
  for (const [action,delta] of [['previous',-1],['next',1]]) find(`[data-action="${action}"]`).addEventListener('click',() => run(async () => {page += delta; await refreshList();}));
  find('.publish-close').addEventListener('click',() => dialog.close());
  dialog.addEventListener('cancel',event => { if (busy) event.preventDefault(); });
  dialog.addEventListener('close',() => opener?.focus());
  find('.publish-refresh').addEventListener('click',() => run(async () => {
    const scope = form.elements.scope.value;
    if (selected) selected = await account.inventory.get(selected.id);
    if (post) post = await account.posts.get(post.id);
    renderSelected(); if ([...form.elements.scope.options].some(option => option.value === scope)) form.elements.scope.value = scope;
    await refreshList(); say('수정 번호를 새로 읽었습니다. 입력한 제목·설명은 유지했습니다.');
  }));
  form.addEventListener('submit',event => { event.preventDefault(); void run(async () => {
    if (!selected) throw new Error('공개할 원본을 선택하세요.');
    const input = {source:{objectId:selected.id,revision:selected.revision},scope:form.elements.scope.value,
      release:{name:form.elements.releaseName.value,gameVersion:form.elements.gameVersion.value,changeNotes:form.elements.changeNotes.value}};
    if (post) input.postRevision = post.revision;
    else Object.assign(input,{title:form.elements.title.value,description:form.elements.description.value,tags:form.elements.tags.value.split(',').map(value => value.trim()).filter(Boolean)});
    const next = JSON.stringify(input); if (fingerprint !== next) { fingerprint = next; requestKey = root.crypto.randomUUID(); }
    const saved = await account.posts.publish(input,requestKey,post?.id);
    dialog.close(); onPublished(saved);
  }); });
  return {open(record = null,currentPost = null) {
    if (busy) return; opener = documentRef.activeElement; selected = record; post = currentPost; page = 1; list = null; requestKey = null; fingerprint = null;
    form.reset(); search.reset(); search.elements.type.value = record?.type || post?.type || 'build';
    find('#publishTitle').textContent = post ? '새 공개 버전 발행' : '구성 공개';
    find('.publish-post-fields').hidden = Boolean(post); form.elements.title.required = !post;
    form.elements.title.value = record?.name || ''; form.elements.releaseName.value = post ? `버전 ${post.latestRelease.number + 1}` : '첫 공개';
    form.querySelector('[type="submit"]').textContent = post ? '새 버전 발행' : '공개하기';
    renderSelected(); find('.publish-picker').open = !record; dialog.showModal(); void run(refreshList);
  }};
}
