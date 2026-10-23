/* 모든 전투 스킬의 등록 골격. 수식은 트리별 원문 검증 모듈이 덮어쓴다. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  var metadata = window.TORAM_SKILL_REGISTRATION_METADATA;
  if (!registry || !catalog || !metadata) throw new Error('전체 스킬 등록은 카탈로그·등록기·메타데이터 뒤에 로드되어야 합니다.');
  var known = new Set((window.TORAM_SKILL_EFFECT_DATA.skills || []).concat(registry.all()).map(function (skill) { return skill.id; }));
  function kindOf(meta) {
    if (meta.type === 'passive') return 'passive';
    if (meta.type === 'buff') return 'buff';
    return meta.damageType === 'none' ? 'utility' : 'attack';
  }
  var definitions = catalog.skills.filter(function (skill) { return !known.has(skill.id); }).map(function (skill) {
    var meta = metadata[skill.id];
    if (!meta) throw new Error('견본 메타데이터가 없는 스킬: ' + skill.id);
    var kind = kindOf(meta);
    var definition = {
      id: skill.id, treeId: skill.treeId, skillId: skill.skillId, nameKo: skill.nameKo,
      kind: kind, source: skill.treeId.toLowerCase(), sourceUrl: skill.sourceUrl,
      dataStatus: 'unreviewed', sampleType: meta.type, sampleDamageType: meta.damageType
    };
    if (kind === 'attack') definition.attacks = [];
    if (kind === 'passive' || kind === 'buff') definition.effects = [];
    return definition;
  });
  registry.register('catalog-registration', definitions);
}());