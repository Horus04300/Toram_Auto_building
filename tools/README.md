# 개발 도구와 검사

실행 명령은 저장소 루트의 package.json에 모읍니다. 제품 원본은 ../web/·../desktop/·../engine/이며, 도구에 별도 계산기를 만들지 않습니다.

| 위치 | 역할 |
| --- | --- |
| prepare-frontend.mjs, web-dev.mjs | 공통 원본으로 배포본 조립·개발 서버 |
| support/frontend-paths.mjs | 배포 URL과 원본 파일의 대응 |
| build-wasm.mjs | 공용 Rust를 WASM으로 빌드 |
| extraction/ | 아이템·보스 원문 가공·수동 갱신 |
| tests/, fixtures/, regression-fixtures.mjs | 회귀 테스트·입력·분류 |
| verification/ | 구조·출처·실제 브라우저 검사 |
| benchmarks/, support/ | 계측·테스트 지원 |
| statting/ | 앱과 분리된 옵부 오프라인 실험 |

결과물은 ../build/ 또는 Rust target/에 씁니다. 주요 검사: npm run verify:architecture, test:regression, verify:web:browser, ai:audit.
