const dancerSkills = [
  {
    "id": 0,
    "name": "Fairy Dance",
    "nameKo": "요정의 춤",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Dancer/00_Fairy Dance.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["한손검", "마도구", "권갑", "단검", "선풍창"],[cite: 21]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 스택 기반 적 명중 감소 버프[cite: 21]
  },
  {
    "id": 1,
    "name": "Frenzy Dance",
    "nameKo": "격정의 춤",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Dancer/01_Frenzy Dance.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["한손검", "마도구", "권갑", "단검", "선풍창"],[cite: 21]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 부위 파괴 데미지 증가 버프[cite: 21]
  },
  {
    "id": 2,
    "name": "Spirited Dance",
    "nameKo": "예민의 춤",
    "prereq": 0,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Dancer/02_Spirited Dance.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["한손검", "마도구", "권갑", "단검", "선풍창"],[cite: 21]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 적의 회피 감소 버프[cite: 21]
  },
  {
    "id": 3,
    "name": "Astute Dance",
    "nameKo": "매혹의 춤",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Dancer/03_Astute Dance.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["한손검", "마도구", "권갑", "단검", "선풍창"],[cite: 21]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 적의 안정률 감소 버프[cite: 21]
  },
  {
    "id": 4,
    "name": "Charming Dance",
    "nameKo": "응원의 춤",
    "prereq": 3,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Dancer/04_Charming Dance.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["한손검", "마도구", "권갑", "단검", "선풍창"],[cite: 21]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "MPRestoreF": 50 + (5 * level) }; // 파티원 MP 회복 버프[cite: 21]
    }
  },
  {
    "id": 5,
    "name": "Elegant Poise",
    "nameKo": "우아한 몸가짐",
    "prereq": -1,
    "x": 2,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Dancer/05_Elegant Poise.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["한손검", "마도구", "권갑", "단검", "선풍창"],[cite: 21]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "DamageReduction": (level * level) / 2, // 데미지 경감 (%)[cite: 21]
        "AilmentResistance": (level * level) / 4 // 상태이상 무시 확률 (%)[cite: 21]
      };
    }
  },
  {
    "id": 6,
    "name": "Nature's Wonders",
    "nameKo": "화조풍월",
    "prereq": 5,
    "x": 3,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Dancer/06_Nature's Wonders.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "마도구", "권갑", "단검", "선풍창"],[cite: 21]
    "damagetype": "physical",[cite: 21]
    "distancePower": true,[cite: 21]
    "longRange": false,[cite: 21]
    "unsheathePower": false,[cite: 21]
    "getMultiplier": function(level, stats) {
      return (1.5 + (0.75 * level)) / 4; // 각 히트당 계수[cite: 21]
    },
    "getConstant": function(level, stats) {
      return 100;[cite: 21]
    },
    "getEffects": function(level, stats) { return {}; } // 상태이상 내성 및 아군 HP 회복[cite: 21]
  }
];