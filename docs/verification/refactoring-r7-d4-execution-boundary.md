# R7 — D4 / Worker / Native 실행 경계 검증

## 범위

- D4 탐색 알고리즘, 후보 삭제, Pair 정책, 안전 상한, `exact`/`bounded` 판정과 결과 정렬은 변경하지 않는다.
- `OptimizationProblem`, `OptimizationProgress`, `OptimizationResult`, `OptimizationRunner`를 `frontend/application/ports.ts`에 명시한다.
- `assets/js/d4-execution-adapter.js`가 Rust Native 우선 실행, Worker fallback, 취소, 일시정지, 재개, continuation 폐기의 유일한 실행 경계다.
- `optimizer.js`와 `optimizer-ui-controller.js`는 구체 Worker/Native 클라이언트를 직접 참조하지 않는다.

## 실행 계약

- Native를 시작할 수 있으면 기존 Rust 클라이언트에 그대로 위임한다.
- Native 시작/준비가 실패하면 기존처럼 Worker를 사용한다. 입력 버전이 바뀐 요청은 fallback Worker를 시작하지 않는다.
- 취소는 Native와 Worker에 모두 전달한다. 일시정지·재개·continuation 폐기는 Rust Native 세션에만 위임한다. Worker에는 존재하지 않는 재개 세션을 만들지 않는다.
- Adapter는 문제 컴파일, 후보 변환/삭제, 상한 계산, 탐색 또는 결과 정렬을 하지 않는다. 따라서 기존에 관찰 가능한 동점 순서와 tie-break만 보존한다.

## 검증 결과 (2026-09-01)

- `npm run verify:r7`: R2~R6 경계, R7 실행 계약, Adapter fallback/취소/일시정지/재개 검증 통과
- `npm run test:r0`: 현재 66/66 통과. 네이티브 저장 E2E는 `TORAM_E2E_CDP` 미설정으로 `SKIP`
- 소형 oracle·상한 property: `test-d4-evaluator-stage1`, `test-d4-global-optimizer-stage2` (oracle 3,430 / solver 144 / bounds 1,093), `test-d4-pair-frontier`, `test-d4-utility-dependencies` 통과
- Worker/Native 실행 회귀: `test-d4-worker-stage3`, `test-d4-browser-worker-runtime`, `test-d4-native-client`, `test-d4-native-resume-ui-n5` 통과
- JS/Rust parity: 실제 최종 크리스타 216개 × 6 구조 + 결정적 aggregate 1,152개, 총 1,488건 통과
- 실제 425개 5초 gate: `bounded`, 하한 14,089, 상한 20,371, gap 44.588%, 92,337회 평가, 첫 유효해 61ms, solve 5,002ms로 통과. 이 결과는 `exact`가 아니며 기존 bounded 의미를 보존한 것이다.
- `cargo test --manifest-path src-tauri/Cargo.toml`: 72개 통과 (19 + 19 + 5 + 29). 비ASCII 사용자 경로 canonicalize 경고는 결과에 영향이 없었다.
- `npm run desktop:build:exe`: Tauri no-bundle 실행 파일 생성 통과

## 남은 경계

- Rust Native가 아닌 Worker 경로에는 중단된 frontier를 재개하는 계약이 없다. Adapter가 이를 모방하거나 새 정렬·재탐색 정책을 추가하지 않는다.
- 10초 exact 성능 목표와 새 탐색 정책은 이 단계의 범위 밖이며 `docs/architecture/d4-exact-optimization-plan.md`의 별도 Gate를 따른다.
