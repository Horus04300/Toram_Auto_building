/* 사용자 제공 콤보 원문을 구조화한 공통 콤보 규칙 데이터. */
(function () {
  'use strict';
  window.TORAM_COMBO_RULE_DATA = Object.freeze({
    schemaVersion: 1,
    source: Object.freeze({ type: 'user-provided', description: '게임 내 콤보 도움말 본문 전사' }),
    constants: Object.freeze({
      firstTaggablePosition: 2,
      damageMultiplier: Object.freeze({ min: 0.10, max: 1.50 }),
      swiftMotionSpeedCap: 50
    }),
    progression: Object.freeze({
      comboPoints: '콤보의 스킬·효과 수용량',
      comboLevel: '콤보 포인트 최대치 증가',
      experienceRequirement: '마지막 스킬까지 실행'
    }),
    tags: Object.freeze({
      consecutive: Object.freeze({
        nameKo: '연속공격',
        allowedFromPosition: 2,
        mp: Object.freeze({ operation: 'reduce', value: Object.freeze({ op: 'multiply', args: [{ op: 'subtract', left: { op: 'ref', path: 'combo.position' }, right: { op: 'value', value: 1 } }, { op: 'value', value: 100 }] }) }),
        damage: Object.freeze({ operation: 'reduce', value: Object.freeze({ op: 'multiply', args: [{ op: 'ref', path: 'combo.tagOrdinal.consecutive' }, { op: 'value', value: 0.10 }] }) })
      }),
      charge: Object.freeze({
        nameKo: '충전',
        allowedFromPosition: 2,
        mp: Object.freeze({ operation: 'storeAndDefer', storedMp: 'skill.nativeMp', overwritePreviousStoredMp: true, settleUnusedAtComboEnd: true }),
        damage: Object.freeze({ operation: 'reduceByRelativePosition', values: Object.freeze([0.80, 0.60, 0.40, 0.20]), stackWithOtherCharge: true })
      }),
      swift: Object.freeze({
        nameKo: '신속',
        allowedFromPosition: 2,
        motionSpeed: Object.freeze({ operation: 'increase', value: 50, cap: 'combo.constants.swiftMotionSpeedCap' })
      }),
      smite: Object.freeze({
        nameKo: '강타',
        allowedFromPosition: 2,
        damage: Object.freeze({ self: Object.freeze({ operation: 'increase', value: 0.50 }), nextEntry: Object.freeze({ operation: 'reduce', value: 0.50 }) }),
        mp: Object.freeze({ ifNoNextEntry: Object.freeze({ operation: 'multiply', value: 2 }) })
      }),
      mindsEye: Object.freeze({
        nameKo: '심안',
        allowedFromPosition: 2,
        accuracy: Object.freeze({ absoluteHit: true, bonus: Object.freeze({ op: 'multiply', args: [{ op: 'ref', path: 'combo.position' }, { op: 'value', value: 10 }] }) }),
        comboControl: Object.freeze({ stopWhenAilmentResistanceRemaining: true, revealRemainingResistance: true })
      }),
      tenacity: Object.freeze({
        nameKo: '집념',
        allowedFromPosition: 2,
        mp: Object.freeze({ operation: 'replaceMissingMpWithHp', hpCost: Object.freeze({ perMissingMp: 100, maxHpPercent: 10 }) })
      }),
      invincible: Object.freeze({
        nameKo: '무적',
        allowedFromPosition: 2,
        motion: Object.freeze({ invincibilityChance: Object.freeze({ op: 'multiply', args: [{ op: 'subtract', left: { op: 'ref', path: 'combo.position' }, right: { op: 'value', value: 1 } }, { op: 'value', value: 20 }] }) })
      }),
      bloodsucker: Object.freeze({
        nameKo: '흡혈',
        allowedFromPosition: 2,
        onDamage: Object.freeze({ hpHealPercent: Object.freeze({ op: 'add', args: [{ op: 'value', value: 10 }, { op: 'ref', path: 'combo.position' }] }) }),
        afterSeconds: Object.freeze({ duration: 10, replaceWith: Object.freeze({ hpCostPercent: Object.freeze({ op: 'subtract', left: { op: 'value', value: 10 }, right: { op: 'ref', path: 'combo.position' } }), damageIncreasePercent: Object.freeze({ op: 'add', args: [{ op: 'value', value: 10 }, { op: 'ref', path: 'combo.position' }] }) }) })
      }),
      tough: Object.freeze({
        nameKo: '강인',
        allowedFromPosition: 2,
        damageTaken: Object.freeze({ selfMotionReduction: 0.50, nextMotionReduction: 0.25, nextReductionCancelledByNextTag: 'smite' })
      }),
      reflection: Object.freeze({
        nameKo: '반사',
        allowedFromPosition: 2,
        onHitTaken: Object.freeze({ triggerNormalAttack: 1, appliesAmpr: true, changesProration: true }),
        onNoHitTaken: Object.freeze({ nextSkillMpReduction: 100 })
      })
    }),
    invariants: Object.freeze([
      '대미지 변화 태그는 버프 스킬에 적용하지 않는다.',
      '콤보 대미지 배율은 최종적으로 10% 이상 150% 이하로 제한한다.',
      '두 번째 위치부터 콤보 태그를 붙일 수 있다.',
      '충전의 MP 저장량은 새 충전 태그가 오면 덮어쓴다. 대미지 감소는 누적한다.'
    ])
  });
}());