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
const window = {
  TORAM_SKILL_EFFECT_DATA: { skills: [] },
  TORAM_SKILL_COMBAT_CATALOG: { skills: [skill] },
  ToramSkillEffectRegistry: { all: () => [null, skill] },
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

vm.runInContext(await readFile(resolve(root, 'assets/js/combo-ui.js'), 'utf8'), context, { filename: 'assets/js/combo-ui.js' });
assert.deepEqual(Array.from(window.ToramComboUi.getAvailableSkills(), (item) => item.id), ['Demo:0'], '빈 등록 슬롯은 콤보 스킬 목록에서 무시해야 합니다.');

console.log('Combo UI null-definition regression: PASS');
