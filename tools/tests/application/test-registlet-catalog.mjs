import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {DatabaseSync} from 'node:sqlite';
import {randomUUID} from 'node:crypto';
import {publishRegistlets} from '../../extraction/publish-toram-registlets.mjs';
import {createRegistletCatalog,createRegistletSelection,registletDescription,registletEffect,registletEnhancement,registletLocations,cleanRegistletText,validateRegistletSelection} from '../../../web/src/application/registlet-catalog.mjs';
import {catalogState} from '../../../web/src/application/catalog-browser.mjs';
import {validateInventoryObject,sections,captureObject,applyObject} from '../../../web/src/application/inventory-objects.mjs';
import {describeInventoryObject} from '../../../web/src/application/inventory-summary.mjs';
import {inventoryMajor} from '../../../web/src/pages/inventory/inventory-navigation.mjs';
import {createInventoryStore} from '../../../server/inventory-store.mjs';
import {createPostStore} from '../../../server/post-store.mjs';
import {inventoryRules} from '../../../server/inventory-rules.mjs';

await publishRegistlets(true);
const raw = JSON.parse(await readFile(new URL('../../../web/public/game-data/registlets/catalog.json',import.meta.url)));
const source = JSON.parse(await readFile(new URL('../../../data/sources/toram-registlet/catalog.json',import.meta.url)));
let requests = 0;
const catalog = createRegistletCatalog(new URL('https://registlet.test/catalog.json'),async () => {requests++; return {ok:true,json:async () => structuredClone(raw)};});
assert.equal(requests,0,'Catalog must stay lazy on home/inventory startup');
const [items,slots] = await Promise.all([catalog.list(),catalog.slots()]);
assert.equal(requests,1); assert.equal(items.length,166);
assert.equal(items.filter(item => item.locations.length).length,163);
assert.deepEqual(slots,{slotLimit:10,costs:[100,400,2000,7000,30000,200000,500000,2000000,7000000]});
assert.deepEqual(Object.fromEntries(['stats','status','support','skills'].map(kind => [kind,items.filter(item => item.category === kind).length])),{stats:10,status:16,support:32,skills:108});
assert.equal(catalogState(new URLSearchParams('section=registlets&registletKind=slots')).registletKind,'slots');
for (const query of ['registletKind=skills','section=registlets&registletKind=wrong']) assert.throws(() => catalogState(new URLSearchParams(query)));
for (const item of items) {
  const cost = registletEnhancement(item,1);
  assert.equal(cost.same.powder,Math.floor(item.enhancePowder / 10),'All current master powder values agree with native float32 truncation');
  assert.equal(cost.different.powder,item.enhancePowder);
  assert.equal(registletEnhancement(item,item.levelCap).max,true);
  if (item.levelCap > 1) assert.deepEqual(registletEnhancement(item,item.levelCap - 1,item.levelCap).same,{powder:cost.same.powder,toLevel:item.levelCap});
  for (const level of [0,1.5,item.levelCap + 1]) assert.throws(() => registletEnhancement(item,1,level));
}
assert.equal(registletEnhancement(await catalog.get(11),1).same.powder,7);
assert.equal(registletEnhancement(await catalog.get(78),1).same.powder,333);
assert.match(registletEffect(createRegistletSelection(await catalog.get(207),4),6).description,/5%/);
const powerWave = await catalog.get(207);
assert.throws(() => registletEffect(createRegistletSelection(powerWave),11));
for (const [level,halberd,staff] of [[1,'8.25','11'],[3,'9.75','13'],[5,'11.25','15']]) {
  const effect = registletEffect(createRegistletSelection(await catalog.get(1053),level),10);
  assert.equal(effect.rows[0].result,level + '스택'); assert.equal(effect.rows[1].result,'0%');
  assert.equal(effect.rows[2].result,halberd); assert.equal(effect.rows[3].result,staff);
}
assert.equal(registletEffect(createRegistletSelection(await catalog.get(1053),4),1).rows[2].result,'7.78','Native truncation occurs before multiplying by stack count');
assert.equal(inventoryMajor('registlet'),'registlets');
assert.equal(catalogState(new URLSearchParams('section=registlets&selected=12&level=30')).selected,12);
assert.throws(() => catalogState(new URLSearchParams('section=registlets&selected=0')));
const format = value => Number(value.toFixed(2)).toLocaleString('ko-KR',{maximumFractionDigits:2});
for (const row of source.registlets) {
  const item = await catalog.get(row.registletId);
  for (const locale of ['kr','us','jp','cnt','idn','th']) {
    for (const [level,expected] of [[1,row.displayRule.atLevel1],[row.levelCap,row.displayRule.atLevelCap]]) {
      const selection = createRegistletSelection(item,level,locale);
      validateInventoryObject('registlet',{selection},inventoryRules);
      const text = registletDescription(selection);
      if (expected !== null) {
        const values = Array.isArray(expected) ? expected : [expected];
        let template = cleanRegistletText(row.descriptionTemplates[locale]);
        values.forEach((value,index) => {template = template.replaceAll(`{${index}}`,format(value));});
        assert.equal(text,template,`${row.registletId}/${locale}/Lv${level}: extracted native substitution`);
      }
      const effect = registletEffect(selection,row.registletId === 207 ? 10 : null);
      if (row.baseValue !== -1) assert.ok(effect.rows.length && effect.rows.every(row => row.formula && row.substitution && row.result));
      assert.doesNotMatch(text,/\{\d+\}|\[[a-f0-9]{6}\]/iu);
    }
  }
}
assert.match(registletDescription(createRegistletSelection(await catalog.get(12),30)),/30%/);
assert.match(registletDescription(createRegistletSelection(await catalog.get(207))),/⌊.*파워 웨이브.*÷ 2⌋/);
assert.match(registletLocations(await catalog.get(1036)),/Lv220.*S 상자/);
for (const id of [1040,1046,1054]) assert.match(registletLocations(await catalog.get(id)),/없습니다/);
const selection = createRegistletSelection(await catalog.get(12),30);
for (const level of [0,31,1.5,NaN,Infinity,'1']) assert.throws(() => validateRegistletSelection({...selection,level}));
for (const changes of [{registletId:999999},{levelCap:999},{baseValue:Infinity},{cacheVersion:12345678},{extra:true}]) assert.throws(() => validateRegistletSelection({...selection,...changes}));
await assert.rejects(catalog.get(999999));
items[0].names.kr = 'changed'; slots.costs[0] = 1;
assert.notEqual((await catalog.list())[0].names.kr,'changed'); assert.equal((await catalog.slots()).costs[0],100);
let attempts = 0;
const retry = createRegistletCatalog(new URL('https://registlet.test/catalog.json'),async () => ({ok:++attempts > 1,json:async () => raw}));
await assert.rejects(retry.list()); assert.equal((await retry.list()).length,166);
for (const mutate of [value => {value.items[1].id = value.items[0].id;},value => {value.slotExpansion.costs = [];},value => {value.items[0].locations = null;}]) {
  const bad = structuredClone(raw); mutate(bad);
  await assert.rejects(createRegistletCatalog(new URL('https://registlet.test/catalog.json'),async () => ({ok:true,json:async () => bad})).list());
}

const db = new DatabaseSync(':memory:');
try {
  db.exec("CREATE TABLE users (id TEXT PRIMARY KEY, nickname TEXT NOT NULL); INSERT INTO users VALUES ('alice','테스터'),('bob','복사자');");
  const store = createInventoryStore(db), posts = createPostStore(db,store);
  const saved = store.create('alice',{type:'registlet',schemaVersion:1,name:selection.name,data:{selection}});
  assert.deepEqual(saved.provenance,[{kind:'registlet-catalog',registletId:12,cacheVersion:raw.cacheVersion,sourceSha256:raw.sourceSha256}]);
  assert.equal(store.list('alice',new URLSearchParams({type:'registlet',q:'맹독'})).total,1);
  assert.equal(store.list('bob',new URLSearchParams({type:'registlet'})).total,0);
  assert.throws(() => store.get('bob',saved.id),error => error.status === 404);
  const updated = store.update('alice',saved.id,{type:saved.type,schemaVersion:1,name:'내 맹독 회복',revision:1,data:{selection:{...selection,level:15}}});
  assert.equal(updated.revision,2); assert.equal(updated.data.selection.level,15); assert.deepEqual(updated.provenance,saved.provenance);
  assert.throws(() => store.update('alice',saved.id,{type:saved.type,schemaVersion:1,name:saved.name,revision:1,data:saved.data}),error => error.status === 409);
  assert.match(describeInventoryObject(updated).join('\n'),/Lv15 \/ 30/);
  assert.throws(() => sections(updated),/개별 보관/);
  assert.throws(() => captureObject('registlet',{}),/도감/);
  assert.throws(() => applyObject(updated,{},inventoryRules),/개별 보관/);
  assert.throws(() => store.preview('alice',{left:{objectId:updated.id,revision:2},right:{objectId:updated.id,revision:2}}),error => error.status === 400);
  const post = posts.publish('alice',{title:updated.name,source:{objectId:updated.id,revision:2},release:{name:'첫 공개'}},randomUUID());
  assert.deepEqual(post.release.catalogVersions,[raw.cacheVersion]);
  const copied = posts.copy('bob',{postId:post.id,releaseNumber:1},randomUUID());
  assert.deepEqual(copied.data,updated.data);
  store.remove('alice',updated.id,{revision:2});
  assert.equal(store.get('bob',copied.id).data.selection.level,15,'Independent copies survive source deletion');
} finally {db.close();}
console.log('Registlet catalog/inventory: PASS (166 definitions, six locales, native display endpoints, 16 stages/163 links, slot costs, level guards, private CRUD/revisions, provenance, independent public snapshots)');
