# 제품별 소스 폴더 재배치

2026-10-23 사용자 승인 구조. 공통 화면·데스크톱 전용 코드·공용 추천 엔진·서버·원문·도구를 루트부터 구분한다. 현재 상태·검증 요약은 ../handoff/current-development-handoff.md가 기준이다.

## 이전 위치와 수정할 원본

| 이전 | 현재 |
| --- | --- |
| index.html | web/index.html |
| assets/js/의 공통 JS | web/src/ |
| assets/css·fonts·icons·game-data/ | web/public/ |
| frontend/application·contracts·domain/ | web/src/의 같은 역할 폴더 |
| frontend/runtime/tauri-build-storage-adapter.ts | desktop/adapters/saved-build-storage.ts |
| frontend/runtime/tauri-update-adapter.ts | desktop/adapters/update.ts |
| assets/js/optimization/native-client.js | desktop/adapters/optimization-client.js |
| assets/js/update/·ui/update-ui-controller.js | desktop/adapters/update/ |
| src-tauri/ | desktop/ |
| crates/optimization-core/ | engine/ |
| assets/source-data/ | data/sources/ |
| assets/game-data/ui/의 비교용 원본 | data/sources/game-ui/ |
| skill_effect_source_links.json | data/sources/skill-effect-source-links.json |
| 프로젝트 전반 리팩토링 지시.md | docs/architecture/project-refactoring-instructions.md |
| assets/wasm/ | build/generated/wasm/ |
| 생성 저장·업데이트 JS | build/generated/desktop/ |

## 배포와 원본 경계

- 브라우저의 assets/... URL과 화면 로딩 순서는 유지한다. tools/support/frontend-paths.mjs가 배포 URL을 편집 원본에 연결한다. 개발 서버도 같은 대응을 쓴다.
- 웹·앱 결과물은 build/web/·build/desktop/이다. 앱 전용 JS는 앱에만 포함하며, Tauri의 frontendDist는 ../build/desktop이다.
- package.json의 desktop 명령은 desktop/에서 CLI를 실행한다. TS 어댑터는 desktop/tsconfig.{storage,update}.json을 통해 build/generated/desktop/로 출력한다.
- 배포는 선택한 JS·정적 파일·발행 manifest가 참조하는 JSON만 복사한다. 예전 산출물의 불필요한 일반 파일·빈 폴더는 제거하며, symlink 출력은 거부한다.
- 원문·저장 샘플·발행된 게임 데이터의 바이트와 해시는 보존한다. 고정 pipeline 계약·itemUseRules·과거 snapshot에 기록된 assets/source-data/ 경로는 원문 식별자다. 검사 시 현재 data/sources/로 투영한 뒤 기존 해시를 검증한다. 발행 revision이나 게임 데이터 값은 재생성하지 않는다.
- 앱 식별자·설치 위치·사용자 저장 위치·저장 JSON v2·업데이트 endpoint는 유지한다. 플랫폼별 별도 화면 복사본이나 미구현 Android 폴더를 추가하지 않는다.

## 검증 진입점

루트에서 verify:architecture, web:build, desktop:prepare, verify:entry/web/dist, test:regression, verify:web:browser, ai:audit를 실행한다. Rust는 engine/·desktop/ manifest의 fmt/test/clippy, 출처는 audit-stack-source-links.mjs --require-s1, 데이터 도구는 두 Python pipeline의 --self-test다. desktop:build:exe로 새 경로의 Tauri 준비·컴파일도 확인한다.

폴더 이동 후 기존 Cargo 캐시의 Tauri 권한 메타데이터가 과거 절대 경로를 참조할 수 있다. 이 경우 desktop:clean으로 해당 패키지의 캐시만 정리한 뒤 재빌드한다. 실제 업데이터 설치·서명 배포는 이 구조 변경의 검증 범위와 구분한다.

## 이번 실행 근거

- npm run verify:architecture: 타입·저장·계산·실행·원본 위치·Worker 의존성 PASS.
- npm run web:build / desktop:prepare, verify:entry / verify:entry:web / verify:entry:dist: PASS. npm run desktop:build:exe도 새 desktop/ 경로의 준비 hook·릴리스 EXE 빌드를 통과했다.
- node tools/run-regression-suite.mjs: 73/73 스위트 PASS. TORAM_E2E_CDP가 없어 실제 네이티브 저장 E2E 1건은 SKIP이며 실제 73건 실행 성공을 뜻하지 않는다.
- cargo fmt/test/clippy: 두 manifest PASS. 공용 엔진 89개, 데스크톱 main 18개·headless 11개·parallel 4개 테스트 PASS. 이동 전 캐시의 hard-link 경고는 재컴파일/복사로 처리됐다.
- 두 Python pipeline --self-test: 15/15·10/10 PASS. Python 도구 29개 구문 PASS. audit-stack-source-links.mjs --require-s1: 427/427 PASS.
- verify-session-restore-browser.mjs: 전체 입력·장비 7조합·재열기 PASS. verify-update-browser.mjs: 실제 Edge의 앱 전용 어댑터·최신 입력 저장·동의/실패 흐름 PASS(실제 설치 mock).
- 별도 임시 browser-layout.mjs: 개발 루트·배포 /calculator/에서 실제 화면·계산·JSON 가져오기/내보내기·재열기·소형 16조합 Worker exact/취소·앱 전용 기능 제외 PASS. 실제 UI 입력은 exact/bounded 제품 계약으로 검사했다. 원래 전체 브라우저 Gate의 exact 기대값을 대체한 검사가 아니다.
- 이동 전 목록 대비 기존 3,267개 파일 모두 존재, 원문·발행 데이터·사용자 샘플 2,275개 SHA-256 동일. web/src/·desktop/src/·engine/src/의 실행 원본은 출처 파일명 주석 한 줄 외에 바이트가 동일하다. Git 제외 pipeline 이력도 디렉터리 이동으로 보존했다.

전체 verify:web:browser는 실제 UI 입력에서 exact를 30초 안에 요구하는 기존 대기로 실패했다. 페이지/리소스 오류는 없고 bounded 상태다. 이어하기를 누른 별도 확인에서도 120초 안에 최적성 증명에 도달하지 않았다(누적 탐색 약 91초·853만 노드). 계산·탐색 원본을 수정하거나 기존 exact 기대값을 낮추지 않았다. 실패 메시지에는 상태/진행량을 추가했다. 이 결과를 루트/하위 경로 배포 실패 또는 전체 입력 exact 달성으로 해석하지 않는다.

상세 실행 로그·원본 보존 목록은 Git 제외 build/tmp/layout-migration/에 있다. 공개 배포·서명 설치·실제 Google OAuth/Docker는 실행하지 않았다.
