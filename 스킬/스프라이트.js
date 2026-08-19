const spriteSkills = [
  {
    "id": 0,
    "name": "Auto-Device",
    "nameKo": "오토 디바이스",
    "prereq": -1,
    "x": 0,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/00_Auto-Device.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["메인 마도구"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 1;
    },
    "getConstant": function(level, stats) {
      return 0;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 1,
    "name": "Express Aid",
    "nameKo": "러쉬 에이드",
    "prereq": 0,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/01_Express Aid.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 이속 증가 및 뎀감 횟수는 특수 매커니즘으로 외부 연산 필요
  },
  {
    "id": 2,
    "name": "Micro Heal",
    "nameKo": "클라인 힐",
    "prereq": 1,
    "x": 2,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/02_Micro Heal.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; }, // 회복량(50 + MATK * 0.05) * level 은 외부 연산
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Resurrection",
    "nameKo": "리저렉션",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/03_Resurrection.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 4,
    "name": "Enhance",
    "nameKo": "인핸스",
    "prereq": 1,
    "x": 2,
    "y": 3,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/04_Enhance.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 파티원 타겟팅 버프이므로 외부 연산
  },
  {
    "id": 5,
    "name": "Stabiliz",
    "nameKo": "스타빌리스",
    "prereq": 4,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/05_Stabiliz.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let crt = (stats && stats.totalCRT) ? stats.totalCRT : 0; // 개성 스탯 CRT
      return { 
        "CRIT": 5 + (2 * level) + (crt / 8.5),
        "M_Stability": level // 마법 안정률 증가
      };
    }
  },
  {
    "id": 6,
    "name": "Sprite Upgrade",
    "nameKo": "스프라이트 강화",
    "prereq": 5,
    "x": 4,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/06_Sprite Upgrade.png",
    "iconAvailable": true,
    "type": "passive",
    "conditions": ["메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 버프 지속시간 증가 패시브
  },
  {
    "id": 7,
    "name": "Sprite Shield",
    "nameKo": "스프라이트 실드",
    "prereq": 4,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/07_Sprite Shield.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["메인 마도구"],
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "AilmentResistance": level * level }; // 1회 피격시 이상 내성 증가
    }
  },
  {
    "id": 8,
    "name": "Counterforce",
    "nameKo": "카운터포스",
    "prereq": 0,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/08_Counterforce.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["메인 마도구"],
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let intStat = (stats && stats.totalINT) ? stats.totalINT : 0;
      return (0.3 * level) + (intStat / 1000); // 1타 기준
    },
    "getConstant": function(level, stats) {
      return 75;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Astral Lance",
    "nameKo": "아스트랄 랜스",
    "prereq": 8,
    "x": 2,
    "y": 5,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/09_Astral Lance.png",
    "iconAvailable": true,
    "type": "buff",
    "conditions": ["메인 마도구"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 2.5 + (0.5 * level);
    },
    "getConstant": function(level, stats) {
      return 500;
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "MagicPierce": (level * level) / 2 };
    }
  },
  {
    "id": 10,
    "name": "Magic Vulcan",
    "nameKo": "매직 불칸",
    "prereq": 9,
    "x": 3,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/10_Magic Vulcan.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 마도구"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 0.5 + (0.05 * level); // 첫 5타 중 1타 기준
    },
    "getConstant": function(level, stats) {
      return 0; // 첫 5타 상수 0
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 11,
    "name": "Cursed Altar",
    "nameKo": "카타라보모스",
    "prereq": 10,
    "x": 4,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/11_Cursed Altar.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 마도구"],
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; }, // 도트 데미지 메커니즘
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 12,
    "name": "Ignition",
    "nameKo": "이그니션",
    "prereq": -1,
    "x": 0,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/12_Ignition.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 마도구"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      // (0.6 * 스킬레벨) + 최종 무기 ATK/100 이며 최대 12이므로 기본 계수만 반영
      return 0.6 * level; 
    },
    "getConstant": function(level, stats) {
      return 100;
    },
    "getEffects": function(level, stats) { return {}; } // 안정률 저하 및 마법 안정률 치환은 특수 연산
  },
  {
    "id": 13,
    "name": "Terrawrym",
    "nameKo": "알데드락",
    "prereq": 12,
    "x": 1,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/13_Terrawrym.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 마도구"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let intStat = (stats && stats.baseINT) ? stats.baseINT : 0;
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0;
      return 3.5 + (0.35 * level) + (intStat / 200) + (dex / 200);
    },
    "getConstant": function(level, stats) {
      return 300;
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 14,
    "name": "Faux Weapon",
    "nameKo": "팍티스악름",
    "prereq": 13,
    "x": 2,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/14_Faux Weapon.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 마도구"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": true,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let dex = (stats && stats.totalDEX) ? stats.totalDEX : 0;
      let agi = (stats && stats.totalAGI) ? stats.totalAGI : 0;
      return 7.5 + (dex / 100) + (agi / 100); // 팍티스알름의 기본 계수
    },
    "getConstant": function(level, stats) {
      return 6 * level * level; // 기본 상수
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 15,
    "name": "Slash Reaper",
    "nameKo": "슬래시 리퍼",
    "prereq": 14,
    "x": 3,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/15_Slash Reaper.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 마도구"],
    "damagetype": "magic",
    "distancePower": true,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let intStat = (stats && stats.baseINT) ? stats.baseINT : 0;
      return 2 + (intStat / 500); // 마법검 공격 계수 기준
    },
    "getConstant": function(level, stats) {
      return 100; // 마법검 공격 상수
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 16,
    "name": "Lebenglanz",
    "nameKo": "레벤그란츠",
    "prereq": 15,
    "x": 4,
    "y": 8,
    "via": null,
    "icon": "coryn_skill_icons/Weapon Skills/Sprite/16_Lebenglanz.png",
    "iconAvailable": true,
    "type": "active",
    "conditions": ["메인 마도구"],
    "damagetype": "magic",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 10 + level; // 생명 폭파 계수
    },
    "getConstant": function(level, stats) {
      return 400; // 생명 폭파 상수
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { "AMPR": level }; // 공격 마나 회복 버프
    }
  }
];