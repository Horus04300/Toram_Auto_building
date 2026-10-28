# 정수 비율 산술

공용 Rust evaluator는 백분율·소수 배율을 정수 분자/분모로 계산하고 정의된 단계에서 내림한다. 음수는 수학적 floor다. JS의 산술 API는 같은 WASM export를 호출한다. 입력 소수·범위 초과·float32 옵션의 단위와 절삭 순서를 보존한다.

후보 준비는 관련 옵션이 모두 i32 정수일 때만 Int32Array Pareto 비교를 사용한다. 소수·범위 초과는 반올림 없이 일반 비교로 되돌린다. 비교 예산·동점 ID·원본 raw 패키지를 보존한다.

- tools/tests/application/test-decimal-floor.mjs: 독립 BigInt 분수와 음수·소수·큰 정수 경계·실제 대미지.
- tools/tests/application/test-evaluator-integration.mjs: 독립 JS oracle과 full/summary/supply 동치.
- tools/tests/optimization/test-crysta-integer-pareto.mjs: 제품 후보 준비의 frontier/예산·i32/소수 경계.
- tools/tests/optimization/test-crysta-rust-native-parity.mjs: 독립 JS oracle과 Native 평가 동치.

변경 Gate는 ../architecture/crysta-optimization-contract.md, 현재 버전·검증 상태는 ../handoff/current-development-handoff.md를 따른다.
