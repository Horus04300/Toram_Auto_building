const mononofuSkills = [
  {
    "id": 0,
    "name": "Issen",
    "nameKo": "일섬",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/00_Issen.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": true, //[cite: 9]
    "longRange": false,
    "unsheathePower": true, //[cite: 9]
    "getMultiplier": function(level, stats) {
      // 2타 기준[cite: 9]
      return 1 + (0.05 * level); //[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level); //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 1,
    "name": "Pulse Blade",
    "nameKo": "파동인",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/01_Pulse Blade.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": true, //[cite: 9]
    "longRange": false,
    "unsheathePower": true, //[cite: 9]
    "getMultiplier": function(level, stats) {
      // 3타 기준[cite: 9]
      return 0.5 + (0.1 * level); //[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 30 + level; //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Triple Thrust",
    "nameKo": "삼단뚫기",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/02_Triple Thrust.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": true, //[cite: 9]
    "longRange": false,
    "unsheathePower": true, //[cite: 9]
    "getMultiplier": function(level, stats) {
      let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0; //[cite: 9]
      return 1.5 + (0.2 * level) + (agi / 500); //[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 0; //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Hasso Happa",
    "nameKo": "팔상발파",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/03_Hasso Happa.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": false, // 항상 근거리 위력 적용[cite: 9]
    "longRange": false,
    "unsheathePower": true, //[cite: 9]
    "getMultiplier": function(level, stats) {
      // 1타 기준[cite: 9]
      if (level === 10) return 6; //[cite: 9]
      return 2.1 + (0.1 * level); //[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 130 + (2 * level); //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Tenryu Ransei",
    "nameKo": "천류난성",
    "prereq": 3,
    "x": 4,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/04_Tenryu Ransei.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": true, //[cite: 9]
    "longRange": false,
    "unsheathePower": true, //[cite: 9]
    "getMultiplier": function(level, stats) {
      let stack = 4; // 최대 4스택 기준 가정[cite: 9]
      return (1.5 + 0.25 * level) * stack; //[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 10 * level; //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Kasumisetsu Getsuka",
    "nameKo": "하설월화",
    "prereq": 4,
    "x": 5,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/05_Kasumisetsu Getsuka.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": true, //[cite: 9]
    "longRange": false,
    "unsheathePower": true, //[cite: 9]
    "getMultiplier": function(level, stats) {
      return 7.5 + (0.75 * level); // 첫 4타 기준[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 500; //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Garyou Tensei",
    "nameKo": "화룡점정",
    "prereq": 3,
    "x": 4,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/06_Garyou Tensei.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": true, //[cite: 9]
    "longRange": false,
    "unsheathePower": false, // 발도 공격: X[cite: 9]
    "getMultiplier": function(level, stats) {
      let stack = 10; // 최대 10스택 기준[cite: 9]
      return (0.2 * level + 0.1 * stack) * stack; //[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 100; //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 7,
    "name": "Shadowless Slash",
    "nameKo": "무영참",
    "prereq": 6,
    "x": 5,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/07_Shadowless Slash.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": false, // 항상 근거리 위력 적용[cite: 9]
    "longRange": false,
    "unsheathePower": true, //[cite: 9]
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0; //[cite: 9]
      let agi = (stats && stats.baseAGI) ? stats.baseAGI : 0; //[cite: 9]
      return 4 + (0.5 * level) + (dex / 200) + (agi / 200); //[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 300; //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 8,
    "name": "Pommel Strike",
    "nameKo": "칼자루치기",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/08_Pommel Strike.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": true, //[cite: 9]
    "longRange": false,
    "unsheathePower": false, // 발도 공격: X[cite: 9]
    "getMultiplier": function(level, stats) {
      return 1 + (0.05 * level); //[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 100 + (10 * level); //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Magadachi",
    "nameKo": "재앙베기",
    "prereq": 8,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/09_Magadachi.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": true, //[cite: 9]
    "longRange": false,
    "unsheathePower": false, // 발도 공격: X[cite: 9]
    "getMultiplier": function(level, stats) {
      return 2 + (0.3 * level); // 재앙베기 공격[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 100 + (10 * level); //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Zantei Settetsu",
    "nameKo": "참정절철",
    "prereq": 9,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/10_Zantei Settetsu.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": true, //[cite: 9]
    "longRange": false,
    "unsheathePower": true, //[cite: 9]
    "getMultiplier": function(level, stats) {
      return 5 + level; // 반격 기준[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 30 * level; //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Bushido",
    "nameKo": "무사도",
    "prereq": -1,
    "x": 0,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/11_Bushido.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 9]
    "conditions": ["All"], //[cite: 9]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isKatana = (stats && stats.mainWeapon === "발도검"); //[cite: 9]
      let atkp = 0; //[cite: 9]
      if (level >= 1 && level <= 2) atkp = 1; //[cite: 9]
      else if (level >= 3 && level <= 7) atkp = 2; //[cite: 9]
      else if (level >= 8) atkp = 3; //[cite: 9]
      return {
        "MAXHP": 10 * level, //[cite: 9]
        "MAXMP": 10 * level, //[cite: 9]
        "HIT": level, //[cite: 9]
        "WATKP": isKatana ? 3 * level : 0, //[cite: 9]
        "ATKP": isKatana ? atkp : 0 //[cite: 9]
      };
    }
  },
  {
    "id": 12,
    "name": "Shukuchi",
    "nameKo": "축지법",
    "prereq": 11,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/12_Shukuchi.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 9]
    "conditions": ["All"], //[cite: 9]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 공격 mp 회복 증가는 외부 로직 필요[cite: 9]
  },
  {
    "id": 13,
    "name": "Nukiuchi Sennosen",
    "nameKo": "불시 선의 선",
    "prereq": 12,
    "x": 5,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/13_Nukiuchi Sennosen.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 9]
    "conditions": ["메인 발도검"], //[cite: 9]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 강화 평타 매커니즘은 외부 연산 필요[cite: 9]
  },
  {
    "id": 14,
    "name": "Two-Handed",
    "nameKo": "양손쥐기",
    "prereq": 11,
    "x": 1,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/14_Two-Handed.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 9]
    "conditions": ["All"], //[cite: 9]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isKatana = (stats && stats.mainWeapon === "발도검"); //[cite: 9]
      let crit = 0.5 * level * (isKatana ? 2 : 1); //[cite: 9]
      let stab = 0.5 * level * (isKatana ? 2 : 1); //[cite: 9]
      return {
        "CRIT": crit, //[cite: 9]
        "Stability": stab, //[cite: 9]
        "HITP": level, //[cite: 9]
        "WATKP": level //[cite: 9]
      };
    }
  },
  {
    "id": 15,
    "name": "Meikyo Shisui",
    "nameKo": "명경지수",
    "prereq": 14,
    "x": 2,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/15_Meikyo Shisui.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 9]
    "conditions": ["All"], //[cite: 9]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isKatana = (stats && stats.mainWeapon === "발도검"); //[cite: 9]
      return {
        "CRIT": 20 + (2 * level) + (isKatana ? 25 : 0), //[cite: 9]
        "DEF": -(1100 - 100 * level), //[cite: 9]
        "MDEF": -(1100 - 100 * level) //[cite: 9]
      };
    }
  },
  {
    "id": 16,
    "name": "Kairiki Ranshin",
    "nameKo": "괴력난신",
    "prereq": 15,
    "x": 4,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/16_Kairiki Ranshin.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 9]
    "conditions": ["All"], //[cite: 9]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "ATK": 10 * level }; //[cite: 9]
    }
  },
  {
    "id": 17,
    "name": "Dauntless",
    "nameKo": "불요불굴",
    "prereq": 16,
    "x": 5,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/17_Dauntless.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 9]
    "conditions": ["메인 발도검"], //[cite: 9]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 누적 스택 버프는 외부 연산 필요[cite: 9]
  },
  {
    "id": 18,
    "name": "Auspicious Wind",
    "nameKo": "서풍",
    "prereq": 15,
    "x": 2,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/18_Auspicious Wind.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 스택 기반 패시브 효과이므로 외부 연산[cite: 9]
  },
  {
    "id": 19,
    "name": "Gust",
    "nameKo": "일진강풍",
    "prereq": 18,
    "x": 3,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/19_Gust.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": true, // 롱 레인지 적용 가능 (파생 스킬에 따라 다름)[cite: 9]
    "longRange": true, //[cite: 9]
    "unsheathePower": false, // 발도 공격: X[cite: 9]
    "getMultiplier": function(level, stats) {
      return 5 + (0.5 * level); // 무풍 기준[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 300; //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 20,
    "name": "Zephyr Rush",
    "nameKo": "질풍",
    "prereq": 19,
    "x": 4,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/20_Zephyr Rush.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      // 무적 시간 최대 보너스(+12)를 임의로 반영[cite: 9]
      return (0.6 * level) + 12; //[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 100; //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 21,
    "name": "Super Gust",
    "nameKo": "일진강풍 • 개정",
    "prereq": 20,
    "x": 5,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/21_Super Gust.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 9]
    "conditions": ["발도검"], //[cite: 9]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 각 타격 계수 증가는 별도 연산 필요[cite: 9]
  },
  {
    "id": 22,
    "name": "Bouncing Blade",
    "nameKo": "칼 튕기기",
    "prereq": -1,
    "x": 3,
    "y": 10,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Mononofu/22_Bouncing Blade.png",
    "iconAvailable": true,
    "type": "active", //[cite: 9]
    "conditions": ["메인 발도검"], //[cite: 9]
    "damagetype": "physical", //[cite: 9]
    "distancePower": true, //[cite: 9]
    "longRange": false,
    "unsheathePower": true, // 발도 공격: O[cite: 9]
    "getMultiplier": function(level, stats) {
      return 2 + (0.2 * level); // 반격 기준[cite: 9]
    },
    "getConstant": function(level, stats) {
      return 100 + (10 * level); //[cite: 9]
    },
    "getEffects": function(level, stats) { return {}; }
  }
];