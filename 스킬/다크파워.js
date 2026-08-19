const darkPowerSkills = [
  {
    "id": 0,
    "name": "Bloody Bite",
    "nameKo": "블러드 바이트",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/00_Bloody Bite.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1 + (0.1 * level);
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; } // 가한 데미지 비례 HP 회복 및 다크 스팅거 연계 효과 존재
  },
  {
    "id": 1,
    "name": "Dark Stinger",
    "nameKo": "다크 스팅거",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/01_Dark Stinger.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0;
      let vit = (stats && stats.baseVIT) ? stats.baseVIT : 0;
      return 1 + (0.3 * level) + ((str + vit) / 100); // HP 소모량 추가 계수는 외부 연산
    },
    "getConstant": function(level, stats) {
      return 1000; // 최대 상수 기준 (HP 소모량 비례)
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Red Tear",
    "nameKo": "레드 티어",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/02_Red Tear.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1.8 + (0.02 * level); // 각 히트당 계수
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
    "id": 3,
    "name": "Soul Hunter",
    "nameKo": "소울 헌트",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/03_Soul Hunter.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 5 + (0.5 * level); // 1타 기준 (2타는 스택 비례 계수 적용)
    },
    "getConstant": function(level, stats) {
      return 100 + (30 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Sacrifice",
    "nameKo": "새크리파이스",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/04_Sacrifice.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return Math.min(10, 5 + level);
    },
    "getConstant": function(level, stats) {
      return 0;
    },
    "getEffects": function(level, stats) { return {}; } // 특수 데미지 공식 및 안정률 적용
  },
  {
    "id": 5,
    "name": "Demon Claw",
    "nameKo": "데몬 크로우",
    "prereq": 4,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/05_Demon Claw.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let hpRatioFactor = 0.9; // 체력 비례 계수 최대치 가정
      return (1 + 0.1 * level) * (hpRatioFactor * 100 / 12);
    },
    "getConstant": function(level, stats) {
      return 40 * level;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Regretless",
    "nameKo": "리그렛",
    "prereq": 5,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/06_Regretless.png",
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
      let stack = 1; // 기본 1스택 기준 예시
      let atkBonus = level >= 9 ? 5 : level >= 7 ? 4 : level >= 5 ? 3 : level >= 3 ? 2 : 1;
      return { 
        "AMPR": level * stack,
        "P_RES": level * stack,
        "M_RES": level * stack,
        "MAXMP": 100 * stack,
        "ATK": atkBonus * stack,
        "MATK": atkBonus * stack
      };
    }
  },
  {
    "id": 7,
    "name": "Eternal Nightmare",
    "nameKo": "이터널 나이트메어",
    "prereq": 6,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/07_Eternal Nightmare.png",
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
        "MAXHPP": 2 * level,
        "DarkResistance": 5
      };
    }
  },
  {
    "id": 8,
    "name": "Intimidating Evil Eye",
    "nameKo": "위압의 마안",
    "prereq": -1,
    "x": 0,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/08_Intimidating Evil Eye.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.01 * level;
    },
    "getConstant": function(level, stats) {
      return 20 * level;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Bewitching Evil Eye",
    "nameKo": "매혹의 마안",
    "prereq": 8,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/09_Bewitching Evil Eye.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return level; // 매료 상태 적 대상 시 계수 (비상태 시 0.01 * level)
    },
    "getConstant": function(level, stats) {
      return 0; // 매료 상태 적 대상 시 상수 (비상태 시 0)
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Black Flame Evil Eye",
    "nameKo": "흑염의 마안",
    "prereq": 9,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/10_Black Flame Evil Eye.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 10 + level; // 이터널 나이트메어 연계 보너스 포함 가능
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Chaotic Evil Eye",
    "nameKo": "혼돈의 마안",
    "prereq": 10,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/DarkPower/11_Chaotic Evil Eye.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 5 + level; // 상태이상 성공 시 2.5배 증폭
    },
    "getConstant": function(level, stats) {
      return 50 * level;
    },
    "getEffects": function(level, stats) { return {}; }
  }
];