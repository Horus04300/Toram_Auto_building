# 장비 옵션 적용식 검증 원형

이 모듈은 수식 검증용 원형이며 앱에서 로드하지 않는다. 추출 현황은 equipment-option-formulas.md를 따른다.

`web/src/calculation/option-event-calculator.js`의 `ToramOptionEvents.evaluate(calculation, inputs)`는 입력된 1회 사건의 수식을 계산한다. 자동 피격·시간 경과·반복 전투 상태를 실행하지 않는다. 선행 장면 조건이 필요한 값은 입력 전 `null`이다. 서로 다른 단계의 결과를 최종 전투 피해로 합쳐 표시하지 않는다.

## 입력과 결과 계약

- 장비·크리스타·수동 옵션은 기존 `calculation.ctx.preservedStats`에서 읽는다. 최대 HP는 `calculation.finalMaxHP`다.
- `supportedKeys`는 실제 소비 키, `inputDefinitions`는 UI 메타데이터다. 결과는 `values`, `outcomes`, `rows`, `requirements`다.
- `incomingDamage`는 내성·배리어·반사의 각 단계에 넣는 정수 피해다. 개별 단계 행은 동일한 입력을 독립 적용한다.
- 결합 내성 행은 `incomingType`, `incomingActionType`, `incomingElement`를 받아 물리/마법 내성+형태 경감 합계 → 속성 내성 순서를 계산한다. Guard·후속 버프·배리어를 이 행에 자동 합산하지 않는다.
- Guard력·Guard/Avoid 회복량·배리어 기본 재사용 시간·MTL은 그 수식의 선행 입력이다. 절대회피는 유효 공격 조건과 명시적 난수를 받는다.

## 네이티브 근거

입력 신원은 `data/sources/toram-items/native-option-calculation/index.json`, 메서드 토큰·주소·본문 해시는 `extended-consumption/index.json`이다. 아래 번호는 현재 메타데이터 인덱스다.

- 9991~9994: 내성은 ±50 단위로 나누어 양수는 0.5배, 음수는 1.5배 하고 매 단계 float32→int 절삭한다. 나머지 내성도 float32 연산 뒤 절삭한다. 내성 0은 원래 정수를 그대로 반환한다.
- 10018, 10085, 10101: 원본 행동 유형별 cap121~131을 선택한다. 물리/마법 내성과 형태 경감은 먼저 더하고, 속성 내성은 별도 두 번째 내성 계산이다. enum에 없는 행동 유형은 추가 형태 경감 0이다.
- 16302/16317/16332 및 28387/28398/28409: 준비된 배리어는 최소 피해 1을 남긴다. 비율 배리어는 `trunc(f32(MaxHP * f32(비율/100)))`만큼 흡수한다.
- 13594~13596, 2722: Guard력은 기초값×(100+옵션)/100 뒤 정수 절삭·최소100이다. Guard/Avoid 회복량은 같은 비율식 뒤 최소1이다. 일반 Guard 피해 계산은 Guard력을 최대10000으로 제한한 배율만큼 정수 피해를 뺀다. 특수 Guard 행동·현재 게이지 자동 전이는 포함하지 않는다.
- 16242: 반사는 `trunc(f32(f32(반사비율/100) * 피해))`다.
- 13630, 13592: 상태 이상 내성은 `trunc(MTL*10/34)+장비 옵션`과 별도 버프 기여의 합이며 getter 상한100이다. 현재 행은 MTL·장비 기여만 계산한다. 특수 상태 이상·Guard·보스 보정이 포함된 전체 부여 확률로 표시하지 않는다.
- 16231/16232: 배리어 속도 상한100, 재사용 시간은 `입력-trunc(f32(f32(속도*20)/100))`다. 입력 시간에 비율을 곱하는 식이 아니다.
- AbsoluteFreeRate 16208/16209: 유효한 명중 공격에서만 확률 판정한다. 장비 확률 상한은30이다. 공격 분류·실행 중 스킬 등 장면 자격은 명시적 입력으로 받는다.

상수는 같은 mapped 이미지의 VA에서 확인했다: `0x7ffe9c049b88`=`0000a041`=20f, `0x7ffe9c049cf4`=`00004842`=50f, `0x7ffe9c049b4c`=`0000003f`=0.5f, `0x7ffe9c049ec0`=`00401c46`=10000f. 이미지 경로·SHA-256은 상위 index와 같다.

## 검증

`node tools/tests/application/test-option-event-calculator.mjs`: 내성 양수·음수·50 경계, float32에 들어가기 전 무변경 정수, 11개 형태 매핑, 합산 내성 순서, 속성, 배리어, Guard 회복·하한, 반사, MTL 상한, 배리어 속도, 절대회피30% 경계를 검증한다.
