import { validateEquipmentObject } from './equipment-object.mjs';
import { resolveConsumableBuffs } from './item-catalog.mjs';
import { validateBossSelection } from './boss-target.mjs';

const object = value => value && typeof value === 'object' && !Array.isArray(value);
const finite = value => typeof value === 'number' && Number.isFinite(value);
const requireValue = (ok, message) => { if (!ok) throw new Error(message); };
function fields(value, allowed) { requireValue(object(value) && Object.keys(value).every(key => allowed.includes(key)), '지원하지 않는 구성 필드가 있습니다.'); }
const attributes = ['STR','INT','VIT','AGI','DEX','CRT'];
const targetFields = ['bossLevel','bossDef','bossMdef','bossPhysResist','bossMagResist','bossCritResist'];

export function validateCharacter(value) {
  fields(value,['level','attributes']); fields(value.attributes,attributes);
  requireValue(finite(value.level) && Object.keys(value.attributes).length === attributes.length && Object.values(value.attributes).every(finite), '스테이터스를 확인하세요.');
}
export function validateOptions(value, registry) {
  requireValue(Array.isArray(value) && value.length <= 100, '옵션 목록이 올바르지 않습니다.');
  for (const option of value) { fields(option,['key','value']); requireValue(typeof option.key === 'string' && registry.normalize(option.key) && finite(option.value), '장비 옵션을 확인하세요.'); }
}
export function validateFood(value, food) {
  requireValue(Array.isArray(value) && value.length === 5, '요리는 5칸이어야 합니다.');
  const normalized = food.normalize(value);
  value.forEach((item,index) => { if (item === null) return; fields(item,['id','level']); requireValue(normalized[index]?.id === item.id && normalized[index]?.level === item.level, '요리의 중복·레벨을 확인하세요.'); });
}
export function validateScenario(value) {
  fields(value,['target','conditions','optimizationPreferences','bossSelection']);
  fields(value.target,[...targetFields,'targetElement']);
  requireValue(targetFields.every(key => finite(value.target[key])), '대상 수치를 확인하세요.');
  if (value.target.targetElement !== undefined) requireValue(Number.isSafeInteger(value.target.targetElement) && value.target.targetElement >= 0 && value.target.targetElement <= 7, '대상 속성을 확인하세요.');
  if (value.conditions !== undefined) {
    requireValue(object(value.conditions) && Object.keys(value.conditions).length <= 64 && Object.keys(value.conditions).every(key => /^[A-Za-z0-9_:-]{1,80}$/u.test(key)), '계산 조건을 확인하세요.');
    for (const [key,item] of Object.entries(value.conditions)) {
      if (key === 'activeItemEventTypes') requireValue(Array.isArray(item) && item.length <= 256 && new Set(item).size === item.length && item.every(type => Number.isSafeInteger(type) && type >= 0 && type <= 255), '장비 이벤트 조건을 확인하세요.');
      else requireValue(item === null || typeof item === 'boolean' || finite(item) || typeof item === 'string' && item.length <= 160, '계산 조건을 확인하세요.');
    }
  }
  if (value.bossSelection !== undefined) validateBossSelection(value.bossSelection);
  if (value.optimizationPreferences !== undefined) {
    const pref = value.optimizationPreferences; fields(pref,['rangeOverride','requirements','bannedCrystas']);
    if (pref.rangeOverride !== undefined) requireValue([null,'SHORT','LONG'].includes(pref.rangeOverride), '거리 설정을 확인하세요.');
    if (pref.requirements !== undefined) {
      fields(pref.requirements,['maxHp','maxMp','amprBeforeDual','normalAttackCrit','aspd']);
      requireValue(Object.values(pref.requirements).every(item => item === null || finite(item) && item >= 0), '요구조건 수치를 확인하세요.');
    }
    if (pref.bannedCrystas !== undefined) requireValue(Array.isArray(pref.bannedCrystas) && pref.bannedCrystas.length <= 1000 && pref.bannedCrystas.every(item => typeof item === 'string' && item.length <= 160), '제외 목록을 확인하세요.');
  }
  return value;
}
export function validateBuildExtras(value, rules) {
  validateOptions(value.externalOptions,rules.registry);
  if (value.myRoomFood !== undefined) validateFood(value.myRoomFood,rules.food);
  if (value.guildFoodBuff !== undefined) requireValue(typeof value.guildFoodBuff === 'boolean', '길드 요리 설정이 올바르지 않습니다.');
}
export function validateBuild(value, rules) {
  requireValue(object(value) && object(value.equipment) && object(value.skillLevels) && object(value.activeBuffs) && Array.isArray(value.combo), '빌드 구성을 확인하세요.');
  validateCharacter(value.character); validateBuildExtras(value,rules);
  for (const slot of ['mainWeapon','subWeapon','armor','additional','special']) validateEquipmentObject({slot,equipment:value.equipment[slot]},rules.registry);
  if (value.consumableBuffs !== undefined) resolveConsumableBuffs(value.consumableBuffs,rules.registry);
  return value;
}
