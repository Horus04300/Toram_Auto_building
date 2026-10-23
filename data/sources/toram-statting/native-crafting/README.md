# 제작 장비의 기초 잠재력 상한 근거

2026-10-21. 보존된 GameAssembly 스냅샷과 기존 아이템/레시피 원본을 대조했다. 현재 게임·서버에 접속하거나 제작을 실행하지 않았다. REA provider 대신 지정 함수 Ghidra 분석을 재사용했으며 REA retained Evidence ID는 없다.

## 확정한 것

- `ItemDBData.get_Potential`(RVA `0xe245c0`)은 **signed short `self+0x4c`**를 반환한다. 원본 아이템 기초 잠재력 필드다.
- `RecipeDBData` 생성자는 `Difficulty`를 `+0x1c`, `CreateId`를 `+0x20`에 저장한다.
- `SmithManufacture.loadRecipe`는 플레이어 모드에서 `RecipeDBDataManager.GetData(...,isShop=false,isSmith=true)`를 호출한다.
- `getData`의 플레이어 분기는 `Difficulty==0`인 레시피를 건너뛰고, 제작 난이도 충족 여부를 `CanCreate`에 기록한다. `loadRecipe`의 후속 predicate `<loadRecipe>b__60_0`는 출력 아이템의 기초 잠재력이 1 미만인지 검사한다.
- 기존 원본의 Type0=Smith 레시피 중 `Difficulty>0`이고 출력 아이템 `Potential>0`인 후보를 비교하면 아래 10개 카테고리의 최대 기초 잠재력이 나온다. 이 선택과 입력 해시는 `extract-base-profiles.py --check`로 재현한다.

| 유형 | 최대 기초 잠재력 | 해당 아이템 |
| --- | ---: | --- |
| 한손검 | 67 | 11주년의 축검 VI (10188) |
| 양손검 | 67 | 11주년의 축대검 VI (11169) |
| 활 | 67 | 11주년의 축궁 VI (12154) |
| 자동활 | 67 | 11주년의 축궁총 VI (13160) |
| 지팡이 | 67 | 11주년의 축장 VI (14184) |
| 마도구 | 67 | 11주년의 축익 VI (15162) |
| 권갑 | 67 | 11주년의 축수갑 VI (16171) |
| 선풍창 | 67 | 11주년의 축창 VI (24162) |
| 발도검 | 67 | 11주년의 축인 VI (25144) |
| 몸장비 | 63 | 주년제의 축하 옷 VII (20155) |

`base-profiles.json`에는 모든 동률 아이템·6개 언어·적합한 레시피 ID/난이도를 보존한다. 9개 무기는 난이도320 레시피, 몸장비는 난이도300 레시피를 갖는다. 이 결과는 원본에 존재하는 제작 장비의 이론적 비교이며, 해당 주년제 제작 이벤트가 지금 열려 있다거나 모든 캐릭터의 숙련도로 바로 제작 가능하다는 뜻이 아니다. 오래된 제작 장비의 보유/거래 가능성과 현재 제작 메뉴 노출도 구분한다.

## 완성 잠재력은 아직 원형으로 확정하지 않은 부분

`docs/sources/skills/Smith.txt`는 신중한 제작 Lv10의 기본 잠재력 +10%, 장인의 제작기술 Lv10의 +20%를 합산하고 스탯 보너스보다 먼저 적용한다고 설명한다. `docs/statting.md`는 장비 유형별 제작자 기본 스탯 보너스를 정의한다. 이는 **원문/사용자 제공 규칙**이며 이번 조사에서 그 30%의 반올림 순서를 확정하는 네이티브 함수는 확보하지 못했다.

따라서 `base-profiles.json`은 완성 잠재력 138/128/132 등을 네이티브 검증값으로 저장하지 않는다. 상위 실험기는 별도로 출처를 분리한 프로필을 만들 수 있지만, 기반 비용 연산이 원형과 같다는 사실로 시작 잠재력 계산까지 검증됐다고 설명해서는 안 된다. 슬롯 수에 따른 제작 잠재력 저하·제작 실패의 잠재력 변화도 여기서 검증하지 않았다.

이번 확인은 `SmithManufacture`의 레시피 로딩·정보 표시·제작 요청 진입점과 `ItemDBData` getter까지다. 제작 요청 진입점에 연결 코드가 있다는 사실만으로 생성 공식 전체가 서버에만 존재한다고 단정하지 않는다. 초기의 `RequireData.GetAllPotential` 조사 함수들은 TEC 반환과 카테고리 패널티를 계산하는 **옵부 보조 경로**여서 제작식 근거로 사용하지 않았다.

## 정적 분석 범위와 재현

`index.json`에 원본 해시·토큰·주소·보존 파일 해시를 연결했다. `RecipeDBDataManager-getData`는 타입 검사 공용 함수에서 decompiler가 PIC로 분기를 오인하는 경고가 남아 있어 `.partial.c`로 보존했다. 사용한 근거는 그 경고 위치 이전의 독립적인 플레이어 `Difficulty` 검사이며, 누락된 하단 제어 흐름이나 전체 함수 복원을 완료했다고 주장하지 않는다. getter·Recipe 생성자·후속 predicate에는 해당 제거 경고가 없다.

```powershell
python assets/source-data/toram-statting/native-crafting/extract-base-profiles.py --check
python assets/source-data/toram-statting/native-crafting/self-check.py
```

위 검증은 바이트 해시와 고정 원본의 선택/최대값을 확인하며 실제 게임 제작 결과를 실행 검증하지 않는다.
