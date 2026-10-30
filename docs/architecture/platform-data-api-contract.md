# 플랫폼 데이터·API 계약

- 확정일: 2026-10-24. [플랫폼 구현 기준](platform-design-contract.md)을 구체화하는 저장·서버 계약이다.
- 구현·검증 상태는 [현재 인계](../handoff/current-development-handoff.md), 기존 인증·개인 저장은 [계정 서버 계약](account-home-server.md)을 따른다.
- 사용자 합의의 핵심인 독립 복사·계층 조립·두 객체 병합·장비 귀속 외형·게시글 단위 평가·고정 릴리스를 유지한다. 아래 이름과 형식은 구현 기준이며 변경이 필요하면 문서와 호환 계획을 함께 갱신한다.

## 1. 저장 경계

- 기존 Node·SQLite 기반을 확장한다. 인증·세션을 다시 만들거나 계산을 모두 서버로 옮기지 않는다. Native/WASM의 공통 계산 엔진을 유지한다.
- 개인 객체, 공개 게시글, 공개 스냅샷, 평가 관계는 분리한다. 모든 옵션·스킬을 SQL 열로 펼치지 않고 구성 본문은 종류별 검증 JSON으로 저장한다.
- 이름·종류·정렬 시각·검색용 분류는 조회 가능한 필드로 관리한다. 검색용 장비 종류·무기·역할 등은 검증된 구성에서 추출하며 클라이언트의 임의 색인을 신뢰하지 않는다.
- 게임 도감의 원본/발행 JSON과 ID·버전 스냅샷은 재사용한다. 도감 전체를 계정 DB에 중복 저장하거나 조회할 때마다 기존 객체를 최신 데이터로 교체하지 않는다.

## 2. 테이블

### inventory_objects

| 필드 | 계약 |
| --- | --- |
| `id` | 개인 객체 고유 ID. UUID 문자열을 기본으로 사용 |
| `owner_id` | 계정 ID. 세션에서 결정하며 요청의 사용자 ID로 소유권을 정하지 않음 |
| `type` | 등록된 객체 종류 |
| `name` | 사용자 지정 이름 |
| `schema_version` | 해당 종류의 저장 형식 버전 |
| `revision` | 수정 충돌 검사용 증가 번호 |
| `data_json` | 검증된 구성 스냅샷 |
| `provenance_json` | 도감·공개 릴리스·내 객체 등 출처 목록과 당시 버전 |
| `created_at`, `updated_at` | 생성·수정 시각 |

목록 조회는 소유자·종류·수정 시각·ID로 정렬할 수 있도록 색인한다. 필요한 장비 세부 종류 등은 검증된 검색 필드로 추가한다. 출처가 같다고 UNIQUE 제약을 걸지 않는다. 출처 삭제가 복사본에 연쇄 삭제를 일으키는 FK도 만들지 않는다.

개인 객체의 `revision`은 공개 이력이 아니다. 매 편집마다 공개 릴리스를 만들거나 개인 과거 전체를 자동 보존하는 기능까지 포함하지 않는다. 객체 수정과 부모 스냅샷 교체는 서로 다른 행동이다.

### posts

| 필드 | 계약 |
| --- | --- |
| `id`, `author_id` | 게시글 ID·작성자 |
| `content_type` | 공유할 구성 종류 |
| `title`, `description` | 게시글 제목·소개 |
| `visibility` | 공개·비공개·삭제 상태 |
| `latest_release_id` | 해당 게시글의 최신 공개 릴리스 |
| `revision` | 게시글 관리 정보의 수정 충돌 번호 |
| `created_at`, `updated_at`, `deleted_at` | 게시글 수명 정보 |

공개 목록은 공개 상태이면서 유효한 릴리스를 가진 게시글만 반환한다. 원본 접근 불가 안내를 위해 식별·상태를 유지하며, 실제 영구 삭제·복구 정책은 별도 결정한다. 최신 릴리스는 반드시 같은 게시글 소속이어야 한다.

### post_releases

| 필드 | 계약 |
| --- | --- |
| `id`, `post_id` | 릴리스 ID·소속 게시글 |
| `release_number` | 게시글 안에서 증가하는 공개 버전 번호 |
| `name`, `change_notes` | 릴리스 이름·변경 설명 |
| `object_type`, `schema_version` | 고정 구성의 종류·형식 |
| `snapshot_json` | 공개할 전체 또는 일부 구성의 독립 스냅샷 |
| `game_version` | 작성/대상 게임 버전 정보 |
| `catalog_version`, `calculation_rules_version` | 사용한 데이터·계산 규칙 정보 |
| `published_at` | 공개 시각 |

`(post_id, release_number)`는 유일하다. 공개된 구성과 릴리스 설명을 덮어쓰지 않는다. 새 릴리스 추가와 `posts.latest_release_id` 갱신은 같은 트랜잭션이다. 개인 객체가 바뀌거나 삭제되어도 릴리스는 유지한다. 알 수 없는 게임 버전을 임의 최신값으로 채우지 않는다.

### 평가·검색·재시도

| 테이블 | 주요 필드·제약 |
| --- | --- |
| `post_favorites` | `user_id`, `post_id`, `created_at`; 사용자·게시글 조합 유일 |
| `post_ratings` | `user_id`, `post_id`, `value`, 생성·수정 시각; 사용자·게시글 조합 유일 |
| `post_tags` | `post_id`, `tag`; 같은 태그 중복 금지, 태그 검색 색인 |
| `request_receipts` | 사용자·요청 키·요청 식별값·상태 코드·처리 결과·생성 시각; 같은 키 재시도 결과 재사용 |

평가 FK는 릴리스가 아닌 게시글을 가리킨다. 즐겨찾기 수·별점 집계는 별도 원본으로 중복 관리하지 않으며 캐시를 둔다면 실제 관계와 일치시킨다. 복사 횟수는 즐겨찾기에 합산하지 않는다. 별점 범위·별도 추천 여부는 후속 UI 결정과 일치시킨다.

요청 키는 저장 객체의 ID나 출처가 아니다. 같은 사용자의 같은 키·같은 요청은 같은 처리 결과를 돌려주고, 같은 키로 다른 요청을 보내면 충돌이다. 사용자가 의도적으로 다시 복사할 때는 새 키를 사용한다. 요청 기록의 보존 기간은 콘텐츠의 영구 수명과 별도 운영 정책이다.

## 3. 객체 형식과 조립

기본 종류는 `equipment`, `equipment_set`, `status`, `skill_tree`, `skill_set`, `consumable`, `consumable_set`, `combo`, `combo_set`, `build`다. 종류별 `schema_version`과 허용 자식 종류를 검증한다. 외형은 장비 하위 데이터다.

### 장비 v1 DTO

장비 생성 입력은 `{type:"equipment", schemaVersion:1, name, data:{slot,equipment}}`다. `equipment`는 기존 `EquipmentPieceDraft`의 type·attack·refinement·stability·options·crystas·lockedCrystaSlots·선택적 catalogItem을 사용한다. 별도 `toram.account-item.v1` 표식을 data 안에 중첩하지 않는다. 수정은 같은 입력에 기대 `revision`을 추가하고 삭제는 `{revision}`을 보낸다.

- 슬롯은 mainWeapon/subWeapon/armor/additional/special이다. 기본 수치·종류의 null, 보조 장비 0개/나머지 2개의 크리스타·잠금 배열을 기존 BuildDraft와 일치시킨다.
- 옵션은 공용 스탯 레지스트리와 유한 수치, catalogItem은 기존 장비 원본 검증·부위/종류 호환을 따른다. 알 수 없는 필드는 무시·손실 저장하지 않고 거부한다. 외형/염색은 해당 게임 자료·다음 DTO가 정해지기 전 v1 요청에 넣지 않는다.
- 수동 옵션 100개·조건부 원본 그룹 100개 등은 요청 복잡도 제한이며 게임 능력치 상한이 아니다. 개인 장비 200개·본문 1 MiB는 기존 보관함의 운영 제한을 이어받는 초기 정책이며 자동 만료는 없다.
- 응답은 id/type/name/schemaVersion/revision/equipmentType/createdAt/updatedAt/data/provenance다. 목록에는 data/provenance를 제외하고 `{items,page,pageSize,total}`로 반환한다. 기본 6개, 최대 50개이며 updatedAt 내림차순·ID 오름차순으로 정렬한다. q는 이름의 부분 문자열 검색이다. 인벤토리 UI는 최대 50개씩 배치를 읽어 종류별 전체 보관 객체(최대 200개)를 같은 목록에 표시하며 화면의 이전/다음 페이지로 노출하지 않는다.
- equipmentType은 공용 `equipment-object.mjs`의 고정 키다. sword=한손검/듀얼, greatsword=양손검, staff=지팡이 등이며 armor/additional/special은 부위로 추출한다. 클라이언트가 별도 색인을 지정하지 않는다.
- 목록은 장비 `slot`·`equipmentType`, 개별 스킬트리 `skillCategory`·`treeId`, 개별 도핑 `buffGroupId`를 추가 필터로 지원한다. 해당 객체 종류와 등록된 부위·트리·native 계열로 검증한다. 기존 JSON 스냅샷에서 조회하며 저장 스키마·기존 행을 변경하지 않는다.
- 직접 장비 등록은 계산기 상태를 읽지 않고 입력한 `{type:'equipment',schemaVersion:1,name,data}`를 같은 POST에 저장한다. 기본 수치·수동 옵션·크리스타는 공통 장비 검증을 거치고, 소유자·revision·출처 계약은 동일하다. 공개도 기존 게시글/릴리스 경로를 따른다.
- 최초 catalogItem이 있으면 서버가 ID·cacheVersion·출처 해시로 최초 출처를 기록한다. 수정은 최초 출처를 유지하고 현재 선택한 원본 스냅샷은 data에 보존한다. POST에 임의 소유자/출처 필드를 보내면 거부한다.
- 웹 작업 공간은 `/inventory?type=equipment&equipmentType=staff&selected=ID&page=1&q=이름`을 쓴다. 앱 내 전환은 임베디드 진입 문서를 유지하는 `/index.html?view=inventory&type=equipment`를 사용한다. 구형3개 API의 새 쓰기도 inventory_objects를 사용한다. 외부 형식·기존 ID는 record_links로 연결하고 미이관 records는 읽기 보존한다. 이관 도구 검증과 운영 이관은 구분한다.

계산기에서 장비를 담기는 명시적 POST이며 자동 업로드가 아니다. 장비 적용은 현재 빌드의 해당 부위만 교체하고 다른 부위·캐릭터·Scenario를 보존한다. 주/보조 무기가 호환되지 않으면 적용 전에 거부한다. 편집 연결은 조회한 ID·revision으로 저장하며 409에서 초안을 보존한다. 새로운 사본은 별도 POST로 생성한다. 공개 출처의 독립 복사 API는 접근성 검증·요청 키 계약을 별도로 따른다.

### 레지스트렛 v1 DTO

조립 가능한 기본10종에 독립 보관 종류 `registlet`을 추가한다. 생성 입력은 `{type:"registlet",schemaVersion:1,name,data:{selection}}`이며 기존 개인 객체 CRUD·종류별200개·revision·공개 릴리스/독립 복사 계약을 따른다. DB 열·기존 행은 변경하지 않는다.

- `selection`은 `{schema:"toram.registlet.v1",registletId,cacheVersion,sourceSha256,name,level,levelCap,baseValue,descriptionTemplate}`다. 이름·효과 원문·기본값·상한·ID·버전을 저장 당시 값으로 보존한다. 등록 ID와 원본 상한, 정수 `1..levelCap`, 허용 필드를 클라이언트/서버 공통 검증한다. 향후 원본 상한이 바뀌면 기존 스냅샷을 수용하는 호환 검증부터 변경한다.
- 최초 출처는 서버가 `{kind:"registlet-catalog",registletId,cacheVersion,sourceSha256}`로 기록한다. 일반 아이템 ID와 별도 공간이며 수정은 최초 출처를 유지한다. 공개 릴리스는 원본 버전을 함께 기록한다.
- `/catalog?section=registlets`는166종·6언어를 지연 로드한다. `registletKind=all|stats|status|support|skills`는 도감용 효과 용도 분류이며 `slots`는 별도 확장 비용 화면이다. 레벨 입력마다 설명·수식/대입/결과·재료별 강화 비용을 즉시 갱신하고 URL의 level은 replace로 유지한다. 도감에서 담기는 명시적 POST이며 `/inventory?type=registlet`에서 새 젬 선택·레벨 수정·이름 수정·삭제를 지원한다. 기존 항목의2분/이탈 저장과 실패 시 초안 보존을 재사용한다.
- 설명 치환은 추출된 native UI 식이며 전투 계산과 분리한다. 파워 웨이브207과 스컬 셰이커1053은 관련 스킬 Lv 입력을 받는다. 1053은 사용 스택=min(현재 스택,L), 상한=L·기절확률0과 최대 스택의 두 무기 계수를 표시한다. 강화는 동종 재료1개당 `-trunc0(f32(P)*f32(-0.1))` 분말/재료Lv 증가, 타종은 P분말/+1Lv이며 상한을 넘기지 않는다. 이 컨텍스트 입력은 보관 selection에 추가하지 않는다. 획득처 미관측3종·보상 드롭률은 추정하지 않는다. 레지스트렛은 `sections`·병합·빌드 자식·계산기 담기/적용 대상에 넣지 않는다.
- 발행은 `node tools/extraction/publish-toram-registlets.mjs [--check]`다. 원문 SHA256·도감 분류·해시 검증한 추가 native 근거에서 발행 버전을 만들고 공개 JSON과 공통 상한 색인을 함께 생성한다. 공개 배포에는 프로세스 캡처·역컴파일 원문을 포함하지 않는다. 검증은 `test-registlet-catalog.mjs`, `verify-registlet-browser.mjs [--source]`, `npm test`다.

### 조립 v1 DTO

모든 종류는 `{type, schemaVersion:1, name, data}`로 생성한다. 수정·삭제의 revision 계약과 목록 응답은 장비와 같다. 종류별 200개이며 다른 종류에는 equipmentType 색인을 빈 문자열로 저장한다. 구형 장비 행·records를 재작성하지 않는 가산 스키마다.

하위 구성은 `{type, schemaVersion:1, name, data, provenance}` 스냅샷이다. 개인 객체를 포함하면 `{kind:"inventory",objectId,revision}` 출처를 남기며 조회 시 최신 원본을 결합하지 않는다. 하위 스냅샷은 아래 고정된 종류 관계만 허용한다.

| 종류 | data |
| --- | --- |
| status | `{character:{level,attributes:{STR,INT,VIT,AGI,DEX,CRT}}}` 전체 |
| equipment_set | `{slots:{주무기/보조/몸/추가/특수 ID: equipment 스냅샷 또는 null}}` |
| skill_tree | `{treeId,levels:{스킬 ID:투자 레벨},activeBuffs:{트리:스킬 ID:{active,stacks}}}` |
| skill_set | `{trees:{고정 트리 ID: skill_tree 스냅샷 또는 null}}` |
| consumable | `{selection: 기존 toram.consumable-buff.v1}` |
| consumable_set | `{categories:{고정 native buffGroupId: consumable 스냅샷 또는 null}}` |
| combo | `{steps: 기존 9칸 이내 콤보 순서}`; 스킬 ID·태그·특수 공격 포함 여부·입력값 |
| combo_set | `{entries:[{id,combo: combo 스냅샷}]}`; 최대 100개 보관 |
| build | 선택적인 status/equipment/skills/consumables/combos 스냅샷과 context |

- 세트의 누락 키는 제공하지 않은 영역, 명시적인 null은 그 부위·트리·계열을 비우는 선택이다. status는 항상 전체이며 null을 받지 않는다. 개별 스킬 선택이나 장비 내부 필드 병합은 없다.
- 트리·스킬 ID와 투자 상한·선행 투자는 기존 skill-tree-data.js로 검증한다. 버프 선택은 해당 트리에 귀속한다. 스킬 계산식·스택 상한을 새로 만들거나 S1~S5 완료 상태를 바꾸지 않는다.
- 도핑 비교 키는 기존 원문 연결을 가진 native buffGroupId다. 같은 MAXHP 효과라도 다른 native 그룹이면 합친다. 임의의 화면 카테고리 이름이나 스탯 이름으로 그룹을 재분류하지 않는다. 카테고리의 표시 이름 확정은 별도 작업이다.
- context는 externalOptions·myRoomFood·guildFoodBuff·Scenario(target/conditions/optimizationPreferences/bossSelection)를 보존한다. 두 빌드에서 다르면 `context` 전체 충돌로 선택한다. 추천 요구조건의 null과 누락은 구별하며 Request·실행 상태는 넣지 않는다.
- 2개 병합 결과는 같은 단위면 해당 개별 종류, 여러 동일 영역이면 세트, 다른 영역이면 build다. 기존 build는 부분 build로 유지할 수 있다. 부분 build를 계산기에서 편집해 저장할 때 원래 포함한 영역·부위를 유지하고 다른 현재 세팅을 임의 추가하지 않는다. 새 전체 빌드 담기는 별도 명시적 생성이다.
- 적용은 포함한 영역을 바꾼다. 개별 도핑은 그 계열만 교체하고 도핑 세팅·빌드의 도핑 영역은 보관한 목록으로 교체한다. 호환되지 않는 주/보조 또는 미습득 콤보 스킬로 인해 기존 복원기가 데이터를 버리게 되는 경우에는 적용 전에 거부한다.
- 콤보를 합치면 같은 내용도 모두 유지하고 결과 안에서 고유한 항목 ID를 부여한다. 여러 콤보 중 적용·편집할 하나를 명시적으로 선택하며, 그 콤보 편집으로 다른 항목을 덮어쓰지 않는다. 사용자가 선택 항목만 제거할 수 있다. 구형 계산기/JSON에는 선택한 콤보 하나만 적용되며 보관한 전체 목록은 DB에 유지한다.

병합 미리보기는 `{left:{objectId,revision},right:{objectId,revision},choices?:[{unit,take}],name?}`를 받고 `{type,conflicts,groups,complete,result}`를 반환한다. 미해결이면 result는 null이다. conflicts는 양쪽의 고정 구성과 허용 선택 단위, groups는 전체 선택 가능한 영역이다. 전체/세부 선택의 중복과 실제 충돌 외 선택은 거부한다.

확정은 같은 입력과 `Idempotency-Key`(16~120자 영숫자/하이픈/밑줄)를 받는다. BEGIN IMMEDIATE 안에서 요청 키·소유권·revision·선택·결과 검증, 새 객체와 request_receipts 기록을 원자적으로 처리한다. 같은 요청 재전송은 원본이 나중에 바뀌어도 최초 성공 응답을 반환한다. 같은 키의 다른 요청은 REQUEST_KEY_CONFLICT 409, 변경 원본은 REVISION_CONFLICT 409, 미해결 충돌은 MERGE_UNRESOLVED 409다. 실패 시 객체나 요청 기록을 부분 생성하지 않는다.

| 구성 | 저장·해석 단위 |
| --- | --- |
| 장비 세팅 | 주무기·보조·몸·추가·특수별 장비 스냅샷 |
| 스테이터스 | 전체 스테이터스 스냅샷 |
| 스킬셋 | 고정 트리 ID별 트리 스냅샷 |
| 도핑 세팅 | 고정 카테고리 ID별 도핑 스냅샷 |
| 콤보 목록 | 독립 항목 식별자를 가진 콤보 스냅샷 리스트 |
| 빌드 | 위 구성들과 기존 계산 조건·설정 경계를 조립한 스냅샷 |

개별 객체·중간 객체를 조립 입력으로 받고 목적 필드로 해석한다. 같은 영역에 여러 구성을 넣으면 병합 계약을 거치며 조용히 마지막 값으로 덮어쓰지 않는다. 객체를 무제한 재귀 참조하는 범용 그래프는 만들지 않는다. 기존 `BuildDraft`·`Scenario`·일회성 Request의 구분과 계산 입력 연결은 보존한다.

스냅샷에는 필요한 원본 ID·버전·정의와 출처를 고정한다. 상위 객체를 읽는 중 소유 인벤토리의 최신 자식이나 최신 공개 릴리스를 자동 결합하지 않는다. 병합한 두 출처와 하위 구성의 출처를 보존하며 공개 응답에는 불필요한 비공개 객체 식별자를 노출하지 않는다.

### 외형 표현

아래는 장비의 외형 관련 부분만 나타낸 예시다. `dyes`의 실제 키·값은 아직 미정이다.

```json
{
  "gameItemId": 10001,
  "appearance": {
    "overrideItemId": null,
    "dyes": {}
  }
}
```

표시 외형은 override가 없으면 해당 장비의 게임 ID를 사용한다. 외형 가져오기는 원본의 실제 표시 ID를 해석한 뒤 대상 override에 넣고 옵션·제련·크리스타는 유지한다. 원본의 null을 그대로 복사하지 않는다. 염색까지 가져올지는 UI에서 명확히 선택한다. 원본 게임 ID가 없는 수동 제작 장비의 기본 외형 선택은 모델 자료와 함께 결정한다.

## 4. API와 페이지 상태

기존 `/api/session`, `/api/auth/google`, `/api/auth/google/callback`, 앱 인증, `/api/logout`, `/api/me` 계약은 유지한다. 새 구조의 기본 경로는 다음과 같다.

| API | 동작 |
| --- | --- |
| `GET /api/inventory` | 내 객체 목록·검색·종류/장비 종류 필터·정렬·페이지 전환 |
| `POST /api/inventory` | 종류·이름·형식·구성을 검증해 새 개인 객체 생성 |
| `GET /api/inventory/{id}` | 내 객체와 수정 번호 조회 |
| `PUT /api/inventory/{id}` | 기대 수정 번호 확인 후 구성 교체·수정 번호 증가 |
| `DELETE /api/inventory/{id}` | 기대 수정 번호 확인 후 내 객체 삭제 |
| `POST /api/inventory/copies` | 도감·공개 릴리스·내 객체의 지정 버전을 독립 복사 |
| `POST /api/inventory/merges/preview` | 두 원본의 자동 병합 영역·충돌·검증 정보를 반환; 저장하지 않음 |
| `POST /api/inventory/merges` | 원본·선택을 재검증하고 새 병합 객체 생성 |
| `GET /api/posts` | 공개 게시글 검색·분류·태그·무기/역할 필터·정렬·페이지 전환 |
| `POST /api/posts` | 게시글과 첫 릴리스 생성 |
| `PATCH /api/posts/{id}` | 작성자가 게시글 관리 정보·공개 상태 수정 |
| `GET /api/posts/{id}` | 일반 진입은 최신 공개 릴리스와 게시글 집계 반환 |
| `GET /api/posts/{id}/releases` | 릴리스 이력 목록 |
| `GET /api/posts/{id}/releases/{number}` | 지정 공개 버전 조회 |
| `POST /api/posts/{id}/releases` | 새 릴리스 생성 |
| `PUT /api/posts/{id}/favorite` / `DELETE /api/posts/{id}/favorite` | 게시글 즐겨찾기 설정·해제 |
| `PUT /api/posts/{id}/rating` / `DELETE /api/posts/{id}/rating` | 게시글 별점 설정·해제 |
| `GET /api/me/posts` | 내 비공개·삭제 상태를 포함한 관리 목록 |

인벤토리 목록 예시는 `/api/inventory?type=equipment&equipmentType=sword&page=1`이다. 공개 목록은 즐겨찾기 수·평점·최근 업데이트 등의 명시적 정렬을 지원한다. 페이지 크기·허용 정렬·동점 정책은 서버에서 제한하고 응답에 페이지 정보를 제공한다. 마우스 휠 기반 무한 스크롤을 요구하지 않는다.

프론트 인벤토리는 `/inventory?type=build` 또는 `/inventory?type=equipment&equipmentType=sword&selected=객체ID` 같은 같은 작업 공간의 상태로 다룬다. `selected`는 상세 상태 표현의 예시이며 최종 키는 후속 결정이다. 도감·시뮬레이터·계산기에는 직접 접근 가능한 경로/탭 상태를 둔다. 게시판 프론트 URL은 API 경로와 별개로 미확정이다.

페이지 URL은 조회·선택·복귀를 표현하고 주소를 여는 것만으로 장비 적용·저장·게시를 확정하지 않는다. 인증 후 돌아올 위치는 같은 서비스의 허용 경로만 사용한다. 큰 초안·세션 토큰은 URL에 넣지 않는다.

### 공개·복사 v1 DTO

- 첫 공개는 `POST /api/posts`에 `{title,description?,tags?,source:{objectId,revision},scope?,release:{name,changeNotes?,gameVersion?}}`와 `Idempotency-Key`를 보낸다. 게시글과 첫 릴리스가 한 트랜잭션에서 생성된다. 새 객체 UUID를 클라이언트가 지정하지 않는다.
- 새 버전은 `POST /api/posts/{id}/releases`에 `{postRevision,source:{objectId,revision},scope?,release:{name,changeNotes?,gameVersion?}}`와 요청 키를 보낸다. 게시글 종류는 유지하며 제목·소개·태그 변경을 함께 보내지 않는다. 개인 원본 revision과 게시글 revision을 모두 검사한다.
- `scope`는 기본 `whole`, 빌드에서는 `status/equipment/skills/consumables/combos`를 선택할 수 있다. 선택 영역의 독립 객체 종류로 공개하며 다른 영역·context를 포함하지 않는다. 모든 종류는 인벤토리의 같은 검증기를 통과한다.
- 공개 스냅샷의 루트·하위 출처에서 개인 `inventory` ID를 제거한다. 도감·이미 공개된 릴리스 출처와 게임 데이터 정의는 유지한다. 작성자 응답에는 닉네임과 `isAuthor`를 제공하며 계정·소스 객체 ID를 불필요하게 공개하지 않는다.
- 제목·버전 이름은 80자, 소개 4000자, 변경 설명 2000자, 게임 버전 80자다. 태그는 24자 이내 최대 10개이며 중복을 제거한다. HTML로 실행하지 않는다. 게임 버전은 작성자가 선택적으로 기록하고 누락은 빈 값이다. `catalogVersions`는 고정 장비/도핑 데이터의 실제 cacheVersion 목록, 계산 규칙 버전은 확인되지 않으면 null이다.
- 상세 응답은 게시글 관리 정보·집계·`latestRelease` 요약과 선택한 `release`를 제공한다. 릴리스는 id/number/name/changeNotes/type/schemaVersion/gameVersion/catalogVersions/calculationRulesVersion/publishedAt/snapshot이다. 목록은 snapshot을 제외한다.
- 목록 조건은 `type/q/tag/equipmentType/sort/page/pageSize/favorites`, q는 제목·소개 부분 검색이다. sort는 recent/favorites, 기본 6개·최대 50개다. 초기 동점 정책은 updatedAt 내림차순·ID 오름차순이다. 장비 분류는 고정 구성의 주무기에서 추출한다. 역할 자동 분류는 하지 않는다. 공개 이력은 페이지당 6개다. `favorites=1`은 로그인한 사용자의 즐겨찾기만 반환하며 비로그인은 401이다.
- 게시글 관리는 `PATCH /api/posts/{id}`에 `{revision,title?,description?,tags?,visibility?}`를 보낸다. visibility는 public/private/deleted다. 삭제는 상태 보존이며 복구 정책을 확정하기 전 삭제 게시글을 다시 공개하지 않는다. 작성자는 내 관리 목록에서 비공개·삭제 상태를 확인할 수 있다. 공개 및 타인 조회는 SOURCE_UNAVAILABLE을 따른다.
- 공개 릴리스 복사는 `POST /api/inventory/copies`에 `{postId,releaseNumber,name?}`와 요청 키를 보낸다. 새 개인 객체에 `{kind:"release",postId,releaseNumber}` 출처를 붙인다. 새 원본 버전은 별도 복사이며 예전 사본을 갱신하지 않는다. 같은 요청 재시도는 원본이 이후 비공개가 되어도 최초 저장 결과를 재사용한다.
- 즐겨찾기 설정·해제는 빈 JSON `{}`를 보내고 사용자·게시글당 하나의 관계만 유지한다. 신규 버전에서 초기화하지 않는다. 복사 수를 즐겨찾기 수로 계산하지 않는다.
- `request-receipts.mjs`는 기존 병합 fingerprint를 보존하며 공개·릴리스·복사는 작업 종류와 대상 게시글까지 구분한다. 다른 작업/본문에서 같은 키를 재사용하면 409다.
- 최초 게시판 경로는 `/board?post=ID&release=번호`, 최신은 release 생략이다. 검색·선택·이력은 같은 작업 공간에서 전환하며 최종 URL 정책 변경 시 호환을 검토한다. 앱은 `index.html?view=board`에 같은 상태를 쓴다.
- 홈은 공개 build 게시글만 favorites 정렬로 조회한다. 기본 페이지는 PC 3개·모바일 1개이며 버튼으로 전환한다. 최신 버전·게임 버전·발행 날짜를 함께 표시한다. 공개되지 않은 데이터나 개인 저장 수로 순위를 만들지 않는다.

위 요청 형식은 별점 척도·별도 추천·구형 records 이관·도감 원본 복사·공개 원본과의 직접 병합까지 정하지 않는다. 해당 후속 범위와 실제 검증 상태는 현재 인계를 따른다.

## 5. 병합 요청 계약

- 원본은 정확한 개인 객체 ID와 `revision`, 또는 접근 가능한 고정 공개 릴리스를 지정한다. 두 원본만 비교하며 선택은 검증된 영역·부위·트리·카테고리 ID로 제한한다.
- 미리보기는 자동 결합 영역과 충돌 단위를 반환한다. 클라이언트는 큰 단위 선택 또는 허용 세부 선택을 제공한다. 별도 영구 병합 세션 테이블은 기본 범위가 아니다.
- 확정 요청은 원본 식별·기대 버전·선택·새 이름을 전달한다. 클라이언트가 만든 결과 JSON을 검증 없이 그대로 저장하지 않는다.

아래 트리 이름·ID는 형태 설명용이며 실제 구현은 게임 데이터의 고정 ID를 사용한다.

```json
{
  "left": { "objectId": "객체-A", "revision": 4 },
  "right": { "objectId": "객체-B", "revision": 2 },
  "name": "합친 빌드",
  "choices": [
    { "unit": "status", "take": "left" },
    { "unit": "equipment.mainWeapon", "take": "right" },
    { "unit": "equipment.armor", "take": "left" },
    { "unit": "skills.Blade", "take": "right" }
  ]
}
```

같은 영역의 `equipment` 전체 선택과 `equipment.mainWeapon` 등의 세부 선택을 동시에 보내면 거부한다. 스테이터스 개별 필드·장비 내부 옵션·개별 스킬 선택 경로는 받지 않는다. 도핑은 카테고리별, 콤보는 그대로 목록 결합, 외형은 선택 장비 귀속이다.

확정 시 소유권/공개 접근, 원본 수정 여부, 미해결·중복·모순 선택, 타입·게임 규칙을 다시 검증한다. 미리보기 후 원본 변경은 충돌로 돌려주고 원본이나 결과를 조용히 덮어쓰지 않는다. 저장은 새 객체 생성과 요청 재시도 결과 기록을 한 트랜잭션으로 처리한다.

외형 가져오기는 원본 조회 → 편집 초안의 외형 하위 데이터만 변경 → 기존 객체 저장 API를 사용하는 것으로 충분하다. 모든 UI 버튼에 별도 서버 API를 만들지 않는다. 장비/외형 ID·부위 호환은 저장 경계에서 검증한다.

## 6. 공개·복사·평가 트랜잭션

1. 공개 요청은 소유 객체 ID·기대 수정 번호·공개 범위·릴리스 메타정보를 전달한다. 서버가 해당 시점의 전체/부분 구성을 읽고 검증·고정한다. 클라이언트가 보낸 작성자/소유자 ID는 권한 근거가 아니다.
2. 공개 구성·릴리스 설명 수정은 새 릴리스다. 제목·소개 등 게시글 관리 정보는 별도 수정 번호로 처리하며 범위는 후속 UI에서 명확히 한다.
3. 게시글 생성과 첫 릴리스, 후속 릴리스 번호 할당과 최신 릴리스 갱신은 각각 원자적으로 처리한다. 동시 공개·재시도에서 번호가 중복되거나 빈 최신 링크가 생기지 않아야 한다.
4. 복사 시 서버가 지정 출처·버전의 접근성을 확인해 새 개인 객체·소유자·생성 시각을 부여하고 출처를 기록한다. 같은 출처의 다른 복사본은 허용한다. 기존 객체를 이름/출처 기준으로 자동 갱신하지 않는다.
5. 게시글 즐겨찾기/별점은 설정·해제에 따라 한 사용자 관계만 갱신한다. 새 릴리스에서 이전 관계·집계를 초기화하지 않는다. 공개 인기 목록은 공개 게시글과 그 최신 공개 릴리스를 사용한다.
6. 특정 버전 출처는 유지한다. 원본 비공개/삭제 시 공개 조회는 상세 데이터 대신 `SOURCE_UNAVAILABLE`과 접근 불가 메시지를 반환한다. 개인 복사본·고정 부모 스냅샷은 바뀌지 않는다.

## 7. 인증·검증·오류

- 공개 목록·접근 가능한 공개 릴리스 조회와, 로그인 필수인 개인 저장·복사·평가·게시를 구분한다. 작성자 관리 경로는 별도 소유권 검증을 한다.
- Google OAuth·웹 HttpOnly 쿠키·앱 메모리 Bearer·Origin/JSON·요청 제한·본문 크기 제한 등 [기존 인증 계약](account-home-server.md)을 유지한다. 여러 UI 진입점이 권한을 추가하지 않는다.
- 모든 객체 타입에 필수 필드·수치/키/ID·배열/깊이/크기·호환성을 검증한다. 설명/마크업에서 임의 HTML·스크립트를 실행하지 않는다. 기존 장비·스킬·도핑 규칙을 UI별로 복제하지 않는다.
- 수정 요청은 기대 `revision`을 확인한다. 다른 사용자의 개인 ID나 공개 불가 원본을 통해 비공개 내용을 추측할 수 있게 상세를 반환하지 않는다.
- 오류는 기존 클라이언트의 `error` 문자열을 유지하면서 기계 판독용 `code`·필요한 충돌 정보를 제공한다. 잘못된 요청 400, 로그인 필요 401, 찾을 수 없거나 접근 불가 404, 수정/선택 충돌 409, 크기 초과 413을 기본으로 한다.
- `Idempotency-Key`에 해당하는 요청 키를 복사·병합 저장·공개 같은 생성 요청에서 사용한다. 같은 키와 다른 요청의 조합도 409로 구분한다. 실패해도 초안은 보존한다.

## 8. 기존 저장·실행·배포 호환

- 기존 `records`의 `builds`·`items`·`favorites`는 새 개인 객체로 손실 없이 이관한다. 특히 기존 favorites는 장비 스냅샷이며 신규 게시글 즐겨찾기 관계가 아니다. 중복처럼 보여도 임의 삭제하지 않는다.
- `toram-auto-build-document` v2·`toram.account-item.v1`·앱/웹 자동 복원의 경계를 보존한다. 구형 API를 새 형식과 같은 이름으로 조용히 재해석하지 않는다. 이관·구형 경로/어댑터·백업/복구를 함께 검증한다.
- 기존 빌드의 단일 콤보와 새 콤보 객체 목록을 변환할 때 손실을 숨기지 않는다. 구형 내보내기는 선택한 콤보만 가능한지 명시하거나 지원 불가를 알린다. 정확한 DTO와 변환 규칙은 별도 확정한다.
- 장비·소모품의 ID·버전·정의 스냅샷, 수동 옵션, 장비 잠금·빈 잠금·제외 목록, Scenario·Request 경계는 유지한다. UI 재배치가 계산 계약을 바꾸지 않는다.
- 페이지 직접 접근/새로고침을 위해 허용 페이지 경로에 프론트 진입 문서를 제공한다. 없는 `/api/`·정적 자산까지 HTML로 처리하지 않는다. 기존 Worker/WASM 경로·공유 메모리 헤더를 유지한다.
- 정확한 제품 1.x 번호·DB 이관·배포 순서·실제 도메인/HTTPS/OAuth 검증은 후속 출시 작업이다. 세션·OAuth 대기·요청 기록의 운영 수명과 사용자 콘텐츠의 영구 수명을 구분한다.

## 9. 검증 Gate

- 원본 수정/삭제와 독립 복사, 단일/중간 객체의 조립·부분 공개·저장 왕복, 수정 충돌·요청 재시도를 검증한다.
- 장비 전체/부위·스킬 전체/트리·스테이터스 전체·도핑 카테고리·콤보 중복 유지·외형의 실제 ID 복사를 각각 검증한다.
- 게시글 최신/특정 릴리스·고정 이력·누적 평가·접근 불가 출처·비공개 소유권이 여러 진입점에서 일치해야 한다.
- 여러 원본 변경·동시 공개·같은 즐겨찾기/별점 재전송에서도 중복·부분 저장이 없어야 한다.
- 이관은 실제 저장 fixture·백업/복원·구버전 왕복으로 검증한다. 계산 변경은 기존 S1/회귀/정확성 Gate를 유지하며 실제 로그인·Docker·배포 검증과 구별한다.
- 문서만 변경하는 작업의 검증은 `node tools/verification/audit-ai-context.mjs`·`git diff --check`다. 이 문서의 확정이 위 구현 Gate 통과를 뜻하지 않는다.

인벤토리는 선택 전부터 기본 편집 초안을 표시하고 ‘내 목록’의 저장 요청에서만 새 객체를 register한다. 새로 만들기는 선택을 해제하고 기본 초안을 열며 DB 객체를 만들지 않는다. 이름은 같은 종류에서 비어 있는 ‘새 스킬트리’, ‘새 무기’ 등과 (n)을 사용하며 사용자 이름의 유일성을 DB에서 강제하지 않는다. 기존 객체는 같은 ID·revision으로 update하고, 변경 없는 수동 저장은 갱신하지 않는다. 기존 객체의 변경은 2분 주기와 편집 화면 이탈 때 저장한다. 기본 초안은 명시적 저장 전까지 메모리에 유지하고 계정 변경 시 폐기한다. revision은 내부 충돌 검사 값이며 수정 번호로 표시하지 않는다. 기존 DTO·schema와 계산기 세션 경계, 실패 시 URL/입력 보존, 트리/전체 병합 규칙과 snapshot 출처를 유지한다.

구형 보관함 이관: tools/migrate-records.mjs는 기본 읽기 전용 계획이며 명시적 적용 전에 SQLite 백업·무결성을 검사한다. 원본 records를 덮어쓰거나 삭제하지 않고, ID 매핑·원본 해시·삭제 표식으로 재실행과 부활을 막는다. 미지원/변경/충돌 자료는 보존·보고한다. 기존 구형 종류별 200개와 신규 인벤토리 종류별 200개의 독립 한도는 유지하며, 이관 자료를 한도 때문에 버리지 않는다. 운영 이관은 별도 유지보수 작업이다.
