import assert from 'node:assert/strict';
import { readFile, writeFile, mkdtemp, mkdir } from 'node:fs/promises';
import { resolve } from 'node:path';
import { spawnSync } from 'node:child_process';
import { createBossCatalog } from '../../../web/src/application/boss-catalog.mjs';
import { convertBosses, readBossManifest, publishLatestProjectBosses } from '../../extraction/convert-toram-project-bosses.mjs';
import { hash, encode } from '../../extraction/project-catalog-store.mjs';
import { itemPython } from '../../extraction/sync-toram-dev-items.mjs';

const root = resolve(import.meta.dirname, '../../..');
for (const script of ['extract-toram-monster-data.py','test-toram-field-bundle.py','test-toram-boss-pipeline.py']) {
  const result = spawnSync(await itemPython(), [resolve(root,'tools/extraction',script), ...(script.startsWith('extract-') ? ['--self-test'] : [])], { cwd:root, encoding:'utf8', windowsHide:true });
  assert.equal(result.status, 0, result.stdout + result.stderr);
}
const parent = resolve(root,'build/tmp/boss-catalog-tests'); await mkdir(parent,{ recursive:true });
const temp = await mkdtemp(resolve(parent,'run-')), project = resolve(temp,'snapshot/project');
const contractBytes = await readFile(resolve(root,'tools/extraction/toram-boss-pipeline-contract.json')), contract = JSON.parse(contractBytes);
function variant(fieldId, masterId, id, def, flagRaw = 4) {
  return { key:`${fieldId}:${masterId}`, gameMonsterId:id, masterId, fieldId, sourceSha256:'a'.repeat(64),
    classification:'unresolved', classificationEvidence:[], raw:{
    id:masterId, uuid:id, flagRaw, roomId:0, nameRaw:'same name', rawRecordHex:'00', level:195, maxHp:1000, def, mdef:390,
    necessaryHit:584, cutAttack:7, cutMagicAttack:7, guard:0, avoid:0, elementRaw:1,
    expDefNormal:20, expDefSkill:30, expDefMagic:40, parts:[], modes:[], properties:[{uid:0,typeRaw:6,values:[25,0,0,0,0]}]
  } };
}
const input = { schema:'toram.raw-monsters.v1', revision:'b'.repeat(64), contractSha256:hash(contractBytes),
  coverage:{scope:'all-manifest-field-script-groups'}, rejectedFields:[],
  monsters:[variant(23000,10,540,429),variant(23000,11,540,-5),variant(23001,10,540,800),variant(23000,12,888,123),variant(23000,13,974,0,8),variant(101100,1,1001,600),variant(100500,1,1195,175)],
  fields:[23000,23001,101100,100500].map(fieldId => ({fieldId,master:{sha256:'a'.repeat(64)},mapInfo:{popMobs:[],childGameObjects:[]}})),
  names:Object.fromEntries(contract.requiredLocales.map(locale => [locale,{540:locale === 'kr' ? '기드론' : 'Grimuckus',888:'same name',974:'same name'}])),
  fieldNames:Object.fromEntries(contract.requiredLocales.map(locale => [locale,{23000:'A',23001:'B'}])) };
input.monsters[0].classification = 'field-boss'; input.monsters[0].classificationEvidence = [{kind:'serialized-mmo-pop'}];
input.monsters[3].classification = 'entry-boss'; input.monsters[3].classificationEvidence = [{kind:'BossMenu-entry'}];
input.monsters[3].raw.parts = [{partId:1,value:13},{partId:2,value:999}];
input.monsters[5].classification = 'high-raid-boss'; input.monsters[5].classificationEvidence = [{kind:'HighRaidBossMaster',record:{baseLevel:290,minLevel:290}}];
input.monsters[6].classification = 'guild-raid-boss'; input.monsters[6].classificationEvidence = [{kind:'reviewed-guild-raid-route',actor:{identity:'male'}}];
const manifest = await convertBosses(input,project);
assert.deepEqual(manifest.counts,{monsterIds:4,variants:6});
const requests = [], url = new URL('https://example.test/calculator/web/public/game-data/bosses/manifest.json');
let fail = false;
const catalog = createBossCatalog(url, async target => {
  assert.ok(target.href.startsWith(new URL('.',url).href));
  const path = target.href.slice(new URL('.',url).href.length); requests.push(path);
  if (fail && path.startsWith('bosses/')) throw new Error('Temporary unavailable');
  return new Response(await readFile(resolve(project,path)),{status:200});
});
assert.equal(requests.length,0);
assert.equal((await catalog.search('기드론')).at(0).gameMonsterId,540);
assert.ok(requests.every(path => !path.startsWith('bosses/')),'Search must not load variant records.');
fail = true; await assert.rejects(catalog.get(540),/Temporary/); fail = false;
const boss = await catalog.get(540);
assert.equal(boss.variants.length,3); assert.equal(boss.variants[1].baseStats.def,-5);
assert.equal(boss.variants[0].classification,'field-boss');
assert.equal(boss.variants[0].entry.model,'single'); assert.equal(boss.variants[0].entry.difficulty,null);
assert.equal(boss.variants[0].baseStats.physicalResistance,undefined);
assert.deepEqual(boss.variants.map(row => row.key),['23000:10','23000:11','23001:10']);
const count = requests.length; await catalog.get(540); assert.equal(requests.length,count);
assert.equal((await catalog.get(540,'us')).name,'Grimuckus');
assert.equal((await catalog.get(888)).variants[0].entry.model,'difficulty-select');
const linkedParts = (await catalog.get(888)).variants[0].partStats;
assert.equal(linkedParts[0].masterId,13); assert.equal(linkedParts[0].stats.mdef,390);
assert.deepEqual(linkedParts[0].properties,input.monsters[4].raw.properties,'Parts without Boss4 remain linked for body stat contributions.');
assert.equal(linkedParts[1].stats,null,'An unresolved part reference is explicit, not a fabricated zero.');
assert.deepEqual((await catalog.get(1001)).variants[0].entry,{model:'level-select',levelParameters:{baseLevel:290,minLevel:290}});
assert.deepEqual((await catalog.get(1195)).variants[0].entry,{model:'level-select',levelParameters:{baseLevel:40,minLevel:40,maxLevel:1020,step:4},actor:'male'});
for (const [classification,id] of [['entry-boss',888],['field-boss',540],['high-raid-boss',1001],['guild-raid-boss',1195]]) {
  assert.deepEqual((await catalog.search('','kr',{classification})).map(item => item.gameMonsterId),[id]);
}
assert.deepEqual(await catalog.search('same name','kr',{classification:'field-boss'}),[]);
assert.deepEqual(await catalog.search('','kr',{classification:'event-boss'}),[]);
assert.equal((await catalog.get(540)).variants.length,3,'Search filters must not mutate the original variants');
assert.equal(await catalog.get(999),null); await assert.rejects(catalog.get(540,'xx'),/language/);
const snapshot = resolve(temp,'snapshot'), output = resolve(temp,'published');
const report = {status:'ready',outputHashes:Object.fromEntries(await Promise.all(['manifest.json',...Object.keys(manifest.files)].map(async path => ['project/'+path,hash(await readFile(resolve(project,path)))])))};
await writeFile(resolve(snapshot,'report.json'),encode(report));
await writeFile(resolve(temp,'latest.json'),encode({snapshot:'snapshot',reportSha256:hash(encode(report))}));
await publishLatestProjectBosses(temp,output);
const before = await readFile(resolve(output,'manifest.json'));
await publishLatestProjectBosses(temp,output);
assert.deepEqual(await readFile(resolve(output,'manifest.json')),before);
const corePath = Object.values(manifest.groups)[0];
await writeFile(resolve(project,corePath),'tampered');
await assert.rejects(publishLatestProjectBosses(temp,output));
assert.deepEqual(await readFile(resolve(output,'manifest.json')),before);
await assert.rejects(readBossManifest(project),/mismatch/);
const liveCatalog = createBossCatalog('https://bosses.test/manifest.json',async url =>
  new Response(await readFile(resolve(root,'web/public/game-data/bosses',url.pathname.slice(1)))));
const colon = await liveCatalog.get(41);
const construction = colon.variants.find(variant => variant.key === '3300:10');
assert.equal(construction.entry.model,'difficulty-select');
assert.equal(construction.classification,'entry-boss');
assert.deepEqual(construction.classificationEvidence[0].controlFlow.map(edge=>edge.opcode),[38,20]);
assert.equal(colon.variants.find(variant=>variant.key==='4500:100').entry.model,'single','Never copy an entry route across maps sharing a UUID');
console.log('Boss catalog: PASS (binary/field/pipeline gates, distinct phases/maps, signed raw stats, lazy six-language reads, retry/hash checks, immutable/atomic publication)');
