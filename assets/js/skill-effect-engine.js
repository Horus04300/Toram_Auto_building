/* 제한된 AST만 해석하는 스킬 효과 엔진. */
(function () {
  'use strict';
  function read(object, path) { return String(path).split('.').reduce(function (value, key) { return value == null ? undefined : value[key]; }, object); }
  function num(value) { value = Number(value); return Number.isFinite(value) ? value : 0; }
  function expr(node, context) {
    if (typeof node === 'number') return node;
    if (!node || typeof node !== 'object') return 0;
    if (node.op === 'value') return node.value;
    if (node.op === 'ref') return read(context, node.path);
    if (node.op === 'add') return node.args.reduce(function (sum, item) { return sum + num(expr(item, context)); }, 0);
    if (node.op === 'multiply') return node.args.reduce(function (sum, item) { return sum * num(expr(item, context)); }, 1);
    if (node.op === 'divide') { var divisor = num(expr(node.right, context)); return divisor ? num(expr(node.left, context)) / divisor : 0; }
    if (node.op === 'max') return Math.max.apply(Math, node.args.map(function (item) { return num(expr(item, context)); }));
    if (node.op === 'tier') { var selected = node.cases.find(function (item) { return test(item.when, context); }); return selected ? expr(selected.value, context) : 0; }
    if (node.op === 'if') return expr(test(node.when, context) ? node.then : node.else, context);
    throw new Error('지원하지 않는 스킬 식: ' + node.op);
  }
  function test(node, context) {
    if (!node) return true;
    if (node.op === 'all') return node.args.every(function (item) { return test(item, context); });
    if (node.op === 'truthy') return Boolean(expr(node.value, context));
    if (node.op === 'eq') return expr(node.left, context) === expr(node.right, context);
    if (node.op === 'gte') return expr(node.left, context) >= expr(node.right, context);
    if (node.op === 'lte') return expr(node.left, context) <= expr(node.right, context);
    if (node.op === 'in') return Array.isArray(node.values) && node.values.indexOf(expr(node.value, context)) >= 0;
    throw new Error('지원하지 않는 스킬 조건: ' + node.op);
  }
  function mainWeapon(value) { return ({ '활':'bow', '자동활':'bowgun', '지팡이':'staff', '마도구':'magicDevice' })[value] || value; }
  function investments() {
    var simulator = window.skillSimulatorState;
    return simulator && typeof simulator.getInvestments === 'function' ? simulator.getInvestments() : {};
  }
  function skillLevel(skill) { var levels = investments(); return num(levels[skill.treeId] && levels[skill.treeId][skill.skillId]); }
  function context(base, skill, combat, inputs) {
    base = base || {};
    return {
      skill: { id: skill.id, level: skillLevel(skill) },
      baseStats: { STR:num(base.strBase), INT:num(base.intBase), VIT:num(base.vitBase), AGI:num(base.agiBase), DEX:num(base.dexBase), CRT:num(base.crtBase) },
      buildStats: combat || {}, combatStats: combat || {},
      equipment: { mainWeapon:mainWeapon(base.mainType) },
      attack: { inputs:inputs || {}, flags:{} }
    };
  }
  function find(id) { return window.TORAM_SKILL_EFFECT_DATA.skills.find(function (skill) { return skill.id === id; }); }
  function passiveStatChanges(base) {
    return window.TORAM_SKILL_EFFECT_DATA.skills.filter(function (skill) { return skill.kind === 'passive' && skillLevel(skill) > 0; }).reduce(function (changes, skill) {
      var state = context(base, skill);
      skill.effects.forEach(function (effect) {
        if (effect.type === 'stat' && test(effect.when, state)) changes.push({ key:effect.key, value:num(expr(effect.value, state)), source:skill });
      });
      return changes;
    }, []);
  }
  function attackProfile(id, base, combat, inputs) {
    var skill = find(id); if (!skill || skill.kind !== 'attack') return null;
    var state = context(base, skill, combat, inputs);
    return {
      skill:skill, available:state.skill.level > 0,
      hits:state.skill.level ? skill.attacks.filter(function (hit) { return test(hit.when, state); }).map(function (hit) {
        state.attack.flags = hit.flags || {};
        return { id:hit.id, count:num(expr(hit.count, state)), multiplier:num(expr(hit.multiplier, state)), constant:num(expr(hit.constant, state)), damageType:hit.damageType, flags:hit.flags || {} };
      }) : []
    };
  }
  window.ToramSkillEffects = Object.freeze({ expression:expr, condition:test, find:find, passiveStatChanges:passiveStatChanges, attackProfile:attackProfile });
}());
