/* Tauri 네이티브 파일 명령을 R6 Settings Repository 어댑터로 연결한다. */
(() => {
  'use strict';

  const root = window as SettingsRepositoryTauriWindow;
  const invoke = root.__TAURI__?.core?.invoke;
  if (typeof invoke !== 'function') return;
  const adapter: SettingsFileRepositoryAdapter = Object.freeze({
    directory: () => invoke('settings_directory'),
    list: () => invoke('list_settings'),
    save: (name: string, content: string) => invoke('save_setting', { name, content }),
    load: (name: string) => invoke('load_setting', { name }),
    overwrite: (name: string, content: string) => invoke('overwrite_setting', { name, content }),
    delete: (name: string) => invoke('delete_setting', { name })
  });

  root.ToramSettingsFileRepositoryAdapter = adapter;
})();
