'use strict';

self.window = self;
const BASE_ASPD_MAP = {
  '한손검':100, '양손검':50, '활':75, '자동활':30, '지팡이':60,
  '마도구':90, '권갑':120, '선풍창':25, '발도검':200, '맨손':1000
};

importScripts(
  'stat-registry.js',
  'calculator.js',
  'build-evaluator.js',
  'd4-source-profile.js',
  'd4-dynamic-marginal.js',
  'd4-dynamic-seed.js',
  'd4-pair-partition.js',
  'd4-global-optimizer.js'
);

var DYNAMIC_ACCELERATION_DEFAULTS = Object.freeze({
  enableDynamicSeedIncumbent:true,
  enableDynamicSeedOrdering:true,
  dynamicSeedTimeLimitMs:1500,
  dynamicSeedEvaluationLimit:10000,
  dynamicSeedLocalEvaluationLimit:1000,
  dynamicSeedCartesianLimit:64,
  dynamicSeedBeamWidth:32,
  dynamicSeedRepairInputLimit:2,
  dynamicSeedRepairPerGroupLimit:4,
  dynamicSeedRepairPairLimit:3,
  dynamicSeedLocalStartLimit:2,
  dynamicSeedLocalPassLimit:1,
  dynamicSeedLocalCandidateLimit:4,
  dynamicSeedLocalPairCandidateLimit:2
});

var parallelPlan = null;

function dynamicOptionsFor(requestedOptions) {
  return requestedOptions && requestedOptions.enableDynamicSeedIncumbent === false
    ? { enableDynamicSeedIncumbent:false, enableDynamicSeedOrdering:false }
    : DYNAMIC_ACCELERATION_DEFAULTS;
}

function optimizerOptions(requestedOptions, progressCallback) {
  var requested = requestedOptions || {};
  return Object.assign({}, requested, dynamicOptionsFor(requested), {
    registry:self.ToramStatRegistry,
    evaluator:self.ToramBuildEvaluator,
    sourceProfile:self.ToramD4SourceProfile,
    kernel:self.ToramCalculationKernel.evaluateContext,
    onProgress:progressCallback
  });
}

function findShard(plan, shardId) {
  return (plan && plan.shards || []).find(function (shard) { return String(shard.id) === String(shardId); }) || null;
}

function reportError(version, error) {
  self.postMessage({ type:'error', version:version, message:error && error.message ? error.message : String(error) });
}

self.onmessage = function (event) {
  var message = event && event.data || {};
  var version = message.version;
  try {
    if (message.type === 'optimize') {
      self.postMessage({ type:'progress', version:version, progress:{ stage:'preparing', status:'running', elapsedMs:0, visitedNodes:0, evaluations:0, lowerBound:null, upperBound:null, optimalityGap:null } });
      var result = self.ToramD4GlobalOptimizer.optimize(message.problem, optimizerOptions(message.options, function (progress) {
        self.postMessage({ type:'progress', version:version, progress:progress });
      }));
      self.postMessage({ type:'result', version:version, result:result });
      return;
    }
    if (message.type === 'prepare-parallel') {
      var requested = message.options || {};
      parallelPlan = self.ToramD4GlobalOptimizer.createParallelShardPlan(message.problem, optimizerOptions(Object.assign({}, requested, { targetShards:message.targetShards || requested.targetShards }), null));
      if (!parallelPlan || parallelPlan.status !== 'ready') { self.postMessage({ type:'parallel-plan', version:version, plan:parallelPlan }); return; }
      var initialBudget = Math.max(1, Math.min(Number(requested.timeLimitMs) || 5000, Number(requested.parallelInitialTimeLimitMs) || Math.min(1500, Math.max(250, Math.floor((Number(requested.timeLimitMs) || 5000) * 0.3)))));
      var initialResult = self.ToramD4GlobalOptimizer.optimize(parallelPlan.preparedProblem, Object.assign({}, optimizerOptions(Object.assign({}, requested, { timeLimitMs:initialBudget }), null), { prepared:true }));
      parallelPlan = Object.assign({}, parallelPlan, { initialResult:initialResult });
      self.postMessage({ type:'parallel-plan', version:version, plan:parallelPlan });
      return;
    }
    if (message.type === 'parallel-init') {
      parallelPlan = message.plan || null;
      if (!parallelPlan || parallelPlan.schema !== self.ToramD4GlobalOptimizer.parallelShardSchema) throw new Error('유효한 병렬 shard plan이 필요합니다.');
      self.postMessage({ type:'parallel-ready', version:version });
      return;
    }
    if (message.type === 'optimize-parallel-shard') {
      if (!parallelPlan || parallelPlan.schema !== self.ToramD4GlobalOptimizer.parallelShardSchema) throw new Error('병렬 shard plan이 초기화되지 않았습니다.');
      var shard = findShard(parallelPlan, message.shardId);
      if (!shard) throw new Error('요청한 병렬 shard를 찾을 수 없습니다.');
      var shardProblem = self.ToramD4GlobalOptimizer.createParallelShardProblem(parallelPlan, shard);
      self.postMessage({ type:'parallel-shard-progress', version:version, shardId:shard.id, progress:{ stage:'preparing-shard', status:'running', elapsedMs:0, visitedNodes:0, evaluations:0, lowerBound:null, upperBound:shard.upper, optimalityGap:null } });
      var shardResult = self.ToramD4GlobalOptimizer.optimize(shardProblem, Object.assign({}, optimizerOptions(message.options, function (progress) {
        self.postMessage({ type:'parallel-shard-progress', version:version, shardId:shard.id, progress:progress });
      }), { prepared:true }));
      self.postMessage({ type:'parallel-shard-result', version:version, shardId:shard.id, result:shardResult });
      return;
    }
    if (message.type === 'merge-parallel') {
      var mergePlan = message.plan || parallelPlan;
      var merged = self.ToramD4GlobalOptimizer.mergeParallelShardResults(mergePlan, message.entries || []);
      self.postMessage({ type:'parallel-result', version:version, result:merged });
      return;
    }
  } catch (error) {
    reportError(version, error);
  }
};
