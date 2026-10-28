import {rustBridge} from '../../web/src/optimization/rust-bridge.js';
export function createNativeClient(core) {
  'use strict';

  var SCHEMA = 'toram.crysta-native-parallel-client.v1';
  var bridge = rustBridge;
  var CALCULATION_VERSION = bridge.policy.calculationVersion;
  var ENGINE_VERSION = bridge.policy.engineVersion;
  var SPLIT_POLICY = bridge.policy.splitPolicy;
  var GPU_POLICY = bridge.policy.gpuPolicy;

  function invoke() {
    return core && typeof core.invoke === 'function' ? core.invoke : null;
  }

  function progressChannel(onmessage) {
    if (!core || typeof core.Channel !== 'function') return null;
    var channel = new core.Channel();
    channel.onmessage = onmessage;
    return channel;
  }

  function nextJobId() {
    return 'optimization-' + Date.now().toString(36) + '-' + Math.random().toString(36).slice(2, 12);
  }

  function stableStringify(value) {
    if (value === null || typeof value !== 'object') return JSON.stringify(value);
    if (Array.isArray(value)) return '[' + value.map(stableStringify).join(',') + ']';
    var keys = Object.keys(value);
    // These coordinates are derived from raw options and the versioned plan.
    if (value.statDelta && value.searchProjection) keys = keys.filter(function (key) { return key !== 'searchProjection' && key !== 'searchProjectionClass'; });
    return '{' + keys.sort().map(function (key) { return JSON.stringify(key) + ':' + stableStringify(value[key]); }).join(',') + '}';
  }

  function cacheKey(problem, options, profile) {
    if (!profile || !Number.isFinite(Number(profile.logicalThreads))) return null;
    var budget = Math.max(1, Math.floor(Number(options && options.timeLimitMs) || 30000));
    var key = [SCHEMA, CALCULATION_VERSION, ENGINE_VERSION, SPLIT_POLICY, 'threads=' + Math.max(1, Math.floor(Number(profile.logicalThreads))), 'gpu=' + GPU_POLICY, 'budget=' + budget, stableStringify(problem)].join(':');
    return key.length <= 4 * 1024 * 1024 ? key : null;
  }

  function loadHardwareProfile(run) {
    return Promise.resolve(run('crysta_hardware_profile')).then(function (profile) {
      var threads = Math.floor(Number(profile && profile.logicalThreads));
      return Number.isFinite(threads) && threads > 0 ? { logicalThreads:threads } : null;
    }).catch(function () { return null; });
  }

  var prepare = bridge.prepare, nativeProblem = bridge.projectProblem, normalize = bridge.normalize, optimalityGap = bridge.gap;

  function continuationState(id, prepared, evaluate, profile, result) {
    return {
      id:id,
      prepared:prepared,
      evaluate:evaluate,
      profile:profile,
      progress:{
        elapsedMs:result.elapsedMs,
        lowerBound:result.lowerBound,
        upperBound:result.upperBound,
        evaluations:result.evaluations,
        visitedNodes:result.visitedNodes,
        prunedByBound:result.prunedByBound,
        readyWorkItems:result.readyWorkItems,
        optimalityGap:result.optimalityGap
      }
    };
  }

  function NativeParallelClient() {
    this.active = null;
    this.continuation = null;
    this.cache = null;
  }

  NativeParallelClient.prototype.isAvailable = function () { return typeof invoke() === 'function'; };
  NativeParallelClient.prototype.isRunning = function () { return Boolean(this.active); };

  NativeParallelClient.prototype.optimize = function (problem, callbacks, options) {
    var self = this, handlers = callbacks || {}, run = invoke();
    if (!run) return Promise.reject(new Error('CrystaOptimization 네이티브 실행 경로를 사용할 수 없습니다.'));
    this.cancel('새 계산이 시작되어 이전 계산을 취소했습니다.');
    var disposal = this.disposeContinuation();
    var startedAt = Date.now();
    var requestedBudget = Math.max(1, Math.floor(Number(options && options.timeLimitMs) || 30000));
    var setup;
    try {
      setup = prepare(problem, options || {});
    } catch (error) {
      return Promise.reject(error);
    }
    var jobId = nextJobId(), active = { jobId:jobId, cancelled:false };
    this.active = active;
    return Promise.resolve(disposal).then(function () { return loadHardwareProfile(run); }).then(function (profile) {
      if (active.cancelled) {
        var cancelled = normalize(setup.problem, setup.evaluate, { status:'cancelled', exact:false }, profile);
        if (self.active === active) self.active = null;
        if (typeof handlers.onComplete === 'function') handlers.onComplete(cancelled, { native:true, cancelled:true, cached:false });
        return cancelled;
      }
      var key = cacheKey(setup.problem, options || {}, profile), cached = self.cache && self.cache.key === key && Date.now() - self.cache.savedAt < 300000 ? self.cache.result : null;
      if (!cached) self.cache = null;
      if (cached) {
        if (self.active === active) self.active = null;
        if (typeof handlers.onProgress === 'function') handlers.onProgress(Object.assign({}, cached, { stage:'native-cache', elapsedMs:0, cached:true }));
        if (typeof handlers.onComplete === 'function') handlers.onComplete(cached, { native:true, cached:true });
        return cached;
      }
      if (typeof handlers.onProgress === 'function') handlers.onProgress({ stage:'native-prepared', status:'running', elapsedMs:0, visitedNodes:0, evaluations:0, engine:'rust-native', engineVersion:ENGINE_VERSION, calculationVersion:CALCULATION_VERSION, splitPolicy:SPLIT_POLICY, gpuPolicy:GPU_POLICY, threadsUsed:profile && profile.logicalThreads || null, native:true });
      var requestProblem = nativeProblem(setup.problem);
      var remainingBudget = Math.max(1, requestedBudget - (Date.now() - startedAt));
      var progress = progressChannel(function (event) {
        if (self.active !== active || active.cancelled || typeof handlers.onProgress !== 'function') return;
        var snapshot = Object.assign({}, event || {}, { native:true, engine:'rust-native', engineVersion:ENGINE_VERSION, calculationVersion:CALCULATION_VERSION, splitPolicy:SPLIT_POLICY, gpuPolicy:GPU_POLICY });
        snapshot.optimalityGap = optimalityGap(snapshot.lowerBound, snapshot.upperBound, false);
        snapshot.threadsUsed = Number(snapshot.threadsTotal) || (profile && profile.logicalThreads) || null;
        handlers.onProgress(snapshot);
      });
      return Promise.resolve(run('crysta_optimize_parallel', {
        jobId:jobId,
        problem:requestProblem,
        options:{ remainingBudgetMs:remainingBudget, progressIntervalMs:Math.max(50, Number(options && options.progressIntervalMs) || 100) },
        progress:progress
      })).then(function (nativeResult) {
        var result = normalize(setup.problem, setup.evaluate, nativeResult, profile);
        if (result.continuationId) {
          self.continuation = continuationState(result.continuationId, setup.problem, setup.evaluate, profile, result);
        } else {
          self.continuation = null;
        }
        // A bounded result is only useful while its native frontier remains in
        // the session registry.  Caching it would later make a stale button
        // look resumable, so cache only terminal exact results.
        if (key && result.status === 'exact') self.cache = { key:key, result:result, savedAt:Date.now() };
        if (self.active === active) self.active = null;
        if (typeof handlers.onComplete === 'function') handlers.onComplete(result, { native:true, cancelled:result.status === 'cancelled', cached:false });
        return result;
      });
    }).catch(function (error) {
      if (self.active === active) self.active = null;
      throw error;
    });
  };

  NativeParallelClient.prototype.resume = function (callbacks, options) {
    var self = this, handlers = callbacks || {}, run = invoke(), continuation = this.continuation;
    if (!run) return Promise.reject(new Error('CrystaOptimization 네이티브 실행 경로를 사용할 수 없습니다.'));
    if (!continuation || !continuation.id) {
      var unavailable = new Error('정밀 계산 세션이 만료되었습니다. 새 전역 계산을 시작해 주세요.');
      unavailable.code = 'OPTIMIZATION_CONTINUATION_UNAVAILABLE';
      return Promise.reject(unavailable);
    }
    this.cancel('정밀 계산을 시작합니다.');
    // Rust removes the stored session while it is running.  Keep the client
    // from issuing a duplicate resume; a bounded return below installs it
    // again with the same continuation id.
    this.continuation = null;
    var requestedBudget = Math.max(1, Math.floor(Number(options && options.timeLimitMs) || 30000));
    var jobId = nextJobId(), active = { jobId:jobId, cancelled:false, continuationId:continuation.id };
    this.active = active;
    if (typeof handlers.onProgress === 'function') handlers.onProgress(Object.assign({}, continuation.progress || {}, { stage:'native-resume', status:'running', engine:'rust-native', engineVersion:ENGINE_VERSION, calculationVersion:CALCULATION_VERSION, splitPolicy:SPLIT_POLICY, gpuPolicy:GPU_POLICY, threadsUsed:continuation.profile && continuation.profile.logicalThreads || null, native:true, resumed:true }));
    var progress = progressChannel(function (event) {
      if (self.active !== active || active.cancelled || typeof handlers.onProgress !== 'function') return;
      var snapshot = Object.assign({}, event || {}, { native:true, resumed:true, engine:'rust-native', engineVersion:ENGINE_VERSION, calculationVersion:CALCULATION_VERSION, splitPolicy:SPLIT_POLICY, gpuPolicy:GPU_POLICY });
      snapshot.optimalityGap = optimalityGap(snapshot.lowerBound, snapshot.upperBound, false);
      snapshot.threadsUsed = Number(snapshot.threadsTotal) || (continuation.profile && continuation.profile.logicalThreads) || null;
      handlers.onProgress(snapshot);
    });
    return Promise.resolve(run('resume_crysta_optimization', {
      jobId:jobId,
      continuationId:continuation.id,
      options:{ remainingBudgetMs:requestedBudget, progressIntervalMs:Math.max(50, Number(options && options.progressIntervalMs) || 100) },
      progress:progress
    })).then(function (nativeResult) {
      var result = normalize(continuation.prepared, continuation.evaluate, nativeResult, continuation.profile);
      if (result.continuationId) {
        self.continuation = continuationState(result.continuationId, continuation.prepared, continuation.evaluate, continuation.profile, result);
      }
      var key = cacheKey(continuation.prepared, options || {}, continuation.profile);
      if (key && result.status === 'exact') self.cache = { key:key, result:result, savedAt:Date.now() };
      if (self.active === active) self.active = null;
      if (typeof handlers.onComplete === 'function') handlers.onComplete(result, { native:true, resumed:true, cancelled:result.status === 'cancelled', cached:false });
      return result;
    }).catch(function (error) {
      if (self.active === active) self.active = null;
      var message = String(error && error.message || error || '');
      if (/만료|존재하지/.test(message)) {
        var unavailable = new Error('정밀 계산 세션이 만료되었습니다. 새 전역 계산을 시작해 주세요.');
        unavailable.code = 'OPTIMIZATION_CONTINUATION_UNAVAILABLE';
        throw unavailable;
      }
      throw error;
    });
  };

  NativeParallelClient.prototype.cancel = function () {
    var active = this.active, run = invoke();
    if (!active || active.cancelled || !run) return false;
    active.cancelled = true;
    if (active.continuationId) this.continuation = null;
    Promise.resolve(run('cancel_crysta_optimization', { jobId:active.jobId })).catch(function () {});
    return true;
  };

  // Pause keeps the Rust frontier and incumbent in the continuation registry.
  // It is intentionally distinct from cancel, which discards the session.
  NativeParallelClient.prototype.pause = function () {
    var active = this.active, run = invoke();
    if (!active || active.cancelled || active.pausing || !run) return false;
    active.pausing = true;
    Promise.resolve(run('pause_crysta_optimization', { jobId:active.jobId })).catch(function () {});
    return true;
  };

  NativeParallelClient.prototype.disposeContinuation = function () {
    var continuation = this.continuation, run = invoke();
    this.continuation = null;
    if (!continuation || !continuation.id || !run) return Promise.resolve(false);
    return Promise.resolve(run('dispose_crysta_optimization', { continuationId:continuation.id })).catch(function () { return false; });
  };

  NativeParallelClient.prototype.hasContinuation = function () { return Boolean(this.continuation && this.continuation.id); };

  var client = new NativeParallelClient();
  return Object.freeze({
    schema:SCHEMA,
    optimize:client.optimize.bind(client),
    resume:client.resume.bind(client),
    cancel:client.cancel.bind(client),
    pause:client.pause.bind(client),
    disposeContinuation:client.disposeContinuation.bind(client),
    hasContinuation:client.hasContinuation.bind(client),
    isAvailable:client.isAvailable.bind(client),
    isRunning:client.isRunning.bind(client),
    cachePolicy:Object.freeze({ calculationVersion:CALCULATION_VERSION, engineVersion:ENGINE_VERSION, splitPolicy:SPLIT_POLICY, gpuPolicy:GPU_POLICY })
  });
}
