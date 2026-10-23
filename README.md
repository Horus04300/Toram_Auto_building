# Toram Auto Building

토람 대미지·빌드 계산기. 화면·입력·데이터를 공유하는 웹 페이지와 Tauri Windows 앱입니다. 추천 탐색은 공용 Rust 코어를 Native/WASM으로 컴파일합니다.

## 시작

Node.js 24 LTS와 Rust가 필요합니다. Windows 앱에는 Microsoft C++ Build Tools와 WebView2도 필요합니다.

    npm ci
    rustup target add wasm32-unknown-unknown
    cargo install wasm-bindgen-cli --version 0.2.127 --locked
    npm run web:dev

웹은 http://127.0.0.1:5173/ 에서 열립니다. HTML·JS·CSS 변경은 새로고침, Rust 변경은 npm run wasm:build 후 새로고침합니다. 포트는 환경변수 PORT로 바꿉니다.

| 명령 | 용도 |
| --- | --- |
| npm run web:build | 정적 웹 배포본 build/web/ |
| npm run desktop:dev | Tauri 개발 앱 |
| npm run desktop:prepare | 앱 프론트엔드 build/desktop/ 생성 |
| npm run desktop:build | Windows NSIS 설치 파일 |
| npm run desktop:build:exe | 설치 없는 실행 파일 |
| npm run desktop:clean | 폴더 이동 후 Tauri 캐시 정리 |
| npm run verify:architecture | 타입·모듈·저장·실행 경계 |
| npm run test:regression | 계산·입력·Rust/WASM 회귀 |
| npm run verify:web:browser | 실제 Edge·하위 경로·세션 복원 검사 |
| npm run bench:optimization:build | Native 계측 서비스 빌드 |
| npm run bench:optimization | 새 프로세스 반복 계측 |
| npm run ai:audit | 문서·검색 경로 점검 |
| npm run server:start | 홈 서버 계정 API·웹 제공 (server/.env 필요) |
| npm run test:account | Google 인증 흐름·계정 저장 회귀 (실제 Google 응답은 mock) |

브라우저 검증은 설치된 Playwright 모듈 경로를 CODEX_PLAYWRIGHT_PATH에 지정하고 web:build 후 실행합니다. Rust 검사는 engine/Cargo.toml과 desktop/Cargo.toml을 각각 대상으로 fmt/test/clippy를 실행합니다.

## 폴더를 찾는 순서

```text
root/
├─ web/              웹·앱 공통 화면 원본
│  ├─ index.html     화면 뼈대
│  ├─ src/           JS·타입 계약: 화면·계산·입력 상태·저장·추천 연결
│  └─ public/        CSS·폰트·아이콘·배포용 게임 데이터
├─ desktop/          데스크톱 전용 Tauri 코드·설정
│  ├─ src/           Rust: 앱 실행·파일 저장·업데이트·Native 작업 수명
│  └─ adapters/      공통 화면과 데스크톱 기능을 연결하는 JS·TS 원본
├─ engine/           웹 WASM·앱 Native가 공유하는 Rust 추천 엔진
├─ server/           계정·Google 로그인·서버 저장
├─ data/             추출 원문·출처·가공 근거
├─ tools/            빌드·데이터 가공·테스트·검증
├─ samples/          사용자 제공 빌드 입력
├─ docs/             개발 상태·계약·검증·출처 문서
└─ build/            자동 생성물: generated/·web/·desktop/·release/·tmp/
```

화면을 고치면 [web/](web/README.md), 앱 전용 기능을 고치면 [desktop/](desktop/README.md), 추천 알고리즘을 고치면 [engine/](engine/README.md)부터 엽니다. 원본·출처는 [data/](data/README.md), 실행·검사는 [tools/](tools/README.md)에서 찾습니다. 안드로이드 전용 폴더는 실제 구현할 때 추가합니다.

`build/web/`와 `build/desktop/`는 따로 개발하는 소스가 아닙니다. `web/`의 같은 화면을 배포 대상으로 조립한 결과이며, Tauri는 `build/desktop/`를 앱 안에 포함합니다. 앱 전용 어댑터는 데스크톱 배포본에만 들어갑니다.

```text
web/ + engine/ → WASM → build/generated/wasm/ → build/web/
web/ + desktop/adapters/ + WASM               → build/desktop/
desktop/src/ + engine/ + build/desktop/        → Windows 앱
```

브라우저의 `assets/...` URL은 디스크의 원본 폴더 이름과 구분합니다. 빌드 도구가 `web/src/`를 `assets/js/`, `web/public/`를 `assets/`로 배치합니다. 개발 서버도 같은 URL을 제공합니다. 대응은 `tools/support/frontend-paths.mjs`, 로딩 순서는 `web/src/classic-script-manifest.mjs` 한곳에서 관리합니다.

빠른 추천은 Rust WASM 초기해, 정밀 추천은 웹에서 같은 WASM 세션, 앱에서 Native를 사용합니다. 후보 준비·입력 조립·최종 결과 재평가에는 JS를 사용합니다. 이전 JS 추천기와 실험 Worker pool은 삭제했습니다.

웹은 build/web/ 전체를 정적 호스팅에 올리며 하위 경로 배포를 지원합니다. 앱과 웹은 빌드 JSON v2를 공유합니다. 자동 복원은 접속 주소별 localStorage이며, 이름 있는 앱 세팅은 %LOCALAPPDATA%\ToramOnlineAutoBuildCalculator 에 저장합니다. JSON 내보내기/불러오기로 다른 주소·기기로 옮깁니다.

저장 옆 계정 아이콘에서 Google 로그인과 내 빌드·내 아이템·즐겨찾기를 사용합니다. 계정 저장은 Linux/Docker 홈 서버에서 운영합니다. Google 발급 키·공개 HTTPS 주소 설정과 실제 배포가 필요하며, 설정 전에는 기존 로컬 저장을 사용합니다. [홈 서버 설계·배포 방법](docs/architecture/account-home-server.md)을 참고하세요. 계정 서버는 웹 루트에서 제공하고, Windows 앱에는 빌드 시 서버 주소를 주입합니다.

data/sources/, web/public/game-data/, docs/sources/는 원문·발행 데이터이므로 유지합니다. build/ 전체, 각 Rust 프로젝트의 target/, node_modules/는 Git에서 제외한 생성물입니다. 저장·업데이트 어댑터는 desktop/adapters/의 TypeScript 원본을 수정하고 npm run types:emit으로 build/generated/desktop/에 생성합니다.

배포 준비는 index.html과 실행용 assets만 남깁니다. 선택된 실행 스크립트·CSS·폰트/라이선스·아이콘·WASM을 복사하며 원문·타입 전용 TS·검사 로그는 포함하지 않습니다. 새 classic 스크립트는 classic-script-manifest.mjs에, 새 ES Module은 tools/support/frontend-paths.mjs에 등록합니다. 브라우저 검사 스크린샷은 build/tmp/, Native 계측·검사 로그는 desktop/target/에 보관합니다.

[현재 상태](docs/handoff/current-development-handoff.md) · [작업 진입점](docs/ai-context-guide.md) · [추천 정확성 계약](docs/architecture/crysta-optimization-contract.md)
