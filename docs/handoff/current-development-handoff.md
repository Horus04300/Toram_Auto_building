# 현재 개발 상태 및 인수인계

- 갱신: 2026-10-23. v0.7.3, Native/checkpoint v23·split v8. 이 문서·코드·실행 검증이 현재 기준이다.
- 제품: 공통 화면의 정적 웹·Tauri v2 Windows 앱. 이전 JS 추천기/Worker 실험은 삭제했다.

## 구조·입력

- web/index.html → web/src/app-entry.mjs → classic-script-manifest.mjs → ui-bootstrap.js. 웹/앱 환경별 스크립트와 Worker 상대 경로를 유지한다.
- 루트는 web/(공통 화면)·desktop/(앱 전용)·engine/(Rust 추천)·server/·data/(원문)·tools/·docs/로 나눈다. 각 README가 진입점이다. web/src/는 JS·타입 원본, web/public/은 정적 리소스다. 앱 전용 JS/TS는 desktop/adapters/다.
- engine/src/가 evaluator·solver·stats·joint_supply의 유일한 원본이다. Native 앱·개발용 바이너리·WASM 모두 이 crate를 사용한다. desktop/src/optimization/은 앱 서비스·병렬 작업 수명만 소유한다.
- JS는 화면·문제 compile·보수적 후보 준비·최종 재평가를 담당한다. 계산 조립은 web/src/application/application-use-cases.js, 공통 규칙은 calculation-policies.js, 영속 입력은 build-draft-store.js의 BuildDraft/Scenario다. 선택 타격·일회성 값은 Request로 분리한다.
- 스킬은 29개 트리 파일이다. 기본 계산·콤보는 첫 유효 정의, 버프 카드만 preferStackControl 스택 보강 정의를 사용한다. 등록 우선순위는 tools/fixtures/skill-definition-precedence.json을 따른다.
- npm run web:dev는 소스 HTTP, web:build는 build/web/, desktop:prepare는 build/desktop/를 만든다. 웹은 Native 저장·업데이트 스크립트를 제외한다. build/generated/wasm/은 wasm:build 생성물이다.
- build/{generated,desktop,web,release,tmp}/는 생성물이다. generated/는 WASM·어댑터 JS, desktop/은 Tauri가 포함할 화면, web/은 웹 배포본이다. 배포 URL assets/...와 원본 위치의 대응은 tools/support/frontend-paths.mjs에 있다. 사용자 세팅 경로는 유지한다.
- tools/prepare-frontend.mjs는 index.html·실행 assets만 배포한다. 원문·타입 TS·로그는 제외한다. 고정 pipeline 계약/근거의 과거 경로·해시는 보존하고 검사 시 data/sources/로 연결한다.

## 추천 계약

- 빠른 추천은 Rust WASM 세션의 초기해·트리 준비만 실행하며 방문 노드 0, heuristic·인증 상한/gap 없음이다. 웹 정밀 실행은 같은 세션, 앱 정밀 실행은 Native다. JS 탐색 fallback은 없다.
- exact·bounded·heuristic·no-incumbent-yet·paused·cancelled·invalid를 구분한다. 30초 slice·pause/resume·취소를 유지하고 사용자 대기 시간을 실행 시간에 합산하지 않는다. Native continuation은 최대 4개/oldest eviction, WASM 취소는 Worker와 frontier를 폐기한다.
- 잠금·빈 잠금·금지·계보·동점 ID를 보존하고 추천 적용은 잠기지 않은 슬롯만 변경한다. 계산 입력 변경은 이전 추천·continuation을 폐기한다. 이름·검색·미적용 요구조건 편집·중복 화면 알림은 폐기 사유가 아니다.
- Native 좌표 52개·기본 결합 14쌍, 정수 비율 내림·i32 Pareto·%/+ 공급 좌표 투영을 유지한다. STR/DEX/AGI/INT/VIT의 무효 %는 입력별로 판정하고 raw 옵션은 끝까지 보존한다. 안전하지 않은 envelope에는 fallback을 쓴다.
- 유틸리티 목표는 MP 2000/신속의 수도 2300, AMPR% 제외, 저항 후 평타 CRIT 100, ASPD/행동속도 50%다. utilityPolicyVersion 2, Native 계산 v4, WASM result v1이다.
- 미채택된 국소 상한·공급상태 상한·GPU는 활성화하지 않는다. 모든 입력의 10초 exact를 보증하지 않는다.
- 정확성·후보 삭제 Gate: docs/architecture/crysta-optimization-contract.md. 실행 제어: docs/architecture/native-optimization-runtime.md.

## 저장·앱

- SettingsRepository는 toram-auto-build-document schema v2의 saved-build/application-state를 관리한다. 이름 있는 앱 빌드는 Native JSON, 자동 복원 키는 toram.auto-build.application-state.v2다. v1은 버프 파생 externalOptions만 폐기하고 읽는다.
- 장비 선택지는 저장 복원 전에 초기화하며 기본 옵션 자동 생성은 삭제했다. 사용자 옵션·빈 목록·방패·제련값 복원을 유지한다. docs/verification/session-restore.md 참고.
- 장비 탭에서 게임 ID로 주무기·보조·몸/추가/특수 원본 옵션을 선택한다. catalogItem?에 ID·버전·정의를 고정하고 현재 조건으로 계산한다. 수동 옵션은 보존·합산하며 제작 장비는 수동 입력만 사용한다. 보조 일반 옵션은 방패/단검/화살/두루마리만 반영하고 나머지는 제외한다. ATK·안정률·제련은 기존 입력을 유지하며 미연결 효과/속성은 차단한다. docs/architecture/item-data-format.md.
- 버프 탭에서 단순 고정 스탯 소모품 209개를 선택·계산·저장한다. consumableBuffs?에 ID·버전·그룹·초·옵션을 고정한다. 같은 duration 그룹은 교체하고 수동 externalOptions는 유지한다. 복합 스크립트·동적 0 operand·자동 만료는 제외한다. 근거 data/sources/toram-items/item-use-rules.md·native-item-usage/의 함수/해시다.
- 스테이터스 타겟은 검색·지역/개체·필드 단일/입장 난이도/고난도 레벨을 선택해 DEF/MDEF·물리/마법 내성·크리티컬 저항·레벨을 자동 입력한다. 원본 순서·float32 절삭·부위 보정·고난도 고정 플래그를 따른다. 관성 변동률은 %p 정보로 표시한다. scenario.bossSelection?에 원본/선택을 고정하며 수동 target 숫자는 별도 보존한다. 부위는 전체 미파괴 가정, 동적 전투 상태와 서버 입장 최대 레벨은 미반영이다. 근거 native-target/·native-highraid-target/, 상세 toram-boss-pipeline.md.
- 길드 레이드 6종·소테리아 두 본체/후속 페이즈를 별도 분류한다. 현재 레벨=max(40,남은 HP 게이지×4), DEF/MDEF는 정수 곱→float32 0.01배, 내성은 원본+레벨/10 절삭이다. Lv40 HP는 미확정, Lv528 이상 int32 HP도 미확정이다. 서버 랜덤/type40·클리어 후 다음 레벨 증가량·미래 부위 난이도는 미반영이다. 신원은 사용자 제공 분류와 정확 ID/모델을 대조한 검토 목록이며 서버 입장 표를 추출했다고 주장하지 않는다.
- 설치: LocalAppData 아래 공백 포함 Toram Online Auto Build Calculator 폴더. 사용자 세팅: %LOCALAPPDATA%\ToramOnlineAutoBuildCalculator. 앱 제거와 세팅 삭제는 다르다.
- 앱 식별자는 com.toramonline.autobuildcalculator. package/Cargo/Tauri·제품 lockfile v0.7.3 유지. Latest 공개 상태를 로컬 코드 변경과 혼동하지 않는다. 마지막 출시 확인은 v0.7.3이며 이번 정리는 배포하지 않았다.
- Tauri updater 2.11.0·GitHub Latest endpoint·동의 후 다운로드/서명 검증/설치를 유지한다. 설치 전 계산 종료와 최신 입력 저장이 실패하면 설치를 차단한다. docs/architecture/app-update-release.md 참고.
- 저장/업데이트 어댑터는 desktop/adapters/ TypeScript가 원본이다. types:emit은 build/generated/desktop/에 JS를 생성한다.

## 기능 경계·보류

- 스킬 트리 기존 배치 유지·이름11px/레벨10px·습득 배지(10/19).
- 콤보 9칸, 거리 override 상호 배타, 요구조건 null=제한 해제/누락=동적 기본값, 추천 제외 목록을 유지한다. 마이룸 요리 5칸·중복 금지·Lv.1~10, guildFoodBuff 기본 true(HP+1000/MP+100)다.
- 결계 Lv.10 ON 행동속도 +25% 연결을 유지한다. 피격 시뮬레이션·콤보 포인트/레벨·보류 고급 태그·자동 장비 옵션 탐색은 임의 구현하지 않는다.
- S1 출처 연결, S2~S5 계산 검증, 실제 전투 상태 전이는 별도 완료 기준이다. docs/skill-tree-verification-standard.md와 docs/verification/unimplemented.md를 따른다. 스킬 계산 전달 누락 감사는 docs/verification/skill-calculation-wiring-audit.md에 있으며 이번 정리에서 수정하지 않았다.
- 계정 모달·Google 로그인·빌드/장비/즐겨찾기와 Node24·SQLite·Docker 서버 추가. test:account·architecture·Entry·Edge PASS. 실제 OAuth/Docker·배포 미검증. 앱 세션은 메모리만 쓴다. docs/architecture/account-home-server.md.

## 검증 진입점

- 10/23 재배치 검증(Entry3종·배포경로·Rust/EXE 포함)은 docs/verification/repository-layout.md. ID 통합 후 architecture·회귀74항목(저장E2E1 SKIP)·S1·Python15/11·Edge 데이터/JSON/재열기·한 슬롯 UI Worker PASS. 전체 후보10초 bounded로 verify:web:browser 성능 Gate는 미통과. 상세 crysta-id-catalog.md.

- 아이템/보스 갱신은 npm run items:sync / bosses:sync 수동 명령이다. 기본 공개 분기는 블랑을 확인한 releaseC(10/22)이며 서버 자동 판정이 아니다. --application releaseB로 과거 분기를 재현한다. --check는 발행하지 않으며 재검토2/실패1을 전달한다. 코드/참조/형식 실패 시 이전 latest·개발판 manifest를 유지한다. Git 제외 pipeline 이력은 별도 백업한다. 상세 toram-item-pipeline.md·toram-boss-pipeline.md.
- 발행: 아이템11,749개·보스691 ID/5,209변종. 오류3표·EOF10맵·미연결 레이드1건 격리.10/23 퀘스트/Check 분기 추적으로 메뉴40경로·입장65변종을 추가 연결했다. 콜론 보스3300:10은 난이도 선택,4500:100은 필드 유지. 상세 toram-boss-pipeline.md.
- DLL/metadata는 사용자 동의의 VM_READ 캡처로 재검토했고 근거를 양쪽 native-update-20261022/에 해시 고정했다. 게임 접근은 sync에 추가하지 않았다. 상세 함수·상수·한계는 위 pipeline 문서를 따른다.
- toram.project-items.v1: 크리스타553개를 ID로 이름·옵션·조건·이전ID에 결합해 공통 조회한다. 댄드라이언9776 포함, 이전425개 이름은 저장/잠금/금지 alias로 호환한다.7,742 조건 대조·실데이터 WASM oracle 통과. notModeled는 보존/표시하고 계산하지 않는다. 상세 item-data-format.md·crysta-id-catalog.md.
- 갱신/ID 통합 로그: build/tmp/{update-pipeline-20261022,crysta-id-catalog,boss-colon-menu}/. 상세 검증은 해당 문서를 따른다.
- 아이템 원형·6언어는 data/sources/toram-items/items.77596232.connected.json·item-connections.md에 보존한다. Coryn ID·미연결 옵션·드롭 후보를 게임 확정값으로 합치지 않는다.
- 옵부 Lv325·TEC255·예산840: tools/statting 오프라인 입력/경로 실험1,753건·약121만 경로, 소형 기준12/12·추적63개 재생·원형/스탯/제작 검증 PASS. 설계 docs/architecture/statting-recommendation-design.md, 근거 docs/verification/toram-statting-{extraction,experiments}.md. 앱 추천 미연결. 초기 제작 절삭·DTE 연결·반전/서버/소재 미확인.
- npm run verify:architecture: 타입·계산·저장·UI·실행 경계. npm run test:regression: 현재 기능 회귀. 분류는 tools/regression-fixtures.mjs와 docs/verification/regression-baseline.md.
- Rust: 두 manifest에 fmt/test/clippy. 공용 코어에 상한 property·완전탐색·동점·병렬·중단/재개 테스트를 둔다. WASM·후보 투영 검사는 이전 JS 탐색기 없이 독립 소형 완전탐색으로 확인한다.
- 스킬 S1: node tools/verification/audit-stack-source-links.mjs --require-s1. 실제 앱 저장 E2E는 TORAM_E2E_CDP가 없으면 SKIP이다.
- npm run verify:web:browser: 설치된 Playwright·Edge, web:build 필요. 개발/하위 경로·JSON·Worker 재사용/취소/재개·세션 재열기 검사.
- npm run bench:optimization:build 후 bench:optimization. raw compile부터 최종 JS 재평가까지 측정하며 새 산출물은 desktop/target/에 둔다.
- 사용자 루브닐·두 마법 입력과 실행 검증 기록: docs/verification/rust-shared-runtime.md. 정리 후 실제 실행 결과도 이 문서에 기록한다.
- npm run ai:audit, git diff --check. handoff는 12 KiB 이하. 탐색: docs/ai-context-guide.md.
