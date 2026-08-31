# D4 native bounded·진행·재개·tail·고정 크리스타 교정 계획

- 상태: N0~N6 완료
- 기준일: 2026-08-31
- 적용 범위: Tauri Rust native D4 전역 크리스타 최적화 경로
- 상위 정확성 계약: `d4-exact-optimization-plan.md`
- 기존 병렬화 기록: `d4-parallel-exact-optimization-plan.md`
- 현재 상태 기준: `docs/handoff/current-development-handoff.md`, 실제 코드, 실행한 회귀 결과

## 1. 목적

현재 native 경로는 특정 물리 근거리 fixture에서는 약 21초 exact를 달성했지만, 제품이 요구하는 시간 제한형 anytime optimizer로 동작하지 않는다. 이 계획의 목적은 다음 다섯 요구를 하나의 일관된 실행 계약으로 구현하는 것이다.

1. 사용자가 계산을 시작한 시점부터 30초 안에 `exact` 또는 인증 가능한 `bounded` 결과를 반환한다.
2. native 탐색의 실제 진행 상황을 UI에 지속적으로 반영한다.
3. 마지막 소수의 무거운 shard 때문에 대부분의 CPU가 쉬는 tail 현상을 제거한다.
4. `bounded` 결과의 정밀 계산 버튼이 처음부터 다시 계산하지 않고 남은 탐색을 이어서 `exact`까지 진행한다.
5. 잠긴 고정 크리스타를 정확히 한 번 반영하고, 잠긴 슬롯을 전역 탐색의 교체 후보에서 제외한다.

좋은 추천을 빨리 찾는 것만으로는 완료가 아니다. `bounded`의 상한과 gap, 재개한 frontier의 완전성, 고정 크리스타의 효과·계보·슬롯 제약, 최종 `exact`의 점수와 build ID가 모두 증명돼야 한다.

## 2. 현 상황 보고

### 2.1 30초 제한이 native에 전달되지 않는다

UI의 `launchD4Worker(..., timeLimitMs)`는 5,000ms 또는 30,000ms를 options에 넣지만, `d4-native-client.js`가 Tauri에 전달하는 인자는 `jobId`와 `problem`뿐이다. Rust `d4_optimize_parallel`도 deadline을 받지 않고 취소용 `AtomicBool`만 solver에 넘긴다.

따라서 native는 시간 만료로 `bounded`를 반환할 수 없고, 다음 셋 중 하나로만 끝난다.

- frontier가 모두 소진됨: `exact`
- 사용자가 취소함: `cancelled`
- 유효해 또는 실행 조건이 없음: `invalid`

현재 UI의 5초/30초 숫자는 native 실행 시간 계약이 아니다. 사용자가 보고한 20분 초과 실행은 이 단절 때문에 중지되지 않았다.

### 2.2 진행 상황은 실제로 streaming되지 않는다

native client는 Rust 호출 직전에 `native-prepared` 진행 이벤트를 한 번 보낸다. 이후 Rust command가 끝날 때까지 평가 수, lower/upper bound, gap, 활성 스레드, 남은 frontier 변화가 UI로 전달되지 않는다.

결과적으로 현재 진행 UI는 native 계산이 살아 있는지, tail에 진입했는지, 최선해가 개선됐는지 판단할 수 없다. P8 기록의 “진행 상태 표시”는 필드 표시 형식만 추가된 것이며 실제 native progress channel 완료를 뜻하지 않는다.

### 2.3 tail shard가 CPU 사용률을 떨어뜨린다

현재 solver는 시작할 때 `logicalThreads × 8`을 목표로 약 130개 shard를 만든 뒤 atomic index로 한 번씩 배정한다. 각 worker는 받은 shard의 `BinaryHeap`을 끝까지 독점한다.

초기 shard 수가 충분해도 실제 탐색량은 균등하지 않다. incumbent가 갱신되면 어떤 shard는 즉시 prune되지만 다른 shard는 수백 배 오래 남을 수 있다. 쉬는 worker는 다른 worker의 local heap에서 노드를 가져올 수 없다. 현재 사건 중 24개 process thread가 존재했지만 5초 동안 process CPU time은 5.03초만 증가해 사실상 한 코어만 일하는 tail 상태가 확인됐다.

초기 shard 수만 늘리는 것은 근본 해결이 아니다. 분할 비용과 메모리만 늘고, 실행 중 드러나는 난이도 편차를 교정하지 못한다.

### 2.4 정밀 계산은 이어서 계산하지 않는다

현재 정밀 계산 버튼은 같은 problem을 30,000ms option으로 다시 `optimize`한다. native에는 checkpoint/frontier/session 계약이 없고 cache key도 time budget을 분리하므로, 이전 bounded 탐색을 이어받는 구조가 아니다.

native가 현재 exact-only이기 때문에 보통 bounded 버튼 자체도 정상적인 native 결과 흐름에서 나오지 않는다. JavaScript fallback에서 bounded가 나와도 Rust exact continuation으로 frontier를 이전할 수 없다.

### 2.5 고정 크리스타는 부분 구현됐지만 제품 정확성 Gate가 없다

컴파일러는 잠긴 크리스타를 해당 부위의 모든 package에 포함해 domain을 제한한다. 그러나 설계 문서의 계약인 “고정 효과를 먼저 합산하고 잠기지 않은 슬롯만 탐색”과는 구조가 다르다.

현재 위험은 다음과 같다.

- 잠긴 입력을 찾지 못하면 `lockedAt()`이 `null`을 반환해 빈 슬롯처럼 package를 만들 수 있다.
- JavaScript problem의 `diagnostics`는 Rust `NativeProblem`이 받지 않으며 native client도 command 전에 잠금 오류를 강제 차단하지 않는다.
- 고정 효과가 정확히 한 번 적용되는지, 잠금 후보가 결과에서 교체되지 않는지, 고정 크리스타와 탐색 후보 사이 계보 충돌이 유지되는지 검증하는 native 통합 회귀가 없다.
- 현재 실제 425개 장기 회귀는 `currentCrystas: []`, `locks: []`로 만들어져 잠금 경로를 검증하지 않는다.

따라서 “코드에 locks 분기가 있다”는 사실만으로 고정 크리스타 반영 완료를 주장할 수 없다.

### 2.6 기존 성능 수치의 적용 한계

P6의 약 21초는 하나의 425개 물리 근거리 fixture 결과다. 이는 모든 무기·거리·Utility·잠금 조합의 상한이 아니다. 상한이 느슨하거나 feasible incumbent가 늦게 나오는 시나리오는 훨씬 오래 걸릴 수 있다. 앞으로는 단일 fixture 수치를 일반 실행 시간으로 표현하지 않는다.

## 3. 목표 실행 구조

```text
UI 입력
  │
  ├─ 문제 컴파일
  │    ├─ 고정 크리스타 검증·고정 효과 분리
  │    └─ 잠기지 않은 슬롯 domain 생성
  │
  └─ Native Search Session
       ├─ 공유 best-bound frontier
       ├─ 동적 split / work stealing
       ├─ 전역 incumbent + 인증 upper bound
       ├─ 주기적 progress snapshot
       └─ 30초 deadline
             ├─ frontier 소진 → exact
             └─ frontier 보존 → bounded + continuationId
                                      │
                                      └─ 정밀 계산 → 같은 session 재개 → exact 또는 사용자 취소
```

핵심은 `한 번 호출하면 끝날 때까지 점유하는 solver`를 `중단 가능한 증명 상태를 보존하는 search session`으로 바꾸는 것이다.

## 4. 불변 계약

### 4.1 30초 bounded 계약

- 최초 실행의 제품 시간 예산은 UI 클릭부터 결과 렌더까지 30초다.
- JavaScript 컴파일·Pareto 준비·직렬화에 사용한 시간을 먼저 차감하고 남은 예산을 Rust에 전달한다.
- Rust는 deadline 도달 전에 cooperative yield를 시작해 모든 active work를 frontier로 되돌리고 결과를 병합한다.
- deadline 시 feasible incumbent가 있으면 `bounded`, frontier가 이미 증명 종료됐으면 `exact`를 반환한다.
- feasible incumbent가 없지만 feasible 가능성이 남아 있으면 `invalid`로 거짓 단정하지 않고 별도 `no-incumbent-yet` 상태 또는 진단을 반환한다. UI 정책은 구현 Gate에서 확정하되 `exact`로 승격하지 않는다.
- `bounded.upperBound`는 반환 시점의 모든 pending·active work upper의 최댓값 이상이어야 한다.
- `optimalityGap = max(0, upperBound - lowerBound) / max(abs(lowerBound), epsilon)` 계약을 JS와 Rust에서 동일하게 유지한다.

### 4.2 progress 계약

Tauri channel은 coordinator가 일정 간격으로 snapshot을 보내고 worker hot loop가 직접 UI event를 만들지 않는다. 최소 필드는 다음과 같다.

- `sessionId`, `stage`, `status`, `elapsedMs`, `deadlineRemainingMs`
- `lowerBound`, `upperBound`, `optimalityGap`
- `evaluations`, `visitedNodes`, `prunedByBound`, `prunedByConstraint`
- `threadsTotal`, `threadsActive`, `readyWorkItems`
- `completedWorkItems`, `splitCount`, `stealCount`
- `largestPendingEstimate`, `tailDetected`

UI는 원시 조합 비율을 진행률로 위장하지 않는다. 경과 시간, 최선 점수, 인증 gap, 활성 스레드, 남은 작업 및 tail 상태를 표시한다.

### 4.3 exact continuation 계약

- bounded 결과는 `continuationId`와 같은 input/계산식/엔진/분할/GPU 정책 signature를 반환한다.
- session은 immutable prepared problem, incumbent, 공유 frontier, 누적 counters를 보존한다.
- 정밀 계산 버튼은 새 problem을 만들거나 초기 seed부터 재시작하지 않고 해당 session을 resume한다.
- resume 뒤 evaluation/visited counter는 단조 증가해야 한다.
- 입력 변경, 계산식 버전 변경, 잠금 변경, 앱 종료, 명시적 폐기 시 session을 무효화한다.
- 정밀 계산은 exact 또는 사용자 취소까지 이어가되 progress와 취소 기능을 계속 제공한다.
- 메모리 보호를 위해 session 수, TTL, frontier memory budget을 제한한다. eviction된 session은 “재개 불가”를 명시하고 사용자의 확인 없이 새 exact를 재시작하지 않는다.

### 4.4 tail-free scheduler 계약

- 탐색 가능한 work item이 남아 있고 분할 가능하다면 idle worker가 존재해서는 안 된다.
- worker가 shard 전체를 소유하는 대신 공유 best-bound frontier 또는 work-stealing deque에서 작은 work unit을 가져간다.
- 큰 node는 조합 수·최근 처리 시간·남은 active worker를 기준으로 실행 중 재분할한다.
- deadline 직전 active worker는 현재 node와 local frontier를 손실 없이 공유 frontier/checkpoint로 반환한다.
- scheduling 순서가 달라도 safe upper와 최종 exact score/build ID는 같아야 한다.
- bounded incumbent는 스케줄에 따라 달라질 수 있으므로 cache/session signature에 scheduler policy version을 포함한다.

### 4.5 고정 크리스타 계약

- 잠긴 비어 있지 않은 슬롯은 반드시 데이터의 정확한 크리스타 하나로 해석돼야 한다. 실패하면 계산을 시작하지 않는다.
- 잠긴 빈 슬롯은 “빈 상태 고정”으로 명시하며 후보를 넣지 않는다.
- 고정 크리스타의 활성 조건을 장비 구조에 맞춰 한 번 resolve한다.
- `fixedStatDelta`, `fixedCrystaIds`, `fixedSlots`를 problem의 명시 필드로 분리한다.
- evaluator와 bound는 항상 `fixedStatDelta + searchedStatDelta`를 사용한다.
- 결과 `statDelta`와 최종 JS 재평가에도 고정 효과를 정확히 한 번 포함한다.
- 잠기지 않은 슬롯만 candidate domain과 socket cost에 포함한다.
- 고정 크리스타와 후보 사이의 동일 장비 중복·계보 충돌·부위 제한을 컴파일 시 제거한다.
- build ID와 UI 결과는 고정/탐색 크리스타를 원래 8개 슬롯 순서로 복원한다.

## 5. 구현 단계

### N0 — 실패 fixture와 계측 기준 고정

1. 사용자가 20분 이상 실행한 현재 입력을 개인 정보 없는 deterministic problem fixture로 저장한다.
2. 무잠금 P6 fixture, 1개 잠금, 한 부위 2개 잠금, 8개 잠금, 잠긴 빈 슬롯, 알 수 없는 잠금 fixture를 준비한다.
3. 현재 코드에서 클릭→결과 wall time, native elapsed, thread active 추이, shard별 처리량을 기록한다.
4. 기존 P6 21초 수치와 새 장기 fixture를 별도 행으로 관리한다.

완료 기준: 현재의 deadline 무시, progress 부재, tail CPU 하락, 잠금 실패를 자동 또는 재현 가능한 절차로 다시 만들 수 있다.

2026-08-30 완료 기록: 사용자가 제공한 실제 26분 실행 화면을 `tools/fixtures/d4-native-runtime-26min-revenir.json`으로 고정했다. 이 fixture는 Lv.325 한손검+방패/경량옷, 보스 Lv.300 DEF·MDEF 1,950, 선택 타격 루브닐 3타(소모 스택 2)·강타 태그의 최종 계수 32.805·상수 400, 현재 특수 크리스타 에투왈, 금지 크리스타 오로로 콜론·카나요간을 기록한다. 사용자가 에투왈을 포함한 8개 슬롯 모두 잠금 해제였음을 확인했으므로 재현 fixture도 8개 슬롯을 모두 미고정으로 둔다. 같은 입력에서 에투왈 슬롯만 고정한 사용자 측정은 118.83초이며, 완료 모드와 결과는 자동 캡처하지 못했으므로 fixture에는 사용자 보고 경과 시간으로만 별도 보존한다. `tools/test-d4-native-runtime-n0.mjs`가 컴파일 diagnostics 0, 완결 Pareto 준비, 화면의 MAX MP 2,275, 잠금 0/1/2/8개(명시적 빈 슬롯 포함)와 알 수 없는 잠금 입력의 현재 compiler 진단을 확인한다. 이 회귀는 현 bridge가 `timeLimitMs`를 native command로 보내지 않고 native command에 deadline/progress protocol도 없음을 명시적으로 검출한다. prepared package 수는 무기/방어구/추가/특수 1,102/859/770/1,004이며 현재 에투왈 조합은 AMPR·평타 CRIT hard constraint를 충족하지 않는다. 따라서 이 fixture는 탐색 초기에 유효 incumbent를 찾아야 하는 N0 장기 실행 경계다. `tools/measure-d4-native-n0.mjs`는 기본 5초 명시 취소로 process wall/native elapsed/CPU/working set/thread sample을 수집하며, per-shard throughput과 UI progress가 현재 제공되지 않음을 결과에 기록한다. 같은 도구로 에투왈만 고정해 한 번 완주한 현 환경 측정은 16 threads, exact, solver 12,348ms/wall 12,541.378ms/CPU 156,031.25ms/peak 25.81MiB였다(`tools/fixtures/d4-native-runtime-26min-revenir-locked-measurement.json`). CPU는 처음 10초 약 13~14 logical cores에서 마지막 2초 9.41 cores, process thread 20→9로 하락했다. 이는 tail 하락의 재현 기준이지만 26분 사용자 실행의 한 코어 tail과 동일하다고 해석하지 않는다. 사용자 118.83초와 현 12.54초는 실행본·환경·입력 상태 차이를 아직 분리하지 못했으므로 서로 대체하지 않는다. 사용자가 보고한 26분은 기준으로 보존하되, deadline 도입 전 같은 무잠금 native exact를 다시 장시간 실행해 기준 수치를 덮어쓰지 않는다.

### N1 — 고정 크리스타 통합 검증

1. 현재 compiler가 잠금 입력을 먼저 검증하고 잠긴 후보를 모든 해당 부위 package에 보존하는 계약을 회귀로 유지한다.
2. 잠금 diagnostics가 하나라도 있으면 native/Worker 공통으로 계산을 차단하는지만 확인한다.
3. JS optimizer와 Rust `NativeProblem`을 0/1/2/8개 잠금 fixture로 대조해, 잠긴 슬롯이 결과에서 바뀌지 않는지 확인한다.
4. seed, bound, leaf, result restoration이 잠긴 효과를 정확히 한 번 반영하는지 회귀로 확인한다.
5. 고정/후보 계보 및 동일 장비 중복을 property test로 감사한다.

완료 기준: 잠금 0/1/2/8개에서 oracle과 native의 score/build ID가 같고, 잠긴 슬롯은 어떤 결과에서도 바뀌지 않는다.

2026-08-30 범위 정정: 사용자는 에투왈 고정 기능 자체가 정상 동작하며, 앞선 장기 실행은 고정 체크가 빠진 조작/표시 문제였음을 확인했다. 따라서 N1은 고정 기능을 다시 설계하거나 교체하지 않는다. 현재 compiler 회귀와 native/UI 통합 회귀로 정상 계약을 보존하는 검증 단계로만 진행하며, 실제 실패가 확인될 때에만 교정 구현을 연다.

2026-08-30 완료 기록: `node tools/test-d4-native-locks-n1.mjs`가 실제 compiler 입력으로 0/1/2/8개 잠금과 알 수 없는 잠금 diagnostic을 준비하고, 축소한 결정적 domain을 Rust `d4_native_parallel`에 전달한다. 네 경우 모두 exact 결과의 package ID가 compiler가 건넨 package로 복원되며, 특수장비의 에투왈 단일 잠금·에투왈/오르그 이중 잠금은 결과 package에서도 보존된다. 최종 `statDelta`는 선택된 네 package의 합과 같아 각 package 효과가 한 번만 반영됨을 확인한다. 이 Gate는 현재 고정 기능이 정상이라는 사용자 확인과 일치하며, 고정 로직을 변경하지 않았다.

### N2 — 중단 가능한 search state 도입

1. tree 준비, incumbent, frontier, counters를 `NativeSearchSession`으로 분리한다.
2. work item을 안전한 yield 경계에서 다시 queue에 넣을 수 있게 한다.
3. frontier가 남은 종료를 `bounded`로 직렬화한다.
4. pending/active upper를 빠뜨리지 않는 checkpoint completeness audit를 추가한다.
5. deadline과 사용자 cancel을 구분한다. deadline은 session 보존, cancel은 정책에 따라 보존/폐기를 명시한다.

완료 기준: 임의 node/evaluation 시점에 중단·재개해도 무중단 exact와 같은 결과가 나오며 누락·중복 work item이 없다.

2026-08-30 완료 기록: `d4_native_solver::NativeSearchSession`이 tree·requirements·incumbent·frontier·counter를 메모리 내 세션으로 보유하고 `run_slice(node_budget)`가 safe node 경계에서 `bounded` 결과와 현재 frontier upper를 반환한다. `NativeSearchCheckpoint`는 problem·incumbent·counter·frontier의 네 tree path/upper를 `toram.d4-native-search-checkpoint.v1` JSON으로 직렬화하고, 복원 시 중복 path·비유한 upper·존재하지 않는 tree path를 거부한다. checkpoint는 node 사이에서만 생성하므로 active work는 0이고 frontier가 모든 미해결 work다. 작은 동점 oracle에서 1-node slice와 JSON checkpoint 왕복 뒤 반복 재개 결과가 무중단 `solve_exact`와 같은 score/build ID임을 Rust 회귀로 확인했다. Tauri job/continuation registry와 UI deadline/cancel 명령 연결은 session 기반을 사용하는 N4의 범위다.

### N3 — 동적 tail 분할과 work stealing

1. 고정 shard 독점 방식을 공유 frontier 또는 work-stealing 구조로 교체한다.
2. worker가 idle 상태가 되면 가장 큰 splittable node를 재분할한다.
3. small-box 완전 열거도 큰 단일 leaf batch가 되면 prefix 단위로 나눌 수 있게 한다.
4. incumbent 읽기·counter 갱신·queue lock의 contention을 profile하고 batch atomic update를 적용한다.
5. thread별 busy time, longest work item, split/steal 수를 기록한다.

완료 기준: splittable work가 있는 동안 한 코어 tail이 재현되지 않고, 모든 thread 수에서 exact 결과와 tie ID가 유지된다.

2026-08-30 착수 기록: `d4_parallel_runtime::run_work_stealing`이 shared FIFO frontier와 active-work counter를 제공한다. worker는 ready queue와 active work가 동시에 0일 때만 종료하므로, 다른 worker가 분할해 넣은 child work를 idle worker가 계속 가져갈 수 있다. binary-tree regression은 8 workers에서 runtime 중 생성된 127개 work를 누락·중복 없이 모두 처리하고 steal을 확인한다.

2026-08-31 완료 기록: `solve_exact_parallel_with_control`은 초기 shard를 worker-local heap에 독점 배정하던 방식을 제거하고, 모든 worker가 하나의 max-priority `BinaryHeap<WorkItem>` frontier에서 node를 꺼내도록 교체했다. node 분할 후 child는 같은 frontier로 즉시 되돌아가며, queue가 비었어도 active worker가 있으면 종료하지 않으므로 새 child를 다시 가져갈 수 있다. `expand_parallel_node`는 safe node 단위로만 child를 반환하고, 작은 box는 기존의 최대 64 complete-combination 경계를 유지해 단일 leaf가 무한히 커지지 않는다. terminal native 결과의 `scheduler`에는 split 수, active wait 뒤 재획득한 work의 `stealCount`, 총/worker별 busy microseconds, 최장 work-item 시간을 포함했다. 8^4 동점 oracle은 serial exact와 parallel exact의 score/build ID가 같고, 초기 shard보다 더 많은 descendant node가 drain됨을 확인한다. 기존 1/2/4/8/16/64-thread exact/tie 회귀도 유지한다. 실제 26분 입력 fixture는 unbounded exact를 다시 실행하지 않고 16 thread·5초 explicit cancel만 계측했다: solver 5,000ms, wall 5,262.213ms, CPU 71,953.125ms(약 13.7 logical cores), split 1,732,518회, worker busy 4.527~4.566초, longest work item 11.547ms였다. `stealCount` 0은 초기/동적 shared frontier가 계속 비지 않아 wait 뒤 재획득할 상황이 없었음을 뜻한다. 이 5초 표본은 해당 구간의 one-core tail 미재현 근거이며, 사용자의 26분 완주 시간이나 모든 입력의 성능 보증으로 확대 해석하지 않는다.

### N4 — Tauri deadline·progress·resume protocol

1. native command에 remaining budget와 progress channel을 추가한다.
2. session registry를 `jobId`와 별도 `continuationId`로 관리한다.
3. UI 시작 시 30초 absolute budget을 만들고 준비 비용을 차감한다.
4. Rust coordinator가 progress snapshot을 주기적으로 전송한다.
5. `resume_d4_optimization(continuationId)`와 session dispose 명령을 추가한다.
6. 창 종료·입력 변경·새 계산에서 실행 job과 보존 session을 안전하게 정리한다.

완료 기준: 실제 Tauri WebView에서 progress가 증가하고, initial run은 30초 안에 exact/bounded로 돌아오며 cancel latency가 회귀 기준을 만족한다.

2026-08-31 완료 기록: Tauri command는 `options.remainingBudgetMs`와 `tauri::ipc::Channel` progress를 받고, UI client는 prepare 이전부터 30초 absolute budget을 시작해 준비 경과 시간을 뺀 값만 native에 전달한다. Rust coordinator는 `NativeSearchSession`을 safe node batch 단위로 실행하고 deadline 시 `bounded` 또는 `no-incumbent-yet`의 frontier를 continuation registry에 보존한다. 각 batch는 immutable tree와 shared incumbent를 공유한 전체 CPU task scheduler로 처리하고, 반환 전에 모든 child를 persistent frontier로 병합하므로 checkpoint에 active work가 남지 않는다. `resume_d4_optimization(jobId, continuationId, ...)`, `dispose_d4_optimization(continuationId)`, 최대 4개 session의 oldest eviction, 취소 job registry를 추가했으며 terminal/progress에는 실제 lower·upper·평가·방문·ready work를 보낸다. 취소는 `cancelled`/`exact:false`/상한 없음으로 세션을 폐기한다. 취소·deadline은 leaf/분기 내부에서도 감지하고, 중단된 node는 frontier에 안전하게 되돌려 deadline continuation의 upper를 보존한다. 1/2/8/64-thread parallel slice가 serial exact와 같은 score/build ID로 재개되고, deadline frontier·cancelled 상한 제거·oldest eviction·client channel gap/thread/ready-work 전달도 회귀했다. 개발 Tauri WebView에서 progress의 evaluation/visited/ready work 증가와 16/16 worker 표시를 확인했으며, 30초 안에 `no-incumbent-yet` terminal 결과를 확인했다. 최종 cooperative-cancel 변경 뒤의 화면 클릭 지연 재측정은 사용자가 불필요하다고 명시해 제외한다. `cargo fmt --check`, Rust 65 tests, `cargo clippy --all-targets -- -D warnings`, native client·N0 fixture·browser runtime 회귀가 통과했다.

### N5 — UI와 정밀 계산 연결

1. 최초 native 예산을 30초로 통일한다.
2. UI에 lower/upper/gap, 평가 수, active/total thread, ready work, tail 상태를 표시한다.
3. bounded 결과에만 정밀 계산 버튼을 표시한다.
4. 정밀 계산은 같은 `continuationId`를 resume하고 exact/취소까지 진행한다.
5. session이 만료됐으면 재시작하지 말고 이유와 선택지를 표시한다.
6. 고정 슬롯은 결과 카드에서 원래 위치와 잠금 표시를 유지한다.

완료 기준: 사용자가 bounded→정밀 계산→exact의 연속성을 UI에서 확인할 수 있고, evaluation counter가 초기값으로 돌아가지 않는다.

2026-08-31 완료 기록: native bounded 결과의 `continuationId`와 준비된 후보/evaluator 문맥을 `d4-native-client.js`가 메모리에 보존한다. 결과 UI는 continuation이 있는 native `bounded`에만 “정밀 계산 계속”을 표시하며, 클릭은 `d4_optimize_parallel`을 다시 호출하지 않고 `resume_d4_optimization(jobId, continuationId, ...)`에 새 30초 예산과 progress channel을 전달한다. 따라서 Rust가 보관한 동일 frontier·incumbent·evaluation counter에서 계속 탐색한다. exact 종료에는 continuation을 제거하고 exact 결과만 cache한다. bounded 결과는 session registry 밖에서 유효하지 않으므로 cache하지 않는다. 입력 변경·새 계산·창 종료는 active job을 cancel하고 보존 session을 `dispose_d4_optimization`으로 폐기한다. session eviction/만료/없음 오류는 Worker 재시작으로 바꾸지 않고 “새 전역 계산을 시작”하라는 UI 오류로 표시한다. `tools/test-d4-native-client.mjs`는 bounded→resume이 새 optimize command를 호출하지 않음, 동일 continuation 전달, exact 뒤 token 제거 및 만료 오류를 확인한다. `tools/test-d4-native-resume-ui-n5.mjs`와 browser Worker runtime 회귀는 버튼 노출 조건·resume wiring·입력/창 종료 cleanup을 보호한다.

### N6 — 정확성·성능·배포 승격 Gate

다음 검증을 모두 통과하기 전에는 native runtime을 완료로 표시하지 않는다.

- small exhaustive oracle: deadline 전/후, 1~64 thread, 입력 순서 반전
- checkpoint property: 모든 pending/active work 합집합의 누락·중복 0
- upper-bound property: 반환 upper가 모든 미탐색 실제 최고값 이상
- pause/resume exact: 무중단 exact와 score/build ID 동일
- 잠금 0/1/2/8개 및 빈 잠금·오류 잠금 회귀
- JS/Rust evaluator parity와 최종 JS CPU 재평가
- P6 fixture와 사용자 장기 fixture 각각 cold 반복 측정
- 최초 결과 click-to-render 30초 제한
- tail 구간 thread busy/steal/split 계측
- 취소, 입력 변경, native crash, session eviction, Worker fallback
- release NSIS 설치본에서 progress·bounded·resume·exact E2E

2026-08-31 완료 기록: 사용자 N5 검증에서 확인된 세 가지 runtime UX 결함을 교정했다. `NativeSearchSession`은 생성 시각의 벽시계 대신 실제 준비·slice 실행 시간을 `elapsedMs`로 누적하므로, bounded 상태로 사용자가 대기한 시간은 재개 뒤 경과에 더해지지 않는다. checkpoint도 누적 elapsed를 보존한다. `pause_d4_optimization(jobId)`는 cancel과 별도 atomic signal로 실행 중인 safe batch가 끝난 뒤 `paused` 상태와 인증 upper/frontier를 continuation registry에 보존하며, 재개는 무중단 exact와 같은 frontier를 사용한다. UI는 native 실행 중 일시정지 버튼을 제공하고, 일시정지 후에는 “계산 재개”를 표시한다. bounded 또는 no-incumbent-yet에서 “정밀 계산 계속”을 한 번 누르면 동일 continuation의 30초 slice를 exact·일시정지·오류까지 자동 연결한다. Rust 회귀는 parked elapsed 제외, pause→resume exact, deadline/cancel/checkpoint/1~64 thread·입력 순서 반전 upper property를 통과했다. JS native client/UI/Worker regression, JS/Rust parity 1,488 cases, lock 0/1/2/8 regression, P6와 사용자 fixture cold/5초 계측, release NSIS build까지 통과했다. 새 installer SHA-256은 `C05C74B4FD932237CA5E369D2FF00134CAEC6560A6509F97CB8EFAB8B7739A0C`이다. 사용자가 설치본 UI에서 자동 연속, 일시정지·재개, inactive elapsed 제외를 확인해 N6을 완료 처리했다.

## 6. 결과 상태와 UI 의미

| 상태 | 의미 | continuation |
|---|---|---|
| `exact` | 모든 남은 upper가 incumbent 이하이거나 frontier 소진 | 불필요 |
| `bounded` | 30초 deadline, feasible incumbent와 인증 upper 존재 | 필수 |
| `no-incumbent-yet` | deadline까지 feasible 해를 못 찾았지만 가능성 남음 | 필수 |
| `paused` | 사용자가 요청해 safe batch 경계에서 멈췄고 frontier·인증 upper를 보존 | 필수 |
| `cancelled` | 사용자 또는 입력 변경으로 중단 | 명시 정책에 따름 |
| `invalid` | 입력/잠금 오류 또는 feasible 가능성 없음이 증명됨 | 없음 |

`invalid`를 시간 만료나 내부 실패의 포괄 상태로 사용하지 않는다. `exact`는 완료 증명 외에는 절대 반환하지 않는다.

## 7. 캐시와 메모리 정책

- exact 결과 cache와 resumable session을 분리한다.
- bounded 결과만 저장하고 frontier를 버리는 cache는 정밀 계산 재개에 사용할 수 없다.
- session signature에는 problem hash, 계산식 버전, engine version, fixed contract version, scheduler/split policy, thread/GPU 정책을 포함한다.
- thread 수가 바뀌어도 exact 결과는 같지만 bounded 성능 비교와 session scheduler 상태가 달라지므로 session signature는 분리한다.
- frontier memory가 예산을 넘으면 안전한 압축/재분할 제한을 적용하고, work item을 버려 upper를 낮추는 방식은 금지한다.

## 8. 주의할 점

- deadline을 cancel flag로 흉내 내고 `upperBound:null`을 반환하면 bounded 증명이 되지 않는다.
- active worker가 가진 local heap을 checkpoint에서 빠뜨리면 거짓 exact 또는 과소 upper가 된다.
- 진행률을 평가 수/전체 조합 수로 표시하지 않는다. 가지치기 탐색에는 의미 있는 전체 분모가 없다.
- 정밀 계산에서 problem을 다시 compile하면 continuation이 아니다.
- tail 해결을 초기 shard 수 증가 하나로 끝내지 않는다.
- 고정 크리스타 효과를 base와 package 양쪽에 더해 이중 적용하지 않는다.
- 잠금된 알 수 없는 이름을 빈 슬롯로 자동 대체하지 않는다.
- P6 단일 fixture의 시간을 모든 시나리오 예상 시간으로 사용하지 않는다.
- bounded 결과의 품질 개선과 exact 정확성 증명을 같은 완료 기준으로 섞지 않는다.

## 9. 완료 정의

이 교정 작업은 다음이 모두 충족될 때 완료다.

1. 최초 결과가 통제된 release 환경에서 30초 안에 `exact` 또는 인증된 `bounded`로 반환된다.
2. UI가 native 탐색 진행, thread 사용, gap과 tail 상태를 실제 channel 값으로 갱신한다.
3. 분할 가능한 work가 남아 있는 동안 idle worker가 생기는 구조적 tail이 제거된다.
4. bounded 정밀 계산이 같은 frontier를 이어받아 최종 exact에 도달하며 재시작하지 않는다.
5. 모든 잠긴 크리스타가 정확히 한 번 반영되고 결과에서 교체되지 않는다.
6. oracle/property/native 설치본 E2E가 모두 통과하고 handoff의 runtime 미완료 표시가 제거된다.
