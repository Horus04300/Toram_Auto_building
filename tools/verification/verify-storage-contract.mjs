import assert from 'node:assert/strict';
import { access, readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { CLASSIC_SCRIPT_PATHS } from '../../web/src/classic-script-manifest.mjs';

const root = resolve(import.meta.dirname, '../..');
const read = path => readFile(resolve(root, path), 'utf8');
const repository = await read('web/src/storage/settings-repository.js');
const application = await read('web/src/application/application-use-cases.js');
const buildState = await read('web/src/storage/build-state-snapshot.js');
const buffs = await read('web/src/ui/active-buff-ui.js');
const combo = await read('web/src/ui/combo-ui.js');
const skills = await read('web/src/ui/skill-tree.js');
const rust = await read('desktop/src/settings.rs');
const e2e = await read('tools/tests/application/test-tauri-native-storage-e2e.mjs');

await assert.rejects(access(resolve(root, 'web/src/build-setting-snapshot.js')));
assert.ok(!CLASSIC_SCRIPT_PATHS.includes('assets/js/build-setting-snapshot.js'));
assert.ok(CLASSIC_SCRIPT_PATHS.includes('assets/js/storage/settings-repository.js'));
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
console.log('Settings storage contract boundary verification: PASS');
