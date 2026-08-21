/* 어새신 쉐도우 워크의 원문 대조 스택·avoid 공격 규칙. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('어새신 스택 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v = function (n) { return { op:'value', value:n }; };
  var r = function (path) { return { op:'ref', path:path }; };
  var l = function () { return r('skill.level'); };
  var a = function () { return { op:'add', args:[].slice.call(arguments) }; };
  var m = function () { return { op:'multiply', args:[].slice.call(arguments) }; };
  var d = function (left, right) { return { op:'divide', left:left, right:right }; };
  var tier = function (cases) { return { op:'tier', cases:cases }; };
  var between = function (min, max, value) { return { when:{ op:'all', args:[{ op:'gte', left:r('buff.stacks'), right:v(min) }, { op:'lte', left:r('buff.stacks'), right:v(max) }] }, value:value }; };
  var daggerOrNinja = { op:'any', args:[{ op:'eq', left:r('equipment.subWeapon'), right:v('단검') }, { op:'eq', left:r('equipment.subWeapon'), right:v('인술 두루마리') }] };
  var skill = catalog.skills.find(function (item) { return item.id === 'Assassin:8'; });
  if (!skill) throw new Error('쉐도우 워크를 카탈로그에서 찾지 못했습니다.');
  registry.register('Assassin-stack-buff', [{
    id:skill.id, treeId:'Assassin', skillId:8, nameKo:skill.nameKo, kind:'buff', source:'assassin', dataStatus:'partial',
    sourceRef:{ file:'docs/sources/skills/Assassin.txt', anchor:'쉐도우 워크 버프 / 단검, 인술 두루마리 전용' }, requirements:{ when:daggerOrNinja },
    stackRole:'combat-resource', cost:{ mp:{ timing:'cast', value:v(100) } }, activeBuff:true,
    stackControl:{ stateId:'assassinShadowWalk', minStacks:v(0), maxStacks:a(v(10),l()), initialStacks:l(), label:'쉐도우 스택' },
    stackModel:{ mode:'avoid-resource', hardCap:a(v(10),l()), initialStacks:l(), gainEvents:['manualAvoid:+1','assassinStepSide:+1','assassinStepBack:+2','backstep:+3'], clearEvents:['targetedEnemyHit'], notes:'어그로 대상·피격·avoid 성공에 따른 자동 증감은 전투 상태 엔진이 필요하다.' },
    stateTransitions:[{ event:'cast', operation:'setStacks', stateId:'assassinShadowWalk', stacks:l(), maxStacks:a(v(10),l()), durationSeconds:v(180) }, { event:'avoidSuccessAt10Stacks', operation:'consumeStacks', stateId:'assassinShadowWalk', stacks:v(10), maxStacks:a(v(10),l()) }],
    specialAttacks:[
      { id:'shadowAvoid', hits:[{ id:'normal', damageType:'physical', count:v(1), multiplier:m(a(v(1),m(v(.1),l())),d(r('equipment.subWeaponAttack'),v(100)),tier([between(1,4,v(1)),between(5,8,v(1.25)),between(9,12,v(1.5)),between(13,16,v(1.75)),between(17,20,v(2))])), constant:v(100), flags:{ longRange:false, unsheathe:false } }], notes:'어그로 대상이 아닌 적의 무기 사거리 내에서 avoid 시 발동.' },
      { id:'shadowAvoidEnhanced', hits:[{ id:'enhanced', damageType:'physical', count:v(1), multiplier:a(v(10),m(v(2),l())), constant:v(100), flags:{ longRange:false, unsheathe:false, invincibilityDuringAvoid:true } }], notes:'10스택 이상에서 avoid로 공격 회피 성공 시 10스택 소비.' }
    ]
  }]);
}());