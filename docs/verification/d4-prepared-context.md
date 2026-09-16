# D4 기본 설정 조회 캐시

- 날짜: 2026-09-16. 하위호환 강화는 보류한 상태로 진행했다.
- 대상: `src-tauri/src/d4_native_evaluator.rs`, `src-tauri/src/d4_native_solver.rs`.

## 변경과 정확성 계약

상한과 leaf 평가에서 동일한 기본 설정의 JSON 필드를 반복 조회하던 비용을 줄였다. `NativeProblem`은 역직렬화할 때 `PreparedContext`를 만들고, 자주 읽는 필드는 문자열 키로 JSON 트리를 다시 탐색하지 않고 전용 필드에서 읽는다. 수식은 기존 평가 함수를 공유하고 입력 조회 방식만 제네릭으로 분리했다. 후보별 스탯 합산·반올림·연산 순서·상한·초기해·동점 정책은 유지한다.

캐시에는 값의 원래 JSON 타입과 누락 여부를 그대로 보존한다. 누락/null/잘못된 타입의 기존 기본값 처리를 바꾸지 않으며, 캐시에 없는 필드는 원본 조회로 처리한다. 원본과 캐시는 외부에서 수정할 수 없다. checkpoint에는 기존 원본 JSON만 직렬화하고, 복원할 때 캐시를 다시 만든다. 따라서 캐시 때문에 checkpoint schema/version을 추가 변경하지 않는다. JS fallback은 기존 구현을 유지한다.

개발용 summary bridge는 모든 parity 사례에서 기존 Value 평가와 실제 solver의 PreparedContext+map 평가가 같은지 추가 확인한 뒤 JS와 비교한다. 준비된 캐시 경로가 검증에서 빠지지 않게 했다.

이번 작업의 분기 생성 공통화는 `d4-branch-allocation.md` 참조. 그 변경만으로는 유의미한 시간 단축이 없었다.

## 검증

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 95개(25+25+7+38, 공유 모듈의 binary별 실행 포함). 신규 JSON 타입·기본값·알 수 없는 필드·직렬화 왕복·유효하지 않은 입력 검증 포함.
- `node tools/test-d4-rust-native-parity.mjs`: PASS, 1,488개에서 JS/기존 Rust/캐시 Rust 동치.
- `node tools/test-d4-native-exact-p4.mjs`: PASS, exhaustive oracle와 최적 결과 동치.
- `node tools/test-d4-global-optimizer-stage2.mjs`: PASS, oracle 3,430 / solver 144 / bounds 1,093.
- `node tools/test-d4-worker-stage3.mjs`, `node tools/test-d4-native-client.mjs`, `node tools/test-d4-native-resume-ui-n5.mjs`: PASS.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo clippy --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: PASS.
- `cargo build --manifest-path src-tauri/Cargo.toml --release --bin d4_native_exact --bin d4_native_parallel`: PASS.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, S1 427/427.

## 실제 전체 후보 측정

Windows / Ryzen 7 9800X3D / Node v24.17.0 / rustc 1.98.0. P6 물리 근거리, 패키지 992/844/724/929, 8스레드. `D4_P6_THREAD=8`, `D4_P6_PACKAGE_LIMIT=0`, 유틸리티 감사 비활성. `D4_NATIVE_BINARY`를 바꾸며 `node tools/benchmark-d4-native-p6.mjs`를 새 프로세스로 실행했다. 측정 중 빌드/테스트를 병행하지 않았다.

baseline은 직전 signed envelope·분기 점수 캐시·스탯 합산 개선을 포함한 `d4_native_parallel-before-branch-alloc.exe`다. 변경본은 이번 분기 생성 공통화와 설정 조회 캐시를 포함한다. 이전 개선 효과를 이번 수치에 다시 합산하지 않는다.

| 비교 | 실행 순서 | 기존 solver ms | 변경 solver ms | 기존 wall ms | 변경 wall ms |
| --- | --- | ---: | ---: | ---: | ---: |
| 1 | 전→후 | 22,678 | 13,096 | 22,870.265 | 13,276.934 |
| 2 | 후→전 | 22,600 | 13,122 | 22,784.180 | 13,298.344 |

solver 시간은 각각 42.3%, 41.9% 감소했다. 두 번씩의 측정 평균은 22,639ms→13,109ms(42.1% 단축)다. solver 시간에는 JS 후보 준비/Pareto가 포함되지 않는다. 외부 wall은 Native 프로세스 실행 비용을 포함한다. PowerShell의 exitCode가 null로 나오는 기존 계측 한계는 있어 결과 JSON의 exact와 완료 상태도 확인했다.

네 실행 모두 exact 14,097, 평가 25,872,175회, 방문 4,453,143회, bound 제거 12,593,214회, 64/64 shard 완료. 최적 ID도 `weapon:도이+후빗||armor:알타달+칼레리프||additional:카나요간+칼레리프||special:저편의 잔영+칼레리프`로 동일했다. 탐색량 감소가 아니라 평가 비용 감소다.

peak working set은 기존 89,968,640~90,001,408 bytes, 변경 90,021,888~97,009,664 bytes다. 원본 외에 캐시를 유지하므로 메모리 감소를 주장하지 않는다.

서비스 30초 slice 전체/WebView/설치본 E2E, 배포, 전체 필수 fixture cold 10회 P95는 미실행이다. 두 쌍의 특정 fixture 측정으로 모든 입력의 단축률이나 10초 exact를 보장하지 않는다.
