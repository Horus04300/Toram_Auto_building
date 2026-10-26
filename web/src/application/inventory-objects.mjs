import { EQUIPMENT_SLOTS, validateEquipmentObject } from './equipment-object.mjs';
import { validateConsumableBuffSelection, resolveConsumableBuffs, isConsumableGroupId } from './item-catalog.mjs';
import { validateBossSelection } from './boss-target.mjs';

export const INVENTORY_TYPES = Object.freeze({ equipment:'장비', equipment_set:'장비 세팅', status:'스테이터스', skill_tree:'스킬트리', skill_set:'스킬셋', consumable:'도핑', consumable_set:'도핑 세팅', combo:'콤보', combo_set:'콤보 목록', build:'빌드' });
export const SECTION_TYPES = Object.freeze({ status:'status', equipment:'equipment_set', skills:'skill_set', consumables:'consumable_set', combos:'combo_set' });
const groups = { equipment_set:['slots','equipment'], skill_set:['trees','skill_tree'], consumable_set:['categories','consumable'] };
const own = (value, key) => Object.hasOwn(value, key);
const object = value => value && typeof value === 'object' && !Array.isArray(value);
export const requireValue = (ok, message) => { if (!ok) throw new Error(message); };
export function fields(value, allowed) { requireValue(object(value) && Object.keys(value).every(key => allowed.includes(key)), '지원하지 않는 구성 필드가 있습니다.'); }
const finite = value => typeof value === 'number' && Number.isFinite(value);
const scalar = value => value === null || typeof value === 'boolean' || finite(value) || typeof value === 'string' && value.length <= 160;
function map(value, max = 100) { requireValue(object(value) && Object.keys(value).length <= max && Object.keys(value).every(key => /^[A-Za-z0-9_:-]{1,80}$/u.test(key)), '구성 키 또는 목록 크기가 올바르지 않습니다.'); }
function options(value, registry) { requireValue(Array.isArray(value) && value.length <= 100, '옵션 목록이 올바르지 않습니다.'); for (const item of value) { fields(item,['key','value']); requireValue(typeof item.key === 'string' && registry.normalize(item.key) && finite(item.value), '장비 옵션을 확인하세요.'); } }
export function validateProvenance(value) {
  requireValue(Array.isArray(value) && value.length <= 64, '출처 목록이 올바르지 않습니다.');
  for (const source of value) {
    if (source?.kind === 'inventory') { fields(source,['kind','objectId','revision']); requireValue(/^[a-f0-9-]{36}$/u.test(source.objectId) && Number.isSafeInteger(source.revision) && source.revision > 0, '개인 객체 출처가 올바르지 않습니다.'); }
    else if (source?.kind === 'release') { fields(source,['kind','postId','releaseNumber']); requireValue(/^[a-f0-9-]{36}$/u.test(source.postId) && Number.isSafeInteger(source.releaseNumber) && source.releaseNumber > 0, '공개 릴리스 출처가 올바르지 않습니다.'); }
    else { fields(source,['kind','gameItemId','cacheVersion','sourceSha256']); requireValue(source.kind === 'catalog' && Number.isSafeInteger(source.gameItemId) && source.gameItemId > 0 && /^[a-f0-9]{8}$/iu.test(source.cacheVersion) && /^[a-f0-9]{64}$/u.test(source.sourceSha256), '도감 출처가 올바르지 않습니다.'); }
  }
}
export function snapshot(record) {
  return structuredClone({type:record.type, schemaVersion:1, name:record.name, data:record.data,
    provenance:record.id ? [{kind:'inventory',objectId:record.id,revision:record.revision}] : record.provenance || []});
}
export function makeSnapshot(type, data, previous) { return {type, schemaVersion:1, name:previous?.name || INVENTORY_TYPES[type], data, provenance:structuredClone(previous?.provenance || [])}; }

function child(value, type, rules) {
  fields(value,['type','schemaVersion','name','data','provenance']);
  requireValue(value.type === type && value.schemaVersion === 1 && typeof value.name === 'string' && value.name.trim() && value.name.length <= 80 && !/[\x00-\x1f\x7f]/u.test(value.name), '하위 구성 종류가 맞지 않습니다.');
  validateProvenance(value.provenance); validateInventoryObject(type, value.data, rules);
}
function treeInfo(rules, id) { return rules.trees.trees.find(tree => tree.id === id); }
function skillId(rules, id) { const [tree, index, ...extra] = String(id).split(':'); return !extra.length && /^\d+$/u.test(index || '') && treeInfo(rules,tree)?.skills.some(skill => skill.id === Number(index)); }
function validateContext(data, rules) {
  fields(data,['externalOptions','myRoomFood','guildFoodBuff','scenario']); options(data.externalOptions, rules.registry);
  if (data.myRoomFood !== undefined) {
    requireValue(Array.isArray(data.myRoomFood) && data.myRoomFood.length === 5, '요리는 5칸이어야 합니다.');
    const normalized = rules.food.normalize(data.myRoomFood);
    data.myRoomFood.forEach((item,index) => { if (item === null) return; fields(item,['id','level']); requireValue(normalized[index]?.id === item.id && normalized[index]?.level === item.level, '요리의 중복·레벨을 확인하세요.'); });
  }
  if (data.guildFoodBuff !== undefined) requireValue(typeof data.guildFoodBuff === 'boolean', '길드 요리 설정이 올바르지 않습니다.');
  const scenario = data.scenario; fields(scenario,['target','conditions','optimizationPreferences','bossSelection']);
  fields(scenario.target,['bossLevel','bossDef','bossMdef','bossPhysResist','bossMagResist','bossCritResist']);
  requireValue(Object.keys(scenario.target).length === 6 && Object.values(scenario.target).every(finite), '대상 수치를 확인하세요.');
  map(scenario.conditions,64); requireValue(Object.values(scenario.conditions).every(scalar), '계산 조건을 확인하세요.');
  if (scenario.bossSelection !== undefined) validateBossSelection(scenario.bossSelection);
  if (scenario.optimizationPreferences !== undefined) {
    const pref = scenario.optimizationPreferences; fields(pref,['rangeOverride','requirements','bannedCrystas']);
    requireValue([null,'SHORT','LONG'].includes(pref.rangeOverride), '거리 설정을 확인하세요.');
    fields(pref.requirements,['maxHp','maxMp','amprBeforeDual','normalAttackCrit','aspd']); requireValue(Object.values(pref.requirements).every(value => value === null || finite(value) && value >= 0), '요구조건 수치를 확인하세요.');
    requireValue(Array.isArray(pref.bannedCrystas) && pref.bannedCrystas.length <= 1000 && pref.bannedCrystas.every(value => typeof value === 'string' && value.length <= 160), '제외 목록을 확인하세요.');
  }
}

export function validateInventoryObject(type, data, rules) {
  requireValue(own(INVENTORY_TYPES,type), '지원하지 않는 구성 종류입니다.');
  if (type === 'equipment') return validateEquipmentObject(data, rules.registry);
  if (type === 'status') {
    fields(data,['character']); fields(data.character,['level','attributes']); fields(data.character.attributes,['STR','INT','VIT','AGI','DEX','CRT']);
    requireValue(finite(data.character.level) && Object.keys(data.character.attributes).length === 6 && Object.values(data.character.attributes).every(finite), '스테이터스를 확인하세요.');
  } else if (type === 'skill_tree') {
    fields(data,['treeId','levels','activeBuffs']); const tree = treeInfo(rules,data.treeId); requireValue(tree, '등록된 스킬트리가 필요합니다.');
    map(data.levels); map(data.activeBuffs);
    for (const [id, level] of Object.entries(data.levels)) requireValue(tree.skills.some(skill => String(skill.id) === id) && Number.isInteger(level) && level >= 0 && level <= rules.trees.skillMaxLevel, '스킬 ID·투자 레벨을 확인하세요.');
    for (const skill of tree.skills) if (data.levels[skill.id] > 0 && skill.prereq >= 0) requireValue(data.levels[skill.prereq] >= rules.trees.prerequisiteLevel, '스킬 선행 투자가 부족합니다.');
    for (const [id, value] of Object.entries(data.activeBuffs)) { fields(value,['active','stacks']); requireValue(id.startsWith(data.treeId + ':') && skillId(rules,id) && typeof value.active === 'boolean' && finite(value.stacks) && value.stacks >= 0, '스킬 버프 선택을 확인하세요.'); }
  } else if (type === 'consumable') {
    fields(data,['selection']); fields(data.selection,['schema','gameItemId','cacheVersion','sourceSha256','name','typeId','buffGroupId','durationSeconds','stats']); validateConsumableBuffSelection(data.selection,rules.registry);
    requireValue(data.selection.name === null || data.selection.name.length <= 240,'도핑 원본 이름이 너무 깁니다.');
  } else if (type === 'combo') {
    fields(data,['steps']); requireValue(Array.isArray(data.steps) && data.steps.length <= 9, '콤보는 기존 편집기의 9칸 이하여야 합니다.');
    for (const step of data.steps) {
      fields(step,['skillId','tag','includeSpecialAttack','inputs']); map(step.inputs,32);
      requireValue(skillId(rules,step.skillId) && ['none','consecutive','charge','swift','smite','mindsEye','tenacity'].includes(step.tag) && typeof step.includeSpecialAttack === 'boolean' && Object.values(step.inputs).every(scalar), '콤보 스킬·태그·입력값을 확인하세요.');
    }
  } else if (groups[type]) {
    const [key, subtype] = groups[type]; fields(data,[key]); map(data[key]);
    for (const [id, value] of Object.entries(data[key])) {
      requireValue(type === 'equipment_set' ? own(EQUIPMENT_SLOTS,id) : type === 'skill_set' ? treeInfo(rules,id) : /^\d+$/u.test(id) && isConsumableGroupId(Number(id)), '구성 위치가 올바르지 않습니다.');
      if (value === null) continue;
      child(value,subtype,rules);
      requireValue(String(type === 'equipment_set' ? value.data.slot : type === 'skill_set' ? value.data.treeId : value.data.selection.buffGroupId) === id, '하위 구성과 위치가 맞지 않습니다.');
    }
    if (type === 'consumable_set') resolveConsumableBuffs(Object.values(data.categories).filter(Boolean).map(value => value.data.selection),rules.registry);
  } else if (type === 'combo_set') {
    fields(data,['entries']); requireValue(Array.isArray(data.entries) && data.entries.length <= 100, '콤보 목록은 100개 이하여야 합니다.');
    const ids = new Set(); for (const entry of data.entries) { fields(entry,['id','combo']); requireValue(typeof entry.id === 'string' && /^[A-Za-z0-9_-]{1,80}$/u.test(entry.id) && !ids.has(entry.id), '콤보 목록의 식별자가 중복됐습니다.'); ids.add(entry.id); child(entry.combo,'combo',rules); }
  } else if (type === 'build') {
    fields(data,[...Object.keys(SECTION_TYPES),'context']); requireValue(Object.keys(data).length > 0, '빌드에 구성을 하나 이상 넣으세요.');
    for (const [key, subtype] of Object.entries(SECTION_TYPES)) if (own(data,key)) child(data[key],subtype,rules);
    if (own(data,'context')) validateContext(data.context,rules);
  }
  return data;
}

export function sections(record) {
  const item = snapshot(record), data = item.data;
  switch (record.type) {
    case 'build': return structuredClone(data);
    case 'equipment': return {equipment:makeSnapshot('equipment_set',{slots:{[data.slot]:item}})};
    case 'skill_tree': return {skills:makeSnapshot('skill_set',{trees:{[data.treeId]:item}})};
    case 'consumable': return {consumables:makeSnapshot('consumable_set',{categories:{[data.selection.buffGroupId]:item}})};
    case 'combo': return {combos:makeSnapshot('combo_set',{entries:[{id:'combo-1',combo:item}]})};
    default: return {[Object.keys(SECTION_TYPES).find(key => SECTION_TYPES[key] === record.type)]:item};
  }
}

export function captureObject(type, session, {slot = 'mainWeapon', treeId, consumableId, previous, comboId} = {}) {
  const build = session.build, prior = previous ? sections(previous) : {};
  const single = (kind, data, old) => makeSnapshot(kind,data,old);
  const skill = id => single('skill_tree',{treeId:id, levels:structuredClone(build.skillLevels[id] || {}), activeBuffs:Object.fromEntries(Object.entries(build.activeBuffs).filter(([key]) => key.startsWith(id + ':')))},prior.skills?.data.trees[id]);
  const equipment = id => single('equipment',{slot:id,equipment:structuredClone(build.equipment[id])},prior.equipment?.data.slots[id]);
  const consumable = value => single('consumable',{selection:structuredClone(value)},prior.consumables?.data.categories[value.buffGroupId]);
  const combos = structuredClone(prior.combos?.data.entries || []);
  if (type === 'build' || type === 'combo_set') {
    requireValue(combos.length <= 1 || combos.some(entry => entry.id === comboId), '편집할 콤보를 선택하세요. 다른 콤보는 유지됩니다.');
    const current = combos.find(entry => entry.id === comboId) || combos[0];
    if (current) current.combo = single('combo',{steps:structuredClone(build.combo)},current.combo);
    else if (build.combo.length) combos.push({id:'combo-1',combo:single('combo',{steps:structuredClone(build.combo)})});
  }
  if (type === 'equipment') return equipment(slot).data;
  if (type === 'status') return {character:structuredClone(build.character)};
  if (type === 'skill_tree') return skill(treeId).data;
  if (type === 'consumable') {
    const values = build.consumableBuffs || [];
    const value = values.find(item => item.gameItemId === Number(consumableId)) || (previous?.type === 'consumable' ? values.find(item => item.buffGroupId === previous.data.selection.buffGroupId) : null);
    requireValue(value,'현재 계산기에서 도핑을 선택하세요.'); return consumable(value).data;
  }
  if (type === 'combo') return {steps:structuredClone(build.combo)};
  const result = {
    status:single('status',{character:structuredClone(build.character)},prior.status),
    equipment:single('equipment_set',{slots:Object.fromEntries(Object.keys(EQUIPMENT_SLOTS).map(id => [id,equipment(id)]))},prior.equipment),
    skills:single('skill_set',{trees:Object.fromEntries(Object.keys(build.skillLevels).filter(id => id !== 'Scroll').map(id => [id,skill(id)]))},prior.skills),
    consumables:single('consumable_set',{categories:Object.fromEntries((build.consumableBuffs || []).map(value => [value.buffGroupId,consumable(value)]))},prior.consumables),
    combos:single('combo_set',{entries:combos},prior.combos),
    context:{externalOptions:structuredClone(build.externalOptions), ...(build.myRoomFood !== undefined ? {myRoomFood:structuredClone(build.myRoomFood)} : {}), ...(build.guildFoodBuff !== undefined ? {guildFoodBuff:build.guildFoodBuff} : {}), scenario:structuredClone(session.scenario)}
  };
  if (previous) {
    for (const [section,field] of [['equipment','slots'],['skills','trees']]) if (prior[section]) result[section].data[field] = Object.fromEntries(Object.keys(prior[section].data[field]).map(id => [id,result[section].data[field][id]]));
  }
  if (type === 'build') return previous ? Object.fromEntries(Object.keys(previous.data).map(key => [key,result[key]])) : result;
  return result[Object.keys(SECTION_TYPES).find(key => SECTION_TYPES[key] === type)].data;
}

function emptyEquipment(slot) { const weapon = ['mainWeapon','subWeapon'].includes(slot), count = slot === 'subWeapon' ? 0 : 2; return {type:({mainWeapon:'맨손',subWeapon:'없음',armor:'일반옷'})[slot] || null, attack:weapon ? 0 : null, refinement:weapon ? 0 : null, stability:weapon ? 0 : null, options:[], crystas:Array(count).fill(''), lockedCrystaSlots:Array(count).fill(false)}; }
export function comboEntries(record) { return sections(record).combos?.data.entries || []; }
export function applyObject(record, session, rules, comboId) {
  validateInventoryObject(record.type,record.data,rules);
  const result = structuredClone(session), build = result.build, parts = sections(record);
  if (parts.status) build.character = structuredClone(parts.status.data.character);
  for (const [slot, item] of Object.entries(parts.equipment?.data.slots || {})) build.equipment[slot] = item ? structuredClone(item.data.equipment) : emptyEquipment(slot);
  for (const [id, item] of Object.entries(parts.skills?.data.trees || {})) {
    build.skillLevels[id] = structuredClone(item?.data.levels || {});
    for (const key of Object.keys(build.activeBuffs)) if (key.startsWith(id + ':')) delete build.activeBuffs[key];
    Object.assign(build.activeBuffs,structuredClone(item?.data.activeBuffs || {}));
  }
  if (parts.consumables) {
    const categories = parts.consumables.data.categories;
    build.consumableBuffs = record.type === 'consumable' ? (build.consumableBuffs || []).filter(item => !own(categories,String(item.buffGroupId))) : [];
    build.consumableBuffs.push(...Object.values(categories).filter(Boolean).map(item => structuredClone(item.data.selection)));
    resolveConsumableBuffs(build.consumableBuffs,rules.registry);
  }
  if (parts.combos) {
    const entries = parts.combos.data.entries;
    const selected = entries.find(entry => entry.id === comboId) || (entries.length === 1 ? entries[0] : null);
    requireValue(entries.length === 0 || selected,'적용할 콤보를 하나 선택하세요. 보관한 다른 콤보는 유지됩니다.');
    build.combo = structuredClone(selected?.combo.data.steps || []);
  }
  if (parts.context) { for (const key of ['externalOptions','myRoomFood','guildFoodBuff']) if (own(parts.context,key)) build[key] = structuredClone(parts.context[key]); result.scenario = structuredClone(parts.context.scenario); }
  const main = build.equipment.mainWeapon.type, sub = build.equipment.subWeapon.type;
  requireValue(rules.subWeaponRules?.[main]?.includes(sub),'현재 주무기와 보조 장비가 호환되지 않습니다. 계산기에서 보조 장비를 먼저 변경하세요.');
  // Combo restore filters unknown/unlearned skills; reject instead of silently dropping steps.
  for (const step of build.combo || []) {
    const [tree,id] = step.skillId.split(':'); requireValue(build.skillLevels[tree]?.[id] > 0,'콤보에 필요한 스킬을 먼저 적용하거나 습득하세요.');
    requireValue(!rules.comboSkillIds || rules.comboSkillIds.has(step.skillId),'현재 콤보 편집기가 지원하는 공격·버프·유틸리티 스킬만 적용할 수 있습니다.');
  }
  return result;
}
