/* 다크 파워: 리그렛 스택 버프. 원문 no=40846 기준. */
(function () {
  'use strict';
  var registry=window.ToramSkillEffectRegistry, catalog=window.TORAM_SKILL_COMBAT_CATALOG;
  if(!registry||!catalog) throw new Error('다크 파워 효과 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v=function(n){return {op:'value',value:n};}, r=function(path){return {op:'ref',path:path};};
  var l=function(){return r('skill.level');}, a=function(){return {op:'add',args:[].slice.call(arguments)};};
  var m=function(){return {op:'multiply',args:[].slice.call(arguments)};}, d=function(left,right){return {op:'divide',left:left,right:right};};
  var tier=function(cases){return {op:'tier',cases:cases};};
  var range=function(min,max,value){return {when:{op:'all',args:[{op:'gte',left:l(),right:v(min)},{op:'lte',left:l(),right:v(max)}]},value:v(value)};};
  var skill=catalog.skills.find(function(item){return item.id==='DarkPower:6';});
  if(!skill) throw new Error('리그렛을 카탈로그에서 찾지 못했습니다.');
  var stacks=r('buff.stacks');
  var beneficialStacks={op:'min',args:[stacks,v(10)]};
  registry.register('DarkPower',[{
    id:skill.id,treeId:'DarkPower',skillId:6,nameKo:skill.nameKo,kind:'buff',source:'darkPower',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/DarkPower.txt',anchor:'이로운 효과에 적용되는 스택은 최대 10까지이며, 지속 시간과 최대 hp 감소에 적용되는 스택은 한계가 없다.'},
    cost:{mp:{timing:'cast',value:v(200)}},combo:{canStart:true,canReceiveTag:true},
    stackControl:{stateId:'darkPowerRegret',minStacks:v(1),maxStacks:v(15),initialStacks:v(1),label:'리그렛 스택'},
    stateTransitions:[{event:'cast',operation:'addStacks',stateId:'darkPowerRegret',stacks:v(1),maxStacks:v(15),durationSeconds:{op:'subtract',left:v(32),right:m(v(2),stacks)}}],
    effects:[
      {phase:'combat',type:'stat',key:'AMPR',value:m(l(),beneficialStacks)},
      {phase:'combat',type:'stat',key:'PHYS_RES',value:m(l(),beneficialStacks)},
      {phase:'combat',type:'stat',key:'MAG_RES',value:m(l(),beneficialStacks)},
      {phase:'combat',type:'stat',key:'MAXMP',value:m(v(100),beneficialStacks)},
      {phase:'combat',type:'stat',key:'ATK',value:m(tier([range(1,2,1),range(3,4,2),range(5,6,3),range(7,8,4),range(9,10,5)]),beneficialStacks)},
      {phase:'combat',type:'stat',key:'MATK',value:m(tier([range(1,2,1),range(3,4,2),range(5,6,3),range(7,8,4),range(9,10,5)]),beneficialStacks)},
      {phase:'combat',type:'stat',key:'MAXHP_P',value:m(v(-10),stacks)}
    ]
  }]);
}());

