/* 서포터 스킬: 원문 https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40366 기준. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('서포터 효과 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v=function(n){return {op:'value',value:n};}, r=function(path){return {op:'ref',path:path};};
  var l=function(){return r('skill.level');}, a=function(){return {op:'add',args:[].slice.call(arguments)};};
  var m=function(){return {op:'multiply',args:[].slice.call(arguments)};}, d=function(left,right){return {op:'divide',left:left,right:right};};
  var tier=function(cases){return {op:'tier',cases:cases};};
  var levelIs=function(min,max,value){return {when:{op:'all',args:[{op:'gte',left:l(),right:v(min)},{op:'lte',left:l(),right:v(max)}]},value:v(value)};};
  var active=function(){return {op:'truthy',value:r('buff.active')};};
  function skill(skillId, kind, dataStatus, data) {
    var source = catalog.skills.find(function (item) { return item.id === 'Support:' + skillId; });
    if (!source) throw new Error('서포터 스킬을 카탈로그에서 찾지 못했습니다: ' + skillId);
    data = data || {};
    return Object.assign({ id:source.id, treeId:'Support', skillId:skillId, nameKo:source.nameKo, kind:kind, source:'support', dataStatus:dataStatus }, data);
  }
  function aura(skillId, mp, effects) {
    return skill(skillId, 'buff', 'partial', { cost:{mp:{timing:'cast',value:v(mp)}}, combo:{canStart:true,canReceiveTag:false}, stateTransitions:[{event:'cast',operation:'grant',stateId:'support.' + skillId,stacks:v(1),maxStacks:v(1),durationSeconds:v(900)}], effects:effects });
  }
  registry.register('Support', [
    skill(0, 'passive', 'partial', {effects:[{phase:'combat',type:'reviveTimeReductionRate',value:m(v(2),l()),notes:'기본 부활 시간 감소율 30%에 곱연산'}]}),
    skill(1, 'utility', 'partial', {cost:{mp:{timing:'cast',value:v(100)}},combo:{canStart:true,canReceiveTag:false},effects:[{phase:'cast',type:'heal',value:a(m(v(30),l()),m(r('target.maxHp'),d(l(),v(100))))},{phase:'cast',type:'reviveWaitReductionSeconds',value:l()}]}),
    skill(2, 'utility', 'partial', {cost:{mp:{timing:'cast',value:v(100)}},combo:{canStart:true,canReceiveTag:false},effects:[{phase:'cast',type:'removeAilment',count:v(1)},{phase:'cast',type:'resourceRestore',key:'MP',value:m(l(),l()),when:{op:'truthy',value:r('combat.ailmentRemoved')}}]}),
    skill(3, 'buff', 'partial', {cost:{mp:{timing:'cast',value:v(400)}},combo:{canStart:true,canReceiveTag:false},stateTransitions:[{event:'cast',operation:'grant',stateId:'support.sanctuary',stacks:v(1),maxStacks:v(1),durationSeconds:a(v(5),l())}],effects:[{phase:'combat',type:'thresholdDamageReduction',thresholdPercent:a(v(5),d(l(),v(2))),value:tier([levelIs(1,3,30),levelIs(4,6,50),levelIs(7,9,70),levelIs(10,10,90)])}]}),
    skill(4, 'utility', 'partial', {cost:{mp:{timing:'cast',value:v(300)}},combo:{canStart:true,canReceiveTag:false},effects:[{phase:'cast',type:'heal',value:a(m(v(300),l()),m(r('target.maxHp'),d(a(v(10),l()),v(100))))},{phase:'cast',type:'reviveWaitReductionSeconds',value:a(v(10),m(v(2),l()))}]}),
    aura(5, 300, [{phase:'combat',type:'resourceRegen',key:'HP',value:a(v(10),m(v(4),l()),r('combatStats.VIT')),notes:'시전자 총 VIT 기준, 자신과 범위 내 아군'}]),
    aura(6, 400, [{phase:'combat',type:'damageMultiplier',target:'attack',when:active(),value:a(v(1),d(m(v(2),l()),v(100)))},{phase:'combat',type:'stat',key:'WATKP',when:active(),value:a(v(10),m(v(2),l()))},{phase:'combat',type:'stat',key:'HIT',when:active(),scope:'self',value:{op:'subtract',left:m(v(2.5),l()),right:v(75)}}]),
    aura(7, 500, [{phase:'combat',type:'stat',key:'CSPD_P',when:active(),value:m(v(25),l())},{phase:'combat',type:'stat',key:'CSPD',when:active(),value:a(v(50),m(v(50),l()))},{phase:'combat',type:'resourceRegenPenalty',key:'MP',scope:'self',value:{op:'subtract',left:m(v(2.5),l()),right:v(50.5)}},{phase:'combat',type:'attackMpRecoveryPenalty',scope:'self',value:{op:'subtract',left:m(v(1.5),l()),right:v(90.5)}}]),
    aura(8, 600, [{phase:'combat',type:'stat',key:'ASPD_P',when:active(),value:m(v(25),l())},{phase:'combat',type:'stat',key:'ASPD',when:active(),value:a(v(100),m(v(100),l()))},{phase:'combat',type:'attackMpRecoveryPenalty',scope:'self',value:{op:'subtract',left:m(v(3),l()),right:v(100)}}]),
    aura(9, 300, [{phase:'combat',type:'resourceRegen',key:'MP',value:a(v(10),m(v(1.5),l()),d(r('combatStats.INT'),v(10))),notes:'시전자 총 INT 기준, 자신과 범위 내 아군'},{phase:'combat',type:'damageTakenMultiplier',scope:'self',value:d({op:'subtract',left:v(50),right:m(v(2.5),l())},v(100))}]),
    aura(10, 400, [{phase:'combat',type:'stat',key:'DEFP',when:active(),value:a(v(10),m(v(2),l()))},{phase:'combat',type:'stat',key:'MDEFP',when:active(),value:a(v(10),m(v(2),l()))},{phase:'combat',type:'damageTakenMultiplier',value:{op:'subtract',left:v(1),right:d(m(v(2),l()),v(100))}},{phase:'combat',type:'stat',key:'FLEE',scope:'self',value:{op:'subtract',left:m(v(2.5),l()),right:v(75)}}]),
    aura(11, 500, [{phase:'combat',type:'ailmentResistanceChance',value:a(v(20),m(v(3),l()))},{phase:'combat',type:'attackSpeedPenalty',scope:'self',value:{op:'subtract',left:m(v(75),l()),right:v(1000)}}]),
    aura(12, 600, [{phase:'combat',type:'guardRecoveryRate',value:a(v(10),l())},{phase:'combat',type:'evasionRecoveryRate',value:l()},{phase:'combat',type:'castSpeedPenalty',scope:'self',value:{op:'subtract',left:m(v(75),l()),right:v(1000)}}])
  ]);
}());