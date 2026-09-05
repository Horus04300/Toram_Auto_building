# D4 실제 최종 강화 크리스타 전수 분석 기반 사전 축소 계획

- 문서 역할: 공급 구조 기반 축소의 설계 가설. 아래 단계는 구현 여부나 새 구현 승인을 뜻하지 않는다. 실제 채택은 코드와 `docs/architecture/d4-exact-optimization-plan.md`의 증명 Gate로 확인한다.
- 기준일: 2026-08-26
- 목표: 실제 사용 가능한 최종 강화 크리스타의 공급 구조를 전수 분석해, `exact`를 훼손하지 않는 `Proven Drop`만 D4 후보 컴파일 단계에 연결한다.
- 상위 계약: `d4-exact-optimization-plan.md`, `d4-build-optimizer-design.md`, `d4-build-optimizer-prerequisites.md`
- 강한 초기해 상세 계획: `d4-dynamic-score-exact-acceleration-plan.md`
- 분석 근거: `D4 전역 크리스타 최적화 — 탐색 공간 사전 축소 전략 분석.md`, `equipment-option-assignment-spec.md`

## 1. 결론

다음 D4 개선의 우선순위는 탐색기 후단의 상한을 더 복잡하게 만드는 것보다, 실제 최종 강화 크리스타가 만드는 입력 공간을 시나리오별로 증명 가능하게 축소하는 것이다.

단, 크리스타 이름이나 물리·마법 같은 단일 분류값으로 삭제하지 않는다. 모든 판단은 현재 구조에서 해결된 효과 벡터, 부위, 두 슬롯 패키지, Utility 원값 의존성, 계보·중복·조건, 결정적 동점 규칙을 보존해야 한다.

기회비용·사용 빈도·평균 효율은 초기해와 탐색 순서에만 사용한다. 실제 삭제는 별도 증명서가 있는 경우에만 허용한다. 단, 단순 그림자가격과 구별되는 **Replacement Proof**는 삭제 증명으로 사용할 수 있다. Replacement Proof는 제거 대상이 들어간 모든 허용 문맥을 동등하거나 더 좋은 실제 대체 선택으로 바꾸는 전사 규칙을 제시해야 한다.

이 문서의 R0~R8 범위는 **Crysta-only opportunity cost**다. 즉 실제 최종 강화 크리스타와 현재 사용자가 입력·활성화한 고정 스탯만으로 공급·대체 가능성을 판단한다. 장비 옵션, 고정 장비 카탈로그, 스킬·버프·음식의 선택 자체를 최적화 대상으로 포함하는 전역 기회비용은 각 공급원 데이터 계약이 준비된 뒤에만 확장한다.

## 2. 현재 확인된 기반과 정보 공백

### 2.1 현재 사용할 수 있는 기반

- 원본 크리스타 데이터는 425개이며 `d4-problem-compiler.js`가 강화 계보의 하위 후보를 기본 제외한다.
- 조건 키 `main`, `sub`, `armor`는 장비 구조를 먼저 확정한 뒤 활성 효과 벡터로 변환한다.
- 같은 크리스타는 다른 장비에 반복할 수 있지만 같은 장비에는 중복할 수 없다.
- 같은 강화 계보와 같은 시작점의 분기 강화는 같은 장비 안에서 충돌한다.
- `StatRegistry` 감사 결과는 크리스타 원시 키 87종, 스킬 키와 합친 원시 키 111종, 미등록 키 0종이다.
- 현재 계산에 연결된 스탯과 향후 보존 스탯은 구분돼 있다. 보존 스탯은 값이 존재한다는 이유만으로 목적함수 기여 또는 지배 축으로 사용하지 않는다.
- `BuildEvaluator`는 선택 공격 기대 대미지와 MAXHP, MAXMP, AMPR, 평타 크리티컬, ASPD, 행동속도, CSPD를 같은 계산 경로에서 반환한다.
- `d4-source-profile.js`는 Utility 의존성, 잔여 요구량, 단일 부위 패키지 변화량, 로그 대미지 변화와 공급 집중도를 계산한다.
- 현재 실제 부족 fixture에서 MAXHP·ASPD는 단일 2슬롯 패키지 충족원이 존재하지만 MAXMP·AMPR·평타 크리티컬은 단일 패키지 충족원이 없어 부위 결합이 필요하다.

### 2.2 즉시 확인된 정보 공백

장비 옵션부여 사양에는 데이터 계약만 있고 다음의 검증 완료 카탈로그가 없다.

- 옵션별 `min`, `max`, `step`
- 기준 레벨에 따른 수치 상한
- 양수·음수 옵션의 잠재력 비용
- 무기·몸장비 및 세부 유형 호환성
- 옵션 간 배타·요구 조건
- 출처와 규칙 버전이 연결된 검증 상태

따라서 현재 단계에서 확정할 수 있는 것은 실제 크리스타의 부위별 공급 상한과 사용자가 이미 입력한 고정 장비 효과까지다. 장비 옵션부여가 추가로 공급할 수 있는 이론 상한과 잠재력 기회비용은 검증 카탈로그가 준비되기 전에는 계산하거나 추정하지 않는다.

고정 장비 전체 카탈로그도 현재 없으므로, 일반 장비의 전역 공급 상한은 사용자 입력 스냅샷에 포함된 값만 반영한다.

마이룸 요리처럼 사용자가 활성화 여부와 수치를 입력하는 버프, 그리고 현재 스테이터스 탭의 CRT 투자값은 `FixedInputSupply`다. 이들은 후보 축소 **이전**에 BuildEvaluator의 기본 Context로 반영하여 CRIT 잔여 요구량과 후보의 한계가치를 바꾸지만, D4가 음식 선택·스테이터스 포인트 배분을 결정하지 않는 현재 범위에서는 슬롯 기회비용 또는 대체 공급 frontier에 넣지 않는다. 입력되지 않은 음식·버프는 자동으로 가정하지 않는다.

사용자가 장비 옵션부여에서 크리티컬 대미지+, 크리티컬 대미지%, 크리티컬률+의 현 레벨 최대치를 알고 있더라도, 실제 수치·출처·장비 호환·잠재력 비용이 검증 카탈로그로 제공되기 전에는 R9의 상한에 넣지 않는다.

### 2.3 제작 잠재력 프로필과 부여 공식 출처

사용자 제공 기본 잠재력 기준은 무기 67, 몸장비 63이다. 이는 제작 성공 장비의 시작 잠재력 상한 분석에 사용할 입력값으로 기록하되, 원문 출처·반올림 순서와 함께 검증되기 전에는 게임의 확정 상수로 표시하지 않는다.

Smith 원문은 신중한 제작과 장인의 제작기술의 기본 잠재력 증가가 스탯 보너스 전 단계에서 합산됨을 설명한다. 따라서 제작 잠재력 상한은 아래처럼 별도 계약으로 모델링한다.

```text
CraftPotentialCeiling = applyVerifiedRounding(
  basePotential(type) × (1 + (carefulCraftLevel + 2 × masterCraftLevel) / 100)
) + typeSpecificBaseStatBonus
```

`typeSpecificBaseStatBonus`는 제작 캐릭터의 기본 STR/DEX/INT/AGI/VIT와 장비 유형에 따라 결정한다. 실제 제작 실패·슬롯 수에 따른 잠재력 감소와 최종 반올림 순서가 확인되기 전에는 위 식의 값으로 사용자 장비의 시작 잠재력을 확정하지 않는다.

실사용에서 2슬롯 제작품의 시작 잠재력을 약 10% 낮게 본다는 값은 `practicalPotentialRatio = 0.90`이라는 **휴리스틱 프로필**로만 제공한다. 이는 현실적인 추천 정렬·표시에는 쓸 수 있지만, 후보 infeasible 증명, `Proven Drop`, exact 상한 또는 자동 옵션부여의 확정 예산에는 사용하지 않는다. 그 경로들은 사용자가 입력한 실제 시작 잠재력 또는 검증된 제작 상한만 사용한다.

Dodamu 수동·자동부여와 Coryn Statting Simulator는 R9 카탈로그와 fixture의 교차 검증 출처다. Dodamu 자동부여는 사용자가 선택한 양수 옵션을 대신 고르는 D4 목적함수가 아니라, 음수 옵션·부여 단계·반복을 조합해 성공률 또는 소재량 기준의 부여 공식을 비교하는 도구로 취급한다. 따라서 자동부여가 산출한 결과는 대표 부여 패턴과 최소 시작 잠재력/성공률 fixture로 채택하되, 코드나 휴리스틱 순위를 그대로 복사하지 않는다.

## 3. 분석 대상의 정확한 정의

`실제 사용되는 최종 강화 크리스타`는 인기·사용 빈도가 아니라 다음 조건으로 결정한다.

1. `crysta-data.js`에 등록되어 있다.
2. 다른 등록 크리스타의 `prev`로 참조되는 하위 강화체가 아니다.
3. 현재 장비 부위에 장착 가능한 전용 또는 공용 크리스타다.
4. 사용자가 금지하지 않았다.
5. 현재 구조 조건을 해결한 뒤에도 구조·계보·동점 증명에 필요한 원본 메타데이터를 보존한다.

공용 크리스타는 하나의 전역 후보로만 세지 않고, 무기·몸장비·추가·특수의 서로 다른 슬롯 공급원으로 각각 분석한다. 같은 효과라도 슬롯 기회비용이 다르기 때문이다.

분석의 최소 단위는 단일 크리스타와 부위별 2슬롯 패키지 두 층이다.

- 단일 크리스타 층: 무관 효과 투영, 조건 해석, 계보·부위 서명, 명백한 동등성 후보 탐지
- 2슬롯 패키지 층: 실제 Utility 공급, 다른 한 슬롯과의 보완, 슬롯 비용, 계보 충돌, 대미지 기회비용 판정

단일 크리스타가 열등해 보여도 다른 한 슬롯과 결합해 Utility 경계를 정확히 만족할 수 있으므로, 전역 삭제는 패키지 수준 증명 없이 수행하지 않는다.

## 4. 데이터 모델

### 4.1 ScenarioProjection

```text
ScenarioProjection {
  scenarioHash,
  structureSignature,
  dependencyPolicyVersion,
  objectiveKeys,
  hardConstraintKeys,
  rawRequiredKeys,
  ignoredKeys,
  calculationBoundaryMetadata
}
```

`objectiveKeys`와 `rawRequiredKeys`는 공격 유형 이름으로 고정하지 않고 실제 계산 의존성에서 얻는다. 물리·마법, 근거리·원거리, 발도, 일진강풍 변환, 확정 크리티컬, 대상 DEF/MDEF·내성, 듀얼소드 AMPR, 신속의 수도 등 계산 경계를 시나리오 서명에 포함한다.

### 4.2 CrystaSupplyRecord

```text
CrystaSupplyRecord {
  candidateId,
  lineageRoot,
  terminalUpgrade,
  slotGroup,
  structureSignature,
  conditionSignature,
  rawEffectVector,
  projectedEffectVector,
  preservedEffectVector,
  availability,
  sourceVersion
}
```

`rawEffectVector`는 원문 데이터를 보존하고, 비교에는 `projectedEffectVector`를 사용한다. 계산에 아직 연결되지 않은 보존 스탯은 0으로 취급하지 않고 삭제 증명을 차단하는 보수적 의존성으로 처리한다.

### 4.3 PackageSupplyPoint

```text
PackageSupplyPoint {
  packageId,
  slotGroup,
  candidateIds,
  statDelta,
  rawUtility,
  cappedConstraintContribution,
  outcomeDelta,
  deltaLogDamage,
  remainingSlotCapacity,
  structureSignature,
  conditionSignature,
  conflictSignature,
  lineageSignature
}
```

Supply Frontier는 다음 축을 최소한 보존한다.

- 옵션/Utility 종류와 실제 수치 단계
- 장비 부위와 소비 슬롯 수
- 선택 공격 대미지의 `DeltaLogDamage`
- MAXHP, MAXMP, AMPR, 평타 크리티컬, ASPD의 raw 값
- 순수 제약으로 증명된 경우에만 잔여 요구량까지 포화한 값
- 다른 Utility와의 동시 공급
- 구조·조건·계보·충돌·동점 서명

### 4.4 PruningCertificate

```text
PruningCertificate {
  ruleId,
  scenarioHash,
  removedId,
  witnessIds,
  coveredSlotGroups,
  preservedSignatures,
  objectiveProof,
  utilityProof,
  feasibilityProof,
  replacementProof,
  tieBreakProof,
  policyVersions
}
```

삭제된 모든 후보 또는 패키지는 재현 가능한 증명서를 남긴다. 증명서가 없거나 정책 버전이 달라지면 캐시된 삭제 결과를 사용하지 않는다.

`replacementProof`는 다음 중 하나여야 한다.

1. 같은 부위·같은 슬롯 비용의 대체 후보가 모든 목적·raw Utility·구조 서명에서 우위인 단순 치환
2. 같은 부위의 2슬롯 패키지 A가 같은 자원 비용의 패키지 B로 바뀌는 패키지 치환
3. 여러 부위 대체가 필요한 경우, A를 포함하는 모든 허용 완성 문맥마다 충돌·계보·Utility 제약을 보존하면서 더 나쁘지 않은 완성 문맥으로 대응시키는 전사 규칙

초기 구현은 1과 2만 기본 삭제 규칙으로 허용한다. 3은 전역 문맥 증명 비용이 커지므로 별도 oracle과 성능 Gate 없이 활성화하지 않는다.

## 5. 공급 상한의 층위

상한을 하나로 합치지 않고 출처별로 구분한다.

1. `CrystaGroupBound`: 실제 최종 강화 크리스타가 특정 부위 0~2슬롯에서 제공 가능한 좌표별 안전 상한
2. `RemainingCrystaBound`: 일부 슬롯을 선택한 뒤 남은 크리스타 슬롯에서 제공 가능한 Utility·공격축 상한
3. `FixedInputSupply`: 현재 세팅에서 활성화된 스킬·버프·요리·도핑·길드·수동 장비 옵션 및 고정 스테이터스의 공급량
4. `EquipmentOptionBound`: 검증된 옵션부여 카탈로그와 잠재력·8줄 제약 아래 무기·몸장비가 제공 가능한 상한
5. `GlobalResidualBound`: 고정 공급량을 뺀 부족분과 남은 슬롯별 상한을 결합한 feasibility 판정

현재 1~3은 구현·분석 가능하다. 4는 검증 카탈로그 부재로 차단하며, 5는 4를 제외한 현재 크리스타 전용 범위부터 구현한다.

옵션부여 상한은 각 옵션의 독립 최대값을 합친 가상 장비로 만들면 안 된다. 정확히 8줄, 잠재력, 음수 옵션, 호환·배타 조건을 만족하는 Pareto DP 상태의 envelope만 안전 상한으로 인정한다.

## 6. 단계별 구현 Gate

### Gate R0 — 재현 가능한 전수 목록

- 원본 425개에서 최종 강화체를 결정하는 lineage terminal 목록을 생성한다.
- 부위별 전용·공용 후보 수, 조건부 후보 수, 원시/정규화 스탯 키를 기록한다.
- 현재 compiler가 만든 부위별 단일 후보 수와 2슬롯 패키지 수를 같은 입력에서 대조한다.
- 사용자 금지·잠금은 데이터 전수 목록과 분리해 별도 입력 차이로 기록한다.

완료 기준은 같은 데이터 버전에서 ID·개수·해시가 결정적으로 재현되는 것이다.

### Gate R1 — 계산 의존성 투영

- `StatRegistry`의 정적 역할만으로 의존성을 추정하지 않고 `BuildEvaluator`와 계산 커널의 실제 읽기 의존성을 시나리오별 정책으로 등록한다.
- 활성 계산 축, raw 보존 축, 무관 축, 불명 축을 구분한다.
- 불명 또는 보존 전용 축이 존재하면 후보를 유지한다.
- 불가능한 구조 조건은 효과를 0으로 투영하되 원본 조건 메타데이터를 보존한다.

완료 기준은 투영 전후 완성 빌드 Outcome이 소형·실제 표본에서 일치하는 것이다.

### Gate R2 — 부위별 Package Supply Map

- 최종 강화 크리스타를 무기·몸장비·추가·특수의 실제 2슬롯 패키지로 컴파일한다.
- 각 패키지를 원래 `BuildEvaluator`로 평가해 공격축·Utility 변화량을 얻는다.
- 옵션 × 수치 단계 × 부위 × Scenario × 슬롯 비용 단위의 Supply Map을 만든다.
- CRIT, MAXMP, AMPR, ASPD, MAXHP뿐 아니라 현재 목적함수에 읽히는 ATK/MATK, 관통, 거리 위력, 크리티컬 대미지, 발도, 스탯 계열을 함께 기록한다.
- 단일 패키지가 주는 값뿐 아니라 해당 부위 frontier와 DPS 손실 최솟값을 계산한다.

이 Gate의 결과는 분석·초기해·탐색 순서에만 사용하고 후보를 삭제하지 않는다. 결과의 범위는 Crysta-only로 명시하고, 고정 입력은 이미 계산된 baseline으로만 반영한다.

### Gate R3 — 구조·동등성 축약

- 현재 구조에서 완전히 무관한 투영 벡터를 찾는다.
- evaluator 효과가 같아도 계보·중복·충돌·동점 규칙이 다르면 병합하지 않는다.
- 동일한 모든 서명과 동일 투영 벡터를 가진 후보만 대표 ID와 대체 ID 집합으로 묶는다.
- 후보가 같은 부위에서 최소 하나의 합법적인 2슬롯 패키지에 참여할 수 있는지 검사한다.
- 계보·중복·잠금·금지와 남은 슬롯 domain에 대해 arc consistency와 잔여 domain propagation을 수행한다.
- 어느 남은 부위 domain도 비거나, 국소 제약만으로 충족 불가능한 상태만 제거한다.
- “최소 하나의 전역 완성 조합이 존재하는가”를 이 Gate에서 정확히 탐색하지 않는다. 그것은 축소 전 전역 탐색을 다시 수행하는 비용을 만들 수 있으므로 R4 이후 작은 문제 또는 oracle 감사에서만 확인한다.

이 단계의 실제 삭제는 semantic/structural/tie-break equivalence 또는 위의 값싼 필요조건만으로 완성 불가능성이 증명된 경우에만 허용한다.

### Gate R4 — Residual Feasibility

- 현재 고정 공급량을 평가해 Utility 잔여 요구량을 계산한다.
- 후보 또는 패키지를 선택한 뒤 남은 각 부위의 안전한 최대 공급을 합산한다.
- 남은 모든 슬롯을 사용해도 요구치를 충족하지 못하면 해당 분기를 제거한다.
- MAXMP→AMPR, ASPD→행동속도, 평타 크리티컬의 목적함수 기여처럼 raw 값이 필요한 축은 파생 계산까지 포함한 Outcome 상한으로 판정한다.

독립 부위 최대값은 infeasible 증명용 안전 과대 상한으로만 사용할 수 있으며, feasible 조합의 존재 증거로 사용하지 않는다.

### Gate R5 — Strict Dominance와 Supply Frontier 지배

- 동일 구조·조건·충돌·계보·슬롯 비용 서명 안에서만 비교한다.
- 목적함수 관련 좌표, capped 순수 Utility, raw Utility가 모두 같거나 우수한 경우만 지배로 인정한다.
- 하나 이상의 엄격 우위 또는 동일 Outcome에서 더 빠른 결정적 ID가 있어야 한다.
- 크리스타 단독 지배와 2슬롯 패키지 지배를 별도 측정한다.

기회비용 frontier는 지배 증명의 입력이 될 수 있지만, 그림자가격이나 평균 DPS 손실만으로 지배를 증명하지 않는다.

대신 Replacement Proof를 추가한다. 예를 들어 물리 Scenario에서 `MATK + Utility` 후보 A가 제공하는 CRIT 14를, 동일 부위·동일 2슬롯 비용·동일 구조 서명 안의 패키지 B가 CRIT 14 이상과 더 높은 물리 Outcome으로 항상 대체하면 A 패키지를 `Proven Drop` 할 수 있다. CRIT 14를 B+C로 대체하는 경우에도 B+C가 같은 자원 비용을 쓰고 A를 포함하는 모든 허용 문맥에서 충돌·계보·hard constraint·동점 계약을 보존함을 증명해야 한다.

따라서 scalar opportunity cost는 heuristic, exact replacement dominance는 삭제 증명으로 명확히 분리한다.

### Gate R6 — Candidate/Package-Level Upper Bound

강한 실제 초기해의 점수 정의, 다중 seed Top-K, 패키지 조합, Utility repair, 국소 교환, 시간 예산과 성능 승인 절차는 `d4-dynamic-score-exact-acceleration-plan.md`의 Gate S0~S7을 따른다. 이 초기해는 하한과 탐색 순서만 바꾸며, 점수만으로 `Proven Drop`을 만들지 않는다.

- 다음 cheap-to-expensive cascade를 고정한다.
  1. 의존성 투영·불가능 조건·부위/계보 domain propagation
  2. 효과 벡터 strict dominance와 Replacement Proof 후보 생성
  3. BuildEvaluator를 호출하지 않는 좌표별 잔여 Utility/공격축 안전 상한
  4. 위 단계를 통과한 소수 후보·패키지에만 집계 `BuildEvaluator` 기반 상한
  5. 마지막 생존 집합에 기존 branch-and-bound 상한
- 강한 실제 초기해로 전역 하한을 확보한다.
- 후보 또는 패키지를 반드시 포함한 상태에서 남은 슬롯의 안전 envelope을 적용한다.
- `UB(candidate or package) < incumbent LB`인 경우에만 포함 부분공간 전체를 제거한다.
- 동점 최적해의 ID 계약을 보존하려면 점수가 같은 경우 더 빠른 동점 가능성을 별도로 검사한다.

상한은 기존 독립 envelope, 잔여 feasibility, 안전한 작은 상자 실제 최대값 중 검증된 상한의 최솟값을 사용한다. 실제 후보 하나를 상한으로 사용하지 않는다.

### Gate R7 — Compiler 연결

- R3~R6의 `Proven Drop`만 `d4-problem-compiler` 또는 Pareto 준비 직전에 연결한다.
- 삭제 규칙별 전후 후보·패키지 수와 증명서 해시를 문제 metadata에 남긴다.
- 분석 모드에서는 삭제 전후 두 문제를 모두 생성해 결과를 교차 비교한다.
- 정책·데이터·계산식·Scenario 버전을 캐시 키에 포함한다.

### Gate R8 — 정확성·성능 승인

- 소형 전수조사에서 축소 전후 exact 점수와 동점 ID가 일치해야 한다.
- 무작위 property에서 삭제된 후보를 강제 포함한 최고값이 최종 최적값을 이길 수 없음을 확인한다.
- 모든 후보 상한이 실제 포함 부분공간 최고값 이상이어야 한다.
- 실제 425개 데이터의 시나리오 fixture에서 추천 결과와 인증 gap을 기록한다.
- 기본 활성화는 실제 콜드 프로세스 10회 P95에서 컴파일+탐색 시간, exact 비율 또는 gap이 기준선보다 개선될 때만 한다.

안전성은 통과했지만 성능 개선이 없는 규칙은 분석 도구로만 남긴다.

### Gate R9 — 장비 옵션부여 공급원 통합

다음 선행조건을 모두 충족한 뒤 별도 착수한다.

- 검증된 옵션 카탈로그
- StatRegistry 1:1 매핑 감사
- 레벨별 상한·잠재력 비용·호환·배타 fixture
- 정확히 8줄과 잠재력 예산을 만족하는 Pareto DP
- 소형 옵션 도메인 전수조사와 DP 결과 일치

R9 데이터 수집은 다음 순서를 따른다.

1. Dodamu 수동부여에서 옵션별 잠재력 단가, 레벨별 min/max, 장비 조건, 양수·음수 수치 단위, 소재 분류를 독립 카탈로그로 전사한다.
2. Coryn Simulator와 Dodamu 자동부여의 대표 결과로 해당 카탈로그와 단계별 성공률·잠재력 소비를 교차 fixture화한다.
3. 자동부여의 결과는 `successRate` 우선과 `material` 우선 패턴을 별도 fixture로 보존한다. D4의 최종 옵션 벡터 최적화와 실제 부여 순서·성공률 최적화는 서로 다른 문제로 유지한다.
4. 무기 67·몸장비 63, 제작 스킬, 제작 캐릭터 기본 스탯을 이용한 `CraftPotentialCeiling`과 사용자가 입력한 실제 시작 잠재력, 90% 실사용 휴리스틱 프로필을 각각 분리해 기록한다.

통과 후 옵션부여 DP frontier를 무기·몸장비의 추가 `SourceProfile`로 넣는다. 크리스타 frontier와 단순 합치지 않고 크리스타 2슬롯, 옵션 8줄, 잠재력이라는 서로 다른 자원 제약을 유지한 채 전역 평가한다.

## 7. 필수 Scenario 행렬

최소 성능·정확성 fixture는 다음을 교차한다.

- 물리 근거리 기본
- 물리 원거리
- 발도 공격
- 일진강풍 변환 활성
- 마법 공격과 무기별 MATK 반영률
- 듀얼소드와 AMPR 2배 전 제약
- Utility 없음·일부 부족·대부분 부족·이미 충족
- 평타 크리티컬 100 직전·정확히 100·초과
- MAXMP→AMPR 경계
- ASPD 1,000 및 행동속도 50% 경계
- MAXHP 고정/퍼센트 혼합과 낮은·높은 VIT
- 잠금·금지·계보 분기·공용 크리스타 반복
- 음수 Utility를 포함한 고DPS 후보
- 유효 조합 없음

모든 조합을 동일 비중으로 성능 Gate에 넣지는 않는다. 안전성 oracle은 경계 중심으로 넓게, 실제 425개 P95는 대표 시나리오 세트로 운영한다.

## 8. 산출물

1. 최종 강화 크리스타 전수 목록과 데이터 해시
2. 부위·Scenario별 Supply Map
3. 옵션/Utility별 Supply Frontier와 공급 집중도 보고서
4. 후보·패키지별 유지/삭제/휴리스틱 분류와 근거
5. `PruningCertificate` 감사 파일
6. 축소 전후 후보·패키지·Pareto·탐색 노드 비교 보고서
7. 소형 oracle/property 회귀
8. 실제 425개 콜드 10회 P95 성능 보고서
9. 장비 옵션부여 카탈로그 정보 공백 목록과, 준비 후 통합할 R9 계약

## 9. 단계별 측정 지표

- 최종 강화체 수와 부위별 사용 가능 단일 후보 수
- 원시·조건 투영·동등성·지배 뒤 후보 수
- 부위별 2슬롯 패키지 수와 frontier 크기
- 규칙별 `Proven Drop` 수와 삭제 비율
- 분석·컴파일 시간과 최대 메모리
- 첫 유효해 시간과 하한
- 5초/10초 평가 횟수·탐색 노드·상한·gap
- 10초 콜드 10회 exact 비율과 P95
- 상한 property 위반 수
- 축소 전후 최적 점수·동점 ID 불일치 수

## 10. 착수 순서

첫 구현 묶음은 R0~R2의 분석 전용 도구다. 기존 Worker와 추천 결과를 바꾸지 않고 최종 강화체 목록, Scenario projection, 부위별 2슬롯 Supply Map을 생성한다. 마이룸 요리와 CRT 투자처럼 현재 입력된 비후보 공급량은 baseline에 반영하되, 선택 기회비용으로 최적화하지 않는다.

두 번째 묶음은 R3~R5의 증명 도구다. 후보 삭제를 아직 활성화하지 않은 상태에서 값싼 arc consistency, equivalence, residual feasibility, strict dominance, Replacement Proof 증명서를 생성하고 전수조사로 감사한다.

세 번째 묶음은 R6~R8의 cheap-to-expensive 후보 단위 상한·compiler 연결·성능 승인이다. 실제 425개 P95 개선과 exact 계약이 확인된 규칙만 기본 경로에 넣는다.

장비 옵션부여 R9는 검증 카탈로그가 준비될 때까지 차단한다. 수치 공백을 임의 상한으로 채우지 않는다.
