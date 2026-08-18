(function (app) {
    'use strict';

    function bindUiEvents() {
        var crystaUi = app.crystaUi;
        var optimizer = app.optimizer;
        if (!crystaUi || !optimizer) throw new Error('UI modules were not initialized.');

        document.querySelectorAll('[data-add-option]').forEach(function (button) {
            button.addEventListener('click', function () { crystaUi.addOptionRow(button.dataset.addOption); });
        });
        document.querySelector('[data-action="add-skill-stat"]').addEventListener('click', crystaUi.addSkillStatRow);
        document.querySelector('[data-action="add-ban"]').addEventListener('click', crystaUi.addBanTag);
        document.querySelector('[data-action="calculate"]').addEventListener('click', optimizer.runCalculationSafe);
        document.querySelector('[data-action="main-weapon-change"]').addEventListener('change', function () {
            crystaUi.updateSubWeaponList();
            crystaUi.refreshAllCrystaInfo();
        });
        document.querySelector('[data-action="sub-weapon-change"]').addEventListener('change', crystaUi.onSubWeaponChange);
        document.querySelector('[data-action="armor-change"]').addEventListener('change', crystaUi.refreshAllCrystaInfo);
        optimizer.initialize();
    }

    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', bindUiEvents, { once: true });
    } else {
        bindUiEvents();
    }
}(window.ToramApp = window.ToramApp || {}));