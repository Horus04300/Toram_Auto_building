# D4 분기 생성 할당 절감

- 날짜: 2026-09-16. 하위호환 강화는 계속 보류했다.
- 대상: `src-tauri/src/d4_native_solver.rs`의 분기 차원 선택과 자식 상자 생성.

## 변경과 보존 계약

네 장비 중 최대 두 차원을 선택하는 과정에서 두 개의 임시 Vec를 만들던 코드를 고정 크기 배열로 바꿨다. slack 내림차순·후보 수 내림차순·그룹 인덱스 오름차순의 기존 비교 순서를 유지한다.

`ChildBoxes` 반복자는 기존 LL/LR/RL/RR 순서로 최대 네 자식 상자를 하나씩 생성한다. 첫 부모 벡터와 단계별 확장 벡터를 없애고, 교체할 부모 Arc까지 복사했다가 즉시 버리던 작업도 줄였다. 2차원 분기에서 기존 임시 Vec 다섯 개(차원 선택 두 개, 자식 확장 세 개)를 제거했다. 병렬 스케줄러에 반환할 실제 자식 작업 Vec는 유지한다.

직렬 exact·직렬 session slice·병렬 work 확장·초기 shard 생성의 네 곳에 공통 반복자를 사용한다. 후보·초기해·상한 식·분기 순서·동점 정책·checkpoint 형식은 바꾸지 않았다. 취소/deadline은 각 자식 평가 전에 확인하며 중단된 부모를 재큐잉하는 기존 계약을 유지한다. 중단 시 일부 생성된 자식으로 부모 공간을 잘못 대체하지 않는다.

## 검증

- `cargo test --manifest-path src-tauri/Cargo.toml`: PASS, 91개(공유 모듈의 binary별 테스트 포함).
- 새 검증은 4개 그룹의 leaf/branch 16가지 패턴에서 생성 순서·원래 조합 수 보존·중복 없는 분할·반복자의 잔여 길이·종료 후 동작을 확인한다.
- 기존 exact·동점·1~64스레드·deadline·취소·pause/resume·checkpoint 회귀 유지.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo clippy --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`, 두 Native 개발 bridge release 빌드: PASS. 최초 fmt의 일시적 Windows 파일 매핑 오류는 재실행으로 해소했다.
- `node tools/test-d4-native-exact-p4.mjs`: PASS, 소형 exhaustive oracle와 Native 결과 동치.
- `node tools/test-d4-rust-native-parity.mjs`: PASS, 1,488개.
- `node tools/test-d4-native-client.mjs`, `node tools/test-d4-native-resume-ui-n5.mjs`: PASS.

## 성능 비교 조건

baseline은 signed envelope·분기 점수 캐시·스탯 합산 개선까지 반영한 직전 release binary(`d4_native_parallel-before-branch-alloc.exe`)다. 초기 코드와 비교해 이전 개선 효과를 재계상하지 않는다.

Windows / Ryzen 7 9800X3D / Node v24.17.0 / rustc 1.98.0, P6 물리 근거리 전체 후보, 8스레드. 패키지 수 992/844/724/929. `D4_P6_THREAD=8`, `D4_NATIVE_BINARY=<대상 binary>`, `D4_P6_REPORT=<기록 경로>`로 `node tools/benchmark-d4-native-p6.mjs` 실행. 유틸리티 감사는 비활성. 전→후 / 후→전 순서를 번갈아 각 네 번 새 프로세스로 측정한다.

solver 시간에는 JS 준비/Pareto가 포함되지 않는다. 외부 wall에는 Native 프로세스 실행 비용이 포함된다. PowerShell의 종료 CPU/exitCode가 일부 0/null로 나오는 기존 한계는 유지되므로 해당 필드로 성능을 판정하지 않는다.

실제 서비스의 30초 slice 전체/WebView/설치본 E2E, 배포 및 전체 필수 fixture cold 10회 P95는 미실행이다. 모든 입력의 10초 exact를 보증하지 않는다.

## 분기 할당만 변경한 결과

| 비교 | 순서 | 기존 solver ms | 변경 solver ms |
| --- | --- | ---: | ---: |
| 1 | 전→후 | 22,484 | 22,385 |
| 2 | 후→전 | 22,609 | 22,475 |
| 3 | 전→후 | 22,437 | 22,494 |
| 4 | 후→전 | 22,488 | 22,502 |

차이는 약 ±0.6% 이내로 유의미한 속도 개선을 확인하지 못했다. 이 변경은 분기 코드 공통화와 임시 할당 제거로 유지하며, 성능 개선 수치로 주장하지 않는다. 8회 모두 점수 14,097·최적 ID·평가 25,872,175회·방문 4,453,143회·bound 제거 12,593,214회·64/64 shard가 일치했다. 이어서 진행한 기본 설정 조회 캐시는 `d4-prepared-context.md`를 참조한다.
