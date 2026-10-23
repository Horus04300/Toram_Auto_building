# 아이템 보조 테이블 추출

2026-10-17, 캐시 `77596232`와 기존 마스터 11,723개를 기준으로 추가 추출했다. 앱 계산 데이터는 변경하지 않았다. 결과는 [item-relations.json](item-relations.json), 재현 도구는 [extract-toram-item-relations.py](../../../tools/extraction/extract-toram-item-relations.py)다.

## 완료 범위

| 원문 테이블 | 추출 결과 | ID 연결 결과 |
| --- | --- | --- |
| ItemRandomPropertyMaster | 328행, 행마다 옵션 10칸, 0이 아닌 옵션 513개 | 한국어 랜덤 문구 328/328, 옵션 enum 513/513 연결 |
| RecipeMaster | 2,079행, 재료 목록 전체 | 아이템 결과물 1,699개·외형 변경 330개·수집 가방 확장 50개를 서로 다른 ID 체계로 연결 |
| ItemCreateSupport | 2그룹, 아이템 참조 40개 | 40/40 마스터 연결 |
| NGItem | 29개 ID | 29/29 마스터 연결 |
| EquipModelProperty | 5그룹, 모델 속성 2,498개 | 타입·모델 번호 일치 후보 보존, 4그룹 반환 enum 확인 |
| ItemDorpData | 전 바이트, 13바이트 구획 3,143개 보존 | 선두 정수 후보 3,143/3,143이 마스터에 존재하나 의미 미확정 |

위 첫 5개 테이블은 실제 네이티브 로더가 읽는 타입과 순서를 확인했고, 전 파일 EOF와 구조화 값의 바이트 단위 재조립을 통과했다. ItemDorpData는 구획 재조립만 검증했다. 파일 크기 일치를 스키마의 의미 검증으로 취급하지 않는다.

## 데이터 구조

`tables.<원문 이름>`에 원본별 레코드가 있다. 각 원문 레코드에 `decodedOffset`과 `rawRecordHex`가 있으며, 출처 경로·길이·SHA-256은 `source`에 있다. 참조가 해석된 경우 원문 필드를 유지하고 별도 `reference` 또는 `createdItem`을 추가했다. 이름을 복사하지 않고 `gameItemId`로 기존 카탈로그를 참조한다.

### 랜덤 옵션

헤더는 i32 두 개다. 첫 정수는 로더가 읽고 사용하지 않으며 현재 값은 0, 다음 정수는 행 수 328이다. 각 행은 68바이트다.

| 파일 내 행 상대 오프셋 | 형식 | 메타데이터 속성 |
| --- | --- | --- |
| 0 | i16 | Id |
| 2, 3, 4, 5 | u8 각각 | ConditionType1, ConditionVal1, ConditionType2, ConditionVal2 |
| 6, 8 | i16 각각 | ActCount, MaxActCount |
| 10 | u8 | ActStatus |
| 11 | i16 | ReflectionRate |
| 13, 14 | u8 각각 | EffectTime, CoolDownTime |
| 15 | i16 | MaxStack |
| 17 | i32 | Flag |
| 21~60 | `(i16 ID, i16 수치)` 10쌍 | CapIds, CapVals |
| 61, 62 | u8 각각 | Tier, EffectStatus |
| 63 | i16 | EffectReflectionRate |
| 65 | u8 | StackStatus |
| 66 | i16 | StackReflectionRate |

네이티브 생성자의 읽기 순서와 각 getter의 실제 메모리 오프셋을 함께 대조했다. `localizedTextByKind.kr["0"/"1"]`는 `ItemRandomProperty_kr`의 같은 ID 문구다. 옵션 수치는 `caps[].rawValue`로 보존하며 조건·반영률·시간 단위를 이름만 보고 환산하지 않았다.

이 표의 ID와 아이템 ID가 숫자로 같다는 이유로 연결하지 않는다. 특정 아이템의 고정 참조 또는 소유 아이템 인스턴스의 랜덤 옵션 참조는 별도의 코드 경로가 필요하다. 해당 연결을 이 추출기가 임의로 생성하지 않는다.

### 제작 레시피

i32 행 수 뒤 각 행은 `RecipeId:i32, Type:u8, ReleaseLv:i16, Price:i32, Difficulty:i16, CreateId:i32, CreateVal:i16, Category:u8, 재료 수:i32`이며, 재료마다 `RecipeNo:u8, Lv:u8, Id:i32, Val:i16`을 읽는다. 네이티브 `RecipeDBDataManager.LoadData`와 생성자 매개변수/필드를 대조했다.

메타데이터 `recipeType` 상수는 다음과 같다.

| Type | 이름 | 행 수 | 결과 참조 |
| --- | --- | --- | --- |
| 0 | Smith | 1,507 | CreateId → ItemMaster |
| 1 | Synthetic | 192 | CreateId → ItemMaster |
| 2 | Recreate | 330 | 외형 카테고리 + 해당 외형 옵션 ID |
| 3 | CollectSlot | 50 | CreateVal → 수집 가방 확장 진행 단계 |

Type 2는 캐릭터 외형 변경이다. `Category`는 `Toram.Common.Operations.Main.Shop.RecreateType` enum이며, `CreateId`는 그 카테고리의 외형 옵션 ID다. `UIRecreatePanel.getRecipeData`가 카테고리별 목록을 고르고, 실제 predicate가 레시피의 CreateId와 선택 ID를 비교한다. 전체 330개 `(Category, CreateId)` 키에 중복이 없다.

| 카테고리 | enum 이름 | 레시피 수 |
| --- | --- | --- |
| 201 | HairColor | 52 |
| 202 | FrontHair | 72 |
| 203 | BackHair | 68 |
| 204 | TailHair | 41 |
| 205 | EyeColor | 16 |
| 206 | Face | 15 |
| 207 | SkinColor | 15 |
| 208 | Sex | 4 |
| 209 | EyePattern | 5 |
| 211 | Height | 5 |
| 212 | Body | 2 |
| 213 | OddEyeColor | 17 |
| 214 | MeshColor | 18 |

카테고리 이름은 `RecreateRecipeType` + enum 이름을 System 텍스트 키로 조회한다. 이 접두사는 저장된 모듈의 encoded metadata usage `0xa0004dfb`에서 literal 9981로 직접 복원했다. mscorlib CodeGenModule의 메서드 포인터를 대조해 호출 함수도 `System.Enum.ToString`과 `System.String.Concat`임을 확인했다. 13개 카테고리와 330개 레시피 모두 한국어 카테고리 문구가 연결된다. 동일 키 원문이 여러 개면 `categoryText.rows`에 모두 보존하고, 텍스트가 모두 같을 때만 `textConsensus`를 제공한다. 이 값은 화면 관찰 결과가 아니다.

`operationTarget.namespace`는 `character-appearance-option`, 실제 번호는 `targetIndexRaw`다. `getModelIndexString`은 실행 중 모델 목록의 순서에 따라 표시 번호를 바꾸므로, 이 원본 번호에 무조건 1을 더해 화면 번호라고 하지 않는다. 외형별 모델/색상 이름이나 최종 화면 표시 순서는 이 결과의 완료 범위가 아니다.

Type 3은 수집 가방 확장 진행표다. `UIItemBagManager.RecipeLoadData.MoveNext`가 Type 3, Category 0을 읽고, `OpenCollectBuySlotPanel`은 현재 `GameUserDataManager.CollectItemSlot + 1`과 CreateVal이 같은 레시피를 찾는다. 실제 predicate에서도 CreateVal 필드 오프셋 0x24를 확인했다. 50행의 CreateId는 모두 0, CreateVal은 정확히 1~50이다. `operationTarget.namespace`는 `collect-bag-expansion-step`, 진행 번호는 `targetExpansionStep`으로 제공한다. **1~50은 가방의 최종 총 수용량이 아니다.**

Type 2/3은 `createdItem`이나 가짜 gameItemId를 만들지 않는다. 380개의 비아이템 대상 ID 체계는 전부 확인했으며, 관련 원문 수치와 재료는 그대로 유지했다. 이 작업은 제작 성공률·외형 변경 비용 계산·슬롯 확장 공식을 구현한 것이 아니다.

재료 `Lv=0`은 아이템 참조, 비zero는 재료 포인트 참조로 분리했다. 실제 재료 확인 코드에서 전자는 ItemManager의 개수 조회, 후자는 MaterialManager.GetMaterialPoint로 갈라진다. 따라서 2,178개 재료 포인트 참조를 아이템 번호로 합치지 않는다. 포인트 종류·레벨은 원문 `Id`와 `Lv`를 유지한다.

### 생성 지원·NG

ItemCreateSupport는 `그룹 수:i32`, 그룹마다 `그룹 키:i32, 항목 수:i32, itemId:i32[]`다. 현재 그룹 키 2에 1개, 키 1에 39개가 있다. 키의 적용 대상·성공률 의미는 확정하지 않았다.

NGItem은 `항목 수:i32, itemId:i32[]`이며 `ItemTextManager.SetNGItem`의 목록 입력임을 확인했다. 목록 존재만으로 소지·거래·장비 금지라고 해석하지 않는다.

### 모델 속성

`그룹 수:u8`, 그룹마다 `키:u8, 항목 수:i16`, 이후 `modelId:i32, flag:i16`을 읽는다. 그룹별 행 수는 20:151, 10:15, 21:590, 27:1,738, 25:4다.

네이티브 getter가 다음 그룹과 enum의 관계를 확인해 준다.

| 그룹 키 | getter | 반환 enum |
| --- | --- | --- |
| 20 | GetBodyModelFlag | BodyModelFlag |
| 21 | GetOptionModelFlag | OptionModelFlag |
| 25 | GetAvatarTopModelFlag | AvatarModelFlag |
| 27 | GetAvatarOptionModelFlag | OptionModelFlag |

enum 상수 원문은 결과의 `metadataEnums`에 보존했다. `sameTypeAndModelItemCandidates`는 기존 아이템의 `(type_id, model)`이 일치하는 후보이고, 모든 호출자의 모델 변환 경로를 추적한 연결은 아니다. 그룹 10의 enum은 아직 확정하지 않았다.

탐색 경계: 현재 Assembly-CSharp 메서드 이름 전체에서 ModelFlag getter는 위 4개이며, 그룹 10용 getter가 명시적으로 확인되지 않았다. 그룹 키가 아이템 타입 10과 같거나 플래그 값이 기존 enum 값과 같다는 이유로 enum을 확정하지 않는다. 다른 모델·아바타 선택 경로의 변환을 전부 추적하지 않았으므로 후보 연결도 확정 연결로 승격하지 않았다.

로더는 그룹 20에서 모델 1의 속성을 모델 0에도 추가한다. 이 원문 밖 파생 항목 1개는 `runtimeDerivedEntries`에 분리했으며, 현재 마스터에서는 아이템 20998이 같은 키를 사용한다. 원문 2,498행에 합쳐 넣지 않았다.

### 미해석 드롭 표

ItemDorpData는 현재 40,863바이트다. 선두 i32는 3,143이며, 이후를 13바이트씩 나누면 EOF까지 정확히 맞는다. 각 구획의 선두 i32 후보도 모두 마스터에 존재한다. `uninterpreted13ByteChunks`에 전 구획의 오프셋·원문 hex·선두 정수 후보·일치 여부를 남겼다.

현재 메타데이터/함수명과 제한된 로더 탐색에서 대응 코드를 찾지 못했다. 따라서 남은 9바이트를 드롭률·몬스터 ID·희귀도로 이름 붙이지 않았고, 후보 정수를 확정된 아이템 참조로 제공하지 않았다. 대응 코드의 부재를 전체 클라이언트에서 사용하지 않는다는 증거로 취급하지 않는다.

## 코드 근거와 재현

동의하에 먼저 확보한 GameAssembly 사본만 분석했다. 이번 보조 테이블 작업은 프로세스에 접근하지 않았다. 원본 소스가 아닌 Ghidra 12.1.4 의사 코드이며, REA 엔진 Evidence로 표시하지 않는다. 메타데이터는 SHA-256 `f0cf212a7c7dca1973a401bda6d208549c13f57f0bbdb8782e5d607ed7e8789f`, 재구성 PE는 `013f5d1668b857820490a9e7f49b716a41eaa2aec1b4c1a449d12ec38a4d7fa0`다.

| 메서드 | 저장 모듈 RVA |
| --- | --- |
| ItemRandomPropertyMaster.ReadMasterData | 0xe33e00 |
| ItemRandomPropertyMasterData.ctor(BinaryReader) | 0xe339f0 |
| MasterItemDataManager.ReadCreateSupportItem | 0xe34860 |
| ItemTextManager.SetNGItem | 0x308fe0 |
| RecipeDBDataManager.LoadData | 0xa482a0 |
| RecipeDBData.ctor(필드 매개변수) | 0xa49490 |
| RecipeMaterialData.ctor | 0xa49600 |
| MasterModelDataManager.ReadMasterData | 0xe3f330 |
| SmithManufacture.CheckManufactureMaterial | 0xa3bf20 |
| MasterModelDataManager.GetBodyModelFlag | 0xe35c20 |
| MasterModelDataManager.GetAvatarTopModelFlag | 0xe35b60 |
| MasterModelDataManager.GetOptionModelFlag | 0xe36160 |
| MasterModelDataManager.GetAvatarOptionModelFlag | 0xe359f0 |
| RecreateRecipeElement.SetRecipe | 0xa8ba30 |
| RecreateRecipeElement.setTypeName | 0xa8c270 |
| UIRecreatePanel.getRecipeData | 0xa97dc0 |
| UIRecreatePanel.getModelIndexString | 0xa979b0 |
| 외형 레시피 CreateId 비교 predicate | 0x36aa40 |
| UIItemBagManager.RecipeLoadData.MoveNext | 0x776a90 |
| UIItemBagManager.OpenCollectBuySlotPanel | 0x77fc00 |
| 수집 가방 CreateVal 비교 predicate | 0x777bf0 |
| System.Enum.ToString (mscorlib) | 0x1dfddb0 |
| System.String.Concat(string,string) (mscorlib) | 0x1c21970 |

관련 의사 코드 29개와 각 코드 SHA-256, token/RVA, 랜덤 옵션 getter 바이트, enum 선언을 JSON에 포함했다. `recipeTargetLookupRule`에는 접두사 literal의 원문 위치, BCL 호출 매핑, System 텍스트·출처 번들의 해시를 추가했다. Ghidra의 일부 enum 반환형 표현이 포인터로 나오는 한계가 있어 실제 타입은 메타데이터 선언을 기준으로 기록했다. 분석 프로젝트·전체 모듈은 `build/tmp/toram-item-extraction/code-trace/runtime/relations/` 및 그 상위 사본 경로에 남아 있다.

```powershell
python tools/extraction/extract-toram-item-relations.py --self-test
python tools/extraction/extract-toram-item-relations.py
```

검증 결과: 5개 스키마의 정상/잘림/후행 바이트 fixture PASS, 음수 옵션·실제 필드 순서 PASS, 레시피 namespace 구분·잘못된 카테고리/단계 거부 PASS, 실제 5개 표 EOF·바이트 단위 재조립 PASS, 미해석 표 전 구획 재조립 PASS. 외형 330개 카테고리/문구 연결·키 유일성 PASS, 수집 가방 50개 단계 1~50 완주 PASS. 게임 화면·서버 동작·앱 계산 적용은 검사하지 않았다.
