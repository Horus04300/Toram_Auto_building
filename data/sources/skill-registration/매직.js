const magicSkills = [
  {
    "id": 0,
    "name": "Magic: Arrows",
    "nameKo": "술식/애로",
    "prereq": -1,
    "x": 0,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/00_Magic_ Arrows.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": true, //[cite: 5]
    "longRange": true, //[cite: 5]
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isStaff = (stats && stats.mainWeapon === "지팡이"); //[cite: 5]
      return 0.65 + (0.06 * level) + (isStaff ? 0.25 : 0); //[cite: 5]
    },
    "getConstant": function(level, stats) {
      return 90 + (5 * level); //[cite: 5]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 1,
    "name": "Magic: Javelin",
    "nameKo": "술식/쟈베린",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/01_Magic_ Javelin.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": true, //[cite: 5]
    "longRange": true, //[cite: 5]
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isStaff = (stats && stats.mainWeapon === "지팡이"); //[cite: 5]
      return 1.5 + (0.1 * level) + (isStaff ? 0.5 : 0); //[cite: 5]
    },
    "getConstant": function(level, stats) {
      return 50 + (15 * level); //[cite: 5]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Magic: Lances",
    "nameKo": "술식/랜서",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/02_Magic_ Lances.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": true, //[cite: 5]
    "longRange": true, //[cite: 5]
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isStaff = (stats && stats.mainWeapon === "지팡이"); //[cite: 5]
      let isMD = (stats && stats.mainWeapon === "마도구"); //[cite: 5]
      let totalINT = (stats && stats.totalINT) ? stats.totalINT : 0; //[cite: 5]
      let bonus = 0; //[cite: 5]
      if (isStaff) bonus = 1.5 + (totalINT / 500); //[cite: 5]
      else if (isMD) bonus = totalINT / 500; //[cite: 5]
      return 2.5 + (0.15 * level) + bonus; //[cite: 5]
    },
    "getConstant": function(level, stats) {
      return 300 + (40 * level); //[cite: 5]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Magic: Impact",
    "nameKo": "술식/임팩트",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/03_Magic_ Impact.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": true, //[cite: 5]
    "longRange": true, //[cite: 5]
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isMD = (stats && stats.mainWeapon === "마도구"); //[cite: 5]
      return (0.25 * level) + (isMD ? 2.5 : 0); //[cite: 5]
    },
    "getConstant": function(level, stats) {
      return 100 + (10 * level); //[cite: 5]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Magic: Finale",
    "nameKo": "술식/피날레",
    "prereq": 3,
    "x": 4,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/04_Magic_ Finale.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": false, //[cite: 5]
    "longRange": false, //[cite: 5]
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isStaff = (stats && stats.mainWeapon === "지팡이"); //[cite: 5]
      let baseINT = (stats && stats.baseINT) ? stats.baseINT : 0; //[cite: 5]
      return 30 + (isStaff ? (7.5 + (baseINT / 100)) : 0); //[cite: 5]
    },
    "getConstant": function(level, stats) {
      return 300 * level; //[cite: 5]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Chronos Shift",
    "nameKo": "크로노스 시프트",
    "prereq": 4,
    "x": 5,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/05_Chronos Shift.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["메인 마도구"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Magic: Laser",
    "nameKo": "술식/레이저",
    "prereq": 4,
    "x": 6,
    "y": 1,
    "via": [4, 1],
    "icon": "coryn_skill_icons/Weapon Skills/Magic/06_Magic_ Laser.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["한손검", "지팡이", "메인 마도구"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.75 * level; //[cite: 5]
    },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 7,
    "name": "Magic: Wall",
    "nameKo": "술식/월",
    "prereq": 0,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/07_Magic_ Wall.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": true, //[cite: 5]
    "longRange": true, //[cite: 5]
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isStaff = (stats && stats.mainWeapon === "지팡이"); //[cite: 5]
      let baseINT = (stats && stats.baseINT) ? stats.baseINT : 0; //[cite: 5]
      return 0.8 + (0.04 * level) + (baseINT / 1000) + (isStaff ? 0.3 : 0); //[cite: 5]
    },
    "getConstant": function(level, stats) {
      return 120 + (10 * level); //[cite: 5]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 8,
    "name": "Magic: Blast",
    "nameKo": "술식/블래스트",
    "prereq": 7,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/08_Magic_ Blast.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": true, //[cite: 5]
    "longRange": true, //[cite: 5]
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isStaff = (stats && stats.mainWeapon === "지팡이"); //[cite: 5]
      let isMD = (stats && stats.mainWeapon === "마도구"); //[cite: 5]
      let totalINT = (stats && stats.totalINT) ? stats.totalINT : 0; //[cite: 5]
      let bonus = 0; //[cite: 5]
      if (isStaff) bonus = 1.5 + (totalINT / 500); //[cite: 5]
      else if (isMD) bonus = totalINT / 500; //[cite: 5]
      return 7 + (0.3 * level) + bonus; //[cite: 5]
    },
    "getConstant": function(level, stats) {
      return 180 + (20 * level); //[cite: 5]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Magic: Storm",
    "nameKo": "술식/스톰",
    "prereq": 8,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/09_Magic_ Storm.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": true, //[cite: 5]
    "longRange": true, //[cite: 5]
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isStaff = (stats && stats.mainWeapon === "지팡이"); //[cite: 5]
      return 1.8 + (0.02 * level) + (isStaff ? 1 : 0); //[cite: 5]
    },
    "getConstant": function(level, stats) {
      return 420; //[cite: 5]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Magic: Burst",
    "nameKo": "술식/버스트",
    "prereq": 9,
    "x": 4,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/10_Magic_ Burst.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 15 + (0.6 * level); //[cite: 5]
    },
    "getConstant": function(level, stats) {
      return 200 + (30 * level); //[cite: 5]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Magic: Magic Cannon",
    "nameKo": "술식/매직 카논",
    "prereq": 10,
    "x": 5,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/11_Magic_ Magic Cannon.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let chargePercent = 100; //[cite: 5]
      return 0.03 * level * chargePercent; //[cite: 5]
    },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 12,
    "name": "Magic: Crash",
    "nameKo": "술식/폴",
    "prereq": 9,
    "x": 6,
    "y": 3,
    "via": [3, 3],
    "icon": "coryn_skill_icons/Weapon Skills/Magic/12_Magic_ Crash.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 3 + (0.2 * level); //[cite: 5]
    },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 13,
    "name": "Magic Mastery",
    "nameKo": "매직 마스터리",
    "prereq": -1,
    "x": 0,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/13_Magic Mastery.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 5]
    "conditions": ["지팡이", "메인 마도구"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let matkp = 0; //[cite: 5]
      if (level >= 1 && level <= 2) matkp = 1; //[cite: 5]
      else if (level >= 3 && level <= 7) matkp = 2; //[cite: 5]
      else if (level >= 8) matkp = 3; //[cite: 5]
      return { 
        "WATKP": 3 * level, //[cite: 5]
        "MATKP": matkp //[cite: 5]
      };
    }
  },
  {
    "id": 14,
    "name": "Magic Knife",
    "nameKo": "매직 나이프",
    "prereq": 13,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/14_Magic Knife.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["지팡이"], //[cite: 5]
    "damagetype": "physical", //[cite: 5]
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.6 + (0.1 * level); //[cite: 5]
    },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 15,
    "name": "Qadal",
    "nameKo": "게달 일렉시오",
    "prereq": 14,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/15_Qadal.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 5]
    "conditions": ["지팡이"], //[cite: 5]
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 16,
    "name": "Spell Calibration",
    "nameKo": "스펠 튜닝",
    "prereq": 15,
    "x": 4,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/16_Spell Calibration.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 5]
    "conditions": ["지팡이", "메인 마도구"], //[cite: 5]
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 17,
    "name": "MP Charge",
    "nameKo": "차징",
    "prereq": -1,
    "x": 0,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/17_MP Charge.png",
    "iconAvailable": true,
    "type": "active", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 18,
    "name": "Chain Cast",
    "nameKo": "체인 캐스트",
    "prereq": 17,
    "x": 2,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/18_Chain Cast.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 19,
    "name": "Power Wave",
    "nameKo": "파워 웨이브",
    "prereq": 18,
    "x": 3,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/19_Power Wave.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 20,
    "name": "Maximizer",
    "nameKo": "맥시마이저",
    "prereq": 19,
    "x": 4,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/20_Maximizer.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 5]
    "conditions": ["All"], //[cite: 5]
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 21,
    "name": "Rapid Charge",
    "nameKo": "급속 차지",
    "prereq": 20,
    "x": 5,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/21_Rapid Charge.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 5]
    "conditions": ["지팡이", "마도구"], //[cite: 5]
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 22,
    "name": "Enchanted Barrier",
    "nameKo": "술식 결계",
    "prereq": 20,
    "x": 5,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/22_Enchanted Barrier.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 5]
    "conditions": ["지팡이", "메인 마도구"], //[cite: 5]
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 23,
    "name": "Magic: Guardian Beam",
    "nameKo": "술식/이겔",
    "prereq": -1,
    "x": 3,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Magic/23_Magic_ Guardian Beam.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 5]
    "conditions": ["지팡이", "메인 마도구"], //[cite: 5]
    "damagetype": "magic", //[cite: 5]
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let totalINT = (stats && stats.totalINT) ? stats.totalINT : 0; //[cite: 5]
      return 0.5 + (totalINT / 100); //[cite: 5]
    },
    "getConstant": function(level, stats) {
      return 300; //[cite: 5]
    },
    "getEffects": function(level, stats) { return {}; }
  }
];