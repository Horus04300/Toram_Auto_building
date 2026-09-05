(function (app) {
    'use strict';

    function bindUiEvents() {
        if (!app.buildUi || !app.optimizerUi || !app.optimizer) throw new Error('UI 기능 컨트롤러가 준비되지 않았습니다.');
        app.buildUi.bind();
        document.addEventListener('toram:preview', app.optimizer.runPreviewSafe);
        document.addEventListener('toram:calculate', app.optimizer.runCalculationSafe);
        app.optimizerUi.initialize();
    }

    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', bindUiEvents, { once: true });
    } else {
        bindUiEvents();
    }
}(window.ToramApp = window.ToramApp || {}));
