/* Shared candidate preparation for Rust Native and WASM; no search implementation. */
(function (root) {
  'use strict';

  var EPSILON=1e-9;

  var CANDIDATE_PROJECTION_POLICY='optimization-candidate-projection.v2';


  function clone(value){if(value===null||value===undefined||typeof value!=='object')return value;if(Array.isArray(value))return value.map(clone);var result={};Object.keys(value).forEach(function(key){result[key]=clone(value[key]);});return result;}

  function addStats(left,right){var result=clone(left||{});Object.keys(right||{}).forEach(function(key){result[key]=(Number(result[key])||0)+(Number(right[key])||0);});return result;}


  function modeledKeys(registry){
    if(!registry||typeof registry.entries!=='function')return[];
    return registry.entries().filter(function(entry){return entry.status!=='notModeled'&&entry.target;}).map(function(entry){return entry.id;}).sort();
  }


  function dominates(left,right,keys){
    var strict=false;
    for(var i=0;i<keys.length;i++){
      var key=keys[i];var a=Number(left&&left[key])||0;var b=Number(right&&right[key])||0;
      if(a+EPSILON<b)return false;if(a>b+EPSILON)strict=true;
    }
    return strict;
  }


  // Integer coordinates are already exact; do not round fractional options.
  // For i32 values, EPSILON < 1 makes the original comparisons equivalent to
  // plain integer comparisons. Keep the original path for every other input.
  function integerParetoValues(packages,keys){
    if(packages.length<2||keys.length===0)return null;
    var values=new Int32Array(packages.length*keys.length);
    for(var i=0;i<packages.length;i++){
      var stats=packages[i].statDelta;
      for(var k=0;k<keys.length;k++){
        var value=Number(stats&&stats[keys[k]])||0;
        if(!Number.isInteger(value)||value<-2147483648||value>2147483647)return null;
        values[i*keys.length+k]=value;
      }
    }
    return values;
  }


  function integerDominates(values,leftOffset,rightOffset,width){
    var strict=false;
    for(var k=0;k<width;k++){
      var a=values[leftOffset+k],b=values[rightOffset+k];
      if(a<b)return false;if(a>b)strict=true;
    }
    return strict;
  }


  function strictParetoFrontier(packages,keys,options){
    var input=(packages||[]).slice().sort(function(a,b){return String(a.id)<String(b.id)?-1:String(a.id)>String(b.id)?1:0;});
    var unique=[];var seen=Object.create(null);var duplicates=0;
    input.forEach(function(item){
      // Coordinate order is fixed within this frontier. Numeric strings cannot
      // contain '|', so repeated key names add no information to duplicate keys.
      var values=new Array(keys.length);
      for(var k=0;k<keys.length;k++)values[k]=Number(item.statDelta&&item.statDelta[keys[k]])||0;
      var key=values.join('|');
      if(seen[key]){duplicates++;return;}seen[key]=true;unique.push(item);
    });
    var configuredLimit=Number(options&&options.maxComparisons);
    var frontier=[];var comparisons=0;var limit=Number.isFinite(configuredLimit)&&configuredLimit>0?configuredLimit:2000000;var complete=true;
    var integerValues=integerParetoValues(unique,keys),frontierOffsets=[];
    for(var i=0;i<unique.length;i++){
      var candidate=unique[i];var rejected=false;
      for(var j=0;j<frontier.length;j++){
        comparisons++;
        if(comparisons>limit){complete=false;break;}
        if(integerValues?integerDominates(integerValues,frontierOffsets[j],i*keys.length,keys.length):dominates(frontier[j].statDelta,candidate.statDelta,keys)){rejected=true;break;}
      }
      if(!complete){frontier=frontier.concat(unique.slice(i));break;}
      if(rejected)continue;
      frontier.push(candidate);
      frontierOffsets.push(i*keys.length);
    }
    frontier.sort(function(a,b){return String(a.id)<String(b.id)?-1:String(a.id)>String(b.id)?1:0;});
    return Object.freeze({packages:Object.freeze(frontier.slice()),inputCount:input.length,outputCount:frontier.length,duplicateCount:duplicates,comparisons:comparisons,complete:complete});
  }


  function candidateProjection(problem,keys){
    var kernel=root.ToramCalculationKernel,context=problem.baseContext||{};
    if(!kernel||typeof kernel.candidateSupplyBases!=='function')return null;
    if(problem.groups.some(function(group){return !group.packages.length;}))return null;
    if((context.activeBuildConversions||[]).some(function(effect){return !effect||effect.conversion!=='unsheatheToAtk';}))return null;
    var minimum={},maximum={},invalid=new Set(),modeled=new Set(modeledKeys(root.ToramStatRegistry));
    problem.groups.forEach(function(group){
      var ranges=new Map();
      group.packages.forEach(function(item){Object.keys(item.statDelta||{}).forEach(function(key){
        if(!modeled.has(key))return;
        var value=Number(item.statDelta[key])||0,range=ranges.get(key)||{low:Infinity,high:-Infinity,count:0};
        range.low=Math.min(range.low,value);range.high=Math.max(range.high,value);range.count++;ranges.set(key,range);
        if(!boundedInteger(value))invalid.add(key);
      });});
      ranges.forEach(function(range,key){
        if(range.count<group.packages.length){range.low=Math.min(range.low,0);range.high=Math.max(range.high,0);}
        minimum[key]=(minimum[key]||0)+range.low;maximum[key]=(maximum[key]||0)+range.high;
      });
    });
    if(!Object.values(minimum).concat(Object.values(maximum)).every(Number.isFinite))return null;
    function boundedInteger(value){return Number.isSafeInteger(value)&&Math.abs(value)<=1000000;}
    function fixed(dependencies){return dependencies.every(function(key){return (minimum[key]||0)===(maximum[key]||0);});}
    var lowStats=clone(minimum),highStats=clone(maximum);
    ['STR','DEX','AGI','INT','VIT'].forEach(function(key){
      if(Number(context[key.toLowerCase()+'Base'])<0){lowStats[key+'P']=maximum[key+'P']||0;highStats[key+'P']=minimum[key+'P']||0;}
    });
    var low=kernel.candidateSupplyBases(context,lowStats),high=kernel.candidateSupplyBases(context,highStats);
    var stats=['STR','DEX','AGI','INT','VIT'],statKeys=stats.flatMap(function(key){return [key,key+'P'];});
    var ignoredPercents=new Set(),constantStatReports=[],math=root.ToramExactMath;
    stats.forEach(function(key){
      var percent=key+'P',prefix=key.toLowerCase(),base=low[key];
      var contextPercent=Number(context[prefix+'P'])||0,contextFlat=Number(context[prefix+'F'])||0;
      var minPercent=contextPercent+(minimum[percent]||0),maxPercent=contextPercent+(maximum[percent]||0);
      if(!keys.includes(percent)||!math||!(minimum[percent]||maximum[percent])||invalid.has(percent)||invalid.has(key)||![base,contextPercent,contextFlat,minPercent,maxPercent,minimum[key]||0,maximum[key]||0].every(boundedInteger))return;
      var initial=math.percent(base,contextPercent),lower=math.percent(base,minPercent),upper=math.percent(base,maxPercent);
      // Integer flat options commute with floor; equality holds for every sum.
      if(initial!==lower||initial!==upper)return;
      ignoredPercents.add(percent);
      constantStatReports.push({key:percent,base:base,percentRange:[minPercent,maxPercent],constantValue:initial,reason:'constant-after-floor'});
    });
    var upKeys=['ATK','MATK'].flatMap(function(prefix){return stats.map(function(key){return prefix+'_UP_'+key;});});
    var conversions=(context.activeBuildConversions||[]).some(function(effect){return effect.conversion==='unsheatheToAtk';})?['UNSHEATHE','UNSHEATHEP']:[];
    var pairs=stats.map(function(key){return {id:key,percent:key+'P',flat:key,prefix:key.toLowerCase(),dependencies:[]};}).concat([
      {id:'CRIT',percent:'CRITP',flat:'CRIT',prefix:'crit',dependencies:[]},
      {id:'WATK',percent:'WATKP',flat:'WATK',prefix:'watk',dependencies:conversions},
      {id:'ATK',percent:'ATKP',flat:'ATK',prefix:'atk',dependencies:statKeys.concat(upKeys,['WATKP','WATK'],conversions)},
      {id:'MATK',percent:'MATKP',flat:'MATK',prefix:'matk',dependencies:statKeys.concat(upKeys,['WATKP','WATK'],conversions)},
      {id:'CDMG',percent:'CDMGP',flat:'CDMG',prefix:'cdmg',dependencies:['STR','STRP','AGI','AGIP'],interval:true},
      {id:'MAXHP',percent:'MAXHPP',flat:'MAXHP',prefix:'maxHp',dependencies:['VIT','VITP'],interval:true,utility:true},
      {id:'ASPD',percent:'ASPD_P',flat:'ASPD',prefix:'aspd',dependencies:statKeys,interval:true,utility:true},
      {id:'CSPD',percent:'CSPD_P',flat:'CSPD',prefix:'cspd',dependencies:['AGI','AGIP','DEX','DEXP'],interval:true},
      {id:'UNSHEATHE',percent:'UNSHEATHEP',flat:'UNSHEATHE',prefix:'unsheathe',dependencies:[],raw:true}
    ]);
    var bundles=[],replaced=new Set(),projectedKeys=[],equality=new Set();
    pairs.forEach(function(pair){
      if(!keys.includes(pair.percent)||!keys.includes(pair.flat)||ignoredPercents.has(pair.percent))return;
      var dependenciesFixed=fixed(pair.dependencies),bases=[];
      var safe=!pair.raw&&boundedInteger(Number(context[pair.prefix+'P'])||0)&&boundedInteger(Number(context[pair.prefix+'F'])||0);
      if(invalid.has(pair.percent)||invalid.has(pair.flat))safe=false;
      if(pair.dependencies.length&&(!dependenciesFixed&&!pair.interval))safe=false;
      if(pair.interval&&statKeys.some(function(key){return !boundedInteger(lowStats[key]||0)||!boundedInteger(highStats[key]||0);}))safe=false;
      if(pair.id==='MAXHP'&&!dependenciesFixed&&Number(context.level)<0)safe=false;
      if(safe){
        bases=Array.from(new Set([].concat(low[pair.id],high[pair.id]))).sort(function(a,b){return a-b;});
        if(!bases.length||!bases.every(boundedInteger))safe=false;
      }
      if(!safe){bundles.push({id:pair.id,mode:'raw',keys:[pair.percent,pair.flat],reason:pair.raw?'different-formula-stages':'variable-base-or-arithmetic-boundary'});return;}
      var divisor=100;
      bases.forEach(function(base){var a=divisor,b=Math.abs(base);while(b){var remainder=a%b;a=b;b=remainder;}divisor=a;});
      var bundle={id:pair.id,mode:bases.length===1?'fixed-base':'base-function',keys:[pair.percent,pair.flat],bases:bases,divisor:divisor,utility:Boolean(pair.utility)};
      bundle.coordinates=bases.map(function(_,index){return '@'+pair.id+':'+index;});bundles.push(bundle);
      replaced.add(pair.percent);replaced.add(pair.flat);
      bundle.coordinates.forEach(function(key){projectedKeys.push(key);if(!pair.utility)equality.add(key);});
    });
    if(!replaced.size&&!ignoredPercents.size)return null;
    keys.forEach(function(key){if(!replaced.has(key)&&!ignoredPercents.has(key)){projectedKeys.push(key);equality.add(key);}});
    // Damage/stat branches may be nonmonotone. New dominance changes only HP/ASPD;
    // other transformed outputs must be identical for every remaining completion.
    var equalityKeys=projectedKeys.filter(function(key){return equality.has(key);});
    var utilityKeys=projectedKeys.filter(function(key){return !equality.has(key);});
    var rawKeys=keys.filter(function(key){return !replaced.has(key)&&!ignoredPercents.has(key);}),directions=[];
    bundles.forEach(function(bundle){if(bundle.mode==='raw')return;bundle.bases.forEach(function(base,index){directions.push({key:bundle.coordinates[index],percent:bundle.keys[0],flat:bundle.keys[1],percentWeight:base/bundle.divisor,flatWeight:100/bundle.divisor});});});
    var classes=new Map();
    return {
      keys:projectedKeys,bundles:bundles,constantStatReports:constantStatReports,ignoredPercents:ignoredPercents,
      project:function(item){
        var values={},source=item.statDelta||{};
        for(var i=0;i<rawKeys.length;i++)values[rawKeys[i]]=Number(source[rawKeys[i]])||0;
        for(var j=0;j<directions.length;j++){var direction=directions[j];values[direction.key]=direction.percentWeight*(Number(source[direction.percent])||0)+direction.flatWeight*(Number(source[direction.flat])||0);}
        var originalSignature=JSON.stringify([item.slot,item.source,item.structureSignature,item.sockets,item.resourceCost,item.conflicts]);
        var classKey=originalSignature+'|'+equalityKeys.map(function(key){return values[key];}).join('|');
        if(!classes.has(classKey))classes.set(classKey,classes.size);
        return Object.freeze(Object.assign({},item,{searchProjection:Object.freeze(values),searchProjectionClass:classes.get(classKey)}));
      },
      replacementRelation:function(left,right){
        if(left.searchProjectionClass!==right.searchProjectionClass)return -1;
        var strict=false;
        for(var i=0;i<utilityKeys.length;i++){
          var key=utilityKeys[i],a=left.searchProjection[key],b=right.searchProjection[key];
          if(a<b)return -1;if(a>b)strict=true;
        }
        return strict?1:0;
      }
    };
  }


  function projectedFrontier(packages,projection,options){
    var buckets=new Map(),retained=[],duplicates=0,dominated=0,comparisons=0;
    var limit=Number(options&&options.maxComparisons)||2000000,complete=true;
    for(var i=0;i<packages.length;i++){
      var item=packages[i],bucket=buckets.get(item.searchProjectionClass)||[],removed=false;
      for(var j=0;j<bucket.length;j++){
        if(++comparisons>limit){complete=false;break;}
        var relation=projection.replacementRelation(bucket[j],item);
        if(relation>=0){if(relation===0)duplicates++;else dominated++;removed=true;break;}
      }
      if(!complete){retained=retained.concat(packages.slice(i));break;}
      if(removed)continue;
      bucket.push(item);buckets.set(item.searchProjectionClass,bucket);retained.push(item);
    }
    return {packages:retained,duplicateCount:duplicates,dominatedCount:dominated,comparisons:comparisons,complete:complete};
  }


  function uniqueRawPackages(packages,keys){
    var seen=new Set(),unique=[];
    packages.slice().sort(function(a,b){return String(a.id)<String(b.id)?-1:String(a.id)>String(b.id)?1:0;}).forEach(function(item){
      var key=keys.map(function(k){return Number(item.statDelta&&item.statDelta[k])||0;}).join('|');
      if(!seen.has(key)){seen.add(key);unique.push(item);}
    });
    return unique;
  }


  function groupVaryingKeys(group,keys){
    var packages=group&&group.packages||[];
    return (keys||[]).filter(function(key){
      if(packages.length<2)return false;
      var first=Number(packages[0].statDelta&&packages[0].statDelta[key])||0;
      for(var i=1;i<packages.length;i++)if(Math.abs((Number(packages[i].statDelta&&packages[i].statDelta[key])||0)-first)>EPSILON)return true;
      return false;
    });
  }


  function prepareProblem(problem,options){
    if(!problem||!Array.isArray(problem.groups))throw new Error('CrystaOptimization 후보 문제가 필요합니다.');
    var registry=options&&options.registry||root.ToramStatRegistry;var keys=options&&options.relevantKeys||modeledKeys(registry);var reports=[];
    var projectionDisabled=!root.ToramCalculationKernel||typeof root.ToramCalculationKernel.candidateSupplyBases!=='function'||options&&(options.disableCandidateProjection||options.disablePareto||options.evaluateStats||options.kernel&&options.kernel!==root.ToramCalculationKernel.evaluateContext||options.registry&&options.registry!==root.ToramStatRegistry||options.evaluator&&options.evaluator!==root.ToramBuildEvaluator);
    var uniqueGroups=projectionDisabled?problem.groups:problem.groups.map(function(group){return {id:group.id,packages:uniqueRawPackages(group.packages,keys)};});
    var projection=projectionDisabled?null:candidateProjection(Object.assign({},problem,{groups:uniqueGroups}),keys);
    var groups=problem.groups.map(function(group,index){
      var groupKeys=groupVaryingKeys(group,projection?keys.filter(function(key){return !projection.ignoredPercents.has(key);}):keys),rawDuplicates=projection?group.packages.length-uniqueGroups[index].packages.length:0;
      var packages=projection?uniqueGroups[index].packages.map(projection.project):group.packages;
      var projected=projection?projectedFrontier(packages,projection,options&&options.pareto):{packages:packages,duplicateCount:0,dominatedCount:0,comparisons:0,complete:true};
      var result=options&&options.disablePareto
        ? {packages:Object.freeze((group.packages||[]).slice()),inputCount:group.packages.length,outputCount:group.packages.length,duplicateCount:0,comparisons:0,complete:true}
        : strictParetoFrontier(projected.packages,groupKeys,options&&options.pareto);
      reports.push({groupId:group.id,inputCount:group.packages.length,outputCount:result.packages.length,duplicateCount:rawDuplicates+result.duplicateCount+projected.duplicateCount,projectedDuplicateCount:projected.duplicateCount,projectedDominatedCount:projected.dominatedCount,projectionComparisons:projected.comparisons,comparisons:result.comparisons,complete:result.complete&&projected.complete,relevantKeyCount:groupKeys.length,projectedKeyCount:projection?projection.keys.length:keys.length});
      return Object.freeze({id:group.id,label:group.label,slots:clone(group.slots||[]),packages:result.packages});
    });
    var prepared=Object.freeze({schema:problem.schema,baseContext:clone(problem.baseContext||{}),scenarioSnapshot:clone(problem.scenarioSnapshot||null),structure:clone(problem.structure||{}),groups:Object.freeze(groups),diagnostics:clone(problem.diagnostics||[]),metadata:Object.assign({},clone(problem.metadata||{}),{paretoReports:reports,modeledKeys:keys,candidateProjection:projection?{policyVersion:CANDIDATE_PROJECTION_POLICY,keys:projection.keys,bundles:projection.bundles,constantStatReports:projection.constantStatReports}:null})});
    return prepared;
  }


  function groupMinimum(group,keys){
    var result={},packages=group.packages||[];
    for(var k=0;k<keys.length;k++)result[keys[k]]=0;
    // Broad registry queries contain many absent coordinates. Visit the sparse
    // options instead; short queries retain direct coordinate lookup.
    var included=keys.length>8?new Set(keys):null;
    for(var i=0;i<packages.length;i++){
      var stats=packages[i].statDelta||{},prototype=Object.getPrototypeOf(stats);
      var sparse=included&&(prototype===Object.prototype||prototype===null);
      var coordinates=sparse?Object.getOwnPropertyNames(stats):keys;
      for(var j=0;j<coordinates.length;j++){
        var key=coordinates[j];
        if(!included||included.has(key))result[key]=Math.min(result[key],Number(stats[key])||0);
      }
    }
    return result;
  }


  function deriveRelevantKeys(problem,registry,evaluateStats){
    var entries=registry&&typeof registry.entries==='function'?registry.entries():[];
    var objective=entries.filter(function(entry){return entry.status==='calculated'&&entry.target;}).map(function(entry){return entry.id;});
    var context=problem.baseContext||{};var attackType=String(context.atkType||'PHYS').toUpperCase();var powerMode=String(context.attackPowerMode||'default');var usesAtk=powerMode==='sum'||powerMode==='higher'||powerMode==='atk'||powerMode==='wizardBlend'||attackType!=='MAG';var usesMatk=powerMode==='sum'||powerMode==='higher'||powerMode==='wizardBlend'||(attackType==='MAG'&&powerMode!=='atk');
    objective=objective.filter(function(key){
      if((key==='ATKP'||key==='ATK'||key.indexOf('ATK_UP_')===0)&&!usesAtk)return false;
      if((key==='MATKP'||key==='MATK'||key.indexOf('MATK_UP_')===0)&&!usesMatk)return false;
      if(key==='PHYS_PIERCE'&&(attackType==='MAG'||context.ignoreDefense===true))return false;
      if(key==='MAG_PIERCE'&&(attackType!=='MAG'||context.ignoreMdef===true))return false;
      if(key==='SRW'&&String(context.rangeType||'SHORT').toUpperCase()!=='SHORT'&&!context.useHigherRangeDamage)return false;
      if(key==='LRW'&&String(context.rangeType||'SHORT').toUpperCase()==='SHORT'&&!context.useHigherRangeDamage)return false;
      if((key==='UNSHEATHE'||key==='UNSHEATHEP')&&!context.chkIsUnsheathe&&!(context.activeBuildConversions||[]).some(function(effect){return effect&&effect.conversion==='unsheatheToAtk';}))return false;
      return true;
    });
    var all=modeledKeys(registry);var pessimistic={};
    (problem.groups||[]).forEach(function(group){pessimistic=addStats(pessimistic,groupMinimum(group,all));});
    var outcome=evaluateStats(pessimistic,{relevanceAudit:true});var requirements=problem.scenarioSnapshot&&problem.scenarioSnapshot.requirements||{};
    var metrics=[
      {requirement:'maxHp',actual:outcome&&outcome.utility&&outcome.utility.maxHp,keys:['MAXHP','MAXHPP']},
      {requirement:'maxMp',actual:outcome&&outcome.utility&&outcome.utility.maxMpBeforeBuff,keys:['MAXMP']},
      {requirement:'amprBeforeDual',actual:outcome&&outcome.utility&&outcome.utility.amprBeforeDual,keys:['AMPR','AMPRP','MAXMP']},
      {requirement:'aspd',actual:outcome&&outcome.utility&&outcome.utility.aspd,keys:['ASPD','ASPD_P'].concat(Number(requirements.aspd)>1000?['MOTIONSPEED']:[])}
    ];
    metrics.forEach(function(metric){
      var required=requirements[metric.requirement];
      if(required!==null&&required!==undefined&&Number(metric.actual)<Number(required))objective=objective.concat(metric.keys);
    });
    var present=Object.create(null);(problem.groups||[]).forEach(function(group){(group.packages||[]).forEach(function(item){Object.keys(item.statDelta||{}).forEach(function(key){if(Math.abs(Number(item.statDelta[key])||0)>EPSILON)present[key]=true;});});});
    return Array.from(new Set(objective)).filter(function(key){return present[key];}).sort();
  }
  var api=Object.freeze({prepareProblem:prepareProblem,deriveRelevantKeys:deriveRelevantKeys,modeledKeys:modeledKeys,strictParetoFrontier:strictParetoFrontier,dominates:dominates,addStats:addStats});
  if(typeof module==='object'&&module.exports)module.exports=api;
  if(root)root.ToramCrystaOptimizationCandidates=api;
})(typeof window!=='undefined'?window:globalThis);
