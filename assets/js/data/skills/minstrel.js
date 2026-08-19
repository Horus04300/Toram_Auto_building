/* 민스트럴: 시간 경과형 노래 스택 버프. 원문 캐시: docs/sources/skills/Minstrel.txt */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('민스트럴 효과 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v = function (n) { return { op:'value', value:n }; };
  var r = function (path) { return { op:'ref', path:path }; };
  var l = function () { return r('skill.level'); };
  var m = function () { return { op:'multiply', args:[].slice.call(arguments) }; };
  function base(id, stateId, max, sourceRef, effects) {
    var skill = catalog.skills.find(function (item) { return item.id === 'Minstrel:' + id; });
    if (!skill) throw new Error('민스트럴 스킬을 카탈로그에서 찾지 못했습니다: ' + id);
    return {
      id:skill.id, treeId:'Minstrel', skillId:id, nameKo:skill.nameKo, kind:'buff', source:'minstrel', dataStatus:'partial', sourceRef:sourceRef,
      cost:{ mp:{ timing:'cast', value:v(200) } }, combo:{ canStart:true, canReceiveTag:true },
      stackControl:{ stateId:stateId, minStacks:v(0), maxStacks:v(max), initialStacks:v(0), label:'노래 스택' },
      stateTransitions:[{ event:'cast', operation:'setStacks', stateId:stateId, stacks:v(0), maxStacks:v(max) }], effects:effects
    };
  }
  registry.register('Minstrel', [
    base(4, 'minstrelLifeSong', 50, { file:'docs/sources/skills/Minstrel.txt', anchor:'최대 50스택까지 1스택이 쌓인다.' }, [{ phase:'combat', type:'stat', key:'MAXHP', value:m(v(50), l(), r('buff.stacks')) }]),
    base(5, 'minstrelFantasySong', 9, { file:'docs/sources/skills/Minstrel.txt', anchor:'최대 9스택' }, [{ phase:'cast', type:'resourceRestore', key:'MP', value:m(v(100), r('buff.stacks')) }])
  ]);
}());
