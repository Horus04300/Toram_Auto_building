# D4 공유 묶음 메시지 최적화

- 날짜: 2026-09-16. 기준은 `d4-session-optimization.md`의 합산 배열화·재사용 풀·선택적 추가 분할까지 적용한 코드다.
- 측정 원본: `d4-shared-batch-measurements.json`. 기존 변경은 보존했다.

## 구현과 정확성 계약

세션의 작업 묶음은 기존처럼 스레드당 32노드다. 이전에는 각 노드마다 입력/결과 메시지를 보냈다. 이제 불변 노드 목록과 incumbent/counters/cancel/deadline을 `Arc<NodeBatch>` 하나로 공유하고, 작업자 수만큼 메시지를 보낸다. 작업자는 atomic 인덱스로 다음 노드를 하나씩 가져가며 결과를 모아 반환한다. 가득 찬 묶음의 각 방향 메시지는 256→8 또는 512→16개로 줄어든다.

작업 배분은 여전히 노드 단위다. 결과는 원래 입력 인덱스로 병합한다. 각 노드의 기존 취소/deadline 검사와 panic 포착, 오류 시 부모 frontier 복원은 유지한다. 빈 묶음·스레드 수보다 적은 노드·나누어떨어지지 않는 묶음에서도 누락/중복 없이 처리한다. 계산식·후보·bound·동점 규칙은 바꾸지 않았다.

실행 정책 변경에 따라 JS Native engine과 Rust checkpoint를 v4로 올렸다. v3 checkpoint는 거부하고 이전 캐시/continuation과 구분한다. 계산 버전 v2와 split policy는 유지한다.

## 성능 비교

Windows / Ryzen 7 9800X3D, P6 물리 근거리 전체 후보 992/844/724/929. Native 세션 경로, 새 프로세스, 30초 한도. 빌드/테스트와 동시에 측정하지 않았다. 각 스레드에서 전→후, 후→전 순서로 두 번씩 비교했다.

| 스레드 | 순서 | 기존 세션 wall | 공유 묶음 wall | 단축 |
| --- | --- | ---: | ---: | ---: |
| 8 | 전→후 | 6,709.852ms | 6,382.755ms | 4.9% |
| 8 | 후→전 | 5,853.808ms | 5,645.576ms | 3.6% |
| 16 | 전→후 | 4,690.606ms | 4,632.511ms | 1.2% |
| 16 | 후→전 | 4,723.011ms | 4,640.794ms | 1.7% |

모든 측정은 exact 14,097이며 같은 ID `weapon:도이+후빗||armor:알타달+칼레리프||additional:카나요간+칼레리프||special:저편의 잔영+칼레리프`를 반환했다. 평가 수는 8스레드 25,932,301 / 16스레드 25,932,305로 전후 동일하다. 세션 묶음 수도 각각 13,769 / 6,887로 동일하다. 이 개선은 탐색량보다 메시지 전달 비용을 줄인다.

세션 wall은 Native 준비를 포함하되 JS compile/Pareto·Tauri IPC·UI는 제외한다. 두 번씩의 단일 fixture 결과이며 전체 입력이나 cold 10회 P95 개선을 보장하지 않는다. CPU/exitCode의 기존 측정 한계 때문에 성공은 exact와 oracle 일치로 판단했다.

재현: release `d4_native_parallel` 빌드 후 `D4_SESSION_BENCH_MS=30000`, `D4_P6_THREAD=8` 또는 `16`, `D4_NATIVE_BINARY=<비교 binary>`, `D4_P6_REPORT=<json>`로 `node tools/benchmark-d4-native-p6.mjs` 실행.

### 채택하지 않은 고정 묶음

4개 또는 8개 노드를 한 작업자에 고정 배정하는 방식도 비교했다. 8스레드에서 반복적으로 느려져 제거했다. 16스레드에서도 일관된 이점이 없거나 작았다. 무거운 노드가 특정 묶음에 몰리는 부담을 피하기 위해 공유 묶음에서 개별 노드를 가져오는 방식을 채택했다. 고정 8개 실험의 첫 baseline 14.104초는 이후 baseline과 크게 달라 유리한 단축률 산출에 사용하지 않았다. 실패한 실험도 원본 JSON에 보존했다.

## 검증

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 118개(32+32+9+45, binary별 공유 모듈 실행 포함).
- 새 회귀: 1/2/8/16/64스레드, 0/1/7/31/33/65/257노드의 결과 순서·실행 횟수·사전 취소·만료 deadline. 기존 pool 재사용·오류 복구·pause/resume/checkpoint 회귀 유지.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, clippy `--all-targets -- -D warnings`, release parallel 빌드: PASS.
- `node tools/test-d4-native-exact-p4.mjs`: PASS, exhaustive oracle 동치.
- `node tools/test-d4-rust-native-parity.mjs`: PASS, 1,488개 계산 동치.
- `npm run verify:r9`: PASS, 하위 Gate 포함.
- `npm run test:r0`: PASS, 70개 스크립트 집계. Native client cache/resume 및 UI continuation 회귀 포함. 실제 Native 저장 E2E는 `TORAM_E2E_CDP` 미설정으로 SKIP이다.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, S1 427/427.

설치·배포·WebView/IPC E2E는 이번 작업 범위에서 실행하지 않았다.
