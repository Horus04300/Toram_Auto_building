# 개선 후보 2: 우선순위 큐의 문자열 비교 제거

- 날짜: 2026-09-17. 사용자와 합의한 후보 목록의 **2번** 작업이다. 3번 평가 경로 준비와 4번 추가 분할 범위 조정은 이번 범위에 포함하지 않는다.
- 기준: 공유 묶음 메시지·작업자별 통계·자식 결과 지연 할당까지 반영한 코드.
- 원본 측정: `d4-priority-path-rank-measurements.json`.

## 구현과 순서 보존

CandidateTree를 만들 때 각 노드에 `usize` 숫자 순위를 준비한다. 이진 path에서 접두어인 부모는 모든 자손보다 앞서며, 0으로 시작하는 왼쪽 부분트리는 1로 시작하는 오른쪽 부분트리보다 앞선다. 따라서 부모→왼쪽→오른쪽 전위 순회가 기존 path 문자열의 사전식 순서다.

부모 순위가 r이고 왼쪽 후보 수가 m이면 왼쪽 루트는 r+1, 오른쪽 루트는 r+2m이다. 후보 m개를 가진 완전 이진 분할 부분트리에 2m−1개 노드가 있기 때문이다. 빈/단일 후보 루트에는 0을 부여한다. 순위는 해당 장비의 트리 내부에서만 사용하며, 같은 검색 문제의 네 장비 좌표끼리 비교한다.

`WorkItem::cmp`는 먼저 기존 `f64::total_cmp`로 상한을 비교한다. 동점이면 네 장비를 기존 순서대로 검사하되 path 대신 숫자 순위를 비교한다. 사전식으로 작은 path를 우선하는 방향도 유지한다. `PartialEq`에도 같은 숫자 비교를 사용해 Ord와 일치시킨다.

체크포인트에는 기존 path를 저장하며 복원 시 동일한 트리를 다시 만들어 순위가 재구성된다. path 문자열을 노드에서 삭제하거나 저장 형식을 바꾸지 않았다. 후보·계산·bound·분할·동점 순서가 동일하므로 engine/checkpoint v4를 유지한다.

## 검증 방법

새 회귀는 후보 0~65개의 균등/불균등 트리에서 모든 노드 쌍의 숫자 비교와 기존 문자열 비교를 대조한다. 각 트리에서 128개 네 장비 상자를 만들고 모든 상자 쌍 및 heap pop 순서를 기존 비교기로 확인한다. 상한에는 동점, 양수/음수 0, 양/음 무한대와 NaN을 포함한다.

기존 정확성·동점·취소/deadline·pause/resume·checkpoint 복원·1~64스레드 회귀를 함께 실행한다.

## 성능 측정 조건

Windows / Ryzen 7 9800X3D, P6 물리 근거리 전체 후보 992/844/724/929. Native 세션 경로, 새 프로세스, 30초 한도. 8/16스레드 각각 전→후 / 후→전 순서로 두 번씩 측정하며 빌드/테스트와 겹치지 않았다.

재현: release parallel bridge 빌드 후 `D4_SESSION_BENCH_MS=30000`, `D4_P6_THREAD=8` 또는 `16`, `D4_NATIVE_BINARY=<전/후 binary>`, `D4_P6_REPORT=<json>`로 `node tools/benchmark-d4-native-p6.mjs` 실행.

세션 wall은 JS 준비·UI·IPC를 제외한다. 단일 물리 fixture 결과이며 루브닐·마법·듀얼의 성능 향상이나 전체 입력의 cold 10회 P95 달성을 주장하지 않는다. CPU/exitCode 일부 표본은 기존 측정 한계가 있어 판정 근거로 사용하지 않는다.

| 스레드 | 순서 | 기존 세션 wall | 숫자 비교 | 단축 |
| --- | --- | ---: | ---: | ---: |
| 8 | 전→후 | 6,121.488ms | 5,602.413ms | 8.5% |
| 8 | 후→전 | 6,229.514ms | 5,499.683ms | 11.7% |
| 16 | 전→후 | 4,745.533ms | 4,190.651ms | 11.7% |
| 16 | 후→전 | 4,735.439ms | 4,266.770ms | 9.9% |

모두 exact 14,097과 같은 추천 ID `weapon:도이+후빗||armor:알타달+칼레리프||additional:카나요간+칼레리프||special:저편의 잔영+칼레리프`를 반환했다. 평가 수는 25,932,301~25,932,305회로 병렬 타이밍에 따른 소수 차이가 있다. 묶음 수는 8스레드 13,769 / 16스레드 6,887로 전후 같다.

변경 후 peak working set은 76.8~77.9MB였다. 변경 전 첫 8스레드 표본은 102.2MB, 나머지는 76.6~77.5MB여서 이를 일관된 메모리 감소로 해석하지 않는다. 숫자 순위는 트리 노드당 usize 하나를 추가한다.

## 검증 결과

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 121개(33+33+9+46). 새 순서 동치 회귀와 기존 세션/병렬 회귀 포함.
- fmt, clippy `--all-targets -- -D warnings`, release parallel bridge 빌드: PASS.
- `node tools/test-d4-native-exact-p4.mjs`: PASS, 소형 exhaustive oracle 동치.
- `node tools/test-d4-global-optimizer-stage2.mjs`: PASS, oracle 3,430 / solver 144 / bound 1,093.
- `node tools/test-d4-rust-native-parity.mjs`: PASS, 1,488개.
- `node tools/test-d4-native-client.mjs`, `node tools/test-d4-native-resume-ui-n5.mjs`: PASS.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, S1 427/427.

전체 R0/R9, 실제 WebView/IPC E2E, 설치·배포는 이번 변경에서 실행하지 않았다. 다음 합의된 후보는 **3번 입력에 맞춰 평가 경로 준비**이며 아직 구현하지 않았다.
