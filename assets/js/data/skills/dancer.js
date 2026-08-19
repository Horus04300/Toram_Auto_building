/* 댄서: 공통 춤 스택 버프. 원문 캐시: docs/sources/skills/Dancer.txt */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('댄서 효과 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v = function (n) { return { op:'value', value:n }; };
  var sourceRef = { file:'docs/sources/skills/Dancer.txt', anchor:'스택은 최소 0, 최대 10이지만, 동시에 여러 개의 춤 버프 스킬이 발동 중이면 최대 스택은 (11 - 동시에 발동 중인 춤 버프 스킬의 수)로 줄어든다.' };
  function dance(id, mp, stateId) {
    var skill = catalog.skills.find(function (item) { return item.id === 'Dancer:' + id; });
    if (!skill) throw new Error('댄서 스킬을 카탈로그에서 찾지 못했습니다: ' + id);
    return {
      id:skill.id, treeId:'Dancer', skillId:id, nameKo:skill.nameKo, kind:'buff', source:'dancer', dataStatus:'partial', sourceRef:sourceRef,
      cost:{ mp:{ timing:'cast', value:v(mp) } }, combo:{ canStart:true, canReceiveTag:true },
      stackControl:{ stateId:stateId, minStacks:v(0), maxStacks:v(10), initialStacks:v(5), label:'춤 스택', sharedGroup:'dancerDance', sharedMaxBase:11 },
      stateTransitions:[{ event:'cast', operation:'setStacks', stateId:stateId, stacks:v(5), maxStacks:v(10), durationSeconds:v(15) }],
      effects:[]
    };
  }
  registry.register('Dancer', [
    dance(0, 100, 'dancerFairy'), dance(1, 200, 'dancerFrenzy'), dance(2, 500, 'dancerAstute'),
    dance(3, 300, 'dancerCharming'), dance(4, 300, 'dancerSpirited')
  ]);
}());
