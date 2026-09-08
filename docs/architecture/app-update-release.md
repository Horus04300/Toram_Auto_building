# Windows 업데이트 운영 계약

현재 구현·검증·공개 여부는 `docs/handoff/current-development-handoff.md`가 기준이다.

## 실행 경계

- `src-tauri/src/update_service.rs`: Latest 확인, 버전 고정, 중복 요청 배제, 다운로드·서명 검증, 설치. `src-tauri/src/tauri_commands.rs`는 IPC만 제공한다.
- `frontend/application/ports.ts`의 UpdateService → `frontend/runtime/tauri-update-adapter.ts` → native IPC. JS 출력은 `tsconfig.updater.json`으로 생성한다.
- `assets/js/update-controller.js`는 일시적 상태, `assets/js/update-ui-controller.js`는 알림·동의, `assets/js/update-install-coordinator.js`는 계산 종료·저장 조정이다.
- 시작 확인은 복원/UI 초기화 이후 비동기 실행한다. 업데이트 없음·확인 실패는 자동 알림을 띄우지 않는다. 수동 확인에는 결과/오류를 표시한다.
- 다운로드는 사용자 승인 후에만 한다. 설치 직전 새 계산/continuation이 있으면 다시 동의를 받는다. 승인된 계산은 기존 cancel/dispose 경계에서 종료를 확인한다. 대기 중인 UI 작업도 무효화한다.
- 다운로드 동안 편집 가능하다. 최종 설치 구간만 UI를 잠그고 SettingsRepository로 최신 Build/Scenario를 다시 저장한다. 저장·종료 실패 시 설치하지 않는다.
- 저장 추가값은 기존 schema v2 application-state의 `appSettings.update.checkOnStartup`뿐이다. 누락 시 true. 업데이트/D4 진행 상태를 Build/Scenario에 저장하지 않는다.
- plugin의 `download`가 서명 검증된 바이트를 반환한 뒤 별도 `install`을 호출한다. Windows에서는 plugin이 NSIS를 실행하고 앱을 종료한다. NSIS가 재시작을 담당하므로 별도 중복 relaunch를 하지 않는다.
- 서명 실패는 설치 금지다. 설치 프로그램 실행 이후 발생하는 OS/설치 오류를 앱이 모두 관찰하거나 자동 복구한다고 보장하지 않는다. rollback은 범위 밖이다.

## 키와 배포

- 공개키만 Tauri 설정에 포함한다. 비밀키는 저장소 밖에서 보관하고 Actions의 `TAURI_SIGNING_PRIVATE_KEY` Secret으로 등록한다. 암호화한 키를 쓰면 `TAURI_SIGNING_PRIVATE_KEY_PASSWORD`도 필요하다. 키 내용을 문서/로그/릴리스 자산에 넣지 않는다.
- 이번에 생성한 키의 로컬 보관 위치는 `%LOCALAPPDATA%\ToramUpdaterSigning\updater.key`다. 같은 폴더 `.pub`는 공개키다. 키를 분실하면 후속 업데이트를 서명할 수 없으므로 안전하게 백업한다. 새 키로 기존 키를 자동 덮어쓰지 않는다.
- updater 서명은 Windows Authenticode와 다르다. SmartScreen 신뢰나 Windows 코드서명을 제공하지 않는다.
- 설치 위치·앱 식별자·사용자 세팅 위치를 바꾸지 않는다. named build는 `%LOCALAPPDATA%\ToramOnlineAutoBuildCalculator`, WebView 자동 복원은 기존 application-state 경로를 유지한다.
- updater 미포함 설치본은 첫 지원 버전을 수동 설치해야 한다. 그 이후부터 앱 내 업데이트가 가능하다. 첫 `latest.json` 공개 전에는 확인 요청의 404가 오류 처리될 수 있다.

## 릴리스 절차

1. package/Cargo/Tauri 및 두 lockfile 버전을 다음 일반 공개 버전으로 맞춘다. `node tools/release-version.mjs`로 확인한다. prerelease 채널을 만들지 않는다.
2. 검토한 main 커밋에 같은 `vX.Y.Z` 태그를 만든다. `.github/workflows/release.yml`은 태그 push 또는 기존 태그를 지정한 수동 실행을 지원한다. 워크플로 작성 자체는 태그/공개 승인이 아니다.
3. workflow는 R9·R0, Rust fmt/test/clippy, x64 NSIS 서명 빌드, 실제 설치 파일의 공개키 검증을 거친다. R0의 desktop storage SKIP은 실제 업그레이드 통과가 아니다.
4. `tools/prepare-update-release.mjs`가 파일명을 공백 없는 ASCII 이름으로 정규화하고 `.sig`, `latest.json`을 `release-assets/`에 준비한다. private key는 포함하지 않는다. 실제 서명은 `src-tauri/src/bin/verify_updater_artifact.rs`로 검사한다.
5. 비공개 draft에 자산을 업로드하고 원격 파일명·크기를 확인한 뒤 일반 Latest로 공개한다. 이미 공개한 릴리스는 덮어쓰지 않는다. 실패한 draft는 문제를 수정한 후 같은 태그로 재실행 가능하다.
6. Endpoint는 `https://github.com/Horus04300/Toram_Auto_building/releases/latest/download/latest.json`, platform은 `windows-x86_64`다. 설치 파일과 updater artifact는 동일 NSIS 파일이며 서명은 파일 내용으로 manifest에 넣는다.

## 검증과 실제 업그레이드 Gate

- 기본: `npm run verify:r9`, `npm run test:r0`, Rust fmt/test/clippy, `npm run desktop:build`, `node tools/prepare-update-release.mjs`.
- 화면: Playwright 모듈 경로를 `CODEX_PLAYWRIGHT_PATH`로 지정하고 `npm run desktop:prepare` 다음 `node tools/verify-update-browser.mjs`. Edge 화면에서 동의/진행/저장을 검증하지만 native 설치는 mock이므로 upgrade E2E가 아니다.
- 실제 Gate: updater 포함 vN 설치 → vN+1 일반 Release 공개 → vN에서 감지·승인·서명 검증·설치·재시작 → vN+1 표시 확인. named build JSON의 전후 내용과 자동 복원 Build/Scenario·checkOnStartup 보존도 확인한다.
- 동의 거부, 네트워크 실패, 변조 서명 거부, 저장 실패, 실행/일시정지 계산, 다운로드 중 새 입력도 확인한다. 실제 Gate가 끝나기 전 전체 자동 업데이트 완료로 판정하지 않는다.

공식 근거: [Tauri v2 Updater](https://v2.tauri.app/plugin/updater/). 구현 API는 Cargo.lock의 plugin 2.11.0 소스와 함께 확인했다.
