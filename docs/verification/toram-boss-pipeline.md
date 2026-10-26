# 보스 원본 갱신 파이프라인

현재 기능 판정과 검증 결과는 `../handoff/current-development-handoff.md`를 기준으로 한다. 이 문서는 수동 명령·출처·보존/발행 계약을 설명한다.

## 실행

```powershell
npm run bosses:sync
npm run bosses:sync -- --check
npm run bosses:test
```

기본 공개 리소스 브랜치는 2026-10-22 블랑 신규 원본을 확인한 `releaseC`다. 이전 분기는 `--application releaseB`로 재현한다. 실제 로그인 서버의 활성 브랜치를 관찰했다는 의미는 아니다. `--application releaseA` 등은 명시적으로 선택하며 브랜드별 캐시를 섞지 않는다. `--check`는 manifest/설치/도구 식별자만 확인하고 개발판을 교체하지 않는다. Python은 기존 아이템 명령과 같은 `TORAM_ITEM_PYTHON` 또는 번들 런타임을 사용한다. UnityPy 1.25.4 경로는 `--unitypy-path`로 지정할 수 있다. 새 설치에서는 이 의존성을 먼저 준비한다.

재현·오프라인 입력은 `manifest.bytes`와 해당 manifest의 모든 FieldScript/GameScene 번들이 있는 source 디렉터리다.

```powershell
npm run bosses:sync -- --offline build/tmp/toram-monster-capture/source
```

실행은 수동이다. 게임 실행/메모리 접근/계정 API/예약 실행/사용자 세팅 변경은 없다. 공개 배포·앱 설치도 하지 않는다.

## 출처와 식별자

`https://toram-jp.akamaized.net/resources/windows/{application}/RevisionInfoBinary.bytes`의 **전체 `FieldScript/FieldScript_{0}` 그룹**, BynaryData, 여섯 언어 GameScene 번들을 읽는다. 지형 `Field/Field_{0}` 전체를 받는 방식은 사용하지 않는다. outer UnityFS TextAsset을 manifest의 개별 cacheKey로 복호한 뒤, 실제 `MapInfo.mobDb` 로컬 참조가 가리키는 TextAsset을 추출한다. mobDb 바이트 자체는 BinaryReader 원문이며 다시 XOR하지 않는다. MapInfo·출현점·방 계층·이벤트 영역·스크립트 바이트와 HighRaidBossMaster도 보존한다.

`MobStatusMaster.uuid`가 Enemy 번역 사전의 키라는 호출 경로를 보존했다. 게임 몬스터 ID는 UUID, 변종 키는 **`fieldId:masterId`**다. 이름이 같아도 맵·모드·부위·레벨이 다른 레코드를 합치지 않는다. 여섯 언어 Enemy/FieldName 표는 매 실행 새 번들에서 파싱하며, 없는 번역은 null로 남긴다.

근거: `data/sources/toram-monsters/monster-schema.md`, `native-schema/`, `monster-native-rules.json`, `native-rules/`, `boss-classification.md`, `native-classification/`, `native-target/`, `native-highraid-target/`, `native-guildraid-target/`, `native-guildraid-links/`, `guild-raid-bosses.json`. 계약은 `tools/extraction/toram-boss-pipeline-contract.json`이다. 네이티브 근거·규칙 파일 해시 632개와 설치 DLL/metadata 식별자를 검증한다. 정적 분석은 앞서 보존한 이미지에 대한 것이며 이번 수집에서 실행 중 게임을 관찰하지 않았다.

## 이력·차이·발행

원본 이력: `data/sources/toram-monsters/pipeline/{application}/`. Git 제외이므로 별도 백업한다.

- `bundle-cache/`: 브랜치·asset·manifest revision별 불변 다운로드 캐시. 재사용 전에 SHA를 검사한다.
- `snapshots/.../source/`: 시작/종료 manifest, 원본 69개 번들, 복호 mobDb/언어/스크립트 바이트.
- `monsters.raw.json`: 모든 정상 몬스터 레코드·액션·부위·모드·속성·드롭·원시 hex·참조. 보스 외 몬스터도 분석 원본에 보존한다.
- `delta.json`: 변종 키의 추가/삭제/실제 값·분류 변경, 언어 변경, 리소스 해시 변경. 오프셋·출처 증거 위치·컨테이너 SHA 변화만으로 같은 변종을 변경으로 세지 않는다.
- `report.json`, `latest.json`, `observed.json`: 검증 결과와 해시. ready만 latest를 진행시킨다. 실패 원본과 failure.json/needs-review 보고서를 보존한다.

현재 원본의 field 0/1/14001은 각각 드롭 수 누락·현재 형식 불일치·다른 field 헤더 참조다. 가짜 값을 채우지 않는다. 정확한 SHA·오류·크기를 계약에 고정해 격리하며 바뀐 예외나 새 실패는 검토 대상으로 차단한다. 이 3건을 정상/빈 몬스터 표로 세지 않는다.

스크립트 10맵의 마지막 EOF 슬롯과 레이드 표의 미연결 field 90960 기록도 별도 진단으로 보존한다. 잘못된 슬롯은 분류에 사용하지 않는다. 정확한 알려진 예외만 허용하며 새로운 오류는 발행을 차단한다.

코드·형식·참조·근거·중간 revision·변환 검증 실패 시 기존 latest와 개발판 manifest를 유지한다. source 및 project 모든 파일 해시를 검증한 후 hash 이름 자산을 먼저 복사하고 manifest를 마지막에 원자 교체한다. 동시 실행은 잠금으로 차단한다. 손상된 기존 파일을 같은 경로에 덮어쓰지 않는다.

## 앱 계약과 남은 연결

개발판은 `web/public/game-data/bosses/manifest.json`의 `toram.project-bosses.v1`을 읽는다. `ToramApp.bosses.search('기드론', 'kr')`, `ToramApp.bosses.get(540, 'us')`를 제공한다. 검색은 ID index/언어만, 상세는 ID 구간별 변종 파일만 지연 로딩한다. 하위 경로와 웹/앱 준비 도구에 포함되며 원본 자료는 배포하지 않는다.

도감의 `search('', locale, {classification})`는 분류를 선택했을 때만 변종 shard를 읽어 일치 개체가 있는 ID를 반환한다. 기본 검색의 지연 조회는 유지한다. `bossKind` URL은 입장/필드/고난도 선택을 보존하며 상세 개체도 해당 분류로 제한한다. 전체에서는 길드·던전·미분류도 원형대로 보존한다. 이벤트보스는 사용자 요청으로 카테고리 칸만 두고 기간·맵 연결은 보류한다.

앱 파일은 Boss 비트 4 레코드를 보존한다. 여기에는 부위·단계 변종도 있으며 서로 다른 독립 보스의 수가 아니다. `baseStats`는 네이티브 명칭과 원시 단위다. 변종마다 출처 SHA, 방 목록, 직렬화 출현점, 속성·부위·모드를 제공한다. `partStats`는 같은 필드의 부위 마스터를 연결하며 Boss 비트가 없는 부위의 DEF/MDEF와 보정 속성도 포함한다. 누락 참조는 stats:null이다.

분류는 변종별 `classification`·`classificationEvidence`와 `entry`로 전달한다. 필드는 정확한 mmo 출현점(`single`, 난이도 null), 입장은 BossMenu의 명시적 대상 맵/방(`difficulty-select`), 고난도 레이드는 HighRaidBossMaster의 ID 연결(`level-select`, BaseLevel/MinLevel 보존)이다. Dungeon 비트는 별도로 구분한다. 양성 근거가 없는 변종만 unresolved다. 다른 맵의 분류를 UUID만으로 복사하지 않는다. 상세 근거는 `boss-classification.md`에 있다.

## 타겟 UI·저장·기본 스탯

`스테이터스 > 타겟` 위에서 이름/ID와 여섯 언어로 검색하고 지역·개체/페이즈를 선택한다. 아래 기존 수동 입력은 유지한다. 필드 보스는 난이도 없이 단일 개체, 입장 보스는 Easy~Ultimate 선택, HighRaid는 최소 레벨 이상 정수 선택이다. 실제 서버 LevelLimit은 수집하지 않아 게임의 입장 최대치라고 표시하지 않는다. 32767은 HighRaid 입력의 signed short 표현 한계다. 길드 레이드는 아래 별도 현재 레벨 규칙을 쓴다. 미분류/Dungeon은 원본만 표시하고 계산 값은 유지한다.

`web/src/application/boss-target.mjs`는 출처로 확인한 정적 규칙만 사용한다. 일반 입장 DEF/MDEF는 본체와 각 부위를 별도로 float32 스케일·절삭한 뒤 합산한다. HighRaid는 별도의 레벨식과 첫 type32 고정 플래그를 적용한다. CutAttack/CutMagicAttack은 물리/마법 내성의 % 포인트이며 미파괴 부위의 type8 BodyCutCorrection을 더한다. 부위 원시 Cut를 합하는 식은 아니다. 기본 크리티컬 저항은 원본 순서의 첫 type6 Values[0], 속성이 없으면 0이다. UID를 단계 번호로 취급하지 않는다.

부위 합산은 **등록 부위 모두 미파괴인 정적 가정**이다. 실제 장면의 활성 부위·파괴·상태이상·버프·보석을 자동 시뮬레이션하지 않는다. 연결 누락 수치는 기존 수동 값을 유지하고 경고한다. 관성 변동률 세 종류는 %p로 표시하며 현재 관성 배율로 사용하지 않는다. 추가 정보에서 본체 HP/명중·원본 방어/내성·가드/회피·속성 코드·버전을 볼 수 있다.

선택은 `scenario.bossSelection?`의 `toram.boss-selection.v1`로 ID·revision·변종 원본·난이도·레벨을 고정한다. 실제 계산에는 기존 `scenario.target` 여섯 숫자만 전달한다. JSON/세션 복원은 최신 카탈로그를 다시 읽거나 원본으로 덮어쓰지 않으므로 수동 수정도 보존한다. 원본을 갱신하려면 검색에서 다시 선택한다. 연결 해제도 현재 숫자를 유지한다. 기존 선택 필드 없는 v2 문서는 그대로 읽는다.

검증은 `npm run bosses:test`의 파서/변환/부위/반올림/레벨/예외 플래그와 `npm run verify:web:browser`의 필드·입장·고난도 선택, 수동 수정, JSON/재열기, 모바일 폭으로 나뉜다. 보존된 함수는 게임 실행 관측이 아닌 정적 근거다.

## 길드 레이드

여섯 종류는 `guild-raid-bosses.json`의 검토한 UUID·필드/방·로컬 ID·모델·속성을 기준으로 연결한다. 사용자 제공 분류를 실제 다국어/마스터에 대조한 목록이며 추출한 GuildRaidBossMaster라고 주장하지 않는다. 실제 필드/방·MobList·랜덤 옵션은 서버 이벤트가 선택한다. 원본 38개 BynaryData TextAsset 목록과 조사 경계는 `native-guildraid-links/README.md`에 있다.

주요 본체만 anchor로 삼고 같은 정체성의 명시적 mode 참조로 후속 페이즈를 연결한다. 같은 필드에 있는 추가 몬스터를 이름/단순 Boss 비트로 주요 보스에 합치지 않는다. UUID1195 소테리아는 `100500:1→101` 남자/마법 방어형, `100500:2→102` 여자/물리 방어형으로 구분한다. 성별 라벨은 사용자 설명과 DEF/MDEF·모델을 대조한 UI 식별이며 게임 성별 필드가 아니다. anchor·모델·속성·참조가 바뀌면 기존 latest/manifest를 유지하고 검토 대상으로 격리한다.

`guild-raid-boss`는 `entry.model=level-select`를 사용하되 HighRaid 식과 분리한다. 현재 레벨은 `max(40,남은 HP 게이지 byte*4)`다. UI의 40~1020·4단위는 byte 표현 범위이며 서버 입장 한계가 아니다. 원본 level100은 실제 전투 레벨로 고정하지 않는다. 소테리아의 개체/페이즈를 전환할 때 같은 필드의 선택 레벨을 유지하고, actor·레벨·원본을 저장한다.

- DEF/MDEF는 `trunc(f32(i32(raw*Level))*f32(0.01))`이다. 정수 곱셈을 먼저 하므로 HighRaid와 절삭 결과가 다를 수 있다.
- 내성은 `rawCut+trunc(Level/10)`이며 기본 크리티컬 저항은 원본 첫 type6이다. 서버 randomProperty/type40, 버프/상태이상은 제외한 기본값임을 UI에 표시한다.
- HP는 별도 게이지를 쓴다. Lv44 이상은 게이지=Level/4로 역산해 native 순서대로 계산한다. Lv40은 게이지0~10이 겹쳐 미확정이며 Lv528 이상에서 signed int32를 넘는 HP도 양의 수로 확장하지 않는다. 정확 식과 256개 byte 반올림 검사는 `native-guildraid-target/report.json`·`self-check.py`에 있다.
- 현재 여섯 계열 본체에는 부위가 없다. 미래 부위가 추가되면 방 난이도 근거가 확보될 때까지 DEF/MDEF·내성 자동값을 보류하며 HighRaid 부위식을 대신 쓰지 않는다.

클리어 후 다음 최대 게이지/레이드 레벨은 서버 자료다. 클라이언트에서 확인한 현재 레벨별 스탯식과 성공 횟수별 증가량을 구분하며 미확인 증가량을 고정값으로 만들지 않는다. 검증에는 6종 기본값, 소테리아 두 개체/페이즈, 레벨 변경/범위, 수동 수정·JSON 복원과 기존 보스 회귀를 포함한다.

Coryn의 공개 API는 독립 참고 출처다. `coryn-reference.md`에 예시 5개/18개 응답의 종류·맵·난이도와 한계를 기록했다. Coryn 숫자 ID를 게임 ID로 승격하지 않는다.

## 2026-10-22 실제 업데이트 재검증

- releaseB는 이전 원본을 제공했고 releaseC에서 1,172 MapInfo·정상 몬스터9,238변종·ID1,298개를 추출했다. 이전 releaseB ready 원본과의 별도 의미 비교는 추가32·변경29·삭제0이다. releaseC의 첫 ready 전에는 같은 분기의 기준 포인터가 없으므로 원본 report의 added=9,238과 이 교차분기 비교를 혼동하지 않는다. 원본 번들/언어는 분기별로 분리한다.
- 블랑은 UUID1314, key107602:1000의 field-boss/single로 기존 MMO 출현점 근거에 연결된다. Lv320·DEF/MDEF1280·물리/마법 내성12가 원본이다. 새 보스 변종13개 중 블랑1개가 field-boss이며 나머지12개는 양성 입장 근거가 없는 unresolved로 유지한다. 새 의미를 이름이나 Boss 비트만으로 채우지 않았다.
- 설치 코드 변경 needs-review를 먼저 확인한 뒤 사용자 동의의 읽기 전용 모듈 보존본으로 보스221함수를 대조했다. Toram.Common 난이도 함수10개를 포함하며 난이도 초기화 배열10개×20바이트와 고난도/길드 상수15건을 원문에서 대조했다. 원본 추출·분류·정적 타겟 계산의 신규 의미 변경을 발견하지 못했다. [검토 보고서](../../data/sources/toram-monsters/native-update-20261022/README.md)·index/C/상수/재현 도구를 기존 근거와 함께 해시632개로 고정한 뒤 계약을 갱신했다.
- sync의 `--check`는 발행하지 않는다. 설치 불일치를 update-available/0으로 반환하던 Python 검사를 needs-review/2로 고쳤고 wrapper의 실패·비JSON/비정상 성공 종료도1로 전달한다. Python self-test10/10, bosses:test 통과.
- 공개분기·교차분기 의미 비교·최종 검토 자료는 `build/tmp/update-pipeline-20261022/`, 원본 이력은 `data/sources/toram-monsters/pipeline/releaseC/`에 보존한다. 이 폴더들은 Git 제외이므로 별도 백업한다.

10/22 발행 검증: `npm run bosses:sync`는 development-updated/developmentApplied=true,691ID/5,209변종이었다. 같은 날짜의 `--check`·재실행은 unchanged였다. `bosses:test`·Python10/10·architecture·S1 427/427·회귀71/71(저장E2E1SKIP)·Edge 데이터/JSON/재열기 검증은 [아이템 갱신 검증](toram-item-pipeline.md)에 보존한다. 현재 판정은 handoff와 아래 후속 검증을 따른다.

## 2026-10-23 퀘스트 분기 뒤 입장 메뉴

사용자가 콜론 보스/조성중 지구의 실제 입장 방식을 알려 주어 원본을 대조했다.3300:10/UUID41의 이벤트10 시작 명령은 ProgressQuest38이며 Check20 뒤5719 위치에서 BossMenu130이 field3300/room0을 가리킨다. 이벤트 첫 명령만 보던 파이프라인 범위의 누락이었다. 보존된 코드와 metadata만으로 추가 분석했으며 게임 실행/프로세스 추가 접근은 없었다.

version16의 검토한 ProgressQuest/Check와 정수 operand만 따라가도록 보완했다. Check 양 분기는 가능한 출처 경로로 읽으며 실제 퀘스트 해금/현재 상태는 확정하지 않는다. 동적 operand·미검토 명령에서 멈추고 잘린 입력·분기 범위·순환 방문을 검사한다. native 근거/스크립트 fixture/재현 Java/metadata enum을 `native-entry-flow/`에 해시 고정했다. 이 근거 없이 다른 UUID/맵에 분류를 복사하지 않는다.

전체 보존 스크립트에서 추가 메뉴 경로40개를 찾아 기존 미분류65변종을 entry-boss로 연결했다.691ID/5,209변종은 그대로이며 분류는 entry851·field117·high-raid133·dungeon26·guild9·unresolved4073이다. 콜론 보스3300:10은 difficulty-select,4500:100은 기존 field/single을 유지한다. 다른 미연결 경로는 여전히 남으며 모르는 명령을 임의 건너뛰지 않는다.

오프라인 sync와 재실행 unchanged, `bosses:test`·Python11/11 통과. Edge 소스/하위경로에서 콜론 보스 조성중 지구의 일반/Ultimate 난이도와 DEF7/42를 확인했다. 크리스타 ID 통합과 함께 수행한 검증/전체 성능 Gate 미통과는 [검증 기록](crysta-id-catalog.md)에 있다. 로그 `build/tmp/boss-colon-menu/`.
