const survivalSkills = [
  {
    "id": 0,
    "name": "Play Dead",
    "nameKo": "죽은 척",
    "prereq": -1,
    "x": 0,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Survival/00_Play Dead.png",
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
      return { "ReviveTimeReduction": 5 * level }; // 부활 시간 단축 (%)[cite: 22]
    }
  },
  {
    "id": 1,
    "name": "EXP Gain Up",
    "nameKo": "경험치 업",
    "prereq": -1,
    "x": 0,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Survival/01_EXP Gain Up.png",
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
      return { "EXPGain": level }; // 경험치 증가 (%)[cite: 22]
    }
  },
  {
    "id": 2,
    "name": "Drop Rate Up",
    "nameKo": "수집률 업",
    "prereq": -1,
    "x": 0,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Survival/02_Drop Rate Up.png",
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
      return { "DropRate": level }; // 드랍률 증가 (%)[cite: 22]
    }
  },
  {
    "id": 3,
    "name": "Safe Rest",
    "nameKo": "안전한 휴식",
    "prereq": -1,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Survival/03_Safe Rest.png",
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
      return { 
        "HPRestoreP": 10 * level, // 비전투 HP 자연회복 증가 (%)[cite: 22]
        "HPRestoreF": 10 * level  // 비전투 HP 자연회복 증가 (고정)[cite: 22]
      };
    }
  },
  {
    "id": 4,
    "name": "HP Boost",
    "nameKo": "HP 부스트",
    "prereq": 3,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Survival/04_HP Boost.png",
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
      return { 
        "MAXHPP": 2 * level,  // 최대 HP 증가 (%)[cite: 22]
        "MAXHP": 100 * level  // 최대 HP 증가 (고정)[cite: 22]
      };
    }
  },
  {
    "id": 5,
    "name": "Fighter's High",
    "nameKo": "여유있는 전투",
    "prereq": 3,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Survival/05_Fighter's High.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 전투 중 HP 자연회복 일부 발생 (외부 계산)[cite: 22]
  },
  {
    "id": 6,
    "name": "Short Rest",
    "nameKo": "작은 휴식",
    "prereq": -1,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Survival/06_Short Rest.png",
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
      return { 
        "MPRestoreP": 5 * level, // 비전투 MP 자연회복 증가 (%)[cite: 22]
        "MPRestoreF": level     // 비전투 MP 자연회복 증가 (고정)[cite: 22]
      };
    }
  },
  {
    "id": 7,
    "name": "MP Boost",
    "nameKo": "MP 부스트",
    "prereq": 6,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Survival/07_MP Boost.png",
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
      return { "MAXMP": 30 * level }; // 최대 MP 증가 (고정)[cite: 22]
    }
  },
  {
    "id": 8,
    "name": "Sober Analysis",
    "nameKo": "냉정한 전술",
    "prereq": 6,
    "x": 2,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Survival/08_Sober Analysis.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 전투 중 MP 자연회복 일부 발생 (외부 계산)[cite: 22]
  }
];