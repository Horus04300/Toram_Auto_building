# 장비 옵션 적용식 추출 원장

범위는 장비 옵션의 입력 단위 → 합산/배율 → 절삭/상한 → 게임 소비 위치다. 자동 전투, 피격·회복·보상 입력 화면, 서버 지급 시뮬레이션은 제공하지 않는다. 계산기에 연결된 속성·비례 ATK/MATK와 수식 검증용 원형을 구분한다.

## 확인된 식

f32는 각 연산의 float32 반올림, trunc는0방향 절삭이다. 아래는 장비 기여를 소비하는 단계이며 다른 스킬/버프·전체 전투 결과를 뜻하지 않는다. 함수 원문은 native-option-calculation/extended-consumption/, 토큰·VA·해시는 그 index.json에 있다. 200개 선택 함수의 디컴파일과 해시를 확인했다.

| 장비 옵션 | 확인한 적용식/규칙 | 소비 위치 |
| --- | --- | --- |
| DEF/DEFP·MDEF/MDEFP | 레벨·VIT/INT·장비 DEF·경량/중량/맨몸 분기로 기초값 계산 후 정수 비율/고정값 적용. 화살은 방어 비율에-25%p | PlayerSecondaryStatus 방어 getter |
| ACC/ACCP | trunc(f32((레벨+최종DEX)×옵션별 f32 비율 누적))+고정 명중 | 명중 getter |
| FLEE/FLEEP | 레벨·AGI·방어구 개조별 기초값에 옵션별 f32 비율과 고정 회피 적용 | 회피 getter |
| HP_REGEN/HP_REGENP | 기초 trunc(min(MaxHP,99999)/25)+10에 자연회복 %·고정값 적용 | 비전투 회복 getter |
| MP_REGEN/MP_REGENP | 기초 trunc(clamp(MaxMP,0,2000)/100)+1에 자연회복 %·고정값 적용 | 비전투 회복 getter |
| REVIVE_TIME | trunc(f32((1-별도 아바타 비율/100)×300)-장비 초) |13599 get_Respawn |
| ABS_ACC | 옵션별 합산 시 상한30, 유효 판정의 절대명중 단계에 적용 |16216/16217 |
| ANTICIPATE·GUARD_BREAK | 옵션별 합산 시 상한100, 대상 Avoid/Guard 무효 판정에 적용 | 전용 instant handler |
| ITEM_DELAY | 원시값/1000을 기본 대기시간의 감소율로 적용. 원시 상한500, 결과 최소5초. 기본값10초이면 표시값 D에 대해 max(5,10-D)초와 대응 |16294·5048 |
| EXP·PET_EXP·DROP_RATE·GEM_DUST_DROP | 클라이언트 합산 비율에 가산. PET은 EXP도 포함, DROP은 LUK/5도 포함. 서버 최종 지급/정수 반올림을 장비식으로 만들지 않음 | 보상 비율 getter |
| PHYS_RES·MAG_RES·7속성 내성·11형태 경감 | ±50 구간별0.5/1.5배와 잔여 배율을 순차 f32→정수 절삭. 물리/마법+형태 먼저, 속성은 두 번째 단계 |9991~9994·10018·10085·10101 |
| PHYS_BARR·MAG_BARR | 해당 고정 배리어만큼 흡수하며 피해 최소1 |16302/16317 |
| FRAC_BARR | 흡수량 trunc(f32(MaxHP×f32(비율/100))), 피해 최소1 |16332 |
| GUARD_POWER | 기초 Guard력×(100+옵션)/100, 절삭·최소100 |13594 |
| GUARD_RECHARGE·AVOID_RECHARGE | 기초 회복량×(100+옵션)/100, 절삭·최소1 |13595/13596 |
| REFLECT | trunc(f32(f32(비율/100)×단계 피해)) |16242 |
| AILMENT_RES | min(100,trunc(MTL×10/34)+장비값+별도 버프값) |13592·13630 |
| BARR_SPEED | 속도 상한100. 기본 재사용 시간-trunc(f32(f32(속도×20)/100)) |16231/16232 |
| ABS_DODGE | 유효 공격의 별도 확률 판정. 장비 확률 상한30 |16208/16209 |
| AGGRO | max(-100,옵션 합계), 상한 없음 |2026-10-27 사용자 제공 규칙 |
| PHYS_PURSUIT·MAG_PURSUIT | 장비 값+별도 스킬 기여를 합산 후100으로 나누어 추격 피해 계수 파라미터0x12에 전달. 장비 단독 기여=값/100 |14185:49~61/109·14096:47~99 |
| STOP_FLINCH·STOP_TUMBLE·STOP_STUN | 불리언. 하나라도 활성인 부여 정지가 있으면 true |16364·사용자 확정 |

이 표와 두 검증 원형이 다루는 키는57개다. supplemental-stats.js·option-event-calculator.js는 수식 확인용이며 제품 ESM 그래프에 포함하지 않는다. 대응 단위 검사와 앱 기능 연결의 완료 기준은 별개다.



## 범위 정정과 남은 확인

- HELP_INVINCIBILITY: HelpMaster.GetParam은 signed short, SumValue는 옵션을 추가할 때마다 상한10을 적용한다. 소비 시간 연결은 별도로 확인한다.
- SELF_DMG_RATE(반동)는 2026-10-27 사용자 지시에 따라 계산·추적 대상에서 제외한다. 저장 데이터는 보존한다.
- AVOID_RATE/FLOOR_RES/ITEM_CD는 구형 수동 키다. 앞의2개는 실제 ID9806/9851/9896의 cap47(Avoid회복),9910의 cap128(장판경감)과 대응한다. ITEM_CD의 단위 변환은 미확정이다. 별도 효과3개를 새로 만들지 않는다.

## 검증

- 원문200개 함수 해시 대조 PASS.
- test-supplemental-stats.mjs, test-option-event-calculator.mjs: 확인된 수식·절삭·음수·상한 단위 검사 PASS.
- npm test: 기존 아이템/크리스타 계산 연결 PASS.

미확정 항목을 추정식이나 단순 옵션 총합으로 채워서 추출 완료라고 표시하지 않는다.

도구 대기시간 일반 함수5048은 f32 연산으로 max(5,기초시간×(1-원시값/1000))을 사용한다. 표시 환산값은 원시값×0.01이므로 기초10초에서 -1표시는1초 감소와 대응한다. 다른 기초시간에도 고정1초 차감이라고 일반화하지 않는다. 별도 스킬의 추가 초 차감은 이후 단계이므로 장비값에 섞지 않는다.

Avoid회복은13596의 cap47(bAvoid) 소비를 기준으로 max(1,trunc(기초회복량×(100+장비옵션+별도버프)/100))이다. 구형 AVOID_RATE를 별도 회피 확률로 만들지 않는다.

이번 변경은 검증 원형·원장만 갱신했다. 앱 화면·실전 전투·추천 목적함수는 변경하지 않았다.
