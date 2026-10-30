import {createCatalogReader} from './catalog-assets.mjs';
import {REGISTLET_LEVEL_CAPS} from '../data/registlet-levels.mjs';

export const REGISTLET_SCHEMA = 'toram.registlet.v1';
const requireValue = (ok,message) => {if (!ok) throw new Error(message);};
const plain = value => value && typeof value === 'object' && !Array.isArray(value);
const keys = (value,allowed) => requireValue(plain(value) && Object.keys(value).every(key => allowed.includes(key)),'레지스트렛 필드를 확인하세요.');
export const cleanRegistletText = value => String(value || '').replace(/\[[a-f0-9]{6}\]/giu,'').replaceAll('\\n','\n');

export function validateRegistletSelection(value) {
  keys(value,['schema','registletId','cacheVersion','sourceSha256','name','level','levelCap','baseValue','descriptionTemplate']);
  requireValue(value.schema === REGISTLET_SCHEMA && Object.hasOwn(REGISTLET_LEVEL_CAPS,value.registletId) && Number.isSafeInteger(value.registletId),'등록된 레지스트렛을 선택하세요.');
  requireValue(typeof value.cacheVersion === 'string' && typeof value.sourceSha256 === 'string' && /^[a-f0-9]{8}$/u.test(value.cacheVersion) && /^[a-f0-9]{64}$/u.test(value.sourceSha256),'레지스트렛 원본 버전을 확인하세요.');
  requireValue(typeof value.name === 'string' && value.name.trim() && value.name.length <= 240,'레지스트렛 이름을 확인하세요.');
  requireValue(value.levelCap === REGISTLET_LEVEL_CAPS[value.registletId] && Number.isSafeInteger(value.level) && value.level >= 1 && value.level <= value.levelCap,`레지스트렛 레벨은 1~${REGISTLET_LEVEL_CAPS[value.registletId]}로 입력하세요.`);
  requireValue(Number.isSafeInteger(value.baseValue) && value.baseValue >= -1 && value.baseValue <= 2147483647 && typeof value.descriptionTemplate === 'string' && value.descriptionTemplate.length <= 4000,'레지스트렛 효과 원문을 확인하세요.');
  return value;
}
export function createRegistletSelection(item,level = 1,locale = 'kr') {
  const selection = {schema:REGISTLET_SCHEMA,registletId:item.id,cacheVersion:item.cacheVersion,sourceSha256:item.sourceSha256,
    name:item.names[locale] || item.names.kr,level,levelCap:item.levelCap,baseValue:item.baseValue,descriptionTemplate:item.descriptionTemplates[locale] || item.descriptionTemplates.kr};
  return validateRegistletSelection(selection);
}

// Description substitution follows the native UI; no combat calculation is performed here.
export function registletEffect(selection,skillLevel = null) {
  const {registletId:id,level:L,baseValue:B} = validateRegistletSelection(selection);
  const template = cleanRegistletText(selection.descriptionTemplate);
  if (id === 1053) {
    const rows = [{label:'스택 상한',formula:'L',substitution:String(L),result:`${L}스택`},{label:'기절 부여 확률',formula:'0',substitution:'0',result:'0%'}];
    if (skillLevel !== null) {
      requireValue(Number.isSafeInteger(skillLevel) && skillLevel >= 1 && skillLevel <= 10,'스컬 셰이커 스킬 레벨은 1~10으로 입력하세요.');
      const increment = Math.trunc(Math.fround(skillLevel * Math.fround(7.5)));
      rows.push({label:'할버드 계수 (최대 스택)',formula:'(750 + ⌊7.5 × S⌋ × L) ÷ 100',substitution:`(750 + ${increment} × ${L}) ÷ 100`,result:formatRegistletNumber((750 + increment * L) / 100)},
        {label:'지팡이 계수 (최대 스택)',formula:'(1000 + (⌊7.5 × S⌋ + 25) × L) ÷ 100',substitution:`(1000 + (${increment} + 25) × ${L}) ÷ 100`,result:formatRegistletNumber((1000 + (increment + 25) * L) / 100)});
    }
    return {description:template,rows,notes:'사용 스택 = min(현재 스택, 젬 Lv). 위력 계수는 스택에 따라 달라지며, 표는 최대 스택일 때의 값입니다. 기절 삭제는 레벨과 무관합니다.'};
  }
  if (B === -1) return {description:template,rows:[]};
  if (id === 207 && skillLevel === null) return {description:template.replaceAll('{0}','⌊(파워 웨이브 Lv + 젬 Lv) ÷ 2⌋'),rows:[]};
  if (id === 207) requireValue(Number.isSafeInteger(skillLevel) && skillLevel >= 1 && skillLevel <= 10,'파워 웨이브 스킬 레벨은 1~10으로 입력하세요.');
  let amount = L * B, formula = 'L × B';
  if (id === 44) {amount = Math.fround(Math.fround(Math.fround(B / 100) * L) + 1); formula = '(B ÷ 100) × L + 1';}
  else if ([205,206,76,1031].includes(id)) {amount = Math.fround(amount / 10); formula = 'L × B ÷ 10';}
  else if ([24,25,26,32].includes(id)) {amount = B - L; formula = 'B − L';}
  else if ([29,33,35,38,41].includes(id)) {amount = B + L; formula = 'B + L';}
  else if (id === 37) {amount = B - L + 1; formula = 'B − L + 1';}
  else if (id === 42) {amount = B - 100 * L + 100; formula = 'B − 100 × L + 100';}
  else if (id === 211) {amount = B - 10 * L + 10; formula = 'B − 10 × L + 10';}
  else if ([1011,1012,1013].includes(id)) {amount = 100 - (L + 1) * B; formula = '100 − (L + 1) × B';}
  else if (id === 1030) {amount = 300 - L * B; formula = '300 − L × B';}
  else if (id === 1042) {amount = Math.fround((amount - 1) / 10); formula = '(L × B − 1) ÷ 10';}
  else if (id === 1039) {amount = 60 - amount; formula = '60 − L × B';}
  else if (id === 1045) {amount = (4 - L) * B; formula = '(4 − L) × B';}
  else if (id === 1047) {amount = 15 - L; formula = '15 − L';}
  else if (id === 1051) {amount = 100 - amount; formula = '100 − L × B';}
  else if (id === 207) {amount = Math.trunc((skillLevel + L) / 2); formula = '⌊(S + L) ÷ 2⌋';}
  const row = (label,expression,value) => ({label,formula:expression,substitution:expression.replace(/\b[LSB]\b/gu,key => ({L,B,S:skillLevel})[key]),result:formatRegistletNumber(value)});
  const rows = [row(id === 1004 ? '위력 증가' : '설명 수치',formula,amount)];
  if (id === 1004) rows.push(row('명중률 증가','10 × L × B',10 * L * B));
  return {description:template.replaceAll('{0}',formatRegistletNumber(amount)).replaceAll('{1}',formatRegistletNumber(10 * L * B)),rows};
}
export const formatRegistletNumber = value => Number(value.toFixed(2)).toLocaleString('ko-KR',{maximumFractionDigits:2});
export const registletDescription = selection => registletEffect(selection).description;
export function registletEnhancement(item,level,materialLevel = 1) {
  requireValue(Number.isSafeInteger(level) && level >= 1 && level <= item.levelCap,'강화할 젬 레벨을 확인하세요.');
  requireValue(Number.isSafeInteger(materialLevel) && materialLevel >= 1 && materialLevel <= item.levelCap,`동일 재료 젬 레벨은 1~${item.levelCap}로 입력하세요.`);
  const P = item.enhancePowder;
  requireValue(Number.isSafeInteger(P) && P >= 0 && P <= 2147483647,'강화 분말 기본값을 확인하세요.');
  const samePowder = -Math.trunc(Math.fround(Math.fround(P) * Math.fround(-0.1)));
  return {max:level === item.levelCap,basePowder:P,
    same:{powder:samePowder,toLevel:Math.min(item.levelCap,level + materialLevel)},
    different:{powder:P,toLevel:Math.min(item.levelCap,level + 1)}};
}
export function registletLocations(item,locale = 'kr') {
  return item.locations.length ? item.locations.map(place => `Lv${place.level} · ${place.names[locale] || place.names.kr} · ${place.ranks.join('/')} 상자`).join('\n') : '확인된 스투디의 실험 보상 목록에 없습니다.';
}
export function createRegistletCatalog(url = new URL('../../game-data/registlets/catalog.json',import.meta.url),fetcher = globalThis.fetch) {
  const reader = createCatalogReader(url,fetcher,async response => {
    requireValue(response.ok,'레지스트렛 데이터를 불러오지 못했습니다.');
    const catalog = await response.json();
    requireValue(catalog.schema === 'toram.registlet-catalog.v1' && Array.isArray(catalog.items) && catalog.items.length === Object.keys(REGISTLET_LEVEL_CAPS).length,'레지스트렛 데이터 형식이 올바르지 않습니다.');
    const ids = new Set();
    for (const item of catalog.items) {
      requireValue(!ids.has(item.id),'중복된 레지스트렛 ID입니다.'); ids.add(item.id);
      for (const locale of ['kr','us','jp','cnt','idn','th']) createRegistletSelection({...item,cacheVersion:catalog.cacheVersion,sourceSha256:catalog.sourceSha256},1,locale);
      requireValue(['stats','status','support','skills'].includes(item.category) && Number.isSafeInteger(item.enhancePowder) && item.enhancePowder >= 0,'레지스트렛 분류·강화 분말을 확인하세요.');
      requireValue(Array.isArray(item.locations) && item.locations.every(place => Number.isSafeInteger(place.level) && place.level > 0 && plain(place.names) && typeof place.names.kr === 'string' && Array.isArray(place.ranks) && place.ranks.length > 0 && place.ranks.every(rank => ['A','S'].includes(rank))),'레지스트렛 획득처를 확인하세요.');
    }
    requireValue(catalog.slotExpansion?.slotLimit === 10 && Array.isArray(catalog.slotExpansion.costs) && catalog.slotExpansion.costs.length === 9 && catalog.slotExpansion.costs.every(cost => Number.isSafeInteger(cost) && cost > 0),'레지스트렛 슬롯 확장표를 확인하세요.');
    return catalog;
  });
  async function data() {return reader.read('catalog.json');}
  async function list(locale = 'kr') {const catalog = await data(); return catalog.items.map(item => ({...structuredClone(item),name:item.names[locale] || null,cacheVersion:catalog.cacheVersion,sourceSha256:catalog.sourceSha256}));}
  return Object.freeze({
    list,
    async get(id,locale = 'kr') {const item = (await list(locale)).find(item => item.id === id); requireValue(item,'레지스트렛 ID를 찾을 수 없습니다.'); return item;},
    async slots() {return structuredClone((await data()).slotExpansion);}
  });
}
