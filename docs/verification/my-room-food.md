# 마이룸 요리

## 출처와 사용자 확정 범위

- 원문: https://coryn.club/food.php — 2026-09-11 열람, 원문 39개 요리의 Lv.1~10 제공량.
- 사용자는 앞선 효과 매핑을 승인하고 버프 탭에서 요리 분리, 5칸 고정, 중복 금지, 영문 효과 선택, 읽기 전용 수치와 Lv.1~10 입력, 보라색 빠른 선택 버튼을 요청했다.
- 원문의 stronger against Fire/Earth/Water/Light/Wind/Dark/Neutral은 요청에 따라 `속성에 유리`/`ELEM_P` 하나로 통합한다. 7종 합산은 하지 않는다. 원래 요리 이름은 데이터에만 보존하며 화면에 표시하지 않는다.
- `AGGRO`와 `AGGRO_MINUS`는 같은 어그로 효과 그룹으로 처리해 동시 중복 선택을 막는다.
- 처음 선택/빠른 선택의 기본은 Lv.10, 빠른 선택은 맨 위 첫 빈 칸에 넣는다. 선택된 버튼 재클릭은 해당 칸을 비운다. 5칸이 차도 선택된 버튼은 해제할 수 있다.
- 빠른 선택은 전투(CRIT/WATK/AMPR/속성에 유리), HP/MP/-어그로, 기본 스탯 순서의 2열 격자다. 효과 선택란 폭을 제한하고 CRIT/AMPR/WATK 표기를 사용한다.
- 제목 옆 길드 요리 버프는 기본 활성화다. 사용자 지정 수치인 MAXHP +1000, MAXMP +100을 적용하고 회색 작은 글씨로 표시한다. 마이룸 5칸과 별개다.

## 코드·저장 경계

- `assets/js/data/my-room-food.js`: 33개 통합 효과, 39개 원래 요리명, 원문 레벨별 전체 값, 연결 여부, 정규화.
- `assets/js/my-room-food-ui.js`: 고정 행, 영문 효과 선택, Lv.1~10, 읽기 전용 제공량, 빠른 선택. 기존 외부 버프/범용 옵션은 계속 수동 추가할 수 있다.
- `BuildDraft.myRoomFood`: `{id,level}` 또는 null 5개. 기존 schema v2의 선택 필드이며 요리 정보가 없는 저장은 빈 5칸으로 복원한다. 값·이름은 저장에 중복하지 않고 카탈로그에서 파생한다. 잘못된 ID/뒤쪽 중복은 빈 칸, 레벨은 정수 1~10으로 보정한다.
- `BuildDraft.guildFoodBuff`: schema v2 선택 boolean. 누락은 true, 명시 false는 해제로 저장·복원한다. Application에서 MAXHP/MAXMP 옵션을 한 번 합산한다. 외부 버프의 수동 입력값을 임의로 제거하지 않는다.
- Application에서만 음식 입력을 옵션으로 변환해 기존 계산 커널에 전달한다. STR/INT/VIT/AGI/DEX, ATK/MATK/WATK, CRIT, MAXHP/MAXMP/AMPR, 통합 ELEM_P를 연결한다.
- 그 외 보존 효과는 UI·저장만 지원한다. 계산/피격 시뮬레이션/획득 경험치·드랍 계산 등으로 연결하지 않는다.

## 실행 검증 (2026-09-11)

- 후속 UI/길드 수정: `npm run verify:r6`, `node tools/test-my-room-food.mjs`, `node tools/audit-stack-source-links.mjs --require-s1`, `node tools/verify-food-browser.mjs` 통과. Edge에서 요리명 미표시·재클릭 해제, 길드 기본 on·실제 HP 1000/MP 100 차이·off 저장/새로고침 복원·구형 저장 기본 on을 확인했다. 아래 R0 전체/Rust 기록은 최초 요리 구현 시 실행 결과이며 이번 후속 수정에서 반복하지 않았다.
- `node tools/test-my-room-food.mjs`: 33개 효과·39개 이름, 330개 레벨 사례, 중복/경계, 명시 Snapshot 입력, 보존 효과 미연결 통과.
- `npm run verify:r6`: 타입·계산/Application/BuildDraft/UI·저장 Snapshot/어댑터/Repository 계약 통과. 저장 테스트에 요리 슬롯 왕복 추가.
- `npm run verify:r1a`: 86개 classic script 로딩 순서/브라우저·Tauri URL 통과.
- `node tools/audit-stack-source-links.mjs --require-s1`: S1 427/427 통과.
- `npm run test:r0`: 70개 프로세스 종료 성공, 실제 69개 통과·Native 저장 E2E 1개 SKIP (`TORAM_E2E_CDP` 미설정).
- `cargo test --manifest-path src-tauri/Cargo.toml settings_repository`: 저장 단위 테스트 3개 통과.
- `node tools/verify-food-browser.mjs`: 실제 headless Edge에서 고정 5칸, 빠른 선택·첫 빈 칸 채우기, 중복 비활성화, 레벨 변경/상한, 읽기 전용, 새로고침 복원, STR/CRIT/MP/ELEM_P 계산 반영, 보존 효과 미연결, 구형 저장 복원, 390px 화면 범위 검증 통과. 데스크톱/모바일 스크린샷 육안 확인.
- 브라우저 검증은 `CODEX_PLAYWRIGHT_PATH`에 설치된 Playwright 경로를 지정한다. `FOOD_QA_DIR` 지정 시 스크린샷을 그 경로에 저장한다.
- 설치본 빌드·Native 실제 요리 저장 E2E·배포는 실행하지 않았다.
