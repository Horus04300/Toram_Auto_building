# 개선 후보 5: 고정 입력의 숫자·불리언 사전 준비

- 날짜: 2026-09-17. 후보 1~4의 변경을 보존했다.
- 구현: `src-tauri/src/d4_native_evaluator.rs`.
- 반복 측정 원본: `d4-prepared-scalars-measurements.json`.

## 변경과 보존 계약

`PreparedContext` 생성 시 각 고정 필드의 숫자와 불리언 해석 결과를 저장한다. 반복 평가의 `number`/`flag` 호출은 저장된 값을 읽으므로 JSON 타입 검사와 숫자 변환을 반복하지 않는다. 원래 JSON과 필드 값은 문자열·배열·선택값 조회 및 직렬화를 위해 유지한다. 추가 메모리는 준비 컨텍스트의 필드별 스칼라 저장 공간이며 평가마다 할당하지 않는다.

숫자 해석 실패는 기존과 같은 0, 불리언 해석 실패는 false다. 문자열 숫자를 숫자로 바꾸지 않는다. 별도 기본값을 쓰는 `finite_number`, 선택적 숫자, 배열과 문자열은 기존 경로를 보존한다. 등록되지 않은 키는 원래 JSON 조회로 처리한다. 역직렬화 시 캐시를 다시 만든다.

계산식·부동소수점 연산 순서·상한·후보 삭제·탐색 순서는 변경하지 않았다. 표현만 바꾸므로 Native/checkpoint v5, split v3, 계산 v2를 유지한다. 6번 요구조건 선검사 및 7번 결과 생성 생략은 이번 범위에 포함하지 않았다.

## 반복 성능 비교

Windows, Ryzen 7 9800X3D의 동일 환경에서 P6 물리 근거리 입력(후보 992/844/724/929)을 측정했다. 변경 전후 release binary를 별도로 보존하고, 각 스레드에서 전→후 / 후→전 순으로 두 번씩 새 프로세스를 실행했다. 빌드·테스트는 측정과 겹치지 않았다.

| 스레드 | 기존 평균 세션 wall | 변경 평균 세션 wall | 단축 |
| --- | ---: | ---: | ---: |
| 8 | 4,190.723ms | 3,931.084ms | 6.2% |
| 16 | 3,228.685ms | 2,985.891ms | 7.5% |

8회 모두 exact 14,097 및 동일 추천 ID를 반환했다. ID는 `weapon:도이+후빗||armor:알타달+칼레리프||additional:카나요간+칼레리프||special:저편의 잔영+칼레리프`다. peak working set은 전후 모두 약 58~59MB였다. 평가 수는 약 25,972,600회로 같으며 병렬 타이밍에 따른 소수 차이는 원본에 남겼다.

재현: release `d4_native_parallel`을 빌드하고 `D4_SESSION_BENCH_MS=30000`, `D4_P6_THREAD=8` 또는 `16`, `D4_NATIVE_BINARY=<비교 binary>`, `D4_P6_REPORT=<json>`으로 `node tools/benchmark-d4-native-p6.mjs`를 실행한다. 세션 wall은 JS 준비·UI·IPC 시간을 제외하며 원본에 외부 wall·CPU·준비 시간도 기록했다.

단일 물리 입력의 각 두 번 측정이다. 루브닐·마법·듀얼·유틸리티 부족 입력의 성능 향상과 전체 입력 cold 10회 P95는 입증하지 않았다. 이들 계산 경계의 회귀 통과를 성능 측정으로 해석하지 않는다.

## 이번 검증

- `cargo test --manifest-path src-tauri/Cargo.toml`: PASS, 132개(36+36+11+49).
- 새 테스트는 모든 준비 필드와 미등록 키에 누락/null/boolean/정수/-0/음수/큰 정수/문자열/배열/객체를 넣어 raw 경로와 숫자 비트·불리언·별도 기본값·원본 조회·직렬화/복원 동치를 확인했다.
- `npm run test:r0`: PASS, 70/70 스크립트 집계. JS/Rust parity 1,920건, native exact oracle, utility·마법·듀얼·루브닐 fixture 회귀 포함. Native 저장 E2E는 `TORAM_E2E_CDP` 미설정 SKIP.
- `npm run verify:r9`: PASS, 하위 구조 Gate 포함.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, 427/427.
- Rust fmt 검사, clippy `--all-targets -- -D warnings`, release parallel binary 빌드: PASS.

실제 WebView/IPC E2E, 설치·배포는 미실행이다.
