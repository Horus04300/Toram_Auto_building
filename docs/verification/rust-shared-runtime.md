# Rust 공용 추천 코어

현재 상태는 [handoff](../handoff/current-development-handoff.md), 정확성 기준은 [추천 계약](../architecture/crysta-optimization-contract.md)을 따른다.

## 구현

engine/src/의 evaluator.rs·solver.rs·stats.rs·joint_supply.rs가 유일한 추천 코어다. 앱·개발용 Native 바이너리와 WASM이 같은 crate를 사용한다. 앱 디렉터리로 돌아가는 path include와 테스트 바이너리별 소스 복제를 제거했다.

평가·탐색 테스트는 evaluator_tests.rs·solver_tests.rs로 분리해 기존 private 접근·테스트 이름·89개 검사를 유지했다. 실행 알고리즘은 변경하지 않았다. JS는 ui/calculation/application/storage/update/optimization/data로 배치했다. Worker의 계산 모듈 import·manifest·TypeScript 출력·도구/문서 경로도 함께 갱신했다.

web/src/optimization/은 문제 compile·보수적 후보 준비·전송·결과 복원·JS 최종 평가·실행 제어를 담당한다. 빠른 추천은 Rust 초기해, 정밀 실행은 앱 Native 또는 웹의 동일 WASM 세션이다. 취소·중단/재개·인증 gap을 유지한다.

기존 JS 탐색기·seed·한계효용·pair·Worker pool 7개와 이에 종속된 테스트·실험 도구는 삭제했다. 대량 과거 계측 JSON·실험 설계 문서도 제거했다. 생성 로그는 desktop/target/에 쓴다. UI·저장 JSON v2·원문·스킬 데이터·사용자 샘플은 유지한다.

정확성 검사는 공용 Rust 단위 테스트, 실제 Native/WASM, 제품 후보 준비, 테스트 전용 소형 완전탐색으로 구성한다. 소형 완전탐색은 모든 조합의 점수와 동점 ID만 확인하며 추천 정책·가지치기·초기해·캐시가 없다.

## 사용자 입력 확인

2026-10-16, 정리 전 공용 Rust 전환에서 확인한 결과다. 모두 Native/WASM exact 점수·크리스타 ID·raw 옵션과 JS 최종 평가가 일치했다. 과거 수치를 정리 후 성능 향상으로 주장하지 않는다.

| 입력 | 최종 기대 대미지 | 웹 WASM 측정 |
| --- | --- | --- |
| 루브닐 재현 fixture | 1,123,905.36 | 875.9~964.8 ms |
| 인힘 마도구 사용자 샘플 | 737,214.9525 | 225.8~241.2 ms |
| 지팡이 크법 사용자 샘플 | 910,857.5775 | 1,375.2~1,437.6 ms |

Edge의 새 Worker 3회다. 루브닐은 초기 문제 compile을 제외하고 WASM 로딩~최종 재평가, 마법은 compile부터 최종 재평가까지이며 UI 렌더링은 제외했다. Native 마법 입력은 새 프로세스 3회, 마도구 357.1~362.2 ms·지팡이 535.6~540.0 ms였다. 런타임·스레드·계측 경계가 달라 코어 자체 속도 우열을 뜻하지 않는다.

마법 샘플은 원본 잠금·금지·요구조건을 유지한 차지 200%·강타 매직 캐논의 첫 타격 cannon1이다. 전체 콤보 대미지와 구분한다. 두 마법 입력의 빠른 초기해는 최종 조합과 같았으며 지팡이의 추가 정밀 시간은 최적성 증명에 사용됐다. 전체 입력의 10초 exact·모바일·P95·메모리 개선을 보증하지 않는다.

## 검증·재현

- npm run verify:architecture: 타입·저장·계산·실행·Native 경계.
- npm run test:regression: 현재 계산·입력·Native/WASM 회귀. 실제 앱 저장 E2E는 CDP 미설정 시 SKIP이다.
- cargo test --offline --manifest-path engine/Cargo.toml --lib: 89개 평가·상한·동점·직렬/병렬·중단/재개 테스트.
- test-crysta-wasm.mjs: 실제 WASM 40개 문제와 raw 완전탐색, 물리/마법·불가능 조건·동점·재개·최종 JS 평가.
- test-crysta-candidate-projection.mjs: 120개 context·5,426 완전탐색 completion·332 replacement 검사. 실제 제품 후보 준비를 사용한다.
- npm run verify:web:browser: Edge 개발/하위 경로·JSON 백업/복원·실제 Worker 완료/취소/재개·세션 재열기.
- npm run bench:optimization:build 후 node tools/benchmarks/benchmark-crysta-magic-wasm.mjs: 사용자 마법 두 입력의 Native/Edge 3회 동치·시간. CODEX_PLAYWRIGHT_PATH와 Edge가 필요하다. 결과는 desktop/target/rust-wasm-magic-comparison.json에 쓴다.

코어와 앱 두 manifest의 fmt/test/clippy를 확인한다. CI도 코어 테스트를 별도로 실행한다. 실제 설치·업그레이드 검증과 브라우저 검증은 구분한다.

2026-10-16 정리 후 실행: architecture·전체 회귀 67개 명령(실제 통과 66개, 저장 E2E 1개 SKIP), 공용 Rust 89개·앱 17개, 두 manifest fmt/clippy 및 WASM clippy, 웹/앱 배포 준비·진입점·실제 Edge·마법 두 입력 3회 동치·S1 427/427 통과. 생성 로그와 계측 JSON은 desktop/target/에 있으며 docs에 다시 쌓지 않는다. 이번 정리는 설치본을 배포하지 않았다.

추가 배치/배포 정리 후 architecture·67개 회귀 명령(66 PASS·1 SKIP)·공용 Rust 89개·두 manifest clippy·웹/앱 prepare·진입점·실제 Edge·S1 427/427을 확인했다. 웹 회귀는 원본 자료/로그/이전 파일 제거, 웹의 Native JS 제외, 라이선스·472개 데이터 아이콘과 동적 on/off 아이콘 보존을 검사한다. 실제 브라우저는 web/public HTTP 오류도 실패로 처리한다. 로그는 desktop/target/layout-*.log에 있다.
