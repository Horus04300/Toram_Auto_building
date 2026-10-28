import {skillTreeData} from '../data/skill-tree-data.js';
import {buildStore} from '../application/build-draft-store.js';
import {createSkillTreeSimulator} from './skill-tree-simulator.mjs';
import {createBookmarkButton} from './bookmark-button.mjs';
export function createSkillUi(document) {
  const root=document.defaultView;

        const data = skillTreeData;
        if (!data || !Array.isArray(data.trees)) return;
        const maxLevel = Number(data.skillMaxLevel) || 10;
        const categoryDefinitions = [
            { id: 'weapon', directory: 'Weapon_Skills', display: '무기', icon: 'assets/icons/skills/Weapon_Skills/Blade/00_HammerSlam.png' },
            { id: 'buff', directory: 'Buff_Skills', display: '버프', icon: 'assets/icons/skills/Buff_Skills/Assassin/00_AssassinStab.png' },
            { id: 'assist', directory: 'Assist_Skills', display: '보조', icon: 'assets/icons/skills/Assist_Skills/Battle/00_MagicUP.png' }
        ];
        const treesById = new Map(data.trees.map(function (tree) { return [tree.id, tree]; }));
        const state = { step: 10, levels: {} };
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

        const simulator = createSkillTreeSimulator(document, {data:data, levels:state.levels, step:function () {return state.step;}, onChange:commitSkillChange});
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
                tree.skills.forEach(function (skill) { if (state.levels[tree.id][skill.id] > 0) simulator.ensurePrerequisite(tree, skill.prereq); });
            });
        }function persistSkillState() {
            setStorageStatus('자동 저장됨');
            document.dispatchEvent(new CustomEvent('toram:persistent-state-changed'));
            return true;
        }
        function commitSkillChange() {
            buildStore.commitBuild({skillLevels:state.levels});
            persistSkillState();
            document.dispatchEvent(new CustomEvent('toram:skill-investments-changed'));
            renderAll();
        }
        function exportSkillState() {
            const snapshot = createSkillSnapshot();
            const blob = new Blob([JSON.stringify(snapshot, null, 2)], { type: 'application/json' });
            const link = document.createElement('a');
            const date = new Date().toISOString().slice(0, 10);
            link.href = URL.createObjectURL(blob); link.download = 'toram-coryn-skill-save-' + date + '.json';
            document.body.appendChild(link); link.click(); link.remove();
            root.setTimeout(function () { URL.revokeObjectURL(link.href); }, 0);
            setStorageStatus('저장 파일을 내려받음');
        }
        function importSkillState(file) {
            if (!file) return;
            const reader = new FileReader();
            reader.onload = function () {
                try {
                    const snapshot = JSON.parse(String(reader.result));
                    if (snapshot.format && snapshot.format !== 'toram-auto-skill-tree') throw new Error('다른 형식의 파일입니다.');
                    applySkillSnapshot(snapshot); commitSkillChange(); setStorageStatus('저장 파일을 불러옴');
                } catch (error) {
                    setStorageStatus('불러오기 실패: 스킬 저장 JSON만 사용할 수 있습니다.');
                }
            };
            reader.onerror = function () { setStorageStatus('저장 파일을 읽지 못했습니다.'); };
            reader.readAsText(file, 'utf-8');
        }
        function resetSkillState() {
            if (!root.confirm('모든 스킬 투자 포인트를 초기화할까요?')) return;
            data.trees.forEach(function (tree) { tree.skills.forEach(function (skill) { state.levels[tree.id][skill.id] = 0; }); });
            commitSkillChange(); setStorageStatus('스킬 포인트를 초기화함');
        }
        function treeLabel(tree) { return tree.nameKo || tree.id; }
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
        function createCategoryButton(category) {
            const button = createBookmarkButton(document, {
                label:category.display, icon:category.icon, active:category.id === activeCategoryId,
                points:'(' + categoryTotal(category.directory) + '/' + categoryMaximum(category.directory) + ')',
                onClick:function () { activeCategoryId = category.id; activeCombatTree = categoryTrees(category.directory)[0].id; renderAll(); }
            });
            button.classList.replace('skill-tree-button','skill-category-button');
            return button;
        }
        function categoryTrees(directory) { return data.trees.filter(function (tree) { return tree.category === directory; }); }
        function createTreeButton(tree, active, onClick) {
            const total = treeTotal(tree.id);
            return createBookmarkButton(document, {
                label:treeLabel(tree), icon:'assets/icons/skills/' + tree.category + '/' + tree.id + '/title.png', active:active,
                points:'(' + total.spent + '/' + total.maximum + ')', onClick:onClick
            });
        }
        function renderStage(stage, treeId) { simulator.render(stage, treeId); }
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
            skillTotalSummary.textContent = '전체 (' + totalInvestedSkillPoints() + '/' + availableSkillPoints() + ')';
            renderStepControls();
            categoryRail.innerHTML = ''; categoryDefinitions.forEach(function (category) { categoryRail.appendChild(createCategoryButton(category)); });
            combatTreeRail.innerHTML = ''; categoryTrees(activeCategory.directory).forEach(function (tree) { combatTreeRail.appendChild(createTreeButton(tree, tree.id === activeCombatTree, function () { activeCombatTree = tree.id; renderAll(); })); });
            otherTreeRail.innerHTML = ''; categoryTrees('Other_Skills').forEach(function (tree) { otherTreeRail.appendChild(createTreeButton(tree, tree.id === activeOtherTree, function () { activeOtherTree = tree.id; renderAll(); })); });
            renderStage(combatStage, activeCombatTree); renderStage(otherStage, activeOtherTree);
        }
        buildStore.commitBuild({skillLevels:state.levels});
        const getInvestments=function () {return buildStore.getBuild().skillLevels;};
        const api = Object.freeze({data:data, refresh:renderAll, restore:function (snapshot) { applySkillSnapshot(snapshot); buildStore.commitBuild({skillLevels:state.levels}); renderAll(); }, getInvestments:getInvestments });
        const charLevelInput = document.getElementById('charLevel');
        if (charLevelInput) charLevelInput.addEventListener('input', renderAll);
        renderAll();
        let resizeTimer;
        root.addEventListener('resize', function () {
            root.clearTimeout(resizeTimer);
            resizeTimer = root.setTimeout(renderAll, 120);
        });

return api;
}
