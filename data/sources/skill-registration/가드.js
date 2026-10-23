const guardSkills = [
  {
    "id": 0,
    "name": "Heavy Armor Mastery",
    "nameKo": "중갑옷 마스터리",
    "prereq": -1,
    "x": 0,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Guard/00_Heavy Armor Mastery.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["중량옷"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "GuardRecharge": level }; 
    }
  },
  {
    "id": 1,
    "name": "Advanced Guard",
    "nameKo": "어드밴스 가드",
    "prereq": 0,
    "x": 1,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Guard/01_Advanced Guard.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["중량옷"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "GuardRecharge": level,
        "GuardPower": (level + 1) / 2
      };
    }
  },
  {
    "id": 2,
    "name": "Physical Guard",
    "nameKo": "피지컬 가드",
    "prereq": 0,
    "x": 2,
    "y": 0,
    "via": [0, 0],
    "icon": "coryn_skill_icons/Buff Skills/Guard/02_Physical Guard.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // HP 조건부 이상 내성 증가는 외부 연산 필요
  },
  {
    "id": 3,
    "name": "Light Armor Mastery",
    "nameKo": "경갑옷 마스터리",
    "prereq": -1,
    "x": 0,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Guard/03_Light Armor Mastery.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["경량옷"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "AvoidRecharge": level };
    }
  },
  {
    "id": 4,
    "name": "Advanced Evasion",
    "nameKo": "어드밴스 프리",
    "prereq": 3,
    "x": 1,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Guard/04_Advanced Evasion.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["경량옷"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "AvoidRecharge": level };
    }
  },
  {
    "id": 5,
    "name": "Mirage Evasion",
    "nameKo": "미라쥬 스텝",
    "prereq": 3,
    "x": 2,
    "y": 4,
    "via": [0, 4],
    "icon": "coryn_skill_icons/Buff Skills/Guard/05_Mirage Evasion.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 차지/영창 중 어보이드 사용 기능은 특수 매커니즘
  }
];