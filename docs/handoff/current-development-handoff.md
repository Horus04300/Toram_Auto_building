# 현재 개발 상태 및 인수인계

- 갱신: 2026-10-26. v0.7.3, Native/checkpoint v25·split v9. 이 문서·코드·실행 검증이 현재 기준이다.
- 제품: 공통 웹·Tauri v2 Windows 앱.

## 구조·입력

- web/index.html은 공통 틀·홈, app-entry.mjs는 라우팅이다. pages/calculator/의 HTML·classic 초기화는 필요할 때 1회 로드한다. 웹/앱·Worker 상대 경로 유지.
- 각 제품 폴더 README가 진입점. web/src/는 JS·타입, public/은 자산, desktop/adapters/는 앱 JS/TS다.
- engine/src/가 evaluator·solver·stats·joint_supply의 유일한 원본이다. Native 앱·개발용 바이너리·WASM 모두 이 crate를 사용한다. desktop/src/optimization/은 앱 서비스·병렬 작업 수명만 소유한다.
- JS는 UI·compile·후보 준비·최종 재평가다. application-use-cases.js는 조립, calculation-policies.js는 규칙, build-draft-store.js의 BuildDraft/Scenario는 영속 입력, Request는 일회성 값이다.
- 스킬29트리: 계산/콤보는 첫 유효 정의, 버프 카드는 preferStackControl 정의. tools/fixtures/skill-definition-precedence.json을 따른다.
- web:dev는 소스, web:build→build/web/, desktop:prepare→build/desktop/. wasm:build는 단일·병렬 WASM을 build/generated/wasm/에 만든다. 웹은 Native 저장/업데이트 제외. 설치는 README.
- build/{generated,desktop,web,release,tmp}/는 생성물. assets/... 원본 대응은 tools/support/frontend-paths.mjs다.
- 배포는 index.html·실행 assets만 포함하고 원문·TS·로그는 제외한다. 과거 pipeline 경로·해시는 보존하며 검증 시 data/sources/로 연결한다.

## 추천 계약

- 빠른 추천은 Rust WASM 초기해·트리 준비만 실행: 방문0, heuristic·인증 상한/gap 없음. 웹 정밀은 같은 세션의 공유 메모리 Rayon 풀(논리 코어1~64), 앱은 Native. COOP/COEP·SharedArrayBuffer 미지원은 단일 WASM, JS 탐색 fallback 없음. 웹 배포 헤더는 web/README.md.
- exact·bounded·heuristic·no-incumbent-yet·paused·cancelled·invalid를 구분한다. 30초 slice·pause/resume·취소를 유지하고 사용자 대기 시간을 실행 시간에 합산하지 않는다. Native continuation은 최대 4개/oldest eviction, WASM 취소는 Worker와 frontier를 폐기한다.
- 잠금·빈 잠금·금지·계보·동점 ID를 보존하고 추천 적용은 잠기지 않은 슬롯만 변경한다. 계산 입력 변경은 이전 추천·continuation을 폐기한다. 이름·검색·미적용 요구조건 편집·중복 화면 알림은 폐기 사유가 아니다.
- Native 좌표 59개·기본 결합 14쌍, 정수 비율 내림·i32 Pareto·%/+ 공급 좌표 투영을 유지한다. STR/DEX/AGI/INT/VIT의 무효 %는 입력별로 판정하고 raw 옵션은 끝까지 보존한다. 안전하지 않은 envelope에는 fallback을 쓴다.
- 유틸리티 목표는 MP 2000/신속의 수도 2300, AMPR% 제외, 저항 후 평타 CRIT 100, ASPD/행동속도 50%다. utilityPolicyVersion 2, Native 계산 v5, WASM result v1이다.
- 미채택된 국소 상한·공급상태 상한·GPU는 활성화하지 않는다. 모든 입력의 10초 exact를 보증하지 않는다.
- 정확성·후보 삭제 Gate: docs/architecture/crysta-optimization-contract.md. 실행 제어: docs/architecture/native-optimization-runtime.md.

## 저장·앱

- SettingsRepository는 toram-auto-build-document schema v2의 saved-build/application-state를 관리한다. 이름 있는 앱 빌드는 Native JSON, 자동 복원 키는 toram.auto-build.application-state.v2다. v1은 버프 파생 externalOptions만 폐기하고 읽는다.
- 장비 선택지는 저장 복원 전에 초기화하며 기본 옵션 자동 생성은 삭제했다. 사용자 옵션·빈 목록·방패·제련값 복원을 유지한다. docs/verification/session-restore.md 참고.
- 장비 탭에서 게임 ID로 주무기·보조·몸/추가/특수 원본 옵션을 선택한다. catalogItem?에 ID·버전·정의를 고정하고 현재 조건으로 계산한다. 수동 옵션은 보존·합산하며 제작 장비는 수동 입력만 사용한다. 보조 일반 옵션은 방패/단검/화살/두루마리만 반영하고 나머지는 제외한다. ATK·안정률·제련은 기존 입력을 유지한다. 무기/조건부 속성·대상 속성·비례 ATK/MATK를 연결한다. docs/architecture/item-data-format.md.
- 소모품15카테고리/290개를 원문 선언·native 계열로 연결해 도감/버프 목록에 표시·검색한다. 고정 옵션 지원212개와 구분한다. consumableBuffs?는 ID·버전·그룹·초·옵션을 고정한다. 같은 그룹만 교체하며 수동 externalOptions 유지. 표시 분류와 중복 규칙은 별개다. 복합/동적0/자동 만료 제외. 근거 docs/verification/consumable-categories.md.
- 스테이터스 타겟은 검색·지역/개체·필드 단일/입장 난이도/고난도 레벨을 선택해 DEF/MDEF·물리/마법 내성·크리티컬 저항·레벨을 자동 입력한다. 원본 순서·float32 절삭·부위 보정·고난도 고정 플래그를 따른다. 관성 변동률은 %p 정보로 표시한다. scenario.bossSelection?에 원본/선택을 고정하며 수동 target 숫자는 별도 보존한다. 부위는 전체 미파괴 가정, 동적 전투 상태와 서버 입장 최대 레벨은 미반영이다. 근거 native-target/·native-highraid-target/, 상세 toram-boss-pipeline.md.
- 길드 레이드 6종·소테리아 두 본체/후속 페이즈를 별도 분류한다. 현재 레벨=max(40,남은 HP 게이지×4), DEF/MDEF는 정수 곱→float32 0.01배, 내성은 원본+레벨/10 절삭이다. Lv40 HP는 미확정, Lv528 이상 int32 HP도 미확정이다. 서버 랜덤/type40·클리어 후 다음 레벨 증가량·미래 부위 난이도는 미반영이다. 신원은 사용자 제공 분류와 정확 ID/모델을 대조한 검토 목록이며 서버 입장 표를 추출했다고 주장하지 않는다.
- 설치: LocalAppData 아래 공백 포함 Toram Online Auto Build Calculator 폴더. 사용자 세팅: %LOCALAPPDATA%\ToramOnlineAutoBuildCalculator. 앱 제거와 세팅 삭제는 다르다.
- 앱 식별자는 com.toramonline.autobuildcalculator. package/Cargo/Tauri·제품 lockfile v0.7.3 유지. Latest 공개 상태를 로컬 코드 변경과 혼동하지 않는다. 마지막 출시 확인은 v0.7.3이며 이번 정리는 배포하지 않았다.
- Tauri updater 2.11.0·GitHub Latest endpoint·동의 후 다운로드/서명 검증/설치를 유지한다. 설치 전 계산 종료와 최신 입력 저장이 실패하면 설치를 차단한다. docs/architecture/app-update-release.md 참고.
- 저장/업데이트 어댑터는 desktop/adapters/ TypeScript가 원본이다. types:emit은 build/generated/desktop/에 JS를 생성한다.

## 기능 경계·보류

- 하늘색 UI. 기본 `/` 홈, 앱 ?view=페이지ID. 홈·도감·게시판·인벤토리 조회는 계산기와 독립. 계산기 진입·구성 담기/적용·계정 저장/불러오기만 ensureCalculator() 대기. DOM/입력 유지·실패 격리.
- 콤보 9칸, 거리 override 상호 배타, 요구조건 null=제한 해제/누락=동적 기본값, 추천 제외 목록을 유지한다. 마이룸 요리 5칸·중복 금지·Lv.1~10, guildFoodBuff 기본 true(HP+1000/MP+100)다.
- 결계 Lv.10 ON 행동속도 +25% 연결을 유지한다. 피격 시뮬레이션·콤보 포인트/레벨·보류 고급 태그·자동 장비 옵션 탐색은 임의 구현하지 않는다.
- S1 출처 연결, S2~S5 계산 검증, 실제 전투 상태 전이는 별도 완료 기준이다. docs/skill-tree-verification-standard.md와 docs/verification/unimplemented.md를 따른다. 스킬 계산 전달 누락 감사는 docs/verification/skill-calculation-wiring-audit.md에 있으며 이번 정리에서 수정하지 않았다.
- 도감 `/catalog`: 8분류·6언어. 책갈피2열·무기/크리스타 팝업. 보스 전체/입장/필드/고난도·이벤트 칸만. 우측 검색·목록/상세(기초ATK/DEF·원문옵션·조건색·내부스크롤), 탭/진단 제거. 계보·난이도/레벨. Chrome 소스/웹 PC/모바일 PASS. 인벤토리 연결 후속.
- 인증: Node24·SQLite, 웹 쿠키·앱 메모리 세션. docs/architecture/account-home-server.md.
- 플랫폼: 인벤토리10종·2객체 병합, 전체/부분 공개·고정 릴리스·독립 복사·출처·즐겨찾기·순위·검색/관리. 개인 ID 제거·revision/요청 키 유지. 후속: records 이관·별점·도감 복사·공개본 직접 병합. 계약 docs/architecture/platform-{design,data-api}-contract.md. v0.7.3·1.x 목표.

- 인벤토리: 2열·세로 팝업·내 목록440px·초안/종류별 이름·트리맞춤. 기존 항목2분/이탈저장·실패보존·충돌검사. 계산기/인벤토리 기본10·Shift+클릭=선택/선행 Lv10·다른분기보존. 단위·Chrome PASS.

## 검증 진입점

- 웹 병렬화·Rust 최적화 검증과 과거 측정은 docs/verification/rust-shared-runtime.md. 기초99종 자동 제외·잠금 유지. 전체 입력10초 exact/P95 보증 없음.

- 아이템/보스 갱신은 npm run items:sync / bosses:sync 수동 명령이다. 기본 공개 분기는 블랑을 확인한 releaseC(10/22)이며 서버 자동 판정이 아니다. --application releaseB로 과거 분기를 재현한다. --check는 발행하지 않으며 재검토2/실패1을 전달한다. 코드/참조/형식 실패 시 이전 latest·개발판 manifest를 유지한다. Git 제외 pipeline 이력은 별도 백업한다. 상세 toram-item-pipeline.md·toram-boss-pipeline.md.
- 발행: 아이템11,749개·보스691 ID/5,209변종. 오류3표·EOF10맵·미연결 레이드1건 격리.10/23 퀘스트/Check 분기 추적으로 메뉴40경로·입장65변종을 추가 연결했다. 콜론 보스3300:10은 난이도 선택,4500:100은 필드 유지. 상세 toram-boss-pipeline.md.
- toram.project-items.v1: 크리스타553개를 ID로 이름·옵션·조건·이전ID에 결합해 공통 조회한다. 댄드라이언9776 포함, 이전425개 이름은 저장/잠금/금지 alias로 호환한다.7,742 조건 대조·실데이터 WASM oracle 통과. notModeled는 보존/표시하고 계산하지 않는다. 상세 item-data-format.md·crysta-id-catalog.md.
- 옵션 계산: 대상별 피해7종·속성/화살 우선·고정 스킬 속성·비례10계열을 JS/Rust로 연결. 비례는 원본별 tenths 복원→기초 스탯 float32 합산→1회 절삭. 후보 투영 v3, 가변 비례는 raw 보존·f32 오차 상한. 신규 scalar6종 포함62종의 효과 소비는 notModeled. 장비 미연결0·7,380개, 이벤트3종 수동 활성. 근거 docs/verification/item-option-calculation-wiring.md.
- 옵션 검증: Rust99·JS/Rust432·WASM40·Chrome/저장·architecture PASS. 회귀79 PASS·앱1 SKIP.
- 아이템 원형·6언어는 data/sources/toram-items/items.77596232.connected.json·item-connections.md에 보존한다. Coryn ID·미연결 옵션·드롭 후보를 게임 확정값으로 합치지 않는다.
- 옵부 오프라인 실험·원형/제작 검증은 docs/verification/toram-statting-{extraction,experiments}.md. 앱 추천은 보류, 초기 제작 절삭·DTE·반전/서버/소재 미확인.
- npm run verify:architecture: 타입·계산·저장·UI·실행 경계. npm run test:regression: 현재 기능 회귀. 분류는 tools/regression-fixtures.mjs와 docs/verification/regression-baseline.md.
- Rust: 두 manifest에 fmt/test/clippy. 공용 코어에 상한 property·완전탐색·동점·병렬·중단/재개 테스트를 둔다. WASM·후보 투영 검사는 이전 JS 탐색기 없이 독립 소형 완전탐색으로 확인한다.
- 스킬 S1: node tools/verification/audit-stack-source-links.mjs --require-s1. 실제 앱 저장 E2E는 TORAM_E2E_CDP가 없으면 SKIP이다.
- 기존 플랫폼/도감·홈/인벤토리 Chrome 검증은 각 주제 문서. OAuth 사용자 로컬 성공, Docker·공개 배포 미검증. verify:web:browser는 web:build 필요.
- npm run ai:audit, git diff --check. handoff는 12 KiB 이하. 탐색: docs/ai-context-guide.md.
