# 레지스트렛 데이터·수식 추출

2026-10-29. 보존된 releaseC 번들과 대응 GameAssembly/IL2CPP 메타데이터를 연결했다. 앱·저장 형식·계산 엔진에는 적용하지 않았다. 원문 수치, 설명 치환식, 실제 전투 producer/consumer, 서버 보상은 서로 다른 검증 범위다.

## 결과와 원본

- [통합 JSON](../../data/sources/toram-registlet/catalog.json), [한국어 CSV](../../data/sources/toram-registlet/catalog.csv): 젬 카트리지166종, 네이티브 ID/enum·최대 레벨·강화 분말·6언어 이름/원문·BaseValue·설명 치환식·전투 근거·획득처 연결 상태.
- [원본/복호화 바이트](../../data/sources/toram-registlet/assets/README.md): 마스터166행, cnt/idn/jp/kr/th/us 각각 이름166·설명166·BaseValue165행. 마스터와 원문 ID 집합·6언어 BaseValue가 일치한다. 원본 순서·바이트 offset·해시·번들 revision/pathId를 보존한다.
- [전투 규칙166행](../../data/sources/toram-registlet/combat-rules.md), [구조화 규칙](../../data/sources/toram-registlet/combat-rules.json): Buff subclass163종, query 반환식104종, BonusData 반환식11종, 장착 유무/직접 소비48종을 구분한다. 59·68·1046의 Buff subclass는 조사한 매핑에 없으며 효과가 없다는 판정으로 쓰지 않는다.
- [슬롯 비용](../../data/sources/toram-registlet/native-slots/README.md), [획득처](../../data/sources/toram-registlet/acquisition/README.md), [정적 입력/함수 해시](../../data/sources/toram-registlet/provenance.json).

`RegistletMaster`는 int32 version, int16 count 이후 int16 Id·int16 LevelCap·int32 EnhancePowder다. 네이티브 로더와 getter의 저장 위치까지 대조했다. EnhancePowder를 슬롯 확장 비용이나 드롭 확률로 사용하지 않는다. 원문의 kind0/1/2는 이름/설명/BaseValue이며 BaseValue 누락·파싱 실패는 -1이다.

## 설명식과 실제 효과

`catalog.json.displayRule`은 UI의 `{0}` 치환식이다. `L`은 젬 레벨, `B`는 원문의 BaseValue다. 기본 `L×B` 외에 쿨다운·감소·소수·복수 치환·현재 습득 스킬 레벨을 쓰는 분기가 있다. 1004는 두 값을 치환하며 207은 SkillId107=PowerWave의 습득 레벨이 필요하다. float32 상수와 연산 순서를 보존하고, 필요한 외부 입력 없이 표시값을 추정하지 않는다.

`nativeBuffer`와 `combatRules`는 실제 반환식·query selector·조건·쿨다운/상태 함수로 연결한다. BonusType 내부 값과 화면 단위는 별개다. 예를 들어 최대 HP의 내부 BonusData `L`을 곧바로 최종 HP `L`로 해석하면 안 된다. 공통 GetValue는 쿨다운과 CheckTrigger를 검사하지만 장착 유무를 직접 확인하는 효과는 이 경로를 쓰지 않을 수 있다.

| 예시 | ID | 최대Lv | 확인한 효과/경계 |
| --- | ---: | ---: | --- |
| 맹독 회복 | 12 | 30 | 원문상 맹독 대미지를 받을 때 `L%` 해제, producer `Value=L`. 실제 틱·난수 분모/서버 구현은 미확정 |
| 스파이크 | 18 | 10 | producer `5L`, 둔족 이동 배율 `0.5×(1+0.01×5L)`; Lv1=0.525, Lv10=0.75. 다른 스킬 분기와 구분 |
| 어보이드 세트 | 50 | 1 | 장착 유무로 Avoid 장비 제한 검사를 통과; 확률 반환식이 아님 |
| 프로텍션 이지스 | 1036 | 1 | 반대 스킬을 배웠을 때 그 습득 레벨의 버프도 추가. SkillId263 Protection↔264 Aegis |

화둔술·용염1031의 캐시식은 `ceil(f32(2.5×L))`다. System.Math.Ceiling의 네이티브 상대 점프가 해당 helper에 도달함을 대조했다. 쿨다운은 Time.deltaTime과 연결되며, 버서크·억제401의 Random.Range(int,int) 호출도 별도 근거에 있다. 모든 소비 함수의 최종 피해 순서나 서버 난수 구현을 전수 검증한 것은 아니다.

## 분말을 통한 슬롯 확장

최대 슬롯10, 분말 보유 상한999,999,999다. 실제 비용은 `NeedGemPowder[현재 슬롯 수-1]`이다. 게임이 실행된 상태에서 생성자 코드24바이트·필드 참조8·FieldInfo32·컴파일러 필드 이름65의 총129바이트만 읽어 메타데이터 상수 배열과 연결했다. 모듈·메타데이터·코드·필드 토큰·배열 SHA-256을 확인했다. 사용자가 보고한 현재500,000 표시도 일치한다.

| 확장 | 분말 |
| --- | ---: |
| 1→2 | 100 |
| 2→3 | 400 |
| 3→4 | 2,000 |
| 4→5 | 7,000 |
| 5→6 | 30,000 |
| 6→7 | 200,000 |
| 7→8 | 500,000 |
| 8→9 | 2,000,000 |
| 9→10 | 7,000,000 |

전체9단계 합계9,739,500이다. 신규 계정의 초기 슬롯 수는 서버 전달값으로 남겼다. 실제 확장·분말 차감은 실행하지 않았다.

## 획득처 연결

엘 스카로의 ‘스투디의 실험’ 진입 스크립트에서 Lv10/30/50/70/90/110/130/150/170/190/210/220/230/250/270/290의16단계를 연결했다. 각 목적지 필드·방 ID·6언어 이름과 원본 명령 offset은 [stages.json](../../data/sources/toram-registlet/acquisition/stages.json)에 있다.

서버 `CheckTreasureHuntRoomResponse.ItemData`에서 방 데이터와 UI의 D/C/B/A/S 상자 보상 목록으로 이어지는 코드 경로를 확인했다. 사용자가16개 레벨의 보상 창을 순서대로 열었을 때 해당 목록만 고정 참조로 읽었다. 전체44,592바이트이며 각 캡처의 모듈/메타데이터/코드·객체 타입·배열 길이·최종 루트 안정성을 검사했다. 계정·캐릭터·인벤토리 데이터나 임의 힙 검색은 사용하지 않았다.

166종 중163종의 획득 레벨과 상자 등급을 연결했다. 맹독 회복12는 Lv30/50/270의 A/S, 스파이크18은 Lv110/130/270의 A/S, 어보이드 세트50은 Lv250의 A/S, 프로텍션 이지스1036은 Lv220의 S 및 Lv290의 A/S에 표시됐다. 원본 목록·비트 보존 값과 근거 해시는 `acquisition/captures/`와 `stages.json`에 있다.

루나 디재스터·절약1040, 디코이 슈터·유도1046, 신속의 호수1054는 관측한16개 목록에 없다. 미출시·다른 획득처 등으로 임의 분류하지 않는다. 후보 목록에는 개별 드롭 확률이 없어 `dropProbability=null`을 유지한다. 목록 순서나 개수를 균등 확률로 바꾸지 않으며, 효과 발동 확률과 보상 드롭 확률을 섞지 않는다.

## 앱 발행과 보관

`node tools/extraction/publish-toram-registlets.mjs`는 추출 카탈로그에서 `web/public/game-data/registlets/catalog.json`과 공통 상한 색인 `web/src/data/registlet-levels.mjs`를 함께 만든다. `--check`는 두 발행본의 바이트 일치를 확인한다. 공개 데이터는166종·6언어·원문/기본값/상한/강화분말·효과 용도 분류·16단계 획득처·9단계 확장 비용을 포함한다. sourceSha256은 원본 카탈로그 해시이며 cacheVersion은 그 해시와 presentation.json·reviewed-rules.json을 결합한 SHA256의 앞8자리다. 추가 근거 파일의 해시도 발행 시 검사한다.

도감 `section=registlets`와 인벤토리 `type=registlet`은 일반 아이템 ID와 구분한다. 레벨·정의 스냅샷을 저장하며 전투 계산/빌드 조립은 연결하지 않는다. 설명의 수치·확률은 native 표시 치환식이며 드롭률과 구분한다. 저장 DTO·호환 경계는 [플랫폼 데이터/API 계약](../architecture/platform-data-api-contract.md)의 레지스트렛 항목을 따른다.

`node tools/tests/application/test-registlet-catalog.mjs`는 전166종의6언어 Lv1/상한 표시값을 추출 근거와 대조하고 획득처·슬롯·개인 CRUD/수정 충돌·공개 독립 복사를 검사한다. `node tools/verification/verify-registlet-browser.mjs [--source]`는 격리 DB와 Chrome PC/모바일에서 담기·수정·재로딩/이탈 저장·삭제를 검사한다. 기본은 웹 생성본이며 `--source`는 개발 소스다.

## 강화 비용과 설명에 없는 스컬 셰이커 수식

분류는 [presentation.json](../../data/sources/toram-registlet/presentation.json)에166개 ID를 한 번씩 배정한 도감용 기준이다. 게임 공식 분류로 표시하지 않는다. 기본 능력10·상태 대응16·전투/편의32·스킬 변경108종이며 슬롯 확장표는 독립 화면이다. 도감과 인벤토리의 설명·수식·대입값·결과는 입력 이벤트마다 함께 갱신한다.

추가 정적 검토는 [reviewed-rules.json](../../data/sources/toram-registlet/reviewed-rules.json)에 함수·바이트 해시와 범위를 고정한다. REA provider의 Ghidra 환경은 연결되지 않아 기존 Ghidra12.1.4/JDK를 격리된 headless로 사용했다. 이미 보존한 PE/mapped/metadata만 읽었으며 게임 실행·프로세스 변경은 없다.

- 강화: [OnClickSelectMaterialGem](../../data/sources/toram-registlet/native-enhancement/66058.c)의 재료 합산에서 P=대상 젬 EnhancePowder다. 동종 재료1개는 `-trunc0(f32(P)*f32(-0.1))` 분말과 재료Lv만큼 상승, 타종은 P분말과1Lv 상승이다. 현재166종의 P에서는 동종 비용이 전부 floor(P/10)과 같다. 예: P50→5/50, P75→7/75, P3333→333/3333. 단계별 Lv 비례 비용으로 해석하지 않는다.
- 동종의 새 레벨은 Math.Min(상한,현재 예상Lv+재료Lv)이다. 상한 직전에서 고레벨 재료를 써도 비용1개분은 그대로다. 최대10개를 한 번에 선택하며 상한/선택수 도달 후 추가 선택은 막는다. [강화 버튼](../../data/sources/toram-registlet/native-enhancement/65824.c)은 현재Lv=상한에서 즉시 반환한다. 장착/잠금/자기 자신인 재료 제외는66067.c다. 실제 강화·재료/분말 소모·서버 계산은 실행하지 않았다.
- 스컬 셰이커1053: BaseValue=-1이고 원문에 숫자 자리가 없다. [ActionPreparation](../../data/sources/toram-registlet/native-skill-effects/1053/25972.c)에서 사용 스택을 min(현재 스택,L)로 제한하고 기절 확률을0으로 설정한다. [calcPlayerToMobDamage](../../data/sources/toram-registlet/native-skill-effects/1053/25974.c)는 기존 스택≥L이면 추가 스택을 만들지 않는다. 따라서 젬 Lv1/3/5의 상한은1/3/5스택이다.
- S=스킬Lv, K=min(현재 스택,L)일 때 native 계수는 할버드 `(750+trunc0(f32(S*7.5))*K)/100`, 지팡이 `(1000+(trunc0(f32(S*7.5))+25)*K)/100`이다. 초기값은 기존25971.c, 나누는100f는1053/constant.json의 `0000c842`로 연결한다. UI는 K=L인 최대 스택 계수를 계산한다. S10에서 L1→8.25/11, L3→9.75/13, L5→11.25/15다. S1의 곱셈은 먼저7로 버린 뒤 K를 곱하며, 고정 대미지 감소율로 바꾸지 않는다.
- Ghidra가 TryGetBuff의 R8 out 포인터를 놓치면 유효한 스택 분기를 제거했다. 보존된 TraceToramRegistletEffectReviewFocused.java는 관측 ABI를 선언하고 unreachable 제거를 끄며 assembly를 함께 출력한다. 해당 조건은 assembly와 교차 확인했다. 재현 입력은1053/method-map.json이며, 강화는 native-slots/TraceToramRegistletSlots.java와 native-enhancement/method-map.json을 재사용한다. 게임 전투 엔진 연결/실제 대미지 관측과는 별개다.

## 재현과 검증

```powershell
python data/sources/toram-registlet/assets/extract-assets.py --self-test
python data/sources/toram-registlet/assets/extract-assets.py --check
python data/sources/toram-registlet/acquisition/extract-acquisition.py --self-test
python data/sources/toram-registlet/acquisition/extract-acquisition.py --check
python data/sources/toram-registlet/acquisition/capture-reward-list.py --self-test
python data/sources/toram-registlet/native-slots/self-check.py
python tools/extraction/extract-toram-registlets.py --self-test
python tools/extraction/extract-toram-registlets.py --check
node tools/verification/audit-ai-context.mjs
git diff --check
```

`extract-toram-registlets.py`는 보존된 원문/함수 해시·166ID·163클래스·소비 참조·표시식 경계를 확인하고 JSON/CSV를 재생성한다. 네이티브 분석은 Ghidra12.1.4의 선택 함수 디컴파일이며 retained REA Evidence ID는 없다. 정적 스냅샷은 비원자적 모듈 캡처다. 현재 설치 입력과 다르면 재분석해야 하며 임의 버전을 허용하지 않는다.

검증 명령은 `node tools/tests/application/test-registlet-catalog.mjs`, `node tools/verification/verify-registlet-browser.mjs` 기본/`--source`, `npm test`, `node tools/verification/audit-ai-context.mjs`, `git diff --check`다. 레지스트렛 단위/소스·웹 생성본 Chrome1280/390px과 전체 회귀88개(87 PASS·Native 저장 E2E1 SKIP), Rust96·desktop24·타입/모듈 경계·S1·fmt/clippy를 통과했다. 실제 Native 저장은 TORAM_E2E_CDP가 없어 제외한다. 전체 로그는 `build/tmp/registlet-refinement/npm-test.log`다.

원본 재현에는 Git에서 제외된 해당 releaseC 번들/메타데이터/모듈 스냅샷이 필요하다. 보존된 바이트·fixture·추출 근거는 캐시 정리 대상으로 취급하지 않는다. 게임 파일 쓰기·전투·구매·실제 슬롯 확장은 수행하지 않았다.
