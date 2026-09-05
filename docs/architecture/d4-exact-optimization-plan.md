# D4 정확성·성능 변경 계약

- 갱신: 2026-09-05. D4 정확성·성능·후보 탐색 변경 시 이 문서를 전체 읽는다.
- 역할: 불변 계약, 변경 승인 Gate, 재시도 금지 근거. 현재 제품 상태는 `docs/handoff/current-development-handoff.md`에서만 관리한다.
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
| 계산/평가 표현 | 원문 연결, full/summary 동치, JS/Rust parity, 최종 JS 재평가 |
| 후보 삭제/포화 | 축소 전후 oracle, 조건/계보/raw Utility/동점 증명 |
| Pair/분기/상한 | 부분공간 coverage, 상한 property, 입력 순서 결정성 |
| 병렬화/세션 | 1~64 thread의 exact·동점 동치, cancel/deadline/pause/resume, pending·active work 보존 |
| 성능 승격 | 동일 입력·환경의 변경 전후 cold 반복, 시간·메모리·품질 동시 비교 |

소형 fixture는 Utility 없음/부족/충족, 음수 Utility 고DPS, HP+DPS, MAXMP→AMPR, 크리티컬 경계, 행동속도 상한, 발도/일진강풍, 물리/원거리/마법/듀얼, 잠금/금지/계보/동점/불가능 문제를 포함한다.

10초 exact 목표 판정은 데이터 버전·PC·Node/WebView 버전을 기록하고 필수 실제 fixture마다 새 프로세스 10회 P95로 측정한다. 컴파일+탐색을 포함하며 외부 wall time도 구분한다. 한 입력의 단발 시간, bounded 품질 개선, 과거 P6 수치를 전체 exact 달성으로 보고하지 않는다. 목표를 통과하기 전 exact 강제 성능 조건을 임의로 활성화하지 않는다.

## 5. 이미 폐기한 가설과 재개 조건

- 큰 Pair 전체 물질화와 불완전 Pareto: 생성/비교 비용과 메모리가 과다했다. 같은 전면 물질화를 재시도하지 않는다.
- root-only Pair 상관 상한: 자식에서 관계를 잃어 준비 비용을 회수하지 못했다.
- 기존 개별 CandidateTree에 Pair bucket filter 유지: 자식마다 Pair를 재순회하거나 중복 공간이 생겼다. 관계를 보존하는 새 표현과 oracle이 없으면 재시도하지 않는다.
- leaf summary, 후보 rank 분할, 분기 차원 증가: 당시 long-exact 또는 품질 Gate에서 개선되지 않았다. 새 병목 근거 없이 기본값을 바꾸지 않는다.
- JavaScript Worker pool: 후보 복제·초기화 비용 때문에 실제 데이터 Gate에서 기본 경로로 승격하지 못했다. 스레드 수 증가만으로 해소됐다고 가정하지 않는다.
- Replacement Proof 감사는 증명된 삭제만 허용한다. 실험 옵션이나 보고서 존재를 제품 후보 삭제 연결로 해석하지 않는다.
- GPU는 독립 대량 batch의 CPU 병목과 전송 포함 이득이 입증된 후 별도 검토한다. f32 값을 그대로 exact pruning에 쓰지 않는다.

계측에 따라 노드 과다이면 표현/상한, 평가 비용이면 조밀 벡터·증분 평가, 작업 실행 비용이면 지속 스레드 풀을 검토한다. 어느 방향도 새 실측 없이 우선 채택하지 않는다. 중첩 inclusive 시간은 합산하지 않는다.

Gate 0~E의 상세 실패 근거는 `docs/handoff/d4-gate0-to-gatee-worklog.md`, 강한 초기해의 상세는 `docs/architecture/d4-dynamic-score-exact-acceleration-plan.md`, 초기 병렬 실험은 `docs/architecture/d4-parallel-exact-optimization-plan.md`에서 해당 주제만 읽는다.

## 6. 검증 진입점과 기록

- `tools/test-d4-evaluator-stage1.mjs`, `tools/test-d4-global-optimizer-stage2.mjs`: 평가·oracle·상한.
- `tools/test-d4-utility-dependencies.mjs`, `tools/test-d4-pair-frontier.mjs`: Utility/Pair.
- `tools/test-d4-rust-native-parity.mjs`: JS/Rust 평가 동치.
- `tools/test-d4-full-stage3.mjs`, `tools/benchmark-d4-exact.mjs`: 실제 후보 회귀와 반복 계측.
- 실행 제어: `docs/architecture/d4-native-runtime-correction-plan.md`.

영향받는 Gate를 선택해 명령·입력·PASS/SKIP/미실행을 보고한다. 현재 handoff에는 채택 여부·현재 계약·검증 요약만 갱신하고 긴 계측 결과를 누적하지 않는다. 이 문서는 12 KiB 이하로 유지한다.
