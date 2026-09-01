/* 계산 조립 경계가 공유하는 결정 정책. UI 표시와 계산 커널은 이 계약만 사용한다. */
(function (root) {
  'use strict';

  function definitions(options) {
    var settings = options || {};
    var base = root.TORAM_SKILL_EFFECT_DATA && root.TORAM_SKILL_EFFECT_DATA.skills || [];
    var registry = root.ToramSkillEffectRegistry;
    var byId = Object.create(null);
    var orderedIds = [];

    base.concat(registry ? registry.all() : []).forEach(function (skill) {
      if (!skill || !skill.id) return;
      var existing = byId[skill.id];
      if (!existing) {
        byId[skill.id] = skill;
        orderedIds.push(skill.id);
        return;
      }
      // 기존 버프 UI의 표시 정책만 명시적으로 유지한다. 계산 정책의 기본값은
      // 기존 효과 엔진과 같이 먼저 등록된 정의를 사용한다.
      if (settings.preferStackControl && skill.stackControl && !existing.stackControl) byId[skill.id] = skill;
    });
    return orderedIds.map(function (id) { return byId[id]; });
  }

  function definition(id, options) {
    return definitions(options).find(function (skill) { return skill.id === id; }) || null;
  }

  function matchesCrystaCondition(context, condition) {
    if (!condition) return true;
    var ctx = context || {};
    if (condition.sub && condition.sub.split('/').indexOf(ctx.subType) === -1) return false;
    if (condition.armor && condition.armor.split('/').indexOf(ctx.armorType) === -1) return false;
    if (condition.main && condition.main.split('/').indexOf(ctx.mainType) === -1) return false;
    return true;
  }

  function applyStat(context, key, value) {
    var registry = root.ToramStatRegistry;
    if (!registry || typeof registry.apply !== 'function') throw new Error('StatRegistry가 준비되지 않았습니다.');
    return registry.apply(context, key, value);
  }

  root.ToramCalculationPolicies = Object.freeze({
    applyStat: applyStat,
    matchesCrystaCondition: matchesCrystaCondition,
    resolveSkillDefinition: definition,
    resolveSkillDefinitions: definitions,
    statRegistry: root.ToramStatRegistry
  });
}(typeof window !== 'undefined' ? window : globalThis));
