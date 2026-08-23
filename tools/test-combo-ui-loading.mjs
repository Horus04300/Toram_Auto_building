import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const skill = {
  id: 'Demo:0', treeId: 'Demo', skillId: 0, nameKo: '검증 스킬', kind: 'attack',
  sourceRef: { file: 'docs/sources/skills/Blade.txt', anchor: '블레이드 마스터리 패시브' },
  attacks: [], effects: []
};
// 상태 표시용 등록은 아직 계산 효과를 갖지 않을 수 있다.
const metadataOnlyBuff = { id: 'Demo:1', treeId: 'Demo', skillId: 1, nameKo: '표시 전용 버프', kind: 'buff' };
const window = {
  TORAM_SKILL_EFFECT_DATA: { skills: [] },
  TORAM_SKILL_COMBAT_CATALOG: { skills: [skill] },
  ToramSkillEffectRegistry: { all: () => [null, skill, metadataOnlyBuff] },
  ToramComboSequence: {},
  skillSimulatorState: { getInvestments: () => ({ Demo: { 0: 10 } }) },
  localStorage: { getItem: () => 'null', setItem() {} }
};
window.window = window;
const document = { readyState: 'loading', addEventListener() {} };
const context = { window, document, console };
vm.createContext(context);

vm.runInContext(await readFile(resolve(root, 'assets/js/skill-effect-engine.js'), 'utf8'), context, { filename: 'assets/js/skill-effect-engine.js' });
assert.doesNotThrow(() => window.ToramSkillEffects.profile('Demo:0', { level: 1 }, {}, {}, {}), '빈 등록 슬롯 뒤의 스킬도 엔진 프로필을 만들 수 있어야 합니다.');
assert.doesNotThrow(() => window.ToramSkillEffects.profile('Demo:0', { level: 1 }, {}, {}, { activeBuffs: { 'Demo:1': { active: true, stacks: 0 } } }), '계산 효과가 없는 액티브 버프가 켜져도 콤보 스킬 프로필은 만들어져야 합니다.');

vm.runInContext(await readFile(resolve(root, 'assets/js/combo-ui.js'), 'utf8'), context, { filename: 'assets/js/combo-ui.js' });
assert.deepEqual(Array.from(window.ToramComboUi.getAvailableSkills(), (item) => item.id), ['Demo:0'], '빈 등록 슬롯은 콤보 스킬 목록에서 무시해야 합니다.');

console.log('Combo UI null-definition regression: PASS');
