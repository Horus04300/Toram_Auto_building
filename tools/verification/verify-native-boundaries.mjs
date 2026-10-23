import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '../..');
const read = path => readFile(resolve(root, path), 'utf8');
const main = await read('desktop/src/main.rs');
const commands = await read('desktop/src/tauri_commands.rs');
const optimizationService = await read('desktop/src/optimization/service.rs');
const settingsService = await read('desktop/src/settings.rs');
const repository = await read('desktop/src/settings.rs');
const core = await read('engine/src/lib.rs');
assert.match(main, /use toram_optimization_core::crysta_native_solver/u, '앱은 공용 Rust crate를 사용해야 합니다.');
assert.match(core, /path = "solver\.rs"/u, 'WASM과 앱은 같은 solver 원본을 사용해야 합니다.');
assert.match(core, /path = "evaluator\.rs"/u, 'WASM과 앱은 같은 evaluator 원본을 사용해야 합니다.');

for (const module of ['crysta_service', 'settings', 'tauri_commands']) {
  assert.match(main, new RegExp(`mod ${module};`, 'u'), `${module} 모듈을 main에서 조립해야 합니다.`);
}
assert.match(main, /\.manage\(CrystaOptimizationService::default\(\)\)/u, 'managed CrystaOptimization state는 기존처럼 앱 조립 시 한 번만 생성해야 합니다.');
assert.doesNotMatch(main, /std::fs|spawn_blocking|NativeSearchSession|#\[tauri::command\]/u, 'main.rs는 파일·CrystaOptimization 실행·IPC 구현을 소유하면 안 됩니다.');
for (const name of ['settings_directory', 'crysta_hardware_profile', 'crysta_optimize_parallel', 'resume_crysta_optimization', 'dispose_crysta_optimization', 'cancel_crysta_optimization', 'pause_crysta_optimization', 'list_settings', 'save_setting', 'load_setting', 'overwrite_setting', 'delete_setting']) {
  assert.match(commands, new RegExp(`#\\[tauri::command\\][\\s\\S]*?fn ${name}\\b`, 'u'), `${name} IPC command를 유지해야 합니다.`);
}
assert.match(commands, /service\.optimize\(/u, 'CrystaOptimization command는 service에 위임해야 합니다.');
assert.match(commands, /SettingsService::save/u, '저장 command는 SettingsService에 위임해야 합니다.');
assert.match(optimizationService, /spawn_blocking[\s\S]*NativeSearchSession::new/u, '새 CrystaOptimization 실행은 기존 blocking runtime 경계 안에서 준비·실행해야 합니다.');
assert.match(optimizationService, /advance_parallel_slice_with_control\([\s\S]*?Some\(&control.cancel\),\s*Some\(deadline\)/u, 'CrystaOptimization 실행에 취소 신호와 deadline을 전달해야 합니다.');
assert.match(optimizationService, /if last_progress.elapsed\(\) >= interval \|\| session.is_complete\(\) \{\s*let result = session.snapshot\(\);/u, '진행 알림이나 완료 시점에만 중간 결과를 생성해야 합니다.');
assert.match(optimizationService, /MAX_RESUMABLE_SESSIONS: usize = 4/u, 'continuation 수명 한도를 변경하면 안 됩니다.');
assert.match(optimizationService, /pub async fn resume/u, '기존 재개 명령은 service에서 유지해야 합니다.');
assert.match(settingsService, /SettingsRepository::/u, 'SettingsService는 파일 구현을 Repository에 위임해야 합니다.');
assert.match(repository, /pub const SETTING_SCHEMA_VERSION: u64 = 2/u, '현재 저장 schemaVersion 2를 유지해야 합니다.');
assert.match(repository, /const LEGACY_SETTING_SCHEMA_VERSION: u64 = 1/u, '기존 v1 문서 읽기 호환성을 유지해야 합니다.');
assert.match(repository, /documentType.*saved-build/u, 'legacy JSON 대신 saved-build 계약만 허용해야 합니다.');

console.log('Native boundary Rust/Tauri module boundary verification: PASS (assembly, commands, services, repository, CrystaOptimization lifetime)');
