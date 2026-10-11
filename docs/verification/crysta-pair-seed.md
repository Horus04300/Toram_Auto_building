# 두 장비 동시 교환으로 Native 초기해 개선

2026-10-11. 변경 전은 이번 작업 시작 시점의 Native v16 소스·release 실행파일이다. 현재 제품 상태는 [handoff](../handoff/current-development-handoff.md), 입력·소스/실행파일 hash·100회 원시 결과·과정 로그는 [측정 기록](crysta-pair-seed-measurements.json)을 따른다. 기존 사용자 변경을 포함한 baseline을 별도로 보존해 비교했다.

## 변경과 정확성

[이전 과정 조사](crysta-search-process-trace.md)에서 초기 점수가 1,821,006인 채로 넓은 상자를 계속 분기하고, 첫 실제 열거까지 285,462개 노드를 방문했다. 한 장비씩 바꾸는 초기해 개선은 한쪽에서 대미지를 확보하고 다른 쪽에서 부족한 유틸리티를 보완하는 교환을 찾기 어렵다.

`src-tauri/src/optimization/solver.rs`에 작은 두 장비 교환 초기해 탐색을 추가했다. 기존 초기해·좌표 개선 다음에 실행한다.

- 현재 조합의 장비 하나를 각 후보로 교체해 실제 feasible 대미지를 평가하고 상위 16개를 고른다. 유틸리티 부족으로 단일 교체가 불가능한 후보도 연결할 수 있도록 기존 damage/utility heuristic 상위 8개씩과 현재 선택을 포함한다. ID 순서로 동점을 정하고 중복 인덱스를 제거한다.
- 장비별 최대 33개로 여섯 장비 쌍을 시험한다. 나머지 두 장비는 실제 incumbent에 고정하며 기존 `consider`로 모든 요구조건과 정확한 대미지를 평가한다. 최대 두 번 반복하고 점수가 개선되지 않으면 종료한다.
- 루트가 64조합 이하이거나 교체 가능한 장비가 두 개 미만이거나 feasible 초기해가 없으면 건너뛴다. 비용 상한은 두 번의 전체 단일 교체 검사와 `2 × 6 × 33²`회 쌍 교체다. 대규모 Pair frontier를 만들지 않는다.

이는 실제 feasible 하한만 강화한다. 후보 목록·raw 옵션·제약·안전 상한·median 트리·분기 정책을 유지한다. 초기해 풀 밖의 후보도 원래 exact 탐색에 남는다. `solve_exact`, `NativeSearchSession`, 독립 병렬 exact에 공통 적용했다. Worker 미리보기/fallback의 정책은 기존과 같다.

Native engine/checkpoint를 v17로 올려 이전 exact cache와 현재·과거 v4~v16 checkpoint를 구분한다. split policy v6·계산 v3·제품 v0.7.2·앱 저장 schema는 유지했다. 설치 앱 배포/재설치는 이번 작업에 포함하지 않는다.

## 전체 탐색 완료까지의 연산량

제품 compiler → Native client/service → 결과 복원과 최종 JS 재평가를 실행했다. 실제 저장 검방의 콤보 루브닐·단일 에투왈 잠금, 같은 입력의 평타, 루브닐 잠금 해제와 과거 회귀 두 입력을 사용했다. 과거 입력은 현재 사용자 빌드/다른 무기의 대표 사례로 해석하지 않는다. 평타와 과거 잠금 입력의 전체 원문도 측정 JSON에 저장했다.

AMD Ryzen 7 9800X3D / 16 logical threads / Node v24.17.0 / Windows release. 각 입력·정책마다 새 Node/Native 프로세스로 10회, 총 100회 순차 실행했다. 전후 순서를 번갈았고 같은 현재 JS를 사용했다. 테스트·빌드를 동시에 실행하지 않았다. 병렬 완료 순서에 따른 작은 카운터 차이가 있어 아래는 평균이다.

**실제 루브닐·잠금 해제 입력의 최적성 증명 완료까지:**

| 항목 | v16 | v17 | 감소 |
| --- | ---: | ---: | ---: |
| 방문 노드 | 3,143,964.4 | 2,812,028.8 | 10.56% |
| evaluations | 12,677,810.3 | 11,422,114.8 | 9.90% |
| 최종 점수 | 1,910,660.94 | 1,910,660.94 | 동치 |

새 초기해를 만드는 추가 평가도 포함한 순감소다. 약 1,255,696회의 평가를 절약했지만, **전체 원시 연산의 9.90%가 불필요했다는 뜻은 아니다.** evaluations는 기존 제품 카운터의 후보·상한·유틸리티 평가 호출 수다. 평가 종류별 비용은 다르고 준비·정렬·큐 연산은 이 분모에 포함하지 않는다.

100회 모두 exact 점수·전체 bestBuild·compiled/prepared 입력 hash가 같고, raw 옵션 합 및 최종 JS feasibility/점수가 일치했다. 루브닐 단일 잠금 1,753,977.72, 평타 67,120을 보존했다.

## 실행 과정에서 달라진 점

같은 잠금 해제 입력·1 worker·10,000묶음의 작업량 제한 trace를 비교했다. control 복사본과 instrumented 복사본의 결과·카운터 동치, 평가 회계, 최종 JS 재평가가 통과했다.

| 항목 | v16 | v17 |
| --- | ---: | ---: |
| B&B 시작 점수 | 1,821,006 | 1,891,701.18 |
| 초기해 평가 | 1,526 | 24,985 |
| 중단 시 미해결 상자/관측 최대 | 719,651 | 543,726 |
| 중단 시 최선 점수 | 1,851,405.06 | 1,891,701.18 |
| 중단 시 상한 | 2,135,461.80 | 2,135,461.80 |
| 방문 노드 | 517,604 | 656,693 |
| evaluations | 2,069,755 | 2,650,786 |

초기 점수가 높아져 미해결 큐가 **24.45%** 줄었고, B&B 열거 없이도 이전 제한 실행의 최선 점수를 넘겼다. 그러나 같은 묶음 수에서 재귀 lookahead가 196,278→335,843회로 늘었다. 묶음당 작업이 동일하지 않아 이 prefix의 방문/평가 수는 오히려 늘었다. 전체 작업 감소의 근거는 앞 절의 **exact 완료까지** 비교다. 이 trace는 여전히 bounded이며 최적성 증명이 아니다.

trace의 `seedImproved`는 단일 교체 순위를 구하는 임시 SearchState 개선도 센다. 이를 전역 incumbent 갱신 횟수로 사용하지 않는다. 전역 초기 점수는 batch 0의 `result.score`로 확인했다. 최종 B&B `incumbentImproved`는 0이다.

## 시간·메모리 Gate와 한계

시간은 원시 입력의 JS 컴파일·준비부터 Native 실행·결과 복원·최종 JS 재평가까지며 UI/WebView를 제외한다. 사용자의 과정 분석과 별도로 성능 변경 Gate를 검증했다. 이전 실험의 개선율을 합산하지 않는다.

| 입력 | Native 평균 ms 전→후 | 전체 평균 ms 전→후 | 전체 P95 ms 전→후 | Native peak MiB 전→후 |
| --- | ---: | ---: | ---: | ---: |
| 실제 루브닐·단일 잠금 | 180.3→180.1 | 812.6→815.2 | 825.2→853.0 | 25.91→25.88 |
| 실제 평타·단일 잠금 | 176.0→176.7 | 809.4→807.8 | 828.1→814.3 | 25.85→25.88 |
| 실제 루브닐·잠금 해제 | 1199.5→1058.0 | 2141.1→1995.5 | 2191.1→2055.2 | 57.58→57.89 |
| 과거 unlocked 회귀 | 508.2→510.2 | 1251.6→1253.7 | 1273.2→1299.6 | 49.41→49.34 |
| 과거 locked 회귀 | 68.8→68.6 | 640.2→635.1 | 652.5→649.8 | 22.31→22.45 |

잠금 해제 실제 입력은 Native 평균 11.80%, 전체 평균 6.80% 단축했다. 단일 잠금·과거 회귀는 연산/시간 변화가 작고 일부 평균/P95가 증가했다. 모든 입력에서 빨라졌다고 주장하지 않는다. 실제 듀얼 사용자 입력은 이번에 검증하지 않았다.

Native peak working set은 25ms 표본이며 Node/JS 메모리를 제외한 근사치다. 큐 감소를 전체 peak 메모리 절감으로 해석하지 않는다. 실제 잠금 해제 Native peak는 평균 약 0.31MiB 증가했다.

## 검증과 재현

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: 349개 PASS(공유 모듈의 bin별 중복 포함). 새 테스트는 단일 교체로 개선 불가/쌍 교체로 개선 가능한 256조합 oracle, 입력 역순, 직렬/병렬/세션 점수·동점 ID와 작은 문제/no-incumbent skip을 확인했다. 기존 coverage·상한 property·1~64 threads·cancel/deadline/checkpoint/pause/resume Gate도 유지했다.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: PASS.
- `npm run test:regression`: 76/76 PASS. 포함된 Native 저장 실기기 E2E는 `TORAM_E2E_CDP` 미설정 SKIP이며 통과로 해석하지 않는다.
- `npm run verify:architecture`, `node tools/verification/audit-stack-source-links.mjs --require-s1`: PASS, S1 427/427.
- `npm run ai:audit`, `git diff --check`: PASS. 현재 handoff 12,270 bytes로 12 KiB 제한을 만족했다.
- `npm run bench:optimization:build`로 최종 headless service를 빌드했다. 반복 비교 스크립트·입력·전후 소스/실행파일 hash는 측정 JSON의 `scripts`, `inputs`, `stamps`에 보존했다. 로컬 원본은 `src-tauri/target/mp-offense-bound/`에 있으며 MP 상한 실험은 최종 코드에서 제거했다.
- `node tools/benchmarks/trace-crysta-search.mjs build` 및 `run`: PASS. trace 전후 발췌는 측정 JSON의 `processTrace`다. 전체 trace 생성 경로는 재실행 시 덮어쓴다.
- `npm run bench:optimization -- --input tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json --repeats 1 --slice-ms 250 --output src-tauri/target/mp-offense-bound/resume-actual.json`: 6 slice/5회 재개 후 exact, 전체 조합·최종 JS 평가·소스 hash 동치 PASS. 재개 검사는 일반 cold 평균에 포함하지 않았다.

MP 제약으로 공격 상한을 추가 강화하는 별도 실험은 루트 선택 적용에서 실행량이 같았고, 선택 해제 시 해당 prefix 방문/평가가 증가해 폐기했다. 기존 상한 구현을 복원한 뒤 쌍 초기해만 최종 채택했다.
