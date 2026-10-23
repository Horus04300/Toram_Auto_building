# 실제 게임 아이템 ID의 6개 언어 연결

2026-10-17에 공개 정적 CDN의 manifest와 언어 번들을 읽기 전용으로 받았다. [item-localization-links.json](item-localization-links.json)은 현재 한국어 마스터 **11,723개 ID**에 **kr/us/jp/cnt/idn/th** 원문을 연결한 sidecar다. Coryn 번역이나 사이트 ID를 사용하지 않았다. 앱 계산 데이터와 기존 크리스타 425개는 수정하지 않았다.

## 같은 버전이라는 근거

추측한 파일명이 아니라 네이티브 URL 작성 코드와 실제 상수로 주소를 만들었다.

1. `InitGameSystem.<Start>d__28.MoveNext` RVA `0x2fbb60`의 호출 위치 `0x2fcbfb`에서 `SystemManager.GetDownloadURL`의 결과를 `ResourceManager.Initialize`에 전달한다.
2. `SystemManager.GetDownloadURL` RVA `0x397aa0`에는 공개 base URL, `windows/`, `releaseA/`~`releaseF/`를 결합하는 분기가 있다. 기본 분기를 활성 서버라고 가정하지 않고 코드에 실제 열거된 여섯 manifest를 각각 한 번씩 확인했다.
3. `ResourceManager.<Initialize>d__31.MoveNext` RVA `0x39f400`은 `RevisionInfoBinary.bytes`에 `?`와 `DateTime.Now.Ticks.ToString()`을 붙인다. 쿼리는 캐시 무효용이며 이번에는 동일한 정적 파일 본문을 쿼리 없이 받았다. `AssetBundleManager.<Initialize>d__43.MoveNext` RVA `0x37c180`은 base와 이 파일명을 결합한다.
4. `AssetBundleManager.createVersionTable(byte[])`는 header byte, 전체 길이 i64, 그룹 수 i16을 읽는다. 각 그룹은 문자열·flag byte·행 수 i32, 각 행은 i32 세 개다. 전체 **66,201바이트·163개 그룹·5,095행**을 EOF까지 검증했다. 마지막 필드는 단위를 추정하지 않고 `extraRaw`로 보존했다.
5. 각 `GameScene` 이름은 manifest에 실제 등록되어 있다. `LoadCacheAssetBundle`은 해당 이름에 `.unity3d`를 붙여 base URL에 결합한다. 별도 추측 버전 디렉터리나 계정 API를 요청하지 않았다.

| 공개 분기 | manifest HTTP | BynaryData의 cache key | GameScene의 cache key |
| --- | --- | --- | --- |
| releaseA | 200 | 95155932 | 95155932 |
| **releaseB** | **200** | **77596232** | **77596232** |
| releaseC | 200 | 102b5132 | e8e43f32 |
| releaseD | 200 | 102b5132 | e8e43f32 |
| releaseE / releaseF | 404 / 404 | 미확보 | 미확보 |

선택한 [releaseB manifest](https://toram-jp.akamaized.net/resources/windows/releaseB/RevisionInfoBinary.bytes)의 SHA256은 `887207c2878db2002bc079b089449dcf3c81998b9056d88eb77a9f18335e3b74`다. revision signed i32 `845306231`을 네이티브 `AssetDecrypt`의 big-endian XOR key bytes로 쓰면 기존 cache decoder의 key는 `77596232`다. 서로 다른 두 값을 같은 숫자라고 취급하지 않고 byte-order 변환을 명시했다.

이 manifest의 [BynaryData](https://toram-jp.akamaized.net/resources/windows/releaseB/BynaryData.unity3d)도 받아 `ItemMaster`와 `ItemProperties` 각각의 **원시·복호문 SHA256 네 개 전부**를 현재 [한국어 카탈로그](items.kr.77596232.json)의 출처와 대조했다. 모두 같았다. 따라서 단순한 revision 이름 일치뿐 아니라 마스터·옵션 본문 동치도 확인했다. 공개 한국어 텍스트를 기존 카탈로그와 ID별로 비교한 이름·설명 차이는 **0개**다. releaseA는 다른 snapshot으로만 보존했고 이번 연결에 섞지 않았다.

## 확보 범위와 사용 구조

각 언어 `Item_*`는 **22,530행**이다. 현재 마스터에 이름 **11,631개**, 설명 **10,888개**를 연결했다. 마스터 이름이 없는 92개 ID에 번역을 만들지 않았다. 마스터에 없는 원문 11행씩, 총 **66행**은 `orphanItemTexts`로 따로 보존했다.

```text
items[].gameItemId
  ├─ names.{kr,us,jp,cnt,idn,th}
  └─ descriptions.{kr,us,jp,cnt,idn,th}
propertyTexts[].propertyId → templates.{locale}
elementTextById[elementId][locale]
avatarSkillNamesById[skillId][locale]
avatarSkillRawNamesById[skillId][locale]
```

예를 들어 실제 게임 ID **9911**은 한국어 `G이코노스`, 영어 `G. Iconos`, 일본어 `Ｇイコノス`다. 이 연결은 이름 유사도가 아니라 같은 마스터 ID와 언어별 텍스트 ID에서 왔다.

`ItemProperty_*`는 **176개 signed ID × 6언어 = 1,056개 템플릿**이다. `-48`, `-166`~`-175`, `-188`의 음수 ID 12개를 각 언어에서 보존했다. 형식 감사 결과 `{0}` 888회, cap 137의 `{0:0.00}` 6회, cap 140의 `{0:F1}` 6회다. 기타 형식·불균형 중괄호는 0개다. 템플릿이 없는 특수 ID를 일반 숫자 템플릿으로 바꾸지 않았다.

System/Skill은 기존 `extract-toram-item-reference-texts.py`의 레코드 파서와 `derive_skill_name`을 재사용했다. 실제 속성 cap 65에서 사용한 enum ID **1~6, 8**과 아바타 참조 스킬 **1281/1282/1285**를 6언어로 연결했다. 대상 스킬의 이름·설명 행과 기본 N 태그는 모두 고유하며, **18개 기본 이름이 전부 복원**됐다. 원문 이름도 따로 남겼다. 예를 들어 일본어 skill 1285의 원문 `[N]竜破斬[N2]ドラグ・スレイブ[N]`에서 기본 N 이름은 `竜破斬`이다. 최종 화면 실관측이라는 뜻은 아니다.

인도네시아어와 태국어 Skill 표에는 각각 `(skillId=1153, kind=0)`이 두 행 있다. 엄격한 공용 파서가 이 중복을 거부하면 같은 레코드 구조로 모든 행을 보존하며 EOF까지 검사했다. 중복 덮어쓰기 동작을 가정하지 않았고, 대상 아바타 스킬 세 개에는 이 문제가 없다. 다른 skill kind는 숫자와 원문을 유지하며 새 의미를 부여하지 않았다.

메타데이터에 locale tag가 있어도 이번 공개 manifest에는 **cns/fr/esp/prt**의 `GameScene` 항목이 없다. 이 네 언어의 번들을 추측 요청하거나 다른 출처 번역으로 대체하지 않았다. 다른 플랫폼·별도 배포 분기의 존재 여부까지 부정하는 결과는 아니다.

## 원문과 재현

원문은 `build/tmp/toram-item-extraction/game/downloads/localizations/`에 있다. releaseB의 공개 번들 7개와 추출 TextAsset **128개**의 원시·복호문 해시를 sidecar `sources`에 넣었다. `System_*`, `Skill_*`, `Item_*`, `ItemProperty_*`는 파싱 원문도 보존했다. 그 외 TextAsset은 원시·복호문만 남기고 형식을 해석하지 않았다. 모든 파일은 게임 실행·주입·수정 없이 분석했다.

```powershell
python tools/extraction/extract-toram-localizations.py --self-test
python tools/extraction/extract-toram-localizations.py
```

기본 실행은 보존된 파일만 읽는다. 새로운 다운로드 폴더에서 `--download`를 명시하면 releaseB manifest와 그 manifest의 `BynaryData`·실제 열거된 `GameScene`만 순차 GET한다. 현재 카탈로그와 master revision이 다르면 언어 연결 전에 중단하며, 보존된 원문과 다른 내용을 덮어쓰지 않는다. UnityPy는 기존 임시 dependency 경로를 사용하며 설치하지 않는다.

네이티브 coroutine의 고유 token·주소 연결과 Ghidra 입력은 `prepare-toram-localization-trace.py`가 기존 mapper·Ghidra 스크립트를 재사용해 만든다. 근거는 `build/tmp/toram-item-extraction/code-trace/localization-trace/`의 `native-map.json`, `pseudocode-v6/`, `mscorlib-callees.json` 및 부모 조사에서 보존한 `item-connections/public-application-paths.json`·`pseudocode-download-url/`다. 선택 함수만 분석했으며 게임 코드는 실행하지 않았다.

실행한 검증은 localization 추출기 self-test, coroutine 준비 self-test, 공용 참조 문자열 파서 self-test, manifest 길이·EOF·개수, 모든 source 해시, 11,723개 ID 고유성, 원본 master/property 본문 동치, 한국어 원형 동치, signed 음수 property ID, 1,056개 템플릿 및 18개 아바타 이름 검사다. 모두 PASS다.

실제 활성 서버 분기와 최종 UI·지역별 숫자 서식은 관측하지 않았다. 옵션부여·전투 스탯 계산식도 이번 다국어 연결의 완료 범위가 아니다.
