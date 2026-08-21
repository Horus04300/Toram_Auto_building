(function () {
  'use strict';
  const R = window.ToramSkillEffectRegistry;
  const C = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!R || !C) throw new Error('Shield order');
  const v = value => ({ op: 'value', value });
  const r = path => ({ op: 'ref', path });
  const l = () => r('skill.level');
  const a = (...args) => ({ op: 'add', args });
  const m = (...args) => ({ op: 'multiply', args });
  const d = (left, right) => ({ op: 'divide', left, right });
  const q = (when, then, otherwise) => ({ op: 'if', when, then, else: otherwise });
  const I = id => r(`attack.inputs.${id}`);
  const B = stat => r(`baseStats.${stat}`);
  const eq = (left, right) => ({ op: 'eq', left, right });
  const truthy = value => ({ op: 'truthy', value });
  const shield = eq(r('equipment.subWeapon'), v('방패'));
  function definition(skillId, kind, anchor, requirement) {
    const catalog = C.skills.find(skill => skill.id === `Shield:${skillId}`);
    return {
      id: catalog.id, treeId: 'Shield', skillId, nameKo: catalog.nameKo, kind,
      source: 'shield', dataStatus: 'partial',
      sourceRef: { file: 'docs/sources/skills/Shield.txt', anchor },
      requirements: { when: requirement },
      notes: 'S1~S5 calculator scope; guard, hit, party and time events remain metadata.'
    };
  }
  function hit(id, multiplier, constant, flags = {}) {
    return { id, damageType: 'physical', count: v(1), multiplier, constant,
      flags: { longRange: false, unsheathe: false, ...flags } };
  }
  const skills = [
    definition(0, 'passive', '실드 마스터리 패시브', shield),
    definition(1, 'attack', '실드 배쉬 물리 액티브', shield),
    definition(2, 'attack', '실드 캐논 물리 액티브', shield),
    definition(3, 'passive', '가드 스트라이크 패시브', null),
    definition(4, 'passive', '포스 실드 패시브', shield),
    definition(5, 'passive', '매지컬 실드 패시브', shield),
    definition(6, 'attack', '실드 어퍼컷 물리 액티브', shield),
    definition(7, 'buff', '듀얼 실드 버프', shield),
    definition(8, 'utility', '실드 리페어 액티브', shield),
    definition(9, 'attack', '5차 벨라겔룸 물리 액티브', { op: 'all', args: [shield, truthy(I('dualShieldActive'))] }),
    definition(10, 'buff', '프로텍션 버프', null),
    definition(11, 'buff', '이지스 버프', null),
    definition(12, 'buff', '가디언 버프', shield)
  ];
  skills[0].effects = [{ phase: 'build', type: 'shieldAspdPenaltyReduction', value: m(v(5), l()) }];
  skills[1] = { ...skills[1], cost: { mp: { timing: 'cast', value: v(100) } }, attacks: [
    hit('main', m(v(0.015), l()), a(v(50), m(v(5), l())), { castRange: 3, stunChance: a(v(75), m(v(2.5), l())) })
  ] };
  const minimumRefine = { op: 'max', args: [v(1), r('equipment.subWeaponRefinement')] };
  skills[2] = { ...skills[2], inputs: [{ id: 'stunSuccess', type: 'boolean', default: false }], cost: { mp: { timing: 'cast', value: v(200) } }, attacks: [
    hit('main',
      q(truthy(I('stunSuccess')), m(a(v(0.5), m(v(0.1), l())), minimumRefine), a(v(0.5), m(v(0.1), l()))),
      q(truthy(I('stunSuccess')), a(v(100), m(v(10), l()), m(B('VIT'), d(minimumRefine, v(3)))), a(v(100), m(v(10), l()))),
      { castRange: a(v(5), m(v(1.5), l())) }
    )
  ] };
  skills[3] = { ...skills[3], specialAttacks: [{ id: 'guardStrike', hits: [hit('main', m(v(0.1), l()), m(v(10), l()))] }], effects: [
    { phase: 'combat', type: 'guardStrikeShieldBonus', notes: '가드 성공 시 가드력/제련치 보정은 피격 엔진 필요.' }
  ] };
  skills[4].effects = [{ phase: 'build', type: 'stat', key: 'DEF', value: m(v(2), l()) }, { phase: 'build', type: 'stat', key: 'DEF_P', value: l() }, { phase: 'build', type: 'stat', key: 'MAXHP', value: m(v(50), l()) }, { phase: 'build', type: 'stat', key: 'PHYS_RES', value: l() }];
  skills[5].effects = [{ phase: 'build', type: 'stat', key: 'MDEF', value: m(v(2), l()) }, { phase: 'build', type: 'stat', key: 'MDEF_P', value: l() }, { phase: 'build', type: 'stat', key: 'MAXHP', value: m(v(50), l()) }, { phase: 'build', type: 'stat', key: 'MAG_RES', value: l() }];
  skills[6] = { ...skills[6], inputs: [{ id: 'tumbleSuccess', type: 'boolean', default: false }], cost: { mp: { timing: 'cast', value: v(100) } }, attacks: [
    hit('main', a(m(v(0.15), l()), q(truthy(I('tumbleSuccess')), m(m(v(0.01), l()), r('equipment.subWeaponRefinement')), v(0))), v(100), { castRange: 4, tumbleChance: m(v(10), l()) })
  ] };
  skills[7] = { ...skills[7], cost: { mp: { timing: 'cast', value: v(300) } }, activeBuff: true, effects: [
    { phase: 'combat', type: 'dualShieldNormalMode', multiplier: a(m(v(0.1), l()), d(B('VIT'), v(500))), notes: '통상 모션·자동 가드·가드력 종료는 전투 이벤트 필요.' }
  ] };
  skills[8] = { ...skills[8], cost: { mp: { timing: 'cast', value: v(200) } }, castTime: { type: 'fixed', seconds: v(1), affectedByCastSpeed: false }, effects: [
    { phase: 'cast', type: 'guardPowerRestorePercent', value: a(v(10), m(v(4), l())) },
    { phase: 'cast', type: 'mpRestoreFromActualGuardRecovery', divisor: v(10) }
  ] };
  skills[9] = { ...skills[9], inputs: [{ id: 'dualShieldActive', type: 'boolean', default: false }, { id: 'targetIncapacitated', type: 'boolean', default: false }], cost: { mp: { timing: 'cast', value: v(600) } }, attacks: [
    { ...hit('main', q(truthy(I('targetIncapacitated')), a(v(6), m(v(0.525), l())), a(v(4), m(v(0.35), l()))), q(truthy(I('targetIncapacitated')), a(v(100), m(v(10), l()), m(B('VIT'), a(v(1), d(r('equipment.subWeaponRefinement'), v(5))))), a(v(100), m(v(10), l()))), { areaRadius: 4 }), count: v(2) }
  ], stateTransitions: [{ event: 'cast', operation: 'clearStacks', stateId: 'shield.dualShield', stacks: v(1), maxStacks: v(1) }] };
  skills[10] = { ...skills[10], cost: { mp: { timing: 'cast', value: q(shield, v(100), v(300)) } }, activeBuff: true, effects: [{ phase: 'combat', type: 'protectionResistance', physical: [15, 20, 25, 30], magicPenalty: [30, 25, 20, 15], durationSeconds: m(v(60), l()) }] };
  skills[11] = { ...skills[11], cost: { mp: { timing: 'cast', value: q(shield, v(100), v(300)) } }, activeBuff: true, effects: [{ phase: 'combat', type: 'aegisResistance', magic: [15, 20, 25, 30], physicalPenalty: [30, 25, 20, 15], durationSeconds: m(v(60), l()) }] };
  skills[12] = { ...skills[12], cost: { mp: { timing: 'cast', value: v(600) } }, activeBuff: true, effects: [{ phase: 'combat', type: 'guardianAura', notes: '연결 아군 수·방패 제련·3초 어그로·파티 분산은 전투 상태 엔진 필요.' }] };
  R.register('Shield-s5', skills);
}());