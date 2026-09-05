# D4 병렬화 설계·실험 기록

- 문서 역할: P0~P8 당시 설계·실험의 근거. 아래 단계별 현재/아직/미완료 표현과 수치는 각 실험 시점 기록이며 제품의 현재 상태가 아니다.
- 현재 상태는 `docs/handoff/current-development-handoff.md`, 유지할 실행 계약은 `docs/architecture/d4-native-runtime-correction-plan.md`를 따른다. Native deadline/progress/pause/resume을 아래 초기 계획에 따라 다시 구현하지 않는다.
- 기준일: 2026-08-30
- 선행 상태: Gate F 종료, 단일 JavaScript Worker 채택본 exact 1,177,836ms
- 적용 환경: Tauri v2 Windows 데스크톱을 우선하고 일반 브라우저는 JavaScript fallback으로 유지
- 참조 문서: `d4-exact-optimization-plan.md`, `d4-build-optimizer-design.md`, `current-development-handoff.md`

## 1. 목적

첫 목적은 10초 exact를 즉시 보장하는 것이 아니라, 현재 한 개 JavaScript Worker만 사용하는 탐색을 배포 PC의 모든 논리 CPU에서 안전하게 실행할 수 있게 만드는 것이다. 병렬화 뒤에도 다음 계약은 바뀌지 않는다.

- 탐색 후보와 제약을 누락하지 않는다.
- 각 작업 조각은 서로 겹치지 않고, 모든 조각의 합집합은 원래 탐색 공간과 정확히 같다.
- 최적 점수 동률은 기존의 사전식 build ID 규칙으로 결정한다.
- 완료하지 못한 작업이 하나라도 있으면 `exact`로 표시하지 않는다.
- 시간 제한 결과는 모든 미완료 작업의 상한을 합친 인증 gap을 반환한다.
- 작업 스레드 실패, 계산식 불일치, GPU 오류가 있으면 해당 실행을 `exact`로 승격하지 않는다.

병렬화는 10초 목표를 대체하지 않는다. 현재 1,177.8초 작업량은 16스레드가 완벽히 선형 확장돼도 73.6초이므로, 병렬화 뒤에도 실제 결합을 보존하는 새 노드 표현과 상한 강화가 필요할 수 있다.

## 2. 기술 선택

| 선택지 | 역할 | 판정 |
| --- | --- | --- |
| JavaScript Web Worker pool | 가장 빠르게 사용할 수 있는 병렬 fallback과 분할·병합 계약 검증 | 1차 구현 |
| Rust 네이티브 CPU 엔진 | 공유 메모리, 낮은 GC 비용, 동적 전체 스레드 사용, Tauri 직접 연결 | 최종 기본 경로 |
| C/C++ 네이티브 엔진 | 성능 가능성은 있으나 별도 FFI·빌드·배포 계층이 필요 | Rust 대비 이점 부족으로 제외 |
| WebAssembly threads | SharedArrayBuffer·교차 출처 격리와 WebView 지원 상태에 의존 | 기본 경로에서 제외 |
| Rust `wgpu` GPU compute | 규칙적인 대량 평가의 선택적 보조 경로 | CPU 완성 뒤 별도 Gate |

Rust를 최종 기본 언어로 선택한다. 저장·배포 백엔드가 이미 Rust/Tauri로 구성돼 있어 별도 런타임이나 네이티브 DLL을 추가할 필요가 없고, 하나의 후보 저장소를 여러 스레드가 읽는 구조를 만들 수 있다. 계산식은 JavaScript의 IEEE-754 배정밀도 연산 순서와 각 단계 `floor`를 그대로 이식하며, Rust 결과가 JavaScript와 일치하기 전에는 추천 기본 경로로 사용하지 않는다.

## 3. 동적 하드웨어 할당 정책

현재 개발 PC의 8코어/16스레드, 약 48GB RAM, RX 9070 XT는 기준 측정 장비일 뿐 배포 설정에 하드코딩하지 않는다.

### 3.1 CPU

네이티브 백엔드는 매 실행 시 `std::thread::available_parallelism()`을 기준으로 현재 프로세스가 사용할 수 있는 논리 프로세서 수를 조사한다. Rust 전용 ThreadPool에는 감지된 값을 명시적으로 지정한다.

```text
logicalThreads = max(1, available_parallelism())
computeThreads = logicalThreads
initialShardTarget = clamp(logicalThreads × 8, logicalThreads, 안전한 큐 한계)
```

- 일반 배포 기본값은 `auto=0`이며 사용자가 스레드 수를 입력할 필요가 없다.
- 모든 논리 프로세서를 계산 스레드로 만든다. 다른 프로그램이 CPU를 사용 중이어도 스레드 수를 낮추지 않고 Windows 스케줄러와 시간을 공유한다.
- 고정된 16, 물리 코어 수, 특정 CPU 이름을 정책에 사용하지 않는다.
- 작업 조각 수는 OS 스레드 수보다 크게 유지해 느린 조각이 생겨도 유휴 스레드가 다른 조각을 훔쳐갈 수 있게 한다.
- 하이브리드 CPU와 SMT에서는 스레드별 처리량이 달라도 중앙 우선순위와 work stealing으로 자연스럽게 재분배한다.
- 64개가 넘는 논리 프로세서나 다중 NUMA 장비는 별도 배포 회귀에서 모든 processor group 사용 여부를 확인한다. 감지값과 실제 생성 스레드 수가 다르면 진단을 남긴다.

### 3.2 메모리

CPU 스레드는 전부 유지하되, 메모리가 적은 PC에서는 스레드 수가 아니라 큐와 작업 조각의 크기를 줄인다.

- 후보·트리·시나리오는 `Arc` 기반 불변 공유 데이터로 한 번만 보유한다.
- 노드는 전체 객체 복사 대신 후보 범위, 트리 node index, 상한, path ID를 가진 조밀 구조로 저장한다.
- 실행 시작 시 총 메모리와 현재 가용 메모리를 조사해 동적 메모리 예산을 만들고, 실행 중에도 주기적으로 가용 메모리를 다시 확인한다.
- 기본 큐 예산은 `min(총 RAM의 60%, 현재 가용 RAM의 75%)`에서 앱 고정 데이터와 안전 여유를 뺀 값으로 한다.
- 큐가 예산에 접근하면 새 전역 노드 생성을 억제하고 각 작업자가 깊이 우선 탐색으로 전환한다. 정확성이나 CPU 스레드 수는 줄이지 않는다.
- 메모리 부족은 조용한 후보 삭제로 처리하지 않는다. 복구할 수 없으면 bounded/invalid와 진단을 반환한다.

### 3.3 GPU

Rust `wgpu`가 실행 시 어댑터를 열거하고 다음 정보를 보고한다.

- discrete/integrated 구분
- compute shader 지원
- 사용 가능한 storage buffer와 workgroup 한계
- 백엔드가 제공하는 경우의 전용 또는 사용 가능 메모리 추정치
- 실제 소규모 calibration kernel 처리량

어댑터가 없거나 초기화·calibration에 실패하면 CPU-only로 자동 전환한다. GPU 사용 여부는 그래픽 카드 이름으로 결정하지 않는다. GPU 메모리 정보가 제공되면 감지된 안전 범위의 최대 50%만 사용한다. 정보가 없으면 storage buffer 한계 안에서 작은 batch부터 늘리고 할당 실패 시 즉시 CPU-only로 복귀한다. 여러 GPU가 있으면 실제 calibration이 가장 빠른 compute-capable 어댑터를 선택한다.

## 4. 병렬 탐색 구조

### 4.1 공유 준비 단계

한 번만 수행한다.

1. JavaScript에서 현재 입력을 `CompiledProblem`으로 만든다.
2. 후보 정규화, Pareto, 동적 seed, CandidateTree를 한 번 만든다.
3. 기존 heuristic으로 전역 초기 하한과 best build를 만든다.
4. 루트 상자를 결정적으로 분할해 `ParallelShard` 목록을 만든다.
5. 각 shard에 path, 상한, 포함 CandidateTree 범위, 예상 조합 수, checksum을 기록한다.

`ParallelShard`는 원본 공간의 증명 가능한 부분집합이어야 한다. shard 생성기에는 다음 property test를 둔다.

- shard 교집합은 공집합이다.
- shard 합집합은 원본 exhaustive 결과와 같다.
- shard별 최대값의 최댓값은 원본 exhaustive 최대값과 같다.
- 입력 순서를 바꿔도 shard ID와 checksum은 같다.

### 4.2 스케줄링

초기 shard를 `상한 내림차순 → 예상 작업량 내림차순 → path ID 오름차순`으로 배치한다.

- 모든 CPU 작업자는 같은 불변 후보 저장소를 읽는다.
- 각 작업자는 작은 로컬 heap을 사용하고, 작업이 떨어지면 다른 작업자의 deque 또는 중앙 큐에서 가져온다.
- 큰 shard는 실행 중 다시 분할할 수 있고, 작은 shard는 64개 이하 완성 조합을 직접 열거한다.
- 전역 incumbent는 `RwLock<Incumbent>`로 점수·build ID·결과를 함께 보존하고, 변경 세대만 `AtomicU64`로 공유해 작업자가 값이 바뀐 경우에만 다시 읽는다. 부동소수점 점수와 동점 ID를 서로 다른 원자 값으로 갱신하지 않는다.
- 새 incumbent를 본 모든 작업자는 자신의 상한이 낮은 노드를 즉시 버린다.
- 각 스레드의 평가·방문·가지치기 수는 thread-local로 누적하고 진행 보고 시 합친다.

중앙 heap 하나에 모든 pop/push를 몰아넣지 않는다. 전역 best-bound만 고집하면 lock 경합으로 코어가 놀 수 있으므로, 전역 상위 shard 우선순위와 로컬 best-bound/depth-first를 혼합한다.

### 4.3 결과 병합

전역 결과는 다음 방식으로만 계산한다.

```text
globalLower = 모든 실제 feasible 결과 중 최고 점수
globalBest  = globalLower 동률 중 사전식 build ID 최소
globalUpper = max(대기 shard upper, 실행 중 shard upper, 완료 shard의 증명값)
exact       = 실패 shard 없음 AND 대기/실행 shard 없음
              AND globalUpper <= globalLower
```

- shard 하나가 timeout이면 전체는 bounded다.
- shard 하나가 crash하거나 checksum이 다르면 전체는 exact가 아니다.
- 취소 플래그는 모든 스레드가 자주 확인하며, 취소 당시 상한을 모아 안전한 결과를 만든다.
- 병렬 탐색 순서는 달라도 exact 점수와 build ID는 단일 스레드와 같아야 한다.
- 시간 제한 bounded의 방문 순서와 하한은 하드웨어에 따라 달라질 수 있지만, 반환하는 상한과 gap은 항상 안전해야 한다.

## 5. 구현 단계

### P0 — 기준선과 병렬 계약

- 현재 실제 425개 fixture의 단일 Worker exact, 5초, 30초 결과를 보존한다.
- `ParallelShard`, `ParallelProgress`, `ParallelResult`, 하드웨어 profile schema를 정의한다.
- 작은 exhaustive 문제에서 분할 전후 exact·동점·상한이 같은 테스트를 먼저 만든다.
- 측정 항목: wall time, CPU time, CPU 사용률, thread별 busy ratio, peak working set, 평가 수, 중복 평가 수, steal 수, shard 불균형.

### P1 — JavaScript Worker pool

- 기존 계산식과 optimizer를 유지한 채 shard 시작점과 shard 결과 반환 API를 추가한다.
- `d4-worker-client.js`가 네이티브 하드웨어 profile을 우선 사용하고, 일반 브라우저에서는 `navigator.hardwareConcurrency`로 fallback한다.
- 감지된 논리 스레드 수만큼 Worker를 만들고, 준비된 shard를 동적으로 배정한다.
- 후보 데이터 복제 비용, Worker 시작 비용, 메모리 피크를 계측한다.
- 기존 단일 Worker를 fallback으로 유지하고, pool 초기화 실패 시 자동 복귀한다.

이 단계는 빠르게 사용할 수 있는 병렬화다. 다만 Web Worker별 JS heap과 후보 데이터 복제로 인해 저메모리 PC나 많은 스레드에서 효율이 제한될 수 있다.

2026-08-28 구현 기록:

- `d4-global-optimizer.js`에 결정론적 `ParallelShard` plan, shard 전용 문제 생성, 완전성 감사, 안전 병합을 추가했다. 작은 64개 완성 조합은 8개 shard의 합집합과 정확히 같고, 중복·누락 없이 단일 oracle과 같은 `exact 2255` 및 동점 build ID를 반환한다.
- `d4-optimizer-worker.js`는 `prepare-parallel` → `parallel-init` → `optimize-parallel-shard` → `merge-parallel` 프로토콜을 지원한다. 완료하지 않은 shard의 plan upper를 병합 결과에 남기므로 부분 완료/timeout은 `exact`가 될 수 없다.
- `d4-worker-client.js`의 `ParallelWorkerClient`는 명시 설정 또는 `navigator.hardwareConcurrency`로 논리 스레드 수를 결정하고, `threads × shardFactor`의 작업을 준비된 Worker에 동적으로 배정한다. Worker pool 실패 시 현재 단일 `WorkerClient` 경로는 그대로 유지한다.
- Node의 실제 worker-thread에서 브라우저 Worker 코드를 실행한 회귀는 2 Worker·8 shard·`exact 2255`를 확인했다. 이는 실제 425개 성능 또는 저메모리 동작의 증명이 아니며, UI 기본 경로 승격은 P2 이후에만 허용한다.

### P2 — JavaScript 병렬 성능 Gate

- 배포 PC마다 1 / 절반 / 전체 논리 스레드를 자동 calibration fixture로 짧게 비교한다.
- 실제 실행 기본은 사용자의 요구대로 전체 논리 스레드이며, calibration은 작업 조각 크기만 조정한다.
- 실제 425개에서 단일 Worker 대비 wall time 개선, 전체 CPU 점유, 메모리 안전성을 기록한다.
- exact 결과와 동점 ID가 같고, 전체 스레드가 단일 Worker보다 빨라야 기본 pool로 승격한다.

2026-08-28 1차 측정(불승격): 실제 425개 물리 근거리 fixture에서 shard plan 자체는 8 shard 기준 약 1.1초에 만들었지만, planner 결과를 주 스레드로 복사하고 다시 각 Web Worker에 복제·초기화하는 비용 때문에 5초 예산 안에 첫 shard 결과를 받지 못했다. 초기 구현은 유효한 하한 없이 `invalid`가 될 수 있었고, 이를 발견해 planner가 얻은 full-domain feasible lower bound를 병합에 보존하고, shard plan이 예산의 30%(최대 1.5초) 안에 준비되지 않으면 남은 시간으로 기존 단일 Worker를 실행하는 fallback을 추가했다. fallback은 안전한 `bounded` 결과를 보장하지만 병렬 speedup은 아니다. 따라서 P1은 UI 기본 경로로 승격하지 않으며, 후보 저장소를 Worker마다 복사하지 않는 Rust 공유 메모리 경로(P3~P5)가 필요하다는 근거로 기록한다.

### P3 — Rust 계산 커널 동치

- JavaScript `ToramCalculationKernel`과 `BuildEvaluator`의 최적화 필요 필드만 Rust로 이식한다.
- 연산 순서, `floor`, 크리티컬 경계, 방어·관통, MAXHP·MAXMP·AMPR·ASPD hard constraint를 그대로 보존한다.
- 모든 실제 후보 단독·결정적 무작위 합계·경계 fixture에서 JavaScript와 점수 및 feasible 판정을 정확히 일치시킨다.
- 불일치가 하나라도 있으면 Rust 결과를 추천·가지치기에 사용하지 않는다.

2026-08-28 착수 기록: Tauri `d4_hardware_profile` 명령을 추가했다. `available_parallelism()`으로 현재 프로세스가 실제 사용할 수 있는 논리 스레드를 반환하고, Windows에서는 `GlobalMemoryStatusEx`로 총/가용 물리 메모리를 함께 반환한다. profile은 `logicalThreads × 8`의 초기 shard 목표와 `min(총 RAM × 60%, 가용 RAM × 75%) - 512MiB`의 큐 메모리 예산도 반환한다. CPU 스레드는 이 메모리 정책 때문에 줄이지 않으며, 이후 P5에서 큐 확장·깊이 우선 전환만 조절한다. 프런트 `getParallelHardwareProfile()`은 이 명령을 우선 사용하고 일반 브라우저·오류에서는 `navigator.hardwareConcurrency` 기반 profile로 fallback한다. 이는 Rust 계산식 이식이나 추천 경로 승격이 아니라 P5 ThreadPool·메모리 예산의 입력 계약이며, Rust 단위 테스트 5/5로 최소 1 thread와 메모리 범위를 검증했다.

동시에 `d4_parallel_runtime.rs`에 평가기와 독립적인 공유 작업 스케줄러와 shard 병합을 추가했다. task는 한 번만 atomic index로 점유하고 불변 후보 저장소는 참조로 공유한다. 병합은 initial feasible lower bound를 보존하지만 pending/failed shard upper를 숨기지 않으며, 동점은 build ID 사전식 순서를 사용한다. 1/2/16/64 thread 회귀와 pending·동점 병합 회귀를 통과했다. 아직 실제 D4 evaluator가 연결되지 않았으므로 이 모듈은 Tauri command에서 호출하지 않으며, P3의 JavaScript 동치 fixture가 준비된 뒤 P4/P5에 연결한다.

`tools/generate-d4-rust-evaluator-fixtures.mjs`는 JavaScript 계산 커널에서 summary 기준값을 생성한다. 생성기는 수식의 원천이 아니며 JavaScript 값을 fixture로 고정·대조하는 용도다.

2026-08-28 Rust summary evaluator 확장: `d4_native_evaluator.rs`는 physical short, magic long/저항, dual sword, unsheathe·critical-damage cap에 더해 active AMPR 선택, 발도→ATK conversion, 다중 내성, 고정 CRIT/최소 CDMG, 방어 무시·마방 절반 무시, skillStats·다층 배율, 확률 proc, 화살/서브 마도구, attack power mode, dual-bringer 마법 반영 fixture까지 JavaScript summary 값과 일치한다. 특히 JavaScript의 `x * (ratio / 100)` 연산 순서가 `x * ratio / 100`과 다른 floor 경계를 만들 수 있음을 fixture로 포착해 같은 순서를 보존했다. Rust 테스트는 13개로 늘었다.

2026-08-28 실제 데이터 parity Gate: Tauri command로 등록하지 않은 개발용 `d4_native_summary` JSON bridge와 `tools/test-d4-rust-native-parity.mjs`를 추가했다. 계보에서 후속 강화가 없는 실제 최종 크리스타 216개를 물리·마법·듀얼·화살·방패 중량·두루마리의 6 구조에 각각 적용하고, 같은 데이터에서 결정적으로 만든 192개의 8개-stat aggregate도 비교한다. 총 1,488건에서 damage·MAXHP·MAXMP·AMPR·평타 CRIT·ASPD 및 그 값으로 계산한 기본 D4 feasible 판정이 JavaScript와 일치한다. 조건부 옵션은 각 구조의 main/sub/armor 조건을 적용한 canonical stat vector로 넣는다. 이는 전수 단독과 결정적 aggregate parity이지만, 실제 후보 패키지의 계보/중복 제약을 포함한 full `BuildEvaluator` outcome 및 Rust exact solver parity는 P4에서 별도로 검증한다. 따라서 native evaluator/runtime은 아직 Tauri command·추천·상한에 연결하지 않는다.

### P4 — Rust 단일 스레드 exact

- 먼저 같은 shard·CandidateTree·상한·동점 규칙을 가진 단일 스레드 Rust solver를 만든다.
- 소형 oracle과 실제 425개 exact 결과가 JavaScript와 같은지 확인한다.
- 이 단계가 통과해야 언어 전환에 의한 차이와 병렬화 차이를 분리해서 진단할 수 있다.

2026-08-29 완료 기록: `d4_native_solver.rs`는 prepared D4 문제의 현재/Utility/Damage 초기해, 192개 후보 pool의 2회 coordinate pass, CandidateTree의 정규화된 split-key·heuristic·ID 정렬, 2축 box 분할, envelope bound, 64개 이하 완전 열거와 build-ID 사전식 동점을 Rust로 이식했다. Frontier work item은 고정 4슬롯 `Arc` 배열로 보관하고 bound/leaf aggregate는 JSON 변환 없이 Rust stats map으로 평가한다. 따라서 초기 프로토타입의 매-node `Vec`·path string·JSON object 할당을 제거했지만 탐색 의미는 JavaScript와 같다. `tools/test-d4-native-exact-p4.mjs`의 소형 exhaustive oracle 및 실제 425개 fixture 직접 비교(`D4_P4_REAL=1 D4_P4_VERIFY_JS=1`)에서 JS/Rust의 exact 점수 14,097과 최종 build ID가 일치했다. 동일 조건의 재측정에서 JS single-thread exact는 1,015,641ms(26,208,511회 평가), Rust는 148,833ms(26,198,199회 평가, 4,486,581개 방문 노드)로 Rust가 6.82배 빠르고 85.3% 짧았다. 이 개발용 bridge는 아직 Tauri command·추천 경로에 연결하지 않으며, P5에서만 공유 저장소 병렬 실행으로 확장한다.

### P5 — Rust 전체 CPU 병렬 엔진

- `available_parallelism()` 값을 명시한 전용 Rayon ThreadPool을 만든다.
- 공유 후보 저장소, work stealing, 전역 incumbent, 취소 token, 메모리 예산을 연결한다.
- Tauri async command로 시작·결과를 처리하고, 고빈도 진행 정보는 channel로 전달한다.
- `cancel_d4_optimization(jobId)`는 원자 취소 플래그를 설정한다.
- Tauri 배포에서는 Rust 엔진을 기본으로, 일반 브라우저에서는 P1 Worker pool을 사용한다.

2026-08-29 1차 구현·실측: `solve_exact_parallel`은 prepared 후보·CandidateTree·base context를 한 번만 생성해 공유하고, 루트 상자를 `available_parallelism() × 8` 목표로 결정론적으로 분할한다. 고정 4-slot box handle만 worker에 전달하고, atomic task index로 다음 shard를 가져가므로 빠르게 끝난 worker가 남은 shard를 이어서 처리한다. worker별 local heap과 전역 incumbent(원자 점수의 빠른 pruning + 동점 ID를 보존하는 짧은 mutex 갱신)를 사용해 exact와 사전식 동점을 보존한다. 개발 bridge `d4_native_parallel`은 요청 thread가 없으면 현재 프로세스의 `available_parallelism()`을 사용한다. 실제 425개 fixture에서 16 논리 스레드·130 shard가 단일 Rust와 같은 exact 점수 14,097/build ID를 반환했고, 단일 141,713ms에서 병렬 20,811ms로 6.81배 단축됐다. 소형 oracle은 1/2/16/64 요청 thread 모두에서 exact·동점·전 shard 완료를 확인한다.

2026-08-29 P5 연결 완료: Tauri `d4_optimize_parallel(jobId, problem)`은 감지한 모든 논리 스레드로 cancellable Rust 탐색을 `spawn_blocking`에서 실행하며, `cancel_d4_optimization(jobId)`는 원자 취소 신호만 설정한다. 취소된 탐색은 최선의 유효 incumbent가 있더라도 `cancelled`, `exact:false`, `upperBound:null`으로만 반환한다. `assets/js/d4-native-client.js`는 결과의 package ID를 준비된 JavaScript 후보 객체와 최종 `BuildEvaluator` outcome으로 다시 연결하고, 데스크톱에서는 이 경로를 우선 사용한다. 명령 시작·직렬화·실행 오류는 기존 JavaScript Worker로 자동 fallback한다. P5 취소 회귀와 native client bridge 회귀를 추가했다. 공유 CandidateTree/compact work handle 구조는 Worker-pool의 후보 heap 복제를 없애지만, 저메모리 장비의 peak working-set·장시간 진행 보고·Windows 설치본 E2E는 P6/P8의 별도 계측·배포 Gate로 남긴다.

### P6 — CPU 병렬 검증·승격

- mock 하드웨어 profile 1/2/4/8/16/64 스레드에서 할당 정책을 검증한다.
- 실제 장비에서는 1 / 논리 스레드의 절반 / 전체 논리 스레드를 각각 콜드 반복 측정한다.
- 전체 논리 스레드 실행에서 CPU 사용률, speedup, peak memory, exact 일치, 취소 지연을 기록한다.
- 목표 성능은 우선 단일 JavaScript 대비 유의미한 단축이다. 10초 미달도 정확히 기록하며 거짓 exact로 승격하지 않는다.

2026-08-29 완료·승격: `parallel_scheduler_preserves_exact_result_at_supported_thread_counts`가 1/2/4/8/16/64 요청 thread에서 small exhaustive 결과와 같은 `exact`·사전식 build ID를 확인한다. `tools/benchmark-d4-native-p6.mjs`와 Windows peak-working-set sampler는 release `d4_native_parallel.exe`로 실제 425개 물리 근거리 fixture를 새 프로세스에서 측정한다. 1 thread 두 cold run은 141.36초/140.58초(peak 29.31MB/29.27MB), 8 thread는 21.93초(peak 40.32MB), 16 thread는 21.78초·20.97초(peak 42.94MB/42.89MB)였으며 모두 score 14,097·동일 build ID·전 shard 완료를 반환했다. 16 thread의 1-thread 대비 wall-time speedup은 6.70~6.74배이고, `threadsUsed:16`, 130 shard를 확인했다. 16-thread run의 process CPU time은 233.8초으로 wall 21.0초 동안 약 11.1 logical-core 상당(약 70%)이었다. 즉 모든 논리 thread를 생성·배정하지만 이 fixture에서는 shard 불균형/전역 가지치기 때문에 16개가 계속 포화되지는 않는다. Rust CPU 경로는 기존 JavaScript exact 1,015.6초보다 약 48배 짧다. 16-thread timed cancellation은 100ms 신호 뒤 wall 358~359ms/solver 177~180ms, peak 16.06~20.64MB, `cancelled`·`exact:false`·0/130 completed shard로 종료했다. 따라서 Tauri desktop의 Rust 경로를 CPU 기본 경로로 승격한다. 10초 exact와 8→16 scaling 개선은 완료 조건이 아니며, 다음 Pair-native 성능 작업의 대상이다.

### P7 — GPU 타당성 Gate

CPU 병렬 엔진의 profile에서 동일 계산을 큰 batch로 수행하는 구간이 전체 시간의 50% 이상일 때만 GPU prototype을 만든다.

1. `wgpu`로 discrete/integrated 어댑터를 동적으로 탐지한다.
2. 65,536개 이상의 bound 또는 leaf 평가 batch를 대상으로 CPU 전체 스레드와 비교한다.
3. GPU의 f32 결과는 exact 가지치기에 사용하지 않는다.
4. 정수·고정소수점 커널 또는 보수적으로 올림한 상한이 JavaScript/Rust f64 property test를 전부 통과한 경우에만 상한 보조로 검토한다.
5. 완성 후보는 CPU가 최종 점수와 동점 ID를 다시 계산한다.
6. 전송·dispatch를 포함해 전체 CPU 대비 P95 1.5배 이상 빠르고, 전체 exact wall time도 개선될 때만 기본 활성 후보가 된다.

GPU가 이 Gate를 통과하지 못하면 코드는 실험 경로로 격리하거나 제거하고 CPU-only를 유지한다.

2026-08-30 완료·CPU-only 결정: P6의 실제 native 탐색에는 GPU prototype의 선행조건인 ``전체 시간의 50% 이상을 차지하는 동일 대량 batch``가 확인되지 않았다. 가장 가까운 Gate F profile은 JavaScript 탐색의 상한 평가 12,895,255회·487.4초와 완성 조합 평가 8,573,588회·328.1초를 보여 주지만, 두 시간은 중첩 inclusive 값이라 합산하거나 어느 하나를 전체의 절반 이상인 독립 batch로 해석할 수 없다. P6 Rust 병렬 탐색도 각 shard의 동적 heap, 후보 조합별 `Stats` map 생성, 전역 incumbent 갱신과 즉시 bound prune가 얽혀 있어 65,536개 단위로 모아 보내도 결과가 같은 규칙적 커널을 식별하지 못했다. 특히 GPU f32 결과는 exact pruning에 사용할 수 없고, CPU 재평가·전송·dispatch까지 더하면 이 상태에서 P7의 P95 1.5배 및 전체 wall-time 개선을 입증할 수 없다. 따라서 `wgpu` 의존성이나 숨은 실험 경로를 추가하지 않고 Rust CPU 기본 경로를 유지한다. GPU는 향후 profile이 독립적인 대량 bound/leaf kernel이 전체의 50% 이상임을 보인 뒤에만 다시 연다. 그때에도 65,536개 이상 batch의 전송 포함 CPU/GPU P95 비교와 보수 상한 property test, 최종 CPU 재평가를 모두 통과해야 한다.

### P8 — 배포·fallback

- cache key에 계산식 버전, 엔진 버전, 분할 정책, thread 수, GPU 정책을 포함한다. exact 결과는 같은 계산식 버전에서 재사용할 수 있지만 bounded 결과는 다른 병렬 정책의 성능을 가리지 않게 분리한다.
- UI에 엔진(JS/Rust), 사용 스레드 수, GPU 사용 여부, elapsed, 평가 수, 인증 gap을 표시한다.
- Rust command 실패 시 JavaScript Worker pool, pool 실패 시 기존 단일 Worker 순으로 fallback한다.
- 설치 파일에서 Rust 병렬 엔진·취소·진행 channel·fallback을 실제로 검증한다.

2026-08-30 완료: `d4-native-client.js`의 memory cache key는 계산식(`d4-native-evaluator.v1`), 엔진(`d4-native-solver.v1`), CandidateTree 분할 정책, 감지한 logical thread 수, P7 GPU 정책(`cpu-only.p7`)과 time budget을 모두 포함한다. 따라서 다른 실행 계약의 exact/bounded 결과가 섞이지 않는다. native 결과와 진행 상태는 `engine: rust-native`, `threadsUsed`, GPU 정책을 반환하며, 결과 UI는 Rust CPU/스레드/GPU 미사용·경과·평가·gap을 함께 표시한다. native command 시작·직렬화·실행 실패는 기존 JavaScript Worker로, Worker 실패는 기존 invalid-safe 결과로 귀결되는 fallback 계약을 유지했다. P8 중 Cargo의 개발용 `src/bin/d4_native_exact.rs`가 NSIS 기본 실행 파일로 선택되는 배포 결함을 발견해 `default-run = "toram-online-auto-build-calculator"`로 실제 Tauri 앱을 고정했다. release NSIS build log가 실제 앱 EXE 선택을 확인했고, 새 설치 파일을 격리된 `C:\\Temp\\ToramD4P8-20260830`에 silent 설치한 뒤 3초 실행·silent 제거까지 모두 exit 0으로 통과했으며 임시 설치 폴더도 제거됐다. `test-d4-native-client`의 실제 command bridge/cache 계약, Worker runtime fallback/UI 계약, small native exact와 Rust 37개 단위 회귀도 통과했다.

2026-08-30 runtime 정정: 위 완료는 cache 표시 형식·fallback 연결·패키징 smoke 범위다. 실제 native command에는 5초/30초 deadline이 전달되지 않고, Rust progress channel·bounded checkpoint·resume frontier가 없으며, 고정 shard local heap 때문에 한 코어 tail이 발생한다. 잠금 크리스타도 native 통합 정확성 Gate가 없다. 따라서 native runtime 전체는 완료가 아니며, `d4-native-runtime-correction-plan.md`의 N0~N6를 통과해야 실사용 완료로 다시 승격한다.

## 6. 필수 회귀

### 정확성

- 단일/병렬 exact 점수와 build ID 일치
- shard 분할 합집합·비중복 property
- 모든 shard upper가 실제 shard 최고값 이상
- incumbent 갱신 경쟁과 동점 ID 결정성
- worker 수와 입력 순서 변화에도 exact 결과 동일
- timeout·취소·worker crash에서 exact 오표기 없음
- JavaScript/Rust 계산식 경계값 완전 일치

### 성능·자원

- 1/2/4/.../전체 논리 스레드 speedup 곡선
- thread별 busy ratio와 work stealing 균형
- peak working set과 큐 메모리 예산 준수
- Worker 데이터 복제·Rust 공유 저장소 크기
- 5초/30초 bounded gap 및 long exact wall time
- GPU가 있거나 없는 PC, integrated-only PC, 저메모리 PC fallback

### 배포

- Tauri 개발·release 빌드
- Windows x64 설치본에서 하드웨어 profile 감지
- 일반 브라우저 Worker fallback
- 계산 중 새 요청·사용자 취소·창 종료
- 캐시 버전 분리와 기존 저장 세팅 호환

## 7. 완료 기준

병렬화 1차 완료는 다음을 모두 만족할 때다.

- 배포 PC의 감지된 모든 논리 CPU 스레드를 사용한다.
- 단일 스레드와 같은 exact 점수·build ID를 반환한다.
- 전체 탐색 공간의 shard 증명과 안전한 전역 gap 병합이 자동 회귀로 보호된다.
- 실제 425개에서 단일 Worker보다 wall time이 단축된다.
- 메모리 부족·Worker/Rust/GPU 실패 시 안전한 fallback이 동작한다.
- 현재 개발 PC뿐 아니라 mock 1~64스레드 및 서로 다른 RAM/GPU profile에서 하드코딩 없이 동작한다.

10초 exact는 별도 최종 성능 완료 기준으로 유지한다. 병렬화가 완료돼도 10초를 넘으면 결과를 그대로 기록하고 다음 Pair-native 노드 표현 Gate로 이어간다.

## 8. 공식 기술 근거

- Tauri v2 command와 async 실행: https://v2.tauri.app/develop/calling-rust/
- Tauri Rust→frontend channel/streaming: https://tauri.app/develop/calling-frontend/
- Rayon 명시적 ThreadPool과 work stealing: https://docs.rs/rayon/latest/rayon/struct.ThreadPoolBuilder.html
- wgpu compute 지원 확인: https://docs.rs/wgpu/latest/wgpu/struct.DownlevelFlags.html
