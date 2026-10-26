import { EQUIPMENT_SLOTS } from './equipment-object.mjs';
import { INVENTORY_TYPES } from './inventory-objects.mjs';

export function describeInventoryObject(record) {
    const data = record.data;
    if (record.type === 'equipment') { const p = data.equipment; return [`${EQUIPMENT_SLOTS[data.slot]} · ${p.type || INVENTORY_TYPES[record.type]} · ATK ${p.attack ?? '—'} · 제련 ${p.refinement ?? '—'} · 옵션 ${p.options.slice(0,4).map(item => item.key + ' ' + item.value).join(', ') || '없음'}${p.options.length > 4 ? ' 외 ' + (p.options.length - 4) + '개' : ''}`]; }
    if (record.type === 'status') return [`Lv.${data.character.level}`,Object.entries(data.character.attributes).map(([key,value]) => key + ' ' + value).join(' · ')];
    if (record.type === 'skill_tree') return [data.treeId,`투자 ${Object.values(data.levels).reduce((sum,value) => sum + value,0)}포인트 · 버프 ${Object.values(data.activeBuffs).filter(value => value.active).length}개`];
    if (record.type === 'consumable') return [`${data.selection.name || '#' + data.selection.gameItemId} · 계열 ${data.selection.buffGroupId}`,Object.entries(data.selection.stats).map(([key,value]) => key + ' ' + value).join(' · ')];
    if (record.type === 'combo') return [record.name || '콤보',data.steps.map(step => `${step.skillId} [${step.tag}]`).join(' → ') || '빈 콤보'];
    if (record.type === 'combo_set') return data.entries.map((entry,index) => `${index + 1}. ${entry.combo.name} · ${entry.combo.data.steps.length}칸`);
    if (record.type === 'build') return Object.entries(data).map(([key,value]) => key === 'context' ? '계산 조건 · 수동 버프 · 요리 포함' : `${INVENTORY_TYPES[value.type]} · ${key === 'status' ? 'Lv.' + value.data.character.level : describeInventoryObject(value).length + '개 단위'}`);
    const [map,label] = record.type === 'equipment_set' ? [data.slots,id => EQUIPMENT_SLOTS[id]] : record.type === 'skill_set' ? [data.trees,id => id] : [data.categories,id => '계열 ' + id];
    return Object.entries(map).map(([id,item]) => `${label(id)} · ${item ? describeInventoryObject(item).join(' / ') : '비우기'}`);
  }
export function nextInventoryName(records, kind) {
  const names = new Set(records.map(record => record.name));
  const base = `새 ${kind}`;
  let index = 0;
  while (names.has(index ? `${base} (${index})` : base)) index++;
  return index ? `${base} (${index})` : base;
}

