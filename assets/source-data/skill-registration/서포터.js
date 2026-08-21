const supportSkills = [
  {
    "id": 0,
    "name": "First Aid",
    "nameKo": "응급처치",
    "prereq": -1,
    "x": 0,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/00_First Aid.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "ReviveTimeReduction": 2 * level }; // 부활 시간 감소율 증가 (%)[cite: 23]
    }
  },
  {
    "id": 1,
    "name": "Mini Heal",
    "nameKo": "작은 힐",
    "prereq": -1,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/01_Mini Heal.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) {
      return 30 * level; // 회복 상수[cite: 23]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Recovery",
    "nameKo": "리커버리",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/02_Recovery.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Sanctuary",
    "nameKo": "생츄어리",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/03_Sanctuary.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Heal",
    "nameKo": "힐",
    "prereq": 3,
    "x": 4,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/04_Heal.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) {
      return 300 * level; // 힐 회복량 상수[cite: 23]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Life Recovery",
    "nameKo": "라이프 리커버리",
    "prereq": -1,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/05_Life Recovery.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let vit = (stats && stats.totalVIT) ? stats.totalVIT : 0;
      let penalty = 400 - (20 * level);
      return { 
        "HPRestoreF": 10 + (4 * level) + vit, // HP 자연회복 증가 (고정+VIT)[cite: 23]
        "DamageReceived": penalty // 받는 데미지 증가 패널티 (시전자만)[cite: 23]
      };
    }
  },
  {
    "id": 6,
    "name": "Brave Aura",
    "nameKo": "브레이브 오라",
    "prereq": 5,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/06_Brave Aura.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "DamageBonus": 2 * level, // 데미지 증가 버프 (%)[cite: 23]
        "WATKP": 10 + (2 * level),  // 무기 ATK 증가 (%)[cite: 23]
        "HIT": -(75 - 2.5 * level)  // 명중 감소 패널티 (시전자만)[cite: 23]
      };
    }
  },
  {
    "id": 7,
    "name": "High Cycle",
    "nameKo": "하이 사이클",
    "prereq": 6,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/07_High Cycle.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "CSPDP": 25 * level, // 시전 속도 증가 (%)[cite: 23]
        "CSPD": 50 + (50 * level) // 시전 속도 증가 (고정)[cite: 23]
      };
    }
  },
  {
    "id": 8,
    "name": "Quick Motion",
    "nameKo": "퀵모션",
    "prereq": 7,
    "x": 4,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/08_Quick Motion.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "ASPDP": 25 * level, // 공격 속도 증가 (%)[cite: 23]
        "ASPD": 100 + (100 * level) // 공격 속도 증가 (고정)[cite: 23]
      };
    }
  },
  {
    "id": 9,
    "name": "Mana Recharge",
    "nameKo": "마나 리차지",
    "prereq": -1,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/09_Mana Recharge.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let intStat = (stats && stats.totalINT) ? stats.totalINT : 0;
      let penalty = 50 - (2.5 * level);
      return { 
        "MPRestoreF": 10 + (1.5 * level) + (intStat / 10), // MP 자연회복 증가 (고정+INT)[cite: 23]
        "DamageBonus": -penalty // 데미지 감소 패널티 (시전자만, 브오라 등과 합연산)[cite: 23]
      };
    }
  },
  {
    "id": 10,
    "name": "Magic Barrier",
    "nameKo": "매직 배리어",
    "prereq": 9,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/10_Magic Barrier.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "DEFP": 10 + (2 * level), // 방어력 증가 (%)[cite: 23]
        "MDEFP": 10 + (2 * level), // 마법 방어력 증가 (%)[cite: 23]
        "FLEE": -(75 - 2.5 * level) // 회피 감소 패널티 (시전자만)[cite: 23]
      };
    }
  },
  {
    "id": 11,
    "name": "Immunity",
    "nameKo": "디지토실",
    "prereq": 10,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/11_Immunity.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "AilmentResistance": 20 + (3 * level) // 이상내성 확률 (%)[cite: 23]
      };
    }
  },
  {
    "id": 12,
    "name": "Fast Reaction",
    "nameKo": "하이 리액션",
    "prereq": 11,
    "x": 4,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Support/12_Fast Reaction.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "GuardRecharge": 10 + level, // 가드 회복 증가 (%)[cite: 23]
        "AvoidRecharge": level       // 어보이드 회복 증가 (%)[cite: 23]
      };
    }
  }
];