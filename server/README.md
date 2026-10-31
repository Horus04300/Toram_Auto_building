# 계정 서버

account-server.mjs는 Google 로그인·계정별 빌드/장비/즐겨찾기 저장과 ../build/web/ 정적 배포를 제공합니다. inventory-store.mjs는 개인 구성·수정 충돌·검색/페이지·두 객체 조립과 요청 키 재시도 트랜잭션을 담당합니다. inventory-rules.mjs는 공용 트리 메타데이터·옵션·장비 호환·요리 검증을 연결합니다. 계산·추천은 사용자 기기에서 실행합니다.

로컬 전체 개발은 루트의 npm run web:dev 하나로 실행합니다. server/.env를 읽고 http://localhost:8787/에서 소스 화면과 실제 계정·인벤토리·게시판 API를 함께 제공합니다. 운영 배포는 node --env-file=server/.env server/account-server.mjs로 build/web/을 제공합니다. 검증은 npm test이며 환경 설정·HTTPS·OAuth·Docker는 ../docs/architecture/account-home-server.md를 따릅니다.

toram.nimp.dev 운영은 루트에서 `npm run web:deploy`로 검사·웹 빌드·SSH 전송·교체·HTTPS 확인을 실행합니다. 최초 Cloudflare에서 toram 터널 생성 → `npm run web:deploy -- --setup` → 표시된 서버 sudo 명령에서 터널 토큰 입력 → 공개 경로를 HTTPS caddy:443, Origin Server Name toram.nimp.dev로 등록합니다. TLS 검증은 켜둡니다. 기존 Google 키 두 값만 SSH로 보내며 로컬 DB는 전송하지 않습니다. `server/deploy/compose.yaml`의 cloudflared가 이중 NAT의 인바운드 연결을 우회하고 기존 proxy 네트워크의 Caddy HTTPS443 → Toram HTTPS443으로 연결합니다. Toram 호스트 포트는 공개하지 않습니다. `TLS_CERT_PATH`와 `TLS_KEY_PATH`를 함께 지정하면 운영 진입점은 HTTPS(기본443), 둘 다 없으면 개발용 HTTP(기본8787)입니다.

post-store.mjs는 공개 게시글·고정 릴리스·개인 사본 생성·게시글 즐겨찾기·검색을 담당합니다. request-receipts.mjs는 병합·공개·복사 생성의 원자적 재시도를 공유합니다. 게시판 공개 조회만 비로그인에 허용하며 개인 저장·게시·평가는 기존 세션을 사용합니다. 스키마는 가산 테이블로 만들며 기존 개인 저장을 재작성하지 않습니다. 별점은 보류입니다. 구형 API 쓰기도 inventory_objects를 사용하며 records는 읽기 보존합니다. record_links는 ID·수정 번호·외부 형식과 삭제 표식을 연결합니다.

.env와 data/의 SQLite DB는 비공개 사용자 데이터이며 Git·웹 배포 대상에서 제외합니다. 실제 Google 로그인·Docker·공개 배포는 mock 회귀와 별도로 검증합니다.

이관은 서버를 중지한 유지보수 시간에 수행합니다. `node tools/migrate-records.mjs --database PATH --report NEW_PLAN.json`은 읽기 전용 dry-run이며, `--apply --backup NEW_BACKUP.sqlite`를 명시할 때만 검증한 백업 후 대상·ID 매핑을 한 트랜잭션으로 기록합니다. 기존 records는 삭제하지 않습니다. 미지원 형식·변경된 원본·ID 충돌은 검토 대상으로 남기며 운영 이관은 이번 작업에서 실행하지 않았습니다.
