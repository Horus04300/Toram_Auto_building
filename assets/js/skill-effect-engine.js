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
  function investmentSummary(levels, predicate) {
    return Object.keys(levels).reduce(function (totals, treeId) {
      totals[treeId] = Object.keys(levels[treeId] || {}).reduce(function (sum, skillId) {
        var level = num(levels[treeId][skillId]);
        return sum + (predicate(level) ? level : 0);
      }, 0);
      return totals;
    }, {});
  }
  function skillLevel(skill) { var levels = investments(); return num(levels[skill.treeId] && levels[skill.treeId][skill.skillId]); }
  function normalizedActiveBuffs(runtime) {
    var selections = runtime && runtime.activeBuffs || {};
    return Object.keys(selections).reduce(function (result, skillId) {
      var setting = selections[skillId];
      result[skillId.replace(/[^A-Za-z0-9_$]/g, '_')] = setting === true ? { active:true, stacks:0 } : { active:Boolean(setting && setting.active), stacks:Math.max(0, Math.floor(num(setting && setting.stacks))) };
      return result;
    }, {});
  }
  function definitions() {
    var root = window.TORAM_SKILL_EFFECT_DATA && window.TORAM_SKILL_EFFECT_DATA.skills || [];
    var registry = window.ToramSkillEffectRegistry;
    return root.concat(registry ? registry.all() : []);
  }
  function context(base, skill, combat, inputs, runtime) {
    base = base || {}; runtime = runtime || {};
    var levels = investments();
    return {
      skill: { id: skill.id, level: skillLevel(skill) },
      investments: levels,
      investmentTotals: investmentSummary(levels, function () { return true; }),
      learnedSkillCounts: investmentSummary(levels, function (level) { return level > 0; }),
      player: { level:num(base.level) },
      baseStats: { STR:num(base.strBase), INT:num(base.intBase), VIT:num(base.vitBase), AGI:num(base.agiBase), DEX:num(base.dexBase), CRT:num(base.crtBase), TEC:num(base.tecBase) },
      buildStats: combat || {}, combatStats: combat || {},
      combat: combat || {},
      equipment: { mainWeapon:mainWeapon(base.mainType), subWeapon:base.subType || null, armorType:base.armorType || null, subWeaponRefinement:num(base.subRefine), subWeaponAttack:num(base.subAtk) },
      character: { level:num(base.level) },
      resources: { maxMp:num(runtime.maxMp), currentMp:num(runtime.currentMp) },
      activeBuffs: normalizedActiveBuffs(runtime),
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
    return { event:transition.event, operation:transition.operation, stateId:transition.stateId, targetSkillIds:transition.targetSkillIds || null, requiresActualMpCost:Boolean(transition.requiresActualMpCost), stacks:num(expr(transition.stacks, state)), maxStacks:num(expr(transition.maxStacks, state)), durationSeconds:num(expr(transition.durationSeconds, state)), effects:(transition.effects || []).filter(function (effect) { return test(effect.when, state); }).map(function (effect) { return resolveEffect(effect, state); }) };
  }
  function resolveCost(cost, state) {
    if (!cost || !test(cost.when, state)) return null;
    return { timing:cost.timing || (cost.mp && cost.mp.timing) || 'cast', mp:num(expr(cost.mp && cost.mp.value, state)), hp:num(expr(cost.hp && cost.hp.value, state)), when:cost.when || null };
  }
  function resolveCastTime(castTime, state) {
    if (!castTime) return null;
    var seconds = castTime.seconds === undefined ? 0 : num(expr(castTime.seconds, state));
    if (castTime.weaponModifier !== undefined) seconds *= num(expr(castTime.weaponModifier, state));
    return { type:castTime.type || 'fixed', seconds:Math.max(0, seconds), affectedByCastSpeed:castTime.affectedByCastSpeed !== false };
  }
  function triggeredPassiveEffects(sourceSkill, base, combat, inputs, runtime) {
    return definitions().filter(function (candidate) {
      return candidate.kind === 'passive' && skillLevel(candidate) > 0 && Array.isArray(candidate.castTriggers);
    }).reduce(function (result, candidate) {
      var state = context(base, candidate, combat, inputs, runtime);
      if (!test(candidate.requirements && candidate.requirements.when, state)) return result;
      candidate.castTriggers.forEach(function (trigger) {
        if (trigger.skillId !== sourceSkill.id || !test(trigger.when, state)) return;
        (trigger.effects || []).forEach(function (effect) {
          if (test(effect.when, state)) result.push(Object.assign({ source:candidate.nameKo }, resolveEffect(effect, state)));
        });
      });
      return result;
    }, []);
  }  function normalizeInputs(skill, state) {
    (skill.inputs || []).forEach(function (input) {
      var current = state.attack.inputs[input.id];
      if (current === undefined) current = input.default !== undefined ? expr(input.default, state) : (input.type === 'boolean' ? false : 0);
      if (input.type === 'boolean') { state.attack.inputs[input.id] = Boolean(current); return; }
      var value = num(current);
      var min = input.min === undefined ? -Infinity : num(expr(input.min, state));
      var max = input.max === undefined ? Infinity : num(expr(input.max, state));
      state.attack.inputs[input.id] = Math.min(max, Math.max(min, value));
    });
  }
  function matchesDamageTarget(target, skill) {
    if (!target || target === 'attack') return true;
    if (target.indexOf('skillCategory:') === 0) return target.slice('skillCategory:'.length) === skill.treeId;
    if (target.indexOf('skillTrees:') === 0) return target.slice('skillTrees:'.length).split(',').indexOf(skill.treeId) >= 0;
    if (target === 'otherSkillTrees') return skill.treeId !== 'Martial' && skill.treeId !== 'Crusher' && skill.treeId !== 'Assassin' && skill.treeId !== 'DarkPower';
    return false;
  }
  function passiveDamageModifiers(skill, base, combat, inputs, runtime, flags) {
    return definitions().filter(function (candidate) { return candidate.kind === 'passive' && skillLevel(candidate) > 0; }).reduce(function (result, candidate) {
      var candidateState = context(base, candidate, combat, inputs, runtime);
      candidateState.attack.flags = flags || {};
      if (!test(candidate.requirements && candidate.requirements.when, candidateState)) return result;
      (candidate.effects || []).forEach(function (effect) {
        if (effect.type !== 'damageMultiplier' || !test(effect.when, candidateState) || !matchesDamageTarget(effect.target, skill)) return;
        var value = num(expr(effect.value, candidateState)); result.multiplier *= value; result.sources.push({ source:candidate.nameKo, value:value });
      });
      return result;
    }, { multiplier:1, sources:[] });
  }
  function activeBuffSetting(runtime, skillId) {
    var setting = runtime && runtime.activeBuffs && runtime.activeBuffs[skillId];
    if (setting === true) return { active:true, stacks:0 };
    if (!setting || typeof setting !== 'object') return { active:false, stacks:0 };
    return { active:Boolean(setting.active), stacks:Math.max(0, Math.floor(num(setting.stacks))) };
  }
  function activeCombatModifiers(skill, base, combat, inputs, runtime, flags) {
    return definitions().filter(function (candidate) { return candidate.kind === 'buff' || candidate.activeBuff === true; }).reduce(function (result, candidate) {
      var setting = activeBuffSetting(runtime, candidate.id);
      if (!setting.active && !setting.stacks) return result;
      var candidateRuntime = Object.assign({}, runtime || {}, { buff:{ active:setting.active, stacks:setting.stacks } });
      var candidateState = context(base, candidate, combat, inputs, candidateRuntime);
      candidateState.attack.flags = flags || {};
      if (!test(candidate.requirements && candidate.requirements.when, candidateState)) return result;
      (setting.active ? candidate.effects : (candidate.inactiveEffects || [])).forEach(function (effect) {
        if (!test(effect.when, candidateState)) return;
        if (effect.type === 'damageMultiplier' && matchesDamageTarget(effect.target, skill)) {
          var multiplier = num(expr(effect.value, candidateState)); result.multiplier *= multiplier; result.sources.push({ source:candidate.nameKo, value:multiplier });
        } else if (effect.type === 'globalSkillConstant') {
          var constant = num(expr(effect.value, candidateState)); result.constant += constant; result.sources.push({ source:candidate.nameKo, key:'constant', value:constant });
        } else if (effect.type === 'resourceCostModifier' && effect.key === 'MP' && matchesDamageTarget(effect.target || 'attack', skill)) {
          var mp = num(expr(effect.value, candidateState)); result.mpCostFlat += mp; result.sources.push({ source:candidate.nameKo, key:'MP', value:mp });
        }
      });
      return result;
    }, { multiplier:1, constant:0, mpCostFlat:0, sources:[] });
  }
  function profile(id, base, combat, inputs, runtime) {
    var skill = find(id); if (!skill) return null;
    var state = context(base, skill, combat, inputs, runtime);
    normalizeInputs(skill, state);
    var available = state.skill.level > 0 && test(skill.requirements && skill.requirements.when, state);
    var activeModifiers = available ? activeCombatModifiers(skill, base, combat, inputs, runtime, {}) : { multiplier:1, constant:0, mpCostFlat:0, sources:[] };
    var resolvedCost = available ? resolveCost(skill.cost, state) : null;
    if (resolvedCost) resolvedCost.mp += activeModifiers.mpCostFlat;
    return {
      skill:skill,
      available:available,
      cost:resolvedCost,
      activeCombatModifiers:activeModifiers.sources,
      castTime:available ? resolveCastTime(skill.castTime, state) : null,
      stateTransitions:available ? (skill.stateTransitions || []).map(function (item) { return resolveTransition(item, state); }).filter(Boolean) : [],
      triggeredEffects:available ? triggeredPassiveEffects(skill, base, combat, inputs, runtime) : [],
      effects:available ? (skill.effects || []).filter(function (effect) { return test(effect.when, state); }).map(function (effect) { return resolveEffect(effect, state); }) : [],
      hits:available && skill.kind === 'attack' ? (skill.attacks || []).filter(function (hit) { return test(hit.when, state); }).map(function (hit) {
        state.attack.flags = hit.flags || {};
        var modifiers = passiveDamageModifiers(skill, base, combat, inputs, runtime, state.attack.flags);
        var active = activeCombatModifiers(skill, base, combat, inputs, runtime, state.attack.flags);
        return { id:hit.id, count:num(expr(hit.count, state)), multiplier:num(expr(hit.multiplier, state)) * modifiers.multiplier * active.multiplier, constant:num(expr(hit.constant, state)) + active.constant, damageType:hit.damageType, flags:hit.flags || {}, passiveDamageModifiers:modifiers.sources.concat(active.sources), stateTransitions:(hit.stateTransitions || []).map(function (item) { return resolveTransition(item, state); }).filter(Boolean) };
      }) : []
    };
  }
  function passiveStatChanges(base) {
    return definitions().filter(function (skill) { return skill.kind === 'passive' && skillLevel(skill) > 0; }).reduce(function (changes, skill) {
      var state = context(base, skill);
      if (!test(skill.requirements && skill.requirements.when, state)) return changes;
      (skill.effects || []).forEach(function (effect) {
        if (effect.type === 'stat' && (!effect.phase || effect.phase === 'build') && test(effect.when, state)) changes.push({ key:effect.key, value:num(expr(effect.value, state)), source:skill });
      });
      return changes;
    }, []);
  }
  function attackProfile(id, base, combat, inputs, runtime) { var result = profile(id, base, combat, inputs, runtime); return result && result.skill.kind === 'attack' ? result : null; }
  function specialAttackProfile(id, specialId, base, combat, inputs, runtime) {
    var skill = find(id); if (!skill) return null;
    var state = context(base, skill, combat, inputs, runtime);
    normalizeInputs(skill, state);
    var available = state.skill.level > 0 && test(skill.requirements && skill.requirements.when, state);
    var special = (skill.specialAttacks || []).find(function (item) { return item.id === specialId; });
    if (!special) return null;
    return {
      skill:skill, specialAttack:special, available:available,
      hits:available ? (special.hits || []).filter(function (hit) { return test(hit.when, state); }).map(function (hit, index) {
        return { id:hit.id || ('hit' + (index + 1)), count:num(expr(hit.count === undefined ? {op:'value',value:1} : hit.count, state)), multiplier:num(expr(hit.multiplier, state)), constant:num(expr(hit.constant, state)), damageType:hit.damageType || special.damageType || 'physical', flags:Object.assign({}, special.flags || {}, hit.flags || {}) };
      }) : []
    };
  }
  window.ToramSkillEffects = Object.freeze({ expression:expr, condition:test, find:find, passiveStatChanges:passiveStatChanges, attackProfile:attackProfile, specialAttackProfile:specialAttackProfile, profile:profile });
}());
