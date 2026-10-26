import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { createRequire } from 'node:module';
import { ITEM_CATALOG_SCHEMA } from '../../web/src/application/item-catalog.mjs';
import { hash, encode, child, saveImmutable, validateManifestFiles, publishProjectSnapshot, publishLatestProjectSnapshot } from './project-catalog-store.mjs';

const root = fileURLToPath(new URL('../..', import.meta.url));
const require = createRequire(import.meta.url);
const registry = require('../../web/src/calculation/stat-registry.js');
const typeLabels = { 8:['발도검'], 9:['선풍창'], 10:['한손검','한손검(듀얼소드)'], 11:['양손검'], 12:['활'],
  13:['자동활'], 14:['지팡이'], 15:['마도구'], 16:['권갑'], 17:['방패'], 18:['단검'], 19:['화살'], 23:['인술 두루마리'] };

export function projectCondition(capId) {
  const weapons = { 96:23, 97:10, 98:11, 99:12, 100:13, 101:14, 102:15, 103:16, 109:17, 115:9, 116:8, 117:19, 118:18 };
  if (weapons[capId]) return { kind:'either-weapon-slot', types:typeLabels[weapons[capId]] };
  if (capId === 108) return { kind:'both-weapon-slots', main:'한손검', sub:'한손검(듀얼소드)' };
  assert.ok(capId === 119 || capId === 120, 'Unreviewed condition cap.');
  return { kind:'body-battle-customize', armor:capId === 119 ? '경량옷' : '중량옷' };
}

function kindFor(item) {
  const checks = item.references.nativeChecks, type = item.master.type_id;
  if (checks.CheckCristaItem) return 'crystas';
  if (checks.CheckAvatarEquipItem) return 'avatars';
  if (type === 20) return 'armor';
  if (type === 21) return 'additional';
  if (type === 22) return 'special';
  if (checks.CheckWeaponItem || [17,18,19,23].includes(type)) return 'weapons';
  return checks.CheckUseItem || type < 6 ? 'consumables' : 'other';
}

export function consumableCategoryFor(source, rules) {
  const normalize = text => text.normalize('NFKC').replace(/\s+/gu, '');
  const declaredNames = {};
  const declared = new Set();
  for (const locale of ['kr','jp']) {
    const text = (source.descriptions[locale] || '').normalize('NFKC');
    const labels = [...text.matchAll(/「([^」]+)」[\s@]*(?:카테고리|カテゴリ)|\[([^\]]+)\][\s@]*(?:카테고리|カテゴリ)/gu)].map(match => (match[1] || match[2]).trim());
    if (labels.length) declaredNames[locale] = labels;
    for (const label of labels) {
      const category = rules.categories.find(row => (row.aliases[locale] || []).some(alias => normalize(alias) === normalize(label)));
      if (category) declared.add(category.id);
      else return null;
    }
  }
  assert.ok(declared.size <= 1, `Conflicting consumable category descriptions: ${source.gameItemId}.`);
  const markers = (source.propertyRecord?.caps || []).filter(cap => rules.categories.some(row => row.durationCapId === cap.cap_id));
  if (markers.length !== 1) return null;
  const category = rules.categories.find(row => declared.size ? declared.has(row.id) : row.durationCapId === markers[0].cap_id);
  return { id:category.id, names:category.names, basis:declared.size ? 'item-description' : 'duration-marker',
    durationCapId:markers[0].cap_id, declaredNames };
}

export function convertCatalog(catalog, mappings, useRules = {}, aliases = {}, categories) {
  assert.equal(catalog.nativeRulesApplied, true, 'Only native-gated connected data can be converted.');
  const byCap = new Map(mappings.map(row => [row.capId, row]));
  assert.equal(byCap.size, mappings.length);
  for (const row of mappings) assert.equal(registry.normalize(row.statId), row.statId, `Invalid stat ${row.statId}.`);
  const kinds = {}, names = {}, details = {}, index = {}, counts = { items:0, mappedOptions:0, unresolvedOptions:0, conditionGroups:0, buffMarkers:0, fullyMappedEquipment:0, fullyMappedConsumableBuffs:0 };
  for (const locale of catalog.availableItemLocales) { names[locale] = {}; details[locale] = {}; }
  for (const source of catalog.items) {
    const id = source.gameItemId, kind = kindFor(source);
    assert.ok(Number.isSafeInteger(id) && id > 0 && !Object.hasOwn(index, id), 'Invalid/duplicate game ID.');
    index[id] = kind;
    const item = { typeId:source.master.type_id, defaultSlot:({1:'mainWeapon',2:'subWeapon',3:'armor',4:'additional',5:'special'})[source.references.defaultSelectedEquipSlotValue] || null,
      effectScope:source.references.nativeChecks.CheckEquipItem || source.references.nativeChecks.CheckCristaItem ? 'equipment' : 'catalog-only',
      stats:{}, conditionalStats:[], unresolved:[] };
    item.baseRaw = { function:source.master.function, stability:source.master.stability, range:source.master.range_raw,
      slotMax:source.master.slot_max_raw, potential:source.master.potential, flags:source.master.flag_raw, model:source.master.model };
    if (kind === 'consumables' && categories) item.consumableCategory = source.references.nativeChecks.CheckUseItem
      ? consumableCategoryFor(source, categories) : null;
    if (kind === 'crystas') {
      item.gameItemId = id;
      item.names = source.names;
      item.descriptions = source.descriptions;
      item.aliases = aliases[id] || [];
      item.category = ({31:'노말',32:'무기',33:'방어구',34:'추가',35:'특수',61:'노말',62:'무기',63:'방어구',64:'추가',65:'특수'})[item.typeId] || null;
      item.previousId = item.typeId >= 61 && item.typeId <= 65 ? source.master.model : null;
      item.options = (source.propertyRecord?.caps || []).filter(cap => cap.cap_id !== 0).map(cap => ({
        slot:cap.slot, capId:cap.cap_id, rawValue:cap.value, enumName:cap.enumName,
        multiplierFloat32:cap.display.multiplierFloat32, valueFloat32:cap.display.scaledValueFloat32,
        conditionMarkerSlot:cap.conditionMarkerSlot ?? null, texts:cap.display.plainTextCandidates
      }));
    }
    const caps = (source.propertyRecord?.caps || []).filter(cap => cap.cap_id !== 0);
    const durationMarkers = caps.filter(cap => Object.hasOwn(useRules.durationMarkers || {}, cap.cap_id));
    const buffMarker = source.references.nativeChecks.CheckUseItem && useRules.consumableTypeIds?.includes(item.typeId)
      && durationMarkers.length === 1 && durationMarkers[0] === caps[0]
      && Number.isSafeInteger(caps[0].value) && caps[0].value > 0 && !(source.propertyRecord?.conditionGroups || []).length ? caps[0] : null;
    if (buffMarker) {
      assert.equal(buffMarker.enumName, useRules.durationMarkers[buffMarker.cap_id], 'Duration marker enum changed.');
      item.effectScope = 'consumable-buff';
      item.buff = { groupId:buffMarker.cap_id, durationSeconds:buffMarker.value };
      counts.buffMarkers++;
    }
    const groups = new Map(), assigned = new Map();
    for (const group of source.propertyRecord?.conditionGroups || []) {
      const marker = source.propertyRecord.caps.find(cap => cap.slot === group.markerSlot);
      assert.equal(marker?.cap_id, group.capId);
      assert.equal(marker.value, group.instructionCount);
      assert.equal(group.uiScopeMatchesBonusScope, true);
      assert.equal(group.instructionCount, group.targetSlots.length);
      assert.ok(!groups.has(group.markerSlot));
      const converted = { when:projectCondition(group.capId), stats:{}, unresolved:[] };
      groups.set(group.markerSlot, converted);
      item.conditionalStats.push(converted);
      for (const slot of group.targetSlots) { assert.ok(!assigned.has(slot)); assigned.set(slot, group.markerSlot); }
      counts.conditionGroups++;
    }
    const eventGates = [], eventTargets = new Map();
    for (const cap of source.propertyRecord?.caps || []) {
      if (cap.cap_id === 0) continue;
      if (cap === buffMarker) continue;
      if (groups.has(cap.slot)) { assert.equal(cap.role, 'equipment-condition-marker'); continue; }
      assert.notEqual(cap.role, 'equipment-condition-marker', 'Condition marker lacks a group.');
      assert.equal(cap.conditionMarkerSlot ?? null, assigned.get(cap.slot) ?? null, 'Conditional scope mismatch.');
      let target = cap.conditionMarkerSlot == null ? item : groups.get(cap.conditionMarkerSlot);
      assert.ok(target, 'Unknown option condition.');
      if (cap.cap_id === 114 && item.effectScope === 'equipment') {
        assert.equal(cap.enumName, 'bEventCheck');
        assert.ok(Number.isSafeInteger(cap.value), 'Invalid item event operand.');
        // eventCheck reads an unsigned byte. A false check stops the remaining script,
        // but a marker skipped by an equipment condition never executes.
        const event = { kind:'item-event', eventType:cap.value & 255 };
        eventGates.push(target === item ? event : { kind:'any', conditions:[{ kind:'not', condition:target.when }, event] });
        continue;
      }
      if (eventGates.length) {
        const conditions = [...eventGates, ...(target === item ? [] : [target.when])];
        const when = conditions.length === 1 ? conditions[0] : { kind:'all', conditions };
        const key = JSON.stringify(when);
        if (!eventTargets.has(key)) {
          const converted = { when, stats:{}, unresolved:[] };
          eventTargets.set(key, converted); item.conditionalStats.push(converted); counts.conditionGroups++;
        }
        target = eventTargets.get(key);
      }
      if (kind === 'weapons' && cap.cap_id === 65) {
        assert.equal(cap.enumName,'bElement');
        assert.ok(Number.isSafeInteger(cap.value) && cap.value >= 0 && cap.value <= 8 && cap.reference?.kind === 'element','Unreviewed weapon element.');
        assert.equal(target.element,undefined,'Duplicate weapon element.');
        target.element = cap.value; continue;
      }
      const candidateMapping = byCap.get(cap.cap_id);
      const mapping = candidateMapping?.scope && candidateMapping.scope !== kind ? null : candidateMapping;
      if (!mapping || (buffMarker && (cap.value === 0 || !mapping.enumName.startsWith('b')))) {
        target.unresolved.push({ slot:cap.slot, capId:cap.cap_id, rawValue:cap.value,
          reason:mapping ? 'dynamic-consumable-operand' : 'no-reviewed-project-stat-mapping', ...(cap.reference ? { reference:cap.reference } : {}) });
        counts.unresolvedOptions++;
        continue;
      }
      assert.equal(cap.enumName, mapping.enumName, 'Cap enum changed.');
      const value = cap.display.scaledValueFloat32;
      assert.equal(Math.fround(Math.fround(cap.value) * cap.display.multiplierFloat32), value);
      assert.ok(Number.isFinite(value));
      // Duplicate contributions need native aggregation review before becoming a single project stat.
      assert.ok(!Object.hasOwn(target.stats, mapping.statId), `Duplicate ${mapping.statId} in ${id}; review aggregation.`);
      target.stats[mapping.statId] = value;
      counts.mappedOptions++;
    }
    item.fullyMapped = ['equipment','consumable-buff'].includes(item.effectScope) && item.unresolved.length === 0
      && item.conditionalStats.every(group => group.unresolved.length === 0) && (item.effectScope !== 'consumable-buff' || Object.keys(item.stats).length > 0);
    if (item.fullyMapped && item.effectScope === 'equipment') counts.fullyMappedEquipment++;
    if (item.fullyMapped && item.effectScope === 'consumable-buff') counts.fullyMappedConsumableBuffs++;
    (kinds[kind] ||= {})[id] = item;
    for (const locale of catalog.availableItemLocales) {
      ((names[locale][kind] ||= {}))[id] = source.names[locale] ?? null;
      const texts = {};
      for (const cap of source.propertyRecord?.caps || []) {
        if (cap !== buffMarker && !byCap.has(cap.cap_id) && cap.cap_id > 0 && !groups.has(cap.slot)) texts[cap.slot] = cap.display?.plainTextCandidates?.[locale] ?? null;
      }
      (details[locale][kind] ||= {})[id] = { description:source.descriptions[locale] ?? null,
        optionTextCandidates:texts,
        displayOptions:(source.propertyRecord?.caps || []).filter(cap => cap.cap_id > 0 && cap !== buffMarker && cap.display?.plainTextCandidates?.[locale]?.trim())
          .map(cap => ({text:cap.display.plainTextCandidates[locale],conditional:groups.has(cap.slot) || assigned.has(cap.slot)})) };
    }
    counts.items++;
  }
  for (const item of Object.values(kinds.crystas || {})) {
    const visited = new Set([item.gameItemId]);
    let current = item;
    while (current.previousId !== null) {
      assert.ok(Number.isSafeInteger(current.previousId) && !visited.has(current.previousId), 'Invalid/cyclic crysta lineage.');
      visited.add(current.previousId);
      current = kinds.crystas[current.previousId];
      assert.ok(current && current.category === item.category, 'Missing/cross-category crysta predecessor.');
    }
  }
  return { kinds, names, details, index, counts };
}

async function reviewedInput(name) {
  const contract = JSON.parse(await readFile(resolve(root, 'tools/extraction/toram-item-pipeline-contract.json')));
  const input = contract.inputs[name];
  assert.ok(input, `Reviewed input is missing: ${name}.`);
  const bytes = await readFile(child(root, input.path.replace(/^assets\/source-data\//u, 'data/sources/')));
  assert.equal(hash(bytes), input.sha256, `Reviewed input changed: ${name}.`);
  const value = JSON.parse(bytes);
  if (name === 'itemUseRules') {
    assert.equal(value.schemaVersion, 1);
    // Frozen evidence keeps its original path and hash across repository moves.
    for (const evidence of value.evidence) assert.equal(hash(await readFile(child(root, evidence.path.replace(/^assets\/source-data\//u, 'data/sources/')))), evidence.sha256, `Item use evidence changed: ${evidence.path}.`);
  }
  return { value, sha256:hash(bytes) };
}

export async function exportProjectItems(input, output) {
  const bytes = await readFile(input), catalog = JSON.parse(bytes);
  const [mapping, useRules, aliases, categories] = await Promise.all([reviewedInput('projectStatMapping'), reviewedInput('itemUseRules'), reviewedInput('crystaAliases'), reviewedInput('consumableCategories')]);
  const rows = mapping.value.statMapping;
  const converted = convertCatalog(catalog, rows, useRules.value, aliases.value.aliases, categories.value);
  for (const item of Object.values(converted.kinds.crystas || {})) {
    assert.ok(item.category || item.typeId === 36, `Unreviewed crysta type: ${item.gameItemId}.`);
    assert.ok(!item.category || item.fullyMapped, `Crysta options need review before publication: ${item.gameItemId}.`);
  }
  const manifest = { schema:ITEM_CATALOG_SCHEMA, cacheVersion:catalog.cacheVersion, kinds:{}, locales:{}, files:{}, counts:converted.counts,
    source:{ catalogSha256:hash(bytes), mappingSha256:mapping.sha256, itemUseRulesSha256:useRules.sha256, crystaAliasesSha256:aliases.sha256, consumableCategoriesSha256:categories.sha256,
      registrySha256:hash(await readFile(resolve(root, 'web/src/calculation/stat-registry.js'))) },
    statDefinitions:Object.fromEntries(rows.map(row => [row.statId, { unit:registry.get(row.statId).unit, status:registry.get(row.statId).status }])),
    calculationContract:'StatOptionDraft {key,value}; resolve conditions before applying; fullyMapped is mapping coverage, not combat/UI verification.',
    optimizerEligible:true, optimizerReason:'ID-keyed crystas with validated native predecessor IDs; legacy names are aliases.' };
  async function asset(name, value) {
    const data = encode(value), sha256 = hash(data), path = `${name}.${sha256.slice(0, 16)}.json`;
    await saveImmutable(child(output, path), data);
    manifest.files[path] = { sha256, bytes:data.length };
    return path;
  }
  manifest.index = await asset('index', converted.index);
  for (const [kind, rows] of Object.entries(converted.kinds)) manifest.kinds[kind] = await asset(`items/${kind}`, rows);
  for (const [locale, groups] of Object.entries(converted.names)) {
    manifest.locales[locale] = {};
    for (const [kind, rows] of Object.entries(groups)) manifest.locales[locale][kind] = {
      names:await asset(`locales/${locale}/${kind}.names`, rows), details:await asset(`locales/${locale}/${kind}.details`, converted.details[locale][kind])
    };
  }
  await saveImmutable(child(output, 'manifest.json'), encode(manifest));
  return manifest;
}

export async function readProjectManifest(directory) {
  const manifest = JSON.parse(await readFile(child(directory, 'manifest.json')));
  assert.equal(manifest.schema, ITEM_CATALOG_SCHEMA);
  assert.equal(manifest.source.registrySha256, hash(await readFile(resolve(root, 'web/src/calculation/stat-registry.js'))), 'Project stat registry changed; regenerate the item export.');
  assert.equal(manifest.source.itemUseRulesSha256, (await reviewedInput('itemUseRules')).sha256, 'Item use rules changed; regenerate the item export.');
  assert.equal(manifest.source.mappingSha256, (await reviewedInput('projectStatMapping')).sha256, 'Project stat mapping changed; regenerate the item export.');
  assert.equal(manifest.source.crystaAliasesSha256, (await reviewedInput('crystaAliases')).sha256, 'Crysta aliases changed; regenerate the item export.');
  assert.equal(manifest.source.consumableCategoriesSha256, (await reviewedInput('consumableCategories')).sha256, 'Consumable categories changed; regenerate the item export.');
  const referenced = [manifest.index, ...Object.values(manifest.kinds),
    ...Object.values(manifest.locales).flatMap(kinds => Object.values(kinds).flatMap(group => [group.names, group.details]))];
  await validateManifestFiles(directory, manifest, referenced);
  return manifest;
}

export async function publishProjectItems(snapshot, output) {
  return publishProjectSnapshot(snapshot, output, readProjectManifest);
}

export async function publishLatestProjectItems(store, output) {
  return publishLatestProjectSnapshot(store, output, readProjectManifest);
}

async function main() {
  const args = process.argv.slice(2), flags = {};
  for (let i = 0; i < args.length; i += 2) {
    assert.ok(['--input','--output','--snapshot'].includes(args[i]) && args[i + 1], 'Use --input or --snapshot, plus --output.');
    assert.ok(!Object.hasOwn(flags, args[i])); flags[args[i]] = resolve(args[i + 1]);
  }
  assert.ok(!(flags['--input'] && flags['--snapshot']), 'Choose input conversion or snapshot publication.');
  const output = flags['--output'] || resolve(root, 'web/public/game-data/items');
  let manifest;
  if (flags['--input']) manifest = await exportProjectItems(flags['--input'], output);
  else {
    let snapshot = flags['--snapshot'];
    if (!snapshot) {
      manifest = await publishLatestProjectItems(resolve(root, 'data/sources/toram-items/pipeline/releaseC'), output);
    } else manifest = await publishProjectItems(snapshot, output);
  }
  console.log(JSON.stringify({ schema:manifest.schema, output, counts:manifest.counts, files:Object.keys(manifest.files).length }));
}

if (process.argv[1] && import.meta.url === pathToFileURL(resolve(process.argv[1])).href) await main();
