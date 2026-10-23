# 몬스터 원본 레코드 계약

기준은 `native-schema/index.json`에 기록한 설치 DLL·metadata·저장된 모듈의 SHA-256과 해당 함수의 Ghidra 12.1.4 정적 결과다. 게임 실행 관찰이나 원본 C# 복원으로 해석하지 않는다.

## 자원 연결

`<loadFieldData>d__125.MoveNext`(VA `0x7fff603f3f50`)는 `MapInfo` 객체의 `+0x48` TextAsset을 `MobMaster.ReadMaster`에 전달한다. 현재 metadata의 `MapInfo`에는 `mobDb` 필드와 `UnityEngine.TextAsset get_MobDb()`가 있다. 따라서 몬스터 마스터를 찾을 곳은 필드 프리팹의 `MapInfo.mobDb` 참조다. `BynaryData`에 이름이 비슷한 파일이 없다는 사실은 몬스터 수치가 없다는 근거가 아니다.

`MobMaster.ReadMaster`(VA `0x7fff5fe48ff0`)는 TextAsset 바이트를 `BinaryReader`로 직접 읽는다. 이 경로에는 아이템 BynaryData의 피드백 XOR 복호를 적용하지 않는다. `<LoadMapInfo>d__94.MoveNext`(VA `0x7fff6037e4c0`)의 기본 경로는 필드 ID/1000으로 묶음 자원을 고르고 전체 필드 ID로 객체를 고른다. 실제 `FieldScript/FieldScript_0`, `_23`, `_32`, `_100` 공개 번들에서 `MapInfo.mobDb` 참조와 해당 `mob_*` TextAsset을 확인했다. `Field_*` 지형 번들과 구분한다.

## 파일 및 레코드

첫 int32가 양수면 필드 ID와 구버전 식별값을 겸한다. 음수/0이면 버전 값이며 다음 int32가 필드 ID다. 이어서 int32 몬스터 수와 가변 길이 레코드가 있다.

`MobStatusMaster.CreateStatusMaster`(VA `0x7fff5fe6a780`)의 앞부분:

| 직렬화 필드 | 형식 | 런타임 객체 오프셋 |
| --- | --- | --- |
| id, uuid | int32 각각 | +0x10, +0x14 |
| roomId | byte | +0x18 |
| name | BinaryReader UTF-8 string | +0x20 |
| level | int16 → int32 | +0x28 |
| exp, maxHp | int32 각각 | +0x2c, +0x30 |
| expDefNormal, expDefSkill, expDefMagic | byte 각각 | +0x34, +0x35, +0x36 |
| necessaryHit, def, mdef, cutAttack, cutMagicAttack, guard, avoid | int16 각각 → int32 | +0x38 ~ +0x50 |
| flag | int32 비트 | +0x58 |
| element | byte → enum | +0x54 |
| model | int32 | +0x5c |
| size, scale, color1/2/3, moveSpeed, persona, personaValue | byte, int16, int32×3, int16, byte, int16 | +0x60 ~ +0x7c |

객체의 `element`와 `flag` 오프셋 순서는 파일 순서와 다르다. 파일에서는 **flag 다음 element**다. `raw` 접미사는 원본 단위를 유지한다는 의미이며 정적 레코드 자체를 최종 전투 수치로 간주하지 않는다.

뒤에는 액션 수/액션들, 부위 수/(byte,int32) 쌍, 모드 수/35바이트 모드들이 온다. 버전 < -1은 각 몬스터 뒤에 속성 수와 `(byte uid, int16 type, int32 values[5])` 23바이트 속성들이 붙는다. 파일 버전 < 0은 마지막에 드롭 그룹 수와 `(int32 key, int32 pairCount, (int32,int32)[pairCount])`가 붙는다. 두 번째 드롭 단어는 네이티브에서 읽고 버리지만 추출본은 보존한다.

액션은 `MobActionPattern.CreateActionPattern`(VA `0x7fff5fe32440`)을 따른다. ID와 combo는 버전 < -2에서 byte에서 int16으로 바뀐다. 버전 < -3이면 int16 commonFlag, 버전 ≤ -5이면 int16 값 10개가 추가된다. 각 레코드 크기는 구버전 54, -3은 56, -4는 58, ≤ -5는 78바이트다. 타이밍 바이트와 기타 피연산자의 게임상 효과는 별도 규칙 확인 전까지 원형으로 보존한다.

## 언어 및 식별자

`EnemyTextManager.Initialize`(VA `0x7fff5f555c00`)는 int32 수 뒤 `(int32 ID, BinaryReader string)`을 읽어 사전을 만든다. `GetName`(VA `0x7fff5f555b60`)는 해당 ID로 조회한다.

**이름 연결 키는 uuid다.** `EnemyMobActionManagerBase.get_MobName`(VA `0x7fff5fe22e10`)는 `LocalizeManager.Get(7)`을 얻고 `mobStatusMaster + 0x14` 값을 해당 관리자의 Get에 전달한 뒤 이름을 반환한다. metadata의 `LocalizeType.Enemy` 값은 7, `MobStatusMaster.get_Uuid`(VA `0x7fff5f4e44f0`)는 +0x14를 읽는다. 일반 경로의 +0x70과 대체 부모 경로는 `get_MobStatusMaster`(VA `0x7fff5fe22f70`)로 대조했다. 따라서 `gameMonsterId = uuid`, `key = fieldId:id`로 구분한다. 같은 UUID의 레벨·전투 모드·부위 레코드는 합치지 않는다.

실제 표본은 `23000:10`의 UUID 540(기드론/Grimuckus), `32700:1`의 UUID 888(기룡 미뮤가/Trickster Dragon Mimyugon), `100800:1`의 UUID 974(폴버로스/Falburrows)에서 각각 모든 언어로 연결됐다. UUID 974는 필드 100802에 다른 레벨·HP·DEF를 가진 레코드도 있으므로 이름 하나로 수치를 덮어쓰면 안 된다.

## 검증과 한계

`tools/extraction/extract-toram-monster-data.py --self-test`는 앞/뒤 바이트 경계, 음수 값, 가변 액션 버전, 속성, 중복 텍스트 ID, 정확한 EOF, UUID 언어 연결과 동일 필드/로컬 ID 중복을 검사한다. 원본 레코드 hex와 소스 해시를 보존한다. `parse_mob_db`는 형식 오류에서 실패하고 `parse_tables`는 해당 표를 해시·오류와 함께 `rejectedTables`로 분리한다. 공개할 수 있는 예외인지 여부는 상위 파이프라인 계약이 판정한다.

초기 실제 58개 표 중 56개 표/311개 레코드가 정확한 EOF를 통과했다. `mob_0`은 50개 레코드 뒤에 네이티브가 읽는 드롭 수 4바이트가 없고 `mob_1`은 현재 Reader 경로와 맞지 않는다. 두 원본은 보존하고 가짜 0 바이트나 추정 레코드를 추가하지 않았다. 이 표본 수는 전체 게임의 최신 추출 건수 판정에 사용하지 않는다.

난이도 보정, 모드별 대상 교체·속성 override, 서버 상태는 이 원본 파서의 범위 밖이다. `maxHp`, DEF/MDEF 및 저항 필드가 존재한다는 사실만으로 화면의 최종 난이도 수치나 실제 전투 효과가 검증됐다고 표시하지 않는다.
