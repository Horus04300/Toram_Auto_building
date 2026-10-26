import { INVENTORY_TYPES } from '../../application/inventory-objects.mjs';
import { describeInventoryObject } from '../../application/inventory-summary.mjs';
import { createPublishDialog } from './publish-dialog.mjs';

export function createBoardPage(documentRef,account,shell) {
  const root = documentRef.defaultView, page = documentRef.createElement('main'); page.id = 'boardWorkspace'; page.hidden = true;
  page.innerHTML = `<header class="board-heading"><div><h2>구성 게시판</h2><p>공개된 구성을 발견하고, 내 사본으로 사용하세요.</p></div><button type="button" data-action="publish" class="board-primary">내 구성 공개</button></header>
    <form class="board-search"><label>종류<select name="type"><option value="">모든 구성</option>${Object.entries(INVENTORY_TYPES).map(([id,label]) => `<option value="${id}">${label}</option>`).join('')}</select></label><label>정렬<select name="sort"><option value="recent">최근 업데이트</option><option value="favorites">즐겨찾기 순</option></select></label><label>검색<input name="q" type="search" maxlength="80" placeholder="제목·소개"></label><label>태그<input name="tag" maxlength="24"></label><button type="submit">검색</button><label class="board-mine"><input type="checkbox" name="mine"> 내 게시글</label><label class="board-mine"><input type="checkbox" name="favorites"> 내 즐겨찾기</label></form>
    <div class="board-columns"><section class="board-list-panel" aria-label="게시글 목록"><div class="board-list"></div><nav class="board-pagination" aria-label="게시글 목록 페이지"><button type="button" data-action="previous">이전</button><span></span><button type="button" data-action="next">다음</button></nav></section>
      <section class="board-detail" aria-label="게시글 상세"><div class="board-placeholder">게시글을 선택하세요.</div><article class="board-selected" hidden>
        <header><button type="button" data-action="list">목록</button><span class="board-visibility"></span><h3 class="board-title"></h3><p class="board-author"></p><div class="board-tags"></div></header>
        <details class="board-description"><summary>게시글 소개</summary><p></p></details><div class="board-release-heading"><strong></strong><button type="button" data-action="latest">최신 버전 보기</button></div><p class="board-release-meta"></p><details class="board-release-notes"><summary>변경 설명</summary><p></p></details>
        <div class="board-summary"></div><nav class="board-summary-pages" aria-label="구성 내용"><button type="button" data-action="summary-previous">이전 구성</button><span></span><button type="button" data-action="summary-next">다음 구성</button></nav>
        <div class="board-actions"><button type="button" data-action="favorite"></button><button type="button" data-action="copy" class="board-primary">내 인벤토리에 복사</button><button type="button" data-action="history">버전 이력</button></div>
        <details class="board-owner" hidden><summary>작성자 관리</summary><button type="button" data-action="release">새 버전 발행</button><form class="board-manage"><label>제목<input name="title" maxlength="80" required></label><label>소개<textarea name="description" maxlength="4000" rows="2"></textarea></label><label>태그<input name="tags" maxlength="250"></label><button type="submit">게시글 정보 저장</button></form><button type="button" data-action="visibility"></button><button type="button" data-action="delete">게시글 삭제</button></details>
      </article></section></div><p class="board-status" role="status" aria-live="polite"></p>`;
  const find = selector => page.querySelector(selector), action = name => find(`[data-action="${name}"]`), form = find('.board-search');
  let current = null, list = null, busy = false, pending = false, member = null, summaryPage = 0, copyKey = null, copyFingerprint = null, generation = 0;
  const history = documentRef.createElement('dialog'); history.className = 'board-history-dialog'; history.setAttribute('aria-label','공개 버전 이력');
  history.innerHTML = '<header><h2>공개 버전 이력</h2><button type="button" data-history="close">닫기</button></header><div class="board-history-list"></div><nav class="board-pagination"><button type="button" data-history="previous">이전</button><span></span><button type="button" data-history="next">다음</button></nav><p role="status"></p>';
  documentRef.body.append(history); let historyPage = 1, historyList, historyPost, historyBusy = false;
  const publish = createPublishDialog(documentRef,account,saved => { shell.open('board',{skipGuard:true,params:{post:saved.id}}); documentRef.dispatchEvent(new root.Event('toram:posts-changed')); });
  const text = (tag,value) => { const node = documentRef.createElement(tag); node.textContent = value; return node; };
  function state() { const query = new URL(root.location.href).searchParams; return {type:query.get('type') || '',sort:query.get('sort') || 'recent',q:query.get('q') || '',tag:query.get('tag') || '',page:query.get('page') || 1,post:query.get('post'),release:query.has('release') ? Number(query.get('release')) : undefined,favorites:query.get('favorites') || '',mine:query.get('mine') === '1'}; }
  function url(changes) { const next = new URL(root.location.href); for (const [key,value] of Object.entries(changes)) { if (value === null || value === '') next.searchParams.delete(key); else next.searchParams.set(key,String(value)); } root.history.pushState(null,'',next); }
  function say(value = '') { find('.board-status').textContent = value; }
  async function run(work) {
    if (busy) return; busy = true; page.setAttribute('aria-busy','true'); say('');
    page.querySelectorAll('button,input,select,textarea').forEach(node => {node.disabled = true;});
    try { await work(); } catch (error) { say(error.message); }
    finally {
      busy = false; page.removeAttribute('aria-busy'); page.querySelectorAll('button,input,select,textarea').forEach(node => {node.disabled = false;});
      action('previous').disabled = !list || list.page <= 1; action('next').disabled = !list || list.page * list.pageSize >= list.total;
      renderSummary();
      if (pending) {pending = false; if (shell.active('board')) void run(refresh);}
    }
  }
  function renderSummary() {
    if (!current) return;
    const rows = describeInventoryObject(current.release.snapshot), target = find('.board-summary'); target.replaceChildren();
    for (const line of rows.slice(summaryPage * 3,summaryPage * 3 + 3)) target.append(text('p',line));
    find('.board-summary-pages').hidden = rows.length <= 3;
    find('.board-summary-pages span').textContent = `${summaryPage + 1} / ${Math.max(1,Math.ceil(rows.length / 3))}`;
    action('summary-previous').disabled = busy || summaryPage <= 0; action('summary-next').disabled = busy || (summaryPage + 1) * 3 >= rows.length;
  }
  function renderDetail() {
    find('.board-placeholder').hidden = Boolean(current); find('.board-selected').hidden = !current; page.classList.toggle('board-has-selection',Boolean(current));
    if (!current) return;
    const release = current.release;
    find('.board-title').textContent = current.title; find('.board-author').textContent = `${current.author.nickname} · ${INVENTORY_TYPES[current.type]}`;
    find('.board-visibility').textContent = {public:'공개',private:'비공개',deleted:'삭제됨'}[current.visibility];
    find('.board-tags').textContent = current.tags.map(tag => '#' + tag).join(' '); find('.board-description p').textContent = current.description || '소개 없음';
    find('.board-release-heading strong').textContent = `v${release.number} · ${release.name}`;
    action('latest').hidden = release.number === current.latestRelease.number;
    find('.board-release-meta').textContent = `게임 ${release.gameVersion || '버전 미기재'} · ${new Date(release.publishedAt).toLocaleString('ko-KR')} · 데이터 ${release.catalogVersions.join(', ') || '미기재'}`;
    find('.board-release-notes p').textContent = release.changeNotes || '변경 설명 없음';
    action('favorite').textContent = `${current.favorited ? '즐겨찾기 해제' : '즐겨찾기'} · ${current.favoriteCount}`; action('favorite').setAttribute('aria-pressed',String(current.favorited));
    find('.board-owner').hidden = !current.isAuthor || current.visibility === 'deleted';
    const manage = find('.board-manage'); manage.elements.title.value = current.title; manage.elements.description.value = current.description; manage.elements.tags.value = current.tags.join(', ');
    action('visibility').textContent = current.visibility === 'public' ? '비공개로 전환' : '공개로 전환';
    summaryPage = 0; renderSummary();
  }
  async function refresh() {
    const query = state(), request = ++generation;
    for (const field of ['type','sort','q','tag']) form.elements[field].value = query[field]; form.elements.mine.checked = query.mine; form.elements.favorites.checked = query.favorites === '1';
    member = (await account.session()).user;
    if (request !== generation) return;
    const {post,release,mine,...params} = query;
    const response = await account.posts.list(params,mine); if (request !== generation) return;
    list = response; const target = find('.board-list'); target.replaceChildren();
    for (const item of list.items) {
      const button = text('button',''); button.type = 'button'; button.dataset.postId = item.id;
      button.append(text('strong',item.title),text('small',`${INVENTORY_TYPES[item.type]} · ${item.author.nickname} · v${item.latestRelease.number} · 즐겨찾기 ${item.favoriteCount}`));
      button.addEventListener('click',() => run(async () => { url({post:item.id,release:null}); current = await account.posts.get(item.id); renderDetail(); })); target.append(button);
    }
    if (!list.items.length) target.append(text('p','공개된 구성이 없습니다. 내 인벤토리의 구성을 공유해 보세요.'));
    find('.board-pagination span').textContent = `${list.page} / ${Math.max(1,Math.ceil(list.total/list.pageSize))} · ${list.total}개`;
    current = null;
    if (post) { try { const selected = await account.posts.get(post,release); if (request !== generation) return; current = selected; } catch (error) { if (request !== generation) return; if (error.status !== 404) throw error; say(error.message); } }
    renderDetail();
  }
  async function requireMember() { member = (await account.session()).user; if (!member) {documentRef.getElementById('appAccountButton').click(); throw new Error('로그인 후 사용할 수 있습니다.');} }
  async function refreshHistory() {
    if (historyBusy) return; historyBusy = true; history.setAttribute('aria-busy','true'); history.querySelectorAll('button').forEach(node => {node.disabled = true;});
    try {
      historyList = await account.posts.history(historyPost,historyPage); const target = history.querySelector('.board-history-list'); target.replaceChildren();
      for (const release of historyList.items) {
        const button = text('button',`v${release.number} · ${release.name} · 게임 ${release.gameVersion || '미기재'} · ${new Date(release.publishedAt).toLocaleDateString('ko-KR')}`); button.type = 'button';
        button.addEventListener('click',() => { history.close(); void run(async () => { url({release:release.number}); current = await account.posts.get(historyPost,release.number); renderDetail(); }); }); target.append(button);
      }
      history.querySelector('nav span').textContent = `${historyPage} / ${Math.max(1,Math.ceil(historyList.total / 6))}`;
    } catch (error) { history.querySelector('[role="status"]').textContent = error.message; }
    finally { historyBusy = false; history.removeAttribute('aria-busy'); history.querySelectorAll('button').forEach(node => {node.disabled = false;}); history.querySelector('[data-history="previous"]').disabled = historyPage <= 1; history.querySelector('[data-history="next"]').disabled = !historyList || historyPage * 6 >= historyList.total; }
  }
  action('publish').addEventListener('click',() => run(async () => { await requireMember(); publish.open(); }));
  action('release').addEventListener('click',() => publish.open(null,current));
  action('list').addEventListener('click',() => {url({post:null,release:null}); current = null; renderDetail();});
  action('latest').addEventListener('click',() => run(async () => {url({release:null}); current = await account.posts.get(current.id); renderDetail();}));
  action('favorite').addEventListener('click',() => run(async () => {await requireMember(); await account.posts.favorite(current.id,!current.favorited); await refresh(); documentRef.dispatchEvent(new root.Event('toram:posts-changed'));}));
  action('copy').addEventListener('click',() => run(async () => {
    await requireMember(); const input = {postId:current.id,releaseNumber:current.release.number}, fingerprint = JSON.stringify(input);
    if (copyFingerprint !== fingerprint) {copyFingerprint = fingerprint; copyKey = root.crypto.randomUUID();}
    const saved = await account.inventory.copy(input,copyKey); copyKey = null; copyFingerprint = null;
    say(`“${saved.name}”을 내 독립 구성으로 복사했습니다.`);
    const link = text('button','내 사본 열기'); link.type = 'button'; link.addEventListener('click',() => shell.open('inventory',{params:{type:saved.type,selected:saved.id}})); find('.board-status').append(' ',link);
  }));
  action('history').addEventListener('click',() => {historyPost = current.id; historyPage = 1; historyList = null; history.querySelector('[role="status"]').textContent = ''; history.showModal(); void refreshHistory();});
  history.querySelector('[data-history="close"]').addEventListener('click',() => history.close()); history.addEventListener('close',() => action('history').focus());
  for (const [direction,delta] of [['previous',-1],['next',1]]) history.querySelector(`[data-history="${direction}"]`).addEventListener('click',() => {historyPage += delta; void refreshHistory();});
  for (const [direction,delta] of [['previous',-1],['next',1]]) action(direction).addEventListener('click',() => run(async () => {url({page:list.page + delta,post:null,release:null}); await refresh();}));
  for (const [direction,delta] of [['previous',-1],['next',1]]) action('summary-' + direction).addEventListener('click',() => {summaryPage += delta; renderSummary();});
  form.addEventListener('submit',event => { event.preventDefault(); void run(async () => {url({type:form.elements.type.value,sort:form.elements.sort.value,q:form.elements.q.value.trim(),tag:form.elements.tag.value.trim(),mine:form.elements.mine.checked ? 1 : null,favorites:form.elements.favorites.checked ? 1 : null,page:null,post:null,release:null}); await refresh();}); });
  find('.board-manage').addEventListener('submit',event => {event.preventDefault(); void run(async () => {
    const values = event.target.elements; await account.posts.manage(current.id,{revision:current.revision,title:values.title.value,description:values.description.value,tags:values.tags.value.split(',').map(value => value.trim()).filter(Boolean)}); await refresh(); say('게시글 정보를 저장했습니다.');
  });});
  for (const name of ['visibility','delete']) action(name).addEventListener('click',() => run(async () => {
    const visibility = name === 'delete' ? 'deleted' : current.visibility === 'public' ? 'private' : 'public';
    if (!root.confirm(visibility === 'deleted' ? '게시글을 삭제 상태로 바꿀까요? 기존 사본은 유지됩니다.' : `${visibility === 'public' ? '공개' : '비공개'}로 전환할까요?`)) return;
    await account.posts.manage(current.id,{revision:current.revision,visibility}); await refresh(); documentRef.dispatchEvent(new root.Event('toram:posts-changed'));
  }));
  documentRef.addEventListener('toram:account-changed',() => {generation++; current = null; list = null; find('.board-list').replaceChildren(); renderDetail(); if (shell.active('board')) {if (busy) pending = true; else void run(refresh);}});
  shell.register('board',page,{enter() {if (busy) pending = true; else void run(refresh);}});
  return {publish:record => publish.open(record)};
}
