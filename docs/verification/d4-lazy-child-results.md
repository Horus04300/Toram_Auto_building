# D4 생존 자식 결과의 지연 할당

- 날짜: 2026-09-17. 기준은 `d4-local-counters.md`의 작업자별 통계 집계까지 반영한 코드다.
- 측정 원본: `d4-lazy-child-results-measurements.json`.

## 구현

병렬 노드 확장에서 자식 결과 Vec를 분할 직후 최대 자식 수로 할당하던 부분을 빈 Vec로 시작하도록 변경했다. 자식이 모두 안전 상한/요구조건에 의해 제거되면 결과 버퍼를 할당하지 않는다. 생존한 자식 또는 손자가 생기면 기존 push/extend가 공간을 확보한다.

후보·상한·평가 순서·통계·분할·동점 정책은 같다. 중단된 부모 재큐잉과 worker 오류 복구도 유지한다. 결과 버퍼의 메모리 할당 시점만 바꾸므로 Native engine/checkpoint v4 및 계산 버전 v2를 유지한다.

먼저 시도한 `WorkItem` 참조 대여는 8스레드 단축률 -0.7%~+1.1%, 16스레드에서는 약 0.7~2.1% 느려져 일관된 개선이 없었다. 해당 변경은 원복했고 측정은 보존했다. 최종 코드에는 결과 Vec 지연 할당만 추가했다.

## 측정 조건

Windows / Ryzen 7 9800X3D. P6 물리 근거리 전체 후보 992/844/724/929, Native 세션 경로, 30초 한도. 전→후 / 후→전 순서로 각 두 번 새 프로세스에서 비교했다. 측정 중 빌드/테스트는 실행하지 않았다.

재현: release parallel bridge 빌드 후 `D4_SESSION_BENCH_MS=30000`, `D4_P6_THREAD=8` 또는 `16`, `D4_NATIVE_BINARY=<전/후 binary>`, `D4_P6_REPORT=<json>`를 설정해 `node tools/benchmark-d4-native-p6.mjs` 실행.

세션 wall은 JS 준비·UI·IPC를 제외한다. 단일 fixture의 작은 차이이므로 전체 입력의 개선이나 cold 10회 P95 달성을 주장하지 않는다. CPU/exitCode 일부 표본은 기존 측정 한계가 있어 성능/성공 판정에 사용하지 않는다.

| 스레드 | 순서 | 기존 세션 wall | 지연 할당 | 단축 |
| --- | --- | ---: | ---: | ---: |
| 8 | 전→후 | 6,007.896ms | 5,910.995ms | 1.6% |
| 8 | 후→전 | 6,184.767ms | 6,090.000ms | 1.5% |
| 16 | 전→후 | 4,580.784ms | 4,462.354ms | 2.6% |
| 16 | 후→전 | 4,725.368ms | 4,596.372ms | 2.7% |

모두 exact 14,097 및 동일 ID `weapon:도이+후빗||armor:알타달+칼레리프||additional:카나요간+칼레리프||special:저편의 잔영+칼레리프`를 반환했다. 평가 수는 25,932,301~25,932,305회로 병렬 타이밍에 따른 소수 차이가 있다. peak working set은 전후 약 76.6~77.7MB로 뚜렷한 감소가 없었다. 메모리 상주량 감소보다 반복 할당 회피를 위한 변경이다.

## 검증

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 118개(32+32+9+45). 기존 분할 coverage·동점·1~64스레드·통계 집계·취소/deadline·checkpoint·worker 오류 회귀 포함.
- fmt `--check`, clippy `--all-targets -- -D warnings`, release parallel bridge 빌드: PASS.
- `node tools/test-d4-native-exact-p4.mjs`: PASS, 소형 oracle 동치.
- `node tools/test-d4-rust-native-parity.mjs`: PASS, 1,488건.
- `node tools/test-d4-native-client.mjs`, `node tools/test-d4-native-resume-ui-n5.mjs`: PASS.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, S1 427/427.

이번 변경은 결과 버퍼 할당만 바꾸므로 전체 R0/R9는 반복하지 않았다. 실제 WebView/IPC E2E와 설치·배포는 미실행이다.
