/* 마셜: 원문 대조가 끝난 아수라 오라의 양방향 상태·스택 규칙. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('마셜 스킬 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v=function(n){return {op:'value',value:n};}, r=function(path){return {op:'ref',path:path};};
  var l=function(){return r('skill.level');}, m=function(){return {op:'multiply',args:[].slice.call(arguments)};};
  var active=function(){return {op:'truthy',value:r('buff.active')};};
  var hasStacks=function(){return {op:'gt',left:r('buff.stacks'),right:v(0)};};
  var mainKnuckle={op:'eq',left:r('equipment.mainWeapon'),right:v('권갑')};
  var skill=catalog.skills.find(function(item){return item.id==='Martial:11';});
  if(!skill) throw new Error('아수라 오라를 카탈로그에서 찾지 못했습니다.');
  registry.register('Martial-stack-buff', [{
    id:skill.id, treeId:'Martial', skillId:11, nameKo:skill.nameKo, kind:'buff', source:'martial', dataStatus:'partial',
    sourceRef:{file:'docs/sources/skills/Martial.txt',anchor:'아수라 오라 버프 / 권갑 전용'}, requirements:{when:mainKnuckle}, cost:{mp:{timing:'cast',value:v(0)}}, combo:{canStart:false,canReceiveTag:true},
    stackRole:'combat-resource',
    stackControl:{stateId:'martialAsuraAura',minStacks:v(0),maxStacks:v(40),initialStacks:v(0),label:'아수라 스택',persistWhenDisabled:true,showWhenDisabled:true,applyWhenDisabled:true,resetStacksOnEnable:true},
    stackModel:{mode:'dual-mode-persistent',hardCap:v(40),onCastClearsStacks:true,offStatePreservesStacks:true,gain:{event:'mpSpent',perMp:v(100),stacks:v(1)},over20HpCostPerStackPercent:v(5),deathAtStacks:v(40),notes:'ON으로 전환하면 스택을 지우고, OFF로 전환하면 모은 스택을 유지한다.'},
    stateTransitions:[
      {event:'toggleOn',operation:'setStacks',stateId:'martialAsuraAura',stacks:v(0),maxStacks:v(40),durationSeconds:v(0),effects:[{type:'invincibility',durationSeconds:v(2)}]},
      {event:'mpSpent',operation:'addStacks',stateId:'martialAsuraAura',stacks:v(1),maxStacks:v(40),perResource:v(100)},
      {event:'toggleOff',operation:'preserveStacks',stateId:'martialAsuraAura'},
      {event:'normalAttackHit',operation:'consumeStacks',stateId:'martialAsuraAura',stacks:v(1),when:{op:'not',value:active()}}
    ],
    effects:[
      {phase:'combat',type:'stat',key:'CRIT',when:active(),value:m(v(7.5),l())},
      {phase:'combat',type:'globalSkillConstant',when:active(),value:m(v(20),l())},
      {phase:'combat',type:'damageMultiplier',target:'skillTrees:Martial,Crusher,Assassin,DarkPower',when:active(),value:v(1.3)},
      {phase:'combat',type:'damageMultiplier',target:'otherSkillTrees',when:active(),value:v(1.1)},
      {phase:'combat',type:'resourceCostModifier',key:'MP',when:active(),value:v(100),notes:'마셜·크러셔 이외 스킬, MP 반감 뒤·콤보 태그 전'},
      {phase:'combat',type:'asuraOnState',when:active(),notes:'현재 MP 기반 피해 감소/이상 내성, 공마회 차단, 아수라 블로는 전투 상태 엔진 구현 대기'}
    ],
    inactiveEffects:[
      {phase:'combat',type:'stat',key:'CRIT',when:hasStacks(),value:m(v(7.5),l())},
      {phase:'combat',type:'globalSkillConstant',when:hasStacks(),value:m(v(20),l())},
      {phase:'combat',type:'damageMultiplier',target:'attack',when:hasStacks(),value:v(1.1)},
      {phase:'combat',type:'asuraOffState',when:hasStacks(),notes:'아수라 블로는 통상 공격마다 스택 1을 소모하며 공마회 효과를 별도 계산해야 함'}
    ],
    specialAttacks:[{id:'asuraBlow',damageType:'physical',requiresTargetWithinMeters:v(3.5),multiplier:{op:'add',args:[v(.5),{op:'divide',left:r('baseStats.AGI'),right:{op:'subtract',left:v(2400),right:m(v(200),l())}}]},constant:v(0),hitIntervalSeconds:v(.25),flags:{guaranteedHit:true,longRange:false,unsheathe:false}}]
  }]);
}());