/* 스프라이트 아스트랄 랜스의 원문 대조 스택·발사 규칙. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('스프라이트 스택 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v = function (n) { return { op:'value', value:n }; };
  var r = function (path) { return { op:'ref', path:path }; };
  var l = function () { return r('skill.level'); };
  var a = function () { return { op:'add', args:[].slice.call(arguments) }; };
  var m = function () { return { op:'multiply', args:[].slice.call(arguments) }; };
  var d = function (left, right) { return { op:'divide', left:left, right:right }; };
  var magicDevice = { op:'eq', left:r('equipment.mainWeapon'), right:v('magicDevice') };
  var skill = catalog.skills.find(function (item) { return item.id === 'Sprite:9'; });
  if (!skill) throw new Error('아스트랄 랜스를 카탈로그에서 찾지 못했습니다.');
  registry.register('Sprite-stack-buff', [{
    id:skill.id, treeId:'Sprite', skillId:9, nameKo:skill.nameKo, kind:'buff', source:'sprite', dataStatus:'partial',
    sourceRef:{ file:'docs/sources/skills/Sprite.txt', anchor:'아스트랄 랜스 버프 / 메인 마도구 전용' }, requirements:{ when:magicDevice },
    stackRole:'combat-resource', cost:{ mp:{ timing:'cast', value:v(500) } }, castTime:{ type:'fixed', seconds:v(2), affectedByCastSpeed:true }, activeBuff:true,
    stackControl:{ stateId:'spriteAstralLance', minStacks:v(0), maxStacks:v(5), initialStacks:v(0), label:'아스트랄 스택' },
    stackModel:{ mode:'mp-spend-resource', hardCap:v(5), gainPerMp:v(100), consumeAtCap:v(5), concurrentProjectileCap:v(1), overflowCarry:true, notes:'MP 사용·투사체 종료·자동 발동을 시간/전투 상태 엔진이 처리하지 않는다.' },
    stateTransitions:[
      { event:'cast', operation:'setStacks', stateId:'spriteAstralLance', stacks:v(0), maxStacks:v(5), durationSeconds:v(90) },
      { event:'mpSpent', operation:'addStacks', stateId:'spriteAstralLance', stacks:v(1), maxStacks:v(5), perResource:v(100) },
      { event:'stacksAtCap', operation:'consumeStacks', stateId:'spriteAstralLance', stacks:v(5), maxStacks:v(5), effects:[{ type:'specialAttack', id:'astralLance' }] }
    ],
    specialAttacks:[{ id:'astralLance', hits:[{ id:'main', damageType:'magic', count:v(1), multiplier:a(v(2.5),m(v(.5),l())), constant:v(500), flags:{ longRange:false, unsheathe:false, areaRadius:1, physicalPierceBonus:d(m(l(),l()),v(2)) }}], notes:'5스택 도달 시 자동 발사. 콤보 피해 변화는 적용하지 않는다.' }]
  }]);
}());