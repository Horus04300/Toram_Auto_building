# Toram Auto Building

토람 대미지·빌드 계산기. 화면·입력·데이터를 공유하는 웹 페이지와 Tauri Windows 앱입니다. 전체 평가·추천 탐색은 공용 Rust 코어를 사용합니다. 일반 계산은 WASM, 앱 정밀 탐색은 Native로 실행합니다.

## 시작

Node.js 24 LTS와 Rust가 필요합니다. Windows 앱에는 Microsoft C++ Build Tools와 WebView2도 필요합니다.

    npm ci
    rustup target add wasm32-unknown-unknown
    rustup toolchain install nightly-2025-11-15 --profile minimal --component rust-src --target wasm32-unknown-unknown
    cargo install wasm-bindgen-cli --version 0.2.127 --locked
    npm run web:dev

웹 개발은 http://localhost:8787/ 에서 화면과 계정·인벤토리·게시판 API를 함께 제공합니다. `server/.env`를 자동으로 읽고 기존 Google 키와 계정 DB를 사용합니다. 첫 설정은 server/.env.example을 복사해 키를 입력하고 Google 콜백을 http://localhost:8787/api/auth/google/callback으로 등록합니다. 기존 .env와 DB는 덮어쓰지 않습니다. HTML·JS·CSS는 새로고침, Rust·서버 코드는 개발 서버를 다시 시작합니다. 포트를 바꿀 때는 PORT·PUBLIC_ORIGIN·Google 콜백을 함께 맞춥니다.

| 명령 | 용도 |
| --- | --- |
| npm run desktop:build | Windows 앱·NSIS 설치 파일 |
| npm run web:build | 정적 웹 배포본 build/web/ |
| npm run desktop:dev | Tauri 개발 앱 |
| npm run web:dev | 웹 개발 서버 |
| npm test | 타입·모듈 경계·JS 회귀·S1·Rust fmt/test/clippy |

WASM·앱 TypeScript와 프론트엔드 준비는 build/dev/test가 필요한 만큼 실행합니다. 따로 준비 명령을 실행하지 않습니다. 설치 파일 없이 EXE만 필요하면 `npm run desktop:build -- --no-bundle`을 사용합니다. 서명 릴리스에는 업데이터 키가 필요합니다.

최초 실행·Rust 변경 때는 단일/병렬 WASM을 컴파일합니다. 변경 없는 재실행은 Cargo 신선도와 출력 해시만 확인합니다. 고정 nightly의 atomics 경고는 공유 메모리 병렬 타깃의 알려진 경고이며 빌드 실패와 구분합니다. 출력이 같으면 변경 없음으로 표시합니다.

브라우저 검증은 Chrome과 CODEX_PLAYWRIGHT_PATH를 지정한 뒤 `npm test -- browser`로 실행합니다. 웹 준비도 이 명령이 수행합니다.

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
├─ engine/           전체 평가·추천의 공통 Rust 코어
├─ server/           계정·Google 로그인·서버 저장
├─ data/             추출 원문·출처·가공 근거
├─ tools/            빌드·데이터 가공·테스트·검증
├─ samples/          사용자 제공 빌드 입력
├─ docs/             개발 상태·계약·검증·출처 문서
└─ build/            자동 생성물: generated/·web/·desktop/·release/·tmp/
```

화면을 고치면 [web/](web/README.md), 앱 전용 기능을 고치면 [desktop/](desktop/README.md), 추천 알고리즘을 고치면 [engine/](engine/README.md)부터 엽니다. 원본·출처는 [data/](data/README.md), 실행·검사는 [tools/](tools/README.md)에서 찾습니다.

`build/web/`와 `build/desktop/`는 따로 개발하는 소스가 아닙니다. `web/`의 같은 화면을 배포 대상으로 조립한 결과이며, Tauri는 `build/desktop/`를 앱 안에 포함합니다. 앱 전용 어댑터는 데스크톱 배포본에만 들어갑니다.

```text
web/ + engine/ → WASM → build/generated/wasm/ → build/web/
web/ + desktop/adapters/ + WASM               → build/desktop/
desktop/src/ + engine/ + build/desktop/        → Windows 앱
```

브라우저의 `assets/...` URL은 디스크의 원본 폴더 이름과 구분합니다. 빌드 도구가 `web/src/`를 `assets/js/`, `web/public/`를 `assets/`로 배치합니다. 개발 서버도 같은 URL을 제공합니다. 대응은 `tools/support/frontend-paths.mjs`, 실행 모듈은 실제 ESM import 그래프에서 수집합니다.

빠른 추천은 Rust WASM 초기해, 정밀 추천은 웹에서 같은 WASM 세션, 앱에서 Native를 사용합니다. JS는 입력·후보 조립과 표시를 맡으며 전체/요약/공급값 평가·정밀 탐색은 공통 Rust 수식으로 실행합니다. 계산기 모듈을 로드할 때 WASM을 한 번 초기화하고 기존 동기 계산 API를 유지합니다. 일반 계산에도 WebAssembly가 필요합니다. 단일 스레드는 COOP/COEP 없이도 작동합니다. 개별 계산 검사를 직접 실행할 때만 node tools/build-wasm.mjs로 산출물을 준비합니다.

웹은 build/web/ 전체를 정적 호스팅에 올리며 하위 경로 배포를 지원합니다. 앱과 웹은 빌드 JSON v2를 공유합니다. 자동 복원은 접속 주소별 localStorage이며, 이름 있는 앱 세팅은 %LOCALAPPDATA%\ToramOnlineAutoBuildCalculator 에 저장합니다. JSON 내보내기/불러오기로 다른 주소·기기로 옮깁니다.

홈(`/`)·계산기(`/calculator`)·도감(`/catalog`)·내 구성(`/inventory?type=equipment`)·게시판을 공통 메뉴로 전환하며 계산기 입력을 유지합니다. 화면 동작은 [웹 안내](web/README.md)를 따릅니다.

계정 저장·Google 로그인·공개 빌드는 별도 홈 서버가 필요합니다. 키·HTTPS·Docker·앱 서버 주소 설정은 [홈 서버 배포 방법](docs/architecture/account-home-server.md)을 따릅니다. 서버 설정 전에는 로컬 저장을 사용합니다.

data/sources/와 docs/sources/의 원문, web/public/game-data/의 현재 manifest와 참조 자산은 보존합니다. 과거 자산 정리는 이전 manifest를 캐시한 화면에 영향을 줄 수 있으므로 별도 검토합니다. build/ 전체, 각 Rust 프로젝트의 target/, node_modules/는 Git에서 제외한 생성물입니다. 저장·업데이트 어댑터는 desktop/adapters/의 TypeScript 원본을 수정합니다. 앱 build/dev가 build/generated/desktop/에 컴파일합니다.

배포 준비는 index.html과 실행용 assets만 남깁니다. 선택된 실행 스크립트·CSS·폰트/라이선스·아이콘·WASM을 복사하며 원문·타입 전용 TS·검사 로그는 포함하지 않습니다. 새 모듈은 사용처에서 import하면 배포 그래프에 포함됩니다. 준비 진입점이 WASM·앱 타입을 조립하고 내용이 같은 산출물은 다시 쓰지 않습니다. Native 전용 경로 별칭만 tools/support/frontend-paths.mjs가 관리합니다. 브라우저 검사 스크린샷은 build/tmp/, Native 계측·검사 로그는 desktop/target/에 보관합니다.

[현재 상태](docs/handoff/current-development-handoff.md) · [작업 진입점](docs/ai-context-guide.md) · [추천 정확성 계약](docs/architecture/crysta-optimization-contract.md) · [종합 플랫폼 설계](docs/architecture/platform-design-contract.md)
