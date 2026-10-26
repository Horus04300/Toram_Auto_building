# 아이템 옵션 계산 연결 검증 기록

2026-10-26 작업 기록. 현재 기능·릴리스 판정은 current-development-handoff.md를 따른다.

## 원본과 변환

releaseC e99f6b32의 items.connected.json(SHA256 1e360559738f04313b522096107d327c8d8d99bb532ddd7d12ef650b41a19820)을 그대로 사용했다. 매핑 scope 제한11개를 해제하고 누락 비례8개·scalar6개를 등록했다. cap65 무기 속성과 cap114 이벤트 조건은 일반 스탯으로 만들지 않고 별도 메타데이터/조건으로 연결했다. cap53~59의 registryUnit은 percent다.

당시 발행 결과: 11,749개, scalar 연결16,333개, 장비 옵션 연결7,380개, 고정 버프 소모품212개, 조건595개. 미연결646개는 소모품 사용 명령612개·시나리오 젬22개·아바타 스킬 참조12개였다. weapons/armor/additional/special/crystas의 미연결 옵션은0개다. 이것은 옵션 키 커버리지이며 피격·보상·추격 등 모든 효과 소비 완료를 뜻하지 않는다.

## 계산과 저장

- 대상별 피해7종, 무기/화살 속성, 조건부 속성, 고정 스킬 속성 및 targetAdvantage를 연결했다. 대상 속성을 선택/자동 입력하고 저장한다.
- cap166~175는 원본별 tenths 복원 후 기초 스탯을 참조해 float32 순서 합산·1회 절삭한다. signed i16 전체 범위와 상쇄 경계를 검사한다.
- Rust JSON은 float_roundtrip으로 실제 저장 소수1.3499999999999999의 비트를 유지한다.
- 이벤트 장비3종은 서버 활성 상태 대신 명시적 체크박스를 사용한다. false 이후 종료·앞선 옵션 보존·장비 조건으로 marker 건너뛰기를 검사했다.
- 앱 진입점에서 StatRegistry를 먼저 로드한다. 기존 누락은 원본 옵션을 불러온 뒤 계산할 때 드러났고 Chrome에서 재현/수정했다.
- 계산 v5·solver/checkpoint v25·후보 투영 v3으로 이전 exact 캐시와 재개 상태를 분리한다.

정적 디컴파일53개 함수와 원시 상수/해시는 data/sources/toram-items/native-option-calculation/README.md에 보존했다. 실행 중인 게임에 연결하지 않았다.

## 검증 명령

- npm run items:test: 변환/ID·단위·속성·이벤트·저장·실데이터 WASM oracle.
- node tools/tests/optimization/test-elemental-option-parity.mjs: JS/Rust432사례와 signed i16 전체 범위/기초 스탯 경계·소수 파싱.
- npm run verify:architecture: 타입·Application/저장/UI·실행 경계.
- node tools/run-regression-suite.mjs:80fixture. localhost 차단3건은 같은 스크립트를 샌드박스 밖에서 재실행해 통과, Native 저장E2E1건은 TORAM_E2E_CDP가 없어 SKIP.
- 두 Cargo manifest의 fmt/test/clippy, npm run wasm:build, source/web/desktop entry 검사.
- Chrome verify-web-browser·verify-session-restore-browser: 개발 루트와 웹 하위 경로, PC/모바일, 실제 Worker, JSON/새로고침·탭 재열기. Browser plugin 미제공으로 기존 Playwright 사용.
- npm run ai:audit, git diff --check, S1 --require-s1.

피격·도움·보상 사건 소비와 현재 서버 이벤트 캘린더·실전 전투 결과는 검증하지 않았다. METEOR_RES/SUCTION_RES/HELP_INVINCIBILITY/STOP_FLINCH/PET_EXP/GEM_DUST_DROP은 보존/미계산으로 유지한다. 사용자 보류 범위의 피격 시뮬레이션과 콤보 후속을 구현하지 않았다.

## 추천 정확성·성능 재검증

가변 비례를 이유로 전체 affine plan/후보 투영을 비활성화하는 중간 구현은 웹 기존10초 exact Gate에서 bounded가 되어 채택하지 않았다. 최종 구현은 원시 비례 좌표를 동일하게 유지한 후보끼리만 비교하고, 독립적인 HP/공속 투영을 보존한다. affine 상한에는128×f32 epsilon×항별 절댓값 합의 오차와0 방향 절삭 완화를 포함한다. f32 overflow 영역에는 plan fallback을 유지한다. signed i16 경계·수동 격자 밖 소수·양/음 기초 스탯·상쇄의 부분공간 property를 추가했다.

최종 Rust99테스트와 실제 WASM 독립40완전탐색 score/ID 사례가 통과했다. 후보 투영은121context/5,430완성 조합/332교체 비교를 통과했다. Chrome의 기존26min-revenir fixture는 중단/재개 후 exact, 반복3회 모두 exact였다. 준비+탐색+JS 재평가 총883/794/958ms, 정밀203/144/220ms, 점수1,149,067.74로 재평가와 일치했다. 이것은 해당 입력의3회 측정이며 모든 입력10초나 P95를 보증하지 않는다.

보존되지만 실제 소비가 미계산인 키는 총62종이다. 기존 명중/회피·DEF/MDEF·피해 저항/배리어·추격·자연 회복·쿨다운·어그로·경험치/드롭 계열을 포함하며 이번 정적 옵션 연결로 지원 상태를 바꾸지 않았다. 미연결0은 장비 데이터 매핑의 의미다. 사용자에게 모든 전투 효과 계산이 끝났다고 보고하면 안 된다.
