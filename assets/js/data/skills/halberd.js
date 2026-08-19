/* 할버드: 원문 대조가 끝난 신속의 수도의 누적 버프 규칙. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('할버드 스킬 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v = function (n) { return { op:'value', value:n }; };
  var r = function (path) { return { op:'ref', path:path }; };
  var l = function () { return r('skill.level'); };
  var a = function () { return { op:'add', args:[].slice.call(arguments) }; };
  var m = function () { return { op:'multiply', args:[].slice.call(arguments) }; };
  var s = function (left, right) { return { op:'subtract', left:left, right:right }; };
  var i = function (when, yes, no) { return { op:'if', when:when, then:yes, else:no }; };
  var eq = function (left, right) { return { op:'eq', left:left, right:right }; };
  var neg = function (value) { return m(v(-1), value); };
  var skill = catalog.skills.find(function (item) { return item.id === 'Halberd:19'; });
  if (!skill) throw new Error('신속의 수도를 카탈로그에서 찾지 못했습니다.');
  var stacks = r('buff.stacks');
  var halberd = eq(r('equipment.mainWeapon'), v('선풍창'));
  var resistanceDecrease = m(s(v(100), m(v(3), l())), i(halberd, v(.55), v(1)), stacks);
  registry.register('Halberd-stack-buff', [{
    id:skill.id, treeId:'Halberd', skillId:19, nameKo:skill.nameKo, kind:'buff', source:'halberd', dataStatus:'partial',
    sourceRef:{ file:'docs/sources/skills/Halberd.txt', anchor:'신속의 수도 버프 / 모든 무기 사용 가능' },
    stackRole:'active-buff', cost:{ mp:{ timing:'cast', value:v(100) } },
    stackControl:{ stateId:'halberdGodspeedWield', minStacks:v(0), maxStacks:v(3), initialStacks:v(1), label:'신속 스택' },
    stackModel:{ mode:'recast-stack', hardCap:v(3), endsOnHit:true, notes:'시전마다 1스택을 얻고, 피격 시 버프가 종료된다. 선풍창은 지속시간 +30초 및 내성 감소량 45% 완화.' },
    stateTransitions:[
      { event:'cast', operation:'addStacks', stateId:'halberdGodspeedWield', stacks:v(1), maxStacks:v(3), durationSeconds:a(v(10), m(v(2), l()), i(halberd, v(30), v(0))) },
      { event:'takeHit', operation:'clearStacks', stateId:'halberdGodspeedWield', stacks:v(0), maxStacks:v(3) }
    ],
    effects:[
      { phase:'combat', type:'stat', key:'ASPD', value:m(a(m(v(30), l()), i(halberd, v(100), v(0))), stacks) },
      { phase:'combat', type:'stat', key:'MOTIONSPEED', value:m(l(), stacks) },
      { phase:'combat', type:'stat', key:'AVOID_RECHARGE', value:m(l(), stacks) },
      { phase:'combat', type:'stat', key:'MAXMP', value:m(v(-100), stacks) },
      { phase:'combat', type:'stat', key:'PHYS_RES', value:neg(resistanceDecrease) },
      { phase:'combat', type:'stat', key:'MAG_RES', value:neg(resistanceDecrease) }
    ]
  }]);
}());

