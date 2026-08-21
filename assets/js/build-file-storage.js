/* 세팅 저장 오버레이. 실제 저장 위치는 ToramBuildStorageAdapter가 담당한다. */
(function () {
  'use strict';

  var elements = {};
  var settings = window.ToramBuildSettings;

  function adapter() {
    return window.ToramBuildStorageAdapter || null;
  }

  function errorMessage(error) {
    return error && error.message ? error.message : String(error || '알 수 없는 오류');
  }

  function setStatus(message, isError) {
    if (!elements.status) return;
    elements.status.textContent = message;
    elements.status.classList.toggle('is-error', Boolean(isError));
  }

  function settingName() {
    return settings.safeFileStem(elements.name && elements.name.value);
  }

  function selectedSettingStem() {
    return String(elements.fileList.value || '').replace(/\.json$/i, '');
  }

  function setNativeVisible(visible) {
    if (elements.nativeFunctions) elements.nativeFunctions.hidden = !visible;
  }

  async function refreshFileList(showStatus) {
    var storage = adapter();
    if (!storage) return;
    var files = await storage.list();
    elements.fileList.innerHTML = '';
    files.forEach(function (item) {
      var option = document.createElement('option');
      option.value = item.name;
      option.textContent = item.name;
      elements.fileList.appendChild(option);
    });
    elements.load.disabled = files.length === 0;
    elements.overwrite.disabled = files.length === 0;
    elements.deleteButton.disabled = files.length === 0;
    if (showStatus) setStatus(files.length ? files.length + '개 세팅 파일을 찾았습니다.' : '저장된 세팅 파일이 없습니다.');
  }

  async function saveSetting() {
    var storage = adapter();
    if (!storage) throw new Error('데스크톱 저장 기능이 아직 연결되지 않았습니다.');
    var name = settingName();
    await storage.save(name, settings.serialize(name));
    setStatus(name + '.json 저장 완료');
    await refreshFileList(false);
  }

  async function overwriteSelectedSetting() {
    var storage = adapter();
    var selected = elements.fileList.value;
    if (!storage) throw new Error('데스크톱 저장 기능이 아직 연결되지 않았습니다.');
    if (!selected) { setStatus('덮어쓸 세팅 파일을 선택하세요.', true); return; }
    if (!window.confirm('“' + selected + '” 파일을 현재 세팅으로 덮어쓸까요?')) return;
    await storage.overwrite(selected, settings.serialize(selectedSettingStem()));
    setStatus(selected + ' 덮어쓰기 완료');
    await refreshFileList(false);
  }

  async function loadSelectedSetting() {
    var storage = adapter();
    var selected = elements.fileList.value;
    if (!storage) throw new Error('데스크톱 저장 기능이 아직 연결되지 않았습니다.');
    if (!selected) { setStatus('불러올 세팅 파일을 선택하세요.', true); return; }
    settings.apply(settings.parse(await storage.load(selected)));
  }

  async function deleteSelectedSetting() {
    var storage = adapter();
    var selected = elements.fileList.value;
    if (!storage) throw new Error('데스크톱 저장 기능이 아직 연결되지 않았습니다.');
    if (!selected) { setStatus('삭제할 세팅 파일을 선택하세요.', true); return; }
    if (!window.confirm('“' + selected + '” 파일을 삭제할까요? 이 작업은 되돌릴 수 없습니다.')) return;
    await storage.delete(selected);
    setStatus(selected + ' 삭제 완료');
    await refreshFileList(false);
  }

  function exportJson() {
    var name = settings.download(settings.safeFileStem(elements.backupName && elements.backupName.value));
    setStatus(name + ' 내보내기 완료');
  }

  function importJson(file) {
    if (!file) return;
    file.text().then(function (text) {
      settings.apply(settings.parse(text));
    }).catch(function (error) {
      setStatus('불러오기 실패: ' + errorMessage(error), true);
    });
  }

  function createUi() {
    var launcher = document.getElementById('appBuildStorageButton');
    if (!launcher || !settings) return;
    var overlay = document.createElement('div');
    overlay.className = 'build-file-overlay';
    overlay.hidden = true;
    overlay.innerHTML = '<section class="build-file-dialog" role="dialog" aria-modal="true" aria-labelledby="buildFileDialogTitle"><header class="build-file-dialog-header"><div><h2 id="buildFileDialogTitle">💾 저장</h2><p>현재 세팅을 저장하거나 불러옵니다.</p></div><button type="button" id="buildFileDialogClose" class="build-file-dialog-close" aria-label="세팅 파일 닫기">×</button></header><div class="build-file-storage"><div id="buildNativeFileFunctions" class="build-file-functions" hidden><div class="build-file-controls"><label>세팅 이름<input id="buildSettingName" type="text" value="내 세팅" maxlength="80"></label><button type="button" id="buildSettingSave">저장</button><button type="button" id="buildSettingRefresh">목록 새로고침</button></div><div class="build-file-controls"><label>저장 파일<select id="buildSettingList"></select></label><button type="button" id="buildSettingLoad" disabled>불러오기</button><button type="button" id="buildSettingOverwrite" disabled>덮어쓰기</button><button type="button" id="buildSettingDelete" disabled>삭제</button></div></div><div class="build-file-functions build-file-backup"><p class="build-file-storage-help">기존 브라우저 세팅을 데스크톱 앱으로 옮기거나 별도로 백업할 수 있습니다.</p><div class="build-file-controls"><label>백업 파일 이름<input id="buildBackupName" type="text" value="내 세팅" maxlength="80"></label><button type="button" id="buildSettingExport">JSON 내보내기</button><label class="build-file-import">JSON 불러오기<input id="buildSettingImport" type="file" accept="application/json,.json"></label></div></div><p id="buildFileStorageStatus" class="build-file-storage-status" role="status"></p></div></section>';
    document.body.appendChild(overlay);
    elements = {
      overlay:overlay,
      launcher:launcher,
      close:overlay.querySelector('#buildFileDialogClose'),
      nativeFunctions:overlay.querySelector('#buildNativeFileFunctions'),
      name:overlay.querySelector('#buildSettingName'),
      backupName:overlay.querySelector('#buildBackupName'),
      save:overlay.querySelector('#buildSettingSave'),
      refresh:overlay.querySelector('#buildSettingRefresh'),
      fileList:overlay.querySelector('#buildSettingList'),
      load:overlay.querySelector('#buildSettingLoad'),
      overwrite:overlay.querySelector('#buildSettingOverwrite'),
      deleteButton:overlay.querySelector('#buildSettingDelete'),
      exportButton:overlay.querySelector('#buildSettingExport'),
      importInput:overlay.querySelector('#buildSettingImport'),
      status:overlay.querySelector('#buildFileStorageStatus')
    };
    function closeOverlay() { elements.overlay.hidden = true; }
    elements.launcher.addEventListener('click', function () {
      elements.overlay.hidden = false;
      elements.name.focus();
    });
    elements.close.addEventListener('click', closeOverlay);
    elements.overlay.addEventListener('click', function (event) { if (event.target === elements.overlay) closeOverlay(); });
    document.addEventListener('keydown', function (event) { if (event.key === 'Escape') closeOverlay(); });
    elements.save.addEventListener('click', function () { saveSetting().catch(function (error) { setStatus('저장 실패: ' + errorMessage(error), true); }); });
    elements.refresh.addEventListener('click', function () { refreshFileList(true).catch(function (error) { setStatus('목록 갱신 실패: ' + errorMessage(error), true); }); });
    elements.load.addEventListener('click', function () { loadSelectedSetting().catch(function (error) { setStatus('불러오기 실패: ' + errorMessage(error), true); }); });
    elements.overwrite.addEventListener('click', function () { overwriteSelectedSetting().catch(function (error) { setStatus('덮어쓰기 실패: ' + errorMessage(error), true); }); });
    elements.deleteButton.addEventListener('click', function () { deleteSelectedSetting().catch(function (error) { setStatus('삭제 실패: ' + errorMessage(error), true); }); });
    elements.exportButton.addEventListener('click', exportJson);
    elements.importInput.addEventListener('change', function () {
      importJson(elements.importInput.files && elements.importInput.files[0]);
      elements.importInput.value = '';
    });
  }

  async function initialize() {
    createUi();
    if (!elements.status) return;
    var hasAdapter = Boolean(adapter());
    setNativeVisible(hasAdapter);
    if (hasAdapter) {
      var directory = typeof adapter().directory === 'function' ? await adapter().directory() : '';
      setStatus(directory ? '저장 위치: ' + directory : '데스크톱 세팅 저장소가 연결되어 있습니다.');
      await refreshFileList(false);
    } else {
      setStatus('JSON 내보내기로 기존 브라우저 세팅을 백업할 수 있습니다.');
    }
  }

  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', function () {
    initialize().catch(function (error) { setStatus('저장 UI 초기화 실패: ' + errorMessage(error), true); });
  }, { once:true });
  else initialize().catch(function (error) { setStatus('저장 UI 초기화 실패: ' + errorMessage(error), true); });
}());
