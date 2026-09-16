# D4 고정 보정값 사전 계산

- 날짜: 2026-09-16. 하위호환 강화는 보류 유지.
- 대상: `src-tauri/src/d4_native_evaluator.rs`.

## 변경과 계약

후보 스탯에 의존하지 않는 기본 ATK/MATK 보정 합계, 물리/마법 저항 배율, 확률 효과 기대 배율을 `PreparedContext` 생성 시 계산한다. 상한/완성 조합 평가에서는 준비된 f64 다섯 개를 읽는다. 후보에 따라 달라지는 총 스탯·무기 공격력·크리티컬 등은 계속 평가한다.

기존 표현식과 항목 순서·각 항목 floor·저항 반올림·확률 clamp를 그대로 공유한다. Value 참조 평가 경로는 매번 같은 표현식을 계산하고, 준비 경로만 재사용한다. 계산식/후보/분할/상한 정책/초기해/동점/취소 처리는 바꾸지 않았다. 캐시는 원본 JSON과 분리하고 역직렬화할 때 재구성하므로 checkpoint 형식과 버전은 유지한다.

## 채택하지 않은 실험

먼저 병렬 통계 카운터를 노드 내부에서 모아서 반영했다. P6 8스레드 전→후 비교는 11,061→11,007ms, 후→전 비교는 기존 10,925 / 변경 10,982ms였다. 유의미한 개선이 없어 해당 코드와 전용 테스트를 원복했다. 통계는 기존 갱신 방식이다. 이 실험 효과를 아래 결과에 포함하지 않는다.

## 검증

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 99개(26+26+8+39). 기존 설정 직렬화 테스트에 고정 보정값의 비트 단위 동치, 음수/소수 보정, 물리/마법 저항, 잘못된 타입, 확률 clamp와 복원 검증을 추가했다.
- `node tools/test-d4-rust-native-parity.mjs`: PASS, 1,488개에서 JS/Value 참조/캐시 경로 동치.
- `node tools/test-d4-native-exact-p4.mjs`: PASS, exhaustive oracle 동치.
- release exact/parallel bridge 빌드: PASS.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo clippy --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: PASS.
- `node tools/test-d4-evaluator-stage1.mjs`, `node tools/test-d4-global-optimizer-stage2.mjs`: PASS(oracle 3,430 / solver 144 / bounds 1,093).
- `node tools/test-d4-worker-stage3.mjs`, `node tools/test-d4-native-client.mjs`, `node tools/test-d4-native-resume-ui-n5.mjs`: PASS.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, S1 427/427.

## 측정 조건

Windows / Ryzen 7 9800X3D / Node v24.17.0 / rustc 1.98.0. P6 물리 근거리 전체 후보 992/844/724/929, 8스레드. `D4_P6_THREAD=8`, `D4_P6_PACKAGE_LIMIT=0`, 유틸리티 감사 비활성으로 `node tools/benchmark-d4-native-p6.mjs` 실행.

`D4_NATIVE_BINARY`로 직전 스탯 직접 조회까지 포함한 baseline(`d4_native_parallel-before-local-counters.exe`)과 변경본을 전→후 / 후→전 순서로 두 번씩 새 프로세스에서 측정했다. baseline 이름은 폐기한 첫 실험에서 저장했기 때문이며, 통계 카운터 변경을 포함하지 않는다. 측정 중 빌드/테스트를 병행하지 않았다.

solver 시간은 JS 준비/Pareto를 제외한다. wall은 Native 프로세스 실행 비용을 포함한다. PowerShell 종료 CPU/exitCode가 0/null로 나오는 기존 한계가 있어 해당 필드로 성능을 판정하지 않는다.

전체 필수 fixture cold 10회 P95, 서비스 30초 slice 전체/WebView/설치본 E2E와 배포는 미실행이다. 특정 fixture의 반복 결과이며 모든 입력의 단축률이나 10초 exact를 보증하지 않는다.

## 결과

| 비교 | 순서 | 기존 solver ms | 변경 solver ms | 기존 wall ms | 변경 wall ms |
| --- | --- | ---: | ---: | ---: | ---: |
| 1 | 전→후 | 11,185 | 10,563 | 11,358.400 | 10,740.510 |
| 2 | 후→전 | 10,990 | 10,686 | 11,166.044 | 10,866.770 |

solver 단축률은 각각 5.6%, 2.8%, 두 번씩 평균은 11,087.5→10,624.5ms(4.2%)다. peak working set은 기존 89,292,800~90,480,640 bytes, 변경 89,702,400~89,722,880 bytes로 비슷한 범위다.

네 실행 모두 exact 14,097, 평가 25,872,175회, 방문 4,453,143회, bound 제거 12,593,214회, 64/64 shard 완료. 최적 ID는 `weapon:도이+후빗||armor:알타달+칼레리프||additional:카나요간+칼레리프||special:저편의 잔영+칼레리프`로 일치했다.
