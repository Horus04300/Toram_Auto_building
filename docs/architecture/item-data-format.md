# 개발판 아이템 데이터 계약

원본 추출·검토용 카탈로그와 화면/계산이 읽는 가공본을 분리한다. 원본 raw hex·offset·네이티브 근거는 배포하지 않는다. 가공본 schema는 `toram.project-items.v1`이다. 시작 시 크리스타 통합 shard를 읽고 나머지 종류·언어는 지연 조회한다.

## 식별·파일 구성

- 정적 아이템의 식별자는 양수 정수 `gameItemId`다. 이름·번역·Coryn ID·보유 장비 UUID는 식별자로 대체하지 않는다. 이름이 같거나 없는 객체도 ID별로 보존한다.
- `web/public/game-data/items/manifest.json`은 버전, 원본/매핑/StatRegistry/아이템 사용 규칙 hash, 각 파일의 SHA256·크기, 종류·언어별 파일명을 기록한다. 원본 근거와 생성 파일은 Git 줄바꿈 변환에서도 바이트를 유지한다.
- `index.<hash>.json`은 ID → 종류다. 종류는 weapons/armor/additional/special/crystas/avatars/consumables/other다. 종류별 `items/<kind>.<hash>.json`은 ID → 가공 객체다.
- 이름과 설명은 `locales/<locale>/<kind>.{names,details}.<hash>.json`으로 분리한다. 크리스타 통합 객체에도 ID별 이름·설명·옵션 원문을 결합한다. 없는 번역은 null이며 임의 번역으로 채우지 않는다.
- details의 `displayOptions[] = {text, conditional}`은 원본 옵션의 순서·선택 언어 문구·조건 범위를 보존한다. 조건 제목과 대상 slot 모두 conditional이며 빈 문구와 별도 지속시간 marker는 제외한다. 도감은 이 목록을 한 번만 표시하고 옵션 연결/원본 진단은 노출하지 않는다. 계산용 stats/conditionalStats·선택 스냅샷과는 별개다.
- 파일명은 내용 hash를 포함한다. 교체 전 파일은 보존하며 마지막에 manifest 파일 하나를 교체한다. 준비/배포 시 현재 manifest가 참조하는 파일만 복사한다. 원본·분석 근거·실패 스냅샷은 배포하지 않는다.

## 가공 객체와 계산 연결

```text
typeId / defaultSlot              종류와 기본 선택 슬롯
effectScope                       equipment / consumable-buff / catalog-only
buff?                             소모품 duration 그룹 ID와 지속시간(초)
stats                             프로젝트의 canonical StatRegistry 키 → 표시 환산값
element?                          native 무기 속성 0~8 (일반 스탯과 별도)
conditionalStats[]                when / stats / unresolved / element?
unresolved[]                      원본 slot/capId/rawValue와 미연결 이유·특수 참조
baseRaw                           function/stability/range/slotMax/potential/flags/model
fullyMapped                       이 객체의 옵션 키 연결 범위. 계산식/UI 검증 등급 아님
```

변환은 검토한 `project-stat-mapping.json.statMapping`의 cap ID·enum 이름·적용 scope를 대조하고 실제 StatRegistry에 존재하는 키만 사용한다. 값은 추출 단계의 float32 환산값과 다시 대조한다. 미검토 매핑, clamp, 수치 보정, 미확정 단위 변환을 만들지 않는다. 같은 scope에서 동일 프로젝트 키가 중복되면 집계 의미 재검토를 요구한다.

장비 조건은 다음 N개 옵션 범위를 보존한다. native main OR sub는 `either-weapon-slot`, main·sub 모두 한손검인 조건은 `both-weapon-slots`, 방어구 개조는 `body-battle-customize`다. 호환 뷰의 `condStats`는 각각 `eitherWeapon[]`, `main/sub`, `armor`로 표현하며 Application과 compiler가 같은 의미로 평가한다. OR를 AND로 바꾸거나 양쪽 무기에서 중복 합산하지 않는다.

`web/src/application/item-catalog.mjs`의 `resolveItemOptions(item, context)`가 조건을 해소한 뒤 기존 `StatOptionDraft[] = {key,value}[]`를 만든다. 활성 상태의 미연결 효과가 있거나 catalog-only 아이템이면 조용히 누락하지 않고 오류를 반환한다. 비활성 조건의 미연결 효과는 적용 대상이 아니다. `notModeled` 키는 기존 StatRegistry의 보존 계약을 따르며 산식 지원을 새로 보증하지 않는다. manifest의 `statDefinitions`에서 unit/status를 확인한다.

`baseRaw.function` 등을 보유 장비의 실제 ATK/DEF/제련값으로 자동 입력하지 않는다. 속성·아바타 스킬·회복/사용 효과를 일반 스탯으로 강제 변환하지 않는다.

## 개발판 적용 경계

`node tools/extraction/sync-toram-dev-items.mjs`는 공개 revision 확인 → 추출/검증 → snapshot/project 변환 → 개발판 파일 검증/교체를 한 번 실행한다. 수동 명령만 제공하며 주기 실행·백그라운드 작업은 만들지 않는다. 코드 변경/형식 오류/변환 실패/출처 hash 불일치면 이전 개발판 manifest를 유지한다. 동시 sync는 잠금으로 차단한다.

현재 앱은 `window.ToramApp.items`로 `getItem(id, locale)`, `listItems(kind, locale)`, `getDetails(id, locale)`, `refresh()`를 노출한다. 시작 시 데이터는 요청하지 않는다. 동일 파일의 동시 요청은 하나의 Promise를 공유하고 실패한 요청은 재시도할 수 있다. 반환한 캐시 데이터는 불변이다. 개발판 파일 갱신 뒤 페이지를 새로 열거나 `refresh()`로 manifest를 다시 읽는다.

`listItems(kind, locale, {typeId, category})`는 선택한 세부 분류가 있을 때만 해당 종류의 정의 shard도 읽고 이름 목록을 필터링한다. 옵션을 생략하면 기존 이름 목록과 지연 조회를 유지한다. 도감의 무기는 원본 typeId, 크리스타는 일반·강화에 공통인 category로 구분하며 계산·추천 후보는 바꾸지 않는다.

장비 탭의 `게임 아이템에서 장비 옵션 불러오기`는 목록을 요청했을 때만 해당 종류·언어 파일을 읽는다. 주무기·보조·몸/추가/특수 장비의 ID를 선택하고 원본 옵션을 적용할 수 있다. 이름 언어가 달라도 ID는 유지한다. 주무기·보조는 현재 종류와 일치해야 하며, 비활성 조건까지 포함해 미연결 효과가 하나라도 있는 장비는 적용을 차단한다. ATK·안정률·제련은 보유 장비의 실제 값을 수동 입력한다.

보조의 일반 옵션은 native `PlayerStatusBase.SetEquip`에 따라 방패17·단검18·화살19·두루마리23만 합산한다. 마도구15·권갑16·발도검8·듀얼 보조검10의 일반 옵션은 합산하지 않으며 선택 ID/정의와 수동 옵션은 보존한다. 기존 화살/듀얼 기본 ATK·안정률·제련 경로와 이 옵션 경로를 분리한다. cap65는 별도 element 메타데이터로 보존하며 주무기·조건부 속성을 해소한다. 활/자동활은 속성 있는 화살이 주무기 속성을 대체한다. 다른 보조의 속성은 일반 옵션처럼 주무기로 합산하지 않는다. 근거는 `data/sources/toram-items/item-use-rules.md`다.

**기존 커스텀 옵션은 적용·재적용·해제·저장·복원 과정에서 유지한다.** 제작 장비는 원본을 선택하지 않고 기존 수동 옵션만 사용한다. 원본을 선택한 칸에서는 원본 옵션과 수동 옵션을 합산하며 화면에 이를 안내한다. 원본 해제는 그 원본의 기여만 제거한다.

`EquipmentPieceDraft.catalogItem?`은 `toram.equipment-item.v1`의 선택 스냅샷이다. ID·선택 언어의 이름·캐시 버전·원본 SHA256·종류·검토된 stats/conditionalStats와 선택적 element만 저장하고, 전체 카탈로그/설명/다국어 문구는 복제하지 않는다. 저장 문서 v2의 기존 빌드는 이 필드 없이 그대로 읽는다. 새 필드가 있는 빌드는 이를 지원하는 실행기가 필요하며 이전 출시 앱에서 같은 계산을 보장하지 않는다. 복원 전에 종류/슬롯·스탯 키/유한 수치·조건 형식·빈 unresolved를 검증한다.

계산은 Application의 `kernelInput`에서 선택 스냅샷의 조건을 현재 main/sub/armor로 해소하고 기존 `StatOptionDraft[]`에 한 번 합산한다. 화면에 수치 행을 복제하지 않아 조건 변경·저장 복원에서 중복 합산되지 않는다. 같은 baseContext를 사용하는 크리스타 추천에도 고정 장비 옵션으로 전달된다. 업데이트는 카탈로그만 갱신하고 저장된 선택의 값은 자동 변경하지 않는다. 사용자가 해당 ID를 다시 적용할 때 최신 정의를 사용한다. 열린 화면에서 새 카탈로그를 쓰려면 새로고침한다.

크리스타의 단일 원본은 ID-keyed `items/crystas.<hash>.json`이다. `gameItemId`, `names`, `descriptions`, `options`의 cap/operand/float32/조건 slot/6언어 문구, `stats/conditionalStats`, `previousId`, 검토한 기존 이름 `aliases`를 결합한다. type61~65의 Model만 강화 전 ID로 읽고 부모 존재·동일 카테고리·cycle을 검증한다. type36 빈 아이템은 선택 대상에서 제외한다. 근거는 `data/sources/toram-items/native-crysta-lineage/README.md`다.

`getCrystaCatalog()`와 `ToramApp.crystas.getById(id)`가 같은 통합 데이터를 사용한다. `crysta-data.js`는 이 데이터의 호환 뷰이며 별도 수치 목록을 보유하지 않는다. 기존 저장/잠금/금지 문자열·추천 tie ID는 유지하고 명시적 aliases로 ID를 찾는다. 번역 이름 충돌은 별칭 조회에서 제외하며 이름 유사도/스탯으로 런타임 ID를 추정하지 않는다. 이전 수치 fixture는 검증용으로만 보존한다. `optimizerEligible=true`는 이 결합/계보 계약을 뜻하며 미구현 전투 사건 지원을 뜻하지 않는다.

새 실제 크리스타의 옵션이 미연결이거나 종류가 미검토이면 가공본 발행을 차단하고 이전 manifest를 유지한다. 원본 snapshot의 미연결 기록은 보존하며 화면 목록에서 조용히 빼고 성공으로 처리하지 않는다.

## 버프 소모품

`consumableCategory?`는 카테고리 표시/검색을 위한 별도 메타데이터다. `id`, `names`, `basis`, 원본 `durationCapId`, `declaredNames`를 보존한다. 검토한 `consumable-categories.json`으로 한국어/일본어 설명의 명시적 카테고리를 먼저 연결하고, 선언이 없을 때만 확인한 지속 계열을 사용한다. 미검토 선언·복수 계열·즉시 회복 아이템은 임의 분류하지 않는다. 표시 카테고리로 `buff.groupId`나 저장된 중복 적용 규칙을 바꾸지 않는다. 출처/예외/검증은 `docs/verification/consumable-categories.md`다.

버프 탭의 소모품 목록은 `listBuffItems(locale)`가 해당 종류/언어만 읽어 만든다. native CheckUseItem을 통과한 type 2/50 중 첫 유효 cap이 검토된 duration marker 하나이고, 뒤에는 검토된 고정 스탯만 있는 항목을 지원한다. 양의 cap ID와 0이 아닌 부호 있는 operand를 요구한다. 0은 script workvalue 참조이므로 0 스탯으로 변환하지 않는다. 조건·반복·회복·상태 명령·미해석 효과가 섞이면 아이템 전체를 선택 대상에서 제외한다. 원본/미해석 레코드는 유지한다.

`BuildDraft.consumableBuffs?`는 `toram.consumable-buff.v1` 선택 목록이다. 각 선택은 gameItemId/cacheVersion/sourceSha256/name/typeId/buffGroupId/durationSeconds/stats를 고정한다. 같은 duration cap ID는 새 선택으로 교체하며, 계산·저장 입력의 그룹/ID 중복은 오류다. 서로 다른 그룹의 같은 스탯은 합산한다. 기존 externalOptions는 선택·교체·해제·복원에서도 보존한다. Application은 선택한 고정 옵션을 기존 커널에 한 번만 전달한다.

지속시간은 초 단위의 참고값이며 선택 목록은 현재 활성 상태를 뜻한다. 아이템 사용·경과 시간·사망/만료 자동 전이는 시뮬레이션하지 않는다. `notModeled` 스탯은 화면에 계산 미지원·보존으로 표시한다. 카탈로그 갱신이 저장한 선택을 자동 변경하지 않으며 최신 값은 다시 선택해 적용한다. 이 선택을 지원하지 않는 이전 출시 앱에서 같은 계산을 보장하지 않는다.

현재 건수는 handoff와 manifest를 기준으로 한다. 누락 이름은 ID로 표시하며 매핑 건수를 전투식 검증 건수로 해석하지 않는다. `item-use-rules.json`, `project-stat-mapping.json`, `crysta-legacy-aliases.json`과 핵심 native 함수 hash를 검사하고 manifest의 출처 hash로 버전을 연결한다.

## 검증 Gate

- `npm test`: 스탯 값/키, OR·듀얼·개조 조건, 활성 미연결 효과 차단, 중복 ID/키, lazy 요청·캐시·재시도·같은 이름의 ID 분리, hash·부분 적용/동시 실행 차단.
- 같은 명령의 `test-item-equipment.mjs`: 실제 ID/보조 8종, 일반 옵션 제외, 버프 값·그룹·저장 검증, 기존 커널 동치와 수동 옵션 보존. 변환 테스트는 동적 0 operand·음수 페널티·복합 명령·duration 순서/enum·사용 불가 분류도 확인한다. 브라우저는 한/영 ID·보조 기본 입력·수동 옵션·버프 교체/해제·JSON 왕복·재열기를 확인한다.
- `test-crysta-catalog.mjs`: 실제 전수 ID/이전 이름/부모 연결, 조건별 원본·Application·compiler 동치, ID/영문 금지·잠금, 실데이터 소형 WASM 완전탐색의 점수·tie ID. 상세 `docs/verification/crysta-id-catalog.md`.
- Python 파이프라인 `--self-test`: 추출 실패·코드 변경·변환 실패 때 latest 유지, 원본 보존·변경 비교·중도 revision 변경.
- `npm test`, source/web/desktop `verify-es-module-entry.mjs`: 기존 계산/저장/실행 경계와 새 카탈로그 진입점.
- 실제 브라우저에서 개발 루트·배포 하위 경로의 ID 조회가 같은 데이터를 읽고, 필요 없는 언어/설명/재요청을 만들지 않는지 확인한다.
- 표현/키/조건을 바꿀 때는 원본 옵션 커버리지와 float32·기존 산식 계약을 다시 대조한다. 추천기 전체 전환은 크리스타 최적화 계약의 계보/잠금/동점 Gate를 따른다.

## 속성·스탯 비례 옵션 계산

cap53~59는 대상 속성에 맞는 피해 퍼센트만 사용한다. scenario.target.targetElement는 0(미지정) 또는1~7(불/물/바람/땅/빛/어둠/무)이다. 보스 선택은 확인된 elementRaw를 입력하고 수동 변경·저장·복원한다. 약점25%와 대상별 추가 위력을 구분하며 Mana8을 무조건 약점으로 바꾸지 않는다. 고정 속성 스킬은 해당 속성을 사용하고, 속성 미지정 스킬은 무기 속성을 계승한다.

cap166~175는 기초 STR/INT/VIT/AGI/DEX를 참조한다. 원본별 표시 float32 값을 native 정수 tenths로 복원한 뒤 합산하고, raw/1000의 float32 항을 STR→INT→VIT→AGI→DEX 순으로 더해 마지막에 한 번 0 방향 절삭한다. 수동 입력의 격자 밖 소수는 정수로 강제 반올림하지 않는다. JS·Rust가 같은 연산을 사용하고 Rust JSON은 float_roundtrip으로 입력 비트를 보존한다. 원문/VA/바이트/해시는 data/sources/toram-items/native-option-calculation/README.md를 따른다.

대상에 맞지 않는 피해 키는 추천 목적 좌표에서 제외하되 원시 옵션을 보존한다. 비례 계수가 후보마다 달라지면 그 원시 좌표를 동등성 분류에 유지하고 ATK/MATK 투영을 생략한다. 다른 HP/공속 투영은 유지한다. affine 상한은 항별 절댓값 합의128×float32 epsilon 오차와 부호별 절삭 완화를 포함하며 f32 overflow 영역에는 fallback을 사용한다. 고정 계수는 정확한 합산 기여를 사용한다. 계산 v5·solver/checkpoint v25·후보 투영 v3으로 이전 캐시/재개 상태를 구분한다.

장비/소모품에 잘못 제한됐던 기존 scalar 매핑과 누락된10개 비례 계수를 연결한다. METEOR_RES·SUCTION_RES·HELP_INVINCIBILITY·STOP_FLINCH·PET_EXP·GEM_DUST_DROP도 원본 키/단위로 보존한다. 피격·도움·보상 사건 소비는 notModeled이며 옵션 데이터 연결을 전투 시뮬레이션 완료로 표시하지 않는다. 아바타 스킬 참조·이동/회복/랜덤 사용 명령은 일반 스탯이 아니다.

추가 Gate: tools/tests/optimization/test-elemental-option-parity.mjs는 대상/무기/고정 스킬 속성, 실제 저장 소수 계수, signed i16 전체 범위와 음수 상쇄를 JS/Rust로 대조한다. 일반 회귀 목록에도 포함한다.

cap114는 item-event 조건이며 활성 여부는 scenario.conditions.activeItemEventTypes의 중복 없는 byte 집합으로 입력한다. false이면 그 marker 이후 현재 스크립트의 나머지만 종료되고 앞선 옵션은 유지된다. all/any/not 조합은 장비 조건으로 marker 자체를 건너뛴 원시 흐름을 보존한다. 계산기 장비 탭은 실제3종의 활성 체크박스를 제공하고 기본은 모두 꺼짐이다. 서버 캘린더는 추정하지 않는다. 저장 조건 검증·장비 미리보기·커널·복원은 같은 집합을 사용한다.
