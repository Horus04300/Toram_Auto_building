(function (root) {
  'use strict';
  var SCHEMA='toram.d4-build-evaluator.v1';
  function clone(value){if(value===null||value===undefined||typeof value!=='object')return value;if(Array.isArray(value))return value.map(clone);return Object.keys(value).reduce(function(result,key){result[key]=clone(value[key]);return result;},{});}
  function freeze(value){if(!value||typeof value!=='object'||Object.isFrozen(value))return value;Object.keys(value).forEach(function(key){freeze(value[key]);});return Object.freeze(value);}
  function stableStringify(value){if(value===null||typeof value!=='object')return JSON.stringify(value);if(Array.isArray(value))return '['+value.map(stableStringify).join(',')+']';return '{'+Object.keys(value).sort().map(function(key){return JSON.stringify(key)+':'+stableStringify(value[key]);}).join(',')+'}';}
  function hashString(text){var hash=2166136261;for(var i=0;i<text.length;i++){hash^=text.charCodeAt(i);hash=Math.imul(hash,16777619);}return('00000000'+(hash>>>0).toString(16)).slice(-8);}
  function createBuildSnapshot(baseContext,candidates,metadata){var snapshot={schema:SCHEMA,baseContext:clone(baseContext||{}),candidates:clone(Array.isArray(candidates)?candidates:[]),metadata:clone(metadata||{})};snapshot.hash=hashString(stableStringify(snapshot));return freeze(snapshot);}
  function defaultRequirements(baseContext){var ctx=baseContext||{};return{maxHp:ctx.rangeType==='LONG'?null:10000,maxMp:Number(ctx.godspeedWieldLevel)===10?2300:2000,amprBeforeDual:Number(ctx.maximizerLevel)===10?0:100,normalAttackCrit:100,aspd:1000};}
  function createScenarioSnapshot(baseContext,overrides){var input=overrides||{};var scenario={schema:SCHEMA,basisName:String(input.basisName||baseContext&&baseContext.optimizationBasisName||'평타'),attackType:String(input.attackType||baseContext&&baseContext.atkType||'PHYS'),rangeType:String(input.rangeType||baseContext&&baseContext.rangeType||'SHORT'),requirements:Object.assign(defaultRequirements(baseContext),clone(input.requirements||{})),combo:clone(input.combo||null),metadata:clone(input.metadata||{})};scenario.hash=hashString(stableStringify(scenario));return freeze(scenario);}
  function violation(metric,actual,required){return{metric:metric,actual:Number(actual),required:Number(required),shortage:Number(required)-Number(actual)};}
  function outcomeFromRaw(raw,scenario,buildHash,immutable){
    var requirements=scenario.requirements||{};var violations=[];
    if(requirements.maxHp!==null&&requirements.maxHp!==undefined&&raw.finalMaxHP<requirements.maxHp)violations.push(violation('MAXHP',raw.finalMaxHP,requirements.maxHp));
    if(requirements.maxMp!==null&&requirements.maxMp!==undefined&&raw.finalMaxMP<requirements.maxMp)violations.push(violation('MAXMP',raw.finalMaxMP,requirements.maxMp));
    if(requirements.amprBeforeDual!==null&&requirements.amprBeforeDual!==undefined&&raw.amprBeforeDual<requirements.amprBeforeDual)violations.push(violation('AMPR',raw.amprBeforeDual,requirements.amprBeforeDual));
    if(requirements.normalAttackCrit!==null&&requirements.normalAttackCrit!==undefined&&raw.normalAttackCrit<requirements.normalAttackCrit)violations.push(violation('NORMAL_ATTACK_CRIT',raw.normalAttackCrit,requirements.normalAttackCrit));
    if(requirements.aspd!==null&&requirements.aspd!==undefined&&raw.finalASPD<requirements.aspd)violations.push(violation('ASPD',raw.finalASPD,requirements.aspd));
    var diagnostics=immutable?clone(raw.ctx&&raw.ctx.statDiagnostics||[]):raw.ctx&&raw.ctx.statDiagnostics||[];
    var outcome={schema:SCHEMA,buildHash:buildHash||null,scenarioHash:scenario.hash,basisName:scenario.basisName,damage:{base:raw.damageFactor,triggered:raw.procTriggeredDamageFactor,expected:raw.optimizationDamageFactor},offense:{atk:raw.finalATK,matk:raw.finalMATK,criticalDamage:raw.finalCDMG,selectedAttackCritical:raw.finalCrit,normalAttackCrit:raw.normalAttackCrit,stability:raw.finalStab,physicalPierce:raw.ctx.physPierce,magicPierce:raw.ctx.magPierce},utility:{maxHp:raw.finalMaxHP,maxMpBeforeBuff:raw.finalMaxMP,maxMpAfterBuff:raw.finalMaxMPAfterBuff,baseAmpr:raw.baseAMPR,amprPercent:raw.ctx.amprP,equipmentAndBuffAmpr:raw.equipmentAndBuffAMPR,amprBeforeNormalAttackActive:raw.amprBeforeNormalAttackActive,normalAttackActiveCandidates:immutable?clone(raw.normalAttackAmprActiveCandidates||[]):raw.normalAttackAmprActiveCandidates||[],selectedNormalAttackActive:immutable?clone(raw.selectedNormalAttackAmprActive):raw.selectedNormalAttackAmprActive,amprBeforeDual:raw.amprBeforeDual,finalAmpr:raw.finalAMPR,aspd:raw.finalASPD,motionSpeed:raw.finalMotionSpeed,cspd:raw.finalCSPD,castReduction:raw.finalCastReduction},constraints:{feasible:violations.length===0&&diagnostics.length===0,violations:violations},diagnostics:diagnostics,calculation:raw};
    return immutable?freeze(outcome):outcome;
  }
  function evaluate(buildSnapshot,scenarioSnapshot,kernel){
    if(!buildSnapshot||buildSnapshot.schema!==SCHEMA)throw new Error('유효한 D4 BuildSnapshot이 필요합니다.');
    var evaluator=kernel||root.ToramCalculationKernel&&root.ToramCalculationKernel.evaluateContext;if(typeof evaluator!=='function')throw new Error('D4 계산 커널이 연결되지 않았습니다.');
    var scenario=scenarioSnapshot||createScenarioSnapshot(buildSnapshot.baseContext);var raw=evaluator(clone(buildSnapshot.baseContext),clone(buildSnapshot.candidates));
    return outcomeFromRaw(raw,scenario,buildSnapshot.hash,true);
  }
  function evaluateAggregate(baseContext,scenarioSnapshot,stats,kernel){
    var evaluator=kernel||root.ToramCalculationKernel&&root.ToramCalculationKernel.evaluateContext;if(typeof evaluator!=='function')throw new Error('D4 계산 커널이 연결되지 않았습니다.');
    var scenario=scenarioSnapshot||createScenarioSnapshot(baseContext);var raw=evaluator(baseContext||{},[{name:'D4 aggregate',stats:stats||{}}]);
    return outcomeFromRaw(raw,scenario,null,false);
  }
  function evaluateAggregateSummary(baseContext,scenarioSnapshot,stats,kernel){
    var evaluator=kernel||root.ToramCalculationKernel&&root.ToramCalculationKernel.evaluateContext;if(typeof evaluator!=='function')throw new Error('D4 계산 커널이 연결되지 않았습니다.');
    var scenario=scenarioSnapshot||createScenarioSnapshot(baseContext);var requirements=scenario.requirements||{};var raw=evaluator(baseContext||{},[{name:'D4 aggregate',stats:stats||{}}],true);var feasible=!(raw.ctx&&raw.ctx.statDiagnostics&&raw.ctx.statDiagnostics.length);
    if(requirements.maxHp!==null&&requirements.maxHp!==undefined&&raw.finalMaxHP<requirements.maxHp)feasible=false;
    if(requirements.maxMp!==null&&requirements.maxMp!==undefined&&raw.finalMaxMP<requirements.maxMp)feasible=false;
    if(requirements.amprBeforeDual!==null&&requirements.amprBeforeDual!==undefined&&raw.amprBeforeDual<requirements.amprBeforeDual)feasible=false;
    if(requirements.normalAttackCrit!==null&&requirements.normalAttackCrit!==undefined&&raw.normalAttackCrit<requirements.normalAttackCrit)feasible=false;
    if(requirements.aspd!==null&&requirements.aspd!==undefined&&raw.finalASPD<requirements.aspd)feasible=false;
    return{damage:{expected:raw.optimizationDamageFactor},constraints:{feasible:feasible}};
  }
  var api=Object.freeze({schema:SCHEMA,createBuildSnapshot:createBuildSnapshot,createScenarioSnapshot:createScenarioSnapshot,defaultRequirements:defaultRequirements,evaluate:evaluate,evaluateAggregate:evaluateAggregate,evaluateAggregateSummary:evaluateAggregateSummary,stableStringify:stableStringify});
  if(typeof module==='object'&&module.exports)module.exports=api;if(root)root.ToramBuildEvaluator=api;
}(typeof window!=='undefined'?window:globalThis));
