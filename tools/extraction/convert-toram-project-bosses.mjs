import assert from 'node:assert/strict';
import { readFile, mkdir, writeFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { hash, encode, child, saveImmutable, validateManifestFiles, publishLatestProjectSnapshot } from './project-catalog-store.mjs';

const root = fileURLToPath(new URL('../..', import.meta.url));
const contractPath = resolve(root, 'tools/extraction/toram-boss-pipeline-contract.json');
export const BOSS_SCHEMA = 'toram.project-bosses.v1';

async function projectRules() {
  return { ...JSON.parse(await readFile(resolve(root,'data/sources/toram-monsters/monster-native-rules.json'))),
    classification:JSON.parse(await readFile(resolve(root,'data/sources/toram-monsters/boss-classification-rules.json'))) };
}

async function reviewedContract() {
  const bytes = await readFile(contractPath), contract = JSON.parse(bytes);
  // Published snapshots pin this contract's bytes, including the original source paths.
  for (const [path, expected] of Object.entries(contract.evidenceFiles)) assert.equal(hash(await readFile(child(root, path.replace(/^assets\/source-data\//u, 'data/sources/')))), expected, 'Boss evidence changed: ' + path);
  return { bytes, contract };
}

export async function readBossManifest(directory) {
  const manifest = JSON.parse(await readFile(child(directory, 'manifest.json')));
  assert.equal(manifest.schema, BOSS_SCHEMA);
  assert.match(manifest.revision, /^[a-f0-9]{64}$/u);
  const { bytes } = await reviewedContract();
  assert.equal(manifest.contractSha256, hash(bytes), 'Boss source contract differs.');
  await validateManifestFiles(directory, manifest, [manifest.index, manifest.rules, ...Object.values(manifest.groups), ...Object.values(manifest.locales)]);
  assert.deepEqual(JSON.parse(await readFile(child(directory, manifest.rules))), await projectRules());
  return manifest;
}

export async function convertBosses(input, output) {
  const { bytes:contractBytes, contract } = await reviewedContract();
  assert.equal(input.schema, 'toram.raw-monsters.v1');
  assert.equal(input.contractSha256, hash(contractBytes), 'Boss source contract differs.');
  assert.match(input.revision, /^[a-f0-9]{64}$/u);
  assert.equal(input.coverage.scope, 'all-manifest-field-script-groups');
  const fields = new Map(input.fields.map(field => [field.fieldId, field]));
  const masters = new Map(input.monsters.map(monster => [monster.key, monster]));
  assert.equal(fields.size, input.fields.length);
  const files = {}, groups = {}, index = {}, seen = new Set(), classifications = {};
  async function asset(name, value) {
    const bytes = encode(value), sha256 = hash(bytes), path = `${name}.${sha256.slice(0,16)}.json`;
    files[path] = { bytes:bytes.length, sha256 };
    await saveImmutable(child(output, path), bytes);
    return path;
  }
  const byGroup = new Map();
  for (const monster of input.monsters) {
    const raw = monster.raw, field = fields.get(monster.fieldId);
    assert.equal(monster.key, `${monster.fieldId}:${raw.id}`);
    assert.equal(monster.gameMonsterId, raw.uuid);
    assert.ok(Number.isSafeInteger(raw.uuid) && raw.uuid >= 0 && field && !seen.has(monster.key), 'Invalid/duplicate boss variant.');
    seen.add(monster.key);
    if (!(raw.flagRaw & 4)) continue;
    const expectedEvidence = { 'guild-raid-boss':'reviewed-guild-raid-route', 'high-raid-boss':'HighRaidBossMaster', 'dungeon-boss':'MobMultiFlag.Dungeon',
      'field-boss':'serialized-mmo-pop', 'entry-boss':'BossMenu-entry', unresolved:null };
    assert.ok(Object.hasOwn(expectedEvidence,monster.classification) && Array.isArray(monster.classificationEvidence), 'Invalid boss classification.');
    if (expectedEvidence[monster.classification]) assert.ok(monster.classificationEvidence.some(row => row.kind === expectedEvidence[monster.classification]), 'Missing boss classification evidence.');
    classifications[monster.classification] = (classifications[monster.classification] || 0) + 1;
    assert.equal(monster.sourceSha256, field.master.sha256);
    assert.match(monster.sourceSha256, /^[a-f0-9]{64}$/u);
    const baseStats = Object.fromEntries(['level','maxHp','def','mdef','necessaryHit','cutAttack','cutMagicAttack','guard','avoid','elementRaw','expDefNormal','expDefSkill','expDefMagic'].map(key => {
      assert.ok(Number.isSafeInteger(raw[key]), 'Invalid raw monster stat: ' + key);
      return [key, raw[key]];
    }));
    const entry = { model:({ 'field-boss':'single', 'entry-boss':'difficulty-select', 'high-raid-boss':'level-select', 'guild-raid-boss':'level-select' })[monster.classification] || 'unresolved' };
    if (entry.model === 'single') entry.difficulty = null;
    if (monster.classification === 'guild-raid-boss') {
      entry.levelParameters = { baseLevel:40, minLevel:40, maxLevel:1020, step:4 };
      entry.actor = monster.classificationEvidence.find(row => row.kind === 'reviewed-guild-raid-route').actor.identity ?? null;
    } else if (entry.model === 'level-select') {
      const record = monster.classificationEvidence.find(row => row.kind === 'HighRaidBossMaster').record;
      assert.ok(Number.isSafeInteger(record.baseLevel) && Number.isSafeInteger(record.minLevel), 'Invalid HighRaid level parameters.');
      entry.levelParameters = { baseLevel:record.baseLevel, minLevel:record.minLevel };
    }
    const group = String(Math.floor(raw.uuid / 100));
    if (!byGroup.has(group)) byGroup.set(group, []);
    byGroup.get(group).push({ key:monster.key, gameMonsterId:raw.uuid, masterId:raw.id, fieldId:monster.fieldId,
      roomId:raw.roomId, flagRaw:raw.flagRaw, nameRaw:raw.nameRaw, baseStats,
      parts:raw.parts, modes:raw.modes, properties:raw.properties,
      partStats:raw.parts.map(part => {
        const linked = masters.get(`${monster.fieldId}:${part.value}`);
        return { partId:part.partId, masterId:part.value, sourceSha256:linked?.sourceSha256 ?? null,
          properties:linked?.raw.properties ?? null,
          stats:linked ? Object.fromEntries(['def','mdef','cutAttack','cutMagicAttack'].map(key => [key, linked.raw[key]])) : null };
      }),
      sourceSha256:monster.sourceSha256, rawRecordSha256:hash(Buffer.from(raw.rawRecordHex,'hex')),
      spawnRooms:field.mapInfo.popMobs.filter(pop => pop.tree.monsterDatabaseID === raw.id).map(pop => ({
        name:pop.gameObjectName, ancestors:pop.ancestorGameObjectNames, definition:pop.tree
      })),
      mapRooms:field.mapInfo.childGameObjects.map(room => room.name),
      classification:monster.classification, classificationEvidence:monster.classificationEvidence,
      entry, difficultyScope:entry.model === 'single' ? 'none' : 'unresolved' });
    index[raw.uuid] = group;
  }
  assert.ok(byGroup.size, 'Empty boss catalog.');
  for (const [group, variants] of byGroup) groups[group] = await asset('bosses/' + group, variants);
  const locales = {};
  for (const locale of contract.requiredLocales) {
    assert.ok(input.names[locale] && input.fieldNames[locale], 'Missing boss locale.');
    locales[locale] = await asset('names/' + locale, { monsters:input.names[locale], fields:input.fieldNames[locale] });
  }
  const manifest = { schema:BOSS_SCHEMA, revision:input.revision, contractSha256:input.contractSha256,
    coverage:input.coverage, rejectedFields:input.rejectedFields,
    sourceDiagnostics:{ invalidScriptEntryFieldIds:input.fields.filter(field => field.mapInfo?.invalidScriptEntryOffsets?.length).map(field => field.fieldId),
      unresolvedHighRaidRecordNumbers:(input.unresolvedHighRaidReferences || []).map(record => record.no) },
    counts:{ monsterIds:Object.keys(index).length, variants:[...byGroup.values()].reduce((count, rows) => count + rows.length, 0) },
    classifications,
    index:await asset('index', index), groups, locales,
    rules:await asset('native-rules', await projectRules()),
    limitations:['Raw base master values; phase, parts, room, difficulty and runtime buffs are separate.',
      'Boss flag includes phase/part records. Only positively linked source routes are classified; difficulty scope remains unresolved.',
      'CutAttack/CutMagicAttack are percentage points. Final target values require the classified route, difficulty/level and part properties.'], files };
  await mkdir(output, { recursive:true });
  await writeFile(child(output, 'manifest.json'), encode(manifest), { flag:'wx' });
  await readBossManifest(output);
  return manifest;
}

export const publishLatestProjectBosses = (store, output) => publishLatestProjectSnapshot(store, output, readBossManifest);

if (process.argv[1] && import.meta.url === pathToFileURL(resolve(process.argv[1])).href) {
  const args = process.argv.slice(2);
  assert.equal(args.length, 4); assert.equal(args[0], '--input'); assert.equal(args[2], '--output');
  const manifest = await convertBosses(JSON.parse(await readFile(resolve(args[1]))), resolve(args[3]));
  console.log(JSON.stringify({ schema:manifest.schema, counts:manifest.counts }));
}
