# 레지스트렛 원본 바이트·6언어

`extract-assets.py`는 보존된 releaseC 스냅샷의 BynaryData 및 GameScene 6언어 번들을 읽는다. 네트워크·게임 실행·프로세스 접근은 하지 않는다. 입력 번들·manifest·복호화 revision·TextAsset pathId·원본/decoded 해시는 `manifest.json`에 있다. manifest 해시를 고정해 다른 버전을 조용히 섞지 않는다.

- `RegistletMaster.raw.bin` / `.decoded.bin`: 1,334바이트. int32 version=1, int16 count=166, 이후 각 행은 int16 Id, int16 LevelCap, int32 EnhancePowder다. `RegistletMaster.structural.json`은 원본 순서·행 시작 offset을 유지한다.
- `Registlet_<locale>.raw.bin` / `.decoded.bin` / `.parsed.json`: cnt/idn/jp/kr/th/us. int32 count=497, 이후 int32 ID·byte kind·BinaryReader UTF-8 문자열이다. kind0=이름166행, kind1=설명166행, kind2=BaseValue 정수 문자열165행이다. 모든 언어의 이름/설명 ID 집합은 마스터166개와 일치하며 BaseValue는 6언어가 동일하다.
- `System_<locale>.selected.json`: Registlet/TreasureHunt 및 젬 카트리지 관련 원문·원본 offset이다. 전체 System 원본은 크기가 커 중복 보존하지 않으며 입력 번들과 전체 raw/decoded 해시로 재현한다. 선택 원문에는 `RegistletPanelAddSlotButton`·`RegistletPanelAddSlotMes`의 “분말을 {0} 사용해 슬롯을 늘린다”가 포함된다. 실제 수량은 이 문자열에 없고 네이티브 계산 경로를 따른다.

필드 의미는 [`ReadRegistletData`](../native/20085.c), [`CreateGemCartData`](../native/20083.c)와 Id/EnhancePowder/LevelCap getter(20077/20079/20081)를 함께 대조했다. 필드 저장 위치는 각각 +0x10/+0x14/+0x18이다. EnhancePowder는 강화 분말 필드이며 경험치·슬롯 확장 비용·획득 확률로 읽지 않는다.

[`RegistletTextManager.Initialize`](../native/46486.c)는 kind0 이름·kind1 설명·kind2 BaseValue를 별도 사전에 모아 연결한다. 누락/파싱 실패한 BaseValue는 -1이다. UI는 BaseValue=-1인 설명을 수치 치환하지 않으며, 다른 값은 [`GetDescriptionValueText`](../native/65962.c)의 ID별 식을 사용한다. ID1004는 [`ChangeActiveDetailWindow`](../native/65950.c)에서 두 값을 별도로 만든다. parsed JSON에는 화면 치환 전 원문·이스케이프·태그를 그대로 보존한다. 설명 치환식은 전투 효과의 계산식과 구분해야 한다.

사용자 예시 ID는 맹독 회복12, 스파이크18, 어보이드 세트50, 프로텍션 이지스1036이다. 이름 문자열만으로 다른 카탈로그 ID와 연결하지 않는다.

```powershell
python data/sources/toram-registlet/assets/extract-assets.py --self-test
python data/sources/toram-registlet/assets/extract-assets.py --check
```

첫 명령은 버전·개수·EOF·중복 ID·잘못된 LevelCap 거부를 확인한다. 두 번째는 7번들/13 TextAsset을 다시 추출하여 모든 보존 파일과 바이트 단위로 비교하고 이름/설명 ID·6언어 BaseValue 동치를 검사한다. UnityPy는 기존 `build/tmp/toram-item-extraction/python-deps`를 재사용한다. 새 패키지는 설치하지 않는다. 저장된 클라이언트 자료이며 현재 서버 활성화·최종 UI·실제 보상 추첨은 관측하지 않았다.
