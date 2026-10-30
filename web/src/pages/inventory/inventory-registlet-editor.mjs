import {createRegistletSelection,registletEffect,validateRegistletSelection} from '../../application/registlet-catalog.mjs';
import {renderRegistletDetails} from '../../ui/registlet-details.mjs';

export function createInventoryRegistletEditor(documentRef,panel,catalog,shell) {
  panel.innerHTML = `<h3>레지스트렛 보관</h3><form novalidate><label>젬 카트리지<select name="registletId"></select></label><label>젬 레벨<input name="registletLevel" type="number" min="1" step="1" required aria-describedby="inventoryRegistletError"></label><label class="registlet-skill-level" hidden><span>파워 웨이브 스킬 Lv</span><input name="registletSkillLevel" type="number" min="1" max="10" step="1" value="10" required></label><label class="registlet-material-level">동일 재료 젬 Lv<input name="registletMaterialLevel" type="number" min="1" step="1" value="1" required></label></form><p class="registlet-cap"></p><p class="registlet-effect"></p><div class="registlet-detail-values"></div><p id="inventoryRegistletError" role="status" class="is-error"></p><button type="button">도감에서 보기</button>`;
  const form = panel.querySelector('form'), id = form.elements.registletId, level = form.elements.registletLevel;
  const find = selector => panel.querySelector(selector);
  let items, record, dirty = false;
  function selection() {
    const item = items.find(item => item.id === Number(id.value));
    return record?.data.selection.registletId === item.id
      ? validateRegistletSelection({...record.data.selection,level:Number(level.value)})
      : createRegistletSelection(item,Number(level.value));
  }
  function preview() {
    const item = items.find(item => item.id === Number(id.value));
    level.max = record?.data.selection.registletId === item.id ? record.data.selection.levelCap : item.levelCap;
    find('.registlet-cap').textContent = `최대 Lv${level.max}`;
    find('.registlet-skill-level').hidden = ![207,1053].includes(item.id);
    find('.registlet-skill-level span').textContent = item.id === 1053 ? '스컬 셰이커 스킬 Lv' : '파워 웨이브 스킬 Lv';
    find('.registlet-material-level').hidden = item.levelCap === 1;
    form.elements.registletMaterialLevel.max = item.levelCap;
    try {
      const value = selection(), effect = registletEffect(value,[207,1053].includes(item.id) ? Number(form.elements.registletSkillLevel.value) : null);
      find('.registlet-effect').textContent = effect.description;
      renderRegistletDetails(documentRef,find('.registlet-detail-values'),item,value,{effect,materialLevel:Number(form.elements.registletMaterialLevel.value)});
      find('.is-error').textContent = ''; level.removeAttribute('aria-invalid');
    } catch (error) {find('.registlet-effect').textContent = ''; find('.registlet-detail-values').replaceChildren(); find('.is-error').textContent = error.message; level.setAttribute('aria-invalid','true');}
  }
  id.addEventListener('change',() => {level.value = form.elements.registletMaterialLevel.value = 1; dirty = true; preview();});
  level.addEventListener('input',() => {dirty = true; preview();});
  for (const name of ['registletSkillLevel','registletMaterialLevel']) form.elements[name].addEventListener('input',preview);
  panel.querySelector('button').addEventListener('click',() => shell.open('catalog',{params:{section:'registlets',registletKind:null,q:null,selected:id.value,level:level.value}}));
  return {form,record:() => record,isOpen:() => !panel.hidden,isDirty:() => dirty,
    async load() {
      if (items) return;
      items = await catalog.list();
      id.replaceChildren(...items.map(item => new documentRef.defaultView.Option(item.name,item.id)));
    },
    close() {panel.hidden = true; dirty = false;},
    saved(value) {record = value; dirty = false;},
    open(value) {record = value; form.reset(); id.value = value?.data.selection.registletId ?? items[0].id; level.value = value?.data.selection.level ?? 1; dirty = false; panel.hidden = false; preview();},
    async read() {const value = selection(); return {name:record?.name || value.name,type:'registlet',data:{selection:value}};}
  };
}
