const knightSkills = [
  {
    "id": 0,
    "name": "Assault Attack",
    "nameKo": "어솔트 어택",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/00_Assault Attack.png",
    "iconAvailable": true,
    "type": "active", //[cite: 15]
    "conditions": ["All"], //[cite: 15]
    "damagetype": "physical", //[cite: 15]
    "distancePower": true, //[cite: 15]
    "longRange": false, //[cite: 15]
    "unsheathePower": false, //[cite: 15]
    "getMultiplier": function(level, stats) {
      let isShield = (stats && stats.subWeapon === "방패"); //[cite: 15]
      let knightWillLevel = (stats && stats.skill_KnightWill) ? stats.skill_KnightWill : 0; //[cite: 15]
      let willBonus = (level === 10) ? (0.6 * knightWillLevel) : 0; //[cite: 15]
      if (!isShield) willBonus /= 2; //[cite: 15]
      return 0.25 + (0.1 * level) + (isShield ? 0.25 : 0) + willBonus; //[cite: 15]
    },
    "getConstant": function(level, stats) {
      let isShield = (stats && stats.subWeapon === "방패"); //[cite: 15]
      return (5 * level) + (isShield ? 50 : 0); //[cite: 15]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 1,
    "name": "Parry",
    "nameKo": "파리",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/01_Parry.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 15]
    "conditions": ["All"], //[cite: 15]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 데미지 감소(확률)이므로 스탯창 적용은 아님[cite: 15]
  },
  {
    "id": 2,
    "name": "P. Defense",
    "nameKo": "P 디펜스",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/02_P. Defense.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 15]
    "conditions": ["방패"], //[cite: 15]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // HP 회복 및 어그로 증가는 조건부[cite: 15]
  },
  {
    "id": 3,
    "name": "Fareth",
    "nameKo": "파레스",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/03_Fareth.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 15]
    "conditions": ["방패"], //[cite: 15]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 중첩형 버프이므로 기본 상태에서 적용 제외[cite: 15]
  },
  {
    "id": 4,
    "name": "Aftershield",
    "nameKo": "에프터 실드",
    "prereq": 3,
    "x": 4,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/04_Aftershield.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 15]
    "conditions": ["한손검"], //[cite: 15]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "NeutralResistance": level }; // 무내성 증가[cite: 15]
    }
  },
  {
    "id": 5,
    "name": "Provoke",
    "nameKo": "프로보크",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/05_Provoke.png",
    "iconAvailable": true,
    "type": "active", //[cite: 15]
    "conditions": ["All"], //[cite: 15]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 고정 어그로 발생[cite: 15]
  },
  {
    "id": 6,
    "name": "Rage Sword",
    "nameKo": "레이지 소드",
    "prereq": 5,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/06_Rage Sword.png",
    "iconAvailable": true,
    "type": "active", //[cite: 15]
    "conditions": ["한손검", "양손검"], //[cite: 15]
    "damagetype": "physical", //[cite: 15]
    "distancePower": true, //[cite: 15]
    "longRange": false, //[cite: 15]
    "unsheathePower": false, //[cite: 15]
    "getMultiplier": function(level, stats) {
      let isShield = (stats && stats.subWeapon === "방패"); //[cite: 15]
      let vit = (stats && stats.totalVIT) ? stats.totalVIT : 0; //[cite: 15]
      let knightWillLevel = (stats && stats.skill_KnightWill) ? stats.skill_KnightWill : 0; //[cite: 15]
      let willBonus = (level === 10) ? (0.5 * knightWillLevel) : 0; //[cite: 15]
      if (!isShield) willBonus /= 2; //[cite: 15]
      
      return 1.5 + (0.1 * level) + (isShield ? 0.3 + (vit / 200) : 0) + willBonus; //[cite: 15]
    },
    "getConstant": function(level, stats) {
      return 150 + (5 * level); //[cite: 15]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 7,
    "name": "Binding Strike",
    "nameKo": "바인딩 스트라이크",
    "prereq": 6,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/07_Binding Strike.png",
    "iconAvailable": true,
    "type": "active", //[cite: 15]
    "conditions": ["한손검", "양손검"], //[cite: 15]
    "damagetype": "physical", //[cite: 15]
    "distancePower": true, //[cite: 15]
    "longRange": false, //[cite: 15]
    "unsheathePower": false, //[cite: 15]
    "getMultiplier": function(level, stats) {
      let isShield = (stats && stats.subWeapon === "방패"); //[cite: 15]
      let vit = (stats && stats.totalVIT) ? stats.totalVIT : 0; //[cite: 15]
      let knightWillLevel = (stats && stats.skill_KnightWill) ? stats.skill_KnightWill : 0; //[cite: 15]
      let willBonus = (level === 10) ? (0.4 * knightWillLevel) : 0; //[cite: 15]
      if (!isShield) willBonus /= 2; //[cite: 15]
      
      return 4.5 + (0.05 * level) + (isShield ? 1.5 + (vit / 50) : 0) + willBonus; //[cite: 15]
    },
    "getConstant": function(level, stats) {
      let isShield = (stats && stats.subWeapon === "방패"); //[cite: 15]
      return 50 + (10 * level) + (isShield ? 150 : 0); //[cite: 15]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 8,
    "name": "Knight Will",
    "nameKo": "나이트 윌",
    "prereq": 7,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/08_Knight Will.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 15]
    "conditions": ["All"], //[cite: 15]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isShield = (stats && stats.subWeapon === "방패"); //[cite: 15]
      let aggro = 2 * level; //[cite: 15]
      if (!isShield) aggro /= 2; //[cite: 15]
      return { "Aggro": aggro }; //[cite: 15]
    }
  },
  {
    "id": 9,
    "name": "Blink Sword",
    "nameKo": "블링크 소드",
    "prereq": 8,
    "x": 4,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/09_Blink Sword.png",
    "iconAvailable": true,
    "type": "active", //[cite: 15]
    "conditions": ["한손검"], //[cite: 15]
    "damagetype": "physical", //[cite: 15]
    "distancePower": true, //[cite: 15]
    "longRange": false, //[cite: 15]
    "unsheathePower": false, //[cite: 15]
    "getMultiplier": function(level, stats) {
      return 5 + (0.75 * level); // 기죽음 시 보너스는 특수[cite: 15]
    },
    "getConstant": function(level, stats) {
      return 200; //[cite: 15]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Sonic Thrust",
    "nameKo": "소닉 슬라스트",
    "prereq": 6,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/10_Sonic Thrust.png",
    "iconAvailable": true,
    "type": "active", //[cite: 15]
    "conditions": ["한손검"], //[cite: 15]
    "damagetype": "physical", //[cite: 15]
    "distancePower": false, // 거리 위력 X[cite: 15]
    "longRange": true, // 롱 레인지는 O[cite: 15]
    "unsheathePower": false, //[cite: 15]
    "getMultiplier": function(level, stats) {
      let isShield = (stats && stats.subWeapon === "방패"); //[cite: 15]
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0; //[cite: 15]
      return 1.5 + (0.15 * level) + (isShield ? (dex / 100) : 0); //[cite: 15]
    },
    "getConstant": function(level, stats) {
      return 200; //[cite: 15]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Revenir",
    "nameKo": "루브닐",
    "prereq": 10,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/11_Revenir.png",
    "iconAvailable": true,
    "type": "active", //[cite: 15]
    "conditions": ["한손검"], //[cite: 15]
    "damagetype": "physical", //[cite: 15]
    "distancePower": true, //[cite: 15]
    "longRange": false, //[cite: 15]
    "unsheathePower": false, //[cite: 15]
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0; //[cite: 15]
      let stack = 2; // 최대 소모 스택 2 가정[cite: 15]
      return (5 + (0.1 * level) + (dex / 50)) * (1 + stack); //[cite: 15]
    },
    "getConstant": function(level, stats) {
      return 40 * level; //[cite: 15]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 12,
    "name": "Knight's Stance",
    "nameKo": "나이트 스탠스",
    "prereq": -1,
    "x": 0,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/12_Knight's Stance.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 15]
    "conditions": ["한손검"], //[cite: 15]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isShield = (stats && stats.subWeapon === "방패"); //[cite: 15]
      return { 
        "Aggro": (2 * level) + (isShield ? level : 0), //[cite: 15]
        "VIT": level //[cite: 15]
      };
    }
  },
  {
    "id": 13,
    "name": "Knight's Remedy",
    "nameKo": "나이트 힐",
    "prereq": 12,
    "x": 3,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/13_Knight's Remedy.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 15]
    "conditions": ["한손검"], //[cite: 15]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // HP 저장 후 회복이므로 특수 연산 필요[cite: 15]
  },
  {
    "id": 14,
    "name": "Knight Pledge",
    "nameKo": "나이트 플레지",
    "prereq": 13,
    "x": 4,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Knight/14_Knight Pledge.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 15]
    "conditions": ["한손검"], //[cite: 15]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 보호막 설치 및 데미지 경감이므로 특수[cite: 15]
  }
];