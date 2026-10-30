# 개발 도구와 검사

명령은 루트 package.json에서 실행한다. 제품 원본은 web/·desktop/·engine/이며 도구에 별도 계산기를 만들지 않는다. 설치·빌드는 루트 README, 작업별 진입점은 docs/ai-context-guide.md를 따른다.

| 위치 | 역할 |
| --- | --- |
| prepare-frontend.mjs, web-dev.mjs | 배포본 조립·실제 계정 API를 포함한 개발 서버 |
| support/frontend-paths.mjs | 배포 URL과 원본 대응 |
| build-wasm.mjs | stable 단일·pinned nightly 공유 메모리 WASM 생성 |
| extraction/ | 아이템·보스·레지스트렛 추출·수동 갱신 |
| tests/, fixtures/, regression-fixtures.mjs | 회귀·입력·분류 (동작 검증의 단일 실행 목록) |
| verification/ | 구조·출처·브라우저 검사 |
| benchmarks/, support/ | 계측·테스트 지원 |
| statting/ | 앱과 분리된 옵부 실험 |

`npm test`는 프론트엔드 준비·타입·모듈 경계·S1·JS 회귀·Rust fmt/test/clippy를 실행한다. tests/의 test-*.mjs는 분류 목록과 대조하며 새 검사는 normalValue 또는 characterization에 등록한다. 실제 앱 저장 E2E는 TORAM_E2E_CDP가 없으면 SKIP이다.

브라우저는 Chrome과 기존 Playwright를 사용한다. CODEX_PLAYWRIGHT_PATH에 모듈 경로를 지정하고 생성본 검사 전 web:build를 실행한다.

| tools/verification/ 스크립트 | 범위 |
| --- | --- |
| verify-web-browser.mjs, verify-session-restore-browser.mjs, verify-web-parallel.mjs | 소스·하위 경로·계산·저장·WASM 정밀/취소/재개·격리 없는 fallback |
| verify-platform-startup-browser.mjs | 홈 독립 로딩·계산기 최초 1회 초기화·입력 유지·실패 격리 |
| verify-catalog-browser.mjs [--web] | 도감 검색·번역·계보·보스 선택·반응형·읽기 전용 |
| verify-registlet-browser.mjs [--source] | 웹 생성본/소스 효과별2열·실시간 수식/결과·스컬 스택·재료별 강화·별도 슬롯표·담기/복원·모바일 |
| verify-inventory-browser.mjs | 홈·계정·내 구성·병합·계산기 왕복 |
| verify-inventory-authoring-browser.mjs | 직접 등록·책갈피·트리 편집·2분/이탈 저장·실패 보존 |
| verify-posts-browser.mjs | 공개·버전·즐겨찾기·독립 복사·409 초안 |
| verify-skill-shift-browser.mjs | 계산기/인벤토리 Shift+클릭·저장 복원 |
| verify-update-browser.mjs, verify-food-browser.mjs | 앱 업데이트 어댑터(mock 설치)·요리 |

브라우저 검사는 임시 서버·별도 DB를 사용하며 Google 실인증·공개 배포를 보증하지 않는다. 결과는 build/ 또는 Rust target/에 둔다. pipeline 이력·추출 근거·계정 DB·저장 샘플은 캐시와 구분해 보존한다.

Google 키 없는 로컬 체험은 `node tools/preview-platform.mjs` → http://127.0.0.1:5182/__preview 이며 build/tmp/platform-preview/accounts.sqlite를 사용한다. 모든 체험 브라우저가 같은 계정을 공유한다. 운영 인증은 server/README.md를 따른다.
