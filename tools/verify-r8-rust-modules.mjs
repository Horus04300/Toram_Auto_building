import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const read = path => readFile(resolve(root, path), 'utf8');
const main = await read('src-tauri/src/main.rs');
const commands = await read('src-tauri/src/tauri_commands.rs');
const d4Service = await read('src-tauri/src/d4_service.rs');
const settingsService = await read('src-tauri/src/settings_service.rs');
const repository = await read('src-tauri/src/settings_repository.rs');

for (const module of ['d4_service', 'settings_repository', 'settings_service', 'tauri_commands']) {
  assert.match(main, new RegExp(`mod ${module};`, 'u'), `${module} 모듈을 main에서 조립해야 합니다.`);
}
assert.match(main, /\.manage\(D4OptimizationService::default\(\)\)/u, 'managed D4 state는 기존처럼 앱 조립 시 한 번만 생성해야 합니다.');
assert.doesNotMatch(main, /std::fs|spawn_blocking|NativeSearchSession|#\[tauri::command\]/u, 'main.rs는 파일·D4 실행·IPC 구현을 소유하면 안 됩니다.');
for (const name of ['settings_directory', 'd4_hardware_profile', 'd4_optimize_parallel', 'resume_d4_optimization', 'dispose_d4_optimization', 'cancel_d4_optimization', 'pause_d4_optimization', 'list_settings', 'save_setting', 'load_setting', 'overwrite_setting', 'delete_setting']) {
  assert.match(commands, new RegExp(`#\\[tauri::command\\][\\s\\S]*?fn ${name}\\b`, 'u'), `${name} IPC command를 유지해야 합니다.`);
}
assert.match(commands, /service\.optimize\(/u, 'D4 command는 service에 위임해야 합니다.');
assert.match(commands, /SettingsService::save/u, '저장 command는 SettingsService에 위임해야 합니다.');
assert.match(d4Service, /spawn_blocking[\s\S]*NativeSearchSession::new/u, '새 D4 실행은 기존 blocking runtime 경계 안에서 준비·실행해야 합니다.');
assert.match(d4Service, /run_parallel_slice_with_control/u, 'D4 취소·일시정지 협력 실행 방식을 유지해야 합니다.');
assert.match(d4Service, /MAX_RESUMABLE_SESSIONS: usize = 4/u, 'continuation 수명 한도를 변경하면 안 됩니다.');
assert.match(d4Service, /pub async fn resume/u, '기존 재개 명령은 service에서 유지해야 합니다.');
assert.match(settingsService, /SettingsRepository::/u, 'SettingsService는 파일 구현을 Repository에 위임해야 합니다.');
assert.match(repository, /SETTING_SCHEMA_VERSION: u64 = 1/u, 'R6 저장 schemaVersion을 유지해야 합니다.');
assert.match(repository, /documentType.*saved-build/u, 'legacy JSON 대신 saved-build 계약만 허용해야 합니다.');

console.log('R8 Rust/Tauri module boundary verification: PASS (assembly, commands, services, repository, D4 lifetime)');
