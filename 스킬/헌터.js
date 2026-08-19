const hunterSkills = [
  {
    "id": 0,
    "name": "Kick",
    "nameKo": "킥 백",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/00_Kick.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0;
      if (level <= 5) {
        return (0.1 * level) + (str / 200);
      } else {
        return (0.2 * level) - 0.5 + (str / 200);
      }
    },
    "getConstant": function(level, stats) {
      return 10 * level;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 1,
    "name": "Sunrise Arrow",
    "nameKo": "슬리프 애로",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/01_Sunrise Arrow.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      return 1 + (0.1 * level) + (dex / 100); // 수면 상태 시 최종 계수 2배는 외부 연산
    },
    "getConstant": function(level, stats) {
      return 180 + (2 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Magic Arrow",
    "nameKo": "선라이즈 애로",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/02_Magic Arrow.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["활", "자동활"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "AMPR": level / 2,
        "WATKP": level / 2
      };
    }
  },
  {
    "id": 3,
    "name": "Satellite Arrow",
    "nameKo": "새틀라이트 애로",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/03_Satellite Arrow.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      return 5 + (0.5 * level) + (dex / 100); // 각 히트당 계수
    },
    "getConstant": function(level, stats) {
      return 300;
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "PhysicalPierce": 50 + (5 * level) };
    }
  },
  {
    "id": 4,
    "name": "Focus",
    "nameKo": "포커스",
    "prereq": 3,
    "x": 4,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/04_Focus.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "LRD": level / 2, // 원거리 위력 증가
        "SRD": level / 2  // 근거리 위력 증가 (조건부)
      };
    }
  },
  {
    "id": 5,
    "name": "Sleep Trap",
    "nameKo": "베놈 트랩",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/05_Sleep Trap.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isArrow = (stats && stats.subWeapon === "화살");
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      return (0.01 * level) + (isArrow ? dex / 200 : 0);
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Bear Trap",
    "nameKo": "스네아 트랩",
    "prereq": 5,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/06_Bear Trap.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isArrow = (stats && stats.subWeapon === "화살");
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      return (0.01 * level) + (isArrow ? dex / 200 : 0);
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 7,
    "name": "Land Mine",
    "nameKo": "익스플로시브",
    "prereq": 6,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/07_Land Mine.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isArrow = (stats && stats.subWeapon === "화살");
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      let tec = (stats && stats.baseTEC) ? stats.baseTEC : 0;
      return 2 + (0.6 * level) + (isArrow ? (dex / 50 + tec / 50) : 0);
    },
    "getConstant": function(level, stats) {
      return 100 + (30 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 8,
    "name": "Dark Trap",
    "nameKo": "블랭크 트랩",
    "prereq": 7,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/08_Dark Trap.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["All"],
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isArrow = (stats && stats.subWeapon === "화살");
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      return (0.01 * level) + (isArrow ? dex / 200 : 0);
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level);
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Camouflage",
    "nameKo": "카무플라주",
    "prereq": 8,
    "x": 4,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/09_Camouflage.png",
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
      let pLevel = (stats && stats.level) ? stats.level : 0;
      let isBowOrBowgun = (stats && ["활", "자동활"].includes(stats.mainWeapon));
      let atkBonus = (pLevel / 2) * (level / 10);
      if (isBowOrBowgun) atkBonus *= 2;
      return { 
        "Aggro": -(20 + 4 * level),
        "CRIT": 4 * level,
        "ATK": atkBonus
      };
    }
  },
  {
    "id": 10,
    "name": "Homing Shot",
    "nameKo": "호밍 샷",
    "prereq": -1,
    "x": 0,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/10_Homing Shot.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활", "자동활"],
    "damagetype": "physical",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.1 * level; // 각 히트당 계수
    },
    "getConstant": function(level, stats) {
      let isArrow = (stats && stats.subWeapon === "화살");
      return isArrow ? 200 : 0;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Detection",
    "nameKo": "디텍션",
    "prereq": 10,
    "x": 1,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/11_Detection.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["활", "자동활"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "CRIT": level,
        "Aggro": -(10 + level)
      };
    }
  },
  {
    "id": 12,
    "name": "Cyclon Arrow",
    "nameKo": "사이클론 애로우",
    "prereq": 11,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/12_Cyclon Arrow.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      let isArrow = (stats && stats.subWeapon === "화살");
      return (0.1 * level) + (isArrow ? dex / 200 : 0);
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 13,
    "name": "Vertical Air",
    "nameKo": "버티컬 에어",
    "prereq": 12,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/13_Vertical Air.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["활"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 3 + (0.45 * level); // 1타 기준
    },
    "getConstant": function(level, stats) {
      return 250;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 14,
    "name": "Hunter Bowgun",
    "nameKo": "보우건 헌터",
    "prereq": 11,
    "x": 2,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/14_Hunter Bowgun.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["자동활"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "WATKP": 2.5 * level };
    }
  },
  {
    "id": 15,
    "name": "Multiple Hunt",
    "nameKo": "멀티풀 헌터",
    "prereq": 14,
    "x": 3,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/15_Multiple Hunt.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["자동활"],
    "damagetype": "physical",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let isArrow = (stats && stats.subWeapon === "화살");
      let isShield = (stats && stats.subWeapon === "방패");
      let isDagger = (stats && stats.subWeapon === "단검");
      let isMD = (stats && stats.subWeapon === "마도구");
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      
      if (isArrow || isShield || isDagger || isMD) {
        // 분기별 계수 적용 (화살/권갑/맨손/방패/단검/마도구 등)
        if (isArrow) return 7 + (0.3 * level) + (dex / 200);
        if (isShield) {
          let vit = (stats && stats.totalVIT) ? stats.totalVIT : 0;
          return 7.5 + (0.25 * level) + (vit / 100);
        }
        if (isDagger) {
          let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0;
          return 5 + (0.5 * level) + (agi / 100);
        }
        if (isMD) return 0.75 * level; // 마법 공격 계수 기준 예시
      }
      return 7 + (0.3 * level) + (dex / 200);
    },
    "getConstant": function(level, stats) {
      return 200;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 16,
    "name": "Hunter Knowledge",
    "nameKo": "사냥군의 지식",
    "prereq": 15,
    "x": 4,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Hunter/16_Hunter Knowledge.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["자동활"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 멀티풀 헌터 계수 증가 패시브
  }
];