# 개선 후보 9: 작업자 내부 통계의 atomic 연산 제거

- 날짜: 2026-09-20. 기존 1~7번 변경을 보존하고 9번만 구현했다.
- 구현: `src-tauri/src/d4_native_solver.rs`.
- 원본 측정: `d4-local-plain-counters-measurements.json`.

## 변경과 유지한 계약

기존 작업자 메시지별 `ParallelCounters`는 공유 위치 경합을 줄였지만 평가마다 atomic 증가 연산을 수행했다. Native 세션 `NodePool`의 작업자 내부에서는 여섯 필드만 가진 `LocalSearchCounters`를 사용한다. 평가·방문·상한 제거·제약 제거·완전열거·분할 횟수를 일반 `u64`로 누적한다. 재귀 함수에 `&mut`로 전달하여 수정 권한을 한 작업자가 독점하고, 같은 전용 카운터를 동시에 수정하지 못하도록 한다.

`SearchCounters`의 정적 디스패치로 동일한 탐색 함수가 전용 카운터와 공유 atomic 카운터를 지원한다. 런타임 분기나 trait object를 추가하지 않는다. 독립 병렬 scheduler는 기존 공유 atomic 통계를 유지한다. 전역 최적값·취소 신호·다음 노드 점유도 기존 atomic을 유지한다.

작업자 메시지 완료 시 여섯 값을 기존 공유 카운터에 합산한 후 결과를 전달한다. 합산 단계에는 atomic이 필요하다. 오류·panic을 포착한 노드도 기존 합산 경계를 지나고, coordinator의 부모 복원·오류 반환 정책은 그대로다. `wrapping_add`로 atomic 증가의 정수 오버플로 의미도 보존한다.

후보·상한·계산식·분할·동점·통계 집계 의미·checkpoint/진행 스키마를 바꾸지 않아 Native/checkpoint v5, split v3, 계산 v2를 유지한다. 8번 성능 회귀 원인 분석 및 10~13번은 이번 범위에 포함하지 않았다.

## 검증

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 142개(39+39+12+52).
- 기존 `shared_messages_cover_ragged_batches_in_input_order`가 실제 풀의 비원자 누적·합산과 atomic 참조 경로의 여섯 통계를 비교한다. 1/2/8/16/64스레드, 빈/불균등 묶음, 취소/deadline 및 결과 순서 검사를 유지한다.
- 신규 테스트는 여섯 카운터 모두 `u64::MAX`에서 증가할 때 atomic과 같은 0으로 순환하고, 후속 값이 공유 통계로 정확히 합산되는지 검사한다.
- 기존 오류 시 부모 보존, exact·동점, pause/resume·checkpoint, 대기 시간 제외 회귀 통과.
- `npm run test:r0`: PASS, 70/70 스크립트 집계. parity 1,920건·선검사 28,800회 포함. Native 저장 E2E는 CDP 미설정 SKIP.
- `npm run verify:r9`, Rust fmt, clippy `--all-targets -- -D warnings`, release parallel 빌드: PASS.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, 427/427.

실제 WebView/IPC E2E와 설치·배포는 미실행이다.

## 측정 조건

Windows / Ryzen 7 9800X3D, P6 물리 근거리 전체 후보 992/844/724/929. 변경 전후 release binary를 보존하고 각 스레드에서 전→후, 후→전 순으로 각각 두 번 새 프로세스를 실행했다. 빌드/테스트를 측정과 겹치지 않았다.

재현: `D4_SESSION_BENCH_MS=30000`, `D4_P6_THREAD=8` 또는 `16`, `D4_NATIVE_BINARY=<비교 binary>`, `D4_P6_REPORT=<json>`으로 `node tools/benchmark-d4-native-p6.mjs` 실행. 세션 wall은 JS 준비·UI/IPC 시간을 제외한다. 다른 입력·장비의 개선이나 cold 10회 P95 달성을 입증하지 않는다.

| 스레드 | 변경 전 평균 세션 wall | 최종 변경 후 평균 | 변화 |
| --- | ---: | ---: | ---: |
| 8 | 4,007.513ms | 3,965.014ms | 1.1% 단축 |
| 16 | 3,042.949ms | 2,987.557ms | 1.8% 단축 |

8회 모두 exact 14,097과 동일 추천 ID를 유지했다. peak working set은 전후 약 58~59MB였다. 8스레드는 한 회차에서 느려졌고, 16스레드는 두 회차 모두 빨랐지만 평균 개선 폭이 작다. 반복 수가 적어 안정적인 전체 성능 향상으로 단정하지 않는다. 이전 6·7번의 회귀가 해소됐다고 주장하지 않는다.

첫 `Cell<u64>` 구현은 별도 전후 비교에서 16스레드가 약 5.8% 느려져 폐기했다. 최종 구현은 독점 `&mut` 참조를 사용하는 일반 `u64`다. 중간 실험도 원본 JSON에 보존했다. 시간 차이의 기계어 수준 원인을 확정한 것은 아니다.

최종 binary의 100ms 취소는 cancelled, solver 100ms / 외부 wall 280.393ms이며 exact false·인증 upper 제거를 확인했다. 100ms deadline은 bounded, 세션 100.066ms, lower 14,089 / upper 18,729로 oracle을 포함했다.
