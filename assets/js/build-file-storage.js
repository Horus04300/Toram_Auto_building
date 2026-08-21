/* File System Access API 기반 세팅 JSON 저장/불러오기. */
(function () {
  'use strict';
  var APP_FOLDER_NAME = 'ToramOnlineAutoBuildCalculator';
  var DB_NAME = 'toram-auto-building.file-storage';
  var STORE_NAME = 'handles';
  var HANDLE_KEY = 'settings-parent-folder';
  var STATE_KEYS = [
    'toram-auto-building.build-state.v1',
    'toram-auto-building.skill-tree.v1',
    'toram-auto-building.skill-tree-ui.v1',
    'toram-auto-active-buffs-v1',
    'toram.combo-sequence.v1'
  ];
  var folderHandle = null;
  var elements = {};
  var countdownTimer = null;

  function supportsFileSystemAccess() {
    return typeof window.showDirectoryPicker === 'function' && typeof window.indexedDB !== 'undefined';
  }
  function openDatabase() {
    return new Promise(function (resolve, reject) {
      var request = window.indexedDB.open(DB_NAME, 1);
      request.onupgradeneeded = function () { request.result.createObjectStore(STORE_NAME); };
      request.onsuccess = function () { resolve(request.result); };
      request.onerror = function () { reject(request.error); };
    });
  }
  function withStore(mode, action) {
    return openDatabase().then(function (database) {
      return new Promise(function (resolve, reject) {
        var transaction = database.transaction(STORE_NAME, mode);
        var request = action(transaction.objectStore(STORE_NAME));
        transaction.oncomplete = function () { database.close(); resolve(request && request.result); };
        transaction.onerror = function () { database.close(); reject(transaction.error || request.error); };
        transaction.onabort = function () { database.close(); reject(transaction.error || request.error); };
      });
    });
  }
  function loadStoredHandle() { return withStore('readonly', function (store) { return store.get(HANDLE_KEY); }); }
  function storeHandle(handle) { return withStore('readwrite', function (store) { return store.put(handle, HANDLE_KEY); }); }
  function setStatus(message, isError) {
    if (!elements.status) return;
    elements.status.textContent = message;
    elements.status.classList.toggle('is-error', Boolean(isError));
  }
  function setSetupVisible(visible) {
    if (elements.setup) elements.setup.hidden = !visible;
  }
  function setControlsVisible(visible) {
    if (elements.controls) elements.controls.hidden = !visible;
  }
  async function permissionFor(handle, request) {
    if (!handle || typeof handle.queryPermission !== 'function') return 'denied';
    var state = await handle.queryPermission({ mode:'readwrite' });
    if (state !== 'granted' && request && typeof handle.requestPermission === 'function') state = await handle.requestPermission({ mode:'readwrite' });
    return state;
  }
  async function getAppFolder(requestPermission) {
    if (!folderHandle) return null;
    if (await permissionFor(folderHandle, requestPermission) !== 'granted') return null;
    return folderHandle.getDirectoryHandle(APP_FOLDER_NAME, { create:true });
  }
  function snapshot() {
    var storage = {};
    STATE_KEYS.forEach(function (key) { storage[key] = window.localStorage.getItem(key); });
    return { format:'toram-auto-build-setting', schemaVersion:1, savedAt:new Date().toISOString(), storage:storage };
  }
  function safeFileName(value) {
    var name = String(value || '').trim().replace(/[\\/:*?"<>|]/g, '-').replace(/\s+/g, ' ');
    return name || ('세팅-' + new Date().toISOString().slice(0, 19).replace(/[:T]/g, '-'));
  }
  function fileName() { return safeFileName(elements.name && elements.name.value) + '.json'; }
  function serialize() {
    var data = snapshot();
    data.name = safeFileName(elements.name && elements.name.value);
    return JSON.stringify(data, null, 2);
  }
  function download(content, name) {
    var blob = new Blob([content], { type:'application/json' });
    var link = document.createElement('a');
    link.href = URL.createObjectURL(blob); link.download = name;
    document.body.appendChild(link); link.click(); link.remove();
    window.setTimeout(function () { URL.revokeObjectURL(link.href); }, 0);
  }
  async function refreshFileList(requestPermission) {
    var folder = await getAppFolder(requestPermission);
    if (!folder) { setStatus('저장 폴더 권한이 필요합니다.', true); return; }
    var files = [];
    for await (var entry of folder.values()) {
      if (entry.kind !== 'file' || !/\.json$/i.test(entry.name)) continue;
      var file = await entry.getFile();
      files.push({ name:entry.name, modified:file.lastModified });
    }
    files.sort(function (left, right) { return right.modified - left.modified; });
    elements.fileList.innerHTML = '';
    files.forEach(function (item) {
      var option = document.createElement('option'); option.value = item.name; option.textContent = item.name; elements.fileList.appendChild(option);
    });
    elements.load.disabled = files.length === 0;
    elements.overwrite.disabled = files.length === 0;
    setStatus(files.length ? files.length + '개 세팅 파일을 찾았습니다.' : '저장된 세팅 파일이 없습니다.');
  }
  function validate(data) {
    return data && data.format === 'toram-auto-build-setting' && data.schemaVersion === 1 && data.storage && typeof data.storage === 'object' && !Array.isArray(data.storage);
  }
  function applySnapshot(data) {
    if (!validate(data)) throw new Error('이 계산기의 세팅 JSON 파일이 아닙니다.');
    STATE_KEYS.forEach(function (key) {
      var value = data.storage[key];
      if (typeof value === 'string') window.localStorage.setItem(key, value);
      else window.localStorage.removeItem(key);
    });
    window.location.reload();
  }
  async function writeSetting(folder, name, content) {
    var handle = await folder.getFileHandle(name, { create:true });
    var writer = await handle.createWritable();
    await writer.write(content); await writer.close();
  }
  async function saveSetting() {
    var content = serialize(), name = fileName();
    if (!supportsFileSystemAccess()) { setStatus('이 브라우저에서는 폴더 저장을 지원하지 않습니다.', true); return; }
    if (!folderHandle) { setStatus('먼저 저장 폴더를 지정하세요.', true); return; }
    var folder = await getAppFolder(true);
    if (!folder) { setStatus('저장 폴더 권한이 필요합니다.', true); return; }
    try {
      await folder.getFileHandle(name);
      setStatus('같은 이름의 세팅이 있습니다. 목록에서 선택 후 “덮어쓰기”를 사용하세요.', true);
      return;
    } catch (error) {
      if (error && error.name !== 'NotFoundError') throw error;
    }
    await writeSetting(folder, name, content);
    setStatus(name + ' 저장 완료');
    await refreshFileList(false);
  }
  async function overwriteSelectedSetting() {
    var selected = elements.fileList.value;
    if (!selected) { setStatus('덮어쓸 세팅 파일을 선택하세요.', true); return; }
    if (!window.confirm('“' + selected + '” 파일을 현재 세팅으로 덮어쓸까요?')) return;
    var folder = await getAppFolder(true);
    if (!folder) { setStatus('저장 폴더 권한이 필요합니다.', true); return; }
    await writeSetting(folder, selected, serialize());
    setStatus(selected + ' 덮어쓰기 완료');
    await refreshFileList(false);
  }
  async function loadSelectedSetting() {
    var folder = await getAppFolder(true), selected = elements.fileList.value;
    if (!folder || !selected) { setStatus('불러올 세팅 파일을 선택하세요.', true); return; }
    var handle = await folder.getFileHandle(selected);
    var data = JSON.parse(await (await handle.getFile()).text());
    applySnapshot(data);
  }
  function loadDirectFile(file) {
    if (!file) return;
    file.text().then(function (text) { applySnapshot(JSON.parse(text)); }).catch(function (error) { setStatus('불러오기 실패: ' + error.message, true); });
  }
  function closeGuide() {
    window.clearTimeout(countdownTimer); countdownTimer = null;
    if (elements.guide.open) elements.guide.close();
  }
  function openGuide() {
    setStatus('문서 폴더에서 저장 위치를 선택하세요.');
    elements.confirm.disabled = true;
    elements.countdown.textContent = '확인 버튼은 3초 뒤 활성화됩니다.';
    elements.guide.showModal();
    countdownTimer = window.setTimeout(function () { elements.confirm.disabled = false; elements.countdown.textContent = '이제 확인을 눌러 폴더를 선택하세요.'; }, 3000);
  }
  async function chooseFolder() {
    try {
      var parent = await window.showDirectoryPicker({ mode:'readwrite', startIn:'documents', id:'toram-auto-build-settings' });
      var appFolder = await parent.getDirectoryHandle(APP_FOLDER_NAME, { create:true });
      var test = await appFolder.getFileHandle('.write-test', { create:true });
      var writer = await test.createWritable(); await writer.write('ok'); await writer.close(); await appFolder.removeEntry('.write-test');
      folderHandle = parent;
      await storeHandle(parent);
      closeGuide(); setSetupVisible(false); setControlsVisible(true);
      setStatus(APP_FOLDER_NAME + ' 폴더를 만들고 저장 위치를 지정했습니다.');
      await refreshFileList(false);
    } catch (error) {
      if (error && error.name === 'AbortError') { setStatus('저장 폴더 선택을 취소했습니다.'); return; }
      setStatus('저장 폴더를 지정하지 못했습니다: ' + error.message, true);
    }
  }
  function createUi() {
    var launcher = document.getElementById('appBuildStorageButton');
    if (!launcher) return;
    var overlay = document.createElement('div'); overlay.className = 'build-file-overlay'; overlay.hidden = true;
    overlay.innerHTML = '<section class="build-file-dialog" role="dialog" aria-modal="true" aria-labelledby="buildFileDialogTitle"><header class="build-file-dialog-header"><div><h2 id="buildFileDialogTitle">💾 저장</h2><p>현재 세팅을 저장하거나 불러옵니다.</p></div><button type="button" id="buildFileDialogClose" class="build-file-dialog-close" aria-label="세팅 파일 닫기">×</button></header><div class="build-file-storage"><div id="buildFolderSetup" class="build-folder-setup"><button type="button" id="buildFolderSetupButton">저장 폴더 지정</button><span>권장 위치: <code>문서</code></span></div><div id="buildFileFunctions" class="build-file-functions" hidden><div class="build-file-controls"><label>세팅 이름<input id="buildSettingName" type="text" value="내 세팅" maxlength="80"></label><button type="button" id="buildSettingSave">저장</button><button type="button" id="buildSettingRefresh">목록 새로고침</button></div><div class="build-file-controls"><label>저장 파일<select id="buildSettingList"></select></label><button type="button" id="buildSettingLoad" disabled>불러오기</button><button type="button" id="buildSettingOverwrite" disabled>덮어쓰기</button><label class="build-file-import">JSON 직접 불러오기<input id="buildSettingImport" type="file" accept="application/json,.json"></label></div></div><p id="buildFileStorageStatus" class="build-file-storage-status" role="status"></p></div><dialog id="buildFolderGuide" class="build-folder-guide"><h3>저장 위치 안내</h3><p>파일 선택창은 문서 폴더에서 시작합니다. 문서 폴더를 선택하세요.</p><code>문서</code><p>선택한 위치 안에 <strong>ToramOnlineAutoBuildCalculator</strong> 폴더를 자동 생성합니다.</p><p id="buildFolderCountdown"></p><div><button type="button" id="buildFolderCancel">취소</button><button type="button" id="buildFolderConfirm" disabled>확인</button></div></dialog></section>';
    document.body.appendChild(overlay);
    elements = { overlay:overlay, launcher:launcher, close:overlay.querySelector('#buildFileDialogClose'), setup:overlay.querySelector('#buildFolderSetup'), setupButton:overlay.querySelector('#buildFolderSetupButton'), controls:overlay.querySelector('#buildFileFunctions'), name:overlay.querySelector('#buildSettingName'), save:overlay.querySelector('#buildSettingSave'), refresh:overlay.querySelector('#buildSettingRefresh'), fileList:overlay.querySelector('#buildSettingList'), load:overlay.querySelector('#buildSettingLoad'), overwrite:overlay.querySelector('#buildSettingOverwrite'), import:overlay.querySelector('#buildSettingImport'), status:overlay.querySelector('#buildFileStorageStatus'), guide:overlay.querySelector('#buildFolderGuide'), confirm:overlay.querySelector('#buildFolderConfirm'), cancel:overlay.querySelector('#buildFolderCancel'), countdown:overlay.querySelector('#buildFolderCountdown') };
    function closeOverlay() { if (!elements.guide.open) elements.overlay.hidden = true; }
    elements.launcher.addEventListener('click', function () { elements.overlay.hidden = false; elements.name.focus(); });
    elements.close.addEventListener('click', closeOverlay);
    elements.overlay.addEventListener('click', function (event) { if (event.target === elements.overlay) closeOverlay(); });
    document.addEventListener('keydown', function (event) { if (event.key === 'Escape') closeOverlay(); });
    elements.setupButton.addEventListener('click', openGuide);
    elements.cancel.addEventListener('click', closeGuide);
    elements.guide.addEventListener('close', function () { window.clearTimeout(countdownTimer); countdownTimer = null; });
    elements.confirm.addEventListener('click', chooseFolder);
    elements.save.addEventListener('click', function () { saveSetting().catch(function (error) { setStatus('저장 실패: ' + error.message, true); }); });
    elements.refresh.addEventListener('click', function () { refreshFileList(true).catch(function (error) { setStatus('목록 갱신 실패: ' + error.message, true); }); });
    elements.load.addEventListener('click', function () { loadSelectedSetting().catch(function (error) { setStatus('불러오기 실패: ' + error.message, true); }); });
    elements.overwrite.addEventListener('click', function () { overwriteSelectedSetting().catch(function (error) { setStatus('덮어쓰기 실패: ' + error.message, true); }); });
    elements.import.addEventListener('change', function () { loadDirectFile(elements.import.files && elements.import.files[0]); elements.import.value = ''; });
  }
  async function initialize() {
    createUi();
    if (!elements.status) return;
    if (!supportsFileSystemAccess()) { setSetupVisible(false); setControlsVisible(false); setStatus('이 브라우저에서는 폴더 저장을 지원하지 않습니다.'); return; }
    try {
      folderHandle = await loadStoredHandle();
      setSetupVisible(!folderHandle);
      setControlsVisible(Boolean(folderHandle));
      setStatus(folderHandle ? '저장 폴더가 지정되어 있습니다.' : '저장 폴더를 한 번 지정하면 이후 자동으로 사용합니다.');
    } catch (_) { setControlsVisible(false); setStatus('저장 폴더 정보를 읽지 못했습니다. 다시 지정하세요.', true); }
  }
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', initialize, { once:true }); else initialize();
}());