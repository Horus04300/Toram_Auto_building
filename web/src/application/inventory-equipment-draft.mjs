import { EQUIPMENT_SLOT_TYPES, validateEquipmentObject } from './equipment-object.mjs';

export function createEquipmentDraft(input,registry,crystas = {}) {
  const number = value => {
    if (value === '' || !Number.isFinite(Number(value))) throw new Error('기본 수치와 옵션에 숫자를 입력하세요.');
    return Number(value);
  };
  if (!Object.hasOwn(EQUIPMENT_SLOT_TYPES,input.slot)) throw new Error('장비 부위를 선택하세요.');
  const weapon = ['mainWeapon','subWeapon'].includes(input.slot), sub = input.slot === 'subWeapon';
  const resolveCrysta = value => {
    const text = String(value || '').trim(); if (!text) return '';
    const item = Object.values(crystas).find(item => String(item.gameItemId) === text || item.names?.kr === text || item.name === text);
    if (!item) throw new Error(`크리스타 “${text}”를 찾을 수 없습니다. 도감의 이름 또는 ID를 선택하세요.`);
    return String(item.gameItemId);
  };
  const data = {slot:input.slot,equipment:{type:input.type,attack:weapon ? number(input.attack) : null,refinement:weapon ? number(input.refinement) : null,stability:weapon ? number(input.stability) : null,
    options:input.options.map(option => ({key:option.key,value:number(option.value)})),crystas:sub ? [] : input.crystas.map(resolveCrysta),lockedCrystaSlots:sub ? [] : [...input.lockedCrystaSlots]}};
  return validateEquipmentObject(data,registry);
}
