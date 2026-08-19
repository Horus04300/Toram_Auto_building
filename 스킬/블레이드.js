const bladeSkills = [
  {
    "id": 0,
    "name": "Hammer Slam",
    "nameKo": "해머 다운",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/00_Hammer Slam.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let vit = (stats && stats.totalVIT) ? stats.totalVIT : 0;
      return 1 + (0.5 * level) + (vit / 100);
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) {
      return {};
    }
  },
  {
    "id": 1,
    "name": "Cleaving Attack",
    "nameKo": "클리브 어택",
    "prereq": 0,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/01_Cleaving Attack.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0;
      let hitCount = 1; // 1체 타격 가정
      return 1.5 + (0.1 * level) + ((str / 200) * (hitCount - 1));
    },
    "getConstant": function(level, stats) {
      let vit = (stats && stats.totalVIT) ? stats.totalVIT : 0;
      return 150 + (15 * level) + vit;
    },
    "getEffects": function(level, stats) {
      return {};
    }
  },
  {
    "id": 2,
    "name": "Storm Blaze",
    "nameKo": "스톰 블레이저",
    "prereq": 1,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/02_Storm Blaze.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      let maxStacks = 10 + Math.floor(dex / 25);
      let consumedStacks = Math.min(10, maxStacks); // 최대 10스택 소모 가정
      return (0.5 + 0.05 * level) * consumedStacks;
    },
    "getConstant": function(level, stats) {
      let vit = (stats && stats.totalVIT) ? stats.totalVIT : 0;
      return 100 + (10 * level) + vit;
    },
    "getEffects": function(level, stats) {
      return {};
    }
  },
  {
    "id": 3,
    "name": "Garde Blade",
    "nameKo": "가드 블레이드",
    "prereq": 2,
    "x": 4,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/03_Garde Blade.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["양손검"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "P_RES": level, "M_RES": level };
    }
  },
  {
    "id": 4,
    "name": "Ogre Slash",
    "nameKo": "오거 슬래시",
    "prereq": 3,
    "x": 5,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/04_Ogre Slash.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0;
      let vit = (stats && stats.baseVIT) ? stats.baseVIT : 0;
      let stacks = 10; // 단일 타격 기준 최대 10스택 소모 적용
      
      let baseMulti = (str + vit) / 100;
      let pierceBonus = level * stacks; 
      
      if (pierceBonus > 100) {
        baseMulti += (pierceBonus - 100) * 0.01;
      }
      return baseMulti;
    },
    "getConstant": function(level, stats) {
      return (stats && stats.totalDEX) ? stats.totalDEX : 0;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Hard Hit",
    "nameKo": "하드 히트",
    "prereq": -1,
    "x": 0,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/05_Hard Hit.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let is2h = (stats && stats.mainWeapon === "양손검");
      return 1 + (0.05 * level) + (is2h ? 0.5 : 0);
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Astute",
    "nameKo": "아스튜트",
    "prereq": 5,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/06_Astute.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let is2h = (stats && stats.mainWeapon === "양손검");
      return 1.5 + (0.1 * level) + (is2h ? 0.5 : 0);
    },
    "getConstant": function(level, stats) {
      return 150 + (5 * level);
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let is2h = (stats && stats.mainWeapon === "양손검");
      return { 
        "CRIT": 25 + (is2h ? 25 : 0), 
        "ASPDP": 5 * level 
      };
    }
  },
  {
    "id": 7,
    "name": "Trigger Slash",
    "nameKo": "트리거 슬래시",
    "prereq": 6,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/07_Trigger Slash.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let is2h = (stats && stats.mainWeapon === "양손검");
      return 1.5 + (0.05 * level) + (is2h ? 1 : 0);
    },
    "getConstant": function(level, stats) {
      return 200 + (10 * level);
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "AMPR": 2 * level };
    }
  },
  {
    "id": 8,
    "name": "Rampage",
    "nameKo": "램페이지",
    "prereq": 7,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/08_Rampage.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "AMPR": 2.5 * level };
    }
  },
  {
    "id": 9,
    "name": "Meteor Breaker",
    "nameKo": "메테오 브레이커",
    "prereq": 7,
    "x": 4,
    "y": 3,
    "via": [2, 3],
    "icon": "coryn_skill_icons/Weapon Skills/Blade/09_Meteor Breaker.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let is2h = (stats && stats.mainWeapon === "양손검");
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0;
      return 4 + (0.2 * level) + (is2h ? (2 + (str / 1000)) : 0); // 1타 단일 타격 계수
    },
    "getConstant": function(level, stats) {
      return 400 + (20 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Shut-Out",
    "nameKo": "셧아웃",
    "prereq": 8,
    "x": 6,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/10_Shut-Out.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let is2h = (stats && stats.mainWeapon === "양손검");
      let is1h = (stats && stats.mainWeapon === "한손검");
      let isDual = (is1h && stats && stats.subWeapon === "한손검");
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      let agi = (stats && stats.baseAGI) ? stats.baseAGI : 0;
      
      let multi = 5;
      if (is2h) multi += level;
      else if (isDual) multi += (agi / 400);
      else if (is1h) multi += (dex / 200);
      return multi;
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Lunar Slash",
    "nameKo": "문 슬래시",
    "prereq": 9,
    "x": 5,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/11_Lunar Slash.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 10;
    },
    "getConstant": function(level, stats) {
      return 400;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 12,
    "name": "Sonic Blade",
    "nameKo": "액셀 블레이드",
    "prereq": 5,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/12_Sonic Blade.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let is2h = (stats && stats.mainWeapon === "양손검");
      return 1 + (0.05 * level) + (is2h ? 0.5 : 0);
    },
    "getConstant": function(level, stats) {
      return 100 + (5 * level);
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let is1h = (stats && stats.mainWeapon === "한손검");
      return { "CRIT": level * (is1h ? 10 : 1) };
    }
  },
  {
    "id": 13,
    "name": "Spiral Air",
    "nameKo": "스파이럴 에어",
    "prereq": 12,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/13_Spiral Air.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let is2h = (stats && stats.mainWeapon === "양손검");
      return 0.1 + (0.03 * level) + (is2h ? 0.5 : 0);
    },
    "getConstant": function(level, stats) {
      return 30;
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let is2h = (stats && stats.mainWeapon === "양손검");
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      let cdmg = 0.5 + (0.5 * level) + (dex / 50);
      if (is2h) cdmg /= 2; 
      return { "CDMG": cdmg };
    }
  },
  {
    "id": 14,
    "name": "Sword Tempest",
    "nameKo": "소드 템페스트",
    "prereq": 13,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/14_Sword Tempest.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let is2h = (stats && stats.mainWeapon === "양손검");
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0;
      return 1.5 + (0.1 * level) + (is2h ? (1 + (str / 500)) : 0);
    },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 15,
    "name": "Buster Blade",
    "nameKo": "버스터 블레이드",
    "prereq": 13,
    "x": 4,
    "y": 5,
    "via": [2, 5],
    "icon": "coryn_skill_icons/Weapon Skills/Blade/15_Buster Blade.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let is2h = (stats && stats.mainWeapon === "양손검");
      let is1h = (stats && stats.mainWeapon === "한손검");
      let isDual = (is1h && stats && stats.subWeapon === "한손검");
      
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0;
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      let auraLevel = (stats && stats.skill_AuraBlade) ? stats.skill_AuraBlade : 0;
      
      let multi = 0.75 * level;
      if (is2h) {
        multi += (str / 100);
      } else if (is1h && !isDual) {
        multi += (dex / 200) + (0.2 * auraLevel);
      } else if (isDual) {
        multi += (dex / 200);
      }
      return multi;
    },
    "getConstant": function(level, stats) {
      return 30 * level;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 16,
    "name": "Aura Blade",
    "nameKo": "오라 블레이드",
    "prereq": 15,
    "x": 5,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/16_Aura Blade.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 5 + level;
    },
    "getConstant": function(level, stats) {
      return 200;
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let is2h = (stats && stats.mainWeapon === "양손검");
      let is1h = (stats && stats.mainWeapon === "한손검");
      let isDual = (is1h && stats && stats.subWeapon === "한손검");
      
      let dmgBonus = 0;
      if (is2h) dmgBonus = 30;
      else if (isDual) dmgBonus = 10;
      else if (is1h) dmgBonus = 20;
      return { "DamageBonus": dmgBonus }; 
    }
  },
  {
    "id": 17,
    "name": "Sword Mastery",
    "nameKo": "블레이드 마스터리",
    "prereq": -1,
    "x": 0,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/17_Sword Mastery.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["한손검", "양손검"],
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
      return { "WATKP": 3 * level, "ATKP": atkp };
    }
  },
  {
    "id": 18,
    "name": "Quick Slash",
    "nameKo": "재빠른 참격",
    "prereq": 17,
    "x": 1,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/18_Quick Slash.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "ASPDP": level, "ASPD": 10 * level };
    }
  },
  {
    "id": 19,
    "name": "Sword Techniques",
    "nameKo": "장인의 검술",
    "prereq": 18,
    "x": 2,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/19_Sword Techniques.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "SkillDamage": 2 * level }; 
    }
  },
  {
    "id": 20,
    "name": "War Cry",
    "nameKo": "워 크라이",
    "prereq": 18,
    "x": 3,
    "y": 7,
    "via": [1, 7],
    "icon": "coryn_skill_icons/Weapon Skills/Blade/20_War Cry.png",
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
      let is2h = (stats && stats.mainWeapon === "양손검");
      return { "ATKP": level + (is2h ? 5 : 0) };
    }
  },
  {
    "id": 21,
    "name": "Berserk",
    "nameKo": "버서크",
    "prereq": 20,
    "x": 4,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/21_Berserk.png",
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
      let is2h = (stats && stats.mainWeapon === "양손검");
      let is1h = (stats && stats.mainWeapon === "한손검");
      
      let crit = 2.5 * level * (is2h ? 2 : 1);
      let stabDrop = 100 - (5 * level);
      if (is1h || is2h) stabDrop /= 2; 
      
      let defDrop = 100 - level;
      if (is1h) defDrop /= 2; 
      
      return { 
        "ASPDP": 10 * level, 
        "ASPD": 100 * level, 
        "CRIT": crit,
        "Stability": -stabDrop,
        "DEFP": -defDrop,
        "MDEFP": -defDrop
      };
    }
  },
  {
    "id": 22,
    "name": "Gladiate",
    "nameKo": "글래디에이트",
    "prereq": 21,
    "x": 5,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/22_Gladiate.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 23,
    "name": "Swift Attack",
    "nameKo": "퍼스트 어택",
    "prereq": -1,
    "x": 3,
    "y": 9,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Blade/23_Swift Attack.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["한손검", "양손검"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let is2h = (stats && stats.mainWeapon === "양손검");
      let is1h = (stats && stats.mainWeapon === "한손검");
      let isDual = (is1h && stats && stats.subWeapon === "한손검");
      
      let baseMulti = Math.min(0.5, 0.05 + 0.05 * level);
      let bonus = 0;
      if (isDual) {
        bonus = ((stats && stats.totalAGI) ? stats.totalAGI : 0) / 500;
      } else if (is1h) {
        bonus = ((stats && stats.totalDEX) ? stats.totalDEX : 0) / 500;
      } else if (is2h) {
        bonus = ((stats && stats.totalSTR) ? stats.totalSTR : 0) / 500;
      }
      return baseMulti + bonus;
    },
    "getConstant": function(level, stats) {
      return Math.min(300, 3 * Math.pow(level + 1, 2));
    },
    "getEffects": function(level, stats) { return {}; }
  }
];