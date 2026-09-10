# 0.6.5 릴리스와 실제 버전 상승 검증

## 릴리스 변경

- 권갑 STR→ATK, 선풍창·발도검 MATK 스탯 계수를 근거에 맞춰 JS/Rust에 동시 반영하고 Native 계산 캐시 버전을 v2로 변경했다.
- 빈 잠금 크리스타 슬롯을 유지하면서 추천을 적용한다.
- 빠른 추천 실패를 불가능 증명과 구분하고, 실패·취소 시 이전 추천 상세를 비운다.
- 크리스타 잠금/해제 아이콘을 상태에 맞춰 표시한다.
- package/Cargo/Tauri 및 두 lockfile 버전을 0.6.5로 통일했다.

## 2026-09-10 공개 전 검증

- `npm run verify:r9`: PASS.
- `npm run test:r0`: 69개 프로세스 종료 성공. 68개 통과, 실제 native 저장 E2E 1개는 `TORAM_E2E_CDP` 미설정으로 SKIP.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`: PASS.
- `cargo test --locked --manifest-path src-tauri/Cargo.toml`: 79개 통과.
- `cargo clippy --locked --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: PASS.
- `node tools/audit-stack-source-links.mjs --require-s1`: S1 427/427 통과.
- `npm run desktop:prepare`, `node tools/release-version.mjs`: PASS.
- `node tools/verify-update-browser.mjs`: 실제 Edge 화면 PASS, native 설치는 mock.
- `npm run ai:audit`: PASS.

로그는 `src-tauri/target/release-r0-0.6.5.log`, `release-rust-0.6.5.log`에 보관한다.

추가 검증: `node tools/audit-browser-e2e.mjs` 실제 Edge 15개 통과. `node tools/audit-weapon-stat-recommendations.mjs --single-slot`은 110개 exact/oracle/재계산·상한 검사와 JS/Rust 10,010건 비교를 통과했다. 외부 계수 및 Native 불일치는 0이다.

## 공개 결과

- 릴리스 커밋: `217b46ddb70b6f926ff4f164ded3b4da3624c43a`, 태그 `v0.6.5`. main과 태그를 atomic push했다.
- [Windows release 실행 34484676855](https://github.com/Horus04300/Toram_Auto_building/actions/runs/34484676855): G1~G6 및 전체 작업 성공.
- [v0.6.5](https://github.com/Horus04300/Toram_Auto_building/releases/tag/v0.6.5)는 2026-09-10 23:01:57 KST에 일반 Latest로 공개됐다. draft/prerelease 모두 false.
- 공개 자산: `latest.json` 847 bytes, `ToramOnlineAutoBuildCalculator_0.6.5_x64-setup.exe` 10,281,907 bytes, `.sig` 452 bytes.
- 공개 Latest manifest는 version `0.6.5`, platform `windows-x86_64`이며 해당 태그의 설치 파일을 가리킨다. 공개 파일을 다시 다운로드하여 `verify_updater_artifact.exe`로 앱 공개키 서명 검증 PASS.

## 실제 업데이트 Gate

**실제 0.6.4→0.6.5 설치 업데이트 PASS.** 2026-09-10 23:02:31~23:02:36 KST에 `tools/audit-release-upgrade.mjs upgrade`를 실행했다. updater IPC·다운로드·서명·설치·재시작을 mock하거나 대체하지 않았다.

| 단계 | 관찰 결과 |
| --- | --- |
| 출발 설치본 | 공개 0.6.4 NSIS의 서명을 확인해 격리 폴더에 설치. Tauri API 버전 0.6.4 |
| 자동 확인 | 새 프로세스 시작 시 0.6.5 알림과 현재 버전 0.6.4 표시 |
| 동의 취소 | 설치 동의를 취소한 뒤 0.6.4 프로세스와 세팅 유지 |
| 재승인·실제 다운로드 | 다운로드 및 검증 중 표시와 40% 진행을 관찰한 뒤 설치 프로그램 시작 표시 |
| 설치·자동 재시작 | 기존 앱 종료 후 NSIS가 직접 새 앱 실행. 감사 도구는 설치 이후 앱 실행 명령을 호출하지 않음 |
| 도착 버전 | Tauri API, 화면 제목, 설치된 EXE ProductVersion 모두 0.6.5 |
| 자동 복원 | Build/Scenario 전체가 설치 직전 snapshot과 동일. 레벨 321, 보스 DEF 123, 빈 잠금 슬롯 유지 |
| 업데이트 설정 | 설치 전 false로 바꾼 checkOnStartup 및 실제 체크박스 상태 유지 |
| 이름 있는 빌드 | 설치 전후 `UpgradePreservation.json` SHA-256 동일 |
| 재확인 | 0.6.5에서 수동 업데이트 확인 시 `최신 버전입니다.` 표시 |
| 설치 후 저장 E2E | `TORAM_E2E_CDP=http://127.0.0.1:9226`으로 `node tools/test-tauri-native-storage-e2e.mjs` 실행. 실제 native 저장·중복 방지·덮어쓰기·불러오기·삭제 통과, SKIP 없음 |
| 제거·정리 | 격리 NSIS 제거 후 시험 빌드 파일 보존. 원래 앱 등록 정보 복원 및 기존 사용자 설치 EXE·세팅 파일 해시 보존 확인 |

설치된 EXE SHA-256:

- 0.6.4: `ccb23d67d8bd0cb8d319c2d32799146f33c56c7c14cb6d9b6cf4c503656a1836`
- 0.6.5: `70fd6b7de7fb5365babf42d92a76ac97503d53c8eb8e043a60c9eb10632dc32f`
- 보존한 빌드: `a4794b2cc7159b8d999eca9fa795c4f97cae86a05eb0558538ee3dbee860624e`

## 시험 환경과 증거

Windows x64의 실제 설치 앱과 WebView2를 사용했다. 격리 폴더는 `src-tauri/target/upgrade-0.6.4-to-0.6.5/`이며, 그 아래 공백 포함 제품명 폴더에 0.6.4를 `/S /NS /UPDATE /D=<격리 설치 경로>`로 설치했다. 기존 제품 레지스트리는 먼저 백업했다. NSIS의 기존 설치 경로 탐색이 격리 설치 위치를 사용하도록 실제 설치 프로그램이 등록한 상태에서 업데이트했다.

`LOCALAPPDATA=<격리 루트>/local`, `WEBVIEW2_USER_DATA_FOLDER=<격리 루트>/webview`, 로컬 CDP 9226을 사용했다. named build 경로가 정확히 `<격리 루트>/local/ToramOnlineAutoBuildCalculator`인지 앱 native IPC로 검사했다. 실제 사용자 앱과 프로필에 시험 입력을 넣지 않았다.

`CODEX_PLAYWRIGHT_PATH`는 설치된 Playwright 경로로 지정한다. `node tools/audit-release-upgrade.mjs prepare`가 출발 버전 데이터를 준비하고, `upgrade`가 실제 공개 버전 상승을 검증한다. 이미 설치·저장한 시험 디렉터리를 재사용하거나 다른 앱의 CDP에 연결하지 않도록 실행 전 격리 상태를 확인한다.

로컬 증거는 격리 루트의 `prepare-report.json`, `upgrade-report.json`, `before.json`, `expected-after.json`, `after.json`, `native-storage-0.6.5.log`, `cleanup-report.json`, `0.6.4-update-available.png`, `0.6.5-updated.png`에 있다. 전체 CI 대기는 `src-tauri/target/release-ci-0.6.5.log`에 기록했다.

이번 실제 설치 Gate는 이 Windows 환경의 정상 공개 업데이트·동의 취소·데이터 보존 경로를 검증한다. 네트워크/저장/변조 실패 회귀는 앞선 자동 업데이트 감사와 구분하며, 모든 OS 오류의 복구나 rollback을 보장하지 않는다.
