# 개선 후보 10: 작은 상자 완전열거의 후보 목록 재사용

- 날짜: 2026-09-20. 기존 1~7·9번 변경을 보존했다.
- 구현: `src-tauri/src/d4_native_solver.rs`.
- 측정 원본: `d4-enumeration-lists-measurements.json`.

## 구현과 보존 계약

기존 `enumerate_box`와 `enumerate_box_parallel`은 재귀 진입마다 현재 부위의 후보 인덱스 Vec을 새로 만들고 하위 트리를 순회했다. 앞 부위의 후보를 바꿀 때 뒤 부위의 동일 목록을 반복 생성했다.

64조합 이하 상자에 진입할 때 `box_candidate_indices`로 네 부위의 목록을 한 번씩 준비하고, 재귀 함수에는 불변 목록 참조를 전달한다. 직렬 탐색·직렬 세션·병렬 탐색에서 같은 준비 함수를 사용한다. 트리의 왼쪽→오른쪽 순서와 부위 순서는 그대로이며, 스탯 합산·부동소수점 연산·후보 평가·동점 규칙은 변경하지 않는다.

상자당 목록 생성은 네 번이다. 예를 들어 부위별 후보 수 4×4×2×2의 기존 목록 생성 1+4+16+32=53회를 4회로 줄인다. 이는 코드 구조에서 계산한 호출 수로, 전체 실행의 할당 profiler 결과는 아니다. 1×1×1×1이나 1×1×1×64처럼 기존에도 네 번만 생성한 상자는 이 부분의 절감이 없다.

취소/deadline은 병렬 상자 진입 및 기존 재귀 경계에서 확인한다. 목록 준비는 64조합 이하에서만 수행하며 최대 후보 합은 67개다. 중간 중단 시 기존 부모 복원 계약을 유지한다. 캐시를 세션 밖에 남기지 않으며 checkpoint/입력 직렬화를 바꾸지 않는다. Native/checkpoint v5, split v3, 계산 v2를 유지한다.

## 검증

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 145개(40+40+12+53).
- 신규 테스트는 이전 트리 순회 방식의 열거기를 테스트 전용으로 보존해 새 방식과 비교한다. 1×1×1×1, 1×1×1×64, 64×1×1×1, 2×2×2×8, 4×4×2×2, 3×1×7×3을 검사한다. 입력 순서 반전, 동점, 소수 스탯·음수 HP 옵션을 포함하고 초기 최적값 없이 시작해 최종 선택·점수·평가 수·열거 수가 일치함을 확인했다. 마지막 경계 사례 보강 후 해당 테스트를 모든 Rust 대상에서 다시 실행해 통과했다.
- 기존 직렬/1~64스레드 exact·동점, 불균등 묶음 통계, 취소/deadline·오류 부모 복원·pause/resume·checkpoint 회귀 유지.
- `npm run test:r0`: PASS, 70/70 스크립트 집계. JS/Rust parity 1,920건·선검사 28,800회 포함. Native 저장 E2E는 CDP 미설정 SKIP.
- `npm run verify:r9`, Rust fmt, clippy `--all-targets -- -D warnings`, release parallel 빌드: PASS.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, 427/427.

실제 WebView/IPC E2E와 설치·배포는 미실행이다.

## 측정 조건

Windows / Ryzen 7 9800X3D, P6 물리 근거리 전체 후보 992/844/724/929. release binary를 변경 전후 각각 보존하고 스레드별 전→후, 후→전 순으로 각 두 번 새 프로세스를 실행했다. 빌드·테스트는 측정과 겹치지 않았다.

재현: `D4_SESSION_BENCH_MS=30000`, `D4_P6_THREAD=8` 또는 `16`, `D4_NATIVE_BINARY=<비교 binary>`, `D4_P6_REPORT=<json>`으로 `node tools/benchmark-d4-native-p6.mjs` 실행. 세션 wall은 JS 준비·UI/IPC를 제외한다. 다른 입력·장비의 성능이나 cold 10회 P95는 입증하지 않는다.

| 스레드 | 변경 전 평균 세션 wall | 변경 후 평균 | 단축 |
| --- | ---: | ---: | ---: |
| 8 | 4,196.785ms | 3,796.091ms | 9.5% |
| 16 | 3,379.701ms | 3,179.884ms | 5.9% |

전후 8회 모두 exact 14,097 및 동일 추천 ID를 반환했다. 양쪽 스레드 수에서 두 회차 모두 단축됐지만 단일 입력·각 두 번의 제한된 측정이다. 평가/방문 수의 소수 차이는 원본에 보존했고, peak working set은 전후 약 58~60MB였다.

최종 binary 16스레드 100ms 취소는 cancelled, solver 100ms / 외부 wall 290.665ms이며 exact false·인증 upper 제거 검사를 통과했다. 100ms deadline은 bounded, 세션 100.025ms, lower 14,089 / upper 18,759로 oracle 14,097을 포함했다.
