/* 트리별 스킬 효과 정의를 합치는 등록기. */
(function () {
  'use strict';
  var trees = Object.create(null);
  function register(treeId, definitions) {
    if (!treeId || !Array.isArray(definitions)) throw new Error('스킬 효과 등록 형식이 올바르지 않습니다.');
    if (trees[treeId]) throw new Error('이미 등록된 스킬 효과 트리: ' + treeId);
    trees[treeId] = Object.freeze(definitions.slice());
  }
  function all() {
    return Object.freeze(Object.keys(trees).reduce(function (items, treeId) {
      return items.concat(trees[treeId]);
    }, []));
  }
  window.TORAM_SKILL_EFFECT_TREE_DATA = trees;
  window.ToramSkillEffectRegistry = Object.freeze({ register: register, all: all });
}());