# 공용 Rust 평가·추천 런타임

현재 상태는 [handoff](../handoff/current-development-handoff.md), 정확성은 [추천 계약](../architecture/crysta-optimization-contract.md), 작업 수명은 [실행 계약](../architecture/native-optimization-runtime.md)을 따른다.

## 책임

- engine/src/evaluator.rs: full/summary/supply·정수 비율 산술·AMPR/확률/내성 프로필. Native 정수 DTO와 화면의 소수 full 값을 구분한다.
- engine/src/solver.rs·stats.rs·joint_supply.rs: 탐색·상한·스탯·공급 제약. Native와 WASM은 같은 crate를 사용한다.
- web/src/calculation/calculator.js: 입력/옵션 조립·WASM 호출·표시 문자열. 모듈 초기화 뒤 동기 API를 제공한다. 일반 계산에도 WASM이 필요하다.
- web/src/optimization/: 문제 compile·보수적 후보 준비·전송·package 복원·최종 재평가. 앱 작업 수명은 desktop/src/optimization/이 소유한다.
- tools/fixtures/calculation-oracle.mjs: 제품과 독립된 테스트 수식. 제품 import 그래프와 배포본에는 포함하지 않는다.

## 실행

빠른 추천은 WASM 세션의 초기해/트리 준비만 사용한다. 정밀은 앱 Native 또는 같은 웹 세션을 이어받는다. 웹 coordinator가 frontier를 소유하고 정밀 실행 때만 공유 메모리 Rayon 풀을 연다. COOP/COEP·SharedArrayBuffer가 없으면 단일 WASM으로 동작한다. 헤더·하위 경로 설정은 web/README.md를 따른다.

초기해 ID는 장비 수와 일치하는 완전한 문자열 배열만 전송한다. 불완전 초기해는 생략하며 null을 필터링해 장비 인덱스를 옮기지 않는다. 기본 스탯 비례의 상수/가변 판정은 절삭 경계와 네 장비 합산을 포함해 증명하고 안전하지 않은 상한은 fallback한다.

## 검증

- npm test: 실제 계산·입력·WASM/Native·잠금·취소·재개.
- 두 Cargo manifest의 fmt/test/clippy: 평가·완전탐색·안전 상한·동점·병렬·체크포인트·저장/앱 서비스.
- test-evaluator-integration.mjs: 독립 oracle과 full/summary/supply. test-decimal-floor.mjs: 독립 BigInt 산술. test-crysta-rust-native-parity.mjs: 독립 JS와 Native.
- test-crysta-candidate-projection.mjs·test-crysta-integer-pareto.mjs: 제품 후보 준비와 raw/동점/경계. test-crysta-wasm.mjs: 독립 소형 완전탐색.
- web:build 뒤 npm test -- browser: 실제 Chrome의 계산/저장/Worker·병렬 제어·단일 fallback. 실제 Windows 앱은 audit-desktop-e2e.mjs의 격리 프로필로 검사한다.

검사 파일은 tools/tests/ 아래에 있다. 비교 시 입력·출력·직렬화·표시·cold 초기화 범위를 맞춘다. 계측 계약은 optimization-computation-timing.md, 생성 결과는 build/ 또는 target/에 둔다. 단일 입력 시간이나 스레드 수를 모든 입력의 exact/P95 보증으로 일반화하지 않는다.
