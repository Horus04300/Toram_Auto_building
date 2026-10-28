import { createSkillTreeSimulator } from '../../ui/skill-tree-simulator.mjs';
import { createBookmarkButton } from '../../ui/bookmark-button.mjs';
import { makeSnapshot } from '../../application/inventory-objects.mjs';
import { mergeInventoryObjects } from '../../application/inventory-merge.mjs';

const categories = {Weapon_Skills:'무기',Buff_Skills:'버프',Assist_Skills:'보조',Other_Skills:'생활'};
const label = tree => (tree.nameKo || tree.id).replace(/ 스킬$/u,'');

export function createInventorySkillEditor(documentRef, panel, api, perform, getTreeData) {
  panel.innerHTML = `<nav class="inventory-skill-modes" aria-label="스킬셋 작업"><button type="button" data-skill-mode="edit">전체 편집</button><button type="button" data-skill-mode="assemble">개별 구성 합치기</button></nav>
    <div class="inventory-skill-edit"><header><strong class="inventory-skill-title"></strong><span class="inventory-skill-points"></span><div class="skill-point-step-group"></div></header>
    <div class="inventory-skill-layout"><nav class="skill-category-rail" aria-label="편집할 스킬 분류"></nav><nav class="skill-tree-rail" aria-label="편집할 스킬트리"></nav><div class="inventory-skill-stage"></div></div></div>
    <section class="inventory-skill-assemble" hidden><div class="inventory-skill-sources"></div><div class="inventory-skill-conflicts"></div></section>`;
  const find = selector => panel.querySelector(selector);
  let data, type, record, levels, simulator, activeTree, category, step = 10, dirty = false, mode = 'edit', pendingMerge;
  const trees = () => getTreeData().trees;
  function markDirty() {dirty = true;}
  function treeData(id) {
    const previous = type === 'skill_tree' ? data : data.trees[id]?.data;
    return {treeId:id,levels:{...levels[id]},activeBuffs:structuredClone(previous?.activeBuffs || {})};
  }
  function read() {
    if (pendingMerge) throw new Error('겹치는 스킬트리에 사용할 구성을 먼저 선택하세요.');
    const title = record?.name || (type === 'skill_tree' ? '새 스킬트리' : '새 스킬셋');
    if (type === 'skill_tree') return {name:title,type,data:treeData(activeTree)};
    const next = structuredClone(data);
    for (const tree of trees()) {
      if (next.trees[tree.id] || Object.values(levels[tree.id]).some(value => value > 0)) next.trees[tree.id] = makeSnapshot('skill_tree',treeData(tree.id),next.trees[tree.id]);
    }
    return {name:title,type,data:next};
  }
  function loadLevels() {
    levels = Object.fromEntries(trees().map(tree => [tree.id,Object.fromEntries(tree.skills.map(skill => [skill.id,(type === 'skill_tree' && data.treeId === tree.id ? data.levels : data.trees?.[tree.id]?.data.levels)?.[skill.id] || 0]))]));
    simulator = createSkillTreeSimulator(documentRef,{data:getTreeData(),levels,step:() => step,onChange() {markDirty(); render();}});
  }
  function bookmark(label, active, onClick, icon, points) {return createBookmarkButton(documentRef,{label,active,onClick,icon,points});}
  function render() {
    const tree = trees().find(tree => tree.id === activeTree), set = type === 'skill_set';
    panel.classList.toggle('inventory-skill-is-set',set);
    find('.inventory-skill-modes').hidden = !set;
    for (const node of panel.querySelectorAll('[data-skill-mode]')) node.setAttribute('aria-pressed',String(node.dataset.skillMode === mode));
    find('.inventory-skill-edit').hidden = mode !== 'edit'; find('.inventory-skill-assemble').hidden = mode !== 'assemble';
    find('.inventory-skill-title').textContent = label(tree);
    const spent = Object.values(levels[tree.id]).reduce((sum,value) => sum + value,0);
    find('.inventory-skill-points').textContent = set ? `전체 ${Object.values(levels).reduce((sum,values) => sum + Object.values(values).reduce((n,value) => n + value,0),0)} · 트리 ${spent} 포인트` : `${spent} 포인트`;
    find('.skill-point-step-group').replaceChildren(...[1,5,10].map(amount => {const node = bookmark(String(amount),step === amount,() => {step = amount; render();}); node.classList.add('skill-point-step'); node.title = `한 번에 ${amount} 포인트`; return node;}));
    find('.skill-category-rail').replaceChildren(...(set ? Object.entries(categories).map(([id,title]) => bookmark(title,id === category,() => {category = id; activeTree = trees().find(tree => tree.category === id).id; render();})) : []));
    find('.skill-tree-rail').replaceChildren(...(set ? trees().filter(tree => tree.category === category).map(tree => bookmark(label(tree),tree.id === activeTree,() => {activeTree = tree.id; render();},`assets/icons/skills/${tree.category}/${tree.id}/title.png`,String(Object.values(levels[tree.id]).reduce((sum,value) => sum + value,0)))) : []));
    simulator.render(find('.inventory-skill-stage'),activeTree);
    fitTree();
  }
  function fitTree() {
    const stage = find('.inventory-skill-stage'), canvas = stage.querySelector('.skill-tree-canvas');
    if (!canvas || !stage.clientWidth || !stage.clientHeight) return;
    canvas.style.zoom = Math.min(.9,(stage.clientWidth - 2) / canvas.offsetWidth,(stage.clientHeight - 2) / canvas.offsetHeight);
  }
  new documentRef.defaultView.ResizeObserver(fitTree).observe(find('.inventory-skill-stage'));
  async function sources() {
    const items = [], target = find('.inventory-skill-sources'); target.replaceChildren();
    for (let page = 1, total = 1; (page - 1) * 50 < total; page++) {const result = await api.list({type:'skill_tree',page,pageSize:50}); total = result.total; items.push(...result.items);}
    if (!items.length) {const node = documentRef.createElement('p'); node.textContent = '저장한 개별 스킬트리가 없습니다.'; target.append(node);}
    for (const item of items) {
      const node = documentRef.createElement('button'); node.type = 'button'; node.textContent = item.name; node.dataset.skillSource = item.id;
      node.addEventListener('click',() => perform(async () => {
        const left = {...read(),schemaVersion:1}, right = await api.get(item.id), merged = mergeInventoryObjects(left,right);
        if (merged.complete) acceptMerge(merged);
        else {pendingMerge = {left,right,preview:merged,choices:[]}; renderConflicts();}
      })); target.append(node);
    }
  }
  function acceptMerge(merged) {
    data = structuredClone(merged.result.data); pendingMerge = null; find('.inventory-skill-conflicts').replaceChildren();
    loadLevels(); markDirty(); render();
  }
  function renderConflicts() {
    const target = find('.inventory-skill-conflicts'); target.replaceChildren();
    for (const conflict of pendingMerge.preview.conflicts) {
      const row = documentRef.createElement('section'), title = documentRef.createElement('strong'); title.textContent = label(trees().find(tree => tree.id === conflict.unit.split('.')[1])); row.append(title);
      for (const [take,text] of [['left','현재 구성 사용'],['right','가져올 구성 사용']]) {
        const node = documentRef.createElement('button'); node.type = 'button'; node.textContent = text; node.dataset.skillTake = take;
        node.addEventListener('click',() => {pendingMerge.choices = pendingMerge.choices.filter(choice => choice.unit !== conflict.unit); pendingMerge.choices.push({unit:conflict.unit,take}); const result = mergeInventoryObjects(pendingMerge.left,pendingMerge.right,pendingMerge.choices); if (result.complete) acceptMerge(result);}); row.append(node);
      }
      target.append(row);
    }
    for (const [take,text] of [['left','현재 셋 전체 사용'],['right','가져온 구성 전체 사용']]) {
      const node = documentRef.createElement('button'); node.type = 'button'; node.textContent = text;
      node.addEventListener('click',() => acceptMerge(mergeInventoryObjects(pendingMerge.left,pendingMerge.right,[{unit:'skills',take}]))); target.append(node);
    }
    const cancel = documentRef.createElement('button'); cancel.type = 'button'; cancel.textContent = '합치기 취소'; cancel.addEventListener('click',() => {pendingMerge = null; target.replaceChildren();}); target.append(cancel);
  }
  for (const node of panel.querySelectorAll('[data-skill-mode]')) node.addEventListener('click',() => perform(async () => {if (pendingMerge) throw new Error('겹치는 트리를 선택하거나 합치기를 취소하세요.'); mode = node.dataset.skillMode; render(); if (mode === 'assemble') await sources();}));
  return {read,isDirty:() => dirty || Boolean(pendingMerge),canSave:() => !pendingMerge,isOpen:() => !panel.hidden,close() {panel.hidden = true;},
    record:() => record,
    saved(value) {record = value; data = structuredClone(value.data); dirty = false;},
    open(value,state) {
      record = value; type = value?.type || state.type; mode = 'edit'; step = 10; dirty = false; pendingMerge = null;
      activeTree = value?.data.treeId || state.treeId || trees().find(tree => !state.skillCategory || tree.category === state.skillCategory).id; category = trees().find(tree => tree.id === activeTree).category;
      data = structuredClone(value?.data || (type === 'skill_tree' ? {treeId:activeTree,levels:{},activeBuffs:{}} : {trees:{}}));
      find('.inventory-skill-conflicts').replaceChildren(); loadLevels(); render(); panel.hidden = false;
    }
  };
}
