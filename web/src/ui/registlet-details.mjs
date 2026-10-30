import {registletEffect,registletEnhancement,registletLocations,formatRegistletNumber} from '../application/registlet-catalog.mjs';

export function renderRegistletDetails(documentRef,target,item,selection,{effect = registletEffect(selection),materialLevel = 1,locale = 'kr'} = {}) {
  const cost = registletEnhancement(item,selection.level,materialLevel);
  const node = (tag,text) => {const value = documentRef.createElement(tag); value.textContent = text; return value;};
  function table(caption,headers,rows,className) {
    const table = node('table',''); table.className = className;
    table.append(node('caption',caption));
    const head = node('thead',''), tr = node('tr','');
    for (const value of headers) {const th = node('th',value); th.scope = 'col'; tr.append(th);} head.append(tr); table.append(head);
    const body = node('tbody','');
    for (const values of rows) {const row = node('tr',''); for (const value of values) row.append(node('td',value)); body.append(row);} table.append(body); return table;
  }
  target.replaceChildren();
  target.append(node('h4','효과 수식'));
  if (effect.rows.length) {
    target.append(node('p',`L = 젬 레벨 ${selection.level}${selection.baseValue !== -1 ? ` · B = 원본 기본값 ${selection.baseValue}` : ''}${[207,1053].includes(item.id) ? ' · S = 관련 스킬 레벨' : ''}`));
    target.append(table('수식과 현재 결과',['항목','수식 · 값 대입','결과'],effect.rows.map(row => [row.label,`${row.formula}\n= ${row.substitution}`,row.result]),'registlet-formulas'));
  } else target.append(node('p',item.levelCap === 1 ? 'Lv1 고정 효과입니다.' : '효과 원문에 레벨별 수치가 표시되지 않습니다.'));
  if (effect.notes) target.append(node('p',effect.notes));
  if (effect.rows.some(row => row.formula.includes('⌊'))) target.append(node('p','⌊ ⌋는 소수점 버림입니다.'));
  target.append(node('h4','강화 비용'));
  if (cost.max) target.append(node('p','최대 레벨입니다. 더 강화할 수 없습니다.'));
  else {
    target.append(node('p',`P = 강화 분말 기본값 ${formatRegistletNumber(cost.basePowder)}개 · 재료 젬 카트리지 1개 기준`));
    target.append(table('재료 종류별 필요 분말과 강화 결과',['소모 재료','분말 수식 · 비용','강화 결과'],[
      [`동일 종류 젬 Lv${materialLevel}`,`⌊P × 0.1⌋ = ${formatRegistletNumber(cost.same.powder)}개`,`Lv${selection.level} → Lv${cost.same.toLevel}`],
      ['다른 종류 젬','P = ' + formatRegistletNumber(cost.different.powder) + '개',`Lv${selection.level} → Lv${cost.different.toLevel}`]
    ],'registlet-enhancement'));
    target.append(node('p','동일 종류는 재료 젬 레벨만큼, 다른 종류는 재료 1개당 1레벨 상승합니다. 재료 젬은 소모되며 결과는 최대 레벨을 넘지 않습니다. ⌊ ⌋는 소수점 버림입니다.'));
  }
  target.append(node('h4','획득처'));
  const locations = node('p',registletLocations(item,locale)); locations.className = 'catalog-acquisition registlet-locations'; target.append(locations);
  target.append(node('p','보상 상자별 획득 확률은 확인되지 않았습니다.'));
}
