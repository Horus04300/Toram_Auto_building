/* 트리별 스킬 효과 정의를 합치는 등록기. */
(function () {
  'use strict';
  var trees = Object.create(null);
  // Definition precedence is independent of physical file layout.
  var definitionOrder = ["Battle","Survival","Guard","Support","DarkPower","Dancer","Necromancer:calculation-rules","Golem:calculation-rules","Minstrel","Blade","DualSword-core","DualSword:calculation-rules","Halberd-stack-buff","Halberd-source-coverage","Crusher-core","Crusher:calculation-rules","Mononofu-passives","Mononofu:calculation-rules","Knight-stack-buff","Knight:calculation-rules","Martial-stack-buff","Shot-source-coverage","Shot-stack-buff","Magic-source-coverage","Sprite-stack-buff","Sprite:calculation-rules","Assassin-stack-buff","Assassin:calculation-rules","Dagger:calculation-rules","Shield:calculation-rules","Priest:calculation-rules","Hunter:calculation-rules","Wizard:calculation-rules","Guard:calculation-rules","DarkPower:calculation-rules","MagicBlade:calculation-rules","Barehand:calculation-rules","Ninja:calculation-rules","Partisan:calculation-rules","catalog-registration"];
  function register(treeId, definitions) {
    if (!treeId || !Array.isArray(definitions)) throw new Error('스킬 효과 등록 형식이 올바르지 않습니다.');
    if (trees[treeId]) throw new Error('이미 등록된 스킬 효과 트리: ' + treeId);
    trees[treeId] = Object.freeze(definitions.slice());
  }
  function all() {
    return Object.freeze(Object.keys(trees).sort(function (a, b) {
      var ai = definitionOrder.indexOf(a), bi = definitionOrder.indexOf(b);
      return (ai < 0 ? definitionOrder.length : ai) - (bi < 0 ? definitionOrder.length : bi);
    }).reduce(function (items, treeId) {
      return items.concat(trees[treeId]);
    }, []));
  }
  window.TORAM_SKILL_EFFECT_TREE_DATA = trees;
  window.ToramSkillEffectRegistry = Object.freeze({ register: register, all: all });
}());