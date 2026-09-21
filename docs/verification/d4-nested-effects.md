# 개선 후보 13: 중첩 고정 효과의 사전 준비

- 날짜: 2026-09-21. 기존 1~7·9~12번을 보존했다.
- 구현: src-tauri/src/d4_native_evaluator.rs. JS 비교: tools/test-d4-rust-native-parity.mjs.
- 측정 원본: d4-nested-effects-measurements.json.

## 구현과 보존 계약

PreparedContext가 입력 준비 시 다음 효과를 형식화한다.

- AMPR passive/active 후보: percent, multiplier, flat과 동점 ID 문자열. 매 평가의 중첩 JSON 조회와 ID 문자열 생성을 없앤다. 순차 passive 적용·각 floor·최대 active 선택과 동점 비교는 유지한다.
- 발도→ATK 변환: 해당 변환의 계수 목록. 원래 순서대로 적용하며 중복 효과를 합치지 않는다.
- 피해 배율: skill/passive/active/combo 네 값과 기존 누락·null·형식 오류의 기본값. 단계마다 피해를 내리는 기존 순서를 유지하며 배율끼리 미리 곱하지 않는다.
- skillStats: 고정 기본 스탯 값 또는 후보에 따라 변하는 총 스탯의 인덱스, ratio, 적용 대상. 원래 항목 순서대로 곱셈·덧셈하며 여러 항을 합치거나 정렬하지 않는다. 알 수 없는 target은 기존처럼 적용하지 않고, 알 수 없는 stat은 0으로 해석한다.

원본 JSON은 그대로 직렬화하며 복원할 때 파생 캐시를 다시 만든다. 후보별 AMPR·스탯·피해를 고정값으로 캐시하지 않는다. 일반 Value 평가 경로를 비교 기준으로 유지한다. 후보·제약·상한·분할·동점 정책 변경이 아니므로 Native/checkpoint v5, split v3, 계산 v2를 유지한다. AMPR/스킬 등의 게임 규칙이나 수치는 추가하지 않았다.

## 검증

- cargo test --manifest-path src-tauri/Cargo.toml -q: PASS 156개(43+43+14+56).
- 신규 Rust 회귀: 원본 JSON/준비 객체/직렬화 후 복원 결과 일치. 누락·null·잘못된 타입, 소수·음수 보정, AMPR active 동점, 중복 변환, 고정·동적 skillStats 순서 포함. AMPR은 음수·소수·큰 값과 부호 있는 0의 비트도 원본과 비교한다.
- npm run test:r0: PASS 70/70 스크립트. Native 저장 E2E는 TORAM_E2E_CDP 미설정 SKIP.
- 전체 회귀 뒤 JS 중첩 효과 18개를 보강하고 node tools/test-d4-rust-native-parity.mjs 재실행: PASS 1,938개(기존 1,488 + 평가 계획 432 + 중첩 효과 18). 5개 유틸리티 × 3개 경계 = 29,070회 조건 검사도 포함한다.
- npm run verify:r9, Rust fmt --check, clippy --all-targets -- -D warnings, release parallel 빌드: PASS.
- node tools/audit-stack-source-links.mjs --require-s1: PASS 427/427.

실제 WebView/IPC E2E와 설치·배포는 미실행이다.

## 측정 조건

Windows / Ryzen 7 9800X3D, 기본 P6 물리 근거리 전체 후보 992/844/724/929. 이전 release binary를 보존하고 스레드별 전→후, 후→전으로 각 2회 새 프로세스를 실행한다. 빌드·테스트는 측정과 겹치지 않는다.

D4_SESSION_BENCH_MS=30000, D4_P6_THREAD=8 또는 16, D4_NATIVE_BINARY=<대상>, D4_P6_REPORT=<json>으로 node tools/benchmark-d4-native-p6.mjs 실행. 세션 wall은 JS 준비·UI/IPC를 제외한다. 기본 입력에는 복잡한 AMPR/skillStats 효과가 없으므로 이 측정은 기본 경로의 비용 변화이며 효과가 많은 실제 빌드의 speedup을 뜻하지 않는다. 복잡한 효과는 정확성 검증만 했다. 다른 입력/장비·cold 10회 P95는 미검증이다.

| 스레드 | 변경 전 평균 | 변경 후 평균 | 변화 |
| --- | ---: | ---: | ---: |
| 8 | 4183.623ms | 4210.943ms | 0.7% 증가 |
| 16 | 3210.238ms | 3151.209ms | 1.8% 단축 |

8회 모두 exact 14,097 및 동일 추천 ID를 반환했다. 16스레드는 두 회차 모두 단축, 8스레드는 한 번 증가·한 번 단축이다. 작은 차이와 제한된 반복이므로 안정적인 전체 성능 향상으로 단정하지 않는다. 전체 peak working set은 약 55~57MiB이며 원본 수치를 보존했다.

100ms 취소는 cancelled, solver 100ms / 외부 wall 293.622ms, exact false·upper 제거 검사 통과. 100ms deadline은 bounded, 세션 100.0865ms, lower 14089 / upper 18750로 oracle 14,097 포함.

npm run ai:audit와 git diff --check: PASS.
