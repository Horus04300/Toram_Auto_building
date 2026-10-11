# 자식 감소폭을 반영한 Native 분기 우선순위

2026-10-07. 현재 제품 판정은 `../handoff/current-development-handoff.md`, 전후 수치와 소스/바이너리 hash는 [측정 원본](crysta-branch-priority-measurements.json)을 따른다. baseline은 직전 Native v14 제품이다. 과거 개선율을 합산하지 않는다.

## 변경과 근거

기존 분기용 점수 S는 노드의 옵션 envelope로 계산하는 heuristic이다. 부모에서 자식 둘 중 **더 높은 점수**를 뺀 차이로 분기 축을 골랐다. 한 자식이 부모의 점수를 유지하면 다른 자식의 점수가 크게 낮아져도 감소폭이 0이 되었다. 이때 후보 수·그룹 인덱스의 순서로 넘어갈 수 있었다.

실제 딜검방·루브닐·에투왈 단일 잠금의 기존 트리를 따로 조사했다. 내부 노드 3,699개 중 기존 점수가 0인 노드는 1,165개이며, 그중 935개는 한 자식의 점수가 낮았다. 후보 8개 이상인 내부 노드에서는 772개 중 119개가 기존 점수 0이고, 116개에 같은 문제가 있었다. 이 진단은 성능 평균에 포함하지 않았다.

새 분기 우선순위는 다음과 같다.

```text
이전: S(parent) − max(S(left), S(right))
변경: S(parent) − min(S(left), S(right))
```

한쪽 자식을 크게 약화시키는 축을 먼저 분리한다. 후보 트리의 스탯 선택·median 절단점·패키지 순서·자식 모양은 유지하며 두 축의 선택 우선순위만 바꾼다. 감소폭은 기존 노드 필드에 한 번 캐시하므로 분기당 추가 후보 평가나 추가 메모리 필드를 만들지 않는다. 후보 수·그룹 인덱스의 동점 정렬, LL/LR/RL/RR 생성, smallbox 64와 lookahead·관측 기반 결합 제약 사전 검사는 유지한다. 선행 구현은 [분기 처리 기록](crysta-branch-processing.md)에 있다.

장비명·스킬 ID·특정 빌드를 조건으로 선택하지 않는다. 모든 Native 분기에서 동일한 규칙을 사용한다. 초기해·후보·요구조건·계산식·기존 안전 상한도 유지한다. 우선순위에 따라 큐 순서·incumbent 발견 시점·lookahead 관측과 탐색량은 달라질 수 있다.

## 정확성과 버전

분기용 S와 감소폭은 **상한이나 후보 삭제 증거가 아니다**. 선택한 두 축의 모든 자식 공간을 보존하고, 실제 제거에는 기존 Utility/대미지 안전 상한을 사용한다. 취소/deadline 때 부분 자식 결과를 폐기하고 부모를 재등록하는 동작과 pending/active work를 보존한다.

새 합성 회귀는 기존 점수가 모두 0인 세 그룹 중 상한 점수 감소가 큰 그룹을 먼저 고르는지 확인한다. 네 자식이 부모의 모든 16개 완성 조합을 중복 없이 포함하는지도 검사한다. 이 합성 fixture는 사용자 성능 근거로 사용하지 않는다. 기존 exhaustive oracle, 모든 feasible 조합의 조상 상한 property, 입력 순서 반전·동점 ID·잠금·1~64 thread·중단/재개 Gate도 유지한다.

Native 엔진·checkpoint는 v15, split policy는 `candidate-tree-2axis-child-gain-smallbox64-lookahead-precheck.v5`다. v14 이하의 현재/과거 checkpoint를 거부하고 JS exact cache도 구분한다. 계산 v3, 앱 저장 schema, 제품 버전 v0.7.2는 유지한다. Worker fallback의 분기 규칙은 변경하지 않았다.

## 최종 전후 비교

실제 저장 딜검방의 루브닐·실제 콤보 및 평타, 에투왈 단일 잠금을 그대로 사용했다. 인위적인 AMPR/CRIT 가산과 입력/요구조건 변경은 없다. 과거 불완전 루브닐 두 입력은 회귀용이며 현재 사용자 빌드나 다른 직업의 대표 사례로 세지 않는다. 실제 듀얼소드 사용자 성능은 검증하지 않았다.

AMD Ryzen 7 9800X3D / Node v24.17.0 / Native 16 threads. 5개 case·mode에서 전후 각각 10회, 총 100회 새 Node·Native 프로세스를 순차 실행했다. 순서를 번갈았고 cache를 사용하지 않았으며 빌드·테스트와 겹치지 않았다. 양쪽에 같은 현재 JS를 사용했다. baseline 실행파일은 직전 채택한 공격 상한 제품 바이너리와 hash가 같으며, solver 외 Rust 소스는 전후 같다.

| 입력·실행 | Native 평균 전→후(ms) | 전체 평균 전→후(ms) | 전체 P95 전→후(ms) | 전체 단축 |
| --- | ---: | ---: | ---: | ---: |
| 실제 루브닐 release | 339.2→188.9 | 975.4→828.2 | 981.8→863.6 | 15.1% |
| 실제 평타 release | 332.2→185.1 | 968.7→822.1 | 974.0→830.2 | 15.1% |
| 과거 unlocked 회귀 release | 484.8→504.4 | 1228.7→1245.6 | 1246.4→1254.6 | -1.4% |
| 과거 locked 회귀 release | 74.8→66.4 | 641.0→630.0 | 646.3→633.6 | 1.7% |
| 실제 루브닐 debug | 1703.1→1032.8 | 2372.5→1705.2 | 2448.4→1763.1 | 28.1% |


전체 시간은 JS 후보 생성·준비부터 Native 결과 복원·최종 JS 재평가까지이며 UI/WebView는 제외한다. 이전 인앱 10.90초와 직접 비교하지 않는다. 실제 루브닐 release 방문 노드는 평균 925,906.3→458,325.5, evaluations는 4,203,217.8→2,187,448.3이다. 평타도 방문 노드가 약 51% 줄었다.

Native peak working set의 50ms 표본은 실제 두 입력에서 약 3MiB 줄었다. 반면 과거 unlocked 회귀는 약 37.9→50.0MiB로 증가했다. 해당 입력은 evaluations가 줄어도 방문 노드/대기 공간과 시간이 늘었다(Native +4.0%, 전체 +1.4%). 짧은 실행의 peak 표본은 불안정하고 Node 메모리는 제외한다. 모든 입력에서 실행시간·메모리가 개선됐다는 보장은 없다.

100회 모두 exact 점수·전체 bestBuild·원시 옵션 합·compiled/prepared problem hash가 같았다. 실제 루브닐 1,753,977.72, 평타 67,120을 보존하고 최종 JS 재평가도 통과했다. 실제 250ms 재개: 2개 slice·재개 1회, 전체 exact 조합/점수 일치. 재개 시간을 일반 반복 평균에 섞지 않았다.

## 채택하지 않은 분기

후보 수의 중간 대신 서로 다른 스탯 값의 경계에서 자르는 방법을 조사했다. 최초 1/4~3/4 균형 제한은 실제 입력에서 탐색량을 크게 줄였지만 과거 회귀 입력의 방문 노드·시간을 늘렸다. 더 좁은 균형 제한(1/3, 3/8, 9/20)도 회수하지 못했다. 후보 트리의 절단점 변경은 제품에 남기지 않았다.

두 자식 점수의 후보 수 가중 평균을 사용하는 기준과 값 경계 분할의 결합도 과거 회귀에서 퇴행했다. 최종 코드는 median 트리를 유지하고 더 낮은 자식 점수와의 차이만 사용한다. 탐색용 자료는 `src-tauri/target/branch-boundary/`에 보존하며 최종 100회에 섞지 않았다.

## 검증·재현

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: 329개 PASS(79+72+72+21+85, 공유 모듈 중복 포함). 분기 캐시 bit 일치·우선순위 반례·중복 없는 coverage와 기존 oracle/상한/스레드/재개 검증을 포함한다.
- `npm run test:regression`: 76/76 프로세스 PASS. Native 저장 E2E는 CDP 미설정 SKIP이다.
- `npm run verify:architecture`, clippy all-targets `-D warnings`, S1 출처 427/427, fmt PASS.
- `npm run desktop:prepare`, dist entry 검증, 개발용 앱/headless 및 release headless 재빌드 완료. 앱을 강제 종료하거나 재시작하지 않았다.
- `npm run ai:audit`, `git diff --check`: PASS.

```powershell
npm run bench:optimization:build
npm run bench:optimization -- --input tools/fixtures/crysta-saved-sword-shield-revenir-etowal.json --repeats 10 --output src-tauri/target/branch-boundary/official.json
npm run bench:optimization -- --input tools/fixtures/crysta-saved-sword-shield-revenir-etowal.json --repeats 1 --slice-ms 250 --output src-tauri/target/branch-boundary/resume-actual.json
```

로컬 전후 비교는 `compare.ps1`·`sample.mjs`, 집계는 `summarize.mjs`다. 새 checkout에 과거 baseline 실행파일이 자동 제공되지는 않는다. 측정 JSON에 입력·출처·전체 결과·시간/카운터·환경·메모리·소스/바이너리 hash와 진단·재개 결과를 보존한다.
