# 개선 후보 12: 유틸리티 조건의 단계별 조기 검사

- 날짜: 2026-09-21. 기존 1~7·9~11번을 보존했다.
- 구현: src-tauri/src/d4_native_evaluator.rs, src-tauri/src/d4_native_solver.rs.
- 측정 원본: d4-staged-utility-measurements.json.

## 구현과 보존 계약

기존에는 다섯 유틸리티 값을 모두 계산한 뒤 요구조건을 검사했다. 이제 HP→MP→듀얼 적용 전 AMPR→평타 CRIT→ASPD 값이 확정될 때 각 조건을 검사하고, 미달이면 뒤 단계와 피해 계산을 건너뛴다. VIT와 HP를 먼저 계산하고 INT는 MP 단계, STR·DEX·AGI는 ASPD 단계까지 미룬다. 이미 계산한 값은 통과 경로의 피해 계산에서 재사용한다.

기존 수식과 각 수식 내부 연산·floor·정수 변환·상한 순서는 그대로다. 요구조건의 None 해제와 f64 비교도 유지한다. MAXMP→AMPR 및 AMPR profile 보정은 완전히 계산한 뒤 검사하며, 평타 CRIT는 피해용 CRIT와 혼동하지 않는다. ASPD·피해 계산에 필요한 스탯을 임의로 생략하지 않는다.

초기해 후보, 완성 조합, 직렬/병렬 자식 envelope와 lookahead·shard 준비가 동일한 단계 검사를 사용한다. 불가능 루트의 피해 상한을 반환하는 계약과 일반 summary API는 전체 평가를 유지한다. 후보 삭제 기준·안전 상한·분할·동점·평가 시도 수 계약은 바뀌지 않는다. Native/checkpoint v5, split v3, 계산 v2를 유지한다.

## 검증

- cargo test --manifest-path src-tauri/Cargo.toml -q: PASS 152개(42+42+13+55).
- 새 회귀는 다섯 단계 각각에서 거부하고, 이후 단계 또는 피해 스탯을 읽으면 실패하도록 하여 실제 조기 종료를 확인한다.
- parity bridge는 기존 1,920개 JS/Rust 비교에 대해 좌표별 -0.5/동일/+0.5 요구조건 28,800회를 단계 API로 검증한다. 통과 경로의 전체 summary가 JS 참조와 일치하고, 탈락까지 읽은 각 값도 전체 평가 값과 일치해야 한다.
- Rust clippy --all-targets -- -D warnings 및 release parallel 빌드: PASS.
- npm run verify:r9: PASS. node tools/audit-stack-source-links.mjs --require-s1: PASS 427/427.

실제 WebView/IPC E2E와 설치·배포는 미실행이다.

## 측정 조건

Windows / Ryzen 7 9800X3D, P6 물리 근거리 전체 후보. 기본 입력과 HP 26,000/40,000 제한(다른 요구조건은 null)을 비교한다. 변경 전후 release binary를 보존하며 전→후, 후→전으로 각각 새 프로세스 2회 실행한다. 빌드·테스트와 측정은 겹치지 않는다.

D4_SESSION_BENCH_MS=30000, D4_P6_THREAD=8 또는 16, D4_NATIVE_BINARY=<대상>, D4_P6_REPORT=<json>으로 node tools/benchmark-d4-native-p6.mjs를 실행한다. HP 입력에는 D4_P6_REQUIREMENTS와 반대쪽 D4_P6_REFERENCE_BINARY를 지정하여 두 결과의 exact·점수·ID·upper 일치를 검사한다. 세션 wall은 JS 준비·UI/IPC를 제외하며, 다른 입력/장비 또는 cold 10회 P95를 입증하지 않는다.

| 입력 | 스레드 | 변경 전 평균 | 변경 후 평균 | 변화 |
| --- | ---: | ---: | ---: | ---: |
| basic | 8 | 4076.936ms | 4140.915ms | 1.6% 증가 |
| basic | 16 | 3028.140ms | 3079.297ms | 1.7% 증가 |
| hp26000 | 8 | 2772.265ms | 2788.998ms | 0.6% 증가 |
| hp26000 | 16 | 2298.114ms | 2269.080ms | 1.3% 단축 |
| hp40000 | 8 | 1577.973ms | 1542.619ms | 2.2% 단축 |
| hp40000 | 16 | 1349.216ms | 1288.144ms | 4.5% 단축 |

기본 exact 14,097, HP 26,000 exact 14,089, HP 40,000 exact 13,051이며 24회 모두 입력별 최종 ID·upper가 동일하다. 기본 입력은 평균 약 1.6~1.7% 증가했고 HP 26,000의 8스레드도 약 0.6% 증가했다. HP 40,000은 두 회차·두 스레드 수 모두 단축했지만 각 2회뿐이므로 일반적인 속도 향상을 주장하지 않는다. 유틸리티 조기 탈락 입력을 위한 최적화로 채택하며 통과 위주 입력의 작은 회귀는 남긴다. 전체 메모리·평가 수는 측정 원본을 따른다. CPU 시간 0인 표본은 미수집으로 해석한다.

- npm run test:r0: PASS 70/70 스크립트. Native 저장 E2E는 CDP 미설정 SKIP. fmt --check, git diff --check, npm run ai:audit: PASS.
- 최종 16스레드 100ms 취소: cancelled, solver 100ms / 외부 wall 293.244ms, exact false·upper 제거 검사 통과.
- 100ms deadline: bounded, 세션 100.1107ms, lower 14089 / upper 18909로 oracle 14,097 포함.
