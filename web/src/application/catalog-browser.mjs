import { WEAPON_ITEM_TYPES } from './item-catalog.mjs';

export const CATALOG_KINDS = Object.freeze({all:'전체 아이템',weapons:'무기',armor:'몸장비',additional:'추가장비',special:'특수장비',crystas:'크리스타',consumables:'소모품',avatars:'아바타',other:'기타'});
export const CATALOG_LOCALES = Object.freeze({kr:'한국어',us:'English',jp:'日本語',cnt:'繁體中文',idn:'Indonesia',th:'ไทย'});
export const CATALOG_SUBCATEGORIES = Object.freeze({weapons:WEAPON_ITEM_TYPES,crystas:Object.freeze({'노말':'공용','무기':'무기','방어구':'몸장비','추가':'추가장비','특수':'특수장비'})});
export const CATALOG_BOSS_KINDS = Object.freeze({all:'전체 보스','entry-boss':'입장보스','field-boss':'필드보스','event-boss':'이벤트보스','high-raid-boss':'고난도보스'});
export function catalogState(params) {
  const section = params.get('section') || 'items', kind = params.get('kind') || 'all', locale = params.get('locale') || 'kr', q = (params.get('q') || '').trim();
  const subcategory = params.get('subcategory') || 'all';
  const bossKind = params.get('bossKind') || 'all';
  const page = Number(params.get('page') || 1), selected = params.has('selected') ? Number(params.get('selected')) : null;
  const variant = params.get('variant') || '', difficulty = Number(params.get('difficulty') || 0), level = params.has('level') ? Number(params.get('level')) : null;
  if (!['items','bosses'].includes(section) || !Object.hasOwn(CATALOG_KINDS,kind) || !Object.hasOwn(CATALOG_LOCALES,locale) || q.length > 80
    || subcategory !== 'all' && (section !== 'items' || !Object.hasOwn(CATALOG_SUBCATEGORIES[kind] || {},subcategory))
    || !Object.hasOwn(CATALOG_BOSS_KINDS,bossKind) || section !== 'bosses' && bossKind !== 'all'
    || !Number.isSafeInteger(page) || page < 1 || page > 100000
    || selected !== null && (!Number.isSafeInteger(selected) || selected < (section === 'items' ? 1 : 0))
    || variant && !/^\d+:\d+$/u.test(variant) || ![-1,0,1,2,3].includes(difficulty) || level !== null && (!Number.isSafeInteger(level) || level < 1 || level > 32767)) throw new Error('도감 분류·ID·페이지·선택 조건을 확인하세요.');
  return {section,kind,subcategory,bossKind,locale,q,page,selected,variant,difficulty,level};
}
export function catalogPage(entries,{q = '',page = 1},pageSize = 6) {
  const search = q.toLocaleLowerCase(), filtered = entries.filter(item => !search || `${item.name ?? ''} ${item.id}`.toLocaleLowerCase().includes(search));
  const total = filtered.length, current = Math.min(page,Math.max(1,Math.ceil(total/pageSize)));
  return {items:filtered.slice((current - 1) * pageSize,current * pageSize),page:current,pageSize,total};
}
export function itemCatalogContent(item,details) {
  const raw = item.baseRaw, type = WEAPON_ITEM_TYPES[item.typeId] || ({20:'몸장비',21:'추가장비',22:'특수장비'})[item.typeId];
  let summary = '';
  if (type) {
    summary = `[${type}]`;
    if (item.typeId !== 23 && Number.isFinite(raw?.function)) {
      const defense = [17,20,21,22].includes(item.typeId);
      summary += ` Base ${defense ? 'DEF' : 'ATK'} : ${raw.function}`;
      if (!defense && raw.stability > 0) summary += ` (${raw.stability}%)`;
    }
  }
  return {summary,description:(details?.description || '').replaceAll('@','\n').trim(),
    duration:item.buff ? `효과 시간 : ${item.buff.durationSeconds}초` : '',
    options:(details?.displayOptions || []).filter(option => option.text?.trim())};
}
