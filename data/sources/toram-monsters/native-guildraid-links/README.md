# 길드 레이드 경로·개체 연결 근거

2026-10-19. 이전에 보존한 GameAssembly 스냅샷·동일 메타데이터·공개 원본 번들을 읽었다. 게임 실행·프로세스 재접근·네트워크 요청은 하지 않았다. `index.json`에 함수 주소·메타데이터 토큰·SHA-256과 재현 방법을 보존했다. 직접 scoped Ghidra 결과이며 REA Evidence ID는 없다.

## 관측된 로컬 자료와 서버 경계

검사한 BynaryData 번들의 TextAsset 38개 전체 이름·원시 해시는 `bynary-inventory.json`이다. HighRaidBossMaster는 있지만 GuildRaid 이름의 마스터는 없다. 메타데이터에도 HighRaidBossMasterData 같은 대응 길드 보스 로컬 마스터 타입을 발견하지 못했다. 이 범위의 부재를 게임 전체에 동등한 자료가 절대 없다는 주장으로 확대하지 않는다.

길드 레이드의 명시적인 입장 데이터는 서버 이벤트 `Toram.Common.Events.Room.GuildRaid.EnterGuildRaidField`다. 이 타입은 `Setting`, `BossFieldSettingData`, `MobList`, `RandomPropertyList`, `StartHpCount`, `CurrentHpCount`를 따로 가진다. `BossFieldSettingData`에는 FieldId·RoomId가 있고, MobList에는 그 장면의 개체가 들어간다. `PhotonListener.OnEventEnterGuildRaidField`(0x135c7d0)는 이 데이터를 받아 GuildRaidRoomData를 준비하고 네트워크 Setting.Level을 설정하며, 서버의 필드/방과 MobList를 생성 경로에 전달한다. 서버 이벤트 payload는 이 조사에 없다.

`GuildRaidRoomData.ReceiveBossSymbolData`(0xe908b0)의 실제 인자는 `mobUuid, currentHpGauge, maxHpGauge, battleHp, element, isPractice`다. UUID와 속성을 해당 방 데이터에 저장한다. 이를 로컬 HighRaid 마스터처럼 고정 6개 행을 파싱하는 구조로 만들면 근거를 잘못 표현한다.

기존 `native-classification/MobFactory-CreateMobObject-7fff5fe35980.c`에는 room type 29가 `MobTypeFlag.GuildRaid=256`을 더하고, master의 Boss 비트가 별도로 Boss=1을 더하는 경로가 있다. `metadata.json`의 FieldRoomType.GuildRaid=29, MobTypeFlag.GuildRaid=256 선언과 대응한다. 같은 방에 Boss 비트가 있는 추가 몬스터도 길드 보스 클래스로 만들어질 수 있다. 따라서 추가 몬스터를 일반 MobBattleStatus라고 가정해 주요 보스와 구분하지 않는다.

## 요청한 6종과 현재 원본의 연결

아래 연결은 사용자가 2026-10-19 제공한 이름·길드 레이드 분류를 현재 원본의 UUID·필드/로컬 ID·다국어 이름·모델·속성과 대조한 검토 기준이다. 게임에서 추출한 고정 GuildRaidBossMaster라고 주장하지 않는다. 6개 MapInfo에 있는 `soro_0/mmo_0/mo_0` 방 이름만으로도 길드 분류를 확정하지 않는다. 현재 스크립트의 이벤트 첫 명령에도 길드 레이드 입장 명령은 없다.

| 필드:로컬 ID | UUID | 한글 원본 | elementRaw | 모델 |
| --- | ---: | --- | ---: | ---: |
| 100100:1 | 916 | 혁작의 셀디테 | 1 | 1010101 |
| 100200:1 | 741 | 빙암의 바이슨 | 2 | 1008001 |
| 100300:1 | 802 | 굉뢰의 구름전차 | 3 | 1010601 |
| 100400:1 | 830 | 진암의 키마이라 | 4 | 1005702 |
| 100500:1 | 1195 | 구원의 소테리아 | 5 | 1015601 |
| 100500:2 | 1195 | 구원의 소테리아 | 5 | 1015602 |
| 100600:1 | 742 | 용골의 마인 | 6 | 1003902 |

소테리아는 같은 UUID를 공유하지만 로컬 ID와 모델이 다르다. 100500:1은 DEF175/MDEF350, 100500:2는 DEF300/MDEF125이며, 각각 mode.targetMonsterId=101/102로 연결한다. 사용자가 알려 준 남/여의 DEF/MDEF 특징과 이를 대조해 UI 이름을 붙일 수 있다. 게임 원본에 성별 필드가 있다고 표현하지 않는다. 다른 UUID인 추가 몬스터를 이름이나 같은 필드라는 이유만으로 이 주요 개체에 포함하지 않는다.

파이프라인에는 검토한 exact anchor·UUID·속성·모델을 명시하고 불일치 시 발행을 멈추는 방법이 적절하다. 같은 필드·동일 UUID인 명시적 mode 참조를 전파할 때도 다른 개체/필드로 이름 기반 추측을 확장하지 않는다. 이 문서는 앱의 검토 목록이나 파이프라인 계약을 직접 변경하지 않았다.

## 레벨과 전투 상태 경계

원본의 위 7개 기본 행은 level100이다. 실제 길드 레이드 레벨은 별도 값이다. `RaidHeldData.get_SummonLevel`(0xe01950)은 HeldCount byte를 2비트 왼쪽 이동한다. `ReceiveBossSymbolData`는 CurrentLevel을 `max(40, (currentHpGauge & 255) * 4)`로, GuildRaidLevel short를 `max(40, maxHpGauge * 4)`로 설정한다. 입장 이벤트에서는 Setting.Level도 별도로 설정한다. 이 관측을 일반 입장 보스 난이도로 치환하거나 로컬 원본 level100을 실제 전투 레벨로 고정하면 안 된다.

RandomPropertyList는 서버 이벤트/응답의 독립 자료다. 원본 카탈로그만으로 매번 실제 선택된 랜덤 옵션이나 현재 HP 게이지를 알 수 없다. 기본 스탯 제공과 특정 실행 중 방의 최종 전투 상태는 구분한다.

## 검증

보존한 16개 함수의 해시와 스크립트·메타데이터 해시를 검사했다. `index.json.reproduction`에 재현 명령이 있다. JVM 설정·캐시·임시는 작업용 build/tmp에 한정했다. 정적 자료에서 확인한 구조와 사용자가 제공한 분류를 분리했으며, 현재 서버의 실제 입장 payload나 모든 부위 활성 상태를 관측한 것으로 표현하지 않는다.
