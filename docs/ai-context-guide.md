# 작업 진입점

필독 순서는 AGENTS.md를 따른다. 현재 상태는 docs/handoff/current-development-handoff.md, 실제 코드·이번 테스트로 판단한다.

| 작업 | 코드 | 검증 |
| --- | --- | --- |
| 화면·입력 | web/src/ui/ui-bootstrap.js, build-draft-store.js, 해당 UI 파일 | Application 회귀·실제 브라우저 |
| 계산 조립 | web/src/application/application-use-cases.js, calculation-policies.js | 해당 계산 회귀 |
| 전체/요약/공급값 수식 | engine/src/evaluator.rs; web/src/calculation/calculator.js는 조립·표시 | test-evaluator-integration.mjs, Rust full golden·기존 상한 Gate |
| 스킬·계산식 | web/src/calculation/skill-effect-engine.js, data/skills/ | 원문·스킬 검증 기준·S1 및 해당 트리 |
| 추천 코어 | engine/src/ | Rust 단위 테스트·WASM 완전탐색 회귀 |
| 후보 준비 | web/src/optimization/candidate-preparation.js, problem-compiler.js | 축소 전후 exhaustive·raw/동점 검사 |
| 추천 실행 | web/src/optimization/{execution-adapter,rust-bridge,wasm-client,wasm-worker}.js, desktop/adapters/optimization-client.js | 실행·취소·재개·Native 경계 |
| Native 수명 | desktop/src/optimization/ | 서비스·병렬 실행 Rust 테스트 |
| 저장·업데이트 | web/src/storage/, desktop/adapters/, desktop/src/{settings,update_service}.rs | 저장 계약·세션 복원 브라우저 |
| 계정·홈 서버 | web/src/application/account-client.mjs, web/src/ui/account-ui.mjs, server/account-server.mjs, desktop/src/account_browser.rs | npm test, docs/architecture/account-home-server.md |
| 종합 플랫폼 설계 | [제품·객체·병합 기준](architecture/platform-design-contract.md) → [DB/API 계약](architecture/platform-data-api-contract.md) | 사용자 확정 범위·후속 결정·구현 Gate 확인; 설계 확정과 구현 완료 구분 |
| 홈·공통 탐색 | web/src/layout/platform-shell.mjs, web/src/pages/home/home-page.mjs, web/public/css/{platform,home}.css | verify-inventory-browser.mjs (Chrome): 비로그인·계정·최근 메뉴·PC/모바일·계산기 유지 |
| 기본 페이지·계산기 분리 | web/index.html(공통 틀·홈), web/src/app-entry.mjs, web/src/pages/calculator/ | verify-platform-startup-browser.mjs: 다른 페이지의 계산기 요청 없음·지연/중복 초기화·메뉴 이동·실패 격리; 저장 복원·계정/인벤토리 왕복 |
| 도감 조회 | web/src/application/catalog-browser.mjs, web/src/pages/catalog/, web/public/css/catalog.css | test-catalog-browser.mjs, verify-catalog-browser.mjs (Chrome): 검색·번역·원문·계보·보스 선택·읽기 전용 |
| 공개·릴리스·복사·즐겨찾기 | server/{post-store,request-receipts}.mjs, web/src/pages/board/, application/account-client.mjs | test:account, test-post-store.mjs, verify-posts-browser.mjs (Chrome): 버전/사본 독립·권한·검색·홈 순위·409 초안 |
| 인벤토리·조립 | web/src/application/{equipment-object,inventory-objects,inventory-merge,account-client}.mjs, web/src/pages/inventory/, server/inventory-{store,rules}.mjs | test:account, verify-inventory-browser.mjs (Chrome), 기존 저장 왕복; DTO는 플랫폼 DB/API 계약 |
| 빌드 | tools/support/frontend-paths.mjs, tools/prepare-frontend.mjs, tools/web-dev.mjs | npm test; 실제 배포본은 verify-es-module-entry.mjs --web/--dist |
| 게임 아이템 갱신 | tools/extraction/update-toram-items.py, toram-item-pipeline-contract.json | --self-test, docs/verification/toram-item-pipeline.md |
| 레지스트렛 추출 | tools/extraction/extract-toram-registlets.py, data/sources/toram-registlet/ | --self-test/--check, docs/verification/toram-registlet-extraction.md; 원문·전투식·슬롯·서버 획득처 경계 분리 |
| 레지스트렛 도감·보관 | tools/extraction/publish-toram-registlets.mjs, web/src/application/registlet-catalog.mjs, pages/inventory/inventory-registlet-editor.mjs | test-registlet-catalog.mjs, verify-registlet-browser.mjs [--source], npm test; 독립 보관 DTO는 플랫폼 DB/API 계약 |
| 앱 아이템 가공/적용 | tools/extraction/{convert-toram-project-items,sync-toram-dev-items}.mjs, web/src/application/item-catalog.mjs, web/src/ui/item-{equipment,consumable}-ui.mjs | npm test, docs/architecture/item-data-format.md |
| 보스 원본/앱 데이터 갱신 | tools/extraction/update-toram-bosses.py, toram-boss-pipeline-contract.json, {convert-toram-project-bosses,sync-toram-dev-bosses}.mjs, web/src/application/boss-catalog.mjs | npm test, docs/verification/toram-boss-pipeline.md |
| 타겟 검색/기본 스탯 | web/src/ui/boss-target-ui.mjs, web/src/application/boss-target.mjs, application/build-draft-store.js | npm test / npm test -- browser; 원문 native-target/·native-highraid-target/·native-guildraid-target/; 길드 식별 guild-raid-bosses.json |
| 옵부 오프라인 입력/경로 설계 | tools/statting/{native_model,routes,simulate,experiment}.py | self_check.py, review_results.py; docs/verification/toram-statting-experiments.md; 앱 추천 미연결 |

파일 목록은 rg --files, 내용은 rg -n에 --hidden --ignore-file .aiignore를 붙인다. .aiignore는 명시적으로 전달해야 한다. 생성물·의존성은 제외하며 원문·fixture는 필요한 정확한 경로로 읽는다.

원본 소유권은 각 제품 README를 따른다. 앱 build/dev가 저장/업데이트 TS와 WASM을 build/generated/에 출력한다. 스킬 정의는 web/src/data/skills/의 ID별 단일 원본이다. data/sources/skill-registration/은 원문 메타데이터다. 배포 URL 대응은 tools/support/frontend-paths.mjs, build/는 생성물이다.

검증·검색 규칙은 AGENTS.md, 브라우저 도구별 범위는 tools/README.md를 따른다. .aiignore의 제외 파일도 해당 주제 작업에는 정확한 경로로 읽는다.
