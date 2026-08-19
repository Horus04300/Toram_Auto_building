const martialSkills = [
  {
    "id": 0,
    "name": "Smash",
    "nameKo": "스매시",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/00_Smash.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return 0.5 + (0.02 * level) + (isKnuckle ? 0.5 + 0.03 * level : 0);
    },
    "getConstant": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0;
      return (5 * level) + (isKnuckle ? 25 + (agi / 10) : 0);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 1,
    "name": "Bash",
    "nameKo": "배쉬",
    "prereq": 0,
    "x": 1,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/01_Bash.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0;
      return 1 + (0.05 * level) + (isKnuckle ? 1 + (agi / 500) : 0);
    },
    "getConstant": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0;
      return (10 * level) + (isKnuckle ? 50 + (agi / 5) : 0);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Shell Break",
    "nameKo": "셸 브레이크",
    "prereq": 1,
    "x": 2,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/02_Shell Break.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      // 적 방어력 및 레벨 연산은 별도 로직 필요 (임의로 0 적용)
      return 1 + (0.05 * level) + (isKnuckle ? 0.5 : 0);
    },
    "getConstant": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return 50 + (10 * level) + (isKnuckle ? 150 : 0);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Heavy Smash",
    "nameKo": "헤비 스매시",
    "prereq": 2,
    "x": 3,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/03_Heavy Smash.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return 1 + (0.15 * level) + (isKnuckle ? 1.5 : 0);
    },
    "getConstant": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return 100 + (10 * level) + (isKnuckle ? 100 : 0);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Chariot",
    "nameKo": "채리엇",
    "prereq": 3,
    "x": 4,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/04_Chariot.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      let agi = (stats && stats.baseAGI) ? stats.baseAGI : 0;
      return 9.9 + (0.01 * level) + (isKnuckle ? 2.5 + (agi / 100) : 0);
    },
    "getConstant": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return 50 + (20 * level) + (isKnuckle ? 250 : 0);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Abstract Arms",
    "nameKo": "심상천수",
    "prereq": 4,
    "x": 5,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/05_Abstract Arms.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["권갑"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Mountain Press",
    "nameKo": "첩산고",
    "prereq": 4,
    "x": 6,
    "y": 0,
    "via": [4, 0],
    "icon": "coryn_skill_icons/Weapon Skills/Martial/06_Mountain Press.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["권갑", "메인 맨손"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0;
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      let isBarehand = (stats && stats.mainWeapon === "맨손");
      return 7.5 + (0.25 * level) + (isBarehand ? Math.max(agi, dex) / 100 : 0);
    },
    "getConstant": function(level, stats) {
      return 500;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 7,
    "name": "Sonic Wave",
    "nameKo": "소닉 웨이브",
    "prereq": 0,
    "x": 1,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/07_Sonic Wave.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return 0.75 + (0.025 * level) + (isKnuckle ? 0.25 : 0);
    },
    "getConstant": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return (5 * level) + (isKnuckle ? 25 : 0);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 8,
    "name": "Earthbind",
    "nameKo": "어스바인드",
    "prereq": 7,
    "x": 2,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/08_Earthbind.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0;
      return 1 + (0.025 * level) + (isKnuckle ? 0.25 + (agi / 500) : 0);
    },
    "getConstant": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return (5 * level) + (isKnuckle ? 25 : 0);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Triple Kick",
    "nameKo": "트라이 어츠",
    "prereq": 8,
    "x": 3,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/09_Triple Kick.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return 1 + (0.1 * level) + (isKnuckle ? 1 : 0);
    },
    "getConstant": function(level, stats) {
      return 25 + (2 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Rush",
    "nameKo": "러시",
    "prereq": 9,
    "x": 4,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/10_Rush.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      let agi = (stats && stats.baseAGI) ? stats.baseAGI : 0;
      return 3 + (0.4 * level) + (isKnuckle ? 2 + (agi / 50) : 0);
    },
    "getConstant": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return (20 * level) + (isKnuckle ? 200 : 0);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Asura Aura",
    "nameKo": "아수라 오라",
    "prereq": 10,
    "x": 5,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/11_Asura Aura.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["권갑"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 12,
    "name": "Seismic Stomp",
    "nameKo": "진각",
    "prereq": 8,
    "x": 6,
    "y": 2,
    "via": [2, 2],
    "icon": "coryn_skill_icons/Weapon Skills/Martial/12_Seismic Stomp.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["권갑", "메인 맨손"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isBarehand = (stats && stats.mainWeapon === "맨손");
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0;
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      return 7.5 + (0.25 * level) + (isBarehand ? Math.max(str, dex) / 100 : 0);
    },
    "getConstant": function(level, stats) {
      return 300;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 13,
    "name": "Spin Sweep",
    "nameKo": "선휘",
    "prereq": 10,
    "x": 6,
    "y": 4,
    "via": [4, 4],
    "icon": "coryn_skill_icons/Weapon Skills/Martial/13_Spin Sweep.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["권갑", "메인 맨손"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isBarehand = (stats && stats.mainWeapon === "맨손");
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0;
      let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0;
      return 2.5 + (0.25 * level) + (isBarehand ? Math.max(str, agi) / 100 : 0);
    },
    "getConstant": function(level, stats) {
      return 400;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 14,
    "name": "Flash Blink",
    "nameKo": "플래시 아트",
    "prereq": 9,
    "x": 5,
    "y": 5,
    "via": [3, 5],
    "icon": "coryn_skill_icons/Weapon Skills/Martial/14_Flash Blink.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["권갑"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      let agi = (stats && stats.baseAGI) ? stats.baseAGI : 0;
      return 3 + (0.3 * level) + (isKnuckle ? agi / 400 : 0);
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 15,
    "name": "Martial Mastery",
    "nameKo": "머셜 마스터리",
    "prereq": -1,
    "x": 0,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/15_Martial Mastery.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["메인 권갑"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let atkp = 0;
      if (level >= 1 && level <= 2) atkp = 1;
      else if (level >= 3 && level <= 7) atkp = 2;
      else if (level >= 8) atkp = 3;
      return { 
        "WATKP": 3 * level, 
        "ATKP": atkp 
      };
    }
  },
  {
    "id": 16,
    "name": "Martial Discipline",
    "nameKo": "체술단련",
    "prereq": 15,
    "x": 3,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/16_Martial Discipline.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["권갑"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return { 
        "SkillDamage": level, 
        "ASPDP": isKnuckle ? level : 0, 
        "ASPD": isKnuckle ? 10 * level : 0 
      };
    }
  },
  {
    "id": 17,
    "name": "Chakra",
    "nameKo": "차크라",
    "prereq": 16,
    "x": 4,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/17_Chakra.png",
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
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      let dmgReduc = 10 + (2 * level) + (isKnuckle ? 20 : 0);
      return { "DamageReduction": dmgReduc };
    }
  },
  {
    "id": 18,
    "name": "Energy Control",
    "nameKo": "화경",
    "prereq": 17,
    "x": 6,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/18_Energy Control.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["권갑"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return { 
        "Stability": 10, 
        "WATKP": isKnuckle ? 5 * level : 0 
      };
    }
  },
  {
    "id": 19,
    "name": "Aggravate",
    "nameKo": "원 찬스",
    "prereq": -1,
    "x": 0,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/19_Aggravate.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["권갑", "메인 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "AMPR": Math.floor((level + 1) / 2) };
    }
  },
  {
    "id": 20,
    "name": "Strong Chase Attack",
    "nameKo": "강력한 추격",
    "prereq": 19,
    "x": 2,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/20_Strong Chase Attack.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["권갑", "메인 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isKnuckle = (stats && stats.mainWeapon === "권갑");
      return { "HITP": level * (isKnuckle ? 2 : 1) };
    }
  },
  {
    "id": 21,
    "name": "Slide",
    "nameKo": "슬라이딩",
    "prereq": -1,
    "x": 3,
    "y": 9,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Martial/21_Slide.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 권갑"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  }
];