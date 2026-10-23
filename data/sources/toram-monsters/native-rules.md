# 몬스터 분류·난이도 원본 규칙

2026-10-18. 저장된 GameAssembly PE 스냅샷과 현재 메타데이터의 지정 함수만 분석했다. 게임 프로세스 재접근·함수 실행은 하지 않았다. 수치와 원문 위치는 `monster-native-rules.json`, 함수·메타데이터 토큰·SHA-256은 `native-rules/index.json`이다. REA provider를 사용할 수 없어 private Ghidra 12.1.4 프로젝트의 `-noanalysis` 지정 함수 분석을 사용했으며 REA Evidence ID는 없다.

## 분류에서 확인한 것

- `MobMultiFlag.Boss=4`, `Dungeon=16`. `MobStatusMasterEx.CheckMultiFlag`는 master+0x58의 비트가 모두 켜졌는지 확인한다. 이 Boss 비트 하나로 입장/필드/고난이도를 결정하면 안 된다.
- `BossRoomData.get_RoomType`는 2를 반환하며 `FieldRoomType.Mo=2`다. `MobActionManager`는 일반 `MobBattleStatus`를 만들고 Boss 비트를 별도로 검사한다. 반면 `BossMobActionManager`는 Dungeon 비트가 없는 경우 `BossMobBattleStatus`에 `RoomManager.GetAreaLevel()`을 전달한다. Dungeon 비트가 있으면 별도의 Dungeon 클래스를 쓴다.
- `HighRaidBossActionManager`는 별도 `HighRaidBossBattleStatus`와 레벨 필드를 사용한다. `FieldRoomType.HighRaid=28`, `MobTypeFlag.HighRaid=128`은 메타데이터 상수다. 이것만으로 사용자가 말한 모든 고난이도 보스를 HighRaid라고 확정하지 않는다.
- 현재 메타데이터에는 `MapInfo.typeRoomObj` 필드는 있지만 `RoomObjInfo` 타입은 없다. `MapInfo.Initialize`는 room type과 room ID로 Transform 하위 객체를 선택한다. 번들의 직렬화된 방 이름과 실제 몬스터 연결을 유지해야 하며 해당 숫자를 임의의 enum으로 바꾸지 않는다.

## 일반 입장 보스의 난이도 계산

`DifficultyState`는 Easy=-1, Normal=0, Hard=1, Lunatic=2, Ultimate=3이다. 인덱스는 `clamp(difficulty,-1,3)+1`이다.

| 값 | Easy | Normal | Hard | Lunatic | Ultimate |
| --- | ---: | ---: | ---: | ---: | ---: |
| HP 배율 | 0.1 | 1 | 2 | 5 | 10 |
| DEF/MDEF/NecessaryHit 배율 | 0.1 | 1 | 2 | 4 | 6 |
| 레벨 가산 | -10 | 0 | 10 | 20 | 40 |

HP·스탯 곱셈은 정수 입력을 float32로 바꾸고 float32 배율을 곱한 뒤 signed int32로 0 방향 절삭한다. 레벨은 short 덧셈 후 최소 1이다. 배율 배열은 `.cctor`의 초기화 필드 참조를 메타데이터 원시 blob에 연결했고, 20바이트 SHA-256이 컴파일러 필드명과 일치함을 검증했다. JSON에는 0.1의 실제 float32 값도 보존했다. 유효 int32 범위 밖의 결과를 앱 값으로 지원하지 않는다.

위 표는 필드 보스·HighRaid·던전 등 모든 하위 클래스의 공통 규칙이 아니다. 최종 DEF/MDEF에는 미파괴 부위, 버프와 상태이상도 작용한다. `CutAttack`, `CutMagicAttack`, 가드/회피 값에는 같은 난이도 곱셈이 없으며 부위/속성 변경이 추가될 수 있다. 이 조사에서는 CutAttack 이름을 임의로 물리내성 단위로 변환하지 않았다.

## 크리티컬 저항·관성

`MobPropertyCriticalResist.get_PropertyType`은 6을 반환한다. 이 속성의 `Values[0]`이 기본 크리티컬 저항 operand이며, 적용 함수는 크리티컬 확률에서 저항을 빼고 최소 0으로 제한한다. 상태이상과 버프가 저항 자체를 낮출 수 있으므로 기본 operand를 전투 중 최종 값으로 간주하지 않는다. 몬스터별 속성 목록 연결을 확인한 뒤에만 앱에 적용한다.

마스터의 `ExpDefNormal`, `ExpDefSkill`, `ExpDefMagic` getter는 각각 +0x34, +0x35, +0x36의 byte다. 이 이름과 원시 byte를 보존했다. 최종 관성 상태의 시간 전이나 상한·하한까지 확인한 것으로 보지 않는다.

## 검증·한계

보존한 67개 함수의 파일 SHA-256과 초기화 배열 10개의 컴파일러 필드 SHA-256을 확인했다. 분석 스크립트는 고정 PE SHA·image base를 검사하고 메타데이터 토큰으로 함수 원형을 지정한다. index.json과 새 출력 디렉터리를 인자로 재현할 수 있다. JVM의 설정/캐시/임시 디렉터리는 작업용 build/tmp에 한정했다.

런타임 heap은 이 모듈 스냅샷에 없으므로 이미 해석된 문자열·delegate 포인터를 복원하지 않았다. 원시 마스터와 방/스폰 연결 추출은 별도이며, 여기서 이름으로 보스 분류나 누락 저항·레벨을 추정하지 않는다.
