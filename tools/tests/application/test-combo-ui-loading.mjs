import {skillRegistry} from '../../../web/src/data/skill-effect-registry.js';
import {skillEffects} from '../../../web/src/calculation/skill-effect-engine.js';
import {createComboUi} from '../../../web/src/ui/combo-ui.js';
import {buildStore} from '../../../web/src/application/build-draft-store.js';
import assert from 'node:assert/strict';

const skill = {
  id: 'Demo:0', treeId: 'Demo', skillId: 0, nameKo: '검증 스킬', kind: 'attack',
  sourceRef: { file: 'docs/sources/skills/Blade.txt', anchor: '블레이드 마스터리 패시브' },
  attacks: [], effects: []
};
// 상태 표시용 등록은 아직 계산 효과를 갖지 않을 수 있다.
const metadataOnlyBuff = { id: 'Demo:1', treeId: 'Demo', skillId: 1, nameKo: '표시 전용 버프', kind: 'buff' };
const document={defaultView:globalThis,getElementById:()=>null,addEventListener(){}};
assert.throws(() => skillRegistry.register([null,skill]));
skillRegistry.register([skill,metadataOnlyBuff]);
assert.doesNotThrow(() => skillEffects.profile('Demo:0', {skillLevels:{Demo:{0:10}}, level: 1 }, {}, {}, {}), '빈 등록 슬롯 뒤의 스킬도 엔진 프로필을 만들 수 있어야 합니다.');
assert.doesNotThrow(() => skillEffects.profile('Demo:0', {skillLevels:{Demo:{0:10}}, level: 1 }, {}, {}, { activeBuffs: { 'Demo:1': { active: true, stacks: 0 } } }), '계산 효과가 없는 액티브 버프가 켜져도 콤보 스킬 프로필은 만들어져야 합니다.');

buildStore.commitBuild({skillLevels:{Blade:{0:10},Demo:{0:10}}});
const comboUi=createComboUi(document,{});
assert.deepEqual(comboUi.getAvailableSkills().map(item=>item.id),['Blade:0'],'Only learned catalog skills belong in the combo selector');

const nineEntries = Array.from({ length:9 }, (_, index) => ({ skillId:'Demo:0', tag:'none', inputs:{ position:index + 1 } }));
comboUi.restore(nineEntries);
assert.equal(comboUi.getEntries().length, 9, '9번째 콤보 칸을 복원할 때 버리면 안 됩니다.');
assert.equal(comboUi.getEntries()[8].inputs.position, 9, '9번째 칸의 입력도 보존해야 합니다.');
comboUi.restore(comboUi.getEntries());
assert.equal(comboUi.getEntries().length, 9, '저장용 입력을 다시 복원해도 9칸을 유지해야 합니다.');
comboUi.restore([...nineEntries, nineEntries[0]]);
assert.equal(comboUi.getEntries().length, 9, '10번째 칸은 현재 지원 범위 밖입니다.');

console.log('Combo UI null-definition regression: PASS');
