const daggerSkills = [
  {
    "id": 0,
    "name": "Throwing Knife",
    "nameKo": "스로잉",
    "prereq": -1,
    "x": 0,
    "y": 1,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/00_Throwing Knife.png",
    "iconAvailable": true,
    "type": "active", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "physical", //[cite: 16]
    "distancePower": true, //[cite: 16]
    "longRange": false, //[cite: 16]
    "unsheathePower": false, //[cite: 16]
    "getMultiplier": function(level, stats) {
      return 0.1 + (0.04 * level); //[cite: 16]
    },
    "getConstant": function(level, stats) {
      return 0; // 단검 공격력 고정 데미지 추가는 별도 연산[cite: 16]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 1,
    "name": "Spike Dart",
    "nameKo": "스파이크 다트",
    "prereq": 0,
    "x": 1,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/01_Spike Dart.png",
    "iconAvailable": true,
    "type": "active", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "physical", //[cite: 16]
    "distancePower": true, //[cite: 16]
    "longRange": false, //[cite: 16]
    "unsheathePower": false, //[cite: 16]
    "getMultiplier": function(level, stats) {
      let hitCount = 1 + Math.floor(level / 2); //[cite: 16]
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0; //[cite: 16]
      return ((0.75 + 0.075 * level) / hitCount) + (dex / (2000 - 100 * level)); // 각 히트당 계수[cite: 16]
    },
    "getConstant": function(level, stats) {
      // 단검 공격력/5 는 스탯 반영 함수 내에서 직접 계산 필요
      return 10 + level; //[cite: 16]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 2,
    "name": "Gatling Knife",
    "nameKo": "개틀링 나이프",
    "prereq": 1,
    "x": 2,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/02_Gatling Knife.png",
    "iconAvailable": true,
    "type": "active", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "physical", //[cite: 16]
    "distancePower": true, //[cite: 16]
    "longRange": false, //[cite: 16]
    "unsheathePower": false, //[cite: 16]
    "getMultiplier": function(level, stats) {
      let agi = (stats && stats.baseAGI) ? stats.baseAGI : 0; //[cite: 16]
      let dex = (stats && stats.baseDEX) ? stats.baseDEX : 0; //[cite: 16]
      let str = (stats && stats.baseSTR) ? stats.baseSTR : 0; //[cite: 16]
      let statBonus = (agi + dex + str) / 3000; //[cite: 16]
      let baseMap = [0, 0.4, 0.4, 0.5, 0.6, 0.7, 0.7, 0.8, 0.9, 1, 1]; //[cite: 16]
      return baseMap[level] + statBonus; // 각 히트당 계수[cite: 16]
    },
    "getConstant": function(level, stats) {
      return 20 + (2 * level); // 단검 공격력 추가는 별도 연산[cite: 16]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 3,
    "name": "Amazing Throw",
    "nameKo": "경이의 투척술",
    "prereq": 2,
    "x": 3,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/03_Amazing Throw.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 확률 발동 메커니즘[cite: 16]
  },
  {
    "id": 4,
    "name": "Mad Dagger",
    "nameKo": "크레이지 대거",
    "prereq": 3,
    "x": 4,
    "y": 0,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/04_Mad Dagger.png",
    "iconAvailable": true,
    "type": "active", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "physical", //[cite: 16]
    "distancePower": true, //[cite: 16]
    "longRange": true, //[cite: 16]
    "unsheathePower": false, //[cite: 16]
    "getMultiplier": function(level, stats) {
      let isBonusWeapon = (stats && ["한손검", "권갑", "맨손"].includes(stats.mainWeapon)); //[cite: 16]
      let weaponAtkMulti = 0.5; // (장비 단검 ATK/10)/100 (소수점 버림) 최소 0.5, 장비 연산 필요[cite: 16]
      return 0.5 + (0.15 * level) + weaponAtkMulti + (isBonusWeapon ? 0.5 : 0); // 시전 공격[cite: 16]
    },
    "getConstant": function(level, stats) {
      return 200; //[cite: 16]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 5,
    "name": "Poison Dagger",
    "nameKo": "포이즌대거",
    "prereq": 0,
    "x": 1,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/05_Poison Dagger.png",
    "iconAvailable": true,
    "type": "active", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "physical", //[cite: 16]
    "distancePower": true, //[cite: 16]
    "longRange": false, //[cite: 16]
    "unsheathePower": false, //[cite: 16]
    "getMultiplier": function(level, stats) {
      let intStat = (stats && stats.baseINT) ? stats.baseINT : 0; //[cite: 16]
      return 0.5 + (0.025 * level) + (intStat / (1100 - 100 * level)); //[cite: 16]
    },
    "getConstant": function(level, stats) {
      let pLevel = (stats && stats.level) ? stats.level : 0; //[cite: 16]
      let totalAGI = (stats && stats.totalAGI) ? stats.totalAGI : 0; //[cite: 16]
      let totalDEX = (stats && stats.totalDEX) ? stats.totalDEX : 0; //[cite: 16]
      return 100 + (10 * level) + pLevel + (totalAGI * 2) + (totalDEX / 2); //[cite: 16]
    },
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 6,
    "name": "Double Stab",
    "nameKo": "더블 스로",
    "prereq": 5,
    "x": 2,
    "y": 2,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/06_Double Stab.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 어보이드 시 데미지 2배는 외부 연산[cite: 16]
  },
  {
    "id": 7,
    "name": "Hidden Arm",
    "nameKo": "세컨드 암",
    "prereq": -1,
    "x": 0,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/07_Hidden Arm.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "physical", //[cite: 16]
    "distancePower": false, //[cite: 16]
    "longRange": false, //[cite: 16]
    "unsheathePower": false, //[cite: 16]
    "getMultiplier": function(level, stats) {
      let intenseKnifeLevel = (stats && stats.skill_IntensiveKnife) ? stats.skill_IntensiveKnife : 0; //[cite: 16]
      let bonus = (intenseKnifeLevel > 0) ? 0.25 : 0; //[cite: 16]
      return 0.25 + bonus; //[cite: 16]
    },
    "getConstant": function(level, stats) { return 0; }, // 단검 공격력 추가는 별도 연산[cite: 16]
    "getEffects": function(level, stats) { return {}; }
  },
  {
    "id": 8,
    "name": "Intensive Knife",
    "nameKo": "인텐스 나이프",
    "prereq": 7,
    "x": 1,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/08_Intensive Knife.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 세컨드 암 계수 증가는 세컨드 암에서 적용[cite: 16]
  },
  {
    "id": 9,
    "name": "Mail Breaker",
    "nameKo": "메일 브레이커",
    "prereq": 8,
    "x": 3,
    "y": 4,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/09_Mail Breaker.png",
    "iconAvailable": true,
    "type": "passive", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "none",
    "distancePower": false,
    "longRange": false,
    "unsheathePower": false,
    "getMultiplier": function(level, stats) { return 0; },
    "getConstant": function(level, stats) { return 0; },
    "getEffects": function(level, stats) { return {}; } // 세컨드 암 관통 증가 및 공마회/크리율 조건부 획득은 외부 연산[cite: 16]
  },
  {
    "id": 10,
    "name": "Knife Combat",
    "nameKo": "나이프 컴뱃",
    "prereq": 8,
    "x": 2,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/10_Knife Combat.png",
    "iconAvailable": true,
    "type": "active", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "physical", //[cite: 16]
    "distancePower": true, //[cite: 16]
    "longRange": false, //[cite: 16]
    "unsheathePower": false, //[cite: 16]
    "getMultiplier": function(level, stats) {
      return 1; // 시작 공격 기준[cite: 16]
    },
    "getConstant": function(level, stats) {
      return 0; //[cite: 16]
    },
    "getEffects": function(level, stats) {
      if (level === 0) return {};
      // 통상 공격 모션 변화 버프이므로, 평타 계수 등에 영향을 줌 (ATK 상승 등은 별도 연산)[cite: 16]
      return { 
        "CRIT": 25 + (5 * level), //[cite: 16]
        "AMPR": 10 * level //[cite: 16]
      };
    }
  },
  {
    "id": 11,
    "name": "Flincher Knife",
    "nameKo": "플린치 나이프",
    "prereq": 10,
    "x": 3,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/11_Flincher Knife.png",
    "iconAvailable": true,
    "type": "active", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "physical", //[cite: 16]
    "distancePower": true, //[cite: 16]
    "longRange": false, //[cite: 16]
    "unsheathePower": false, //[cite: 16]
    "getMultiplier": function(level, stats) {
      let isAggroTarget = true; // 어그로 대상 여부에 따라 2배 분기
      let multi = 2 + (0.2 * level); // 단검 공격력/200 은 외부에서 합산 필요[cite: 16]
      return isAggroTarget ? multi : multi * 2; //[cite: 16]
    },
    "getConstant": function(level, stats) {
      return 30 * level; //[cite: 16]
    },
    "getEffects": function(level, stats) { return {}; } // 어그로 대상이 아닐 시 파이팅 나이프 발동 및 물리관통 보너스 추가[cite: 16]
  },
  {
    "id": 12,
    "name": "Rolling Bite",
    "nameKo": "휠 바이트",
    "prereq": 11,
    "x": 4,
    "y": 6,
    "via": null,
    "icon": "coryn_skill_icons/Buff Skills/Dagger/12_Rolling Bite.png",
    "iconAvailable": true,
    "type": "active", //[cite: 16]
    "conditions": ["단검"], //[cite: 16]
    "damagetype": "physical", //[cite: 16]
    "distancePower": true, //[cite: 16]
    "longRange": true, //[cite: 16]
    "unsheathePower": false, //[cite: 16]
    "getMultiplier": function(level, stats) {
      return 7.5 + (0.25 * level); //[cite: 16]
    },
    "getConstant": function(level, stats) {
      return 400; //[cite: 16]
    },
    "getEffects": function(level, stats) { return {}; } // 뎀감 성공 시 2초 무적 및 후속 공격 계수 증가는 별도 연산[cite: 16]
  }
];