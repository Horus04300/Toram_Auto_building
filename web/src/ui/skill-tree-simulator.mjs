export function createSkillTreeSimulator(documentRef, {data, levels, step = () => 10, onChange}) {
  const root = documentRef.defaultView, treesById = new Map(data.trees.map(tree => [tree.id,tree]));
  const maxLevel = Number(data.skillMaxLevel) || 10, prerequisiteLevel = Number(data.prerequisiteLevel) || 5;
  const skillLabel = skill => skill.nameKo || skill.name;
  const iconPath = path => encodeURI(path);
        function skillById(tree, id) { return tree.skills.find(function (skill) { return skill.id === id; }); }
        function ensurePrerequisite(tree, skillId, level = prerequisiteLevel) {
            if (skillId < 0) return false;
            const prerequisite = skillById(tree, skillId);
            if (!prerequisite) return false;
            const changed = ensurePrerequisite(tree, prerequisite.prereq, level);
            const current = levels[tree.id][prerequisite.id];
            levels[tree.id][prerequisite.id] = Math.max(current, level);
            return changed || levels[tree.id][prerequisite.id] !== current;
        }
        function addSkillLevel(treeId, skillId, maximize = false) {
            const tree = treesById.get(treeId);
            const skill = skillById(tree, skillId);
            const current = levels[treeId][skillId];
            const next = maximize ? maxLevel : Math.min(maxLevel, current + step());
            if (!maximize && next === current) return;
            const changed = ensurePrerequisite(tree, skill.prereq, maximize ? maxLevel : prerequisiteLevel);
            if (next === current && !changed) return;
            levels[treeId][skillId] = next;
            onChange();
        }
        function removeDescendants(tree, skillId) {
            tree.skills.filter(function (candidate) { return candidate.prereq === skillId; }).forEach(function (child) {
                levels[tree.id][child.id] = 0;
                removeDescendants(tree, child.id);
            });
        }
        function removeSkillLevel(treeId, skillId) {
            const tree = treesById.get(treeId);
            const current = levels[treeId][skillId];
            const next = Math.max(0, current - step());
            if (next === current) return;
            levels[treeId][skillId] = next;
            if (next < prerequisiteLevel) removeDescendants(tree, skillId);
            onChange();
        }
        function renderStage(stage, treeId) {
            const tree = treesById.get(treeId);

            stage.classList.add('skill-simulator-stage');
            stage.innerHTML = '';

            const scroll = documentRef.createElement('div'); scroll.className = 'skill-tree-scroll';
            const canvas = documentRef.createElement('div'); canvas.className = 'skill-tree-canvas'; canvas.style.setProperty('--tree-columns', String(tree.grid.columns)); canvas.style.setProperty('--tree-rows', String(tree.grid.rows));
            const compactLayout = root.matchMedia('(max-width: 600px)').matches;
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
            const connectorLayer = documentRef.createElementNS('http://www.w3.org/2000/svg', 'svg');
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
                const line = documentRef.createElementNS('http://www.w3.org/2000/svg', 'polyline');
                line.setAttribute('class', 'skill-tree-connector' + (levels[tree.id][skill.id] > 0 ? ' is-active' : ''));
                line.setAttribute('points', points.map(function (point) { return point[0] + ',' + point[1]; }).join(' '));
                connectorLayer.appendChild(line);
            });
            canvas.appendChild(connectorLayer);
            tree.skills.forEach(function (skill) {
                const level = levels[tree.id][skill.id];
                const node = documentRef.createElement('button'); node.type = 'button'; node.className = 'skill-node' + (level > 0 ? ' is-invested' : ''); node.style.gridColumn = String(skill.x + 1); node.style.gridRow = String(skill.y + 1); node.style.backgroundImage = "url('" + iconPath('assets/icons/skills/icons/' + (level > 0 ? 'skill_on.png' : 'skill_off.png')) + "')"; node.title = skillLabel(skill) + ' Lv ' + level + '/' + maxLevel + '\nShift+클릭: 선택 스킬과 선행 스킬 모두 Lv.' + maxLevel;
                const image = documentRef.createElement('img'); image.className = 'skill-node-icon' + (skill.iconAvailable ? '' : ' is-missing'); image.src = iconPath(skill.icon); image.alt = skillLabel(skill); image.onerror = function () { this.classList.add('is-missing'); };
                const name = documentRef.createElement('span'); name.className = 'skill-node-name'; name.textContent = skillLabel(skill);
                const levelLabel = documentRef.createElement('span'); levelLabel.className = 'skill-node-level'; levelLabel.textContent = 'Lv ' + level + '/' + maxLevel;
                node.append(image, name, levelLabel); node.addEventListener('click', function (event) { addSkillLevel(tree.id, skill.id, event.shiftKey); }); node.addEventListener('contextmenu', function (event) { event.preventDefault(); removeSkillLevel(tree.id, skill.id); }); canvas.appendChild(node);
            });
            scroll.appendChild(canvas); stage.appendChild(scroll);
        }
  return {render:renderStage,ensurePrerequisite,add:addSkillLevel,remove:removeSkillLevel};
}
