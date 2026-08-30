import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const listeners = {};
const controls = {
  mainWeaponType:{ value:'한손검' }, subWeaponType:{ value:'방패' }, subRefine:{ value:'15' }, subAtk:{ value:'300' }, subStab:{ value:'80' }, charLevel:{ value:'300' },
  strBase:{ value:'100' }, intBase:{ value:'100' }, vitBase:{ value:'100' }, agiBase:{ value:'100' }, dexBase:{ value:'100' }, crtBase:{ value:'50' }
};
let proxy = null;
const buffOpts = {
  querySelector(selector) { return selector === '#activeSkillBuffOptions' ? proxy : null; },
  appendChild(node) { proxy = node; }
};
function element(tag) {
  return {
    tagName:tag.toUpperCase(), className:'', children:[], hidden:false, value:'',
    append(...nodes) { this.children.push(...nodes); },
    appendChild(node) { this.children.push(node); return node; },
    set innerHTML(value) { this.children = []; this._innerHTML = value; },
    get innerHTML() { return this._innerHTML || ''; }
  };
}
const document = {
  readyState:'loading',
  addEventListener(type, callback) { (listeners[type] ||= []).push(callback); },
  getElementById(id) { return id === 'buffOpts' ? buffOpts : (controls[id] || null); },
  createElement:element
};
const skill = {
  id:'Demo:0', treeId:'Demo', skillId:0, nameKo:'컨텍스트 검증', kind:'buff', activeBuff:true,
  effects:[
    { type:'stat', key:'REFINE_TEST', value:{ test:'refine' } },
    { type:'stat', key:'BASE_CRT_TEST', value:{ test:'baseCrt' } },
    { type:'stat', key:'TOTAL_VIT_TEST', value:{ test:'totalVit' } }
  ]
};
const window = {
  TORAM_SKILL_EFFECT_DATA:{ skills:[skill] },
  localStorage:{ getItem:() => JSON.stringify({ 'Demo:0':true }), setItem() {} },
  skillSimulatorState:{ getInvestments:() => ({ Demo:{ 0:10 } }) },
  ToramSkillEffects:{
    condition:() => true,
    expression(value, context) {
      if (value.test === 'refine') return context.equipment.subWeaponRefinement;
      if (value.test === 'baseCrt') return context.baseStats.CRT;
      if (value.test === 'totalVit') return context.combatStats.VIT;
      return 0;
    }
  },
  getBaseContext:() => ({ strBase:100, intBase:100, vitBase:100, agiBase:100, dexBase:100, crtBase:50 }),
  applyPassiveSkillStats() {},
  getCurrentCrystas:() => [],
  simulateWithCrystas:() => ({ finalSTR:110, finalINT:120, finalVIT:450, finalAGI:130, finalDEX:140, finalATK:1000, finalMATK:800, finalASPD:1200, finalCSPD:1000, finalStab:80, finalWeaponAttack:300, finalMaxMP:1000 })
};
window.window = window;
const context = { window, document, console };
vm.createContext(context);
vm.runInContext(await readFile(resolve(root, 'assets/js/active-buff-ui.js'), 'utf8'), context, { filename:'assets/js/active-buff-ui.js' });

for (const callback of listeners['toram:calculate'] || []) callback();
assert.ok(proxy, '액티브 버프 옵션 프록시를 생성해야 합니다.');
const values = proxy.children.map(row => Number(row.children[1].value));
assert.deepEqual(values, [15, 50, 450], '방패 제련치·기본 CRT·최종 VIT를 기존 계산 입력에서 가져와야 합니다.');

console.log('Active buff calculation-context regression: PASS');
