# 회귀 검사

npm test는 프론트엔드 준비·타입·모듈 경계·JS 회귀·S1·두 Rust manifest의 fmt/test/clippy를 실행한다. tools/tests/의 test-*.mjs는 tools/regression-fixtures.mjs의 단일 목록과 대조한다. normalValue는 원문·공식·명시적 불변식, characterization은 선택된 스킬 정의·저장 입력의 golden을 고정한다. API·저장·취소·상태 불변식은 normalValue로 검사한다.

공용 Rust 단위 검사는 평가·완전탐색·안전 상한·동점·병렬·중단/재개를 다룬다. JS 후보 준비는 실제 제품 구현을 검사하고 독립 소형 완전탐색과 축소 전후 최적 점수/동점 ID를 비교한다. 계산은 제품 WASM과 동결 JS oracle, Native를 대조한다.

실제 Tauri 저장 E2E는 TORAM_E2E_CDP가 없으면 SKIP이다. Windows 실앱은 tools/verification/audit-desktop-e2e.mjs의 격리 프로필로 실행한다. 브라우저 흐름·JSON/재열기·Worker·병렬 제어는 npm test -- browser로 확인한다.

npm test는 타입·실제 import 방향·Docker 의존 폐쇄·공개 IPC 등록을 검사한다. 파일 수·과거 함수명·배치 자체보다 현재 경계와 동작을 검증한다. 마지막 통합 결과는 ../handoff/current-development-handoff.md를 따른다.
