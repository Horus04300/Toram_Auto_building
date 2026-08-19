const wizardSkills = [
  {
    "id": 0,
    "name": "Familia",
    "nameKo": "패밀리어",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/00_Familia.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["지팡이", "마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let pLevel = (stats && stats.level) ? stats.level : 0;
      let matkBonus = pLevel / (10 - 0.6 * level);
      return { 
        "MAXMP": 100 + (10 * level),
        "MATK": matkBonus
      };
    }
  },
  {
    "id": 1,
    "name": "Lightning",
    "nameKo": "라이트닝",
    "prereq": 0,
    "x": 2,
    "y": 0,
    "via": [0, 0],
    "icon": "coryn_skill_icons/Buff Skills/Wizard/01_Lightning.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이", "마도구"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let highFamLevel = (stats && stats.skill_AdvancedFamilia) ? stats.skill_AdvancedFamilia : 0;
      return 4 + (0.3 * level) + (0.45 * highFamLevel);
    },
    "getConstant": function(level, stats) {
      return 80;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Blizzard",
    "nameKo": "블리자드",
    "prereq": 0,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/02_Blizzard.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이", "마도구"],
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let highFamLevel = (stats && stats.skill_AdvancedFamilia) ? stats.skill_AdvancedFamilia : 0;
      return 1 + (0.05 * level) + (0.075 * highFamLevel); // 각 히트당 계수
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Meteor Strike",
    "nameKo": "메테오 스트라이크",
    "prereq": 2,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/03_Meteor Strike.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이", "마도구"],
    "damagetype": "magic",
    "distancePower": true, // 근/원거리 중 높은 것 적용이므로 true 처리
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let highFamLevel = (stats && stats.skill_AdvancedFamilia) ? stats.skill_AdvancedFamilia : 0;
      return 5 + level + (0.75 * highFamLevel); // 각 히트당 계수
    },
    "getConstant": function(level, stats) {
      return 300;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Imperial Ray",
    "nameKo": "임페리얼 레이",
    "prereq": 3,
    "x": 4,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/04_Imperial Ray.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이", "마도구"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let magicResearchLevel = (stats && stats.skill_MagicResearch) ? stats.skill_MagicResearch : 0;
      return 5 + (0.5 * level) + (0.2 * magicResearchLevel); // 첫 타 기준 (마술 연구 보너스 포함)
    },
    "getConstant": function(level, stats) {
      return 200 + (20 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Magic Research",
    "nameKo": "마술 연구",
    "prereq": 4,
    "x": 5,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/05_Magic Research.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["지팡이", "마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 임페리얼 레이 강화 및 사역마 영창 시간 감소 패시브
  },
  {
    "id": 6,
    "name": "Mana Crystal",
    "nameKo": "마나 크리스탈",
    "prereq": 0,
    "x": 1,
    "y": 4,
    "via": [0, 4],
    "icon": "coryn_skill_icons/Buff Skills/Wizard/06_Mana Crystal.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["지팡이", "마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 7,
    "name": "Stone Barrier",
    "nameKo": "스톤 스킨",
    "prereq": 6,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/07_Stone Barrier.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["지팡이", "마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 배리어 부여 버프
  },
  {
    "id": 8,
    "name": "Advanced Familia",
    "nameKo": "하이 패밀리어",
    "prereq": 7,
    "x": 4,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/08_Advanced Familia.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["지팡이", "마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 자동 스킬 시전 및 패시브 계수 증가 패시브
  },
  {
    "id": 9,
    "name": "Kitty's Treasure",
    "nameKo": "고양이의 분실물",
    "prereq": 8,
    "x": 5,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/09_Kitty's Treasure.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["지팡이", "메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Cast Mastery",
    "nameKo": "캐스트 마스터리",
    "prereq": -1,
    "x": 0,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/10_Cast Mastery.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["지팡이", "메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "CSPD": 100 * level, // 대략적인 시속 증가치 반영 (상세 공식은 외부 연산)
        "ATKP": -(50 - 2.5 * level) 
      };
    }
  },
  {
    "id": 11,
    "name": "Crystal Laser",
    "nameKo": "크리스탈 레이저",
    "prereq": 6,
    "x": 2,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/11_Crystal Laser.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["지팡이", "메인 마도구"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 7 + (0.3 * level);
    },
    "getConstant": function(level, stats) {
      return 200;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 12,
    "name": "Overlimit",
    "nameKo": "오버 리미트",
    "prereq": 11,
    "x": 3,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/12_Overlimit.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["지팡이", "메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "AttributeDamage": level, // 속성 데미지 증가
        "CSPD": -1000 
      };
    }
  },
  {
    "id": 13,
    "name": "Sorcery Guide",
    "nameKo": "마술 가이드",
    "prereq": 12,
    "x": 4,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/13_Sorcery Guide.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["지팡이", "메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "AttributeDamage": level }; // 오버 리미트 속성 데미지 추가 증가
    }
  },
  {
    "id": 14,
    "name": "Shift",
    "nameKo": "시프트",
    "prereq": 13,
    "x": 5,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Wizard/14_Shift.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["지팡이", "메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  }
];