import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
const events = createRequire(import.meta.url)('../../../web/src/calculation/option-event-calculator.js');
const calculate = (stats = {}, inputs = {}, overrides = {}) => events.evaluate({ctx:{preservedStats:stats},finalMaxHP:1000,...overrides},inputs);

// Hand-calculated native integer truncation at every 50-point band.
for (const [resistance,expected] of [[0,1001],[25,750],[50,500],[51,495],[75,375],[100,250],[-25,1251],[-50,1501],[-75,1876],[-100,2251]]) {
  assert.equal(events.resistDamage(1001,resistance),expected,`Resistance ${resistance}`);
}
assert.equal(events.resistDamage(100000001,0),100000001,'A zero resistance pass returns the integer unchanged before float32 arithmetic');
assert.equal(calculate().outcomes.damageAfter_PHYS_RES,null,'A missing event base never produces invented damage');
assert.throws(()=>calculate({}, {incomingDamage:-1}),/입력 범위/u);
assert.throws(()=>calculate({}, {incomingDamage:1.5}),/정수 피해/u);
assert.throws(()=>calculate({PHYS_RES:NaN},{incomingDamage:1000}),/유한한/u);
for (const [action,key] of [[1,'AROUND_RES'],[12,'AREA_RES'],[44,'CHARGE_RED'],[1220,'LINE_RED'],[150,'WIDD_RES'],[1061,'METEOR_RES'],[1231,'BULLET_RES'],[1084,'TRANSLATION_RES'],[1110,'AOE_RES'],[1175,'SUCTION_RES'],[1181,'EXPLOSION_RES']]) assert.equal(events.shapeStat(action),key);
assert.equal(events.shapeStat(999999),null);
const combined=calculate({PHYS_RES:40,AROUND_RES:20,FIRE_RES:50},{incomingDamage:1000,incomingType:'physical',incomingActionType:1,incomingElement:1});
assert.equal(combined.outcomes.damageAfterBodyAndShape,450,'Body and shape resistance are added before the 50-point band calculation');
assert.equal(combined.outcomes.damageAfterElement,225,'Element resistance is a separate second pass');
const neutral=calculate({MAG_RES:20,NEUTRAL_RES:25},{incomingDamage:1000,incomingType:'magic',incomingActionType:0,incomingElement:0});
assert.equal(neutral.outcomes.damageAfterElement,600);
for(const key of ['PHYS_RES','MAG_RES','FIRE_RES','WATER_RES','WIND_RES','EARTH_RES','LIGHT_RES','DARK_RES','NEUTRAL_RES','AROUND_RES','AREA_RES','LINE_RED','CHARGE_RED','METEOR_RES','BULLET_RES','TRANSLATION_RES','AOE_RES','WIDD_RES','EXPLOSION_RES','SUCTION_RES']) assert.equal(calculate({[key]:75},{incomingDamage:1001}).outcomes['damageAfter_'+key],375,key);
const barrier=calculate({PHYS_BARR:100,MAG_BARR:10,FRAC_BARR:20},{incomingDamage:50});
assert.equal(barrier.outcomes.damageAfter_PHYS_BARR,1);
assert.equal(barrier.outcomes.damageAfter_MAG_BARR,40);
assert.equal(barrier.values.barrierAbsorption_FRAC_BARR,200);
assert.equal(barrier.outcomes.damageAfter_FRAC_BARR,1);
assert.equal(calculate({REFLECT:30},{incomingDamage:1001}).outcomes.reflectedDamage,300);
assert.equal(calculate({REFLECT:-30},{incomingDamage:1001}).outcomes.reflectedDamage,-300,'Signed reflection is preserved rather than silently clamped');
const guard=calculate({GUARD_POWER:20,GUARD_RECHARGE:50,AVOID_RECHARGE:-20},{incomingDamage:1000,baseGuardPower:7500,baseGuardRecharge:75,baseAvoidRecharge:300});
assert.equal(guard.values.guardPower,9000);
assert.equal(guard.outcomes.damageAfterGuard,100);
assert.equal(guard.values.guardRecharge,112);
assert.equal(guard.values.avoidRecharge,240);
assert.equal(calculate({GUARD_POWER:-200},{baseGuardPower:7500}).values.guardPower,100);
assert.equal(calculate({GUARD_RECHARGE:-200},{baseGuardRecharge:75}).values.guardRecharge,1);
assert.equal(calculate({AILMENT_RES:20},{mentality:255}).values.ailmentResistance,95);
assert.equal(calculate({AILMENT_RES:100},{mentality:255}).values.ailmentResistance,100);
assert.equal(calculate({AILMENT_RES:-25},{mentality:0}).values.ailmentResistance,-25,'Getter has an upper cap, not an invented lower cap');
assert.equal(calculate({BARR_SPEED:50},{baseBarrierCooldown:30}).values.barrierCooldown,20,'Barrier speed subtracts 20*speed/100, not a percent of the caller base');
assert.equal(calculate({BARR_SPEED:150},{baseBarrierCooldown:30}).values.barrierCooldown,10);
assert.equal(calculate({BARR_SPEED:-50},{baseBarrierCooldown:30}).values.barrierCooldown,40);
assert.equal(calculate({ABS_DODGE:80}).values.absoluteDodgeChance,30,'Absolute dodge cap is 30, not 100');
assert.equal(calculate({ABS_DODGE:30},{absoluteDodgeEligible:true,absoluteDodgeRoll:29}).outcomes.absoluteDodge,true);
assert.equal(calculate({ABS_DODGE:30},{absoluteDodgeEligible:true,absoluteDodgeRoll:30}).outcomes.absoluteDodge,false);
assert.equal(calculate({ABS_DODGE:30},{absoluteDodgeEligible:false,absoluteDodgeRoll:0}).outcomes.absoluteDodge,false);
assert.equal(calculate({ABS_DODGE:-10}).values.absoluteDodgeChance,0);
console.log('Option incoming stages: PASS (native resistance bands/order, all 11 shapes, barriers, guard/recovery, reflection, explicit event bases)');
