import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';
import { LEGACY_SCRIPT_PATHS } from '../assets/js/legacy-script-manifest.mjs';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const dataScripts = LEGACY_SCRIPT_PATHS
  .filter((path) => path.startsWith('assets/js/data/'));
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
window.window = window;
const context = { window, document, console };
vm.createContext(context);

for (const path of dataScripts) {
  vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename: path });
}
vm.runInContext(await readFile(resolve(root, 'assets/js/active-buff-ui.js'), 'utf8'), context, { filename: 'assets/js/active-buff-ui.js' });

const rawSkills = window.TORAM_SKILL_EFFECT_DATA.skills.concat(window.ToramSkillEffectRegistry.all());
const duplicateStackBuffIds = [...new Set(rawSkills.filter((skill) => skill.stackControl).map((skill) => skill.id))]
  .filter((id) => rawSkills.filter((skill) => skill.id === id && (skill.kind === 'buff' || skill.activeBuff === true)).length > 1);
assert.ok(duplicateStackBuffIds.length > 0, '중복 스택 버프 정의가 있어야 회귀 테스트가 유효합니다.');

const displaySkills = window.ToramActiveBuffs.getDisplaySkills();
assert.equal(new Set(displaySkills.map((skill) => skill.id)).size, displaySkills.length, '액티브 버프 카드 목록은 스킬 ID별로 하나여야 합니다.');
for (const id of duplicateStackBuffIds) {
  assert.ok(displaySkills.find((skill) => skill.id === id)?.stackControl, id + ': 스택 조절 정의가 카드에 우선되어야 합니다.');
}

console.log('Active buff UI dedup regression: PASS (' + duplicateStackBuffIds.length + ' duplicate stack buffs)');
