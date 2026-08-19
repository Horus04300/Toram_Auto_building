/* 블레이드: 공격 후 지속 버프를 얻는 오라 블레이드. 원문 no=39513 기준. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('블레이드 효과 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v=function(n){return {op:'value',value:n};}, r=function(path){return {op:'ref',path:path};};
  var l=function(){return r('skill.level');}, a=function(){return {op:'add',args:[].slice.call(arguments)};};
  var e=function(left,right){return {op:'eq',left:left,right:right};};
  var weapon=function(name){return e(r('equipment.mainWeapon'),v(name));};
  var aura = catalog.skills.find(function (item) { return item.id === 'Blade:16'; });
  if (!aura) throw new Error('오라 블레이드를 카탈로그에서 찾지 못했습니다.');
  registry.register('Blade', [{
    id:aura.id, treeId:'Blade', skillId:16, nameKo:aura.nameKo, kind:'attack', activeBuff:true,
    source:'blade', dataStatus:'partial', requirements:{when:{op:'in',value:r('equipment.mainWeapon'),values:['한손검','양손검']}},
    cost:{mp:{timing:'cast',value:v(200)}}, combo:{canStart:true,canReceiveTag:true},
    attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(5),l()),constant:v(200),flags:{longRange:true,unsheathe:false}}],
    stateTransitions:[{event:'cast',operation:'grant',stateId:'blade.auraBlade',stacks:v(1),maxStacks:v(1),durationSeconds:v(40)}],
    effects:[
      {phase:'combat',type:'damageMultiplier',target:'attack',when:weapon('한손검'),value:v(1.2)},
      {phase:'combat',type:'damageMultiplier',target:'attack',when:weapon('양손검'),value:v(1.3)},
      {phase:'combat',type:'physicalChaseDamage',when:weapon('한손검'),value:{op:'multiply',args:[v(10),l()]}},
      {phase:'combat',type:'physicalChaseDamage',when:weapon('양손검'),value:{op:'multiply',args:[v(5),l()]}}
    ]
  }]);
}());