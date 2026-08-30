(function (root) {
  'use strict';

  var SCHEMA='toram.d4-pair-partition.v1';
  var PAIR_PARTITION_POLICY_VERSION='d4-pair-partition.v1';
  var DEFAULT_MATERIALIZATION_LIMIT=250000;
  var SLOT_IDS=Object.freeze(['weapon','armor','additional','special']);
  var PARTITIONS=Object.freeze([
    Object.freeze({id:'armor-special__weapon-additional',pairs:Object.freeze([Object.freeze(['armor','special']),Object.freeze(['weapon','additional'])])}),
    Object.freeze({id:'armor-weapon__additional-special',pairs:Object.freeze([Object.freeze(['armor','weapon']),Object.freeze(['additional','special'])])}),
    Object.freeze({id:'armor-additional__weapon-special',pairs:Object.freeze([Object.freeze(['armor','additional']),Object.freeze(['weapon','special'])])})
  ]);

  function number(value){var parsed=Number(value);return Number.isFinite(parsed)?parsed:0;}
  function product(left,right){var value=number(left)*number(right);return Number.isSafeInteger(value)?value:Number.MAX_SAFE_INTEGER;}
  function groupMap(problem){var result=Object.create(null);(problem&&problem.groups||[]).forEach(function(group){if(group&&group.id!==undefined)result[String(group.id)]=group;});return result;}
  function countOf(groups,id){var group=groups[id];return group&&Array.isArray(group.packages)?group.packages.length:0;}
  function sum(values){return(values||[]).reduce(function(total,value){return total+number(value);},0);}
  function fixed(value,digits){return Number(number(value).toFixed(digits));}
  function utilityMap(supplyReport){return supplyReport&&supplyReport.utilities||{};}

  function pairUtilitySummary(pair,utilities){
    var ids=pair.slice();
    var rows=Object.keys(utilities).sort().map(function(id){
      var utility=utilities[id]||{};var residual=Math.max(0,number(utility.residual));
      var maxima={};(utility.groupMaximums||[]).forEach(function(entry){maxima[String(entry.groupId)]=number(entry.maximum);});
      var supply=number(maxima[ids[0]])+number(maxima[ids[1]]);
      return Object.freeze({id:id,active:Boolean(utility.active&&residual>0),residual:residual,supply:supply,coverageRatio:residual>0?Math.min(1,supply/residual):1,canCoverResidual:residual===0||supply>=residual});
    });
    return Object.freeze(rows);
  }

  function partitionMetrics(definition,rawGroups,preparedGroups,utilities,limit){
    var pairs=definition.pairs.map(function(pair,index){
      var rawLeft=countOf(rawGroups,pair[0]),rawRight=countOf(rawGroups,pair[1]);
      var preparedLeft=countOf(preparedGroups,pair[0]),preparedRight=countOf(preparedGroups,pair[1]);
      var rawProduct=product(rawLeft,rawRight),preparedProduct=product(preparedLeft,preparedRight);
      return Object.freeze({
        id:pair.join('+'),index:index,groups:Object.freeze(pair.slice()),
        rawCandidateCount:rawProduct,preparedCandidateCount:preparedProduct,
        rawGroupCounts:Object.freeze([rawLeft,rawRight]),preparedGroupCounts:Object.freeze([preparedLeft,preparedRight]),
        materializationEligible:preparedProduct<=limit,
        utility:Object.freeze(pairUtilitySummary(pair,utilities))
      });
    });
    var active=Object.keys(utilities).sort().filter(function(id){var utility=utilities[id]||{};return Boolean(utility.active&&number(utility.residual)>0);});
    var split=0,fullCoverage=0,coverageScore=0;
    active.forEach(function(id){
      var sides=pairs.map(function(pair){return pair.utility.filter(function(row){return row.id===id;})[0];});
      var canCover=sides.some(function(row){return row&&row.canCoverResidual;});
      if(canCover)fullCoverage++;
      else split++;
      coverageScore+=Math.max.apply(Math,sides.map(function(row){return row?row.coverageRatio:0;}));
    });
    var maxPair=Math.max.apply(Math,pairs.map(function(pair){return pair.preparedCandidateCount;}));
    var totalPair=sum(pairs.map(function(pair){return pair.preparedCandidateCount;}));
    var mode=pairs.every(function(pair){return pair.materializationEligible;})?'materialize':'lazy-box';
    return Object.freeze({
      id:definition.id,pairs:Object.freeze(pairs),mode:mode,
      activeUtilityCount:active.length,splitUtilityCount:split,fullCoverageUtilityCount:fullCoverage,
      singleSideCoverageScore:fixed(coverageScore,8),maxPreparedPairCandidates:maxPair,totalPreparedPairCandidates:totalPair,
      maxRawPairCandidates:Math.max.apply(Math,pairs.map(function(pair){return pair.rawCandidateCount;})),
      totalRawPairCandidates:sum(pairs.map(function(pair){return pair.rawCandidateCount;})),
      frontierStatus:mode==='materialize'?'not-measured':'deferred-lazy',
      measurementReason:mode==='materialize'?'Pair Frontier materialization is permitted; Gate D must measure its actual size and time.':'At least one prepared pair exceeds the configured materialization limit; Gate D must use lazy generation/box search.'
    });
  }

  function comparePartitions(left,right){
    var fields=['splitUtilityCount','maxPreparedPairCandidates','totalPreparedPairCandidates','maxRawPairCandidates','totalRawPairCandidates'];
    for(var i=0;i<fields.length;i++){var key=fields[i];if(number(left[key])!==number(right[key]))return number(left[key])-number(right[key]);}
    if(number(left.singleSideCoverageScore)!==number(right.singleSideCoverageScore))return number(right.singleSideCoverageScore)-number(left.singleSideCoverageScore);
    return String(left.id)<String(right.id)?-1:String(left.id)>String(right.id)?1:0;
  }

  function analyzePairPartitions(problem,supplyReport,options){
    var settings=options||{};var rawGroups=groupMap(problem);var preparedProblem=settings.preparedProblem||problem;var preparedGroups=groupMap(preparedProblem);var missing=SLOT_IDS.filter(function(id){return !rawGroups[id]||!preparedGroups[id];});
    var limit=Number.isFinite(Number(settings.pairMaterializationLimit))?Math.max(1,Math.floor(Number(settings.pairMaterializationLimit))):DEFAULT_MATERIALIZATION_LIMIT;
    if(missing.length)return Object.freeze({schema:SCHEMA,policyVersion:PAIR_PARTITION_POLICY_VERSION,status:'invalid',missingGroups:Object.freeze(missing),pairMaterializationLimit:limit,partitions:Object.freeze([]),selection:null});
    var utilities=utilityMap(supplyReport);
    var partitions=PARTITIONS.map(function(definition){return partitionMetrics(definition,rawGroups,preparedGroups,utilities,limit);}).sort(comparePartitions);
    var selected=partitions[0]||null;
    return Object.freeze({
      schema:SCHEMA,policyVersion:PAIR_PARTITION_POLICY_VERSION,status:'ok',pairMaterializationLimit:limit,
      rawGroupCounts:Object.freeze(SLOT_IDS.reduce(function(result,id){result[id]=countOf(rawGroups,id);return result;},{})),
      preparedGroupCounts:Object.freeze(SLOT_IDS.reduce(function(result,id){result[id]=countOf(preparedGroups,id);return result;},{})),
      partitions:Object.freeze(partitions),
      selection:selected?Object.freeze({id:selected.id,mode:selected.mode,reason:Object.freeze({
        splitUtilityCount:selected.splitUtilityCount,singleSideCoverageScore:selected.singleSideCoverageScore,
        maxPreparedPairCandidates:selected.maxPreparedPairCandidates,totalPreparedPairCandidates:selected.totalPreparedPairCandidates
      })}):null
    });
  }

  var api=Object.freeze({schema:SCHEMA,pairPartitionPolicyVersion:PAIR_PARTITION_POLICY_VERSION,defaultMaterializationLimit:DEFAULT_MATERIALIZATION_LIMIT,partitions:PARTITIONS,analyzePairPartitions:analyzePairPartitions});
  if(typeof module==='object'&&module.exports)module.exports=api;if(root)root.ToramD4PairPartition=api;
}(typeof window!=='undefined'?window:globalThis));
