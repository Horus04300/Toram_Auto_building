import { EQUIPMENT_SLOTS as slots, SUB_WEAPON_RULES, validateEquipmentObject } from './equipment-object.mjs';
import { captureObject, applyObject, validateInventoryObject } from './inventory-objects.mjs';

export function createAccountClient(documentRef) {
  const root = documentRef.defaultView;
  const desktop = documentRef.documentElement.dataset.runtime === 'desktop';
  const server = desktop ? documentRef.querySelector('meta[name="account-server"]')?.content : root.location.origin;
  let token = null, loginController = null;
  const ensureCalculator = () => root.ToramApp?.ensureCalculator?.();
  const rules = () => ({registry:root.ToramApp.statRegistry,trees:root.ToramApp.skillTreeData,food:root.ToramApp.foodCatalog,subWeaponRules:SUB_WEAPON_RULES,
    comboSkillIds:root.ToramApp.skillRegistry ? new Set(root.ToramApp.skillRegistry.definitions().filter(skill => skill.sourceRef && ['attack','buff','utility'].includes(skill.kind) && root.ToramApp.skillCatalog.skills.some(item => item.id === skill.id)).map(skill => skill.id)) : null});
  const accountChanged = () => documentRef.dispatchEvent?.(new root.Event('toram:account-changed'));

  async function request(path, options = {}) {
    if (!server) throw new Error('계정 서버 연결을 준비 중입니다. 로컬 저장은 계속 사용할 수 있습니다.');
    const response = await root.fetch(new URL('/api/' + path, server), {
      ...options, credentials:desktop ? 'omit' : 'same-origin',
      headers:{ 'Content-Type':'application/json', ...(token ? { Authorization:'Bearer ' + token } : {}), ...options.headers },
      signal:options.signal || AbortSignal.timeout(15000)
    });
    const body = await response.json().catch(() => ({}));
    if (!response.ok) {
      if (response.status === 401) token = null;
      const error = new Error(body.error || (response.status === 404 ? '계정 서버 연결을 준비 중입니다.' : '서버에 연결할 수 없습니다. 잠시 후 다시 시도하세요.'));
      error.status = response.status;
      error.code = body.code;
      throw error;
    }
    return body;
  }

  function cancelLogin() { loginController?.abort(); loginController = null; }
  async function login() {
    cancelLogin();
    const controller = new AbortController();
    loginController = controller;
    try {
      const state = await request('session', { signal:controller.signal });
      if (!state.configured) throw new Error('Google 로그인 서버 설정이 필요합니다. 로컬 저장은 계속 사용할 수 있습니다.');
      if (!desktop) {
        if (!root.ToramApp?.ensureCalculator || root.ToramApp.calculatorReady) root.ToramApp.settingsRepository?.flushApplicationState();
        if (root.location.pathname === '/inventory') root.sessionStorage.setItem('toram.inventory.return', root.location.pathname + root.location.search);
        root.location.assign(new URL('/api/auth/google', server).href);
        return;
      }
      const secret = root.crypto.randomUUID() + root.crypto.randomUUID();
      const digest = await root.crypto.subtle.digest('SHA-256', new TextEncoder().encode(secret));
      const challenge = Array.from(new Uint8Array(digest), byte => byte.toString(16).padStart(2, '0')).join('');
      const pending = await request('auth/desktop', { method:'POST', body:JSON.stringify({ challenge }), signal:controller.signal });
      const url = new URL('/api/auth/google', server);
      url.searchParams.set('desktop', pending.id);
      await root.__TAURI__.core.invoke('open_account_login', { url:url.href });
      while (!controller.signal.aborted && Date.now() < pending.expiresAt) {
        await new Promise((resolve, reject) => {
          const done = () => { controller.signal.removeEventListener('abort', aborted); resolve(); };
          const timer = root.setTimeout(done, 2000);
          const aborted = () => { root.clearTimeout(timer); reject(new DOMException('Login cancelled', 'AbortError')); };
          controller.signal.addEventListener('abort', aborted, { once:true });
        });
        const result = await request('auth/desktop/' + pending.id, { method:'POST', body:JSON.stringify({ secret }), signal:controller.signal });
        if (result.token) { token = result.token; accountChanged(); return result.user; }
      }
      if (controller.signal.aborted) throw new DOMException('Login cancelled', 'AbortError');
      throw new Error('로그인 대기 시간이 끝났습니다. 다시 시도하세요.');
    } finally { if (loginController === controller) loginController = null; }
  }

  function itemData(name, slot) {
    if (!slots[slot]) throw new Error('장비 부위를 선택하세요.');
    return { schema:'toram.account-item.v1', slot, equipment:root.ToramApp.settingsRepository.snapshot(name).build.equipment[slot] };
  }
  async function save(kind, name, slot) {
    await ensureCalculator();
    const data = kind === 'builds' ? root.ToramApp.settingsRepository.snapshot(name) : itemData(name, slot);
    if (kind === 'favorites' && !data.equipment.catalogItem) throw new Error('게임 아이템을 선택한 장비만 즐겨찾기에 추가할 수 있습니다.');
    return request(kind, { method:'POST', body:JSON.stringify({ name, data }) });
  }
  async function load(kind, id) {
    const record = await request(kind + '/' + encodeURIComponent(id));
    await ensureCalculator();
    if (kind === 'builds') root.ToramApp.settingsRepository.importSavedBuild(JSON.stringify(record.data));
    else {
      const data = record.data;
      if (data?.schema !== 'toram.account-item.v1' || !slots[data.slot] || !data.equipment || typeof data.equipment !== 'object') throw new Error('저장된 장비 형식이 올바르지 않습니다.');
      const current = root.ToramApp.settingsRepository.snapshot('내 세팅');
      current.build.equipment[data.slot] = data.equipment;
      root.ToramApp.settingsRepository.importSavedBuild(JSON.stringify(current));
    }
    return record;
  }
  function equipmentData(slot) {
    const data = itemData('내 장비', slot);
    const value = { slot:data.slot, equipment:data.equipment };
    validateEquipmentObject(value, root.ToramApp.statRegistry);
    return value;
  }
  function captured(type, name, parameters) {
    const data = captureObject(type,root.ToramApp.settingsRepository.snapshot(name),parameters); validateInventoryObject(type,data,rules()); return data;
  }
  const inventory = Object.freeze({
    register(name, type, data) { return request('inventory',{method:'POST',body:JSON.stringify({name,type,schemaVersion:1,data})}); },
    list(params = {}) { return request('inventory?' + new URLSearchParams(params)); },
    get(id) { return request('inventory/' + encodeURIComponent(id)); },
    async create(name, slot) { await ensureCalculator(); return request('inventory', { method:'POST', body:JSON.stringify({ type:'equipment', schemaVersion:1, name, data:equipmentData(slot) }) }); },
    async capture(name, type, parameters = {}) { await ensureCalculator(); return request('inventory',{method:'POST',body:JSON.stringify({type,schemaVersion:1,name,data:captured(type,name,parameters)})}); },
    async update(record, name, fromCalculator = false, parameters = {}) {
      if (fromCalculator) await ensureCalculator();
      const data = fromCalculator ? captured(record.type,name,{...parameters,slot:record.data.slot,treeId:record.data.treeId,consumableId:record.data.selection?.gameItemId,previous:record}) : record.data;
      return request('inventory/' + encodeURIComponent(record.id), { method:'PUT', body:JSON.stringify({ type:record.type, schemaVersion:1, revision:record.revision, name, data }) });
    },
    remove(record) { return request('inventory/' + encodeURIComponent(record.id), { method:'DELETE', body:JSON.stringify({ revision:record.revision }) }); },
    preview(input) { return request('inventory/merges/preview',{method:'POST',body:JSON.stringify(input)}); },
    merge(input, key) { return request('inventory/merges',{method:'POST',headers:{'Idempotency-Key':key},body:JSON.stringify(input)}); },
    copy(input,key) { return request('inventory/copies',{method:'POST',headers:{'Idempotency-Key':key},body:JSON.stringify(input)}); },
    async apply(record, comboId) {
      if (record.schemaVersion !== 1) throw new Error('지원하지 않는 구성 형식입니다.');
      await ensureCalculator();
      root.ToramApp.settingsRepository.applySession(applyObject(record,root.ToramApp.settingsRepository.snapshot('내 세팅'),rules(),comboId));
    }
  });
  const posts = Object.freeze({
    list(params = {},mine = false) { return request((mine ? 'me/posts?' : 'posts?') + new URLSearchParams(params)); },
    get(id,number) { return request('posts/' + encodeURIComponent(id) + (number === undefined ? '' : '/releases/' + encodeURIComponent(number))); },
    history(id,page = 1) { return request('posts/' + encodeURIComponent(id) + '/releases?page=' + page); },
    publish(input,key,id) { return request('posts' + (id ? '/' + encodeURIComponent(id) + '/releases' : ''),{method:'POST',headers:{'Idempotency-Key':key},body:JSON.stringify(input)}); },
    manage(id,input) { return request('posts/' + encodeURIComponent(id),{method:'PATCH',body:JSON.stringify(input)}); },
    favorite(id,enabled) { return request('posts/' + encodeURIComponent(id) + '/favorite',{method:enabled ? 'PUT' : 'DELETE',body:'{}'}); }
  });
  return Object.freeze({ slots, login, cancelLogin, save, load, inventory, posts,
    async session() { if (!server) return { configured:false, user:null }; return request('session'); },
    async logout() { cancelLogin(); await request('logout', { method:'POST', body:'{}' }); token = null; accountChanged(); },
    nickname(name) { return request('me', { method:'PATCH', body:JSON.stringify({ nickname:name }) }); },
    list(kind) { return request(kind); },
    remove(kind, record) { return request(kind + '/' + encodeURIComponent(record.id), { method:'DELETE', body:JSON.stringify({ version:record.version }) }); }
  });
}
