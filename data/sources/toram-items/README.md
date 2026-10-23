# 게임 아이템 추출 기록

조사일: 2026-10-17. 최초 설치 파일·캐시 추출 후 사용자의 동의로 실행 중 GameAssembly 모듈을 읽기 전용으로 확보해 로더와 표시 배율을 확인했다. 앱 계산 데이터에 적용하거나 배포하지 않았다.

**현재 통합 결과는 [items.77596232.connected.json](items.77596232.connected.json)과 [연결 완료 기록](item-connections.md)**이다. 마스터 11,723개·옵션 18,439개에 한국어·영어·일본어·중문 번체·인도네시아어·태국어 원문, 조건부 옵션 범위, 속성·아바타 스킬, 장비 분류와 레시피 참조를 연결했다. 원본 한국어 카탈로그와 표시 배율 sidecar도 보존했다. 아래 e8e43f32 수치는 최초 오프라인 추출의 기록이다.

## 결과 파일

| 파일 | 내용 |
| --- | --- |
| [items.77596232.connected.json](items.77596232.connected.json) | 원본 필드·슬롯을 보존한 현재 6언어 통합 카탈로그 |
| [item-connections.md](item-connections.md) | 연결 구조·검증 결과·미해석 필드·재현 방법 |
| [item-localization-links.json](item-localization-links.json) / [기록](item-localization.md) | 같은 master/property 본문에 연결된 6언어 텍스트 |
| [item-relations.json](item-relations.json) / [기록](item-relations.md) | 레시피·랜덤 옵션·제작 보조·모델 표와 참조의 의미 |
| [item-classification-rules.json](item-classification-rules.json) | 실제 네이티브 장비 분류·기본 슬롯·아바타 범주 |
| [item-reference-audit.json](item-reference-audit.json) | 이름 누락·enum·알 수 없는 flag 감사 |
| [item-special-references.json](item-special-references.json) | 속성·아바타 스킬의 코드 기반 연결 |
| [crysta-link-audit.json](crysta-link-audit.json) | 기존 크리스타와의 후보 비교. 게임 객체 동일성 확정 자료는 아님 |
| [current-artifacts.json](current-artifacts.json) | 현재 보존 파일의 크기·SHA256 |
| [items.kr.77596232.json](items.kr.77596232.json) | 게임 실행 후 새 캐시에서 다시 추출한 현재 카탈로그 |
| [code-trace.md](code-trace.md) | 실제 로더·옵션 배율·문자열 조립 경로와 검증 경계 |
| [option-display-rules.json](option-display-rules.json) | 코드에서 확인한 기본 배율 1과 예외 24개 |
| [item-options.scaled.kr.77596232.json](item-options.scaled.kr.77596232.json) | 원본과 float32 표시 입력 수치를 함께 보존한 옵션 sidecar |
| [items.kr.e8e43f32.json](items.kr.e8e43f32.json) | 실제 게임 ID로 결합한 마스터·한국어 이름/설명·원본 옵션·옵션 enum 이름 |
| [game-extraction-manifest.json](game-extraction-manifest.json) | 캐시 24개 번들에서 추출한 137개 TextAsset의 원문/변환 후 SHA256·경로·버전 키 |
| [coryn-items.json](coryn-items.json) | Coryn 영어 목록 8,448개. 사이트 ID를 별도로 보존하며 gameItemId는 null |
| [coryn-manifest.json](coryn-manifest.json) | 공개 API/문서/표본 90개 응답의 URL·시각·해시 |
| [existing-crysta-name-candidates.json](existing-crysta-name-candidates.json) | 기존 한국어 크리스타 425개와 게임 이름의 일치 후보. 359개 단일 후보·66개 불일치 |
| [bonus-types.json](bonus-types.json) | 메타데이터에서 읽은 옵션 enum 432개와 원본 상수 바이트 위치 |

전체 원문·메타데이터·문자열 검색 결과·검증 기록은 저장소 `build/tmp/toram-item-extraction/`에 있다. 이 임시 폴더는 Git에서 제외되므로 위 결과 JSON과 이 문서는 별도로 보존했다. 같은 폴더의 python-deps는 분석 도구용이며 제품 의존성이 아니다.

대용량 카탈로그와 연결 sidecar는 .aiignore의 기본 검색에서 제외했다. 필요할 때 위의 정확한 경로를 지정해 읽는다.

## 최초 오프라인 추출 범위 — e8e43f32 이력

선택한 캐시 버전 키는 `e8e43f32`다. BynaryData와 GameScene_kr의 마지막 수정 시각이 가장 최근인 공통 키였으며, 현재 서버/실행 중인 클라이언트의 최신 버전이라는 증거는 없다. 서로 다른 버전을 합치지 않았다.

| 원본 | 검증한 결과 |
| --- | --- |
| ItemMaster | 11,718개, 37바이트 고정 레코드, 양수·고유 ID, 정확한 EOF |
| ItemProperties | 4,460개, 44바이트 레코드, 마스터 연결 4,460개·고아 ID 0 |
| 비어 있지 않은 옵션 | 18,439개, cap ID 165종, 음수 값 1,317개 보존 |
| Item_kr | 22,530행 = 이름 11,636행 + 설명 10,894행, ID 11,716종, 정확한 EOF·UTF-8 |
| ItemProperty_kr | 옵션 문구 176개, 정확한 EOF·UTF-8 |
| ItemRandomProperty_kr | 이름/설명 656행·ID 328종, 정확한 EOF·UTF-8. 별도 원문/JSON에 보존 |
| BonusType | 메타데이터의 실제 압축 정수 상수 432개. 추출한 cap ID 165종 모두 포함 |

최종 마스터에는 한국어 이름 11,631개가 연결된다. 이름이 없는 마스터 87개를 임의로 채우지 않았다. 이름과 설명이 모두 없는 마스터 ID는 8개다. 마스터가 없는 텍스트 11행(이름 5·설명 6)은 최상위 orphanTexts에 보존했다.

게임 ID 예:

- `1000`: 리바이타 Ⅰ. 한국어 설명은 `HP 250 회복 `, 원본 옵션은 `201/hp_heal = 250`으로 서로 일치한다.
- `10001`: 숏 소드. master.function=10, stability=80, range_raw=4, potential=15. function의 종류별 의미나 거리 단위를 일반화하지 않았다.
- `9911`: G이코노스. `12/bMaxHpTo10 = 100`, `124/bMoveAttackResist = 10`을 원형 보존했다.

**옵션의 value는 표시값이 아닌 원본 signed i16이다.** 후속 코드 분석에서 GetBonusTime과 UIItemProperty의 배율 적용을 확인했다. 예를 들어 ID 12의 100은 표시 입력 1000이 된다. 원본 JSON에는 환산을 덮어쓰지 않았으며 부호별 문구·컨텍스트 분기까지의 범위는 [code-trace.md](code-trace.md)에 구분했다. 범위·플래그·슬롯의 종류별 해석도 미확정이다. 빈 옵션 슬롯 10개와 propertyRecord=null을 구별해 보존했다.

## 문자열에서 게임 객체로 연결한 방법

1. ToramOnline.exe는 x64 PE이며, 같은 설치에 GameAssembly.dll·IL2CPP 메타데이터·Unity 리소스가 있다.
2. 설치의 resources.assets에는 초기 화면용 BuildInLocalize 리소스가 있었고, 다운로드 캐시를 별도로 찾았다.
3. 캐시는 `%USERPROFILE%/AppData/LocalLow/Unity/Asobimo,Inc_ToramOnline/`다. 계산기 사용자 세팅 폴더와 다르다.
4. `BynaryData/<32자리 키>/__data`와 `GameScene_kr/<32자리 키>/__data`를 UnityPy 1.25.4로 읽어 TextAsset 바이트를 보존했다.
5. 알려진 이름을 UTF-8/UTF-16LE로 검색했다. 원문 TextAsset에서는 리바이타를 찾지 못했지만 변환 후 모든 11개 한국어 버전에서 UTF-8로 찾았다. 선택 버전의 첫 위치는 디코딩된 Item_kr의 offset 47이다.
6. 메타데이터에는 ItemData, ItemDBData, MasterItemDataManager.ReadItemData/ReadItemProperty/GetMasterItemData/GetAllMasterItemIdList, ItemTextManager와 LocalizeManager가 있다. 선언·토큰·바이트 범위는 metadata/item-schema.json에 기록했다.
7. 이름으로 범위를 좁힌 뒤 원본 정수 ID로 ItemMaster ↔ ItemProperties ↔ Item_kr를 결합했다. ID는 인벤토리 개별 장비의 인스턴스 ID가 아닌 정적 마스터 ID다. 실행 중 C# 객체 포인터를 관측한 결과도 아니다.

관측한 변환은 완전한 4바이트 단어에만 적용된다. 캐시 키의 하위 u32를 little-endian으로 놓고 `plain[i] = cipher[i] XOR cipher[i-4] XOR key[i%4]`를 계산한다. 첫 단어에서 이전 바이트는 0이며 마지막 0~3바이트는 그대로 둔다. 이전 바이트는 변환 전 cipher다. 합성 왕복 검사와 전체 행·UTF-8·EOF 검사로 검증했다. 이 식은 최초 구조 관측에서 도출했으며, 후속 네이티브 복호화 코드와의 대조 범위는 code-trace.md에 기록했다.

ItemMaster 레코드의 도출한 순서는 id:i32, sort_id:i32, type_id:i32, price:i32, material_level:u8, material_id:u8, process:i16, stack:i16, function:i16, stability:u8, range_raw:u8, slot_max_raw:u8, potential:i16, model:i32, flag_raw:u32다. 이름·순서는 ItemDBData 선언과 전체 파일 구조에서 도출했으며 원본 record hex와 offset을 보존했다. ItemProperties는 id:i32 뒤에 10개의 (cap_id:i16,value:i16) 쌍이다.

## 언어·외부 자료의 연결 경계

현재 아이템 이름/설명은 **kr/us/jp/cnt/idn/th**를 같은 게임 ID로 연결했다. 공개 manifest와 master/property 본문 동치 근거는 [item-localization.md](item-localization.md)에 있다. 메타데이터에 있는 cns/fr/esp/prt는 선택 manifest에 없어 확보했다고 표시하지 않았다.

[Coryn 공개 API 문서](https://coryn.club/api/)의 [아이템 목록 API](https://coryn.club/api/v1/items.php?limit=100&offset=0)를 100개씩 순차 수집했다. 목록에는 stats가 빠져 있다. [8416 상세 표본](https://coryn.club/api/v1/items.php?id=8416)만 옵션 포함 원문을 별도로 보존했다. 영어 Coryn ID와 게임 ID의 동일성은 확인하지 않았다. lang=ja/ko 표본도 기본 표본과 SHA256이 같아서 다국어 연결 근거가 되지 않는다.

기존 크리스타는 정확한 한국어 이름만 비교한 후보이며, 359개의 동일 이름을 곧바로 검증된 동일 객체/동일 옵션이라고 판정하지 않았다. 전체 게임에는 같은 이름의 다른 ID도 있으므로 옵션·분류 검증이 필요하다. 환산되지 않은 원본 수치를 기존 수치에 덮어쓰지 않았다.

최초 CDN 탐색의 404 결과는 game/downloads/cdn-discovery.json에 남아 있다. 후속 네이티브 호출·고정 상수 추적으로 실제 공개 releaseB manifest와 언어 번들을 확보했다. 최초 실패를 현재 미확보 상태로 해석하지 않는다.

## REA 근거와 한계

REA open_binary로 지정한 exe의 식별을 확인했다: SHA256 `a8139774475d99d855df49c6e86443c637dca170c546c983911262ef34734775`.

REA PE 리소스 관측은 `ev_9501eb6d797bf4896167cd3da5cc4fb01a809eac9d4e97890accba665460f312`다. 정적 RT_ICON/RT_GROUP_ICON/RT_VERSION/RT_MANIFEST 등 12개 페이로드를 확인했다. 이 관측은 exe의 전체 문자열이나 실행을 검사한 것이 아니다. Evidence 번들은 rea-evidence.json에 저장했고 세션을 닫았다.

최초 REA 세션에서는 Ghidra 경로가 미설정이었다. 이후 설치된 Ghidra 12.1.4를 찾아 현재 모듈 사본의 선택 함수 22개를 직접 분석했다. 그 결과는 별도 native-trace와 code-trace.md에 보존했으며 REA Evidence로 포장하지 않았다. 최종 전투 계산식과 인벤토리 객체는 확인하지 않았다.

메타데이터는 IL2CPP v31, SHA256 `0de18c3efde797096df6820d6dc0b24f359471cd1ab92c0718eb7496012dc7a5`다. 타입 20,148·필드 96,638·메서드 157,330개 중 관련 타입 63개와 문자열 636개를 선별했다. 레이아웃/압축 정수는 [Il2CppDumper 메타데이터 정의](https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Il2Cpp/MetadataClass.cs), [정수 판독 정의](https://github.com/Perfare/Il2CppDumper/blob/master/Il2CppDumper/Extensions/BinaryReaderExtensions.cs)를 참고했다.

## 재현·검증

저장소 루트에서 Python 3.12와 UnityPy 1.25.4를 사용한다. 아래 python은 설치된 실제 Python 실행 파일로 바꿀 수 있다. UnityPy가 별도 임시 디렉토리에 있으면 --unitypy-path를 전달한다. 기본 출력 경로는 build/tmp이며 이미 존재하는 다른 결과를 덮어쓰지 않는다.

```powershell
python tools/extraction/extract-il2cpp-item-schema.py 'C:/Asobimo/AsobimoGames/Toram/ToramOnline_Data/il2cpp_data/Metadata/global-metadata.dat' build/tmp/toram-item-extraction/metadata
python tools/extraction/extract-toram-item-assets.py --version e8e43f32 --unitypy-path build/tmp/toram-item-extraction/python-deps
python tools/extraction/decode-toram-item-master.py build/tmp/toram-item-extraction/game/cache/BynaryData/e8e43f32/ItemMaster.decoded.bin build/tmp/toram-item-extraction/metadata/master-items.json --properties build/tmp/toram-item-extraction/game/cache/BynaryData/e8e43f32/ItemProperties.decoded.bin
```

Coryn 재수집은 `node tools/extraction/extract-coryn-items.mjs 새출력폴더`다. 네트워크와 변경될 수 있는 외부 API를 사용하므로 보존한 snapshot과 같다고 보장하지 않는다.

각 Python 추출기의 `--self-test`, Coryn 추출기의 `--self-test`·`node --check`, 실제 전체 파일 EOF/ID/조인 검증, 원문 해시 검사, `npm run verify:architecture`, `npm run ai:audit`, `git diff --check`를 실행했다. 최초 검증 수치는 verification.json, 로더·배율은 native-verification.json, 현재 통합 검증은 [connection-verification.json](connection-verification.json)에 있다. 장비 강화·ASPD/CSPD/ATK/서브 안정률의 최종 계산 로직과 실제 화면 일치는 검증하지 않았다.
