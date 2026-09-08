"use strict";
/* Emitted as a classic script; Tauri objects never cross the Application Port. */
(() => {
    'use strict';
    const root = window;
    const core = root.__TAURI__?.core;
    const available = typeof core?.invoke === 'function' && typeof core.Channel === 'function';
    function record(value) {
        return typeof value === 'object' && value !== null && !Array.isArray(value);
    }
    function metadata(value) {
        if (value === null)
            return null;
        const version = /^(0|[1-9]\d*)\.(0|[1-9]\d*)\.(0|[1-9]\d*)$/;
        if (!record(value) || typeof value['currentVersion'] !== 'string' || !version.test(value['currentVersion']) ||
            typeof value['version'] !== 'string' || !version.test(value['version']) ||
            !(value['notes'] === null || typeof value['notes'] === 'string') ||
            !(value['publishedAt'] === null || typeof value['publishedAt'] === 'string')) {
            throw new Error('업데이트 정보가 올바르지 않습니다. 다시 확인해 주세요.');
        }
        return { currentVersion: value['currentVersion'], version: value['version'], notes: value['notes'], publishedAt: value['publishedAt'] };
    }
    async function invoke(command, args) {
        if (!available || !core)
            throw new Error('업데이트는 Windows 데스크톱 앱에서 사용할 수 있습니다.');
        try {
            return await core.invoke(command, args);
        }
        catch (error) {
            throw new Error(record(error) && typeof error['message'] === 'string' ? error['message'] : '업데이트 요청에 실패했습니다. 다시 시도해 주세요.');
        }
    }
    const service = Object.freeze({
        isAvailable: () => available,
        check: async () => metadata(await invoke('check_for_update')),
        install: async (version, onProgress, beforeInstall) => {
            if (!available || !core)
                throw new Error('업데이트는 Windows 데스크톱 앱에서 사용할 수 있습니다.');
            const progress = new core.Channel();
            progress.onmessage = (value) => {
                if (!record(value) || typeof value['downloaded'] !== 'number' || !Number.isSafeInteger(value['downloaded']) || value['downloaded'] < 0)
                    return;
                const total = value['total'];
                onProgress({ downloaded: value['downloaded'], total: typeof total === 'number' && Number.isSafeInteger(total) && total > 0 && total >= value['downloaded'] ? total : null });
            };
            await invoke('download_update', { version, progress });
            // Download resolves only after signature verification. The caller can flush or abort here.
            await beforeInstall();
            await invoke('install_update', { version });
        }
    });
    root.ToramUpdateService = service;
})();
