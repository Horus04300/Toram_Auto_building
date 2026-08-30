(function (root) {
  'use strict';
  var SCHEMA = 'toram.d4-source-profile.v1';
  function number(value) { var parsed=Number(value); return Number.isFinite(parsed) ? parsed : 0; }
  function createSourceProfile(input) {
    var item=input||{};
    return Object.freeze({
      schema:SCHEMA,
      sourceId:String(item.sourceId||''),
      sourceType:String(item.sourceType||'equipment'),
      competesForSlot:Boolean(item.competesForSlot),
      slotGroup:item.slotGroup===undefined?null:String(item.slotGroup),
      resolvedContributions:Object.freeze(Object.assign({},item.resolvedContributions||{})),
      structureConditionMetadata:Object.freeze(Object.assign({},item.structureConditionMetadata||{})),
      availability:item.availability!==false
    });
  }
  var UTILITY_DEPENDENCY_POLICY_VERSION='d4-utility-dependency.v1';
  var SUPPLY_DIFFICULTY_POLICY_VERSION='d4-supply-difficulty.v1';
  var UTILITY_DEPENDENCY_DEFINITIONS=Object.freeze({
    maxHp:Object.freeze({requirement:'maxHp',statKeys:Object.freeze(['MAXHP','MAXHPP']),objectiveDependent:false,derivedDependencies:Object.freeze([]),potentialConditionDependencies:Object.freeze(['maxHpProportionalDamage'])}),
    maxMp:Object.freeze({requirement:'maxMp',statKeys:Object.freeze(['MAXMP']),objectiveDependent:false,derivedDependencies:Object.freeze(['amprBeforeDual']),potentialConditionDependencies:Object.freeze(['maxMpProportionalDamage'])}),
    amprBeforeDual:Object.freeze({requirement:'amprBeforeDual',statKeys:Object.freeze(['AMPR','AMPRP','MAXMP']),objectiveDependent:false,derivedDependencies:Object.freeze(['finalAmpr']),potentialConditionDependencies:Object.freeze(['normalAttackAmprActiveSelection','dualSwordAmprMultiplier'])}),
    normalAttackCrit:Object.freeze({requirement:'normalAttackCrit',statKeys:Object.freeze(['CRIT','CRIT_P','CRITP']),objectiveDependent:true,derivedDependencies:Object.freeze([]),potentialConditionDependencies:Object.freeze(['guaranteedCritical','criticalCap'])}),
    aspd:Object.freeze({requirement:'aspd',statKeys:Object.freeze(['ASPD','ASPD_P']),objectiveDependent:false,derivedDependencies:Object.freeze(['motionSpeed']),potentialConditionDependencies:Object.freeze(['actionSpeedObjective'])}),
    motionSpeed:Object.freeze({requirement:null,statKeys:Object.freeze(['MOTIONSPEED','ASPD','ASPD_P']),objectiveDependent:false,derivedDependencies:Object.freeze([]),potentialConditionDependencies:Object.freeze(['actionSpeedObjective'])}),
    cspd:Object.freeze({requirement:null,statKeys:Object.freeze(['CSPD','CSPD_P']),objectiveDependent:false,derivedDependencies:Object.freeze([]),potentialConditionDependencies:Object.freeze(['castTimeObjective'])}),
    castReduction:Object.freeze({requirement:null,statKeys:Object.freeze(['CAST_RED','CSPD','CSPD_P']),objectiveDependent:false,derivedDependencies:Object.freeze(['cspd']),potentialConditionDependencies:Object.freeze(['castTimeObjective'])})
  });
  function uniqueStrings(values){var seen=Object.create(null);return(values||[]).map(String).filter(function(value){if(!value||seen[value])return false;seen[value]=true;return true;}).sort();}
  function dependencyOverride(scenario,id){var metadata=scenario&&scenario.metadata||{};var overrides=metadata.utilityDependencyOverrides||{};var value=overrides[id];return value&&typeof value==='object'?value:{};}
  function utilityDependencyMetadata(scenario){
    var input=scenario||{};var requirements=input.requirements||input;var result={};
    Object.keys(UTILITY_DEPENDENCY_DEFINITIONS).forEach(function(id){
      var definition=UTILITY_DEPENDENCY_DEFINITIONS[id];var override=dependencyOverride(input,id);var derived=uniqueStrings(definition.derivedDependencies.concat(override.derivedDependencies||[]));var conditions=uniqueStrings(override.conditionDependencies||[]);var objective=Boolean(definition.objectiveDependent||override.objectiveDependent);var required=definition.requirement!==null&&requirements[definition.requirement]!==null&&requirements[definition.requirement]!==undefined;var constraintOnly=Boolean(required&&!objective&&!derived.length&&!conditions.length);
      result[id]=Object.freeze({id:id,requirement:definition.requirement,statKeys:definition.statKeys,constraintOnly:constraintOnly,objectiveDependent:objective,derivedDependencies:Object.freeze(derived),conditionDependencies:Object.freeze(conditions),potentialConditionDependencies:definition.potentialConditionDependencies,saturationRule:constraintOnly?'cap-to-residual':'preserve-raw',rawRequired:!constraintOnly});
    });
    return Object.freeze(result);
  }
  function capUtilityContribution(profile,contribution,residual){var amount=number(contribution);if(!profile||profile.saturationRule!=='cap-to-residual')return amount;return Math.min(amount,Math.max(0,number(residual)));}
  function residualRequirements(outcome,requirements,options) {
    var utility=outcome&&outcome.utility||{};var offense=outcome&&outcome.offense||{};var req=requirements||{};
    var actual={maxHp:number(utility.maxHp),maxMp:number(utility.maxMpBeforeBuff),amprBeforeDual:number(utility.amprBeforeDual),normalAttackCrit:number(offense.normalAttackCrit),aspd:number(utility.aspd)};
    var residual={};Object.keys(actual).forEach(function(key){var required=req[key];residual[key]=required===null||required===undefined?0:Math.max(0,number(required)-actual[key]);});
    var metadata=utilityDependencyMetadata({requirements:req,metadata:options&&options.metadata||{}});
    return Object.freeze({actual:Object.freeze(actual),required:Object.freeze(Object.assign({},req)),residual:Object.freeze(residual),dependencies:metadata});
  }
  function addStats(left,right){var result=Object.assign({},left||{});Object.keys(right||{}).forEach(function(key){result[key]=(Number(result[key])||0)+(Number(right[key])||0);});return result;}
  function outcomeMetric(outcome,id){var utility=outcome&&outcome.utility||{};var offense=outcome&&outcome.offense||{};var values={maxHp:utility.maxHp,maxMp:utility.maxMpBeforeBuff,amprBeforeDual:utility.amprBeforeDual,normalAttackCrit:offense.normalAttackCrit,aspd:utility.aspd,motionSpeed:utility.motionSpeed,cspd:utility.cspd,castReduction:utility.castReduction};return number(values[id]);}
  function analyzeSupplyDifficulty(problem,evaluateStats,options){
    if(typeof evaluateStats!=='function')throw new Error('SupplyDifficulty requires evaluateStats.');
    var input=problem||{};var scenario=input.scenarioSnapshot||{};var requirements=scenario.requirements||{};var settings=options||{};var baseStats=Object.assign({},settings.baseStats||{});var baseOutcome=evaluateStats(baseStats,{supplyDifficulty:true,baseline:true});var residuals=residualRequirements(baseOutcome,requirements,{metadata:scenario.metadata||{}});var dependencies=residuals.dependencies;
    var ids=Object.keys(dependencies).filter(function(id){var profile=dependencies[id];return profile.requirement!==null&&requirements[profile.requirement]!==null&&requirements[profile.requirement]!==undefined;});
    var rows=[];(input.groups||[]).forEach(function(group){(group.packages||[]).forEach(function(item){var after=evaluateStats(addStats(baseStats,item.statDelta||{}),{supplyDifficulty:true,groupId:group.id,packageId:item.id});var values={};ids.forEach(function(id){values[id]=outcomeMetric(after,id)-outcomeMetric(baseOutcome,id);});rows.push({groupId:String(group.id),packageId:String(item.id),contributions:values,deltaLogDamage:deltaLogDamage(baseOutcome&&baseOutcome.damage&&baseOutcome.damage.expected,after&&after.damage&&after.damage.expected)});});});
    var utilities={};ids.forEach(function(id){var residual=number(residuals.residual[id]);var positive=rows.filter(function(row){return number(row.contributions[id])>0;});var groupMaximums={};positive.forEach(function(row){groupMaximums[row.groupId]=Math.max(number(groupMaximums[row.groupId]),number(row.contributions[id]));});var groupList=Object.keys(groupMaximums).sort().map(function(groupId){return Object.freeze({groupId:groupId,maximum:groupMaximums[groupId]});});var maximumSupply=groupList.reduce(function(total,entry){return total+entry.maximum;},0);var peak=groupList.reduce(function(total,entry){return Math.max(total,entry.maximum);},0);var satisfying=residual>0?positive.filter(function(row){return number(row.contributions[id])>=residual;}):[];var minimumLoss=Infinity;satisfying.forEach(function(row){minimumLoss=Math.min(minimumLoss,Math.max(0,-number(row.deltaLogDamage)));});var dpsOverlap=positive.filter(function(row){return number(row.deltaLogDamage)>0;}).length;var otherOverlap=positive.filter(function(row){return ids.some(function(other){return other!==id&&number(row.contributions[other])>0;});}).length;utilities[id]=Object.freeze({id:id,active:residual>0,residual:residual,supplierCount:positive.length,satisfyingSourceCount:satisfying.length,satisfyingSourceRatio:positive.length?satisfying.length/positive.length:0,groupMaximums:Object.freeze(groupList),maximumSupply:maximumSupply,concentration:maximumSupply?peak/maximumSupply:0,minimumLogDamageLoss:minimumLoss===Infinity?null:minimumLoss,dpsOverlapCount:dpsOverlap,otherUtilityOverlapCount:otherOverlap,feasibleByIndependentGroupMax:maximumSupply>=residual});});
    return Object.freeze({policyVersion:SUPPLY_DIFFICULTY_POLICY_VERSION,measurementMode:'single-package-delta-heuristic',baseline:residuals,utilities:Object.freeze(utilities)});
  }
  function hasOwn(value,key){return Object.prototype.hasOwnProperty.call(value||{},key);}
  function safeResidualDominance(left,right,input){
    var settings=input||{};var reasons=[];var strict=false;var l=left||{},r=right||{};var ls=l.signatures||{},rs=r.signatures||{};
    ['structure','condition','conflict','lineage'].forEach(function(key){if(ls[key]===undefined||rs[key]===undefined||ls[key]!==rs[key])reasons.push('signature:'+key);});
    if(!Number.isFinite(Number(l.slotCost))||!Number.isFinite(Number(r.slotCost))||Number(l.slotCost)>Number(r.slotCost))reasons.push('slotCost');else if(Number(l.slotCost)<Number(r.slotCost))strict=true;
    function compare(keys,leftValues,rightValues,label,transform){(keys||[]).forEach(function(key){if(!hasOwn(leftValues,key)||!hasOwn(rightValues,key)){reasons.push('missing:'+label+':'+key);return;}var a=transform?transform(leftValues[key],key):number(leftValues[key]);var b=transform?transform(rightValues[key],key):number(rightValues[key]);if(a<b)reasons.push(label+':'+key);else if(a>b)strict=true;});}
    if(!Array.isArray(settings.objectiveKeys)||!settings.objectiveKeys.length)reasons.push('missing:objectiveKeys');else compare(settings.objectiveKeys,l.objective,r.objective,'objective');
    var dependencies=settings.dependencies||{};var residual=settings.residual||{};var capped=Object.keys(dependencies).filter(function(key){return dependencies[key]&&dependencies[key].saturationRule==='cap-to-residual';});compare(capped,l.utilityContribution,r.utilityContribution,'cappedUtility',function(value,key){return capUtilityContribution(dependencies[key],value,residual[key]);});
    if(!Array.isArray(settings.rawUtilityKeys))reasons.push('missing:rawUtilityKeys');else compare(settings.rawUtilityKeys,l.rawUtility,r.rawUtility,'rawUtility');
    if(!strict){if(String(l.id||'')<String(r.id||''))strict=true;else reasons.push('tieId');}
    return Object.freeze({proven:reasons.length===0&&strict,reasons:Object.freeze(reasons),leftId:String(l.id||''),rightId:String(r.id||'')});
  }
  function deltaLogDamage(before,after) {
    var left=Math.max(Number.EPSILON,number(before));var right=Math.max(Number.EPSILON,number(after));return Math.log(right/left);
  }
  function attackEquivalentAxis(baseAttack,targetDefense,pierce) {
    var base=Math.max(Number.EPSILON,number(baseAttack));var defense=number(targetDefense);var penetration=number(pierce);
    var effective=base-defense*(1-penetration/100);
    return Object.freeze({effectiveAttack:effective,axisPercentPoint:100*effective/base});
  }
  function pierceEquivalentAttackPercent(baseAttack,targetDefense,deltaPierce) {
    var base=Math.max(Number.EPSILON,number(baseAttack));return number(targetDefense)/base*number(deltaPierce);
  }
  function sourceValue(beforeOutcome,afterOutcome) {
    var beforeDamage=beforeOutcome&&beforeOutcome.damage&&beforeOutcome.damage.expected;var afterDamage=afterOutcome&&afterOutcome.damage&&afterOutcome.damage.expected;
    var beforeUtility=beforeOutcome&&beforeOutcome.utility||{};var afterUtility=afterOutcome&&afterOutcome.utility||{};
    return Object.freeze({
      deltaLogDamage:deltaLogDamage(beforeDamage,afterDamage),
      utilityDelta:Object.freeze({
        maxHp:number(afterUtility.maxHp)-number(beforeUtility.maxHp),
        maxMp:number(afterUtility.maxMpBeforeBuff)-number(beforeUtility.maxMpBeforeBuff),
        amprBeforeDual:number(afterUtility.amprBeforeDual)-number(beforeUtility.amprBeforeDual),
        aspd:number(afterUtility.aspd)-number(beforeUtility.aspd),
        motionSpeed:number(afterUtility.motionSpeed)-number(beforeUtility.motionSpeed)
      })
    });
  }
  var REPLACEMENT_PROOF_POLICY_VERSION='d4-replacement-proof-witness.v1';
  function stable(value){if(value===null||typeof value!=='object')return JSON.stringify(value);if(Array.isArray(value))return '['+value.map(stable).join(',')+']';return '{'+Object.keys(value).sort().map(function(key){return JSON.stringify(key)+':'+stable(value[key]);}).join(',')+'}';}
  function hash(text){var state=2166136261;for(var index=0;index<text.length;index++){state^=text.charCodeAt(index);state=Math.imul(state,16777619);}return ('00000000'+(state>>>0).toString(16)).slice(-8);}
  function uniqueKeys(values){var seen=Object.create(null);return(values||[]).map(String).filter(function(key){if(!key||seen[key])return false;seen[key]=true;return true;}).sort();}
  function packageSignature(group,item,problem){var structure=item&&item.structureSignature||problem&&problem.structure&&problem.structure.signature||'';return Object.freeze({structure:String(structure),condition:stable(item&&item.resolvedConditionMetadata||{}),conflict:stable({groupId:group&&group.id||'',slots:group&&group.slots||[]}),lineage:'package-local-prevalidated.v1:'+String(group&&group.id||'')});}
  function hasSameSignatures(left,right){return ['structure','condition','conflict','lineage'].every(function(key){return left&&right&&left[key]===right[key];});}
  function vector(keys,stats){var result={};(keys||[]).forEach(function(key){result[key]=number(stats&&stats[key]);});return result;}
  function vectorMayDominate(left,right,keys,leftId,rightId){var strict=false;for(var index=0;index<(keys||[]).length;index++){var key=keys[index],a=number(left&&left[key]),b=number(right&&right[key]);if(a<b)return false;if(a>b)strict=true;}return strict||String(leftId||'')<String(rightId||'');}
  function replacementRecord(group,item,baseline,evaluateStats,objectiveKeys,utilityKeys){
    var outcome=evaluateStats(item&&item.statDelta||{},{replacementProof:true,groupId:group&&group.id,packageId:item&&item.id}),raw={},contribution={};
    (utilityKeys||[]).forEach(function(key){raw[key]=outcomeMetric(outcome,key);contribution[key]=number(raw[key])-number(baseline&&baseline.rawUtility&&baseline.rawUtility[key]);});
    return {id:String(item&&item.id||''),groupId:String(group&&group.id||''),item:item,slotCost:number(item&&item.resourceCost&&item.resourceCost.sockets),signatures:packageSignature(group,item),objective:vector(objectiveKeys,item&&item.statDelta),rawUtility:raw,utilityContribution:contribution,outcome:outcome};
  }
  function createReplacementProofReport(problem,evaluateStats,options){
    if(typeof evaluateStats!=='function')throw new Error('ReplacementProof requires evaluateStats.');
    var input=problem||{},settings=options||{},scenario=input.scenarioSnapshot||{},requirements=scenario.requirements||{},baselineOutcome=evaluateStats(settings.baseStats||{},{replacementProof:true,baseline:true}),residuals=residualRequirements(baselineOutcome,requirements,{metadata:scenario.metadata||{}}),dependencies=residuals.dependencies||{};
    var objectiveKeys=uniqueKeys(settings.objectiveKeys&&settings.objectiveKeys.length?settings.objectiveKeys:input.metadata&&input.metadata.modeledKeys&&input.metadata.modeledKeys.length?input.metadata.modeledKeys:(input.groups||[]).reduce(function(keys,group){return keys.concat((group.packages||[]).reduce(function(all,item){return all.concat(Object.keys(item&&item.statDelta||{}));},[]));},[]));
    if(!objectiveKeys.length)throw new Error('ReplacementProof requires objective keys.');
    var rawUtilityKeys=uniqueKeys(settings.rawUtilityKeys||Object.keys(dependencies).filter(function(key){return dependencies[key]&&dependencies[key].rawRequired;})),baseline={rawUtility:{}};rawUtilityKeys.forEach(function(key){baseline.rawUtility[key]=outcomeMetric(baselineOutcome,key);});
    var maxComparisons=Number.isFinite(Number(settings.maxComparisons))&&Number(settings.maxComparisons)>=0?Math.floor(Number(settings.maxComparisons)):5000000,maxWitnesses=Number.isFinite(Number(settings.maxWitnesses))&&Number(settings.maxWitnesses)>=0?Math.floor(Number(settings.maxWitnesses)):1024,comparisons=0,complete=true,certificates=[],unprovenWitnesses=[],groupReports=[];
    var scenarioHash=String(scenario.hash||hash(stable({requirements:requirements,metadata:scenario.metadata||{},structure:input.structure&&input.structure.signature||''}))),proofInput={objectiveKeys:objectiveKeys,dependencies:dependencies,residual:residuals.residual,rawUtilityKeys:rawUtilityKeys};
    (input.groups||[]).forEach(function(group){
      var records=(group.packages||[]).map(function(item){return replacementRecord(group,item,baseline,evaluateStats,objectiveKeys,rawUtilityKeys);}).sort(function(left,right){return left.id.localeCompare(right.id);}),dropped=Object.create(null);
      for(var rightIndex=0;rightIndex<records.length;rightIndex++){
        var removed=records[rightIndex];if(dropped[removed.id])continue;
        for(var leftIndex=0;leftIndex<records.length;leftIndex++){
          var witness=records[leftIndex];if(witness===removed||dropped[witness.id])continue;
          if(witness.slotCost!==removed.slotCost||!hasSameSignatures(witness.signatures,removed.signatures)||!vectorMayDominate(witness.objective,removed.objective,objectiveKeys,witness.id,removed.id))continue;
          if(comparisons>=maxComparisons){complete=false;break;}comparisons++;
          var proof=safeResidualDominance(witness,removed,proofInput);
          if(!proof.proven){if(unprovenWitnesses.length<maxWitnesses)unprovenWitnesses.push(Object.freeze({removedId:removed.id,witnessId:witness.id,groupId:removed.groupId,reasons:proof.reasons}));continue;}
          var payload={ruleId:'d4-package-replacement-dominance.v1',scenarioHash:scenarioHash,removedId:removed.id,witnessIds:[witness.id],coveredSlotGroups:[removed.groupId],preservedSignatures:removed.signatures,objectiveProof:{kind:'componentwise-stat-vector',keys:objectiveKeys,witness:Object.freeze(vector(objectiveKeys,witness.item.statDelta)),removed:Object.freeze(vector(objectiveKeys,removed.item.statDelta))},utilityProof:{dependenciesPolicyVersion:UTILITY_DEPENDENCY_POLICY_VERSION,residual:Object.freeze(Object.assign({},residuals.residual)),witnessContribution:Object.freeze(Object.assign({},witness.utilityContribution)),removedContribution:Object.freeze(Object.assign({},removed.utilityContribution)),witnessRaw:Object.freeze(Object.assign({},witness.rawUtility)),removedRaw:Object.freeze(Object.assign({},removed.rawUtility))},feasibilityProof:{kind:'same-group-prevalidated-package',groupId:removed.groupId,slotCost:removed.slotCost,compilerInvariant:'package-local lineage conflict is resolved before package creation; no cross-group candidate exclusivity exists'},replacementProof:{kind:'sameGroupPackage',witnessId:witness.id,removedId:removed.id,sameSlotCost:true,sameSignatures:true},tieBreakProof:{witnessId:witness.id,removedId:removed.id,deterministicPreference:String(witness.id)<String(removed.id)?'witness-id-earlier':'strict-stat-improvement'},policyVersions:{replacementProof:REPLACEMENT_PROOF_POLICY_VERSION,utilityDependency:UTILITY_DEPENDENCY_POLICY_VERSION,sourceProfile:SCHEMA}};
          certificates.push(Object.freeze(Object.assign({schema:'d4-pruning-certificate.v1',certificateHash:hash(stable(payload))},payload)));dropped[removed.id]=true;break;
        }
        if(!complete)break;
      }
      groupReports.push(Object.freeze({groupId:String(group.id),packageCount:records.length,provenDropCount:Object.keys(dropped).length}));
    });
    var signature={policyVersion:REPLACEMENT_PROOF_POLICY_VERSION,scenarioHash:scenarioHash,objectiveKeys:objectiveKeys,rawUtilityKeys:rawUtilityKeys,certificates:certificates.map(function(item){return item.certificateHash;})};
    return Object.freeze({schema:'toram.d4-replacement-proof-report.v1',policyVersion:REPLACEMENT_PROOF_POLICY_VERSION,scenarioHash:scenarioHash,reportHash:hash(stable(signature)),complete:complete,comparisons:comparisons,objectiveKeys:Object.freeze(objectiveKeys),rawUtilityKeys:Object.freeze(rawUtilityKeys),certificates:Object.freeze(certificates),provenDrops:Object.freeze(certificates.map(function(item){return item.removedId;})),unprovenWitnesses:Object.freeze(unprovenWitnesses),groups:Object.freeze(groupReports)});
  }
  function applyProvenDropsForAudit(problem,report){
    if(!report||report.schema!=='toram.d4-replacement-proof-report.v1')throw new Error('ReplacementProof audit requires a report.');
    var drop=Object.create(null);(report.certificates||[]).forEach(function(certificate){if(certificate&&certificate.schema==='d4-pruning-certificate.v1')drop[String(certificate.removedId)]=true;});
    var groups=(problem&&problem.groups||[]).map(function(group){return Object.freeze(Object.assign({},group,{packages:Object.freeze((group.packages||[]).filter(function(item){return !drop[String(item.id)];}))}));});
    var metadata=Object.assign({},problem&&problem.metadata||{}, {replacementProofAudit:{reportHash:report.reportHash,provenDropCount:Object.keys(drop).length}});
    return Object.freeze(Object.assign({},problem,{groups:Object.freeze(groups),metadata:metadata}));
  }
  var api=Object.freeze({schema:SCHEMA,utilityDependencyPolicyVersion:UTILITY_DEPENDENCY_POLICY_VERSION,supplyDifficultyPolicyVersion:SUPPLY_DIFFICULTY_POLICY_VERSION,replacementProofPolicyVersion:REPLACEMENT_PROOF_POLICY_VERSION,createSourceProfile:createSourceProfile,utilityDependencyMetadata:utilityDependencyMetadata,capUtilityContribution:capUtilityContribution,analyzeSupplyDifficulty:analyzeSupplyDifficulty,safeResidualDominance:safeResidualDominance,createReplacementProofReport:createReplacementProofReport,applyProvenDropsForAudit:applyProvenDropsForAudit,residualRequirements:residualRequirements,deltaLogDamage:deltaLogDamage,attackEquivalentAxis:attackEquivalentAxis,pierceEquivalentAttackPercent:pierceEquivalentAttackPercent,sourceValue:sourceValue});
  if(typeof module==='object'&&module.exports)module.exports=api;if(root)root.ToramD4SourceProfile=api;
}(typeof window!=='undefined'?window:globalThis));
