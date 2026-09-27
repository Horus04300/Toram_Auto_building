# 가상 입력: 유틸리티 요구조건 충돌

2026-09-24. 동일 후보에 MP·AMPR·평타 크리티컬·ASPD 요구조건만 바꿔 Native 탐색 병목을 측정했다. 이번 작업은 fixture·계측 도구·문서만 추가/수정했으며 제품 알고리즘은 이전 4진 힙 상태를 유지한다(`d4-frontier-heap.md`).

## 입력 구성과 통제

- `tools/fixtures/d4-synthetic-utility-conflict.json`: Lv.220 활/원거리, STR 70·DEX 380·AGI 120, 공격력 380·제련 9. 범용 물리 공격의 테스트 계수다. **실제 게임 크리스타나 스킬 수치라고 주장하지 않는 합성 데이터**이며 카탈로그에 등록하지 않는다.
- 부위별 MP·AMPR·CRIT·ASPD 특화 4종 × 강도 8개, 총 128개 가상 크리스타. 한 후보는 유틸리티 한 종류를 공급하고 강도가 높을수록 ATKP가 낮다. CDMG와 SRW도 결정적인 패턴으로 달라진다. 기존 compiler가 부위·2슬롯·동일 장비 중복 규칙을 적용한다.
- 모든 유틸리티 좌표가 활성인 tight 조건으로 **한 번만 준비**하고, 그룹 445/448/446/449개를 세 조건에 그대로 사용한다. 약 399억 조합이다. 그룹 해시 일치를 검사한다. 실제 앱처럼 매 조건마다 Pareto 준비를 다시 하는 전체 경로의 벤치마크는 아니다. 준비 결과를 고정해 탐색 단계에 미치는 제약의 영향을 분리한다.
- 각 유틸리티를 균형 있게 공급하는 8슬롯 조합을 증인으로 구성하고, 기본값→증인 값 증가분의 25%/65%/100%를 요구한다. 임의의 불가능 문제를 빡빡한 입력으로 오인하지 않도록 세 조건 모두 증인의 실제 계산값이 제약을 만족하는지 검사한다.

| 조건 | MP | 듀얼 전 AMPR | 평타 CRIT | ASPD | 소형 입력의 유효 조합 |
| --- | ---: | ---: | ---: | ---: | ---: |
| 느슨함 | 822 | 30 | 42 | 843 | 1,728 / 4,096 |
| 중간 | 1,142 | 45 | 54 | 1,003 | 390 / 4,096 |
| 빡빡함 | 1,422 | 59 | 65 | 1,143 | 13 / 4,096 |

HP 제한은 세 조건 모두 해제한다. 소형 입력은 각 그룹 8개이며 증인 패키지를 포함한다. 유효 조합 비율은 소형 부분집합의 값으로, 전체 후보의 비율을 추정하는 데 사용하지 않는다.

## 결과

Ryzen 7 9800X3D / 논리 16개, Windows 10.0.26200, Node 24.17.0. 16작업자, 새 프로세스, 완료까지 60초 예산으로 control/profile 각 3회씩 순차 실행했다. 다른 빌드·검증은 측정과 병행하지 않았다. 아래 시간은 구간 타이머 없는 control Native 세션의 중앙값이며 JS 준비·UI·IPC 시간은 제외한다. control에도 초당 최대 한 번 snapshot과 batch 경계의 최대 ready 수 수집은 있다.

| 조건 | 완료 시간 | 평가 수 | 완성 조합 열거 | 최대 ready 후보 | 열거 후 제약 탈락률¹ |
| --- | ---: | ---: | ---: | ---: | ---: |
| 느슨함 | **0.046초** | 646,148 | 211,337 | 34,983 | 63.70% |
| 중간 | **0.385초** | 6,784,995 | 2,709,768 | 357,208 | 90.04% |
| 빡빡함 | **16.255초** | 324,683,321 | 224,547,344 | 8,790,223 | **98.01%** |

¹ 별도 leaf 계측 실행 1회씩의 값이다. 기존 prunedByConstraint는 작은 박스의 완성 조합 탈락을 세지 않으므로, 복사한 solver의 consider_parallel에서 제약 통과/탈락을 작업자 로컬로 추가 집계했다. 합이 enumeratedCompletions와 정확히 같음을 확인했다. 빡빡한 입력의 224,547,344개 중 **220,077,555개가 제약 위반**, 4,469,789개가 제약 통과였다. 이는 실제 방문한 완성 조합의 비율이며 전체 탐색 공간의 비율은 아니다.

전체 조건에서 exact 결과가 일치했다(느슨함 47537, 중간 45645, 빡빡함 41203). 빡빡함의 평가는 느슨함의 약 502배, 시간은 약 355배였다. Native 준비는 약 8ms 수준으로, 증가분은 본 탐색에 집중됐다. 제약이 강해지면 항상 느려진다는 일반 법칙은 아니며, 이 합성 후보에서 확인한 양상이다.

빡빡함의 구간 계측은 총 16.53~16.89초 중 큐 pop 6.19~6.34초(약 37.5%), 큐 재삽입 약 1.15초, poolRun 9.12~9.34초였다. workerJob 합은 98.7~99.1초, 그 안의 evaluator 추정 합은 65.6~65.9초, boxStats 추정 합은 12.3~12.7초였다. 작업자 합은 동시 실행 시간이므로 벽시계에 더하지 않는다. poolRun은 전달·실행·대기·수신을 포함하며 순수 잠금 대기가 아니다. evaluator/boxStats는 1024회당 1회 표본이므로 타이머 비용·샘플 편향이 있는 추정치다.

구간 계측 시간 증가는 빡빡함의 대응 반복에서 약 1.7~5.7%였다. 이후 leaf 카운터 추가 계측은 별도 파일로 분리했다. 따라서 leaf 계측 실행을 기존 3회 중앙값에 섞지 않았다. 짧은 느슨함/중간 입력의 타이머·프로세스 시작 오차는 상대적으로 크다.

control 관측 peak working set은 느슨함 약 12~13 MiB, 중간 약 26 MiB, 빡빡함 443~642 MiB였다. OS 표본값이며 짧은 프로세스에서는 순간 peak를 놓칠 수 있다. ready 최대값은 매 batch 경계에서 직접 기록해 초당 snapshot만으로 짧은 입력의 최대치를 판단하지 않았다.

## 해석과 다음 개선 후보

이 입력의 핵심은 **완성 조합을 만든 뒤 유틸리티 부족을 알아내는 비용**이다. 초기 유효 해만 보강하거나 평가 함수 내부의 몇 연산을 줄이는 것으로는 2억 개 넘는 열거를 충분히 줄이기 어렵다. 큐의 직렬 비용도 여전히 크다.

다음 실험은 작은 박스 열거의 부분 조합마다 **현재 기여 + 남은 그룹의 안전한 유틸리티 최대 공급량**을 확인해, 충족 불가능한 가지를 완성 전에 건너뛰는 방식이 우선이다. MP→AMPR 같은 파생 의존성을 보존해야 하고, 검사 추가 비용보다 열거 감소 이익이 큰지 느슨함·중간 입력까지 함께 비교해야 한다. 아직 이 개선의 안전성·속도 향상을 검증하거나 제품에 연결한 것은 아니다.

98% 탈락만으로 특정 pair 상한이나 새로운 하위호환 삭제가 안전하다는 결론을 내리지 않는다. 현실 입력에서의 빈도나 성능 개선율도 이 합성 입력만으로 일반화하지 않는다.

## 검증과 재현

- 소형 JS 완전 탐색: 3 × 4,096조합. Native control/profile × 1/16작업자 총 **12회 점수·ID 일치**.
- 소형 CandidateTree 상한: 각 8,191개, 총 **24,573개** 검사, 위반 0. envelope 단조성: 각 56개, 총 **168개** 검사, 위반 0.
- 전체 18회 완료 측정의 최적 조합을 실제 준비 후보에서 복원해 **JS 최종 재평가·제약 검사 18/18 통과**. 전체 입력을 JS 완전 탐색한 것은 아니다.
- leaf 별도 6회도 exact 점수·ID 일치 및 leaf 통과+탈락 합 검사 통과.
- `cargo test --offline --release --manifest-path src-tauri/target/slow-profile/crate/Cargo.toml --bin d4_native_parallel`: **43/43 통과**.
- 새 도구 2개와 수정한 profile 도구의 `node --check`, `npm run ai:audit`, `git diff --check`: 통과. 이번에 제품 계산·탐색 코드는 바꾸지 않아 앱 R0/R9/S1·UI E2E·배포는 재실행하지 않았다.

```powershell
node tools/prepare-d4-utility-conflict.mjs
node tools/profile-d4-slow-inputs.mjs build
$env:D4_PROFILE_FIXTURES='utility-loose,utility-medium,utility-tight'
$env:D4_PROFILE_THREADS='16'
$env:D4_PROFILE_REPEATS='3'
$env:D4_PROFILE_BUDGET='60000'
$env:D4_PROFILE_REPORT='utility-complete.json'
node tools/profile-d4-slow-inputs.mjs run
$env:D4_PROFILE_REPEATS='1'
$env:D4_PROFILE_REPORT='utility-leaves.json'
node tools/profile-d4-slow-inputs.mjs run
$env:D4_PROFILE_FIXTURES='utility-loose-oracle,utility-medium-oracle,utility-tight-oracle'
$env:D4_PROFILE_THREADS='1,16'
$env:D4_PROFILE_REPORT='utility-oracle.json'
node tools/profile-d4-slow-inputs.mjs run
node tools/prepare-d4-utility-conflict.mjs verify
node tools/summarize-d4-utility-conflict.mjs
```

현재 profile 생성기는 leaf 카운터도 포함한다. 최초 3회 구간 계측 당시에는 leaf 카운터가 없었고 이후 추가했다. 재실행 시 control 중앙값은 같은 방식으로 비교하고 profile에는 해당 추가 비용이 포함됨을 구분한다. 15초 pilot은 탐색용으로 사용했으며 위 중앙값에 포함하지 않았다.

입력·증인·소형 oracle: `d4-utility-conflict-inputs.json`. 환경·제품 소스 해시·공통 후보 해시·전체 측정·스레드별 카운터: `d4-utility-conflict-measurements.json`. 준비 입력과 OS 원시 샘플은 target 아래 생성되며 위 명령으로 재생성한다.
