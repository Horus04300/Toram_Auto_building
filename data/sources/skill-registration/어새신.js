const assassinSkills = [
  {
    "id": 0,
    "name": "Assassin Stab",
    "nameKo": "어새신 스탭",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/00_Assassin Stab.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isDaggerOrScroll = (stats && ["단검", "인술두루마리"].includes(stats.subWeapon));
      // 백스탭 기준 최대 계수 또는 기본 프론트/사이드 분기 중 백스탭 기준 기본치 반영
      return 1.1 + (0.09 * level) + (isDaggerOrScroll ? 3 : 0);
    },
    "getConstant": function(level, stats) {
      return 30 * level;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 1,
    "name": "Backstep",
    "nameKo": "백 스텝",
    "prereq": 0,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/01_Backstep.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 백스탭 성공 시 어새신 스탭 강화 버프
  },
  {
    "id": 2,
    "name": "Arcane Strike",
    "nameKo": "퓨네빈테",
    "prereq": 1,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/02_Arcane Strike.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["단검", "인술두루마리"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      // 소모 MP를 최대로 가정하거나 기본 계수 형태 적용 (소모 MP에 따라 변동)
      return (0.1 * level) + (0.6 + 0.04 * level) * 20; // 2000mp(최대) 소모 기준 예시
    },
    "getConstant": function(level, stats) {
      return 500 + (50 * level);
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "AMPR": level >= 6 ? 20 : 10 };
    }
  },
  {
    "id": 3,
    "name": "Sicarius",
    "nameKo": "시카리우스",
    "prereq": 1,
    "x": 3,
    "y": 0,
    "via": [1, 0],
    "icon": "coryn_skill_icons/Buff Skills/Assassin/03_Sicarius.png",
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
      let isDaggerOrScroll = (stats && ["단검", "인술두루마리"].includes(stats.subWeapon));
      return { 
        "ATK": 5 * level * (isDaggerOrScroll ? 2 : 1),
        "PhysicalPierce": level + (isDaggerOrScroll ? 15 : 0)
      };
    }
  },
  {
    "id": 4,
    "name": "Secret Assassin",
    "nameKo": "암살의 극의",
    "prereq": 2,
    "x": 4,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/04_Secret Assassin.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 어새신 스탭 및 퓨네빈테 계수 보정 패시브
  },
  {
    "id": 5,
    "name": "Evasion",
    "nameKo": "이베이션",
    "prereq": -1,
    "x": 0,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/05_Evasion.png",
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
      let isDaggerOrScroll = (stats && ["단검", "인술두루마리"].includes(stats.subWeapon));
      let fleeAdd = isDaggerOrScroll ? 10 : level;
      return { 
        "FLEE": level + fleeAdd,
        "FLEEP": level
      };
    }
  },
  {
    "id": 6,
    "name": "Serum",
    "nameKo": "시에라무",
    "prereq": 5,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/06_Serum.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 화상/맹독 대미지 경감 버프
  },
  {
    "id": 7,
    "name": "Foresight",
    "nameKo": "포기",
    "prereq": 6,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/07_Foresight.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 어새신 스탭 계수 보정 및 최소 명중 보정 감소 패시브
  },
  {
    "id": 8,
    "name": "Shadow Walk",
    "nameKo": "쉐도우 워크",
    "prereq": 7,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/08_Shadow Walk.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["단검", "인술두루마리"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 10 + (2 * level); // 강화 물리 피해 기준
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Assault Chase",
    "nameKo": "어솔트 체이스",
    "prereq": 8,
    "x": 4,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/09_Assault Chase.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["All"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 어보이드 회복 및 근거리 위력 증가 버프
  },
  {
    "id": 10,
    "name": "Venom Injection",
    "nameKo": "베놈 인젝트",
    "prereq": -1,
    "x": 0,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/10_Venom Injection.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["단검", "인술두루마리", "메인 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Corrosive Poison",
    "nameKo": "갉아먹는 맹독",
    "prereq": 10,
    "x": 1,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/11_Corrosive Poison.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["단검", "인술두루마리", "메인 맨손"],
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
    "name": "Venom Thief",
    "nameKo": "베놈 스내치",
    "prereq": 11,
    "x": 2,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/12_Venom Thief.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["단검", "인술두루마리", "메인 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 13,
    "name": "Death Reception",
    "nameKo": "데스 리셉션",
    "prereq": 12,
    "x": 3,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/13_Death Reception.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["단검", "인술두루마리", "메인 맨손"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isSpecialWeapon = (stats && ["한손검", "선풍창", "맨손"].includes(stats.mainWeapon));
      return 2.5 + (0.25 * level);
    },
    "getConstant": function(level, stats) {
      return 30 * level;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 14,
    "name": "Poison Master",
    "nameKo": "독 조합사",
    "prereq": 13,
    "x": 4,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Assassin/14_Poison Master.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["단검", "인술두루마리", "메인 맨손"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  }
];