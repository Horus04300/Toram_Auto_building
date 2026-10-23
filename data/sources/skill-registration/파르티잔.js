const partisanSkills = [
  {
    "id": 0,
    "name": "L Boomerang",
    "nameKo": "L 부메랑",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Partisan/00_L Boomerang.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["양손검"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      return 2 + (0.25 * level) + (dex / 100);
    },
    "getConstant": function(level, stats) {
      return 200;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 1,
    "name": "L Boomerang II",
    "nameKo": "L 부메랑 II",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Partisan/01_L Boomerang II.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["양손검"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      let baseVal = 2 + (0.25 * level) + (dex / 100);
      return baseVal * 0.5; // L 부메랑 계수의 50%
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "L Boomerang III",
    "nameKo": "L 부메랑 III",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Partisan/02_L Boomerang III.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["양손검"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      return 2 + (0.25 * level) + (dex / 100); // L 부메랑 계수와 동일
    },
    "getConstant": function(level, stats) {
      return 200;
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "PhysicalPierce": 5 * level,
        "CRIT": 10 * level
      };
    }
  },
  {
    "id": 3,
    "name": "N Dragon Tooth",
    "nameKo": "N 드래곤 투스",
    "prereq": -1,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Partisan/03_N Dragon Tooth.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["선풍창"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.75 * level; // 1타 기준
    },
    "getConstant": function(level, stats) {
      return 0;
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "PhysicalPierce": 10 * level };
    }
  },
  {
    "id": 4,
    "name": "Healing Shot",
    "nameKo": "힐링 샷",
    "prereq": -1,
    "x": 0,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Partisan/04_Healing Shot.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) {
      return 50 * level; // 틱당 고정 회복 상수 기여
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Arrow Sharpening",
    "nameKo": "화살 갈기",
    "prereq": 4,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Partisan/05_Arrow Sharpening.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["활", "자동활"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0;
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      return { 
        "PhysicalPierce": Math.max(level, (str / 50) * level),
        "CDAM": Math.max(level, (dex / 25) * level)
      };
    }
  },
  {
    "id": 6,
    "name": "Survival Instinct",
    "nameKo": "생존 본능",
    "prereq": 5,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Partisan/06_Survival Instinct.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["활", "자동활"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "MAXHP": 500 * level,
        "MAXHPP": level
      };
    }
  },
  {
    "id": 7,
    "name": "Frontliner",
    "nameKo": "전선 유지",
    "prereq": -1,
    "x": 0,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Partisan/07_Frontliner.png",
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
        "Aggro": 2 * level
      };
    }
  },
  {
    "id": 8,
    "name": "Frontliner II",
    "nameKo": "전선 유지 II",
    "prereq": 7,
    "x": 1,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Partisan/08_Frontliner II.png",
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
      let pLevel = (stats && stats.level) ? stats.level : 0;
      return { 
        "MAXHP": (100 * level) + (10 * pLevel)
      };
    }
  }
];