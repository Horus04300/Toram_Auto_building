# 부족량 기반 공통 검사 순서 실험

2026-10-06. 사용자 제안의 요구조건까지 부족한 양을 입력별 표본으로 삼아, 공통 검사 순서를 선택하는 구현을 직접 적용·검증했다. 유의미한 공통 가속을 확인하지 못해 제품 승격을 취소하고 시작 전 solver/evaluator를 복원했다. 기존 공격 상한 커널·평가 최적화와 Native/checkpoint v13을 유지한다.

## 구현한 정책

최대 128개 균등 분포 조합과 기존 초기해 2~3개를 표본으로 사용했다. 준비된 네 장비의 실제 패키지를 하나씩 선택하고 실제 baseContext·요구조건으로 평가한다. 이름으로 분기하지 않으며 추가 AMPR/CRIT 가산을 넣지 않았다. 잠금·금지·계보 계약을 반영한 준비 후보는 그대로다.

부족량은 max(0, 목표-실제값)/max(1, abs(목표))로 단위를 맞춰 비교한다. HP, MP·AMPR, CRIT 검사 묶음의 실패 빈도를 우선하고 동률에는 상대 부족량 합을 사용한다. MP는 AMPR에 필요한 값이므로 먼저 계산한다. ASPD는 기존 마지막 위치를 유지한다. 제약이 없거나 모든 그룹이 고정된 경우 표본 작업을 생략한다.

초기 표본은 기존 결합 상한이 이미 제거하는 조합 때문에 CRIT 우선으로 치우쳤다. 후속 구현은 결합 검사를 통과한 조합으로 utility 검사 순서를 선택했다. 같은 전체 표본에서는 다섯 AMPR·CRIT 지지 방향의 탈락 빈도를 집계해 가장 많이 탈락시킨 방향부터 검사한다. 다섯 방향과 공격 상한 45개 방향은 모두 유지한다. 직접 배열 접근·전개를 사용하며 API의 추가 호출 비용도 줄였다.

실제 루브닐 진단에서 중복 제거 후 130개 표본 중 기존 결합 검사를 통과한 것은 6개였다. 이 6개에서 HP 실패 0, MP·AMPR 실패 4, CRIT 실패 1로 MP·AMPR 우선을 선택했다. 결합 방향별 실패 횟수는 [105,110,116,119,117]이며 인덱스 3을 우선했다. 이 진단 실행은 성능 평균에 포함하지 않았다.

표본은 검사 순서만 선택한다. 과거 입력의 판정이나 학습 예측으로 후보를 제외하지 않는다. 모든 생존 조합은 기존 정확한 조건 검사·대미지 계산을 거친다. 코드·상한·최적 점수·동점 의미를 유지하는 순서 변경이므로 실험도 Native/checkpoint v13을 사용했다. 정책은 immutable 트리에 준비하고 역직렬화/재개 시 원본에서 재구성한다.

## 같은 입력 전후·고정 순서 비교

AMD Ryzen 7 9800X3D, Node v24.17.0, Native 16 threads. 입력·모드·버전당 fresh process 10회다. before는 시작 전 제품, fixed는 새 커널·API 정리를 사용하되 기존 검사 순서와 결합 방향을 고정한 분리 비교, adaptive는 부족량 표본으로 순서를 선택한 최종 실험이다. 실제 입력 3개 모드에는 3개 버전, 과거 fixture 2개에는 before/adaptive를 비교해 총 130회 실행했다. 실행 순서를 회전·역순으로 배분했으며 컴파일·테스트와 성능 측정은 겹치지 않았다.

전체 시간은 JS scenario·후보 생성부터 Native 결과 복원·최종 JS 재평가까지다. UI·WebView IPC는 제외한다. 앞선 날짜의 측정 평균을 이번 baseline으로 사용하지 않았다.

| 입력·모드 | before Native ms | fixed Native ms | adaptive Native ms | 전체 평균 초 before→adaptive |
|---|---:|---:|---:|---:|
| 실제 루브닐 · release | 388.4 | 387.1 | 385.6 | 1.027 → 1.026 |
| 실제 평타 · release | 394.4 | 399.1 | 400.9 | 1.041 → 1.050 |
| 과거 전체 해제 fixture · release | 505.4 | — | 511.0 | 1.252 → 1.256 |
| 과거 잠금 fixture · release | 77.2 | — | 77.9 | 0.644 → 0.646 |
| 실제 루브닐 · debug | 1964.5 | 1943.2 | 1928.5 | 2.630 → 2.602 |

실제 루브닐 debug는 before 대비 Native 1.8% 감소했지만 고정 순서 정리 대비 부족량 정책 자체의 차이는 0.76%다. release에서는 각각 0.72%, 0.39%다. 실제 평타 release는 before 대비 1.65%, fixed 대비 0.45% 느렸다. 루브닐 release 전체 P95는 1.048→1.055초, 평타는 1.062→1.089초다. 배포 빌드에서 의미 있는 가속을 확보한 것으로 판정하지 않았다.

현재 정책은 동일한 상한과 후보 공간을 검사하는 순서를 바꾼다. 실제 루브닐 release 방문량은 평균 1,083,528→1,083,539개, 평타는 1,053,353→1,053,331개로 거의 같았다. 병렬 스케줄에 따른 소폭 차이는 허용한다. 기존 강한 상한이 먼저 많은 조합을 제거하며, 순서 변경으로 아끼는 비용이 작아 정책 선택·분기 처리 비용을 확실히 회수하지 못했다. 모든 입력에 공통 기준을 사용할 수 있다는 성질만으로 실행시간이 줄어드는 것은 아니다.

총 130회 exact 점수·전체 최적 조합·compiled/prepared problem hash가 일치했다. 루브닐 1,753,977.72, 평타 67,120을 보존했다. 입력은 실제 딜검방 저장 세팅의 루브닐·실제 콤보·에투왈 단일 잠금과 같은 세팅의 평타다. 과거 fixture는 불완전 입력의 회귀·퇴행 검사이며 실제 듀얼 성능 근거로 사용하지 않는다. 실제 듀얼 입력 검증은 이번에도 수행하지 않았다.

## 검증·제품 상태

- 실험 cargo test --offline --manifest-path src-tauri/Cargo.toml: 334 PASS(80+73+73+22+86, 공유 모듈 중복 포함). 물리/마법/듀얼 평가의 값·거절 단계·지연 합산·점수 bit 동치, 다섯 방향의 모든 순서와 부분공간의 기존 참조 판정 동치, 입력 역순·JSON 원본 보존·정책 재구성을 추가했다. 기존 exhaustive oracle·feasible coverage·1~64 threads·deadline/cancel/checkpoint Gate도 유지했다.
- npm run test:regression: 76/76 프로세스 PASS. Native 저장 E2E는 TORAM_E2E_CDP 미설정 SKIP이다.
- npm run verify:architecture; cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings; cargo fmt --manifest-path src-tauri/Cargo.toml --check: PASS.
- node tools/verification/audit-stack-source-links.mjs --require-s1: 427/427 PASS.
- 최종 실험 npm run bench:optimization:build 후 실제 fixture --repeats 1 --slice-ms 250: 같은 exact 점수·전체 조합으로 재개 완료. 이 표본은 성능 평균에서 제외했다.
- 제품 solver/evaluator는 시작 전 파일로 복원하고 여섯 Native 소스의 SHA-256을 시작 전과 대조했다. 복원 제품 Rust 321개·clippy·fmt 및 개발 앱/측정용 debug·release 빌드를 확인했다. 사용자 앱을 강제 종료하지 않았다.
- npm run ai:audit; git diff --check: PASS. [실험 패치](../../tools/benchmarks/experiments/crysta-deficit-order.patch)는 복원된 소스에 git apply --check로 적용 가능함을 확인했다. 제품에는 연결하지 않았다.

[측정 원본](crysta-deficit-order-measurements.json)에 입력 전체·점수/조합·개별 시간/카운터/메모리·세 버전의 소스/바이너리 hash·진단·실제 재개 결과·복원 확인을 저장했다. 로컬 산출물은 src-tauri/target/deficit-order/에 있다. 실험 패치는 같은 기반에서 재검토할 수 있도록 남겼으며 새로운 탐색량 감소 근거나 대표 표본 개선 없이 재적용하지 않는다.
