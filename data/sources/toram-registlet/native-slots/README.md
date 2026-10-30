# 레지스트렛 슬롯 확장 근거

2026-10-29. 보존된 2026-10-22 GameAssembly 모듈과 대응 메타데이터의 선택 함수 15개를 Ghidra 12.1.4로 분석하고, 사용자가 실행한 게임의 고정 초기화 참조 129바이트를 읽어 비용 배열을 연결했다. 에이전트가 게임을 실행하거나 함수를 호출하거나 게임 파일을 수정하지 않았다. REA의 Ghidra 경로가 설정되지 않아 기존 저장소 방식대로 직접 scoped headless를 사용했으며 retained REA Evidence ID는 없다.

## 확인된 규칙

- `RegistletManager..cctor`(메서드 20115)는 `GemPowderLimit=999999999`, `SlotLimit=10`을 설정한다. `SetEquipList`(65873)는 현재 슬롯 수가 10보다 작을 때만 확장 버튼을 만든다.
- `RegistletManager..ctor`(20100)는 9개 Int32 배열을 만들고 `RuntimeHelpers.InitializeArray`로 `NeedGemPowder`를 채워 인스턴스 `+0x30`에 보관한다.
- `CreateEquipGemButton`(65874)과 `OnClickAddSlotButton`(65881)은 비용을 `NeedGemPowder[현재 슬롯 수 - 1]`로 읽는다. 전자는 보유 분말이 비용 이상일 때 버튼의 가능 상태를 설정하고, 후자는 비용·현재 분말·차감 후 분말을 표시한다. 따라서 배열 원소 0~8은 슬롯 `1→2`부터 `9→10`까지의 단계 비용이다.
- `ExtensionSlot`(20107)은 응답으로 받은 분말과 슬롯 수를 저장한다. 이 함수가 로컬에서 위 비용을 차감하거나 새 슬롯 수를 계산하지는 않는다.
- `Initialize`(20101)는 전달받은 `RegistletData`의 `Slot`(객체 `+0x21`)을 장착 가방에 넣는다. 신규 계정의 초기 슬롯 수는 이번 클라이언트 정적 근거로 확정하지 않았다. `RegistletData` 생성자의 `+0x18=1`은 슬롯 필드가 아니므로 초기 1슬롯의 증거로 쓰지 않는다.

현재 결과는 [slot-rules.json](slot-rules.json), 선언·토큰·주소는 [metadata.json](metadata.json) 및 [method-map.json](method-map.json), 디컴파일 결과와 SHA-256은 `pseudocode/`에 있다.

## 확장 비용

| 현재 → 확장 후 슬롯 | 필요한 분말 | 1슬롯부터 누적 |
| --- | ---: | ---: |
| 1 → 2 | 100 | 100 |
| 2 → 3 | 400 | 500 |
| 3 → 4 | 2,000 | 2,500 |
| 4 → 5 | 7,000 | 9,500 |
| 5 → 6 | 30,000 | 39,500 |
| 6 → 7 | 200,000 | 239,500 |
| 7 → 8 | 500,000 | 739,500 |
| 8 → 9 | 2,000,000 | 2,739,500 |
| 9 → 10 | 7,000,000 | 9,739,500 |

[JSON](slot-rules.json)과 [CSV](slot-expansion-costs.csv)에 동일한 단계 비용을 보존했다. 이는 클라이언트가 저장한 표이며, 일정한 증가율의 단일 수식으로 근사하지 않는다. 누적 비용은 원소 합이다. 10슬롯에는 다음 확장 단계가 없다.

스냅샷의 초기화 필드 참조 VA `0x7ffe9c930e10`(RVA `0x31f0e10`)은 이미 힙의 `FieldInfo` 주소로 해석되어 있었고, 모듈만 보존되어 해당 힙 구조가 없었다. 설치 DLL의 이 RVA도 원본 파일에 바이트가 없는 packed 가상 영역이다. 따라서 실행 중인 게임에서 같은 상대 참조를 읽어 필드를 연결했다. 샌드박스 내부 프로세스 열거는 게임을 보여주지 않아, 사용자 실행 확인 후 샌드박스 밖의 읽기 전용 추출로 확인했다.

[initializer-capture.json](initializer-capture.json)은 다음 일치를 보존한다.

- 설치 DLL SHA-256 `c0f666aa071136bfae7ada61135ba01fc2907c3987945a86cce5909c6011fbff`와 메타데이터 SHA-256 `c5cb57c13fb2f4ba9258b8cf155ee866a8f67eee30f32d043e1fd854bba2eec9`.
- 현재 모듈의 생성자 첫 24바이트와 정적 분석 입력의 동일성.
- `FieldInfo` 토큰 `0x0400d409`, 메타데이터 필드 인덱스 54280, 컴파일러 필드 이름 `36E3BC65CDC0D0B6096AFEB3920791878FAA471FB3B14D041D7CF8E6D4324052`.
- 메타데이터 offset 9,739,968의 36바이트와 위 필드 이름(SHA-256)의 일치.

사용자가 별도로 확인한 게임 화면의 500,000분말 표시도 위 표의 7→8단계와 일치한다. 비용표는 이 화면 값으로 추정하지 않고 초기화 필드 원문으로 확정했다. 비교했던 미연결 원문 후보는 `metadata-candidate-evidence.json`에 보존하며 현재 규칙표와 구분한다.

[capture-constants.py](capture-constants.py)는 게임이 이미 실행 중일 때만 지정 PID의 고정 `FieldInfo`와 64자리 컴파일러 필드 이름을 읽는다. 총 129바이트(생성자 코드 24, 참조 8, FieldInfo 32, 이름 65)를 넘지 않고, 모듈/메타데이터 SHA·생성자 바이트·필드 토큰·배열 SHA를 대조한다. 인벤토리·계정·캐릭터 상태는 읽지 않으며 프로세스를 실행하거나 수정하지 않는다.

```powershell
python data/sources/toram-registlet/native-slots/capture-constants.py --self-test
python data/sources/toram-registlet/native-slots/capture-constants.py --pid <실행중인게임PID> --output <새출력파일.json>
python data/sources/toram-registlet/native-slots/self-check.py
```

## 정적 분석 재현

`TraceToramRegistletSlots.java`는 `method-map.json`의 PE SHA-256·image base를 검사하고 선택 함수만 분석한다. 입력은 `build/tmp/update-pipeline-20261022/snapshot/GameAssembly.snapshot.dll`이며 원본 해시는 `slot-rules.json.sources`에 있다. 자동 전체 분석을 하지 않는다.

```text
java -Djava.system.class.loader=ghidra.GhidraClassLoader
  -Dapplication.settingsdir=<작업폴더/settings>
  -Dapplication.cachedir=<작업폴더/cache>
  -Djava.io.tmpdir=<작업폴더/temp>
  -cp C:/Tools/Ghidra/ghidra/Framework/Utility/lib/Utility.jar
  ghidra.Ghidra ghidra.app.util.headless.AnalyzeHeadless
  <작업폴더/project> slots -import <입력PE> -noanalysis
  -scriptPath <이폴더> -postScript TraceToramRegistletSlots.java
  <method-map.json절대경로> <새출력폴더> -deleteProject
```

직접 `java`를 사용하는 이유는 Ghidra 배치 런처의 JDK 탐색 단계가 별도 사용자 설정 폴더에 `java_home.save`를 쓰기 때문이다. 위 실행은 설정·캐시·임시 파일을 작업 폴더로 제한한다.

이 결과는 클라이언트의 표시·응답 적용 규칙이다. 실제 서버의 확장 실행 결과와 초기 계정 상태는 별도 검증이다.
