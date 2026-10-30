import { EQUIPMENT_SLOTS } from './equipment-object.mjs';
import { INVENTORY_TYPES, SECTION_TYPES, sections } from './inventory-objects.mjs';
import {registletDescription} from './registlet-catalog.mjs';

export function describeInventoryObject(record) {
  if (record.type === 'registlet') {const item = record.data.selection; return [item.name,`Lv${item.level} / ${item.levelCap}`,registletDescription(item)];}
  const {values,origins}=sections(record);
  function unit(section,id,value,name) {
    if(section==='equipment') return [`${EQUIPMENT_SLOTS[id]} · ${value.type||INVENTORY_TYPES.equipment} · ATK ${value.attack??'—'} · 제련 ${value.refinement??'—'} · 옵션 ${value.options.slice(0,4).map(item=>item.key+' '+item.value).join(', ')||'없음'}${value.options.length>4 ? ' 외 '+(value.options.length-4)+'개' : ''}`];
    if(section==='status') return [`Lv.${value.level}`,Object.entries(value.attributes).map(([key,amount])=>key+' '+amount).join(' · ')];
    if(section==='skills') return [id,`투자 ${Object.values(value.levels).reduce((sum,amount)=>sum+amount,0)}포인트 · 버프 ${Object.values(value.activeBuffs).filter(value=>value.active).length}개`];
    if(section==='consumables') return [`${value.name||'#'+value.gameItemId} · 계열 ${value.buffGroupId}`,Object.entries(value.stats).map(([key,amount])=>key+' '+amount).join(' · ')];
    return [name||'콤보',value.map(step=>`${step.skillId} [${step.tag}]`).join(' → ')||'빈 콤보'];
  }
  if(record.type==='build') return Object.entries(values).map(([key,value])=>key==='context' ? '계산 조건 · 수동 버프 · 요리 포함' : `${INVENTORY_TYPES[SECTION_TYPES[key]]} · ${key==='status' ? 'Lv.'+value.level : Object.keys(value).length+'개 단위'}`);
  const section=Object.keys(values)[0], value=values[section];
  if(record.type==='status') return unit(section,null,value);
  if(record.type==='combo') return unit(section,null,value[0].steps,record.name);
  if(record.type==='combo_set') return value.map((entry,index)=>`${index+1}. ${origins['combos.'+entry.id].name} · ${entry.steps.length}칸`);
  if(['equipment','skill_tree','consumable'].includes(record.type)) {const [id,item]=Object.entries(value)[0];return unit(section,id,item);}
  return Object.entries(value).map(([id,item])=>`${section==='equipment' ? EQUIPMENT_SLOTS[id] : section==='consumables' ? '계열 '+id : id} · ${item ? unit(section,id,item).join(' / ') : '비우기'}`);
}
export function nextInventoryName(records, kind) {
  const names = new Set(records.map(record => record.name));
  const base = `새 ${kind}`;
  let index = 0;
  while (names.has(index ? `${base} (${index})` : base)) index++;
  return index ? `${base} (${index})` : base;
}

