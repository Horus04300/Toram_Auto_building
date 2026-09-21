# 개선 후보 6: 유틸리티 요구조건 선검사

- 날짜: 2026-09-19. 후보 1~5를 보존했다. 후보 7은 미착수다.
- 원본 측정: `d4-utility-precheck-measurements.json`.

## 구현과 정확성

Native 평가기에서 HP·MP·듀얼 적용 전 AMPR·평타 CRIT·ASPD를 대미지 연산보다 먼저 계산한다. 기존 Requirements 판정이 실패하면 `None`을 반환하여 ATK/MATK, 발도 변환, 크리티컬 피해 및 피해 배율 계산을 건너뛴다. 통과하면 이미 계산한 스탯과 평타 CRIT 원시값을 재사용한다. 수식과 각 수식 내부의 연산·내림·정수 변환 순서는 그대로다.

초기해 후보, 완성 조합, 직렬/병렬 자식 envelope, 추가 분할과 shard 준비에 연결했다. 후보 삭제 조건이나 안전 상한을 강화한 변경이 아니다. 기존에 요구조건으로 버리던 동일한 공간에서 피해 연산을 생략한다. 평가 횟수는 계속 평가 시도 수다. `prunedByConstraint`는 기존처럼 자식 공간 제거 수이며 실패한 완성 조합 전체 수는 아니다.

루트의 불가능 결과에는 기존 피해 상한을 반환하는 계약이 있어 루트는 전체 평가를 유지한다. 실패 결과를 0점 summary로 위장하지 않는다. 일반 summary API도 전체 결과를 유지한다. 계산 결과·분할·저장 표현이 같으므로 Native/checkpoint v5, split v3, 계산 v2를 유지한다.

## 반복 성능과 한계

Windows / Ryzen 7 9800X3D, release binary, 30초 세션 한도. 기본 P6와 HP 제한 26,000/40,000 입력을 비교했다. HP 입력은 다른 네 요구조건을 null로 해제했다. 각 입력·스레드별 전후 각 2회, 실행 순서를 반대로 바꿔 반복했다. 빌드·테스트를 측정과 겹치지 않았다.

| 입력 | 스레드 | 변경 전 평균 세션 wall | 변경 후 평균 | 변화 |
| --- | ---: | ---: | ---: | ---: |
| 기본 | 8 | 3,850.271ms | 3,917.070ms | 1.7% 증가 |
| 기본 | 16 | 2,997.363ms | 3,123.759ms | 4.2% 증가 |
| HP ≥ 26,000 | 8 | 2,854.578ms | 2,724.185ms | 4.6% 단축 |
| HP ≥ 26,000 | 16 | 2,318.387ms | 2,285.095ms | 1.4% 단축 |
| HP ≥ 40,000 | 8 | 1,631.793ms | 1,527.586ms | 6.4% 단축 |
| HP ≥ 40,000 | 16 | 1,295.594ms | 1,285.251ms | 0.8% 단축 |

기본 입력에는 constraint 가지치기가 없고, HP 26,000 입력은 약 977,235회, HP 40,000은 약 2,953,750회였다. 모든 전후 결과는 exact이며 각 입력의 점수·추천 ID·상한이 일치했다(기본 14,097 / HP 26,000 14,089 / HP 40,000 13,051). 메모리는 전후 기본 약 58~59MB, HP 26,000 약 49~50MB, HP 40,000 약 44~57MB 수준이며 정확한 값은 원본을 따른다. 프로세스 표본 수집에서 CPU/메모리가 0으로 나온 값은 미수집으로 취급한다.

유틸리티 미달이 많은 입력을 위한 변경으로 채택했다. 기본 입력의 소폭 회귀가 남아 있으며 모든 입력이 빨라졌다고 주장하지 않는다. 16스레드 제약 입력은 두 회차가 엇갈린 경우도 있어 0.8~1.4% 평균 차이를 안정적인 개선으로 단정하지 않는다. 루브닐·마법·듀얼의 전체 탐색 성능, cold 10회 P95, UI/IPC 포함 성능은 이번 측정 대상이 아니다.

## 재현과 검증

`cargo build --release --manifest-path src-tauri/Cargo.toml --bin d4_native_parallel`로 변경 전후 binary를 각각 준비한다. `D4_SESSION_BENCH_MS=30000`, `D4_P6_THREAD=8` 또는 `16`, `D4_NATIVE_BINARY=<대상>`, `D4_P6_REPORT=<json>`으로 `node tools/benchmark-d4-native-p6.mjs`를 실행한다.

HP 변형은 `D4_P6_REQUIREMENTS={"maxHp":26000,"maxMp":null,"amprBeforeDual":null,"normalAttackCrit":null,"aspd":null}`과 `D4_P6_REFERENCE_BINARY=<비교 대상>`을 추가한다. 40,000도 같은 방식이다. 이 경로는 두 binary 모두 exact 및 동일 점수·ID·상한을 요구한다. 완전열거 oracle은 `D4_P6_PACKAGE_LIMIT=20`으로 별도 실행했다. 두 HP 입력 각각 160,000개 조합에서 JS oracle과 점수·ID가 일치했다(11,775 / 9,109). 작은 표본의 1~2ms 탐색 시간을 성능 근거로 사용하지 않았다.

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 136개(37+37+12+50). 새 검사에서 유틸리티 거부 후 피해용 스탯을 읽으면 실패하도록 하여 실제 조기 종료를 검증했다.
- `npm run test:r0`: PASS, 70/70 스크립트 집계. Native 저장 E2E는 `TORAM_E2E_CDP` 미설정 SKIP.
- parity bridge는 기존 1,920건 각각 5개 유틸리티 좌표의 -0.5/동일/+0.5 경계를 검사한다. 28,800회 선검사 판정 및 통과 summary가 전체 평가와 일치한다. JS 원본 계산 비교, 마법·듀얼·변환 경계도 유지했다.
- `npm run verify:r9`, `node tools/audit-stack-source-links.mjs --require-s1`(427/427), Rust fmt, clippy `--all-targets -- -D warnings`, release 빌드: PASS. clippy가 지적한 불필요한 참조는 제거 후 재검증했다.

실제 WebView/IPC E2E와 설치·배포는 미실행이다.
