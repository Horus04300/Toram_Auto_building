/* 크러셔 S1~S5 계산기 범위 정의. 시간·피격 자동 전이는 메타데이터로 보존한다. */
(function () {
  'use strict';
  var R = window.ToramSkillEffectRegistry, C = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!R || !C) throw new Error('Crusher S5 data order');
  var v = function (x) { return { op:'value', value:x }; };
  var r = function (x) { return { op:'ref', path:x }; };
  var l = function () { return r('skill.level'); };
  var a = function () { return { op:'add', args:[].slice.call(arguments) }; };
  var m = function () { return { op:'multiply', args:[].slice.call(arguments) }; };
  var d = function (x, y) { return { op:'divide', left:x, right:y }; };
  var q = function (w, y, n) { return { op:'if', when:w, then:y, else:n }; };
  var eq = function (x, y) { return { op:'eq', left:x, right:y }; };
  var i = function (x) { return r('attack.inputs.' + x); };
  var total = function (x) { return r('combatStats.' + x); };
  var base = function (x) { return r('baseStats.' + x); };
  var active = function () { return { op:'truthy', value:r('buff.active') }; };
  var truthy = function (x) { return { op:'truthy', value:x }; };
  var gt = function (x, y) { return { op:'gt', left:x, right:y }; };
  var gte = function (x, y) { return { op:'gte', left:x, right:y }; };
  var all = function () { return { op:'all', args:[].slice.call(arguments) }; };
  var knuckle = { op:'eq', left:r('equipment.mainWeapon'), right:v('권갑') };
  function definition(id, kind, anchor, requirement) {
    var skill = C.skills.find(function (item) { return item.id === 'Crusher:' + id; });
    if (!skill) throw new Error('Crusher catalog missing: ' + id);
    return { id:skill.id, treeId:'Crusher', skillId:id, nameKo:skill.nameKo, kind:kind, source:'crusher', dataStatus:'partial', sourceRef:{ file:'docs/sources/skills/Crusher.txt', anchor:anchor }, requirements:{ when:requirement }, notes:'S1~S5 calculator scope; automatic combat events remain metadata.' };
  }
  function hit(id, multiplier, constant, flags) { return { id:id, damageType:'physical', count:v(1), multiplier:multiplier, constant:constant, flags:Object.assign({ longRange:true, unsheathe:false }, flags || {}) }; }
  var x = [
    definition(0, 'attack', '1차 정권 찌르기 물리 액티브 / 메인 권갑 전용', knuckle),
    definition(1, 'attack', '2차 골리아스테이크 샷 물리 액티브 / 메인 권갑 전용', knuckle),
    definition(2, 'attack', '3차갓 핸드 물리 액티브 / 메인 권갑 전용', knuckle),
    definition(3, 'passive', '4차 신강체 패시브 / 메인 권갑 전용', knuckle),
    definition(4, 'buff', '호흡법 버프 / 권갑 전용', knuckle),
    definition(5, 'attack', '플로팅 킥 물리 액티브 / 권갑 전용', knuckle),
    definition(6, 'attack', '가이저 슛 물리 액티브 / 메인 권갑 전용', knuckle),
    definition(7, 'attack', '콤비네이션 물리 액티브 / 메인 권갑 전용', knuckle),
    null,
    definition(9, 'attack', '지오크러셔 물리 액티브 / 메인 권갑 전용', knuckle)
  ];

  x[0] = Object.assign(x[0], { cost:{ mp:{ timing:'cast', value:v(300) } }, attacks:[hit('main', a(v(2), m(v(.2), l())), v(200), { guaranteedCritical:true })], effects:[{ phase:'combat', type:'motionDamageReduction', maxHpPercent:v(25), uses:v(1) }] });
  x[1] = Object.assign(x[1], {
    inputs:[{ id:'charging', label:'충전으로 사용', type:'boolean', default:false }, { id:'goliathStacks', label:'골리아 스택', type:'number', min:v(0), max:v(5), default:v(0) }, { id:'godHandStacks', label:'갓 핸드 스택', type:'number', min:v(0), max:v(3), default:v(0) }],
    cost:{ mp:{ timing:'cast', value:q(truthy(i('charging')), v(500), v(0)) } }, activeBuff:true,
    stackControl:{ stateId:'crusher.goliath', minStacks:v(0), maxStacks:v(5), initialStacks:v(0), label:'골리아 스택' },
    stackModel:{ mode:'charge-resource', hardCap:v(5), chargeIntervalSeconds:{ byLevel:['1:3','2-3:2.5','4-6:2','7-9:1.5','10:1'] }, decayAfterMaxSeconds:a(v(2),l()), decayIntervalSeconds:v(6), notes:'충전·피해·행동 불능 이벤트에 따른 자동 증감은 현재 엔진 미지원.' },
    stateTransitions:[{ event:'castWhenCharging', operation:'grant', stateId:'crusher.goliath', stacks:v(0), maxStacks:v(5), durationSeconds:v(0) }, { event:'crusherSkillDamage', operation:'addStacks', stateId:'crusher.goliath', stacks:v(1), maxStacks:v(5), requires:['Crusher:3','Crusher:8'] }],
    attacks:[Object.assign(hit('main',a(v(8),m(a(v(3),m(v(.1),l())),i('goliathStacks')),m(v(.1),r('investments.Crusher.2'),i('godHandStacks'),a(i('goliathStacks'),v(1)))),v(500)),{when:{op:'not',value:truthy(i('charging'))},flags:{longRange:true,unsheathe:false,areaRadius:2}})]
  });
  x[2] = Object.assign(x[2], { cost:{ mp:{ timing:'cast', value:v(400) } }, activeBuff:true, stackControl:{ stateId:'crusher.godHand', minStacks:v(0), maxStacks:v(3), initialStacks:v(0), label:'갓 핸드 스택' }, stackModel:{ mode:'combat-resource', hardCap:v(3), durationSeconds:v(60), gainEvents:['damageReductionSuccess','godHandDamageReduction'], notes:'피격 피해 감소 성공에 따라 자동 누적되는 스택은 전투 상태 엔진이 필요하다.' }, stateTransitions:[{ event:'damageReductionSuccess', operation:'addStacks', stateId:'crusher.godHand', stacks:v(1), maxStacks:v(3), durationSeconds:v(60) }], attacks:[hit('main',v(10),m(v(40),l()))], effects:[{ phase:'combat', type:'motionDamageReduction', byLevel:[9,10,13,18,25,34,45,58,73,90] }, { phase:'combat', type:'crusherSkillMultiplierPerStack', value:m(v(.1),l()), excludes:['Crusher:1','Crusher:9','Crusher:2'] }] });
  x[3] = Object.assign(x[3], { effects:[{ phase:'combat', type:'godHandPercentDamageReduction', byLevel:[10,13,17,22,28,36,45,57,72,90] }, { phase:'combat', type:'mpRestore', value:v(200), capPerGodHandUse:v(400), trigger:'godHandDamageReductionSuccess' }, { phase:'combat', type:'surviveLethalDamage', value:v(1), trigger:'godHandMotion' }], stateTransitions:[{ event:'godHandDamageReductionSuccess', operation:'clearCooldown', stateId:'crusher.breathwork', except:'invincibilityBlocked' }] });
  var destroyerLevel10=eq(r('investments.Crusher.8'),v(10)), destroyerBonus=q(destroyerLevel10,v(1),v(0));
  x[4] = Object.assign(x[4], { cost:{ mp:{ timing:'cast', value:v(300) } }, stateTransitions:[{ event:'cast', operation:'grant', stateId:'crusher.breathwork', stacks:v(1), maxStacks:v(1), durationSeconds:v(0), effects:[{ type:'nextSkillModifier', key:'mpCostMultiplier', when:destroyerLevel10, value:v(.5) }] }], effects:[{ phase:'cast', type:'hpRestorePercent', value:a(l(),destroyerBonus) , notes:'파괴자 Lv.10 보너스는 스킬 탭의 실제 투자 레벨을 사용한다.' }, { phase:'nextSkillCast', type:'hpRestorePercent', value:a(m(v(.5),l()),destroyerBonus) }, { phase:'combat', type:'cooldown', seconds:v(30), recastRecoveryPercent:v(1) }] });
  x[5] = Object.assign(x[5], { inputs:[{ id:'commandInput', label:'커맨드 입력', type:'boolean', default:false }], cost:{ mp:{ timing:'cast', value:v(200) } }, attacks:[hit('main',a(v(5),m(v(.2),l())),a(v(100),m(v(10),l())),{ castRange:7, minimumCriticalDamage:200, guaranteedHitWhen:'commandInput' })] });
  x[6] = Object.assign(x[6], { inputs:[{ id:'distance', label:'시전 거리(m)', type:'number', min:v(0), max:v(30), default:v(0) }], cost:{ mp:{ timing:'cast', value:v(300) } }, attacks:[hit('main',a(v(9),m(v(.1),l()),d(total('AGI'),v(200)),q(gte(i('distance'),v(8)),m(v(.5),l()),v(0))),a(v(200),m(v(10),l())),{ castRange:12, physicalPierceBonus:m(v(2),l()) })], stateTransitions:[{ event:'castWhenRangeAtLeast8', operation:'trigger', stateId:'crusher.breathwork', notes:'습득한 호흡법을 자동 발동; 회복·쿨다운은 시간 상태 엔진 필요.' }] });
  x[7] = Object.assign(x[7], { cost:{ mp:{ timing:'cast', value:v(0) } }, combo:{ canStart:false, canReceiveTag:true }, attacks:[hit('main',a(v(1),m(v(.1),l())),v(0),{ criticalChanceBonus:m(l(),l()), normalProration:true })] });
  x[9] = Object.assign(x[9], { inputs:[{ id:'targetBroken', label:'대상 파괴', type:'boolean', default:false }, { id:'godHandStacks', label:'갓 핸드 스택', type:'number', min:v(0), max:v(3), default:v(0) }], cost:{ mp:{ timing:'cast', value:v(800) } }, attacks:[hit('main',a(v(9),m(v(.6),l()),d({ op:'max', args:[base('STR'),base('AGI')] },v(100))),a(v(700),m(v(10),l())),{ areaRadius:4, guaranteedCriticalWhen:'destroyerActive && targetBroken' })], effects:[{ phase:'afterCast', type:'mpRestore', value:m(i('godHandStacks'),v(100)) }, { phase:'afterCast', type:'barrierFromLostHp', durationSeconds:v(10), absorptionPercent:v(90), refreshable:false }] });
  R.register('Crusher-s5', x.filter(Boolean));
}());
