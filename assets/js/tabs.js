    (function () {
        const container = document.querySelector('.container');
        if (!container || document.getElementById('appTabNavigation')) return;

        const navigation = document.createElement('nav');
        navigation.id = 'appTabNavigation';
        navigation.className = 'app-tab-navigation';
        navigation.style.setProperty('--tab-count', '4');
        navigation.setAttribute('aria-label', '자동 빌드 계산기 구분');
        const panelHost = document.createElement('div');
        panelHost.id = 'appTabPanels';
        const tabDefinitions = [
            ['stats-target', '스탯 및 대상'], ['skills', '스킬'], ['equipment', '장비'], ['doping', '요리 및 도핑'], ['results', '결과']
        ];
        const panels = {};
        const buttons = {};
        tabDefinitions.forEach(function (definition, index) {
            const id = definition[0];
            const button = document.createElement('button');
            button.type = 'button';
            button.className = 'app-tab-button' + (index === 0 ? ' active' : '');
            button.id = 'appTabButton-' + id;
            button.textContent = definition[1];
            button.setAttribute('role', 'tab');
            button.setAttribute('aria-selected', String(index === 0));
            button.setAttribute('aria-controls', 'appTabPanel-' + id);
            if (id === 'results') button.hidden = true;
            navigation.appendChild(button);
            buttons[id] = button;
            const panel = document.createElement('section');
            panel.className = 'app-tab-panel' + (index === 0 ? ' active' : '');
            panel.id = 'appTabPanel-' + id;
            panel.setAttribute('role', 'tabpanel');
            panel.setAttribute('aria-labelledby', button.id);
            panelHost.appendChild(panel);
            panels[id] = panel;
        });
        function selectTab(id) {
            if (!buttons[id] || buttons[id].hidden) return;
            Object.keys(panels).forEach(function (key) {
                const isSelected = key === id;
                panels[key].classList.toggle('active', isSelected);
                buttons[key].classList.toggle('active', isSelected);
                buttons[key].setAttribute('aria-selected', String(isSelected));
            });
        }
        Object.keys(buttons).forEach(function (id) { buttons[id].addEventListener('click', function () { selectTab(id); }); });
        window.revealResultTab = function () {
            if (buttons.results.hidden) {
                buttons.results.hidden = false;
                navigation.style.setProperty('--tab-count', '5');
            }
            selectTab('results');
        };

        const firstChild = container.firstChild;
        container.insertBefore(navigation, firstChild);
        container.insertBefore(panelHost, firstChild);
        const sectionTitles = Array.from(container.querySelectorAll(':scope > .section-title'));
        const equipmentStart = sectionTitles[3];
        const blacklistStart = sectionTitles[4];
        function moveUntil(start, stop, destination) {
            let node = start;
            while (node && node !== stop) {
                const next = node.nextSibling;
                destination.appendChild(node);
                node = next;
            }
        }
        moveUntil(sectionTitles[0], equipmentStart, panels['stats-target']);
        const externalBuffCard = Array.from(container.children).find(function (element) {
            return element.classList && element.classList.contains('equip-card') && element.querySelector('#buffOpts');
        });
        moveUntil(equipmentStart, externalBuffCard, panels.equipment);
        if (externalBuffCard) panels.doping.appendChild(externalBuffCard);
        document.querySelectorAll('body > .skill-bookmark-section').forEach(function (section) { panels.skills.appendChild(section); });
        const resultArea = document.getElementById('resultArea');
        if (resultArea) panels.results.appendChild(resultArea);
        const globalActions = document.createElement('section');
        globalActions.className = 'app-global-actions';
        globalActions.setAttribute('aria-label', '공통 계산 설정');
        moveUntil(blacklistStart, resultArea, globalActions);
        const calculationButton = globalActions.querySelector('.btn-calc');
        if (calculationButton) globalActions.appendChild(calculationButton);
        container.appendChild(globalActions);
    }());
