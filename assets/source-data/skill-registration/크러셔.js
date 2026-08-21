const crusherSkills = [
  {
    "id": 0,
    "name": "Forefist Punch",
    "nameKo": "정권 찌르기",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Crusher/00_Forefist Punch.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 권갑"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 2 + (0.2 * level);
    },
    "getConstant": function(level, stats) {
      return 200;
    },
    "getEffects": function(level, stats) { return {}; } // 확정 크리티컬 및 피해 감소는 특수 연산 필요
  },
  {
    "id": 1,
    "name": "Goliath Punch",
    "nameKo": "골리아스테이크 샷",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Crusher/01_Goliath Punch.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 권갑"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      // 골리아 스택(최대 5)과 갓핸드 스택(최대 3)에 비례하여 증가하므로 최대 스택 기준으로 임의 작성
      let goliathStack = 5; 
      let godHandLevel = 10; // 갓 핸드 스킬 10레벨 가정
      let godHandStack = 3; 
      
      let baseMulti = 8 + (3 + 0.1 * level) * goliathStack;
      let godHandBonus = 0.1 * godHandLevel * godHandStack * (goliathStack + 1);
      
      return baseMulti + godHandBonus;
    },
    "getConstant": function(level, stats) {
      return 500;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "God Hand",
    "nameKo": "갓 핸드",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Crusher/02_God Hand.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 권갑"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 10;
    },
    "getConstant": function(level, stats) {
      return 40 * level;
    },
    "getEffects": function(level, stats) { return {}; } // 받는 피해 감소 버프는 외부 연산 필요
  },
  {
    "id": 3,
    "name": "Divine Rigid Body",
    "nameKo": "신강체",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Crusher/03_Divine Rigid Body.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["메인 권갑"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 갓핸드 강화 패시브 메커니즘
  },
  {
    "id": 4,
    "name": "Breathwork",
    "nameKo": "호흡법",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Crusher/04_Breathwork.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["권갑"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // HP 회복 및 마나 반감 버프
  },
  {
    "id": 5,
    "name": "Floating Kick",
    "nameKo": "플로팅 킥",
    "prereq": 4,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Crusher/05_Floating Kick.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["권갑"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 5 + (0.2 * level);
    },
    "getConstant": function(level, stats) {
      return 100 + (10 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Geyser Kick",
    "nameKo": "가이저 슛",
    "prereq": 5,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Crusher/06_Geyser Kick.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 권갑"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0;
      // 8m 이상에서 시전 시 추가 계수는 배제하고 기본 타격 계수만 작성
      return 9 + (0.1 * level) + (agi / 200);
    },
    "getConstant": function(level, stats) {
      return 200 + (10 * level);
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "PhysicalPierce": 2 * level }; // 물리 관통 보너스
    }
  },
  {
    "id": 7,
    "name": "Combination",
    "nameKo": "콤비네이션",
    "prereq": 4,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Crusher/07_Combination.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 권갑"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1 + (0.1 * level);
    },
    "getConstant": function(level, stats) {
      return 0;
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "CRIT": level * level };
    }
  },
  {
    "id": 8,
    "name": "Annihilator",
    "nameKo": "파괴자",
    "prereq": 7,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Crusher/08_Annihilator.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["권갑"], // 메인 권갑 전용 버프 효과가 주를 이룸
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      if (isKnuckle) {
        return { 
          "WATKP": 5 * level, 
          "Stability": -10 
        };
      }
      return {};
    }
  },
  {
    "id": 9,
    "name": "Terrablast",
    "nameKo": "지오크러셔",
    "prereq": 8,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Crusher/09_Terrablast.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 권갑"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0;
      let agi = (stats && stats.baseAGI) ? stats.baseAGI : 0;
      return 9 + (0.6 * level) + (Math.max(str, agi) / 100);
    },
    "getConstant": function(level, stats) {
      return 700 + (10 * level);
    },
    "getEffects": function(level, stats) { return {}; } // 확정 크리티컬 및 배리어 효과는 특수 매커니즘
  }
];