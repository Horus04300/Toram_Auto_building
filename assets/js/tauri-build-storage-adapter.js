"use strict";
/* Tauri 네이티브 파일 명령을 R6 Settings Repository 어댑터로 연결한다. */
(() => {
    'use strict';
    const root = window;
    const invoke = root.__TAURI__?.core?.invoke;
    if (typeof invoke !== 'function')
        return;
    const adapter = Object.freeze({
        directory: () => invoke('settings_directory'),
        list: () => invoke('list_settings'),
        save: (name, content) => invoke('save_setting', { name, content }),
        load: (name) => invoke('load_setting', { name }),
        overwrite: (name, content) => invoke('overwrite_setting', { name, content }),
        delete: (name) => invoke('delete_setting', { name })
    });
    root.ToramSettingsFileRepositoryAdapter = adapter;
})();
