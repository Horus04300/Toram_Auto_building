# 요구조건을 반영한 공격 옵션 상한

> 아래는 v12 당시의 구현·측정 기록이다. v13에서 적용 범위를 확장한 현재 결과는 [공통 상한 확대 검증](crysta-general-upper-bound.md)을 따른다.

2026-10-03. 현재 구현 상태는 `../handoff/current-development-handoff.md`를 따른다. 기존 v11의 AMPR·CRIT 결합 제약 및 분기 개선을 baseline으로 삼아, Native v12에 공격 옵션의 조건부 상한을 추가했다.

이 문서의 전후 수치는 기존 해석 완료 fixture에 대한 결과다. 이후 실제 저장 딜검방 빌드를 재조립한 입력에는 램페이지 AMPR 보정이 있어 이 상한이 적용되지 않음을 확인했다. 현재 인앱 시간과의 차이와 같은 입력의 debug/release 재현은 `crysta-in-app-timing-gap.md`를 따른다. 아래 개선율을 현재 저장 빌드의 개선율로 사용하지 않는다.

## 변경 이유와 적용

기존 상한은 각 옵션의 독립 최댓값을 합산한다. AMPR·CRIT을 채우는 조합과 ATK%·거리 대미지·크리티컬 대미지가 높은 조합을 동시에 고를 수 없는 경우에도 큰 대미지 상한이 남는다. 기존 결합 검사가 유틸리티 때문에 완전히 불가능한 공간을 제거했다면, 이번 변경은 **요구조건을 만족하는 조합의 공격 옵션 최댓값**을 제한한다.

`src-tauri/src/optimization/solver.rs`의 `JointUtilityBounds`에 `ConstrainedOffenseBounds`를 추가했다. 실제 패키지에서 다음 세 좌표의 지지값을 트리 노드마다 캐시한다.

- 물리 `ATKP`, 마법 `MATKP`.
- 근거리 `SRW`, 원거리 `LRW`.
- `CDMG`.

선택 방향은 기존 AMPR·CRIT 방향 5개와 공격 옵션 계수 1/2/4의 곱이다. 계수는 상한의 강도/비용을 선택하는 값이며 게임 수치가 아니다. 그룹별 패키지 값을 캐시하고 내부 노드는 두 자식의 최댓값을 저장한다. 상자를 평가할 때 안전 상한으로 기존 세 좌표의 최댓값을 낮추고, 그대로 기존 계산 커널을 호출한다. 실제 후보나 반환 옵션을 수정하지 않는다.

기존 트리 분할 점수·패키지 순서·자식 생성 규칙·초기해·잠금·동점 비교·계산식을 유지한다. 큐의 대미지 상한은 더 작아질 수 있고 이에 따른 탐색 우선순위와 lookahead 대상은 달라질 수 있다. 일반 `box_stats` 경로에서 적용하므로 직렬·독립 병렬·제품 shared session에 같은 증거를 사용한다. 작은 상자의 기존 suffix 검사/완성 조합 평가는 그대로다.

## 안전성

각 공격 옵션의 실제 합을 `D`, 실제 flat AMPR/CRIT 합을 `M`, `C`라 한다. 기존 결합 상한에서 얻은 AMPR 최소량 `A`와 현재 상자의 CRITP 최대값 `P`에 따른 CRIT 최소량 `C_min(P)`는 모든 feasible 완성 조합의 필요조건이다.

노드마다 실제 패키지의 `k·D + a·M + c·C` 최댓값을 `U_g(k,a,c)`라 하면, 모든 feasible 조합은 다음을 만족한다.

```text
k·D + a·M + c·C ≤ Σ U_g(k,a,c)
M ≥ A, C ≥ C_min(P)
D ≤ [Σ U_g(k,a,c) − a·A − c·C_min(P)] / k
```

상자의 CRITP 최대값으로 최소 필요 CRIT를 계산하므로 실제 패키지보다 낙관적인 필요량을 사용한다. 위 식의 공격 옵션 상한은 모든 feasible 조합 이상이다. 기존 좌표별 상한과 이들 상한의 최솟값을 취할 수 있다. 세 좌표를 서로 다른 완성 조합이 최대화해도 각 좌표가 실제 feasible 합 이상인 envelope를 유지하므로 기존 대미지 상한 커널을 계속 사용할 수 있다.

지원하는 좌표는 패키지별 유한 정수, 절댓값 1,000,000 이하이고 합 범위가 변하는 경우다. 기존 AMPR/CRIT 정수·CRITP 구간·nonnegative INT/CRT base·AMPR 보정 profile fallback도 유지한다. 공격 좌표 하나가 소수거나 범위를 벗어나면 그 좌표만 기존 상한을 유지한다. modeledKeys에서 빠진 좌표는 새로 생성하지 않는다. 표현 범위는 구현 예산이며 게임 옵션을 자르는 규칙이 아니다.

이 범위에서 지지값과 합·차는 f64로 정확한 정수다. 계수 1/2/4로 나누는 연산도 정확하다. 실제 `D`가 정수이므로 최종 좌표 상한을 내림할 수 있다. 등호와 기존 점수 EPSILON·동점 ID 계약을 유지한다. heuristic 점수나 실제 후보 한 개의 대미지를 상한으로 쓰지 않는다.

Native engine/checkpoint는 v12다. v11 이하 현재/과거 schema를 거부한다. split policy는 분할 규칙이 같은 v4를 유지하고 앱 저장 schema·계산 v3·제품 버전은 변경하지 않았다. 새 캐시는 checkpoint에 직렬화하지 않고 복원 시 원시 패키지로 다시 만든다. 기존 취소/deadline rollback과 pending/active 작업 보존을 유지한다.

## 실제 사용자 재현 입력의 비교

원본은 `tools/fixtures/crysta-native-runtime-26min-revenir.json`의 `resolvedExecutionContext`다. 장비·능력치·보스·요구조건·외부 옵션을 수정하지 않았다. 파일의 rawInput과 계산 문맥을 모두 보존한다. 해당 fixture에는 당시 UI/콤보 해석과 MP 활성 상태 보정의 재현 근거가 있으며 이번 작업에서 새로운 숫자를 넣지 않았다.

두 번째 입력은 같은 빌드에 사용자가 보고했던 에투왈 잠금 배열만 적용한다. 근거는 `crysta-native-runtime-26min-revenir-locked-measurement.json`의 locks다. 현재 크리스타·스탯·요구조건은 동일하다. 과거 측정 시간은 이번 결과와 비교하지 않는다. 두 입력은 하나의 사용자 빌드의 잠금 상태 두 가지이며, 서로 다른 직업의 대표 입력으로 세지 않는다. 기존 임의 듀얼 입력과 가산 제거 입력은 사용자 요청 성능 근거에서 제외했다.

Windows / AMD Ryzen 7 9800X3D / 논리 16스레드 / Node v24.17.0. 각 입력과 버전마다 새 Node·Native 프로세스로 10회씩, 총 40회를 전→후/후→전 순서를 번갈아 순차 실행했다. 측정 중 빌드·회귀 테스트를 실행하지 않았다. 양쪽 실행파일에 같은 현재 JS를 사용했고 cache를 쓰지 않았다. raw 입력 컴파일·JS 준비·Native 실행·결과 복원·최종 JS 재평가까지 `timing.totalMs`로 측정하며 UI/WebView는 제외한다.

| 사용자 입력 | 평균 전→후 | 중앙값 전→후 | 평균 감소 |
| --- | --- | --- | --- |
| 루브닐, 전체 잠금 해제 | **2.189→1.644초** | **2.185→1.638초** | **24.9%** |
| 루브닐, 에투왈 잠금 | 0.874→0.847초 | 0.873→0.846초 | 3.1% |

모두 10쌍에서 후가 더 빨랐다. 전체 잠금 해제의 표본 범위는 2.173~2.217→1.622~1.687초, 잠금 상태는 0.863~0.885→0.841~0.858초다. 잠금 상태의 절감은 약 27ms로 작다. 전체 잠금 해제의 10회 nearest-rank 표본 P95는 2.217→1.687초다. 이 두 상태만으로 모든 필수 실제 입력의 10초/P95 또는 실제 UI 성능을 인증하지 않는다.

전체 잠금 해제에서 방문 노드는 약 414만→143만, 평가 약 778만→486만, 완성 조합 열거 약 64.2만→17.6만이다. 잠금 상태는 약 33만→15.5만 노드, 평가 약 68.5만→46.9만, 열거 약 10.6만→2.0만이다. 새 공격 좌표 지지값 산술은 기존 evaluations에 별도로 합산하지 않는다. 카운터 감소율을 전체 시간 감소율로 해석하지 않는다.

Native peak working set은 전체 잠금 해제에서 약 45.1~46.2→35.9~37.2 MiB다. 50ms마다 `PeakWorkingSet64`를 표본 수집했고 Node 메모리는 제외한다. 잠금 입력의 Native 실행은 짧아 peak 표본이 불안정하므로 그 메모리 개선율은 주장하지 않는다. 캐시 자체는 메모리를 추가하지만 이 사용자 입력에서는 frontier 축소 후 전체 peak가 줄었다.

40회 모두 feasible **exact**이며 입력별 전체 bestBuild·원시 옵션 합·최적 점수·최종 upper가 일치했다. 최종 JS 재평가도 통과했다. 전체 해제 점수 1,123,905.36, 에투왈 잠금 점수 1,048,419.24다.

별도 250ms slice 실행은 최초 실행+3회 재개로 총 2.585초에 같은 전체 해제 exact 점수와 전체 bestBuild에 도달했다. 이 결과를 일반 30초 slice 평균에 섞지 않았다.

## 검증과 한계

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: **293개 통과**(71+64+64+17+77, 공유 모듈의 bin별 중복 포함).
- 새 상한 property는 물리·마법·원거리/발도·듀얼, 음수 옵션과 소수 요구조건에 대해 8⁴ 완성 조합을 평가한다. 모든 feasible 완성 조합의 모든 조상 상자에서 세 좌표 상한과 대미지 상한이 실제 값 이상인지 검사하며 실제 상한 감소도 확인한다.
- 소수/표현 예산 밖의 공격 좌표별 fallback, modeledKeys 누락, 원시 패키지 보존을 검사한다. 기존 oracle·입력 역순·동점·1~64스레드·취소/deadline·checkpoint/resume 회귀도 유지했다.
- `npm run test:regression`: **76/76 프로세스 성공**. 독립 JS exhaustive oracle의 joint fixture에 세 공격 좌표의 충돌/음수를 추가해 Native 결과와 비교했다. Native 저장 E2E는 `TORAM_E2E_CDP` 미설정으로 SKIP이다.
- `npm run verify:architecture`, `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: 통과.
- `node tools/verification/audit-stack-source-links.mjs --require-s1`: S1 **427/427 통과**. 스킬 수치나 계산식은 변경하지 않았다.

기존 결합 상한이 지원되지 않거나 AMPR 요구량이 이미 최저 공급량으로 충족된 경우에는 이번 공격 좌표 상한도 사용하지 않는다. 위 사용자 입력의 개선을 모든 직업·요구조건·실제 듀얼소드 성능으로 일반화하지 않는다. 실제 듀얼소드 사용자 입력의 검증은 별도 입력이 필요하다.

## 재현

```powershell
npm run bench:optimization:build
npm run bench:optimization -- --repeats 10 --output src-tauri/target/computation-benchmark/constrained-offense.json
npm run bench:optimization -- --repeats 1 --slice-ms 250 --output src-tauri/target/computation-benchmark/constrained-offense-resume.json
```

전후 40회는 `crysta-constrained-offense-bound-measurements.json`에 입력·출처·실행 순서·개별 값·전체 결과·JS/Rust/실행파일 SHA-256을 보존한다. 집계 스크립트에서 원본 context/requirements와 두 입력의 일치, 입력별 전체 결과 일치, baseline 대비 solver 이외의 Rust 일치, 최종 바이너리의 현재 소스 일치를 확인했다.

로컬 Git 제외 디렉터리 `src-tauri/target/constrained-upper-bound/`에는 v11 baseline solver/실행파일/build stamp와 v12 실행파일, `prepare.mjs`, `sample.mjs`, `compare.ps1`, `summarize.mjs`, 테스트 로그를 보존한다. 전후 비교는 `node .../prepare.mjs` → `& ./.../compare.ps1` → `node .../summarize.mjs`다. 새 checkout에는 로컬 baseline 실행파일이 자동 제공되지 않는다. 초기 3회 탐색 실험은 최종 40회에 포함하지 않았다.
