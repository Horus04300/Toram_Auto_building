# 정수 비율 산술

JS calculator.js와 공용 Rust evaluator.rs는 백분율·소수 배율을 정수 분자/분모로 계산하고 각 단계에서 기존 위치에 내림한다. 음수는 수학적 floor다. JS 안전 정수 범위는 Number, 소수 계수·범위 초과는 BigInt 분수, Rust는 대응 정수 비율을 사용한다. 계산 변경은 탐색 평가와 최종 JS 재평가 양쪽에서 검증한다.

후보 준비는 관련 옵션이 모두 i32 정수일 때만 Int32Array Pareto 비교를 사용한다. 소수·범위 초과는 반올림 없이 일반 비교로 되돌린다. 비교 예산·동점 ID·원본 raw 패키지를 보존한다.

- tools/tests/application/test-decimal-floor.mjs: 독립 정수 분수 75,250건, 음수·소수·큰 정수 경계와 실제 JS/Rust 대미지.
- tools/tests/optimization/test-crysta-integer-pareto.mjs: 제품 후보 준비의 1,268개 frontier/예산·i32/소수 경계.
- tools/tests/optimization/test-crysta-rust-native-parity.mjs: JS/Rust 실제 평가 동치.

현재 버전·검증 상태는 docs/handoff/current-development-handoff.md를 따른다. 과거 JS 추천기 성능 비교·실험 로그는 삭제했다.
