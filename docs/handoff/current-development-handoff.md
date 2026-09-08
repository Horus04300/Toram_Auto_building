# 현재 개발 상태 및 AI 인수인계

- 갱신: 2026-09-08 — 업데이트 알림·설치 및 서명 배포 코드를 0.6.4 일반 릴리스 절차에 포함.
- 제품: 토람 온라인 대미지 계산기 및 빌드 시뮬레이터, Tauri v2 Windows 앱.
- 현재 상태 판단은 이 문서, 실제 코드, 이번에 실행한 테스트를 함께 사용한다.
- 작업 시작 시 `git status --short`로 기존 변경을 확인·보존한다. 과거 테스트 결과를 이번 실행 결과로 보고하지 않는다.

## 1. 현재 기능과 유지할 계약

- 웹 진입점은 `assets/js/app-entry.mjs`, classic script 순서는 `assets/js/legacy-script-manifest.mjs`다. 기존 전역·Worker 로딩 계약을 보존한다.
- `BuildDraft`가 영속 계산 입력의 단일 출처다. 보스/요구조건은 `ScenarioContext`, 선택 타격/일회성 값은 `CalculationRequest`이며 UI·최적화 runtime 상태와 분리한다.
- 계산 조립은 `assets/js/application-use-cases.js`, 공통 정책은 `assets/js/calculation-policies.js`를 거친다. 계산식·StatRegistry·크리스타 조건 처리의 별도 fallback을 다시 만들지 않는다.
- UI 기능은 build/skills/buffs/combo/optimizer/settings로 분리했다. 전체 기능 지도는 `docs/architecture/current-webapp-feature-map.md`, 최근 감사와 A-01~A-04 처리는 `docs/verification/current-webapp-feature-audit.md`다.
- 결과 탭은 raw 후보의 Greedy/좌표 개선 초기해를 `heuristic`·최적성 미검사로 표시한다. 자동 결과 표시에서 Pareto 준비·branch-and-bound를 실행하지 않는다. 사용자가 정밀 계산 시작을 누르면 Rust 우선/Worker fallback으로 탐색한다.
- Native 정밀 계산은 30초 slice의 continuation을 자동 연결한다. 일시정지·재개를 지원하고, 대기 시간을 실행 시간에 넣지 않는다. 입력 변경 시 이전 추천·continuation을 폐기한다. `exact`, `bounded`, `heuristic`, `cancelled`, `invalid`의 의미를 섞지 않는다.
- 최적화 취소는 빌드 UI의 계산 입력 분류와 확정 변경 이벤트를 사용한다. 세팅/백업 이름·파일 선택·검색어·미적용 요구조건 편집은 결과/continuation을 유지한다. 화면 재렌더의 중복 알림은 Build/Scenario/Request 서명이 같으면 무시한다. 장비·스탯 입력과 실제 스킬/버프/콤보/요구조건 변경, 저장 빌드 복원은 이전 계산을 무효화한다.
- 추천 적용은 잠기지 않은 크리스타 값만 바꾸며 잠금 상태와 잠긴 값은 보존한다. 후보/상한/동점 변경에는 D4 정확성 Gate가 필요하다. 모든 입력의 10초 exact 달성을 주장하지 않는다.
- 정밀 Worker의 dynamic seed+ordering은 기본 연결, Replacement Proof 축소는 감사 전용이다. 데스크톱은 Rust CPU 우선이며 JavaScript 병렬 pool과 GPU는 기본 제품 경로로 승격하지 않았다.
- 콤보의 근거리/원거리 override는 상호 배타적이며 둘 다 해제하면 스킬 기본 판정이다. 트리 탐색·증감 단위·resize는 투자 변경 이벤트를 내지 않는다.
- 결과 요구조건 모달은 MAXHP/MAXMP/듀얼 적용 전 AMPR/평타 CRIT/ASPD 제한을 설정한다. 거리·요구조건 override와 추천 제외 크리스타는 schema v2의 `ScenarioContext.optimizationPreferences`에 저장한다. `null`은 제한 해제, 누락 키는 동적 기본값이다.

## 2. 저장 및 배포

- 소스 패키지 버전은 0.6.4다. 기존 v0.6.3 일반 Latest의 공개 태그 Cargo 버전은 0.6.2여서 태그와 소스가 불일치한다. 새 배포는 package/Cargo/Tauri/두 lockfile/태그의 0.6.4 일치를 검사하고, `release.yml`이 draft 자산 검증 후 Latest로 공개한다.
- 업데이트: Tauri updater 2.11.0, GitHub Latest 단일 endpoint, 자동 확인 기본 true, 동의 후 다운로드·서명 검증·설치. 별도 UpdateService Port/adapter/controller와 Rust service를 사용한다. 저장 추가값은 schema v2 `appSettings.update.checkOnStartup`뿐이다.
- 설치 전 실행·일시정지·대기 계산을 확인하고 승인 시 cancel/dispose한다. 다운로드 중 새 계산은 다시 동의를 받고 최신 입력을 재저장한다. 종료/저장 실패 시 설치를 차단한다. 진입점/운영 계약은 `docs/architecture/app-update-release.md`다.
- 0.6.4 서명 NSIS·`.sig`·`latest.json`을 로컬 생성·검증했다. 키는 저장소 밖에 생성했지만 GitHub Secret 업로드는 자동 승인 검토가 명시 승인/소유 확인 부족으로 거절하여 미등록이다. workflow 실행·공개·vN→vN+1 설치 E2E는 미실행이며 전체 업데이트 완료로 판정하지 않는다. updater 없는 공개본은 첫 지원 버전을 수동 설치해야 한다.
- 앱 식별자는 `com.toramonline.autobuildcalculator`, 제품명은 `Toram Online Auto Build Calculator`다.
- 설치 폴더는 LocalAppData 아래 공백 포함 제품명 폴더다. 사용자 세팅은 정확히 `%LOCALAPPDATA%\ToramOnlineAutoBuildCalculator`이며 `settings` 하위 폴더를 추가하지 않는다. 설치 제거와 사용자 데이터 삭제를 혼동하지 않는다.
- `SettingsRepository`가 `format: toram-auto-build-document`, `schemaVersion: 2`의 `saved-build`와 `application-state`를 관리한다. 이름 있는 빌드는 native JSON, 자동 복원은 단일 `toram.auto-build.application-state.v2` 문서다. UI/D4 runtime 상태는 저장하지 않는다.
- 오염된 v1 문서를 읽을 때는 버프 파생값이 섞인 `externalOptions`만 폐기하고 v2로 쓴다. 이는 폐기한 베타 localStorage 키/`toram-auto-build-setting` JSON을 다시 지원한다는 뜻이 아니다. File System Access API·IndexedDB 저장 경로도 복원하지 않는다.
- 활성 버프의 효과는 계산 엔진이 on/off·스택에서 직접 해석한다. 외부 옵션 행으로 복제해 중복 합산하지 않는다.
- 프런트 저장 어댑터의 수정 원본은 `frontend/runtime/tauri-build-storage-adapter.ts`다. `types:emit`이 JS를 생성한다. Rust IPC/저장 구현은 `src-tauri/src/tauri_commands.rs`, `src-tauri/src/settings_repository.rs`를 확인한다.
- NSIS는 currentUser/WebView2 downloadBootstrapper를 사용한다. v0.6.2 공개 설치 파일은 코드 서명이 없다. 배포 작업에서는 해당 릴리스 자산과 새 빌드 결과를 직접 확인한다.

## 3. 출처와 보류 범위

- S1은 원문 출처 연결, S2~S5는 조건·수식·엔진·회귀 검증이다. 전투 상태 시뮬레이션은 별도 완료 기준이다. 기존 S1 기록은 427/427이며 전체 계산 완성을 의미하지 않는다.
- 스킬 수치·상한을 추정하지 않는다. `docs/skill-tree-verification-standard.md`에 따라 원문과 코드·테스트 연결을 확인한다. 스킬 등록 재생성 원본은 `assets/source-data/skill-registration/`다.
- 피격 시뮬레이션, 피격/저항 시간 의존 효과, 콤보 포인트·레벨 및 보류된 고급 태그는 임의로 구현하지 않는다. 다음 스킬 한정 효과·사용 후 소멸·MP 흐름·직접 피해와 버프가 우선이다.
- 미구현 판단/후속 구현 전에는 `docs/verification/unimplemented.md`를 읽고 실제 코드로 재판정한다. 사용자 선택 없이 보류 항목을 확대하지 않는다.
- 자동 장비 옵션 부여/잠재력 탐색은 검증된 카탈로그와 별도 승인 범위다. 현재 완성된 수동 장비 옵션 입력을 유지한다. 관련 계약은 `docs/architecture/equipment-option-assignment-spec.md`다.

## 4. 작업별 필독과 검증

- D4 정확성·성능·후보 탐색: `docs/architecture/d4-exact-optimization-plan.md` 전체를 먼저 읽는다. 병렬화는 `docs/architecture/d4-parallel-exact-optimization-plan.md`, 실행 제어는 `docs/architecture/d4-native-runtime-correction-plan.md`의 관련 계약을 추가 확인한다.
- UI·저장·계산의 파일별 진입점과 유지할 구현 경계는 `docs/ai-context-guide.md`에서 해당 항목만 찾는다. 회귀 fixture의 근거와 분류는 `docs/verification/refactoring-r0-baseline.md`를 따른다.
- 계산/스킬 변경: `node tools/audit-stack-source-links.mjs --require-s1`과 영향받는 트리·계산·콤보 회귀. D4 변경은 해당 oracle/property/parity/성능 Gate를 추가한다.
- 저장 변경: snapshot/adapter/Repository 테스트와 Rust 단위 테스트. 실제 데스크톱 저장 E2E는 `TORAM_E2E_CDP`가 필요하고 SKIP은 통과가 아니다.
- 구조 변경: 필요한 최상위 `verify:r*` 명령과 `npm run test:r0`. `verify:r9`가 하위 r8→…→r2를 포함하므로 각 단계를 중복 실행하지 않는다.
- Rust 변경: `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo test --manifest-path src-tauri/Cargo.toml`, 필요한 clippy/빌드. 배포 변경은 NSIS 설치·실행·제거와 사용자 데이터 보존을 검증한다.
- 문서/검색 설정만 변경: `npm run ai:audit`, `git diff --check`. 모든 작업에서 실행 명령·결과·SKIP/미실행을 구분해 보고한다.

## 5. 검증 기록과 문서 유지

- 2026-09-07 업데이트: R9, R0 69개 프로세스 종료 성공(native 저장 E2E SKIP 포함), Rust 75개·fmt·clippy, updater 단위/동의/재저장 회귀, 실제 Edge 화면 검증(native install mock), 0.6.4 서명 빌드·공개키 검증·변조 파일 거부, actionlint 통과. 실제 업그레이드·설치 후 사용자 데이터 보존 검증과 구분한다.

- 2026-09-06 입력 무효화 수정: `npm run verify:r9`, Native N5 UI 이벤트/재개·Native client·저장 snapshot·Browser Worker 회귀, S1 427/427, `npm run ai:audit`, `git diff --check` 통과. 세팅 이름 입력의 취소 문제를 수정 전 실패/수정 후 통과로 재현했다. 실제 데스크톱 화면 E2E·Rust 전체·성능 계측은 이번 UI 수정에서 실행하지 않았다.
- 이전 세션 기록(2026-09-04): `npm run verify:r9`, R0 67개 프로세스 종료 성공, `node tools/test-d-sector.mjs`, `node tools/test-d4-global-optimizer-stage2.mjs`, `npm run desktop:prepare`, Rust 72개 테스트 통과. R0 성공 집계에는 데스크톱 저장 E2E의 `TORAM_E2E_CDP` 미설정 SKIP이 포함되므로 67개 모두 실제 실행 통과로 해석하지 않는다.
- 2026-09-05 문서 상태 정리 검증: Native client·N5 UI 연결·Blade S4/S5 모델 범위·콤보 태그 회귀가 통과했다. 앞선 구조 감사의 `npm run verify:r9`도 통과했다. 실제 화면 E2E·Rust 전체·성능 P95는 이 문서 정리에서 재실행하지 않았다.
- 2026-09-05 AI 컨텍스트 정리: `.aiignore`를 `ai:files`/`ai:search` 명령에 명시 연결하고 현재 handoff를 축약했다. 원문·계산·회귀 fixture는 검색에 남겼다. 후속 사용자 요청으로 오래된 AI 전달문·전체 이력 복사본·R1~R9 단계 보고서 12개를 삭제하고 유효한 경계는 현재 안내에 통합했다. 앱 동작과 테스트 코드는 변경하지 않았다. 문서 검증은 `npm run ai:audit`와 `git diff --check`로 재현한다.
- 실패한 D4 실험의 재시도를 피할 근거는 `docs/handoff/d4-gate0-to-gatee-worklog.md`에 남아 있다. 해당 실험을 재검토할 때만 읽는다.
- 현재 handoff는 12 KiB 이하로 유지한다. 중요한 계산·저장·릴리스 변경은 이 문서의 해당 현재 항목을 갱신하고, 긴 경과·계측 로그는 주제 문서에 둔다.
- D4 정확성 문서는 불변 계약·Gate, Native 문서는 현재 실행 경계, unimplemented는 남은 결정·보류 범위를 담당한다. 초기 설계/실험 기록은 해당 가설을 재검토할 때만 읽고 현재 상태 판단에 재사용하지 않는다.
