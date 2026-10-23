const necromancerSkills = [
  {
    "id": 0,
    "name": "Grave Digger",
    "nameKo": "그레이브디거",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/00_Grave Digger.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 영혼 스택 관리 및 지팡이 전용 AMPR/이상내성 버프[cite: 25]
  },
  {
    "id": 1,
    "name": "Phantom Missile",
    "nameKo": "팬텀 미사일",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/01_Phantom Missile.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이"],
    "damagetype": "magic",
    "distancePower": false,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1; // 각 히트당 계수 (히트 수는 소모한 영혼 스택)[cite: 25]
    },
    "getConstant": function(level, stats) {
      return 500; // 각 히트당 상수[cite: 25]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Blood Siphon",
    "nameKo": "블러드 스틸",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/02_Blood Siphon.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이"],
    "damagetype": "magical", 
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1; // 흡혈 유지형 디버프 스킬 세부 계수 외부 연산
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Soul Stream",
    "nameKo": "소울 스트림",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/03_Soul Stream.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let intStat = (stats && stats.baseINT) ? stats.baseINT : 0;
      let usedSoulStack = 1; // 사용한 영혼 스택 가정치
      return level + (intStat / 100) + (0.75 * usedSoulStack);[cite: 25]
    },
    "getConstant": function(level, stats) {
      return 450 + (45 * level);[cite: 25]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Skeleton Call",
    "nameKo": "서몬 스켈레톤",
    "prereq": 0,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/04_Skeleton Call.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.1 * level; // 스켈레톤 기본 공격 계수[cite: 25]
    },
    "getConstant": function(level, stats) {
      return 0;[cite: 25]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Demonic Pact",
    "nameKo": "서몬 데모닉",
    "prereq": 4,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/05_Demonic Pact.png",
    "iconAvailable": true,
    "type": "active", // EX 스킬[cite: 25]
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1; // 악마 통상 공격 계수 (소모 마나 비례)[cite: 25]
    },
    "getConstant": function(level, stats) {
      return 0;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Fine Shovel",
    "nameKo": "양질의 샵",
    "prereq": 0,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/06_Fine Shovel.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["지팡이"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 전투 시작 시 영혼 스택 및 무덤 범위 증가[cite: 25]
  },
  {
    "id": 7,
    "name": "Harvest",
    "nameKo": "하베스트",
    "prereq": 6,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/07_Harvest.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["지팡이"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 적 처치 시 HP/MP 회복 및 스켈레톤 소환[cite: 25]
  },
  {
    "id": 8,
    "name": "Opportunist",
    "nameKo": "매치 점프",
    "prereq": 7,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/08_Opportunist.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["지팡이"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 스켈레톤 폭발 시 하베스트 발동 패시브[cite: 25]
  },
  {
    "id": 9,
    "name": "Tomb",
    "nameKo": "툼",
    "prereq": -1,
    "x": 0,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/09_Tomb.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 2.5; // 메인 히트 기준[cite: 25]
    },
    "getConstant": function(level, stats) {
      return 300;[cite: 25]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Skull Shaker",
    "nameKo": "스컬 셰이커",
    "prereq": 9,
    "x": 2,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/10_Skull Shaker.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이", "선풍창"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isStaff = (stats && stats.mainWeapon === "지팡이");
      let stack = 10; // 스컬 셰이커 스택 가정치
      return (isStaff ? 10 : 7.5) + (0.075 * level * stack) + (isStaff ? 0.25 * stack : 0);[cite: 25]
    },
    "getConstant": function(level, stats) {
      return 200;[cite: 25]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Hazard Strike",
    "nameKo": "데인져 셰이크",
    "prereq": 10,
    "x": 3,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Necromancer/11_Hazard Strike.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이", "선풍창"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isStaff = (stats && stats.mainWeapon === "지팡이");
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0;
      return (isStaff ? 10 : 7.5) + (str / 200); // 메인 히트 기준[cite: 25]
    },
    "getConstant": function(level, stats) {
      return 100;[cite: 25]
    },
    "getEffects": function(level, stats) { return {}; }
  }
];