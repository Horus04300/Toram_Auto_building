# D4 Native 실행 계약

- 갱신: 2026-09-05. 과거 N0~N6 단계 계획을 현재 실행 계약으로 정리했다.
- 역할: 실행 제어 수정 시 유지할 경계. 현재 기능/릴리스 상태는 `docs/handoff/current-development-handoff.md`, 정확성은 `docs/architecture/d4-exact-optimization-plan.md`가 기준이다.
- deadline·Channel progress·pause/resume·continuation·잠금 통합 경로는 이미 존재한다. 모든 입력의 30초 exact 또는 모든 CPU의 지속 포화를 보증하지 않는다.

## 1. 실행 흐름

사용자 정밀 계산 → JS 문제 준비 → 남은 예산/Channel을 Native에 전달 → 안전한 노드 묶음 실행 → frontier·incumbent·counter 병합 → 결과/continuation.

`assets/js/d4-native-client.js`가 준비 시작부터 사용한 시간을 차감해 `remainingBudgetMs`를 보낸다. `src-tauri/src/d4_service.rs`가 job 제어와 최대 4개 continuation session의 oldest eviction을 소유한다. `src-tauri/src/d4_native_solver.rs`의 NativeSearchSession이 탐색 상태를 보유한다.

제품 정밀 계산은 30초 slice를 자동 연결하며 exact·일시정지·취소·오류까지 진행한다. 사용자 대기 시간은 실제 준비/실행 누적 시간에 더하지 않는다. 일반 Worker에는 Native frontier 재개 계약이 없다.

## 2. 중단과 결과

| 사건/결과 | 유지할 의미 |
| --- | --- |
| exact | 미해결 공간의 최적성 증명 종료; continuation 제거 |
| deadline + feasible 해 | bounded, 인증 upper/gap, frontier 보존 |
| deadline + 해 미발견 | no-incumbent-yet; 불가능 증명으로 바꾸지 않음 |
| 사용자 pause | safe 경계에서 paused와 continuation 보존 |
| cancel/입력 변경 | cancelled, exact 아님, 인증 상한 제거, session 폐기 |
| 입력/잠금 오류·실행 실패 | 진단을 보존하며 최적성 증명으로 표시하지 않음 |

deadline과 cancel을 같은 flag/상한 없는 결과로 처리하지 않는다. 노드 내부에서 중단하면 해당 미해결 work를 frontier에 돌려놓는다. pending·active work를 빠뜨려 upper를 낮추거나 거짓 exact를 만들지 않는다. `gap = max(0, upper-lower) / max(abs(lower), epsilon)`의 JS/Rust 계약을 보존한다.

## 3. 진행·재개·캐시

- coordinator가 실제 평가 수·방문 수·lower/upper/gap·ready work·실행 시간을 Channel로 전달한다. worker hot loop에서 UI 이벤트를 직접 만들지 않는다.
- 평가 수/원시 전체 조합 수를 진행률로 표시하지 않는다. thread 표시만으로 실제 CPU busy time이나 tail 개선을 증명하지 않는다.
- resume은 같은 prepared problem·frontier·incumbent·누적 counter를 사용한다. 새 compile/seed 시작을 continuation으로 부르지 않는다.
- exact cache와 resumable session을 분리한다. bounded 결과만 캐시하고 frontier를 버리는 방식은 재개가 아니다.
- 입력/계산식/후보/실행 정책이 바뀌거나 창이 닫히면 해당 work와 continuation을 무효화한다. session 만료는 명시 오류로 처리하며 자동 Worker 재시작으로 바꾸지 않는다.
- 메모리 제한을 강화할 때도 work를 버려 인증 upper를 낮추지 않는다. 과거 계획에 적힌 TTL·추가 telemetry 필드를 구현된 기능으로 추정하지 않는다.

## 4. 병렬화·잠금 변경 경계

- 실행 중 분할되는 work도 누락·중복 없이 처리하고 모든 스레드 수에서 exact score/build ID를 보존한다.
- 현재 서비스의 slice 묶음은 `run_shared_tasks`를 호출한다. 별도의 `solve_exact_parallel_with_control` 경로가 존재한다고 서비스가 같은 스케줄러를 쓴다고 가정하지 않는다.
- 스레드 생성·큐 동기화·tail·평가 비용을 현재 제품 경로에서 계측한다. 과거 5초 CPU 표본/단일 exact 시간을 모든 입력의 처리량으로 일반화하지 않는다.
- 잠긴 크리스타는 compiler package에 보존되며 효과를 base와 package 양쪽에 중복 합산하지 않는다. 알 수 없는 잠금은 진단으로 차단한다.
- 잠금 0/1/2/8개, 빈 잠금, 강화 계보 충돌, 최종 package ID 복원과 JS 재평가를 계속 검증한다. 고정 기능을 재설계할 필요성은 실제 실패로 판단한다.

## 5. 검증과 남은 개선 후보

- `tools/test-d4-native-client.mjs`: 준비·결과 복원·cache·resume·만료.
- `tools/test-d4-native-resume-ui-n5.mjs`: UI 재개 연결.
- `tools/test-d4-native-runtime-n0.mjs`, `tools/test-d4-native-locks-n1.mjs`: 사용자 입력/잠금 경계.
- `tools/test-d4-rust-native-parity.mjs`: JS/Rust 평가 동치.
- Rust 단위 테스트: deadline/cancel/pause/checkpoint·직렬/병렬 exact·동점·session eviction.
- 실제 WebView/설치본 검증은 별도 실행 환경이 필요하다. mock/정적 연결 테스트를 실제 화면 E2E로 보고하지 않는다.

N0~N6 완료 이력은 기존 기능 연결을 뜻하며 추가 성능 개선 완료를 뜻하지 않는다. 현 구조 감사의 후속 후보는 작업 묶음마다 스레드 생성 비용과 결과 오류 표현이다. 입력 무효화는 계산 입력/실제 확정 변경에만 적용하고 화면 편집·중복 알림으로 session을 폐기하지 않는다. 보류된 피격/콤보 엔진을 이 작업에 포함하지 않는다.

이 문서에는 과거 실행 수치와 단계별 완료 로그를 다시 누적하지 않는다. 8 KiB 이하로 유지한다.
