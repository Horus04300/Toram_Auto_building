import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { mkdtemp, rm } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { DatabaseSync } from 'node:sqlite';
import { createAccountServer } from '../../../server/account-server.mjs';

const origin = 'https://calculator.example';
const temporary = await mkdtemp(join(tmpdir(), 'toram-account-'));
const database = join(temporary, 'accounts.sqlite');
let googleSub = 'google-user-a', googleFailure = false;
const server = createAccountServer({ publicOrigin:origin, clientId:'test-id', clientSecret:'test-secret', database,
  fetchImpl:async (url, options) => {
    if (googleFailure) return { ok:false };
    if (url.endsWith('/token')) {
      assert.equal(options.body.get('client_secret'), 'test-secret');
      assert.equal(options.body.get('grant_type'), 'authorization_code');
      assert.ok(options.body.get('code_verifier'));
      return { ok:true, json:async () => ({ access_token:'google-access-token' }) };
    }
    assert.equal(url, 'https://openidconnect.googleapis.com/v1/userinfo');
    assert.equal(options.headers.Authorization, 'Bearer google-access-token');
    return { ok:true, json:async () => ({ sub:googleSub, name:'모험가' }) };
  } });
await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));
const base = `http://127.0.0.1:${server.address().port}`;
async function call(path, { method = 'GET', data, cookie, token, requestOrigin = origin, headers = {} } = {}) {
  const response = await fetch(base + '/api/' + path, { method, redirect:'manual', headers:{ Origin:requestOrigin,
    ...(cookie ? { Cookie:cookie } : {}), ...(token ? { Authorization:'Bearer ' + token } : {}),
    ...(data === undefined ? {} : { 'Content-Type':'application/json' }), ...headers }, body:data === undefined ? undefined : JSON.stringify(data) });
  const text = await response.text();
  return { status:response.status, headers:response.headers, body:text ? JSON.parse(text) : null };
}
async function start(desktop) {
  const response = await call('auth/google' + (desktop ? '?desktop=' + desktop : ''));
  assert.equal(response.status, 302);
  const url = new URL(response.headers.get('location'));
  assert.equal(url.origin, 'https://accounts.google.com');
  assert.equal(url.searchParams.get('scope'), 'openid profile');
  assert.equal(url.searchParams.get('code_challenge_method'), 'S256');
  return { state:url.searchParams.get('state'), cookie:response.headers.get('set-cookie').split(';')[0] };
}
async function callback(login) { return call('auth/google/callback?code=test-code&state=' + login.state, { cookie:login.cookie }); }
async function signIn() {
  const response = await callback(await start());
  assert.equal(response.status, 302);
  const cookies = response.headers.getSetCookie();
  assert.ok(cookies.every(value => /HttpOnly/u.test(value) && /Secure/u.test(value) && /SameSite=Lax/u.test(value)));
  return cookies.find(value => value.startsWith('__Host-toram_session=')).split(';')[0];
}
const item = { schema:'toram.account-item.v1', slot:'mainWeapon', equipment:{ type:'지팡이', attack:100, refinement:15, stability:60, options:[{ key:'MATK', value:20 }], crystas:[], lockedCrystaSlots:[] } };
const build = { format:'toram-auto-build-document', schemaVersion:2, documentType:'saved-build', name:'테스트 빌드', createdAt:new Date().toISOString(), updatedAt:new Date().toISOString(), build:{ character:{}, equipment:{}, skillLevels:{}, activeBuffs:{}, externalOptions:[], combo:[] }, scenario:{ target:{} } };
try {
  assert.deepEqual((await call('session')).body, { configured:true, user:null });
  assert.equal((await call('builds')).status, 401);
  assert.equal((await call('session', { requestOrigin:'https://evil.example' })).status, 403);
  const preflight = await call('builds', { method:'OPTIONS', requestOrigin:'https://tauri.localhost' });
  assert.equal(preflight.headers.get('access-control-allow-origin'), 'https://tauri.localhost');
  assert.equal(preflight.headers.get('access-control-allow-credentials'), null);
  const login = await start();
  assert.equal((await callback({ ...login, cookie:'' })).status, 400, 'OAuth state must be bound to the browser');
  assert.equal((await callback(login)).status, 302);
  assert.equal((await callback(login)).status, 400, 'OAuth state must be consumed once');
  googleFailure = true;
  assert.equal((await callback(await start())).status, 502);
  googleFailure = false;
  const cookieA = await signIn();
  assert.equal((await call('me', { method:'PATCH', cookie:cookieA, data:{ nickname:'새 닉네임' } })).body.nickname, '새 닉네임');
  assert.equal((await call('me', { method:'PATCH', cookie:cookieA, data:{ nickname:' ' } })).status, 400);
  const saved = await call('builds', { method:'POST', cookie:cookieA, data:{ name:'내 빌드', data:build, user_id:'forged' } });
  assert.equal(saved.status, 201);
  const id = saved.body.id;
  assert.deepEqual((await call('builds/' + id, { cookie:cookieA })).body.data, build);
  assert.equal((await call('items', { method:'POST', cookie:cookieA, data:{ name:'지팡이', data:item } })).status, 201);
  assert.equal((await call('favorites', { method:'POST', cookie:cookieA, data:{ name:'잘못된 즐겨찾기', data:item } })).status, 400);
  const favorite = structuredClone(item); favorite.equipment.catalogItem = { gameItemId:123 };
  assert.equal((await call('favorites', { method:'POST', cookie:cookieA, data:{ name:'아이템', data:favorite } })).status, 201);
  assert.equal((await call('builds', { method:'POST', cookie:cookieA, data:{ name:'잘못된 빌드', data:{} } })).status, 400);
  assert.equal((await call('builds', { method:'POST', cookie:cookieA, data:{ name:'용량 초과', data:{ junk:'a'.repeat(1024 * 1024) } } })).status, 413);
  assert.equal((await call('items', { method:'POST', cookie:cookieA, requestOrigin:'https://evil.example', data:{ name:'공격', data:item } })).status, 403);
  assert.equal((await call('items', { method:'POST', cookie:cookieA, data:{}, headers:{ 'Content-Type':'text/plain' } })).status, 415);
  googleSub = 'google-user-b';
  const cookieB = await signIn();
  assert.deepEqual((await call('builds', { cookie:cookieB })).body, []);
  for (const record of [id, "' OR 1=1--"]) {
    assert.equal((await call('builds/' + encodeURIComponent(record), { cookie:cookieB })).status, 404);
    assert.equal((await call('builds/' + encodeURIComponent(record), { method:'DELETE', cookie:cookieB, data:{ version:1 } })).status, 404);
  }
  assert.equal((await call('builds/' + id, { method:'DELETE', cookie:cookieA, data:{ version:0 } })).status, 409);
  assert.equal((await call('builds/' + id, { method:'DELETE', cookie:cookieA, data:{ version:1 } })).status, 200);
  assert.equal((await call('builds/' + id, { cookie:cookieA })).status, 404);
  const secret = 'a'.repeat(64), challenge = createHash('sha256').update(secret).digest('hex');
  const pending = await call('auth/desktop', { method:'POST', requestOrigin:'https://tauri.localhost', data:{ challenge } });
  assert.equal(pending.status, 201);
  const poll = 'auth/desktop/' + pending.body.id;
  assert.equal((await call(poll, { method:'POST', data:{ secret:'b'.repeat(64) } })).status, 410);
  assert.deepEqual((await call(poll, { method:'POST', data:{ secret } })).body, { pending:true });
  // Desktop callback returns static HTML rather than a browser session cookie.
  const deviceLogin = await start(pending.body.id);
  const completed = await fetch(base + '/api/auth/google/callback?code=test-code&state=' + deviceLogin.state, { headers:{ Cookie:deviceLogin.cookie } });
  assert.equal(completed.status, 200);
  assert.match(await completed.text(), /앱으로 돌아가세요/);
  const delivered = await call(poll, { method:'POST', data:{ secret } });
  assert.equal(delivered.status, 200);
  assert.equal(delivered.body.user.id, (await call('session', { cookie:cookieB })).body.user.id);
  const token = delivered.body.token;
  assert.equal((await call('session', { token })).body.user.nickname, '모험가');
  assert.equal((await call(poll, { method:'POST', data:{ secret } })).status, 410, 'Desktop token must be delivered once');
  assert.equal((await call('logout', { method:'POST', token, data:{} })).status, 200);
  assert.equal((await call('items', { token })).status, 401);
  assert.equal((await call('logout', { method:'POST', cookie:cookieA, data:{} })).status, 200);
  assert.equal((await call('items', { cookie:cookieA })).status, 401);
  const inspect = new DatabaseSync(database);
  const session = inspect.prepare('SELECT token_hash FROM sessions LIMIT 1').get();
  assert.match(session.token_hash, /^[a-f0-9]{64}$/u, 'Only token hashes are stored');
  inspect.prepare('UPDATE sessions SET expires_at=0').run();
  inspect.close();
  assert.equal((await call('items', { cookie:cookieB })).status, 401);
  for (const path of ['/server/.env', '/.git/config', '/assets/%2e%2e%5cserver/.env']) {
    assert.equal((await fetch(base + path)).status, 404);
  }
  console.log('Account server: PASS (OAuth state/PKCE/replay/failure, private CRUD, validation/limits, CSRF/CORS, one-time desktop login, logout/expiry, token hashes, private files)');
} finally {
  await new Promise(resolve => server.close(resolve));
  await rm(temporary, { recursive:true, force:true });
}
