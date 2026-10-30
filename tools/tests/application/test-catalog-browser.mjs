import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {CATALOG_KINDS,CATALOG_SUBCATEGORIES,catalogState,catalogPage,itemCatalogContent,bossCatalogContent,bossCatalogPhaseLabel} from '../../../web/src/application/catalog-browser.mjs';
import {createItemCatalog} from '../../../web/src/application/item-catalog.mjs';
import {createBossSelection} from '../../../web/src/application/boss-target.mjs';

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
  if (['weapons','armor','additional','special'].includes(kind)) for (const item of await api.listItems(kind)) assert.equal(item.typeId,items[item.id].typeId,'Equipment lists retain their game type for icons');
  if (kind === 'crystas') for (const item of await api.listItems(kind)) assert.equal(item.category,items[item.id].category,'Crysta lists retain the shared base/enhanced family for icons');
  if (kind === 'consumables') {
    const result = itemCatalogContent(items[2000],details[2000]);
    assert.equal(result.duration,'효과 시간 : 1800초'); assert.equal(result.summary,'');
    assert.ok(result.description.includes('\n'));
  }
}
assert.equal(count,manifest.counts.items);
const bossBase = new URL('../../../web/public/game-data/bosses/',import.meta.url), bossManifest = JSON.parse(await readFile(new URL('manifest.json',bossBase)));
const variants = (await Promise.all(Object.values(bossManifest.groups).map(path => readFile(new URL(path,bossBase)).then(JSON.parse)))).flat();
const selectBoss = key => {const row = variants.find(row => row.key === key); return createBossSelection({gameMonsterId:row.gameMonsterId,name:'보스',revision:bossManifest.revision},row);};
const contentFor = selection => bossCatalogContent(selection,variants.filter(row => row.gameMonsterId === selection.gameMonsterId));
const stat = (content,label) => content.groups.flatMap(([,rows]) => rows).find(([key]) => key === label)?.[1];
const colon = selectBoss('3300:10');
for (const [difficulty,hp,def,hit] of [[-1,'100','0','1'],[0,'1,000','7','11'],[1,'2,000','14','22'],[2,'5,000','28','44'],[3,'10,000','42','66']]) {
  const content = contentFor({...colon,difficulty});
  assert.equal(stat(content,'HP'),hp); assert.equal(stat(content,'DEF'),def); assert.equal(stat(content,'회피'),hit);
  assert.equal(stat(content,'속성'),'땅'); assert.equal(stat(content,'어보이드율'),'0%');
  assert.equal(content.notes,undefined); assert.equal(content.description,undefined);
  assert.match(content.summary,new RegExp(['Easy','Normal','Hard','Nightmare','Ultimate'][difficulty + 1]));
}
const soteria = selectBoss('100500:1'), phases = variants.filter(row => row.gameMonsterId === soteria.gameMonsterId);
assert.equal(stat(contentFor(soteria),'선택 개체'),'남자 소테리아 · 마법 방어형 · 페이즈 #1');
assert.equal(stat(contentFor(soteria),'다음 페이즈'),'#101');
assert.match(bossCatalogPhaseLabel(phases.find(row => row.key === '100500:102'),phases),/여자.*페이즈 #102/);
const independent = {...phases[0],key:'100500:999',masterId:999,modes:[]};
assert.match(bossCatalogPhaseLabel(independent,[...phases,independent]),/개체 #999/,'Sharing a field does not prove a phase relationship');
assert.match(bossCatalogPhaseLabel({...independent,modes:[{targetMonsterId:1}]},[{...phases[0],gameMonsterId:999},independent]),/개체 #999/,'A different boss in the same field is not merged');
const raid = contentFor({...selectBoss('90961:1'),level:200});
assert.match(raid.summary,/입장 Lv200/);
const unresolved = selectBoss(variants.find(row => row.entry.model === 'unresolved').key), raw = contentFor(unresolved);
assert.match(raw.summary,/난이도 미확인/); assert.equal(stat(raw,'DEF'),unresolved.variant.baseStats.def.toLocaleString('ko-KR'));
assert.equal(stat(raw,'크리티컬 저항'),(unresolved.variant.properties.find(property => property.typeRaw === 6)?.values[0] ?? 0).toLocaleString('ko-KR'));
const enumMetadata = JSON.parse(await readFile(new URL('../../../data/sources/toram-items/native-option-calculation/metadata-bindings.json',import.meta.url)));
const element = enumMetadata.types.find(type => type.name === 'ElementType');
for (const [name,label] of [['None','미지정'],['Fire','불'],['Water','물'],['Wind','바람'],['Earth','땅'],['Light','빛'],['Dark','어둠'],['Normal','무']]) {
  const elementRaw = element.fields.find(field => field.name === name).default.int32_value;
  assert.equal(stat(contentFor({...colon,variant:{...colon.variant,baseStats:{...colon.variant.baseStats,elementRaw}}}),'속성'),label);
}
for (const row of variants) {
  const content = contentFor(selectBoss(row.key));
  for (const label of ['HP','속성','회피','어보이드율','크리티컬 저항','DEF','MDEF','물리 내성','마법 내성','통상','물리','마법']) assert.ok(stat(content,label),`${row.key}: ${label}`);
  assert.doesNotMatch(JSON.stringify(content),/undefined|NaN/);
  assert.doesNotMatch(JSON.stringify(content),/원본|필요 명중|본체|플레이어/);
}
console.log(`Catalog browser: PASS (URL/subcategory validation, 13 weapon types, 5 crysta families including enhancements, all views, name/ID search, bounded pages, Unicode text, ${count} published item details, unresolved effects preserved)`);
console.log(`Boss catalog display: PASS (${variants.length} variants, complete stats, native elements, five difficulties, raid levels, explicit phase links, unknown rules preserved)`);
