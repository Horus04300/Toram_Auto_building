const priestSkills = [
  {
    "id": 0,
    "name": "Bless",
    "nameKo": "브레스",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/00_Bless.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 주기적 HP 회복 버프 (외부 연산 필요)
  },
  {
    "id": 1,
    "name": "Gloria",
    "nameKo": "글로리아",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/01_Gloria.png",
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
      let defBonus = 50 + (level * level * 1.5);
      return { 
        "DEFP": defBonus, 
        "MDEFP": defBonus 
      };
    }
  },
  {
    "id": 2,
    "name": "Enhanced Bless",
    "nameKo": "브레스 강화",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/02_Enhanced Bless.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 브레스 회복량 및 지속시간 강화 패시브
  },
  {
    "id": 3,
    "name": "Royal Heal",
    "nameKo": "하이네스 힐",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/03_Royal Heal.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) {
      return 500 * level; // 회복 상수 기여
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Sacred Teaching",
    "nameKo": "신성한 가르침",
    "prereq": 3,
    "x": 4,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/04_Sacred Teaching.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 임시 체력 비례 ATK/MATK 증가 패시브
  },
  {
    "id": 5,
    "name": "Holy Fist",
    "nameKo": "홀리 피스트",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/05_Holy Fist.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical", // 물리+마법 복합
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0;
      let basePart = 0.5 + (0.05 * level);
      return basePart * (isKnuckle ? 2 : 1) + (isKnuckle ? str / 100 : 0);
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Holy Light",
    "nameKo": "홀리 라이트",
    "prereq": 5,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/06_Holy Light.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isStaff = (stats && stats.mainWeapon === "지팡이");
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      return 1 + (0.15 * level) + (isStaff ? (dex / 50) : 0);
    },
    "getConstant": function(level, stats) {
      return 200;
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "MagicPierce": level };
    }
  },
  {
    "id": 7,
    "name": "Ether Barrier",
    "nameKo": "에테르 코드",
    "prereq": 6,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/07_Ether Barrier.png",
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
        "FlinchResistance": 50 + (5 * level),
        "MATK": -(8 - 0.3 * level) // MATK 감소 버프
      };
    }
  },
  {
    "id": 8,
    "name": "Prayer",
    "nameKo": "프리엘",
    "prereq": 7,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/08_Prayer.png",
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
      let isMD = (stats && stats.mainWeapon === "마도구");
      return { "MATK": level + (isMD ? 5 : 0) };
    }
  },
  {
    "id": 9,
    "name": "Aspis Soul",
    "nameKo": "아스피스 소울",
    "prereq": 8,
    "x": 4,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/09_Aspis Soul.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 비율 데미지 감소 패시브
  },
  {
    "id": 10,
    "name": "Staff Thrust",
    "nameKo": "로드 스터브",
    "prereq": -1,
    "x": 0,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/10_Staff Thrust.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0;
      return 1.9 + (0.01 * level) + (str / 100);
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Exorcism",
    "nameKo": "엑소시즘",
    "prereq": 6,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Exorcism.png", // 아이콘 경로 정합성 유지
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이", "방패"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.45 + (0.2 * level); // 일반 계수 기준 (강화 시 3.95 + 0.25 * level)
    },
    "getConstant": function(level, stats) {
      return 10 * level;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 12,
    "name": "Holy Book",
    "nameKo": "홀리 바이블",
    "prereq": 11,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/12_Holy Book.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["한손검", "지팡이", "권갑"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 홀리 라이트 자동 발동형 버프
  },
  {
    "id": 13,
    "name": "Nemesis",
    "nameKo": "네메시스",
    "prereq": 12,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/13_Nemesis.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "지팡이", "권갑"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isShield = (stats && stats.subWeapon === "방패");
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0;
      return 10 + (isShield ? str / 100 : 0); // 물리 피해 1타 기준
    },
    "getConstant": function(level, stats) {
      return 60 * level;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 14,
    "name": "Holy Grace",
    "nameKo": "홀리 그레이스",
    "prereq": 13,
    "x": 4,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Priest/14_Holy Grace.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 도핑 유지 및 마나 반감 버프
  }
];