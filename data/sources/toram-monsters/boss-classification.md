# 보스 종류와 입장 방식의 연결 근거

규칙 원본은 `boss-classification-rules.json`, 네이티브 토큰·주소·파일 SHA는 `native-classification/index.json`이다. 앞서 보존한 GameAssembly 이미지의 선택 함수 25개를 Ghidra로 정적 확인했다. 실행 중 방 선택이나 실제 전투를 관찰한 결과로 취급하지 않는다. `TraceToramBossClassification.java`에 `method-map.json`과 새 출력 폴더를 전달해 재현한다. PE SHA와 image base를 검사하며 전체 자동 분석이나 게임 실행은 필요 없다.

## 고난도 레이드

`HighRaidEventData.LoadBossMaster`는 byte 헤더, int32 수 뒤 다음 순서를 읽어 `HighRaidBossMasterData`를 만든다.

| 필드 | 원문 형식 |
| --- | --- |
| No | byte |
| FieldId | int32 |
| RoomId, RaidFlag | byte 각각 |
| MonsterId, MonsterUuid | int32 각각 |
| BaseLevel, MinLevel | int16 각각 |
| 보상 수 | int16 |
| 보상 | byte RewardNo, int32 Cost, byte Type, int32 Value/Num, byte Flag |

`FieldId:MonsterId`가 실제 맵 마스터에 있고 UUID도 같을 때만 연결한다. 같은 필드·방·UUID의 단계 변종에 그 출처를 공유한다. 이름이나 `hrmo_` 방이 존재한다는 사실로 다른 몬스터까지 확대하지 않는다. 알타달은 field 101100/UUID 1001, 메르제하르는 field 90965/UUID 1187에 직접 등록돼 있다.

`HighRaidRoomData.get_MobDifficultyLevel`은 0을 반환하고 `get_AreaLevel`은 별도의 short 레벨을 읽는다. `HighRaidBossActionManager.SetMobLevel`은 별도의 레벨 필드를 갱신하며, `OnSetStatus`와 `HighRaidBossBattleStatus.get_Level`은 그 값의 저장·조회 경로다. 입장 UI도 선택 수치를 증감한다. 따라서 이 축은 일반 Easy~Ultimate 선택과 분리한 `level-select`다. BaseLevel/MinLevel은 원명과 값으로 보존하며, 런타임 선택 상한·실제 입장 가능 여부나 레벨별 최종 HP/DEF를 만들어내지 않는다.

## 일반 입장 메뉴

`FieldScriptLoader.ReadEventIndex`는 byte 버전·int16 이벤트 수·int32 절대 오프셋 표에서 해당 이벤트 시작 위치를 얻는다. `_ScriptThread.MoveNext`는 그 위치에서 short 명령을 읽어 핸들러를 호출한다. `FieldScriptCommand.BossMenu=130`과 `_OnBossMenuCommand.MoveNext`의 필드/방 입력을 연결한다.

- 스크립트 버전 <14: int16 FieldId, byte RoomId.
- 버전 14: int32 FieldId, byte RoomId.
- 버전 ≥15: byte 명령 형식 버전, byte 읽고 버리는 값, int32 FieldId, byte RoomId.

뒤의 위치·방향·기타 인수는 이 식별자 연결에서 해석하지 않는다. 이벤트 시작점과 **검토한 version16 ProgressQuest(38)·Check(20) 분기**만 따라간다. Check의 두 절대 offset을 가능한 경로로 검사하고 현재 퀘스트 상태/해금 여부는 판단하지 않는다. 동적 ReadInt operand·미검토 opcode에서 멈추며 임의 바이트열에서130을 검색하지 않는다. 순환 방문·잘린 operand·잘못된 분기 위치를 검사한다. 근거 `native-entry-flow/README.md`.

콜론 보스/조성중 지구3300:10은 이벤트10의5695→5703→5719 경로로 BossMenu에 연결된다. 첫 명령만 읽던 범위에서 놓친 사례다. source 이벤트 맵과 메뉴의 대상 맵을 구분하며 대상 FieldId/RoomId에 연결한다. 미뮤가32700, 폴버로스100801/100802도 직접 메뉴 경로다. 폴버로스100800이나 콜론 보스4500:100처럼 다른 맵의 같은 UUID에는 분류를 복사하지 않는다.

이 연결의 입장 방식은 `difficulty-select`다. 일반 BossMobBattleStatus의 난이도 배열은 별도 `monster-native-rules.json`에 있다. 특정 보스의 모든 난이도 해금/사용 가능성이나 특수 전투 클래스까지 이 연결 하나로 확정하지 않는다.

## 필드 개체와 던전

Boss 비트 4와 정확한 `MobPopPoint.monsterDatabaseID` 참조, 해당 마스터 RoomId의 `mmo_{RoomId}` 조상 연결을 요구한다. 기드론의 field 23000/masterId 10은 이 출현점에 직접 연결된다. MapInfo의 방이 단순히 존재하는 것만으로 판정하지 않는다.

`FieldRoomType.Mmo=0`, `FieldManager.IsMmo`, `MapInfo.GetMobPopPoint`, `MobFactory.CreateMmoMobObject/CreateMobObject`가 일반 필드 생성 경로를 뒷받침한다. 팩토리는 Mmo/GameEvent 방에서 일반 Boss 컴포넌트 선택 비트를 제거한다. `mmo_`의 직렬화 명명과 네이티브 Mmo 계약의 대응을 사용하는 정적 출처 분류이며, 캡처 이미지에 없는 heap 문자열 포인터나 현재 활성 방을 관찰했다고 주장하지 않는다.

필드 보스는 `single`, `difficulty:null`이다. 맵별 기록·단계는 원형으로 유지하지만 난이도 선택지로 만들지 않는다. Boss와 Dungeon 비트 16이 함께 있는 기록은 별도 `dungeon-boss`이며 일반 입장 난이도를 적용하지 않는다.

## 누락과 오류 경계

양성 근거가 없는 변종은 `unresolved`다. 같은 UUID의 다른 맵으로 분류를 복사하지 않는다. 몬스터 개수, 이름, 미출현, 단순 방 이름만으로 분류하지 않는다. 과거 표에 있는 field 90960 레이드 참조는 이번 리소스의 정확한 맵 마스터와 연결되지 않아 별도로 남긴다.

일부 보존 스크립트에는 마지막 미사용 슬롯이 파일 EOF를 가리킨다. 해당 슬롯은 실행 가능한 메뉴 근거로 쓰지 않고, 정상 이벤트 시작점만 검사한다. 정확한 스크립트 SHA·문제 슬롯을 갱신 계약에 고정했다. 새로운 오류/다른 참조 불일치는 개발판 발행을 차단한다.
