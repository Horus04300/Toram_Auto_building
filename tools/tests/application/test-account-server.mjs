import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { mkdtemp, rm } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { DatabaseSync } from 'node:sqlite';
import { createAccountServer } from '../../../server/account-server.mjs';
import { createInventoryStore } from '../../../server/inventory-store.mjs';

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
  const equipment = { type:'equipment', schemaVersion:1, name:'내 지팡이', data:{ slot:'mainWeapon', equipment:{ ...item.equipment, crystas:['',''], lockedCrystaSlots:[true,false] } } };
  assert.equal((await call('inventory', { method:'POST', data:equipment })).body.code, 'AUTH_REQUIRED');
  const created = await call('inventory', { method:'POST', cookie:cookieA, data:equipment });
  assert.equal(created.status, 201);
  assert.equal(created.body.revision, 1);
  assert.equal(created.body.equipmentType, 'staff');
  const objectId = created.body.id;
  assert.deepEqual((await call('inventory/' + objectId, { cookie:cookieA })).body.data, equipment.data);
  const duplicate = await call('inventory', { method:'POST', cookie:cookieA, data:equipment });
  assert.equal(duplicate.status, 201); assert.notEqual(duplicate.body.id, objectId);
  const listing = await call('inventory?type=equipment&equipmentType=staff&q=지팡이&page=1&pageSize=1', { cookie:cookieA });
  assert.equal(listing.body.total, 2); assert.equal(listing.body.items.length, 1); assert.equal(listing.body.items[0].data, undefined);
  assert.equal((await call('inventory?page=2&pageSize=1', { cookie:cookieA })).body.items.length, 1);
  for (const query of ['page=0', 'pageSize=51', 'equipmentType=unknown', 'type=unknown', 'q=' + 'a'.repeat(81)]) assert.equal((await call('inventory?' + query, { cookie:cookieA })).status, 400);
  for (const bad of [ { ...equipment, schemaVersion:2 }, { ...equipment, owner_id:'forged' },
    { ...equipment, data:{ ...equipment.data, equipment:{ ...equipment.data.equipment, options:[{ key:'UNKNOWN', value:1 }] } } },
    { ...equipment, data:{ ...equipment.data, equipment:{ ...equipment.data.equipment, attack:'100' } } },
    { ...equipment, data:{ ...equipment.data, equipment:{ ...equipment.data.equipment, catalogItem:{ gameItemId:123 } } } },
    { ...equipment, data:{ ...equipment.data, equipment:{ ...equipment.data.equipment, appearance:{} } } } ]) {
    assert.equal((await call('inventory', { method:'POST', cookie:cookieA, data:bad })).status, 400);
  }
  const inventoryPreflight = await call('inventory/' + objectId, { method:'OPTIONS', requestOrigin:'https://tauri.localhost' });
  assert.match(inventoryPreflight.headers.get('access-control-allow-methods'), /PUT/u);
  const update = { ...equipment, name:'수정한 지팡이', revision:1, data:structuredClone(equipment.data) }; update.data.equipment.attack = 500;
  assert.equal((await call('inventory/' + objectId, { method:'PUT', cookie:cookieA, data:update })).body.revision, 2);
  assert.equal((await call('inventory/' + objectId, { method:'PUT', cookie:cookieA, data:update })).body.code, 'REVISION_CONFLICT');
  assert.equal((await call('inventory/' + objectId, { method:'DELETE', cookie:cookieA, data:{ revision:1 } })).status, 409);
  assert.equal((await call('inventory/' + duplicate.body.id, { cookie:cookieA })).body.data.equipment.attack, 100, 'Independent objects must not update together.');
  assert.equal((await call('inventory/' + objectId, { cookie:cookieA })).body.data.equipment.attack, 500);
  const armorInput = {type:'equipment',schemaVersion:1,name:'조립용 몸 장비',data:{slot:'armor',equipment:{type:'일반옷',attack:null,refinement:null,stability:null,options:[],crystas:['',''],lockedCrystaSlots:[false,false]}}};
  const ownArmor = await call('inventory',{method:'POST',cookie:cookieA,data:armorInput});
  const mergeInput = {left:{objectId,revision:2},right:{objectId:ownArmor.body.id,revision:1},name:'내 장비 세팅',choices:[]};
  assert.equal((await call('inventory/merges/preview',{method:'POST',cookie:cookieA,data:mergeInput})).body.type,'equipment_set');
  assert.equal((await call('inventory/merges',{method:'POST',cookie:cookieA,data:mergeInput})).body.code,'REQUEST_KEY_REQUIRED');
  const mergeOptions = {method:'POST',cookie:cookieA,data:mergeInput,headers:{'Idempotency-Key':'account-merge-key-0001'}};
  const mergedSet = await call('inventory/merges',mergeOptions);
  assert.equal(mergedSet.status,201); assert.equal(mergedSet.body.type,'equipment_set');
  assert.deepEqual((await call('inventory/merges',mergeOptions)).body,mergedSet.body);
  assert.equal((await call('inventory?type=equipment_set',{cookie:cookieA})).body.total,1);
  googleSub = 'google-user-b';
  const cookieB = await signIn();
  assert.deepEqual((await call('builds', { cookie:cookieB })).body, []);
  assert.equal((await call('inventory', { cookie:cookieB })).body.total, 0);
  assert.equal((await call('inventory/merges/preview',{method:'POST',cookie:cookieB,data:mergeInput})).status,404);
  for (const method of ['GET','PUT','DELETE']) assert.equal((await call('inventory/' + objectId, { method, cookie:cookieB, ...(method === 'GET' ? {} : {data:update}) })).status, 404);
  assert.equal((await call('inventory/' + objectId, { method:'DELETE', cookie:cookieA, data:{revision:2} })).status, 200);
  assert.equal((await call('inventory/' + objectId, { cookie:cookieA })).status, 404);
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
  const inventoryOwner = inspect.prepare('SELECT id FROM users WHERE google_sub=?').get('google-user-a').id;
  const reopened = createInventoryStore(inspect);
  assert.equal(reopened.get(inventoryOwner, duplicate.body.id).data.equipment.attack, 100, 'Reopening the schema must preserve saved objects.');
  assert.equal(inspect.prepare('SELECT count(*) AS total FROM records WHERE user_id=?').get(inventoryOwner).total, 2, 'Legacy item/favorite records must remain untouched.');
  const stored = inspect.prepare('SELECT * FROM inventory_objects WHERE id=?').get(duplicate.body.id);
  const fillInventory = inspect.prepare('INSERT INTO inventory_objects VALUES (?,?,?,?,?,?,?,?,?,?,?)');
  const alreadyStored = inspect.prepare('SELECT count(*) AS total FROM inventory_objects WHERE owner_id=? AND type=?').get(inventoryOwner,'equipment').total;
  for (let i = alreadyStored; i < 200; i++) fillInventory.run('quota-' + i, inventoryOwner, stored.type, stored.name, stored.schema_version, 1, stored.equipment_type, stored.data_json, stored.provenance_json, stored.created_at, stored.updated_at);
  assert.throws(() => reopened.create(inventoryOwner, equipment), error => error.apiCode === 'INVENTORY_LIMIT');
  const session = inspect.prepare('SELECT token_hash FROM sessions LIMIT 1').get();
  assert.match(session.token_hash, /^[a-f0-9]{64}$/u, 'Only token hashes are stored');
  inspect.prepare('UPDATE sessions SET expires_at=0').run();
  inspect.close();
  assert.equal((await call('items', { cookie:cookieB })).status, 401);
  for (const path of ['/server/.env', '/.git/config', '/assets/%2e%2e%5cserver/.env']) {
    assert.equal((await fetch(base + path)).status, 404);
  }
  console.log('Account server: PASS (OAuth/CSRF/CORS, private records + inventory CRUD/filter/pages, independent objects, revision conflicts, validation/quota, schema reopen/legacy preservation, desktop login, logout/expiry)');
} finally {
  await new Promise(resolve => server.close(resolve));
  await rm(temporary, { recursive:true, force:true });
}
