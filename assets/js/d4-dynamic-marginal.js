(function (root) {
  'use strict';
  var SCHEMA='toram.d4-dynamic-marginal.v1';
  var POLICY_VERSION='d4-dynamic-marginal.v1';
  var AXES=Object.freeze(['physicalAttack','magicAttack','range','critical','unsheathe','other']);
  var UTILITY_KEYS=Object.freeze(['maxHp','maxMpBeforeBuff','maxMpAfterBuff','baseAmpr','amprBeforeDual','finalAmpr','aspd','motionSpeed','cspd','castReduction']);
  var OFFENSE_KEYS=Object.freeze(['atk','matk','criticalDamage','selectedAttackCritical','normalAttackCrit','stability','physicalPierce','magicPierce']);
  function number(value){var parsed=Number(value);return Number.isFinite(parsed)?parsed:0;}
  function clone(value){return JSON.parse(JSON.stringify(value));}
  function stable(value){
    if(value===null||typeof value!=='object')return JSON.stringify(value);
    if(Array.isArray(value))return '['+value.map(stable).join(',')+']';
    return '{'+Object.keys(value).sort().map(function(key){return JSON.stringify(key)+':'+stable(value[key]);}).join(',')+'}';
  }
  function hash(text){var state=2166136261;for(var index=0;index<text.length;index++){state^=text.charCodeAt(index);state=Math.imul(state,16777619);}return ('00000000'+(state>>>0).toString(16)).slice(-8);}
  function addStats(left,right){var result=Object.assign({},left||{});Object.keys(right||{}).forEach(function(key){result[key]=number(result[key])+number(right[key]);});return result;}
  function outcomeSummary(outcome){
    var item=outcome||{};var damage=item.damage||{};var offense=item.offense||{};var utility=item.utility||{};var constraints=item.constraints||{};
    var result={damage:{base:number(damage.base),triggered:number(damage.triggered),expected:number(damage.expected)},offense:{},utility:{},constraints:{feasible:Boolean(constraints.feasible),violations:clone(constraints.violations||[])}};
    OFFENSE_KEYS.forEach(function(key){result.offense[key]=offense[key]===undefined?null:offense[key];});
    UTILITY_KEYS.forEach(function(key){result.utility[key]=utility[key]===undefined?null:utility[key];});
    return Object.freeze(result);
  }
  function outcomeDelta(before,after){
    var left=outcomeSummary(before);var right=outcomeSummary(after);var result={damageExpected:number(right.damage.expected)-number(left.damage.expected),offense:{},utility:{}};
    OFFENSE_KEYS.forEach(function(key){result.offense[key]=number(right.offense[key])-number(left.offense[key]);});
    UTILITY_KEYS.forEach(function(key){result.utility[key]=number(right.utility[key])-number(left.utility[key]);});
    return Object.freeze({damageExpected:result.damageExpected,offense:Object.freeze(result.offense),utility:Object.freeze(result.utility)});
  }
  function damageScore(before,after){var left=number(before&&before.damage&&before.damage.expected);var right=number(after&&after.damage&&after.damage.expected);return left>0&&right>0?100*Math.log(right/left):null;}
  function statAxis(key){
    var value=String(key||'').toUpperCase();
    if(value==='SRW'||value==='LRW')return 'range';
    if(value==='UNSHEATHE'||value==='UNSHEATHEP')return 'unsheathe';
    if(value==='CRIT'||value==='CRITP'||value==='CRIT_P'||value==='CDMG'||value==='CDMGP'||value==='CDMG_P')return 'critical';
    if(value==='MATK'||value==='MATKP'||value==='MAG_PIERCE'||value.indexOf('MATK_UP_')===0||value==='INT'||value==='INTP')return 'magicAttack';
    if(value==='ATK'||value==='ATKP'||value==='WATK'||value==='WATKP'||value==='PHYS_PIERCE'||value.indexOf('ATK_UP_')===0||value==='STR'||value==='STRP'||value==='DEX'||value==='DEXP'||value==='AGI'||value==='AGIP')return 'physicalAttack';
    return 'other';
  }
  function axisStats(stats,axis){var result={};Object.keys(stats||{}).sort().forEach(function(key){if(statAxis(key)===axis)result[key]=number(stats[key]);});return result;}
  function scenarioSignature(problem,baseStats){
    var context=problem&&problem.baseContext||{};var scenario=problem&&problem.scenarioSnapshot||{};var requirements=scenario.requirements||{};
    var conversions=(context.activeBuildConversions||[]).map(function(item){return clone(item);}).sort(function(left,right){return stable(left).localeCompare(stable(right));});
    var value={
      evaluatorSchema:scenario.schema||null,evaluatorScenarioHash:scenario.hash||null,basisName:scenario.basisName||context.optimizationBasisName||null,
      attackType:context.atkType||null,rangeType:context.rangeType||null,
      usesUnsheathe:Boolean(context.chkIsUnsheathe)||(conversions.some(function(item){return item&&item.conversion==='unsheatheToAtk';})),
      attackPowerMode:context.attackPowerMode||null,useHigherRangeDamage:Boolean(context.useHigherRangeDamage),
      bossDef:number(context.bossDef),bossMdef:number(context.bossMdef),
      physicalPierce:number(context.physPierce)+number(context.physicalPierceSkillBonus),
      magicPierce:number(context.magPierce)+number(context.magicPierceSkillBonus),
      noCritical:Boolean(context.noCritical),guaranteedCritical:Boolean(context.chkGuaranteedCrit),
      fixedCriticalChance:context.fixedCriticalChance===undefined?null:context.fixedCriticalChance,
      criticalChanceBonus:number(context.criticalChanceBonus),criticalChanceMultiplier:number(context.criticalChanceMultiplier),minimumCriticalDamage:number(context.minimumCriticalDamage),
      requirements:clone(requirements),activeBuildConversions:conversions,baseStats:clone(baseStats||{})
    };
    value.hash=hash(stable(value));return Object.freeze(value);
  }
  function makeEvaluate(problem,settings){
    if(typeof settings.evaluateStats==='function')return settings.evaluateStats;
    var evaluator=settings.evaluator||(root&&root.ToramBuildEvaluator);var kernel=settings.kernel||(root&&root.ToramCalculationKernel&&root.ToramCalculationKernel.evaluateContext);
    if(!evaluator||typeof evaluator.evaluateAggregate!=='function')throw new Error('DynamicMarginal requires BuildEvaluator.evaluateAggregate or evaluateStats.');
    if(typeof kernel!=='function')throw new Error('DynamicMarginal requires calculator kernel or evaluateStats.');
    var context=problem&&problem.baseContext||{};var scenario=problem&&problem.scenarioSnapshot;
    if(!scenario&&typeof evaluator.createScenarioSnapshot==='function')scenario=evaluator.createScenarioSnapshot(context);
    return function(stats){return evaluator.evaluateAggregate(context,scenario,stats||{},kernel);};
  }
  function residual(outcome,requirements,sourceProfile,metadata){
    if(sourceProfile&&typeof sourceProfile.residualRequirements==='function')return sourceProfile.residualRequirements(outcome,requirements,{metadata:metadata||{}});
    var utility=outcome&&outcome.utility||{};var offense=outcome&&outcome.offense||{};var actual={maxHp:number(utility.maxHp),maxMp:number(utility.maxMpBeforeBuff),amprBeforeDual:number(utility.amprBeforeDual),normalAttackCrit:number(offense.normalAttackCrit),aspd:number(utility.aspd)};var value={};
    Object.keys(actual).forEach(function(key){value[key]=requirements[key]===null||requirements[key]===undefined?0:Math.max(0,number(requirements[key])-actual[key]);});
    return Object.freeze({actual:Object.freeze(actual),required:Object.freeze(clone(requirements)),residual:Object.freeze(value),dependencies:Object.freeze({})});
  }
  function residualReduction(before,after){var result={};var left=before&&before.residual||{};var right=after&&after.residual||{};Object.keys(left).sort().forEach(function(key){result[key]=number(left[key])-number(right[key]);});return Object.freeze(result);}
  function makeAxisMarginals(baseStats,stats,baselineOutcome,evaluate){
    var result={};AXES.forEach(function(axis){var delta=axisStats(stats,axis);if(!Object.keys(delta).length)return;var after=evaluate(addStats(baseStats,delta));result[axis]=Object.freeze({statDelta:Object.freeze(delta),damageScore:damageScore(baselineOutcome,after),outcome:outcomeSummary(after),outcomeDelta:outcomeDelta(baselineOutcome,after)});});return Object.freeze(result);
  }
  function packageRecord(group,item,baseStats,baselineOutcome,baselineResidual,evaluate,requirements,sourceProfile,metadata){
    var stats=Object.assign({},item&&item.statDelta||{});var after=evaluate(addStats(baseStats,stats));var afterResidual=residual(after,requirements,sourceProfile,metadata);
    return Object.freeze({groupId:String(group&&group.id||''),packageId:String(item&&item.id||''),statDelta:Object.freeze(stats),damageScore:damageScore(baselineOutcome,after),outcome:outcomeSummary(after),outcomeDelta:outcomeDelta(baselineOutcome,after),residualReduction:residualReduction(baselineResidual,afterResidual),residualAfter:afterResidual,axisMarginals:makeAxisMarginals(baseStats,stats,baselineOutcome,evaluate)});
  }
  function createDynamicMarginalProfile(problem,options){
    var input=problem||{};var settings=options||{};var baseStats=Object.assign({},settings.baseStats||{});var evaluate=makeEvaluate(input,settings);
    var requirements=(input.scenarioSnapshot&&input.scenarioSnapshot.requirements)||{};var metadata=input.scenarioSnapshot&&input.scenarioSnapshot.metadata||{};var sourceProfile=settings.sourceProfile||(root&&root.ToramD4SourceProfile);var evaluations=0;
    function measured(stats){evaluations++;return evaluate(stats);}
    var baselineOutcome=measured(baseStats);var baselineResidual=residual(baselineOutcome,requirements,sourceProfile,metadata);
    var groups=(input.groups||[]).slice().sort(function(left,right){return String(left&&left.id||'').localeCompare(String(right&&right.id||''));}).map(function(group){
      var packages=(group&&group.packages||[]).slice().sort(function(left,right){var a=String(left&&left.id||'');var b=String(right&&right.id||'');return a===b?stable(left&&left.statDelta||{}).localeCompare(stable(right&&right.statDelta||{})):a.localeCompare(b);}).map(function(item){return packageRecord(group,item,baseStats,baselineOutcome,baselineResidual,measured,requirements,sourceProfile,metadata);});
      return Object.freeze({groupId:String(group&&group.id||''),packages:Object.freeze(packages)});
    });
    var signature=scenarioSignature(input,baseStats);var inputSignature={policyVersion:POLICY_VERSION,scenario:signature,groups:groups.map(function(group){return {groupId:group.groupId,packages:group.packages.map(function(item){return {packageId:item.packageId,statDelta:item.statDelta};})};})};
    return Object.freeze({schema:SCHEMA,policyVersion:POLICY_VERSION,profileHash:hash(stable(inputSignature)),scenarioSignature:signature,evaluationCount:evaluations,baseline:Object.freeze({stats:Object.freeze(baseStats),outcome:outcomeSummary(baselineOutcome),residual:baselineResidual}),groups:Object.freeze(groups)});
  }
  var api=Object.freeze({schema:SCHEMA,policyVersion:POLICY_VERSION,axes:AXES,createDynamicMarginalProfile:createDynamicMarginalProfile,outcomeSummary:outcomeSummary,scenarioSignature:scenarioSignature});
  if(typeof module==='object'&&module.exports)module.exports=api;if(root)root.ToramD4DynamicMarginal=api;
}(typeof window!=='undefined'?window:globalThis));
