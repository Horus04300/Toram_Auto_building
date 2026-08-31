/* 콤보 순서 계산: 피격·시간 경과 없이 다음 스킬 1회 효과, 콤보 태그, MP 소모를 평가한다. */
(function () {
  'use strict';
  var effects = window.ToramSkillEffects;
  if (!effects) throw new Error('콤보 순서 엔진은 스킬 효과 엔진 뒤에 로드되어야 합니다.');

  function number(value, fallback) { value = Number(value); return Number.isFinite(value) ? value : (fallback || 0); }
  function emptyModifiers() { return { mpCostMultiplier:1, motionSpeed:0, damageMultiplier:1, physicalChaseDamage:0, shortRangeDamagePercent:0, hit:0, skillConstant:0, castTimeReductionPercent:0, guaranteedCritical:false, sources:[], targeted:[] }; }
  function copyModifiers(value) { return { mpCostMultiplier:value.mpCostMultiplier, motionSpeed:value.motionSpeed, damageMultiplier:value.damageMultiplier, physicalChaseDamage:value.physicalChaseDamage, shortRangeDamagePercent:value.shortRangeDamagePercent, hit:value.hit, skillConstant:value.skillConstant, castTimeReductionPercent:value.castTimeReductionPercent, guaranteedCritical:Boolean(value.guaranteedCritical), sources:value.sources.slice(), targeted:(value.targeted || []).map(function (item) { return Object.assign({}, item, { skillIds:item.skillIds.slice() }); }) }; }
  function addSource(target, source, key, value) { target.sources.push({ source:source, key:key, value:value }); }
  function mergeModifier(target, key, value, source) {
    value = number(value);
    if (key === 'mpCostMultiplier') target.mpCostMultiplier *= value;
    else if (key === 'motionSpeed') target.motionSpeed = Math.min(50, target.motionSpeed + value);
    else if (key === 'damageMultiplier') target.damageMultiplier *= value;
    else if (key === 'physicalChaseDamage') target.physicalChaseDamage += value;
    else if (key === 'shortRangeDamagePercent' || key === 'hit' || key === 'skillConstant') target[key] += value;
    else if (key === 'castTimeReductionPercent') target.castTimeReductionPercent = Math.min(100, target.castTimeReductionPercent + value);
    else if (key === 'guaranteedCritical') target.guaranteedCritical = Boolean(value);
    else return;
    addSource(target, source, key, value);
  }
  function collectNextSkillModifiers(profile, target) {
    (profile.stateTransitions || []).forEach(function (transition) {
      (transition.effects || []).forEach(function (effect) {
        if (effect.type === 'nextSkillModifier' && transition.targetSkillIds && transition.targetSkillIds.length) target.targeted.push({ key:effect.key, value:effect.value, source:profile.skill.nameKo, skillIds:transition.targetSkillIds.slice(), requiresActualMpCost:Boolean(transition.requiresActualMpCost) });
        else if (effect.type === 'nextSkillModifier') mergeModifier(target, effect.key, effect.value, profile.skill.nameKo);
      });
    });
    (profile.triggeredEffects || []).forEach(function (effect) {
      if (effect.type === 'nextSkillModifier') mergeModifier(target, effect.key, effect.value, effect.source || profile.skill.nameKo);
    });
    (profile.effects || []).forEach(function (effect) {
      if (effect.type === 'nextSkillModifier') mergeModifier(target, effect.key, effect.value, profile.skill.nameKo);
    });
  }
  function castMpRefund(profile) {
    return (profile.effects || []).reduce(function (total, effect) {
      return effect.phase === 'cast' && effect.type === 'resourceRefund' && effect.key === 'MP' ? total + number(effect.value) : total;
    }, 0);
  }
  function comboRule(tag) {
    var data = window.TORAM_COMBO_RULE_DATA || {};
    return data.tags && data.tags[tag] || null;
  }
  function clampComboDamageMultiplier(value) {
    var bounds = ((window.TORAM_COMBO_RULE_DATA || {}).constants || {}).damageMultiplier || {};
    return Math.min(Number(bounds.max) || 1.5, Math.max(Number(bounds.min) || .1, value));
  }
  function chargeDamageMultiplier(position, effects) {
    return effects.reduce(function (multiplier, effect) {
      var offset = position - effect.position;
      return offset < 1 || offset > effect.values.length ? multiplier : multiplier * Math.max(0, 1 - number(effect.values[offset - 1]));
    }, 1);
  }
  function tenacityHpCost(missingMp, maxHp, rule) {
    var cost = rule && rule.mp && rule.mp.hpCost || {};
    return missingMp > 0 && maxHp > 0 ? maxHp * (missingMp / number(cost.perMissingMp, 100)) * (number(cost.maxHpPercent, 10) / 100) : 0;
  }
  function comboTag(entry, position, consecutiveOrdinal, isLast, isDamageSkill) {
    var tag = position === 1 ? 'none' : (entry.tag || 'none');
    var rule = comboRule(tag);
    var result = { id:tag, mpReduction:0, mpMultiplier:1, damageMultiplier:1, motionSpeed:0, nextDamageMultiplier:1, chargeStore:false, chargeDamageReductions:[], absoluteHit:false, hitBonus:0, usesTenacity:false, valid:true };
    if (tag === 'consecutive') {
      result.mpReduction = (position - 1) * 100;
      if (isDamageSkill) result.damageMultiplier = 1 - consecutiveOrdinal * .1;
    } else if (tag === 'charge' && rule) {
      result.chargeStore = true;
      result.chargeDamageReductions = Array.isArray(rule.damage && rule.damage.values) ? rule.damage.values.slice() : [];
    } else if (tag === 'swift') result.motionSpeed = 50;
    else if (tag === 'smite') {
      if (isDamageSkill) result.damageMultiplier = 1.5;
      if (isLast) result.mpMultiplier = 2;
      else result.nextDamageMultiplier = .5;
    } else if (tag === 'mindsEye' && rule) {
      result.absoluteHit = Boolean(rule.accuracy && rule.accuracy.absoluteHit);
      result.hitBonus = position * number(rule.accuracy && rule.accuracy.bonus && rule.accuracy.bonus.args && rule.accuracy.bonus.args[1] && rule.accuracy.bonus.args[1].value);
    } else if (tag === 'tenacity' && rule) {
      result.usesTenacity = true;
    } else if (tag !== 'none') result.valid = false;
    return result;
  }
  function evaluate(entries, base, combat, runtime) {
    entries = Array.isArray(entries) ? entries : [];
    runtime = runtime || {};
    var hasMpLimit = Number.isFinite(Number(runtime.maxMp));
    var maxMp = hasMpLimit ? Math.max(0, Math.floor(Number(runtime.maxMp))) : null;
    var currentMp = maxMp;
    var maxHp = Math.max(0, number(runtime.maxHp, combat && combat.MAXHP));
    var canceledAt = null;
    var blockedAt = null;
    var blockReason = '';
    var pending = emptyModifiers();
    var consecutiveOrdinal = 0;
    var lastMagicAttack = null;
    var storedMp = 0;
    var chargeDamageEffects = [];
    var results = [];
    entries.forEach(function (entry, index) {
      var position = index + 1;
      if (canceledAt !== null) {
        results.push({ position:position, skillId:entry.skillId, available:false, executionStatus:'skipped', canceledByPosition:canceledAt, error:'이전 스킬의 MP 부족으로 실행되지 않음' });
        return;
      }
      if (blockedAt !== null) {
        results.push({ position:position, skillId:entry.skillId, available:false, executionStatus:'skipped', blockedByPosition:blockedAt, error:blockReason + ' 이후 스킬은 실행되지 않음' });
        return;
      }
      var carriedTargeted = (pending.targeted || []).slice();
      var matchedTargeted = [];
      var applied = copyModifiers(pending);
      applied.targeted = [];
      pending = emptyModifiers();
      carriedTargeted.forEach(function (item) {
        if (item.skillIds.indexOf(entry.skillId) >= 0) matchedTargeted.push(item);
        else pending.targeted.push(item);
      });
      var profile = effects.profile(entry.skillId, base, combat, entry.inputs || {}, Object.assign({}, runtime, { maxMp:maxMp, currentMp:currentMp, combo:{ position:position } }));
      if (!profile) {
        blockedAt = position; blockReason = '정의가 없는 스킬';
        results.push({ position:position, skillId:entry.skillId, available:false, executionStatus:'unavailable', error:blockReason });
        return;
      }
      if (!profile.available) {
        blockedAt = position; blockReason = '현재 장비·조건에서 사용할 수 없는 스킬';
        results.push({ position:position, skillId:entry.skillId, skill:profile.skill, available:false, executionStatus:'unavailable', error:blockReason });
        return;
      }
      var comboRules = profile.skill.combo || {};
      var requestedTag = position === 1 ? 'none' : (entry.tag || 'none');
      if (position === 1 && comboRules.canStart === false) {
        blockedAt = position; blockReason = '콤보 기점으로 사용할 수 없는 스킬';
        results.push({ position:position, skillId:entry.skillId, skill:profile.skill, available:false, executionStatus:'unavailable', error:blockReason });
        return;
      }
      if (requestedTag !== 'none' && comboRules.canReceiveTag === false) {
        blockedAt = position; blockReason = '콤보 효과를 설정할 수 없는 스킬';
        results.push({ position:position, skillId:entry.skillId, skill:profile.skill, available:false, executionStatus:'unavailable', error:blockReason });
        return;
      }
      var copiedFrom = null;
      if (profile.skill.id === 'Magic:5') {
        if (!lastMagicAttack) { blockedAt = position; blockReason = '복사할 이전 매직 공격 스킬이 없습니다.'; results.push({ position:position, skillId:entry.skillId, skill:profile.skill, available:false, executionStatus:'unavailable', error:blockReason }); return; }
        copiedFrom = lastMagicAttack;
        profile = Object.assign({}, profile, { hits:lastMagicAttack.profile.hits.map(function (hit) { return Object.assign({}, hit, { flags:Object.assign({}, hit.flags || {}) }); }), castTime:null });
      }
      var isDamageSkill = profile.hits.length > 0 || Boolean(copiedFrom);
      if ((entry.tag || 'none') === 'consecutive' && position > 1) consecutiveOrdinal += 1;
      var tag = copiedFrom ? comboTag({ tag:'none' }, position, consecutiveOrdinal, index === entries.length - 1, isDamageSkill) : comboTag(entry, position, consecutiveOrdinal, index === entries.length - 1, isDamageSkill);
      var nativeMp = copiedFrom ? copiedFrom.finalMp : (profile.cost ? number(profile.cost.mp) : 0);
      matchedTargeted.forEach(function (item) {
        if (!item.requiresActualMpCost || nativeMp > 0) mergeModifier(applied, item.key, item.value, item.source);
        else pending.targeted.push(item);
      });
      var skillAdjustedMp = nativeMp * applied.mpCostMultiplier;
      var finalMp = Math.max(0, Math.round((skillAdjustedMp - tag.mpReduction) * tag.mpMultiplier));
      var storedMpBefore = storedMp;
      var storedMpUsed = 0;
      var mpPaidFromCurrent = 0;
      var hpCost = 0;
      var discardedStoredMp = 0;
      var chargeStoredMp = 0;
      if (tag.chargeStore) {
        discardedStoredMp = storedMp;
        storedMp = nativeMp;
        chargeStoredMp = storedMp;
      } else {
        storedMpUsed = Math.min(storedMp, finalMp);
        storedMp -= storedMpUsed;
        mpPaidFromCurrent = finalMp - storedMpUsed;
        if (tag.usesTenacity && hasMpLimit && mpPaidFromCurrent > currentMp) {
          hpCost = tenacityHpCost(mpPaidFromCurrent - currentMp, maxHp, comboRule('tenacity'));
          mpPaidFromCurrent = currentMp;
        }
      }
      if (hasMpLimit && mpPaidFromCurrent > currentMp) {
        storedMp = storedMpBefore;
        pending = applied;
        canceledAt = position;
        results.push({
          position:position, skillId:entry.skillId, skill:profile.skill, available:profile.available, executionStatus:'canceled',
          tag:tag, nativeMp:nativeMp, skillAdjustedMp:skillAdjustedMp, finalMp:finalMp,
          mpBefore:currentMp, mpAfter:currentMp, appliedNextSkillModifiers:applied,
          storedMpBefore:storedMpBefore, storedMpUsed:storedMpUsed, chargeStoredMp:chargeStoredMp, discardedStoredMp:discardedStoredMp, hpCost:0,
          damageMultiplier:1, motionSpeed:0, physicalChaseDamage:0, hits:[], effects:[], stateTransitions:[],
          generatedNextSkillModifiers:copyModifiers(pending), error:'현재 MP보다 소모 MP가 많아 콤보가 취소됨'
        });
        return;
      }
      var appliedDamageMultiplier = copiedFrom ? 1 : applied.damageMultiplier;
      var tagDamageMultiplier = copiedFrom ? 1 : tag.damageMultiplier;
      var damageMultiplier = copiedFrom ? 1 : clampComboDamageMultiplier(appliedDamageMultiplier * tagDamageMultiplier * chargeDamageMultiplier(position, chargeDamageEffects));
      var motionSpeed = Math.min(50, applied.motionSpeed + tag.motionSpeed);
      var hitBonus = applied.hit + tag.hitBonus;
      var hits = profile.hits.map(function (hit) {
        var runtimeFlags = hit.resolvedFlags || hit.flags || {};
        var comboDamageMultiplier = runtimeFlags.ignoresComboDamageChange ? 1 : damageMultiplier;
        var damageMultiplierLayers = {
          skill:Number.isFinite(Number(hit.baseMultiplier)) ? Number(hit.baseMultiplier) : Number(hit.multiplier) || 1,
          passive:Number.isFinite(Number(hit.passiveMultiplier)) ? Number(hit.passiveMultiplier) : 1,
          active:Number.isFinite(Number(hit.activeMultiplier)) ? Number(hit.activeMultiplier) : 1,
          combo:comboDamageMultiplier
        };
        return Object.assign({}, hit, { flags:Object.assign({}, runtimeFlags, applied.guaranteedCritical ? { guaranteedCritical:true } : {}, tag.absoluteHit ? { guaranteedHit:true } : {}, hitBonus ? { hitBonus:number(runtimeFlags.hitBonus) + hitBonus } : {}), constant:hit.constant + applied.skillConstant, damageMultiplierLayers:damageMultiplierLayers, effectiveMultiplier:hit.multiplier * comboDamageMultiplier });
      });
      var castTimeSeconds = profile.castTime ? Math.max(0, profile.castTime.seconds * (1 - applied.castTimeReductionPercent / 100)) : null;
      var mpRefund = castMpRefund(profile);
      var result = {
        position:position, skillId:entry.skillId, skill:profile.skill, available:profile.available, executionStatus:'executed', tag:tag,
        nativeMp:nativeMp, skillAdjustedMp:skillAdjustedMp, finalMp:finalMp,
        mpBefore:currentMp, mpAfter:hasMpLimit ? Math.min(maxMp, currentMp - mpPaidFromCurrent + mpRefund) : null, mpRefund:mpRefund,
        storedMpBefore:storedMpBefore, storedMpUsed:storedMpUsed, storedMpAfter:storedMp, chargeStoredMp:chargeStoredMp, discardedStoredMp:discardedStoredMp, mpPaidFromCurrent:mpPaidFromCurrent, hpCost:hpCost,
        appliedNextSkillModifiers:applied, damageMultiplier:damageMultiplier, motionSpeed:motionSpeed, castTimeSeconds:castTimeSeconds,
        physicalChaseDamage:applied.physicalChaseDamage, hitBonus:hitBonus, absoluteHit:tag.absoluteHit, hits:hits, effects:profile.effects,
        stateTransitions:profile.stateTransitions
      };
      if (hasMpLimit) currentMp = result.mpAfter;
      if (!copiedFrom && profile.skill.treeId === 'Magic' && profile.skill.kind === 'attack' && profile.hits.length) lastMagicAttack = { profile:profile, finalMp:finalMp };
      if (copiedFrom) result.copiedSkillId = copiedFrom.profile.skill.id;
      if (profile.skill.id === 'Blade:11' && base && base.mainType === '양손검') {
        result.generatedState = { stateId:'blade.moonSlash', stacks:Math.min(9, position === 1 ? 1 : position), notes:'현재 문 슬래시 시전으로 획득하는 스택' };
      }
      if (entry.includeSpecialAttack) {
        var specialId = typeof entry.includeSpecialAttack === 'string' ? entry.includeSpecialAttack : (((profile.skill.specialAttacks || [])[0] || {}).id || 'finishAttack');
        result.specialAttack = effects.specialAttackProfile(entry.skillId, specialId, base, combat, entry.inputs || {}, runtime);
      }
      collectNextSkillModifiers(profile, pending);
      if (tag.nextDamageMultiplier !== 1) mergeModifier(pending, 'damageMultiplier', tag.nextDamageMultiplier, '강타 후속 페널티');
      if (tag.chargeStore && tag.chargeDamageReductions.length) chargeDamageEffects.push({ position:position, values:tag.chargeDamageReductions });
      result.generatedNextSkillModifiers = copyModifiers(pending);
      results.push(result);
    });
    var chargeSettlementMp = 0;
    var chargeSettlementShortfall = 0;
    if (hasMpLimit && storedMp > 0) {
      chargeSettlementMp = Math.min(currentMp, storedMp);
      chargeSettlementShortfall = Math.max(0, storedMp - chargeSettlementMp);
      currentMp -= chargeSettlementMp;
    }
    return { entries:results, maxMp:maxMp, remainingMp:currentMp, canceledAt:canceledAt, blockedAt:blockedAt, blockReason:blockReason, chargeSettlementMp:chargeSettlementMp, chargeSettlementShortfall:chargeSettlementShortfall, unconsumedNextSkillModifiers:copyModifiers(pending) };
  }

  window.ToramComboSequence = Object.freeze({ evaluate:evaluate });
}());
