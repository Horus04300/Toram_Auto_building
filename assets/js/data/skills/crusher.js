/* 크러셔: 원문 대조가 끝난 파괴자 버프 규칙. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('크러셔 스킬 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v = function (n) { return { op:'value', value:n }; };
  var r = function (path) { return { op:'ref', path:path }; };
  var l = function () { return r('skill.level'); };
  var m = function () { return { op:'multiply', args:[].slice.call(arguments) }; };
  var active = function () { return { op:'truthy', value:r('buff.active') }; };
  var knuckle = { op:'eq', left:r('equipment.mainWeapon'), right:v('권갑') };
  var skill = catalog.skills.find(function (item) { return item.id === 'Crusher:8'; });
  if (!skill) throw new Error('파괴자를 카탈로그에서 찾지 못했습니다.');
  registry.register('Crusher-core', [{
    id:skill.id, treeId:'Crusher', skillId:8, nameKo:skill.nameKo, kind:'buff', source:'crusher', dataStatus:'partial',
    sourceRef:{ file:'docs/sources/skills/Crusher.txt', anchor:'파괴자 버프 / 권갑 전용' }, requirements:{ when:knuckle },
    cost:{ mp:{ timing:'cast', value:v(100) } }, combo:{ canStart:false, canReceiveTag:true },
    stateTransitions:[{ event:'cast', operation:'grant', stateId:'crusherDestroyer', stacks:v(1), maxStacks:v(1), durationSeconds:v(600) }],
    effects:[
      { phase:'combat', type:'stat', key:'WATKP', when:active(), value:m(v(5), l()) },
      { phase:'combat', type:'stat', key:'STABILITY', when:active(), value:v(-10) },
      { phase:'combat', type:'crusherDestroyerState', when:active(), notes:'호흡법 강화, 셸 브레이크 파괴 확률 +25%, 기죽음·넘어짐·기절·넉백 부여 불가. 화경과 합산한 무기 공격력 증가는 최대 50%.' }
    ]
  }]);
}());
