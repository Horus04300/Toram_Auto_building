# 공용 Rust 평가·추천 엔진

src/의 평가·탐색·스탯·공급 제약 구현을 웹 WASM과 데스크톱 Native가 함께 사용합니다. 화면·계정·파일 저장·앱 업데이트는 소유하지 않습니다.

- 검사 CLI: src/bin/crysta_native_{exact,parallel,summary}.rs. cargo run --manifest-path engine/Cargo.toml --bin 이름으로 실행하며 JSON·환경 옵션은 유지합니다.
- 평가: src/evaluator.rs, src/evaluator_tests.rs
- 탐색·상한·중단/재개: src/solver.rs, src/solver_tests.rs
- 앱 실행 수명·스레드 조립: ../desktop/src/optimization/
- 웹 연결·후보 준비: ../web/src/optimization/

루트에서 node tools/build-wasm.mjs로 ../build/generated/wasm/에 출력합니다. Rust 검사는 cargo test --manifest-path engine/Cargo.toml --lib입니다. 변경 Gate는 ../docs/architecture/crysta-optimization-contract.md를 따릅니다.

기본 WASM은 stable ES module, parallel/은 nightly-2025-11-15 + rust-src로 표준 라이브러리를 atomics·bulk-memory와 함께 다시 빌드한 ES module입니다. wasm-bindgen-cli 0.2.127을 사용합니다. wasm-threads feature에서 Rayon이 Native와 같은 노드 확장·incumbent·frontier 병합을 실행합니다. nightly와 RUSTFLAGS는 병렬 빌드 자식 프로세스에만 적용합니다.
