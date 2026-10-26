# 홈 서버 계정·Google 로그인

종합 플랫폼으로 확장할 때는 [제품·객체·병합 기준](platform-design-contract.md)과 [DB/API 계약](platform-data-api-contract.md)을 함께 따른다. 아래 기존 개인 저장·인증 계약과 신규 게시글 평가를 혼동하지 않는다.

구현 진입점은 `server/account-server.mjs`, `web/src/application/account-client.mjs`, `web/src/ui/account-ui.mjs`다. Linux/Docker 한 인스턴스와 SQLite로 시작한다. Firebase/Supabase 계정은 필요 없다. 아직 실제 홈 서버에 배포하거나 Google 발급 키로 로그인하지 않았다.

새 인벤토리 저장·화면의 경계는 `server/inventory-store.mjs`, 공용 `web/src/application/{equipment-object,inventory-objects,inventory-merge}.mjs`, `web/src/pages/inventory/`다. 공통 틀·전환은 `web/src/layout/`, 홈은 `web/src/pages/home/`이며 인증 요청은 기존 account-client를 공유한다. DTO·검색·수정 충돌·병합 요청 키는 [플랫폼 데이터·API 계약](platform-data-api-contract.md)의 v1을 따른다. `/` 홈·`/inventory`·`/calculator`를 프론트 진입 문서로 허용하고 없는 API·자산은 HTML로 대체하지 않는다. 구형 records의 이관 여부와 현재 구현 범위는 현재 인계에서 확인한다.

조회 전용 도감의 `/catalog`도 프론트 진입 문서로 허용한다. 도감은 발행된 같은 출처의 아이템·보스 정적 자산을 직접 사용하므로 인증·계정 DB·업로드가 필요하지 않다. 공개 게시판·인벤토리 API의 인증 계약을 바꾸지 않는다.

## 사용자 흐름과 저장 범위

공개 구성은 `server/post-store.mjs`, 생성 요청 재시도는 `server/request-receipts.mjs`, 게시판·공개 창은 `web/src/pages/board/`가 소유한다. 공개 검색·특정 버전은 비로그인 조회가 가능하며 공개/새 버전/복사/즐겨찾기/작성자 관리는 기존 세션·Origin·JSON 검증을 사용한다. `/board`는 프론트 진입 문서로 허용한다. 기존 records의 favorites와 게시글 즐겨찾기는 다른 테이블이다. 상세 DTO는 [플랫폼 DB/API 계약](platform-data-api-contract.md)을 따른다.

로컬 실제 로그인은 `server/.env`의 `PUBLIC_ORIGIN=http://localhost:8787`, `PORT=8787`과 Google 웹 클라이언트의 `http://localhost:8787/api/auth/google/callback`을 맞춘다. 처음 접속하는 주소도 localhost로 통일한다. 127.0.0.1에서 시작하면 로그인 요청 쿠키가 localhost 콜백으로 넘어가지 않는다. 발급 키·Secret은 이 문서나 브라우저 코드에 넣지 않는다.

인증 설정 전 개발 체험은 `npm run web:preview` → `http://127.0.0.1:5182/__preview`의 명시적 체험 계정 버튼을 사용한다. 이 별도 실행기는 loopback·Host·Origin을 제한하고 `build/tmp/platform-preview/accounts.sqlite`에 테스트 데이터만 저장한다. 여러 체험 브라우저가 같은 로컬 계정을 쓰며 실제 계정 데이터와 합치지 않는다. 운영 서버에 체험 경로·환경 우회 설정을 넣지 않고 Docker에도 실행기를 포함하지 않는다. 로그아웃 뒤에는 체험 진입 페이지에서 다시 들어온다.

- 저장 버튼 바로 옆 계정 아이콘 → 계정 모달. 미로그인은 Google 로그인, 로그인 후에는 닉네임 변경과 내 빌드·내 아이템·즐겨찾기를 제공한다.
- 내 빌드는 기존 `toram-auto-build-document` schema v2를 이름 있는 새 항목으로 저장/조회/불러오기/삭제한다. 로컬 JSON·앱 파일 저장과 자동 복원은 계속 동작한다.
- 내 아이템은 현재 장비 부위 하나의 수동 옵션·ATK·제련·안정률·크리스타·catalogItem을 `toram.account-item.v1` 스냅샷으로 저장한다. 불러오기는 현재 세팅의 해당 부위만 교체한다. 즐겨찾기도 같은 형식이며 게임 아이템이 연결된 장비만 허용한다. 아이템 검색 UI 전체의 별표 버튼은 이번 범위에 없다.
- 로그인만으로 로컬 데이터를 업로드하거나 서버 데이터로 덮어쓰지 않는다. 저장은 명시적 새 항목 생성, 불러오기와 삭제는 확인 후 실행한다. 자동 동기화·오프라인 쓰기 큐·이름별 덮어쓰기는 없다. 각각 최대 200항목, 요청 본문 1 MiB다.
- 웹은 홈 서버가 계산기 정적 배포본과 `/api/`를 같은 HTTPS origin에서 제공한다. 하위 경로 배포는 이 서버의 범위가 아니다.
- Windows 앱은 빌드 시 주입한 홈 서버 origin을 사용한다. 기본 브라우저에서 인증 후 5분 내 일회성 요청을 통해 앱에 세션을 전달한다. 앱 토큰은 메모리에만 두므로 앱을 종료하면 다시 로그인한다. 웹 쿠키와 앱 세션은 서로 독립이다. 다른 OS 앱 로그인은 지원하지 않는다.

## 인증·소유권 계약

Google OAuth 웹 클라이언트의 Authorization Code + PKCE(S256)를 서버에서 처리한다. `openid profile`만 요청하고 비밀번호·메일·Google refresh token은 보관하지 않는다. 서버가 Google token endpoint와 userinfo endpoint를 직접 호출하고 확인한 `sub`를 내부 계정 UUID에 연결한다. 클라이언트가 보낸 Google ID나 사용자 ID는 인증에 사용하지 않는다.

5분 OAuth state는 브라우저의 HttpOnly/SameSite=Lax 쿠키와 일치해야 하며 한 번만 소비한다. Google client secret은 서버 환경 파일에만 둔다. 계정 세션은 무작위 256비트 값이며 DB에는 SHA-256 해시만 저장한다. 웹은 Secure/HttpOnly/SameSite=Lax의 `__Host-` 쿠키, 앱은 Authorization Bearer를 사용한다. 둘 다 7일 후 만료하고 로그아웃 시 서버에서 폐기한다.

앱은 무작위 비밀값의 SHA-256 challenge로 로그인 대기를 생성한다. 기본 브라우저는 공개 대기 ID로 Google 로그인을 완료하며, 비밀값을 가진 앱만 토큰을 한 번 받을 수 있다. 비밀값과 앱 세션 토큰은 URL에 넣지 않는다. 브라우저용 세션 쿠키를 앱으로 복사하지 않는다. 앱 열기 IPC는 HTTPS의 지정 로그인 경로와 대기 ID 형식만 허용하고 셸 문자열을 실행하지 않는다.

모든 빌드·아이템·즐겨찾기 SQL은 세션의 내부 `user_id`와 종류를 조건에 포함한다. 다른 계정의 ID는 404다. 삭제는 조회한 version이 일치해야 한다. 동적 SQL 입력은 없으며 값은 바인딩한다. 클라이언트는 서버 항목을 HTML로 삽입하지 않고, 불러올 때 기존 Settings 검증/복원 경계를 통과한다.

쓰기 요청은 JSON과 허용된 Origin이 필요하다. 웹은 같은 origin, 앱은 Tauri 고정 origin만 CORS 허용하며 cross-origin 쿠키는 허용하지 않는다. Google 콜백은 state/브라우저 쿠키로 검증한다. 인증 시작/일반 API 요청 제한과 데이터 크기/항목 수 제한이 있다. 프록시의 임의 X-Forwarded-For를 신뢰하지 않아 단일 reverse proxy 뒤의 요청 제한은 사용자 전체가 공유한다. 공개 트래픽이 늘면 신뢰 프록시 설정과 IP별 제한을 보강한다.

## API

| 경로 | 동작 |
| --- | --- |
| GET /api/session | 서버 설정 여부, 현재 계정 ID·닉네임 |
| GET /api/auth/google | Google 인증 시작 |
| GET /api/auth/google/callback | state/코드 확인, 세션 생성 또는 앱 대기 완료 |
| POST /api/auth/desktop | `{challenge}` → `{id,expiresAt}` |
| POST /api/auth/desktop/:id | `{secret}` → `{pending:true}` 또는 일회성 `{token,user}` |
| POST /api/logout | 현재 세션 폐기 |
| PATCH /api/me | `{nickname}` 변경 (1~40자, 중복 허용) |
| GET /api/{builds,items,favorites} | 내 목록의 ID·이름·version·updatedAt |
| POST /api/{builds,items,favorites} | `{name,data}`를 새 항목으로 저장 (이름 최대 80자) |
| GET /api/{kind}/:id | 내 항목의 데이터 조회 |
| DELETE /api/{kind}/:id | `{version}` 확인 후 내 항목 삭제 |
| GET/POST /api/inventory | 내 구성 목록 종류·검색·분류·페이지 / 새 구성 생성 |
| GET/PUT/DELETE /api/inventory/:id | 내 구성 상세 / 기대 revision으로 수정·삭제 |
| POST /api/inventory/merges/preview | 내 두 구성의 조립·충돌 미리보기 |
| POST /api/inventory/merges | 원본 revision·선택·요청 키 확인 후 새 구성 저장 |

SQLite는 사용자/세션/OAuth 대기/앱 로그인 대기/저장 항목을 분리한다. WAL·foreign key를 활성화하고 데이터 폴더는 컨테이너 밖에 둔다. 공유/공개 빌드·권한 역할·계정 탈퇴·일괄 내보내기 UI는 추가하지 않았다. 현재 항목은 각 기기에 불러와 기존 JSON 내보내기로 백업할 수 있다.

## Linux/Docker 배포

필요한 준비물은 공개 HTTPS 주소(예: `https://calculator.example.com`), 그 주소를 홈 서버로 연결할 도메인/프록시, Google Cloud OAuth 웹 클라이언트 ID·secret이다. 사설 IP의 HTTP 주소만으로 외부 Google 로그인 서비스를 배포하지 않는다. Google Cloud 프로젝트/동의 화면/발급 키는 소유자가 준비해야 한다.

1. Google Cloud의 OAuth 클라이언트 유형을 **웹 애플리케이션**으로 만들고 승인된 리디렉션 URI를 `https://실제주소/api/auth/google/callback`으로 정확하게 등록한다. 동의 화면의 앱 이름·소유자 연락처·대상 사용자·공개 상태를 설정한다. 테스트 모드라면 로그인할 Google 계정을 테스트 사용자로 등록한다.
2. Node.js 24 LTS 환경에서 `npm ci` 후 `npm run web:build`로 `build/web/`를 만든다. 기존 계산기 빌드에 필요한 Rust/WASM 도구는 기존 웹 빌드 절차를 따른다. 홈 서버에서 직접 빌드하지 않으면 다른 개발 기기에서 생성한 `build/web/`와 서버 파일을 함께 옮겨도 된다.
3. 저장소 루트에서 아래 명령을 실행하고 `.env`의 예시 주소/키를 실제 값으로 수정한다. 예시 키로는 로그인할 수 없다.

```sh
cp server/.env.example server/.env
mkdir -p server/data
sudo chown 1000:1000 server/data server/.env
chmod 700 server/data
chmod 600 server/.env
docker compose -f server/compose.yaml up -d --build
```

`server/.env`·`server/data/`는 Git/Docker build context에서 제외한다. 컨테이너는 UID 1000인 node 사용자로 실행한다. `.env`와 데이터 파일을 공개 웹 디렉터리로 복사하지 않는다. DB 파일에는 Google 계정 식별자와 개인 빌드가 있으므로 백업도 비공개로 보관한다.

4. 호스트의 reverse proxy에서 공개 HTTPS origin 전체를 `127.0.0.1:8787`로 전달한다. Compose는 이 포트를 loopback에만 바인딩한다. Caddy를 호스트에서 운영한다면 다음처럼 설정한다. 별도 Docker 프록시를 사용하면 두 서비스를 같은 비공개 Docker 네트워크에 연결하고 프록시의 upstream을 calculator:8787로 지정해야 한다.

```caddyfile
calculator.example.com {
    reverse_proxy 127.0.0.1:8787
}
```

5. 웹 로그인과 저장/다른 브라우저 재조회/로그아웃을 실제 Google 계정으로 확인한다. 공개 전 TLS, 프록시 응답, DB 볼륨 재시작 보존, 백업 복구를 확인한다. Google 웹뷰 차단을 피하려면 Windows 앱에서도 반드시 기본 브라우저 흐름을 사용한다.
6. Windows 앱 배포본에는 같은 공개 origin을 빌드 시 주입한다. 주소에 경로나 끝 `/`를 붙이지 않는다.

```powershell
$env:TORAM_ACCOUNT_SERVER_URL = 'https://calculator.example.com'
npm run desktop:prepare
```

설정 없는 앱도 계정 모달과 로컬 저장은 작동하며, 로그인 시 서버 설정 안내를 표시한다. Google secret은 이 변수나 앱 코드에 넣지 않는다.

로컬 서버 테스트는 Node 24에서 `PUBLIC_ORIGIN=http://127.0.0.1:8787`을 쓴다. HTTP loopback만 개발 예외로 허용한다. 서버 DB 백업은 `docker compose -f server/compose.yaml stop calculator` 후 `server/data/` 전체를 안전한 곳에 복사하고 `start calculator`로 재개한다. 운영 중 파일 하나만 복사하면 WAL의 최신 쓰기를 놓칠 수 있다.

## 검증

- `npm run test:account`: 실제 임시 HTTP 서버와 SQLite로 OAuth state·브라우저 바인딩·PKCE·재사용/실패, 계정 격리, 저장 형식/용량, CSRF/CORS, 앱 일회성 전달, 로그아웃/만료, 토큰 해시, 비공개 파일 차단을 검사한다. Google 응답은 mock이며 실제 Google 로그인 성공을 증명하지 않는다. 클라이언트는 Settings 스냅샷/복원·미설정/401·쿠키/리디렉션을 검사한다.
- UI 변경은 실제 브라우저에서 계정 모달·로그인 전후·보관함·작은 화면·키보드 닫기/포커스를 검사한다. 기존 저장 계약·구조는 `npm run verify:architecture`, 배포 포함은 `npm run verify:entry:web`/`verify:entry:dist`로 확인한다.
- Docker 이미지 빌드/실제 Google 키·도메인·TLS·홈 서버 배포는 별도 실환경 확인 사항이다.

2026-10-23 로컬 확인: `npm run test:account`, `npm run verify:architecture`, `npm run verify:entry`/`verify:entry:web`/`verify:entry:dist`, `cargo test --manifest-path desktop/Cargo.toml --bin toram-online-auto-build-calculator account_browser::tests`(1/1), 같은 bin의 `cargo clippy -- -D warnings` 통과. Edge 1280×900·375×812에서 미로그인/미설정 안내·닉네임·빌드 저장/복원·아이템 저장·즐겨찾기 조건·로그아웃 후 목록 제거·Escape/포커스 복귀·기존 저장 모달을 확인했고 콘솔/페이지 오류가 없었다. 로그인 후 UI의 API 응답은 mock이다. Browser 플러그인 스킬이 없어 설치된 Playwright/Edge를 사용했다. Docker 실행 파일이 없어 이미지 빌드는 실행하지 않았다.

공식 근거: [Google 서버 OAuth](https://developers.google.com/identity/protocols/oauth2/web-server), [Google OAuth 정책](https://developers.google.com/identity/protocols/oauth2/policies), [Node SQLite](https://nodejs.org/api/sqlite.html).
