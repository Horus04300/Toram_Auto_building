const slots = Object.freeze({ mainWeapon:'주무기', subWeapon:'보조무기', armor:'몸 장비', additional:'추가 장비', special:'특수 장비' });

export function createAccountClient(documentRef) {
  const root = documentRef.defaultView;
  const desktop = documentRef.documentElement.dataset.runtime === 'desktop';
  const server = desktop ? documentRef.querySelector('meta[name="account-server"]')?.content : root.location.origin;
  let token = null, loginController = null;
  const settings = () => root.ToramApplication.Settings;

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
        settings().flush();
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
        if (result.token) { token = result.token; return result.user; }
      }
      if (controller.signal.aborted) throw new DOMException('Login cancelled', 'AbortError');
      throw new Error('로그인 대기 시간이 끝났습니다. 다시 시도하세요.');
    } finally { if (loginController === controller) loginController = null; }
  }

  function snapshot(name) { return settings().snapshot(name); }
  function itemData(name, slot) {
    if (!slots[slot]) throw new Error('장비 부위를 선택하세요.');
    return { schema:'toram.account-item.v1', slot, equipment:snapshot(name).build.equipment[slot] };
  }
  function save(kind, name, slot) {
    const data = kind === 'builds' ? snapshot(name) : itemData(name, slot);
    if (kind === 'favorites' && !data.equipment.catalogItem) throw new Error('게임 아이템을 선택한 장비만 즐겨찾기에 추가할 수 있습니다.');
    return request(kind, { method:'POST', body:JSON.stringify({ name, data }) });
  }
  async function load(kind, id) {
    const record = await request(kind + '/' + encodeURIComponent(id));
    if (kind === 'builds') settings().import(JSON.stringify(record.data));
    else {
      const data = record.data;
      if (data?.schema !== 'toram.account-item.v1' || !slots[data.slot] || !data.equipment || typeof data.equipment !== 'object') throw new Error('저장된 장비 형식이 올바르지 않습니다.');
      const current = snapshot('내 세팅');
      current.build.equipment[data.slot] = data.equipment;
      settings().import(JSON.stringify(current));
    }
    return record;
  }
  return Object.freeze({ slots, login, cancelLogin, save, load,
    async session() { if (!server) return { configured:false, user:null }; return request('session'); },
    async logout() { cancelLogin(); await request('logout', { method:'POST', body:'{}' }); token = null; },
    nickname(name) { return request('me', { method:'PATCH', body:JSON.stringify({ nickname:name }) }); },
    list(kind) { return request(kind); },
    remove(kind, record) { return request(kind + '/' + encodeURIComponent(record.id), { method:'DELETE', body:JSON.stringify({ version:record.version }) }); }
  });
}
