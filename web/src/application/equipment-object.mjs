import { validateEquipmentSelection, resolveEquipmentOptions } from './item-catalog.mjs';

export const EQUIPMENT_SLOTS = Object.freeze({ mainWeapon:'주무기', subWeapon:'보조무기', armor:'몸 장비', additional:'추가 장비', special:'특수 장비' });
export const SUB_WEAPON_RULES = Object.freeze({
  '한손검':['없음','방패','단검','화살','마도구','권갑','인술 두루마리','한손검(듀얼소드)'], '양손검':['없음'],
  '활':['없음','화살','발도검'], '자동활':['없음','방패','단검','화살','마도구','권갑'],
  '지팡이':['없음','방패','단검','화살','마도구','권갑','인술 두루마리'], '마도구':['없음','인술 두루마리'],
  '권갑':['없음','방패','단검','화살','마도구'], '선풍창':['없음','화살','단검'], '발도검':['없음','단검','인술 두루마리'], '맨손':['없음']
});
export const EQUIPMENT_TYPES = Object.freeze({
  sword:['한손검','한손검(듀얼소드)'], greatsword:['양손검'], bow:['활'], bowgun:['자동활'], staff:['지팡이'],
  device:['마도구'], knuckle:['권갑'], halberd:['선풍창'], katana:['발도검'], shield:['방패'], dagger:['단검'],
  arrow:['화살'], scroll:['인술 두루마리'], unarmed:['맨손'], none:['없음'], armor:['일반옷','경량옷','중량옷'], additional:[null], special:[null]
});
export const EQUIPMENT_SLOT_TYPES = Object.freeze({ mainWeapon:['한손검','양손검','활','자동활','지팡이','마도구','권갑','선풍창','발도검','맨손'],
  subWeapon:['없음','방패','단검','화살','마도구','권갑','인술 두루마리','한손검(듀얼소드)','발도검'],
  armor:EQUIPMENT_TYPES.armor, additional:[null], special:[null] });
const requireValue = (ok, message) => { if (!ok) throw new Error(message); };
const object = value => value && typeof value === 'object' && !Array.isArray(value);
function keys(value, allowed) { requireValue(object(value) && Object.keys(value).every(key => allowed.includes(key)), '지원하지 않는 장비 필드가 있습니다.'); }

// Storage bounds limit request complexity; they are not game stat caps.
export function validateEquipmentObject(data, registry) {
  keys(data, ['slot','equipment']);
  requireValue(Object.hasOwn(EQUIPMENT_SLOTS, data.slot), '장비 부위를 선택하세요.');
  const p = data.equipment;
  keys(p, ['type','attack','refinement','stability','options','crystas','lockedCrystaSlots','catalogItem']);
  requireValue(EQUIPMENT_SLOT_TYPES[data.slot].includes(p.type), '장비 부위와 종류가 맞지 않습니다.');
  const weapon = ['mainWeapon','subWeapon'].includes(data.slot);
  for (const key of ['attack','refinement','stability']) requireValue(weapon ? Number.isFinite(p[key]) : p[key] === null, '장비 기본 수치가 올바르지 않습니다.');
  requireValue(Array.isArray(p.options) && p.options.length <= 100, '장비 옵션은 100개 이하여야 합니다.');
  for (const option of p.options) {
    keys(option, ['key','value']);
    requireValue(typeof option.key === 'string' && option.key.length <= 64 && registry.normalize(option.key) && Number.isFinite(option.value), '등록된 장비 옵션과 유한한 수치가 필요합니다.');
  }
  const count = data.slot === 'subWeapon' ? 0 : 2;
  requireValue(Array.isArray(p.crystas) && p.crystas.length === count && p.crystas.every(value => typeof value === 'string' && value.length <= 160 && !/[\x00-\x1f\x7f]/u.test(value)), '크리스타 슬롯이 올바르지 않습니다.');
  requireValue(Array.isArray(p.lockedCrystaSlots) && p.lockedCrystaSlots.length === count && p.lockedCrystaSlots.every(value => typeof value === 'boolean'), '크리스타 잠금 정보가 올바르지 않습니다.');
  if (p.catalogItem !== undefined) {
    keys(p.catalogItem, ['schema','gameItemId','cacheVersion','sourceSha256','name','typeId','stats','conditionalStats','element']);
    requireValue((p.catalogItem.name === null || typeof p.catalogItem.name === 'string' && p.catalogItem.name.length <= 240)
      && Array.isArray(p.catalogItem.conditionalStats) && p.catalogItem.conditionalStats.length <= 100, '장비 원본 정보가 올바르지 않습니다.');
    validateEquipmentSelection(p.catalogItem, registry, data.slot);
    for (const group of p.catalogItem.conditionalStats) {
      keys(group, ['when','stats','unresolved','element']);
    }
    // Verify the selection against its own type, independently of the current calculator.
    const context = { mainType:data.slot === 'mainWeapon' ? p.type : '한손검', subType:data.slot === 'subWeapon' ? p.type : '없음', armorType:data.slot === 'armor' ? p.type : '일반옷' };
    resolveEquipmentOptions(p.catalogItem, data.slot, context, registry);
  }
  return data;
}

export function equipmentType(data) {
  if (['armor','additional','special'].includes(data.slot)) return data.slot;
  return Object.keys(EQUIPMENT_TYPES).find(key => EQUIPMENT_TYPES[key].includes(data.equipment.type));
}
