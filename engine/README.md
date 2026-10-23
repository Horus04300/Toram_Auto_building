# 공용 Rust 추천 엔진

src/의 평가·탐색·스탯·공급 제약 구현을 웹 WASM과 데스크톱 Native가 함께 사용합니다. 화면·계정·파일 저장·앱 업데이트는 소유하지 않습니다.

- 평가: src/evaluator.rs, src/evaluator_tests.rs
- 탐색·상한·중단/재개: src/solver.rs, src/solver_tests.rs
- 앱 실행 수명·스레드 조립: ../desktop/src/optimization/
- 웹 연결·후보 준비: ../web/src/optimization/

루트에서 npm run wasm:build로 ../build/generated/wasm/에 출력합니다. Rust 검사는 cargo test --manifest-path engine/Cargo.toml --lib입니다. 변경 Gate는 ../docs/architecture/crysta-optimization-contract.md를 따릅니다.
