# D4 동적 점수 기반 강한 초기해 및 exact 가속 계획

- 상태: S0·S1·S2·S3·S4·S5·S6·S7 완료. S7 승인한 dynamic seed+ordering은 Worker 기본 경로에 연결했고 Replacement Proof 축소는 감사 전용이다.
- 기준일: 2026-08-28
- 목표: 물리 대미지 요소와 Utility의 현재 한계가치를 이용해 빠르게 강한 **실제 완성 빌드**를 만들고, 이를 D4 branch-and-bound의 하한으로 사용하여 `exact` 증명 시간을 줄인다.
- 상위 계약: `d4-exact-optimization-plan.md`, `d4-crysta-supply-reduction-plan.md`
- 현재 범위: 실제 최종 강화 크리스타, 네 장비 부위, 부위당 2슬롯, 고정 Build/Scenario
- 후속 범위: 검증된 옵션부여 카탈로그가 준비된 뒤 무기·몸장비 옵션 패키지로 확장

## 1. 보존해야 하는 의도

대미지에 영향을 주는 서로 다른 옵션을 현재 빌드에서의 기대 대미지 변화율로 환산하면 단순 옵션 수치 합보다 강한 초기해를 만들 수 있다. 물리 Scenario에서는 최소한 다음 축을 구분한다.

- 유효 공격력: ATK, ATK%, STR·DEX 계열, 대상 DEF와 물리관통
- 거리 위력: 선택 공격에 맞는 근거리 또는 원거리 위력
- 크리티컬: 크리티컬률, 크리티컬 대미지, 크리티컬 대미지%, 현재 경계와 기대값
- 발도: 선택 공격에 발도공격이 적용될 때의 발도 위력
- Utility: MAXHP, MAXMP, AMPR, 평타 크리티컬, ASPD의 요구량과 파생 결과

사용자가 제시한 `100 기준 점수`는 설명 단위와 값싼 정렬 근사치로 유지한다. 그러나 `ATK% 1 = 항상 1점`, `근거리 위력 1 = 항상 1점`처럼 고정값으로 저장하지 않는다. 현재 ATK, 대상 DEF, 관통, 누적 거리 위력, 크리티컬 대미지 경계, 선택 공격에 따라 한계효용이 달라지기 때문이다.

Greedy가 한 번의 선택으로 미래 조합을 막지 않게 각 단계에서 하나만 남기지 않는다. 서로 다른 관점의 상위 후보군을 부위별로 만들고 네 부위 조합을 실제 완성 빌드로 평가한다. 현재 compiler가 합법적인 부위별 2슬롯 `CandidatePackage`를 만들므로 개별 슬롯보다 이 패키지를 기본 선택 단위로 사용한다.

## 2. 목적과 비목적

### 목적

1. 현재 고정 가중치 초기해보다 높은 feasible 하한을 더 일찍 얻는다.
2. 하한 상승으로 `UB <= LB`가 되는 탐색 노드를 늘려 exact 증명 시간을 줄인다.
3. 동적 점수를 후보 정렬과 분기 순서에도 사용해 좋은 완성해를 앞에서 발견한다.
4. 여러 공격축과 Utility를 함께 공급하는 패키지의 부위별 기회비용을 반영한다.
5. 점수와 Supply Frontier로 Replacement Proof의 witness 탐색을 빠르게 한다.
6. 같은 초기해 원리를 향후 장비 옵션부여 최적화에 재사용한다.

### 비목적

- 점수만으로 후보를 삭제하지 않는다.
- Top-K 밖 후보가 최적해에 참여할 수 없다고 주장하지 않는다.
- `K^4` 또는 beam 결과를 exact라고 표시하지 않는다.
- 평균 기회비용, 그림자가격, 실사용 잠재력 90% 가정으로 안전 상한을 만들지 않는다.
- 옵션부여 데이터가 검증되기 전에 수치·상한·잠재력 비용을 추정하지 않는다.
- 음식, CRT 투자, 스킬·버프 선택을 현재 D4의 탐색 변수로 확장하지 않는다. 활성 입력은 baseline과 잔여 요구량에만 반영한다.

## 3. exact와의 관계

동적 점수 탐색은 먼저 하한 생성기다.

```text
실제 완성 빌드 평가
  → feasible이면 최고 실제 점수 LB 갱신
    → 각 미탐색 노드의 안전한 UB와 비교
      → UB < LB이면 노드 제거
      → UB = LB이면 동점 ID 가능성까지 확인한 뒤 제거
```

점수가 틀려도 완성 빌드를 원래 `BuildEvaluator`로 다시 평가하므로 exact 정확성은 깨지지 않는다. 나쁜 점수는 시간과 초기해 품질만 악화시킨다.

후보를 exact 공간에서 제거하려면 점수 외에 다음 중 하나가 별도로 필요하다.

- 구조·조건·계보·충돌·동점 계약을 포함한 strict dominance
- 같은 부위·같은 슬롯 비용에서 항상 교체 가능한 Replacement Proof
- 해당 후보를 반드시 포함한 부분공간의 안전 상한이 incumbent보다 낮다는 증명

상태도 명확히 분리한다.

```text
ranked        탐색 순서만 앞당김
seedIncluded  초기해 pool에 포함
heuristicLow  낮은 점수지만 exact 공간에는 보존
provenDrop    별도 증명서가 있어 exact 공간에서도 제거
```

## 4. 동적 점수 원리

### 4.1 공통 점수

기본 비교 단위는 로그 대미지 변화량이다.

```text
DamageScore(before, after)
  = 100 × ln(after.expectedDamage / before.expectedDamage)
```

작은 변화에서는 기대 대미지 약 1% 상승이 약 1점이다. 서로 다른 곱연산 축의 작은 변화를 안정적으로 비교할 수 있지만, 최종 하한 순위는 실제 `after.expectedDamage`로 판정한다. 수식 단계별 내림과 조건 분기는 근사식으로 복제하지 않고 원래 계산 커널을 사용한다.

### 4.2 물리 공격축

1. **유효 공격력**
   - 설명용으로는 `ATK - DEF × (1 - 물리관통)`의 변화를 본다.
   - 실제 점수는 ATK%, 고정 ATK, STR%, DEX%, 물리관통을 각각 적용한 evaluator 결과 차이다.
   - ATK 4,000·DEF 1,000은 설명용 입력이며 알고리즘 상수가 아니다.
2. **거리 위력**
   - 선택 공격의 근·원거리 판정과 현재 누적값을 반영한다.
   - 누적 위력이 높을수록 같은 +1%p의 실제 증가율이 낮아지는 것을 재평가한다.
3. **크리티컬**
   - 크리티컬 대미지 경계와 크리티컬률을 함께 반영한다.
   - 크리티컬 대미지+와 %는 현재 STR·AGI에서 계산된 최종 결과로 평가한다.
   - 선택 공격 확정 크리티컬이 평타 크리티컬 hard constraint를 면제하지 않는다.
4. **발도**
   - 선택 공격이 발도를 지원할 때만 가치를 준다.
   - 일진강풍 변환은 ScenarioProjection과 실제 계산 커널 결과를 따른다.

STR%, DEX%처럼 여러 계산 단계에 영향을 주는 옵션은 단일 축으로 임의 환산하지 않고 evaluator 유한차분으로 전체 효과를 얻는다.

### 4.3 Utility

Utility는 hard feasibility와 대미지·파생 가치가 다르다. 모든 Utility를 하나의 벌점으로 합치지 않는다.

- 현재 baseline의 잔여 요구량
- 패키지의 실제 공급량
- 순수 제약으로 증명된 축만 잔여량까지 포화한 기여
- MAXMP→AMPR, ASPD→행동속도, CRIT 기대값에 필요한 raw 값
- Utility 공급 시 잃는 `DeltaLogDamage`
- 같은 패키지가 함께 공급하는 다른 Utility

`많이 공급하는 패키지`와 `가장 적은 DPS 손실로 충족하는 패키지`를 서로 다른 seed로 유지한다. 완성 빌드는 원래 hard constraint 검사를 통과해야만 LB가 된다.

### 4.4 상태별 재평가

한계효용은 선택 상태에 따라 달라진다.

1. `BaselineMarginal`: 고정 Build에 패키지 하나를 더한 변화
2. `PartialMarginal`: 이미 고른 다른 부위 위에 패키지를 더한 변화
3. `CompleteOutcome`: 네 부위 패키지를 모두 적용한 최종 Outcome

초기 pool은 1로 만들고, beam과 국소 개선은 2를 사용하며, 하한 채택은 3만 사용한다. 이전 단계 점수 합을 최종 대미지로 간주하지 않는다.

## 5. 다중 seed Top-K

단일 종합점수는 보완 후보를 잃을 수 있다. 각 부위 pool은 다음 seed별 상위 패키지의 합집합이다.

- 현재 장착
- 순수 기대 대미지
- 유효 공격력·물리관통
- 근거리 또는 원거리
- 크리티컬률·크리티컬 대미지
- 발도 또는 일진강풍
- MAXHP
- MAXMP·AMPR
- 평타 크리티컬
- ASPD·행동속도
- 모든 hard constraint를 함께 고려한 balanced seed
- Supply Frontier의 극점과 무릎점

활성되지 않은 축의 seed는 만들지 않는다. pool은 구조·조건, Utility 충족 패턴, 공격축 패턴, 계보·충돌, 현재 장착 여부의 다양성을 보존한다. 동점은 항상 결정적 ID 순으로 처리한다.

Top-K는 초기해 폭일 뿐 exact 후보 수가 아니다.

```text
perSeedLimit       관점별 후보 수
mergedGroupLimit   중복 제거 후 부위별 초기해 pool 최대 수
```

현재 장착, 잠금 패키지, 활성 Utility의 단독·최소손실 공급 frontier 대표는 제한으로 누락시키지 않는다.

## 6. 완성 빌드 생성

### 6.1 패키지 조합

```text
weapon package
× armor package
× additional package
× special package
```

각 pool이 K개면 최대 `K^4`이다. K=16이면 65,536개지만 현재 평가 처리량에서 10초 예산의 큰 부분이 될 수 있으므로 무조건 고정하지 않는다.

1. 작은 pool은 Cartesian product 전수 평가
2. 큰 pool은 값싼 partial score 기반 결정적 beam 탐색
3. beam의 상위 완성 빌드만 실제 evaluator로 평가
4. 최고해 주변에서 1부위 교환
5. 유망한 부위쌍에 한해 제한된 2부위 교환

이는 Greedy 선택을 여러 갈래로 분기해 미래를 보존하려는 의도를 현재 2슬롯 패키지 구조에 맞게 구현한 것이다.

### 6.2 Utility repair

공격 점수가 높은 빌드가 Utility 하나 때문에 infeasible이면 즉시 버리지 않는다.

1. 부족 Utility와 잔여량을 계산한다.
2. 각 부위에서 부족분 공급 대체 패키지를 DPS 손실 순으로 찾는다.
3. 1부위 교환 후에도 부족하면 제한된 2부위 교환을 검사한다.
4. 실제 evaluator로 feasibility와 최종 대미지를 확인한다.

MAXMP와 AMPR처럼 파생 관계가 있으면 옵션 합이 아니라 교환 후 Outcome으로 부족분을 다시 계산한다.

### 6.3 국소 개선

여러 feasible seed에서 시작해 개선이 멈추거나 예산이 끝날 때까지 반복한다.

```text
현재 완성 빌드
  → 1부위 교환
  → 유망 부위쌍 Top-M × Top-M 교환
  → 실제 점수가 오르면 기준 빌드 갱신
```

반복 횟수·평가 수·시간을 제한한다. 이는 지역 최적점을 완화하는 초기해 탐색이며 exact 증명이 아니다.

## 7. 현재 D4 연결 위치

현재 optimizer 초기해는 현재 장착, 고정 가중치 utility 조합, 고정 가중치 damage 조합과 제한된 Pair 경로다. 새 경로는 기존의 빠른 초기해를 보존하고 prepared group 생성 뒤에 추가한다.

```text
기존 초고속 초기해
  → relevant key와 prepared group
  → DynamicMarginalProfile
  → 부위별 multi-seed pool
  → 완성 빌드·repair·국소 개선
  → incumbent 갱신
  → 기존 candidate tree와 B&B
```

권장 파일 경계:

- `assets/js/d4-dynamic-seed.js`: 점수, pool, beam, repair, 국소 개선
- `assets/js/d4-global-optimizer.js`: incumbent 병합과 탐색 순서
- `assets/js/d4-source-profile.js`: residual과 Supply Frontier
- `assets/js/build-evaluator.js`: aggregate/summary 평가 재사용
- `assets/js/d4-optimizer-worker.js`: 취소, 시간 예산, 정책 버전

처음에는 명시적 실험 옵션으로 두고 성능 Gate 전에는 Worker 기본값을 바꾸지 않는다.

## 8. 실행 시간 예산

초기해 계산도 10초 전체 예산에 포함한다. 다음 제한 중 먼저 도달하면 seed를 종료하고 현재 incumbent로 B&B를 시작한다.

- `seedTimeLimitMs`
- `seedEvaluationLimit`
- `beamWidth`
- `perSeedLimit`, `mergedGroupLimit`
- 국소 개선 반복·교환 한도
- Worker 취소

기본 숫자는 설계만으로 확정하지 않는다. K와 평가 제한을 단계적으로 늘려 다음 곡선을 측정한다.

```text
seed 시간
→ seed 종료 LB
→ B&B 시작 gap
→ 5초/10초 gap
→ exact 도달 시간 또는 미도달
```

채택 기준은 seed 자체가 아니라 **컴파일+seed+B&B 전체 P95 개선**이다.

## 9. 구현 Gate

### S0 — 기준선 계측 (완료: 2026-08-27)

- `d4-initial-seed-telemetry.v1`을 추가했다. raw 현재 장착·utility·damage seed, Pareto 준비 후 seed, coordinate 보강, Pair 하한, heuristic 완료, root UB를 각각 기록한다.
- 기본 checkpoint는 100ms·500ms·1s·5s·10s다. 각 checkpoint는 관측 시각, LB·UB·gap, 평가 수, 방문 노드, 남은 노드, bound/constraint prune 수를 보존한다.
- `tools/test-d4-full-stage3.mjs`가 실제 425개 fixture에서 모든 S0 phase와 5초까지의 checkpoint를 검사하며, `tools/benchmark-d4-exact.mjs` v2가 콜드 실행별 raw/heuristic/root/checkpoint를 출력한다.
- 이 단계는 후보, 점수, tree 정렬, 상한, 탐색 종료 규칙을 변경하지 않는다. 계측만 추가했다.

실행 근거: 10초 콜드 1회에서 raw 초기해는 3회 평가·LB 8,914, 기존 coordinate 보강 뒤에는 1,511회·LB 14,089, root UB는 49,037이었다. 최종은 bounded, gap 35.794%였다. 이는 P95 기준선이 아니라 S0 출력 형식 확인용 단일 실행이며, 이후 S1~S7의 비교 기준은 콜드 10회 P95로 다시 측정한다.

완료 기준: 새 기능 OFF에서 기존 결과와 시간 분포를 재현한다. `test-d4-global-optimizer-stage2`, `test-d4-full-stage3`, `test-d4-worker-stage3`, `test-d4-browser-worker-runtime`을 통과했다.

### S1 — DynamicMarginalProfile (완료: 2026-08-27)

- `assets/js/d4-dynamic-marginal.js`의 `toram.d4-dynamic-marginal.v1`이 baseline Outcome과 부위·패키지별 로그 한계 대미지(`100 × ln(after/before)`)를 기록한다. 이 점수는 후보 삭제·상한·탐색 순서에 쓰지 않는 계측값이다.
- 패키지 전체 효과와 physicalAttack·magicAttack·range·critical·unsheathe·other 효과 벡터 투영을 각각 동일 BuildEvaluator로 재평가한다. 공격/방어 지표와 MAXHP·MAXMP·AMPR·ASPD·행동속도·CSPD의 변화, SourceProfile 기반 Utility 잔여 요구량 감소를 함께 보존한다.
- signature에는 BuildEvaluator scenario hash 외에도 공격 유형·거리·발도/변환·ATK 선택 방식·대상 DEF/MDEF·물리/마법 관통·크리티컬 경계·requirements·기본 stats를 명시적으로 포함한다. 입력 group/package 순서와 무관하게 profile ID·행 순서는 결정적이다.
- Worker도 모듈을 로드하지만, S1은 결과 경로를 아직 사용하지 않는다. S2에서만 이 profile을 Top-K seed 구성에 연결한다.

실행 근거: `node tools/test-d4-dynamic-marginal.mjs`는 혼합 패키지의 전체·각 공격축 값을 직접 evaluator 결과와 1e-12 이내로 비교하고, 실제 425개 크리스타에서 컴파일된 14,973개 패키지 전부를 기록했다. 이 실행은 총 58,309회 evaluator 측정을 수행했고 모든 expected damage가 유한했다. `node tools/test-d4-browser-worker-runtime.mjs`는 Worker 모듈 로딩 계약도 검사한다.

완료 기준 충족: 기록 점수는 직접 evaluator 전후값과 일치하며, 입력 순서를 뒤집어도 profile hash가 동일하고 boss DEF를 바꾸면 Scenario signature가 달라진다.

### S2 — Multi-seed pool (완료: 2026-08-27)

- `assets/js/d4-dynamic-seed.js`의 `toram.d4-dynamic-seed-pool.v1`이 S1 profile로부터 부위별 Top-K pool을 만든다. 순수 기대 대미지, Scenario에서 활성인 physical/magic/range/critical/unsheathe 축, Utility 공급량, Utility frontier의 공급 최대·최소 대미지 손실·무릎점을 합친다.
- 현재 장착 패키지와 활성 Utility frontier landmark는 `mergedGroupLimit`과 무관하게 보존한다. 다른 후보는 full marginal score의 결정적 ID 동점 규칙으로 제한한다. 각 pool 항목은 `current`·`damage`·`axis:*`·`utility:*`·`frontier:*`·`balanced` 중 하나 이상의 포함 이유와 rank/metric을 가진다.
- pool은 별도 자료구조일 뿐 원래 `problem.groups[*].packages`를 변형하거나 optimizer에 전달하지 않는다. 따라서 pool 밖 후보, 잠금/계보/조건 후보, 상한과 exact 공간은 S3 이전에 그대로 보존된다.
- Worker는 향후 S3 사용을 위해 모듈을 로드하지만, 기본 초기해·추천 결과·탐색 순서는 아직 불변이다.

실행 근거: `node tools/test-d4-dynamic-marginal.mjs`는 입력 permutation에서도 pool hash가 같고, 활성 Utility마다 공급 대표와 모든 항목의 포함 이유가 있음을 검사한다. small exact fixture에서는 seed pool 밖 저가치 후보가 원래 문제에 남아 oracle과 solver의 exact 조합이 일치함을 확인했다. 실제 425개에서는 14,973개 원본 패키지를 유지한 채 pool이 무기 28·몸장비 25·추가 31·특수 29개로 결정적으로 생성됐다.

완료 기준 충족: 입력 순서가 바뀌어도 pool ID·순서가 같고 활성 Utility 공급 대표가 존재하며, pool 밖 후보가 exact problem에서 제거되지 않는다.

### S3 — 완성 빌드와 repair (완료: 2026-08-27)

- `createDynamicSeedBuilds`가 S2 pool의 네 부위를 하나씩 선택한 실제 완성 빌드만 반환한다. pool product가 `cartesianLimit` 이하이면 모든 조합을 직접 평가하고, 크면 실측 partial Outcome의 대미지 우선과 잔여 Utility 우선 후보를 함께 보존하는 결정적 beam을 사용한다.
- 모든 partial·complete·repair 평가는 같은 BuildEvaluator aggregate 경로를 사용한다. 대미지 점수 합이나 옵션 합산만으로 feasibility/LB를 판정하지 않으며, 반환된 `statDelta`와 `outcome`은 직접 evaluator 재실행과 일치한다.
- infeasible complete seed는 부족 Utility를 다시 계산한 뒤, 부위별 baseline 공급·대미지 순위로 1부위 교환을 먼저 검사하고 필요할 때만 제한된 2부위 교환을 검사한다. 이미 Cartesian에서 평가한 동일 조합도 `repairAttemptIds`에 남겨 repair 시도 자체를 감사할 수 있다.
- 시간·평가 수·취소를 모든 enumeration, beam expansion, repair loop에서 확인한다. S3도 아직 incumbent·candidate tree·B&B를 갱신하지 않으므로 기본 Worker 결과는 변하지 않는다.

실행 근거: `node tools/test-d4-dynamic-seed-builds.mjs`는 4부위 Cartesian, partial beam, 직접 complete evaluator 일치, 한 부위로는 부족하고 두 부위 교환으로 충족되는 Utility repair, 취소를 검사한다. 실제 425개는 S2 pool(28×25×31×29)에서 제한 beam으로 2,559회를 평가해 네 부위가 모두 선택된 결과만 만들었고, 각 결과를 직접 evaluator와 비교했다.

완료 기준 충족: seed 빌드는 compiler의 부위별 CandidatePackage 구조를 보존하고 보고 outcome이 직접 평가와 일치한다.

### S4 — incumbent와 국소 개선 (완료: 2026-08-27, S7 이전 기본 비활성)

- `enableDynamicSeedIncumbent: true`와 양의 `dynamicSeedTimeLimitMs`가 함께 주어진 실험 경로에서만 S1→S3→local 결과를 기존 incumbent에 병합한다. 기본 Worker/UI 옵션은 이 값을 설정하지 않으므로 기존 초기해·추천·탐색 시간 분포는 바뀌지 않는다.
- feasible seed와 local 후보를 실제 score 내림·ID 오름차순으로 병합하고, 기존 `considerOutcome`의 feasibility·동점 계약으로만 incumbent를 갱신한다. 따라서 더 낮은 seed는 기존 incumbent를 덮어쓸 수 없고, 후보 domain·상한·exact 종료 규칙도 바뀌지 않는다.
- local 개선은 상위 feasible seed별로 제한된 1부위 교환을 먼저, 개선이 없을 때만 제한된 부위쌍 교환을 직접 evaluator로 검사한다. 시작/종료 LB, 평가 수, pool/profile hash, accepted 수, 중단 이유, 성공 교환 경로는 `dynamicSeedReport` 및 `dynamicSeedIncumbent` telemetry phase에 남긴다.
- 실제 425개에서 1.5초 S4 예산은 profile 포함 16,249회(완성 seed 636, local 56)를 추가했고 incumbent를 9,965에서 14,089로 올렸으나 이는 기존 coordinate 탐색도 도달하는 값이었다. 5초 인증 gap은 단일 비교에서 50.713%로 기본 경로의 49.294%보다 개선되지 않았다. 성능 승격은 S7 P95 승인 전까지 보류했다.

완료 기준 충족: `node tools/test-d4-global-optimizer-stage2.mjs`의 S4 ON/OFF small exhaustive는 oracle의 exact score·동점 ID가 동일하며, 실제 425개 ON 회귀는 feasible 결과와 dynamic report를 반환한다. S7 승인 전의 기본 OFF도 기존 Stage 3 성능 계약을 통과했다.

### S5 — 탐색 순서 (완료: 2026-08-28, S7 이전 기본 비활성)

- `createDynamicCandidateOrder`는 S1 profile의 모든 package ID를 보존하고, full marginal DPS 내림 → 현재 잔여 Utility 충족도 내림 → ID 오름차순의 결정적 순서를 `toram.d4-dynamic-candidate-order.v1`과 hash로 기록한다. 이 순서표는 후보 pool이나 exact domain이 아니다.
- 명시적 실험 옵션 `enableDynamicSeedOrdering: true`에서만 S4 profile로 순서표를 만들고 candidate tree의 split 값 동점 보조 순서에 사용한다. split 축, envelope, 안전 상한, 큐의 `upper → pathId` 우선순위, 노드 범위와 종료 조건은 변경하지 않는다. 감사 전용 `dynamicCandidateOrder` 입력도 같은 tree를 재현한다.
- S5 ON/OFF 소형 exhaustive, package 입력 반전, 동점 ID, 같은 순서표 candidate tree의 upper-bound/envelope audit을 모두 검사한다. 실제 425개 1.5초 S4+S5 단일 5초 실행 두 번은 `candidateOrderHash=7462a683`, bounded gap 42.594%·43.161%를 보였지만 P95 비교 전이므로 당시 Worker 기본값은 OFF로 유지했다. S7 P95 승격 결과는 아래를 따른다.

완료 기준 충족: `node tools/test-d4-global-optimizer-stage2.mjs`가 S5 ON과 input permutation의 exact score·동점 ID, order hash, tree upper/envelope 위반 0건을 확인했다. `node tools/test-d4-dynamic-marginal.mjs`는 전체 package 보존·순서표 permutation 결정성을, `node tools/test-d4-full-stage3.mjs`는 실제 425개 S4+S5 report를 확인한다.

### S6 — Replacement Proof 연결 (완료: 2026-08-28, 분석·감사 전용)

- `d4-source-profile.js`의 `createReplacementProofReport`는 같은 부위의 이미 유효한 2슬롯 package만 비교한다. 현재 candidate tree의 모든 package를 유지하며, full stat-effect vector, capped 순수 Utility, raw Utility, 구조·해결 조건·부위 충돌 범위·계보 범위·동점 ID를 `safeResidualDominance`에 모두 전달한다.
- `toram.d4-replacement-proof-report.v1`은 낮은 점수 또는 부분 우위 후보를 `unprovenWitnesses`로만 남긴다. 실제 `provenDrop`에는 scenario hash, witness ID, 보존 서명, objective/utility/feasibility/replacement/tie-break proof와 policy version을 가진 `d4-pruning-certificate.v1` 및 certificate hash가 반드시 붙는다.
- `applyProvenDropsForAudit`은 certificate가 있는 package만 복사본에서 제외하는 테스트 도구다. compiler, Worker 기본 경로, candidate domain, Pareto, upper bound, exact 종료에는 연결하지 않았으므로 실사용 후보는 아직 삭제되지 않는다. 다부위 B+C 전사 치환과 scalar 기회비용 기반 삭제도 S6 범위 밖이다.

완료 기준 충족: `node tools/test-d4-replacement-proof.mjs`는 동일 벡터의 빠른 ID package를 certificate로 교체한 축소 전후 exhaustive score·동점 ID 일치, MAXMP raw 의존성과 조건 서명이 다른 witness의 삭제 거부, input permutation을 검사한다. `node tools/test-d4-dynamic-marginal.mjs`는 실제 425개 prepared package 전체를 끝까지 스캔하고 report hash의 permutation 결정성을 확인한다.

### S7 — 실제 425개 승인 (완료: 2026-08-28, seed+ordering 승격)

`tools/benchmark-d4-s7.mjs`로 실제 최종 강화 크리스타 425개, 물리 근거리 고정 Scenario를 새 Node 프로세스 10회씩 측정했다. 비교 시간은 compiler/preparation + seed + B&B 전체이고, 제한은 10초다.

| 변형 | exact/bounded | core P95 | 인증 gap P95 | 판정 |
| --- | --- | ---: | ---: | --- |
| OFF | 0/10 | 10,146.5ms | 39.68% | 기준 |
| seed-only | 0/10 | 10,132.3ms | 40.34% | gap 악화, 미승격 |
| seed+ordering | 0/10 | 10,133.3ms | 34.58% | 승인 |
| seed+ordering+proof-audit | 0/10 | 18,490.0ms | 35.38% | 삭제 0건, 감사 전용 |

모든 소형 oracle/property/determinism 검사와 exact 동점 ID 검사는 통과했고, S7 측정에서 거짓 exact·잘못된 삭제는 없었다. `seed+ordering`은 core P95를 13.2ms 낮추고 bounded 인증 gap P95를 5.10%p 낮췄으므로 활성화 조건을 충족했다.

따라서 `d4-dynamic-seed-ordering.s7.v1`을 WorkerClient와 Worker의 기본 정책으로 승격했다. 1.5초 seed 예산과 제한된 beam/repair/local 설정은 측정값과 동일하게 고정하며, 명시적으로 `enableDynamicSeedIncumbent:false`를 전달하면 둘 다 끌 수 있다. 이 정책은 초기 feasible 하한과 split 값 동점 정렬만 바꾸며 candidate domain, 안전 상한, heap 우선순위, exact 종료 규칙은 바꾸지 않는다.

Proof audit은 동일 조건 425개 fixture에서 완결 report hash `f40f2179`, proven drop 0건이었고 preparation에 약 8.3초를 추가했다. 따라서 `createReplacementProofReport`와 `applyProvenDropsForAudit`은 계속 분석·감사 전용이며 Worker 후보 삭제에는 연결하지 않는다.

## 10. 필수 테스트

- 대상 DEF 저·고와 물리관통 경계
- 기존 거리 위력 저·고
- 크리티컬 대미지 경계 전·경계·경계 후
- 크리티컬률 부족·정확히 충족·초과·확정 크리티컬
- 발도 미적용·적용·일진강풍
- STR%·DEX%의 다중 효과와 단계별 내림
- MAXMP 증가로 AMPR이 변하는 사례
- CRIT·AMPR을 두 부위 결합으로만 충족하는 사례
- 즉시 점수 A가 높지만 B+D 결합이 최적인 Greedy 반례
- Utility 과잉, 음수 Utility 고DPS
- 현재 장착, 잠금, 금지, 계보 충돌, 공용 크리스타 반복
- 유효 조합 없음
- seed ON/OFF와 small exhaustive 비교
- 입력 순서 permutation, 동점 ID
- 평가 예산 0, 중간 취소
- Top-K 밖에 실제 최적 후보를 둬도 exact가 찾는지 확인

## 11. 측정 항목

각 fixture에 다음을 기록한다.

```text
scenarioHash, policyVersion
groupPackageCounts, seedPoolCounts
seedTimeMs, seedEvaluations
baselineInitialLB, dynamicSeedLB, seedGainPercent
rootUB, gapAfterSeed
firstFeasibleMs
visitedNodes, prunedByBound, prunedByConstraint
finalLB, finalUB, finalGap, status, totalElapsedMs
```

초기해 상승만 보고하지 않고 같은 시간에 실제 노드 제거와 exact 도달이 늘었는지 판단한다.

## 12. 실패 시 다음 분기

- **LB가 오르지 않음:** seed 다양성, partial marginal, Utility repair를 점검하고 계속 효과가 없으면 해당 Scenario에서 끈다.
- **LB는 오르지만 exact가 빨라지지 않음:** 병목은 UB다. seed 확대를 멈추고 Replacement Proof, 분기 후 필터 보존 상한, 계산 경계 envelope, 후보 포함 부분공간 UB로 이동한다.
- **seed가 너무 비쌈:** Cartesian을 beam으로 바꾸고 summary 평가·캐시를 쓰며 2부위 교환 폭을 줄인다.
- **특정 Scenario만 효과 있음:** scenarioHash와 정책 버전별로 예산·활성을 분리한다.

## 13. 장비 옵션부여 확장

검증된 옵션 카탈로그, 잠재력 비용, 장비 조건, 정확히 8줄, 음수 옵션, 성공률 fixture가 준비된 뒤 확장한다.

```text
옵션 초기해
  → 크리스타 동적 seed
  → 고정 크리스타에서 옵션 패키지 재최적화
  → 고정 옵션에서 크리스타 재최적화
  → 실제 점수가 더 오르지 않으면 종료
```

이 결과도 통합 exact의 하한일 뿐이다. 후보 삭제와 상한에는 실제 잠재력·8줄·호환·배타·반올림을 검증한 DP frontier만 사용한다. 무기 67·몸장비 63과 90% 실사용 프로필은 초기 추천 실험에는 쓸 수 있지만 exact 증명에는 쓰지 않는다.

## 14. 구현 순서와 성공 기준

1. S0 계측
2. S1 동적 한계효용
3. S2 다중 seed Top-K
4. S3 완성 빌드·repair·beam
5. S4 incumbent·국소 개선
6. S5 탐색 순서
7. S6 Replacement Proof witness
8. S7 실제 425개 P95 승인

성공은 단지 좋은 추천이 아니다.

- 더 높은 feasible 초기 LB를 재현 가능하게 얻는다.
- 초기해 비용을 포함해 같은 시간에 더 많은 노드를 제거한다.
- 10초 exact 비율이 증가하거나 exact 도달 시간이 줄어든다.
- bounded fixture의 인증 gap이 줄어든다.
- 모든 exact 결과와 동점 ID가 oracle과 일치한다.
- 점수와 증명 경계가 코드·진단·문서에서 분리된다.

이 조건을 만족할 때만 기본 경로로 승격한다.
