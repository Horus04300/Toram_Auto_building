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

(function(){'use strict';const R=window.ToramSkillEffectRegistry,C=window.TORAM_SKILL_COMBAT_CATALOG;if(!R||!C)throw Error('Guard order');const v=value=>({op:'value',value}),r=path=>({op:'ref',path}),l=()=>r('skill.level'),a=(...args)=>({op:'add',args}),d=(left,right)=>({op:'divide',left,right}),eq=(left,right)=>({op:'eq',left,right});const heavy=eq(r('equipment.armorType'),v('중량옷')),light=eq(r('equipment.armorType'),v('경량옷'));function D(skillId,anchor,when){const s=C.skills.find(skill=>skill.id===`Guard:${skillId}`);return{id:s.id,treeId:'Guard',skillId,nameKo:s.nameKo,kind:'passive',source:'guard',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Guard.txt',anchor},requirements:{when},notes:'S1~S5 calculator scope; actual guard/avoid and HP state events remain metadata.'};}const x=[D(0,'1차 중갑옷 마스터리 패시브 / 중량옷 전용',heavy),D(1,'2차 어드밴스 가드 패시브 / 중량옷 전용',heavy),D(2,'3차 피지컬 가드 패시브 / 모든 무기 사용 가능',null),D(3,'경갑옷 마스터리 패시브 / 경량옷 전용',light),D(4,'어드밴스 프리 패시브 / 경량옷 전용',light),D(5,'미라쥬 스텝 패시브 / 모든 무기 사용 가능',null)];x[0].effects=[{phase:'build',type:'stat',key:'GUARD_RECOVERY',value:l()}];x[1].effects=[{phase:'build',type:'stat',key:'GUARD_RECOVERY',value:l()},{phase:'build',type:'stat',key:'GUARD_POWER',value:d(a(l(),v(1)),v(2))}];x[2].effects=[{phase:'combat',type:'physicalGuardAilmentResistanceDouble',hpThresholdPercent:{op:'multiply',args:[v(5),l()]},notes:'현재 HP 조건과 가드 성공은 전투 상태 엔진 필요.'}];x[3].effects=[{phase:'build',type:'stat',key:'AVOID_RECOVERY',value:l()}];x[4].effects=[{phase:'build',type:'stat',key:'AVOID_RECOVERY',value:l()}];x[5].effects=[{phase:'combat',type:'mirageStepCastAvoid',cooldownSeconds:{op:'subtract',left:v(20),right:l()},notes:'차징/영창 중 avoid 가능 여부와 실제 쿨다운은 전투 상태 엔진 필요.'}];R.register('Guard:calculation-rules',x);}());