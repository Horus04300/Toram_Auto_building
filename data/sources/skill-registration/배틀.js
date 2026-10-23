const battleSkills = [
  {
    "id": 0,
    "name": "Magic UP",
    "nameKo": "마법력 UP",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/00_Magic UP.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let pLevel = (stats && stats.level) ? stats.level : 0;
      return { "MATK": (2.5 * level * pLevel) / 100 };
    }
  },
  {
    "id": 1,
    "name": "Concentrate",
    "nameKo": "집중",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/01_Concentrate.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 확률 발동형 데미지 증가 (외부 연산 필요)
  },
  {
    "id": 2,
    "name": "Attack UP",
    "nameKo": "공격력 UP",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/02_Attack UP.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let pLevel = (stats && stats.level) ? stats.level : 0;
      return { "ATK": (2.5 * level * pLevel) / 100 };
    }
  },
  {
    "id": 3,
    "name": "Whack",
    "nameKo": "강타",
    "prereq": 2,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/03_Whack.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 확률 발동형 데미지 증가 (외부 연산 필요)
  },
  {
    "id": 4,
    "name": "Defense UP",
    "nameKo": "방어력 UP",
    "prereq": -1,
    "x": 0,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/04_Defense UP.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let pLevel = (stats && stats.level) ? stats.level : 0;
      return { 
        "DEF": (2.5 * level * pLevel) / 100, 
        "MDEF": (2.5 * level * pLevel) / 100 
      };
    }
  },
  {
    "id": 5,
    "name": "Dodge UP",
    "nameKo": "회피 UP",
    "prereq": 4,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/05_Dodge UP.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "FLEE": level };
    }
  },
  {
    "id": 6,
    "name": "Desperate Resist",
    "nameKo": "필사적인 저항",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/06_Desperate Resist.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 행동 불능 시 데미지 감소 (외부 연산 필요)
  },
  {
    "id": 7,
    "name": "Critical UP",
    "nameKo": "크리티컬 UP",
    "prereq": 3,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/07_Critical UP.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "CRIT": 0.5 * level, 
        "CDMGP": 0.5 * level 
      };
    }
  },
  {
    "id": 8,
    "name": "Accuracy UP",
    "nameKo": "명중 UP",
    "prereq": 5,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/08_Accuracy UP.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "HIT": level };
    }
  },
  {
    "id": 9,
    "name": "Increased Energy",
    "nameKo": "한층 더한 마력",
    "prereq": 6,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/09_Increased Energy.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let pLevel = (stats && stats.level) ? stats.level : 0;
      return { "MATK": (2.5 * level * pLevel) / 100 };
    }
  },
  {
    "id": 10,
    "name": "Intimidating Power",
    "nameKo": "위협의 위력",
    "prereq": 7,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/10_Intimidating Power.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let pLevel = (stats && stats.level) ? stats.level : 0;
      return { "ATK": (2.5 * level * pLevel) / 100 };
    }
  },
  {
    "id": 11,
    "name": "Defense Mastery",
    "nameKo": "수비의 마음가짐",
    "prereq": 8,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/11_Defense Mastery.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let pLevel = (stats && stats.level) ? stats.level : 0;
      return { 
        "DEF": (2.5 * level * pLevel) / 100, 
        "MDEF": (2.5 * level * pLevel) / 100 
      };
    }
  },
  {
    "id": 12,
    "name": "Spell Burst",
    "nameKo": "스펠 버스트",
    "prereq": 9,
    "x": 4,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/12_Spell Burst.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "SpellBurst": 2.5 * level }; // 마법 크리티컬 확률 및 데미지 반영률 증가 변수
    }
  },
  {
    "id": 13,
    "name": "Secret Chase Attack",
    "nameKo": "추격의 극의",
    "prereq": 10,
    "x": 4,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/13_Secret Chase Attack.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 추격 발동 확률 증가 (외부 연산 필요)
  },
  {
    "id": 14,
    "name": "Super Grip",
    "nameKo": "슈퍼그립",
    "prereq": 11,
    "x": 4,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Battle/14_Super Grip.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 사망 시 넉백 거리 감소 (외부 연산 필요)
  }
];