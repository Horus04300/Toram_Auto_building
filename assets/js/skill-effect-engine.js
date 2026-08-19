/* 제한된 AST와 전투 상태 전이를 해석하는 스킬 효과 엔진. */
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
    if (node.op === 'subtract') return num(expr(node.left, context)) - num(expr(node.right, context));
    if (node.op === 'multiply') return node.args.reduce(function (sum, item) { return sum * num(expr(item, context)); }, 1);
    if (node.op === 'divide') { var divisor = num(expr(node.right, context)); return divisor ? num(expr(node.left, context)) / divisor : 0; }
    if (node.op === 'min') return Math.min.apply(Math, node.args.map(function (item) { return num(expr(item, context)); }));
    if (node.op === 'max') return Math.max.apply(Math, node.args.map(function (item) { return num(expr(item, context)); }));
    if (node.op === 'clamp') return Math.min(num(expr(node.max, context)), Math.max(num(expr(node.min, context)), num(expr(node.value, context))));
    if (node.op === 'floor') return Math.floor(num(expr(node.value, context)));
    if (node.op === 'ceil') return Math.ceil(num(expr(node.value, context)));
    if (node.op === 'tier') { var selected = node.cases.find(function (item) { return test(item.when, context); }); return selected ? expr(selected.value, context) : 0; }
    if (node.op === 'if') return expr(test(node.when, context) ? node.then : node.else, context);
    throw new Error('지원하지 않는 스킬 식: ' + node.op);
  }
  function test(node, context) {
    if (!node) return true;
    if (node.op === 'all') return node.args.every(function (item) { return test(item, context); });
    if (node.op === 'any') return node.args.some(function (item) { return test(item, context); });
    if (node.op === 'not') return !test(node.value, context);
    if (node.op === 'truthy') return Boolean(expr(node.value, context));
    if (node.op === 'eq') return expr(node.left, context) === expr(node.right, context);
    if (node.op === 'ne') return expr(node.left, context) !== expr(node.right, context);
    if (node.op === 'gt') return expr(node.left, context) > expr(node.right, context);
    if (node.op === 'gte') return expr(node.left, context) >= expr(node.right, context);
    if (node.op === 'lt') return expr(node.left, context) < expr(node.right, context);
    if (node.op === 'lte') return expr(node.left, context) <= expr(node.right, context);
    if (node.op === 'in') return Array.isArray(node.values) && node.values.indexOf(expr(node.value, context)) >= 0;
    throw new Error('지원하지 않는 스킬 조건: ' + node.op);
  }
  function mainWeapon(value) { return ({ '활':'bow', '자동활':'bowgun', '지팡이':'staff', '마도구':'magicDevice' })[value] || value; }
  function investments() { var simulator = window.skillSimulatorState; return simulator && typeof simulator.getInvestments === 'function' ? simulator.getInvestments() : {}; }
  function skillLevel(skill) { var levels = investments(); return num(levels[skill.treeId] && levels[skill.treeId][skill.skillId]); }
  function definitions() {
    var root = window.TORAM_SKILL_EFFECT_DATA && window.TORAM_SKILL_EFFECT_DATA.skills || [];
    var registry = window.ToramSkillEffectRegistry;
    return root.concat(registry ? registry.all() : []);
  }
  function context(base, skill, combat, inputs, runtime) {
    base = base || {}; runtime = runtime || {};
    return {
      skill: { id: skill.id, level: skillLevel(skill) },
      player: { level:num(base.level) },
      baseStats: { STR:num(base.strBase), INT:num(base.intBase), VIT:num(base.vitBase), AGI:num(base.agiBase), DEX:num(base.dexBase), CRT:num(base.crtBase) },
      buildStats: combat || {}, combatStats: combat || {},
      equipment: { mainWeapon:mainWeapon(base.mainType), subWeapon:base.subType || null, armorType:base.armorType || null },
      target: runtime.target || {}, states: runtime.states || {}, combo: runtime.combo || {}, buff: runtime.buff || {},
      attack: { inputs:inputs || {}, flags:{} }
    };
  }
  function find(id) { return definitions().find(function (skill) { return skill.id === id; }); }
  function resolveEffect(effect, state) {
    var result = { type:effect.type, phase:effect.phase || 'combat', key:effect.key, target:effect.target, scope:effect.scope || 'self' };
    if (effect.value !== undefined) result.value = num(expr(effect.value, state));
    if (effect.chance !== undefined) result.chance = num(expr(effect.chance, state));
    if (effect.durationSeconds !== undefined) result.durationSeconds = num(expr(effect.durationSeconds, state));
    if (effect.maxStacks !== undefined) result.maxStacks = num(expr(effect.maxStacks, state));
    if (effect.notes) result.notes = effect.notes;
    return result;
  }
  function resolveTransition(transition, state) {
    if (!test(transition.when, state)) return null;
    return { event:transition.event, operation:transition.operation, stateId:transition.stateId, stacks:num(expr(transition.stacks, state)), maxStacks:num(expr(transition.maxStacks, state)), durationSeconds:num(expr(transition.durationSeconds, state)), effects:(transition.effects || []).filter(function (effect) { return test(effect.when, state); }).map(function (effect) { return resolveEffect(effect, state); }) };
  }
  function resolveCost(cost, state) {
    if (!cost || !test(cost.when, state)) return null;
    return { timing:cost.timing || (cost.mp && cost.mp.timing) || 'cast', mp:num(expr(cost.mp && cost.mp.value, state)), hp:num(expr(cost.hp && cost.hp.value, state)), when:cost.when || null };
  }
  function profile(id, base, combat, inputs, runtime) {
    var skill = find(id); if (!skill) return null;
    var state = context(base, skill, combat, inputs, runtime);
    var available = state.skill.level > 0 && test(skill.requirements && skill.requirements.when, state);
    return {
      skill:skill,
      available:available,
      cost:available ? resolveCost(skill.cost, state) : null,
      stateTransitions:available ? (skill.stateTransitions || []).map(function (item) { return resolveTransition(item, state); }).filter(Boolean) : [],
      effects:available ? (skill.effects || []).filter(function (effect) { return test(effect.when, state); }).map(function (effect) { return resolveEffect(effect, state); }) : [],
      hits:available && skill.kind === 'attack' ? (skill.attacks || []).filter(function (hit) { return test(hit.when, state); }).map(function (hit) {
        state.attack.flags = hit.flags || {};
        return { id:hit.id, count:num(expr(hit.count, state)), multiplier:num(expr(hit.multiplier, state)), constant:num(expr(hit.constant, state)), damageType:hit.damageType, flags:hit.flags || {}, stateTransitions:(hit.stateTransitions || []).map(function (item) { return resolveTransition(item, state); }).filter(Boolean) };
      }) : []
    };
  }
  function passiveStatChanges(base) {
    return definitions().filter(function (skill) { return skill.kind === 'passive' && skillLevel(skill) > 0; }).reduce(function (changes, skill) {
      var state = context(base, skill);
      skill.effects.forEach(function (effect) {
        if (effect.type === 'stat' && (!effect.phase || effect.phase === 'build') && test(effect.when, state)) changes.push({ key:effect.key, value:num(expr(effect.value, state)), source:skill });
      });
      return changes;
    }, []);
  }
  function attackProfile(id, base, combat, inputs, runtime) { var result = profile(id, base, combat, inputs, runtime); return result && result.skill.kind === 'attack' ? result : null; }
  window.ToramSkillEffects = Object.freeze({ expression:expr, condition:test, find:find, passiveStatChanges:passiveStatChanges, attackProfile:attackProfile, profile:profile });
}());