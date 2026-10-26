(function (root) {
  'use strict';

  var SCHEMA = 'toram.crysta-native-parallel-client.v1';
  // These identifiers are deliberately part of the cache contract.  A formula,
  // tree-splitting, runtime or GPU-policy change must not reuse a result made
  // under a different exact-search contract.
  var CALCULATION_VERSION = 'optimization-native-evaluator.v5';
  var ENGINE_VERSION = 'optimization-native-solver.v25';
  var SPLIT_POLICY = 'candidate-tree-stat-weighted-projected-2axis-gap-work-smallbox64-lookahead-precheck.v9';
  var GPU_POLICY = 'cpu-only.v1';

  function evaluatorAdapter(problem) {
    var evaluator = root.ToramBuildEvaluator;
    var kernel = root.ToramCalculationKernel && root.ToramCalculationKernel.evaluateContext;
    if (!evaluator || typeof evaluator.evaluateAggregate !== 'function') throw new Error('CrystaOptimization BuildEvaluator가 필요합니다.');
    var scenario = problem.scenarioSnapshot || evaluator.createScenarioSnapshot(problem.baseContext);
    return function (stats) {
      return evaluator.evaluateAggregate(problem.baseContext, scenario, stats || {}, kernel);
    };
  }

  function prepare(problem, options) {
    var optimizer = root.ToramCrystaOptimizationCandidates;
    if (!optimizer || typeof optimizer.prepareProblem !== 'function' || typeof optimizer.deriveRelevantKeys !== 'function') throw new Error('CrystaOptimization 전역 탐색기가 연결되지 않았습니다.');
    var adapter = evaluatorAdapter(problem);
    var keys = optimizer.deriveRelevantKeys(problem, root.ToramStatRegistry, adapter);
    return {
      problem:optimizer.prepareProblem(problem, {
        registry:root.ToramStatRegistry,
        relevantKeys:keys,
        disableCandidateProjection:Boolean(options && options.disableCandidateProjection),
        pareto:{ maxComparisons:Number(options && options.maxParetoComparisons) || 1000000 }
      }),
      evaluate:adapter
    };
  }

  function restoreBuild(prepared, nativeBuild) {
    if (!nativeBuild || !Array.isArray(nativeBuild.packageIds) || nativeBuild.packageIds.length !== prepared.groups.length) return null;
    var packages = nativeBuild.packageIds.map(function (id, groupIndex) {
      var group = prepared.groups[groupIndex] || {};
      return (group.packages || []).find(function (candidate) { return String(candidate.id) === String(id); }) || null;
    });
    if (packages.some(function (candidate) { return !candidate; })) return null;
    return { id:nativeBuild.id, packages:packages, statDelta:nativeBuild.statDelta || {} };
  }

  // Match Rust NativeProblem/NativeMetadata/NativeGroup/NativePackage.
  // Keep full raw options: modeledKeys describes search bounds, not the
  // complete evaluator dependencies or the options returned to the user.
  function nativeProblem(prepared) {
    var metadata = prepared.metadata || {};
    var projection = metadata.candidateProjection;
    var initialPackageIds = metadata.initialPackageIds;
    // Rust accepts only complete warm starts; unavailable current packages are null.
    var completeInitialBuild = Array.isArray(initialPackageIds) && initialPackageIds.length === prepared.groups.length &&
      initialPackageIds.every(function (id) { return typeof id === 'string'; });
    return {
      baseContext:prepared.baseContext,
      scenarioSnapshot:prepared.scenarioSnapshot,
      metadata:Object.assign({ modeledKeys:metadata.modeledKeys, initialPackageIds:completeInitialBuild ? initialPackageIds : undefined }, projection ? {searchKeys:projection.keys} : {}),
      groups:prepared.groups.map(function (group) {
        return {
          id:group.id,
          packages:group.packages.map(function (candidate) {
            return Object.assign({ id:candidate.id, statDelta:candidate.statDelta }, projection ? {searchValues:projection.keys.map(function(key){return candidate.searchProjection[key];})} : {});
          })
        };
      })
    };
  }

  function optimalityGap(lower, upper, exact) {
    if (exact) return 0;
    if (lower == null || upper == null) return null;
    var lowerBound = Number(lower), upperBound = Number(upper);
    if (!Number.isFinite(lowerBound) || !Number.isFinite(upperBound)) return null;
    return Math.max(0, upperBound - lowerBound) / Math.max(Math.abs(lowerBound), 1e-9);
  }

  function normalize(prepared, evaluate, result, profile) {
    var build = restoreBuild(prepared, result && result.bestBuild);
    var exact = Boolean(result && result.exact);
    var threads = Math.floor(Number(result && result.threadsUsed));
    if (!Number.isFinite(threads) || threads < 1) threads = Math.floor(Number(profile && profile.logicalThreads)) || 1;
    var lowerBound = build ? Number(result && result.score) : null;
    var upperBound = exact ? lowerBound : (result && result.upperBound != null ? Number(result.upperBound) : null);
    return Object.assign({}, result || {}, {
      schema:SCHEMA,
      engine:'rust-native',
      engineVersion:ENGINE_VERSION,
      calculationVersion:CALCULATION_VERSION,
      splitPolicy:SPLIT_POLICY,
      gpuPolicy:GPU_POLICY,
      threadsUsed:threads,
      status:result && result.status || 'invalid',
      bestBuild:build,
      outcomes:build ? evaluate(build.statDelta) : null,
      lowerBound:lowerBound,
      upperBound:upperBound,
      optimalityGap:optimalityGap(lowerBound, upperBound, exact),
      frontierReports:prepared.metadata && prepared.metadata.paretoReports || [],
      candidateProjectionReport:prepared.metadata && prepared.metadata.candidateProjection || null,
      diagnostics:result && result.diagnostics || []
    });
  }

  root.ToramCrystaOptimizationRustBridge = Object.freeze({
    prepare:prepare, projectProblem:nativeProblem, normalize:normalize, evaluate:evaluatorAdapter, gap:optimalityGap,
    policy:Object.freeze({ calculationVersion:CALCULATION_VERSION, engineVersion:ENGINE_VERSION, splitPolicy:SPLIT_POLICY, gpuPolicy:GPU_POLICY })
  });
})(typeof window !== 'undefined' ? window : globalThis);
