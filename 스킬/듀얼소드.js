const dualSwordSkills = [
  {
    "id": 0,
    "name": "Dual Sword Mastery",
    "nameKo": "듀얼 마스터리",
    "prereq": -1,
    "x": 0,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/00_Dual Sword Mastery.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "HITP": 3 * level, 
        "CRIT": 3 * level 
      };
    }
  },
  {
    "id": 1,
    "name": "Twin Slash",
    "nameKo": "트윈 슬래쉬",
    "prereq": 0,
    "x": 1,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/01_Twin Slash.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1.5 + (0.1 * level);
    },
    "getConstant": function(level, stats) {
      return 100 + (10 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Spinning Slash",
    "nameKo": "에어 슬라이드",
    "prereq": 1,
    "x": 2,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/02_Spinning Slash.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1.25 + (0.025 * level); // 첫 타 기준
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Phantom Slash",
    "nameKo": "팬텀 레이브",
    "prereq": 2,
    "x": 3,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/03_Phantom Slash.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 5 + (0.2 * level);
    },
    "getConstant": function(level, stats) {
      return 200 + (20 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Aerial Cut",
    "nameKo": "에어 슬라이서",
    "prereq": 2,
    "x": 5,
    "y": 0,
    "via": [2, 0],
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/04_Aerial Cut.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      return 2.15 + (0.085 * level) + (dex / 1000 * level); // 첫 타 기준
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Cross Parry",
    "nameKo": "패링 소드",
    "prereq": 0,
    "x": 1,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/05_Cross Parry.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1 + (0.01 * level);
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Charging Slash",
    "nameKo": "드래곤 소드",
    "prereq": 5,
    "x": 2,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/06_Charging Slash.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": true,
    "getMultiplier": function(level, stats) {
      return 1 + (0.1 * level);
    },
    "getConstant": function(level, stats) {
      return 100 + (20 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 7,
    "name": "Shadowstep",
    "nameKo": "돌아 들어가기",
    "prereq": 6,
    "x": 3,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/07_Shadowstep.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "AMPR": level };
    }
  },
  {
    "id": 8,
    "name": "Shining Cross",
    "nameKo": "샤이닝 크로스",
    "prereq": 7,
    "x": 4,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/08_Shining Cross.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0;
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0;
      return 3 + (0.1 * level) + (str / 500) + (dex / 500) + (agi / 500);
    },
    "getConstant": function(level, stats) {
      return 100 + (20 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Lunar Misfortune",
    "nameKo": "루나 디재스터",
    "prereq": 8,
    "x": 5,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/09_Lunar Misfortune.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": true,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      return 5 + (0.5 * level) + (dex / 150);
    },
    "getConstant": function(level, stats) {
      return 400;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Twin Buster Blade",
    "nameKo": "트윈 버스터 블레이드",
    "prereq": 8,
    "x": 5,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/10_Twin Buster Blade.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      let agi = (stats && stats.baseAGI) ? stats.baseAGI : 0;
      return (0.75 * level) + (agi / 200) + (dex / 200);
    },
    "getConstant": function(level, stats) {
      return 20 * level;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Reflex",
    "nameKo": "스텝 리액터",
    "prereq": 0,
    "x": 1,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/11_Reflex.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let drop = 100 - level;
      return { 
        "DEFP": -drop, 
        "MDEFP": -drop 
      };
    }
  },
  {
    "id": 12,
    "name": "Flash Blast",
    "nameKo": "필로 에클레르",
    "prereq": 11,
    "x": 3,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/12_Flash Blast.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isDual = (stats && stats.mainWeapon === "한손검" && stats.subWeapon === "한손검");
      let effects = { "UnsheatheDamage": level };
      if (isDual) {
        effects["WATKP"] = 25;
      }
      return effects;
    }
  },
  {
    "id": 13,
    "name": "Storm Reaper",
    "nameKo": "스톰 리퍼",
    "prereq": 12,
    "x": 4,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/13_Storm Reaper.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": false, 
    "longRange": true,
    "unsheathePower": true,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      return 4 + (0.1 * level) + (dex / 25) * (level / 100);
    },
    "getConstant": function(level, stats) {
      return 100 + (10 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 14,
    "name": "Dual Sword Control",
    "nameKo": "쌍검 단련",
    "prereq": 0,
    "x": 1,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/14_Dual Sword Control.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "ASPD": 50 * level, 
        "HITP": 5 + (3 * level), 
        "CRIT": 5 + (3 * level) 
      };
    }
  },
  {
    "id": 15,
    "name": "Godspeed",
    "nameKo": "신속의 저력",
    "prereq": 14,
    "x": 2,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/15_Godspeed.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isDual = (stats && stats.mainWeapon === "한손검" && stats.subWeapon === "한손검");
      let unsheathe = 5 + level + (isDual ? 10 : 0);
      let agi = (level <= 5) ? level : (2 * level) - 5;
      return { 
        "UnsheatheDamage": unsheathe, 
        "AGI": agi 
      };
    }
  },
  {
    "id": 16,
    "name": "Saber Aura",
    "nameKo": "세이버 오라",
    "prereq": 15,
    "x": 4,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/16_Saber Aura.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 17,
    "name": "Crescent Saber",
    "nameKo": "아크 세이버",
    "prereq": 16,
    "x": 5,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/17_Crescent Saber.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["한손검(듀얼소드)"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "CRIT": 10 * level, 
        "AMPR": 2 * level 
      };
    }
  },
  {
    "id": 18,
    "name": "Aerial Slay",
    "nameKo": "에리얼슬레이",
    "prereq": 15,
    "x": 4,
    "y": 9,
    "via": [2, 9],
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/18_Aerial Slay.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isDual = (stats && stats.mainWeapon === "한손검" && stats.subWeapon === "한손검");
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0;
      let baseDex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      let agi = (stats && stats.baseAGI) ? stats.baseAGI : 0;
      
      if (isDual) {
        return level + (Math.max(str, baseDex, agi) / 200);
      } else {
        return (0.5 * level) + (dex / 100);
      }
    },
    "getConstant": function(level, stats) {
      return 100 + (20 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 19,
    "name": "Horizon Cut",
    "nameKo": "호라이즌탈 컷",
    "prereq": 18,
    "x": 5,
    "y": 9,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/19_Horizon Cut.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isDual = (stats && stats.mainWeapon === "한손검" && stats.subWeapon === "한손검");
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      
      if (isDual) {
        return 4.5 + (0.05 * level) + (dex / 200);
      } else {
        return 9 + (0.1 * level) + (dex / 100);
      }
    },
    "getConstant": function(level, stats) {
      let isDual = (stats && stats.mainWeapon === "한손검" && stats.subWeapon === "한손검");
      return isDual ? (30 * level) : (60 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 20,
    "name": "Sting Blade",
    "nameKo": "블레이드 스팅거",
    "prereq": 18,
    "x": 6,
    "y": 8,
    "via": [4, 8],
    "icon": "coryn_skill_icons/Weapon Skills/DualSword/20_Sting Blade.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isDual = (stats && stats.mainWeapon === "한손검" && stats.subWeapon === "한손검");
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      
      if (isDual) {
        return 3 + (0.4 * level);
      } else {
        return 3 + (0.4 * level) + (dex / 100);
      }
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  }
];