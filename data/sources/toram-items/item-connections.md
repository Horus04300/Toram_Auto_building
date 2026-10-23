# 아이템 데이터 연결 완료 기록

2026-10-17, 캐시 `77596232`. 현재 결과는 [items.77596232.connected.json](items.77596232.connected.json)이다. 정적 게임 마스터 ID를 기준으로 연결했으며, 이름 유사도나 Coryn ID를 게임 ID로 사용하지 않았다. 앱 계산 데이터에는 아직 반영하지 않았다.

## 연결 결과

| 대상 | 결과와 근거 |
| --- | --- |
| 마스터·옵션 | 11,723개 고유 ID, 옵션 레코드 4,460개·전체 슬롯 44,600개·비어 있지 않은 옵션 18,439개. 기존 master·원본 hex·offset·슬롯 값 보존 |
| 언어 | kr/us/jp/cnt/idn/th. 각 언어 이름 11,631개·설명 10,888개. 공개 releaseB의 ItemMaster/ItemProperties 원시·복호 해시가 현재 로컬 원문과 모두 일치 |
| 옵션 문구 | signed ID 176개 × 6언어. 기존 unsigned 해석에서 놓친 음수 ID 12개 복구, 실제 옵션 29개가 음수 템플릿 선택 |
| 조건부 옵션 | 조건 그룹 589개·대상 옵션 704개. 조건 값은 다음 옵션의 개수이며 수치 보너스로 합산하지 않음 |
| 특수 옵션 | 속성 참조 696개, 아바타 스킬 참조 12개. 모든 대상의 6언어 이름 연결 |
| 분류·기본 슬롯 | 47개 실제 type에 대한 네이티브 predicate 연결. 아바타 3,611개의 packed category 복원 |
| 제작 | 2,079개 레시피 중 아이템 생성 1,699개, 외형 변경 330개, 수집 가방 확장 50개. 아이템 재료와 소재 포인트 구별 |
| 보조 표 | 랜덤 옵션 328개, 제작 보조 2그룹·40참조, NGItem 29개, 모델 표 5그룹·2,498레코드 보존 |

이름 누락 92개는 여섯 언어 모두 원문 행이 없다. 그중 80개는 반복되는 상자 계열의 내부용 후보, 4개는 GM 관련 설명이 있는 항목이며, 이를 실제 획득 가능한 아이템이라고 확정하지 않았다. 이름·설명이 모두 없는 항목은 13개다. 마스터 없는 텍스트 11행씩, 총 66행도 보존했다.

## 구조와 값의 사용

```text
items[].gameItemId                  정적 아이템의 게임 ID
  names / descriptions             locale → 원문
  master                           원본 고정 레코드 필드
  propertyRecord                   null 또는 원본 10슬롯
    caps[]                         slot / cap_id / value / enumName
      role / valueKind             조건 개수·속성 enum·스킬 선택자·일반 피연산자
      templates                    locale → 양수 cap ID의 원문 템플릿
      display                      float32 환산값·선택 templateId·문구 후보
      reference                    속성 또는 스킬 참조와 다국어 이름
      conditionMarkerSlot          이 옵션을 제어하는 조건 슬롯
    conditionGroups[]              markerSlot / targetSlots / uiTargetSlots
  references                       type·flag·기본 슬롯·레시피·모델 후보
relatedData                        전체 보조 표의 상대 파일명
conditionRules                     조건 cap ID별 실제 predicate
optionTextRowsKr                   음수 ID를 포함한 한국어 원문 행
connectionSources                  입력 파일 크기·SHA256
```

`cap.value`는 원본 signed i16다. 일반 표시 수치는 `float32(value × multiplierFloat32)`이며 기본 배율 1과 예외 24개는 네이티브 코드에서 확인했다. 예를 들어 G이코노스(9911)의 HP 원본 100은 표시 입력 1000, 돌진경감 원본 10은 10%다. 기존 앱의 수치를 이 값으로 덮어쓰지는 않았다.

음수 값의 cap 48·166~175·188은 음수 ID 템플릿을 먼저 찾는다. `display.templateId`가 실제 선택 ID다. 일반 템플릿이 없는 849개 옵션은 회복·사용 효과 등도 포함하며, 숫자 문구를 임의로 만들지 않았다. cap별 개수는 [connection-verification.json](connection-verification.json)에 있다. 속성 cap 65는 ElementType, cap 189는 raw 0/1/5 → 스킬 1281/1282/1285 연결이다. 스킬 이름은 태그 원문과 기본 N 태그 해석 결과를 함께 보존했다.

조건 범위 `[96,103,108,109,115,120]`은 제한된 런타임 읽기와 컴파일러 초기값의 SHA256·field token 대조로 확인했다. main 또는 sub의 무기 타입, main·sub 모두 한손검인 경우, 경량/중량 방어구 조건을 구분한다. 보너스 실행은 빈 cap을 제외한 다음 N개 명령, UI는 다음 N개 물리 슬롯을 센다. 현재 589그룹에서는 두 범위가 전부 일치하며, 추출기는 중첩·겹침·잘린 그룹을 거부한다.

`master.range_raw`·`slot_max_raw`는 종류에 따라 다른 의미로 쓰인다. 아바타는 `(range_raw << 8) + slot_max_raw`로 범주를 만들므로 모든 항목에 거리·슬롯 개수라는 단위를 붙이면 안 된다. 기본 장착 슬롯은 정적 분류이며, 보유 장비 UUID를 비교하는 실제 장착 상태와 구별한다.

## 출처와 재현

- [code-trace.md](code-trace.md): 최초 로더·배율 분석. [native-connections/](native-connections/)와 [native-classification/](native-classification/)에는 후속 선택 함수 의사코드·token·RVA·해시를 보존했다. C 파일은 원래 C# 소스가 아니다.
- [item-localization.md](item-localization.md): 네이티브 URL 작성 경로, manifest, 7개 공개 번들·128개 TextAsset 해시, 언어별 검증. URL·다운로드 coroutine 의사코드와 고정 상수는 [native-localization/](native-localization/)에도 보존했다. 실제 활성 서버 분기는 관측하지 않았으며 본문이 동일한 공개 분기를 선택했다.
- [item-relations.md](item-relations.md): 보조 표 로더·레코드 길이·EOF·바이트 재구성, 비아이템 레시피 namespace 근거.
- [item-reference-audit.json](item-reference-audit.json): 누락 이름·과거 캐시 대조·enum·미해석 flag. [crysta-link-audit.json](crysta-link-audit.json)의 외부/기존 자료 연결은 모두 후보이며 동일 객체 확정은 아니다.

저장된 메타데이터와 복호문이 있는 현재 작업 공간에서 다음 명령으로 새 출력에 재현할 수 있다. 기본 경로는 각 스크립트에 명시되어 있다. Python 실행 파일은 설치된 Python으로 바꿀 수 있다.

```powershell
python tools/extraction/connect-toram-item-data.py --self-test
python tools/extraction/connect-toram-item-data.py --output build/tmp/toram-item-extraction/새통합결과.json
python tools/extraction/extract-toram-localizations.py --self-test
python tools/extraction/prepare-toram-localization-trace.py --self-test
```

통합 추출기는 캐시 버전·출처 hash·공개 master 본문 동치·원본 한국어 동치·전체 특수 참조 커버리지를 검사한다. 완성 JSON 재생성은 바이트 단위로 일치했다. 별도 전체 데이터 검사에서 원본 슬롯·raw hex·한국어·18,439개 float32를 다시 대조했다. 연결 관련 Python 9개와 크리스타 감사 Node self-test, `npm run verify:architecture`, `npm run ai:audit`, `git diff --check`를 실행했다. 상세 결과는 [connection-verification.json](connection-verification.json)과 현재 작업 로그에 있다.

## 남겨 둔 해석 경계

- `plainTextCandidate(s)`는 네이티브 템플릿 선택 + invariant 숫자 미리보기다. 실제 IL2CPP Single 반올림·지역 서식·색상·줄바꿈·최종 화면 일치까지 검증한 문자열이 아니며 `finalUiVerified=false`다.
- 이름 누락 92개, enum 미정 type 200의 46개, 미해석 flag bit를 가진 3,683개 항목은 원형을 유지했다. `Unsalable`/`AddProperty`의 동일 bit alias를 의미 하나로 강제하지 않았다.
- 모델 표는 type/model이 일치하는 후보만 연결했다. 호출자별 변환·실제 모델 연결은 미확정이다. 랜덤 옵션을 특정 아이템에 배정하는 인스턴스 경로도 미확정이다.
- `ItemDorpData`는 4바이트 뒤 13바이트 × 3,143개의 관측된 분할과 raw hex를 보존했다. 각 묶음의 뒤 9바이트를 드롭률·몬스터 ID로 해석하지 않았다. NGItem도 목록 소속만 확인했으며 거래·소지 금지로 일반화하지 않았다.
- 원문 번들·모듈·메타데이터는 Git 제외 `build/tmp/toram-item-extraction/`에 있다. 이 자료가 없는 다른 환경에서는 완성 JSON·근거를 열람할 수 있지만 전체 네이티브 재현에 같은 원문이 추가로 필요하다.
- 보유 장비 인스턴스·강화 결과·제련·옵션부여 확률·ASPD/CSPD/ATK/서브 안정률의 최종 계산식은 이번 아이템 연결 결과에 포함하지 않았다.
