# D4 작업자별 통계 집계

- 날짜: 2026-09-17. 기준은 v0.7.0 소스의 공유 묶음 메시지 구현이다.
- 측정 원본: `d4-local-counters-measurements.json`.

## 변경

Native 세션 풀에서 평가·방문·상한 가지치기·제약 가지치기·완전열거·분할 횟수를 작업자 메시지별 `ParallelCounters`에 기록하고 메시지 완료 시 공유 카운터에 합산한다. 매 평가마다 모든 스레드가 같은 메모리를 수정하는 비용을 줄인다. 기존 평가 함수의 atomic 표현은 유지하지만 hot loop에서 해당 카운터에 쓰는 작업자는 하나뿐이다.

결과 전송 전에 합산하므로 coordinator가 묶음 완료 후 읽는 누적 통계는 같다. 취소/deadline 및 노드별 오류도 합산 경계를 지나며, 오류 시 부모 공간을 보존하는 기존 계약을 유지한다. incumbent와 취소 신호는 계속 공유한다. 단독 병렬 scheduler의 시간·steal 계측은 그대로다.

탐색 순서·후보·분할·bound·계산·진행 보고 시점은 변경하지 않았다. 내부 통계 저장 위치만 변경하므로 engine/checkpoint v4와 계산 v2를 유지한다.

## 측정

Windows / Ryzen 7 9800X3D, P6 물리 근거리 전체 후보 992/844/724/929, 새 프로세스. Native 세션 경로를 30초 한도로 실행했으며 측정 중 빌드/테스트를 실행하지 않았다.

| 스레드 | 실행 순서 | 기존 세션 wall | 변경 후 | 단축 |
| --- | --- | ---: | ---: | ---: |
| 8 | 전→후 | 7,033.454ms | 6,763.839ms | 3.8% |
| 8 | 후→전 | 6,632.959ms | 6,419.755ms | 3.2% |
| 16 | 전→후 | 4,911.238ms | 4,748.451ms | 3.3% |
| 16 | 후→전 | 5,101.019ms | 5,061.087ms | 0.8% |

모든 결과는 exact 14,097 및 동일 추천 ID다. 평가 수는 8스레드 25,932,301 / 16스레드 25,932,305로 전후 같고 방문·가지치기·묶음 수도 같다. peak working set은 전후 약 76.6~77.7MB 범위였다. CPU 표본 일부는 0으로 반환되어 속도 판단에 사용하지 않았다.

재현: release parallel bridge 빌드 후 `D4_SESSION_BENCH_MS=30000`, `D4_P6_THREAD=8` 또는 `16`, `D4_NATIVE_BINARY=<전/후 binary>`, `D4_P6_REPORT=<json>`를 설정해 `node tools/benchmark-d4-native-p6.mjs` 실행.

두 번씩의 단일 fixture 비교다. 세션 wall은 JS 준비·UI·IPC를 제외하며 전체 입력의 개선이나 cold 10회 P95를 입증하지 않는다.

## 검증

공유 묶음 회귀에 순차 평가와 병렬 평가의 여섯 통계 일치를 추가했다. 1/2/8/16/64스레드와 빈/불균등 크기의 입력에서 검증한다. 기존 exact·동점·취소·deadline·pause/resume·checkpoint·worker 오류 회귀를 유지한다.

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 118개(32+32+9+45).
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, clippy `--all-targets -- -D warnings`: PASS. release parallel bridge 빌드 PASS.
- `npm run test:r0`: PASS, 70개 스크립트 집계. Native exact oracle·잠금·parity 1,488건·client/resume 회귀 포함. Native 저장 E2E는 CDP 미설정으로 SKIP이다.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, 427/427.

실제 WebView/IPC E2E와 설치·배포는 미실행이다.
