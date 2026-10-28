import assert from 'node:assert/strict';
import {createHash,webcrypto} from 'node:crypto';
import {createRequire} from 'node:module';
import {readFile} from 'node:fs/promises';
import {createAccountClient} from '../../../web/src/application/account-client.mjs';
import {createEquipmentSelection} from '../../../web/src/application/item-catalog.mjs';
import {validateEquipmentObject} from '../../../web/src/application/equipment-object.mjs';

let last, imported, configured = true, inventoryResponse = {};
const item = { options:[], crystas:[], lockedCrystaSlots:[] };
const document = { documentElement:{ dataset:{ runtime:'web' } }, defaultView:{
  location:{ origin:'https://calculator.example', assign(url) { last = url; } },
  ToramSettingsRepository:{ flushApplicationState() {}, snapshot(name) { return { name, build:{ equipment:{ mainWeapon:structuredClone(item) } } }; }, importSavedBuild(value) { imported = JSON.parse(value); }, applySession(value) {imported=structuredClone(value);} },
  async fetch(url, options) {
    last = { url:String(url), options };
    const path = new URL(url).pathname;
    if (path.startsWith('/api/inventory')) return { ok:true, json:async () => inventoryResponse };
    if (path === '/api/session') return { ok:true, json:async () => ({ configured, user:null }) };
    if (path.endsWith('/bad')) return { ok:false, status:401, json:async () => ({ error:'로그인이 필요합니다.' }) };
    if (options.method === 'POST') return { ok:true, json:async () => ({ id:'record' }) };
    return { ok:true, json:async () => ({ data:{ schema:'toram.account-item.v1', slot:'mainWeapon', equipment:{ ...item, attack:400 } } }) };
  }
} };
document.defaultView.ToramApp={settingsRepository:document.defaultView.ToramSettingsRepository};
const account = createAccountClient(document);
await account.save('builds', '마법사');
assert.equal(last.url, 'https://calculator.example/api/builds');
assert.equal(last.options.credentials, 'same-origin');
assert.equal(JSON.parse(last.options.body).data.name, '마법사');
await account.save('items', '지팡이', 'mainWeapon');
assert.equal(JSON.parse(last.options.body).data.schema, 'toram.account-item.v1');
await assert.rejects(account.save('favorites', '게임 아이템 없음', 'mainWeapon'), /게임 아이템/);
await account.load('items', 'valid');
assert.equal(imported.build.equipment.mainWeapon.attack, 400);
await assert.rejects(account.load('builds', 'bad'), error => error.status === 401);
configured = false;
await assert.rejects(account.login(), /서버 설정/);
configured = true;
await account.login();
assert.equal(last, 'https://calculator.example/api/auth/google');
const registry = createRequire(import.meta.url)('../../../web/src/calculation/stat-registry.js');
document.defaultView.ToramApp.statRegistry = registry.statRegistry;
document.defaultView.subWeaponRules = { '지팡이':['없음','방패'], '양손검':['없음'] };
const piece = { type:'지팡이', attack:300, refinement:15, stability:60, options:[{key:'MATKP',value:10}], crystas:['',''], lockedCrystaSlots:[true,false] };
const current = { name:'다른 빌드', build:{ character:{level:325}, equipment:{ mainWeapon:piece, subWeapon:{type:'방패'}, armor:{options:[{key:'MAXHP',value:100}]} }, skillLevels:{test:10} }, scenario:{target:{bossLevel:330}} };
document.defaultView.ToramSettingsRepository.snapshot = () => structuredClone(current);
await account.inventory.create('지팡이', 'mainWeapon');
const payload = JSON.parse(last.options.body);
assert.equal(last.url, 'https://calculator.example/api/inventory');
assert.deepEqual(payload, { type:'equipment', schemaVersion:1, name:'지팡이', data:{slot:'mainWeapon',equipment:piece} });
inventoryResponse = { id:'own-equipment', name:'내 지팡이', type:'equipment', schemaVersion:1, revision:3, data:{ slot:'mainWeapon', equipment:{ ...piece, attack:700 } } };
const record = await account.inventory.get('own-equipment');
assert.equal(last.url, 'https://calculator.example/api/inventory/own-equipment');
await account.inventory.apply(record);
assert.equal(imported.build.equipment.mainWeapon.attack, 700);
assert.equal(current.build.equipment.mainWeapon.attack, 300);
assert.deepEqual(imported.build.equipment.armor, current.build.equipment.armor);
assert.deepEqual(imported.scenario, current.scenario);
assert.deepEqual(imported.build.skillLevels, current.build.skillLevels);
await assert.rejects(account.inventory.apply({...record,data:{...record.data,equipment:{...piece,type:'양손검'}}}), /호환되지/);
await account.inventory.update(record, '편집한 지팡이', true);
assert.equal(last.options.method, 'PUT');
assert.equal(JSON.parse(last.options.body).revision, 3);
assert.equal(JSON.parse(last.options.body).data.equipment.attack, 300);
await account.inventory.update(record, '이름만 수정');
assert.equal(JSON.parse(last.options.body).data.equipment.attack, 700);
await account.inventory.list({type:'equipment',equipmentType:'staff',page:2});
assert.equal(last.url, 'https://calculator.example/api/inventory?type=equipment&equipmentType=staff&page=2');
await account.inventory.remove(record);
assert.deepEqual(JSON.parse(last.options.body), {revision:3});
assert.equal(last.options.method, 'DELETE');
const manifest = JSON.parse(await readFile(new URL('../../../web/public/game-data/items/manifest.json', import.meta.url)));
const special = JSON.parse(await readFile(new URL('../../../web/public/game-data/items/' + manifest.kinds.special, import.meta.url)));
const source = createEquipmentSelection({ id:22001, name:'도감 장비', cacheVersion:manifest.cacheVersion, sourceSha256:manifest.source.catalogSha256, ...special[22001] }, 'special', {mainType:'지팡이',subType:'없음',armorType:'일반옷'}, registry);
const catalogObject = {slot:'special',equipment:{type:null,attack:null,refinement:null,stability:null,options:[],crystas:['',''],lockedCrystaSlots:[false,true],catalogItem:source}};
assert.equal(validateEquipmentObject(catalogObject, registry), catalogObject);
assert.throws(() => validateEquipmentObject({...catalogObject,equipment:{...catalogObject.equipment,catalogItem:{...source,stats:{UNKNOWN:1}}}}, registry));
assert.throws(() => validateEquipmentObject({...catalogObject,slot:'armor'}, registry));
assert.throws(() => validateEquipmentObject({...catalogObject,equipment:{...catalogObject.equipment,appearance:{}}}, registry));
const offline = createAccountClient({ documentElement:{ dataset:{ runtime:'desktop' } }, defaultView:{}, querySelector() { return null; } });
let releaseCalculator, calculatorCalls = 0;
const calculatorReady = new Promise(done => { releaseCalculator = done; });
document.defaultView.ToramApp.ensureCalculator=() => {calculatorCalls++; return calculatorReady;};
await account.session(); await account.inventory.list();
assert.equal(calculatorCalls,0,'Account and inventory reads must not initialize the calculator');
await account.inventory.register('직접 등록한 장비','equipment',{slot:'mainWeapon',equipment:piece});
assert.equal(calculatorCalls,0,'Direct registration must not initialize or capture the calculator');
assert.equal(JSON.parse(last.options.body).data.equipment.attack,300);
const previousImport = imported, applying = account.inventory.apply(record);
assert.equal(calculatorCalls,1);
assert.equal(imported,previousImport,'Applying must wait for calculator restoration');
releaseCalculator(); await applying;
assert.equal(imported.build.equipment.mainWeapon.attack,700);
const previousRequest = last;
document.defaultView.ToramApp.ensureCalculator = async () => {throw new Error('calculator unavailable');};
await assert.rejects(account.save('builds','실패한 저장'),/calculator unavailable/);
assert.equal(last,previousRequest,'Failed calculator preparation must not save a partial snapshot');
const application = document.defaultView.ToramApplication;
delete document.defaultView.ToramApplication;
await account.login();
assert.equal(last,'https://calculator.example/api/auth/google','Home login must work without the calculator or Settings');
document.defaultView.ToramApplication = application;
delete document.defaultView.ToramApp;
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
console.log('Account client: PASS (cookies/desktop auth, legacy saves, equipment validation + catalog snapshot, inventory CRUD, isolated slot apply, weapon compatibility, expected revision)');
