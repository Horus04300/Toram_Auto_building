# 계정 서버

account-server.mjs는 Google 로그인·계정별 빌드/장비/즐겨찾기 저장과 ../build/web/ 정적 배포를 제공합니다. inventory-store.mjs는 개인 구성·수정 충돌·검색/페이지·두 객체 조립과 요청 키 재시도 트랜잭션을 담당합니다. inventory-rules.mjs는 공용 트리 메타데이터·옵션·장비 호환·요리 검증을 연결합니다. 계산·추천은 사용자 기기에서 실행합니다.

로컬 실행은 루트에서 npm run server:start, 검증은 npm run test:account입니다. 환경 설정·HTTPS·OAuth·Docker 배포는 ../docs/architecture/account-home-server.md를 따릅니다.

post-store.mjs는 공개 게시글·고정 릴리스·개인 사본 생성·게시글 즐겨찾기·검색을 담당합니다. request-receipts.mjs는 병합·공개·복사 생성의 원자적 재시도를 공유합니다. 게시판 공개 조회만 비로그인에 허용하며 개인 저장·게시·평가는 기존 세션을 사용합니다. 스키마는 가산 테이블로 만들며 기존 개인 저장을 재작성하지 않습니다. 별점·구형 저장 이관은 별도 범위입니다.

.env와 data/의 SQLite DB는 비공개 사용자 데이터이며 Git·웹 배포 대상에서 제외합니다. 실제 Google 로그인·Docker·공개 배포는 mock 회귀와 별도로 검증합니다.
