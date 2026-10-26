# 개발 도구와 검사

실행 명령은 저장소 루트의 package.json에 모읍니다. 제품 원본은 ../web/·../desktop/·../engine/이며, 도구에 별도 계산기를 만들지 않습니다.

| 위치 | 역할 |
| --- | --- |
| prepare-frontend.mjs, web-dev.mjs | 공통 원본으로 배포본 조립·개발 서버 |
| support/frontend-paths.mjs | 배포 URL과 원본 파일의 대응 |
| build-wasm.mjs | 공용 Rust를 WASM으로 빌드 |
| extraction/ | 아이템·보스 원문 가공·수동 갱신 |
| tests/, fixtures/, regression-fixtures.mjs | 회귀 테스트·입력·분류 |
| verification/ | 구조·출처·실제 브라우저 검사 |
| benchmarks/, support/ | 계측·테스트 지원 |
| statting/ | 앱과 분리된 옵부 오프라인 실험 |

결과물은 ../build/ 또는 Rust target/에 씁니다. 주요 검사: npm run verify:architecture, test:regression, verify:web:browser, ai:audit.

wasm:build는 stable 단일 WASM과 pinned nightly 공유 메모리 WASM/Worker snippets를 함께 생성합니다. 설치 명령은 루트 README를 따릅니다. prepare-frontend는 parallel/ 하위 모듈도 함께 복사합니다. verify-web-parallel.mjs는 실제 Chrome에서 스레드별 정답·제어·풀 폐기·격리 없는 fallback과 반복 시간을 검사합니다.

브라우저 검증은 사용자 요청에 따라 Chrome을 사용합니다. CODEX_PLAYWRIGHT_PATH에 설치된 Playwright 경로를 지정합니다. 홈·인벤토리 검증은 웹 배포본 준비 후 node tools/verification/verify-inventory-browser.mjs로 실행합니다. 별도 임시 DB·18784 loopback 포트를 사용하며 실제 Google 인증을 대체하지 않습니다. 화면 증거는 OS 임시 폴더에 남깁니다.

직접 등록·책갈피 검증은 node tools/verification/verify-inventory-authoring-browser.mjs입니다(Chrome·별도 임시 DB·18788 포트). 계산기 없는 장비 입력→저장→새로고침→공개, 부위/무기·개별 트리/스킬셋·도핑 계열/셋 필터, URL·뒤로가기·키보드 포커스·입력 실패/초안 보호와 PC/노트북/모바일을 확인합니다. 고정 두 열(빈 소분류 포함)과 3열 자리의 세로 팝업 크기·배경 필터 없음·선택/취소·제목 경로를 검사하고, 전체 선택의 하위 없음·실제 트리 전부 표시·55개 객체의 한 화면 조회·계산기 공통 책갈피 유지도 확인합니다. 좌우 목록/작업공간과 버튼 소속, 기본 초안의 저장 전 비등록·기존 ID 저장·변경 없는 저장 생략·종류별 이름·목록 내 이름 수정·440px 목록과 버튼 위치·1920/1366/1280/390px 트리 맞춤·불필요한 버튼/수정 번호/편집 이름/저장 하단/안내 제거, 단일 트리·스킬셋 편집·트리 조립/충돌, Chrome 가상 시계로 즉시 저장 없음·2분당 한 번 저장·변경 없는 주기 저장 없음, 화면 전환 전 저장·실패 보존·계산기 상태 독립성도 검사합니다. API/입력 및 공유 시뮬레이터 단위 검증은 test-inventory-composition.mjs와 test-account-client.mjs에 포함됩니다.

초기 표시 회귀는 node tools/verification/verify-platform-startup-browser.mjs입니다. Chrome에서 진입 모듈·계산기 HTML 응답을 보류해 홈 HTML 분리·다른 페이지의 계산기 요청 없음·직접 링크·최초 1회 초기화·로딩 중 메뉴 이동·모바일·스킬 탭·입력 유지·실패 격리를 확인합니다. 소스 개발 서버와 임시 포트를 사용합니다. verify-inventory-browser.mjs는 인증된 새 탭에서도 조회/이름 수정은 독립 동작하고, 적용/구성 담기만 계산기 준비를 기다리는지 확인합니다.

test:account는 개인 저장·10종 구성·조립/충돌·요청 키 재시도를 검사합니다. 새 test-inventory-composition.mjs는 regression-fixtures.mjs의 normalValue에 등록되어 전체 회귀에도 포함됩니다. 브라우저 검사는 홈 비로그인/계정 카드·최근 메뉴·계산기 입력 유지·직접 URL/새로고침/뒤로 가기·모바일 화면과 세팅 조립→부분/전체 빌드→부위별/전체 선택, 원본 변경 뒤 409 초안 보존, 중복 콤보 적용/개별 제거를 확인합니다.

공개 기능은 배포본 준비 후 node tools/verification/verify-posts-browser.mjs로 검증합니다(Chrome·별도 DB·18787 포트). 비로그인 검색/홈 순위, 공개/새 버전/이력, 즐겨찾기 유지, 독립 복사, 비공개 원본 안내와 409 초안을 확인합니다. test:account는 test-post-store.mjs도 실행하며 전체 회귀에는 10종 공개/복사 왕복과 개발 체험 서버 test-platform-preview.mjs가 포함됩니다.

Google 키 없는 로컬 체험은 npm run web:preview → http://127.0.0.1:5182/__preview입니다. build/tmp/platform-preview/accounts.sqlite를 사용하며 모든 체험 브라우저가 같은 계정을 씁니다. 운영 인증 경로는 변경하지 않습니다.

도감 검증은 node tools/tests/application/test-catalog-browser.mjs와 CODEX_PLAYWRIGHT_PATH를 지정한 node tools/verification/verify-catalog-browser.mjs입니다. 발행 아이템 전체의 표시 행, 미연결 효과 보존, URL·검색·언어·강화 계보·보스 난이도, PC/노트북/모바일을 확인합니다. Chrome 테스트는 소스 개발 서버를 임시 포트에 띄우며 계정 API 호출·계산기 입력 변경이 없는지도 검사합니다. 인벤토리/저장 동작은 도감 범위에 추가하지 않습니다.
