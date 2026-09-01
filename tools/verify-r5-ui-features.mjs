import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { LEGACY_SCRIPT_PATHS } from '../assets/js/legacy-script-manifest.mjs';

const root = resolve(import.meta.dirname, '..');
const read = path => readFile(resolve(root, path), 'utf8');
const html = await read('index.html');
const tabs = await read('assets/js/tabs.js');
const bindings = await read('assets/js/ui-bindings.js');
const buildUi = await read('assets/js/build-ui-controller.js');
const optimizer = await read('assets/js/optimizer.js');
const optimizerUi = await read('assets/js/optimizer-ui-controller.js');
const settingsUi = await read('assets/js/build-file-storage.js');
const application = await read('assets/js/application-use-cases.js');
const features = await read('assets/js/ui-feature-registry.js');

for (const id of ['stats', 'target', 'equipment', 'external-buffs', 'crysta-blacklist']) {
  assert.match(html, new RegExp(`data-ui-section="${id}"`), `탭 이동 대상 ${id}는 명시적 식별자가 있어야 합니다.`);
}
assert.match(tabs, /\[data-ui-section="stats"\]/, '탭 UI는 스테이터스 식별자로 시작점을 찾아야 합니다.');
assert.match(tabs, /\[data-ui-section="equipment"\]/, '탭 UI는 장비 식별자로 시작점을 찾아야 합니다.');
assert.doesNotMatch(tabs, /findSectionTitle|textContent\.trim\(\) ===/, '탭 이동은 표시 제목 문자열에 의존하면 안 됩니다.');
assert.match(buildUi, /ToramApp\.buildUi/, '빌드 입력 이벤트는 별도 Build UI 컨트롤러가 소유해야 합니다.');
assert.match(bindings, /app\.buildUi\.bind\(\)/, '공통 UI 부트스트랩은 Build UI 컨트롤러를 호출해야 합니다.');
assert.match(bindings, /app\.optimizerUi\.initialize\(\)/, '공통 UI 부트스트랩은 Optimizer UI 컨트롤러를 호출해야 합니다.');
assert.doesNotMatch(bindings, /addOptionRow|updateSubWeaponList/, '공통 UI 부트스트랩은 세부 빌드 입력 이벤트를 직접 소유하면 안 됩니다.');
assert.match(optimizer, /ToramApplication\.CreateCalculationSnapshot/, '최적화 계산 조립은 Application API를 통해야 합니다.');
assert.match(optimizerUi, /ToramD4ExecutionAdapter\.resume[\s\S]*timeLimitMs:30000/u, 'D4 비동기 재개 제어는 Optimizer UI 컨트롤러에 있어야 합니다.');
assert.match(optimizerUi, /discardD4ContinuationForInputChange/, 'D4 실행 상태 폐기는 Optimizer UI 컨트롤러에 있어야 합니다.');
assert.match(application, /Settings:settings/, '저장 UI는 Application Settings API를 통해야 합니다.');
assert.match(settingsUi, /settingsApi\(\)\.save|settingsApi\(\)\.load|settingsApi\(\)\.remove/, '저장 UI는 Application Settings API만 호출해야 합니다.');
assert.doesNotMatch(settingsUi.replace(/^.*$/m, ''), /ToramBuildSettings|ToramBuildStorageAdapter/, '저장 UI는 저장 계약이나 Tauri 어댑터를 직접 참조하면 안 됩니다.');
for (const feature of ['build:app.buildUi', 'skills:root.ToramSkillUi', 'buffs:root.ToramActiveBuffs', 'combo:root.ToramComboUi', 'optimizer:app.optimizerUi', 'settings:root.ToramBuildFileUi']) {
  assert.ok(features.includes(feature), `UI feature registry에 ${feature}가 있어야 합니다.`);
}
assert.ok(LEGACY_SCRIPT_PATHS.indexOf('assets/js/optimizer.js') < LEGACY_SCRIPT_PATHS.indexOf('assets/js/optimizer-ui-controller.js'), '최적화 UI 컨트롤러는 core 뒤에 로드돼야 합니다.');
assert.ok(LEGACY_SCRIPT_PATHS.indexOf('assets/js/build-ui-controller.js') < LEGACY_SCRIPT_PATHS.indexOf('assets/js/ui-bindings.js'), 'Build UI 컨트롤러는 공통 부트스트랩 전에 로드돼야 합니다.');

console.log('R5 UI feature boundary verification: PASS');
