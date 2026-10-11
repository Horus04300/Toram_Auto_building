# 결합 제약·공격 상한의 공통 적용 확대

2026-10-03. Native v13은 기존 v12에서 제외했던 AMPR 보정 프로필, 소수·큰 옵션, 넓은 CRIT% 범위, 요구조건 일부 해제, 음수 기본 스탯을 지원한다. 무기·스킬 이름이나 특정 저장 빌드를 검사해 활성화하지 않는다. 개발/release 앱과 headless 서비스는 같은 `src-tauri/src/optimization/solver.rs`를 사용한다. Worker fallback에 새 Native 상한을 이식한 변경은 아니다.

실제 저장 딜검방·램페이지 보정·루브닐 콤보·에투왈 단일 잠금을 그대로 유지했다. 입력을 쉽게 만들기 위한 가산이나 보정 삭제는 없다. 실제 듀얼 성능을 주장하지 않으며, 듀얼은 소형 oracle/property 검증에 포함한다. 실제 듀얼 성능 판정에는 사용자가 제공한 입력이 필요하다.

## 적용 범위와 안전성

- AMPR 변환은 기존 `utility_values`를 호출한다. passive 순차 적용과 active 후보 최댓값, 단계별 내림, MP 상한을 그대로 따른다. percent ≥ -100, multiplier ≥ 0이면 입력 AMPR에 단조 증가한다. 음수·소수 flat도 허용한다. 램페이지 flat 25는 스킬에서 조립된 원래 효과다.
- 단조성을 증명할 수 없는 AMPR 변환에는 AMPR 지지값의 가중치만 0으로 둔다. CRIT 제약은 계속 활용하고 실제 요구조건은 완성 후보에서 모두 검사한다. AMPR/CRIT 중 하나를 해제한 경우에도 나머지 제약을 사용한다.
- 각 옵션 x를 `ceil(x/u)`로 외향 완화한다. 보통 정수 u=1, 소수 u=1/1024이며 크면 2의 거듭제곱 단위로 확대한다. 입력 옵션과 후보는 수정하지 않는다. 좌표 절댓값을 100만 이하로 표현해 지지값 가중합은 f64가 정확하게 표현하는 정수가 된다.
- evaluator에서 요구조건을 만족시키는 첫 정수 probe r을 이분 탐색한다. 가능한 실제 총합 x는 x/u > r-1이므로 각 패키지의 올림 좌표 합도 r 이상이다. 따라서 지지값 비교와 공격 좌표 상한이 feasible 완성 조합을 누락하지 않는다.
- 각 부분공간의 최대 `k*D+a*AMPR+c*CRIT`와 최소 요구량 A,C를 이용해 `D ≤ floor((support-a*A-c*C)/k)*u`로 공격 옵션을 제한한다. ATK%/MATK%, 근거리/원거리 대미지, CDMG의 기존 45개 지지 방향을 모두 유지한다. 노드 배열을 한 번 읽어 합산하고 정수 좌표는 불필요한 올림을 생략한다.
- CRIT% 범위가 넓으면 최대 2049개 bucket의 유리한 끝값을 사용한다. 일반 정수 범위는 기존 정확한 표를 유지한다. 기본 CRT로 CRIT%의 증가 방향이 반전되면 최소 끝값을 사용하고, 기본 INT가 음수이면 MP 계산에 유리한 최소 INT%를 사용한다.
- 유한 좌표를 표현할 수 없는 경우 기존 상한을 보존한다. 두 요구조건이 모두 해제되거나 전 범위에서 이미 충족돼 제약으로 상한을 강화할 수 없으면 추가 계산을 생략한다. 지원 확대는 모든 입력에서 같은 개선율을 보장한다는 뜻이 아니다.

Native cache/checkpoint는 v13이다. v12 이하의 현재·과거 이름 checkpoint는 거부한다. 저장 schema, 계산식, raw 옵션, 후보, 잠금, 동점 ID, split policy v4는 유지한다.

## 정확성 검증

14개 형태의 작은 입력에서 모든 feasible 완성 조합과 그 조합을 포함하는 모든 조상 부분공간을 검사했다. 물리/마법/거리/발도/듀얼, 램페이지, 소수 passive·active, 음수 flat·percent, 단조성 없는 profile, 소수 옵션, 큰 값·넓은 CRIT%, 한쪽 요구조건 해제, 음수 기본 INT/CRT를 포함한다. 결합 제약의 통과, 공격 좌표 및 대미지 상한 coverage를 확인했다.

램페이지와 소수 passive·active 입력은 exhaustive oracle의 exact 점수·동점 ID와 비교했고, 역순 후보와 1/4/64 threads의 checkpoint 재개에서도 같은 결과를 확인했다. 최종 성능 표본은 각각 fresh Node/Native이며 exact, 전체 bestBuild, raw 옵션 합, 최종 JS 요구조건·점수 일치를 검사한다.

실행 결과:

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: 297 PASS(공유 모듈의 bin별 중복 포함).
- `cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: PASS.
- `npm run test:regression`: 76/76 프로세스 PASS. Native 저장 E2E는 CDP 미설정 SKIP이며 실제 앱 E2E 통과로 주장하지 않는다.
- `npm run verify:architecture`: PASS. JS/Rust parity, oracle와 기존 실행·잠금·재개 회귀를 유지했다.
- `node tools/verification/audit-stack-source-links.mjs --require-s1`: S1 427/427 PASS.
- `npm run desktop:prepare`, `npm run verify:entry:dist`: PASS(76 classic scripts).
- `cargo build --offline --manifest-path src-tauri/Cargo.toml --bin toram-online-auto-build-calculator`: 개발용 앱 빌드 PASS.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `npm run ai:audit`, `git diff --check`: PASS.

## 같은 입력의 전후 측정

동일 PC(Node 24.17.0, AMD Ryzen 7 9800X3D 8-Core Processor, Native 16 threads)에서 v12/v13을 번갈아 실행했다. 입력·모드마다 전후 각 10회, 총 100회다. 컴파일·다른 테스트는 측정 전에 마쳤다. progress는 UI처럼 32ms 요청→50ms 전달, 30초 slice, 캐시 없음이다. 모든 표본의 exact 점수·전체 조합이 일치했다.

| 입력·모드 | Native 평균 초: 전→후 | 전체 평균 초: 전→후 | 전체 단축률 |
|---|---:|---:|---:|
| 실제 루브닐 · debug | 10.608 → 6.559 | 11.487 → 7.439 | 35.2% |
| 실제 루브닐 · release | 0.973 → 0.593 | 1.832 → 1.463 | 20.2% |
| 실제 평타 · release | 0.797 → 0.505 | 1.637 → 1.348 | 17.6% |
| 과거 전체 해제 fixture · release | 0.630 → 0.649 | 1.652 → 1.689 | -2.2% |
| 과거 에투왈 잠금 fixture · release | 0.089 → 0.089 | 0.856 → 0.853 | 0.3% |

실제 루브닐 debug Native 단축률은 38.2%, release는 39.1%다. 점수는 **1,753,977.72**, 평타는 **67,120**이다. 무기 굉룡 보비나리+도이, 방어구 푸이에트+호뢰파섬, 추가 고블린 주코토+카나요간, 특수 에투왈+죠코의 루브닐 조합을 유지했다. release 루브닐 평가 횟수는 11,161,060→5,028,027, 방문 노드는 2,196,947→1,083,564다.

전체 P95(nearest rank, 10회이므로 최대값)는 실제 루브닐 debug 11.745→7.751초, release 1.974→1.557초다. Native peak working set의 평균은 debug 약 32.9→30.0 MiB, release 31.5→28.1 MiB다(50ms 간격 표본). 과거 전체 해제 fixture는 이미 v12 상한이 동작하던 입력으로 탐색량이 거의 같으며, 확장 후 전체 평균이 36.4ms(2.2%) 증가했다. 이 입력을 개선된 것으로 보고하지 않는다. 과거 잠금 입력도 유의미한 개선으로 판정하지 않는다.

실제 입력을 공식 benchmark로 250ms씩 나누어 재개한 추가 실행은 4 slice 뒤 같은 exact 조합을 반환했다. 이 실행은 100회 성능 평균에 섞지 않았다. 전체 시간·Native 시간·메모리·카운터·입력·source/binary hash와 전체 조합은 [측정 원본](crysta-general-upper-bound-measurements.json)에 보관한다. 과거 fixture는 회귀 비교용이며 현재 사용자 입력의 성능 증거로 대체하지 않는다.

UI에 표시되는 경과는 Native `elapsedMs`이며, 전체 시간은 JS 입력 컴파일부터 Native 실행·결과 복원·최종 JS 평가까지다. 버튼·렌더링 시간은 포함하지 않는다. 실행 중인 개발 앱을 다시 시작하거나 새 앱의 실제 화면 시간을 측정하지 않았다. 새 코드를 앱에서 사용하려면 `npm run desktop:dev`로 Native를 다시 빌드해 실행해야 한다.

재현은 `npm run bench:optimization:build` 후 `npm run bench:optimization -- --input tools/fixtures/crysta-saved-sword-shield-revenir-etowal.json --repeats 10`으로 가능하다. 공식 CLI 기본 progress 요청은 100ms이며 이번 제품 대응 비교는 UI처럼 32ms 요청→50ms 전달로 통일했다. 개발 비교는 `cargo build --offline --manifest-path src-tauri/Cargo.toml --bin crysta_headless_service`를 사용한다. 전후 원본·바이너리와 반복 script는 Git 제외 `src-tauri/target/general-upper-bound/`에 보관했다.
