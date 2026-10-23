# 옵션부여 잠재력 비용 근거

2026-10-20. 보존된 GameAssembly 스냅샷을 선택 함수만 Ghidra로 분석했다. 현재 게임 실행·프로세스 접근은 하지 않았다. `index.json`은 함수 주소/토큰/파일 해시, `report.json`은 연산식과 해석 범위를 보존한다. REA retained Evidence ID는 없다. 앱·자동 추천기·기존 frozen 계약은 수정하지 않았다.

## 계산이 받는 데이터

`EnhanceGetPropertyPosition`은 기존 장비와 목표 옵션을 비교해 **변경량 배열**과 **최종 옵션 배열**을 만든다. `CalcUsePotentialPoint`는 변경량으로 비용을 계산하고, 최종 옵션 배열로 카테고리 배율을 구한다. 따라서 기존 값과 단계 구분이 필요하다.

마스터 `EnhanceProperties2`의 필드 중 실제 비용에 쓰이는 값은 `UsePotential`(단위 잠재력 C), `BaseMax`(기본 구간 경계 t), `OverRate`(경계 밖 정수 나눗셈 s), `DoubleUse`다. Rate/표시 단위와 OverRate를 같은 값으로 취급하면 안 된다. 전체 필드 순서는 metadata-support.json과 report.json에 보존했다. 실제 옵션별 행은 별도 카탈로그 근거와 연결한다.

## 양수 변경과 음수 변경

기존 값 x, 변경량 d, 최종 값 y=x+d라 두면 ±BaseMax를 통과하는 구간을 나눠 계산한다. 정수 나눗셈은 0 방향 절삭이다. 상세 식은 report.json의 up/down에 있다.

- 양수 변경은 기본 구간에서 `C × 변경량`이다. 양의 경계 밖에서는 `2 × C × trunc(구간량/OverRate)`가 들어간다. 이미 음의 경계 밖에 있던 값을 복구하는 구간은 별도 `trunc(구간량/OverRate)`다.
- 음수 변경에는 `float32(TEC/1000 + 0.05)`를 곱한다. TEC는 PlayerStatusBase의 SecondaryStatus → IPlayerStatusCalculator slot9 get_Tec에서 읽는다. TEC255는 약30.5%다.
- 음의 경계 밖으로 더 내려가는 구간은 반환식 안에서 `0.5 × trunc(구간량/OverRate)`를 쓴다. 모든 감소에 균일한 반환액을 대입하면 안 된다.
- 무기 판정이 참이고 DoubleUse=2, 또는 무기 판정이 거짓이고 DoubleUse=1이면 C를 먼저 두 배로 만든다. 무기 판정 함수는 ItemType7~19 중17 제외 및23을 참으로 반환한다.

부동소수점 연산은 매번 float32다. 음수 변경은 **옵션 줄마다 정수 절삭**한 뒤 signed short로 누적한다. 마지막에 전체 합에 카테고리 배율을 한 번 곱하고 int→short로 변환한다. 양/음 비용을 각각 카테고리 보정해 반올림하는 식과 다르다.

예를 들어 `C=3, BaseMax=20, OverRate=1, TEC=255`일 때, `0→-10`은 -9pt지만 `0→-5→-10`은 -4-4=-8pt다(카테고리 배율 전). 같은 최종 옵션이어도 단계별 절삭 때문에 잠재력 반환이 달라진다. 이 연구는 실제 단계 비용을 설명하며, 기존 문서의 최종 옵션 집합 최적화가 이를 자동 재현한다고 주장하지 않는다.

## 속성과 상세 화면

BonusType65(bElement)는 별도 ElementCost 조회 후 일반 ±BaseMax/TEC 분기를 건너뛴다. 원본 아이템 마스터에 동일 속성이 있으면 장비별 두 배 처리 뒤 C를 정수10분의1로 줄인다. 기존 속성을 임의 변경하는 조작이 UI/서버에서 허용되는지는 이 분기만으로 증명하지 못한다.

`CheckOverRateType`은 BonusType12(bMaxHpTo10),22(bHit),24(bFlee),26(bDef),28(bMdef),30(bAspd),32(bCspd)에 참이다. `SetConsumptionPotential`은 표시용 값들을 저장하고 UpdateDetailVal을 부를 뿐 실제 잠재력 예산 공식을 구현하지 않는다. 상한·상세 값 표시·카테고리 계산은 별도 native-penalty 근거가 담당한다. 초벌 getEnhanceMax에서 Math.Max tail-call 경계 문제가 확인되어 이 폴더에는 해당 초벌을 보존하지 않았다.

검증은 `python self-check.py`로 float32·경계 통과·단계 분리·short 계약과 파일 해시를 확인한다. 이는 원형을 번역한 정적 검증이며 현재 게임에서 실행한 검증이 아니다. 실제 마스터 상한, 옵션 허용 여부, 서버 실패 결과·보존 규칙은 별도 증거가 필요하다.
