/* Update runtime only: no BuildDraft, calculation rules, DOM or native IPC. */
(function (root) {
  'use strict';
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
        if (deps.beforeDownload && await deps.beforeDownload() === false) return;
        change({ phase:'downloading', error:null, progress:null, visible:true });
        await service.install(state.update.version, function (progress) { change({ progress:progress }); }, async function () {
          if (deps.beforeInstall) await deps.beforeInstall();
          change({ phase:'installing', progress:null });
        });
        change({ phase:'completed' });
      } catch (error) {
        change({ phase:'failed', error:error.message || '업데이트에 실패했습니다.', visible:true });
      } finally {
        busy = false;
        if (deps.release) deps.release();
      }
    }
    return Object.freeze({
      read:snapshot, check:check, install:install,
      later:function () { if (!busy) change({ phase:state.phase === 'available' ? 'idle' : state.phase, visible:false }); },
      subscribe:function (listener) { listeners.push(listener); listener(snapshot()); return function () { listeners = listeners.filter(function (item) { return item !== listener; }); }; }
    });
  }
  root.ToramUpdateController = Object.freeze({ create:create });
}(typeof window !== 'undefined' ? window : globalThis));
