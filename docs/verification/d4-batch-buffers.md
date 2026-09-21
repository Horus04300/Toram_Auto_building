# 개선 후보 11: 배치 버퍼 재사용과 노드 복사 감소

- 날짜: 2026-09-21. 기존 1~7·9~10번 변경을 보존했다.
- 구현: src-tauri/src/d4_native_solver.rs.
- 측정 원본: d4-batch-buffers-measurements.json.

## 구현과 보존 계약

NativeSearchSession이 입력 Vec과 순서별 결과 Vec의 용량을 배치 사이에 재사용한다. 입력은 Arc<Vec<WorkItem>>로 NodeBatch와 읽기 전용 공유하며 기존 nodes.to_vec() 복제를 제거했다. expand_parallel_node와 내부 lookahead는 WorkItem을 참조로 받으므로 작업자 진입 시의 node.clone()도 제거했다. 배치의 노드마다 네 트리 Arc를 두 번 복제하던 경로가 없어졌다. 이는 코드상의 복제 횟수이며 전체 할당 profiler 수치는 아니다.

작업자는 배치 공유 참조를 놓은 뒤 결과를 전송한다. coordinator가 모든 결과를 받은 뒤에는 입력을 단독 소유하여 drain하고 용량을 유지한다. 결과는 원래 입력 인덱스에 기록하며, 누락 여부와 오류를 검사한 뒤 같은 순서로 병합한다. 채널 실패 시 pool을 종료·join한 후 부모 노드를 복원한다. 평가 오류·취소·deadline에도 기존 부모 복원 계약을 유지한다.

노드 단위 atomic 작업 배정, 후보·상한·분할·평가식·동점 규칙은 유지한다. 임시 버퍼는 checkpoint에 저장하지 않는다. Native/checkpoint v5, split v3, 계산 v2를 유지한다. 작업자별 반환 Vec, 자식 Vec, 채널·배치 제어 객체는 이번 변경의 재사용 대상이 아니다. 입력·결과 버퍼는 세션 최대 배치 용량을 세션 수명 동안 보유한다.

## 검증

- cargo test --manifest-path src-tauri/Cargo.toml -q: PASS 148개(41+41+12+54).
- 기존 불균등 배치 0/1/7/31/33/65/257개와 1/2/8/16/64 작업자 회귀에 공유 참조 회수를 추가 검증했다. 완료 순서와 무관한 결과·통계, 취소/deadline을 확인한다.
- 신규 회귀는 스레드 수를 바꾸며 반복 취소해 입력·결과 버퍼 주소 재사용, 빈 버퍼 정리, checkpoint frontier·incumbent 보존을 확인한다. 기존 오류 부모 복원·직렬/병렬 exact·동점·pause/resume 회귀도 통과했다.
- npm run test:r0: PASS 70/70 스크립트. Native 저장 E2E는 TORAM_E2E_CDP 미설정 SKIP.
- npm run verify:r9, Rust fmt --check, clippy --all-targets -- -D warnings, release parallel 빌드: PASS.
- node tools/audit-stack-source-links.mjs --require-s1: PASS 427/427.

실제 WebView/IPC E2E와 설치·배포는 미실행이다.

## 측정

Windows / Ryzen 7 9800X3D, P6 물리 근거리 전체 후보 992/844/724/929. 변경 전후 release binary를 보존하고 새 프로세스에서 교대로 실행했다. 빌드·테스트와 측정은 겹치지 않았다. D4_SESSION_BENCH_MS=30000, D4_P6_THREAD=8 또는 16, D4_NATIVE_BINARY=<비교 binary>, D4_P6_REPORT=<json>으로 node tools/benchmark-d4-native-p6.mjs를 실행했다. 세션 wall은 JS 준비·UI/IPC를 제외한다. 단일 입력의 측정이며 다른 환경 및 cold 10회 P95 달성을 뜻하지 않는다.

스레드별 전/후→후/전 순서를 두 차례 반복하여 각 4회 측정했다.

| 스레드 | 변경 전 평균 세션 wall | 변경 후 평균 | 평균 단축 |
| --- | ---: | ---: | ---: |
| 8 | 4005.624ms | 3954.106ms | 1.3% |
| 16 | 3125.653ms | 3065.596ms | 1.9% |

16회 모두 exact 14,097과 동일 추천 ID를 반환했다. 양쪽 모두 4쌍 중 3쌍은 단축, 1쌍은 증가했다. 효과는 작고 측정 편차가 있어 일관된 속도 향상으로 단정하지 않는다. peak working set은 약 55~57MiB였다. CPU 시간 0인 샘플은 측정기 값 그대로 보존했으며 실제 CPU 무사용으로 해석하지 않는다.

최종 16스레드 100ms 취소: cancelled, solver 100ms / 외부 wall 288.92ms, exact false·인증 upper 제거 검사 통과. 100ms deadline: bounded, 세션 100.0561ms, lower 14089 / upper 18702로 oracle 14,097을 포함한다.
