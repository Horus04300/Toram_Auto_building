/* 서바이벌 스킬: 원문 https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40367 기준. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('서바이벌 효과 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v=function(n){return {op:'value',value:n};}, r=function(path){return {op:'ref',path:path};};
  var l=function(){return r('skill.level');}, m=function(){return {op:'multiply',args:[].slice.call(arguments)};};
  function skill(skillId, dataStatus, effects) {
    var source = catalog.skills.find(function (item) { return item.id === 'Survival:' + skillId; });
    if (!source) throw new Error('서바이벌 스킬을 카탈로그에서 찾지 못했습니다: ' + skillId);
    return { id:source.id, treeId:'Survival', skillId:skillId, nameKo:source.nameKo, kind:'passive', source:'survival', dataStatus:dataStatus, effects:effects };
  }
  registry.register('Survival', [
    skill(0, 'partial', [{phase:'combat',type:'reviveTimeReduction',value:m(v(5),l())}]),
    skill(1, 'partial', [{phase:'reward',type:'experienceGain',value:l()}]),
    skill(2, 'partial', [{phase:'reward',type:'dropRate',value:l()}]),
    skill(3, 'partial', [{phase:'build',type:'stat',key:'HPR_NONCOMBAT_P',value:m(v(10),l())},{phase:'build',type:'stat',key:'HPR_NONCOMBAT',value:m(v(10),l())}]),
    skill(4, 'verified', [{phase:'build',type:'stat',key:'MAXHP_P',value:m(v(2),l())},{phase:'build',type:'stat',key:'MAXHP',value:m(v(100),l())}]),
    skill(5, 'partial', [{phase:'build',type:'stat',key:'HPR_COMBAT_BASE_P',value:l()}]),
    skill(6, 'partial', [{phase:'build',type:'stat',key:'MPR_NONCOMBAT_P',value:m(v(5),l())},{phase:'build',type:'stat',key:'MPR_NONCOMBAT',value:l()}]),
    skill(7, 'verified', [{phase:'build',type:'stat',key:'MAXMP',value:m(v(30),l())}]),
    skill(8, 'partial', [{phase:'build',type:'stat',key:'MPR_COMBAT_BASE_P',value:m(v(5),l())}])
  ]);
}());