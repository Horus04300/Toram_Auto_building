/* 배틀 스킬: 원문 https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40368 기준. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('배틀 효과 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v=function(n){return {op:'value',value:n};}, r=function(path){return {op:'ref',path:path};};
  var l=function(){return r('skill.level');}, a=function(){return {op:'add',args:[].slice.call(arguments)};};
  var m=function(){return {op:'multiply',args:[].slice.call(arguments)};}, d=function(left,right){return {op:'divide',left:left,right:right};};
  var sub=function(left,right){return {op:'subtract',left:left,right:right};};
  var levelScale=function(){ return d(m(v(2.5),l(),r('player.level')),v(100)); };
  var anchors=['1차 마법력 UP 패시브 / 모든 무기 사용 가능','집중 패시브 / 모든 무기 사용 가능','공격력 UP 패시브 / 모든 무기 사용 가능','강타 패시브 / 모든 무기 사용 가능','방어력 UP 패시브 / 모든 무기 사용 가능','회피 UP 패시브 / 모든 무기 사용 가능','2차 필사적인 저항 패시브 / 모든 무기 사용 가능','크리티컬 UP 패시브 / 모든 무기 사용 가능','명중 UP 패시브 / 모든 무기 사용 가능','3차 한층 더한 마력 패시브 / 모든 무기 사용 가능','위협의 위력 패시브 / 모든 무기 사용 가능','수비의 마음가짐 패시브 / 모든 무기 사용 가능','4차 스펠 버스트 패시브 / 모든 무기 사용 가능','추격의 극의 패시브 / 모든 무기 사용 가능','슈퍼그립 패시브 / 모든 무기 사용 가능'];
  function skill(skillId, kind, dataStatus, effects) {
    var source = catalog.skills.find(function (item) { return item.id === 'Battle:' + skillId; });
    if (!source) throw new Error('배틀 스킬을 카탈로그에서 찾지 못했습니다: ' + skillId);
    return { id:source.id, treeId:'Battle', skillId:skillId, nameKo:source.nameKo, kind:kind, source:'battle', dataStatus:'partial', sourceRef:{file:'docs/sources/skills/Battle.txt',anchor:anchors[skillId]}, notes:'S1~S5 calculator scope; proc, incapacitation and death events remain metadata.', effects:effects };
  }
  registry.register('Battle', [
    skill(0, 'passive', 'verified', [{phase:'build',type:'stat',key:'MATK',value:levelScale()}]),
    skill(1, 'passive', 'partial', [{phase:'hit',type:'procDamageMultiplier',target:'magic',chance:l(),value:a(v(1.10),d(l(),v(100))),notes:'필드 설치형 스킬에는 적용되지 않음'}]),
    skill(2, 'passive', 'verified', [{phase:'build',type:'stat',key:'ATK',value:levelScale()}]),
    skill(3, 'passive', 'partial', [{phase:'hit',type:'procDamageMultiplier',target:'physical',chance:l(),value:a(v(1.10),d(l(),v(100)))}]),
    skill(4, 'passive', 'verified', [{phase:'build',type:'stat',key:'DEF',value:levelScale()},{phase:'build',type:'stat',key:'MDEF',value:levelScale()}]),
    skill(5, 'passive', 'verified', [{phase:'build',type:'stat',key:'FLEE',value:l()}]),
    skill(6, 'passive', 'partial', [{phase:'combat',type:'damageTakenMultiplier',when:{op:'truthy',value:r('combat.incapacitated')},value:sub(v(1),d(l(),v(100)))}]),
    skill(7, 'passive', 'verified', [{phase:'build',type:'stat',key:'CRIT',value:d(l(),v(2))},{phase:'build',type:'stat',key:'CDMG_P',value:d(l(),v(2))}]),
    skill(8, 'passive', 'verified', [{phase:'build',type:'stat',key:'HIT',value:l()}]),
    skill(9, 'passive', 'verified', [{phase:'build',type:'stat',key:'MATK',value:levelScale()}]),
    skill(10, 'passive', 'verified', [{phase:'build',type:'stat',key:'ATK',value:levelScale()}]),
    skill(11, 'passive', 'verified', [{phase:'build',type:'stat',key:'DEF',value:levelScale()},{phase:'build',type:'stat',key:'MDEF',value:levelScale()}]),
    skill(12, 'passive', 'partial', [{phase:'hit',type:'magicCriticalConversion',chance:m(v(2.5),l()),criticalDamageRate:m(v(2.5),l())}]),
    skill(13, 'passive', 'partial', [{phase:'afterHit',type:'chaseAttackChance',chance:m(v(2.5),l())}]),
    skill(14, 'passive', 'partial', [{phase:'combat',type:'knockbackDamageReduction',value:m(v(7.5),l())}])
  ]);
}());