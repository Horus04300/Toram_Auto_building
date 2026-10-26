import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { CATALOG_KINDS,CATALOG_SUBCATEGORIES,catalogState,catalogPage,itemCatalogContent } from '../../../web/src/application/catalog-browser.mjs';
import { createItemCatalog } from '../../../web/src/application/item-catalog.mjs';

const defaults = catalogState(new URLSearchParams()); assert.equal(defaults.section,'items'); assert.equal(defaults.kind,'all'); assert.equal(defaults.selected,null);
for (const query of ['section=quests','kind=invalid','locale=invalid','page=-1','selected=NaN','selected=-1','difficulty=9','variant=../x','level=99999','kind=weapons&subcategory=999','kind=crystas&subcategory=강화','kind=armor&subcategory=17','section=bosses&kind=weapons&subcategory=17','section=bosses&bossKind=wrong','bossKind=entry-boss']) assert.throws(() => catalogState(new URLSearchParams(query)),/확인/);
assert.equal(catalogState(new URLSearchParams('section=bosses&bossKind=event-boss')).bossKind,'event-boss');
assert.equal(catalogState(new URLSearchParams('kind=weapons&subcategory=17')).subcategory,'17');
assert.equal(catalogState(new URLSearchParams('kind=crystas&subcategory=노말')).subcategory,'노말');
assert.equal(catalogState(new URLSearchParams('section=bosses&selected=0')).selected,0);
const entries = [{id:1,name:'같은 이름'},{id:2,name:'같은 이름'},{id:3,name:null},{id:4,name:'Staff'}];
assert.deepEqual(catalogPage(entries,{q:'같은',page:1}).items.map(item => item.id),[1,2]);
assert.equal(catalogPage(entries,{q:'3',page:1}).items[0].name,null);
assert.equal(catalogPage(entries,{q:'STAFF',page:1}).items[0].id,4);
assert.equal(catalogPage(entries,{page:999},2).page,2);
assert.equal(catalogPage(entries,{q:'없는 이름',page:99}).page,1);
const emojiText = '🌧️'.repeat(800);
assert.equal(itemCatalogContent({},{description:emojiText}).description,emojiText);
assert.deepEqual(itemCatalogContent({},null),{summary:'',description:'',duration:'',options:[]});

const base = new URL('../../../web/public/game-data/items/',import.meta.url), manifest = JSON.parse(await readFile(new URL('manifest.json',base)));
const api = createItemCatalog(new URL('manifest.json',base),async url => ({ok:true,json:async () => JSON.parse(await readFile(url))}));
let count = 0;
for (const kind of Object.keys(CATALOG_KINDS).filter(kind => kind !== 'all')) {
  const [items,details] = await Promise.all([readFile(new URL(manifest.kinds[kind],base)),readFile(new URL(manifest.locales.kr[kind].details,base))]).then(values => values.map(value => JSON.parse(value)));
  for (const [id,item] of Object.entries(items)) {
    const content = itemCatalogContent(item,details[id]);
    for (const key of ['summary','description','duration']) assert.equal(typeof content[key],'string');
    assert.deepEqual(content.options,details[id].displayOptions);
    for (const option of content.options) {assert.equal(typeof option.text,'string'); assert.equal(typeof option.conditional,'boolean'); assert.ok(option.text.trim());}
    count++;
  }
  if (kind === 'weapons') {
    assert.ok(itemCatalogContent(items[10009],details[10009]).options.some(option => option.text === '땅속성'));
    const historia = itemCatalogContent(items[10182],details[10182]);
    assert.equal(historia.summary,'[한손검] Base ATK : 730 (80%)'); assert.equal(historia.description,'');
    assert.deepEqual(historia.options.map(option => option.text),['빛속성','근거리 위력+12%','크리티컬률+70','공격속도+1400','물리내성+35%','마법내성+35%','중갑옷 장비 시,','비율 배리어 7%','어그로+70%']);
    assert.deepEqual(historia.options.map(option => option.conditional),[false,false,false,false,false,false,true,true,true]);
  }
  if (kind === 'armor') assert.equal(itemCatalogContent(items[20002],details[20002]).summary,'[몸장비] Base DEF : 11');
  if (kind === 'weapons' || kind === 'crystas') {
    const grouped = [];
    for (const id of Object.keys(CATALOG_SUBCATEGORIES[kind])) {
      const filter = kind === 'weapons' ? {typeId:Number(id)} : {category:id};
      const actual = await api.listItems(kind,'kr',filter);
      const expected = Object.entries(items).filter(([,item]) => kind === 'weapons' ? item.typeId === Number(id) : item.category === id).map(([id]) => Number(id));
      assert.deepEqual(actual.map(item => item.id),expected); grouped.push(...expected);
      if (kind === 'crystas') {
        assert.ok(expected.some(id => items[id].typeId < 60),'Each family includes base crystas');
        assert.ok(expected.some(id => items[id].typeId >= 61),'Each family includes enhanced crystas');
      }
    }
    assert.equal(new Set(grouped).size,grouped.length);
    assert.equal(grouped.length,Object.values(items).filter(item => kind === 'weapons' || item.category).length);
    assert.equal((await api.listItems(kind)).length,Object.keys(items).length,'All view preserves the entire published list');
  }
  if (kind === 'consumables') {
    const result = itemCatalogContent(items[2000],details[2000]);
    assert.equal(result.duration,'효과 시간 : 1800초'); assert.equal(result.summary,'');
    assert.ok(result.description.includes('\n'));
  }
}
assert.equal(count,manifest.counts.items);
console.log(`Catalog browser: PASS (URL/subcategory validation, 13 weapon types, 5 crysta families including enhancements, all views, name/ID search, bounded pages, Unicode text, ${count} published item details, unresolved effects preserved)`);
