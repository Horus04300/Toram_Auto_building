(function (root) {
  'use strict';

  var SCHEMA = 'toram.d4-worker-client.v1';
  var PARALLEL_SCHEMA = 'toram.d4-parallel-worker-client.v1';
  var WORKER_URL = 'assets/js/d4-optimizer-worker.js';
  // S7 approved profile: seed work raises only the lower bound, and ordering
  // resolves split-value ties. Neither setting removes an exact candidate.
  var DYNAMIC_ACCELERATION_POLICY = 'd4-dynamic-seed-ordering.s7.v1';
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

  function dynamicAccelerationOptions(settings) {
    if (settings && settings.enableDynamicSeedIncumbent === false) return { enableDynamicSeedIncumbent:false, enableDynamicSeedOrdering:false };
    return DYNAMIC_ACCELERATION_DEFAULTS;
  }

  function stableStringify(value) {
    if (root.ToramBuildEvaluator && typeof root.ToramBuildEvaluator.stableStringify === 'function') return root.ToramBuildEvaluator.stableStringify(value);
    if (value === null || typeof value !== 'object') return JSON.stringify(value);
    if (Array.isArray(value)) return '[' + value.map(stableStringify).join(',') + ']';
    return '{' + Object.keys(value).sort().map(function (key) { return JSON.stringify(key) + ':' + stableStringify(value[key]); }).join(',') + '}';
  }

  function hashString(text) {
    var hash = 2166136261;
    for (var i = 0; i < text.length; i++) { hash ^= text.charCodeAt(i); hash = Math.imul(hash, 16777619); }
    return ('00000000' + (hash >>> 0).toString(16)).slice(-8);
  }

  function problemCacheKey(problem) {
    var compact = {
      schema:problem && problem.schema,
      structure:problem && problem.structure,
      baseContext:problem && problem.baseContext,
      scenario:problem && problem.scenarioSnapshot,
      groups:(problem && problem.groups || []).map(function (group) { return { id:group.id, packages:(group.packages || []).map(function (item) { return [item.id, item.statDelta]; }) }; })
    };
    var pairPolicy=root.ToramD4PairPartition&&root.ToramD4PairPartition.pairPartitionPolicyVersion||'none';
    var frontierPolicy=root.ToramD4GlobalOptimizer&&root.ToramD4GlobalOptimizer.pairFrontierPolicyVersion||'none';
    return SCHEMA + ':' + pairPolicy + ':' + frontierPolicy + ':' + hashString(stableStringify(compact));
  }

  function optimizationOptions(settings, dynamicOptions, remainingMs) {
    var input = settings || {};
    return Object.assign({
      timeLimitMs:Number.isFinite(Number(remainingMs)) ? Math.max(1, Math.floor(Number(remainingMs))) : (Number(input.timeLimitMs) > 0 ? Number(input.timeLimitMs) : 5000),
      maxNodes:Number(input.maxNodes) > 0 ? Number(input.maxNodes) : null,
      progressIntervalMs:Number(input.progressIntervalMs) > 0 ? Number(input.progressIntervalMs) : 32,
      parallelInitialTimeLimitMs:Number(input.parallelInitialTimeLimitMs) > 0 ? Number(input.parallelInitialTimeLimitMs) : null,
      pareto:{ maxComparisons:Number(input.maxParetoComparisons) > 0 ? Number(input.maxParetoComparisons) : 1000000 }
    }, dynamicOptions || {});
  }

  function cancelledResult(active, reason) {
    var progress = active && active.lastProgress || {};
    return {
      schema:SCHEMA,
      status:'cancelled',
      bestBuild:progress.bestBuild || null,
      score:progress.lowerBound === undefined ? null : progress.lowerBound,
      lowerBound:progress.lowerBound === undefined ? null : progress.lowerBound,
      upperBound:progress.upperBound === undefined ? null : progress.upperBound,
      optimalityGap:progress.optimalityGap === undefined ? null : progress.optimalityGap,
      elapsedMs:progress.elapsedMs || 0,
      visitedNodes:progress.visitedNodes || 0,
      evaluations:progress.evaluations || 0,
      diagnostics:[{ code:'USER_CANCELLED', message:reason || '사용자가 계산을 취소했습니다.' }]
    };
  }

  function WorkerClient(options) {
    var settings = options || {};
    this.WorkerConstructor = settings.WorkerConstructor || root.Worker;
    this.workerUrl = settings.workerUrl || WORKER_URL;
    this.cache = new Map();
    this.active = null;
    this.version = 0;
  }

  WorkerClient.prototype.optimize = function (problem, callbacks, options) {
    var self = this, handlers = callbacks || {}, settings = options || {};
    this.cancel('새 계산이 시작되어 이전 계산을 취소했습니다.', true);
    var dynamicOptions = dynamicAccelerationOptions(settings);
    var budgetKey = [DYNAMIC_ACCELERATION_POLICY, Number(settings.timeLimitMs)||5000, Number(settings.maxNodes)||0, Number(settings.maxParetoComparisons)||1000000, dynamicOptions.enableDynamicSeedIncumbent ? 'seed-ordering' : 'off'].join(':');
    var key = problemCacheKey(problem) + ':' + budgetKey, cached = this.cache.get(key);
    if (cached) return Promise.resolve().then(function () { if (typeof handlers.onProgress === 'function') handlers.onProgress({ stage:'cache', status:cached.status, cached:true, optimalityGap:cached.optimalityGap, elapsedMs:0, visitedNodes:cached.visitedNodes, evaluations:cached.evaluations }); if (typeof handlers.onComplete === 'function') handlers.onComplete(cached, { cached:true }); return cached; });
    if (typeof this.WorkerConstructor !== 'function') {
      var unavailable = { schema:SCHEMA, status:'invalid', bestBuild:null, diagnostics:[{ code:'WORKER_UNAVAILABLE', message:'이 실행 환경에서는 백그라운드 계산을 지원하지 않습니다.' }] };
      if (typeof handlers.onComplete === 'function') handlers.onComplete(unavailable, { cached:false });
      return Promise.resolve(unavailable);
    }
    var version = ++this.version, worker = new this.WorkerConstructor(this.workerUrl);
    return new Promise(function (resolve) {
      var active = { worker:worker, version:version, resolve:resolve, handlers:handlers, lastProgress:null, settled:false };
      self.active = active;
      function finish(result, metadata) {
        if (active.settled) return;
        active.settled = true;
        try { worker.terminate(); } catch (_) {}
        if (self.active === active) self.active = null;
        if (result && (result.status === 'exact' || result.status === 'bounded')) self.cache.set(key, result);
        if (typeof handlers.onComplete === 'function') handlers.onComplete(result, metadata || { cached:false });
        resolve(result);
      }
      worker.onmessage = function (event) {
        var message = event && event.data || {};
        if (message.version !== version || active.settled) return;
        if (message.type === 'progress') { active.lastProgress = message.progress || {}; if (typeof handlers.onProgress === 'function') handlers.onProgress(active.lastProgress); return; }
        if (message.type === 'result') finish(message.result, { cached:false });
        else if (message.type === 'error') finish({ schema:SCHEMA, status:'invalid', bestBuild:null, diagnostics:[{ code:'WORKER_ERROR', message:message.message || '백그라운드 계산 중 오류가 발생했습니다.' }] }, { cached:false });
      };
      worker.onerror = function (event) { finish({ schema:SCHEMA, status:'invalid', bestBuild:null, diagnostics:[{ code:'WORKER_ERROR', message:event && event.message || '백그라운드 계산기를 시작하지 못했습니다.' }] }, { cached:false }); };
      worker.postMessage({ type:'optimize', version:version, problem:problem, options:optimizationOptions(settings, dynamicOptions) });
    });
  };

  WorkerClient.prototype.cancel = function (reason, silent) {
    var active = this.active;
    if (!active || active.settled) return false;
    active.settled = true;
    try { active.worker.terminate(); } catch (_) {}
    if (this.active === active) this.active = null;
    var result = cancelledResult(active, reason);
    if (!silent && typeof active.handlers.onComplete === 'function') active.handlers.onComplete(result, { cached:false, cancelled:true });
    active.resolve(result);
    return true;
  };
  WorkerClient.prototype.clearCache = function () { this.cache.clear(); };
  WorkerClient.prototype.isRunning = function () { return Boolean(this.active && !this.active.settled); };

  function resolveParallelWorkerCount(settings, rootObject) {
    var input = settings || {}, requested = Number(input.parallelThreads);
    if (Number.isFinite(requested) && requested > 0) return Math.max(1, Math.floor(requested));
    var supplied = Number(input.hardwareConcurrency);
    if (!Number.isFinite(supplied) || supplied <= 0) supplied = Number(rootObject && rootObject.navigator && rootObject.navigator.hardwareConcurrency);
    return Math.max(1, Math.floor(Number.isFinite(supplied) && supplied > 0 ? supplied : 1));
  }

  function browserHardwareProfile(rootObject) {
    var logical=resolveParallelWorkerCount({},rootObject);
    return { schema:'toram.d4-hardware-profile.v1', logicalThreads:logical, totalMemoryBytes:null, availableMemoryBytes:null, initialShardTarget:logical*8, queueMemoryBudgetBytes:null, source:'browser' };
  }

  function getParallelHardwareProfile(rootObject) {
    var target=rootObject||root,fallback=browserHardwareProfile(target),tauri=target&&target.__TAURI__,invoke=tauri&&tauri.core&&tauri.core.invoke;
    if(typeof invoke!=='function')return Promise.resolve(fallback);
    return Promise.resolve(invoke('d4_hardware_profile')).then(function(profile){
      var logical=Math.max(1,Math.floor(Number(profile&&profile.logicalThreads)||fallback.logicalThreads));
      return {
        schema:'toram.d4-hardware-profile.v1', logicalThreads:logical,
        totalMemoryBytes:Number.isFinite(Number(profile&&profile.totalMemoryBytes))?Number(profile.totalMemoryBytes):null,
        availableMemoryBytes:Number.isFinite(Number(profile&&profile.availableMemoryBytes))?Number(profile.availableMemoryBytes):null,
        initialShardTarget:Math.max(logical,Math.floor(Number(profile&&profile.initialShardTarget)||logical*8)),
        queueMemoryBudgetBytes:Number.isFinite(Number(profile&&profile.queueMemoryBudgetBytes))?Number(profile.queueMemoryBudgetBytes):null,
        source:'tauri'
      };
    }).catch(function(){return fallback;});
  }

  function ParallelWorkerClient(options) {
    var settings = options || {};
    this.WorkerConstructor = settings.WorkerConstructor || root.Worker;
    this.workerUrl = settings.workerUrl || WORKER_URL;
    this.hardwareConcurrency = settings.hardwareConcurrency;
    this.fallbackClient = settings.fallbackClient || new WorkerClient({ WorkerConstructor:this.WorkerConstructor, workerUrl:this.workerUrl });
    this.cache = new Map();
    this.active = null;
    this.version = 0;
  }

  ParallelWorkerClient.prototype.optimize = function (problem, callbacks, options) {
    var self = this, handlers = callbacks || {}, settings = options || {};
    this.cancel('새 계산이 시작되어 이전 계산을 취소했습니다.', true);
    var dynamicOptions = dynamicAccelerationOptions(settings), workerCount = resolveParallelWorkerCount(Object.assign({}, settings, { hardwareConcurrency:settings.hardwareConcurrency || this.hardwareConcurrency }), root), shardFactor = Math.max(1, Math.floor(Number(settings.parallelShardFactor) || 8));
    var budgetKey = [DYNAMIC_ACCELERATION_POLICY, 'parallel-v1', workerCount, shardFactor, Number(settings.timeLimitMs)||5000, Number(settings.parallelInitialTimeLimitMs)||0, Number(settings.maxNodes)||0, Number(settings.maxParetoComparisons)||1000000, dynamicOptions.enableDynamicSeedIncumbent ? 'seed-ordering' : 'off'].join(':');
    var key = problemCacheKey(problem) + ':' + budgetKey, cached = this.cache.get(key);
    if (cached) return Promise.resolve().then(function () { if (typeof handlers.onProgress === 'function') handlers.onProgress({ stage:'parallel-cache', status:cached.status, cached:true, workerThreads:cached.workerThreads, optimalityGap:cached.optimalityGap, elapsedMs:0, visitedNodes:cached.visitedNodes, evaluations:cached.evaluations }); if (typeof handlers.onComplete === 'function') handlers.onComplete(cached, { cached:true }); return cached; });
    if (typeof this.WorkerConstructor !== 'function') {
      var unavailable = { schema:PARALLEL_SCHEMA, status:'invalid', bestBuild:null, diagnostics:[{ code:'WORKER_UNAVAILABLE', message:'이 실행 환경에서는 백그라운드 계산을 지원하지 않습니다.' }] };
      if (typeof handlers.onComplete === 'function') handlers.onComplete(unavailable, { cached:false });
      return Promise.resolve(unavailable);
    }
    var version = ++this.version, startedAt = Date.now(), requestedBudget = Number(settings.timeLimitMs) > 0 ? Number(settings.timeLimitMs) : 5000, deadline = startedAt + requestedBudget, planner = new this.WorkerConstructor(this.workerUrl);
    return new Promise(function (resolve) {
      var active = { planner:planner, workers:[], version:version, resolve:resolve, handlers:handlers, lastProgress:null, settled:false, finalizing:false, fallback:false, startedAt:startedAt, deadline:deadline, workerThreads:0, plan:null, nextShard:0, completed:0, entries:[], deadlineTimer:null, planningTimer:null };
      self.active = active;
      function terminateWorkers() { active.workers.forEach(function (state) { try { state.worker.terminate(); } catch (_) {} }); active.workers=[]; }
      function finish(result, metadata) {
        if (active.settled) return;
        active.settled = true;
        if (active.deadlineTimer) { clearTimeout(active.deadlineTimer); active.deadlineTimer=null; }
        if (active.planningTimer) { clearTimeout(active.planningTimer); active.planningTimer=null; }
        terminateWorkers();
        try { planner.terminate(); } catch (_) {}
        if (self.active === active) self.active = null;
        if (result && (result.status === 'exact' || result.status === 'bounded')) self.cache.set(key, result);
        if (typeof handlers.onComplete === 'function') handlers.onComplete(result, metadata || { cached:false });
        resolve(result);
      }
      function fallbackToSingle(message) {
        if(active.settled||active.fallback)return;
        active.fallback=true;
        if(active.deadlineTimer){clearTimeout(active.deadlineTimer);active.deadlineTimer=null;}
        if(active.planningTimer){clearTimeout(active.planningTimer);active.planningTimer=null;}
        terminateWorkers();try{planner.terminate();}catch(_){}
        var remaining=Math.max(1,deadline-Date.now());
        self.fallbackClient.optimize(problem,handlers,Object.assign({},settings,{timeLimitMs:remaining})).then(function(result){
          if(active.settled)return;active.settled=true;if(self.active===active)self.active=null;
          if(result&&(result.status==='exact'||result.status==='bounded'))self.cache.set(key,result);
          resolve(result);
        });
      }
      function plannerFailure(message) { if(!active.plan&&Date.now()<deadline){fallbackToSingle(message);return;} finish({ schema:PARALLEL_SCHEMA, status:'invalid', bestBuild:null, diagnostics:[{ code:'PARALLEL_WORKER_ERROR', message:message || '병렬 계산기를 시작하지 못했습니다.' }] }, { cached:false }); }
      function shardProgressById(shardId) { for (var index=0;index<active.workers.length;index++) if (active.workers[index].current && String(active.workers[index].current.id)===String(shardId)) return active.workers[index].progress || null; return null; }
      function publishProgress() {
        if (!active.plan || active.settled) return;
        var lower=-Infinity, upper=-Infinity, visited=0, evaluations=0, remaining=0, bestBuild=null, initial=active.plan.initialResult;
        if(initial&&initial.bestBuild&&Number.isFinite(Number(initial.score))){lower=Number(initial.score);bestBuild=initial.bestBuild;visited+=Number(initial.visitedNodes)||0;evaluations+=Number(initial.evaluations)||0;}
        (active.plan.shards || []).forEach(function (shard) {
          var entry=active.entries.find(function (item) { return String(item.shardId)===String(shard.id); });
          if (entry && entry.result) {
            lower=Math.max(lower, Number(entry.result.lowerBound===undefined?entry.result.score:entry.result.lowerBound));
            if(entry.result.bestBuild&&Number(entry.result.lowerBound===undefined?entry.result.score:entry.result.lowerBound)>=lower)bestBuild=entry.result.bestBuild;
            upper=Math.max(upper, Number(entry.result.upperBound));
            visited+=Number(entry.result.visitedNodes)||0; evaluations+=Number(entry.result.evaluations)||0; remaining+=Number(entry.result.remainingNodes)||0;
            return;
          }
          var progress=shardProgressById(shard.id);
          if (progress) {
            lower=Math.max(lower, Number(progress.lowerBound)); upper=Math.max(upper, Number.isFinite(Number(progress.upperBound))?Number(progress.upperBound):Number(shard.upper));
            visited+=Number(progress.visitedNodes)||0; evaluations+=Number(progress.evaluations)||0; remaining+=Number(progress.remainingNodes)||0;
          } else { upper=Math.max(upper, Number(shard.upper)); remaining++; }
        });
        var validLower=Number.isFinite(lower),validUpper=Number.isFinite(upper),snapshot={ stage:'parallel-search', status:'running', workerThreads:active.workerThreads, totalShards:(active.plan.shards||[]).length, completedShards:active.completed, elapsedMs:Date.now()-active.startedAt, visitedNodes:visited, evaluations:evaluations, remainingNodes:remaining, bestBuild:bestBuild, lowerBound:validLower?lower:null, upperBound:validUpper?upper:null, optimalityGap:validLower&&validUpper?Math.max(0,upper-lower)/Math.max(Math.abs(lower),1e-9):null };
        active.lastProgress=snapshot;
        if (typeof handlers.onProgress === 'function') handlers.onProgress(snapshot);
      }
      function remainingBudget() { return Math.max(1, deadline-Date.now()); }
      function finalize() {
        if (active.finalizing || active.settled) return;
        active.finalizing=true;
        terminateWorkers();
        if (!active.plan) { plannerFailure('병렬 shard 계획을 만들기 전에 시간 제한에 도달했습니다.'); return; }
        planner.postMessage({ type:'merge-parallel', version:version, plan:active.plan, entries:active.entries });
      }
      function dispatch(state) {
        if (active.settled || active.finalizing || !state.ready || state.current) return;
        if (Date.now() >= deadline) { finalize(); return; }
        var shards=active.plan.shards || [];
        if (active.nextShard >= shards.length) { if (active.completed >= shards.length) finalize(); return; }
        var shard=shards[active.nextShard++];
        state.current=shard; state.progress=null;
        state.worker.postMessage({ type:'optimize-parallel-shard', version:version, shardId:shard.id, options:optimizationOptions(settings,dynamicOptions,remainingBudget()) });
      }
      function spawnWorkers() {
        var shardCount=(active.plan.shards||[]).length;
        if (!shardCount) { finalize(); return; }
        active.workerThreads=Math.min(workerCount,shardCount);
        for (var index=0;index<active.workerThreads;index++) (function () {
          var worker=new self.WorkerConstructor(self.workerUrl),state={worker:worker,ready:false,current:null,progress:null}; active.workers.push(state);
          worker.onmessage=function (event) {
            var message=event&&event.data||{};
            if (message.version!==version||active.settled||active.finalizing) return;
            if (message.type==='parallel-ready') { state.ready=true; dispatch(state); return; }
            if (message.type==='parallel-shard-progress') { if (state.current&&String(state.current.id)===String(message.shardId)) { state.progress=message.progress||null; publishProgress(); } return; }
            if (message.type==='parallel-shard-result') {
              if (!state.current || String(state.current.id)!==String(message.shardId)) { plannerFailure('병렬 shard 결과의 ID가 현재 작업과 다릅니다.'); return; }
              active.entries.push({shardId:message.shardId,result:message.result}); active.completed++; state.current=null; state.progress=null; publishProgress();
              if (active.completed>=(active.plan.shards||[]).length) finalize(); else dispatch(state);
              return;
            }
            if (message.type==='error') plannerFailure(message.message);
          };
          worker.onerror=function (event) { plannerFailure(event&&event.message||'병렬 shard Worker 오류'); };
          worker.postMessage({ type:'parallel-init', version:version, plan:active.plan });
        }());
        publishProgress();
      }
      planner.onmessage=function (event) {
        var message=event&&event.data||{};
        if (message.version!==version||active.settled) return;
        if (message.type==='parallel-plan') {
          active.plan=message.plan;
          if(active.planningTimer){clearTimeout(active.planningTimer);active.planningTimer=null;}
          if (!active.plan || active.plan.status!=='ready') { finish({ schema:PARALLEL_SCHEMA,status:'invalid',bestBuild:null,diagnostics:(active.plan&&active.plan.diagnostics)||[{code:'PARALLEL_PLAN_INVALID'}] },{cached:false}); return; }
          spawnWorkers();
          return;
        }
        if (message.type==='parallel-result') {
          var result=Object.assign({},message.result||{}, { schema:PARALLEL_SCHEMA, workerThreads:active.workerThreads, totalShards:active.plan&&active.plan.shards&&active.plan.shards.length||0, completedShards:active.completed, elapsedMs:Date.now()-active.startedAt });
          finish(result,{cached:false,parallel:true});
          return;
        }
        if (message.type==='error') plannerFailure(message.message);
      };
      planner.onerror=function (event) { plannerFailure(event&&event.message||'병렬 planner Worker 오류'); };
      active.deadlineTimer=setTimeout(finalize,Math.max(1,requestedBudget));
      active.planningTimer=setTimeout(function(){if(!active.plan)fallbackToSingle('병렬 shard 준비 시간이 예산 대비 과도합니다.');},Math.min(1500,Math.max(250,Math.floor(requestedBudget*0.3))));
      planner.postMessage({ type:'prepare-parallel', version:version, problem:problem, targetShards:workerCount*shardFactor, options:optimizationOptions(settings,dynamicOptions,requestedBudget) });
    });
  };

  ParallelWorkerClient.prototype.cancel = function (reason, silent) {
    var active=this.active;
    if (!active || active.settled) return false;
    if(active.fallback)return this.fallbackClient.cancel(reason,silent);
    active.settled=true;
    if (active.deadlineTimer) clearTimeout(active.deadlineTimer);
    if (active.planningTimer) clearTimeout(active.planningTimer);
    active.workers.forEach(function (state) { try { state.worker.terminate(); } catch (_) {} });
    try { active.planner.terminate(); } catch (_) {}
    if (this.active===active) this.active=null;
    var result=cancelledResult(active,reason);
    result.schema=PARALLEL_SCHEMA;
    if (!silent && typeof active.handlers.onComplete==='function') active.handlers.onComplete(result,{cached:false,cancelled:true,parallel:true});
    active.resolve(result);
    return true;
  };
  ParallelWorkerClient.prototype.clearCache=function(){this.cache.clear();this.fallbackClient.clearCache();};
  ParallelWorkerClient.prototype.isRunning=function(){return Boolean(this.active&&!this.active.settled);};

  var defaultClient = new WorkerClient();
  var defaultParallelClient = new ParallelWorkerClient();
  var api = Object.freeze({
    schema:SCHEMA,
    parallelSchema:PARALLEL_SCHEMA,
    dynamicAccelerationPolicy:DYNAMIC_ACCELERATION_POLICY,
    WorkerClient:WorkerClient,
    ParallelWorkerClient:ParallelWorkerClient,
    problemCacheKey:problemCacheKey,
    resolveParallelWorkerCount:function(settings){return resolveParallelWorkerCount(settings,root);},
    getParallelHardwareProfile:function(){return getParallelHardwareProfile(root);},
    optimize:function(problem,callbacks,options){return defaultClient.optimize(problem,callbacks,options);},
    optimizeParallel:function(problem,callbacks,options){return defaultParallelClient.optimize(problem,callbacks,options);},
    cancel:function(reason){return defaultClient.cancel(reason)||defaultParallelClient.cancel(reason);},
    clearCache:function(){defaultClient.clearCache();defaultParallelClient.clearCache();},
    isRunning:function(){return defaultClient.isRunning()||defaultParallelClient.isRunning();}
  });
  if (typeof module === 'object' && module.exports) module.exports = api;
  if (root) root.ToramD4WorkerClient = api;
}(typeof window !== 'undefined' ? window : globalThis));
