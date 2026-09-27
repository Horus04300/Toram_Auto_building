# 탐색 평가의 AMPR 중복 계산 제거

2026-09-25. `d4-post-utility-profile.md`의 2순위 후보를 구현·검증했다. 기존 부분 조합 검사와 진행 상한 수정 이후 소스를 기준으로 비교한다.

## 변경

- Native 탐색은 목표 판정과 대미지 점수만 필요하지만 기존 경로는 raw AMPR/평타 효과와 목표 AMPR/평타 효과를 모두 계산했다.
- `evaluate_utility_feasible_score`는 점수만 담는 `D4NativeScore`를 반환한다. 내부 공통 평가기를 const generic으로 분리해 이 경로의 raw AMPR 계산을 생략한다. 목표 AMPR 계산 및 단계별 조기 탈락 순서는 유지한다.
- 원시 summary 경로와 `evaluate_utility_feasible_summary` 대조 경로는 기존 raw AMPR를 계속 계산한다. score 전용 내부 임시 summary의 생략된 AMPR 필드는 외부로 반환하지 않는다. 점수 타입에는 유틸리티 필드가 없다.
- solver 및 utility-only probe가 점수 전용 경로를 사용한다. raw AMPR% 정책, MP/크리티컬/ASPD 목표 의미, 대미지 수식, 후보·분할·동점·checkpoint 내용은 변경하지 않는다. Native/checkpoint v7, 계산 v2, utility policy 2 유지.

## 검증

- 새 Rust 회귀는 MP 4구간 × AMPR% 3구간 × 조기 탈락/완료 6단계 = 72사례를 검사한다. 소수 AMPR, 음수 AMPR%, 패시브·액티브 평타 효과를 포함하며 기존 경로와 모든 목표 callback 값·점수가 일치한다. 기존 summary의 raw AMPR도 full 계산과 일치한다.
- `cargo test --manifest-path src-tauri/Cargo.toml`: 48+48+15+61=172개 통과. 바이너리별 중복 모듈 실행 포함.
- `npm run test:r0`: 71/71 프로세스 성공. raw JS/Rust parity 1938개, utility 105개 JS/직렬 Native/공유 세션 대조 포함. 실제 Native 저장 E2E는 CDP 미설정 SKIP.
- `npm run verify:r9`, `cargo clippy --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings` 통과. 처음 발견한 raw-summary 전용 바이너리의 미사용 점수 필드 경고를 해당 타입에 한정해 처리한 뒤 재검사했다.

## 성능 비교 재현

수정 전 `slow-profile/control.exe`를 `target/ampr-evaluation/before.exe`에 보존했다. 수정 후 `node tools/profile-d4-slow-inputs.mjs build`, `D4_EVALUATION_EXPERIMENT=ampr-evaluation node tools/benchmark-d4-partial-utility.mjs`로 세 입력을 측정한다. 기존 벤치마크 도구는 기본 partial-utility 출력 경로를 유지하며 환경변수로 별도 실험 폴더를 선택할 수 있게 했다.

16작업자, 입력당 전→후/후→전 각 2회, 총 12회 순차 새 프로세스 실행. 빌드·회귀 검사와 성능 실행을 겹치지 않는다. 두 바이너리 모두 초당 진행 snapshot이 있고 앱 UI/IPC·JS 후보 준비는 제외한다. 상세 입력/바이너리 해시·최종 결과·메모리·평가 수는 `d4-ampr-evaluation-measurements.json`에 기록한다. 과거 날짜의 시간과 직접 개선율을 계산하지 않는다.

| 입력 | 변경 전 | 변경 후 | 해석 |
| --- | --- | --- | --- |
| 루브닐 | 7.692 / 7.489초 | 7.632 / 7.551초 | 평균상 사실상 동일 |
| 듀얼 | 13.934 / 14.231초 | 13.573 / 13.559초 | 두 반복 모두 단축, 평균 약 3.7% |
| 유틸리티 충돌 | 4.053 / 4.218초 | 4.085 / 4.019초 | 평균 약 2% 감소지만 반복 범위가 겹침 |

12회 모두 exact, 입력별 점수·최적 ID·최종 upper가 일치했다. 변경 후 진행 snapshot의 upper도 최종 최적점을 포함했다. 듀얼의 완성 조합 열거 50,924,398회는 변하지 않아 동일 계산량의 평가 비용 감소를 관측했다. 다른 입력의 소폭 평가 수 차이는 병렬 작업 배치와 기존 로컬 통계 기반 부분 조합 검사 활성화 시점에 따라 발생한다.

현재 점수 전용 평가를 채택한다. 이번 두 반복에서 듀얼 개선을 관측했으며 모든 입력의 속도 향상이나 P95 달성을 주장하지 않는다. 이전 부분 조합 검사 기록은 `d4-partial-utility-pruning.md`에 보존한다. fmt·AI 문서 감사·diff 검사 통과. 설치본 UI/실제 저장 E2E는 이번에 실행하지 않았다.
