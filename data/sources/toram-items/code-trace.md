# 아이템 로더·옵션 표시 코드 확인

조사일: 2026-10-17. 사용자가 실행한 ToramOnline 프로세스의 **GameAssembly 모듈만 읽기 전용으로 복사**하고 저장한 사본을 분석했다. 게임에 코드를 주입하거나 값을 쓰지 않았다. 앱 계산 데이터에는 적용하지 않았다.

후속 조사에서 조건 배열·표시 상수의 제한된 읽기와 6언어·특수 옵션·연관 표 연결을 완료했다. 아래는 최초 로더/배율 분석 기록이며, 현재 완료 범위와 후속 검증은 [item-connections.md](item-connections.md), [item-localization.md](item-localization.md)를 따른다.

## 결과

- [items.kr.77596232.json](items.kr.77596232.json): 실행 후 새로 생성된 캐시에서 마스터 **11,723개**, 옵션 레코드 **4,460개**, 한국어 텍스트 **22,530행**을 다시 추출했다. 이름 연결 11,631개, 이름 누락 92개, 이름·설명 모두 누락 13개다. 이 캐시가 실제 활성 객체의 버전인지는 관측하지 않았다.
- [option-display-rules.json](option-display-rules.json): 네이티브 초기화 코드에서 읽은 배율 24개와 기본 배율 1.
- [item-options.scaled.kr.77596232.json](item-options.scaled.kr.77596232.json): 원본 수치를 유지하면서 **18,439개 옵션**에 표시 함수 입력용 float32 수치를 추가했다. 최종 UI 문자열이나 전투 계산 결과는 아니다.
- [cache-version-comparison.json](cache-version-comparison.json): 이전 e8e43f32와 비교. ID 90015/91015/92015/93015/94015 추가, 삭제 0, 기존 마스터 필드 값 변경 0, 텍스트 변경 0. ID 8920(★홍시 코린 숲)의 첫 옵션 `244/item_warp` 값은 980 → 0이다. cap ID가 0인데 값이 980인 뒤 슬롯 두 개도 원형 보존했다.

## 문자열과 실제 아이템 데이터의 관계

이름을 검색하는 접근은 유효하다. 다만 실제 구조는 이름을 키로 삼은 하나의 객체가 아니라 **정수 아이템 ID로 결합하는 데이터와 언어별 텍스트**다.

```text
ItemMaster → MasterItemDataManager.ReadItemData → ItemDBData (Id 등)
ItemProperties → ReadItemProperty → 같은 Id의 ItemDBData.capId[10], capVal[10]
Item_kr → ItemTextManager.Initialize → Id → TextManagerDataBase(이름, 설명)
ItemProperty_kr → ItemPropertyTextManager.Initialize → 옵션 ID → 문구
capId/capVal → UIItemProperty.AddCapProperty → 배율 적용 → 문구 포맷
```

`ItemTextManager.Initialize`는 count 뒤에 `(ReadInt32 ID, ReadByte kind, ReadString)`을 읽는다. kind 0은 이름, 1은 설명용 임시 표에 저장하고 같은 ID의 `TextManagerDataBase(name, description)`를 만든다. 설명에는 문자열 치환과 UI 쪽 후처리도 있다. 이름·설명을 저장한 텍스트와 화면에서 최종 조립한 모든 문장이 동일하다고 일반화할 수 없다.

`ItemPropertyTextManager.Initialize`는 `(ReadInt32 옵션 ID, ReadString 문구)`를 읽는다. 따라서 `최대 HP+{0}`와 같은 옵션 문구는 완성된 아이템 옵션 문자열이 아니다. 언어가 달라져도 이 정수 ID 연결이 핵심이다. 확보된 아이템 언어는 여전히 **kr만**이며 Coryn 사이트 ID와 게임 ID의 동일성은 확인하지 않았다.

## 로더에서 확인한 레코드 구조

`ItemDBData.CreateItemData`의 실제 판독 순서와 저장 위치다. `type_id`는 디스크에서는 i32로 읽고 객체에는 하위 i16을 저장한다. 객체 오프셋과 파일 오프셋은 서로 다르다.

| 필드 | 레코드 내 오프셋·판독 | 객체 내 오프셋 |
| --- | --- | --- |
| id | 0 / i32 | 0x28 |
| sort_id | 4 / i32 | 0x2c |
| type_id | 8 / i32 → i16 | 0x30 |
| price | 12 / i32 | 0x34 |
| material_level, material_id | 16, 17 / u8 | 0x38, 0x39 |
| process, stack, function | 18, 20, 22 / i16 | 0x3a, 0x3c, 0x3e |
| stability, range_raw, slot_max_raw | 24, 25, 26 / u8 | 0x40, 0x41, 0x42 |
| potential | 27 / i16 | 0x4c |
| model | 29 / i32 | 0x48 |
| flag_raw | 33 / i32 비트 보존 | 0x44 |

합계 **37바이트**다. `ReadItemProperty`는 count와 i32 아이템 ID를 읽고 마스터 표에서 그 ID를 찾은 뒤 `SetItemDataProperty`를 호출한다. 이 함수는 정확히 10회 `(ReadInt16 capId, ReadInt16 capVal)`을 읽는다. ID를 포함하면 **44바이트**다. cap ID가 양수인 쌍만 bonusLines에도 추가하며 로딩 시 표시 배율을 적용하지 않는다.

판독 함수 식별은 메타데이터의 BinaryReader 가상 슬롯과 호출 오프셋으로 확인했다. IL2CPP vtable 시작 0x138 기준 슬롯 10/13/15/22가 각각 ReadByte/ReadInt16/ReadInt32/ReadString이고 코드의 0x1d8/0x208/0x228/0x298과 일치한다. 문자열 포맷·치환 호출은 mscorlib의 네이티브 메서드 포인터를 대조해 `System.String.Format`·`Replace`로 식별했다.

## 실제 옵션 숫자 배율

`BonusManager.GetBonusTime`은 `BonusTimes`를 먼저 조회하고, 없으면 `AvatarBonusTimes`, 두 표에 모두 없으면 **1.0f**를 반환한다. `UIItemProperty.AddCapProperty`는 `float32(raw signed i16) × 배율`을 계산한다.

| cap ID / enum | 배율 |
| --- | --- |
| 12 bMaxHpTo10, 110 bMaxMpTo10 | ×10 |
| 137 bSelfDmgRate, 140 bItemDelay | ×0.01 |
| 166~175 bStrToAtk … bDexToMAtk | ×0.1 |
| 190 bGemDropFixing | ×0.1 |
| 184~187 bAvatarAspd/Cspd/Hp/Mp | ×10 |
| 180~183, 188 및 나머지 ID | ×1 |

0.1f/0.01f의 실제 IEEE754 상수는 각각 `cd cc cc 3d` / `0a d7 23 3c`다. JSON에는 원본 상수 바이트·RVA와 정확한 float32 값을 같이 저장했다. 이 규칙은 **표시용 숫자 환산**이며 저항·공격력의 최종 계산식, 적용 순서, 상한을 증명하지 않는다.

G이코노스(ID 9911)의 확인 예:

| 옵션 | 원본 | 배율 | 문구에 전달되는 숫자 | 단순 문구 결과 |
| --- | --- | --- | --- | --- |
| 12 / bMaxHpTo10 | 100 | 10 | 1000 | 최대 HP+1000 |
| 124 / bMoveAttackResist | 10 | 1 | 10 | 돌진경감+10% |

기존 계산기 자료의 `CHARGE_RED=1`을 이 원본의 정확한 동치라고 판정할 근거는 없다. 현재 작업에서는 기존 값을 수정하지 않았다.

숫자만 환산하면 끝나는 것도 아니다.

- ID 48, 166~175, 188은 음수일 때 음수 ID의 문구를 먼저 찾는 분기가 있다. 있으면 부호를 뒤집은 숫자를 넘기고 없으면 양수 ID 문구로 되돌아간다.
- ID 65(속성), 189(아바타 스킬)는 별도 객체/관리자를 이용한다. 일반 숫자 문구로 재현하지 않았다.
- `GetItemPropertysTextData`는 10개 슬롯을 순서대로 순회하고 장비 조건 옵션을 판정해 뒤 옵션의 표시 그룹·색상·줄바꿈을 바꾼다. 최초 모듈 사본에는 limitList 배열이 없었으나 후속 확인에서 `[96,103,108,109,115,120]`과 메타데이터 초기값 해시를 검증했다.
- 일반 분기의 음수 문구 치환·색상, 언어별 Single 포맷, 설명의 태그 처리까지 화면과 대조하지 않았다. 따라서 sidecar는 `formattedTextVerified=false`다. 일반 문구 16,673개, 부호별 문구 분기 209개, 별도 컨텍스트 708개, 문구 없음 849개로 분류했다. 모든 아이템 종류가 이 표시 함수를 거친다는 뜻은 아니다.

## 복호화 코드와 근거의 버전

`ResourceManager.AssetDecrypt` 본문은 완전한 4바이트 단어를 **뒤에서 앞으로** 순회한다. big-endian으로 묶은 현재 암호문·이전 암호문·int key를 XOR하고 다시 big-endian으로 쓴다. 첫 단어의 이전 값은 0, 마지막 0~3바이트는 그대로 둔다. 기존 오프라인 디코더의 cipher 피드백 구조와 부합한다. 캐시 폴더 키에서 실제 호출 인자 key를 만드는 전체 경로는 추적하지 않았으므로 byte-order 변환까지 코드로 확정한 것으로 표현하지 않는다. 두 캐시는 기존 디코더로 전체 UTF-8·EOF·ID 검사를 통과했다.

게임 실행 과정에서 설치 파일도 갱신됐다. 이전 정적 메타데이터와 현재 코드를 섞지 않았다. 옵션 enum의 432개 ID·이름은 두 메타데이터에서 모두 일치한다.

| 근거 | SHA256 |
| --- | --- |
| 현재 설치 GameAssembly.dll | a3faf7156734768a3ff7349d4b94de029b68b823d974bf52f92bbc77f93f46dd |
| 현재 global-metadata.dat | f0cf212a7c7dca1973a401bda6d208549c13f57f0bbdb8782e5d607ed7e8789f |
| 읽은 모듈 이미지 | 2baf9dd6ad9f2a32f211c1f97a7ad0b94bf778d689afb054047f9ab621fd370e |
| 오프라인 분석용 재구성 PE | 013f5d1668b857820490a9e7f49b716a41eaa2aec1b4c1a449d12ec38a4d7fa0 |

모듈의 실제 base는 `0x7fff5f250000`, 크기는 83,230,720바이트이며 읽지 못한 페이지는 0이다. 순차 캡처이므로 원자적 스냅샷은 아니다. 후속 조사에서는 검토한 고정 참조를 따라 조건 배열과 표시·공개 리소스 경로 상수만 제한적으로 읽었다. 인벤토리 객체는 읽지 않았다. 원본 모듈 사본은 Git 제외 임시 폴더에만 보존했다.

Assembly-CSharp의 CodeGenModule을 찾아 **75,881개 메서드 포인터 수 = 메타데이터 메서드 수 = 최대 token RID**, RID 연속성을 검증하고 `RID - 1` 슬롯으로 네이티브 주소를 연결했다. 주요 RVA는 다음과 같다.

| 메서드 | RVA |
| --- | --- |
| ItemDBData.CreateItemData / SetItemDataProperty | 0xe24050 / 0xe24300 |
| MasterItemDataManager.ReadItemData / ReadItemProperty | 0xe34ca0 / 0xe350c0 |
| ItemTextManager.Initialize / ItemPropertyTextManager.Initialize | 0x308950 / 0x307570 |
| BonusManager.GetBonusTime / .cctor | 0xda5e00 / 0xda8f60 |
| UIItemProperty.AddCapProperty(전체 인자) | 0x782b20 |
| UIItemProperty.GetItemPropertysTextData / ItemText | 0x7846e0 / 0x785c40 |
| ResourceManager.AssetDecrypt | 0x38df90 |

Ghidra 12.1.4로 저장된 PE의 선택 함수 22개를 분석했다. 메타데이터의 static/instance·기본 타입·반환형을 적용했으며 참조 타입은 opaque pointer다. 생성된 C는 원래 C# 소스가 아닌 **네이티브 의사코드**다. [native-trace/](native-trace/)에 보존했으며 해시·선언·토큰·RVA는 [native-verification.json](native-verification.json)에 있다. 전체 자동 분석 중단 결과와 최초 잘못 추론된 반환형의 출력은 근거에 사용하지 않았다.

REA로 최초 PE 식별·정적 관측을 수행했다. 이번 선택 함수 결과는 Ghidra를 직접 사용한 결과이므로 REA Evidence ID를 새로 붙이지 않았다.

## 재현·검증

도구는 `tools/extraction/`의 `snapshot-toram-module.py`, `map-il2cpp-methods.py`, `extract-toram-option-display.py`, `ghidra/TraceToramItemFunctions.java`다. 프로세스를 다시 읽지 않아도 보존한 사본으로 주소 연결·표시 수치를 재생성할 수 있다. 표시 배율 추출기는 검토한 이미지·초기화 의사코드 해시만 허용한다. 새 버전은 코드 재검토가 필요하다.

```powershell
python tools/extraction/extract-toram-item-assets.py --version 77596232 --output build/tmp/toram-item-extraction/새폴더 --unitypy-path build/tmp/toram-item-extraction/python-deps
python tools/extraction/extract-toram-option-display.py --runtime build/tmp/toram-item-extraction/code-trace/runtime --catalog assets/source-data/toram-items/items.kr.77596232.json --output build/tmp/toram-item-extraction/새표시결과
```

추출기 self-test, 새 캐시 전체 레코드·UTF-8·EOF·조인 검사, 원문 해시, 네이티브 포인터 수·토큰 검증, float32 경계 검사를 실행했다. 장비 강화·ASPD/CSPD/ATK/서브 안정률의 최종 계산식, 다른 언어, 화면과의 최종 문자열 대조는 이번 완료 범위에 포함하지 않았다.
