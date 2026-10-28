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

- npm test: 변환/ID·단위·속성·이벤트·저장·실데이터 WASM oracle.
- node tools/tests/optimization/test-elemental-option-parity.mjs: JS/Rust432사례와 signed i16 전체 범위/기초 스탯 경계·소수 파싱.
- npm test: 타입·Application/저장/UI·실행 경계.
- npm test: 현재 분류된 회귀. TORAM_E2E_CDP 없는 개별 Native 저장 검사는 SKIP이다.
- 두 Cargo manifest의 fmt/test/clippy, node tools/build-wasm.mjs, source/web/desktop entry 검사.
- Chrome verify-web-browser·verify-session-restore-browser: 개발 루트와 웹 하위 경로, PC/모바일, 실제 Worker, JSON/새로고침·탭 재열기. Chrome과 CODEX_PLAYWRIGHT_PATH를 사용한다.
- node tools/verification/audit-ai-context.mjs, git diff --check, S1 --require-s1.

피격·도움·보상 사건 소비와 현재 서버 이벤트 캘린더·실전 전투 결과는 검증하지 않았다. METEOR_RES/SUCTION_RES/HELP_INVINCIBILITY/STOP_FLINCH/PET_EXP/GEM_DUST_DROP은 보존/미계산으로 유지한다. 사용자 보류 범위의 피격 시뮬레이션과 콤보 후속을 구현하지 않았다.

## 후보·상한 계약

원시 비례 좌표가 같은 후보끼리만 비교하고 독립적인 HP/공속 투영을 보존한다. affine 상한에는128×f32 epsilon×항별 절댓값 합의 오차와0 방향 절삭 완화를 포함한다. f32 overflow는 plan fallback이다. signed i16·수동 격자 밖 소수·양/음 기초 스탯·상쇄의 부분공간 property를 검사한다. 실제 성능 비교는 동일 입력·출력·계측 경계와 새 프로세스 반복을 요구한다.

보존되지만 소비가 미계산인 키는 데이터 매핑과 별도다. 명중/회피·DEF/MDEF·피해 저항/배리어·추격·자연 회복·쿨다운·어그로·경험치/드롭이 포함된다. 미연결0은 장비 데이터 매핑의 의미이며 전투 효과 계산 완료가 아니다. 식 추출은 equipment-option-formulas.md, 마지막 통합 검사는 handoff를 따른다.
