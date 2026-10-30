# 공통 웹 화면

웹과 데스크톱이 같은 화면 원본을 사용합니다. 데스크톱 전용 기능은 ../desktop/에 있습니다.

화면 변경 후 생성본을 사용하는 서버/앱을 확인할 때는 `node tools/prepare-frontend.mjs web`과 `node tools/prepare-frontend.mjs desktop`으로 갱신합니다. 도감 브라우저 검증은 기본으로 소스를 제공하며, `node tools/verification/verify-catalog-browser.mjs --web`은 실제 `build/web`을 검증합니다. 보스 전환 전후 책갈피 두 열의 위치·크기도 비교합니다.

| 위치 | 고치는 내용 |
| --- | --- |
| index.html | 화면 구조·입력 요소 |
| src/layout/ | 공통 사이드바·탑바·페이지 전환 |
| src/pages/home/ | 홈 순위 영역·계정 카드·최근 메뉴 |
| src/pages/calculator/ | 계산기 HTML·최초 사용 시 ESM 초기화 |
| src/pages/inventory/ | 내 구성 목록·상세·조립 UI |
| src/pages/inventory/inventory-navigation.mjs | 고정 두 열·3열 위치의 세로 선택 팝업·제목 옆 경로; 전체는 하위 없음 |
| src/pages/inventory/inventory-equipment-editor.mjs | 계산기와 독립된 새 장비 직접 등록 |
| src/pages/board/ | 공개 목록·고정 버전 이력·공개/새 버전 입력 |
| src/pages/catalog/ | 비로그인 아이템·보스·레지스트렛 도감·상세·레지스트렛 담기 |
| src/pages/inventory/inventory-skill-editor.mjs | 트리·셋 편집/조립; 2분·이탈 시 변경 저장 |
| src/ui/skill-tree-simulator.mjs | 계산기·인벤토리 공통 스킬 트리 렌더링/선행 투자/회수, 호출자별 상태 |
| src/ui/ | 화면 표시·이벤트; bookmark-button.mjs는 계산기·인벤토리·도감 공통 책갈피 |
| src/application/ | 입력 상태·사용자 동작·계산 조립 |
| src/calculation/ | 효과 적용·Rust/WASM 호출·표시 문자열 |
| src/optimization/ | 추천 입력 준비·Rust/WASM 연결·실행 선택 |
| src/storage/ | 공통 저장 형식·자동 복원·JSON 가져오기/내보내기 |
| src/data/ | 스킬·게임 규칙 정의 |
| src/contracts/ | 실제 저장·업데이트 어댑터의 TypeScript 계약 |
| public/ | CSS·폰트·아이콘·발행된 아이템/보스 데이터 |

실행은 저장소 루트에서 npm run web:dev, 배포본 생성은 npm run web:build입니다. 개발 서버는 server/.env를 읽고 기본 http://localhost:8787/에서 소스 화면과 실제 계정·Google 로그인·저장/게시판 API를 함께 제공합니다. index.html의 assets/... URL은 개발 서버와 배포 도구가 원본 위치에 연결합니다. src/app-entry.mjs가 진입점, 실제 ESM import 그래프가 배포 파일과 Worker 의존성을 결정합니다.

계산기·인벤토리의 스킬 노드는 Shift+클릭하면 선택 스킬과 필요한 모든 선행 스킬을 Lv.10으로 투자합니다. 1/5/10 포인트 설정과 무관하며 다른 분기는 유지합니다. 선택 스킬이 이미 Lv.10이어도 선행 경로는 올리고, 전체 경로가 최대면 변경·저장을 발생시키지 않습니다. 일반 클릭·우클릭의 투자/회수는 기존 규칙을 유지합니다. `node tools/verification/verify-skill-shift-browser.mjs`로 웹 생성본의 두 화면·저장/복원을 검증합니다.

build/web/와 build/desktop/는 생성물이므로 직접 수정하지 않습니다.

index.html은 공통 틀과 홈 HTML을 소유합니다. app-entry.mjs는 기본 `/`을 홈으로 연결하고 각 페이지를 등록합니다. 계산기 HTML은 src/pages/calculator/calculator.html, 초기화는 같은 폴더 calculator-page.mjs에 있습니다. 계산기 진입·인벤토리 구성 담기/적용·계정의 현재 빌드 저장/불러오기에서만 ensureCalculator()를 기다립니다. 홈·도감·게시판·인벤토리 조회는 계산기를 로드하지 않습니다. 첫 로딩 후에는 DOM과 입력을 유지하며, 초기화 실패도 다른 페이지를 막지 않습니다. 표시용 스탯 이름은 application/stat-labels.mjs를 공유합니다.

웹 첫 화면은 `/` 홈이며 `/calculator` 계산기·`/inventory?type=equipment` 인벤토리·`/board?post=ID&release=번호` 게시판을 공통 메뉴로 전환합니다. 계산기 내부 탭·DOM·입력 상태는 유지합니다. 앱은 같은 페이지를 `index.html?view=home|calculator|inventory|board|catalog`로 전환합니다. 기존 계산기 전용 검증·하위 경로 정적 배포는 `?view=calculator`를 사용할 수 있습니다. 홈 순위는 공개 빌드 게시글의 즐겨찾기를 조회합니다. 최근 메뉴는 이 브라우저의 localStorage에 메뉴 ID만 저장합니다.

내 목록에 새로 만들기·저장을 두고 기본 편집 화면을 바로 표시합니다. 선택 없는 초안은 저장할 때 ‘새 스킬트리’, ‘새 무기’ 등으로 등록하며, 기존 선택은 같은 항목에 저장합니다. 이름은 목록에서 선택한 이름을 누르거나 F2로 수정합니다. 수정 번호·편집 하단 추가 버튼은 표시하지 않으며 변경은 2분 주기 또는 화면 이탈 시 저장합니다. 작업공간은 편집만 맡고 이름 입력·저장 하단·상시 안내를 두지 않습니다. 인벤토리의 ‘게시판에 공개’에서 전체 또는 빌드의 한 영역을 공개합니다. 게시판은 종류·검색·태그·즐겨찾기 정렬·내 글을 지원하고, 작성자는 관리 메뉴에서 새 버전·정보 변경·공개 상태를 다룹니다. ‘내 인벤토리에 복사’는 지정 버전의 독립 객체를 만듭니다. npm run web:dev가 실제 계정·게시판 API와 소스 화면을 함께 제공하며 운영 배포는 별도 계정 서버 설정을 사용합니다.

도감은 `/catalog` 또는 앱의 `index.html?view=catalog`입니다. 왼쪽 대분류·아이템 분류 책갈피를 두 열로 고정하고 오른쪽 내용 영역 상단에서 검색하며, 그 아래 왼쪽 목록과 오른쪽 설명을 함께 봅니다. 무기 책갈피는 주무기·보조무기 구분 없이 13종과 전체 보기 팝업을 열고, 크리스타는 공용·무기·몸장비·추가장비·특수장비와 전체 보기를 제공합니다. 강화 크리스타도 원본 category에 따라 각 계열에 포함합니다. `subcategory` URL로 필터를 유지하며 종류 변경·초기화는 세부 필터를 해제합니다. 모바일은 분류 변경 버튼으로 두 열을 열고 팝업 선택 후 내용으로 돌아옵니다. 목록에서 설명으로 전환해도 검색 바를 유지합니다. 발행된 아이템 8분류·6언어와 보스를 이름/ID로 검색하고, 목록 페이지를 전환합니다. 상세는 이름·기초 ATK/DEF·설명·원문 옵션을 한 화면에서 스크롤하며, 빈 설명/옵션과 내부 연결/원본 정보는 표시하지 않습니다. 조건 제목과 해당 옵션을 연두색 계열로 구분합니다. 크리스타 강화 계보와 보스 지역/개체·난이도/레벨별 수치를 조회합니다. 원본·미연결 효과를 보존하며 아이템·보스는 조회만 합니다. 조회는 계정 API 없이도 동작합니다. 아이템의 인벤토리 담기는 후속 범위입니다.

보스 상세는 HP·속성·레벨·회피·어보이드율·가드율·DEF/MDEF·물리/마법 내성·크리티컬 저항·관성 변동률(%p)·난이도·지역/페이즈를 표시합니다. 시스템 설명이나 ‘원본’ 접미사를 붙이지 않으며 불명 값은 미확정으로 표시합니다. 지역과 개체/페이즈 선택을 분리하고 선택지가 하나면 입력을 숨깁니다. 같은 UUID·지역의 명시적 mode 참조만 페이즈로 식별합니다. 페이즈 변경은 호환되는 난이도·입장 레벨을 유지합니다. 일반 난이도는 선택 즉시 갱신하고 고난도/길드 레이드는 레벨 입력 후 ‘수치 보기’로 반영합니다. 회피/어보이드의 데이터 의미·범위는 `../data/sources/toram-monsters/native-hit-accuracy/README.md`를 따르며 저장·계산 계약은 유지합니다.

레지스트렛은 `section=registlets`에서166종·6언어를 이름/ID로 검색합니다. 두 번째 책갈피 열은 전체·기본 능력10종·상태이상 대응16종·전투/편의32종·스킬 변경108종의 도감용 효과 분류입니다. 레벨 입력 즉시 효과·수식·값 대입·결과가 갱신되며 확인 버튼은 없습니다. 파워 웨이브·스컬 셰이커는 관련 스킬 Lv도 지정합니다. 스컬 셰이커는 스택 상한과 최대 스택의 무기별 계수를 표시합니다. 강화 비용은 동일 종류 재료와 다른 종류 재료를 나누고, 재료1개 기준 비용·도달 레벨을 비교합니다. 슬롯 확장9단계 비용/누적 비용은 두 번째 열의 별도 ‘슬롯 확장’ 화면에 둡니다. 로그인 후 ‘인벤토리에 담기’를 누르면 해당 젬과 레벨을 저장하고, ‘인벤토리 보기’로 바로 이동합니다. 인벤토리 레지스트렛 분류(`type=registlet`)에서도 젬 선택·새 등록·레벨 수정·이름 변경·삭제·공개를 지원합니다. 저장 당시 원문·ID·버전을 보존하며 기존 자동 저장/실패 보존을 사용합니다. 설명 수치는 native UI 표시식이고 전투 계산/빌드 조립은 연결하지 않습니다. 미관측 획득처3종과 보상 드롭률은 추정하지 않습니다. 발행은 `node tools/extraction/publish-toram-registlets.mjs [--check]`, 검증은 `test-registlet-catalog.mjs`와 `verify-registlet-browser.mjs [--source]`입니다.

장비 아이콘은 `src/ui/equipment-icons.mjs`의 공통 대응표로 도감 분류·목록·상세와 인벤토리 장비 분류·목록·종류 편집에 표시합니다. 게임 typeId와 인벤토리 equipmentType을 연결하며 저장 데이터에 이미지 경로를 넣지 않습니다. 마켓 검색의 종류 아이콘을 사용하고, 원본·해시는 `data/sources/game-ui/equipment-icons.json`, 배포 이미지는 `public/icons/equipment/`에 둡니다. 맨손·없음에는 다른 장비 아이콘을 대입하지 않습니다.

크리스타는 같은 대응표의 `CRYSTA_ICONS`를 사용합니다. 마켓의 공용(파랑)·무기(빨강)·몸장비(초록)·추가장비(노랑)·특수장비(보라)를 도감 분류·목록·상세에 연결하고 강화 크리스타도 원본 category를 따릅니다. 전체·대표 아이콘과 인벤토리 크리스타 탭/슬롯 라벨은 회색 빈 크리스타입니다. 원본·해시는 `data/sources/game-ui/crysta-icons.json`, 배포 이미지는 `public/icons/crystas/`에 둡니다.

도감의 아이템/전체 아이템과 공통 메뉴·홈 최근 메뉴의 인벤토리는 게임 ESC 메뉴의 갈색 배낭을 공유합니다. 게시판 메뉴는 ‘길드 알림을 본다’ 옆 녹색 게시판, 도감 메뉴는 대비·깃펜 크기를 높인 책·깃펜 79×69 PNG를 사용합니다. 도감 아이콘은 게임 책·깃펜을 참고한 AI 재구성 이미지이며 원본/생성 지시를 `data/sources/game-ui/custom/catalog-book-quill-v2/`에 보존합니다. `src/ui/game-menu-icons.mjs`의 경로와 `data/sources/game-ui/menu-icons.json`의 원본/해시를 사용합니다.

보스를 선택하면 두 번째 책갈피 열에 전체·입장보스·필드보스·이벤트보스·고난도보스를 표시합니다. 입장/필드/고난도는 원본 classification으로 목록과 상세 개체를 함께 필터링하고 `bossKind` URL로 유지합니다. 이벤트보스는 기간·맵별 분리를 보류하고 준비 중 안내만 제공합니다. 전체 보스에는 길드·던전·미분류도 유지합니다.

웹 정밀 추천은 공유 메모리 WASM 스레드 풀을 사용합니다. 브라우저가 보고한 논리 코어 수를 최대64개까지 사용하며, 빠른 추천의 세션·트리를 그대로 이어받습니다. 개발 서버와 계정 서버는 다음 헤더를 제공합니다. 다른 정적 호스트에도 HTML·Worker·WASM·중첩 모듈에 같은 헤더를 설정하고 HTTPS(로컬은 localhost)를 사용해야 합니다.

    Cross-Origin-Opener-Policy: same-origin
    Cross-Origin-Embedder-Policy: require-corp

crossOriginIsolated 또는 SharedArrayBuffer를 사용할 수 없으면 단일 WASM으로 실행합니다. 외부 리소스는 CORS/CORP 허용이 필요합니다. 현재 폰트·게임 데이터·스크립트는 같은 출처에서 제공합니다. 서버 설정을 바꾼 뒤에는 페이지를 새로고침합니다.

일반 계산도 공통 Rust evaluator의 WASM을 사용합니다. 입력·옵션 조립과 툴팁 문자열은 JS에 남기고, 전체/요약/후보 공급값·정수 비율 산술을 Rust가 소유합니다. 계산기 진입 때 모듈 초기화를 기다리며 홈·도감·계정은 독립적입니다. WASM을 차단하거나 자산을 읽지 못하면 계산기 오류를 표시하며 홈·계정은 유지됩니다.
