# 계정 서버

account-server.mjs는 Google 로그인·계정별 빌드/장비/즐겨찾기 저장과 ../build/web/ 정적 배포를 제공합니다. 계산·추천은 사용자 기기에서 실행합니다.

로컬 실행은 루트에서 npm run server:start, 검증은 npm run test:account입니다. 환경 설정·HTTPS·OAuth·Docker 배포는 ../docs/architecture/account-home-server.md를 따릅니다.

.env와 data/의 SQLite DB는 비공개 사용자 데이터이며 Git·웹 배포 대상에서 제외합니다. 실제 Google 로그인·Docker·공개 배포는 mock 회귀와 별도로 검증합니다.
