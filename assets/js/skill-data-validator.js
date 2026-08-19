/* 전투 스킬 데이터의 등록 범위와 상세화 상태를 검증한다. */
(function () {
  'use strict';
  var kinds = ['attack', 'passive', 'buff', 'utility'];
  function audit() {
    var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
    var data = window.TORAM_SKILL_EFFECT_DATA;
    if (!catalog || !data) throw new Error('스킬 카탈로그와 효과 데이터가 먼저 로드되어야 합니다.');
    var catalogIds = new Set(catalog.skills.map(function (skill) { return skill.id; }));
    var seen = new Set();
    var errors = [];
    var registry = window.ToramSkillEffectRegistry;
    var detailed = (data.skills || []).concat(registry ? registry.all() : []);
    detailed.forEach(function (skill) {
      if (seen.has(skill.id)) errors.push('중복 스킬 정의: ' + skill.id);
      seen.add(skill.id);
      if (!catalogIds.has(skill.id)) errors.push('전투 카탈로그에 없는 스킬 정의: ' + skill.id);
      if (kinds.indexOf(skill.kind) === -1) errors.push('알 수 없는 스킬 종류: ' + skill.id);
      if (!skill.source) errors.push('출처 키 누락: ' + skill.id);
      if (skill.kind === 'attack' && !Array.isArray(skill.attacks)) errors.push('공격 목록 누락: ' + skill.id);
      if ((skill.kind === 'passive' || skill.kind === 'buff') && !Array.isArray(skill.effects)) errors.push('효과 목록 누락: ' + skill.id);
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
      errors: Object.freeze(errors)
    });
  }
  window.ToramSkillData = Object.freeze({ audit: audit });
}());