(function () {
  'use strict';
  const R = window.ToramSkillEffectRegistry;
  const C = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!R || !C) throw new Error('Priest order');
  const v = value => ({ op: 'value', value });
  const r = path => ({ op: 'ref', path });
  const l = () => r('skill.level');
  const a = (...args) => ({ op: 'add', args });
  const m = (...args) => ({ op: 'multiply', args });
  const d = (left, right) => ({ op: 'divide', left, right });
  const q = (when, then, otherwise) => ({ op: 'if', when, then, else: otherwise });
  const I = id => r(`attack.inputs.${id}`);
  const B = stat => r(`baseStats.${stat}`);
  const T = stat => r(`combatStats.${stat}`);
  const eq = (left, right) => ({ op: 'eq', left, right });
  const any = (...args) => ({ op: 'any', args });
  const truthy = value => ({ op: 'truthy', value });
  const staff = eq(r('equipment.mainWeapon'), v('staff'));
  const shield = eq(r('equipment.subWeapon'), v('방패'));
  const magicDevice = eq(r('equipment.mainWeapon'), v('magicDevice'));
  const priestWeapon = any(eq(r('equipment.mainWeapon'), v('한손검')), staff, eq(r('equipment.mainWeapon'), v('권갑')));
  function definition(skillId, kind, anchor, requirement) {
    const catalog = C.skills.find(skill => skill.id === `Priest:${skillId}`);
    return { id: catalog.id, treeId: 'Priest', skillId, nameKo: catalog.nameKo, kind,
      source: 'priest', dataStatus: 'partial', sourceRef: { file: 'docs/sources/skills/Priest.txt', anchor },
      requirements: { when: requirement }, notes: 'S1~S5 calculator scope; party, healing, hit and time events remain metadata.' };
  }
  function hit(id, damageType, multiplier, constant, flags = {}) {
    return { id, damageType, count: v(1), multiplier, constant, flags: { longRange: false, unsheathe: false, ...flags } };
  }
  const skills = [
    definition(0, 'buff', '1차 브레스 버프 / 모든 무기 사용 가능', null),
    definition(1, 'buff', '2차 글로리아 버프 / 모든 무기 사용 가능', null),
    definition(2, 'passive', '3차 브레스 강화 패시브 / 모든 무기 사용 가능', null),
    definition(3, 'utility', '4차 하이네스 힐 액티브 / 모든 무기 사용 가능', null),
    definition(4, 'passive', '5차 신성한 가르침 패시브 / 모든 무기 사용 가능', null),
    definition(5, 'attack', '홀리 피스트 물리 + 마법 액티브', null),
    definition(6, 'attack', '홀리 라이트 마법 액티브', null),
    definition(7, 'buff', '에테르 코드 버프 / 모든 무기 사용 가능', null),
    definition(8, 'buff', '프리엘 버프 / 모든 무기 사용 가능', null),
    definition(9, 'passive', '아스피스 소울 패시브 / 모든 무기 사용 가능', null),
    definition(10, 'attack', '로드 스터프 물리 액티브', staff),
    definition(11, 'attack', '엑소시즘 마법 액티브', any(staff, shield)),
    definition(12, 'buff', '홀리 바이블 버프 / 한손검, 지팡이, 권갑 전용', priestWeapon),
    definition(13, 'attack', '네메시스 액티브 / 한손검, 지팡이, 권갑 전용', priestWeapon),
    definition(14, 'buff', '홀리 그레이스 버프 / 모든 무기 사용 가능', null)
  ];
  const breathMatkRate = q(eq(l(), v(1)), v(0), a(v(0.5), m(v(0.25), l())));
  skills[0] = { ...skills[0], activeBuff: true, cost: { mp: { timing: 'cast', value: v(100) } }, effects: [
    { phase: 'cast', type: 'healOverTime', intervalSeconds: v(5), initialTick: true, value: a(v(10), m(v(5), l()), m(T('MATK'), breathMatkRate)), staffBonus: a(m(T('MATK'), v(0.01)), m(T('INT'), v(0.05))), notes: '파티 HP 회복과 지팡이 보너스는 대상별 회복 엔진이 필요.' },
    { phase: 'combat', type: 'durationTier', seconds: [{ maxLevel: 3, value: 5 }, { maxLevel: 6, value: 10 }, { maxLevel: 9, value: 15 }, { maxLevel: 10, value: 20 }] }
  ] };
  skills[1] = { ...skills[1], activeBuff: true, cost: { mp: { timing: 'cast', value: v(100) } }, castTime: { type: 'fixed', seconds: v(1) }, effects: [
    { phase: 'combat', type: 'stat', key: 'DEF_P', value: a(v(50), m(m(l(), l()), v(1.5))), durationSeconds: v(30) },
    { phase: 'combat', type: 'stat', key: 'MDEF_P', value: a(v(50), m(m(l(), l()), v(1.5))), durationSeconds: v(30) },
    { phase: 'combat', type: 'guardRecoveryPercent', value: a(v(5), d(l(), v(2))), staffBonus: v(5), notes: '파티·방패 장착 대상 한정.' }
  ] };
  skills[2].effects = [{ phase: 'combat', type: 'blessEnhancement', notes: '브레스 레벨·강화 레벨 조합의 틱 회복/지속시간은 회복·시간 엔진 필요.' }];
  skills[3] = { ...skills[3], cost: { mp: { timing: 'cast', value: v(400) } }, castTime: { type: 'fixed', seconds: v(3) }, effects: [
    { phase: 'cast', type: 'partyHeal', value: a(m(v(500), l()), m(T('MAXHP'), d(a(v(10), m(v(2), l())), v(100)))), radius: a(v(7), m(v(0.3), l())), notes: '콤보 불가 및 재사용 중 회복 무효는 시간/파티 엔진 필요.' }
  ] };
  skills[4].effects = [{ phase: 'combat', type: 'temporaryHpOverflow', cap: m(v(1000), l()), notes: '회복 대상별 임시 HP·ATK/MATK 변환은 HP 상태 엔진 필요.' }];
  const holyFistBase = a(v(0.5), m(v(0.05), l()));
  skills[5] = { ...skills[5], cost: { mp: { timing: 'cast', value: v(100) } }, attacks: [
    hit('physical', 'physical', q(eq(r('equipment.mainWeapon'), v('권갑')), a(m(holyFistBase, v(2)), d(T('STR'), v(100))), holyFistBase), a(v(50), m(v(5), l())), { castRange: 1, element: 'light', mergedWith: 'magic' }),
    hit('magic', 'magic', q(staff, a(m(holyFistBase, v(2)), d(T('INT'), v(100))), holyFistBase), a(v(50), m(v(5), l())), { castRange: 1, element: 'light', mergedWith: 'physical' })
  ] };
  skills[6] = { ...skills[6], cost: { mp: { timing: 'cast', value: v(200) } }, castTime: { type: 'fixed', seconds: v(2) }, attacks: [
    hit('main', 'magic', m(a(v(1), m(v(0.15), l())), q(staff, a(v(1), d(B('INT'), v(50))), v(1))), v(200), { castRange: 12, element: 'light', magicPierceBonus: a(l(), q(magicDevice, v(30), v(0))) })
  ], effects: [{ phase: 'afterCast', type: 'hpRestore', value: m(T('MAXHP'), v(0.25)), cap: q(magicDevice, m(B('INT'), v(10)), m(v(100), l())) }] };
  skills[7] = { ...skills[7], activeBuff: true, cost: { mp: { timing: 'cast', value: v(300) } }, castTime: { type: 'fixed', seconds: v(4) }, effects: [{ phase: 'combat', type: 'stat', key: 'MATKP', value: m(v(-1), a(v(8), m(v(-0.3), l()))), durationSeconds: v(5) }, { phase: 'combat', type: 'aetherCode', flinchResistance: a(v(50), m(v(5), l())), durationSeconds: v(5) }] };
  skills[8] = { ...skills[8], activeBuff: true, cost: { mp: { timing: 'cast', value: v(500) } }, castTime: { type: 'fixed', seconds: v(1) }, effects: [{ phase: 'combat', type: 'stat', key: 'MATKP', value: a(l(), q(magicDevice, v(5), v(0))), durationSeconds: q(staff, v(75), v(25)), notes: '쇠약 제거 확률은 상태이상 엔진 필요.' }] };
  skills[9].effects = [{ phase: 'combat', type: 'aspisSoul', notes: '생존 파티원 수·대상 공격·상태이상 예방 시점은 전투/파티 엔진 필요.' }];
  skills[10] = { ...skills[10], cost: { mp: { timing: 'cast', value: v(100) } }, attacks: [
    hit('main', 'physical', a(v(1.9), m(v(0.01), l()), d(T('STR'), v(100))), v(100), { castRange: 7, physicalPierceBonus: a(v(25), d(B('STR'), v(10))), flinchChance: a(v(25), m(v(5), l())), shieldFlinchBonus: v(25) })
  ] };
  const exorcismEnhanced = any(truthy(I('targetDark')), truthy(I('nemesisActive')));
  skills[11] = { ...skills[11], inputs: [{ id: 'targetDark', type: 'boolean', default: false }, { id: 'nemesisActive', type: 'boolean', default: false }], cost: { mp: { timing: 'cast', value: v(200) } }, attacks: [
    hit('main', 'magic', q(exorcismEnhanced, a(v(3.95), m(v(0.25), l())), a(v(0.45), m(v(0.2), l()))), q(exorcismEnhanced, a(v(100), m(v(10), l())), m(v(10), l())), { castRange: 'unlimited', areaRadius: 4, element: 'light', magicDeviceDualElementWhen: 'nemesisActive' })
  ], stateTransitions: [{ event: 'cast', operation: 'grant', stateId: 'priest.exorcism.nextMpHalf', stacks: v(1), maxStacks: v(1), durationSeconds: v(0), effects: [{ type: 'nextSkillModifier', key: 'mpCostMultiplier', value: v(0.5) }] }] };
  skills[12] = { ...skills[12], activeBuff: true, cost: { mp: { timing: 'cast', value: v(100) } }, effects: [{ phase: 'combat', type: 'holyBible', darkResistance: v(5), holyLightTriggerChance: a(v(25), m(v(2.5), l())), shieldChanceMultiplier: v(2), cooldownSeconds: a(v(20), m(v(-1), l())), magicDeviceCooldownMultiplier: v(0.5), notes: '마법 적중·쿨다운·자동 홀리 라이트는 전투 이벤트 필요.' }] };
  skills[13] = { ...skills[13], inputs: [{ id: 'nemesisActive', type: 'boolean', default: false }, { id: 'nemesisStacks', type: 'number', min: v(0), max: v(20), default: v(0) }], cost: { mp: { timing: 'cast', value: v(200) } }, attacks: [
    hit('physical', 'physical', a(v(10), q(shield, d(T('STR'), v(100)), v(0))), m(v(60), l()), { castRange: 8, element: 'light', longRange: false }),
    { ...hit('magicCircle', 'magic', a(v(5), d(T('INT'), v(200))), m(v(30), l()), { areaRadius: q(magicDevice, v(4.5), v(2)), element: 'light', tickSeconds: 0.5, guaranteedCriticalAfterCritical: true }), count: I('nemesisStacks'), when: truthy(I('nemesisActive')) }
  ], stackControl: { stateId: 'priest.nemesis', minStacks: v(0), maxStacks: v(20), label: '신벌 스택' }, stateTransitions: [{ event: 'hit', operation: 'grant', stateId: 'priest.nemesis', stacks: v(1), maxStacks: v(20), durationSeconds: m(v(10), l()) }, { event: 'castWhenActive', when: truthy(I('nemesisActive')), operation: 'consumeStacks', stateId: 'priest.nemesis', stacks: I('nemesisStacks'), maxStacks: v(20) }], effects: [{ phase: 'combat', type: 'nemesisLink', notes: '대상 명중/16m 이탈/각 스킬별 스택 획득은 전투 대상 상태 엔진 필요.' }] };
  skills[14] = { ...skills[14], activeBuff: true, cost: { mp: { timing: 'cast', value: v(500) } }, effects: [{ phase: 'combat', type: 'holyGraceItemBuffPersistence', durationSeconds: m(v(10), l()) }], stateTransitions: [{ event: 'cast', operation: 'grant', stateId: 'priest.holyGrace.nextMpHalf', stacks: v(1), maxStacks: v(1), durationSeconds: v(0), effects: [{ type: 'nextSkillModifier', key: 'mpCostMultiplier', value: v(0.5) }] }] };
  R.register('Priest-s5', skills);
}());