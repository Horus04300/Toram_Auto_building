const golemSkills = [
  {
    "id": 0,
    "name": "Golem Call",
    "nameKo": "골렘 소환",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/00_Golem Call.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["자동활", "지팡이", "메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 골렘 소환 및 플레이어 AMPR 전환 특수 매커니즘
  },
  {
    "id": 1,
    "name": "Neo Lancer",
    "nameKo": "랜서형 개량",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/01_Neo Lancer.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["자동활", "지팡이", "메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "PhysicalPierce": 5 + (7 * level),
        "CRIT": 7.5 * level
      };
    }
  },
  {
    "id": 2,
    "name": "Attack Boost",
    "nameKo": "어택 강화",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/02_Attack Boost.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["자동활", "지팡이", "메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "HIT": 2 * (level * level) };
    }
  },
  {
    "id": 3,
    "name": "Neo Shielder",
    "nameKo": "실드형 개량",
    "prereq": 0,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/03_Neo Shielder.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["자동활", "지팡이", "메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 실드형 골렘 지속 시간 및 데미지 경감 범위 증가
  },
  {
    "id": 4,
    "name": "Shield Boost",
    "nameKo": "실드 강화",
    "prereq": 3,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/04_Shield Boost.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["자동활", "지팡이", "메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Neo Buster",
    "nameKo": "버스터형 개량",
    "prereq": 0,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/05_Neo Buster.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["자동활", "지팡이", "메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "MagicPierce": 5 + (7 * level),
        "CRIT": 7.5 * level
      };
    }
  },
  {
    "id": 6,
    "name": "Speed Boost",
    "nameKo": "스피드 강화",
    "prereq": 5,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/06_Speed Boost.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["자동활", "지팡이", "메인 마도구"],
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
    "name": "Magic Grenade",
    "nameKo": "마도 그레네이드",
    "prereq": -1,
    "x": 0,
    "y": 7,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/07_Magic Grenade.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["자동활", "방패", "메인 맨손"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let intStat = (stats && stats.baseINT) ? stats.baseINT : 0;
      let tecStat = (stats && stats.baseTEC) ? stats.baseTEC : 0;
      let higherStat = Math.max(intStat / 100, tecStat / 50);
      return 1 + (0.4 * level) + higherStat;
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 8,
    "name": "Frost Grenade",
    "nameKo": "동결 그레네이드",
    "prereq": 7,
    "x": 1,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/08_Frost Grenade.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["자동활", "방패", "메인 맨손"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let intStat = (stats && stats.baseINT) ? stats.baseINT : 0;
      let tecStat = (stats && stats.baseTEC) ? stats.baseTEC : 0;
      let higherStat = Math.max(intStat / 100, tecStat / 50);
      return 1 + (0.4 * level) + higherStat;
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Flash Grenade",
    "nameKo": "섬광 그레네이드",
    "prereq": 8,
    "x": 2,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/09_Flash Grenade.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["자동활", "방패", "메인 맨손"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let intStat = (stats && stats.baseINT) ? stats.baseINT : 0;
      let tecStat = (stats && stats.baseTEC) ? stats.baseTEC : 0;
      let higherStat = Math.max(intStat / 100, tecStat / 50);
      return 1 + (0.4 * level) + higherStat;
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Barrier Screen",
    "nameKo": "배리어 스크린",
    "prereq": 7,
    "x": 1,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/10_Barrier Screen.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["자동활", "방패"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 배리어 생성 및 AMPR 감소 패널티
  },
  {
    "id": 11,
    "name": "Barrier Upgrade",
    "nameKo": "배리어 강화",
    "prereq": 10,
    "x": 2,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Assist Skills/Golem/11_Barrier Upgrade.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["자동활", "방패"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 배리어 경감률 증가 및 AMPR 페널티 완화
  }
];