const magicBladeSkills = [
  {
    "id": 0,
    "name": "Magic Warrior Mastery",
    "nameKo": "마법전사의 마음가짐",
    "prereq": -1,
    "x": 0,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/00_Magic Warrior Mastery.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 13]
    "conditions": ["서브 마도구"], //[cite: 13]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let matkBonus = (level <= 5) ? (2 * level) : (3 * level - 5); //[cite: 13]
      let cspdpBonus = (level <= 5) ? level : (2 * level - 5); //[cite: 13]
      return {
        "MATK": matkBonus, //[cite: 13]
        "CSPDP": cspdpBonus, //[cite: 13]
        "CSPD": 10 * level //[cite: 13]
      };
    }
  },
  {
    "id": 1,
    "name": "Conversion",
    "nameKo": "컨버젼",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/01_Conversion.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 13]
    "conditions": ["한손검", "양손검", "자동활", "권갑"], //[cite: 13]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      let isKnuckle = (stats && stats.mainWeapon === "권갑"); //[cite: 13]
      let baseWeaponATK = (stats && stats.baseWeaponATK) ? stats.baseWeaponATK : 0;
      let matkGain = baseWeaponATK * ((level * level) / 100); //[cite: 13]
      if (isKnuckle) matkGain /= 2; //[cite: 13]
      return { "MATK": matkGain }; //[cite: 13]
    }
  },
  {
    "id": 2,
    "name": "Resonance",
    "nameKo": "레조난스",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/02_Resonance.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 13]
    "conditions": ["서브 마도구"], //[cite: 13]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 랜덤 버프 부여 특성으로 외부 연산 필요[cite: 13]
  },
  {
    "id": 3,
    "name": "Enchanted Spell",
    "nameKo": "엔천트 스펠",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/03_Enchanted Spell.png",
    "iconAvailable": true,
    "type": "passive", // EX 스킬[cite: 13]
    "conditions": ["서브 마도구"], //[cite: 13]
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
    "name": "Dual Bringer",
    "nameKo": "듀얼 브링거",
    "prereq": 3,
    "x": 4,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/04_Dual Bringer.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 13]
    "conditions": ["서브 마도구"], //[cite: 13]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // ATK와 MATK 조정 특수 매커니즘은 외부 연산 필요[cite: 13]
  },
  {
    "id": 5,
    "name": "Ether Flare",
    "nameKo": "에텔 플레아",
    "prereq": -1,
    "x": 0,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/05_Ether Flare.png",
    "iconAvailable": true,
    "type": "active", //[cite: 13]
    "conditions": ["서브 마도구"], //[cite: 13]
    "damagetype": "magic", //[cite: 13]
    "distancePower": true, //[cite: 13]
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let intStat = (stats && stats.baseINT) ? stats.baseINT : 0; //[cite: 13]
      return 2.5 + (intStat / 100); //[cite: 13]
    },
    "getConstant": function(level, stats) {
      return 50 + (5 * level); //[cite: 13]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Element Slash",
    "nameKo": "엘레멘트 슬래쉬",
    "prereq": 5,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/06_Element Slash.png",
    "iconAvailable": true,
    "type": "active", //[cite: 13]
    "conditions": ["서브 마도구"], //[cite: 13]
    "damagetype": "magic", //[cite: 13]
    "distancePower": true, //[cite: 13]
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let intStat = (stats && stats.baseINT) ? stats.baseINT : 0; //[cite: 13]
      let strStat = (stats && stats.baseSTR) ? stats.baseSTR : 0; //[cite: 13]
      let maxStat = Math.max(intStat, strStat); //[cite: 13]
      return 1 + (0.5 * level) + (0.08 * level * (maxStat / 100)); //[cite: 13]
    },
    "getConstant": function(level, stats) {
      return 50 + (15 * level); //[cite: 13]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 7,
    "name": "Enchant Sword",
    "nameKo": "엔천트 소드",
    "prereq": 6,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/07_Enchant Sword.png",
    "iconAvailable": true,
    "type": "active", //[cite: 13]
    "conditions": ["한손검", "양손검", "자동활", "권갑"], //[cite: 13]
    "damagetype": "physical", //[cite: 13]
    "distancePower": true, //[cite: 13]
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      let is2h = (stats && stats.mainWeapon === "양손검"); //[cite: 13]
      let intStat = (stats && stats.baseINT) ? stats.baseINT : 0; //[cite: 13]
      let strStat = (stats && stats.baseSTR) ? stats.baseSTR : 0; //[cite: 13]
      let maxStat = Math.max(intStat, strStat); //[cite: 13]
      return 4 + (0.6 * level) + (maxStat / 100) + (is2h ? 2 : 0); //[cite: 13]
    },
    "getConstant": function(level, stats) {
      return 300; // 서브 마도구 보너스 상수 연산은 외부 적용 필요[cite: 13]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 8,
    "name": "Enchanted Burst",
    "nameKo": "엔천트 버스트",
    "prereq": 7,
    "x": 3,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/08_Enchanted Burst.png",
    "iconAvailable": true,
    "type": "active", //[cite: 13]
    "conditions": ["양손검", "서브 마도구"], //[cite: 13]
    "damagetype": "magic", //[cite: 13]
    "distancePower": true, //[cite: 13]
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 13.75 + (3 * level); // 3스택 최대 소모 기준 가정[cite: 13]
    },
    "getConstant": function(level, stats) {
      return 100; // 서브 마도구 ATK 비례 추가 상수 연산 필요[cite: 13]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 9,
    "name": "Union Sword",
    "nameKo": "유니온 소드",
    "prereq": 8,
    "x": 4,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/09_Union Sword.png",
    "iconAvailable": true,
    "type": "active", //[cite: 13]
    "conditions": ["양손검", "서브 마도구"], //[cite: 13]
    "damagetype": "physical", //[cite: 13]
    "distancePower": true, //[cite: 13]
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) {
      return 10 + (0.5 * level); // 1타 기준 (리유니온은 20 + level)[cite: 13]
    },
    "getConstant": function(level, stats) {
      return 500; //[cite: 13]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 10,
    "name": "Siphon Barrier",
    "nameKo": "드레인 배리어",
    "prereq": -1,
    "x": 0,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/10_Siphon Barrier.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 13]
    "conditions": ["마도구"], //[cite: 13]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      return { 
        "P_RES": 9 * level, //[cite: 13]
        "M_RES": 9 * level //[cite: 13]
      };
    }
  },
  {
    "id": 11,
    "name": "Teleport",
    "nameKo": "텔레포트",
    "prereq": 10,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/11_Teleport.png",
    "iconAvailable": true,
    "type": "active", //[cite: 13]
    "conditions": ["마도구"], //[cite: 13]
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
    "name": "Siphon Recall",
    "nameKo": "드레인 리콜",
    "prereq": 11,
    "x": 2,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/12_Siphon Recall.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 13]
    "conditions": ["서브 마도구"], //[cite: 13]
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
    "name": "Float Dash",
    "nameKo": "플로트 대시",
    "prereq": 12,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/13_Float Dash.png",
    "iconAvailable": true,
    "type": "buff", //[cite: 13]
    "conditions": ["서브 마도구"], //[cite: 13]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 이속 증가 등
  },
  {
    "id": 14,
    "name": "Magic Skin",
    "nameKo": "매직 스킨",
    "prereq": 13,
    "x": 4,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/MagicBlade/14_Magic Skin.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 13]
    "conditions": ["서브 마도구"], //[cite: 13]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 피해 감소 매커니즘 외부 연산
  }
];