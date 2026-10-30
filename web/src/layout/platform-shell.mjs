import { ITEM_MENU_ICON, BOARD_MENU_ICON, CATALOG_MENU_ICON } from '../ui/game-menu-icons.mjs';

export const PLATFORM_PAGES = Object.freeze([
  { id:'home', label:'홈', icon:'home' },
  { id:'catalog', label:'도감', icon:'book' },
  { id:'inventory', label:'인벤토리', icon:'bag' },
  { id:'simulator', label:'시뮬레이터', icon:'flask', pending:true },
  { id:'calculator', label:'계산기', icon:'calculator' },
  { id:'board', label:'게시판', icon:'board' }
]);

const paths = {
  home:'<path d="m3 10 9-7 9 7v10H15v-7H9v7H3Z"/>',
  flask:'<path d="M9 3h6m-5 0v7L4 20a1 1 0 0 0 1 1h14a1 1 0 0 0 1-1l-6-10V3M7 15h10"/>',
  calculator:'<rect x="5" y="2" width="14" height="20" rx="2"/><path d="M8 6h8M8 11h1m3 0h1m3 0h.1M8 15h1m3 0h1m3 0h.1M8 19h1m3 0h1m3 0h.1"/>',
  user:'<circle cx="12" cy="8" r="4"/><path d="M4 21v-2a8 8 0 0 1 16 0v2"/>',
  bookmark:'<path d="M6 21V4a2 2 0 0 1 2-2h8a2 2 0 0 1 2 2v17l-6-4Z"/>',
  clock:'<circle cx="12" cy="12" r="9"/><path d="M12 6v6l4 2"/>',
  arrow:'<path d="M4 12h16m-6-6 6 6-6 6"/>'
};
export function platformIcon(name) {
  const image = name === 'bag' ? ITEM_MENU_ICON : name === 'board' ? BOARD_MENU_ICON : name === 'book' ? CATALOG_MENU_ICON : null;
  if (image) return `<img src="${image}" width="25" height="25" alt="" aria-hidden="true">`;
  return `<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.7" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true">${paths[name] || paths.home}</svg>`;
}

export function createPlatformShell(documentRef) {
  const root = documentRef.defaultView, desktop = documentRef.documentElement.dataset.runtime === 'desktop';
  const pages = new Map(), remembered = new Map();
  const header = documentRef.querySelector('.app-titlebar'), title = header.querySelector('h1');
  const calculator = documentRef.createElement('div'); calculator.id = 'calculatorWorkspace'; calculator.hidden = true;
  const shell = documentRef.querySelector('.platform-shell'), content = shell.querySelector('#platformContent');
  const loading = content.querySelector('.platform-loading');
  content.append(calculator);
  shell.querySelector('.platform-brand').href = desktop ? '?view=home' : './';
  const links = new Map();
  for (const item of PLATFORM_PAGES) {
    const node = documentRef.createElement('button'); node.type = 'button'; node.className = 'platform-nav-button';
    node.dataset.page = item.id; node.setAttribute('aria-label', item.label + (item.pending ? ' (준비 중)' : ''));
    node.innerHTML = `${platformIcon(item.icon)}<span>${item.label}</span>`;
    node.disabled = true; node.title = item.label + (item.pending ? ' · 준비 중' : '');
    node.addEventListener('click', () => open(item.id)); shell.querySelector('.platform-sidebar nav').append(node); links.set(item.id,node);
  }
  let current = null, navigation = 0;
  function route() {
    const url = new URL(root.location.href), view = url.searchParams.get('view');
    if (['home','inventory','calculator','board','catalog'].includes(view)) return view;
    return ['inventory','calculator','board','catalog'].find(id => url.pathname === '/' + id || url.pathname === '/' + id + '/') || 'home';
  }
  async function render(checkLeave = false) {
    const request = ++navigation;
    if (checkLeave && current !== route() && pages.get(current)?.beforeLeave) {
      if (await pages.get(current).beforeLeave() !== true || request !== navigation) return;
    }
    current = route();
    const page = pages.get(current);
    for (const value of pages.values()) value.node.hidden = true;
    loading.hidden = true; loading.setAttribute('role','status');
    for (const [id,link] of links) link.setAttribute('aria-current', id === current ? 'page' : 'false');
    const label = PLATFORM_PAGES.find(item => item.id === current).label;
    title.querySelector('.platform-breadcrumb').textContent = label; documentRef.title = `${label} · TORAM`;
    documentRef.body.dataset.page = current; documentRef.body.classList.toggle('is-inventory-page',current === 'inventory');
    documentRef.dispatchEvent(new root.CustomEvent('toram:page-changed', {detail:{page:current}}));
    try {
      if (page.prepare) {
        loading.querySelector('span').textContent = '화면을 준비하고 있습니다.'; loading.hidden = false;
        await page.prepare();
        if (request !== navigation) return;
      }
      loading.hidden = true; page.node.hidden = false;
      page.enter?.();
    } catch (error) {
      if (request !== navigation) return;
      loading.querySelector('span').textContent = '화면을 불러오지 못했습니다. 연결을 확인한 뒤 새로고침해 주세요.';
      loading.setAttribute('role','alert'); loading.hidden = false;
    }
  }
  function open(id, { skipGuard = false, params } = {}) {
    if (!pages.has(id) || !skipGuard && pages.get(current)?.canLeave?.() === false) return false;
    if (!skipGuard && pages.get(current)?.beforeLeave) return Promise.resolve(pages.get(current).beforeLeave()).then(allowed => allowed === true && open(id,{skipGuard:true,params}));
    if (current) remembered.set(current,new URL(root.location.href));
    const url = remembered.get(id) || new URL(root.location.href);
    if (!remembered.has(id)) url.search = '';
    if (params) { url.search = new URLSearchParams(params).toString(); }
    url.pathname = desktop ? '/index.html' : id === 'home' ? '/' : '/' + id;
    if (desktop) url.searchParams.set('view',id);
    if (root.location.href !== url.href) root.history.pushState(null,'',url);
    void render(); content.focus({preventScroll:true}); return true;
  }
  shell.querySelector('.platform-brand').addEventListener('click', event => { event.preventDefault(); open('home'); });
  return {
    calculator, open,
    register(id,node,options = {}) {
      pages.set(id,{node,...options}); node.hidden = id !== current;
      if (node !== calculator) content.append(node);
      links.get(id).disabled = false;
      if (id === current) void render();
    },
    start() { root.addEventListener('popstate',() => {void render(true);}); return render(); },
    active: id => route() === id
  };
}
