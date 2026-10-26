import assert from 'node:assert/strict';
import { readFile, writeFile, mkdir, mkdtemp, unlink } from 'node:fs/promises';
import { resolve, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';
import { createHash } from 'node:crypto';
import childProcess from 'node:child_process';
import { EventEmitter } from 'node:events';
import { syncBuiltinESMExports } from 'node:module';
import { mock } from 'node:test';
import { createItemCatalog, resolveItemOptions, matchesItemCondition } from '../../../web/src/application/item-catalog.mjs';
import { convertCatalog, consumableCategoryFor, projectCondition, exportProjectItems, readProjectManifest, publishProjectItems } from '../../extraction/convert-toram-project-items.mjs';
import { syncDevelopmentItems } from '../../extraction/sync-toram-dev-items.mjs';
import { syncDevelopmentBosses } from '../../extraction/sync-toram-dev-bosses.mjs';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '../../..');
const sha = bytes => createHash('sha256').update(bytes).digest('hex');
const mappings = [{ capId:12, enumName:'bMaxHpTo10', statId:'MAXHP' }, { capId:124, enumName:'bMoveAttackResist', statId:'CHARGE_RED' }, { capId:43, enumName:'bCritical', statId:'CRIT' }];
function cap(slot, id, value, name, multiplier = 1, condition = null) {
  return { slot, cap_id:id, value, enumName:name, conditionMarkerSlot:condition,
    display:{ multiplierFloat32:multiplier, scaledValueFloat32:Math.fround(Math.fround(value) * multiplier), plainTextCandidates:{ kr:'문구', us:'text' } } };
}
function item(id, caps) {
  return { gameItemId:id, master:{ type_id:34, function:0, stability:0, range_raw:0, slot_max_raw:0, potential:0, flag_raw:0, model:0 },
    names:{ kr:'같은 이름', us:'same name' }, descriptions:{ kr:'설명', us:'description' },
    references:{ defaultSelectedEquipSlotValue:0, nativeChecks:{ CheckCristaItem:true, CheckEquipItem:false } },
    propertyRecord:{ caps, conditionGroups:[] } };
}
const catalog = rows => ({ nativeRulesApplied:true, cacheVersion:'77596232', availableItemLocales:['kr','us'], items:rows });
const first = item(9911, [cap(1,12,100,'bMaxHpTo10',10), cap(2,124,10,'bMoveAttackResist')]);
const useRules = JSON.parse(await readFile(resolve(root, 'data/sources/toram-items/item-use-rules.json')));
const categories = JSON.parse(await readFile(resolve(root,'data/sources/toram-items/consumable-categories.json')));
const categorySource = {...item(2000,[cap(1,211,1800,'runn_maxhp')]),descriptions:{kr:'「HP 증가」카테고리와 동시사용 불가',jp:'「ＨＰ増加」ｶﾃｺﾞﾘと併用できません'}};
assert.equal(consumableCategoryFor(categorySource,categories).id,'hp-boost');
assert.equal(consumableCategoryFor({...categorySource,descriptions:{}},categories).basis,'duration-marker');
assert.equal(consumableCategoryFor({...categorySource,descriptions:{kr:'[새 카테고리] 카테고리'}},categories),null);
assert.throws(()=>consumableCategoryFor({...categorySource,descriptions:{kr:'「MP 증가」카테고리',jp:categorySource.descriptions.jp}},categories),/Conflicting consumable category/u);
const unusual = {...categorySource,propertyRecord:{caps:[cap(1,209,1800,'runn_hp_heal')]}};
assert.equal(consumableCategoryFor(unusual,categories).id,'hp-boost');
assert.equal(consumableCategoryFor(unusual,categories).durationCapId,209,'A description category never rewrites the native stacking group');
const buff = item(2000, [cap(1,211,1800,'runn_maxhp'), cap(2,12,50,'bMaxHpTo10',10)]);
buff.master.type_id = 2;
buff.references.nativeChecks = {CheckUseItem:true,CheckEquipItem:false,CheckCristaItem:false};
const convertedBuff = convertCatalog(catalog([buff]), mappings, useRules).kinds.consumables[2000];
assert.equal(convertedBuff.effectScope, 'consumable-buff');
assert.equal(convertedBuff.buff.groupId, 211); assert.equal(convertedBuff.buff.durationSeconds, 1800);
assert.deepEqual(resolveItemOptions(convertedBuff), [{key:'MAXHP',value:500}]);
const zeroBuff = structuredClone(buff); zeroBuff.propertyRecord.caps[1] = cap(2,12,0,'bMaxHpTo10',10);
const zeroConverted = convertCatalog(catalog([zeroBuff]), mappings, useRules).kinds.consumables[2000];
assert.equal(zeroConverted.fullyMapped, false); assert.equal(zeroConverted.unresolved[0].reason, 'dynamic-consumable-operand');
const penaltyBuff = structuredClone(buff); penaltyBuff.propertyRecord.caps[1] = cap(2,12,-50,'bMaxHpTo10',10);
assert.equal(convertCatalog(catalog([penaltyBuff]), mappings, useRules).kinds.consumables[2000].stats.MAXHP, -500);
const reversedBuff = structuredClone(buff); reversedBuff.propertyRecord.caps.reverse();
assert.equal(convertCatalog(catalog([reversedBuff]), mappings, useRules).kinds.consumables[2000].effectScope, 'catalog-only');
const nonUseBuff = structuredClone(buff); nonUseBuff.references.nativeChecks.CheckUseItem = false;
assert.equal(convertCatalog(catalog([nonUseBuff]), mappings, useRules).kinds.consumables[2000].effectScope, 'catalog-only');
const mixedBuff = structuredClone(buff); mixedBuff.propertyRecord.caps.push(cap(3,230,3,'repeatwait'));
assert.equal(convertCatalog(catalog([mixedBuff]), mappings, useRules).kinds.consumables[2000].fullyMapped, false);
const wrongBuffEnum = structuredClone(buff); wrongBuffEnum.propertyRecord.caps[0].enumName = 'wrong';
assert.throws(() => convertCatalog(catalog([wrongBuffEnum]), mappings, useRules), /enum changed/u);
const converted = convertCatalog(catalog([first]), mappings);
assert.deepEqual(converted.kinds.crystas[9911].stats, { MAXHP:1000, CHARGE_RED:10 });
assert.deepEqual(resolveItemOptions(converted.kinds.crystas[9911]), [{ key:'MAXHP', value:1000 }, { key:'CHARGE_RED', value:10 }]);

const reviewedMappings = JSON.parse(await readFile(resolve(root,'data/sources/toram-items/project-stat-mapping.json'))).statMapping;
for (const id of [48,127,129,130,137,140,155,164,165,168,174]) assert.equal(reviewedMappings.find(row => row.capId === id).scope,undefined,'Native cap mappings apply across item kinds');
for (const id of [125,131,143,163,176,177]) {
  const mapping = reviewedMappings.find(row => row.capId === id);
  for (const raw of id === 163 ? [1] : [-7,7]) {
    const result = convertCatalog(catalog([item(9990,[cap(1,id,raw,mapping.enumName)])]),reviewedMappings).kinds.crystas[9990];
    assert.equal(result.stats[mapping.statId],raw,'The six scalar native caps keep their signed multiplier-one values');
  }
}
for (const id of [114,189,190,191,192,193]) assert.equal(reviewedMappings.some(row => row.capId === id),false,'Events, avatar skills and gem commands are not scalar equipment stats');
for (let id = 166; id <= 175; id++) {
  const mapping = reviewedMappings.find(row => row.capId === id);
  for (const raw of [125,-125]) {
    const source = item(9990,[cap(1,id,raw,mapping.enumName,Math.fround(.1))]);
    const result = convertCatalog(catalog([source]),reviewedMappings).kinds.crystas[9990];
    assert.equal(result.stats[mapping.statId],Math.fround(Math.fround(raw) * Math.fround(.1)),'Every proportional cap preserves signed float32 scaling');
    assert.equal(result.fullyMapped,true);
  }
}
const realSource = JSON.parse(await readFile(resolve(root,'data/sources/toram-items/items.77596232.connected.json')));
const realRows = realSource.items.filter(row => [10024,108286,13126,16090,21751,12037,11074,14186,20089,21602].includes(row.gameItemId));
assert.equal(realRows.length,10);
const realConverted = convertCatalog(catalog(realRows),reviewedMappings,useRules);
assert.equal(realConverted.kinds.weapons[10024].stats.ATK_UP_INT,150);
assert.equal(realConverted.kinds.weapons[10024].stats.ATK_UP_STR,-200,'Actual equipment ATK-down must retain its sign');
assert.ok(realConverted.kinds.weapons[10024].unresolved.every(row => ![166,167].includes(row.capId)));
assert.ok(Object.hasOwn(realConverted.kinds.weapons[13126].stats,'ITEM_DELAY'),'Existing preserved keys also map on weapons');
const proportionalBuff = realConverted.kinds.consumables[108286];
assert.equal(proportionalBuff.fullyMapped,true);
assert.deepEqual(proportionalBuff.buff,{groupId:211,durationSeconds:1200});
assert.deepEqual(resolveItemOptions(proportionalBuff),[{key:'MAXHP',value:4000},{key:'ATK_UP_VIT',value:20},{key:'MATK_UP_VIT',value:20}]);
for (const [id,kind,key,value] of [[16090,'weapons','METEOR_RES',-10],[21751,'additional','SUCTION_RES',30],[12037,'weapons','HELP_INVINCIBILITY',3],
  [11074,'weapons','STOP_FLINCH',1],[14186,'weapons','PET_EXP',5],[20089,'armor','GEM_DUST_DROP',50]]) {
  assert.equal(realConverted.kinds[kind][id].stats[key],value);
}
const conditionalHelper = realConverted.kinds.additional[21602];
assert.ok(resolveItemOptions(conditionalHelper,{mainType:'지팡이',subType:'없음'}).some(row => row.key === 'HELP_INVINCIBILITY' && row.value === 2));
assert.ok(!resolveItemOptions(conditionalHelper,{mainType:'한손검',subType:'없음'}).some(row => row.key === 'HELP_INVINCIBILITY'),'Scalar preservation does not flatten native equipment conditions');

const conditional = item(2, [cap(1,12,100,'bMaxHpTo10',10), { ...cap(2,97,1,'limit'), role:'equipment-condition-marker' }, cap(3,43,5,'bCritical',1,2)]);
conditional.propertyRecord.conditionGroups = [{ markerSlot:2, capId:97, instructionCount:1, targetSlots:[3], uiScopeMatchesBonusScope:true }];
const conditionalItem = convertCatalog(catalog([conditional]), mappings).kinds.crystas[2];
assert.deepEqual(convertCatalog(catalog([conditional]), mappings).details.kr.crystas[2].displayOptions,
  [{text:'문구',conditional:false},{text:'문구',conditional:true},{text:'문구',conditional:true}]);
const blankText = structuredClone(first); blankText.propertyRecord.caps[0].display.plainTextCandidates.kr = '  ';
assert.equal(convertCatalog(catalog([blankText]),mappings).details.kr.crystas[9911].displayOptions.length,1);
assert.equal(resolveItemOptions(conditionalItem, { mainType:'한손검', subType:'한손검(듀얼소드)' }).find(row => row.key === 'CRIT').value, 5, 'Either slot must apply once.');
assert.equal(resolveItemOptions(conditionalItem, { mainType:'활', subType:'발도검' }).length, 1);
assert.equal(matchesItemCondition({ mainType:'한손검', subType:'없음' }, projectCondition(108)), false);
assert.equal(matchesItemCondition({ mainType:'한손검', subType:'한손검(듀얼소드)' }, projectCondition(108)), true);
assert.equal(matchesItemCondition({ armorType:'경량옷' }, projectCondition(119)), true);
assert.equal(matchesItemCondition({ armorType:'경량옷' }, projectCondition(120)), false);
assert.throws(() => resolveItemOptions(conditionalItem, {}), /needs mainType/u);
assert.throws(() => matchesItemCondition({}, { kind:'unknown' }), /Unsupported/u);

const unknown = structuredClone(conditional);
unknown.propertyRecord.caps[2].cap_id = 999;
const partial = convertCatalog(catalog([unknown]), mappings).kinds.crystas[2];
assert.equal(partial.fullyMapped, false);
assert.equal(resolveItemOptions(partial, { mainType:'활', subType:'화살' }).length, 1);
assert.throws(() => resolveItemOptions(partial, { mainType:'한손검', subType:'없음' }), /unresolved/u);
assert.throws(() => convertCatalog({ ...catalog([first]), nativeRulesApplied:false }, mappings));
assert.throws(() => convertCatalog(catalog([first, first]), mappings), /duplicate/u);
const predecessor = item(9000, []), upgrade = item(9001, []);
upgrade.master.type_id = 64; upgrade.master.model = 9000;
assert.equal(convertCatalog(catalog([predecessor,upgrade]), mappings).kinds.crystas[9001].previousId,9000);
assert.throws(() => convertCatalog(catalog([upgrade]), mappings), /Missing\/cross-category/u);
const cycle = structuredClone(predecessor); cycle.master.type_id = 64; cycle.master.model = 9001;
assert.throws(() => convertCatalog(catalog([cycle,upgrade]), mappings), /cyclic/u);
const wrongCategory = structuredClone(predecessor); wrongCategory.master.type_id = 33;
assert.throws(() => convertCatalog(catalog([wrongCategory,upgrade]), mappings), /cross-category/u);
const duplicate = structuredClone(first); duplicate.propertyRecord.caps.push(cap(3,12,1,'bMaxHpTo10',10));
assert.throws(() => convertCatalog(catalog([duplicate]), mappings), /Duplicate MAXHP/u);
const badNumber = structuredClone(first); badNumber.propertyRecord.caps[0].display.scaledValueFloat32 = 100;
assert.throws(() => convertCatalog(catalog([badNumber]), mappings));
const badGroup = structuredClone(conditional); badGroup.propertyRecord.conditionGroups[0].capId = 108;
assert.throws(() => convertCatalog(catalog([badGroup]), mappings));
assert.throws(() => resolveItemOptions({ ...conditionalItem, effectScope:'catalog-only' }), /catalog-only/u);

const parent = resolve(root, 'build/tmp/item-catalog-tests');
await mkdir(parent, { recursive:true });
const directory = await mkdtemp(resolve(parent, 'run-'));
assert.ok(directory.startsWith(parent + '\\') || directory.startsWith(parent + '/'));
const input = resolve(directory, 'items.connected.json'), project = resolve(directory, 'project');
await writeFile(input, JSON.stringify(catalog([first, item(9912, [])])));
const manifest = await exportProjectItems(input, project);
assert.equal(manifest.counts.items, 2);
assert.equal(manifest.optimizerEligible, true);
await readProjectManifest(project);
const manifestBytes = await readFile(resolve(project, 'manifest.json'));
await writeFile(resolve(project, 'manifest.json'), JSON.stringify({...manifest,source:{...manifest.source,itemUseRulesSha256:'0'.repeat(64)}}));
await assert.rejects(readProjectManifest(project), /Item use rules changed/u);
await writeFile(resolve(project, 'manifest.json'), manifestBytes);
for (const [key,message] of [['mappingSha256','Project stat mapping changed'],['crystaAliasesSha256','Crysta aliases changed'],['consumableCategoriesSha256','Consumable categories changed']]) {
  await writeFile(resolve(project,'manifest.json'),JSON.stringify({...manifest,source:{...manifest.source,[key]:'0'.repeat(64)}}));
  await assert.rejects(readProjectManifest(project),new RegExp(message));
}
await writeFile(resolve(project,'manifest.json'),manifestBytes);
const partialInput = resolve(directory,'partial.json');
await writeFile(partialInput,JSON.stringify(catalog([unknown])));
await assert.rejects(exportProjectItems(partialInput,resolve(directory,'partial-project')),/Crysta options need review/u);
assert.deepEqual(await readFile(resolve(project,'manifest.json')),manifestBytes,'An unmapped real crysta cannot replace the published catalog');
const base = new URL('https://catalog.test/items/manifest.json');
const requests = [], failures = new Set();
async function fetcher(url) {
  const path = url.href.slice(new URL('.', base).href.length);
  requests.push(path);
  if (failures.delete(path)) return { ok:false, status:503 };
  return { ok:true, status:200, json:async () => JSON.parse(await readFile(resolve(project, path))) };
}
const api = createItemCatalog(base, fetcher);
const [a,b] = await Promise.all([api.getItem(9911), api.getItem(9912)]);
assert.equal(a.name, b.name); assert.notEqual(a.id, b.id);
assert.equal(new Set(requests).size, 4);
assert.equal(requests.length, 4, 'Concurrent requests must share manifest/index/shard/name loads.');
assert.equal(requests.some(path => path.includes('.details.') || path.includes('/us/')), false);
await api.getItem(9911);
assert.equal(requests.length, 4);
assert.equal((await api.getDetails(9911)).description, '설명');
assert.equal(requests.length, 5);
assert.ok(Object.isFrozen(a.stats));
await assert.rejects(api.getItem(999999), /Unknown game item/u);
await assert.rejects(api.getItem(9911, 'missing'), /Unknown item locale/u);
const nameFile = manifest.locales.kr.crystas.names;
failures.add(nameFile);
const retry = createItemCatalog(base, fetcher);
await assert.rejects(retry.listItems('crystas'), /503/u);
assert.equal((await retry.listItems('crystas')).length, 2);
assert.ok((await api.listItems('crystas','kr',{typeId:a.typeId,category:a.category})).some(item => item.id === a.id));
assert.equal((await api.listItems('crystas','kr',{typeId:-1})).length,0);
assert.equal((await api.listItems('crystas','kr',{category:'missing'})).length,0);

const snapshot = resolve(directory, 'snapshot');
await mkdir(snapshot);
const projectCopy = resolve(snapshot, 'project');
await exportProjectItems(input, projectCopy);
const outputHashes = {};
for (const path of ['manifest.json', ...Object.keys(manifest.files)]) outputHashes['project/' + path] = sha(await readFile(resolve(projectCopy,path)));
await writeFile(resolve(snapshot,'report.json'), JSON.stringify({ status:'needs-review', outputHashes }));
await assert.rejects(publishProjectItems(snapshot, resolve(directory,'published')), /needs review/u);
await writeFile(resolve(snapshot,'report.json'), JSON.stringify({ status:'ready', outputHashes }));
const published = resolve(directory,'published');
await publishProjectItems(snapshot, published);
const publishedBefore = await readFile(resolve(published,'manifest.json'));
await publishProjectItems(snapshot, published);
assert.deepEqual(await readFile(resolve(published,'manifest.json')), publishedBefore, 'An unchanged publication must remain identical.');
const corrupted = Object.keys(manifest.files)[0];
await writeFile(resolve(published,corrupted), '{}');
await assert.rejects(publishProjectItems(snapshot, published), /Item asset size mismatch|Different artifact/u);
assert.deepEqual(await readFile(resolve(published,'manifest.json')), publishedBefore);
const syncLock = resolve(published,'.development-sync.lock');
await writeFile(syncLock,'other run');
await assert.rejects(syncDevelopmentItems({ output:published }), { code:'EEXIST' });
assert.equal(await readFile(syncLock,'utf8'),'other run');
await unlink(syncLock);
for (const sync of [syncDevelopmentItems, syncDevelopmentBosses]) {
  for (const [status, code, expected, pipelineArgs, application] of [
    ['update-available',0,0,['--check']], ['unchanged',0,0,['--check']],
    ['needs-review',2,2,['--check']], ['failed',0,1,['--check']], ['failed',0,1,[]],
    ['invalid JSON',0,1,[]], ['failed',1,1,[]], ['unchanged',0,0,['--check'],'releaseB']
  ]) {
    const spawn = mock.method(childProcess, 'spawn', (python, args) => {
      assert.deepEqual(args.includes('--check'), pipelineArgs.includes('--check'));
      assert.equal(args[args.indexOf('--application') + 1], application || 'releaseC');
      const worker = new EventEmitter();
      worker.stdout = new EventEmitter(); worker.stderr = new EventEmitter();
      queueMicrotask(() => {
        worker.stdout.emit('data', status === 'invalid JSON' ? status : JSON.stringify({status}));
        worker.emit('close', code);
      });
      return worker;
    });
    syncBuiltinESMExports();
    try {
      const report = await sync({ output:published, pipelineArgs, ...(application ? {application} : {}) });
      assert.equal(report.exitCode, expected, `${sync.name}: ${status}`);
      assert.equal(report.application, application || 'releaseC');
      assert.equal(report.developmentApplied, false);
      assert.deepEqual(await readFile(resolve(published,'manifest.json')), publishedBefore);
      await assert.rejects(readFile(syncLock), { code:'ENOENT' });
    } finally { spawn.mock.restore(); syncBuiltinESMExports(); }
  }
}
assert.equal(await api.refresh(), '77596232');
console.log('Item catalog: PASS (numeric units, conditional OR/both/armor, unresolved effects, duplicate IDs/stats, sharded localization, shared/retry requests, hash gates, publication safety and item/boss check/failure propagation)');
