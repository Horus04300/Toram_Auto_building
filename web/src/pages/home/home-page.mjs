import { PLATFORM_PAGES, platformIcon } from '../../layout/platform-shell.mjs';
import { EQUIPMENT_TYPES } from '../../application/equipment-object.mjs';

const RECENT_KEY = 'toram.recent-menus.v1';
export function createHomePage(documentRef, account, shell) {
  const root = documentRef.defaultView, page = documentRef.getElementById('homeWorkspace');

  const find = selector => page.querySelector(selector);
  let generation = 0;
  let rankGeneration = 0, rankPage = 1;
  const mobile = root.matchMedia('(max-width:700px)');
  async function refreshRanking() {
    const request = ++rankGeneration, target = find('.home-ranking-content'), navigation = find('.home-rank-pagination');
    navigation.querySelectorAll('button').forEach(button => {button.disabled = true;});
    try {
      const list = await account.posts.list({type:'build',sort:'favorites',page:rankPage,pageSize:mobile.matches ? 1 : 3});
      if (request !== rankGeneration) return;
      if (list.total && !list.items.length && rankPage > 1) {rankPage = 1; void refreshRanking(); return;}
      target.replaceChildren(); navigation.hidden = list.total <= list.pageSize;
      if (!list.items.length) target.innerHTML = `<div class="home-empty">${platformIcon('bookmark')}<strong>아직 공개된 빌드가 없습니다</strong><p>공개 빌드가 등록되면 이곳에서 확인할 수 있어요.</p></div>`;
      for (const [index,item] of list.items.entries()) {
        const button = documentRef.createElement('button'); button.type = 'button'; button.className = 'home-rank-row';
        button.title = item.title;
        const rank = documentRef.createElement('span'), info = documentRef.createElement('span'), title = documentRef.createElement('strong'), meta = documentRef.createElement('small'), count = documentRef.createElement('b');
        rank.textContent = String((list.page - 1) * list.pageSize + index + 1); title.textContent = item.title;
        meta.textContent = `${EQUIPMENT_TYPES[item.equipmentType]?.[0] || '부분 빌드'} · ${item.author.nickname} · v${item.latestRelease.number} · 게임 ${item.latestRelease.gameVersion || '미기재'} · ${new Date(item.latestRelease.publishedAt).toLocaleDateString('ko-KR')}`;
        count.textContent = String(item.favoriteCount); info.append(title,meta); button.append(rank,info,count);
        button.addEventListener('click',() => shell.open('board',{params:{post:item.id}})); target.append(button);
      }
      navigation.querySelector('span').textContent = `${list.page} / ${Math.max(1,Math.ceil(list.total/list.pageSize))}`;
      navigation.querySelector('[data-rank="previous"]').disabled = list.page <= 1;
      navigation.querySelector('[data-rank="next"]').disabled = list.page * list.pageSize >= list.total;
    } catch (error) {
      if (request !== rankGeneration) return;
      navigation.hidden = true; target.replaceChildren(); const empty = documentRef.createElement('div'); empty.className = 'home-empty';
      const message = documentRef.createElement('p'); message.textContent = '인기 빌드를 불러오지 못했습니다. ' + error.message;
      const retry = documentRef.createElement('button'); retry.type = 'button'; retry.textContent = '다시 불러오기'; retry.addEventListener('click',() => {void refreshRanking();}); empty.append(message,retry); target.append(empty);
    }
  }
  for (const [direction,delta] of [['previous',-1],['next',1]]) find(`[data-rank="${direction}"]`).addEventListener('click',() => {rankPage += delta; void refreshRanking();});
  mobile.addEventListener('change',() => {rankPage = 1; if (shell.active('home')) void refreshRanking();});
  documentRef.addEventListener('toram:posts-changed',() => {if (shell.active('home')) void refreshRanking();});
  function readRecent() {
    try {
      const value = JSON.parse(root.localStorage.getItem(RECENT_KEY) || '[]');
      return Array.isArray(value) ? [...new Set(value.filter(id => PLATFORM_PAGES.some(item => item.id === id && !item.pending && id !== 'home')))].slice(0,4) : [];
    } catch { return []; }
  }
  function renderRecent() {
    const target = find('.home-recent-content'), recent = readRecent(); target.replaceChildren();
    if (!recent.length) { target.innerHTML = `<div class="home-empty">${platformIcon('clock')}<strong>아직 사용한 메뉴가 없습니다</strong><p>왼쪽 메뉴에서 작업을 시작해 보세요.</p></div>`; return; }
    for (const id of recent) {
      const item = PLATFORM_PAGES.find(item => item.id === id), button = documentRef.createElement('button'); button.type = 'button';
      button.className = 'home-recent-menu'; button.innerHTML = `${platformIcon(item.icon)}<span>${item.label}</span>${platformIcon('arrow')}`;
      button.addEventListener('click',() => shell.open(id)); target.append(button);
    }
  }
  async function refreshAccount() {
    const request = ++generation;
    try {
      const session = await account.session(); if (request !== generation) return;
      const user = session.user;
      find('.home-account-name').textContent = user ? user.nickname : '로그인하고 구성을 보관하세요';
      find('.home-account-description').textContent = user ? '내 구성은 인벤토리에서 이어서 사용할 수 있어요.' : '내 인벤토리와 저장한 빌드를 한곳에서.';
      find('.home-login').hidden = Boolean(user); find('.home-inventory').hidden = !user; find('.home-account-manage').hidden = !user;
      find('.home-account-status').textContent = session.configured || user ? '' : '로그인 서버 연결을 준비 중입니다.';
    } catch (error) { if (request === generation) find('.home-account-status').textContent = error.message; }
  }
  find('.home-login').addEventListener('click',async () => {
    const button = find('.home-login'); button.disabled = true;
    try { await account.login(); await refreshAccount(); }
    catch (error) { find('.home-account-status').textContent = error.message; }
    finally { button.disabled = false; }
  });
  find('.home-inventory').addEventListener('click',() => shell.open('inventory'));
  find('.home-account-manage').addEventListener('click',() => documentRef.getElementById('appAccountButton').click());
  documentRef.addEventListener('toram:account-changed',() => { void refreshAccount(); });
  documentRef.addEventListener('close',event => {
    if (event.target.matches?.('.account-dialog') && shell.active('home')) void refreshAccount();
  },true);
  documentRef.addEventListener('toram:page-changed',event => {
    const id = event.detail.page;
    if (id !== 'home') { try { root.localStorage.setItem(RECENT_KEY,JSON.stringify([id,...readRecent().filter(value => value !== id)].slice(0,4))); } catch { /* Storage can be disabled by the browser. */ } }
    renderRecent();
  });
  shell.register('home',page,{enter() { renderRecent(); void refreshAccount(); rankPage = 1; void refreshRanking(); }});
}
