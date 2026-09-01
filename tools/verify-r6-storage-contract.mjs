import assert from 'node:assert/strict';
import { access, readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { LEGACY_SCRIPT_PATHS } from '../assets/js/legacy-script-manifest.mjs';

const root = resolve(import.meta.dirname, '..');
const read = path => readFile(resolve(root, path), 'utf8');
const repository = await read('assets/js/settings-repository.js');
const application = await read('assets/js/application-use-cases.js');
const buildState = await read('assets/js/build-state-storage.js');
const buffs = await read('assets/js/active-buff-ui.js');
const combo = await read('assets/js/combo-ui.js');
const skills = await read('assets/js/skill-tree.js');
const rust = await read('src-tauri/src/settings_repository.rs');
const e2e = await read('tools/test-tauri-native-storage-e2e.mjs');

await assert.rejects(access(resolve(root, 'assets/js/build-setting-snapshot.js')));
assert.ok(!LEGACY_SCRIPT_PATHS.includes('assets/js/build-setting-snapshot.js'));
assert.ok(LEGACY_SCRIPT_PATHS.includes('assets/js/settings-repository.js'));
assert.match(repository, /documentType:'saved-build'/);
assert.match(repository, /documentType:'application-state'/);
assert.match(repository, /schemaVersion:SCHEMA_VERSION/);
assert.match(repository, /lastSession/);
assert.match(repository, /appSettings/);
assert.match(application, /ToramSettingsRepository/);
for (const [label, source] of [['build state', buildState], ['active buffs', buffs], ['combo', combo], ['skills', skills]]) {
  assert.doesNotMatch(source, /localStorage/, `${label} UI가 저장소를 직접 읽거나 쓰면 안 됩니다.`);
}
assert.match(rust, /SETTING_FORMAT: &str = "toram-auto-build-document"/);
assert.match(rust, /documentType[\s\S]*saved-build/);
assert.match(rust, /build 객체/);
assert.match(rust, /scenario\.target/);
assert.match(rust, /Self::validate_for_load\(&content\)\.is_err\(\)/, 'v1 JSON은 목록에서 복구 대상으로 인식해야 합니다.');
assert.match(e2e, /ToramSettingsRepository/);
assert.match(e2e, /schemaVersion:2/);
assert.doesNotMatch(e2e, /toram-auto-building\.build-state/);
console.log('R6 storage contract boundary verification: PASS');
