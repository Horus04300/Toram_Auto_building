# 공격 상한 계산 비용 개선 — 제품 반영

2026-10-05. [분리 실험](crysta-next-improvement.md)의 직접 계산 후보를 제품 Native solver에 적용했다. 아래 수치는 분리 prototype을 재인용하지 않고 최종 제품 manifest로 빌드한 바이너리를 전후 비교한 결과다. 기존 역할별 구조 변경과 사용자 작업은 보존했다.

## 변경과 적용 범위

src-tauri/src/optimization/solver.rs의 JointUtilityBounds::tighten_offense에서 4개 장비의 지지 배열 주소를 한 번 읽고, 임시 15개 합산 배열과 중첩 반복을 제거했다. 좌표별 15회 내림은 최솟값 선택 뒤 1회로 줄였다. 모든 공격 좌표가 비활성이면 작업을 생략한다. 세 좌표 × 15개 방향, 총 45개 방향·가중치·필요량·후보·분할·동점 계약은 그대로다.

고정 방향은 macro로 같은 scale-major 순서로 전개한다. 방향 5개·scale 3개의 배열 길이를 컴파일 시 검사하므로 목록의 길이를 바꾸고 전개를 갱신하지 않으면 컴파일이 실패한다. 원래 반복 방식은 cfg(test) 참조 구현으로만 유지한다. 제품 실행에 참조 재계산이나 계측을 넣지 않았다.

수치 동치: 양수 좌표 단위 u에 대해 min_i(floor(x_i)*u) = floor(min_i(x_i))*u이다. 기존 외향 정수 완화가 만든 지지값은 유한한 정확한 정수이며 k=1·2·4와 u는 양수 2의 거듭제곱이다. 기존 raw 좌표 상한과 min을 취하고, 더 작은 값일 때만 같은 좌표를 갱신한다. 평가기의 대미지 내림이나 옵션 값은 바꾸지 않았다. Native/checkpoint v13, split policy v4, 계산 v3를 유지한다.

무기·스킬·세팅 이름으로 적용 여부를 결정하지 않는다. 결합 공격 상한을 사용하는 모든 Native 입력의 공통 경로에 적용된다. 유효한 제약이 없어 상한이 비활성인 입력과 Worker fallback은 이 커널을 사용하지 않는다. 입력별 단축률이 같거나 모든 입력이 빨라진다고 주장하지 않는다.

## 제품 바이너리 전후 10회 측정

AMD Ryzen 7 9800X3D, Node v24.17.0, Native 16 threads. 입력·모드당 전후 각 10회, 총 100회. 같은 JS 소스와 원본 입력, 새 Node/Native 프로세스에서 before/after 순서를 번갈아 실행했다. 컴파일·테스트와 성능 측정은 겹치지 않았다. 전체는 scenario·후보 생성부터 Native 결과 복원·최종 JS 재평가까지이며 UI 렌더링은 제외한다.

| 입력·모드 | Native 평균 초 전→후 | Native 단축률 | 전체 평균 초 전→후 |
|---|---:|---:|---:|
| 실제 루브닐 · release | 0.425 → 0.405 | 4.8% | 1.086 → 1.060 |
| 실제 평타 · release | 0.413 → 0.398 | 3.5% | 1.062 → 1.048 |
| 과거 전체 해제 fixture · release | 0.537 → 0.534 | 0.5% | 1.300 → 1.289 |
| 과거 잠금 fixture · release | 0.080 → 0.079 | 1.7% | 0.654 → 0.657 |
| 실제 루브닐 · debug | 2.521 → 2.053 | 18.6% | 3.210 → 2.746 |

실제 루브닐 debug의 Native 단축은 18.6%, 전체 단축은 14.4%다. 전체 P95(nearest rank, 10회 최대값)는 3.318→2.857초다. release 루브닐 전체 단축은 2.4%, 평타는 1.4%로 작다. 평타 release 전체 P95는 1.082→1.083초, 과거 잠금 fixture 전체 평균은 0.654→0.657초로 개선되지 않았다. 짧은 탐색에서는 JS·전송 비용과 실행 편차가 크게 남는다. 배포 빌드의 큰 단축이나 인앱 표시 시간 개선을 확인한 것으로 해석하지 않는다.

실제 입력은 딜검방 저장 세팅의 루브닐·실제 콤보·에투왈 단일 잠금과 같은 세팅의 평타다. 인위적인 AMPR/CRIT 가산을 추가하지 않았다. 총 100회 모두 exact 점수·전체 최적 조합·compiled/prepared problem hash가 일치했다. 루브닐 1,753,977.72, 평타 67,120을 보존했다. 과거 fixture는 불완전 입력의 회귀·퇴행 검사이며 현재 사용자 세팅이나 실제 듀얼 입력의 성능 근거가 아니다. 실제 듀얼 입력의 성능 검증은 미완료다.

개별 시간·방문/평가 수·메모리·전체 원본 입력·소스/바이너리 hash와 재개 결과는 [측정 원본](crysta-offense-kernel-measurements.json)에 있다. 로컬 산출물은 src-tauri/target/offense-kernel/에 보관한다. 병렬 스케줄에 따른 작업 수 차이를 허용하며 최적 조합·점수·상한 계약은 그대로 검사했다. peak working set은 50ms 주기로 관측했으며 메모리 개선을 주장하지 않는다.

## 실행한 검증

- cargo test --offline --manifest-path src-tauri/Cargo.toml: 321 PASS(77+70+70+21+83, 공유 모듈 중복 포함). 기존 exhaustive oracle·조상 상한 coverage·JS/Rust parity·소수/큰 값·음수 기본 스탯·1~64 threads·checkpoint/deadline/cancel Gate를 유지한다.
- constrained_offense_covers_feasible_scores_in_every_ancestor_box: 기존 14가지 물리/마법/듀얼·실제 AMPR modifier·분수·넓은 CRIT%·음수 기본 스탯 입력의 각 조상 상자에서 새/참조 공격 좌표의 존재 여부와 f64 bit를 대조한다. feasible 조합의 좌표·최적 점수가 상한에 포함되는지도 검사한다.
- offense_kernel_matches_reference_for_every_direction_and_raw_cap: 15개 방향 각각, 음수/양수 지지값, 세 가지 좌표 단위, 활성 마스크 8개, 누락 좌표, 양수/음수 0과 소수 raw cap을 기존 참조 함수와 bit 단위로 대조한다. 무기별 별도 수치 보정을 만들지 않았다.
- npm run test:regression: 76/76 프로세스 PASS. Native 저장 E2E는 TORAM_E2E_CDP 미설정 SKIP이며 통과로 계산하지 않는다.
- npm run verify:architecture; cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings; cargo fmt --manifest-path src-tauri/Cargo.toml --check: PASS.
- node tools/verification/audit-stack-source-links.mjs --require-s1: 427/427 PASS.
- npm run bench:optimization:build 후 실제 fixture를 --repeats 1 --slice-ms 250으로 실행: 3 slice·재개 2회 뒤 전후 측정과 같은 exact 점수·전체 조합. source/binary stamp도 일치하며 이 표본은 성능 평균에서 제외했다.
- cargo build --offline --manifest-path src-tauri/Cargo.toml --bin toram-online-auto-build-calculator: 개발 앱 빌드 PASS. 사용자 앱을 강제 종료하지 않았다. 실제 Tauri IPC·UI 표시 시간은 별도 실측하지 않았다.
- npm run ai:audit; git diff --check: PASS.
