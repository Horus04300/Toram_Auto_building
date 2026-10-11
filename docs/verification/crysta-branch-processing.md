# Native 분기 처리 개선

2026-10-02. 현재 상태는 `../handoff/current-development-handoff.md`가 기준이다. 이번 비교의 baseline은 직전 AMPR·CRIT 결합 상한을 포함한 Native v10이다. 과거 상한 도입 전 성능과 직접 비교하거나 개선율을 합산하지 않는다.

## 변경과 안전성

`src-tauri/src/optimization/solver.rs`에 다음 두 변경을 적용했다.

1. **분기 차원 점수 캐시.** 부모의 heuristic 점수에서 두 자식 점수의 최댓값을 뺀 `split_slack`은 트리가 만들어진 뒤 변하지 않는다. 이를 노드 생성 시 한 번 저장하여, 분기마다 자식 노드를 찾아 점수를 다시 읽고 계산하는 작업을 줄였다. 기존 slack·후보 수·그룹 인덱스의 정렬 순서와 LL/LR/RL/RR 생성 순서를 유지한다. 노드당 f64 하나를 추가한다.
2. **선택적 자식 사전 검사.** Native session 작업자가 결합 제약 탈락을 자주 관측하면, 자식의 스탯 합산·기존 유틸리티/대미지 평가·큐 삽입 전에 결합 상한을 검사한다. 불가능한 자식은 여기서 끝내며, 생존한 자식은 기존 처리를 계속한다. 자식 제약 탈락은 기존 형제 기반 lookahead의 관측에도 반영한다.

작업 메시지의 로컬 카운터에서 결합 검사 8회 이상, 탈락 비율 1/8 초과일 때 자식 검사를 켠다. 희소해지면 다시 끈다. 이 값은 검사 비용을 배분하는 정책이며 게임 수치나 삭제 증거가 아니다. 삭제는 항상 기존 `JointUtilityBounds`의 안전성 증명에 따른다. 로컬 관측은 전역 통계·checkpoint에 합산하지 않는다.

부모를 꺼냈을 때의 기존 안전 검사는 그대로 남는다. 사전 검사하지 않은 자식도 이후 기존 경로로 검사되므로 후보를 빠뜨리지 않는다. 직렬 탐색과 로컬 관측을 사용하지 않는 독립 병렬 scheduler는 기존 제거 시점을 유지하며, 분기 점수 캐시는 공통으로 사용한다. 실제 제품의 shared session 작업자는 선택적 사전 검사를 사용한다.

계산식·후보·초기해·분기 차원 수·추가 깊이·동점 규칙은 변경하지 않았다. 취소/deadline은 자식 처리 전 확인하고, 중간 중단 시 부분 결과를 폐기하여 부모를 재등록한다. Native engine/checkpoint는 v11, split policy는 `candidate-tree-2axis-smallbox64-lookahead-precheck.v4`로 변경했다. v10 이하 checkpoint를 거부하며 앱 저장 schema와 제품 버전은 유지한다.

## 성능 비교

Windows / AMD Ryzen 7 9800X3D, 논리 16스레드 / Node v24.17.0 / rustc 1.98.0. 새 Node·Native 프로세스를 사용하여 입력별 전→후, 후→전, 전→후 각 3회, 총 18회를 순차 실행했다. 측정 중 빌드와 테스트를 실행하지 않았다.

`timing.totalMs`는 raw 입력 컴파일부터 실제 Native client/service 실행과 최종 JS 결과 복원·재평가까지 포함한다. UI와 WebView IPC는 제외하며 stdio JSON lines를 사용한다. 전후 실행파일에 같은 현재 JS를 사용한다. baseline 이후 JS 변경은 engine/split-policy 캐시 식별자뿐이며 각 표본은 fresh client라 cache를 사용하지 않는다.

| 입력 | 변경 전 3회 (초) | 변경 후 3회 (초) | 중앙값 전→후 |
| --- | --- | --- | --- |
| 루브닐 | 4.367 / 3.205 / 3.177 | 2.427 / 2.362 / 2.347 | **3.205→2.362초, 26.3% 감소** |
| 듀얼·유틸리티 여유 | 12.841 / 12.410 / 12.140 | 12.442 / 12.933 / 12.367 | 12.410→12.442초 |
| 합성 유틸리티 충돌 | 4.142 / 4.702 / 4.353 | 4.165 / 4.200 / 4.325 | 4.353→4.200초 |

루브닐 평균은 3.583→2.379초(33.6% 감소)지만 첫 baseline이 다른 두 표본보다 느려 중앙값도 함께 제시한다. 3회만으로 P95나 모든 입력의 개선을 주장하지 않는다. 듀얼 평균은 12.463→12.581초(+0.94%), 합성 입력은 4.399→4.230초다. 두 입력은 표본 범위가 겹치고 탐색량도 거의 같아 확정적인 가속 효과로 해석하지 않는다.

여기서 듀얼은 기존 scaling 회귀의 임의 AMPR/CRIT/HP/MP/ASPD 가산을 포함한 입력이다. 실제 듀얼소드 빌드의 대표 성능으로 해석하지 않는다. 보정 5개를 모두 제거하고 요구조건을 유지한 10회씩의 추가 비교·불가능 판정 결과는 `crysta-dual-unadjusted.md`에 기록했다.

루브닐 방문 노드는 약 631만→413만, 기존 evaluations 카운터는 1,519만→773만으로 줄었다. 완성 조합 열거는 전후 약 64만으로 비슷하다. 이미 불가능한 분기를 큐에 넣기 전 제거하여 중간 처리량을 줄인 결과다. 추가 결합 검사 횟수는 기존 evaluations에 합산하지 않는다.

Native peak working set은 루브닐 약 69.5~70.6→45.1~45.3 MiB, 듀얼 약 114.7 MiB 유지, 합성 입력 약 107.8~108.0→107.9~108.2 MiB다. PowerShell이 50ms마다 `PeakWorkingSet64`를 표본 수집했으며 Node 메모리는 제외한다.

18회 모두 exact이며 입력별 전체 bestBuild·원시 옵션 합·점수·최종 upper가 같았다. 최종 JS 평가와 feasibility도 통과했다. 루브닐 1,123,905.36 / 듀얼 21,458 / 합성 입력 43,247이다.

별도 250ms slice 검사는 최초 실행+6회 재개, 총 4.374초로 같은 루브닐 exact 결과에 도달했다. 기본 30초 slice 성능 평균에 포함하지 않았다.

## 채택하지 않은 처리

모든 자식에 항상 결합 검사를 실행하는 첫 실험은 루브닐에 효과가 있었지만, 합성 입력 평균이 약 4.168→4.382초로 느려졌다. 실제 결합 탈락이 드문 입력에서 중복 검사 비용을 회수하지 못한 것으로 보고, 최종 코드에는 관측 기반 사전 검사만 채택했다. 해당 탐색용 표본은 최종 18회에 섞지 않았다. 분기 점수 캐시의 효과만 독립적으로 분리해 측정한 것은 아니다.

## 검증과 재현

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: **285개 통과**(69+62+62+17+75, bin별 공유 모듈 중복 포함).
- 새 회귀는 캐시가 원래 envelope 기반 분기 점수와 비트 단위로 같은지, 사전 제거한 자식에 스탯 평가/큐 삽입이 발생하지 않는지, 관측 비율에 따라 추가 검사가 켜지고 꺼지는지를 검사한다.
- 기존 feasible coverage, JS exhaustive 대조, 입력 역순·동점·1~64스레드, parent rollback, deadline/cancel, checkpoint/resume 회귀를 유지했다.
- `npm run test:regression`: **76/76 프로세스 성공**. Native 저장 E2E는 `TORAM_E2E_CDP` 미설정으로 SKIP이다.
- `npm run verify:architecture`, `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: 통과.
- `node tools/verification/audit-stack-source-links.mjs --require-s1`: S1 427/427 통과. 계산 규칙·스킬 데이터는 변경하지 않았다.

표준 측정:

```powershell
npm run bench:optimization:build
npm run bench:optimization -- --repeats 3 --output src-tauri/target/computation-benchmark/branch-processing.json
npm run bench:optimization -- --repeats 1 --slice-ms 250 --output src-tauri/target/computation-benchmark/branch-processing-resume.json
```

`crysta-branch-processing-measurements.json`에 raw 입력 3개, 소스·실행파일 SHA-256, 환경, 18회 개별 시간·메모리·결과, 재개 결과를 보존한다. 현재 작업 공간의 `src-tauri/target/branch-processing/`에는 baseline `before.rs`, 전후 실행파일·build stamp, raw 입력, `sample.mjs`, `compare.ps1`, `summarize.mjs`를 보존했다. 비교는 `& ./src-tauri/target/branch-processing/compare.ps1`, 집계·전체 결과 대조는 `node src-tauri/target/branch-processing/summarize.mjs`다. 이 디렉터리는 로컬 Git 제외 산출물이며 새 checkout에는 자동 제공되지 않는다.

실제 설치본 UI/업그레이드 검증과 모든 필수 입력의 cold 10회 P95는 실행하지 않았다.
