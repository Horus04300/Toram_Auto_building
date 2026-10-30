import { EQUIPMENT_SLOTS, validateEquipmentObject } from './equipment-object.mjs';
import { validateConsumableBuffSelection, resolveConsumableBuffs, isConsumableGroupId } from './item-catalog.mjs';
import { validateCharacter, validateScenario, validateBuildExtras } from './build-values.mjs';
import { validateRegistletSelection } from './registlet-catalog.mjs';

export const INVENTORY_TYPES = Object.freeze({ equipment:'장비', equipment_set:'장비 세팅', status:'스테이터스', skill_tree:'스킬트리', skill_set:'스킬셋', consumable:'도핑', consumable_set:'도핑 세팅', combo:'콤보', combo_set:'콤보 목록', build:'빌드', registlet:'레지스트렛' });
export const SECTION_TYPES = Object.freeze({ status:'status', equipment:'equipment_set', skills:'skill_set', consumables:'consumable_set', combos:'combo_set' });
const groups = { equipment_set:['slots','equipment'], skill_set:['trees','skill_tree'], consumable_set:['categories','consumable'] };
const own = (value, key) => Object.hasOwn(value, key);
const object = value => value && typeof value === 'object' && !Array.isArray(value);
export const requireValue = (ok, message) => { if (!ok) throw new Error(message); };
export function fields(value, allowed) { requireValue(object(value) && Object.keys(value).every(key => allowed.includes(key)), '지원하지 않는 구성 필드가 있습니다.'); }
const finite = value => typeof value === 'number' && Number.isFinite(value);
const scalar = value => value === null || typeof value === 'boolean' || finite(value) || typeof value === 'string' && value.length <= 160;
function map(value, max = 100) { requireValue(object(value) && Object.keys(value).length <= max && Object.keys(value).every(key => /^[A-Za-z0-9_:-]{1,80}$/u.test(key)), '구성 키 또는 목록 크기가 올바르지 않습니다.'); }
export function validateProvenance(value) {
  requireValue(Array.isArray(value) && value.length <= 64, '출처 목록이 올바르지 않습니다.');
  for (const source of value) {
    if (source?.kind === 'inventory') { fields(source,['kind','objectId','revision']); requireValue(/^[a-f0-9-]{36}$/u.test(source.objectId) && Number.isSafeInteger(source.revision) && source.revision > 0, '개인 객체 출처가 올바르지 않습니다.'); }
    else if (source?.kind === 'release') { fields(source,['kind','postId','releaseNumber']); requireValue(/^[a-f0-9-]{36}$/u.test(source.postId) && Number.isSafeInteger(source.releaseNumber) && source.releaseNumber > 0, '공개 릴리스 출처가 올바르지 않습니다.'); }
    else if (source?.kind === 'registlet-catalog') {fields(source,['kind','registletId','cacheVersion','sourceSha256']); requireValue(Number.isSafeInteger(source.registletId) && source.registletId > 0 && /^[a-f0-9]{8}$/u.test(source.cacheVersion) && /^[a-f0-9]{64}$/u.test(source.sourceSha256),'레지스트렛 출처가 올바르지 않습니다.');}
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
  fields(data,['externalOptions','myRoomFood','guildFoodBuff','scenario']); validateBuildExtras(data,rules);
  validateScenario(data.scenario);
}

export function validateInventoryObject(type, data, rules) {
  requireValue(own(INVENTORY_TYPES,type), '지원하지 않는 구성 종류입니다.');
  if (type === 'equipment') return validateEquipmentObject(data, rules.registry);
  if (type === 'registlet') {fields(data,['selection']); validateRegistletSelection(data.selection);}
  else if (type === 'status') {
    fields(data,['character']); validateCharacter(data.character);
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

// Values are flat during composition; v1 envelopes and provenance stay at the boundary.
export function sections(record) {
  requireValue(record.type !== 'registlet','레지스트렛은 개별 보관만 지원합니다.');
  const values={}, origins={};
  function origin(path,item) { const {data,...metadata}=snapshot(item); origins[path]=metadata; return data; }
  function leaf(section,id,item) {
    if(item===null) return null;
    const data=origin(section+'.'+id,item);
    return section==='equipment' ? data.equipment : section==='skills' ? {levels:data.levels,activeBuffs:data.activeBuffs} : data.selection;
  }
  function read(item) {
    if(item.type==='build') {
      for(const [key,value] of Object.entries(item.data)) if(key==='context') values.context=structuredClone(value); else read(value);
    } else if(item.type==='status') values.status=origin('status',item).character;
    else if(item.type==='combo' || item.type==='combo_set') {
      const entries=item.type==='combo' ? [{id:'combo-1',combo:item}] : origin('combos',item).entries;
      values.combos=entries.map(entry=>({id:entry.id,steps:origin('combos.'+entry.id,entry.combo).steps}));
    } else {
      const section=item.type.startsWith('equipment') ? 'equipment' : item.type.startsWith('skill') ? 'skills' : 'consumables';
      if(groups[item.type]) {
        const data=origin(section,item), field=groups[item.type][0];
        values[section]=Object.fromEntries(Object.entries(data[field]).map(([id,value])=>[id,leaf(section,id,value)]));
      } else {
        const id=section==='equipment' ? item.data.slot : section==='skills' ? item.data.treeId : item.data.selection.buffGroupId;
        values[section]={[id]:leaf(section,id,item)};
      }
    }
  }
  read(record); return {values,origins};
}

export function encodeSections({values,origins}) {
  const result={};
  for(const [section,value] of Object.entries(values)) {
    if(section==='context') {result.context=structuredClone(value);continue;}
    let data;
    if(section==='status') data={character:structuredClone(value)};
    else if(section==='combos') data={entries:value.map(entry=>({id:entry.id,combo:makeSnapshot('combo',{steps:structuredClone(entry.steps)},origins['combos.'+entry.id])}))};
    else {
      const [field,type]=groups[SECTION_TYPES[section]];
      data={[field]:Object.fromEntries(Object.entries(value).map(([id,item])=>[id,item===null ? null : makeSnapshot(type,
        section==='equipment' ? {slot:id,equipment:structuredClone(item)} : section==='skills' ? {treeId:id,...structuredClone(item)} : {selection:structuredClone(item)},origins[section+'.'+id])]))};
    }
    result[section]=makeSnapshot(SECTION_TYPES[section],data,origins[section]);
  }
  return result;
}

export function captureObject(type, session, {slot='mainWeapon',treeId,consumableId,previous,comboId}={}) {
  requireValue(type !== 'registlet','레지스트렛은 도감에서 선택해 보관하세요.');
  const build=session.build, prior=previous ? sections(previous) : {values:{},origins:{}};
  const section=({equipment:'equipment',skill_tree:'skills',consumable:'consumables',combo:'combos'})[type]||Object.keys(SECTION_TYPES).find(key=>SECTION_TYPES[key]===type);
  const keys=type==='build' ? previous ? Object.keys(previous.data) : [...Object.keys(SECTION_TYPES),'context'] : [section];
  function ids(key,current,single) {return single ? [single] : Object.keys(prior.values[key]||current);}
  let selectedConsumable;
  const readers={
    status:()=>structuredClone(build.character),
    equipment:()=>Object.fromEntries(ids('equipment',build.equipment,type==='equipment'&&slot).map(id=>[id,structuredClone(build.equipment[id])])),
    skills:()=>Object.fromEntries(ids('skills',build.skillLevels,type==='skill_tree'&&treeId).filter(id=>id!=='Scroll').map(id=>[id,{levels:structuredClone(build.skillLevels[id]||{}),activeBuffs:structuredClone(Object.fromEntries(Object.entries(build.activeBuffs).filter(([key])=>key.startsWith(id+':'))))}])),
    consumables:()=>{
      let items=build.consumableBuffs||[];
      if(type==='consumable') {
        selectedConsumable=items.find(item=>item.gameItemId===Number(consumableId)) || (previous?.type==='consumable' ? items.find(item=>item.buffGroupId===previous.data.selection.buffGroupId) : null);
        requireValue(selectedConsumable,'현재 계산기에서 도핑을 선택하세요.'); items=[selectedConsumable];
      }
      return Object.fromEntries(items.map(value=>[value.buffGroupId,structuredClone(value)]));
    },
    combos:()=>{
      if(type==='combo') return [{id:'combo-1',steps:structuredClone(build.combo)}];
      const entries=structuredClone(prior.values.combos||[]);
      requireValue(entries.length<=1||entries.some(entry=>entry.id===comboId),'편집할 콤보를 선택하세요. 다른 콤보는 유지됩니다.');
      const current=entries.find(entry=>entry.id===comboId)||entries[0];
      if(current) current.steps=structuredClone(build.combo);
      else if(build.combo.length) entries.push({id:'combo-1',steps:structuredClone(build.combo)});
      return entries;
    },
    context:()=>({externalOptions:structuredClone(build.externalOptions),...(build.myRoomFood!==undefined ? {myRoomFood:structuredClone(build.myRoomFood)} : {}),...(build.guildFoodBuff!==undefined ? {guildFoodBuff:build.guildFoodBuff} : {}),scenario:structuredClone(session.scenario)})
  };
  const values=Object.fromEntries(keys.map(key=>[key,readers[key]() ]));
  const result=encodeSections({values,origins:prior.origins});
  if(type==='equipment') return result.equipment.data.slots[slot].data;
  if(type==='skill_tree') return result.skills.data.trees[treeId].data;
  if(type==='consumable') return result.consumables.data.categories[selectedConsumable.buffGroupId].data;
  if(type==='combo') return {steps:structuredClone(build.combo)};
  if(type==='build') return previous ? Object.fromEntries(Object.keys(previous.data).map(key=>[key,result[key]])) : result;
  return result[Object.keys(SECTION_TYPES).find(key=>SECTION_TYPES[key]===type)].data;
}

function emptyEquipment(slot) { const weapon = ['mainWeapon','subWeapon'].includes(slot), count = slot === 'subWeapon' ? 0 : 2; return {type:({mainWeapon:'맨손',subWeapon:'없음',armor:'일반옷'})[slot] || null, attack:weapon ? 0 : null, refinement:weapon ? 0 : null, stability:weapon ? 0 : null, options:[], crystas:Array(count).fill(''), lockedCrystaSlots:Array(count).fill(false)}; }
export function comboEntries(record) { return record.type === 'registlet' ? [] : encodeSections(sections(record)).combos?.data.entries || []; }
export function applyObject(record, session, rules, comboId) {
  validateInventoryObject(record.type,record.data,rules);
  const result = structuredClone(session), build = result.build, parts = sections(record).values;
  if (parts.status) build.character = structuredClone(parts.status);
  for (const [slot, item] of Object.entries(parts.equipment || {})) build.equipment[slot] = item ? structuredClone(item) : emptyEquipment(slot);
  for (const [id, item] of Object.entries(parts.skills || {})) {
    build.skillLevels[id] = structuredClone(item?.levels || {});
    for (const key of Object.keys(build.activeBuffs)) if (key.startsWith(id + ':')) delete build.activeBuffs[key];
    Object.assign(build.activeBuffs,structuredClone(item?.activeBuffs || {}));
  }
  if (parts.consumables) {
    const categories = parts.consumables;
    build.consumableBuffs = record.type === 'consumable' ? (build.consumableBuffs || []).filter(item => !own(categories,String(item.buffGroupId))) : [];
    build.consumableBuffs.push(...Object.values(categories).filter(Boolean).map(item => structuredClone(item)));
    resolveConsumableBuffs(build.consumableBuffs,rules.registry);
  }
  if (parts.combos) {
    const entries = parts.combos;
    const selected = entries.find(entry => entry.id === comboId) || (entries.length === 1 ? entries[0] : null);
    requireValue(entries.length === 0 || selected,'적용할 콤보를 하나 선택하세요. 보관한 다른 콤보는 유지됩니다.');
    build.combo = structuredClone(selected?.steps || []);
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
