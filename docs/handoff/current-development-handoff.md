# 현재 개발 상태 및 인수인계

갱신: 2026-10-28. 제품 버전0.7.3, Native/checkpoint v25·split v9. 현재 상태는 이 문서·실제 코드·실행한 검사로 판단한다.

## 책임과 실행

- 공통 화면은 `web/`, Windows 앱은 `desktop/`, 평가·탐색은 `engine/`, 계정 API는 `server/`가 소유한다. 작업별 원본·검사는 `docs/ai-context-guide.md`에서 찾는다.
- `web/index.html`은 공통 틀·홈, `web/src/app-entry.mjs`는 ESM 진입점이다. 계산기는 `web/src/pages/calculator/`에서 최초 사용 시 한 번 초기화한다. 홈·도감·게시판·인벤토리 조회는 계산기와 독립이며 DOM·입력·실패를 격리한다.
- JS는 UI·입력/옵션/후보 조립·표시, 공용 Rust evaluator는 full/summary/supply·산술을 소유한다. 일반 계산은 WASM 필수다. 모듈 초기화 뒤 동기 계산 API를 제공하며 WASM 실패는 계산기에 표시한다.
- BuildDraftStore는 확정 Build/Scenario·일회 Request·revision을, OptimizerController는 추천 작업 수명을 소유한다. SettingsRepository는 저장 계약, UpdateController는 업데이트 상태·설치 조정·잠금/epoch를 소유한다.
- 스킬29트리·427정의는 ID별 단일 원본이며 registry가 중복을 거부한다. 수치·순서는 fixture와 S1 Gate로 검증한다. S1 출처 연결, S2~S5 계산 연결, 전투 상태 시뮬레이션은 별도 완료 기준이다.
- 실제 ESM 그래프가 웹/앱·Worker 배포를 결정한다. 계산 커널은4모듈이고 UI/스킬 데이터에 의존하지 않는다. 동결 JS 수식은 테스트 전용 독립 oracle이며 제품 그래프에 포함하지 않는다.
- npm 명령은 desktop:build/web:build/desktop:dev/web:dev와 test만 제공한다. build/dev/test가 WASM·TS 준비를 소유한다. 웹은 build/web/, 앱 프론트엔드는 build/desktop/, TS는 build/generated/desktop/이다. build/·Rust target/·node_modules/는 생성물이다.

## 추천·계산 계약

- 빠른 추천은 WASM 초기해/트리 준비만 수행하고 방문0·heuristic·인증 상한/gap 없음이다. 웹 정밀은 동일 세션의 공유 메모리 Rayon 풀(논리 코어1~64), 앱 정밀은 Native다. COOP/COEP·SharedArrayBuffer 미지원은 단일 WASM이다.
- exact·bounded·heuristic·no-incumbent-yet·paused·cancelled·invalid를 구분한다. 30초 slice·pause/resume·취소를 제공하며 대기 시간은 실행 시간에 합산하지 않는다. Native continuation은 최대4개, oldest eviction이다. WASM 취소는 Worker/frontier를 폐기한다.
- 잠금·빈 잠금·금지·강화 계보·동점 ID를 보존하며 추천 적용은 잠기지 않은 슬롯만 바꾼다. 계산 입력 변경은 추천/continuation을 무효화한다. 이름·검색·미적용 요구조건·중복 알림은 무효화 사유가 아니다.
- 기초 고정 스탯 ID9401~9504 중99종은 자동 후보에서 제외하되 수동 장착·저장·잠금은 지원한다. exact는 이 허용 후보와 잠금에 대한 최적성이다.
- Native 좌표59개·기본 결합14쌍, 정수 비율 내림·i32 Pareto·%/+ 공급 투영·raw 옵션을 유지한다. 증명할 수 없는 상한/투영은 fallback한다. v25의 두 예약 플래그는 체크포인트 신원만 보존한다.
- Utility: MP2000/신속의 수도2300, AMPR% 제외, 저항 후 평타 CRIT100, ASPD/행동속도50%. utilityPolicyVersion2·계산v5·WASM result v1이다. 모든 입력10초 exact/P95 보증은 없다.
- 정확성 Gate는 `docs/architecture/crysta-optimization-contract.md`, 실행 제어는 `docs/architecture/native-optimization-runtime.md`를 따른다.

## 저장·릴리스

- `toram-auto-build-document` schema v2의 saved-build/application-state를 공유한다. 자동 복원 키는 toram.auto-build.application-state.v2다. v1 읽기는 파생 externalOptions만 폐기한다. 사용자 옵션·빈 목록·장비/제련을 보존하며 선택지를 먼저 초기화한 뒤 복원한다.
- 설치는 LocalAppData 아래 공백 포함 Toram Online Auto Build Calculator 폴더, 사용자 세팅은 `%LOCALAPPDATA%\ToramOnlineAutoBuildCalculator`다. 앱 제거와 세팅 삭제는 별개다.
- 식별자는 com.toramonline.autobuildcalculator다. package/Cargo/Tauri·제품 lockfile은0.7.3이다. 확인된 공개 릴리스는0.7.3이며 현재 로컬 통합본은 설치·배포하지 않았다.
- Tauri updater2.11.0·GitHub Latest endpoint·명시적 동의·서명 검증을 사용한다. 설치 전 계산 종료·최신 입력 저장 실패는 설치를 차단한다. 계약은 `docs/architecture/app-update-release.md`다.
- 저장/업데이트 TS는 `desktop/adapters/` 원본과 `desktop/tsconfig.json`으로 관리한다. 앱 준비의 TS 출력은 `build/generated/desktop/`이다.

## 기능·데이터 경계

- 기본 `/` 홈, 앱은 ?view=페이지ID다. 계산기 내부 탭/입력을 유지한다. 콤보9칸·거리 override 상호 배타·요구조건 null=해제/누락=기본값·추천 제외 저장을 지원한다. 마이룸 요리5칸·중복 금지·Lv1~10, 길드 요리 기본 true(HP+1000/MP+100)다.
- 인벤토리는10종·평평한 값/출처·검증 후 복사/병합·공개/부분 릴리스·독립 사본·즐겨찾기·revision/요청키를 지원한다. 기존 항목은2분/이탈 저장·실패 보존·충돌 검사를 사용한다. 스킬 Shift+클릭은 선택/선행 Lv10, 다른 분기는 보존한다.
- 계정은 Node24·SQLite, 웹 쿠키·앱 메모리 세션이다. 인벤토리가 쓰기 원본이며 구형 API는 투영하고 records는 읽기 보존한다. 운영 DB 이관은 미실행이다. 계약은 `docs/architecture/platform-data-api-contract.md`다.
- 도감은 읽기 전용 아이템8분류·6언어·보스/강화 계보 조회다. 이벤트보스 기간/맵 분류와 도감→인벤토리는 보류/후속이다. 화면 계약은 `web/README.md`다.
- 발행 데이터: 아이템11,749개·크리스타553개·이전 이름425alias·계보246개, 보스691ID/5,209변종이다. 2026-10-28 `releaseC`를 두 sync 명령으로 재수집·검증했으며 추가/수정/삭제·리소스 변경0건, 두 manifest는 이전 발행본과 동일하다. 소모품15분류/290표시·고정 옵션212지원이다. 미연결 값은 원문대로 보존하고 추정하지 않는다.
- 장비/소모품/보스 선택은 ID·버전·정의를 저장에 고정하며 카탈로그 갱신이 저장 값을 자동 변경하지 않는다. 수동 옵션과 타겟을 보존한다. 장비 속성·비례·이벤트 계약은 `docs/architecture/item-data-format.md`다.
- 보스는 정적 방어/내성/크리 저항/레벨을 입력한다. 원본 순서·float32·미파괴 부위 가정과 관성 %p를 유지한다. 길드 레이드6종·소테리아 페이즈와 레벨=max(40,남은 게이지×4)를 지원한다. 서버 입장 한계·random/type40·Lv40/528이상 HP·클리어 후 증가·미래 부위는 미확정이다. `docs/verification/toram-boss-pipeline.md`를 따른다.
- 아이템/보스 sync 도구는 수동이다. 기본 releaseC, 명시적 --application으로 분기를 선택한다. --check는 미발행, 검토 필요2/실패1이며 실패 시 기존 latest/manifest를 유지한다. 원본 pipeline은 Git 제외이므로 별도 백업한다.
- 장비식 추출은 앱 연결과 별개다. 근거는 `docs/verification/equipment-option-formulas.md`다. 스킬 계산 전달 누락은 `docs/verification/skill-calculation-wiring-audit.md`, 보류 범위는 `docs/verification/unimplemented.md`를 따른다. 피격·시간 자동 전이·콤보 후속·자동 장비 옵션 탐색은 임의 구현하지 않는다.

## 검증

- 현재 명령 검증: 2026-10-28 npm test의 회귀86/86(실제85 PASS·Native 저장1 SKIP)·공용 Rust96·desktop24·타입/모듈 경계·S1·fmt/clippy PASS. 데이터 재수집/무결성과 npm test 근거는 build/tmp/data-update-20261028/에 있다. npm test -- browser, 웹/Windows EXE 빌드와 앱/웹 dev 초기화 PASS 로그는 build/tmp/npm-commands-cleanup/에 있다. 별도 실제 Windows 앱8/8의 저장/추천 검증은 build/tmp/good-taste-execution/09-promoted-desktop-e2e-final.log다.
- `npm test`가 프론트엔드 준비·타입·실제 모듈 경계·전체 JS 회귀·S1·두 Rust manifest의 fmt/test/clippy를 소유한다. 개별 계산 검사는 WASM 선행 빌드가 필요하다.
- 실제 Chrome 검사는 `npm test -- browser`가 웹 준비와 계산/JSON/재열기/Worker/병렬 검사를 실행한다. 실제 앱은 audit-desktop-e2e.mjs의 격리 프로필로 확인한다. TORAM_E2E_CDP 없는 개별 Native 저장 검사는 SKIP이다.
- 문서/검색 설정은 `node tools/verification/audit-ai-context.mjs`, `git diff --check`로 검사한다. 설치·서명 업데이트 실행·Docker 이미지/공개 배포는 별도 검증이다. AI 토큰 절감량은 측정하지 않았다.
