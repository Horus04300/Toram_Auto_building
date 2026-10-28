import './skill-effect-engine.js';
import {skillCatalog} from '../data/skill-combat-catalog.js';
import {skillRegistry} from '../data/skill-effect-registry.js';
/* 전투 스킬 데이터의 등록 범위와 상세화 상태를 검증한다. */

  'use strict';
  var kinds = ['attack', 'passive', 'buff', 'utility'];
  function audit() {
    var catalog = skillCatalog;
    if (!catalog || !skillRegistry) throw new Error('스킬 카탈로그와 효과 데이터가 먼저 로드되어야 합니다.');
    var catalogIds = new Set(catalog.skills.map(function (skill) { return skill.id; }));
    var errors = [];
    var detailed = skillRegistry.definitions();
    detailed.forEach(function (skill) {
      if (!catalogIds.has(skill.id)) errors.push('전투 카탈로그에 없는 스킬 정의: ' + skill.id);
      if (kinds.indexOf(skill.kind) === -1) errors.push('알 수 없는 스킬 종류: ' + skill.id);
      if (!skill.source) errors.push('출처 키 누락: ' + skill.id);
      ['attacks','specialAttacks','effects','inactiveEffects','stateTransitions','castTriggers'].forEach(function (key) {
        if (skill[key] !== undefined && !Array.isArray(skill[key])) errors.push(key + ' 배열 형식 오류: ' + skill.id);
      });
      var hasModel = ['requirements','cost','castTime','attacks','specialAttacks','effects','inactiveEffects','stateTransitions','castTriggers','stackModel','stackControl','activeBuff'].some(function (key) { return skill[key] !== undefined; });
      if (!hasModel) errors.push('계산 규칙 누락: ' + skill.id);
    });
    var status = detailed.reduce(function (result, skill) {
      result[skill.dataStatus || 'partial'] = (result[skill.dataStatus || 'partial'] || 0) + 1;
      return result;
    }, { unreviewed: 0, partial: 0, verified: 0 });
    return Object.freeze({
      scoped: catalog.skills.length,
      detailed: detailed.length,
      unreviewed: status.unreviewed || 0,
      partial: status.partial || 0,
      verified: status.verified || 0,
      layered:detailed.length,
      shadowedDefinitions:Object.freeze([]),
      errors: Object.freeze(errors)
    });
  }
  export const skillData = Object.freeze({ audit: audit });
