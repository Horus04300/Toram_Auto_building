import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const rows = [];
const events = [];
const buffOpts = {
  querySelectorAll() { return rows; },
  get lastElementChild() { return rows.at(-1) || null; }
};
const document = {
  readyState:'loading',
  addEventListener() {},
  getElementById(id) { return id === 'buffOpts' ? buffOpts : null; },
  dispatchEvent(event) { events.push(event.type); }
};
const signature = [{ key:'ATK_P', value:10 }, { key:'ASPD', value:1000 }, { key:'DAMAGE_P', value:-45 }];
const window = {
  ToramBuildDraftStore:{ syncFromUi() {} },
  ToramApplication:{ CalculateBuild() { return { snapshot:{ baseContext:{}, build:{ activeBuffs:{ 'Knight:0':{ active:true, stacks:0 } } } }, combat:{} }; } },
  ToramSkillEffects:{ activeStatChanges() { return signature; } },
  ToramSkillUi:{ restore() {} },
  ToramActiveBuffs:{ restore() {} },
  ToramComboUi:{ restore() {} },
  ToramApp:{ crystaUi:{ updateSubWeaponList() {}, refreshAllCrystaInfo() {}, onSubWeaponChange() {}, addOptionRow() {
    const type = { value:'', dispatchEvent() {} }, value = { value:'' };
    rows.push({ remove() { rows.splice(rows.indexOf(this), 1); }, querySelector(selector) { return selector === '.opt-type' ? type : (selector === '.opt-val' ? value : null); } });
  } } },
  setTimeout(callback) { callback(); return 0; }
};
window.window = window;
const context = { window, document, Event:class Event { constructor(type) { this.type = type; } }, CustomEvent:class CustomEvent { constructor(type) { this.type = type; } }, console };
vm.createContext(context);
vm.runInContext(await readFile(resolve(root, 'assets/js/build-state-storage.js'), 'utf8'), context, { filename:'assets/js/build-state-storage.js' });

window.ToramBuildStateUi.restoreSession({
  build:{
    character:{ attributes:{} }, equipment:{}, skillLevels:{}, activeBuffs:{ 'Knight:0':{ active:true, stacks:0 } }, combo:[],
    externalOptions:[{ key:'MAXMP', value:500 }, ...signature, ...signature]
  }, scenario:{ target:{} }
});

assert.equal(rows.length, 1, '구형 프록시가 여러 번 저장된 접미사는 모두 제거해야 합니다.');
assert.equal(rows[0].querySelector('.opt-type').value, 'MAXMP', '실제 사용자가 입력한 외부 옵션 접두사는 보존해야 합니다.');
assert.equal(rows[0].querySelector('.opt-val').value, '500');
assert.ok(events.includes('toram:persistent-state-changed'), '복구한 세션은 정리된 상태로 다시 저장해야 합니다.');
console.log('Active buff session repair: PASS (repeated legacy suffix removed, user options retained)');
