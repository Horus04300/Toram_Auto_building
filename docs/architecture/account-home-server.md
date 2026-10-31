# 홈 서버 계정·Google 로그인

종합 플랫폼으로 확장할 때는 [제품·객체·병합 기준](platform-design-contract.md)과 [DB/API 계약](platform-data-api-contract.md)을 함께 따른다. 아래 기존 개인 저장·인증 계약과 신규 게시글 평가를 혼동하지 않는다.

구현 진입점은 `server/account-server.mjs`, `web/src/application/account-client.mjs`, `web/src/ui/account-ui.mjs`다. Linux/Docker 한 인스턴스와 SQLite로 시작한다. Firebase/Supabase 계정은 필요 없다. 실제 Google 계정 인증 완료와 공개 배포는 별도 환경 검증이다.

새 인벤토리 저장·화면의 경계는 `server/inventory-store.mjs`, 공용 `web/src/application/{equipment-object,inventory-objects,inventory-merge}.mjs`, `web/src/pages/inventory/`다. 공통 틀·전환은 `web/src/layout/`, 홈은 `web/src/pages/home/`이며 인증 요청은 기존 account-client를 공유한다. DTO·검색·수정 충돌·병합 요청 키는 [플랫폼 데이터·API 계약](platform-data-api-contract.md)의 v1을 따른다. `/` 홈·`/inventory`·`/calculator`를 프론트 진입 문서로 허용하고 없는 API·자산은 HTML로 대체하지 않는다. 구형 records의 이관 여부와 현재 구현 범위는 현재 인계에서 확인한다.

조회 전용 도감의 `/catalog`도 프론트 진입 문서로 허용한다. 도감은 발행된 같은 출처의 아이템·보스 정적 자산을 직접 사용하므로 인증·계정 DB·업로드가 필요하지 않다. 공개 게시판·인벤토리 API의 인증 계약을 바꾸지 않는다.

## 사용자 흐름과 저장 범위

공개 구성은 `server/post-store.mjs`, 생성 요청 재시도는 `server/request-receipts.mjs`, 게시판·공개 창은 `web/src/pages/board/`가 소유한다. 공개 검색·특정 버전은 비로그인 조회가 가능하며 공개/새 버전/복사/즐겨찾기/작성자 관리는 기존 세션·Origin·JSON 검증을 사용한다. `/board`는 프론트 진입 문서로 허용한다. 기존 records의 favorites와 게시글 즐겨찾기는 다른 테이블이다. 상세 DTO는 [플랫폼 DB/API 계약](platform-data-api-contract.md)을 따른다.

로컬 개발은 `npm run web:dev`가 `server/.env`를 읽어 소스 화면과 동일한 계정·인벤토리·게시판 서버를 한 포트에서 제공한다. `PUBLIC_ORIGIN=http://localhost:8787`, `PORT=8787`과 Google 웹 클라이언트의 `http://localhost:8787/api/auth/google/callback`을 맞춘다. 기본 DB는 server/data/accounts.sqlite이며 기존 데이터와 키를 덮어쓰지 않는다. 다른 주소로 연 페이지는 설정된 origin으로 이동해 로그인 쿠키/콜백을 일치시킨다. 최초 설정은 server/.env.example을 사용하고 키·Secret은 브라우저 코드나 로그에 넣지 않는다.

인증 설정 전 개발 체험은 `node tools/preview-platform.mjs` → `http://127.0.0.1:5182/__preview`의 명시적 체험 계정 버튼을 사용한다. 이 별도 실행기는 loopback·Host·Origin을 제한하고 `build/tmp/platform-preview/accounts.sqlite`에 테스트 데이터만 저장한다. 여러 체험 브라우저가 같은 로컬 계정을 쓰며 실제 계정 데이터와 합치지 않는다. 운영 서버에 체험 경로·환경 우회 설정을 넣지 않고 Docker에도 실행기를 포함하지 않는다. 로그아웃 뒤에는 체험 진입 페이지에서 다시 들어온다.

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

### nimp 원격 배포

운영 대상은 SSH 별칭 `nimp`, 공개 origin `https://toram.nimp.dev`다. cloudflared가 서버에서 Cloudflare로 먼저 연결해 이중 NAT의 인바운드 경로를 우회한다. 공개 경로는 Tunnel→기존 Caddy HTTPS443→공유 Docker `proxy` 네트워크의 Toram HTTPS443이다. Caddy는 `/srv/compose/proxy`를 유지하고 Toram에는 호스트 `ports`를 설정하지 않는다. cloudflared는 Cloudflare Origin CA와 `toram.nimp.dev` SNI로 Caddy 인증서를 검증하며, Caddy는 전용 내부 인증서를 trust pool에 고정해 Toram을 검증한다. 두 연결 모두 TLS 검증을 끄지 않는다.

최초 Cloudflare의 Networking→Tunnels에서 toram 터널을 만들고 토큰을 준비한다. 개발 PC에서 `npm run web:deploy -- --setup`을 실행한다. 로컬 `server/.env`의 Google client ID/secret 두 값만 SSH로 전송하며 다른 환경값·로컬 DB·원문·테스트 인증서는 배포하지 않는다. 출력된 `ssh -t nimp "sudo bash /srv/compose/toram/bootstrap/setup.sh"`를 사용자가 실행하고 서버 sudo 비밀번호와 터널 토큰을 해당 터미널에 입력한다. 토큰은 채팅·명령 인자·Git에 넣지 않으며 입력은 숨긴다. 설정은 전용 디렉터리·비공개 환경파일·내부 인증서·배포 sudo 권한을 만들고 기존 환경파일과 DB는 보존한다. Google 콜백은 `https://toram.nimp.dev/api/auth/google/callback`이다.

커넥터가 Healthy이면 터널의 Routes→Published application을 `toram.nimp.dev`, 서비스 `https://caddy:443`, Origin Server Name `toram.nimp.dev`로 등록한다. TLS 검증 해제는 끈다. 이 이름의 터널 CNAME이 기존 와일드카드 A보다 우선하며 다른 도메인·Minecraft는 변경하지 않는다. 서버의 외부 TCP/UDP7844 연결이 필요하며 인바운드 NAT 포워딩은 Toram 경로에 사용하지 않는다. 터널 구간 암호화와 로컬 인증서 검증은 zone의 Full 설정과 별개다.

이후 저장소 루트의 `npm run web:deploy` 하나가 다음을 실행한다.

1. 원격 전용 배포 권한·Docker·네트워크·인증서 사전 확인.
2. 로컬 전체 `npm test`, 웹 WASM/정적 빌드, 생성본 ESM 검사.
3. 서버의 실제 import 의존과 Dockerfile·웹 산출물만 SHA-256 manifest와 함께 압축·SCP 전송.
4. 서버에서 파일 경로·종류·전체 해시를 확인한 후 릴리스 보관. Docker는 이미 준비된 파일을 Node24 이미지에 복사하며 소스를 컴파일하거나 npm 의존성을 설치하지 않는다.
5. SQLite backup API로 일관된 백업을 만들고 무결성 검사. 이미지 교체, HTTPS 인증서 검증, cloudflared 연결 readiness 검사.
6. 기존 Toram 빈 Caddy 블록만 변경하고 전체 설정 검증 후 reload. 공개 HTTPS API와 OAuth 설정 확인 후 현재 릴리스를 기록.

로컬 마지막 검사는 공개 HTML·CSS·JS·WASM·API와 COOP/COEP도 확인한다. Cloudflare525나 타임아웃이면 성공으로 표시하지 않는다. 내부 healthcheck만 정상이라면 Tunnel 상태·공개 hostname 경로·CA/SNI와 외부 네트워크를 확인한다. readiness는 커넥터의 localhost metrics를 사용하고 포트를 공개하지 않는다.

경로는 `/srv/compose/toram`(환경·고정 Compose·릴리스·전송 대기), `/srv/data/toram/db`(SQLite), `/srv/data/toram/tls`(내부 TLS), `/srv/data/toram/cloudflared`(토큰·공개 CA), `/srv/backups/toram`(DB·프록시 백업)이다. 토큰은 root:65532/640이며 해당 커넥터에만 읽기 전용으로 마운트한다. Google 키는 커넥터에 주지 않는다. `/usr/local/sbin/toram-deploy`·`/usr/local/lib/toram-deploy`는 root 소유이며 자동화 계정에는 이 배포 명령만 sudo로 허용한다. 인프라를 바꾸면 최초 설정을 다시 적용한다. 루틴 배포는 환경값·DB·다른 사이트를 보존한다.

기존 서비스 교체에는 짧은 중단이 발생할 수 있다. 실패하면 이전 코드/프록시를 복원하고 DB는 보존한다. 이전 코드와 호환되지 않는 DB 변경은 이 방식으로 자동 복구할 수 없으므로 별도 이관/복원 계획이 필요하다. 이전 릴리스·이미지·백업은 자동 삭제하지 않으며 디스크 사용량을 관리한다. 내부 인증서는 최초10년 유효하며 배포 전30일 잔여를 확인한다. 만료 전 운영자가 인증서 교체와 최초 설정을 수행한다. 공개 Caddy 인증서 갱신은 기존 프록시 운영 범위다.

운영 Node CLI는 `TLS_CERT_PATH`·`TLS_KEY_PATH` 두 값을 함께 받으면 HTTPS(기본443)로 실행한다. 둘 다 없으면 HTTP(기본8787)이며 개발 서버는 기존 HTTP를 유지한다. nimp Compose는 환경값을 직접 주입하고 TLS·DB만 마운트한다. 기존 아래 수동 HTTP 배포 예시는 별도 환경용이다.

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
npm run desktop:build -- --no-bundle
```

설정 없는 앱도 계정 모달과 로컬 저장은 작동하며, 로그인 시 서버 설정 안내를 표시한다. Google secret은 이 변수나 앱 코드에 넣지 않는다.

로컬 서버 테스트는 Node 24에서 `PUBLIC_ORIGIN=http://127.0.0.1:8787`을 쓴다. HTTP loopback만 개발 예외로 허용한다. 서버 DB 백업은 `docker compose -f server/compose.yaml stop calculator` 후 `server/data/` 전체를 안전한 곳에 복사하고 `start calculator`로 재개한다. 운영 중 파일 하나만 복사하면 WAL의 최신 쓰기를 놓칠 수 있다.

## 검증

- `npm test`: 실제 임시 HTTP 서버와 SQLite로 OAuth state·브라우저 바인딩·PKCE·재사용/실패, 계정 격리, 저장 형식/용량, CSRF/CORS, 앱 일회성 전달, 로그아웃/만료, 토큰 해시, 비공개 파일 차단을 검사한다. Google 응답은 mock이며 실제 Google 로그인 성공을 증명하지 않는다. 클라이언트는 Settings 스냅샷/복원·미설정/401·쿠키/리디렉션을 검사한다.
- UI 변경은 실제 브라우저에서 계정 모달·로그인 전후·보관함·작은 화면·키보드 닫기/포커스를 검사한다. 기존 저장 계약·구조는 `npm test`, 배포 포함은 verify-es-module-entry.mjs의 --web/--dist로 확인한다.
- Docker 이미지 빌드/실제 Google 키·도메인·TLS·홈 서버 배포는 별도 실환경 확인 사항이다.


공식 근거: [Google 서버 OAuth](https://developers.google.com/identity/protocols/oauth2/web-server), [Google OAuth 정책](https://developers.google.com/identity/protocols/oauth2/policies), [Node SQLite](https://nodejs.org/api/sqlite.html).
