# 개선 후보 7: 사용하지 않는 중간 결과 생성 생략

- 날짜: 2026-09-20. 후보 1~6의 변경을 보존했다.
- 측정 원본: `d4-deferred-snapshots-measurements.json`.

## 변경

`NativeSearchSession::advance_parallel_slice_with_control`은 기존과 같은 작업 묶음을 실행하고 frontier·incumbent·counter·실행 시간을 병합한 뒤 결과 객체 없이 반환한다. 기존 `run_parallel_slice_with_control`은 이 메서드 호출 후 snapshot을 반환하는 호환 경로로 유지했다.

`d4_service.rs`는 진행 알림 주기가 됐거나 탐색이 완료됐을 때만 snapshot을 만든다. 취소·일시정지·deadline의 기존 종료 분기도 snapshot을 유지한다. 완료 시 진행 알림과 최종 응답이 같은 snapshot을 사용한다. 결과에 필요한 추천 ID·네 package ID 복사, 선택 스탯 재합산, status 문자열 생성을 사용하지 않는 묶음에서는 생략한다.

탐색 순서·상한·동점·미해결 work 복원·checkpoint 표현·진행 알림 간격은 변경하지 않았다. Native/checkpoint v5, split v3, 계산 v2를 유지한다. 결과 객체 내부 캐시를 추가하거나 낡은 추천을 재사용하지 않는다.

성능 bridge의 세션 루프도 반환값을 버리던 호출을 새 메서드로 바꿨다. P6 8스레드 9,301묶음은 snapshot 9,302→1회, 16스레드 4,653묶음은 4,654→1회다. 이는 루프와 최종 반환 경로에서 계산한 호출 수이며 할당 profiler 결과가 아니다. 실제 서비스는 진행 알림·종료 snapshot이 추가되므로 1회라고 주장하지 않는다.

## 검증

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 139개(38+38+12+51).
- 신규 테스트는 즉시 snapshot과 지연 snapshot의 결과·checkpoint 전체를 실행 시간 필드만 제외하고 비교한다. 취소 신호, 이미 지난 deadline, 정상 진행, 완료 후 재호출을 포함한다. 테스트 작성 중 Result 래퍼를 풀지 않아 실행 시간 정규화가 잘못된 문제를 수정한 뒤 전체 재실행했다.
- 기존 1~64스레드 exact/동점·오류 복원·pause/resume·checkpoint·대기 시간 제외 회귀 유지.
- `npm run test:r0`: PASS, 70/70 스크립트 집계. JS/Rust parity 1,920건 및 선검사 28,800회, Native client/UI continuation 포함. Native 저장 E2E는 CDP 미설정 SKIP.
- `npm run verify:r9`: PASS. R8의 기존 메서드명 검사를 새 실행 진입점과 취소/deadline 전달 검사로 갱신하고, 알림 조건 안의 snapshot 생성 검사도 추가했다.
- fmt, clippy `--all-targets -- -D warnings`, release parallel 빌드: PASS.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, 427/427.
- 최종 binary 16스레드 100ms 취소: cancelled, solver 100ms / 외부 wall 304.594ms. exact false 및 인증 upper 제거 확인.
- 최종 binary 16스레드 100ms deadline: bounded, 세션 wall 100.076ms, lower 14,089 / upper 19,254로 oracle 14,097을 포함한다.

실제 WebView/IPC E2E와 설치·배포는 미실행이다.

## 성능 측정 조건

Windows / Ryzen 7 9800X3D, P6 물리 근거리 후보 992/844/724/929, release binary. `D4_SESSION_BENCH_MS=30000`, `D4_P6_THREAD=8` 또는 `16`, `D4_NATIVE_BINARY=<비교 binary>`, `D4_P6_REPORT=<json>`으로 `node tools/benchmark-d4-native-p6.mjs` 실행. 빌드·회귀 검증을 측정과 겹치지 않았다.

각 스레드에서 전→후, 후→전 순서를 두 번씩 반복해 전후 각 4회 측정했다. 첫 두 회차가 엇갈려 두 회차를 추가했다. 세션 wall은 JS 준비·실제 UI/IPC를 제외하며, bridge는 주기적 진행 알림을 보내지 않는다. 실제 앱 전체 성능, 루브닐·마법·듀얼 입력, cold 10회 P95는 입증하지 않는다.

| 스레드 | 변경 전 평균 세션 wall | 변경 후 평균 | 변화 |
| --- | ---: | ---: | ---: |
| 8 | 4,399.635ms | 4,246.333ms | 3.5% 단축 |
| 16 | 3,171.161ms | 3,269.102ms | 3.1% 증가 |

16회 모두 exact 14,097과 동일 추천 ID를 유지했다. peak working set은 전후 약 58~60MB다. 불필요한 객체 생성은 제거했지만 전체 실행 시간 개선은 스레드 수에 따라 다르며, 16스레드 회귀가 남아 있다. 할당 감소를 보편적인 시간 단축으로 해석하지 않는다. 해당 회귀의 원인은 이번 측정만으로 확정하지 않았다.
