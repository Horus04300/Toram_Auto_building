/* 슛: 원문 대조가 끝난 퀵 로더 전투 자원 규칙. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('슛 스택 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v=function(n){return {op:'value',value:n};}, r=function(path){return {op:'ref',path:path};};
  var l=function(){return r('skill.level');}, a=function(){return {op:'add',args:[].slice.call(arguments)};};
  var m=function(){return {op:'multiply',args:[].slice.call(arguments)};}, q=function(when,yes,no){return {op:'if',when:when,then:yes,else:no};}, eq=function(left,right){return {op:'eq',left:left,right:right};};
  var skill=catalog.skills.find(function(item){return item.id==='Shot:9';});
  if(!skill) throw new Error('퀵 로더를 카탈로그에서 찾지 못했습니다.');
  var bow=q(eq(r('equipment.mainWeapon'),v('활')),v(3),v(2));
  registry.register('Shot-stack-buff',[{
    id:skill.id,treeId:'Shot',skillId:9,nameKo:skill.nameKo,kind:'buff',source:'shot',dataStatus:'partial',
    sourceRef:{file:'docs/sources/skills/Shot.txt',anchor:'시전 시 스택을 2개 획득하고'}, stackRole:'combat-resource',
    cost:{mp:{timing:'cast',value:v(400)}}, stackControl:{stateId:'shotQuickLoader',minStacks:v(0),maxStacks:bow,initialStacks:bow,label:'퀵 로더 스택'},
    stateTransitions:[
      {event:'cast',operation:'setStacks',stateId:'shotQuickLoader',stacks:bow,maxStacks:bow,durationSeconds:a(v(120),m(v(-6),l())),notes:'지속 중 재사용 시 스택·지속시간을 갱신하지 않음'},
      {event:'cast',operation:'grant',stateId:'shotQuickLoader.hideAttack',stacks:v(1),maxStacks:v(1),linkedSkillId:'Shot:22',levelCap:l()},
      {event:'crossFireOrPenetratorFire',operation:'consumeStacks',stateId:'shotQuickLoader',stacks:v(1),when:{op:'lt',left:r('attack.inputs.charge'),right:r('attack.inputs.maxCharge')},effect:{type:'increaseCharge',amount:v(1)}}
    ],
    recastWhileActive:{nextSkillMotionSpeed:m(v(5),l()),mpRestoreRatio:v(.5)}, effects:[]
  }]);
}());