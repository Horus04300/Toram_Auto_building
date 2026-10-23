# 옵션 부여 카탈로그·필드 구조 근거

2026-10-20. 이전에 보존한 GameAssembly PE 스냅샷과 동일 메타데이터를 정적으로 분석했다. 이번 조사에서 게임 실행·프로세스 접근·쓰기·설정 변경을 하지 않았다. scoped Ghidra 직접 결과로 REA Evidence ID는 없다. 입력 SHA-256·메타데이터 토큰·주소·함수별 해시는 `index.json`, 구조와 상수는 `metadata.json`, `report.json`에 있다.

## 실제 카탈로그 원본

옵션 비용 표는 이 코드에서 TextAsset의 BinaryReader를 통해 읽지 않는다. `GrantData`의 컴파일된 static constructor RVA **0xa30d10**이 두 사전을 직접 구성한다.

- `EnhanceCost`: 일반 옵션, 키 `Toram.Common.Bonus.BonusType`, **67개**.
- `EnhanceElementCost`: 속성 옵션, 키 `ElementType`, **6개**(Fire1/Water2/Wind3/Earth4/Light5/Dark6).

함수의 `EnhanceProperties2` 생성 호출 73개와 이어지는 `FUN_7fff6087ca00` 사전 추가 호출 73개를 원형 보존했다. 일반 사전을 static field +0, 속성 사전을 +8에 저장한다. `SmithGrant.SetEquipEnhance`라는 이름은 이 마스터의 파일 로더가 아니라 현재 장비 옵션을 UI 선택 상태에 연결하는 코드다. `SmithGrant` 자체 static constructor의 정수 8은 MaxSlotNum이며 비용 표가 아니다.

따라서 별도의 EquipEnhance 바이너리 레이아웃을 추정해 만들지 않는다. 조사한 BynaryData에는 EnchantmentData가 있지만 그것을 이 비용 표라고 이름만으로 연결하지 않는다. 실제 일반 옵션 식별은 BonusType ID로, 표시명은 별도 언어 자료로 연결해야 한다.

## 값 구조와 정확한 바이트 순서

`Toram.Common.Productions.EnhanceProperties2` 생성자 RVA **0x25604a0**(VA 0x7fff617b04a0)은 인자를 아래 위치에 직접 저장한다. struct 크기는 40바이트다.

| offset | 필드 | 네이티브 값 |
| ---: | --- | --- |
| 0 | UsePotential | int32 |
| 4 | Coefficient | int32 |
| 8 | MaterialCategory | int32 |
| 12 | AbilityCategory | int32 |
| 16 | Rate | float32 |
| 20 | BaseMax | int32 |
| 24 | UpperMax | int32 |
| 28 | LowerMax | int32 |
| 32 | OverRate | int32 |
| 36 | DoubleUse | int32 |

이는 메타데이터 필드·생성자 인자 이름과 기계 코드의 저장 위치를 함께 확인한 결과다. readonly/composite Il2CppType 레코드 때문에 일부 필드 타입의 exact_byval_name이 null인 것을 임의 타입명으로 채우지 않았으며, 저장 명령과 생성자 인자는 int32/float32를 확정한다.

MaterialCategory는 `Toram.Common.Items.MaterialType`의 Metal0·Cloth1·Beast2·Wood3·Drug4·Magic5와 대응한다. Magic이 없는 다른 전역 MaterialType 선언도 있으므로, 단순히 타입명이 같다는 이유로 그 선언을 선택하지 않는다. AbilityCategory의 이름 있는 enum은 확인하지 못했다. 원시 ID와 해당 그룹의 BonusType 목록을 보존하고 명칭을 추정하지 않는다.

예를 들어 첫 일반 옵션 ID1의 tuple은 `(5,50,2,1,1f,20,50,50,1,0)`, ID6은 `(10,100,2,1,0f,10,10,10,1,0)`이다. 속성 사전 6개는 각각 `(100,300,5,11,0f,1,1,0,1,0)`을 가진다. 이름이 같거나 같은 단위로 보인다는 이유로 서로 다른 필드를 합치지 않는다.

## 상한과 두 배 기준의 소비 경로

`GrantData.LimitLevel=210`은 메타데이터 constant이며 `SmithGrantInfoWindow.getEnhanceMax`가 비교하는 분기 기준이다. 게임 전체 최고 레벨을 뜻하는 상수가 아니다. 이 함수는 캐릭터 레벨·스킬 365/366/367·BaseMax·Rate·UpperMax/LowerMax·OverRate로 실제 상한을 계산한다. Rate=0인 항목과 양/음수 방향도 보존해야 하며 UpperMax를 그대로 현재 레벨의 상한으로 쓰면 안 된다. 구체 계산은 별도 `native-penalty/`의 상한 근거와 함께 사용한다.

`CheckOverRateType`은 BonusType 12 또는 22/24/26/28/30/32에 true를 반환한다. OverRate는 단순 표시 배율이라는 추정으로 삭제할 수 없다. 같은 함수에서 BaseMax 초과 구간을 나누는 데도 쓴다.

`GrantData.GetUsePotential(BonusType, itemUuid, playerData)` RVA0xa30ba0은 일반 사전의 UsePotential을 반환하되, `ShopUtil.IsArmorItem`이 참이고 DoubleUse=1이거나 `ShopUtil.IsWeaponItem`이 참이고 DoubleUse=2이면 2배로 반환한다. DoubleUse=0은 이 분기에서 2배를 적용하지 않는다. 이것은 해당 장비에 옵션을 절대 부여할 수 없다는 호환성 플래그가 아니다. 속성별 비용 조회는 별도의 ElementType overload RVA0xa304e0이며 장비의 기존 속성도 확인한다. 최종 잠재력·음수 회복·동일 카테고리 페널티는 소비 함수 전체를 따라야 하므로 UsePotential의 단순 합으로 대체하지 않는다.

## float32 상수와 재현

초기화 함수에서 참조한 상수 6개의 바이트를 report.json에 보존했다. 0.18/0.35/0.4/0.69는 float32 값 그대로 해석해야 한다. 특히 `fVar2`는 함수 앞부분에서 0.18, 뒷부분에서 0.4로 다시 대입되므로 변수명에 전역 값 하나를 붙여 모든 행에 재사용하면 잘못 추출된다. 함수 순서대로 현재 대입을 해석하거나 실제 각 호출의 기계 코드 인자를 확인한다.

스크립트는 입력 PE SHA-256과 image base를 검사하며 선택 함수만 분석한다. `getEnhanceMax`의 tail call을 잘못 합치는 decompiler PIC 처리를 막으려고 Math.Max/Min 함수 경계를 미리 지정했다. 복원된 파일에는 기존의 제거된 분기 경고가 없다. 상세 재현 형식은 index.json.reproduction이다. Assembly-CSharp.dll의 75,881개 및 Toram.Common.dll의 22,830개 메서드 포인터 수와 연속 RID를 검증한 모듈 매핑을 보존했다.

함수 14개의 SHA-256·73 생성/추가 대응·40바이트 구조 검사를 통과했다. 카탈로그 파서·앱·자동 추천·기존 파이프라인 계약은 이 조사에서 수정하지 않았다. 정적 클라이언트 근거이며 실제 서버의 부여 실행이나 성공 결과를 관측한 것은 아니다.
