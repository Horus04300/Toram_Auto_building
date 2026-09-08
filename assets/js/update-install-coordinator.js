/* User-approved coordination through existing UI execution and Application storage boundaries. */
(function (root) {
  'use strict';
  var locked = false, epoch = 0, previousInert = false;
  function hasWork() {
    var execution = root.ToramD4ExecutionAdapter;
    var runtime = root.ToramRuntimeState && root.ToramRuntimeState.get();
    return Boolean(execution && (execution.isRunning() || execution.hasContinuation()) ||
      runtime && (runtime.calculationQueued || runtime.d4 && runtime.d4.executionStatus === 'running'));
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
    await root.ToramApp.optimizerUi.stopForUpdate();
    // Sync and flush the latest input, including edits made while downloading.
    await root.ToramApplication.Settings.flush();
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
  root.ToramUpdateInstallCoordinator = Object.freeze({ prepare:prepare, beforeInstall:beforeInstall, release:release, isLocked:function () { return locked; }, epoch:function () { return epoch; } });
}(window));
