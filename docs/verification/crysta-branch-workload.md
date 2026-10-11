# 양쪽 자식의 후보량과 현재 점수 차이를 반영한 분기

2026-10-07. 현재 제품 상태는 `../handoff/current-development-handoff.md`, 수치·입력·실행파일/소스 hash는 [측정 원본](crysta-branch-workload-measurements.json)을 따른다. 직전 제품 Native v15가 기본 baseline이다. v14는 잠금 없는 두 입력에서 별도 비교하며 과거 개선율을 합산하지 않는다.

## 변경과 안전성

v15는 부모 heuristic 점수와 더 낮은 자식 점수의 차이만 분기 축의 우선순위로 사용했다. 한 자식의 큰 감소폭이 다른 자식의 잔여 탐색 부담을 대표하지 못했고, 과거 잠금 없는 회귀에서 방문 노드·시간이 증가했다. 근거: [앞선 분기 기록](crysta-branch-priority.md).

새 규칙은 자식 둘의 감소폭과 후보 수를 함께 사용한다. 현재 노드의 실제 안전 대미지 상한 U와 실제 feasible incumbent B의 상대 차이를 기존 heuristic S의 단위로 옮겨 감소폭의 보상 한도 T를 정한다.

```text
T = 2 × sum(S(current group node)) × (U − B) / U
dL = max(S(parent) − S(left), 0)
dR = max(S(parent) − S(right), 0)
priority = left.size × min(dL, T) + right.size × min(dR, T)
```

priority가 큰 두 축을 선택한다. 동점이면 양쪽 모두의 감소폭 `min(dL,dR)`, 기존 큰 감소폭, 후보 수, 그룹 인덱스 순으로 결정한다. 한쪽만 크게 약해지는 분기보다 양쪽에 이득이 있는 분기를 동점에서 먼저 고른다. T보다 큰 감소폭에는 추가 보상을 주지 않으므로 큰 한쪽 감소폭만으로 우선순위를 과도하게 올리지 않는다. U/B가 비유한·누락이거나 U가 양수가 아니거나 점수 차이가 닫혔거나 유효한 T가 없으면 v15 순서를 사용한다. 정수·음수·소수 옵션, 실제 스탯, 요구조건을 수정하지 않는다.

S·T·priority는 **후보 트리의 분기 효율을 추정하는 순서 기준**이다. 전체 Cartesian 조합 수, 실제 남은 시간, 안전 대미지 상한의 정확한 모형이 아니다. 계수 2는 이번 분기 정책의 비용 배분 계수이며 게임 수치·옵션 보정이나 삭제 증거가 아니다. 서로 다른 빌드/무기명/스킬 ID/잠금 여부로 정책을 고르지 않는다.

작은 감소폭·큰 감소폭 쪽의 후보 수·전체 가중 감소폭은 변하지 않아 트리 생성 시 캐시한다. 기존 큰 감소폭 캐시에 세 필드(두 f64·usize, 64비트에서 총 24바이트)를 추가하고, 실제 분기에서는 자식 노드를 다시 찾아 점수를 계산하지 않는다. gap/우선순위는 현재 incumbent에 맞춰 계산하며 추가 후보 평가, JSON 변환, 힙 할당을 하지 않는다. incumbent가 없을 때의 초기 탐색과 보조 Utility lookahead는 기존 캐시 기준을 유지한다.

Native 직렬 exact, 세션 직렬/공유 작업자, 독립 병렬 shard 분기에 공통 적용한다. 후보·median 트리·스탯 선택·패키지 순서·두 축·LL/LR/RL/RR·smallbox 64·기존 lookahead/관측 기반 결합 사전 검사는 유지한다. Worker fallback은 변경하지 않는다.

선택된 두 축의 모든 자식 공간을 보존한다. 삭제는 기존 Utility/대미지 안전 상한으로만 결정한다. 분기 중 취소/deadline이면 부분 결과를 폐기하고 부모를 재등록하는 계약도 유지한다. 다른 스레드에서 incumbent가 갱신되어 선택 순서가 달라져도 원래 공간과 exact·동점 계약은 보존한다.

Native engine/checkpoint v16, split policy `candidate-tree-2axis-gap-work-smallbox64-lookahead-precheck.v6`다. 현재·과거 v4~v15 checkpoint를 거부하고 JS exact cache를 구분한다. 계산 v3·앱 저장 schema·제품 v0.7.2는 유지하며 배포하지 않았다.

## 입력과 최종 측정

실제 저장 딜검방·루브닐/실제 콤보·에투왈 단일 잠금, 같은 입력의 평타를 사용한다. 새 [잠금 해제 fixture](../../tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json)는 실제 루브닐 fixture에서 **마지막 에투왈 잠금만 해제**했다. 원시 스탯·스킬/콤보·요구조건·현재 크리스타·금지를 그대로 보존하는지 측정 집계에서 deep equality로 확인한다. 인위적인 AMPR/CRIT 가산은 없다. 실제 듀얼소드 사용자 성능은 검증하지 않았다. 과거 불완전 콤보 두 입력은 회귀용이며 현재 사용자 빌드나 다른 직업의 대표 사례로 세지 않는다.

AMD Ryzen 7 9800X3D / Node v24.17.0 / Native 16 threads. 기본 6개 case·mode에서 v15/v16 각 10회, 잠금 없는 실제·과거 두 입력은 v14도 각 10회, 총 140회다. 새 Node/Native 프로세스로 순차 실행하고 순서를 번갈거나 3개 정책을 회전했다. 양쪽에 같은 현재 JS를 사용하고 cache·컴파일/테스트 동시 실행을 제외했다. baseline 실행파일은 이전 제품 측정 기록과 SHA-256이 같다.

| 입력·실행 | Native 평균 v15→v16(ms) | 전체 평균 v15→v16(ms) | 전체 P95 v15→v16(ms) | 전체 단축 |
| --- | ---: | ---: | ---: | ---: |
| 실제 루브닐·단일 잠금 release | 191.5→180.5 | 830.7→821.1 | 840.8→854.6 | 1.16% |
| 실제 평타·단일 잠금 release | 186.2→175.7 | 824.2→813.8 | 829.7→819.0 | 1.26% |
| 실제 루브닐·잠금 해제 release | 1283.9→1192.4 | 2231.3→2139.1 | 2247.4→2168.7 | 4.13% |
| 과거 unlocked 회귀 release | 509.1→508.0 | 1252.9→1253.6 | 1258.8→1259.8 | -0.05% |
| 과거 locked 회귀 release | 70.9→67.9 | 645.4→640.6 | 697.5→664.3 | 0.75% |
| 실제 루브닐·단일 잠금 debug | 1036.2→1003.7 | 1710.2→1679.3 | 1768.5→1742.3 | 1.81% |

잠금 없는 입력의 별도 v14 비교:

| 입력 | v14 전체/Native(ms) | v15 전체/Native(ms) | v16 전체/Native(ms) |
| --- | ---: | ---: | ---: |
| 실제 루브닐·잠금 해제 | 3625.1 / 2673.2 | 2231.3 / 1283.9 | 2139.1 / 1192.4 |
| 과거 unlocked 회귀 | 1237.5 / 490.5 | 1252.9 / 509.1 | 1253.6 / 508.0 |


전체 시간은 JS 후보 생성/준비부터 Native client/service 실행·결과 복원·최종 JS 재평가까지며 UI/WebView는 제외한다. 인앱 10.90초와 직접 비교하지 않는다. 평균·중앙값·P95·개별 카운터·전체 추천 조합·입력 hash를 측정 JSON에 보존한다. 짧은 실행의 Native peak working set은 50ms 표본이며 Node 메모리를 포함하지 않아 정밀한 메모리 비교로 해석하지 않는다.

140회 모두 exact 점수·전체 bestBuild·원시 옵션 합·compiled/prepared problem hash가 같고, 최종 JS feasibility/점수 재평가가 통과했다. 실제 잠금 해제 루브닐 1,910,660.94, 단일 잠금 루브닐 1,753,977.72, 평타 67,120을 보존했다.

실제 잠금 해제 입력은 방문 노드 3,576,213.6→3,143,971.9(-12.1%), evaluations 15,892,702.4→12,677,806.7(-20.2%), Native 평균 -7.1%, 전체 평균 -4.1%다. 현재 v15 대비 추가 개선이며 v14 대비 차이는 별도 표의 같은 환경 비교를 따른다. 단일 잠금 입력의 평균 개선은 작고, 루브닐 release P95는 이번 표본에서 늘어 모든 입력/P95의 가속을 주장하지 않는다.

**과거 unlocked 회귀의 기존 퇴행은 해소하지 못했다.** 방문 노드 -0.4%·evaluations -1.8%로 감소폭이 작고 Native 509.1→508.0ms, 전체 1252.9→1253.6ms(+0.05%)로 사실상 같다. 같은 실행에서 v14 전체 1237.5ms와 비교하면 v16도 +1.30%다. 양쪽 부담을 반영했어도 이 입력의 상한/제약 구조에서 충분한 탐색 절감을 얻지 못한 것으로 해석하며, 모든 잠금 없는 입력이 빨라졌다고 보고하지 않는다.

캐시 필드 추가 후 Native peak working set 평균은 사례별 약 +0.1~0.6MiB다. 실제 잠금 해제 58.03→58.29MiB, 과거 unlocked 49.97→50.53MiB다. 사용자의 속도 우선·소폭 메모리 증가 허용을 따르며, 시간 이득과 함께 수치를 공개한다. 이 표본의 증가를 시간 지연의 원인이라고 단정하지 않는다.

실제 잠금 해제 입력의 250ms 재개 검사는 6개 slice·재개 5회 후 full-run exact 점수/전체 조합과 같고 최종 소스/실행파일 hash도 같다. 재개 실행의 전체 4.417초는 일반 140회 평균에 포함하지 않았다.

## 조사에서 제외한 방법

gap 없이 후보 수만 곱하거나 RMS·곱·선형 혼합·기하/조화 감소폭을 쓰는 방법, 손자 점수를 미리 보는 방법은 특정 입력의 퇴행을 회수하지 못했다. gap에 따라 곱 기준으로 전환하는 방법도 실제 입력의 퇴행이 있었다. 현재 gap의 보상 한도를 사용하는 후보량 가중 방식으로 좁혔고, 캐시 전에 매번 자식 점수를 읽는 구현은 과거 회귀에서 비용을 회수하지 못했다.

얕은 분기에서 가능한 두 축의 조합을 기존 결합 Utility/안전 대미지 상한으로 직접 비교하는 strong branching도 조사했다. 깊이 4/8/12 및 Utility-only 검사는 탐색량을 의미 있게 줄이지 못하고 검사 비용이 추가되어 제외했다. 추가 상한 검사나 실험용 환경변수 분기는 제품 코드에 남기지 않았다. 단발 탐색·3회 pilot 표본은 최종 140회에 섞지 않으며 로컬 `src-tauri/target/branch-workload/`에 분리했다.

## 검증·재현

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: 341개 PASS(82+75+75+21+88, 공유 모듈 중복 포함). 새 회귀는 양쪽 감소/후보 수·gap에 따른 순서 변경, 누락/비유한/닫힌 gap의 fallback, incumbent가 바뀌어도 모든 16개 조합을 중복 없이 보존하는지 확인한다. 합성 테스트는 사용자 성능 근거가 아니다. 기존 exhaustive oracle·모든 조상 상한·음수/소수 옵션·입력 역순/동점·1~64 threads·중단/재개 검증도 통과했다.
- `npm run test:regression`: 76/76 프로세스 PASS. Native 저장 E2E는 CDP 미설정 SKIP이다.
- `npm run verify:architecture`, clippy all-targets `-D warnings`, S1 427/427 PASS. 계산식·스킬 데이터 변경은 없다.
- fmt, `npm run desktop:prepare`, dist entry 검증 PASS. 최종 debug 앱/개발 bin·release headless를 다시 빌드했으며 앱을 강제 종료/재시작하지 않았다.
- `npm run ai:audit`, `git diff --check`, 최종 소스·실행파일·prepared frontend 일치 확인 PASS.

```powershell
npm run bench:optimization:build
npm run bench:optimization -- --input tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json --repeats 10 --output src-tauri/target/branch-workload/official.json
npm run bench:optimization -- --input tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json --repeats 1 --slice-ms 250 --output src-tauri/target/branch-workload/resume-actual.json
```

로컬 전후 비교는 `compare.ps1`·`sample.mjs`, 집계/입력·점수·조합·출처 검사는 `summarize.mjs`다. 새 checkout에 과거 실행파일이 자동 제공되지는 않는다. baseline/current Rust 소스·JS·실행파일·입력의 hash와 각 실행의 결과/카운터/시간을 휴대 가능한 측정 JSON에 보존한다.
