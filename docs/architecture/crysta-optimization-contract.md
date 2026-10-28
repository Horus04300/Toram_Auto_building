# 크리스타 최적화 정확성·성능 변경 계약

- 갱신: 2026-09-05. 크리스타 최적화 정확성·성능·후보 탐색 변경 시 이 문서를 전체 읽는다.
- 역할: 불변 계약, 변경 Gate와 설계 제약. 현재 제품 상태는 `docs/handoff/current-development-handoff.md`에서만 관리한다.
- 범위: 고정 Build/Scenario, 네 장비의 크리스타 각 2슬롯. 자동 장비 옵션 부여는 별도 보류 범위다.
- 10초 exact는 성능 목표이며 모든 입력에서 달성됐다는 보증이 아니다. Native deadline/progress/continuation은 이미 연결된 기능이며 재구현 대상이 아니다.

## 1. 결과와 정확성

- 실제 완성 조합만 feasible 하한으로 채택한다. Utility·잠금·금지·부위·동일 장비 중복·강화 계보를 모두 만족해야 한다.
- 모든 미해결 공간을 탐색했거나 남은 안전 상한이 incumbent를 넘지 못함을 증명할 때만 `exact`다. 동점 build ID의 사전식 우선순위를 보존한다.
- 제한 시간에 증명하지 못하면 `bounded`와 인증 상한/gap을 반환한다. feasible 해를 아직 찾지 못한 상태를 불가능 증명과 혼동하지 않는다.
- Greedy/좌표 개선 미리보기는 `heuristic`이며 인증 gap을 만들지 않는다. 취소 결과도 exact 증명이 아니다.
- 입력 순서·스레드 수·Worker 완료 순서가 달라도 exact 점수와 동점 ID는 같아야 한다.
- 계산식·후보·제약·분할 정책 변경은 해당 캐시/continuation을 무효화한다. 학습 모델이나 과거 결과를 정확성 증거로 쓰지 않는다.

## 2. 후보 삭제 증명

동적 점수·공급 집중도·로그 한계효용은 초기해와 탐색 순서에만 사용할 수 있다. 후보 삭제에는 다음 증거를 모두 요구한다.

1. 같은 구조·조건·충돌·계보 서명과 같거나 적은 슬롯 비용.
2. 목적함수 관련 좌표와 미충족 Utility에서 열등하지 않음.
3. 파생값·조건 계산에 필요한 raw 값 보존.
4. 엄격 우위 또는 안전한 동점 ID 보존.
5. 축소 전후 exhaustive oracle의 최적 점수·ID 일치.

MAXMP→AMPR, 평타 CRIT와 기대 대미지, ASPD→행동속도, HP/MP 비례 조건은 포화로 삭제하지 않는다. 조건이 없고 목적/파생 계산에 쓰이지 않는 순수 Utility만 잔여 요구량 R에 대해 min(기여량,R) 비교를 허용한다. 의존성이 불명이면 후보를 보존한다. 이미 충족한 HP라도 DPS를 함께 공급하면 HP만으로 삭제하지 않는다.

고정 크리스타 효과는 한 번만 반영하고 결과에서 교체하지 않는다. 알 수 없는 잠금 이름은 빈 슬롯으로 바꾸지 않는다. 다른 장비에는 동일 크리스타 반복이 가능하지만 같은 장비의 중복·강화 계보 충돌은 금지한다.

사용자 지정 추천 범위에서는 기초 고정 스탯 계열 ID9401~9504를 자동 후보에서 제외한다. 수동 선택·저장·잠금은 보존하며, exact는 이 허용 후보와 잠금으로 구성한 문제의 최적성이다. 이 제품 범위 정책은 수학적 우위에 의한 후보 삭제 증명이 아니다.

## 3. Pair·상한·초기해

- 방어구+특수/무기+추가, 방어구+무기/추가+특수, 방어구+추가/무기+특수는 시나리오별 비교 가설이다. 한 분할을 모든 입력의 우세 규칙으로 고정하지 않는다.
- Pair Frontier는 실제 가능한 결합만 표현한다. 원시/준비 후보 수·생성 비용·메모리·초기 하한·상한 감소량으로 비교한다. 전체 물질화가 예산을 넘으면 지연 생성/상자 표현을 검토한다.
- 작은 Pair의 완결 frontier는 초기 하한에 사용할 수 있지만, 불완전 frontier로 원래 탐색 공간을 없애지 않는다.
- 독립 좌표 최고값의 envelope은 안전할 수 있으나 실제 불가능한 조합을 포함해 느슨할 수 있다. 새 상한은 모든 부분공간의 실제 최고값 이상이어야 한다. 각각 안전한 상한끼리는 최솟값을 취할 수 있다.
- CRIT·크뎀·안정률·행동속도·관통·방어력·단계별 내림·발도 변환·마법·듀얼 등 경계에서 property를 검증한다. 실제 후보 하나의 점수를 상한으로 사용하지 않는다.
- 상한 계산 비용이 가지치기 절감보다 크면 채택하지 않는다. 후보 점수 정렬을 안전 상한으로 오인하지 않는다.

## 4. 변경 Gate

| 변경 | 반드시 확인할 것 |
| --- | --- |
| 계산/평가 표현 | 원문 연결, full/summary 동치, 독립 JS oracle과 Rust parity, 제품 최종 재평가 |
| 후보 삭제/포화 | 축소 전후 oracle, 조건/계보/raw Utility/동점 증명 |
| Pair/분기/상한 | 부분공간 coverage, 상한 property, 입력 순서 결정성 |
| 병렬화/세션 | 1~64 thread의 exact·동점 동치, cancel/deadline/pause/resume, pending·active work 보존 |
| 성능 승격 | 동일 입력·환경의 변경 전후 cold 반복, 시간·메모리·품질 동시 비교 |

소형 fixture는 Utility 없음/부족/충족, 음수 Utility 고DPS, HP+DPS, MAXMP→AMPR, 크리티컬 경계, 행동속도 상한, 발도/일진강풍, 물리/원거리/마법/듀얼, 잠금/금지/계보/동점/불가능 문제를 포함한다.

10초 exact 목표 판정은 데이터 버전·PC·Node/WebView 버전을 기록하고 필수 실제 fixture마다 새 프로세스 10회 P95로 측정한다. 컴파일+탐색을 포함하며 외부 wall time도 구분한다. 한 입력의 단발 시간, bounded 품질 개선, 과거 P6 수치를 전체 exact 달성으로 보고하지 않는다. 목표를 통과하기 전 exact 강제 성능 조건을 임의로 활성화하지 않는다.

## 5. 설계 제약

- 큰 Pair 전면 물질화는 생성/비교/메모리 예산과 완전한 Pareto 증명 없이는 사용하지 않는다.
- Pair 상관 상한은 자식 공간에서도 관계와 coverage를 보존해야 한다. 개별 CandidateTree에 bucket filter를 덧붙여 중복 순회/공간 누락을 만들지 않는다.
- leaf summary·후보 rank 분할·분기 차원·기본 실행 정책 변경은 새 병목 근거와 실제 입력의 정확성/품질/성능 Gate를 요구한다.
- 웹 coordinator가 준비 후보/트리를 소유한다. 후보를 복제·재초기화하는 별도 JS 탐색 Worker pool을 추가하지 않는다.
- 후보 삭제는 2절 증명으로만 허용한다. 실험 옵션이나 보고서의 존재는 삭제 증거가 아니다.
- GPU는 독립 대량 batch의 CPU 병목과 전송 포함 이득을 확인한 뒤 검토한다. f32 값을 그대로 exact pruning에 쓰지 않는다.

노드 수·평가 비용·작업 실행 비용을 구분해 계측한다. 중첩 inclusive 시간은 합산하지 않는다.

## 6. 검증 진입점과 기록

- 공용 Rust: engine/src/의 평가·탐색 단위 테스트(완전탐색, 안전 상한, 동점, 병렬, 중단/재개).
- 제품 후보 준비: tools/tests/optimization/test-crysta-candidate-projection.mjs, test-crysta-integer-pareto.mjs.
- 실제 WASM: tools/tests/optimization/test-crysta-wasm.mjs. 독립 소형 완전탐색은 tools/support/crysta-exhaustive-oracle.mjs이며 추천 정책·가지치기·캐시가 없다.
- Native: tools/tests/optimization/test-crysta-native-exact.mjs, test-crysta-native-locks.mjs, test-crysta-utility-caps.mjs.
- JS/Rust 평가: tools/tests/optimization/test-crysta-rust-native-parity.mjs. 후보 삭제·동점 검사와 평가 동치를 구분한다.
- 실행 제어: docs/architecture/native-optimization-runtime.md.

영향받는 Gate를 선택해 명령·입력·PASS/SKIP/미실행을 보고한다. 현재 handoff에는 채택 여부·현재 계약·검증 요약만 갱신하고 긴 계측 결과를 누적하지 않는다. 이 문서는 12 KiB 이하로 유지한다.

평가 수식은 공통 Rust evaluator가 소유한다. 독립 비교는 tools/fixtures/calculation-oracle.mjs(제품과 독립된 JS 수식)와 tools/tests/application/test-evaluator-integration.mjs로 유지한다. 이 oracle은 제품 import 그래프에 포함하지 않는다. 전체 호출 성능과 사전 준비된 입력의 수치 평가를 구분하고 입출력·표시 비용을 명시한다.
