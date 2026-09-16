# D4 평가 스탯 직접 조회

- 날짜: 2026-09-16. 하위호환 강화는 계속 보류.
- 대상: `src-tauri/src/d4_native_evaluator.rs`.

## 변경과 보존 계약

상한/완성 조합 평가 때 `BTreeMap<String, f64>`에서 같은 스탯을 문자열로 반복 검색하던 작업을 줄였다. `DenseStats`가 평가 시작 시 map을 한 번 순회하여 36개의 숫자 필드를 채운 뒤, 기존 공통 수식에서 직접 읽는다. 임시 숫자 필드는 스택에 두며 별도 heap 할당은 없다.

캐시에 없는 이름은 원본 map에서 조회하므로 향후 새 스탯이 추가돼도 목록 누락 때문에 0으로 계산하지 않는다. 누락은 기존처럼 0이며, 있는 값은 그대로 복사한다. 원본 합산·envelope·연산 순서·수식·후보·초기해·동점 ID·checkpoint는 유지한다. 탐색 공간 축소가 아닌 평가당 비용 절감이다. 이전 기본 설정 캐시(`d4-prepared-context.md`)에 추가되는 변경이다.

## 정확성 검증

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 99개(26+26+8+39, 공유 모듈의 binary별 실행 포함).
- 새 테스트는 캐시된 모든 스탯을 개별/동시 입력하고, 없는 값·음수·소수·큰 값·부호 있는 0·비유한 값·향후 이름에서 원본 lookup과 비트 단위 일치를 검사한다. 비유한 값을 제품 유효 입력으로 승인한다는 뜻은 아니다.
- `node tools/test-d4-rust-native-parity.mjs`: PASS, JS/기존 Value 경로/새 map 경로 1,488개 동치.
- `node tools/test-d4-native-exact-p4.mjs`: PASS, exhaustive oracle 동치.
- `node tools/test-d4-evaluator-stage1.mjs`, `node tools/test-d4-global-optimizer-stage2.mjs`: PASS(oracle 3,430 / solver 144 / bounds 1,093).
- `node tools/test-d4-worker-stage3.mjs`, `node tools/test-d4-native-client.mjs`, `node tools/test-d4-native-resume-ui-n5.mjs`: PASS.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, S1 427/427.
- release exact/parallel bridge 빌드 및 `cargo fmt --manifest-path src-tauri/Cargo.toml --check`: PASS.

## 성능 비교 방법

Windows / Ryzen 7 9800X3D / Node v24.17.0 / rustc 1.98.0, P6 물리 근거리 전체 후보(992/844/724/929), 8스레드. `D4_P6_THREAD=8`, `D4_P6_PACKAGE_LIMIT=0`, 유틸리티 감사 비활성으로 `node tools/benchmark-d4-native-p6.mjs` 실행.

baseline은 바로 직전 기본 설정 캐시까지 포함한 `d4_native_parallel-before-dense-stats.exe`. `D4_NATIVE_BINARY`를 바꿔 전→후 / 후→전 순서로 새 프로세스에서 두 번씩 측정한다. 측정 중 빌드/테스트를 병행하지 않는다. 이전 개선 수치를 이번 효과에 합산하지 않는다.

solver 시간은 JS 후보 준비/Pareto를 제외하고, wall 시간은 Native 프로세스 실행 비용을 포함한다. 기존 PowerShell 종료 계측의 CPU 0/exitCode null은 성능 판정에 사용하지 않고 결과 JSON의 exact·점수·ID·완료 shard도 검사한다.

전체 필수 fixture cold 10회 P95, WebView/설치본 E2E와 배포는 미실행이다. 특정 fixture 반복 측정이며 모든 입력의 단축률이나 10초 exact를 보장하지 않는다.

## 측정 결과

| 비교 | 순서 | 기존 solver ms | 변경 solver ms | 기존 wall ms | 변경 wall ms |
| --- | --- | ---: | ---: | ---: | ---: |
| 1 | 전→후 | 13,306 | 11,686 | 13,530.510 | 11,865.070 |
| 2 | 후→전 | 13,371 | 11,237 | 13,552.785 | 11,413.911 |

각 비교의 solver 단축률은 12.2%, 16.0%. 두 번씩 평균은 13,338.5→11,461.5ms로 14.1% 단축됐다. peak working set은 기존 89,272,320~90,755,072 bytes, 변경 89,706,496~89,755,648 bytes로 비슷한 범위이며 메모리 절감 효과는 주장하지 않는다.

네 실행 모두 exact 14,097, 평가 25,872,175회, 방문 4,453,143회, bound 제거 12,593,214회, 64/64 shard 완료. 최적 ID도 `weapon:도이+후빗||armor:알타달+칼레리프||additional:카나요간+칼레리프||special:저편의 잔영+칼레리프`로 일치했다.
