# 제작 잠재력 절삭 순서의 추가 조사

2026-10-21. 사용자 요청의 대량 옵부 실험에 쓰는 시작 잠재력과, 원형으로 재현하는 부여 단계 계산을 분리하기 위한 조사다. 보존된 PE의 지정 함수 14개만 Ghidra 12.1.4로 분석했다. 게임 실행·현재 프로세스 접근·제작 요청 전송은 하지 않았다. REA retained Evidence ID는 없다.

## 이번에 확인한 경계

- `SmithManufacture.SetRequiredMaterial` RVA0xa43e80은 원본 마스터의 `Potential`(+0x4c)을 읽어 제조 정보 텍스트에 넣는다. 이 함수에서 제작 스킬·기본 스탯을 사용한 완성 잠재력 산술은 찾지 못했다.
- 제조 선택·상세 UI와 `ShopUtil.GetManufactureItemText`/`GetManufactureItemPropertyText`도 확인했다. 결과 텍스트 함수는 전달된 ItemData 수치를 표시하며, 이 범위에 +30% 제작 잠재력 식은 없다.
- 실제 coroutine `<EquipmentProductionConnect>d__88.MoveNext` RVA0xa58700은 플레이어 제작 시 recipeId로 `EquipmentProduction` 객체를 만든다. 이를 `GameManager.OperationConnection`에 넘긴 뒤 `ReconnectionManager.Contains`/`TryGetErr`로 완료를 기다린다. 단순 coroutine 할당 메서드뿐 아니라 실행 본체를 조사했다.
- `EquipmentProduction.OnSuccess` RVA0xa30350은 전달받은 response를 `SmithManufacture+0x1e8`에 저장하고, 반환 아이템·재료 데이터를 적용한다. `<ConnectWaitManufacture>d__86.MoveNext` RVA0xa57760은 이 응답에서 아이템 목록을 골라 완료 화면에 표시한다.

제작 스킬 +30%의 절삭 순서와 제작 스탯 보너스 산술은 **이 14개 지정 함수에서 복구하지 못했다**. 이는 클라이언트 전체에 관련 코드가 없다거나, 공식의 소유자가 서버뿐이라는 전수 증명이 아니다. 요청/응답 경계까지만 확인했다.

## 실험 시작값을 다루는 방법

기초 잠재력은 기존 `native-crafting/base-profiles.json`의 원형/원본 근거를, 제작 스탯 배분은 `native-stat-budget/budget.325.json`의 사용자 승인 앱 예산을 쓴다. 단일 스탯 보너스51과 쌍 스탯 보너스41은 사용자 제작식 기준이다.

로컬 Smith 원문은 신중한 제작10%와 장인의 제작20%를 합산해 기본 잠재력에 먼저 적용한다고 설명한다. 이를 통합 정수 절삭으로 해석하면 무기 기초67에서 보너스 전87, 몸 기초63에서81이며 완성 시작값은 단일 무기138·쌍 무기128·몸132다. 이 해석은 **원문 기반 모델**이며 이번 조사로 native 확정이 된 값은 아니다.

민감도 비교로 각 스킬 보너스를 따로 절삭하는 가정을 넣으면 단일 무기137·쌍 무기127·몸132다. 이 두 가정이 실제 게임의 모든 가능한 구현을 덮는다고 주장하지 않는다. 이웃 시작값에서도 경로 선택 결론이 유지되는지 확인하는 용도로만 사용하고, 실제 아이템 최대값을 확인했다고 표시하지 않는다.

시작값 출처와 원형 단계 비용의 출처를 따로 기록하면, 미확정 초기값 때문에 원형 비용·TEC·카테고리 배율·절삭을 임의로 단순화할 필요가 없다. 실제 제작 개체의 잠재력 또는 제작 산술의 추가 근거가 들어오면 시작 프로필만 교체해 같은 경로 실험을 다시 실행할 수 있다.

## 재현·검증

`index.json`에는 14개 함수의 메타데이터 토큰·포인터 주소·파일 SHA256, 스냅샷 해시와 조사 경계를 보존했다. 세 분석 패스의 Java/메서드 맵도 보존했다. 기본 Ghidra 경계 보정은 기존 crafting 분석과 같고 전체 모듈 자동 분석은 실행하지 않았다.

```powershell
python assets/source-data/toram-statting/native-crafting-rounding/self-check.py
```

원형 함수 실행이 아니라 파일 무결성과 출처별 대안 산술의 소형 검사다.
