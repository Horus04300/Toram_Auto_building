const barehandSkills = [
  {
    "id": 0,
    "name": "Unarmed Mastery",
    "nameKo": "맨손 마스터리",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Barehand/00_Unarmed Mastery.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let pLevel = (stats && stats.level) ? stats.level : 0;
      return { 
        "WATKP": 0.1 * level * pLevel // 무기 ATK 증가 (플레이어 레벨 비례)[cite: 23]
      };
    }
  },
  {
    "id": 1,
    "name": "Qi Charge",
    "nameKo": "집기공",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Barehand/01_Qi Charge.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let currentQi = 10; // 기공 수 가정치 예시
      return { 
        "ATK": (Math.pow(level, 3) / 100) * currentQi, // ATK 증가 (레벨 및 기공 비례)[cite: 23]
        "Stability": 5 * level // 안정률 증가 (%)[cite: 23]
      };
    }
  },
  {
    "id": 2,
    "name": "Lion Rage",
    "nameKo": "사자분신",
    "prereq": 1,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Barehand/02_Lion Rage.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let consumedQi = 5; // 소모한 기공 가정치
      return { 
        "CRIT": level * consumedQi, // 크리티컬 확률 증가[cite: 23]
        "ASPD": -(3000 - 150 * level) // 공격 속도 감소 패널티[cite: 23]
      };
    }
  },
  {
    "id": 3,
    "name": "Ultima Lion Rage",
    "nameKo": "사자분신 • 극",
    "prereq": 2,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Barehand/03_Ultima Lion Rage.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 사자분신 지속 중 통상 공격 계수 추가 증가 및 크리 시 스택 획득[cite: 23]
  },
  {
    "id": 4,
    "name": "Raving Storm",
    "nameKo": "질풍노도",
    "prereq": 1,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Barehand/04_Raving Storm.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let consumedQi = 5; // 소모한 기공 가정치
      return { 
        "ASPD": 100 * level * consumedQi, // 공격 속도 증가[cite: 23]
        "HIT": (level * level) * consumedQi, // 명중 증가[cite: 23]
        "AMPR": 20 // 공격 MP 회복 증가[cite: 23]
      };
    }
  },
  {
    "id": 5,
    "name": "Ultima Raving Storm",
    "nameKo": "질풍노도 • 극",
    "prereq": 4,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Barehand/05_Ultima Raving Storm.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "PhysicalPierce": 2.5 * level // 물리 관통 증가 (%)[cite: 23]
      };
    }
  },
  {
    "id": 6,
    "name": "Internal Elixir",
    "nameKo": "회복기공",
    "prereq": 1,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Barehand/06_Internal Elixir.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "ATK": -(100 - 2.5 * level) // ATK 감소 패널티[cite: 23]
      };
    }
  },
  {
    "id": 7,
    "name": "Clash of Enmity",
    "nameKo": "투지의 충돌",
    "prereq": 6,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Barehand/07_Clash of Enmity.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "DamageReduction": level // 받는 데미지 감소 (%)[cite: 23]
      };
    }
  },
  {
    "id": 8,
    "name": "Miracle Comeback",
    "nameKo": "기사회생",
    "prereq": 7,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Barehand/08_Miracle Comeback.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 사망 시 확률적 생존 및 회복기공 자동 발동 패시브[cite: 23]
  },
  {
    "id": 9,
    "name": "Ultima Qi Charge",
    "nameKo": "집기공•극",
    "prereq": 1,
    "x": 2,
    "y": 6,
    "via": [0, 6],
    "icon": "coryn_skill_icons/Buff Skills/Barehand/09_Ultima Qi Charge.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "AMPR": Math.floor((level + 1) / 2) // 공격 MP 회복 증가[cite: 23]
      };
    }
  },
  {
    "id": 10,
    "name": "Hidden Talent",
    "nameKo": "자기도회",
    "prereq": 9,
    "x": 3,
    "y": 6,
    "via": [0, 6],
    "icon": "coryn_skill_icons/Buff Skills/Barehand/10_Hidden Talent.png",
    "iconAvailable": true,
    "type": "passive", // EX 스킬[cite: 23]
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "GuardPower": 500 * level // 기본 가드력 증가[cite: 23]
      };
    }
  },
  {
    "id": 11,
    "name": "Earthshaker",
    "nameKo": "경천동지",
    "prereq": -1,
    "x": 3,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Barehand/11_Earthshaker.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["메인 + 서브 모두 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let pLevel = (stats && stats.level) ? stats.level : 0;
      let attributeDmg = (2 * level) + (pLevel / 10);
      let physicalPierceVal = (level <= 5) ? (2 * level) : (3 * level - 5);
      return { 
        "AttributeDamage": attributeDmg, // 모든 속성 데미지 증가[cite: 23]
        "Stability": level,              // 안정률 증가[cite: 23]
        "PhysicalPierce": physicalPierceVal // 물리 관통 증가[cite: 23]
      };
    }
  }
];