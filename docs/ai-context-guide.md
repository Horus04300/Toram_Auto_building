# 작업 진입점

필독 순서는 AGENTS.md를 따른다. 현재 상태는 docs/handoff/current-development-handoff.md, 실제 코드·이번 테스트로 판단한다.

| 작업 | 코드 | 검증 |
| --- | --- | --- |
| 화면·입력 | web/src/ui/ui-bootstrap.js, build-draft-store.js, 해당 UI 파일 | Application 회귀·실제 브라우저 |
| 계산 조립 | web/src/application/application-use-cases.js, calculation-policies.js | 해당 계산 회귀 |
| 스킬·계산식 | web/src/calculation/calculator.js, skill-effect-engine.js, data/skills/ | 원문·스킬 검증 기준·S1 및 해당 트리 |
| 추천 코어 | engine/src/ | Rust 단위 테스트·WASM 완전탐색 회귀 |
| 후보 준비 | web/src/optimization/candidate-preparation.js, problem-compiler.js | 축소 전후 exhaustive·raw/동점 검사 |
| 추천 실행 | web/src/optimization/{execution-adapter,rust-bridge,wasm-client,wasm-worker}.js, desktop/adapters/optimization-client.js | 실행·취소·재개·Native 경계 |
| Native 수명 | desktop/src/optimization/ | 서비스·병렬 실행 Rust 테스트 |
| 저장·업데이트 | web/src/storage/, desktop/adapters/, desktop/src/{settings,update_service}.rs | 저장 계약·세션 복원 브라우저 |
| 계정·홈 서버 | web/src/application/account-client.mjs, web/src/ui/account-ui.mjs, server/account-server.mjs, desktop/src/account_browser.rs | npm run test:account, docs/architecture/account-home-server.md |
| 종합 플랫폼 설계 | [제품·객체·병합 기준](architecture/platform-design-contract.md) → [DB/API 계약](architecture/platform-data-api-contract.md) | 사용자 확정 범위·후속 결정·구현 Gate 확인; 설계 확정과 구현 완료 구분 |
| 홈·공통 탐색 | web/src/layout/platform-shell.mjs, web/src/pages/home/home-page.mjs, web/public/css/{platform,home}.css | verify-inventory-browser.mjs (Chrome): 비로그인·계정·최근 메뉴·PC/모바일·계산기 유지 |
| 기본 페이지·계산기 분리 | web/index.html(공통 틀·홈), web/src/app-entry.mjs, web/src/pages/calculator/ | verify-platform-startup-browser.mjs: 다른 페이지의 계산기 요청 없음·지연/중복 초기화·메뉴 이동·실패 격리; 저장 복원·계정/인벤토리 왕복 |
| 도감 조회 | web/src/application/catalog-browser.mjs, web/src/pages/catalog/, web/public/css/catalog.css | test-catalog-browser.mjs, verify-catalog-browser.mjs (Chrome): 검색·번역·원문·계보·보스 선택·읽기 전용 |
| 공개·릴리스·복사·즐겨찾기 | server/{post-store,request-receipts}.mjs, web/src/pages/board/, application/account-client.mjs | test:account, test-post-store.mjs, verify-posts-browser.mjs (Chrome): 버전/사본 독립·권한·검색·홈 순위·409 초안 |
| 인벤토리·조립 | web/src/application/{equipment-object,inventory-objects,inventory-merge,account-client}.mjs, web/src/pages/inventory/, server/inventory-{store,rules}.mjs | test:account, verify-inventory-browser.mjs (Chrome), 기존 저장 왕복; DTO는 플랫폼 DB/API 계약 |
| 빌드 | web/src/classic-script-manifest.mjs, tools/prepare-frontend.mjs, tools/web-dev.mjs | verify:entry / verify:entry:web / verify:entry:dist |
| 게임 아이템 갱신 | tools/extraction/update-toram-items.py, toram-item-pipeline-contract.json | --self-test, docs/verification/toram-item-pipeline.md |
| 앱 아이템 가공/적용 | tools/extraction/{convert-toram-project-items,sync-toram-dev-items}.mjs, web/src/application/item-catalog.mjs, web/src/ui/item-{equipment,consumable}-ui.mjs | npm run items:test, docs/architecture/item-data-format.md |
| 보스 원본/앱 데이터 갱신 | tools/extraction/update-toram-bosses.py, toram-boss-pipeline-contract.json, {convert-toram-project-bosses,sync-toram-dev-bosses}.mjs, web/src/application/boss-catalog.mjs | npm run bosses:test, docs/verification/toram-boss-pipeline.md |
| 타겟 검색/기본 스탯 | web/src/ui/boss-target-ui.mjs, web/src/application/boss-target.mjs, storage/build-state-snapshot.js | bosses:test, verify:web:browser; 원문 native-target/·native-highraid-target/·native-guildraid-target/; 길드 식별 guild-raid-bosses.json |
| 옵부 오프라인 입력/경로 설계 | tools/statting/{native_model,routes,simulate,experiment}.py | self_check.py, review_results.py; docs/verification/toram-statting-experiments.md; 앱 추천 미연결 |

검색은 npm run ai:files, npm run ai:search -- "패턴" 경로 또는 rg --ignore-file .aiignore를 사용한다. .aiignore는 명시적으로 전달해야 한다. 생성물·의존성은 제외하며 원문·fixture는 필요한 정확한 경로로 읽는다.

루트와 각 제품 폴더의 README에서 소유권을 먼저 확인한다. web/src/는 공통 화면·계산·입력·저장·WASM 연결, desktop/adapters/는 Native 추천·파일 저장·업데이트의 화면 연결, engine/src/는 공통 Rust 평가·탐색이다. 공용 Rust 테스트는 solver_tests.rs·evaluator_tests.rs에 있다.

저장/업데이트 JS는 desktop/adapters/ TypeScript에서 types:emit으로 build/generated/desktop/에 생성한다. WASM은 wasm:build로 build/generated/wasm/에 생성한다. 스킬 등록 메타데이터는 data/sources/skill-registration/에서 tools/generate-skill-registration.mjs로 생성한다. 웹/앱 배포본은 web:build/desktop:prepare다. 배포 URL assets/...는 유지하며 원본 대응은 tools/support/frontend-paths.mjs다. build/{generated,desktop,web,release,tmp}/는 직접 수정하지 않는다.

UI 계산·저장은 Application, 영속 입력은 BuildDraft/Scenario, 일회성 선택 타격은 Request를 따른다. Native/WASM은 같은 Rust 코어를 호출한다. 도구에 제품 추천의 별도 구현을 만들지 않는다. 옵부는 사용자 요청으로 앱과 분리한 원형 계산·경로 실험기를 둔다. 테스트 전용 소형 완전탐색은 후보 축소·동점을 독립 확인한다. 실제 앱 저장 E2E는 TORAM_E2E_CDP가 없으면 SKIP이다.

문서만 수정하면 npm run ai:audit와 git diff --check, 코드 수정은 관련 회귀와 verify:architecture를 실행한다. 계산·후보·상한 변경은 docs/architecture/crysta-optimization-contract.md를 따른다. 과거 실험 도구·대량 계측 로그는 제거했으며 새 계측 산출물은 desktop/target/에 쓴다.
