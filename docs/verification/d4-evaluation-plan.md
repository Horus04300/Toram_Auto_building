# 개선 후보 3: 입력별 평가 경로 준비

- 날짜: 2026-09-17. 합의한 후보 **3번**이며 4번 추가 분할 범위 조정은 미구현이다.
- 기준: 후보 2번 숫자 큐 비교 및 앞선 통계/메모리 개선까지 반영한 코드.
- 원본: `d4-evaluation-plan-measurements.json`.

## 구현 및 보존 계약

`PreparedContext` 생성 시 `EvaluationPlan`을 한 번 준비한다. 무기 종류를 enum으로 바꾸고, 물리/마법·공격력 선택 모드·화살·듀얼·서브 마도구·컨버전 적용 여부·무기 기본 ASPD·방어구 ASPD 보정을 캐시한다. 무기별 스탯 공격력·ASPD·안정률 분기는 문자열 대신 enum을 사용하며 식과 연산 순서는 그대로다.

`sum`, `higher`, `wizardBlend`는 ATK/MATK 모두 계산한다. 명시적 `atk`는 마법 타격이어도 ATK를 사용하며 마법 치명타/방어 판정은 유지한다. 기본/알 수 없는 모드는 기존과 같이 물리면 ATK, 마법이면 MATK다. 실제 사용하지 않는 최종 공격력 계산, MATK 컨버전 보정 또는 듀얼 ATK 보정을 생략한다. 기본 스탯 합산 등 공통 계산을 모두 제거한 것은 아니다.

발도→ATK 변환은 무기 공격력에도 연결되므로 마법에서도 유지한다. 듀얼 브링거의 STR/INT 비교는 후보에 따라 달라지므로 캐시하지 않는다. 스킬 계수·상한·후보·제약·탐색 정책은 바꾸지 않았다. 스킬 수치를 새로 추정하지 않았으며 기존 JS 계산 엔진을 oracle로 사용했다.

JSON 직렬화는 기존 원본만 저장한다. plan은 역직렬화 시 다시 준비되므로 checkpoint 복원에도 적용된다. 동일 계산의 실행 표현만 바꾸며 engine/checkpoint v4, 계산 v2를 유지한다. 미리 준비하지 않은 Value 경로는 ATK/MATK를 모두 계산해 생략 경로의 비교 기준으로 남겼다.

## 정확성 범위

기존 JS/Rust parity 1,488건에 432건을 추가했다. 12가지 주/서브 무기 조합 × 물리/마법 × 6가지 공격력 모드 × STR/INT 경계 3가지다. 양손검·활/자동활+화살·지팡이/마도구·권갑·선풍창·발도검·맨손·듀얼을 포함하고, 컨버전·듀얼 브링거·발도 변환을 함께 활성화한다. JS, Rust Value, PreparedContext/map, PreparedContext/NativeStats를 대조한다.

새 Rust 회귀는 알 수 없는/잘못된 타입의 무기·모드 fallback과 JSON 왕복 이후 후보 경계 평가 동치를 확인한다. 기존 exact·동점·취소·deadline·checkpoint 회귀도 유지한다.

## 성능

Windows / Ryzen 7 9800X3D, P6 물리 근거리 후보 992/844/724/929. 새 프로세스의 Native 세션 경로, 30초 한도. 빌드·테스트와 동시에 실행하지 않았다. 각 스레드에서 전→후 / 후→전 순서로 두 번씩 비교했다. 최종안의 첫 8스레드 비교 후 실행이 중단되어, 저장된 결과를 보존하고 나머지 비교를 이어 실행했다.

| 스레드 | 순서 | 기존 세션 wall | 최종안 | 단축 |
| --- | --- | ---: | ---: | ---: |
| 8 | 전→후 | 5,503.856ms | 5,497.560ms | 0.1% |
| 8 | 후→전 | 5,501.311ms | 5,245.274ms | 4.7% |
| 16 | 전→후 | 4,441.880ms | 4,333.656ms | 2.4% |
| 16 | 후→전 | 4,293.550ms | 3,866.593ms | 9.9% |

평균 단축률은 8스레드 약 2.4%, 16스레드 약 6.1%지만 편차가 크고 첫 8스레드 비교는 사실상 동률이다. 모든 결과는 exact 14,097과 기존 추천 ID였다. 평가 수는 25,932,301~25,932,305회로 병렬 타이밍에 따른 소수 차이가 있다. 최종안 peak working set은 약 77~93MB로 메모리 절감을 주장하지 않는다.

먼저 시도한 무기 enum 없는 plan은 16스레드에서 1.7~2.8% 느려 채택하지 않았다(`evalplan` 기록). 최종안은 `weaponplan` 기록이다. 두 단계 모두 보존했다.

재현: release `d4_native_parallel` 빌드 후 `D4_SESSION_BENCH_MS=30000`, `D4_P6_THREAD=8` 또는 `16`, `D4_NATIVE_BINARY=<전/후 binary>`, `D4_P6_REPORT=<json>`로 `node tools/benchmark-d4-native-p6.mjs` 실행.

세션 wall은 JS 준비·UI·IPC를 제외한다. 다른 마법/듀얼/루브닐 입력의 속도 개선 및 전체 입력의 cold 10회 P95는 미검증이다. CPU/exitCode 일부 표본의 기존 측정 한계 때문에 해당 값은 판정 근거로 사용하지 않았다.

## 최종 검증

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 125개(34+34+10+47).
- fmt `--check`, clippy `--all-targets -- -D warnings`, release parallel bridge 빌드: PASS.
- `node tools/test-d4-rust-native-parity.mjs`: PASS, 1,920건.
- `npm run verify:r9`: PASS, 하위 Gate 포함.
- `npm run test:r0`: PASS, 70개 스크립트 집계. Native exact oracle·계산·잠금·client/resume 회귀 포함. 실제 Native 저장 E2E는 `TORAM_E2E_CDP` 미설정으로 SKIP이다.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, S1 427/427.

설치·배포 및 실제 WebView/IPC E2E는 미실행이다.
