    (function () {
        const data = window.SKILL_TREE_DATA;
        if (!data || !Array.isArray(data.trees)) return;
        const maxLevel = Number(data.skillMaxLevel) || 10;
        const prerequisiteLevel = Number(data.prerequisiteLevel) || 5;
        const categoryDefinitions = [
            { id: 'weapon', directory: 'Weapon Skills', display: '무기', icon: 'coryn_skill_icons/Weapon Skills/Blade/00_Hammer Slam.png' },
            { id: 'buff', directory: 'Buff Skills', display: '버프', icon: 'coryn_skill_icons/Buff Skills/Assassin/00_Assassin Stab.png' },
            { id: 'assist', directory: 'Assist Skills', display: '보조', icon: 'coryn_skill_icons/Assist Skills/Battle/00_Magic UP.png' }
        ];
        const treesById = new Map(data.trees.map(function (tree) { return [tree.id, tree]; }));
        const state = { step: 1, levels: {} };
        data.trees.forEach(function (tree) {
            state.levels[tree.id] = {};
            tree.skills.forEach(function (skill) { state.levels[tree.id][skill.id] = 0; });
        });
        const categoryRail = document.getElementById('combatCategoryRail');
        const combatTreeRail = document.getElementById('combatTreeRail');
        const otherTreeRail = document.getElementById('otherTreeRail');
        const combatStage = document.getElementById('combatSkillStage');
        const otherStage = document.getElementById('otherSkillStage');
        if (!categoryRail || !combatTreeRail || !otherTreeRail || !combatStage || !otherStage) return;
        let activeCategoryId = 'weapon';
        let activeCombatTree = 'Blade';
        let activeOtherTree = 'Alchemy';

const skillStorageKey = 'toram-auto-building.skill-tree.v1';
        const skillUiStorageKey = 'toram-auto-building.skill-tree-ui.v1';
        let storageMessage = '';
        let storageStatus = null;

        function setStorageStatus(message) {
            storageMessage = message;
            if (storageStatus) storageStatus.textContent = message;
        }
function createSkillSnapshot() {
            // Coryn Club save_all() compatible: { TreeName: { SkillIndex: Level } }.
            const save = {};
            data.trees.forEach(function (tree) {
                save[tree.id] = {};
                tree.skills.forEach(function (skill) {
                    const level = state.levels[tree.id][skill.id];
                    if (level > 0) save[tree.id][skill.id] = level;
                });
            });
            // Coryn currently includes Scroll. This app intentionally omits the tree, but keeps an empty key for compatibility.
            save.Scroll = {};
            return save;
        }
        function applySkillSnapshot(snapshot) {
            // Also accepts the legacy v1.2.0 wrapper so existing local saves are not lost.
            const saved = snapshot && snapshot.state && snapshot.state.levels ? snapshot.state.levels : snapshot;
            if (!saved || typeof saved !== 'object' || Array.isArray(saved)) throw new Error('유효한 Coryn 스킬 저장 파일이 아닙니다.');
            data.trees.forEach(function (tree) {
                tree.skills.forEach(function (skill) {
                    const value = Number(saved[tree.id] && saved[tree.id][skill.id]);
                    state.levels[tree.id][skill.id] = Number.isFinite(value) ? Math.min(maxLevel, Math.max(0, Math.floor(value))) : 0;
                });
                tree.skills.forEach(function (skill) { if (state.levels[tree.id][skill.id] > 0) ensurePrerequisite(tree, skill.prereq); });
            });
        }function persistSkillState() {
            try {
                window.localStorage.setItem(skillStorageKey, JSON.stringify(createSkillSnapshot()));
                window.localStorage.setItem(skillUiStorageKey, JSON.stringify({ step: state.step, activeCategoryId: activeCategoryId, activeCombatTree: activeCombatTree, activeOtherTree: activeOtherTree }));
                setStorageStatus('자동 저장됨');
                return true;
            } catch (error) {
                setStorageStatus('자동 저장 불가 · 파일로 보관');
                return false;
            }
        }
        function restoreAutoSavedState() {
            try {
                const raw = window.localStorage.getItem(skillStorageKey);
                if (raw) applySkillSnapshot(JSON.parse(raw));
                const uiRaw = window.localStorage.getItem(skillUiStorageKey);
                if (uiRaw) {
                    const ui = JSON.parse(uiRaw);
                    state.step = [1, 5, 10].includes(Number(ui.step)) ? Number(ui.step) : state.step;
                    activeCategoryId = categoryDefinitions.some(function (category) { return category.id === ui.activeCategoryId; }) ? ui.activeCategoryId : activeCategoryId;
                    const activeCategory = categoryDefinitions.find(function (category) { return category.id === activeCategoryId; });
                    activeCombatTree = data.trees.some(function (tree) { return tree.category === activeCategory.directory && tree.id === ui.activeCombatTree; }) ? ui.activeCombatTree : activeCombatTree;
                    activeOtherTree = data.trees.some(function (tree) { return tree.category === 'Other Skills' && tree.id === ui.activeOtherTree; }) ? ui.activeOtherTree : activeOtherTree;
                }
                if (raw) setStorageStatus('자동 저장 복원됨');
            } catch (error) {
                setStorageStatus('자동 저장을 읽지 못함');
            }
        }        function exportSkillState() {
            const snapshot = createSkillSnapshot();
            const blob = new Blob([JSON.stringify(snapshot, null, 2)], { type: 'application/json' });
            const link = document.createElement('a');
            const date = new Date().toISOString().slice(0, 10);
            link.href = URL.createObjectURL(blob); link.download = 'toram-coryn-skill-save-' + date + '.json';
            document.body.appendChild(link); link.click(); link.remove();
            window.setTimeout(function () { URL.revokeObjectURL(link.href); }, 0);
            setStorageStatus('저장 파일을 내려받음');
        }
        function importSkillState(file) {
            if (!file) return;
            const reader = new FileReader();
            reader.onload = function () {
                try {
                    const snapshot = JSON.parse(String(reader.result));
                    if (snapshot.format && snapshot.format !== 'toram-auto-skill-tree') throw new Error('다른 형식의 파일입니다.');
                    applySkillSnapshot(snapshot); persistSkillState(); setStorageStatus('저장 파일을 불러옴'); renderAll();
                } catch (error) {
                    setStorageStatus('불러오기 실패: 스킬 저장 JSON만 사용할 수 있습니다.');
                }
            };
            reader.onerror = function () { setStorageStatus('저장 파일을 읽지 못했습니다.'); };
            reader.readAsText(file, 'utf-8');
        }
        function resetSkillState() {
            if (!window.confirm('모든 스킬 투자 포인트를 초기화할까요?')) return;
            data.trees.forEach(function (tree) { tree.skills.forEach(function (skill) { state.levels[tree.id][skill.id] = 0; }); });
            persistSkillState(); setStorageStatus('스킬 포인트를 초기화함'); renderAll();
        }
        restoreAutoSavedState();

        function treeLabel(tree) { return tree.nameKo || tree.id; }
        function skillLabel(skill) { return skill.nameKo || skill.name; }

        function iconPath(path) { return encodeURI(path); }
        function treeTotal(treeId) {
            const tree = treesById.get(treeId);
            const spent = tree.skills.reduce(function (sum, skill) { return sum + state.levels[treeId][skill.id]; }, 0);
            return { spent: spent, maximum: tree.skills.length * maxLevel };
        }
        function categoryTotal(directory) {
            return data.trees.filter(function (tree) { return tree.category === directory; }).reduce(function (sum, tree) { return sum + treeTotal(tree.id).spent; }, 0);
        }
        function categoryMaximum(directory) {
            return data.trees.filter(function (tree) { return tree.category === directory; }).reduce(function (sum, tree) { return sum + tree.skills.length * maxLevel; }, 0);
        }
        const medalSkillPoints = 43;
        function availableSkillPoints() {
            const levelInput = document.getElementById('charLevel');
            const level = Math.max(0, Math.floor(Number(levelInput && levelInput.value) || 0));
            return level + Math.floor(level / 5) + medalSkillPoints;
        }
        function totalInvestedSkillPoints() {
            return data.trees.reduce(function (sum, tree) { return sum + treeTotal(tree.id).spent; }, 0);
        }
        function skillById(tree, id) { return tree.skills.find(function (skill) { return skill.id === id; }); }
        function ensurePrerequisite(tree, skillId) {
            if (skillId < 0) return;
            const prerequisite = skillById(tree, skillId);
            if (!prerequisite) return;
            ensurePrerequisite(tree, prerequisite.prereq);
            state.levels[tree.id][prerequisite.id] = Math.max(state.levels[tree.id][prerequisite.id], prerequisiteLevel);
        }
        function addSkillLevel(treeId, skillId) {
            const tree = treesById.get(treeId);
            const skill = skillById(tree, skillId);
            const current = state.levels[treeId][skillId];
            const next = Math.min(maxLevel, current + state.step);
            if (next === current) return;
            ensurePrerequisite(tree, skill.prereq);
            state.levels[treeId][skillId] = next;
            renderAll();
        }
        function removeDescendants(tree, skillId) {
            tree.skills.filter(function (candidate) { return candidate.prereq === skillId; }).forEach(function (child) {
                state.levels[tree.id][child.id] = 0;
                removeDescendants(tree, child.id);
            });
        }
        function removeSkillLevel(treeId, skillId) {
            const tree = treesById.get(treeId);
            const current = state.levels[treeId][skillId];
            const next = Math.max(0, current - state.step);
            if (next === current) return;
            state.levels[treeId][skillId] = next;
            if (next < prerequisiteLevel) removeDescendants(tree, skillId);
            renderAll();
        }
        function createCategoryButton(category) {
            const total = categoryTotal(category.directory);
            const maximum = categoryMaximum(category.directory);
            const button = document.createElement('button');
            button.type = 'button';
            button.className = 'skill-bookmark-button skill-category-button' + (category.id === activeCategoryId ? ' active' : '');
            button.setAttribute('aria-pressed', String(category.id === activeCategoryId));
            button.title = category.display;
            const icon = document.createElement('img'); icon.src = iconPath(category.icon); icon.alt = '';
            const info = document.createElement('span'); info.className = 'bookmark-info';
            const label = document.createElement('span'); label.className = 'bookmark-label'; label.textContent = category.display;
            const points = document.createElement('span'); points.className = 'bookmark-points'; points.textContent = '(' + total + '/' + maximum + ')';
            info.append(label, points); button.append(icon, info);
            button.addEventListener('click', function () { activeCategoryId = category.id; activeCombatTree = categoryTrees(category.directory)[0].id; renderAll(); });
            return button;
        }
        function categoryTrees(directory) { return data.trees.filter(function (tree) { return tree.category === directory; }); }
        function createTreeButton(tree, active, onClick) {
            const total = treeTotal(tree.id);
            const button = document.createElement('button');
            button.type = 'button'; button.className = 'skill-bookmark-button skill-tree-button' + (active ? ' active' : '');
            button.setAttribute('aria-pressed', String(active)); button.title = treeLabel(tree);
            const icon = document.createElement('img'); icon.src = iconPath('coryn_skill_icons/' + tree.category + '/' + tree.id + '/title.png'); icon.alt = '';
            const info = document.createElement('span'); info.className = 'bookmark-info';
            const label = document.createElement('span'); label.className = 'bookmark-label'; label.textContent = treeLabel(tree);
            const points = document.createElement('span'); points.className = 'bookmark-points'; points.textContent = '(' + total.spent + '/' + total.maximum + ')';
            info.append(label, points); button.append(icon, info); button.addEventListener('click', onClick);
            return button;
        }
        function renderStage(stage, treeId) {
            const tree = treesById.get(treeId);

            stage.classList.add('skill-simulator-stage');
            stage.innerHTML = '';

            const scroll = document.createElement('div'); scroll.className = 'skill-tree-scroll';
            const canvas = document.createElement('div'); canvas.className = 'skill-tree-canvas'; canvas.style.setProperty('--tree-columns', String(tree.grid.columns)); canvas.style.setProperty('--tree-rows', String(tree.grid.rows));
            const compactLayout = window.matchMedia('(max-width: 600px)').matches;
            const cellWidth = compactLayout ? 70 : 82;
            const cellHeight = compactLayout ? 62 : 68;
            const paddingX = compactLayout ? 8 : 12;
            const paddingY = compactLayout ? 12 : 16;
            const backgroundSize = compactLayout ? 44 : 50;
            const svgWidth = paddingX * 2 + tree.grid.columns * cellWidth;
            const svgHeight = paddingY * 2 + tree.grid.rows * cellHeight;
            const pointFor = function (x, y) {
                return [paddingX + x * cellWidth + cellWidth / 2, paddingY + y * cellHeight + 2 + backgroundSize / 2];
            };
            const connectorLayer = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
            connectorLayer.setAttribute('class', 'skill-tree-connector-layer');
            connectorLayer.setAttribute('width', String(svgWidth)); connectorLayer.setAttribute('height', String(svgHeight));
            connectorLayer.setAttribute('viewBox', '0 0 ' + svgWidth + ' ' + svgHeight);
            tree.skills.filter(function (skill) { return skill.prereq >= 0; }).forEach(function (skill) {
                const parent = skillById(tree, skill.prereq);
                if (!parent) return;
                const parentPoint = pointFor(parent.x, parent.y);
                const skillPoint = pointFor(skill.x, skill.y);
                const points = [parentPoint];
                if (Array.isArray(skill.via) && skill.via.length === 2) {
                    points.push(pointFor(skill.via[0], skill.via[1]));
                } else {
                    const bendX = (parentPoint[0] + skillPoint[0]) / 2;
                    points.push([bendX, parentPoint[1]], [bendX, skillPoint[1]]);
                }
                points.push(skillPoint);
                const line = document.createElementNS('http://www.w3.org/2000/svg', 'polyline');
                line.setAttribute('class', 'skill-tree-connector' + (state.levels[tree.id][skill.id] > 0 ? ' is-active' : ''));
                line.setAttribute('points', points.map(function (point) { return point[0] + ',' + point[1]; }).join(' '));
                connectorLayer.appendChild(line);
            });
            canvas.appendChild(connectorLayer);
            tree.skills.forEach(function (skill) {
                const level = state.levels[tree.id][skill.id];
                const node = document.createElement('button'); node.type = 'button'; node.className = 'skill-node' + (level > 0 ? ' is-invested' : ''); node.style.gridColumn = String(skill.x + 1); node.style.gridRow = String(skill.y + 1); node.style.backgroundImage = "url('" + iconPath('coryn_skill_icons/icons/' + (level > 0 ? 'skill_on.png' : 'skill_off.png')) + "')"; node.title = skillLabel(skill) + ' Lv ' + level + '/' + maxLevel;
                const image = document.createElement('img'); image.className = 'skill-node-icon' + (skill.iconAvailable ? '' : ' is-missing'); image.src = iconPath(skill.icon); image.alt = skillLabel(skill); image.onerror = function () { this.classList.add('is-missing'); };
                const name = document.createElement('span'); name.className = 'skill-node-name'; name.textContent = skillLabel(skill);
                const levelLabel = document.createElement('span'); levelLabel.className = 'skill-node-level'; levelLabel.textContent = 'Lv ' + level + '/' + maxLevel;
                node.append(image, name, levelLabel); node.addEventListener('click', function () { addSkillLevel(tree.id, skill.id); }); node.addEventListener('contextmenu', function (event) { event.preventDefault(); removeSkillLevel(tree.id, skill.id); }); canvas.appendChild(node);
            });
            scroll.appendChild(canvas); stage.appendChild(scroll);
        }
const skillHeading = document.getElementById('combatSkillBookmarkTitle').parentElement;
        const skillTotalSummary = document.createElement('span');
        skillTotalSummary.className = 'skill-simulator-total';
        skillTotalSummary.title = '캐릭터 레벨당 1포인트 + 5레벨당 추가 1포인트 + 훈장 보너스 43포인트입니다. 스타젬 등을 고려해 투자 자체는 제한하지 않습니다.';
        skillHeading.appendChild(skillTotalSummary);
        const stepControl = document.createElement('div');
        stepControl.className = 'skill-point-step-group';
        skillHeading.appendChild(stepControl);
        const storageControls = document.createElement('div');
        storageControls.className = 'skill-storage-controls';
        const exportButton = document.createElement('button');
        exportButton.type = 'button'; exportButton.className = 'skill-storage-button'; exportButton.textContent = '저장'; exportButton.title = 'Coryn Club save_all 형식 JSON으로 저장';
        exportButton.addEventListener('click', exportSkillState);
        const importButton = document.createElement('button');
        importButton.type = 'button'; importButton.className = 'skill-storage-button'; importButton.textContent = '불러오기'; importButton.title = 'Coryn Club save_all 형식 JSON 불러오기';
        const importInput = document.createElement('input');
        importInput.type = 'file'; importInput.accept = 'application/json,.json'; importInput.hidden = true;
        importButton.addEventListener('click', function () { importInput.click(); });
        importInput.addEventListener('change', function () { importSkillState(importInput.files[0]); importInput.value = ''; });
        const resetButton = document.createElement('button');
        resetButton.type = 'button'; resetButton.className = 'skill-storage-button danger'; resetButton.textContent = '초기화'; resetButton.title = '모든 스킬 투자 포인트 초기화';
        resetButton.addEventListener('click', resetSkillState);
        storageStatus = document.createElement('span'); storageStatus.className = 'skill-storage-status'; storageStatus.textContent = storageMessage || '이 기기에 자동 저장';
        storageControls.append(exportButton, importButton, resetButton, importInput, storageStatus);
        skillHeading.appendChild(storageControls);        function renderStepControls() {
            stepControl.innerHTML = '';
            [1, 5, 10].forEach(function (amount) {
                const button = document.createElement('button');
                button.type = 'button';
                button.className = 'skill-point-step' + (state.step === amount ? ' active' : '');
                button.textContent = amount;
                button.title = '한 번에 ' + amount + ' 포인트';
                button.addEventListener('click', function () { state.step = amount; renderAll(); });
                stepControl.appendChild(button);
            });
        }        function renderAll() {
            const activeCategory = categoryDefinitions.find(function (category) { return category.id === activeCategoryId; });
            persistSkillState();
            skillTotalSummary.textContent = '전체 (' + totalInvestedSkillPoints() + '/' + availableSkillPoints() + ')';
            renderStepControls();
            categoryRail.innerHTML = ''; categoryDefinitions.forEach(function (category) { categoryRail.appendChild(createCategoryButton(category)); });
            combatTreeRail.innerHTML = ''; categoryTrees(activeCategory.directory).forEach(function (tree) { combatTreeRail.appendChild(createTreeButton(tree, tree.id === activeCombatTree, function () { activeCombatTree = tree.id; renderAll(); })); });
            otherTreeRail.innerHTML = ''; categoryTrees('Other Skills').forEach(function (tree) { otherTreeRail.appendChild(createTreeButton(tree, tree.id === activeOtherTree, function () { activeOtherTree = tree.id; renderAll(); })); });
            renderStage(combatStage, activeCombatTree); renderStage(otherStage, activeOtherTree);
        }
        window.skillSimulatorState = { data: data, levels: state.levels, getInvestments: function () { return JSON.parse(JSON.stringify(state.levels)); } };
        const charLevelInput = document.getElementById('charLevel');
        if (charLevelInput) charLevelInput.addEventListener('input', renderAll);
        renderAll();
        let resizeTimer;
        window.addEventListener('resize', function () {
            window.clearTimeout(resizeTimer);
            resizeTimer = window.setTimeout(renderAll, 120);
        });
    }());
    // Top-level workspace tabs: existing controls are moved without changing their logic.
