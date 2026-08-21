/* Tauri 네이티브 세팅 저장 명령을 저장 UI의 공통 어댑터로 연결한다. */
(function () {
  'use strict';

  var tauri = window.__TAURI__;
  if (!tauri || !tauri.core || typeof tauri.core.invoke !== 'function') return;
  var invoke = tauri.core.invoke;

  window.ToramBuildStorageAdapter = Object.freeze({
    directory:function () { return invoke('settings_directory'); },
    list:function () { return invoke('list_settings'); },
    save:function (name, content) { return invoke('save_setting', { name:name, content:content }); },
    load:function (name) { return invoke('load_setting', { name:name }); },
    overwrite:function (name, content) { return invoke('overwrite_setting', { name:name, content:content }); },
    delete:function (name) { return invoke('delete_setting', { name:name }); }
  });
}());