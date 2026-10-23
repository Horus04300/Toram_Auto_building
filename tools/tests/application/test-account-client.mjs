import assert from 'node:assert/strict';
import { createHash, webcrypto } from 'node:crypto';
import { createAccountClient } from '../../../web/src/application/account-client.mjs';

let last, imported, configured = true;
const item = { options:[], crystas:[], lockedCrystaSlots:[] };
const document = { documentElement:{ dataset:{ runtime:'web' } }, defaultView:{
  location:{ origin:'https://calculator.example', assign(url) { last = url; } },
  ToramApplication:{ Settings:{ flush() {}, snapshot(name) { return { name, build:{ equipment:{ mainWeapon:structuredClone(item) } } }; }, import(value) { imported = JSON.parse(value); } } },
  async fetch(url, options) {
    last = { url:String(url), options };
    const path = new URL(url).pathname;
    if (path === '/api/session') return { ok:true, json:async () => ({ configured, user:null }) };
    if (path.endsWith('/bad')) return { ok:false, status:401, json:async () => ({ error:'로그인이 필요합니다.' }) };
    if (options.method === 'POST') return { ok:true, json:async () => ({ id:'record' }) };
    return { ok:true, json:async () => ({ data:{ schema:'toram.account-item.v1', slot:'mainWeapon', equipment:{ ...item, attack:400 } } }) };
  }
} };
const account = createAccountClient(document);
await account.save('builds', '마법사');
assert.equal(last.url, 'https://calculator.example/api/builds');
assert.equal(last.options.credentials, 'same-origin');
assert.equal(JSON.parse(last.options.body).data.name, '마법사');
await account.save('items', '지팡이', 'mainWeapon');
assert.equal(JSON.parse(last.options.body).data.schema, 'toram.account-item.v1');
assert.throws(() => account.save('favorites', '게임 아이템 없음', 'mainWeapon'), /게임 아이템/);
await account.load('items', 'valid');
assert.equal(imported.build.equipment.mainWeapon.attack, 400);
await assert.rejects(account.load('builds', 'bad'), error => error.status === 401);
configured = false;
await assert.rejects(account.login(), /서버 설정/);
configured = true;
await account.login();
assert.equal(last, 'https://calculator.example/api/auth/google');
const offline = createAccountClient({ documentElement:{ dataset:{ runtime:'desktop' } }, defaultView:{}, querySelector() { return null; } });
assert.deepEqual(await offline.session(), { configured:false, user:null });
await assert.rejects(offline.login(), /계정 서버/);
let authorization, challenge, opened, pollSecret;
const desktopDocument = { documentElement:{ dataset:{ runtime:'desktop' } }, querySelector() { return { content:'https://calculator.example' }; }, defaultView:{
  crypto:webcrypto, setTimeout(callback) { return setTimeout(callback, 0); }, clearTimeout,
  __TAURI__:{ core:{ async invoke(command, args) { assert.equal(command, 'open_account_login'); opened = args.url; } } },
  async fetch(url, options) {
    authorization = options.headers.Authorization;
    assert.equal(options.credentials, 'omit');
    const path = new URL(url).pathname;
    let result;
    if (path === '/api/session') result = { configured:true, user:null };
    else if (path === '/api/auth/desktop') {
      challenge = JSON.parse(options.body).challenge;
      result = { id:'a'.repeat(43), expiresAt:Date.now() + 10000 };
    } else if (path.startsWith('/api/auth/desktop/')) {
      pollSecret = JSON.parse(options.body).secret;
      assert.equal(createHash('sha256').update(pollSecret).digest('hex'), challenge);
      result = { token:'desktop-session', user:{ id:'me', nickname:'앱 사용자' } };
    } else result = { ok:true };
    return { ok:true, json:async () => result };
  }
} };
const desktopAccount = createAccountClient(desktopDocument);
assert.equal((await desktopAccount.login()).nickname, '앱 사용자');
assert.match(opened, /^https:\/\/calculator.example\/api\/auth\/google\?desktop=a{43}$/u);
assert.ok(!opened.includes(pollSecret));
await desktopAccount.session();
assert.equal(authorization, 'Bearer desktop-session');
await desktopAccount.logout();
await desktopAccount.session();
assert.equal(authorization, undefined);
desktopDocument.defaultView.__TAURI__.core.invoke = async () => desktopAccount.cancelLogin();
await assert.rejects(desktopAccount.login(), error => error.name === 'AbortError');
console.log('Account client: PASS (same-origin cookies, snapshots/restore, validation/401/config errors, Google redirect, desktop challenge/browser/poll/bearer/logout/cancel)');
