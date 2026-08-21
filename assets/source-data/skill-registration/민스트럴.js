const minstrelSkills = [
  {
    "id": 0,
    "name": "Healing Song",
    "nameKo": "치유의 노래",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Minstrel/00_Healing Song.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["양손검", "활", "자동활", "지팡이", "마도구", "발도검"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "HPRestoreP": 10 * level, // HP 자연회복 증가 (%)[cite: 22]
        "MPRestoreP": 5 * level   // MP 자연회복 증가 (%)[cite: 22]
      };
    }
  },
  {
    "id": 1,
    "name": "Fairy Song",
    "nameKo": "요정의 노래",
    "prereq": 0,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Minstrel/01_Fairy Song.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["양손검", "활", "자동활", "지팡이", "마도구", "발도검"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "HITP": 5 * level,  // 명중 %[cite: 22]
        "HIT": 10 * level,  // 명중 고정[cite: 22]
        "FLEEP": 5 * level, // 회피 %[cite: 22]
        "FLEE": 10 * level  // 회피 고정[cite: 22]
      };
    }
  },
  {
    "id": 2,
    "name": "Passion Song",
    "nameKo": "열정의 노래",
    "prereq": 1,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Minstrel/02_Passion Song.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["양손검", "활", "자동활", "지팡이", "마도구", "발도검"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "Aggro": 30 // 어그로 30% 추가[cite: 22]
      };
    }
  },
  {
    "id": 3,
    "name": "Wisdom Song",
    "nameKo": "지혜의 노래",
    "prereq": 1,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Minstrel/03_Wisdom Song.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["양손검", "활", "자동활", "지팡이", "마도구", "발도검"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "DamageReduction": Math.floor(2.5 * level) // 받는 데미지 감소 (%)[cite: 22]
      };
    }
  },
  {
    "id": 4,
    "name": "Life Song",
    "nameKo": "생명의 노래",
    "prereq": 0,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Minstrel/04_Life Song.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["양손검", "활", "자동활", "지팡이", "마도구", "발도검"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let stack = 1; // 스택 기본 가정치
      return { 
        "MAXHP": 50 * level * stack // 최대 HP 증가[cite: 22]
      };
    }
  },
  {
    "id": 5,
    "name": "Fantasy Song",
    "nameKo": "몽환의 노래",
    "prereq": 4,
    "x": 2,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Minstrel/05_Fantasy Song.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["양손검", "활", "자동활", "지팡이", "마도구", "발도검"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 스킬 사용 시 마나 회복 특수 버프[cite: 22]
  },
  {
    "id": 6,
    "name": "Beat Blast",
    "nameKo": "비트 블래스트",
    "prereq": 4,
    "x": 2,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Minstrel/06_Beat Blast.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["양손검", "활", "자동활", "지팡이", "발도검", "마도구"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1 + (0.15 * level); // 각 히트당 계수[cite: 22]
    },
    "getConstant": function(level, stats) {
      return 0; // 상수[cite: 22]
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "MagicPierce": 10 * level }; // 자체 마법 관통 (%)[cite: 22]
    }
  },
  {
    "id": 7,
    "name": "Sound Veil",
    "nameKo": "사운드 베일",
    "prereq": 6,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Minstrel/07_Sound Veil.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["양손검", "활", "자동활", "지팡이", "마도구", "발도검"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 연주 중 어그로 고정 및 감음 스킬 비례 뎀감 패시브[cite: 22]
  },
  {
    "id": 8,
    "name": "Battle Anthem",
    "nameKo": "배틀 노트",
    "prereq": 6,
    "x": 3,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Minstrel/08_Battle Anthem.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["양손검", "활", "자동활", "지팡이", "마도구", "발도검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1; // 통상 관성 공격 패시브 기준 계수
    },
    "getConstant": function(level, stats) {
      return 0;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Ad-lib",
    "nameKo": "애드립",
    "prereq": -1,
    "x": 2,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Minstrel/09_Ad-lib.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "DamageReduction": 10 * level }; // 연주 중 데미지 감소율 (%)[cite: 22]
    }
  }
];