# Native 반복 평가 병목 개선

2026-10-04. JS 준비 비용을 줄인 직전 완료 코드(v13)를 baseline으로 삼아, 실제 저장 입력에서 더 오래 걸리는 Native 반복 평가를 계측하고 개선했다. 과거 문서의 시간과 새 시간을 나눠 개선율을 계산하지 않았다.

## 병목 확인

제품과 같은 headless service·지속 작업자 pool에서 실제 딜검방 입력, 루브닐, 에투왈 한 슬롯 잠금으로 측정했다. 약 108만 방문 노드, 503만 평가가 반복된다. 작업자별 1/1024 함수 호출을 샘플링하고 평가 내부의 도달한 단계만 나누어 시간을 기록했다. 계측용 소스는 별도 실행 파일로 빌드한 뒤 원복했으며 제품에는 타이머·추가 IPC 명령·샘플링 분기가 남지 않는다.

| 구간 | debug 누적 작업자 경과시간 추정 ms | release 추정 ms |
|---|---:|---:|
| 전체 후보·상한 평가 | 66,549 | 5,579 |
| 상자 스탯 구성·공격 상한 | 12,789 | 2,238 |
| 그 안의 공격 상한 조임 | 10,472 | 1,391 |
| 결합 Utility 가능성 검사 | 432 | 60 |

평가 함수가 가장 큰 반복 계산 비용이었다. release에서 평가 내부의 대미지 단계가 1,703ms, HP/MP가 1,084ms, ASPD가 876ms로 기록됐다. debug에서는 문자열로 고정 필드를 선택하는 비용도 모든 평가 단계에 반복됐다. 첫 변경인 context 직접 조회만 적용한 단발 확인은 Native 3.806초였고, 최종 채택 여부는 아래 반복 측정으로 판단했다.

위 수치는 OS CPU cycle profile이나 실행 wall time이 아니다. 스레드의 경과시간을 누적하므로 실제 대기 시간보다 크고 스케줄링 지연·타이머 오차가 포함된다. 중첩 inclusive 값은 합산하지 않는다. 세부 단계는 그 단계 끝에 도달한 평가만 기록하므로 조기 탈락 비용을 빠뜨릴 수 있으며 전체 평가 대비 점유율을 주장하지 않는다. profiler 실행 시간은 성능 비교 표본에서 제외했다. 큐 전체의 독립 점유율을 측정한 것으로 해석하지 않는다.

## 채택한 변경

1. evaluator의 context 조회는 같은 준비 목록에서 생성한 ContextKey로 직접 필드를 선택한다. 스탯은 StatRegistry 이름에 대응하는 StatKey의 고정 배열 좌표를 읽는다. 매번 같은 문자열을 비교해 필드를 찾는 일을 제거했다. godspeedWieldLevel·motionSpeed도 실제 원본에서 준비하며 가산값이나 기본값을 만들어 넣지 않는다.
2. 마지막 패키지의 지연 합산도 직접 좌표를 사용한다. 오른쪽 옵션이 없는 좌표는 왼쪽 값을 유지하고 기존 합산 순서·음수 0·누락 처리를 보존한다. raw JSON/unknown key는 기존 조회 의미를 유지한다.
3. 고정 skill/passive/active/combo 배율의 십진 분자를 immutable context에서 준비한다. 반복 대미지 계산에는 값의 분자와 checked i128 곱셈·Euclidean floor를 사용한다. 오버플로·표현 불가·비유한 값은 기존 exact 경로로 돌아간다. 후보 스탯으로 변한 스킬 배율은 원래 조립된 계수의 경로를 사용한다. float 근사나 EPSILON을 내림에 넣지 않았다.

무기·스킬·세팅 이름으로 경로를 선택하지 않는다. 모든 Native 입력이 공통 평가 경로를 사용하지만 입력마다 배율과 평가 수가 달라 단축률은 같지 않다. 후보·분기·상한의 강도·내림 위치·계산 결과·동점 계약이 같으므로 Native/checkpoint v13, split policy v4, 계산 v3를 유지한다. 준비 필드와 계수는 역직렬화 때 원본에서 재구성한다.

## 동일 입력 전후 10회 측정

AMD Ryzen 7 9800X3D, Node v24.17.0, Native 16 threads. 입력·모드당 전후 각 10회, 순서를 번갈아 새 Node/Native 프로세스를 실행했다. JS 원본과 준비 알고리즘은 동일하다. 전체는 scenario·후보 생성 시작부터 최종 JS 재평가 결과까지이고 UI 렌더링은 제외한다.

| 입력·모드 | Native 평균 초 전→후 | Native 단축률 | 전체 평균 초 전→후 |
|---|---:|---:|---:|
| 실제 루브닐 · debug | 6.567 → 2.521 | 61.6% | 7.255 → 3.200 |
| 실제 루브닐 · release | 0.548 → 0.408 | 25.6% | 1.186 → 1.044 |
| 실제 평타 · release | 0.508 → 0.414 | 18.5% | 1.148 → 1.056 |
| 과거 전체 해제 fixture · release | 0.648 → 0.534 | 17.6% | 1.396 → 1.284 |
| 과거 잠금 fixture · release | 0.093 → 0.082 | 12.4% | 0.668 → 0.658 |

총 100회 모두 exact, 전체 최적 조합·점수·compiled/prepared problem hash가 같았다. 실제 루브닐 점수는 1,753,977.72, 평타는 67,120이다. 과거 fixture는 당시 불완전 입력의 회귀 검사일 뿐 현재 사용자 세팅을 재현한 자료가 아니다. 실제 듀얼 입력의 성능 근거로 사용하지 않았다.

루브닐 전체 P95(nearest rank, 10회 최대값)는 debug 7.634→3.263초, release 1.230→1.073초다. 과거 짧은 잠금 입력은 전체 P95 0.688→0.688초로 개선이 없으며 전체 평균 감소도 1.6%뿐이다. 탐색이 짧으면 JS·전송 비용의 비중이 크다. 전체 입력의 10초 보장이나 동일 단축률을 주장하지 않는다.

Native peak working set 평균은 루브닐 debug 30.04→29.94 MiB, release 28.12→28.18 MiB다. 관측 주기 50ms이며 메모리 개선으로 주장하지 않는다. 병렬 작업자 스케줄에 따라 방문·평가 수가 조금 변하므로 모든 실행에서 카운터 동일성을 요구하지 않는다.

개별 시간·카운터·메모리·입력·전체 조합·소스/바이너리 hash와 profiler 자료는 [측정 원본](crysta-native-evaluation-measurements.json)에 있다. 최종 lint 정리의 주석·속성 및 사용하지 않는 참조 flag helper의 cfg(test)와 실제 계측 소스는 별도 hash로 구분했다. 로컬 반복 실행 자료는 src-tauri/target/native-bottleneck/에 보관한다.

## 검증

- cargo test --offline --manifest-path src-tauri/Cargo.toml: 317 PASS(76+69+69+21+82, 공유 모듈 중복 포함). typed key의 전체 좌표·기존 sparse 조회·지연 합산 bit 동치, JSON 타입·누락·역직렬화, 고정 배율의 음수/소수/오버플로 fallback와 독립 정수 floor oracle 20,001건을 포함한다.
- npm run test:regression: 76/76 프로세스 PASS. JS/Rust parity, exhaustive oracle, 조상 부분공간 상한 coverage, 실제 후보, 스레드·취소·deadline·재개 Gate를 포함한다. Native 저장 E2E는 TORAM_E2E_CDP 미설정 SKIP이다.
- npm run verify:architecture, cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings, cargo fmt --manifest-path src-tauri/Cargo.toml --check: PASS.
- node tools/verification/audit-stack-source-links.mjs --require-s1: 427/427 PASS.
- npm run bench:optimization:build 이후 실제 fixture를 --repeats 1 --slice-ms 250으로 실행: 3 slice, resume 2회 뒤 같은 exact 점수·전체 조합. 이 표본은 성능 평균에서 제외했다.
- cargo build --offline --manifest-path src-tauri/Cargo.toml --bin toram-online-auto-build-calculator: 개발용 앱 빌드 PASS. 기존 앱을 강제 종료·재시작하지 않았으며 새 앱 UI 표시 시간을 실측한 것은 아니다.
