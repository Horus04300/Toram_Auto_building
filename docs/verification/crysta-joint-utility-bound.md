# Native AMPR·CRIT 결합 제약 상한

2026-10-01 측정, 2026-10-02 최종 소스 일치 확인. 현재 기능·버전 판정은 `../handoff/current-development-handoff.md`를 따른다. 이 문서는 증명, 실험, 재현 기록이다.

## 변경

기존 좌표별 envelope는 한 패키지의 AMPR과 다른 패키지의 CRIT를 동시에 공급할 수 있는 것처럼 계산한다. 따라서 두 요구조건을 각각 통과하지만 동시에 만족할 수 없는 부분공간이 큐에 많이 남았다.

`src-tauri/src/optimization/solver.rs`에 실제 패키지의 AMPR·CRIT 가중합 최대를 캐시하는 `JointUtilityBounds`를 추가했다. Native 직렬 탐색, 직렬 session, 병렬 작업자에서 기존 대미지 상한 검사 뒤에 적용한다. 목적함수 값을 근사식으로 교체하는 변경이 아니라, **feasible 조합의 존재 가능성을 제한하는 결합 제약 상한**이다. 대미지 수식, 후보 준비·삭제, 분할 순서, 초기해, 동점 비교는 유지한다. JS Worker에는 이 추가 상한을 넣지 않았으며 JS 완전탐색을 독립 oracle로 사용한다.

Native client engine/checkpoint는 v10이다. 상한 정책 변경에 따라 현재·과거 이름의 v9 이하 checkpoint를 거부하고 exact cache 키도 바꾼다. 앱 저장 schema와 제품 버전은 변경하지 않았다.

새 불가능 입력 회귀에서, feasible 해 없이 frontier를 모두 소진한 session이 `no-incumbent-yet`를 반환하는 기존 문제를 확인했다. 소진된 경우는 `invalid`, 미해결 공간이 남아 있는 deadline 중단은 `no-incumbent-yet`로 구분했다. 취소/deadline에서 원래 노드를 재등록하는 계약은 유지한다.

## 안전성

1. 원시 패키지에서 INT·INTP·MAXMP의 전체 envelope를 만든다. 기존 `utility_values` 평가기를 정수 이분 탐색하여 AMPR 요구조건에 필요한 최소 flat AMPR 기여량 `A`를 구한다. 기존 MP 포화와 내림을 그대로 사용한다.
2. 각 부분공간의 CRITP 최대 합을 `P`라 한다. 기존 평가기로 CRIT 요구조건을 만족하는 최소 flat CRIT 기여량 `C(P)`를 구해 가능한 정수 `P` 구간의 표에 저장한다. 저항·내림·요구조건 포화를 별도 수식으로 복제하지 않는다.
3. 각 트리 노드에서 실제 패키지의 `a·AMPR + c·CRIT` 최댓값 `U_g(a,c)`를 저장한다. 부모는 두 자식의 최댓값이다. 가중치는 양의 정수 쌍 `(1,4), (1,2), (1,1), (2,1), (4,1)`이며 계산 비용과 가지치기 강도를 선택하는 값이다.
4. 모든 feasible 완성 조합은 `AMPR ≥ A`, `CRIT ≥ C(P)`를 만족해야 한다. 따라서 `Σ U_g(a,c) < a·A + c·C(P)`이면 그 부분공간에는 feasible 조합이 없다. **등호는 제거하지 않아 동점을 보존한다.**

필요한 단조성은 nonnegative INT/CRT base와 보정 프로필이 없는 AMPR 경로에서만 사용한다. AMPR/CRIT/CRITP가 정수가 아니거나, AMPR modifier profile이 있거나, base 조건이 범위를 벗어나면 추가 상한을 만들지 않는다. 옵션 절댓값 1,000,000과 CRITP 합 구간 폭 2,048은 정확한 정수 표현·준비 비용을 위한 구현 예산이다. 게임 수치 상한이 아니며, 넘는 입력을 잘라내거나 invalid로 판정하지 않는다. 기존 상한으로 되돌아간다.

가중합·임계값 비교는 이 범위에서 f64로 정확히 표현되는 정수 연산이다. 별도 epsilon으로 동점을 삭제하지 않는다. split용 `modeledKeys`가 불완전하더라도 추가 상한의 의존 좌표는 원시 패키지에서 직접 읽는다. 캐시는 checkpoint에 직렬화하지 않고 복원 시 다시 만든다.

## 최종 전후 측정

환경: Windows, AMD Ryzen 7 9800X3D, 논리 16스레드, Node v24.17.0, rustc 1.98.0. 입력별 새 Node·Native 프로세스로 전→후, 후→전, 전→후 각 3회씩, 총 18회를 순차 실행했다. 측정 중 빌드·회귀검증은 실행하지 않았다.

`tools/support/crysta-computation-measurement.mjs`의 `timing.totalMs`를 사용했다. raw 입력의 시나리오·컴파일부터 실제 Native client/service 실행, 결과 복원, 최종 JS 재평가까지 포함한다. UI와 WebView IPC는 제외하며 transport는 stdio JSON lines다. 양쪽 실행파일에 동일한 현재 JS를 사용했다. 캐시를 사용하지 않았다.

| 입력 | 변경 전 3회 (초) | 변경 후 3회 (초) | 평균 전→후 |
| --- | --- | --- | --- |
| 루브닐 | 6.361 / 6.229 / 6.201 | 3.011 / 2.992 / 2.952 | **6.264→2.985초, 52.34% 감소** |
| 듀얼·유틸리티 여유 | 11.484 / 11.539 / 11.672 | 11.257 / 11.097 / 11.282 | 11.565→11.212초 |
| 합성 유틸리티 충돌 | 3.869 / 4.040 / 4.053 | 3.893 / 3.893 / 3.912 | 3.987→3.899초 |

루브닐 방문 노드는 약 1,492만→631만, 평가는 6,082만→1,519만, 완성 조합 열거는 316만→64만이다. Native peak working set은 약 117.1~117.9→69.2~70.2 MiB다. PowerShell에서 50ms마다 `PeakWorkingSet64`를 표본 수집했으며 Node 메모리는 포함하지 않는다.

듀얼은 AMPR 요구조건이 이미 충분하여 추가 상한을 사용하지 않는다. 평가·열거 수는 사실상 같고 메모리는 약 114.5~114.8 MiB다. 합성 입력은 평가 수 감소가 작고 메모리는 약 107.7~107.8 MiB다. 이 두 입력의 작은 시간 차이를 확정적 가속 효과로 주장하지 않는다.

이 듀얼 입력은 기존 scaling 회귀의 임의 AMPR/CRIT/HP/MP/ASPD 가산을 포함한다. 수치는 듀얼소드 고유 값이나 실제 장비·스킬 합산 근거가 아니며 실제 듀얼소드 성능으로 일반화하지 않는다. 보정 5개를 모두 제거한 후속 10회 비교는 `crysta-dual-unadjusted.md`를 따른다.

18회 모두 exact이며 입력별 전체 bestBuild, 원시 옵션 합, 점수, 최종 상한이 일치했다. 최종 JS 재평가·feasibility도 통과했다. 점수는 루브닐 1,123,905.36, 듀얼 21,458, 합성 입력 43,247이다.

별도 250ms slice 검사는 최초 실행+9회 재개, 전체 5.960초로 같은 루브닐 exact 점수·전체 조합에 도달했다. 이 결과는 기본 30초 slice 성능 평균에서 제외한다.

## 재현 및 산출물

기본 루브닐 입력과 표준 측정:

```powershell
npm run bench:optimization:build
npm run bench:optimization -- --repeats 3 --output src-tauri/target/computation-benchmark/joint-bound.json
npm run bench:optimization -- --repeats 1 --slice-ms 250 --output src-tauri/target/computation-benchmark/joint-bound-resume.json
```

상세 기록은 `crysta-joint-utility-bound-measurements.json`이다. 정확한 raw 입력 3개, JS/Rust 소스·실행파일 SHA-256, 하드웨어, 실행 순서, 개별 시간·메모리·탐색량·선택 ID를 포함한다. 루브닐은 기존 사용자 재현 fixture, 듀얼은 기존 scaling fixture의 context/requirements를 raw 입력으로 복원한 것, 합성 입력은 기존 utility-conflict spec의 128개 가상 크리스타와 tight 요구조건이다. 준비된 groups를 벤치마크 입력으로 사용하지 않았다.

현재 작업 공간의 `src-tauri/target/upper-bound-experiment/`에 원래 solver `before.rs`, 전후 실행파일 `before.exe`/`after.exe`, raw 입력, `sample.mjs`, `compare.ps1`, `summarize.mjs`를 보존했다. 비교 실행은 `& ./src-tauri/target/upper-bound-experiment/compare.ps1`, 집계·전체 조합 대조는 `node src-tauri/target/upper-bound-experiment/summarize.mjs`다. 이 디렉터리는 로컬 Git 제외 산출물이며 새 checkout에 자동 제공되지 않는다. 표준 벤치마크는 저장된 raw 입력을 `--input`으로 받아 재현할 수 있다.

초기 전체 CRITP envelope를 고정한 실험은 루브닐에서 거의 효과가 없었다. 부분공간별 CRITP 임계값으로 바꾼 실험은 큰 감소를 보였고, 최종 코드는 저렴한 기존 대미지 bound 검사를 먼저 하도록 정리했다. 초반 탐색용 측정은 위 최종 18회에 합산하지 않았다.

## 검증과 한계

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: 273개 통과(여러 bin의 공유 모듈 중복 포함). 최종 검사 순서 정리 후 `--bin crysta_native_exact` 59개도 통과.
- 새 Rust 회귀: 모든 feasible 완성 조합의 모든 조상 box 보존, 독립 envelope를 통과하는 불가능 box 제거, 음수·CRITP·소수 요구조건·MP 변화, 동점·입력 역순·1/2/8/16/64스레드·취소·deadline·checkpoint 재개, 지원 범위 밖 fallback, 해 없는 frontier 소진을 검사한다.
- `npm run test:regression`: 76/76 프로세스 성공. Native exact 테스트에 추가한 물리·마법·발도·듀얼 결합 제약 fixture를 독립 JS exhaustive와 1/8/64스레드 Native session으로 대조했다. 기존 oracle 3,430/solver 144/bounds 1,093, JS/Rust parity 1,938개도 포함한다.
- `npm run verify:architecture`, `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: 통과.
- `node tools/verification/audit-stack-source-links.mjs --require-s1`: S1 427/427 통과. 스킬 수식·S2~S5·전투 상태 전이를 변경하거나 추가 완료한 것은 아니다.
- `npm run ai:audit`, `git diff --check`: 통과. 최종 Rust 및 공통 JS 소스의 SHA-256이 측정 보고서와 일치함을 확인했다.
- 저장 E2E는 `TORAM_E2E_CDP` 미설정으로 SKIP이다. 설치본 UI/업그레이드 검증과 전체 필수 입력의 cold 10회 P95는 실행하지 않았다. 모든 입력의 10초 exact 또는 모든 입력의 속도 개선을 주장하지 않는다.
