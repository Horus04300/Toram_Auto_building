import {createActiveBuffUi} from '../../../web/src/ui/active-buff-ui.js';
import {skillRegistry} from '../../../web/src/data/skill-effect-registry.js';
import {skillTreeData} from '../../../web/src/data/skill-tree-data.js';
import {buildStore} from '../../../web/src/application/build-draft-store.js';
import assert from 'node:assert/strict';

const investmentLevels = new Proxy({}, { get: () => new Proxy({}, { get: () => 10 }) });
const document = {
  readyState: 'complete',
  addEventListener() {},
  getElementById(id) {
    if (id === 'mainWeaponType') return { value: '한손검' };
    if (id === 'subWeaponType') return { value: '없음' };
    if (id === 'charLevel') return { value: '290' };
    return null;
  }
};
const window = {
  localStorage: { getItem: () => '{}', setItem() {} },
  skillSimulatorState: { getInvestments: () => investmentLevels },
  ToramSkillEffects: {
    condition: () => true,
    expression: (value) => Number(value && value.value) || 0
  }
};
buildStore.commitBuild({skillLevels:Object.fromEntries(skillTreeData.trees.map(tree=>[tree.id,Object.fromEntries(tree.skills.map(skill=>[skill.id,10]))]))});
const buffs=createActiveBuffUi(document);
const skills = skillRegistry.definitions();
const displaySkills = buffs.getDisplaySkills();
assert.equal(new Set(displaySkills.map(skill=>skill.id)).size,displaySkills.length,'One card per skill ID');
for (const skill of displaySkills) {
  assert.equal(skill,skillRegistry.get(skill.id),'The card and calculator use the same definition');
  if (skills.find(item=>item.id===skill.id).stackControl) assert.ok(skill.stackControl);
}
assert.ok(displaySkills.some(skill=>skill.stackControl),'Stack controls remain available');
console.log('Active buff UI: PASS (canonical skill IDs and stack controls)');
