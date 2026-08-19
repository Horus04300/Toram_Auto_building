/* 듀얼소드: 원문 대조가 끝난 패시브와 세이버 오라 상태 규칙. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('듀얼소드 스킬 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v = function (n) { return { op:'value', value:n }; };
  var r = function (path) { return { op:'ref', path:path }; };
  var l = function () { return r('skill.level'); };
  var a = function () { return { op:'add', args:[].slice.call(arguments) }; };
  var m = function () { return { op:'multiply', args:[].slice.call(arguments) }; };
  var s = function (left, right) { return { op:'subtract', left:left, right:right }; };
  var tier = function (cases) { return { op:'tier', cases:cases }; };
  var between = function (min, max, value) { return { when:{ op:'all', args:[{ op:'gte', left:l(), right:v(min) }, { op:'lte', left:l(), right:v(max) }] }, value:value }; };
  var all = function () { return { op:'all', args:[].slice.call(arguments) }; };
  var eq = function (left, right) { return { op:'eq', left:left, right:right }; };
  var dualSword = all(eq(r('equipment.mainWeapon'), v('한손검')), eq(r('equipment.subWeapon'), v('한손검(듀얼소드)')));
  var stacks = r('buff.stacks');
  function get(id) {
    var skill = catalog.skills.find(function (item) { return item.id === id; });
    if (!skill) throw new Error(id + '를 카탈로그에서 찾지 못했습니다.');
    return skill;
  }
  var mastery = get('DualSword:0');
  var control = get('DualSword:14');
  var speed = get('DualSword:15');
  var saber = get('DualSword:16');
  var agi = tier([between(1, 5, l()), between(6, 10, s(m(v(2), l()), v(5)))]);
  var saberInterval = tier([between(1, 2, v(6)), between(3, 4, v(5)), between(5, 6, v(4)), between(7, 8, v(3)), between(9, 10, v(2))]);
  registry.register('DualSword-core', [
    {
      id:mastery.id, treeId:'DualSword', skillId:0, nameKo:mastery.nameKo, kind:'passive', source:'dualSword', dataStatus:'partial',
      sourceRef:{ file:'docs/sources/skills/DualSword.txt', anchor:'1차 듀얼 마스터리 패시브 / 쌍검 전용' }, requirements:{ when:dualSword },
      effects:[
        { phase:'build', type:'stat', key:'HIT_P', value:a(v(-55), m(v(3), l())) },
        { phase:'build', type:'stat', key:'CRIT_P', value:a(v(-55), m(v(3), l())) }
      ]
    },
    {
      id:control.id, treeId:'DualSword', skillId:14, nameKo:control.nameKo, kind:'passive', source:'dualSword', dataStatus:'partial',
      sourceRef:{ file:'docs/sources/skills/DualSword.txt', anchor:'쌍검 단련 패시브 / 쌍검 전용' }, requirements:{ when:dualSword },
      effects:[
        { phase:'build', type:'stat', key:'ASPD', value:m(v(50), l()) },
        { phase:'build', type:'stat', key:'HIT_P', value:a(v(5), m(v(3), l())) },
        { phase:'build', type:'stat', key:'CRIT_P', value:a(v(5), m(v(3), l())) }
      ]
    },
    {
      id:speed.id, treeId:'DualSword', skillId:15, nameKo:speed.nameKo, kind:'passive', source:'dualSword', dataStatus:'partial',
      sourceRef:{ file:'docs/sources/skills/DualSword.txt', anchor:'신속의 저력 패시브 / 모든 무기 사용 가능' },
      effects:[
        { phase:'build', type:'stat', key:'UNSHEATHE', value:a(v(5), l()) },
        { phase:'build', type:'stat', key:'UNSHEATHE', when:dualSword, value:v(10) },
        { phase:'build', type:'stat', key:'AGI', value:agi }
      ]
    },
    {
      id:saber.id, treeId:'DualSword', skillId:16, nameKo:saber.nameKo, kind:'buff', source:'dualSword', dataStatus:'partial',
      sourceRef:{ file:'docs/sources/skills/DualSword.txt', anchor:'세이버 오러 버프 / 쌍검 전용' }, requirements:{ when:dualSword },
      stackRole:'combat-resource', combo:{ canStart:false, canReceiveTag:true }, cost:{ mp:{ timing:'cast', value:v(900) } },
      stackModel:{ mode:'unbounded-hp-terminated', hardCap:null, initialStacks:v(1), incrementIntervalSeconds:saberInterval, termination:'현재 HP 5% 미만', recastAllowed:false, notes:'고정 최대 스택은 없으며, 종료 시 현재 스택 비례 HP 회복 후 스택 비례 쿨타임에 들어간다.' },
      stateTransitions:[
        { event:'cast', operation:'setStacks', stateId:'dualSwordSaberAura', stacks:v(1), durationSeconds:v(0) },
        { event:'timeElapsed', operation:'addStacks', stateId:'dualSwordSaberAura', stacks:v(1), intervalSeconds:saberInterval },
        { event:'hpBelowPercent', operation:'clearStacks', stateId:'dualSwordSaberAura', thresholdPercent:v(5), effects:[{ type:'resourceRestorePercent', key:'HP', value:m(v(5), stacks) }, { type:'cooldown', durationSeconds:a(v(10), stacks) }] }
      ],
      effects:[
        { phase:'combat', type:'movementSpeedMultiplier', value:v(2), notes:'축지법 사용 불가' },
        { phase:'combat', type:'stat', key:'ASPD_P', value:m(v(10), l(), stacks) },
        { phase:'combat', type:'stat', key:'HIT', value:m(v(5), l(), stacks) },
        { phase:'combat', type:'stat', key:'AMPR', value:m({ op:'ceil', value:m(v(.5), l()) }, stacks) },
        { phase:'combat', type:'hpDrainPercentPerSecond', value:a(s(v(25), m(v(2), l())), m(v(5), s(stacks, v(1)))) },
        { phase:'combat', type:'surviveLethalDamage', value:v(1), notes:'사망에 이르는 공격을 HP 1로 생존' }
      ]
    }
  ]);
}());
