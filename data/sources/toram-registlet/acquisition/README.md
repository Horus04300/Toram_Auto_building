# 레지스트렛 획득처

`stages.json`은 releaseC 엘 스카로의 스투디의 실험16단계와, 사용자가 연 보상 창에서 읽은 D/C/B/A/S 후보 목록을 연결한다. Lv10/30/50/70/90/110/130/150/170/190/210/220/230/250/270/290의 목적지 필드·방 ID·6언어 이름과 원본 명령 offset을 보존한다.

166종 중163종은 레벨/상자가 연결됐다. 1040(루나 디재스터·절약)·1046(디코이 슈터·유도)·1054(신속의 호수)는 이16개 목록에 없으므로 획득처를 추정하지 않는다. 목록에는 개별 확률이 없으며 `dropProbability=null`이다. 후보 개수를 균등 확률로 바꾸지 않는다. 실제 보상 추첨·계정별 입장 가능 여부·향후 서버 목록은 별개다.

## 연결 근거

- `41464.c`: 메뉴 opcode217/version8의 fieldId/roomId/level 인자 순서. 각 명령은 앞 Check의 true target과 일치하며 뒤에 End가 있다.
- `54212.c`: 목적지로 GameManager.CheckTreasureHuntRoom을 요청하고 현재 방과 연결한다.
- `extra/95996.c`, `43938.c`, `22060.c`: 응답 ItemData(+0x40)를 방 itemData(+0xe0)에 저장한다.
- `ui/54214.c`, `54233.c`, `extra/91211.c` 등: UI(+0x198)와 D/C/B/A/S 배열(+0x20/28/30/38/40) 연결.
- `54234.c`, `54238.c`: 배열 길이(+0x18)/포인터(+0x20), RewardData.type(+0x20)/value(+0x24). type23은 젬,24는 분말이다. 젬 ID는 네이티브 코드의 하위16비트 투영을 따르고 rawValue도 보존한다.
- `runtime-root/singleton-get-instance.c`: 고정 method context→generic context→static_fields→RoomManager.instance. `runtime-root/field-offset-witnesses.json`은 방 fieldId(+0x38)/roomId(+0x3c)의 실제 getter 바이트·메타데이터 토큰이다.

## 실행 중 목록 읽기

`capture-reward-list.py`는 이미 실행 중인 ToramOnline의 모듈/메타데이터 SHA와 응답 처리 코드, 객체 타입을 검사한 뒤 위 고정 경로만 읽는다. 배열당256개·캡처당64KiB 상한, 마지막 방/목록/필드 포인터 안정성 검사를 적용한다.16번의 실제 캡처 합계는44,592바이트다. 원문 범위/주소/바이트·시각·해시는 `captures/` 및 `stages.json.captureSources`에 있다.

게임 함수 호출·주입·쓰기·임의 힙 검색·플레이어/계정/인벤토리 읽기는 하지 않는다. 사용자가 보상 창만 열었으며 입장·전투·구매는 실행하지 않았다. 샌드박스 안에서는 실제 프로세스가 보이지 않아 승인된 동일 읽기를 제한 밖에서 실행했다. 순차 읽기이며 원자적 스냅샷은 아니다.

```powershell
python data/sources/toram-registlet/acquisition/capture-reward-list.py --self-test
python data/sources/toram-registlet/acquisition/capture-reward-list.py --pid <실행중PID> --output <새파일.json>
python data/sources/toram-registlet/acquisition/extract-acquisition.py --self-test
python data/sources/toram-registlet/acquisition/extract-acquisition.py --check
```

`extract-acquisition.py`는 게임에 접근하지 않는다. 보존한 원문/함수 해시·분기/EOF·6언어 이름을 검사하고 캡처의 raw field/배열 개수/루트 안정성/버전과 rankPools를 재대조해 재생성한다. 다른 캡처가 같은 레벨의 목록과 충돌하면 덮어쓰지 않고 실패한다.

## 정적 재현

입력 PE는 `build/tmp/update-pipeline-20261022/snapshot/GameAssembly.snapshot.dll`(SHA25649cce5c641aa2077c0395f24640f87ec9925d8919bbfb137638d65b7c6e8eb0d), metadata는 c5cb57c13fb2f4ba9258b8cf155ee866a8f67eee30f32d043e1fd854bba2eec9다. 공개 script/FieldName 원본은 보존된 toram-monsters releaseC 스냅샷에서 복사했다. `inputs.json`은44개 정적 입력, 공통 `../provenance.json`은 캡처를 포함한 근거를 고정한다.

Ghidra12.1.4 직접 scoped headless로 `method-map.json`, `extra-map.json`, `ui-map.json`을 각각 TraceToramAcquisition.java에 전달한다. `-noanalysis -postScript`이며 JVM settings/cache/temp/project는 새 build/tmp 경로로 한정한다. REA 경로가 설정되지 않아 기존 직접 실행을 재사용했으며 retained REA Evidence ID는 없다.
