import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const skill = {
  id:'Demo:0', treeId:'Demo', skillId:0, nameKo:'컨텍스트 검증', kind:'buff', activeBuff:true,
  effects:[
    { type:'stat', key:'REFINE_TEST', value:{ op:'ref', path:'equipment.subWeaponRefinement' } },
    { type:'stat', key:'BASE_CRT_TEST', value:{ op:'ref', path:'baseStats.CRT' } },
    { type:'stat', key:'TOTAL_VIT_TEST', value:{ op:'ref', path:'combatStats.VIT' } }
  ]
};
const window = {
  TORAM_SKILL_EFFECT_DATA:{ skills:[skill] },
  skillSimulatorState:{ getInvestments:() => ({ Demo:{ 0:10 } }) }
};
window.window = window;
const context = { window, console };
vm.createContext(context);
vm.runInContext(await readFile(resolve(root, 'assets/js/skill-effect-engine.js'), 'utf8'), context, { filename:'assets/js/skill-effect-engine.js' });

const changes = window.ToramSkillEffects.activeStatChanges(
  { level:300, mainType:'한손검', subType:'방패', subRefine:15, strBase:100, intBase:100, vitBase:100, agiBase:100, dexBase:100, crtBase:50 },
  { VIT:450 }, {}, { activeBuffs:{ 'Demo:0':{ active:true, stacks:0 } } }
);
assert.equal(JSON.stringify(changes.map(change => [change.key, change.value])), JSON.stringify([['REFINE_TEST', 15], ['BASE_CRT_TEST', 50], ['TOTAL_VIT_TEST', 450]]), '활성 버프는 계산 엔진이 현재 입력 컨텍스트에서 직접 해석해야 합니다.');
assert.equal(JSON.stringify(window.ToramSkillEffects.activeStatChanges({}, {}, {}, { activeBuffs:{ 'Demo:0':{ active:false, stacks:0 } } })), '[]', '비활성 버프는 외부 옵션으로 남거나 계산에 적용되면 안 됩니다.');

const activeBuffUi = await readFile(resolve(root, 'assets/js/active-buff-ui.js'), 'utf8');
assert.doesNotMatch(activeBuffUi, /container\.appendChild\(proxy\)|proxy\.appendChild\(/u, '활성 버프 효과를 외부 옵션 행으로 복제하면 안 됩니다.');

console.log('Active buff calculation-context regression: PASS (engine-owned effects, no option proxy)');
