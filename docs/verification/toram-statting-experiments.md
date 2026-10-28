# 옵션 부여 가상 입력·대량 경로 실험

2026-10-22 검산. 실행 시작일인2026-10-21 폴더에 원본 결과를 보존했다. [추천 설계안](../architecture/statting-recommendation-design.md)을 보강하기 위한 오프라인 실험이며 앱 추천 활성화·실제 게임 제작은 수행하지 않았다.

## 1. 이번에 확인한 범위

고정된 최종 옵션을 만들 때 **부여 순서가 얼마나 차이를 만드는지** 조사했다. 추천할 최종 수치 자체를 전역 최적화한 실험은 아니다. 부여자는 Lv325/TEC255/강화 스킬10·10·10, 제작자는 앱 예산840과 사용자 제작식을 사용한다. 무기9종·몸장비의 원본 제작 대상과 최대 기초 잠재력을 연결했다.

계산 근거는 [옵부 원형 조사](toram-statting-extraction.md), [입력 조건8함수](../../data/sources/toram-statting/native-input-rules/README.md), [경고 계산](../../data/sources/toram-statting/native-success/README.md)다. 단위 비용·±BaseMax 구간·DoubleUse·TEC 반환·행별 절삭·카테고리·float32 연산 순서를 번역했다. 카테고리는 두 번째 등장 순서를 보존한다. 임의의 실수 근삿값으로 패널티를 계산하지 않는다.

아래 경고율은 클라이언트 실행 전 경고다. 서버에서 완성되는 확률, 반전 성공 확률과 구분한다. 중간 단계는100%이고 잠재력1 이상·점유8줄 미만으로 계속할 수 있어야 한다. 마지막 단계는 음수 잠재력도 허용하지만 경고율0 경로는 실행 가능한 추천에서 제외한다.

## 2. 초기 제작 잠재력은 조건부 모델

앱 `pointBreakdown(325,325)=840`은 다섯 기본 스탯 값의 합이다. 기본1을 제외한 실제 투자량은835다. 단일 관련 스탯510 또는 관련 두 스탯510+327로 배분해 사용자 문서의 추가 잠재력51/41을 사용했다. 개인 TEC255를 제작자에게도 중복 배정하지 않았다. 네이티브255/510 상한과 한계돌파 조건, 원본 플레이어 레시피의 기초 잠재력 무기67/몸63은 검증했다.

제작 스킬 보정의 **최종 절삭 순서는 미확정**이다. 원형14함수 추가 조사는 요청·응답 경계를 확인했으며 실제 제작 후 계산 전체를 확보한 것은 아니다. 따라서 아래 두 모델로 민감도를 조사했다.

| 모델 | 단일 스탯 무기 | 두 스탯 무기 | 몸장비 |
| --- | ---: | ---: | ---: |
| `combined-floor`: 기초+floor(기초×.30)+스탯 보너스 | 138 | 128 | 132 |
| `separate-floor`: 기초+floor(기초×.10)+floor(기초×.20)+보너스 | 137 | 127 | 132 |

무기763쌍 중273쌍에서 최선 경고율이 달랐고 최대9%p 차이가 났다. 작은 잠재력 차이가 경로 선택을 바꿀 수 있으므로 실제 초기값 확인을 앱 추천 활성화 Gate로 둔다. 두 모델이 가능한 실제 구현 전부를 포함하지도 않는다. 추적에는 항상 `startingPotentialNativeVerified:false`가 있다. 레시피의 현 시점 획득 가능성·숙련도·슬롯으로 감소한 개체의 잠재력은 이 기준 프로필과 별도다.

## 3. 입력과 조사량

| 조사 | 최종 입력 수 | 입력 내 중복 제거 경로 | 실행 가능한 경로 발견 | 경고율100% 발견 |
| --- | ---: | ---: | ---: | ---: |
| 기본6틀·10장비 카테고리 | 1,670 | 1,199,301 | 1,117 | 544 |
| 몸장비용 감소 풀7틀 추가 | 83 | 12,195 | 22 | 3 |
| 합계 | **1,753** | **1,211,496** | **1,139** | **547** |

기본 틀은 ATK/크리티컬/STR%, MATK/크리티컬/INT%, ATK/불속성 유리/크리티컬, ATK/크리티컬4종, ATK/불속성 유리/STR%, MATK/불속성 유리/INT%다. 지팡이·마도구는 마법 틀, 다른 무기는 물리 틀, 몸장비는 기본6틀을 비교했다. 음수 풀은 처음에는 HP 자연회복-/MP 자연회복-/회피%- 또는 명중%-를 사용했다.

이후 몸장비에는 물리용 MATK%-/마법관통%-/HP 자연회복%-와 마법용 ATK%-/물리관통%-/HP 자연회복%-를 따로 조사했고 일부 틀에는 MP 자연회복%-도 추가했다. 감소 줄의 개수도 고정3으로 제한하지 않았다. 몸장비 실험은 높은 비용 경계 주변에 치우친 표본이므로 낮은 발견률을 ‘몸장비 옵부가 불가능하다’고 해석하지 않는다.

수치는 방향별 Lv325 상한, BaseMax, 그 주변의 유효 정수로 만들었다. seed20261021을 고정하고 같은 틀의 중복 최종 입력은 제거했다. 첫 실행은 틀당24표본, 몸 추가는12표본이다. 무기는 두 초기값 모델을 각각 세며 서로 다른 입력/장비에 같은 모양의 행동열이 있으면 별도 사례로 센다. 모든 게임 옵션 종류 조합을 조사한 수치가 아니다.

일반67종 중 특수 operand 타입7종을 제외한 **60종**은 별도 경계 조사에서11,666경로/65,390전이를 계산했다. 특수7종과 속성 부여65는 요청 operand 왕복이 미확정이어서 입력 거부한다. 이 제한은 게임에서 해당 기능이 불가능하다는 뜻이 아니다. 경계 조사는 위험/잠재력 소진 시 그 단계에서 중단하며 추천 가능한 완성 경로 수에 합산하지 않는다.

원본: [기본 summary](../../data/sources/toram-statting/experiments/2026-10-21/summary.json), [몸 summary](../../data/sources/toram-statting/experiments/2026-10-21/armor/summary.json), [검산 통계](../../data/sources/toram-statting/experiments/2026-10-21/review.json), [경계 조사](../../data/sources/toram-statting/experiments/2026-10-21/catalog-sweep.json). 각 `cases.jsonl`에는 조사한 최종 입력과 계열별 점수가 있다.

## 4. 경로 비교에서 얻은 결론

비교 계열은 음수 선부여, 양수 선소진→음수 반환, 단가1 옵션 분할, 소량 음수+양수 혼합이다. 음수 완성값의 순서 있는 모든 묶음은 비교하지만 양수 선소진 대표는 제한한다. 대표 축소는 근사이며 미발견614건은 불가능 증명이 아니다. 비교 점수0에는 경로 미발견/실행 불가도 포함된다.

기본1,670건 중695건이 단순 음수 일괄→양수 일괄보다 개선됐고,258건은 단순 경로도0보다 높은 상태에서 개선됐다. 결과를 찾은 나머지422건은 단순 경로와 경고율이 같았다. 음수 완성값의 부여 순서/묶음만 바꾼 점수 개선은 이 표본에서는0건, 선소진 없이 단가1을 나누는 개선은204건이었다. 음수 순서가 언제나 무관하다는 증명은 아니다.

몸 추가83건에서는22건이 기준보다 개선됐다. 선소진 계열이 음수 선부여 계열보다 높은 경우21건, 혼합 계열이 다른 모든 계열보다 높은 경우2건이다. 두 수치는 서로 겹칠 수 있다. 기본 summary의 역사적 필드 `drainAddsImprovement`는 실제로 combined와 음수 계열을 비교하므로, 순수 선소진 효과는 `review.json`에서 재계산했다.

### 같은 몸장비 최종 옵션: 경고율3% →100%

최종값은 ATK+8%, 크리티컬 대미지+9%/+18, 크리티컬률+18, MATK-16%, 마법관통-9%, HP 자연회복-10%다. 기준 초기 잠재력132, 최종7줄이다. 감소 옵션의 전투 손해까지 모든 빌드에서 허용할 수 있다는 뜻은 아니다.

| 경로 | 실제 행동 | 잠재력 변화 | 경고율 |
| --- | --- | --- | ---: |
| 단순1 | 감소3종 일괄 | 132→364 | 100% |
| 단순2 | 증가4종 일괄 | 364→-247 | **3%** |
| 개선1 | ATK+1%, CD+1, CR+1 | 132→104 | 100% |
| 개선2~8 | CD%를1씩7까지 올림: 각각 실제1행동 | 104→90→76→62→48→34→20→6 | 모두100% |
| 개선9 | 감소3종 일괄 | 6→374 | 100% |
| 개선10 | 나머지를 최종값까지 일괄 | 374→-59 | **100%** |

정확히 잠재력1을 만들지 않아도 좋은 경로가 나왔다. 선소진은 반환 전에 카테고리를 형성하며, 음수와 이후 양수의 패널티·구간 소비가 함께 바뀐다. 마지막 잠재력 음수 자체는 실패 조건이 아니다. [단계별 행 비용·float32·입력 JSON](../../data/sources/toram-statting/experiments/2026-10-21/armor/review-positive-baseline-gain.json)에 보존했다.

자동활 사례도 같은 최종값에서 단순1%→선소진100%를 확인했다. 이 사례는 미확정 `separate-floor` 초기137 조건이므로 실게임 레시피로 확정하지 않는다. [추적](../../data/sources/toram-statting/experiments/2026-10-21/review-positive-baseline-gain.json).

### 소형 완전탐색이 찾은 누락: 혼합 행동

한손 초기128에서 안정률+5%, 물리관통+4%, HP 자연회복-12를 목표로 했다. 기존 세 계열은 최고87%, 전체 단조 행동 기준은88%였다. 다음 흐름이 차이를 만들었다.

1. 물리관통+1%.
2. **안정률+1%와 HP 자연회복-2를 같은 행동으로 부여.**
3. HP 자연회복을-12까지.
4. 양수 두 옵션을 최종값까지.

각 행 절삭 후 양·음 비용을 합산하고 카테고리 배율·절삭을 적용하므로, 음수 전부를 별도 행동으로 처리하는 탐색이 이 차이를 놓쳤다. 혼합 계열 추가 후 [12개 소형 기준](../../data/sources/toram-statting/experiments/2026-10-21/oracle.json) 모두 최대 경고율이 일치했다. 총492,202전이를 비교했으며 몸 추가 실행에서 같은12건을 반복한 것을24개의 독립 기준으로 세지 않는다. [재생 가능한 반례](../../data/sources/toram-statting/experiments/2026-10-21/oracle-mixed-witness.json).

소형 기준은3타입 이하·중복 카테고리 최대1개·단조 수치만 다룬다. 같은 옵션 벡터에서 최대 잔여 잠재력을 보존하는 DP로 **최대 bounded 경고율**을 구한다. 최소 행동 수·소재·반전·수치 역행의 최적성은 검증하지 않는다. 큰 도메인 전체의 정확성 인증도 아니다.

## 5. 기존 전투 평가기와 연결한 probe

기존 `ToramApplication.CalculateBuild`와 `ToramBuildEvaluator.evaluateAggregate`를 사용해144개 후보 평가를 실행했다. 별도 대미지 식이나 크리스타 탐색기를 만들지 않았다. Lv325 STR510/DEX327, 한손ATK730·안정률80·제련0, 타겟DEF1000·내성/크저0의 평타 기준이다. 나머지 유틸리티 요구는 이 격리 실험에서 해제했다. 후보 평가가 고정 입력을 바꾸지 않는지도 검사했다.

| 고정 세팅의 CR 기여 | 같은 CR+1의 평타 기대 계수 변화 |
| ---: | ---: |
| 0 | 4001→4043: +42 |
| 50 | 6095→6137: +42 |
| 80 | 6220→6220: 0 |

따라서 CR 등은 항상 상한으로 채우기보다 현재 빌드의 포화·요구치를 계산해야 한다. 이 수치는 특정 한손 평타의 내부 평가 계수이며 모든 스킬/무기의 실제 대미지로 일반화하지 않는다. CR+1로 바꾼 후보의 새 부여 경로까지 재탐색한 실험도 아니다.

수치 추천의 선행 연결 누락도 확인했다. 원시 `FIRE_DMG`는 현재 registry에서 `notModeled`, 일반 `ELEM_P`는 `calculated`다. DTE 옵션은 원본에 보존되지만 대상 속성에 맞게 계산 입력으로 바꾸는 검증이 필요하다. 이 연결 전에 DTE를0점으로 평가해 탈락시키거나 전체 옵션 순위가 정확하다고 표시하면 안 된다. [probe 결과와 계산 파일 해시](../../data/sources/toram-statting/experiments/2026-10-21/score-probe.json).

## 6. 설계에 반영한 것

추천은 종류 프리셋→수치 후보→저렴한 경로부터 확장→원형 재생→기존 전투 평가→한 단계/경계 묶음/두 옵션 교환으로 진행한다. 무기와 몸장비의 감소 후보는 따로 계산하고 전투에서는 둘을 합산한다. 혼합 경로도 유지한다. 허용 경고율을 통과한 후보만 채택하고 최종 한 쌍을 확정한 뒤 다음 장비·크리스타 추천을 한 번 실행한다.

고정 최종값의 경로 캐시와 고정 빌드의 전투 평가 캐시를 분리한다. 미발견에는 조사 예산을 붙인다. 단순한 경로가 이미100%라면 통과 여부 조사에서 더 높은 확률을 찾지 않는다. 행동 수 최소화는 최종 후보에서 별도로 비교한다. 프리셋 밖 전역 최적·큰 도메인 exact를 주장하지 않는다. 구체 순서와 남은 결정은 [설계안10~12절](../architecture/statting-recommendation-design.md#10-실험을-반영한-추천-순서)을 따른다.

## 7. 재현과 검증

Python 표준 라이브러리와 기존 프로젝트 Node 환경만 사용한다. 이 PC의 `python` 명령은 Windows Store 별칭이라 실행되지 않아 실제 검증에는 아래 번들 인터프리터를 사용했다. PowerShell에서 한 번 지정하면 다음 명령을 그대로 실행할 수 있다.

```powershell
$stattingPython = "$env:USERPROFILE/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe"
& $stattingPython tools/statting/self_check.py
& $stattingPython tools/statting/simulate.py tools/statting/example-input.json --output build/tmp/statting-trace.json
& $stattingPython tools/statting/experiment.py --samples 24 --seed 20261021 --output data/sources/toram-statting/experiments/2026-10-21
& $stattingPython tools/statting/experiment.py --samples 12 --equipment 20 --frames armor-atk-crit armor-atk-crit-stat armor-matk-crit armor-atk-dte armor-matk-dte armor-atk-crit-four-neg armor-matk-crit-four-neg --output data/sources/toram-statting/experiments/2026-10-21/armor
& $stattingPython tools/statting/catalog_sweep.py --output data/sources/toram-statting/experiments/2026-10-21/catalog-sweep.json
node tools/statting/score_probe.mjs data/sources/toram-statting/experiments/2026-10-21
& $stattingPython tools/statting/review_results.py data/sources/toram-statting/experiments/2026-10-21
```

재실험은 다른 출력 폴더를 지정하면 보존 결과를 유지할 수 있다. 기본 조사434.96초, 몸 추가13.78초였다. 이는 전체 계열을 비교한 오프라인 실행 시간이며 앱 후보당 지연·메모리 상한은 측정하지 않았다. 기본/몸 실행 시점의 Python 원본은 각 `implementation/`에 해시 대조 후 보관했다. 보관본은 원래 `tools/statting/` 상대 위치로 복원해야 실행되며, 보관 폴더에서 단독 실행하는 패키지가 아니다.

이번 검증 결과:

- `tools/statting/self_check.py`: PASS. 보존 원형36함수 해시·행 비용3,000번 대조·방향별 상한·20/45/65%·경고 예시·거부 입력·소형 기준/재생.
- `native-crafting-rounding/self-check.py`: PASS.14함수와 보존 파일 해시, 조건부 초기값 산술.
- `native-input-rules/self-check.py`: PASS.8함수, 점유/재진입 조건·두 번째 카테고리 순서.
- `native-stat-budget/self-check.py`: PASS. 앱840·원형9함수·유효835투자·51/41.
- `native-crafting/extract-base-profiles.py --check`: PASS. 제작 대상·10종 최대값·재생성 동일.
- `tools/statting/review_results.py`: 입력1,753건/원본·실행 코드 해시/통계/저장 추적63개 재생 PASS.
- 실행 코드 자동 보관 smoke: 소형4입력·저장 코드 해시·0인 통계 키 생략 처리 PASS. 본 조사량에는 합산하지 않았다.
- 기존 전투 probe144회 PASS. DTE 미연결 Gate를 별도 표시.
- `npm test`, `node tools/verification/audit-ai-context.mjs`, `git -c core.safecrlf=false diff --check`: PASS.

제작 초기값 절삭·특수 operand·서버 판정/보호/반전·소재량·수치 추천의 전역 최적은 미검증이다. 앱 제품 코드·저장 계약은 바꾸지 않았다.
