export const ITEM_CATALOG_SCHEMA = 'toram.project-items.v1';

function requireValue(condition, message) {
  if (!condition) throw new Error(message);
}

function immutable(value) {
  if (value && typeof value === 'object') {
    Object.values(value).forEach(immutable);
    Object.freeze(value);
  }
  return value;
}

export function matchesItemCondition(context, condition) {
  const ctx = context || {};
  if (condition.kind === 'either-weapon-slot') {
    requireValue(typeof ctx.mainType === 'string' && typeof ctx.subType === 'string', 'Item condition needs mainType and subType.');
    return condition.types.includes(ctx.mainType) || condition.types.includes(ctx.subType);
  }
  if (condition.kind === 'both-weapon-slots') {
    requireValue(typeof ctx.mainType === 'string' && typeof ctx.subType === 'string', 'Item condition needs mainType and subType.');
    return ctx.mainType === condition.main && ctx.subType === condition.sub;
  }
  if (condition.kind === 'body-battle-customize') {
    requireValue(typeof ctx.armorType === 'string', 'Item condition needs armorType.');
    return ctx.armorType === condition.armor;
  }
  throw new Error('Unsupported item condition.');
}

// Returns the project's StatOptionDraft[]; it never drops an active unmapped effect.
export function resolveItemOptions(item, context) {
  requireValue(['equipment','consumable-buff'].includes(item.effectScope), 'This item is catalog-only.');
  const stats = { ...item.stats };
  const unresolved = [...item.unresolved];
  for (const group of item.conditionalStats) {
    if (!matchesItemCondition(context, group.when)) continue;
    unresolved.push(...group.unresolved);
    for (const [key, value] of Object.entries(group.stats)) stats[key] = (stats[key] || 0) + value;
  }
  requireValue(unresolved.length === 0, `Item has unresolved effects in slots: ${unresolved.map(row => row.slot).join(', ')}.`);
  return Object.entries(stats).map(([key, value]) => {
    requireValue(/^[A-Z][A-Z0-9_]*$/u.test(key) && Number.isFinite(value), 'Invalid project stat option.');
    return { key, value };
  });
}

export const EQUIPMENT_ITEM_SCHEMA = 'toram.equipment-item.v1';
const weaponTypes = { 8:'발도검', 9:'선풍창', 10:'한손검', 11:'양손검', 12:'활', 13:'자동활', 14:'지팡이', 15:'마도구', 16:'권갑' };
const subWeaponTypes = { 8:'발도검', 10:'한손검(듀얼소드)', 15:'마도구', 16:'권갑', 17:'방패', 18:'단검', 19:'화살', 23:'인술 두루마리' };
const equipmentTypes = { armor:20, additional:21, special:22 };

export function subEquipmentUsesOptions(typeId) { return [17,18,19,23].includes(typeId); }

function validateSource(selection, registry) {
  requireValue(registry && typeof registry.normalize === 'function', '장비 옵션 레지스트리가 준비되지 않았습니다.');
  requireValue(Number.isSafeInteger(selection.gameItemId) && selection.gameItemId > 0, '장비 게임 ID가 올바르지 않습니다.');
  requireValue(typeof selection.cacheVersion === 'string' && /^[a-f0-9]{8}$/iu.test(selection.cacheVersion), '장비 데이터 버전이 올바르지 않습니다.');
  requireValue(typeof selection.sourceSha256 === 'string' && /^[a-f0-9]{64}$/u.test(selection.sourceSha256), '장비 출처 해시가 올바르지 않습니다.');
  requireValue(selection.name === null || typeof selection.name === 'string', '장비 이름이 올바르지 않습니다.');
}

function validateStats(value, registry) {
  requireValue(value && !Array.isArray(value) && typeof value === 'object', '장비 옵션 객체가 필요합니다.');
  for (const [key, amount] of Object.entries(value)) {
    requireValue(/^[A-Z][A-Z0-9_]*$/u.test(key) && Number.isFinite(amount), '장비 옵션 값이 올바르지 않습니다.');
    requireValue(registry.normalize(key) === key, `등록되지 않은 장비 옵션: ${key}`);
  }
}

// Saved builds pin the selected definition so a catalog update cannot change their calculation.
export function validateEquipmentSelection(selection, registry, slot) {
  requireValue(selection?.schema === EQUIPMENT_ITEM_SCHEMA, '지원하지 않는 장비 데이터 형식입니다.');
  validateSource(selection, registry);
  requireValue(Number.isSafeInteger(selection.typeId) && (Object.hasOwn(weaponTypes, selection.typeId) || Object.hasOwn(subWeaponTypes, selection.typeId) || Object.values(equipmentTypes).includes(selection.typeId)), '이 장비 종류는 아직 적용할 수 없습니다.');
  if (slot !== undefined) requireValue(slot === 'mainWeapon' ? Object.hasOwn(weaponTypes, selection.typeId)
    : slot === 'subWeapon' ? Object.hasOwn(subWeaponTypes, selection.typeId)
      : equipmentTypes[slot] === selection.typeId, '장비 원본과 적용 칸이 일치하지 않습니다.');
  validateStats(selection.stats, registry);
  requireValue(Array.isArray(selection.conditionalStats), '장비 조건 목록이 필요합니다.');
  for (const group of selection.conditionalStats) {
    const when = group.when;
    requireValue(when && typeof when === 'object', '장비 조건이 필요합니다.');
    if (when.kind === 'either-weapon-slot') {
      const labels = [...Object.values(weaponTypes), '한손검(듀얼소드)', '방패', '단검', '화살', '인술 두루마리'];
      requireValue(Array.isArray(when.types) && when.types.length > 0 && when.types.every(type => labels.includes(type)), '장비 무기 조건이 올바르지 않습니다.');
    } else if (when.kind === 'both-weapon-slots') {
      requireValue(when.main === '한손검' && when.sub === '한손검(듀얼소드)', '듀얼 장비 조건이 올바르지 않습니다.');
    } else requireValue(when.kind === 'body-battle-customize' && ['경량옷','중량옷'].includes(when.armor), '장비 개조 조건이 올바르지 않습니다.');
    validateStats(group.stats, registry);
    requireValue(Array.isArray(group.unresolved) && group.unresolved.length === 0, '미연결 장비 옵션은 적용할 수 없습니다.');
  }
  return selection;
}

export function resolveEquipmentOptions(selection, slot, context, registry) {
  validateEquipmentSelection(selection, registry, slot);
  requireValue(slot === 'mainWeapon' ? weaponTypes[selection.typeId] === context.mainType
    : slot === 'subWeapon' ? subWeaponTypes[selection.typeId] === context.subType && (selection.typeId !== 10 || context.mainType === '한손검')
      : equipmentTypes[slot] === selection.typeId, '선택한 장비와 장비 칸의 종류가 다릅니다. 원본 장비를 해제하거나 다시 선택해 주세요.');
  // SetEquip retains only element65 for some sub weapons; base inputs and unmapped elements stay separate.
  if (slot === 'subWeapon' && !subEquipmentUsesOptions(selection.typeId)) return [];
  return resolveItemOptions({ ...selection, effectScope:'equipment', unresolved:[] }, context);
}

export function createEquipmentSelection(item, slot, context, registry) {
  requireValue(item.fullyMapped && item.effectScope === 'equipment' && item.unresolved.length === 0,
    '미연결 옵션이 있는 아이템은 적용할 수 없습니다.');
  const selection = JSON.parse(JSON.stringify({ schema:EQUIPMENT_ITEM_SCHEMA, gameItemId:item.id,
    cacheVersion:item.cacheVersion, sourceSha256:item.sourceSha256, name:item.name, typeId:item.typeId,
    stats:item.stats, conditionalStats:item.conditionalStats }));
  resolveEquipmentOptions(selection, slot, context, registry);
  return immutable(selection);
}

export const CONSUMABLE_BUFF_SCHEMA = 'toram.consumable-buff.v1';

export function validateConsumableBuffSelection(selection, registry) {
  requireValue(selection?.schema === CONSUMABLE_BUFF_SCHEMA, '지원하지 않는 소모품 버프 형식입니다.');
  validateSource(selection, registry);
  requireValue([2,50].includes(selection.typeId), '이 소모품 종류는 버프로 적용할 수 없습니다.');
  requireValue(Number.isSafeInteger(selection.buffGroupId) && ((selection.buffGroupId >= 209 && selection.buffGroupId <= 224) || selection.buffGroupId === 255), '소모품 버프 계열이 올바르지 않습니다.');
  requireValue(Number.isSafeInteger(selection.durationSeconds) && selection.durationSeconds > 0, '소모품 버프 지속시간이 올바르지 않습니다.');
  validateStats(selection.stats, registry);
  requireValue(Object.keys(selection.stats).length > 0, '소모품 버프 효과가 없습니다.');
  requireValue(Object.values(selection.stats).every(value => value !== 0), '0을 참조하는 동적 소모품 효과는 적용할 수 없습니다.');
  return selection;
}

export function createConsumableBuffSelection(item, registry) {
  requireValue(item.effectScope === 'consumable-buff' && item.fullyMapped && item.buff
    && item.unresolved.length === 0 && item.conditionalStats.length === 0, '검증된 능력치 버프 소모품만 적용할 수 있습니다.');
  const selection = JSON.parse(JSON.stringify({ schema:CONSUMABLE_BUFF_SCHEMA, gameItemId:item.id,
    cacheVersion:item.cacheVersion, sourceSha256:item.sourceSha256, name:item.name, typeId:item.typeId,
    stats:item.stats, buffGroupId:item.buff.groupId, durationSeconds:item.buff.durationSeconds }));
  validateConsumableBuffSelection(selection, registry);
  return immutable(selection);
}

export function resolveConsumableBuffs(selections = [], registry) {
  requireValue(Array.isArray(selections), '소모품 버프 목록이 올바르지 않습니다.');
  const groups = new Set(), ids = new Set(), options = [];
  for (const selection of selections) {
    validateConsumableBuffSelection(selection, registry);
    requireValue(!groups.has(selection.buffGroupId) && !ids.has(selection.gameItemId), '같은 계열의 소모품 버프는 중복 적용할 수 없습니다.');
    groups.add(selection.buffGroupId); ids.add(selection.gameItemId);
    options.push(...Object.entries(selection.stats).map(([key, value]) => ({ key, value })));
  }
  return options;
}

export function createItemCatalog(manifestUrl = new URL('../../game-data/items/manifest.json', import.meta.url), fetcher = globalThis.fetch) {
  const base = new URL(manifestUrl);
  const pending = new Map();
  function get(path) {
    if (!pending.has(path)) {
      const url = new URL(path, base);
      requireValue(url.origin === base.origin && url.href.startsWith(new URL('.', base).href), 'Item asset escapes its catalog.');
      const promise = Promise.resolve().then(() => fetcher(url)).then(async response => {
        requireValue(response.ok, `Item asset request failed: ${response.status}.`);
        return immutable(await response.json());
      }).catch(error => { pending.delete(path); throw error; });
      pending.set(path, promise);
    }
    return pending.get(path);
  }
  async function manifest() {
    const value = await get('manifest.json');
    requireValue(value.schema === ITEM_CATALOG_SCHEMA, 'Unsupported item catalog schema.');
    return value;
  }
  async function kindFor(id, value) {
    requireValue(Number.isSafeInteger(id) && id > 0, 'Expected a positive game item ID.');
    const index = await get(value.index);
    requireValue(Object.hasOwn(index, String(id)), `Unknown game item ID: ${id}.`);
    return index[id];
  }
  function localeFiles(value, kind, locale) {
    requireValue(Object.hasOwn(value.locales, locale) && Object.hasOwn(value.locales[locale], kind), 'Unknown item locale/kind.');
    return value.locales[locale][kind];
  }
  return Object.freeze({
    async getCrystaCatalog() {
      const value = await manifest();
      requireValue(value.optimizerEligible === true, '크리스타 ID 통합 데이터 갱신이 필요합니다.');
      return get(value.kinds.crystas);
    },
    async refresh() {
      pending.delete('manifest.json');
      return (await manifest()).cacheVersion;
    },
    async getItem(id, locale = 'kr') {
      const value = await manifest();
      const kind = await kindFor(id, value);
      const files = localeFiles(value, kind, locale);
      const [items, names] = await Promise.all([get(value.kinds[kind]), get(files.names)]);
      requireValue(Object.hasOwn(items, String(id)), 'Item index/shard mismatch.');
      return Object.freeze({ id, kind, name:names[id] ?? null, ...items[id], cacheVersion:value.cacheVersion, sourceSha256:value.source.catalogSha256 });
    },
    async listItems(kind, locale = 'kr') {
      const value = await manifest();
      const files = localeFiles(value, kind, locale);
      const names = await get(files.names);
      return Object.entries(names).map(([id, name]) => ({ id:Number(id), name }));
    },
    async listBuffItems(locale = 'kr') {
      const value = await manifest(), files = localeFiles(value, 'consumables', locale);
      const [items, names] = await Promise.all([get(value.kinds.consumables), get(files.names)]);
      return Object.entries(items).filter(([, item]) => item.effectScope === 'consumable-buff' && item.fullyMapped)
        .map(([id]) => ({ id:Number(id), name:names[id] ?? null }));
    },
    async getDetails(id, locale = 'kr') {
      const value = await manifest();
      const kind = await kindFor(id, value);
      const details = await get(localeFiles(value, kind, locale).details);
      return details[id] || null;
    }
  });
}
