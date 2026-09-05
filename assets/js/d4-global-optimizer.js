(function (root) {
  'use strict';

  var SCHEMA='toram.d4-global-optimizer.v1';
  var EPSILON=1e-9;
  var PAIR_FRONTIER_POLICY_VERSION='d4-pair-frontier.v1';

  function createSearchProfile(enabled){
    if(enabled!==true)return null;
    var sections=Object.create(null),counters=Object.create(null);
    function add(target,key,value){target[key]=(Number(target[key])||0)+(Number(value)||0);}
    function profileNow(){return root.performance&&typeof root.performance.now==='function'?root.performance.now():Date.now();}
    return Object.freeze({
      now:profileNow,
      time:function(section,startedAt){add(sections,section,Math.max(0,profileNow()-startedAt));},
      count:function(counter,amount){add(counters,counter,amount===undefined?1:amount);},
      result:function(totalElapsedMs){
        return Object.freeze({schema:'d4-search-profile.v1',enabled:true,timingMode:'overlapping-inclusive',elapsedMs:Number(totalElapsedMs),sections:Object.freeze(clone(sections)),counters:Object.freeze(clone(counters))});
      }
    });
  }

  function clone(value){if(value===null||value===undefined||typeof value!=='object')return value;if(Array.isArray(value))return value.map(clone);var result={};Object.keys(value).forEach(function(key){result[key]=clone(value[key]);});return result;}
  function addStats(left,right){var result=clone(left||{});Object.keys(right||{}).forEach(function(key){result[key]=(Number(result[key])||0)+(Number(right[key])||0);});return result;}
  function statKey(stats,keys){return(keys||Object.keys(stats||{}).sort()).map(function(key){return key+':'+(Number(stats&&stats[key])||0);}).join('|');}
  function scoreOf(outcome){var score=Number(outcome&&outcome.damage&&outcome.damage.expected);return Number.isFinite(score)?score:-Infinity;}
  function buildId(selections){return(selections||[]).map(function(item){return item&&item.id||'';}).join('||');}

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

  function strictParetoFrontier(packages,keys,options){
    var input=(packages||[]).slice().sort(function(a,b){return String(a.id)<String(b.id)?-1:String(a.id)>String(b.id)?1:0;});
    var unique=[];var seen=Object.create(null);var duplicates=0;
    input.forEach(function(item){var key=statKey(item.statDelta,keys);if(seen[key]){duplicates++;return;}seen[key]=true;unique.push(item);});
    var configuredLimit=Number(options&&options.maxComparisons);
    var frontier=[];var comparisons=0;var limit=Number.isFinite(configuredLimit)&&configuredLimit>0?configuredLimit:2000000;var complete=true;
    for(var i=0;i<unique.length;i++){
      var candidate=unique[i];var rejected=false;
      for(var j=0;j<frontier.length;j++){
        comparisons++;
        if(comparisons>limit){complete=false;break;}
        if(dominates(frontier[j].statDelta,candidate.statDelta,keys)){rejected=true;break;}
      }
      if(!complete){frontier=frontier.concat(unique.slice(i));break;}
      if(rejected)continue;
      frontier.push(candidate);
    }
    frontier.sort(function(a,b){return String(a.id)<String(b.id)?-1:String(a.id)>String(b.id)?1:0;});
    return Object.freeze({packages:Object.freeze(frontier.slice()),inputCount:input.length,outputCount:frontier.length,duplicateCount:duplicates,comparisons:comparisons,complete:complete});
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
    if(!problem||!Array.isArray(problem.groups))throw new Error('D4 후보 문제가 필요합니다.');
    var registry=options&&options.registry||root.ToramStatRegistry;var keys=options&&options.relevantKeys||modeledKeys(registry);var reports=[];
    var groups=problem.groups.map(function(group){
      var groupKeys=groupVaryingKeys(group,keys);
      var result=options&&options.disablePareto
        ? {packages:Object.freeze((group.packages||[]).slice()),inputCount:(group.packages||[]).length,outputCount:(group.packages||[]).length,duplicateCount:0,comparisons:0,complete:true}
        : strictParetoFrontier(group.packages,groupKeys,options&&options.pareto);
      reports.push({groupId:group.id,inputCount:result.inputCount,outputCount:result.outputCount,duplicateCount:result.duplicateCount,comparisons:result.comparisons,complete:result.complete,relevantKeyCount:groupKeys.length});
      return Object.freeze({id:group.id,label:group.label,slots:clone(group.slots||[]),packages:result.packages});
    });
    return Object.freeze({schema:problem.schema,baseContext:clone(problem.baseContext||{}),scenarioSnapshot:clone(problem.scenarioSnapshot||null),structure:clone(problem.structure||{}),groups:Object.freeze(groups),diagnostics:clone(problem.diagnostics||[]),metadata:Object.assign({},clone(problem.metadata||{}),{paretoReports:reports,modeledKeys:keys})});
  }

  function groupMaximum(group,keys){
    var result={};keys.forEach(function(key){result[key]=0;});
    (group.packages||[]).forEach(function(item){keys.forEach(function(key){result[key]=Math.max(result[key],Number(item.statDelta&&item.statDelta[key])||0);});});
    return result;
  }

  function groupMinimum(group,keys){
    var result={};keys.forEach(function(key){result[key]=0;});
    (group.packages||[]).forEach(function(item){keys.forEach(function(key){result[key]=Math.min(result[key],Number(item.statDelta&&item.statDelta[key])||0);});});
    return result;
  }

  function suffixMaximum(groups,keys){
    var suffix=new Array(groups.length+1);suffix[groups.length]={};
    for(var i=groups.length-1;i>=0;i--)suffix[i]=addStats(groupMaximum(groups[i],keys),suffix[i+1]);
    return suffix;
  }

  function splitImportance(key,context){
    var weights={ATKP:12,MATKP:12,ATK:5,MATK:5,SRW:12,LRW:12,UNSHEATHE:12,UNSHEATHEP:12,CDMG_P:10,CDMGP:10,CDMG:8,PHYS_PIERCE:10,MAG_PIERCE:10,WATKP:8,WATK:5,DAMAGE_P:12,ELEM_P:8,CRIT:7,CRIT_P:7,CRITP:7,STABILITY:6,MAXHP:8,MAXHPP:8,MAXMP:8,AMPR:8,AMPRP:8,ASPD:8,ASPD_P:8};
    var weight=weights[key]||3;var type=String(context&&context.atkType||'PHYS').toUpperCase();var range=String(context&&context.rangeType||'SHORT').toUpperCase();
    if(type==='PHYS'&&(key==='MATKP'||key==='MATK'||key==='MAG_PIERCE'||key.indexOf('MATK_UP_')===0))weight*=0.05;
    if(type==='MAG'&&(key==='ATKP'||key==='ATK'||key==='PHYS_PIERCE'||key.indexOf('ATK_UP_')===0))weight*=0.05;
    if(range==='SHORT'&&key==='LRW')weight*=0.05;if(range==='LONG'&&key==='SRW')weight*=0.05;
    var usesUnsheathe=Boolean(context&&context.chkIsUnsheathe)||(context&&context.activeBuildConversions||[]).some(function(effect){return effect&&effect.conversion==='unsheatheToAtk';});
    if(!usesUnsheathe&&(key==='UNSHEATHE'||key==='UNSHEATHEP'))weight*=0.05;
    return weight;
  }

  function dynamicCandidateOrderRanks(candidateOrder,groupId){
    if(!candidateOrder||candidateOrder.schema!=='toram.d4-dynamic-candidate-order.v1')return null;
    var groups=candidateOrder.groups||[],rankById=Object.create(null);
    for(var index=0;index<groups.length;index++)if(String(groups[index].groupId)===String(groupId)){(groups[index].packageIds||[]).forEach(function(packageId,rank){rankById[String(packageId)]=rank;});return rankById;}
    return null;
  }

  function buildCandidateTree(group,keys,context,candidateOrder){
    var packages=(group&&group.packages||[]).slice(),rankById=dynamicCandidateOrderRanks(candidateOrder,group&&group.id);var ranges={};
    keys.forEach(function(key){var low=Infinity,high=-Infinity;packages.forEach(function(item){var value=Number(item.statDelta&&item.statDelta[key])||0;low=Math.min(low,value);high=Math.max(high,value);});ranges[key]=Math.max(0,high-low);});
    function build(items,depth,path){
      var envelope=groupMaximum({packages:items},keys);
      if(items.length<=1)return{path:path,size:items.length,envelope:envelope,packages:items,package:items[0]||null,left:null,right:null};
      var splitKey=null,bestSpread=-Infinity;
      keys.forEach(function(key){var globalRange=ranges[key]||0;if(globalRange<=EPSILON)return;var low=Infinity,high=-Infinity;items.forEach(function(item){var value=Number(item.statDelta&&item.statDelta[key])||0;low=Math.min(low,value);high=Math.max(high,value);});var spread=(high-low)/globalRange*splitImportance(key,context);if(spread>bestSpread+EPSILON||(Math.abs(spread-bestSpread)<=EPSILON&&String(key)<String(splitKey||'\uffff'))){bestSpread=spread;splitKey=key;}});
      var sorted=items.slice().sort(function(a,b){if(splitKey){var av=Number(a.statDelta&&a.statDelta[splitKey])||0;var bv=Number(b.statDelta&&b.statDelta[splitKey])||0;if(Math.abs(av-bv)>EPSILON)return av-bv;}if(rankById){var rankA=Object.prototype.hasOwnProperty.call(rankById,String(a.id))?rankById[String(a.id)]:Infinity,rankB=Object.prototype.hasOwnProperty.call(rankById,String(b.id))?rankById[String(b.id)]:Infinity;if(rankA!==rankB)return rankA-rankB;}var scoreDiff=heuristicPackageScore(a,'damage')-heuristicPackageScore(b,'damage');if(Math.abs(scoreDiff)>EPSILON)return scoreDiff;return String(a.id)<String(b.id)?-1:String(a.id)>String(b.id)?1:0;});
      var middle=Math.floor(sorted.length/2);if(middle<=0)middle=1;
      return{path:path,size:items.length,envelope:envelope,packages:items,package:null,left:build(sorted.slice(0,middle),depth+1,path+'0'),right:build(sorted.slice(middle),depth+1,path+'1')};
    }
    return build(packages,0,'r');
  }

  function candidateTreeNodeCount(tree){return tree?1+candidateTreeNodeCount(tree.left)+candidateTreeNodeCount(tree.right):0;}
  var PARALLEL_SHARD_SCHEMA='toram.d4-parallel-shard-plan.v1';

  function safeMultiply(left,right){var a=Math.max(0,Number(left)||0),b=Math.max(0,Number(right)||0);if(a===0||b===0)return 0;if(a>Number.MAX_SAFE_INTEGER/b)return Number.MAX_SAFE_INTEGER;return a*b;}
  function safeAdd(left,right){var a=Math.max(0,Number(left)||0),b=Math.max(0,Number(right)||0);return a>Number.MAX_SAFE_INTEGER-b?Number.MAX_SAFE_INTEGER:a+b;}
  function parallelBoxCombinationCount(clusters){var count=1;for(var i=0;i<(clusters||[]).length;i++)count=safeMultiply(count,clusters[i]&&clusters[i].size||0);return count;}
  function parallelBoxPathId(groups,clusters){return(clusters||[]).map(function(cluster,index){return String(groups[index]&&groups[index].id||index)+'@'+String(cluster&&cluster.path||'');}).join('|');}
  function parallelBoxStats(clusters){return(clusters||[]).reduce(function(total,cluster){return addStats(total,cluster&&cluster.envelope||{});},{});}
  function parallelSplitSlack(cluster){if(!cluster||(!cluster.left&&!cluster.right))return-Infinity;var parent=heuristicPackageScore({statDelta:cluster.envelope},'damage');var child=Math.max(cluster.left?heuristicPackageScore({statDelta:cluster.left.envelope},'damage'):-Infinity,cluster.right?heuristicPackageScore({statDelta:cluster.right.envelope},'damage'):-Infinity);return parent-child;}
  function chooseParallelSplitIndex(clusters){var selected=-1,bestSlack=-Infinity,bestSize=-1;(clusters||[]).forEach(function(cluster,index){var slack=parallelSplitSlack(cluster);if(!Number.isFinite(slack))return;if(slack>bestSlack+EPSILON||(Math.abs(slack-bestSlack)<=EPSILON&&(cluster.size>bestSize||(cluster.size===bestSize&&index<selected)))){selected=index;bestSlack=slack;bestSize=cluster.size;}});return selected;}
  function candidateTreeNodeAtPath(tree,path){var node=tree,requested=String(path||'');if(!node||requested.charAt(0)!=='r')return null;for(var index=1;index<requested.length;index++){var step=requested.charAt(index);node=step==='0'?node&&node.left:step==='1'?node&&node.right:null;if(!node)return null;}return node&&node.path===requested?node:null;}
  function parallelPreparation(problem,options){var settings=options||{},registry=settings.registry||root.ToramStatRegistry,evaluateStats=settings.evaluateStats||createDefaultAdapter(problem,settings),relevant=settings.relevantKeys||deriveRelevantKeys(problem,registry,evaluateStats),prepared=settings.prepared?problem:prepareProblem(problem,Object.assign({},settings,{relevantKeys:relevant})),keys=prepared.metadata&&prepared.metadata.modeledKeys||relevant;return{prepared:prepared,keys:keys,evaluateStats:evaluateStats};}
  function createParallelShardPlan(problem,options){
    var settings=options||{},setup=parallelPreparation(problem,settings),prepared=setup.prepared,keys=setup.keys,requested=Math.max(1,Math.floor(Number(settings.targetShards)||1));
    if((prepared.diagnostics||[]).length)return Object.freeze({schema:PARALLEL_SHARD_SCHEMA,status:'invalid',preparedProblem:prepared,relevantKeys:Object.freeze(keys.slice()),targetShards:requested,shards:Object.freeze([]),diagnostics:Object.freeze(clone(prepared.diagnostics))});
    for(var groupIndex=0;groupIndex<prepared.groups.length;groupIndex++)if(!(prepared.groups[groupIndex].packages||[]).length)return Object.freeze({schema:PARALLEL_SHARD_SCHEMA,status:'invalid',preparedProblem:prepared,relevantKeys:Object.freeze(keys.slice()),targetShards:requested,shards:Object.freeze([]),diagnostics:Object.freeze([{code:'EMPTY_CANDIDATE_GROUP',groupId:prepared.groups[groupIndex].id}])});
    var trees=prepared.groups.map(function(group){return buildCandidateTree(group,keys,prepared.baseContext,settings.dynamicCandidateOrder);}),boxes=[{clusters:trees.slice()}];
    while(boxes.length<requested){
      var selected=-1,selectedSplit=-1,selectedCombinations=-1,selectedSlack=-Infinity,selectedPath='';
      boxes.forEach(function(box,index){var split=chooseParallelSplitIndex(box.clusters);if(split<0)return;var combinations=parallelBoxCombinationCount(box.clusters),slack=parallelSplitSlack(box.clusters[split]),path=parallelBoxPathId(prepared.groups,box.clusters);if(combinations>selectedCombinations||(combinations===selectedCombinations&&(slack>selectedSlack+EPSILON||(Math.abs(slack-selectedSlack)<=EPSILON&&path<selectedPath)))){selected=index;selectedSplit=split;selectedCombinations=combinations;selectedSlack=slack;selectedPath=path;}});
      if(selected<0)break;
      var parent=boxes[selected],cluster=parent.clusters[selectedSplit],children=[];[cluster.left,cluster.right].forEach(function(child){if(!child)return;var next=parent.clusters.slice();next[selectedSplit]=child;children.push({clusters:next});});
      if(children.length!==2)break;boxes.splice.apply(boxes,[selected,1].concat(children));
    }
    boxes.sort(function(left,right){var a=parallelBoxPathId(prepared.groups,left.clusters),b=parallelBoxPathId(prepared.groups,right.clusters);return a<b?-1:a>b?1:0;});
    var totalCombinations=0,shards=boxes.map(function(box){var outcome=setup.evaluateStats(parallelBoxStats(box.clusters),{parallelShardPlan:true,summaryOnly:true}),paths=box.clusters.map(function(cluster,index){return Object.freeze({groupId:String(prepared.groups[index].id),path:String(cluster.path)});}),packageCounts=box.clusters.map(function(cluster){return Number(cluster.size)||0;}),combinations=parallelBoxCombinationCount(box.clusters),upper=isOutcomeFeasible(outcome)?scoreOf(outcome):-Infinity;totalCombinations=safeAdd(totalCombinations,combinations);return Object.freeze({id:'d4-shard:'+parallelBoxPathId(prepared.groups,box.clusters),paths:Object.freeze(paths),packageCounts:Object.freeze(packageCounts),estimatedCombinations:combinations,upper:upper,feasibleUpper:isOutcomeFeasible(outcome)});});
    return Object.freeze({schema:PARALLEL_SHARD_SCHEMA,status:'ready',preparedProblem:prepared,relevantKeys:Object.freeze(keys.slice()),candidateOrder:clone(settings.dynamicCandidateOrder||null),initialResult:clone(settings.initialResult||null),targetShards:requested,shards:Object.freeze(shards),totalCombinations:totalCombinations,diagnostics:Object.freeze([])});
  }
  function resolveParallelShardClusters(plan,shard){
    if(!plan||plan.schema!==PARALLEL_SHARD_SCHEMA)throw new Error('유효한 D4 병렬 shard plan이 필요합니다.');if(!shard||!Array.isArray(shard.paths))throw new Error('유효한 D4 병렬 shard가 필요합니다.');
    var prepared=plan.preparedProblem;if(!prepared||!Array.isArray(prepared.groups)||shard.paths.length!==prepared.groups.length)throw new Error('병렬 shard의 부위 구성이 일치하지 않습니다.');var trees=prepared.groups.map(function(group){return buildCandidateTree(group,plan.relevantKeys||[],prepared.baseContext,plan.candidateOrder);});
    return prepared.groups.map(function(group,index){var descriptor=shard.paths[index];if(!descriptor||String(descriptor.groupId)!==String(group.id))throw new Error('병렬 shard의 부위 순서가 일치하지 않습니다.');var node=candidateTreeNodeAtPath(trees[index],descriptor.path);if(!node)throw new Error('병렬 shard path를 CandidateTree에서 찾을 수 없습니다.');return node;});
  }
  function createParallelShardProblem(plan,shard){
    var clusters=resolveParallelShardClusters(plan,shard),prepared=plan.preparedProblem,groups=prepared.groups.map(function(group,index){return Object.freeze({id:group.id,label:group.label,slots:clone(group.slots||[]),packages:Object.freeze((clusters[index].packages||[]).slice())});}),metadata=Object.assign({},clone(prepared.metadata||{}),{parallelShard:{schema:PARALLEL_SHARD_SCHEMA,id:shard.id,paths:clone(shard.paths||[]),estimatedCombinations:shard.estimatedCombinations}});
    return Object.freeze({schema:prepared.schema,baseContext:clone(prepared.baseContext||{}),scenarioSnapshot:clone(prepared.scenarioSnapshot||null),structure:clone(prepared.structure||{}),groups:Object.freeze(groups),diagnostics:clone(prepared.diagnostics||[]),metadata:metadata});
  }
  function verifyParallelShardPlan(plan,options){
    if(!plan||plan.schema!==PARALLEL_SHARD_SCHEMA)return Object.freeze({schema:PARALLEL_SHARD_SCHEMA,complete:false,valid:false,diagnostics:Object.freeze([{code:'INVALID_PARALLEL_SHARD_PLAN'}])});
    var settings=options||{},limit=Math.max(1,Math.floor(Number(settings.maxCompletions)||100000)),prepared=plan.preparedProblem,shards=plan.shards||[],ids=Object.create(null),duplicateShardIds=[],structuralErrors=[];
    shards.forEach(function(shard){if(!shard||!shard.id||ids[shard.id]){duplicateShardIds.push(shard&&shard.id||'');return;}ids[shard.id]=true;try{var clusters=resolveParallelShardClusters(plan,shard);if(parallelBoxCombinationCount(clusters)!==Number(shard.estimatedCombinations))structuralErrors.push({code:'SHARD_COMBINATION_MISMATCH',shardId:shard.id});}catch(error){structuralErrors.push({code:'INVALID_SHARD_PATH',shardId:shard&&shard.id||'',message:error&&error.message||String(error)});}});
    var originalCombinations=parallelBoxCombinationCount((prepared.groups||[]).map(function(group){return{size:(group.packages||[]).length};})),reportedCombinations=(shards||[]).reduce(function(total,shard){return safeAdd(total,Number(shard&&shard.estimatedCombinations)||0);},0),complete=originalCombinations<=limit&&reportedCombinations===originalCombinations&&structuralErrors.length===0&&duplicateShardIds.length===0;
    if(!complete)return Object.freeze({schema:PARALLEL_SHARD_SCHEMA,complete:false,valid:structuralErrors.length===0&&duplicateShardIds.length===0&&reportedCombinations===originalCombinations,originalCombinations:originalCombinations,reportedCombinations:reportedCombinations,coveredCompletions:null,duplicateCompletions:null,missingCompletions:null,diagnostics:Object.freeze(structuralErrors.concat(duplicateShardIds.map(function(id){return{code:'DUPLICATE_SHARD_ID',shardId:id};})))});
    var expected=Object.create(null),seen=Object.create(null),expectedCount=0,duplicateCompletions=0;
    function enumerate(groups,onLeaf){var selections=new Array(groups.length);function visit(index){if(index===groups.length){onLeaf(buildId(selections));return;}(groups[index].packages||[]).forEach(function(item){selections[index]=item;visit(index+1);});}visit(0);}
    enumerate(prepared.groups,function(id){expected[id]=true;expectedCount++;});
    shards.forEach(function(shard){var shardProblem=createParallelShardProblem(plan,shard);enumerate(shardProblem.groups,function(id){if(!expected[id])structuralErrors.push({code:'SHARD_OUT_OF_DOMAIN_COMPLETION',shardId:shard.id,completionId:id});if(seen[id])duplicateCompletions++;seen[id]=true;});});
    var missingCompletions=Object.keys(expected).filter(function(id){return!seen[id];}).length;
    return Object.freeze({schema:PARALLEL_SHARD_SCHEMA,complete:true,valid:structuralErrors.length===0&&duplicateCompletions===0&&missingCompletions===0,originalCombinations:originalCombinations,reportedCombinations:reportedCombinations,coveredCompletions:Object.keys(seen).length,duplicateCompletions:duplicateCompletions,missingCompletions:missingCompletions,diagnostics:Object.freeze(structuralErrors)});
  }
  function mergeParallelShardResults(plan,entries){
    if(!plan||plan.schema!==PARALLEL_SHARD_SCHEMA)return Object.freeze({schema:PARALLEL_SHARD_SCHEMA,status:'invalid',diagnostics:Object.freeze([{code:'INVALID_PARALLEL_SHARD_PLAN'}])});
    var byId=Object.create(null),diagnostics=[],duplicateEntries=[];(entries||[]).forEach(function(entry){var shardId=entry&&entry.shardId||entry&&entry.id;if(!shardId){diagnostics.push({code:'MISSING_SHARD_ID'});return;}if(byId[shardId]){duplicateEntries.push(String(shardId));return;}byId[shardId]=entry&&entry.result||entry;});
    duplicateEntries.forEach(function(id){diagnostics.push({code:'DUPLICATE_SHARD_RESULT',shardId:id});});var bestScore=-Infinity,bestId='',bestBuild=null,bestOutcome=null,upper=-Infinity,visited=0,evaluations=0,remaining=0,elapsed=0,pending=0,cancelled=false,invalid=diagnostics.length>0;
    function considerBest(result){var score=Number(result&&result.score);if(result&&result.bestBuild&&Number.isFinite(score)&&betterResult(score,result.bestBuild.id,bestScore,bestId)){bestScore=score;bestId=result.bestBuild.id;bestBuild=result.bestBuild;bestOutcome=result.outcomes||null;}}
    // The planner's full-domain heuristic is a feasible lower bound, not an
    // unresolved upper bound. Keep it when shards time out before producing
    // their first result so the pool never turns a valid recommendation into
    // an invalid one.
    if(plan.initialResult){considerBest(plan.initialResult);visited+=Number(plan.initialResult.visitedNodes)||0;evaluations+=Number(plan.initialResult.evaluations)||0;elapsed=Math.max(elapsed,Number(plan.initialResult.elapsedMs)||0);}
    (plan.shards||[]).forEach(function(shard){var result=byId[shard.id];if(!result){pending++;upper=Math.max(upper,Number(shard.upper));return;}visited+=Number(result.visitedNodes)||0;evaluations+=Number(result.evaluations)||0;remaining+=Number(result.remainingNodes)||0;elapsed=Math.max(elapsed,Number(result.elapsedMs)||0);if(result.status==='cancelled')cancelled=true;if(result.status==='invalid')invalid=true;considerBest(result);var shardUpper=Number(result.upperBound);if(!Number.isFinite(shardUpper))shardUpper=Number(shard.upper);upper=Math.max(upper,shardUpper);});
    if(!bestBuild)invalid=true;var status=invalid?'invalid':cancelled?'cancelled':Number.isFinite(upper)&&upper<=bestScore+EPSILON?'exact':'bounded',gap=Number.isFinite(bestScore)&&Number.isFinite(upper)?Math.max(0,upper-bestScore)/Math.max(Math.abs(bestScore),EPSILON):null;
    if(pending)diagnostics.push({code:'PENDING_SHARDS',count:pending});return Object.freeze({schema:PARALLEL_SHARD_SCHEMA,status:status,bestBuild:bestBuild,score:bestBuild?bestScore:null,outcomes:bestOutcome,lowerBound:bestBuild?bestScore:null,upperBound:Number.isFinite(upper)?upper:null,optimalityGap:gap,elapsedMs:elapsed,visitedNodes:visited,evaluations:evaluations,remainingNodes:remaining,unresolvedShardCount:pending,diagnostics:Object.freeze(diagnostics)});
  }

  function heuristicCandidatePool(group,current,limit){
    var target=Math.max(2,Number(limit)||48);var each=Math.max(1,Math.ceil(target/2));var result=[];var seen=Object.create(null);
    function add(item){if(!item||seen[item.id])return;seen[item.id]=true;result.push(item);}
    add(current);
    ['damage','utility'].forEach(function(mode){group.packages.slice().sort(function(a,b){var diff=heuristicPackageScore(b,mode)-heuristicPackageScore(a,mode);if(Math.abs(diff)>EPSILON)return diff;return String(a.id)<String(b.id)?-1:String(a.id)>String(b.id)?1:0;}).slice(0,each).forEach(add);});
    return result;
  }

  function createDefaultAdapter(problem,options){
    var evaluator=options&&options.evaluator||root.ToramBuildEvaluator;var kernel=options&&options.kernel||root.ToramCalculationKernel&&root.ToramCalculationKernel.evaluateContext;
    if(!evaluator||typeof evaluator.createBuildSnapshot!=='function'||typeof evaluator.evaluate!=='function')throw new Error('D4 BuildEvaluator가 필요합니다.');
    var scenario=problem.scenarioSnapshot||evaluator.createScenarioSnapshot(problem.baseContext);
    return function(stats,metadata){
      if(metadata&&metadata.summaryOnly&&typeof evaluator.evaluateAggregateSummary==='function')return evaluator.evaluateAggregateSummary(problem.baseContext,scenario,stats||{},kernel);
      if(typeof evaluator.evaluateAggregate==='function')return evaluator.evaluateAggregate(problem.baseContext,scenario,stats||{},kernel);
      var candidate={name:'D4 aggregate',stats:clone(stats||{})};
      var build=evaluator.createBuildSnapshot(problem.baseContext,[candidate],metadata||{});
      return evaluator.evaluate(build,scenario,kernel);
    };
  }

  function deriveRelevantKeys(problem,registry,evaluateStats){
    var entries=registry&&typeof registry.entries==='function'?registry.entries():[];
    var objective=entries.filter(function(entry){return entry.status==='calculated'&&entry.target;}).map(function(entry){return entry.id;});
    var context=problem.baseContext||{};var attackType=String(context.atkType||'PHYS').toUpperCase();var powerMode=String(context.attackPowerMode||'default');var usesAtk=powerMode==='sum'||powerMode==='higher'||powerMode==='atk'||powerMode==='wizardBlend'||attackType!=='MAG';var usesMatk=powerMode==='sum'||powerMode==='higher'||powerMode==='wizardBlend'||(attackType==='MAG'&&powerMode!=='atk');
    objective=objective.filter(function(key){
      if((key==='ATKP'||key==='ATK'||key.indexOf('ATK_UP_')===0)&&!usesAtk)return false;
      if((key==='MATKP'||key==='MATK'||key.indexOf('MATK_UP_')===0)&&!usesMatk)return false;
      if(key==='PHYS_PIERCE'&&attackType==='MAG')return false;
      if(key==='MAG_PIERCE'&&attackType!=='MAG')return false;
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
      {requirement:'aspd',actual:outcome&&outcome.utility&&outcome.utility.aspd,keys:['ASPD','ASPD_P']}
    ];
    metrics.forEach(function(metric){
      var required=requirements[metric.requirement];
      if(required!==null&&required!==undefined&&Number(metric.actual)<Number(required))objective=objective.concat(metric.keys);
    });
    var present=Object.create(null);(problem.groups||[]).forEach(function(group){(group.packages||[]).forEach(function(item){Object.keys(item.statDelta||{}).forEach(function(key){if(Math.abs(Number(item.statDelta[key])||0)>EPSILON)present[key]=true;});});});
    return Array.from(new Set(objective)).filter(function(key){return present[key];}).sort();
  }

  function MaxHeap(){this.items=[];}
  MaxHeap.prototype._better=function(a,b){if(Math.abs(a.upper-b.upper)>EPSILON)return a.upper>b.upper;return a.pathId<b.pathId;};
  MaxHeap.prototype.push=function(item){var a=this.items;a.push(item);var i=a.length-1;while(i>0){var p=Math.floor((i-1)/2);if(this._better(a[p],a[i]))break;var t=a[p];a[p]=a[i];a[i]=t;i=p;}};
  MaxHeap.prototype.pop=function(){var a=this.items;if(!a.length)return null;var top=a[0];var last=a.pop();if(a.length){a[0]=last;var i=0;for(;;){var l=i*2+1,r=l+1,b=i;if(l<a.length&&this._better(a[l],a[b]))b=l;if(r<a.length&&this._better(a[r],a[b]))b=r;if(b===i)break;var t=a[i];a[i]=a[b];a[b]=t;i=b;}}return top;};
  MaxHeap.prototype.peek=function(){return this.items.length?this.items[0]:null;};
  MaxHeap.prototype.size=function(){return this.items.length;};

  function isOutcomeFeasible(outcome){return Boolean(outcome&&outcome.constraints&&outcome.constraints.feasible);}
  function betterResult(score,id,bestScore,bestId){return score>bestScore+EPSILON||(Math.abs(score-bestScore)<=EPSILON&&String(id)<String(bestId||'\uffff'));}

  function heuristicPackageScore(item,mode){
    var stats=item&&item.statDelta||{};
    var utility=(Number(stats.MAXHP)||0)/10000+(Number(stats.MAXHPP)||0)/100+(Number(stats.MAXMP)||0)/2000+(Number(stats.AMPR)||0)/100+(Number(stats.AMPRP)||0)/100+(Number(stats.ASPD)||0)/1000+(Number(stats.ASPD_P)||0)/100+(Number(stats.CRIT)||0)/100+(Number(stats.CRIT_P)||0)/100;
    var damage=(Number(stats.ATKP)||0)+(Number(stats.MATKP)||0)+(Number(stats.SRW)||0)+(Number(stats.LRW)||0)+(Number(stats.UNSHEATHE)||0)+(Number(stats.UNSHEATHEP)||0)+(Number(stats.CDMG_P)||0)+(Number(stats.CDMGP)||0)+(Number(stats.PHYS_PIERCE)||0)+(Number(stats.MAG_PIERCE)||0)+(Number(stats.WATKP)||0)+(Number(stats.DAMAGE_P)||0)+(Number(stats.ATK)||0)/100+(Number(stats.MATK)||0)/100+(Number(stats.CDMG)||0)/3;
    return mode==='utility'?utility*1000000+damage:damage*1000+utility;
  }

  function heuristicSelections(problem,prepared){
    var result=[];var metadata=problem&&problem.metadata||{};var initialIds=metadata.initialPackageIds||[];
    if(initialIds.length===prepared.groups.length){
      var initial=[];for(var i=0;i<prepared.groups.length;i++){var found=prepared.groups[i].packages.find(function(item){return item.id===initialIds[i];});if(!found){initial=[];break;}initial.push(found);}if(initial.length)result.push(initial);
    }
    ['utility','damage'].forEach(function(mode){result.push(prepared.groups.map(function(group){var best=null,bestScore=-Infinity;(group.packages||[]).forEach(function(item){var score=heuristicPackageScore(item,mode);if(score>bestScore+EPSILON||(Math.abs(score-bestScore)<=EPSILON&&String(item.id)<String(best&&best.id||'\uffff'))){best=item;bestScore=score;}});return best;}));});
    return result;
  }

  function heuristicSeedLabel(index,count){var hasCurrent=Number(count)>2;var offset=hasCurrent?1:0;if(hasCurrent&&index===0)return'current';return index-offset===0?'utility':index-offset===1?'damage':'seed-'+index;}
  function groupIndexById(groups,id){for(var i=0;i<(groups||[]).length;i++)if(String(groups[i].id)===String(id))return i;return-1;}

  function pairCandidateEntries(left,right,limit,leftCurrent,rightCurrent){
    var leftPool=heuristicCandidatePool(left,leftCurrent,limit);var rightPool=heuristicCandidatePool(right,rightCurrent,limit);var entries=[];var seen=Object.create(null);
    leftPool.forEach(function(a){rightPool.forEach(function(b){var id=String(a.id)+"||"+String(b.id);if(seen[id])return;seen[id]=true;entries.push({id:id,left:a,right:b,statDelta:addStats(a.statDelta,b.statDelta)});});});
    entries.sort(function(a,b){return String(a.id)<String(b.id)?-1:String(a.id)>String(b.id)?1:0;});return entries;
  }

  function allPairCandidateEntries(left,right){var entries=[];(left.packages||[]).forEach(function(a){(right.packages||[]).forEach(function(b){entries.push({id:String(a.id)+"||"+String(b.id),left:a,right:b,statDelta:addStats(a.statDelta,b.statDelta)});});});entries.sort(function(a,b){return String(a.id)<String(b.id)?-1:String(a.id)>String(b.id)?1:0;});return entries;}

  function runPairLowerBound(problem,prepared,keys,settings,acceptSelections,currentSelections){
    function current(){return typeof currentSelections==="function"?currentSelections():currentSelections;}
    var pairApi=settings.pairPartition||root.ToramD4PairPartition;if(!pairApi||typeof pairApi.analyzePairPartitions!=="function"||!current())return[];
    var fullLimit=Number.isFinite(Number(settings.pairFrontierMaterializationLimit))?Math.max(1,Math.floor(Number(settings.pairFrontierMaterializationLimit))):8192;var seedLimit=Number.isFinite(Number(settings.pairSeedPerGroup))?Math.max(2,Math.floor(Number(settings.pairSeedPerGroup))):24;
    var analysis=pairApi.analyzePairPartitions(problem,null,{preparedProblem:prepared,pairMaterializationLimit:fullLimit});if(!analysis||!analysis.selection)return[];var partition=(analysis.partitions||[]).filter(function(item){return item.id===analysis.selection.id;})[0];if(!partition)return[];var reports=[];
    (partition.pairs||[]).forEach(function(pair){var leftIndex=groupIndexById(prepared.groups,pair.groups&&pair.groups[0]),rightIndex=groupIndexById(prepared.groups,pair.groups&&pair.groups[1]);if(leftIndex<0||rightIndex<0)return;var left=prepared.groups[leftIndex],right=prepared.groups[rightIndex];var fullCount=(left.packages||[]).length*(right.packages||[]).length;var entries,mode,frontier=null;
      if(fullCount<=fullLimit){entries=allPairCandidateEntries(left,right);frontier=strictParetoFrontier(entries,keys,settings.pairPareto||settings.pareto);entries=frontier.packages;mode=frontier.complete?"materialized-frontier":"materialized-unreduced";}else if(settings.enableLazyPairSeeds===true){var activeSelections=current();entries=pairCandidateEntries(left,right,seedLimit,activeSelections[leftIndex],activeSelections[rightIndex]);mode="lazy-seed";}else{reports.push({pairId:pair.id,groups:(pair.groups||[]).slice(),mode:"lazy-deferred",fullCandidateCount:fullCount,evaluatedCandidateCount:0,frontierInputCount:null,frontierOutputCount:null,frontierComplete:false});return;}
      var baseline=current().slice();entries.forEach(function(entry){var trial=baseline.slice();trial[leftIndex]=entry.left;trial[rightIndex]=entry.right;acceptSelections(trial,{heuristic:true,pairLowerBound:true,pairId:pair.id,mode:mode});});
      reports.push({pairId:pair.id,groups:(pair.groups||[]).slice(),mode:mode,fullCandidateCount:fullCount,evaluatedCandidateCount:entries.length,frontierInputCount:frontier&&frontier.inputCount||null,frontierOutputCount:frontier&&frontier.outputCount||null,frontierComplete:frontier&&frontier.complete===true});
    });
    return reports;
  }

  function candidateClusterSlack(cluster){if(!cluster||(!cluster.left&&!cluster.right))return-Infinity;var parent=heuristicPackageScore({statDelta:cluster.envelope},'damage');var child=Math.max(cluster.left?heuristicPackageScore({statDelta:cluster.left.envelope},'damage'):-Infinity,cluster.right?heuristicPackageScore({statDelta:cluster.right.envelope},'damage'):-Infinity);return parent-child;}

  function splitTreeToClusterCount(tree,count){var clusters=[tree];var target=Math.max(1,Math.floor(Number(count)||1));while(clusters.length<target){var chosen=-1,bestSlack=-Infinity,bestSize=-1;clusters.forEach(function(cluster,index){var slack=candidateClusterSlack(cluster);if(slack>bestSlack+EPSILON||(Math.abs(slack-bestSlack)<=EPSILON&&(cluster.size>bestSize||(cluster.size===bestSize&&String(cluster.path)<String(chosen>=0&&clusters[chosen].path||'\uffff'))))){chosen=index;bestSlack=slack;bestSize=cluster.size;}});if(chosen<0)break;var parent=clusters[chosen];clusters.splice.apply(clusters,[chosen,1].concat([parent.left,parent.right].filter(Boolean)));}return clusters.sort(function(a,b){return String(a.path)<String(b.path)?-1:String(a.path)>String(b.path)?1:0;});}

  function pairCorrelationRootBoxes(problem,prepared,trees,settings){
    if(settings.enablePairCorrelationBounds!==true)return null;var pairApi=settings.pairPartition||root.ToramD4PairPartition;if(!pairApi||typeof pairApi.analyzePairPartitions!=="function")return null;var analysis=pairApi.analyzePairPartitions(problem,null,{preparedProblem:prepared,pairMaterializationLimit:1});if(!analysis||!analysis.selection)return null;var partition=(analysis.partitions||[]).filter(function(item){return item.id===analysis.selection.id;})[0];if(!partition||!(partition.pairs||[]).length)return null;var pair=partition.pairs[0];var leftIndex=groupIndexById(prepared.groups,pair.groups&&pair.groups[0]),rightIndex=groupIndexById(prepared.groups,pair.groups&&pair.groups[1]);if(leftIndex<0||rightIndex<0)return null;var clusterCount=Number.isFinite(Number(settings.pairCorrelationClustersPerGroup))?Math.max(2,Math.floor(Number(settings.pairCorrelationClustersPerGroup))):4;var leftClusters=splitTreeToClusterCount(trees[leftIndex],clusterCount),rightClusters=splitTreeToClusterCount(trees[rightIndex],clusterCount),boxes=[];leftClusters.forEach(function(left){rightClusters.forEach(function(right){var box=trees.slice();box[leftIndex]=left;box[rightIndex]=right;boxes.push(box);});});return {boxes:boxes,report:{pairId:pair.id,groups:(pair.groups||[]).slice(),clustersPerGroup:clusterCount,leftClusterCount:leftClusters.length,rightClusterCount:rightClusters.length,rootBoxCount:boxes.length}};
  }

  function pairStreamEnvelopeBuckets(left,right,keys,pivotKey,bucketCount){
    var pivotIndex=(keys||[]).indexOf(pivotKey);if(pivotIndex<0||!left||!right)return null;var leftVectors=(left.packages||[]).map(function(item){return(keys||[]).map(function(key){return Number(item.statDelta&&item.statDelta[key])||0;});}),rightVectors=(right.packages||[]).map(function(item){return(keys||[]).map(function(key){return Number(item.statDelta&&item.statDelta[key])||0;});});if(!leftVectors.length||!rightVectors.length)return null;var low=Infinity,high=-Infinity;leftVectors.forEach(function(vector){rightVectors.forEach(function(other){var value=vector[pivotIndex]+other[pivotIndex];if(value<low)low=value;if(value>high)high=value;});});var count=Math.max(2,Math.floor(Number(bucketCount)||4)),span=high-low,envelopes=Array.from({length:count},function(){return(keys||[]).map(function(){return-Infinity;});}),counts=Array(count).fill(0);leftVectors.forEach(function(vector){rightVectors.forEach(function(other){var value=vector[pivotIndex]+other[pivotIndex],bucket=span<=0?0:Math.min(count-1,Math.floor((value-low)/span*count)),envelope=envelopes[bucket];counts[bucket]++;for(var index=0;index<envelope.length;index++){var total=vector[index]+other[index];if(total>envelope[index])envelope[index]=total;}});});var stats=envelopes.map(function(envelope,index){if(!counts[index])return null;var result={};(keys||[]).forEach(function(key,keyIndex){result[key]=envelope[keyIndex];});return result;}).filter(Boolean);return {stats:stats,report:{pivotKey:pivotKey,pivotRange:[low,high],bucketCount:count,nonemptyBuckets:stats.length,pairCandidateCount:leftVectors.length*rightVectors.length}};
  }

  function pairStreamRootProfiles(problem,prepared,keys,settings){
    if(settings.enablePairStreamBounds!==true)return null;var pairApi=settings.pairPartition||root.ToramD4PairPartition;if(!pairApi||typeof pairApi.analyzePairPartitions!=="function")return null;var analysis=pairApi.analyzePairPartitions(problem,null,{preparedProblem:prepared,pairMaterializationLimit:1});if(!analysis||!analysis.selection)return null;var partition=(analysis.partitions||[]).filter(function(item){return item.id===analysis.selection.id;})[0];if(!partition||!(partition.pairs||[]).length)return null;var pivotKey=String(settings.pairStreamPivotKey||"CRIT"),bucketCount=Math.max(2,Math.floor(Number(settings.pairStreamBucketCount)||4)),profiles=[];(partition.pairs||[]).forEach(function(pair){var left=prepared.groups[groupIndexById(prepared.groups,pair.groups&&pair.groups[0])],right=prepared.groups[groupIndexById(prepared.groups,pair.groups&&pair.groups[1])],profile=pairStreamEnvelopeBuckets(left,right,keys,pivotKey,bucketCount);if(profile)profiles.push(profile);});if(profiles.length!==2)return null;return {profiles:profiles,report:{pivotKey:pivotKey,bucketCount:bucketCount,pairReports:profiles.map(function(profile){return profile.report;})}};
  }

  function createSeedTelemetry(settings,start){
    var enabled=!settings||settings.collectSeedTelemetry!==false;
    var configured=settings&&settings.seedTelemetryCheckpointsMs;
    var defaults=[100,500,1000,5000,10000];
    var targets=(Array.isArray(configured)?configured:defaults).map(function(value){return Math.max(0,Math.floor(Number(value)||0));}).filter(function(value,index,list){return value>0&&list.indexOf(value)===index;}).sort(function(a,b){return a-b;});
    var phases=[],checkpoints=[],cursor=0;
    function elapsed(){return Date.now()-start;}
    function gap(lower,upper){return Number.isFinite(lower)&&Number.isFinite(upper)?Math.max(0,upper-lower)/Math.max(Math.abs(lower),EPSILON):null;}
    function record(target,kind,name,details){
      if(!enabled)return;
      target.push(Object.freeze(Object.assign({kind:kind,name:name,elapsedMs:elapsed(),evaluations:0,lowerBound:null,upperBound:null,optimalityGap:null,visitedNodes:0,remainingNodes:0,prunedByBound:0,prunedByConstraint:0},details||{})));
    }
    return Object.freeze({
      phase:function(name,details){record(phases,'phase',name,details);},
      checkpoints:function(name,details){
        if(!enabled)return;
        var now=elapsed();
        while(cursor<targets.length&&now>=targets[cursor]){
          var target=targets[cursor++],sample=Object.assign({targetElapsedMs:target,elapsedMs:now},details||{});
          sample.optimalityGap=gap(sample.lowerBound,sample.upperBound);
          record(checkpoints,'checkpoint',name,sample);
        }
      },
      result:function(){return Object.freeze({schema:'d4-initial-seed-telemetry.v1',enabled:enabled,checkpointTargetsMs:Object.freeze(targets.slice()),phases:Object.freeze(phases.slice()),checkpoints:Object.freeze(checkpoints.slice())});}
    });
  }

  function findGreedyInitialSolution(problem,options){
    var start=Date.now(),settings=options||{},registry=settings.registry||root.ToramStatRegistry,evaluateStats=settings.evaluateStats||createDefaultAdapter(problem,settings),evaluations=0,bestScore=-Infinity,bestId='',bestSelections=null,bestOutcome=null;
    function accept(selections,metadata){
      if(!Array.isArray(selections)||selections.some(function(item){return!item;}))return false;
      var stats=selections.reduce(function(total,item){return addStats(total,item.statDelta);},{}),outcome=evaluateStats(stats,Object.assign({heuristic:true,greedyPreview:true},metadata||{})),score=scoreOf(outcome),id=buildId(selections);evaluations++;
      if(isOutcomeFeasible(outcome)&&betterResult(score,id,bestScore,bestId)){bestScore=score;bestId=id;bestSelections=selections.slice();bestOutcome=outcome;return true;}return false;
    }
    heuristicSelections(problem,problem).forEach(function(selections,index){accept(selections,{phase:'raw',index:index});});
    var relevantKeys=settings.skipParetoPreparation?null:(settings.relevantKeys||deriveRelevantKeys(problem,registry,evaluateStats)),prepared=settings.prepared||settings.skipParetoPreparation?problem:prepareProblem(problem,Object.assign({},settings,{relevantKeys:relevantKeys}));
    if((prepared.diagnostics||[]).length)return Object.freeze({schema:SCHEMA,status:'invalid',bestBuild:null,score:null,outcomes:null,lowerBound:null,upperBound:null,optimalityGap:null,elapsedMs:Date.now()-start,visitedNodes:0,evaluations:evaluations,diagnostics:clone(prepared.diagnostics)});
    for(var groupIndex=0;groupIndex<prepared.groups.length;groupIndex++)if(!(prepared.groups[groupIndex].packages||[]).length)return Object.freeze({schema:SCHEMA,status:'invalid',bestBuild:null,score:null,outcomes:null,lowerBound:null,upperBound:null,optimalityGap:null,elapsedMs:Date.now()-start,visitedNodes:0,evaluations:evaluations,diagnostics:[{code:'EMPTY_CANDIDATE_GROUP',groupId:prepared.groups[groupIndex].id}]});
    heuristicSelections(problem,prepared).forEach(function(selections,index){accept(selections,{phase:'prepared',index:index});});
    var candidateLimit=settings.heuristicCandidateLimit===0?0:Math.max(2,Number(settings.heuristicCandidateLimit)||96),passLimit=Math.max(0,Number.isFinite(Number(settings.heuristicPasses))?Number(settings.heuristicPasses):2);
    if(bestSelections&&candidateLimit>0){for(var pass=0;pass<passLimit;pass++){var changed=false;for(var index=0;index<prepared.groups.length;index++){var baseline=bestSelections.slice(),beforeId=bestId;heuristicCandidatePool(prepared.groups[index],baseline[index],candidateLimit).forEach(function(item){var trial=baseline.slice();trial[index]=item;accept(trial,{phase:'coordinate',pass:pass,group:index});});if(bestId!==beforeId)changed=true;}if(!changed)break;}}
    var valid=Boolean(bestSelections),statDelta=valid?bestSelections.reduce(function(stats,item){return addStats(stats,item.statDelta);},{}):null;
    return Object.freeze({schema:SCHEMA,status:valid?'heuristic':'invalid',bestBuild:valid?Object.freeze({id:bestId,packages:Object.freeze(bestSelections.slice()),statDelta:Object.freeze(statDelta)}):null,score:valid?bestScore:null,outcomes:bestOutcome,hardConstraintStatus:bestOutcome&&bestOutcome.constraints||null,lowerBound:valid?bestScore:null,upperBound:null,optimalityGap:null,elapsedMs:Date.now()-start,visitedNodes:0,evaluations:evaluations,heuristicEvaluations:evaluations,diagnostics:valid?[]:[{code:'NO_FEASIBLE_GREEDY_BUILD'}]});
  }

  function optimize(problem,options){
    var start=Date.now();var settings=options||{};var searchProfile=createSearchProfile(settings.collectSearchProfile===true);var seedTelemetry=createSeedTelemetry(settings,start);var registry=settings.registry||root.ToramStatRegistry;var evaluateStats=settings.evaluateStats||createDefaultAdapter(problem,settings);var earlyEvaluations=0,earlyBestScore=-Infinity,earlyBestId='',earlyBestSelections=null,earlyBestOutcome=null,earlyFirstFeasibleMs=null;function acceptEarly(selections,label){var before=earlyEvaluations,profileStarted=searchProfile&&searchProfile.now();var stats=selections.reduce(function(total,item){return addStats(total,item.statDelta);},{});earlyEvaluations++;var outcome=evaluateStats(stats,{heuristic:true,early:true,seedLabel:label});if(searchProfile){searchProfile.time('evaluate:heuristic',profileStarted);searchProfile.count('evaluate:heuristic');}var score=scoreOf(outcome);var id=buildId(selections);if(isOutcomeFeasible(outcome)&&betterResult(score,id,earlyBestScore,earlyBestId)){earlyBestScore=score;earlyBestId=id;earlyBestSelections=selections.slice();earlyBestOutcome=outcome;if(earlyFirstFeasibleMs===null)earlyFirstFeasibleMs=Date.now()-start;}seedTelemetry.phase('rawInitial:'+label,{evaluations:earlyEvaluations,evaluationDelta:earlyEvaluations-before,lowerBound:Number.isFinite(earlyBestScore)?earlyBestScore:null,bestBuildId:earlyBestSelections?earlyBestId:null,firstFeasibleMs:earlyFirstFeasibleMs});}var rawInitialSelections=heuristicSelections(problem,problem);rawInitialSelections.forEach(function(selections,index){acceptEarly(selections,heuristicSeedLabel(index,rawInitialSelections.length));});seedTelemetry.phase('rawInitialComplete',{evaluations:earlyEvaluations,lowerBound:Number.isFinite(earlyBestScore)?earlyBestScore:null,bestBuildId:earlyBestSelections?earlyBestId:null,firstFeasibleMs:earlyFirstFeasibleMs});var relevantKeys=settings.relevantKeys||deriveRelevantKeys(problem,registry,evaluateStats);var prepared=settings.prepared?problem:prepareProblem(problem,Object.assign({},settings,{relevantKeys:relevantKeys}));var keys=prepared.metadata.modeledKeys||relevantKeys;
    if((prepared.diagnostics||[]).length)return Object.freeze({schema:SCHEMA,status:'invalid',bestBuild:null,score:null,outcomes:null,lowerBound:null,upperBound:null,optimalityGap:null,elapsedMs:Date.now()-start,visitedNodes:0,evaluations:earlyEvaluations,seedTelemetry:seedTelemetry.result(),diagnostics:clone(prepared.diagnostics)});
    for(var gi=0;gi<prepared.groups.length;gi++)if(!prepared.groups[gi].packages.length)return Object.freeze({schema:SCHEMA,status:'invalid',bestBuild:null,score:null,outcomes:null,lowerBound:null,upperBound:null,optimalityGap:null,elapsedMs:Date.now()-start,visitedNodes:0,evaluations:earlyEvaluations,seedTelemetry:seedTelemetry.result(),diagnostics:[{code:'EMPTY_CANDIDATE_GROUP',groupId:prepared.groups[gi].id}]});
    var trees=[];var treeNodes=0;var heap=new MaxHeap();var deadline=Number(settings.timeLimitMs)>0?start+Number(settings.timeLimitMs):Infinity;var maxNodes=Number(settings.maxNodes)>0?Number(settings.maxNodes):Infinity;var progressInterval=Math.max(16,Number(settings.progressIntervalMs)||32);var lastProgress=0;var stoppedBy=null;
    var evaluations=earlyEvaluations,visited=0,prunedByBound=0,prunedByConstraint=0,enumeratedBoxes=0,enumeratedCompletions=0;var bestScore=earlyBestScore,bestId=earlyBestId,bestSelections=earlyBestSelections,bestOutcome=earlyBestOutcome;var firstFeasibleMs=earlyFirstFeasibleMs,heuristicEvaluations=0;
    function evaluationKind(metadata){if(metadata&&metadata.complete)return 'complete';if(metadata&&metadata.bound)return 'bound';if(metadata&&metadata.heuristic)return 'heuristic';if(metadata&&metadata.sourceBaseline)return 'source';if(metadata&&metadata.sourceBefore)return 'source';if(metadata&&metadata.sourceAfter)return 'source';return 'other';}
    function evaluate(stats,metadata){var kind=evaluationKind(metadata),profileStarted=searchProfile&&searchProfile.now();evaluations++;var outcome=evaluateStats(stats,metadata);if(searchProfile){searchProfile.time('evaluate:'+kind,profileStarted);searchProfile.count('evaluate:'+kind);}return outcome;}
    function queueUpper(activeUpper){var queued=heap.peek()&&heap.peek().upper;var upper=Math.max(Number.isFinite(activeUpper)?activeUpper:-Infinity,Number.isFinite(queued)?queued:-Infinity,Number.isFinite(bestScore)?bestScore:-Infinity);return Number.isFinite(upper)?upper:null;}
    function progress(activeUpper,force,stage){var now=Date.now();if(!force&&now-lastProgress<progressInterval)return;lastProgress=now;var upper=queueUpper(activeUpper);var valid=Boolean(bestSelections);var gap=valid&&Number.isFinite(upper)?Math.max(0,upper-bestScore)/Math.max(Math.abs(bestScore),EPSILON):null;var details={lowerBound:valid?bestScore:null,upperBound:upper,optimalityGap:gap,visitedNodes:visited,evaluations:evaluations,remainingNodes:heap.size(),prunedByBound:prunedByBound,prunedByConstraint:prunedByConstraint};seedTelemetry.checkpoints(stage||'searching',details);if(typeof settings.onProgress!=='function')return;settings.onProgress(Object.assign({stage:stage||'searching',status:'running',bestBuild:valid?{id:bestId,packages:bestSelections.slice()}:null,elapsedMs:now-start},details));}
    function considerOutcome(outcome,selections){var score=scoreOf(outcome);var id=buildId(selections);if(isOutcomeFeasible(outcome)&&betterResult(score,id,bestScore,bestId)){bestScore=score;bestId=id;bestSelections=selections.slice();bestOutcome=outcome;if(firstFeasibleMs===null)firstFeasibleMs=Date.now()-start;return true;}return false;}
    function acceptSelections(selections,metadata){var stats=selections.reduce(function(total,item){return addStats(total,item.statDelta);},{});return considerOutcome(evaluate(stats,metadata),selections);}
    var dynamicSeedReport=null,dynamicCandidateOrder=settings.dynamicCandidateOrder||null;
    function runDynamicSeedIncumbent(){
      if(settings.enableDynamicSeedIncumbent!==true)return;
      var configuredTime=Number(settings.dynamicSeedTimeLimitMs);
      if(!Number.isFinite(configuredTime)||configuredTime<=0){dynamicSeedReport={enabled:true,used:false,reason:'missingTimeBudget'};return;}
      var seedApi=settings.dynamicSeed||root.ToramD4DynamicSeed,marginalApi=settings.dynamicMarginal||root.ToramD4DynamicMarginal;
      if(!seedApi||typeof seedApi.createDynamicSeedPool!=='function'||typeof seedApi.createDynamicSeedBuilds!=='function'||typeof seedApi.improveDynamicSeedBuilds!=='function'||(settings.enableDynamicSeedOrdering===true&&typeof seedApi.createDynamicCandidateOrder!=='function')||!marginalApi||typeof marginalApi.createDynamicMarginalProfile!=='function')throw new Error('D4 dynamic seed S1~S5 modules are required when the matching experiment option is enabled.');
      var phaseStartEvaluations=evaluations,phaseStartScore=bestScore,phaseStart=Date.now(),phaseDeadline=Math.min(deadline,phaseStart+configuredTime);
      function shouldStop(){return Date.now()>=phaseDeadline||(typeof settings.shouldCancel==='function'&&settings.shouldCancel());}
      if(shouldStop()){dynamicSeedReport={enabled:true,used:false,reason:'deadline'};return;}
      var common={evaluateStats:evaluate,sourceProfile:settings.sourceProfile||root.ToramD4SourceProfile,shouldCancel:shouldStop};
      var profile=marginalApi.createDynamicMarginalProfile(prepared,common);
      if(shouldStop()){dynamicSeedReport={enabled:true,used:false,reason:'profileDeadline',profileHash:profile.profileHash,evaluations:evaluations-phaseStartEvaluations};return;}
      if(settings.enableDynamicSeedOrdering===true)dynamicCandidateOrder=seedApi.createDynamicCandidateOrder(profile);
      var pool=seedApi.createDynamicSeedPool(prepared,{profile:profile,perSeedLimit:settings.dynamicSeedPerSeedLimit,mergedGroupLimit:settings.dynamicSeedMergedGroupLimit});
      var remaining=Math.max(1,phaseDeadline-Date.now()),builds=seedApi.createDynamicSeedBuilds(prepared,Object.assign({},common,{profile:profile,pool:pool,seedTimeLimitMs:remaining,seedEvaluationLimit:settings.dynamicSeedEvaluationLimit,cartesianLimit:settings.dynamicSeedCartesianLimit,beamWidth:settings.dynamicSeedBeamWidth,repairInputLimit:settings.dynamicSeedRepairInputLimit,repairPerGroupLimit:settings.dynamicSeedRepairPerGroupLimit,repairPairLimit:settings.dynamicSeedRepairPairLimit}));
      var local=null;if(!shouldStop()&&builds.feasibleCandidates&&builds.feasibleCandidates.length)local=seedApi.improveDynamicSeedBuilds(prepared,Object.assign({},common,{profile:profile,pool:pool,seedBuilds:builds,localTimeLimitMs:Math.max(1,phaseDeadline-Date.now()),localEvaluationLimit:settings.dynamicSeedLocalEvaluationLimit,localStartLimit:settings.dynamicSeedLocalStartLimit,localPassLimit:settings.dynamicSeedLocalPassLimit,localCandidateLimit:settings.dynamicSeedLocalCandidateLimit,localPairCandidateLimit:settings.dynamicSeedLocalPairCandidateLimit}));
      var merged=(builds.feasibleCandidates||[]).concat(local&&local.feasibleCandidates||[]),seen=Object.create(null),accepted=0;merged.sort(function(left,right){var score=Number(right.score)-Number(left.score);return Math.abs(score)>EPSILON?score:String(left.id).localeCompare(String(right.id));}).forEach(function(record){if(!record||seen[record.id])return;seen[record.id]=true;if(considerOutcome(record.outcome,record.selections))accepted++;});
      dynamicSeedReport=Object.freeze({enabled:true,used:true,orderingEnabled:settings.enableDynamicSeedOrdering===true,candidateOrderHash:dynamicCandidateOrder&&dynamicCandidateOrder.orderHash||null,profileHash:profile.profileHash,poolHash:pool.poolHash,poolCounts:Object.freeze(pool.groups.map(function(group){return Object.freeze({groupId:group.groupId,count:group.poolPackageCount});})),mode:builds.mode,seedEvaluations:builds.evaluations,localEvaluations:local&&local.evaluations||0,feasibleSeedCount:(builds.feasibleCandidates||[]).length,feasibleLocalCount:local&&(local.feasibleCandidates||[]).length||0,mergedCandidateCount:Object.keys(seen).length,acceptedCount:accepted,startLowerBound:Number.isFinite(phaseStartScore)?phaseStartScore:null,endLowerBound:Number.isFinite(bestScore)?bestScore:null,elapsedMs:Date.now()-phaseStart,stoppedBy:local&&local.stoppedBy||builds.stoppedBy||null});
      seedTelemetry.phase('dynamicSeedIncumbent',{evaluations:evaluations,evaluationDelta:evaluations-phaseStartEvaluations,lowerBound:Number.isFinite(bestScore)?bestScore:null,lowerBoundDelta:Number.isFinite(bestScore)&&Number.isFinite(phaseStartScore)?bestScore-phaseStartScore:null,bestBuildId:bestSelections?bestId:null,firstFeasibleMs:firstFeasibleMs,dynamicSeed:dynamicSeedReport});
    }
    var preparedInitialSelections=heuristicSelections(problem,prepared);preparedInitialSelections.forEach(function(selections,index){var before=evaluations,label=heuristicSeedLabel(index,preparedInitialSelections.length);acceptSelections(selections,{heuristic:true,index:index,seedLabel:label});seedTelemetry.phase('preparedInitial:'+label,{evaluations:evaluations,evaluationDelta:evaluations-before,lowerBound:Number.isFinite(bestScore)?bestScore:null,bestBuildId:bestSelections?bestId:null,firstFeasibleMs:firstFeasibleMs});});
    runDynamicSeedIncumbent();
    var coordinateStartEvaluations=evaluations,coordinateStartScore=bestScore;var heuristicLimit=settings.heuristicCandidateLimit===0?0:Math.max(2,Number(settings.heuristicCandidateLimit)||192);var heuristicPasses=Math.max(0,Number.isFinite(Number(settings.heuristicPasses))?Number(settings.heuristicPasses):2);
    if(bestSelections&&heuristicLimit>0){for(var pass=0;pass<heuristicPasses&&Date.now()<=deadline;pass++){var changed=false;for(var groupIndex=0;groupIndex<prepared.groups.length&&Date.now()<=deadline;groupIndex++){var baseline=bestSelections.slice();var beforeId=bestId;heuristicCandidatePool(prepared.groups[groupIndex],baseline[groupIndex],heuristicLimit).forEach(function(item){if(Date.now()>deadline)return;var trial=baseline.slice();trial[groupIndex]=item;acceptSelections(trial,{heuristic:true,coordinate:true,pass:pass,group:groupIndex});});if(bestId!==beforeId)changed=true;}if(!changed)break;}}
    seedTelemetry.phase('coordinateSearch',{evaluations:evaluations,evaluationDelta:evaluations-coordinateStartEvaluations,lowerBound:Number.isFinite(bestScore)?bestScore:null,lowerBoundDelta:Number.isFinite(bestScore)&&Number.isFinite(coordinateStartScore)?bestScore-coordinateStartScore:null,bestBuildId:bestSelections?bestId:null,firstFeasibleMs:firstFeasibleMs});var pairStartEvaluations=evaluations,pairStartScore=bestScore;var pairFrontierReports=runPairLowerBound(problem,prepared,keys,settings,acceptSelections,function(){return bestSelections;});seedTelemetry.phase('pairLowerBound',{evaluations:evaluations,evaluationDelta:evaluations-pairStartEvaluations,lowerBound:Number.isFinite(bestScore)?bestScore:null,lowerBoundDelta:Number.isFinite(bestScore)&&Number.isFinite(pairStartScore)?bestScore-pairStartScore:null,bestBuildId:bestSelections?bestId:null,firstFeasibleMs:firstFeasibleMs,pairReportCount:pairFrontierReports.length});heuristicEvaluations=evaluations;seedTelemetry.phase('heuristicComplete',{evaluations:heuristicEvaluations,lowerBound:Number.isFinite(bestScore)?bestScore:null,bestBuildId:bestSelections?bestId:null,firstFeasibleMs:firstFeasibleMs});progress(null,true,'heuristic');
    var treeStarted=searchProfile&&searchProfile.now();trees=prepared.groups.map(function(group){return buildCandidateTree(group,keys,prepared.baseContext,dynamicCandidateOrder);});if(searchProfile)searchProfile.time('treeBuild',treeStarted);treeNodes=trees.reduce(function(total,tree){return total+candidateTreeNodeCount(tree);},0);
    function boxStats(clusters){var profileStarted=searchProfile&&searchProfile.now(),stats=clusters.reduce(function(total,cluster){return addStats(total,cluster.envelope);},{});if(searchProfile)searchProfile.time('boxStats',profileStarted);return stats;}
    function boundForBox(clusters,metadata,full){if(searchProfile)searchProfile.count('boundCalls');var details=Object.assign({},metadata||{},full?{}:{summaryOnly:true});var outcome=evaluate(boxStats(clusters),details);return{upper:scoreOf(outcome),outcome:outcome,feasible:isOutcomeFeasible(outcome)};}
    function splitSlack(cluster){if(!cluster||(!cluster.left&&!cluster.right))return-Infinity;var parent=heuristicPackageScore({statDelta:cluster.envelope},'damage');var child=Math.max(cluster.left?heuristicPackageScore({statDelta:cluster.left.envelope},'damage'):-Infinity,cluster.right?heuristicPackageScore({statDelta:cluster.right.envelope},'damage'):-Infinity);return parent-child;}
    function chooseSplitIndices(clusters,count){
      var profileStarted=searchProfile&&searchProfile.now(),indices=clusters.map(function(cluster,index){return{index:index,cluster:cluster,slack:splitSlack(cluster)};}).filter(function(entry){return entry.cluster&&(entry.cluster.left||entry.cluster.right);}).sort(function(a,b){if(Math.abs(a.slack-b.slack)>EPSILON)return b.slack-a.slack;if(a.cluster.size!==b.cluster.size)return b.cluster.size-a.cluster.size;return a.index-b.index;}).slice(0,Math.max(1,count||1)).map(function(entry){return entry.index;});
      if(searchProfile)searchProfile.time('splitSelection',profileStarted);return indices;
    }
    function chooseSplitIndex(clusters){var indices=chooseSplitIndices(clusters,1);return indices.length?indices[0]:-1;}
    var smallBoxEnumerationLimit=Number.isFinite(Number(settings.smallBoxEnumerationLimit))?Math.max(0,Math.floor(Number(settings.smallBoxEnumerationLimit))):64;var splitDimensions=Number.isFinite(Number(settings.splitDimensions))?Math.max(1,Math.min(4,Math.floor(Number(settings.splitDimensions)))):2;var boundGuidedSplitLevels=settings.enableBoundGuidedSplit===true?Math.max(1,Math.floor(Number(settings.boundGuidedSplitLevels)||1)):0;
    function boxCombinationCount(clusters,limit){var count=1;for(var i=0;i<clusters.length;i++){count*=clusters[i]&&clusters[i].size||0;if(count>limit)return count;}return count;}
    function enumerateBox(clusters){
      var profileStarted=searchProfile&&searchProfile.now(),selections=new Array(clusters.length);enumeratedBoxes++;if(searchProfile)searchProfile.count('enumeratedBoxes');
      function visit(index,stats){
        if(index>=clusters.length){enumeratedCompletions++;considerOutcome(evaluate(stats,{complete:true,smallBox:true}),selections);return;}
        clusters[index].packages.forEach(function(item){selections[index]=item;visit(index+1,addStats(stats,item.statDelta));});
      }
      visit(0,{});if(searchProfile)searchProfile.time('smallBoxEnumeration',profileStarted);
    }
    function boxPathId(clusters){return clusters.map(function(cluster,index){return prepared.groups[index].id+'@'+cluster.path;}).join('|');}
    function splitChildBoxes(clusters,splitIndices){var profileStarted=searchProfile&&searchProfile.now(),childBoxes=[clusters];splitIndices.forEach(function(index){var expanded=[];childBoxes.forEach(function(box){[box[index].left,box[index].right].forEach(function(child){if(!child)return;var next=box.slice();next[index]=child;expanded.push(next);});});childBoxes=expanded;});if(searchProfile){searchProfile.time('childBoxExpansion',profileStarted);searchProfile.count('childBoxes',childBoxes.length);}return childBoxes;}
    function chooseBoundGuidedSplit(clusters){var available=clusters.map(function(cluster,index){return cluster&&(cluster.left||cluster.right)?index:-1;}).filter(function(index){return index>=0;}),best=null;for(var left=0;left<available.length;left++)for(var right=left+1;right<available.length;right++){var indices=[available[left],available[right]],boxes=splitChildBoxes(clusters,indices),bounds=[],upper=-Infinity,valid=true;boxes.forEach(function(box){var bounded=boundForBox(box,{bound:true,box:true,boundGuided:true,groups:indices,clusters:indices.map(function(index){return box[index].path;})});bounds.push(bounded);if(!bounded.feasible)valid=false;else upper=Math.max(upper,bounded.upper);});if(!valid||!Number.isFinite(upper))continue;if(!best||upper<best.upper-EPSILON||(Math.abs(upper-best.upper)<=EPSILON&&(indices[0]<best.indices[0]||(indices[0]===best.indices[0]&&indices[1]<best.indices[1]))))best={indices:indices,boxes:boxes,bounds:bounds,upper:upper};}return best;}
    var rootBound=boundForBox(trees,{bound:true,box:true},true);var rootUpper=rootBound.upper;seedTelemetry.phase('rootBound',{evaluations:evaluations,lowerBound:Number.isFinite(bestScore)?bestScore:null,upperBound:Number.isFinite(rootUpper)?rootUpper:null,optimalityGap:Number.isFinite(bestScore)&&Number.isFinite(rootUpper)?Math.max(0,rootUpper-bestScore)/Math.max(Math.abs(bestScore),EPSILON):null,visitedNodes:visited,remainingNodes:heap.size(),prunedByBound:prunedByBound,prunedByConstraint:prunedByConstraint});seedTelemetry.checkpoints('rootBound',{evaluations:evaluations,lowerBound:Number.isFinite(bestScore)?bestScore:null,upperBound:Number.isFinite(rootUpper)?rootUpper:null,visitedNodes:visited,remainingNodes:heap.size(),prunedByBound:prunedByBound,prunedByConstraint:prunedByConstraint});
    if(!rootBound.feasible)return Object.freeze({schema:SCHEMA,status:'invalid',bestBuild:null,score:null,outcomes:null,lowerBound:null,upperBound:rootUpper,optimalityGap:null,elapsedMs:Date.now()-start,visitedNodes:0,evaluations:evaluations,heuristicEvaluations:heuristicEvaluations,firstFeasibleMs:firstFeasibleMs,boundTreeNodes:treeNodes,seedTelemetry:seedTelemetry.result(),diagnostics:[{code:'NO_POSSIBLE_FEASIBLE_BUILD',violations:clone(rootBound.outcome.constraints&&rootBound.outcome.constraints.violations||[])}]});
    var initialBoxes=[{clusters:trees.slice(),upper:rootUpper,pathId:boxPathId(trees),depth:0}];var pairStream=pairStreamRootProfiles(problem,prepared,keys,settings);if(pairStream){var streamUpper=-Infinity;pairStream.profiles[0].stats.forEach(function(leftStats){pairStream.profiles[1].stats.forEach(function(rightStats){var outcome=evaluate(addStats(leftStats,rightStats),{bound:true,box:true,pairStream:true});if(isOutcomeFeasible(outcome))streamUpper=Math.max(streamUpper,scoreOf(outcome));});});if(Number.isFinite(streamUpper)){rootUpper=Math.min(rootUpper,streamUpper);pairStream.report.upper=rootUpper;}};var pairCorrelation=pairCorrelationRootBoxes(problem,prepared,trees,settings);if(pairCorrelation&&pairCorrelation.boxes&&pairCorrelation.boxes.length){var pairUpper=-Infinity,pairEntries=[];pairCorrelation.boxes.forEach(function(clusters){var bounded=boundForBox(clusters,{bound:true,box:true,pairCorrelation:true},true);if(bounded.feasible){pairUpper=Math.max(pairUpper,bounded.upper);pairEntries.push({clusters:clusters,upper:bounded.upper,pathId:boxPathId(clusters),depth:0});}});if(pairEntries.length&&Number.isFinite(pairUpper)){rootUpper=Math.min(rootUpper,pairUpper);pairCorrelation.report.upper=rootUpper;pairCorrelation.report.scheduledBoxCount=pairEntries.length;initialBoxes=pairEntries;}}
    initialBoxes.forEach(function(entry){var profileStarted=searchProfile&&searchProfile.now();heap.push(entry);if(searchProfile){searchProfile.time('heapPush',profileStarted);searchProfile.count('heapPushes');}});progress(rootUpper,true,'searching');
    while(heap.size()&&visited<maxNodes){
      if(typeof settings.shouldCancel==='function'&&settings.shouldCancel()){stoppedBy='cancelled';break;}
      if(Date.now()>deadline){stoppedBy='time';break;}
      var popStarted=searchProfile&&searchProfile.now(),node=heap.pop();if(searchProfile){searchProfile.time('heapPop',popStarted);searchProfile.count('heapPops');}visited++;
      if(node.upper<bestScore-EPSILON){prunedByBound++;continue;}
      if(smallBoxEnumerationLimit>0&&boxCombinationCount(node.clusters,smallBoxEnumerationLimit)<=smallBoxEnumerationLimit){enumerateBox(node.clusters);progress(node.upper,false,'searching');continue;}
      var splitIndex=chooseSplitIndex(node.clusters);
      if(splitIndex<0){var selections=node.clusters.map(function(cluster){return cluster.package;});var stats=selections.reduce(function(total,item){return addStats(total,item.statDelta);},{});considerOutcome(evaluate(stats,{complete:true}),selections);progress(node.upper,false,'searching');continue;}
      if(searchProfile)searchProfile.count('splitNodes');var guided=node.depth<boundGuidedSplitLevels&&splitDimensions===2?chooseBoundGuidedSplit(node.clusters):null;var splitIndices=guided?guided.indices:chooseSplitIndices(node.clusters,splitDimensions);var childBoxes=guided?guided.boxes:splitChildBoxes(node.clusters,splitIndices);
      childBoxes.forEach(function(childClusters,childIndex){var bounded=guided?guided.bounds[childIndex]:boundForBox(childClusters,{bound:true,box:true,groups:splitIndices,clusters:splitIndices.map(function(index){return childClusters[index].path;})});if(!bounded.feasible){prunedByConstraint++;return;}if(bounded.upper<bestScore-EPSILON){prunedByBound++;return;}var pushStarted=searchProfile&&searchProfile.now();heap.push({clusters:childClusters,upper:bounded.upper,pathId:boxPathId(childClusters),depth:node.depth+1});if(searchProfile){searchProfile.time('heapPush',pushStarted);searchProfile.count('heapPushes');}});
      progress(node.upper,false,'searching');
    }
    if(!stoppedBy&&visited>=maxNodes&&heap.size())stoppedBy='nodes';
    var exhausted=heap.size()===0;var finalUpper=exhausted?bestScore:queueUpper(null);var validBest=Boolean(bestSelections);var status=stoppedBy==='cancelled'?'cancelled':exhausted&&validBest?'exact':validBest?'bounded':'invalid';var gap=validBest&&Number.isFinite(finalUpper)?Math.max(0,finalUpper-bestScore)/Math.max(Math.abs(bestScore),EPSILON):null;seedTelemetry.checkpoints(status,{lowerBound:validBest?bestScore:null,upperBound:Number.isFinite(finalUpper)?finalUpper:null,optimalityGap:gap,visitedNodes:visited,evaluations:evaluations,remainingNodes:heap.size(),prunedByBound:prunedByBound,prunedByConstraint:prunedByConstraint});
    var sourceApi=settings.sourceProfile||root.ToramD4SourceProfile;var baseOutcome=null,residuals=null,sourceOpportunityCosts=[];
    if(sourceApi&&validBest){baseOutcome=evaluate({}, {sourceBaseline:true});residuals=sourceApi.residualRequirements(baseOutcome,prepared.scenarioSnapshot&&prepared.scenarioSnapshot.requirements||{});var running={};bestSelections.forEach(function(item){var before=evaluate(running,{sourceBefore:item.slot});running=addStats(running,item.statDelta);var after=evaluate(running,{sourceAfter:item.slot});sourceOpportunityCosts.push({slot:item.slot,packageId:item.id,value:sourceApi.sourceValue(before,after)});});}
    var elapsedMs=Date.now()-start,leadingNode=heap.peek(),leadingSplit=leadingNode?chooseSplitIndex(leadingNode.clusters):-1;var result=Object.freeze({schema:SCHEMA,status:status,bestBuild:validBest?Object.freeze({id:bestId,packages:Object.freeze(bestSelections.slice()),statDelta:Object.freeze(bestSelections.reduce(function(stats,item){return addStats(stats,item.statDelta);},{}))}):null,score:validBest?bestScore:null,outcomes:bestOutcome,hardConstraintStatus:bestOutcome&&bestOutcome.constraints||null,lowerBound:validBest?bestScore:null,upperBound:Number.isFinite(finalUpper)?finalUpper:null,optimalityGap:gap,elapsedMs:elapsedMs,firstFeasibleMs:firstFeasibleMs,heuristicEvaluations:heuristicEvaluations,boundTreeNodes:treeNodes,boundFrontierHead:leadingNode?Object.freeze({groupId:leadingSplit>=0?prepared.groups[leadingSplit].id:null,groupIndex:leadingSplit,clusterSize:leadingSplit>=0?leadingNode.clusters[leadingSplit].size:1,selectedGroups:leadingNode.clusters.filter(function(cluster){return Boolean(cluster.package);}).length,upper:leadingNode.upper}):null,visitedNodes:visited,evaluations:evaluations,remainingNodes:heap.size(),prunedByBound:prunedByBound,prunedByConstraint:prunedByConstraint,enumeratedBoxes:enumeratedBoxes,enumeratedCompletions:enumeratedCompletions,frontierReports:clone(prepared.metadata.paretoReports||[]),pairFrontierReports:Object.freeze(clone(pairFrontierReports)),pairCorrelationReport:pairCorrelation&&clone(pairCorrelation.report)||null,pairStreamReport:pairStream&&clone(pairStream.report)||null,seedTelemetry:seedTelemetry.result(),searchProfile:searchProfile&&searchProfile.result(elapsedMs),dynamicSeedReport:dynamicSeedReport,dynamicCandidateOrderHash:dynamicCandidateOrder&&dynamicCandidateOrder.orderHash||null,sourceResiduals:residuals,sourceOpportunityCosts:Object.freeze(sourceOpportunityCosts),diagnostics:validBest?[]:[{code:'NO_FEASIBLE_BUILD'}]});progress(finalUpper,true,status);return result;
  }

  function verifyCandidateTreeUpperBounds(problem,options){
    var settings=options||{};var prepared=settings.prepared?problem:prepareProblem(problem,settings);var registry=settings.registry||root.ToramStatRegistry;var keys=prepared.metadata.modeledKeys||modeledKeys(registry);var evaluateStats=settings.evaluateStats||createDefaultAdapter(prepared,settings);var trees=prepared.groups.map(function(group){return buildCandidateTree(group,keys,prepared.baseContext,settings.dynamicCandidateOrder);});var checked=0,completions=0,violations=[];
    function combinedEnvelope(clusters){return clusters.reduce(function(total,cluster){return addStats(total,cluster.envelope);},{});}
    function slack(cluster){if(!cluster||(!cluster.left&&!cluster.right))return-Infinity;var parent=heuristicPackageScore({statDelta:cluster.envelope},'damage');var child=Math.max(cluster.left?heuristicPackageScore({statDelta:cluster.left.envelope},'damage'):-Infinity,cluster.right?heuristicPackageScore({statDelta:cluster.right.envelope},'damage'):-Infinity);return parent-child;}
    function splitIndex(clusters){var selected=-1,bestSlack=-Infinity,bestSize=-1;clusters.forEach(function(cluster,index){if(!cluster||(!cluster.left&&!cluster.right))return;var value=slack(cluster);if(value>bestSlack+EPSILON||(Math.abs(value-bestSlack)<=EPSILON&&(cluster.size>bestSize||(cluster.size===bestSize&&index<selected)))){selected=index;bestSlack=value;bestSize=cluster.size;}});return selected;}
    function audit(clusters){var upper=scoreOf(evaluateStats(combinedEnvelope(clusters),{verifyCandidateTreeBound:true}));checked++;var index=splitIndex(clusters);var actual=-Infinity;if(index<0){var stats=clusters.reduce(function(total,cluster){return addStats(total,cluster.package.statDelta);},{});actual=scoreOf(evaluateStats(stats,{verifyCandidateTreeComplete:true}));completions++;}else{[clusters[index].left,clusters[index].right].forEach(function(child){if(!child)return;var next=clusters.slice();next[index]=child;actual=Math.max(actual,audit(next));});}if(actual>upper+EPSILON)violations.push({box:clusters.map(function(cluster){return cluster.path;}),upper:upper,actual:actual});return actual;}
    if(trees.length)audit(trees);return Object.freeze({checked:checked,completions:completions,violations:Object.freeze(violations)});
  }

  function verifyEnvelopeMonotonicity(problem,options){
    var settings=options||{};var prepared=settings.prepared?problem:prepareProblem(problem,settings);var registry=settings.registry||root.ToramStatRegistry;var keys=prepared.metadata.modeledKeys||modeledKeys(registry);var evaluateStats=settings.evaluateStats||createDefaultAdapter(prepared,settings);var trees=prepared.groups.map(function(group){return buildCandidateTree(group,keys,prepared.baseContext,settings.dynamicCandidateOrder);});var checked=0,violations=[];
    function combinedStats(index,node){var result={};trees.forEach(function(tree,groupIndex){result=addStats(result,(groupIndex===index?node:tree).envelope);});return result;}
    function audit(index,node){if(!node||(!node.left&&!node.right))return;var parent=evaluateStats(combinedStats(index,node),{verifyEnvelopeMonotonicity:true,group:index,path:node.path});[node.left,node.right].forEach(function(child){if(!child)return;var outcome=evaluateStats(combinedStats(index,child),{verifyEnvelopeMonotonicity:true,group:index,path:child.path});checked++;var parentScore=scoreOf(parent),childScore=scoreOf(outcome);if(childScore>parentScore+EPSILON||Boolean(outcome&&outcome.constraints&&outcome.constraints.feasible)&&!Boolean(parent&&parent.constraints&&parent.constraints.feasible))violations.push({groupId:prepared.groups[index].id,parentPath:node.path,childPath:child.path,parentUpper:parentScore,childUpper:childScore,parentFeasible:Boolean(parent&&parent.constraints&&parent.constraints.feasible),childFeasible:Boolean(outcome&&outcome.constraints&&outcome.constraints.feasible)});audit(index,child);});}
    trees.forEach(function(tree,index){audit(index,tree);});return Object.freeze({checked:checked,violations:Object.freeze(violations)});
  }

  function verifyPairCorrelationUpperBounds(problem,options){
    var settings=options||{},prepared=settings.prepared?problem:prepareProblem(problem,settings),registry=settings.registry||root.ToramStatRegistry,keys=prepared.metadata.modeledKeys||modeledKeys(registry),evaluateStats=settings.evaluateStats||createDefaultAdapter(prepared,settings),trees=prepared.groups.map(function(group){return buildCandidateTree(group,keys,prepared.baseContext,settings.dynamicCandidateOrder);}),correlation=pairCorrelationRootBoxes(problem,prepared,trees,Object.assign({},settings,{enablePairCorrelationBounds:true})),checked=0,completions=0,violations=[];
    if(!correlation||!correlation.boxes||!correlation.boxes.length)return Object.freeze({checked:checked,completions:completions,report:null,violations:Object.freeze(violations)});
    function boxStats(clusters){return clusters.reduce(function(total,cluster){return addStats(total,cluster.envelope);},{});}
    function actualMaximum(clusters){var best=-Infinity,hasFeasible=false;function visit(index,stats){if(index===clusters.length){completions++;var outcome=evaluateStats(stats,{verifyPairCorrelationComplete:true});if(isOutcomeFeasible(outcome)){hasFeasible=true;best=Math.max(best,scoreOf(outcome));}return;}var cluster=clusters[index];if(cluster.package){visit(index+1,addStats(stats,cluster.package.statDelta));return;}(cluster.packages||[]).forEach(function(item){visit(index+1,addStats(stats,item.statDelta));});}visit(0,{});return {score:best,feasible:hasFeasible};}
    correlation.boxes.forEach(function(clusters){var bounded=evaluateStats(boxStats(clusters),{verifyPairCorrelationBound:true}),actual=actualMaximum(clusters);checked++;if(actual.feasible&&(!isOutcomeFeasible(bounded)||actual.score>scoreOf(bounded)+EPSILON))violations.push({box:clusters.map(function(cluster){return cluster.path;}),upper:scoreOf(bounded),upperFeasible:isOutcomeFeasible(bounded),actual:actual.score});});
    return Object.freeze({checked:checked,completions:completions,report:Object.freeze(clone(correlation.report)),violations:Object.freeze(violations)});
  }

  function exhaustiveSearch(problem,options){
    var settings=options||{};var prepared=settings.prepared?problem:prepareProblem(problem,Object.assign({},settings,{disablePareto:true}));var evaluateStats=settings.evaluateStats||createDefaultAdapter(prepared,settings);var bestScore=-Infinity,bestId='',bestSelections=null,bestOutcome=null,evaluations=0;
    function visit(index,stats,selections){
      if(index===prepared.groups.length){evaluations++;var outcome=evaluateStats(stats,{oracle:true});var score=scoreOf(outcome);var id=buildId(selections);if(isOutcomeFeasible(outcome)&&betterResult(score,id,bestScore,bestId)){bestScore=score;bestId=id;bestSelections=selections.slice();bestOutcome=outcome;}return;}
      prepared.groups[index].packages.forEach(function(item){visit(index+1,addStats(stats,item.statDelta),selections.concat([item]));});
    }
    visit(0,{},[]);
    return Object.freeze({schema:SCHEMA,status:bestSelections?'exact':'invalid',bestBuild:bestSelections?Object.freeze({id:bestId,packages:Object.freeze(bestSelections)}):null,score:bestSelections?bestScore:null,outcomes:bestOutcome,evaluations:evaluations});
  }

  function verifyUpperBounds(problem,options){
    var settings=options||{};var prepared=settings.prepared?problem:prepareProblem(problem,settings);var registry=settings.registry||root.ToramStatRegistry;var keys=prepared.metadata.modeledKeys||modeledKeys(registry);var evaluateStats=settings.evaluateStats||createDefaultAdapter(prepared,settings);var suffix=suffixMaximum(prepared.groups,keys);var completions=[];
    function enumerate(index,stats,path){if(index===prepared.groups.length){var outcome=evaluateStats(stats,{verifyComplete:true});completions.push({path:path.slice(),score:scoreOf(outcome)});return;}prepared.groups[index].packages.forEach(function(item){enumerate(index+1,addStats(stats,item.statDelta),path.concat([item.id]));});}
    enumerate(0,{},[]);var violations=[];var checked=0;
    function prefixes(index,stats,path){var upper=scoreOf(evaluateStats(addStats(stats,suffix[index]),{verifyBound:true,depth:index}));var actual=-Infinity;completions.forEach(function(item){for(var i=0;i<path.length;i++)if(item.path[i]!==path[i])return;actual=Math.max(actual,item.score);});checked++;if(actual>upper+EPSILON)violations.push({path:path.slice(),upper:upper,actual:actual});if(index<prepared.groups.length)prepared.groups[index].packages.forEach(function(item){prefixes(index+1,addStats(stats,item.statDelta),path.concat([item.id]));});}
    prefixes(0,{},[]);return Object.freeze({checked:checked,completions:completions.length,violations:Object.freeze(violations)});
  }

  var api=Object.freeze({schema:SCHEMA,pairFrontierPolicyVersion:PAIR_FRONTIER_POLICY_VERSION,modeledKeys:modeledKeys,deriveRelevantKeys:deriveRelevantKeys,dominates:dominates,strictParetoFrontier:strictParetoFrontier,prepareProblem:prepareProblem,parallelShardSchema:PARALLEL_SHARD_SCHEMA,createParallelShardPlan:createParallelShardPlan,createParallelShardProblem:createParallelShardProblem,verifyParallelShardPlan:verifyParallelShardPlan,mergeParallelShardResults:mergeParallelShardResults,findGreedyInitialSolution:findGreedyInitialSolution,optimize:optimize,exhaustiveSearch:exhaustiveSearch,verifyUpperBounds:verifyUpperBounds,verifyCandidateTreeUpperBounds:verifyCandidateTreeUpperBounds,verifyEnvelopeMonotonicity:verifyEnvelopeMonotonicity,verifyPairCorrelationUpperBounds:verifyPairCorrelationUpperBounds,addStats:addStats});
  if(typeof module==='object'&&module.exports)module.exports=api;if(root)root.ToramD4GlobalOptimizer=api;
}(typeof window!=='undefined'?window:globalThis));
