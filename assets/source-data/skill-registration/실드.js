const shieldSkills = [
  {
    "id": 0,
    "name": "Shield Mastery",
    "nameKo": "실드 마스터리",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/00_Shield Mastery.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["방패"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 방패 장착 시 공속 패널티 완화 효과 (외부 연산 필요)
  },
  {
    "id": 1,
    "name": "Shield Bash",
    "nameKo": "실드 배쉬",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/01_Shield Bash.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["방패"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.015 * level;
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Shield Cannon",
    "nameKo": "실드 캐논",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/02_Shield Cannon.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["방패"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.5 + (0.1 * level); // 기본 계수 기준 (강화 시 방패 재련치 비례)
    },
    "getConstant": function(level, stats) {
      return 100 + (10 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Guard Strike",
    "nameKo": "가드 스트라이크",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/03_Guard Strike.png",
    "iconAvailable": true,
    "type": "passive", // 가드 발동 시 피해를 주는 패시브
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.1 * level; 
    },
    "getConstant": function(level, stats) {
      return 10 * level; 
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Force Shield",
    "nameKo": "포스 실드",
    "prereq": 0,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/04_Force Shield.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["방패"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "DEF": 2 * level, 
        "DEFP": level, 
        "MAXHP": 50 * level,
        "P_RES": level
      };
    }
  },
  {
    "id": 5,
    "name": "Magical Shield",
    "nameKo": "매지컬 실드",
    "prereq": 4,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/05_Magical Shield.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["방패"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "MDEF": 2 * level, 
        "MDEFP": level, 
        "MAXHP": 50 * level,
        "M_RES": level
      };
    }
  },
  {
    "id": 6,
    "name": "Shield Uppercut",
    "nameKo": "실드 어퍼컷",
    "prereq": 0,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/06_Shield Uppercut.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["방패"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.15 * level;
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 7,
    "name": "Dual Shields",
    "nameKo": "듀얼 실드",
    "prereq": 6,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/07_Dual Shields.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["방패"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let vit = (stats && stats.totalVIT) ? stats.totalVIT : 0;
      return { 
        "Stability": 0.1 * level + (vit / 500) // 통상 공격 계수 증가 반영 변수
      };
    }
  },
  {
    "id": 8,
    "name": "Shield Repair",
    "nameKo": "실드 리페어",
    "prereq": 7,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/08_Shield Repair.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["방패"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Belagerung",
    "nameKo": "벨라겔룸",
    "prereq": 8,
    "x": 4,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/09_Belagerung.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["방패"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 4 + (0.35 * level); // 기본 2히트 각 히트당 계수
    },
    "getConstant": function(level, stats) {
      return 100 + (10 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Protection",
    "nameKo": "프로텍션",
    "prereq": -1,
    "x": 0,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/10_Protection.png",
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
      let pRes = 15;
      if (level >= 4 && level <= 6) pRes = 20;
      else if (level >= 7 && level <= 9) pRes = 25;
      else if (level === 10) pRes = 30;
      
      let mRes = 30;
      if (level >= 4 && level <= 6) mRes = 25;
      else if (level >= 7 && level <= 9) mRes = 20;
      else if (level === 10) mRes = 15;
      
      return { 
        "P_RES": pRes, 
        "M_RES": -mRes 
      };
    }
  },
  {
    "id": 11,
    "name": "Aegis",
    "nameKo": "이지스",
    "prereq": 10,
    "x": 1,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/11_Aegis.png",
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
      let mRes = 15;
      if (level >= 4 && level <= 6) mRes = 20;
      else if (level >= 7 && level <= 9) mRes = 25;
      else if (level === 10) mRes = 30;
      
      let pRes = 30;
      if (level >= 4 && level <= 6) pRes = 25;
      else if (level >= 7 && level <= 9) pRes = 20;
      else if (level === 10) pRes = 15;
      
      return { 
        "M_RES": mRes, 
        "P_RES": -pRes 
      };
    }
  },
  {
    "id": 12,
    "name": "Guardian",
    "nameKo": "가디언",
    "prereq": 11,
    "x": 3,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Shield/12_Guardian.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["방패"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 어그로 및 파티원 뎀감 오라 버프
  }
];