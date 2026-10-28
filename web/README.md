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
| src/pages/catalog/ | 비로그인 아이템·보스 도감·조회 상태·상세 페이지 |
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

실행은 저장소 루트에서 npm run web:dev, 배포본 생성은 npm run web:build입니다. index.html의 assets/... URL은 개발 서버와 배포 도구가 원본 위치에 연결합니다. src/app-entry.mjs가 진입점, 실제 ESM import 그래프가 배포 파일과 Worker 의존성을 결정합니다.

계산기·인벤토리의 스킬 노드는 Shift+클릭하면 선택 스킬과 필요한 모든 선행 스킬을 Lv.10으로 투자합니다. 1/5/10 포인트 설정과 무관하며 다른 분기는 유지합니다. 선택 스킬이 이미 Lv.10이어도 선행 경로는 올리고, 전체 경로가 최대면 변경·저장을 발생시키지 않습니다. 일반 클릭·우클릭의 투자/회수는 기존 규칙을 유지합니다. `node tools/verification/verify-skill-shift-browser.mjs`로 웹 생성본의 두 화면·저장/복원을 검증합니다.

build/web/와 build/desktop/는 생성물이므로 직접 수정하지 않습니다.

index.html은 공통 틀과 홈 HTML을 소유합니다. app-entry.mjs는 기본 `/`을 홈으로 연결하고 각 페이지를 등록합니다. 계산기 HTML은 src/pages/calculator/calculator.html, 초기화는 같은 폴더 calculator-page.mjs에 있습니다. 계산기 진입·인벤토리 구성 담기/적용·계정의 현재 빌드 저장/불러오기에서만 ensureCalculator()를 기다립니다. 홈·도감·게시판·인벤토리 조회는 계산기를 로드하지 않습니다. 첫 로딩 후에는 DOM과 입력을 유지하며, 초기화 실패도 다른 페이지를 막지 않습니다. 표시용 스탯 이름은 application/stat-labels.mjs를 공유합니다.

웹 첫 화면은 `/` 홈이며 `/calculator` 계산기·`/inventory?type=equipment` 인벤토리·`/board?post=ID&release=번호` 게시판을 공통 메뉴로 전환합니다. 계산기 내부 탭·DOM·입력 상태는 유지합니다. 앱은 같은 페이지를 `index.html?view=home|calculator|inventory|board|catalog`로 전환합니다. 기존 계산기 전용 검증·하위 경로 정적 배포는 `?view=calculator`를 사용할 수 있습니다. 홈 순위는 공개 빌드 게시글의 즐겨찾기를 조회합니다. 최근 메뉴는 이 브라우저의 localStorage에 메뉴 ID만 저장합니다.

내 목록에 새로 만들기·저장을 두고 기본 편집 화면을 바로 표시합니다. 선택 없는 초안은 저장할 때 ‘새 스킬트리’, ‘새 무기’ 등으로 등록하며, 기존 선택은 같은 항목에 저장합니다. 이름은 목록에서 선택한 이름을 누르거나 F2로 수정합니다. 수정 번호·편집 하단 추가 버튼은 표시하지 않으며 변경은 2분 주기 또는 화면 이탈 시 저장합니다. 작업공간은 편집만 맡고 이름 입력·저장 하단·상시 안내를 두지 않습니다. 인벤토리의 ‘게시판에 공개’에서 전체 또는 빌드의 한 영역을 공개합니다. 게시판은 종류·검색·태그·즐겨찾기 정렬·내 글을 지원하고, 작성자는 관리 메뉴에서 새 버전·정보 변경·공개 상태를 다룹니다. ‘내 인벤토리에 복사’는 지정 버전의 독립 객체를 만듭니다. API 서버가 필요하며 정적 소스 개발 서버만으로는 계정·게시판 요청을 처리하지 않습니다.

도감은 `/catalog` 또는 앱의 `index.html?view=catalog`입니다. 왼쪽 대분류·아이템 분류 책갈피를 두 열로 고정하고 오른쪽 내용 영역 상단에서 검색하며, 그 아래 왼쪽 목록과 오른쪽 설명을 함께 봅니다. 무기 책갈피는 주무기·보조무기 구분 없이 13종과 전체 보기 팝업을 열고, 크리스타는 공용·무기·몸장비·추가장비·특수장비와 전체 보기를 제공합니다. 강화 크리스타도 원본 category에 따라 각 계열에 포함합니다. `subcategory` URL로 필터를 유지하며 종류 변경·초기화는 세부 필터를 해제합니다. 모바일은 분류 변경 버튼으로 두 열을 열고 팝업 선택 후 내용으로 돌아옵니다. 목록에서 설명으로 전환해도 검색 바를 유지합니다. 발행된 아이템 8분류·6언어와 보스를 이름/ID로 검색하고, 목록 페이지를 전환합니다. 상세는 이름·기초 ATK/DEF·설명·원문 옵션을 한 화면에서 스크롤하며, 빈 설명/옵션과 내부 연결/원본 정보는 표시하지 않습니다. 조건 제목과 해당 옵션을 연두색 계열로 구분합니다. 크리스타 강화 계보와 보스 지역/개체·난이도/레벨별 수치를 조회합니다. 원본·미연결 효과를 보존하며 계산기 입력·인벤토리를 바꾸지 않습니다. 계정 API 없이 정적 개발 서버에서도 동작합니다. 도감에서 인벤토리에 담기는 후속 범위입니다.

보스를 선택하면 두 번째 책갈피 열에 전체·입장보스·필드보스·이벤트보스·고난도보스를 표시합니다. 입장/필드/고난도는 원본 classification으로 목록과 상세 개체를 함께 필터링하고 `bossKind` URL로 유지합니다. 이벤트보스는 기간·맵별 분리를 보류하고 준비 중 안내만 제공합니다. 전체 보스에는 길드·던전·미분류도 유지합니다.

웹 정밀 추천은 공유 메모리 WASM 스레드 풀을 사용합니다. 브라우저가 보고한 논리 코어 수를 최대64개까지 사용하며, 빠른 추천의 세션·트리를 그대로 이어받습니다. 개발 서버와 계정 서버는 다음 헤더를 제공합니다. 다른 정적 호스트에도 HTML·Worker·WASM·중첩 모듈에 같은 헤더를 설정하고 HTTPS(로컬은 localhost)를 사용해야 합니다.

    Cross-Origin-Opener-Policy: same-origin
    Cross-Origin-Embedder-Policy: require-corp

crossOriginIsolated 또는 SharedArrayBuffer를 사용할 수 없으면 단일 WASM으로 실행합니다. 외부 리소스는 CORS/CORP 허용이 필요합니다. 현재 폰트·게임 데이터·스크립트는 같은 출처에서 제공합니다. 서버 설정을 바꾼 뒤에는 페이지를 새로고침합니다.

일반 계산도 공통 Rust evaluator의 WASM을 사용합니다. 입력·옵션 조립과 툴팁 문자열은 JS에 남기고, 전체/요약/후보 공급값·정수 비율 산술을 Rust가 소유합니다. 계산기 진입 때 모듈 초기화를 기다리며 홈·도감·계정은 독립적입니다. WASM을 차단하거나 자산을 읽지 못하면 계산기 오류를 표시하며 홈·계정은 유지됩니다.
