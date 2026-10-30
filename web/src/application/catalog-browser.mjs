import { WEAPON_ITEM_TYPES } from './item-catalog.mjs';
import { bossKindLabel, bossActorLabel, resolveBossTarget } from './boss-target.mjs';

export const CATALOG_KINDS = Object.freeze({all:'전체 아이템',weapons:'무기',armor:'몸장비',additional:'추가장비',special:'특수장비',crystas:'크리스타',consumables:'소모품',avatars:'아바타',other:'기타'});
export const CATALOG_LOCALES = Object.freeze({kr:'한국어',us:'English',jp:'日本語',cnt:'繁體中文',idn:'Indonesia',th:'ไทย'});
export const CATALOG_SUBCATEGORIES = Object.freeze({weapons:WEAPON_ITEM_TYPES,crystas:Object.freeze({'노말':'공용','무기':'무기','방어구':'몸장비','추가':'추가장비','특수':'특수장비'})});
export const CATALOG_BOSS_KINDS = Object.freeze({all:'전체 보스','entry-boss':'입장보스','field-boss':'필드보스','event-boss':'이벤트보스','high-raid-boss':'고난도보스'});
export const CATALOG_REGISTLET_KINDS = Object.freeze({all:'전체',stats:'기본 능력',status:'상태이상 대응',support:'전투·편의',skills:'스킬 변경',slots:'슬롯 확장'});
export function catalogState(params) {
  const section = params.get('section') || 'items', kind = params.get('kind') || 'all', locale = params.get('locale') || 'kr', q = (params.get('q') || '').trim();
  const subcategory = params.get('subcategory') || 'all';
  const bossKind = params.get('bossKind') || 'all';
  const registletKind = params.get('registletKind') || 'all';
  const page = Number(params.get('page') || 1), selected = params.has('selected') ? Number(params.get('selected')) : null;
  const variant = params.get('variant') || '', difficulty = Number(params.get('difficulty') || 0), level = params.has('level') ? Number(params.get('level')) : null;
  if (!['items','bosses','registlets'].includes(section) || !Object.hasOwn(CATALOG_KINDS,kind) || !Object.hasOwn(CATALOG_LOCALES,locale) || q.length > 80
    || subcategory !== 'all' && (section !== 'items' || !Object.hasOwn(CATALOG_SUBCATEGORIES[kind] || {},subcategory))
    || !Object.hasOwn(CATALOG_BOSS_KINDS,bossKind) || section !== 'bosses' && bossKind !== 'all'
    || !Object.hasOwn(CATALOG_REGISTLET_KINDS,registletKind) || section !== 'registlets' && registletKind !== 'all'
    || !Number.isSafeInteger(page) || page < 1 || page > 100000
    || selected !== null && (!Number.isSafeInteger(selected) || selected < (section === 'bosses' ? 0 : 1))
    || variant && !/^\d+:\d+$/u.test(variant) || ![-1,0,1,2,3].includes(difficulty) || level !== null && (!Number.isSafeInteger(level) || level < 1 || level > 32767)) throw new Error('도감 분류·ID·페이지·선택 조건을 확인하세요.');
  return {section,kind,subcategory,bossKind,registletKind,locale,q,page,selected,variant,difficulty,level};
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

export function bossCatalogPhaseLabel(row,variants) {
  const source = variants.find(other => other.key === row.key) ?? row;
  const linked = source.modes?.some(mode => variants.some(other => other.fieldId === row.fieldId && other.masterId === mode.targetMonsterId && other.gameMonsterId === row.gameMonsterId))
    || variants.some(other => other.fieldId === row.fieldId && other.gameMonsterId === row.gameMonsterId && other.modes?.some(mode => mode.targetMonsterId === row.masterId));
  return [bossActorLabel(row.entry.actor),`${linked ? '페이즈' : '개체'} #${row.masterId}`].filter(Boolean).join(' · ');
}

export function bossCatalogContent(selection,variants) {
  const row = selection.variant, base = row.baseStats, resolved = resolveBossTarget(selection), raw = row.entry.model === 'unresolved';
  const value = (number,unit = '') => number === null || number === undefined ? '미확정' : typeof number === 'number' ? `${number.toLocaleString('ko-KR')}${unit}` : number;
  const stat = (key,original,unit = '') => value(raw ? original : resolved.target[key],unit);
  const difficulty = row.entry.model === 'difficulty-select' ? ['Easy','Normal','Hard','Nightmare','Ultimate'][selection.difficulty + 1]
    : row.entry.model === 'level-select' ? `${row.classification === 'guild-raid-boss' ? '현재 보스' : '입장'} Lv${selection.level}`
    : raw ? '난이도 미확인' : '단일 난이도';
  const next = [...new Set((variants.find(other => other.key === row.key)?.modes || []).map(mode => mode.targetMonsterId))]
    .filter(id => variants.some(other => other.fieldId === row.fieldId && other.masterId === id && other.gameMonsterId === row.gameMonsterId));
  const hp = resolved.details.find(([label]) => label === '본체 HP')[1];
  return {
    summary:[bossKindLabel(row.classification),row.fieldName ?? `지역 #${row.fieldId}`,difficulty].join(' · '),
    groups:[
      ['기본 능력',[
        ['난이도',difficulty],['레벨',stat('bossLevel',base.level)],
        // ElementType: native-option-calculation/metadata-bindings.json; None(0) differs from Normal(7).
        ['속성',({0:'미지정',1:'불',2:'물',3:'바람',4:'땅',5:'빛',6:'어둠',7:'무'})[base.elementRaw] ?? '미확인'],
        ['HP',typeof hp === 'number' ? value(hp) : '미확정'],
        ['회피',value(resolved.details.find(([label]) => label === '회피')[1])],
        ['어보이드율',value(base.avoid,'%')],['가드율',value(base.guard,'%')]
      ]],
      ['방어 · 저항',[
        ['DEF',stat('bossDef',base.def)],['MDEF',stat('bossMdef',base.mdef)],
        ['물리 내성',stat('bossPhysResist',base.cutAttack,'%')],['마법 내성',stat('bossMagResist',base.cutMagicAttack,'%')],
        ['크리티컬 저항',stat('bossCritResist',row.properties.find(property => property.typeRaw === 6)?.values[0] ?? 0)]
      ]],
      ['관성 변동률',[
        ['통상',value(base.expDefNormal,'%p')],['물리',value(base.expDefSkill,'%p')],['마법',value(base.expDefMagic,'%p')]
      ]],
      ['지역 · 페이즈',[
        ['선택 개체',bossCatalogPhaseLabel(row,variants)],['세부 번호',row.key],['등록 부위',`${row.parts.length}개`],
        ...(next.length ? [['다음 페이즈',next.map(id => `#${id}`).join(' / ')]] : [])
      ]]
    ]
  };
}
