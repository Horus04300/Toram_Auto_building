(function(root){
  'use strict';
  var SCHEMA='toram.d4-dynamic-seed-pool.v1';
  var POLICY_VERSION='d4-multi-seed-pool.v1';
  var EPSILON=1e-12;
  function number(value){var parsed=Number(value);return Number.isFinite(parsed)?parsed:0;}
  function stable(value){if(value===null||typeof value!=='object')return JSON.stringify(value);if(Array.isArray(value))return '['+value.map(stable).join(',')+']';return '{'+Object.keys(value).sort().map(function(key){return JSON.stringify(key)+':'+stable(value[key]);}).join(',')+'}';}
  function hash(text){var state=2166136261;for(var index=0;index<text.length;index++){state^=text.charCodeAt(index);state=Math.imul(state,16777619);}return ('00000000'+(state>>>0).toString(16)).slice(-8);}
  function compareMetric(metric){return function(left,right){var a=number(metric(left)),b=number(metric(right));if(Math.abs(a-b)>EPSILON)return b-a;return String(left.packageId).localeCompare(String(right.packageId));};}
  function top(records,metric,limit){return(records||[]).slice().sort(compareMetric(metric)).slice(0,Math.max(0,Number(limit)||0));}
  function utilityCoverage(record,utilities,residuals){return(utilities||[]).reduce(function(total,utilityId){var residual=number(residuals&&residuals[utilityId]);return total+(residual>0?Math.min(1,number(record.residualReduction&&record.residualReduction[utilityId])/residual):0);},0);}
  function topBalanced(records,utilities,residuals,limit){return(records||[]).slice().sort(function(left,right){var a=utilityCoverage(left,utilities,residuals),b=utilityCoverage(right,utilities,residuals);if(Math.abs(a-b)>EPSILON)return b-a;return compareMetric(function(item){return item.damageScore;})(left,right);}).slice(0,Math.max(0,Number(limit)||0));}
  function activeAxes(signature){
    var input=signature||{};var type=String(input.attackType||'PHYS').toUpperCase();var blended=String(input.attackPowerMode||'').toLowerCase()==='sum'||Boolean(input.useHigherRangeDamage);
    var result=['critical','range'];
    if(type!=='MAG'||blended)result.push('physicalAttack');
    if(type!=='PHYS'||blended)result.push('magicAttack');
    if(input.usesUnsheathe)result.push('unsheathe');
    return result.sort();
  }
  function utilityIds(profile){var residual=profile&&profile.baseline&&profile.baseline.residual&&profile.baseline.residual.residual||{};return Object.keys(residual).filter(function(key){return number(residual[key])>0;}).sort();}
  function createDynamicCandidateOrder(profile){
    var marginal=profile||{};
    if(marginal.schema!=='toram.d4-dynamic-marginal.v1')throw new Error('DynamicCandidateOrder requires a DynamicMarginalProfile.');
    var utilities=utilityIds(marginal),residuals=marginal.baseline&&marginal.baseline.residual&&marginal.baseline.residual.residual||{};
    var groups=(marginal.groups||[]).slice().sort(function(left,right){return String(left.groupId).localeCompare(String(right.groupId));}).map(function(group){
      var packageIds=(group.packages||[]).slice().sort(function(left,right){
        var damageLeft=number(left.damageScore),damageRight=number(right.damageScore);if(Math.abs(damageLeft-damageRight)>EPSILON)return damageRight-damageLeft;
        var coverageLeft=utilityCoverage(left,utilities,residuals),coverageRight=utilityCoverage(right,utilities,residuals);if(Math.abs(coverageLeft-coverageRight)>EPSILON)return coverageRight-coverageLeft;
        return String(left.packageId).localeCompare(String(right.packageId));
      }).map(function(record){return String(record.packageId);});
      return Object.freeze({groupId:String(group.groupId),packageIds:Object.freeze(packageIds)});
    });
    var signature={policyVersion:'d4-dynamic-candidate-order.v1',profileHash:marginal.profileHash,groups:groups.map(function(group){return {groupId:group.groupId,packageIds:group.packageIds};})};
    return Object.freeze({schema:'toram.d4-dynamic-candidate-order.v1',policyVersion:'d4-dynamic-candidate-order.v1',profileHash:marginal.profileHash,orderHash:hash(stable(signature)),activeUtilities:Object.freeze(utilities),groups:Object.freeze(groups)});
  }
  function frontier(records,utilityId){
    var candidates=(records||[]).filter(function(record){return number(record.residualReduction&&record.residualReduction[utilityId])>0;});
    return candidates.filter(function(candidate){
      var utility=number(candidate.residualReduction&&candidate.residualReduction[utilityId]),damage=number(candidate.damageScore);
      return !candidates.some(function(other){if(other===candidate)return false;var otherUtility=number(other.residualReduction&&other.residualReduction[utilityId]),otherDamage=number(other.damageScore);return otherUtility>=utility&&otherDamage>=damage&&(otherUtility>utility+EPSILON||otherDamage>damage+EPSILON);});
    }).sort(function(left,right){var a=number(left.residualReduction&&left.residualReduction[utilityId]),b=number(right.residualReduction&&right.residualReduction[utilityId]);if(Math.abs(a-b)>EPSILON)return b-a;return compareMetric(function(item){return item.damageScore;})(left,right);});
  }
  function frontierLandmarks(records,utilityId){
    var items=frontier(records,utilityId);if(!items.length)return[];
    var maxUtility=items.slice().sort(compareMetric(function(item){return item.residualReduction&&item.residualReduction[utilityId];}))[0];
    var maxDamage=items.slice().sort(compareMetric(function(item){return item.damageScore;}))[0];
    var lowUtility=Math.min.apply(null,items.map(function(item){return number(item.residualReduction&&item.residualReduction[utilityId]);}));var highUtility=Math.max.apply(null,items.map(function(item){return number(item.residualReduction&&item.residualReduction[utilityId]);}));
    var lowDamage=Math.min.apply(null,items.map(function(item){return number(item.damageScore);}));var highDamage=Math.max.apply(null,items.map(function(item){return number(item.damageScore);}));
    var knee=items.slice().sort(function(left,right){function balance(item){var u=(number(item.residualReduction&&item.residualReduction[utilityId])-lowUtility)/Math.max(EPSILON,highUtility-lowUtility);var d=(number(item.damageScore)-lowDamage)/Math.max(EPSILON,highDamage-lowDamage);return Math.min(u,d);}var a=balance(left),b=balance(right);if(Math.abs(a-b)>EPSILON)return b-a;return String(left.packageId).localeCompare(String(right.packageId));})[0];
    return [{record:maxUtility,label:'supplyMaximum'},{record:maxDamage,label:'minimumDamageLoss'},{record:knee,label:'frontierKnee'}];
  }
  function createDynamicSeedPool(problem,options){
    var input=problem||{},settings=options||{};var marginal=settings.profile||(root&&root.ToramD4DynamicMarginal&&root.ToramD4DynamicMarginal.createDynamicMarginalProfile(input,settings));
    if(!marginal||marginal.schema!=='toram.d4-dynamic-marginal.v1')throw new Error('DynamicSeedPool requires a DynamicMarginalProfile.');
    var perSeedLimit=Math.max(1,Number(settings.perSeedLimit)||4),mergedGroupLimit=Math.max(1,Number(settings.mergedGroupLimit)||32),currentIds=input.metadata&&input.metadata.initialPackageIds||[];
    var profileByGroup=Object.create(null);(marginal.groups||[]).forEach(function(group){profileByGroup[String(group.groupId)]=group;});
    var axes=activeAxes(marginal.scenarioSignature),utilities=utilityIds(marginal),resultGroups=[];
    (input.groups||[]).slice().sort(function(left,right){return String(left.id).localeCompare(String(right.id));}).forEach(function(group){
      var profileGroup=profileByGroup[String(group.id)];if(!profileGroup)throw new Error('DynamicMarginalProfile group is missing: '+group.id);
      var packagesById=Object.create(null);(group.packages||[]).forEach(function(item){packagesById[String(item.id)]=item;});
      var records=(profileGroup.packages||[]).filter(function(record){return Boolean(packagesById[String(record.packageId)]);});
      var selected=Object.create(null),reasons=Object.create(null);
      function add(record,reason,forced){if(!record||!packagesById[String(record.packageId)])return;var id=String(record.packageId);if(!selected[id])selected[id]={record:record,forced:Boolean(forced)};selected[id].forced=selected[id].forced||Boolean(forced);var key=stable(reason);if(!reasons[id])reasons[id]=Object.create(null);reasons[id][key]=reason;}
      var currentId=currentIds[(input.groups||[]).indexOf(group)];if(currentId){var currentRecord=records.find(function(record){return String(record.packageId)===String(currentId);});add(currentRecord,{seed:'current',rank:0,metric:null},true);}
      top(records,function(record){return record.damageScore;},perSeedLimit).forEach(function(record,index){add(record,{seed:'damage',rank:index+1,metric:number(record.damageScore)},false);});
      axes.forEach(function(axis){var applicable=records.filter(function(record){return record.axisMarginals&&record.axisMarginals[axis];});top(applicable,function(record){return record.axisMarginals[axis].damageScore;},perSeedLimit).forEach(function(record,index){add(record,{seed:'axis:'+axis,rank:index+1,metric:number(record.axisMarginals[axis].damageScore)},false);});});
      utilities.forEach(function(utilityId){
        var residual=number(marginal.baseline.residual&&marginal.baseline.residual.residual&&marginal.baseline.residual.residual[utilityId]),supply=records.filter(function(record){return number(record.residualReduction&&record.residualReduction[utilityId])>0;});
        top(supply,function(record){return record.residualReduction&&record.residualReduction[utilityId];},perSeedLimit).forEach(function(record,index){add(record,{seed:'utility:'+utilityId,rank:index+1,metric:number(record.residualReduction&&record.residualReduction[utilityId])},false);});
        frontierLandmarks(records,utilityId).forEach(function(item){add(item.record,{seed:'frontier:'+utilityId+':'+item.label,rank:0,metric:{utility:number(item.record.residualReduction&&item.record.residualReduction[utilityId]),damage:number(item.record.damageScore),residual:residual}},true);});
      });
      topBalanced(records,utilities,marginal.baseline.residual&&marginal.baseline.residual.residual,perSeedLimit).forEach(function(record,index){add(record,{seed:'balanced',rank:index+1,metric:null},false);});
      var chosen=Object.keys(selected).map(function(id){return selected[id];});
      var forced=chosen.filter(function(item){return item.forced;}).sort(compareMetric(function(item){return item.record.damageScore;}));
      var optional=chosen.filter(function(item){return !item.forced;}).sort(compareMetric(function(item){return item.record.damageScore;}));
      var limited=forced.concat(optional.slice(0,Math.max(0,mergedGroupLimit-forced.length))).map(function(item){var id=String(item.record.packageId);return Object.freeze({packageId:id,package:packagesById[id],forced:item.forced,reasons:Object.freeze(Object.keys(reasons[id]||{}).sort().map(function(key){return Object.freeze(reasons[id][key]);}))});});
      resultGroups.push(Object.freeze({groupId:String(group.id),sourcePackageCount:(group.packages||[]).length,poolPackageCount:limited.length,packageIds:Object.freeze(limited.map(function(item){return item.packageId;})),packages:Object.freeze(limited)}));
    });
    var signature={policyVersion:POLICY_VERSION,profileHash:marginal.profileHash,perSeedLimit:perSeedLimit,mergedGroupLimit:mergedGroupLimit,groups:resultGroups.map(function(group){return {groupId:group.groupId,packageIds:group.packageIds,reasons:group.packages.map(function(item){return item.reasons;})};})};
    return Object.freeze({schema:SCHEMA,policyVersion:POLICY_VERSION,profileHash:marginal.profileHash,poolHash:hash(stable(signature)),scenarioSignature:marginal.scenarioSignature,perSeedLimit:perSeedLimit,mergedGroupLimit:mergedGroupLimit,activeAxes:Object.freeze(axes),activeUtilities:Object.freeze(utilities),groups:Object.freeze(resultGroups)});
  }
  function addStats(left,right){var result=Object.assign({},left||{});Object.keys(right||{}).forEach(function(key){result[key]=number(result[key])+number(right[key]);});return result;}
  function buildId(selections){return(selections||[]).map(function(item){return String(item&&item.id||'');}).join('||');}
  function outcomeScore(outcome){var score=number(outcome&&outcome.damage&&outcome.damage.expected);return score>0?score:-Infinity;}
  function isFeasible(outcome){return Boolean(outcome&&outcome.constraints&&outcome.constraints.feasible);}
  function makeEvaluate(problem,settings){
    if(typeof settings.evaluateStats==='function')return settings.evaluateStats;
    var evaluator=settings.evaluator||(root&&root.ToramBuildEvaluator),kernel=settings.kernel||(root&&root.ToramCalculationKernel&&root.ToramCalculationKernel.evaluateContext);
    if(!evaluator||typeof evaluator.evaluateAggregate!=='function'||typeof kernel!=='function')throw new Error('DynamicSeedBuilds requires evaluateStats or BuildEvaluator aggregate dependencies.');
    var context=problem&&problem.baseContext||{},scenario=problem&&problem.scenarioSnapshot;
    if(!scenario&&typeof evaluator.createScenarioSnapshot==='function')scenario=evaluator.createScenarioSnapshot(context);
    return function(stats,metadata){return evaluator.evaluateAggregate(context,scenario,stats||{},kernel,metadata);};
  }
  function residual(outcome,requirements,sourceProfile,metadata){
    if(sourceProfile&&typeof sourceProfile.residualRequirements==='function')return sourceProfile.residualRequirements(outcome,requirements,{metadata:metadata||{}});
    var utility=outcome&&outcome.utility||{},offense=outcome&&outcome.offense||{},actual={maxHp:number(utility.maxHp),maxMp:number(utility.maxMpBeforeBuff),amprBeforeDual:number(utility.amprBeforeDual),normalAttackCrit:number(offense.normalAttackCrit),aspd:number(utility.aspd)},value={};
    Object.keys(actual).forEach(function(key){value[key]=requirements[key]===null||requirements[key]===undefined?0:Math.max(0,number(requirements[key])-actual[key]);});
    return {residual:value};
  }
  function buildRecord(selections,outcome,requirements,sourceProfile,metadata,origin){
    var stats=(selections||[]).reduce(function(total,item){return addStats(total,item&&item.statDelta);},{});var residuals=residual(outcome,requirements,sourceProfile,metadata);
    return Object.freeze({id:buildId(selections),selections:Object.freeze((selections||[]).slice()),statDelta:Object.freeze(stats),outcome:outcome,score:outcomeScore(outcome),feasible:isFeasible(outcome),residuals:residuals,origin:origin||'seed'});
  }
  function compareBuild(left,right){if(Math.abs(number(left.score)-number(right.score))>EPSILON)return number(right.score)-number(left.score);return String(left.id).localeCompare(String(right.id));}
  function compareResidual(left,right){function total(item){return Object.keys(item&&item.residuals&&item.residuals.residual||{}).reduce(function(sum,key){return sum+number(item.residuals.residual[key]);},0);}var a=total(left),b=total(right);if(Math.abs(a-b)>EPSILON)return a-b;return compareBuild(left,right);}
  function createDynamicSeedBuilds(problem,options){
    var input=problem||{},settings=options||{},dynamic=settings.dynamicMarginal||root&&root.ToramD4DynamicMarginal;
    if(!dynamic||typeof dynamic.createDynamicMarginalProfile!=='function')throw new Error('DynamicSeedBuilds requires DynamicMarginalProfile support.');
    var profile=settings.profile||dynamic.createDynamicMarginalProfile(input,settings),pool=settings.pool||createDynamicSeedPool(input,Object.assign({},settings,{profile:profile})),evaluate=makeEvaluate(input,settings);
    var sourceProfile=settings.sourceProfile||(root&&root.ToramD4SourceProfile),requirements=input.scenarioSnapshot&&input.scenarioSnapshot.requirements||{},metadata=input.scenarioSnapshot&&input.scenarioSnapshot.metadata||{};
    var timeLimit=Number(settings.seedTimeLimitMs)>0?Number(settings.seedTimeLimitMs):Infinity,evaluationLimit=Number(settings.seedEvaluationLimit)>0?Number(settings.seedEvaluationLimit):Infinity,beamWidth=Math.max(1,Number(settings.beamWidth)||64),cartesianLimit=Math.max(1,Number(settings.cartesianLimit)||65536),repairInputLimit=Math.max(0,Number(settings.repairInputLimit)||8),repairPerGroupLimit=Math.max(1,Number(settings.repairPerGroupLimit)||6),repairPairLimit=Math.max(1,Number(settings.repairPairLimit)||4),start=Date.now(),evaluations=0,repairEvaluations=0,repairAttemptIds=[],stoppedBy=null,records=[],recordById=Object.create(null);
    var poolByGroup=Object.create(null);(pool.groups||[]).forEach(function(group){poolByGroup[String(group.groupId)]=group;});
    var groups=(input.groups||[]).map(function(group){var poolGroup=poolByGroup[String(group.id)];if(!poolGroup||!poolGroup.packages||!poolGroup.packages.length)throw new Error('DynamicSeedPool group is missing or empty: '+group.id);return {id:String(group.id),packages:poolGroup.packages.map(function(entry){return entry.package;}),entries:poolGroup.packages};});
    function stop(){if(stoppedBy)return true;if(typeof settings.shouldCancel==='function'&&settings.shouldCancel()){stoppedBy='cancelled';return true;}if(evaluations>=evaluationLimit){stoppedBy='evaluationLimit';return true;}if(Date.now()-start>=timeLimit){stoppedBy='timeLimit';return true;}return false;}
    function assess(selections,origin,isRepair){if(stop())return null;var stats=(selections||[]).reduce(function(total,item){return addStats(total,item&&item.statDelta);},{});evaluations++;if(isRepair)repairEvaluations++;var outcome=evaluate(stats,{dynamicSeed:true,origin:origin||'seed',complete:(selections||[]).length===groups.length});var record=buildRecord(selections,outcome,requirements,sourceProfile,metadata,origin);if(isRepair)repairAttemptIds.push(record.id);if(!recordById[record.id]){recordById[record.id]=record;records.push(record);}return record;}
    function poolProduct(){return groups.reduce(function(total,group){return total*group.packages.length;},1);}
    function enumerate(index,selections){if(stop())return;if(index===groups.length){assess(selections,'cartesian',false);return;}groups[index].packages.forEach(function(item){if(!stop())enumerate(index+1,selections.concat([item]));});}
    function takeUnion(primary,secondary,limit){var seen=Object.create(null),result=[];function add(state){if(!state||seen[state.id])return;seen[state.id]=true;result.push(state);}primary.forEach(add);secondary.forEach(add);return result.slice(0,limit);}
    function beam(){var states=[{id:'',selections:[],stats:{},record:null}];for(var index=0;index<groups.length&&!stop();index++){var expanded=[];states.forEach(function(state){groups[index].packages.forEach(function(item){if(stop())return;var selections=state.selections.concat([item]),record=assess(selections,'beamPartial',false);if(record)expanded.push({id:record.id,selections:selections,stats:record.statDelta,record:record});});});if(index===groups.length-1){states=expanded;break;}var damage=expanded.slice().sort(function(left,right){return compareBuild(left.record,right.record);}),utility=expanded.slice().sort(function(left,right){return compareResidual(left.record,right.record);});var half=Math.max(1,Math.floor(beamWidth/2));states=takeUnion(damage.slice(0,half),utility.slice(0,beamWidth-half),beamWidth);}
    }
    var product=poolProduct(),mode=product<=cartesianLimit?'cartesian':'beam';
    if(mode==='cartesian')enumerate(0,[]);else beam();
    var completed=records.filter(function(record){return record.selections.length===groups.length;});
    function repairAlternatives(groupIndex,current,residuals){
      var profileGroup=(profile.groups||[]).find(function(group){return String(group.groupId)===groups[groupIndex].id;});var currentId=current.selections[groupIndex]&&current.selections[groupIndex].id,byId=Object.create(null);(profileGroup&&profileGroup.packages||[]).forEach(function(record){byId[String(record.packageId)]=record;});
      return groups[groupIndex].packages.filter(function(item){return String(item.id)!==String(currentId);}).sort(function(left,right){function supply(item){var record=byId[String(item.id)]||{};return Object.keys(residuals&&residuals.residual||{}).reduce(function(total,key){var need=number(residuals.residual[key]);return total+(need>0?Math.min(1,number(record.residualReduction&&record.residualReduction[key])/need):0);},0);}var a=supply(left),b=supply(right);if(Math.abs(a-b)>EPSILON)return b-a;var da=number((byId[String(left.id)]||{}).damageScore),db=number((byId[String(right.id)]||{}).damageScore);if(Math.abs(da-db)>EPSILON)return db-da;return String(left.id).localeCompare(String(right.id));}).slice(0,repairPerGroupLimit);
    }
    var repairSources=completed.filter(function(record){return !record.feasible;}).sort(compareBuild).slice(0,repairInputLimit);
    repairSources.forEach(function(source){if(stop())return;var alternatives=groups.map(function(group,index){return repairAlternatives(index,source,source.residuals);});for(var index=0;index<groups.length&&!stop();index++){alternatives[index].forEach(function(item){if(stop())return;var selections=source.selections.slice();selections[index]=item;assess(selections,'repair:one:'+groups[index].id,true);});}
      if(records.some(function(record){return record.origin.indexOf('repair:')===0&&record.feasible;}))return;
      for(var left=0;left<groups.length&&!stop();left++)for(var right=left+1;right<groups.length&&!stop();right++){var leftItems=alternatives[left].slice(0,repairPairLimit),rightItems=alternatives[right].slice(0,repairPairLimit);leftItems.forEach(function(leftItem){rightItems.forEach(function(rightItem){if(stop())return;var selections=source.selections.slice();selections[left]=leftItem;selections[right]=rightItem;assess(selections,'repair:pair:'+groups[left].id+'+'+groups[right].id,true);});});}
    });
    var complete=records.filter(function(record){return record.selections.length===groups.length;}).sort(compareBuild),feasible=complete.filter(function(record){return record.feasible;});
    return Object.freeze({schema:'toram.d4-dynamic-seed-builds.v1',policyVersion:'d4-dynamic-seed-builds.v1',profileHash:profile.profileHash,poolHash:pool.poolHash,mode:mode,sourcePoolProduct:product,seedTimeLimitMs:timeLimit===Infinity?null:timeLimit,seedEvaluationLimit:evaluationLimit===Infinity?null:evaluationLimit,elapsedMs:Date.now()-start,evaluations:evaluations,repairEvaluations:repairEvaluations,repairAttemptIds:Object.freeze(repairAttemptIds.slice()),stoppedBy:stoppedBy,completeCandidates:Object.freeze(complete),feasibleCandidates:Object.freeze(feasible),best:feasible.length?feasible[0]:null});
  }
  function improveDynamicSeedBuilds(problem,options){
    var input=problem||{},settings=options||{},seedBuilds=settings.seedBuilds;
    if(!seedBuilds||!Array.isArray(seedBuilds.feasibleCandidates))throw new Error('DynamicSeedLocalImprove requires feasible S3 seed builds.');
    var pool=settings.pool;if(!pool||!Array.isArray(pool.groups))throw new Error('DynamicSeedLocalImprove requires the S2 pool.');
    var evaluate=makeEvaluate(input,settings),sourceProfile=settings.sourceProfile||(root&&root.ToramD4SourceProfile),requirements=input.scenarioSnapshot&&input.scenarioSnapshot.requirements||{},metadata=input.scenarioSnapshot&&input.scenarioSnapshot.metadata||{},profile=settings.profile||null;
    var startLimit=Math.max(1,Number(settings.localStartLimit)||4),passLimit=Math.max(0,Number(settings.localPassLimit)||2),candidateLimit=Math.max(1,Number(settings.localCandidateLimit)||8),pairLimit=Math.max(0,Number(settings.localPairCandidateLimit)||3),evaluationLimit=Number(settings.localEvaluationLimit)>0?Number(settings.localEvaluationLimit):Infinity,timeLimit=Number(settings.localTimeLimitMs)>0?Number(settings.localTimeLimitMs):Infinity,start=Date.now(),evaluations=0,stoppedBy=null,paths=[],candidatesById=Object.create(null);
    var poolByGroup=Object.create(null);(pool.groups||[]).forEach(function(group){poolByGroup[String(group.groupId)]=group;});
    var profileByGroup=Object.create(null);(profile&&profile.groups||[]).forEach(function(group){profileByGroup[String(group.groupId)]=group;});
    var groups=(input.groups||[]).map(function(group){
      var poolGroup=poolByGroup[String(group.id)];if(!poolGroup||!poolGroup.packages||!poolGroup.packages.length)throw new Error('DynamicSeedPool group is missing or empty: '+group.id);
      var profileItems=Object.create(null);(profileByGroup[String(group.id)]&&profileByGroup[String(group.id)].packages||[]).forEach(function(item){profileItems[String(item.packageId)]=item;});
      return {id:String(group.id),packages:poolGroup.packages.map(function(entry){return entry.package;}).slice().sort(function(left,right){var a=number((profileItems[String(left.id)]||{}).damageScore),b=number((profileItems[String(right.id)]||{}).damageScore);if(Math.abs(a-b)>EPSILON)return b-a;return String(left.id).localeCompare(String(right.id));})};
    });
    function stop(){if(stoppedBy)return true;if(typeof settings.shouldCancel==='function'&&settings.shouldCancel()){stoppedBy='cancelled';return true;}if(evaluations>=evaluationLimit){stoppedBy='evaluationLimit';return true;}if(Date.now()-start>=timeLimit){stoppedBy='timeLimit';return true;}return false;}
    function assess(selections,origin){if(stop())return null;var stats=(selections||[]).reduce(function(total,item){return addStats(total,item&&item.statDelta);},{});evaluations++;var outcome=evaluate(stats,{dynamicSeed:true,origin:origin||'local',complete:true,localImprove:true});return buildRecord(selections,outcome,requirements,sourceProfile,metadata,origin);}
    function isBetter(left,right){return Boolean(left&&left.feasible)&&(!right||!right.feasible||compareBuild(left,right)<0);}
    var initial=seedBuilds.feasibleCandidates.slice().sort(compareBuild);initial.forEach(function(item){candidatesById[item.id]=item;});var startLower=initial.length?initial[0].score:null,best=initial.length?initial[0]:null;
    initial.slice(0,startLimit).forEach(function(seed,index){
      if(stop())return;var current=seed,steps=[];for(var pass=0;pass<passLimit&&!stop();pass++){var changed=false;
        for(var groupIndex=0;groupIndex<groups.length&&!stop();groupIndex++){var alternatives=groups[groupIndex].packages.filter(function(item){return String(item.id)!==String(current.selections[groupIndex].id);}).slice(0,candidateLimit);alternatives.forEach(function(item){if(stop())return;var selections=current.selections.slice();selections[groupIndex]=item;var trial=assess(selections,'local:single:'+groups[groupIndex].id);if(trial){candidatesById[trial.id]=trial;if(isBetter(trial,current)){steps.push(Object.freeze({kind:'single',pass:pass,groupId:groups[groupIndex].id,fromId:current.id,toId:trial.id,score:trial.score}));current=trial;changed=true;}}});}
        if(!changed&&pairLimit>0){for(var left=0;left<groups.length&&!stop();left++)for(var right=left+1;right<groups.length&&!stop();right++){var leftItems=groups[left].packages.filter(function(item){return String(item.id)!==String(current.selections[left].id);}).slice(0,pairLimit),rightItems=groups[right].packages.filter(function(item){return String(item.id)!==String(current.selections[right].id);}).slice(0,pairLimit);leftItems.forEach(function(leftItem){rightItems.forEach(function(rightItem){if(stop())return;var selections=current.selections.slice();selections[left]=leftItem;selections[right]=rightItem;var trial=assess(selections,'local:pair:'+groups[left].id+'+'+groups[right].id);if(trial){candidatesById[trial.id]=trial;if(isBetter(trial,current)){steps.push(Object.freeze({kind:'pair',pass:pass,groupIds:Object.freeze([groups[left].id,groups[right].id]),fromId:current.id,toId:trial.id,score:trial.score}));current=trial;changed=true;}}});});}}
        if(!changed)break;
      }if(isBetter(current,best))best=current;paths.push(Object.freeze({seedIndex:index,startId:seed.id,endId:current.id,startScore:seed.score,endScore:current.score,steps:Object.freeze(steps)}));
    });
    var candidates=Object.keys(candidatesById).map(function(id){return candidatesById[id];}).filter(function(item){return item&&item.feasible;}).sort(compareBuild);if(candidates.length&&isBetter(candidates[0],best))best=candidates[0];
    return Object.freeze({schema:'toram.d4-dynamic-local-improve.v1',policyVersion:'d4-dynamic-local-improve.v1',profileHash:profile&&profile.profileHash||null,poolHash:pool.poolHash||null,elapsedMs:Date.now()-start,evaluations:evaluations,stoppedBy:stoppedBy,startLowerBound:startLower,endLowerBound:best&&best.score||null,best:best,paths:Object.freeze(paths),feasibleCandidates:Object.freeze(candidates)});
  }
  var api=Object.freeze({schema:SCHEMA,policyVersion:POLICY_VERSION,createDynamicCandidateOrder:createDynamicCandidateOrder,createDynamicSeedPool:createDynamicSeedPool,createDynamicSeedBuilds:createDynamicSeedBuilds,improveDynamicSeedBuilds:improveDynamicSeedBuilds,activeAxes:activeAxes,frontier:frontier});
  if(typeof module==='object'&&module.exports)module.exports=api;if(root)root.ToramD4DynamicSeed=api;
}(typeof window!=='undefined'?window:globalThis));
