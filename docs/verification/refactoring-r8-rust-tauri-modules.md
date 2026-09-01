# R8 Rust / Tauri 모듈화 검증

## 범위

R8은 Tauri 백엔드의 책임 경계를 분리한다. 계산식, 저장 문서 계약, IPC 명령 이름과 DTO, D4 탐색·상한·결과 의미는 바꾸지 않는다.

## 모듈 경계

| 모듈 | 책임 |
| --- | --- |
| `src-tauri/src/main.rs` | Tauri Builder 조립, managed D4 state 등록, command 등록 |
| `src-tauri/src/tauri_commands.rs` | IPC 요청/응답 전달만 수행하는 command 입구 |
| `src-tauri/src/d4_service.rs` | D4 병렬 slice, progress channel, job cancel 및 continuation session 수명 |
| `src-tauri/src/settings_service.rs` | 저장 유스케이스의 얇은 service 경계 |
| `src-tauri/src/settings_repository.rs` | saved-build 문서 검증, 저장 경로와 파일 CRUD |

## 보존 계약

- 기존 Tauri 명령 이름과 직렬화 DTO를 유지한다.
- D4 장시간 실행은 기존과 같이 `spawn_blocking`에서 실행한다. `D4OptimizationService` 하나가 managed state로 등록되며, cancel·pause·resume·dispose와 최대 4개의 continuation session/oldest eviction 수명은 변경하지 않는다.
- `exact`/`bounded`, 후보·상한·Pair 정책, 결과 순서 및 tie-break는 R8 범위 밖이다.
- 저장은 R6의 `toram-auto-build-document` / `schemaVersion: 1` saved-build 문서만 허용한다. 베타 legacy 저장 데이터를 읽거나 migration하지 않는다.

## 검증 결과

2026-09-01 기준 다음을 실행했다.

- `npm run verify:r8`: R2~R8 정적 경계와 기존 R0~R7 검증 통과
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`: 통과
- `cargo test --manifest-path src-tauri/Cargo.toml`: 72개 통과
- `cargo clippy --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: 통과
- `node tools/test-d4-native-client.mjs`, `node tools/test-d4-native-runtime-n0.mjs`, `node tools/test-d4-native-resume-ui-n5.mjs`: 통과
- `node tools/test-tauri-native-storage-e2e.mjs`: `TORAM_E2E_CDP`가 없어 안전하게 skip. 실제 WebView2 저장 E2E 통과를 주장하지 않는다.
