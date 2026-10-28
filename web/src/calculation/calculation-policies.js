import {statRegistry} from './stat-registry.js';
/* 계산 조립 경계가 공유하는 결정 정책. UI 표시와 계산 커널은 이 계약만 사용한다. */

  'use strict';

  function requireValue(value,message) { if (!value) throw new Error(message); }
function matchesItemCondition(context, condition) {
  if (!condition) return true;
  const ctx = context || {};
  if (condition.kind === 'item-event') return (ctx.activeItemEventTypes || []).includes(condition.eventType);
  if (condition.kind === 'all') return condition.conditions.every(when => matchesItemCondition(ctx, when));
  if (condition.kind === 'any') return condition.conditions.some(when => matchesItemCondition(ctx, when));
  if (condition.kind === 'not') return !matchesItemCondition(ctx, condition.condition);
  if (condition.kind === 'either-weapon-slot') {
    requireValue(typeof ctx.mainType === 'string' && typeof ctx.subType === 'string', 'Item condition needs mainType and subType.');
    return condition.types.includes(ctx.mainType) || condition.types.includes(ctx.subType);
  }
  if (condition.kind === 'both-weapon-slots') {
    requireValue(typeof ctx.mainType === 'string' && typeof ctx.subType === 'string', 'Item condition needs mainType and subType.');
    return ctx.mainType === condition.main && ctx.subType === condition.sub;
  }
  if (condition.kind === 'body-battle-customize') {
    requireValue(typeof ctx.armorType === 'string', 'Item condition needs armorType.');
    return ctx.armorType === condition.armor;
  }
  throw new Error('Unsupported item condition.');
}

  function applyStat(context, key, value) {
    var registry = statRegistry;
    if (!registry || typeof registry.apply !== 'function') throw new Error('StatRegistry가 준비되지 않았습니다.');
    return registry.apply(context, key, value);
  }

  var api = Object.freeze({
    matchesItemCondition:matchesItemCondition,
    applyStat: applyStat,
    matchesCrystaCondition: matchesItemCondition
  });

  export const policies = api;


export {matchesItemCondition,matchesItemCondition as matchesCrystaCondition,applyStat};
