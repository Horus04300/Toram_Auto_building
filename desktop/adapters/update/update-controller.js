export function createUpdateCoordinator(root,app) {
  'use strict';
  var locked = false, epoch = 0, previousInert = false;
  function hasWork() {
    var execution = app.execution, runtime = app.optimizer && app.optimizer.getState();
    return Boolean(execution && (execution.isRunning() || execution.hasContinuation()) || runtime && (runtime.calculationQueued || runtime.executionStatus === 'running'));
  }
  function lock() {
    locked = true;
    epoch++;
    previousInert = root.document.body.inert;
    root.document.body.inert = true;
  }
  function release() {
    if (!locked) return;
    root.document.body.inert = previousInert;
    locked = false;
  }
  async function stopAndFlush() {
    await app.optimizer.stopForUpdate();
    // Sync and flush the latest input, including edits made while downloading.
    await app.settingsRepository.flushApplicationState();
  }
  async function prepare(confirm) {
    if (!await confirm(hasWork())) return false;
    lock();
    try { await stopAndFlush(); } finally { release(); }
    return true;
  }
  async function beforeInstall(confirm) {
    if (hasWork() && !await confirm(true)) throw new Error('새 계산을 유지하기 위해 설치를 취소했습니다. 나중에 다시 시도할 수 있습니다.');
    lock();
    try { await stopAndFlush(); } catch (error) { release(); throw error; }
    // Remain locked only across the final native install request; errors release it.
  }

  function create(deps) {
    var service = deps.service;
    var state = { phase:service && service.isAvailable() ? 'idle' : 'unavailable', update:null, progress:null, error:null, visible:false };
    var listeners = [], busy = false;
    function snapshot() { return JSON.parse(JSON.stringify(state)); }
    function change(next) {
      Object.assign(state, next);
      listeners.forEach(function (listener) { listener(snapshot()); });
    }
    async function check(silent) {
      if (busy || state.phase === 'unavailable') return;
      busy = true;
      change({ phase:'checking', update:null, error:null, progress:null, visible:!silent });
      try {
        var update = await service.check();
        change({ phase:update ? 'available' : 'idle', update:update, visible:Boolean(update) || !silent });
      } catch (error) {
        change({ phase:'failed', error:error.message || '업데이트를 확인하지 못했습니다.', visible:!silent });
      } finally { busy = false; }
    }
    async function install() {
      if (busy || !state.update) return;
      busy = true;
      try {
        if (await prepare(deps.confirm) === false) return;
        change({ phase:'downloading', error:null, progress:null, visible:true });
        await service.install(state.update.version, function (progress) { change({ progress:progress }); }, async function () {
          await beforeInstall(deps.confirm);
          change({ phase:'installing', progress:null });
        });
        change({ phase:'completed' });
      } catch (error) {
        change({ phase:'failed', error:error.message || '업데이트에 실패했습니다.', visible:true });
      } finally {
        busy = false;
        release();
      }
    }
    return Object.freeze({
      read:snapshot, check:check, install:install,
      later:function () { if (!busy) change({ phase:state.phase === 'available' ? 'idle' : state.phase, visible:false }); },
      subscribe:function (listener) { listeners.push(listener); listener(snapshot()); return function () { listeners = listeners.filter(function (item) { return item !== listener; }); }; }
    });
  }
  return Object.freeze({ create:create, isLocked:function () { return locked; }, epoch:function () { return epoch; } });

}
