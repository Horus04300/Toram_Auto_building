(function (root) {
  'use strict';
  var initialized = false, controller;
  function element(id) { return document.getElementById(id); }
  function confirmInstall(hasWork) {
    var dialog = element('updateConfirm');
    element('updateConfirmMessage').textContent = hasWork
      ? '실행 중이거나 일시정지한 정밀 계산이 있습니다. 계산을 종료하고 업데이트하시겠습니까? 설치 시 앱이 종료된 뒤 다시 실행됩니다.'
      : '업데이트를 다운로드하고 설치하시겠습니까? 설치 시 앱이 종료된 뒤 다시 실행됩니다. 현재 세팅은 설치 전에 저장합니다.';
    element('updateConfirmAccept').textContent = hasWork ? '계산을 종료하고 업데이트' : '업데이트';
    return new Promise(function (resolve) {
      dialog.returnValue = 'cancel';
      dialog.addEventListener('close', function () { resolve(dialog.returnValue === 'approve'); }, { once:true });
      dialog.showModal();
    });
  }
  function render(state) {
    var busy = ['checking','downloading','installing'].indexOf(state.phase) >= 0;
    element('updatePanel').hidden = !state.visible;
    element('updateCheck').disabled = busy || state.phase === 'unavailable';
    element('updateInstall').hidden = !state.update || ['idle','checking','completed'].indexOf(state.phase) >= 0;
    element('updateInstall').disabled = busy;
    element('updateInstall').textContent = state.phase === 'failed' ? '다시 시도' : '업데이트';
    element('updateRetryCheck').hidden = state.phase !== 'failed';
    element('updateLater').disabled = busy;
    element('updateLater').textContent = state.phase === 'available' ? '나중에' : '닫기';
    element('updateNotes').textContent = state.update && state.update.notes || '';
    element('updateTitle').textContent = state.update ? '새로운 버전 v' + state.update.version : '앱 업데이트';
    var labels = { idle:'최신 버전입니다.', checking:'업데이트 확인 중…', available:state.update ? '현재 버전: ' + state.update.currentVersion : '', downloading:'업데이트 다운로드 및 검증 중…', installing:'설치 프로그램을 시작합니다. 앱이 다시 실행될 때까지 기다려 주세요.', completed:'설치 요청이 완료되었습니다.', failed:state.error, unavailable:'Windows 데스크톱 앱에서 업데이트할 수 있습니다.' };
    var progress = element('updateProgress');
    progress.hidden = state.phase !== 'downloading';
    if (state.progress && state.progress.total) {
      progress.value = Math.min(100, state.progress.downloaded * 100 / state.progress.total);
      labels.downloading += ' ' + Math.floor(progress.value) + '%';
    } else progress.removeAttribute('value');
    element('updateStatus').textContent = labels[state.phase] || '';
    element('updateAvailability').textContent = state.phase === 'unavailable' ? labels.unavailable : '';
  }
  function initialize() {
    if (initialized) return;
    initialized = true;
    var settings = root.ToramApplication.Settings;
    controller = root.ToramUpdateController.create({
      service:root.ToramUpdateService,
      beforeDownload:function () { return root.ToramUpdateInstallCoordinator.prepare(confirmInstall); },
      beforeInstall:function () { return root.ToramUpdateInstallCoordinator.beforeInstall(confirmInstall); },
      release:function () { if (root.ToramUpdateInstallCoordinator) root.ToramUpdateInstallCoordinator.release(); }
    });
    controller.subscribe(render);
    var startup = element('updateCheckOnStartup');
    startup.checked = settings.getUpdateSettings().checkOnStartup;
    startup.disabled = !root.ToramUpdateService.isAvailable();
    startup.addEventListener('change', function () {
      try { settings.setUpdateSettings({ checkOnStartup:startup.checked }); }
      catch (error) { startup.checked = settings.getUpdateSettings().checkOnStartup; element('updateAvailability').textContent = error.message; }
    });
    element('updateCheck').addEventListener('click', function () { controller.check(false); });
    element('updateRetryCheck').addEventListener('click', function () { controller.check(false); });
    element('updateInstall').addEventListener('click', function () { controller.install(); });
    element('updateLater').addEventListener('click', controller.later);
    root.setTimeout(function () { if (startup.checked) controller.check(true); }, 0);
  }
  root.ToramUpdateUi = Object.freeze({ initialize:initialize });
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', initialize, { once:true }); else initialize();
}(window));
