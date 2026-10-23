# 회귀 검사

npm run test:regression은 tools/regression-fixtures.mjs에 등록된 현재 기능을 검사한다. normalValue는 원문·공식·명시적 불변 조건, characterization은 유지해야 할 외부 동작을 뜻한다. 기준 커밋 표시는 이력 식별자이며 현재 제품 상태를 대신하지 않는다.

이전 JS 추천기·pair·Worker pool 전용 회귀는 구현과 함께 삭제했다. Rust 평가·탐색은 engine/src/의 단위 테스트로 검사한다. JS 후보 준비는 제품 구현을 직접 검사하고, 소형 완전탐색은 축소 전후 최적 점수·동점 ID를 독립 확인한다. 실제 WASM, Native serial/parallel, JS 최종 평가의 동치 검사를 유지한다.

화면·스킬·계산식·콤보·저장·업데이트 회귀를 유지한다. 실제 Tauri 저장 E2E는 TORAM_E2E_CDP가 없으면 SKIP이다. 브라우저 흐름·재열기 복원은 npm run verify:web:browser로 별도 실행한다. 현재 실행 결과는 docs/handoff/current-development-handoff.md와 docs/verification/rust-shared-runtime.md에 기록한다.
