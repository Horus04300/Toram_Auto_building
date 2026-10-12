# 현재 개발 상태 및 AI 인수인계

- 갱신: 2026-10-12 — v0.7.3 공개 완료, 로컬 Native v21 후보 공급 좌표 구현.
- 제품: 토람 온라인 대미지 계산기 및 빌드 시뮬레이터, Tauri v2 Windows 앱.
- 현재 상태는 이 문서·코드·이번 검증으로 판정한다. 작업 시작 시 `git status --short`로 기존 변경을 확인·보존한다.

## 1. 구조와 입력 계약

- 웹 진입점은 `assets/js/app-entry.mjs`, 순차 classic 로딩은 `assets/js/classic-script-manifest.mjs`, 기능 등록·이벤트 초기화는 마지막의 `assets/js/ui-bootstrap.js`다. Worker 상대 import 경로는 별도 계약이다.
- 크리스타 최적화 JS는 `assets/js/optimization/`, Rust는 `src-tauri/src/optimization/`에 있다. 평가·컴파일·탐색·전송·실행 제어의 책임을 유지한다. Rust main과 개발용 bin은 같은 역할별 파일을 경로 모듈로 사용한다.
- `src-tauri/src/settings.rs`에 SettingsService/SettingsRepository를 통합했다. IPC·서비스 API·검증/파일 접근의 논리적 경계는 유지한다.
- 스킬 데이터는 트리별 29개 파일이다. 보강 정의를 합쳤지만 중복 ID를 삭제하거나 계산식을 바꾸지 않았다. 등록기의 명시적 우선순위로 전체 정의 순서를 보존한다. 기본 계산·콤보는 첫 유효 정의, `preferStackControl`은 스택 보강 정의를 선택한다. 기준: `tools/fixtures/skill-definition-precedence.json`.
- `BuildDraft`는 영속 계산 입력의 단일 출처다. 보스/요구조건은 `ScenarioContext`, 선택 타격/일회성 값은 `CalculationRequest`다. runtime/UI 상태를 저장하지 않는다.
- 계산 조립은 `assets/js/application-use-cases.js`, 공통 정책은 `assets/js/calculation-policies.js`를 거친다. StatRegistry·계산식·크리스타 조건의 별도 fallback을 만들지 않는다.
- 저장 스냅샷은 `assets/js/build-state-snapshot.js`, 저장 UI는 `assets/js/settings-ui.js`, 결과 표시는 `assets/js/optimization-results.js`다. 기능 지도: `docs/architecture/current-webapp-feature-map.md`.
- 테스트는 `tools/tests/`의 application/skills/optimization, 감사는 `tools/verification/`, 계측은 `tools/benchmarks/`, 실행 지원은 `tools/support/`다. 정리 근거·호환 예외·검증: `docs/verification/role-based-refactoring.md`.

## 2. 계산·최적화 동작

- 결과 탭은 raw 후보의 Greedy/좌표 개선 초기해를 `heuristic`·최적성 미검사로 표시한다. 자동 표시에서 Pareto 준비·정밀 탐색을 실행하지 않는다. 명시적 정밀 시작은 Rust CPU 우선/Worker fallback이다.
- Native는 30초 slice continuation을 연결하고 pause/resume을 지원한다. 사용자 대기 시간을 실행 시간에 합산하지 않는다. `exact`, `bounded`, `heuristic`, `no-incumbent-yet`, `paused`, `cancelled`, `invalid`를 구분한다. 모든 입력의 10초 exact 달성을 주장하지 않는다.
- 잠금·금지·계보·유틸리티·동점 ID 계약을 유지한다. 후보/상한 변경에는 `docs/architecture/crysta-optimization-contract.md`의 oracle/property/parity/성능 Gate가 필요하다. 실행 계약: `docs/architecture/native-optimization-runtime.md`.
- 추천 적용은 잠기지 않은 크리스타만 바꾸고 빈 잠금도 보존한다. 계산 입력 변경 시 이전 추천·continuation을 폐기한다. 세팅/백업 이름·검색·파일 선택·미적용 요구조건 편집·동일 서명의 중복 화면 알림은 결과를 무효화하지 않는다.
- 실행 adapter는 Native/Worker 선택과 제어만 담당한다. 오래된 요청의 fallback을 금지한다. 일반 Worker에 Native 재개를 가장하는 continuation을 만들지 않는다. Native 세션은 최대 4개, oldest eviction이다.
- Worker dynamic seed+ordering은 기본 경로, Replacement Proof 축소는 감사 전용이다. JS 병렬 pool과 GPU는 기본 제품 경로가 아니다.
- 최적화 schema는 `toram.crysta-*`다. Native/checkpoint v21·split v7이며 v20 이하 및 과거 `toram.d4-*` checkpoint를 거부한다. no-incumbent/무한 상한의 JSON 재개·앱 저장 schema·출시 버전을 유지한다.
- 유틸리티 상한은 MP 2000/신속의 수도 2300, AMPR% 제외, 저항 후 CRIT 100, ASPD/행동속도 50%다. 파생 대미지·raw 조건을 보존한다. utilityPolicyVersion 2, Native 계산 v4, Worker client/parallel v3다.
- Native는 52키·14쌍·확장 묶음의 실제 지지값·인증 상한을 쓴다. stat-up/속성 평가, CSPD/영창 표시, 안전 조건 밖 envelope 금지 유지. 계약: `docs/verification/crysta-joint-supply-bound.md`.
- 후보 준비는 고정 %/+ 공급 좌표·가변 기초값 함수로 동등/HP·ASPD 우열 후보를 축소한다. 소수·가변 ATK·알 수 없는 변환은 raw 보존. JS/Native 트리 정렬만 압축하며 상한·최종 평가는 raw다. 전처리로 전체 시간은 증가. 계약/140회 계측: `docs/verification/crysta-candidate-projection.md`.
- Native 분기는 두 자식 감소폭·후보 수·gap으로 두 축을 고른다. median·사전 검사·lookahead 유지. 근거: `docs/verification/crysta-branch-workload.md`.
- CRIT 정수 결합·AMPR/CRIT 조건부 공격 45방향을 유지한다. 예산/단조성 fallback·전체 목록: `docs/verification/crysta-linear-crit-bound.md`, `docs/verification/crysta-axis-upper-bound.md`, `docs/verification/crysta-joint-supply-inventory.md`.
- 백분율·소수 배율 내림은 정수 비율로 계산하며 정수 옵션만 i32 Pareto 비교한다. 산술 계약: `docs/verification/optimization-integer-arithmetic.md`.
- 콤보 근거리/원거리 override는 상호 배타적이고 모두 끄면 스킬 기본 판정이다. 트리 탐색·증감 단위·resize는 투자 변경 이벤트가 아니다.
- 결과 요구조건은 MAXHP/MAXMP/듀얼 적용 전 AMPR/평타 CRIT/ASPD다. 거리·요구조건 override·추천 제외 크리스타는 schema v2 `ScenarioContext.optimizationPreferences`에 저장한다. `null`은 제한 해제, 누락 키는 동적 기본값이다.
- 마이룸 요리는 5칸·중복 금지·Lv.1~10·수치 고정·요리명 미표시다. `myRoomFood`는 `{id,level}`/null, `guildFoodBuff` 기본 true(HP+1000/MP+100)다. Application 파생·ELEM_P·보존 효과 미연결 계약: `docs/verification/my-room-food.md`.

## 3. 저장·설치·업데이트

- 로컬 소스 버전은 package/Cargo/Tauri와 두 lockfile의 v0.7.3이다. 2026-10-12 `gh api .../releases/latest`로 일반 공개 Latest v0.7.3과 NSIS 설치 파일·서명·`latest.json` 자산을 확인했다. 릴리스 커밋은 `b779b42`, 태그는 `v0.7.3`이다. [공개 릴리스](https://github.com/Horus04300/Toram_Auto_building/releases/tag/v0.7.3).
- 앱 식별자는 `com.toramonline.autobuildcalculator`, 제품명은 `Toram Online Auto Build Calculator`다. 설치는 LocalAppData 아래 공백 포함 제품명 폴더, 세팅은 정확히 `%LOCALAPPDATA%\ToramOnlineAutoBuildCalculator`다. 설치 제거와 사용자 데이터 삭제를 구분한다.
- SettingsRepository는 `format: toram-auto-build-document`, schema v2의 `saved-build`/`application-state`를 관리한다. 이름 있는 빌드는 Native JSON, 자동 복원은 `toram.auto-build.application-state.v2`다. v1 입력의 오염된 버프 파생 `externalOptions`만 폐기하고 v2로 쓴다. 폐기한 베타 형식·File System Access API·IndexedDB를 복원하지 않는다.
- 활성 버프는 엔진이 on/off·스택에서 해석하며 외부 옵션으로 중복 복제하지 않는다.
- 저장/업데이트 어댑터 원본은 `frontend/runtime/`의 TypeScript다. `npm run types:emit`으로 JS를 생성한다. 생성 JS만 수정하지 않는다. `dist/`도 생성물이며 prepare는 소스에서 삭제된 배포 파일을 제거한다.
- Tauri updater 2.11.0, GitHub Latest 단일 endpoint, 자동 확인 기본 true, 동의 후 다운로드·서명 검증·설치를 유지한다. 저장 설정은 `appSettings.update.checkOnStartup`이다.
- 설치 전에 실행·일시정지·대기 계산을 확인하고 승인 후 cancel/dispose한다. 다운로드 중 새 계산에는 다시 동의를 받고 최신 입력을 재저장한다. 종료/저장 실패 시 설치를 차단한다. 계약: `docs/architecture/app-update-release.md`.
- NSIS는 currentUser/WebView2 downloadBootstrapper다. 과거 실제 0.6.4→0.6.5 업그레이드·세팅 보존 검증은 `docs/verification/release-0.6.5-upgrade.md`에 있으며 이번 실기기 검증과 구분한다.

## 4. 출처·보류 범위

- S1 출처 연결, S2~S5 계산 검증, 실제 전투 상태 자동 전이는 별개다. 스킬 수치·상한을 추정하지 않는다. `docs/skill-tree-verification-standard.md`와 원문을 따른다. 등록 생성 원본은 `assets/source-data/skill-registration/`다.
- 피격 시뮬레이션·피격/저항 시간 의존 효과·콤보 포인트/레벨·보류 고급 태그를 임의 구현하지 않는다. 다음 스킬 한정 효과·사용 후 소멸·MP 흐름·직접 피해·버프와 구분한다.
- 미구현 판단/후속 구현 전에는 `docs/verification/unimplemented.md`를 읽고 코드로 재판정한다. 자동 장비 옵션/잠재력 탐색은 별도 승인 범위이며 수동 입력을 유지한다. 계약: `docs/architecture/equipment-option-assignment-spec.md`.

## 5. 검증 명령·현재 기록

- v0.7.3은 사용자 요청으로 회귀·성능·설치 검증을 생략했다. `gh run watch 38149861388 --exit-status` 종료 0: `skip_checks=true`로 Web/Rust SKIP, 버전·태그·서명 빌드·자산·Latest 공개 PASS. [실행](https://github.com/Horus04300/Toram_Auto_building/actions/runs/38149861388). 실제 설치/업그레이드·성능 검증과 구분한다.
- 구조: `npm run verify:architecture`, `npm run test:regression`. 단계별 중첩 명령은 폐기했다. normal/characterization 분류: `docs/verification/regression-baseline.md`.
- 로딩/배포 소스: `npm run verify:entry`, `npm run desktop:prepare`, `npm run verify:entry:dist`. Rust: `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo test --manifest-path src-tauri/Cargo.toml`, 필요한 clippy/빌드.
- 폴더 이동 후 `npm run desktop:clean`으로 Tauri·업데이터·앱의 dev/release/Windows x64 release 캐시를 정리한다. 계측 기록·다른 의존성·사용자 세팅 유지. npm 상대 경로·전체 명령: `README.md`.
- 스킬/계산: `node tools/verification/audit-stack-source-links.mjs --require-s1` 및 대상 트리·계산·콤보 회귀. 최적화는 정확성 계약의 해당 Gate를 추가한다.
- 저장 실기기 E2E는 `TORAM_E2E_CDP`가 필요하고 SKIP은 통과가 아니다. 브라우저 검증도 실제 Tauri 설치/업그레이드와 구분한다.
- 계측: `npm run bench:optimization:build` → `npm run bench:optimization`. `timing.totalMs`는 JS 준비부터 Native 결과 복원·최종 JS 재평가까지이며 UI 제외다. 계약: `docs/verification/optimization-computation-timing.md`.
- 구조 변경·이전 인앱 시간 기록: `docs/verification/role-based-refactoring.md`, `docs/verification/crysta-in-app-timing-gap.md`. 과거 수치를 현재 성능으로 쓰지 않는다.
- 이번 검증: Native exact 83개, 압축 oracle 72조건/3,711완성/324대체, JS/Rust 1,986개, 회귀 77/77, architecture/clippy, S1 427/427 PASS. Native 저장 E2E는 CDP 미설정 SKIP. 상세 명령: `docs/verification/crysta-candidate-projection.md`.
- 초기해 단일/두 부위 수리·대미지 개선·정렬 점수 캐시 유지. 당시 v20 계측: `docs/verification/crysta-infeasible-seed-repair.md`.
- 기존 듀얼 계측은 실제 사용자 빌드를 재현하지 못해 성능 근거에서 제외한다. 실제 입력 검증은 미완료다. 감사: `docs/verification/crysta-dual-unadjusted.md`.
- 문서 변경: `npm run ai:audit`, `git diff --check`. 현재 handoff는 12 KiB 이하로 유지한다. 탐색 진입점: `docs/ai-context-guide.md`.
- B&B 과정 로그(bounded, 제품 정책 유지): `docs/verification/crysta-search-process-trace.md`.
