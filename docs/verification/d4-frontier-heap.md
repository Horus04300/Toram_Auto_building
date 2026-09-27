# D4 큰 frontier의 큐 꺼내기 최적화

2026-09-23. `d4-slow-input-profile.md`에서 확인한 중앙 큐 pop 병목을 대상으로 한다.

## 변경과 유지 계약

`NativeSearchSession`의 frontier를 표준 이진 BinaryHeap에서 전용 4진 최대 힙 `WorkHeap`으로 바꿨다. 인접한 자식 4개 중 우선순위가 가장 높은 항목을 고르므로, 큐가 클 때 루트부터 내려가는 단계와 떨어진 메모리 위치를 읽는 횟수가 줄어든다. unsafe 코드나 추가 의존성은 없다.

`WorkItem` 크기와 비교 함수는 그대로다. 안전 상한의 total_cmp, 동점의 네 트리 path_rank 순서를 유지한다. 평가식·상한·후보 삭제·초기해·분할·작업 묶음 크기는 바꾸지 않았다. 변경은 Native 세션 frontier의 내부 저장 구조에 한정되며, 직렬 참조 solver와 별도 shard scheduler의 BinaryHeap은 유지한다.

체크포인트는 여전히 미해결 항목의 upper와 paths를 직렬화한다. 저장 배열의 물리적 순서는 달라질 수 있지만 복원한 큐에서 꺼내는 우선순위는 같다. Native/checkpoint v5, split v3, evaluator v2를 유지한다. 작업 실패·deadline·cancel 시 부모를 되돌리는 경로도 같은 큐 API를 사용한다.

## 정확성 검증

- 기존 `numeric_path_order_matches_lexical_heap_order`에 표준 BinaryHeap과 전용 힙의 혼합 삽입/삭제·일괄 추가·peek·빈 큐·재삽입 비교를 추가했다. 크기 0~65의 불균등 트리와 동점·중복·±0·무한대·기존 NaN total order를 포함한다.
- `cargo test --manifest-path src-tauri/Cargo.toml`: **156개 통과**. 기존 1~64작업자 동점/exact, 체크포인트 복원, 취소/deadline 재삽입, 작업자 실패 시 frontier 보존 검사를 포함한다.
- `npm run test:r0`: **70/70 통과**. JS oracle·상한·JS/Rust parity 1938개·잠금·세션 연결 등을 포함한다. 실제 Native 저장 E2E는 `TORAM_E2E_CDP` 미설정으로 **SKIP**이다.
- `npm run verify:r9`, `node tools/audit-stack-source-links.mjs --require-s1`: 통과, S1 **427/427**.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo clippy --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`, `node --check tools/benchmark-d4-frontier-heap.mjs`, `npm run ai:audit`, `git diff --check`: 통과.
- 실제 UI E2E·설치·배포는 실행하지 않았다. 모든 입력의 10초 exact를 주장하지 않는다.

## 성능 측정 방법

- 동일 PC(Ryzen 7 9800X3D, 논리 16개), Windows 10.0.26200, Node 24.17.0. 16작업자·120초 예산, 새 프로세스마다 exact 완료까지 측정한다.
- 기준 제품 소스: `206c5f61757e0d3acf320cdb6c452e15ca368fba`. 변경 전후 모두 `profile-d4-slow-inputs.mjs build`의 control bridge를 사용한다. 초당 최대 1회 progress snapshot만 있고 구간 타이머는 없다.
- 변경 전 control.exe를 `src-tauri/target/heap-audit/before.exe`, 변경 후를 `after.exe`로 보존했다. `benchmark-d4-frontier-heap.mjs`는 같은 준비 입력을 두 바이너리에 전달하고 score/build ID/upper 일치를 검사한다.
- 첫 파일럿은 루브닐 32.63→23.33초, 듀얼 14.73→13.03초였다. 채택 판단에는 별도의 3회 반복을 사용한다. 반복별 실행 순서는 before/after, after/before, before/after다. 측정 중 다른 빌드나 테스트는 실행하지 않았다.
- Native 세션 벽시계 시간과 프로세스 CPU·working set을 함께 저장한다. JS 후보 준비, UI/IPC는 제외하며, 이 변경은 준비 단계를 수정하지 않는다. 이전 측정 문서의 시간과 섞어 개선율을 계산하지 않는다.

## 재현 명령

준비 입력은 `audit-d4-performance-regressions.mjs prepare`, 루브닐은 `benchmark-d4-native-p6.mjs`의 `D4_P6_REVENIR=1` export로 만든다. 변경 전후 소스 각각에서 `profile-d4-slow-inputs.mjs build`로 만든 control.exe를 위 before/after 이름으로 보존한 뒤 실행한다.

```powershell
node tools/benchmark-d4-frontier-heap.mjs
```

기본값은 루브닐·듀얼·기본·HP40000·마법 입력 각 3회다. `D4_HEAP_FIXTURES`, `D4_HEAP_REPEATS`, `D4_HEAP_REPORT`로 별도 검증 입력·반복·출력 파일을 지정할 수 있다. 각 그룹 16개 샘플의 `*-oracle.json`은 JS 완전 탐색 점수/ID도 함께 검사한다.

## 채택 결과

각 입력·버전 3회씩, 총 30회 모두 exact 점수·최적 조합 ID·upper가 일치했다. 아래는 Native 세션 시간 중앙값이다.

| 입력 | 변경 전 | 변경 후 | 시간 감소 |
| --- | ---: | ---: | ---: |
| 루브닐 | 31.528초 | 22.725초 | **27.9%** |
| 듀얼 | 14.947초 | 12.722초 | **14.9%** |
| 기본 | 2.906초 | 2.700초 | 7.1% |
| HP 40000 | 1.168초 | 1.078초 | 7.7% |
| 마법 | 0.712초 | 0.682초 | 4.2% |

루브닐은 3회 모두 빨라졌으며 평가 횟수는 약 1억 7355만 회로 유지됐다. 병렬 incumbent 공유 시점에 따른 소폭 횟수 차이는 있으나 후보를 삭제하거나 증명을 생략해서 얻은 개선은 아니다. 마법의 작은 차이는 반복 편차와 가까우므로 큰 성능 향상으로 일반화하지 않는다. 측정에 따라 전용 4진 힙을 Native 세션에 채택한다.

관측 peak working set은 루브닐 변경 전 456~614 MiB, 후 409~605 MiB로 변동이 컸고 중앙값은 오히려 510→602 MiB였다. 이 측정으로 메모리 절감을 주장하지 않는다. 듀얼은 양쪽 약 164 MiB, 기본 56 MiB, HP 제한 43 MiB, 마법 30 MiB였다. 항목 크기는 유지했지만 실제 OS working set의 동일성이나 새 메모리 상한을 보장하지 않는다.

5입력의 그룹당 16개 JS oracle(각 65,536조합)과 변경 전후 총 10회 대조도 통과했다. 이는 전체 입력의 JS 완전 탐색은 아니다. 상세 결과·바이너리/입력/solver 해시·환경·진행 값은 `d4-frontier-heap-measurements.json`에 보존했다.
