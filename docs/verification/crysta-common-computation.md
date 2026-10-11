# 최적화 공통 계산 비용 개선

2026-10-04. Native v13의 결합·공격 상한을 유지하면서 고정 계산, 스탯 합산·복사, JS 후보 준비의 공통 비용을 줄였다. 무기·스킬 이름이나 저장 빌드별 전용 경로를 추가하지 않았다. 계산식·후보 삭제 근거·분할·동점·저장 계약은 유지한다.

## 변경과 동치 근거

1. `optimization/evaluator.rs`: 기존 다섯 고정 보정값에 기본 CRIT, 주무기/보조무기 제련도 제곱, 컨버전 레벨 제곱, MP 고정 부분을 추가로 준비한다. 같은 표현식과 기본값, 연산 순서를 유지하고 역직렬화 때 재구성한다. 후보 스탯에 의존하는 부분은 캐시하지 않는다.
2. `optimization/stats.rs`, `solver.rs`: 완성 조합의 마지막 장비와 부분 Utility 검사에서 벡터를 복사·합산해 만들지 않고, evaluator가 읽는 좌표만 기존 왼쪽→오른쪽 순서로 더한다. 오른쪽에 없는 좌표는 왼쪽 값을 그대로 반환해 음수 0도 보존한다. 부모 합에서 값을 빼지 않는다. Utility 탈락 뒤 읽지 않는 공격 좌표는 합산하지 않는다. 마지막 재귀 호출도 생략하지만 후보 순서·평가/열거 수·각 후보의 취소/deadline 검사를 유지한다.
3. `optimization/exact-solver.js`: 넓은 스탯 최소값 조회는 실제 존재하는 옵션을 순회한다. 짧은 조회는 직접 키를 읽고, 사용자 정의 prototype은 이전 조회 의미를 보존한다. 모든 최소값의 초기 0 및 Number(value)||0 처리를 유지한다. Pareto 중복 키는 좌표 순서가 고정돼 있으므로 반복된 스탯 이름을 제거하고 같은 숫자 문자열을 사용한다. 비교 횟수·예산·후보 순서·분수 비교는 동일하다.
4. `optimization/problem-compiler.js`: 한국어 `localeCompare`와 같은 설정의 `Intl.Collator`를 재사용한다. 크리스타 해석 때 이미 깊게 freeze한 evaluator 후보를 패키지마다 복제하지 않고 공유한다. 객체와 stats는 불변이며, 직렬화한 입력과 결과는 기존과 동일하다.

표현·실행 비용 변경이며 평가 결과와 탐색 공간을 바꾸지 않으므로 cache/checkpoint v13, split policy v4, 계산 v3를 유지한다. 이전 상한 확장 결과와 이번 변경의 개선율을 중복 합산하지 않는다.

## 검증

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: 307 PASS(공유 모듈의 bin별 중복 포함). 지연 합산과 실제 합산의 좌표 bit 동치, 모든 Utility 탈락 단계의 값·score 동치, 소수 제련/컨버전·음수 CRT·큰 MP 상쇄·잘못된 JSON 타입·checkpoint 복원 검증을 포함한다.
- 기존 oracle, 모든 조상 부분공간 상한 coverage, 1~64 threads, 취소/deadline/오류 work 복원·pause/resume Gate를 유지한다.
- `npm run test:regression`: 76/76 프로세스 PASS. Native 저장 E2E는 CDP 미설정 SKIP이다.
- JS는 기존 준비 알고리즘을 참조 구현으로 대조한다. 소수·EPSILON 경계·음수 0·Infinity/NaN·빈 좌표·중도 Pareto 예산 소진, 희소 최소값·상속/숨은 속성·한국어 패키지 정렬·공유 후보 불변성을 검사한다. 비유한 입력을 제품의 유효 입력으로 승인한 것은 아니다.
- `npm run verify:architecture`, clippy `--all-targets -- -D warnings`, S1 `--require-s1` 427/427: PASS.

## 동일 입력 전후 측정

동일 PC(AMD Ryzen 7 9800X3D 8-Core Processor, Node v24.17.0, Native 16 threads)에서 이전 상한 확대까지 반영된 v13과 이번 변경을 번갈아 측정했다. 입력당 전후 각 10회, 총 100회에서 최적 점수·전체 조합뿐 아니라 컴파일 결과 및 Pareto 처리 후 전체 문제 hash도 일치했다. 이전 문서의 실행 시간과 직접 비교하지 않고 이번 같은 환경의 baseline을 사용한다.

| 입력·모드 | 전체 평균 초: 전→후 | 전체 단축률 | Native 평균 초: 전→후 |
|---|---:|---:|---:|
| 실제 루브닐 · debug | 7.579 → 7.118 | 6.1% | 6.699 → 6.436 |
| 실제 루브닐 · release | 1.417 → 1.212 | 14.4% | 0.572 → 0.566 |
| 실제 평타 · release | 1.339 → 1.135 | 15.2% | 0.501 → 0.500 |
| 과거 전체 해제 fixture · release | 1.670 → 1.381 | 17.3% | 0.663 → 0.642 |
| 과거 에투왈 잠금 fixture · release | 0.852 → 0.651 | 23.6% | 0.089 → 0.089 |

실제 루브닐 점수 **1,753,977.72**, 평타 **67,120**과 전체 크리스타 조합은 같다. 루브닐 debug Native는 평균 3.9% 감소했지만, release 루브닐과 평타·과거 잠금의 Native 차이는 작아서 유의미한 탐색 속도 개선으로 일반화하지 않는다. JS 준비 감소가 전체 시간 단축의 주된 원인이다.

실제 루브닐 release 준비 시간의 평균(ms):

| 구간 | 변경 전 | 변경 후 |
|---|---:|---:|
| scenario·후보 생성 | 177.8 | 143.1 |
| 필요한 스탯 판별 | 196.9 | 36.9 |
| Pareto 준비 | 161.2 | 153.5 |
| 위 세 구간 합계 | 535.9 | 333.4 |

루브닐 전체 P95(nearest rank, 10회이므로 최대값)는 debug 7.884→7.334초, release 1.441→1.252초다. Native peak working set 평균은 debug 약 29.92→29.88 MiB, release 28.31→28.24 MiB로 비슷하다. 과거 잠금은 21.73→21.81 MiB로 소폭 늘어 메모리 절감으로 주장하지 않는다.

250ms slice로 재개한 추가 실행은 4 slice 뒤 같은 exact 점수·조합을 반환했다. 이 표본은 100회 평균에 섞지 않았다. 모든 개별 시간·메모리·카운터·입력·JS/Rust source/binary hash·전체 조합은 [측정 원본](crysta-common-computation-measurements.json)에 있다.

전후 각 프로세스는 해당 버전의 JS 전체 로더와 Rust 바이너리를 사용한다. 변경 전 JS와 Rust 파일·debug/release 바이너리는 Git 제외 `src-tauri/target/common-computation/before/` 및 같은 폴더의 `before-*.exe`에 보존했다. before/after 실행 순서를 매 반복 반전하며 입력당 전후 각 10회, 총 100회다. 실제 딜검방·루브닐/평타·에투왈 단일 잠금은 스킬·버프·콤보·요구조건을 그대로 사용한다. 추가로 과거 전체 해제/잠금 fixture를 회귀 비교에 사용한다.

모든 표본에서 exact score·전체 bestBuild·컴파일된 전체 문제 hash·Pareto 준비 후 전체 문제 hash를 대조한다. 준비 단계는 compile/필요 스탯 판별/Pareto 처리로 분리해 기록한다. 하위 구간 시간은 전체에 이미 포함되며 따로 더해 단축률을 만들지 않는다. Native peak working set은 50ms 간격으로 기록한다.

전체 시간은 scenario/후보 생성부터 최종 JS 재평가까지이고 UI·렌더링은 제외한다. Native elapsedMs는 앱 결과의 경과 시간과 같은 Rust clock이다. JS 준비 개선은 전체 대기에 반영되지만 앱의 Native 경과 표시에는 포함되지 않는다. 실제 듀얼 성능 자료를 새로 만든 것이 아니다.

개발용 앱 빌드·배포 소스 검증: `npm run desktop:prepare`, `npm run verify:entry:dist`, `cargo build --offline --manifest-path src-tauri/Cargo.toml --bin toram-online-auto-build-calculator`. 공식 반복 CLI는 `npm run bench:optimization:build` 후 `npm run bench:optimization -- --input tools/fixtures/crysta-saved-sword-shield-revenir-etowal.json --repeats 10`이다. 공식 CLI progress 기본값은 100ms이며 이번 전후 비교는 32ms 요청→50ms 전달로 통일했다. 전후 snapshot을 사용하는 반복 script와 원시 실행 출력은 Git 제외 `src-tauri/target/common-computation/`에 보관했다.
