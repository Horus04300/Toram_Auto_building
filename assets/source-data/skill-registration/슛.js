const shotSkills = [
  {
    "id": 0,
    "name": "Power Shot",
    "nameKo": "파워 슈트",
    "prereq": -1,
    "x": 0,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/00_Power Shot.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활", "화살"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1.25 + (0.05 * level);
    },
    "getConstant": function(level, stats) {
      return 50 + (8 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 1,
    "name": "Bullseye",
    "nameKo": "윈 휠",
    "prereq": 0,
    "x": 1,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/01_Bullseye.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활", "화살"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isBow = (stats && stats.mainWeapon === "활");
      return 0.25 + (0.05 * level) + (isBow ? 0.25 : 0);
    },
    "getConstant": function(level, stats) {
      return 30 + (4 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Arrow Rain",
    "nameKo": "애로 레인",
    "prereq": 1,
    "x": 2,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/02_Arrow Rain.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활", "화살"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isBowgun = (stats && stats.mainWeapon === "자동활");
      const multiMap = [0, 1, 1, 1.1, 1.1, 1.15, 1.2, 1.2, 1.25, 1.25, 1.3];
      return multiMap[level] + (isBowgun ? 0.7 : 0);
    },
    "getConstant": function(level, stats) {
      const constMap = [0, 60, 60, 70, 70, 80, 80, 90, 90, 100, 100];
      return constMap[level];
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Snipe",
    "nameKo": "스나이핑",
    "prereq": 1,
    "x": 3,
    "y": 1,
    "via": [1, 1],
    "icon": "coryn_skill_icons/Weapon Skills/Shot/03_Snipe.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활", "화살"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isBow = (stats && stats.mainWeapon === "활");
      let isBowgun = (stats && stats.mainWeapon === "자동활");
      return 7 + (0.1 * level) + (isBow ? 2 : 0) + (isBowgun ? 3 : 0);
    },
    "getConstant": function(level, stats) {
      return 300 + (10 * level);
    },
    "getEffects": function(level, stats) { return {}; } // 크리티컬 패널티 및 안정률 보너스는 특수 연산 필요
  },
  {
    "id": 4,
    "name": "Cross Fire",
    "nameKo": "크로스 파이어",
    "prereq": 2,
    "x": 4,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/04_Cross Fire.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isBowgun = (stats && stats.mainWeapon === "자동활");
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      let maxCharge = Math.min(5, Math.floor((level + 3) / 2)); // 편의상 최대 차지 가정식 사용 (실제 최대 5차지)
      let charge = 5; 
      if (isBowgun) {
        return (4 + 0.5 * level) * charge;
      } else {
        return (4.5 + 0.5 * level + (dex / 500)) * charge;
      }
    },
    "getConstant": function(level, stats) {
      return 300 + (10 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Piercing Shot",
    "nameKo": "페니트레이터",
    "prereq": 3,
    "x": 5,
    "y": 0,
    "via": [3, 0],
    "icon": "coryn_skill_icons/Weapon Skills/Shot/05_Piercing Shot.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0;
      return 10 + (0.25 * level) + (Math.max(dex, str) / 200);
    },
    "getConstant": function(level, stats) {
      return 600;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Vanquisher",
    "nameKo": "콘퀘스터",
    "prereq": 3,
    "x": 6,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/06_Vanquisher.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      let intStat = (stats && stats.baseINT) ? stats.baseINT : 0;
      let isSubKatana = (stats && stats.subWeapon === "발도검");
      let isSubMD = (stats && stats.subWeapon === "마도구");
      
      let bonus = dex / 100;
      if (isSubKatana) bonus = 0;
      else if (isSubMD) bonus = intStat / 200;
      
      return 5 + level + bonus;
    },
    "getConstant": function(level, stats) {
      let isSubKatana = (stats && stats.subWeapon === "발도검");
      let isSubMD = (stats && stats.subWeapon === "마도구");
      return 1200 - ((isSubKatana || isSubMD) ? 600 : 0);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 7,
    "name": "Twin Storm",
    "nameKo": "트윈 스톰",
    "prereq": 4,
    "x": 5,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/07_Twin Storm.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["자동활"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "ASPD": 100 * level };
    }
  },
  {
    "id": 8,
    "name": "Retrograde Shot",
    "nameKo": "역행 사격",
    "prereq": 4,
    "x": 5,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/08_Retrograde Shot.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      return 5 + (0.5 * level) + (dex / 100);
    },
    "getConstant": function(level, stats) {
      return 300;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Quick Loader",
    "nameKo": "퀵 로더",
    "prereq": 4,
    "x": 6,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/09_Quick Loader.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["활", "자동활"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Moeba Shot",
    "nameKo": "메바 샷",
    "prereq": 0,
    "x": 1,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/10_Moeba Shot.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활", "화살"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isBowgun = (stats && stats.mainWeapon === "자동활");
      return 1 + (0.05 * level) + (isBowgun ? 0.5 : 0);
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Paralysis Shot",
    "nameKo": "패럴라이즈 샷",
    "prereq": 10,
    "x": 2,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/11_Paralysis Shot.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활", "화살"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isBow = (stats && stats.mainWeapon === "활");
      let isBowgun = (stats && stats.mainWeapon === "자동활");
      return 1.1 + (0.05 * level) + (isBow ? 1 : 0) + (isBowgun ? 1.5 : 0);
    },
    "getConstant": function(level, stats) {
      return 100 + (20 * level);
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "Stability": level };
    }
  },
  {
    "id": 12,
    "name": "Smoke Dust",
    "nameKo": "스모크 더스트",
    "prereq": 11,
    "x": 3,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/12_Smoke Dust.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활", "화살"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isBow = (stats && stats.mainWeapon === "활");
      let isBowgun = (stats && stats.mainWeapon === "자동활");
      return 1.2 + (0.05 * level) + (isBow ? 2 : 0) + (isBowgun ? 2.5 : 0);
    },
    "getConstant": function(level, stats) {
      return 200 + (30 * level);
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "HIT": Math.floor((level * level) / 2) + (5 * level) };
    }
  },
  {
    "id": 13,
    "name": "Arm Break",
    "nameKo": "암 브레이크",
    "prereq": 12,
    "x": 4,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/13_Arm Break.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활", "화살"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isBow = (stats && stats.mainWeapon === "활");
      let isBowgun = (stats && stats.mainWeapon === "자동활");
      return 3 + (0.05 * level) + (isBow ? 3 : 0) + (isBowgun ? 3.5 : 0);
    },
    "getConstant": function(level, stats) {
      return 300 + (40 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 14,
    "name": "Parabola Cannon",
    "nameKo": "파라볼라 카논",
    "prereq": 13,
    "x": 6,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/14_Parabola Cannon.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활", "화살"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      return 7.5 + (0.25 * level) + (dex / 100);
    },
    "getConstant": function(level, stats) {
      return 40 * level;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 15,
    "name": "Spread Shot",
    "nameKo": "와이드 스프레드",
    "prereq": 13,
    "x": 5,
    "y": 6,
    "via": [4, 6],
    "icon": "coryn_skill_icons/Weapon Skills/Shot/15_Spread Shot.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 2 + (0.1 * level);
    },
    "getConstant": function(level, stats) {
      return 200;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 16,
    "name": "Shot Mastery",
    "nameKo": "슈트 마스터리",
    "prereq": -1,
    "x": 0,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/16_Shot Mastery.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["활", "자동활"],
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
    "id": 17,
    "name": "Long Range",
    "nameKo": "롱 레인지",
    "prereq": 16,
    "x": 2,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/17_Long Range.png",
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
      return { "LRD": level }; // Long Range Damage
    }
  },
  {
    "id": 18,
    "name": "Quick Draw",
    "nameKo": "퀵 드로우",
    "prereq": 17,
    "x": 3,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/18_Quick Draw.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 19,
    "name": "Decoy Shot",
    "nameKo": "디코이 슈터",
    "prereq": 18,
    "x": 4,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/19_Decoy Shot.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.2 + (0.08 * level);
    },
    "getConstant": function(level, stats) {
      return 0;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 20,
    "name": "Element Starter",
    "nameKo": "엘레멘트 리치",
    "prereq": 19,
    "x": 6,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/20_Element Starter.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["활", "자동활"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 21,
    "name": "Samurai Archery",
    "nameKo": "무사 궁술",
    "prereq": 16,
    "x": 5,
    "y": 8,
    "via": [0, 8],
    "icon": "coryn_skill_icons/Weapon Skills/Shot/21_Samurai Archery.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["서브 발도검"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      // 서브 무기(발도검) 공격력에 따른 ATK 상승 및 안정률 보너스는 외부 연산 필요
      return {}; 
    }
  },
  {
    "id": 22,
    "name": "Sneak Attack",
    "nameKo": "하이드 어택",
    "prereq": 16,
    "x": 1,
    "y": 9,
    "via": [0, 9],
    "icon": "coryn_skill_icons/Weapon Skills/Shot/22_Sneak Attack.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
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
    "name": "Hunting Buddy",
    "nameKo": "헌팅 • 원",
    "prereq": 22,
    "x": 4,
    "y": 9,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/23_Hunting Buddy.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["활", "자동활"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 24,
    "name": "Fatal Shot",
    "nameKo": "디스트럭트 샷",
    "prereq": -1,
    "x": 3,
    "y": 10,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Shot/24_Fatal Shot.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.totalSTR) ? stats.totalSTR : 0;
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      return 5 + (0.1 * level) + (str / 200) + (dex / 200);
    },
    "getConstant": function(level, stats) {
      return 200;
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "CRIT": 25 + (5 * level) };
    }
  }
];