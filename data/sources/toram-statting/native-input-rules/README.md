# 가상 입력기의 안전한 입력 범위

2026-10-21. 저장된 게임 PE의 지정 함수만 Ghidra로 분석했다. 게임 실행·프로세스 접근·부여 실행은 하지 않았다. 함수 토큰·주소·원문 해시와 입력 스냅샷의 SHA256은 index.json에 있다. REA retained Evidence ID는 없다. 기존 native-schema/penalty/potential 증거는 수정하지 않았다.

## 부여를 시작할 수 있는 조건

`SetSelected(step=0)`는 현재 장비의 잠재력과 `getEmptySlotCount()`를 `SmithGrantInfoWindow.SetWeaponData`에 넘긴다. SetWeaponData는 잠재력이 양수일 때만 grantnum을 살리고, 그 값이 양수일 때만 진입 버튼을 켠다. 별도의 buttonEnabled 입력도 참이어야 한다.

따라서 일반 UI를 재현하는 실험은 각 행동을 시작할 때 **잠재력≥1, 사용 가능한 빈 줄≥1**을 요구한다. 처음부터 8줄이 채워진 장비로 재진입해 수치만 계속 바꾸는 입력은 허용하지 않는다. 한 행동에서 최종 8줄을 완성하는 것은 이 조건과 충돌하지 않는다. 마지막에 잠재력이0 이하이거나 8줄이 되면 후속 행동을 만들지 않는다.

`getEmptySlotCount`는 `max(0, usableSlots - occupiedCount)`를 반환한다. 세 강화 스킬이 모두 Lv10인 실험에서는 usableSlots=8이다. 원시 배열 용량10과 같은 값이 아니다. 점유 판정은 `<getEmptySlotCount>b__47_0`이며 `<InitSlotSelect>b__41_0`과 같은 원시 주소를 공유한다.

```text
occupied = (IsFixed || FixedBonusValue + BonusValue != 0) && bonusType != 0
```

IsFixed는 기존 장비에서 가져온 옵션의 표시 상태다. 기존 고정 Type이 있으면 값0이어도 점유할 수 있다. 반면 새 옵션에서 합계0이면 일반 UI의 점유 판정은 false다. 이것은 raw CalcUsePotentialPoint가 Type만 보고 카테고리를 세는 것과 다르다. 모든 삭제/교체/0값 정규화를 조사한 것은 아니므로 첫 실험에서 **새 typed-zero·삭제·부호 반전 없이 0에서 목표로 단조롭게 변경**하는 범위를 권한다.

## 수치 단위

일반 옵션은 getEnhanceMax의 방향별 정수 한도를 그대로 내부 값으로 사용할 수 있다. DTE의 일반 BonusType53~58과 보통의 감소 옵션25/34/35/36/37도 이 범위다. 장비별 비용 배수와 BaseMax 경계는 별도로 적용한다.

특수 Type12/22/24/26/28/30/32는 getEnhanceMax가 정규화된 선택기 한도를 돌려준다. SetFixedValue는 내부 기존 값을 `+0xd4/+0xd8`에 저장하고, SetDetailValue는 ±BaseMax 밖의 기존 값과 변경량을 OverRate로 나눠 선택기 값으로 바꾼다. UpdateDetailVal의 라벨은 선택기 합계가 기본 구간을 넘으면 다음처럼 확장한다.

```text
selector > B: raw = B + (selector-B)*OverRate
selector < -B: raw = -B + (selector+B)*OverRate
그 외: raw = selector
```

Type12와110의 표시 배율은 추가로10이다. Type110은 특수 선택기 목록에는 없으므로 raw→표시만10배다. 선택기 수치를 raw로 입력하거나, raw 상한을 선택기 한도로 잘라 버리면 안 된다.

실제 요청에 들어가는 operand의 왕복 경로 전체까지 이번 증거에서 확정하지 않았다. 따라서 첫 대량 실험은 특수7개 Type을 제외하고 진행하거나, 별도 검증을 통과한 변환기만 사용한다. 속성 Type65도 숫자 증가형과 다른 선택/기존속성 예외 경로가 있으므로 첫 일반 수치 조사에서는 제외한다. 데이터에 있는0 하한을 max(1,...) helper만 보고 음수1을 허용하는 것도 피한다.

## 카테고리와 누적 순서

CalcUsePotentialPoint는 최종 옵션 순서대로 카테고리를 처리한다. 카테고리가 두 번째 등장할 때 별도 Dictionary에 값2로 추가하고, 세 번째부터 그 값을 늘린다. 그러므로 배율에 더하는 범주는 **두 번째 등장 순서**로 열거된다. 가상 입력기는 이 순서를 보존하면 된다.

원래 비용의 행별 signed short 누적 뒤 범주 배율을 한 번 적용한다. 값0을 제외하는 UI 판정과 raw 함수의 Type 판정은 다른 단계이므로 raw 카테고리 helper에 임의로 Value!=0 조건을 추가하지 않는다. 안전한 실험 입력 자체에서 typed-zero를 생성하지 않도록 한다.

각 옵션을 딕셔너리 키순으로 재정렬해 슬롯을 바꾸지 않는다. 기존 옵션은 기존 슬롯에 남고 새 옵션은 빈 자리에 들어가는 EnhanceGetPropertyPosition의 구조가 있다. 슬롯 순서는 추후 첫 슬롯 보호/반전 판정에서도 필요하다.

## 이번 범위의 한계

위 판정은 클라이언트의 정상 진입 경로와 보존 코드에 대한 정적 근거다. 서버의 모든 조합 허용 여부, 실패 결과, 기존 속성 교체, 0값 삭제 전수, 특수 Type의 요청 operand 왕복은 별도다. 실험에서 제외한 부분을 불가능한 게임 기능이라고 설명하지 않는다.
