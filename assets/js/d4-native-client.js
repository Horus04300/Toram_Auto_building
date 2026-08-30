(function (root) {
  'use strict';

  var SCHEMA = 'toram.d4-native-parallel-client.v1';
  // These identifiers are deliberately part of the cache contract.  A formula,
  // tree-splitting, runtime or GPU-policy change must not reuse a result made
  // under a different exact-search contract.
  var CALCULATION_VERSION = 'd4-native-evaluator.v1';
  var ENGINE_VERSION = 'd4-native-solver.v1';
  var SPLIT_POLICY = 'candidate-tree-2axis-smallbox64.v1';
  var GPU_POLICY = 'cpu-only.p7';

  function invoke() {
    var tauri = root && root.__TAURI__;
    return tauri && tauri.core && typeof tauri.core.invoke === 'function' ? tauri.core.invoke : null;
  }

  function nextJobId() {
    return 'd4-' + Date.now().toString(36) + '-' + Math.random().toString(36).slice(2, 12);
  }

  function stableStringify(value) {
    if (value === null || typeof value !== 'object') return JSON.stringify(value);
    if (Array.isArray(value)) return '[' + value.map(stableStringify).join(',') + ']';
    return '{' + Object.keys(value).sort().map(function (key) { return JSON.stringify(key) + ':' + stableStringify(value[key]); }).join(',') + '}';
  }

  function hashString(text) {
    var hash = 2166136261;
    for (var index = 0; index < text.length; index++) { hash ^= text.charCodeAt(index); hash = Math.imul(hash, 16777619); }
    return ('00000000' + (hash >>> 0).toString(16)).slice(-8);
  }

  function cacheKey(problem, options, profile) {
    if (!profile || !Number.isFinite(Number(profile.logicalThreads))) return null;
    var budget = Math.max(1, Math.floor(Number(options && options.timeLimitMs) || 5000));
    return [SCHEMA, CALCULATION_VERSION, ENGINE_VERSION, SPLIT_POLICY, 'threads=' + Math.max(1, Math.floor(Number(profile.logicalThreads))), 'gpu=' + GPU_POLICY, 'budget=' + budget, hashString(stableStringify(problem))].join(':');
  }

  function loadHardwareProfile(run) {
    return Promise.resolve(run('d4_hardware_profile')).then(function (profile) {
      var threads = Math.floor(Number(profile && profile.logicalThreads));
      return Number.isFinite(threads) && threads > 0 ? { logicalThreads:threads } : null;
    }).catch(function () { return null; });
  }

  function evaluatorAdapter(problem) {
    var evaluator = root.ToramBuildEvaluator;
    var kernel = root.ToramCalculationKernel && root.ToramCalculationKernel.evaluateContext;
    if (!evaluator || typeof evaluator.evaluateAggregate !== 'function') throw new Error('D4 BuildEvaluator가 필요합니다.');
    var scenario = problem.scenarioSnapshot || evaluator.createScenarioSnapshot(problem.baseContext);
    return function (stats) {
      return evaluator.evaluateAggregate(problem.baseContext, scenario, stats || {}, kernel);
    };
  }

  function prepare(problem, options) {
    var optimizer = root.ToramD4GlobalOptimizer;
    if (!optimizer || typeof optimizer.prepareProblem !== 'function' || typeof optimizer.deriveRelevantKeys !== 'function') throw new Error('D4 전역 탐색기가 연결되지 않았습니다.');
    var adapter = evaluatorAdapter(problem);
    var keys = optimizer.deriveRelevantKeys(problem, root.ToramStatRegistry, adapter);
    return {
      problem:optimizer.prepareProblem(problem, {
        registry:root.ToramStatRegistry,
        relevantKeys:keys,
        pareto:{ maxComparisons:Number(options && options.maxParetoComparisons) || 1000000 }
      }),
      evaluate:adapter
    };
  }

  function restoreBuild(prepared, nativeBuild) {
    if (!nativeBuild || !Array.isArray(nativeBuild.packageIds)) return null;
    var packages = nativeBuild.packageIds.map(function (id, groupIndex) {
      var group = prepared.groups[groupIndex] || {};
      return (group.packages || []).find(function (candidate) { return String(candidate.id) === String(id); }) || null;
    });
    if (packages.some(function (candidate) { return !candidate; })) return null;
    return { id:nativeBuild.id, packages:packages, statDelta:nativeBuild.statDelta || {} };
  }

  function normalize(prepared, evaluate, result, profile) {
    var build = restoreBuild(prepared, result && result.bestBuild);
    var exact = Boolean(result && result.exact);
    var threads = Math.floor(Number(result && result.threadsUsed));
    if (!Number.isFinite(threads) || threads < 1) threads = Math.floor(Number(profile && profile.logicalThreads)) || 1;
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
      lowerBound:build ? Number(result.score) : null,
      upperBound:exact ? Number(result.score) : (result && result.upperBound != null ? Number(result.upperBound) : null),
      optimalityGap:exact ? 0 : null,
      diagnostics:result && result.diagnostics || []
    });
  }

  function NativeParallelClient() {
    this.active = null;
    this.cache = new Map();
  }

  NativeParallelClient.prototype.isAvailable = function () { return typeof invoke() === 'function'; };
  NativeParallelClient.prototype.isRunning = function () { return Boolean(this.active); };

  NativeParallelClient.prototype.optimize = function (problem, callbacks, options) {
    var self = this, handlers = callbacks || {}, run = invoke();
    if (!run) return Promise.reject(new Error('D4 네이티브 실행 경로를 사용할 수 없습니다.'));
    this.cancel('새 계산이 시작되어 이전 계산을 취소했습니다.');
    var setup;
    try {
      setup = prepare(problem, options || {});
    } catch (error) {
      return Promise.reject(error);
    }
    var jobId = nextJobId(), active = { jobId:jobId, cancelled:false };
    this.active = active;
    return loadHardwareProfile(run).then(function (profile) {
      if (active.cancelled) {
        var cancelled = normalize(setup.problem, setup.evaluate, { status:'cancelled', exact:false }, profile);
        if (self.active === active) self.active = null;
        if (typeof handlers.onComplete === 'function') handlers.onComplete(cancelled, { native:true, cancelled:true, cached:false });
        return cancelled;
      }
      var key = cacheKey(setup.problem, options || {}, profile), cached = key && self.cache.get(key);
      if (cached) {
        if (self.active === active) self.active = null;
        if (typeof handlers.onProgress === 'function') handlers.onProgress(Object.assign({}, cached, { stage:'native-cache', elapsedMs:0, cached:true }));
        if (typeof handlers.onComplete === 'function') handlers.onComplete(cached, { native:true, cached:true });
        return cached;
      }
      if (typeof handlers.onProgress === 'function') handlers.onProgress({ stage:'native-prepared', status:'running', elapsedMs:0, visitedNodes:0, evaluations:0, engine:'rust-native', engineVersion:ENGINE_VERSION, calculationVersion:CALCULATION_VERSION, splitPolicy:SPLIT_POLICY, gpuPolicy:GPU_POLICY, threadsUsed:profile && profile.logicalThreads || null, native:true });
      return Promise.resolve(run('d4_optimize_parallel', { jobId:jobId, problem:setup.problem })).then(function (nativeResult) {
        var result = normalize(setup.problem, setup.evaluate, nativeResult, profile);
        if (key && (result.status === 'exact' || result.status === 'bounded')) self.cache.set(key, result);
        if (self.active === active) self.active = null;
        if (typeof handlers.onComplete === 'function') handlers.onComplete(result, { native:true, cancelled:result.status === 'cancelled', cached:false });
        return result;
      });
    }).catch(function (error) {
      if (self.active === active) self.active = null;
      throw error;
    });
  };

  NativeParallelClient.prototype.cancel = function () {
    var active = this.active, run = invoke();
    if (!active || active.cancelled || !run) return false;
    active.cancelled = true;
    Promise.resolve(run('cancel_d4_optimization', { jobId:active.jobId })).catch(function () {});
    return true;
  };

  NativeParallelClient.prototype.clearCache = function () { this.cache.clear(); };

  var client = new NativeParallelClient();
  root.ToramD4NativeClient = Object.freeze({
    schema:SCHEMA,
    optimize:client.optimize.bind(client),
    cancel:client.cancel.bind(client),
    clearCache:client.clearCache.bind(client),
    isAvailable:client.isAvailable.bind(client),
    isRunning:client.isRunning.bind(client),
    cachePolicy:Object.freeze({ calculationVersion:CALCULATION_VERSION, engineVersion:ENGINE_VERSION, splitPolicy:SPLIT_POLICY, gpuPolicy:GPU_POLICY })
  });
})(typeof window !== 'undefined' ? window : globalThis);
