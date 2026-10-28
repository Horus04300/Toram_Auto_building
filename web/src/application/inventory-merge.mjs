import { sections, encodeSections, SECTION_TYPES, requireValue, fields } from './inventory-objects.mjs';
import { EQUIPMENT_SLOTS } from './equipment-object.mjs';

const own = (value, key) => Object.hasOwn(value,key);
function configuration(value, parent = '') {
  if (Array.isArray(value)) return value.map(item => configuration(item));
  if (!value || typeof value !== 'object') return value;
  return Object.fromEntries(Object.keys(value).sort().filter(key => !(value.schema === 'toram.equipment-item.v1' && ['name','cacheVersion','sourceSha256'].includes(key))
    && !(parent === 'levels' && value[key] === 0)
    && !(parent === 'activeBuffs' && value[key]?.active === false && value[key]?.stacks === 0)).map(key => [key,configuration(value[key],key)]));
}
const equal = (left, right) => JSON.stringify(configuration(left)) === JSON.stringify(configuration(right));
const GROUPS = { equipment:['slots','장비'], skills:['trees','스킬'], consumables:['categories','도핑'] };

export function mergeInventoryObjects(left, right, choices = []) {
  requireValue(Array.isArray(choices) && choices.length <= 200,'병합 선택 목록을 확인하세요.');
  const selections = new Map();
  for (const choice of choices) { fields(choice,['unit','take']); requireValue(typeof choice.unit === 'string' && ['left','right'].includes(choice.take) && !selections.has(choice.unit),'중복되거나 잘못된 병합 선택입니다.'); selections.set(choice.unit,choice.take); }
  for (const key of selections.keys()) requireValue(!key.includes('.') || !selections.has(key.split('.')[0]),'전체 선택과 세부 선택을 동시에 지정할 수 없습니다.');
  const a=sections(left), b=sections(right), values={}, origins={}, conflicts=[], groups=[], used=new Set();
  function origin(source,path) {
    for(const key of Object.keys(origins)) if(key===path||key.startsWith(path+'.')) delete origins[key];
    for(const [key,value] of Object.entries(source.origins)) if(key===path||key.startsWith(path+'.')) origins[key]=structuredClone(value);
  }
  const encoded=new Map();
  function external(source,unit) {
    if(!encoded.has(source)) encoded.set(source,encodeSections(source));
    const [section,id]=unit.split('.'), result=encoded.get(source);
    return id ? result[section].data[GROUPS[section][0]][id] : result[section];
  }
  let complete = true;
  function pick(unit, label, x, y, group) {
    if (x === undefined) {origin(b,unit); return structuredClone(y);}
    if (y === undefined || equal(x,y)) {origin(a,unit); return structuredClone(x);}
    conflicts.push({unit,label,left:external(a,unit),right:external(b,unit),group:group || null});
    const path = selections.has(unit) ? unit : group && selections.has(group) ? group : null;
    if (path) { used.add(path); const source=selections.get(path)==='left' ? a : b; origin(source,unit); return structuredClone(source===a ? x : y); }
    complete = false; return undefined;
  }
  for (const key of ['status','equipment','skills','consumables','combos','context']) {
    if (!own(a.values,key) && !own(b.values,key)) continue;
    if (key === 'combos') {
      values.combos=[];
      for(const source of [a,b]) for(const entry of source.values.combos||[]) {
        const id='combo-'+(values.combos.length+1); values.combos.push({id,steps:structuredClone(entry.steps)});
        origins['combos.'+id]=structuredClone(source.origins['combos.'+entry.id]);
      }
      continue;
    }
    if (!GROUPS[key] || !own(a.values,key) || !own(b.values,key)) { const value = pick(key,key === 'status' ? '스테이터스 전체' : key === 'context' ? '계산 조건·수동 버프·요리' : key,a.values[key],b.values[key]); if (value !== undefined) values[key] = value; continue; }
    const [,label] = GROUPS[key], units = {}, before = conflicts.length;
    const x=a.values[key], y=b.values[key];
    for (const id of new Set([...Object.keys(x),...Object.keys(y)])) {
      const value = pick(key + '.' + id,key === 'equipment' ? EQUIPMENT_SLOTS[id] : key === 'consumables' ? '도핑 계열 ' + id : id,x[id],y[id],key);
      if (value !== undefined) units[id] = value;
    }
    if (conflicts.length > before) groups.push({unit:key,label:label + ' 전체'});
    if (selections.has(key) && conflicts.length > before) {
      used.add(key); const source=selections.get(key)==='left' ? a : b; origin(source,key); values[key]=structuredClone(source.values[key]);
    } else { values[key]=units; if(a.origins[key]) origins[key]=structuredClone(a.origins[key]); }
  }
  requireValue([...selections.keys()].every(key => used.has(key)),'충돌하지 않거나 허용되지 않는 단위가 선택됐습니다.');
  const result=encodeSections({values,origins});
  const keys = Object.keys({...a.values,...b.values});
  let type = 'build', data = result;
  if (left.type !== 'build' && right.type !== 'build' && keys.length === 1 && keys[0] !== 'context') {
    const section = keys[0]; type = SECTION_TYPES[section]; data = result[section]?.data;
    if (left.type === right.type && ['equipment','skill_tree','consumable'].includes(left.type)) {
      const id = section === 'equipment' ? left.data.slot : section === 'skills' ? left.data.treeId : String(left.data.selection.buffGroupId);
      const rightId = section === 'equipment' ? right.data.slot : section === 'skills' ? right.data.treeId : String(right.data.selection.buffGroupId);
      if (id === rightId) { type = left.type; data = result[section]?.data[GROUPS[section][0]][id]?.data; }
    }
  }
  return {type,conflicts,groups,complete,result:complete ? {type,schemaVersion:1,data} : null};
}
