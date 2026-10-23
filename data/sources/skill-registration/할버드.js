const halberdSkills = [
  {
    "id": 0,
    "name": "Flash Stab",
    "nameKo": "플래쉬 스탭",
    "prereq": -1,
    "x": 0,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/00_Flash Stab.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["한손검", "선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": true, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      return 1 + (0.05 * level); //[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level); //[cite: 12]
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isHalberd = (stats && stats.mainWeapon === "선풍창"); //[cite: 12]
      return { "ASPDP": 25 + (isHalberd ? 25 : 0) }; //[cite: 12]
    }
  },
  {
    "id": 1,
    "name": "Cannon Spear",
    "nameKo": "캐논 스피어",
    "prereq": 0,
    "x": 1,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/01_Cannon Spear.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": true, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      return 1.5 + (0.1 * level); // 2타(투창) 기준[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 100 + (10 * level); //[cite: 12]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Dragon Tail",
    "nameKo": "드래곤 테일",
    "prereq": 1,
    "x": 2,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/02_Dragon Tail.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": true, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      return 2 + (0.2 * level); // 2타 기준[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 50 + (15 * level); //[cite: 12]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Dive Impact",
    "nameKo": "다이브 임팩트",
    "prereq": 2,
    "x": 3,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/03_Dive Impact.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": true, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0; //[cite: 12]
      return 2 + (0.2 * level) + (str / 250); // 1타 기준[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 200 + (20 * level); //[cite: 12]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Dragon Tooth",
    "nameKo": "드래곤 투스",
    "prereq": 2,
    "x": 4,
    "y": 0,
    "via": [2, 0],
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/04_Dragon Tooth.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": true, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      return 7.5; // 2타 계수[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 0; //[cite: 12]
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "CRIT": 65 + level, //[cite: 12]
        "PhysicalPierce": 10 * level //[cite: 12]
      };
    }
  },
  {
    "id": 5,
    "name": "Draconic Charge",
    "nameKo": "드라코닉 차지",
    "prereq": 4,
    "x": 5,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/05_Draconic Charge.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": true, // 항상 근거리 위력 적용[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      return 5 + (0.5 * level); // 1타, 0% 충전 기준[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 300; //[cite: 12]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Deadly Spear",
    "nameKo": "데들리 스피어",
    "prereq": 0,
    "x": 1,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/06_Deadly Spear.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["한손검", "선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": true, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      let isHalberd = (stats && stats.mainWeapon === "선풍창"); //[cite: 12]
      return 1 + (0.05 * level) + (isHalberd ? 0.2 : 0); //[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 80 + (3 * level); //[cite: 12]
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let pierce = 10; //[cite: 12]
      if (level >= 4 && level <= 6) pierce = 15; //[cite: 12]
      else if (level >= 7 && level <= 9) pierce = 20; //[cite: 12]
      else if (level === 10) pierce = 25; //[cite: 12]
      return { "PhysicalPierce": pierce }; //[cite: 12]
    }
  },
  {
    "id": 7,
    "name": "Strike Stab",
    "nameKo": "스트라이크 스탭",
    "prereq": 6,
    "x": 3,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/07_Strike Stab.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["한손검", "선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": true, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0; //[cite: 12]
      return 1.9 + (0.01 * level) + (str / 500); // 상태이상 보너스는 별도 계산[cite: 12]
    },
    "getConstant": function(level, stats) {
      let isHalberd = (stats && stats.mainWeapon === "선풍창"); //[cite: 12]
      return 100 + (isHalberd ? 100 : 0); //[cite: 12]
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isHalberd = (stats && stats.mainWeapon === "선풍창"); //[cite: 12]
      let critPenalty = isHalberd ? (5 * level) : (50 + 2.5 * level); //[cite: 12]
      return { "CRIT": -critPenalty }; //[cite: 12]
    }
  },
  {
    "id": 8,
    "name": "Chronos Drive",
    "nameKo": "크로노스 드라이브",
    "prereq": 7,
    "x": 4,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/08_Chronos Drive.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": false, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      return 1 + (0.5 * level); //[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 40 * level; //[cite: 12]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Infinite Dimension",
    "nameKo": "디멘젼 틸",
    "prereq": 8,
    "x": 5,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/09_Infinite Dimension.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": false, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0; //[cite: 12]
      let agi = (stats && stats.baseAGI) ? stats.baseAGI : 0; //[cite: 12]
      return 4 + (str / 500) + (agi / 500); //[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 20 * level; //[cite: 12]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Punish Ray",
    "nameKo": "배니쉬 레이",
    "prereq": 6,
    "x": 2,
    "y": 5,
    "via": [1, 5],
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/10_Punish Ray.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["한손검", "선풍창"], //[cite: 12]
    "damagetype": "magic", //[cite: 12]
    "distancePower": true, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      let isHalberd = (stats && stats.mainWeapon === "선풍창"); //[cite: 12]
      let intStat = (stats && stats.totalINT) ? stats.totalINT : 0; //[cite: 12]
      return (0.25 + 0.01 * level * level + intStat / 400) * (isHalberd ? 2 : 1); //[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 0; //[cite: 12]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Blitz Spike",
    "nameKo": "블리츠 파이크",
    "prereq": 10,
    "x": 3,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/11_Blitz Spike.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": true, //[cite: 12]
    "longRange": true, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      return 3 + (0.1 * level); // 찌르기 기준[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 300; //[cite: 12]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 12,
    "name": "Lightning Hail",
    "nameKo": "라이트닝 헤일",
    "prereq": 11,
    "x": 4,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/12_Lightning Hail.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "magic", //[cite: 12]
    "distancePower": true, //[cite: 12]
    "longRange": true, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      let intStat = (stats && stats.totalINT) ? stats.totalINT : 0; //[cite: 12]
      return 0.75 + (0.1 * level) + (intStat / 1000); //[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 200; //[cite: 12]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 13,
    "name": "Thor's Hammer",
    "nameKo": "볼 해머",
    "prereq": 12,
    "x": 5,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/13_Thor's Hammer.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "magic", //[cite: 12]
    "distancePower": false, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      return 10 + (0.5 * level); //[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 400; //[cite: 12]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 14,
    "name": "Halberd Mastery",
    "nameKo": "할버드 마스터리",
    "prereq": -1,
    "x": 0,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/14_Halberd Mastery.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": false, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let atkp = 0; //[cite: 12]
      if (level >= 1 && level <= 2) atkp = 1; //[cite: 12]
      else if (level >= 3 && level <= 7) atkp = 2; //[cite: 12]
      else if (level >= 8) atkp = 3; //[cite: 12]
      return { 
        "WATKP": 3 * level, //[cite: 12]
        "ATKP": atkp //[cite: 12]
      };
    }
  },
  {
    "id": 15,
    "name": "Critical Spear",
    "nameKo": "회심의 일격",
    "prereq": 14,
    "x": 3,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/15_Critical Spear.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": false, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "CRIT": Math.ceil(level / 2), //[cite: 12]
        "CRITP": Math.floor(level / 2) //[cite: 12]
      };
    }
  },
  {
    "id": 16,
    "name": "Tornado Lance",
    "nameKo": "토네이도 랜스",
    "prereq": 15,
    "x": 5,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/16_Tornado Lance.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": false, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 스택형이므로 기본 상태 효과 제외[cite: 12]
  },
  {
    "id": 17,
    "name": "Quick Aura",
    "nameKo": "퀵 오러",
    "prereq": -1,
    "x": 0,
    "y": 9,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/17_Quick Aura.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 12]
    "conditions": ["All"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": false, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "ASPD": 50 * level, //[cite: 12]
        "ASPDP": 2.5 * level //[cite: 12]
      };
    }
  },
  {
    "id": 18,
    "name": "War Cry of Struggle",
    "nameKo": "역경의 사자후",
    "prereq": 17,
    "x": 2,
    "y": 9,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/18_War Cry of Struggle.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["All"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": false, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // MP 회복 메커니즘[cite: 12]
  },
  {
    "id": 19,
    "name": "Godspeed Wield",
    "nameKo": "신속의 수도",
    "prereq": 18,
    "x": 4,
    "y": 9,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/19_Godspeed Wield.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 12]
    "conditions": ["All"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": false, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isHalberd = (stats && stats.mainWeapon === "선풍창"); //[cite: 12]
      let resDrop = 100 - (3 * level); //[cite: 12]
      if (isHalberd) resDrop = Math.max(0, resDrop - 45); // 선풍창 완화 보너스[cite: 12]
      
      return { 
        "ASPD": (30 * level) + (isHalberd ? 100 : 0), //[cite: 12]
        "ASPDP": level, //[cite: 12]
        "FLEE": level, // Avoid 회복[cite: 12]
        "MAXMP": -100, //[cite: 12]
        "P_RES": -resDrop, //[cite: 12]
        "M_RES": -resDrop //[cite: 12]
      };
    }
  },
  {
    "id": 20,
    "name": "Almighty Wield",
    "nameKo": "신의 창솜씨",
    "prereq": 19,
    "x": 5,
    "y": 9,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/20_Almighty Wield.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": false, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "SkillDamage": level }; // 할버드 물리 스킬 최종 데미지 증가[cite: 12]
    }
  },
  {
    "id": 21,
    "name": "Buster Lance",
    "nameKo": "버스터랜스",
    "prereq": -1,
    "x": 3,
    "y": 10,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Halberd/21_Buster Lance.png",
    "iconAvailable": true,
    "type": "active", //[cite: 12]
    "conditions": ["선풍창"], //[cite: 12]
    "damagetype": "physical", //[cite: 12]
    "distancePower": true, //[cite: 12]
    "longRange": false, //[cite: 12]
    "unsheathePower": false, //[cite: 12]
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0; //[cite: 12]
      let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0; //[cite: 12]
      return 5 + (str / 200) + (agi / 200); // 버스터랜스 기본 기준[cite: 12]
    },
    "getConstant": function(level, stats) {
      return 100; //[cite: 12]
    },
    "getEffects": function(level, stats) { return {}; }
  }
];