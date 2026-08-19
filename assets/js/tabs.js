    (function () {
        const container = document.querySelector('.container');
        if (!container || document.getElementById('appTabNavigation')) return;

        const navigation = document.createElement('nav');
        navigation.id = 'appTabNavigation';
        navigation.className = 'app-tab-navigation';
        navigation.style.setProperty('--tab-count', '6');
        navigation.setAttribute('aria-label', '자동 빌드 계산기 구분');
        const panelHost = document.createElement('div');
        panelHost.id = 'appTabPanels';
        const tabDefinitions = [
            ['stats-target', '스테이터스'], ['equipment', '장비'], ['skills', '스킬'], ['buffs', '버프'], ['combo', '콤보'], ['results', '결과']
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
            if (!buttons[id]) return;
            Object.keys(panels).forEach(function (key) {
                const isSelected = key === id;
                panels[key].classList.toggle('active', isSelected);
                buttons[key].classList.toggle('active', isSelected);
                buttons[key].setAttribute('aria-selected', String(isSelected));
            });
        }
        Object.keys(buttons).forEach(function (id) { buttons[id].addEventListener('click', function () {
            selectTab(id);
            if (id === 'buffs' && window.ToramActiveBuffs) window.ToramActiveBuffs.render();
        }); });
        buttons.results.addEventListener('click', function () { document.dispatchEvent(new Event('toram:calculate')); });
        window.revealResultTab = function () { selectTab('results'); };

        const firstChild = container.firstChild;
        container.insertBefore(navigation, firstChild);
        container.insertBefore(panelHost, firstChild);
        const sectionTitles = Array.from(container.querySelectorAll(':scope > .section-title'));
        const equipmentStart = sectionTitles[3];
        const blacklistStart = container.querySelector(':scope > .equipment-blacklist') || sectionTitles[4];
        function moveUntil(start, stop, destination) {
            let node = start;
            while (node && node !== stop) {
                const next = node.nextSibling;
                destination.appendChild(node);
                node = next;
            }
        }
        moveUntil(sectionTitles[0], equipmentStart, panels['stats-target']);
        const statusLayout = document.createElement('div');
        statusLayout.className = 'status-tab-layout';
        const investmentPane = document.createElement('section');
        investmentPane.className = 'status-investment-pane';
        const targetPane = document.createElement('section');
        targetPane.className = 'status-target-pane';
        statusLayout.append(investmentPane, targetPane);
        const conditionPane = document.createElement('section');
        conditionPane.className = 'status-condition-pane';
        panels['stats-target'].append(statusLayout, conditionPane);
        const statTitle = sectionTitles[0];
        const specialTitle = sectionTitles[1];
        const targetTitle = sectionTitles[2];
        const levelGroup = document.getElementById('charLevel').closest('.form-group');
        const investmentHeader = panels['stats-target'].querySelector('.status-investment-header');
        const statsGrid = panels['stats-target'].querySelector('.stats-grid');
        const specialOptions = panels['stats-target'].querySelector('.checkbox-container');
        const targetCard = targetTitle ? targetTitle.nextElementSibling : null;
        const investmentBody = document.createElement('div');
        investmentBody.className = 'status-investment-body';
        investmentPane.append(statTitle, investmentBody);
        investmentBody.append(levelGroup, investmentHeader, statsGrid);
        targetPane.append(targetTitle, targetCard);
        conditionPane.append(specialTitle, specialOptions);
        const externalBuffCard = Array.from(container.children).find(function (element) {
            return element.classList && element.classList.contains('equip-card') && element.querySelector('#buffOpts');
        });
        moveUntil(equipmentStart, externalBuffCard, panels.equipment);
        if (externalBuffCard) panels.buffs.appendChild(externalBuffCard);
        const comboIntro = document.createElement('section');
        comboIntro.className = 'equip-card';
        comboIntro.innerHTML = '<h3>🔗 콤보</h3><p>주력기 선택 및 콤보 태그 계산 기능을 여기에 추가합니다.</p>';
        panels.combo.appendChild(comboIntro);
        document.querySelectorAll('body > .skill-bookmark-section').forEach(function (section) { panels.skills.appendChild(section); });
        const resultArea = document.getElementById('resultArea');
        if (resultArea) panels.results.appendChild(resultArea);
        const globalActions = document.createElement('section');
        globalActions.className = 'app-global-actions';
        globalActions.setAttribute('aria-label', '공통 계산 설정');
        moveUntil(blacklistStart, resultArea, globalActions);
        const calculationButton = globalActions.querySelector('.btn-calc');
        if (calculationButton) calculationButton.remove();
        panels.equipment.appendChild(globalActions);
    }());
