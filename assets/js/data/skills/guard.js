/* 가드 스킬: 원문 https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40324 기준. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('가드 효과 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v=function(n){return {op:'value',value:n};}, r=function(path){return {op:'ref',path:path};};
  var l=function(){return r('skill.level');}, a=function(){return {op:'add',args:[].slice.call(arguments)};};
  var d=function(left,right){return {op:'divide',left:left,right:right};};
  var armorIs=function(value){return {op:'eq',left:r('equipment.armorType'),right:v(value)};};
  function skill(skillId, dataStatus, effects) {
    var source = catalog.skills.find(function (item) { return item.id === 'Guard:' + skillId; });
    if (!source) throw new Error('가드 스킬을 카탈로그에서 찾지 못했습니다: ' + skillId);
    return { id:source.id, treeId:'Guard', skillId:skillId, nameKo:source.nameKo, kind:'passive', source:'guard', dataStatus:dataStatus, effects:effects };
  }
  registry.register('Guard', [
    skill(0, 'partial', [{phase:'combat',type:'guardRecoveryRate',when:armorIs('중량옷'),value:l()}]),
    skill(1, 'partial', [{phase:'combat',type:'guardRecoveryRate',when:armorIs('중량옷'),value:l()},{phase:'combat',type:'guardPower',when:armorIs('중량옷'),value:d(a(l(),v(1)),v(2))}]),
    skill(2, 'partial', [{phase:'combat',type:'ailmentResistance',when:{op:'lte',left:r('combat.hpPercent'),right:{op:'multiply',args:[v(5),l()]}},value:l()}]),
    skill(3, 'partial', [{phase:'combat',type:'evasionRecoveryRate',when:armorIs('경량옷'),value:l()}]),
    skill(4, 'partial', [{phase:'combat',type:'evasionRecoveryRate',when:armorIs('경량옷'),value:l()}]),
    skill(5, 'partial', [{phase:'combat',type:'castChargeEvasionCooldown',value:{op:'subtract',left:v(20),right:l()}}])
  ]);
}());