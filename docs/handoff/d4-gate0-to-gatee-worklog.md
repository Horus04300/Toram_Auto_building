# D4 전역 최적화 작업 기록 — Gate 0부터 Gate E까지

> 상태: 2026-08-25 기준 작업 기록
> 범위: 토람 온라인 빌드 계산기의 D4 전역 크리스타 최적화
> 상위 기준: [D4 exact 최적화 계획](../architecture/d4-exact-optimization-plan.md), [현재 개발 인수인계](current-development-handoff.md)
> 이 문서는 시간순 사실을 태그로 먼저 수집한 뒤, 배경·제약·설계·분석·실패 가설을 다시 묶은 작업 기록이다. 최신 상태 판단은 이 문서만이 아니라 실제 코드와 새로 실행한 테스트 결과를 함께 사용한다.

## 1. 태그 체계와 읽는 법

- `[GOAL]`: 목표와 완료 판정
- `[BASELINE]`: 기준 측정
- `[SAFETY]`: exact를 훼손하지 않기 위한 계약·oracle·property
- `[UTILITY]`: MAXHP·MAXMP·AMPR·ASPD·평타 크리티컬 제약
- `[PAIR]`: 두 부위 결합, Pair Frontier, Pair 상관관계
- `[BOUND]`: 안전 상한과 branch-and-bound 탐색
- `[PERF]`: 시간·메모리·후보 수 측정
- `[REJECTED]`: 검증은 됐으나 기본 경로에 채택하지 않은 방식
- `[PENDING]`: 아직 구현 승인을 뜻하지 않는 후속 조사 후보

숫자는 반드시 어느 fixture·시간 예산에서 나온 것인지 함께 읽는다. 특히 Gate 0의 10초 P95 측정과 후속 5초 실험은 목적과 실행 시점이 달라 한 숫자만으로 성능 회귀·개선을 단정하면 안 된다.

## 2. 배경과 목표

[GOAL] D4는 무기·방어구·추가장비·특수장비의 크리스타 2슬롯씩, 총 8개 슬롯을 **독립 추천이 아니라 하나의 전역 조합 문제**로 푼다. 목표는 가장 좋아 보이는 조합을 제시하는 것이 아니라, 실제 최적 조합임을 증명한 `exact` 결과를 콜드 캐시 기준 10초 안에 반환하는 것이다.

이 문제는 기계학습 또는 재학습 문제가 아니다. 후보 데이터·계산식·조건이 바뀌면 학습 모델을 다시 훈련하는 구조가 아니라, 같은 결정적 컴파일·Pareto·branch-and-bound 절차가 새 입력을 다시 처리한다. 후보 수가 늘어나면 탐색량은 늘 수 있지만, 알고리즘 자체가 학습 상태를 추적하거나 갱신하지는 않는다.

[GOAL] 최적화는 다음 순서를 지킨다.

1. 장비 구조 조건, 잠금·금지, 계보·중복 제약을 후보 컴파일 단계에서 확정한다.
2. BuildEvaluator가 원래 계산식으로 대미지·Utility·hard constraint를 계산한다.
3. 실제 완성 조합으로 하한을 만들고, 부분 후보 상자의 **안전한 상한**으로 가지치기한다.
4. 열린 상자의 최대 상한이 현재 하한보다 낮아지면 그 상자를 버린다.
5. 열린 상자가 없어야만 `exact`를 표시한다. 시간 예산이 끝나면 유효한 하한·상한·gap을 가진 `bounded`를 표시한다.

## 3. 범위와 제약 조건

### 3.1 현재 범위

[GOAL] 현재 D4는 사용자가 입력한 완성 크리스타를 다룬다. 자동 장비 옵션 부여, 잠재력 탐색, 슬롯 생성, 소재·성공률 최적화는 범위 밖이다.

[UTILITY] 기본 Utility hard constraint는 시나리오에 따라 계산된다. 근거리 MAXHP, MAXMP, 듀얼소드 배율 전 AMPR, ASPD, 평타 크리티컬률 등은 후보의 단순 공격 점수보다 우선한다. 선택 스킬이 확정 크리티컬이어도 평타 운용 제약을 임의로 면제하지 않는다.

[SAFETY] 원문 대미지식의 내림·상한·발도/일진강풍·MATK 반영률 등은 BuildEvaluator와 계산 커널에서 처리한다. D4 상한은 별도의 근사 대미지식을 만들지 않고, 후보 envelope을 원래 집계 평가 경로에 넣는다. 따라서 계산식 경계 자체는 이미 집계 평가에 반영되어 있으며, 남은 어려움은 서로 다른 후보에서 얻은 스탯 최대값을 한 조합처럼 섞는 상관관계 손실이다.

### 3.2 비가역 규칙

[SAFETY]

- 불완전 Pareto 결과로 후보를 삭제하지 않는다.
- 실제 후보 하나를 상한으로 사용하지 않는다. 실제 후보는 다른 결합의 최적해보다 낮을 수 있다.
- 상한이 oracle 또는 property에서 한 번이라도 실제 완성해보다 낮게 나오면 해당 상한은 폐기한다.
- 성능이 개선되지 않는 실험은 Worker 기본 옵션, 캐시 계약, 사용자 추천 결과에 연결하지 않는다.
- 사용자가 보류한 피격·시간·AI 중심 전투 시뮬레이션을 D4 성능 작업의 명목으로 추가하지 않는다.

## 4. 구현 구조

[BOUND] 주요 경로는 다음과 같다.

```text
크리스타 데이터
  → d4-problem-compiler
  → CandidatePackage 4개 부위
  → 관련 축 도출 + 완결 Pareto
  → 실제 조합 하한(heuristic / Pair Frontier)
  → 부위별 후보 트리(envelope)
  → best-bound 탐색
  → exact 또는 bounded + 인증 gap
```

핵심 파일:

- `assets/js/build-evaluator.js`: Build/Scenario snapshot과 Outcome
- `assets/js/d4-problem-compiler.js`: 제약을 반영한 후보 패키지 컴파일
- `assets/js/d4-global-optimizer.js`: Pareto, oracle, 상한, best-bound 탐색
- `assets/js/d4-source-profile.js`: Utility 의존성·잔여 요구량·획득처 분석
- `assets/js/d4-pair-partition.js`: 세 Pair 분할의 결정적 비교
- `assets/js/d4-optimizer-worker.js`, `assets/js/d4-worker-client.js`: Worker 실행·취소·캐시
- `tools/benchmark-d4-exact.mjs`, `tools/test-d4-*.mjs`, `tools/analyze-d4-*.mjs`: 기준 측정·oracle·분석

## 5. 시간순 작업 기록

### T0. Gate 0 — 기준선 고정

[BASELINE] 실제 425개 물리·근거리 fixture를 새 Node 프로세스 10회로 측정했다.

| 항목 | 결과 |
| --- | --- |
| 시간 예산 | 10,000ms |
| exact | 0 / 10 |
| bounded | 10 / 10 |
| 컴파일+탐색 P95 | 10,152.0ms |
| 외부 프로세스 포함 P95 | 10,239.5ms |
| 인증 gap 범위 | 38.008% ~ 39.385% |

[PERF] 이 결과는 목표 미달의 기준선이지 실패한 계산 결과가 아니다. 이후 어떤 개선이든 같은 유형의 반복 측정·P95·exact 비율로 비교해야 한다.

### T1. Gate A — Utility 의존성 분류

[UTILITY] `d4-utility-dependency.v1`을 만들었다. 핵심은 “수치가 상한에 닿으면 후보에서 잘라도 되는가”를 옵션 이름만으로 판단하지 않는 것이다.

- 조건 없는 MAXHP만 residual 포화 후보로 분류한다.
- MAXMP는 AMPR에 영향을 주므로 원값을 보존한다.
- AMPR은 통상공격·듀얼소드 운용과 연결되므로 원값을 보존한다.
- 크리티컬은 점수와 hard constraint에 연결되므로 원값을 보존한다.
- ASPD는 행동속도와 연결되므로 원값을 보존한다.
- HP/MP 비례 조건이 metadata로 선언되면 포화를 금지한다.

[SAFETY] 이 단계는 분석 정책만 추가했으며 후보 삭제·상한·추천 결과를 바꾸지 않았다.

### T2. Gate B — SupplyDifficulty와 residual dominance

[UTILITY] `d4-supply-difficulty.v1`은 실제 후보에서 Utility를 단독으로 채우기 쉬운지 측정한다. 부족 fixture에서 HP·ASPD는 단독 충족 후보가 다수였지만, MAXMP·AMPR·평타 크리티컬은 단독 충족 후보가 없었다. 즉 후자는 부위 결합을 고려하지 않고 후보를 제거하면 안 된다.

[SAFETY] `safeResidualDominance`는 구조·조건·충돌·계보·슬롯 비용·목적 좌표·capped/raw Utility·동점 ID 증거가 모두 있을 때만 `proven`을 반환한다. 하나라도 빠지면 삭제를 거부한다. 현재 실제 Pareto 삭제에는 아직 연결하지 않았다.

### T3. Gate C — 사용자 가설을 포함한 세 Pair 분할 비교

[PAIR] 사용자는 방어구+특수와 무기+추가 결합을 직관적으로 제안했다. 이를 고정 규칙으로 넣지 않고 세 가능한 Pair 분할을 실제 후보 수·Utility 충족 가능성·총 Pair 수로 비교하는 `d4-pair-partition.v1`을 만들었다.

| 분할 | 최대 prepared Pair | 총 prepared Pair | 비고 |
| --- | ---: | ---: | --- |
| 방어구+무기 / 추가+특수 | 2,590,656 | 4,780,976 | 선택 |
| 방어구+추가 / 무기+특수 | 2,628,384 | 4,787,264 | 비선택 |
| 방어구+특수 / 무기+추가 | 2,755,456 | 4,814,776 | 사용자 가설, 비선택 |

[PAIR] 세 분할 모두 활성 Utility 하나를 단일 Pair만으로 충족하지 못했고, 250,000개 물질화 한계보다 컸다. 따라서 Pair Frontier를 추정하지 않고 `lazy-box`로 분기했다.

### T4. Gate D — Pair Frontier는 하한 전용으로 연결

[PAIR] 작은 Pair(8,192개 이하)는 가능한 합계를 모두 만들고 완결 Pareto Frontier일 때만 초기 하한 후보로 사용한다. 큰 Pair는 기본 `lazy-deferred`다.

[SAFETY] 큰 Pair의 24×24 결정적 lazy seed는 소형 exhaustive oracle에서 정확성과 동점 규칙을 통과했다. 그러나 실제 425개 fixture에서는 하한을 14,089에서 올리지 못하고 약 1,250회 평가만 추가했다.

[REJECTED] 따라서 lazy seed는 기본 Worker 옵션에 넣지 않았다. 이 결정은 “Pair가 나쁘다”가 아니라 하한 개선이 검증되지 않았다는 뜻이다.

### T5. Gate E-1 — Pair 상관관계 루트 상자

[PAIR] 선택 Pair의 양쪽 부위 트리를 2×2, 3×3, 4×4로 나눠 서로 겹치지 않는 루트 상자를 만들었다. 각 상자는 실제 후보 집합의 부분집합을 덮으므로 안전한 envelope으로 평가할 수 있다.

[SAFETY]

- `verifyPairCorrelationUpperBounds`가 작은 exhaustive oracle에서 각 상자의 모든 완성 조합을 직접 대조한다.
- `verifyEnvelopeMonotonicity`는 실제 425개 후보의 트리 부모·자식 envelope 19,732건에서 위반 0건을 확인했다.
- 상관관계 상자를 독립 초기 큐 분기로 넣어도 exact 점수와 사전식 동점 ID가 유지되는 소형 회귀를 추가했다.

[REJECTED] 실제 5초 측정에서 기준 gap 44.900%에 대해 2×2는 45.262%, 3×3은 45.056%, 4×4는 45.106%였다. 안전하지만 비용 대비 가지치기 이득이 없어서 기본 비활성이다.

### T6. Gate E-2 — 실제 집계 상한으로 분할 부위 선택

[BOUND] 기존 탐색은 heuristic score로 동시에 나눌 두 부위를 고른다. 이를 보강하려고 초기 몇 단계에서 가능한 부위 쌍을 실제 집계 상한으로 직접 비교하는 bound-guided split을 만들었다.

[SAFETY] small oracle에서 exact·동점 규칙을 통과했다. 후보 삭제·상한 정의·exact 판정은 바꾸지 않았다.

[REJECTED] 실제 5초 gap은 안내 깊이 1/2/3에서 47.115% / 47.874% / 48.470%였다. 상한 평가를 더 많이 한 비용이 노드 감소보다 컸다. 기본 비활성이다.

### T7. Gate E-2b — 전체 실제 Pair 프로필 물질화 비용 측정

[PAIR] “실제 Pair 합계만 보존하면 상한이 강해질 것”이라는 가설을 검증하기 위해 선택 Pair 전체를 물질화하고 Pareto 축약 비용을 측정했다.

| Pair | 입력 수 | 생성 시간 | Pareto 시간 | 상태 |
| --- | ---: | ---: | ---: | --- |
| 방어구+무기 | 2,190,320 | 5,479.3ms | 13,260.8ms | 1,000,000 비교에서 불완전 |
| 추가+특수 | 2,590,656 | 6,129.2ms | 17,700.6ms | 1,000,000 비교에서 불완전 |

[PERF] 두 Pair의 생성만 약 11.6초, 제한된 Pareto만 약 31초였다. 축약 후에도 각각 약 176만·197만 후보가 남았다.

[REJECTED] 전체 Pair Frontier/프로필은 10초 exact 경로에서 금지한다. 이는 구현 난이도 문제가 아니라 측정된 시간·메모리·불완전성 문제다.

### T8. Gate E-3 — 고정 메모리 스트리밍 Pair envelope

[PAIR] 전체 Pair를 저장하지 않고, CRIT 합계 범위를 2개 또는 4개 상자로 나눈 뒤 각 상자에 속한 실제 Pair의 좌표별 최대값만 유지하는 스트리밍 요약을 만들었다.

[PERF] Utility 부족 fixture에서 두 Pair 합계 4,780,976개를 고정 메모리로 약 114.9ms에 순회했다. 객체를 478만 개 생성하지 않으므로 전체 물질화보다 훨씬 싸다.

[SAFETY] 각 실제 Pair는 정확히 하나의 상자에 속하고, 그 상자의 각 좌표 envelope은 해당 Pair 이상이다. 작은 oracle에서 exact 점수·동점 규칙이 유지됐다.

[REJECTED] 루트 상한에만 적용하면 자식 상자들이 다시 독립 envelope으로 평가된다. 실제 5초 gap은 2상자 47.321%, 4상자 47.271%로 기준보다 나빠 기본 Worker에 채택하지 않았다.

## 6. 현재 상태

[GOAL] 현재 사용자 경로는 여전히 기존 안전한 4부위 계층형 best-bound 탐색이다. 결과 상태는 `bounded`이며, gap은 인증된 상한과 하한의 차이다. `exact` 목표는 아직 달성하지 않았다.

[SAFETY] 다음은 기본 비활성 실험 또는 분석 도구로 남아 있다.

- Pair 상관관계 루트 상자
- bound-guided split
- 전체 Pair 프로필 측정
- 스트리밍 Pair root envelope

이들은 코드에 남아 있어도 Worker 기본 옵션·캐시 키·일반 추천 결과에 연결되지 않았다. 재활성화하려면 소형 oracle, 상한 property, 실제 425개 성능 게이트를 다시 모두 통과해야 한다.

## 7. 문제 분석

[BOUND] 현 상한은 각 부위 후보 집합에서 스탯별 최대값을 골라 합친 envelope을 BuildEvaluator에 넣는다. 계산식은 정확하지만, 예를 들어 한 후보의 ATK% 최대와 다른 후보의 크리티컬·거리 위력 최대가 같은 장착 조합에 함께 존재하는 것처럼 보일 수 있다. 이 과대 결합이 상한을 높이고 gap을 남긴다.

[PAIR] Pair 상관관계는 이 과대 결합을 줄일 수 있지만, 정확한 Pair 프로필은 수백만 합계를 요구한다. 전체 저장은 시간·메모리 예산을 넘는다. 반대로 너무 작은 루트 상자나 root-only 요약은 자식 탐색에서 상관관계 정보를 잃어 효과가 지속되지 않는다.

[PERF] 따라서 핵심 문제는 “더 많은 후보를 빨리 보는 것”이 아니라, 다음 두 요구를 동시에 만족하는 표현을 찾는 것이다.

1. 실제 가능한 결합의 상관관계를 분기 이후에도 보존할 것
2. 후보를 수백만 개 물질화하지 않고, 10초 예산 안에서 갱신할 것

## 8. 설계 방향성

[PENDING] 다음 작업 후보는 **Pair 필터를 보존하는 상자 노드**다. 이는 이미 구현·승인된 기능이 아니라 검토 대상이다.

개념은 다음과 같다.

```text
선택 Pair의 실제 조합
  → 고정 개수의 서로 배타적인 필터 상자
  → 각 노드는 Pair 필터를 함께 보유
  → 분기 후에도 필터 조건 아래에서만 안전 envelope 재계산
  → 모든 필터 상자의 합집합이 원래 후보 공간과 같을 때만 exact 유지
```

착수 전 반드시 답해야 할 질문:

- 필터가 후보 트리 분할·작은 상자 전수조사·동점 ID 규칙과 함께 정확히 전파되는가?
- 필터별 envelope 재계산의 총 비용이 10초 예산의 작은 비율인가?
- 작은 exhaustive oracle에서 모든 필터 상자의 합집합이 원래 조합을 빠짐없이 한 번씩 덮는가?
- 실제 425개 10회 P95에서 gap 또는 exact 비율이 기준선보다 개선되는가?
- 개선이 없을 때 코드·Worker 경로를 기본 비활성으로 되돌릴 수 있는가?

이 질문 중 하나라도 충족하지 않으면 해당 방식은 탐색기 기본 경로에 넣지 않는다.

## 9. 실패한 방법과 재사용 가능한 결론

| 방법 | 안전성 | 성능 결과 | 결론 |
| --- | --- | --- | --- |
| 큰 Pair lazy seed | oracle 통과 | 하한 상승 없음, 평가 증가 | 하한 전용이라도 기본 비활성 |
| 2×2~4×4 Pair 루트 상자 | oracle·단조성 통과 | 5초 gap 악화 | 루트 분할만으로 부족 |
| bound-guided split | oracle 통과 | 추가 상한 평가 비용이 더 큼 | 초기 몇 단계 직접 비교는 비효율 |
| 전체 Pair 물질화 + Pareto | 완결 시 안전 | 생성만 11.6초, Pareto 31초 | 10초 경로 금지 |
| 스트리밍 Pair root envelope | oracle 통과 | 후속 분기에서 상관관계 소실 | 필터 지속 표현 없이는 부족 |

[REJECTED] 실패는 버려야 할 데이터가 아니다. 각 실험은 앞으로 피해야 할 비용 구조와 안전 계약을 확정했다. 특히 전체 Pair를 객체로 저장하는 방식과 root-only 상관관계 강화는 재측정 없이 되살리지 않는다.

## 10. 검증 기준

[SAFETY] 최소 검증은 변경 범위에 따라 다음을 조합한다.

```powershell
node tools/test-d4-pair-frontier.mjs
node tools/test-d4-global-optimizer-stage2.mjs
node tools/test-d4-full-stage3.mjs
node tools/test-d4-browser-worker-runtime.mjs
node tools/analyze-d4-pair-partitions.mjs
git diff --check
```

추가 규칙:

- 새 상한은 소형 exhaustive oracle에서 실제 완성해보다 작지 않아야 한다.
- 새 후보 삭제는 완결 Pareto 또는 별도 지배 증명이 있어야 한다.
- 실제 425개 성능은 첫 유효해, 하한, gap, 탐색 노드, 평가 횟수, 컴파일·탐색 시간을 함께 기록한다.
- 10초 exact 목표의 판정은 새 Node 프로세스 반복 측정 P95와 exact 비율로 한다.
- 작은 fixture에서 exact여도 실제 425개에서 빠르다는 뜻은 아니다.

## 11. 인수인계용 결론

[GOAL] D4는 구현 결함 때문에 bounded인 것이 아니라, 안전 상한이 후보 간 상관관계를 충분히 보존하지 못해 gap이 남아 있는 상태다.

[SAFETY] 현재까지의 모든 채택 판단은 “정확해 보이는가”가 아니라 oracle·상한 property·실제 성능을 함께 통과했는가로 내렸다.

[PERF] 전체 Pair 물질화는 측정상 불가능하고, root-only 요약은 충분하지 않다. 이후 작업은 Pair 필터가 분기 이후에도 살아남는 표현을 만들 수 있는지부터 증명해야 한다.

[STATUS] 현재 기본 경로를 무리하게 바꾸지 않는다. 다음 구현은 이 문서의 8절 질문에 대한 설계·oracle·성능 근거가 준비된 경우에만 진행한다.
