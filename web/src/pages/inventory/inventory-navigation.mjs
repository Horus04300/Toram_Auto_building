import { createBookmarkButton } from '../../ui/bookmark-button.mjs';
import { EQUIPMENT_SLOTS, EQUIPMENT_TYPES, EQUIPMENT_SLOT_TYPES } from '../../application/equipment-object.mjs';
import { EQUIPMENT_ICONS, EQUIPMENT_SLOT_ICONS } from '../../ui/equipment-icons.mjs';

export const INVENTORY_MAJORS = Object.freeze({equipment:'장비',skills:'스킬',registlets:'레지스트렛',consumables:'도핑',status:'스테이터스',combos:'콤보',build:'빌드'});
const skillCategories = {Weapon_Skills:'무기',Buff_Skills:'버프',Assist_Skills:'보조',Other_Skills:'생활'};
const defaults = {equipment:'equipment',skills:'skill_tree',registlets:'registlet',consumables:'consumable',status:'status',combos:'combo',build:'build'};
export const inventoryMajor = type => Object.keys(defaults).find(key => defaults[key] === type || ({equipment:'equipment_set',skills:'skill_set',consumables:'consumable_set',combos:'combo_set'})[key] === type) || 'equipment';
export const emptyInventoryFilters = () => ({slot:null,equipmentType:null,treeId:null,skillCategory:null,buffGroupId:null,selected:null,page:null,detailTab:null});
export function inventoryGroups(state,{buffs = []} = {}) {
  switch (inventoryMajor(state.type)) {
    case 'equipment': return [{id:'all',label:'전체',type:'equipment',icon:EQUIPMENT_ICONS.equipment},...Object.entries(EQUIPMENT_SLOTS).map(([id,label]) => ({id,label:id === 'mainWeapon' ? '무기' : label,type:'equipment',slot:id,icon:EQUIPMENT_SLOT_ICONS[id]})),{id:'equipment_set',label:'장비셋',type:'equipment_set',icon:EQUIPMENT_ICONS.equipment}];
    case 'skills': return [{id:'all',label:'전체',type:'skill_tree'},...Object.entries(skillCategories).map(([id,label]) => ({id,label,type:'skill_tree',skillCategory:id})),{id:'skill_set',label:'스킬셋',type:'skill_set'}];
    case 'consumables': return [{id:'all',label:'전체',type:'consumable'},...buffs.map(buff => ({id:String(buff.id),label:buff.label,type:'consumable',buffGroupId:String(buff.id)})),{id:'consumable_set',label:'도핑셋',type:'consumable_set'}];
    case 'combos': return [{id:'all',label:'개별 콤보',type:'combo'},{id:'combo_set',label:'콤보 목록',type:'combo_set'}];
    default: return [];
  }
}
export function inventoryLeaves(state,{trees = []} = {}) {
  if (state.type === 'equipment' && ['mainWeapon','subWeapon'].includes(state.slot)) return Object.entries(EQUIPMENT_TYPES).filter(([,types]) => !state.slot || types.some(type => EQUIPMENT_SLOT_TYPES[state.slot]?.includes(type))).map(([id,types]) => ({id,label:types[0] || EQUIPMENT_SLOTS[id],icon:EQUIPMENT_ICONS[id]}));
  if (state.type === 'skill_tree' && state.skillCategory) return trees.filter(tree => tree.category === state.skillCategory).map(tree => ({id:tree.id,label:(tree.nameKo || tree.id).replace(/ 스킬$/u,''),icon:`assets/icons/skills/${tree.category}/${tree.id}/title.png`}));
  return [];
}

function groupMatches(state,group) {
  return state.type === group.type && ['slot','skillCategory','buffGroupId'].every(key => (state[key] || '') === (group[key] || ''));
}

export function createInventoryNavigation(documentRef,page,navigate) {
  const majorRail = page.querySelector('.inventory-major-rail'), groupRail = page.querySelector('.inventory-group-rail'), leafRail = page.querySelector('.inventory-leaf-rail');
  const dialog = page.querySelector('.inventory-navigation-dialog');
  let metadata = {}, state = {}, pendingFocus;
  const mobile = documentRef.defaultView.matchMedia('(max-width:650px)'), toggle = page.querySelector('.inventory-navigation-toggle');
  function choose(value) {page.classList.toggle('inventory-choosing-category',value); toggle.setAttribute('aria-expanded',String(value)); toggle.querySelector('b').textContent = value ? '분류 닫기' : '분류 변경';}
  toggle.addEventListener('click',() => choose(!page.classList.contains('inventory-choosing-category')));
  dialog.querySelector('button').addEventListener('click',() => dialog.hidePopover());
  dialog.addEventListener('toggle',event => {
    if (event.newState !== 'closed') return;
    if (page.hasAttribute('aria-busy')) return;
    const target = Array.from(groupRail.children).find(node => node.dataset.inventoryGroup === pendingFocus?.id);
    target?.focus({preventScroll:true}); pendingFocus = null;
  });
  function button(label,active,filter,id,click,icon) {
    const node = createBookmarkButton(documentRef,{label,active,icon,onClick() {pendingFocus = {filter,id}; click();}});
    node.classList.add('inventory-bookmark'); node.dataset[filter] = id; node.disabled = page.hasAttribute('aria-busy'); return node;
  }
  function render(current = state) {
    state = current;
    const category = current.treeId && !current.skillCategory ? metadata.trees?.find(tree => tree.id === current.treeId)?.category : current.skillCategory;
    const view = {...state,skillCategory:category || ''};
    const major = inventoryMajor(view.type), groups = inventoryGroups(view,metadata), leaves = inventoryLeaves(view,metadata);
    const key = view.type === 'equipment' ? 'equipmentType' : 'treeId';
    const leafLabel = leaves.find(item => item.id === view[key])?.label || (view.equipmentType && EQUIPMENT_TYPES[view.equipmentType]?.[0]);
    const path = [INVENTORY_MAJORS[major],groups.find(group => groupMatches(view,group))?.label,leafLabel].filter(Boolean).join(' · ');
    for (const node of page.querySelectorAll('.inventory-navigation-label,.inventory-location')) {node.textContent = path; node.title = path;}
    majorRail.replaceChildren(...Object.entries(INVENTORY_MAJORS).map(([id,label]) => button(label,id === major,'inventoryMajor',id,() => {if (mobile.matches) choose(Boolean(inventoryGroups({type:defaults[id]},metadata).length)); navigate({...emptyInventoryFilters(),type:defaults[id]});},id === 'equipment' ? EQUIPMENT_ICONS.equipment : undefined)));
    groupRail.replaceChildren(...groups.map(group => {
      const children = inventoryLeaves(group,metadata);
      const changes = {...emptyInventoryFilters(),type:group.type,slot:group.slot || null,skillCategory:group.skillCategory || null,buffGroupId:group.buffGroupId || null};
      const node = button(group.label,groupMatches(view,group),'inventoryGroup',group.id,() => {
        if (!children.length) {if (mobile.matches) choose(false); navigate(changes); return;}
        dialog.querySelector('h3').textContent = `${INVENTORY_MAJORS[major]} · ${group.label}`;
        const childKey = group.type === 'equipment' ? 'equipmentType' : 'treeId';
        leafRail.replaceChildren(...children.map(item => button(item.label,groupMatches(view,group) && item.id === view[childKey],'inventoryLeaf',item.id,() => {
          pendingFocus = {filter:'inventoryGroup',id:group.id};
          dialog.hidePopover(); if (mobile.matches) choose(false);
          navigate({...changes,[childKey]:item.id});
        },item.icon)));
        const rail = groupRail.getBoundingClientRect();
        dialog.style.left = `${rail.right}px`; dialog.style.top = `${rail.top}px`;
        dialog.style.maxHeight = `${rail.height}px`;
        dialog.showPopover(); (leafRail.querySelector('.active') || leafRail.firstElementChild)?.focus();
      },group.icon);
      if (children.length) {node.setAttribute('aria-haspopup','dialog'); node.setAttribute('aria-controls',dialog.id);}
      return node;
    }));
    if (pendingFocus && !page.hasAttribute('aria-busy')) {const focus = pendingFocus; pendingFocus = null; const target = mobile.matches && !page.classList.contains('inventory-choosing-category') ? toggle : Array.from(page.querySelectorAll('.inventory-bookmark')).find(node => node.dataset[focus.filter] === focus.id); target?.focus({preventScroll:true});}
  }
  mobile.addEventListener('change',() => {choose(false); render();});
  documentRef.defaultView.addEventListener('resize',() => dialog.hidePopover());
  return {render,setMetadata(value) {metadata = value;}};
}
