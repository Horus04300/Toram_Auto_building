# 스킬 계산 전달 누락 — 1회 훑기

2026-10-14. 사용자 요청에 따라 한 번의 데이터/소비 경로 점검으로 정리했다. **추가 누락이 있으며, 결계나 위자드에 한정되지 않는다.** 제품 코드는 수정하지 않았다.

## 범위와 방법

- 실제 classic 로딩 후 기본/스택 선택 정책이 반환하는 29개 트리·427개 유효 스킬을 기준으로 확인했다. 중복 ID를 독립 스킬로 세지 않았다.
- 유효 정의의 `effects` 배열(전이·시전 트리거 안의 배열 포함) 641항목, 283타입, `stat` 194항목, 타격 flag 115키와 AST 참조를 목록화했다. 정적 전달 경로 검사이며 모든 효과의 게임 수식 정답을 검증한 것은 아니다.
- 빌드/패시브/활성 버프 → StatRegistry → 계산 커널, 공격 프로필 → 콤보 → Application 선택 타격, 영창/MP 소비 경로와 UI 임시 옵션 전달을 읽었다.
- 크리스타 425개와 그 스탯 키 87개도 등록 경로를 훑었다. 미등록 키는 0개다. 스킬 `stat`의 미등록 키도 0개다. 키가 등록됐다는 사실은 모든 정의가 그 키를 실제 전달한다는 뜻이 아니다.
- 원문 전체 재대조·새 기대값 산출·회귀/성능 재실행·실제 UI E2E·두 번째 확인은 하지 않았다. 아래는 **코드에서 확인한 연결 누락**이며, 정확한 수정식/게임 수치 확정은 별도다.
- 목록/트리별 수·효과 위치·참조·flag 원본 인덱스: [JSON](skill-calculation-wiring-audit.json). 실행은 `loadSavedBuildEnvironment()`로 유효 정의를 추출하고, 정의/소비 경로를 범위 검색해 비교한 일회성 Node 점검이다.

## 빌드 스탯·대미지에 직접 영향을 주는 누락

| 항목 | 빠지는 부분 | 코드 근거 |
| --- | --- | --- |
| 캐스트 마스터리 `Wizard:10` | 습득 수 추가 CSPD%, 고정 CSPD와 위자드 외 공격 관련 항 | 정의는 `states.wizardLearnedCount`를 참조하지만 `passiveStatChanges()`는 상태를 공급하지 않는다. 고정 CSPD 효과 자체도 없다. 기존 피드백 진단과 같다. |
| 오버 리미트·마술 가이드 `Wizard:12/13` | CSPD 페널티/완화와 속성 피해 | `overLimit`/`overLimitGuide`는 특수 메타데이터다. 활성 스탯/대미지 소비 분기에 없다. HP·침묵·종료 자동 전이와 구분한다. |
| 하이 사이클·퀵모션 `Support:7/8` | 본인 AMPR 페널티 | 이로운 CSPD/ASPD `stat`는 적용하지만 `attackMpRecoveryPenalty`는 소비하지 않는다. AMPR·추천 요구조건에 영향을 줄 수 있다. |
| 디지토실·하이 리액션 `Support:11/12` | 본인 ASPD/CSPD 페널티 | `attackSpeedPenalty`/`castSpeedPenalty`는 `activeStatChanges()`의 전달 대상이 아니다. 보호 효과의 피격 자동 처리와 별개다. |
| 파레스 `Knight:3` | VIT 비례 ASPD·관통 | 정의는 `combatStats.VIT`를 쓰지만 빌드 조립은 활성 효과에 최종 VIT가 아닌 `ctx`를 넘긴다. `ctx.vitBase/vitF/vitP`와 `VIT`는 다르며 이 참조는 0으로 계산된다. |
| 집기공·사자분신·질풍노도 `Barehand:1/2/4` | 기공 수/소모량에 비례한 ATK·CRIT·ASPD | 효과는 `attack.inputs.qiStacks/consumedQi` 등을 참조한다. 활성 버프 계산은 빈 입력을 받고 입력 기본값 정규화도 하지 않는다. 버프 저장/UI의 ON·스택과 해당 입력이 연결되지 않는다. |
| 무사 궁술 `Shot:21` | 서브 발도검 안정률/4, 서브 무기 공격력의 WATKP 변환 | `equipment.subWeaponStability`가 효과 컨텍스트에 없다. 별도 타입 `subKatanaWeaponAttackToWATKP`도 소비하지 않는다. |
| 엔천트 소드 `MagicBlade:7` | 서브 무기 안정률을 사용하는 상수 보정 | 같은 `equipment.subWeaponStability` 누락으로 해당 곱셈 항이 0이 된다. 서브 공격력/제련치는 전달되지만 안정률은 빠졌다. |
| 양손쥐기 `Mononofu:14`, 신념 `Ninja:1` | 크리티컬 최종 ATK 배율, 두루마리 장착 시 양손쥐기 허용 | 기본 CRIT/안정률/WATKP는 전달되지만 `criticalFinalAtkMultiplier`와 `convictionTwoHanded`는 소비하지 않는다. 양손쥐기의 서브 없음 조건도 그대로다. |
| 열정의 노래 `Minstrel:2` | 속성 피해 | `elementalDamagePercent`는 빌드/활성 대미지 전달 분기에 없다. 시전자·파티원·약점 조건 입력도 활성 버프 경로에 연결되지 않는다. |
| 스타빌리스 `Sprite:5` | 마법 안정률·최대 피해 상한·graze 보정 | CRIT `stat`만 연결됐다. `magicStability`의 별도 수치/상한은 소비하지 않는다. |
| 집기공•극·질풍노도•극 `Barehand:9/5` | AMPR와 물리 관통의 해당 조건 효과 | `qiExtreme.ampr`, `galeExtreme.physicalPiercePercent`는 스탯으로 전달되지 않는다. 기공 자동 획득/소모 구현과 구분하고, 수정 시 버프 조건을 먼저 확정해야 한다. |
| 마술 연구 `Wizard:5` | 임페리얼 레이 초기/후속 계수 및 사역마 영창 보정 | `imperialRayResearch`가 소비되지 않고 레이의 직접 계수식에도 연구 투자량이 없다. 반면 하이 패밀리어의 투자량은 라이트닝/블리자드/메테오 직접 식에서 사용하므로 통째로 누락이라고 분류하지 않는다. |

핵심 경로: `web/src/calculation/skill-effect-engine.js`의 `context`, `activeStatChanges`, `passiveStatChanges`, `activeCombatModifiers`; `web/src/calculation/calculator.js`의 `getBaseContext`; `web/src/application/application-use-cases.js`의 `CreateCalculationSnapshot`.

## 타격·콤보·영창 전달 누락

| 항목 | 빠지는 부분 | 코드 근거 |
| --- | --- | --- |
| 조건부 확정 크리티컬 | 조건을 만족한 `guaranteedCriticalWhen`이 최종 확정 크리티컬로 전달되지 않는다 | AST는 boolean으로 해석하지만 계산 커널은 `guaranteedCritical`만 읽는다. Blade:0, Crusher:9, Knight:6/11, Magic:0, Sprite:13, Hunter:15, DarkPower:3/10, MagicBlade:9가 이 키를 사용한다. |
| 조건부 절대 명중 | `guaranteedHitWhen`을 실제 명중 플래그로 변환하지 않는다 | Blade:7, Crusher:5, Knight:9, Shot:3/6. 명중 확률 시뮬레이션 보류와 조건 플래그 전달 누락은 별개다. |
| 다음 스킬 확정 크리티컬·명중 | 콤보가 새로 붙인 flag가 Application 선택 과정에서 가려진다 | 콤보는 `hit.flags`만 갱신하고 기존 `resolvedFlags`를 남긴다. `ApplyComboHit()`는 `resolvedFlags`를 우선한다. 게달/팬텀 슬래시 후속 확정 크리티컬 등은 콤보 프로필의 표시와 최종 입력이 달라질 수 있다. |
| 다음 근거리 위력 | 콤보에서 수치는 만들지만 실제 BuildDraft 계산 입력에는 빠진다 | `combo-ui.js`는 `.combo-transient-option` DOM 행에 SRW를 추가한다. `build-draft-store.js`는 그 행을 제외하며 `ApplyComboHit()`도 SRW를 Request로 옮기지 않는다. 임시 값을 영속 저장할 필요는 없지만 Request 연결은 필요하다. |
| N 드래곤 투스·데인져 셰이크의 후속 효과 | 다음 관통·행동속도 키를 콤보가 소비하지 않는다 | `Partisan:3`의 `physicalPiercePercent`, `Necromancer:11`의 `motionSpeedPercent`는 `mergeModifier()` 지원 키에 없다. |
| 시전 후 지속 스탯 | 아스튜트 CRIT·트리거 AMPR·패럴라이즈 샷 안정률 등의 전이 효과는 표시용으로 남는다 | 콤보는 `nextSkillModifier`만 수집한다. 전이 안의 `stat`를 유지/전달하지 않는다. 일부는 활성 버프 선택도 없다. 자동 시간/소멸은 보류할 수 있지만 현재 단발 프로필 표시를 계산 적용 완료로 볼 수 없다. |
| 본인 행동속도·현재 타격 속도 | 아스튜트/플래쉬 스탭 등 현재 스킬 속도 보정 | `skillModifier/motionSpeed`, `motionSpeed` 효과는 읽지 않는다. 콤보 행동속도는 후속 modifier와 태그만 합산한다. 한 타격/다음 스킬 효과를 전역 ASPD 요구조건에 그대로 더하는 수정은 부적절하다. |
| CSPD·영창 감소 | 일반 영창 프로필의 CSPD/CAST_RED 반영 | `affectedByCastSpeed`는 반환하지만 콤보는 소비하지 않는다. `castTimeSeconds`는 기본 시간과 다음 스킬 영창 감소만 쓴다. 피날레처럼 자체 식에 CSPD가 있는 경우는 별도다. |
| 급속 차지·차징→맥시마이저 | 차징 시간 감소·직전 차징 레벨에 따른 맥시마이저 영창 감소 | `chargingTimeReduction`은 소비되지 않는다. 맥시마이저의 직전 차징 연계는 메모에만 있다. 차징/맥시마이저 기본 MP 회복은 기존 `resourceRefund`로 연결돼 있다. |
| MP 회복 타입 차이 | `mpRestore/resourceRestore`로 적힌 일부 회복을 콤보 MP 흐름에 넣지 않는다 | `castMpRefund()`는 `phase:cast,type:resourceRefund,key:MP`만 합산한다. 응원의 춤·소울 스트림·베놈 스내치·소울 헌트 등의 다른 타입은 별도 소비가 없다. 적중/저항/대상·파티 조건을 요구하는 회복은 무조건 적용하면 안 된다. |
| 직접 타격 보정 flag | 스파이럴 에어의 타격별 관통, 관통 초과 계수, 특정 방어/공격 기초값·고정 HP 피해 | `perHitModifiers`, `excessPhysicalPierceToMultiplier`, `enhancedPhysicalPierceMultiplier`, `magicDefenseApplied`, `usesHalberdMagicAtk`, `usesPhysicalCriticalRate`, `usesMaxHpTenPercent/ignoresAtkDefenseCriticalProration` 등은 최종 커널 전달 목록에 없다. 해당 직접식에도 별도 변환 경로가 없어 일반 피해 계산이 남는다. 게임 수치의 재확정은 이번 범위 밖이다. |
| 타수·마법 안정률 보정 flag | 더블샷/추가 타수·특수 마법 안정률 | `shotsPerVolley`, `burstSwordDoubleHitWhen`, `magicStabilityFromPhysical` 등이 일반 타수/최종 안정률로 연결되지 않는다. 확률 추격의 자동 발동과 수동 선택한 타격의 보정은 구분한다. |

## 계산 누락으로 묶지 않은 범위

- 스킬 `stat` 194항목 중 65항목은 DEF/MDEF·명중/회피·물마내/어그로·자연회복·가드/avoid 재충전·EXP처럼 StatRegistry가 명시적으로 `notModeled` 보존하는 영역이다. 크리스타에도 같은 영역이 있다. 키나 데이터가 사라진 것은 아니지만 실제 방어/명중/회복 계산·결과 표시는 지원하지 않는다.
- 보호/피격/영역·지속시간/소멸·소환/자동 통상·확률 추격·파티 대상·스택 자동 증감은 기존 보류 범위다. Guard/Survival, Golem/Necromancer, Dancer/Minstrel 등에서 메타데이터만 남은 항목이 많다. 이를 모두 결계와 같은 단순 스탯 버그로 세지 않았다.
- 실드 마스터리의 방패 ASPD 페널티 완화는 정의에 있으나 소비하지 않는다. 현 커널은 방패 장착 자체의 해당 페널티 모델도 없으므로 **완화만 더하면 해결되는 누락**으로 분류하지 않았다.
- 전투 거리 `equipment.mainWeaponRange`도 컨텍스트에 없다(Martial:12/13). 이번 직접 피해 누락 목록보다 사거리 표시/조건 모델 부족에 가깝다.
- 동일 ID의 먼저 등록된 정의가 우선한다. 후순위 정의에 수식·버프가 있다는 것만으로 적용됐다고 볼 수 없다. 이번 목록은 항상 유효 정의를 기준으로 작성했다.
- 이미 수정한 결계 행동속도는 `stat/MOTIONSPEED` 경로로 전달된다. `MOTION_SPEED_P/MAGIC_PIERCE` 별칭도 등록돼 있다. 모든 행동속도/관통 누락을 키 오타 문제로 보지 않는다.

## 검사 범위의 한계와 다음 작업

이는 전수 **목록화 + 소비 경로 1회 점검**이다. 각 무기/레벨/조건을 실행한 S5 전수검증이나 원문에만 있고 정의 자체에 빠진 규칙의 완전성 검증은 아니다. 따라서 “누락 0개”나 모든 게임 규칙의 누락 총수를 주장하지 않는다.

문서 검사만 `npm run ai:audit`, `git diff --check`로 실행했고 종료 0/PASS였다. 계산 테스트를 실행한 것으로 해석하지 않는다.

발견한 직접 계산 누락은 위 표에 기록했다. 보류 자동 사건을 구현하거나 사용자 샘플·요구조건·최적화 식을 바꾸지 않았다. 수정할 때는 해당 원문과 입력 소유권을 기준으로 범위를 좁혀야 한다. 이번에는 사용자 요청대로 원인별 재현/더블 체크·계산 수정·전체 테스트를 수행하지 않았다.
