# D4 세션 실행·합산·선택적 추가 분할 개선

- 날짜: 2026-09-16.
- 이전 기준: `d4-invariant-evaluation.md`까지 반영된 코드. 이전 작업 변경은 보존했다.
- 측정 원본: `d4-session-optimization-measurements.json`.

## 적용 순서와 계약

1. **앱과 같은 세션 실행 경로 측정**: 개발용 parallel bridge에 `D4_SESSION_BENCH_MS` 모드를 추가했다. `NativeSearchSession::new`와 앱의 `run_parallel_slice_with_control`을 같은 묶음 크기로 실행한다. 준비 시간·세션 wall·묶음 수를 기록한다. Tauri IPC/Channel/UI 자체는 실행하지 않으므로 실제 화면 E2E와 구분한다. 기존 P6 전용 병렬 경로도 유지한다.
2. **요구조건 사전 준비**: HP/MP/AMPR/평타 CRIT/ASPD를 `Option<f64>`로 한 번 읽는다. 누락/null/잘못된 타입의 기존 의미와 조건 경계 비교를 보존한다.
3. **합산 배열화**: `NativeStats`는 36개 알려진 좌표의 숫자 배열·존재 비트와 알 수 없는 좌표의 별도 map을 사용한다. 패키지/envelope/합산/평가까지 같은 표현을 써 매 평가의 문자열 검색·map 생성·DenseStats 변환을 없앴다. 0과 누락을 구별하고, 원래 그룹 순서로 존재하는 좌표만 합산한다. 기존 JSON map 직렬화와 사전식 순회 순서를 유지한다. 미등록 스탯을 삭제하지 않는다.
4. **재사용 스레드 풀**: 세션당 풀을 지연 생성하고 다음 묶음/재개에 재사용한다. 스레드 수 변경 시 재생성하고 세션 폐기 시 종료/join한다. 입력은 풀에 한 번 복사한 불변 Arc이며, 취소는 동일한 `Arc<AtomicBool>`을 공유한다. deadline 확인 위치는 보존한다. 결과는 입력 순서로 병합하며 오류/누락 결과는 부모 frontier를 보존하고 실패로 처리한다. checkpoint는 스레드를 저장하지 않고 복원 후 새 풀을 만든다.
5. **묶음 크기 조정**: 스레드당 1→32노드로 변경했다. 풀을 재사용해도 아주 작은 묶음마다 채널·결과·incumbent를 준비하는 비용이 컸다. deadline/cancel은 노드 내부에서도 확인하고, 중단된 부모를 재큐잉한다. service와 측정 bridge는 동일 상수를 참조한다.
6. **선택적 추가 분할**: 현재 최적값이 있고 child upper가 그 값의 절댓값 기준 2% 이내이며 조합 수가 64 초과이면, 한 단계 더 분할해 검사한 뒤 생존한 손자 상자를 큐에 넣는다. 추가 깊이는 한 단계로 제한한다. 2%는 연산을 투자할 구간을 고르는 기준일 뿐 후보 삭제 근거가 아니다. 삭제에는 기존 안전 envelope 상한·요구조건만 사용한다. 생존 공간은 모두 유지하고, 중간 취소 시 원래 부모를 보존한다. 동점 ID와 strict bound 비교를 유지한다.

실행/분할 정책 변경에 따라 Native engine은 v3, split policy는 `candidate-tree-2axis-smallbox64-lookahead.v2`, checkpoint는 v3로 올렸다. 계산 버전은 v2 유지. v2 checkpoint는 거부한다. 유틸리티 하위호환 감사는 여전히 기본 비활성이다.

## 측정 환경과 결과

Windows / Ryzen 7 9800X3D / Node v24.17.0 / rustc 1.98.0. P6 물리 근거리 전체 후보 992/844/724/929, 유틸리티 감사 비활성. 새 Native 프로세스로 측정하고 측정 중 빌드·테스트를 실행하지 않았다.

재현: release parallel bridge 빌드 후 `D4_SESSION_BENCH_MS=30000`, `D4_P6_THREAD=8`, `D4_P6_REPORT=<json>`를 설정하고 `node tools/benchmark-d4-native-p6.mjs` 실행. 전용 병렬 경로는 `D4_SESSION_BENCH_MS`를 해제한다. 전/후 binary는 `D4_NATIVE_BINARY`로 선택했다.

### 단계별 확인

| 단계 | 경로 | 시간 | 결과 |
| --- | --- | ---: | --- |
| 변경 전 | 앱 세션, 8스레드 | 30.000초 제한 | bounded, 점수 14,089 / upper 15,974, 689,685노드, 86,213묶음 |
| 요구조건 준비 | 전용 병렬, 8스레드 | solver 9.690초 | exact 14,097 |
| 합산 배열화 | 전용 병렬, 8스레드 | solver 7.734초 | exact 14,097 |
| 풀 재사용, 기존 묶음 크기 | 앱 세션, 8스레드 | wall 25.739초 | exact, 556,647묶음 |
| 풀 + 32노드 묶음 | 앱 세션, 8스레드 | wall 7.281초 | exact, 17,399묶음 |

위 단계별 값은 각각 단일 측정이며 경로도 구분했다. 단계 간 수치를 동일 환경의 반복 A/B 단축률로 주장하지 않는다. 변경 전 앱 세션의 exact 완료 시간은 측정하지 않았으므로 전체 단축률을 계산하지 않는다.

### 선택적 추가 분할 반복 비교

| 순서 | 추가 분할 전 세션 wall | 추가 분할 후 세션 wall | 전 외부 wall | 후 외부 wall |
| --- | ---: | ---: | ---: | ---: |
| 전→후 | 7,398.503ms | 6,347.943ms | 7,607.671ms | 6,525.793ms |
| 후→전 | 7,260.900ms | 6,369.416ms | 7,442.786ms | 6,551.758ms |

두 번씩 평균 세션 wall은 7.330→6.359초, 약 13.2% 단축. 평가 수는 25,872,175→25,932,301회로 약 0.23% 늘었으나 묶음 수는 17,399→13,769로 줄었다. 전체 평가 수 감소를 주장하지 않는다. peak working set은 전 91,611,136~92,684,288 / 후 76,271,616~76,357,632 bytes였다.

최종 코드 추가 확인: 8스레드 세션 wall **6.225초**(외부 6.444초), 16스레드 **4.693초**(외부 4.874초). 두 결과 모두 exact 14,097. 준비 시간은 약 51ms였다. 모두 동일 ID `weapon:도이+후빗||armor:알타달+칼레리프||additional:카나요간+칼레리프||special:저편의 잔영+칼레리프`였다. 병렬 timing에 따른 방문·평가 수의 소수 차이는 원본에 남겼다.

세션 wall은 Native 준비와 묶음 간 호출 비용을 포함하지만 JS compile/Pareto와 UI/IPC는 제외한다. solverMs는 기존 누적 실행 시간 계약대로 묶음 사이 시간을 제외한다. PowerShell CPU/exitCode가 일부 0/null로 나오는 기존 한계가 있어 해당 값으로 성공이나 속도를 판정하지 않는다.

## 추가 실험: 작은 상자 후보 목록 재사용

사용자의 계속 개선 요청에 따라 64조합 이하 상자의 후보 인덱스를 한 번 수집해 고정 배열에 재사용하는 실험을 했다. 첫 단발은 5.972초였으나 순서 반전 비교는 전 6.136 / 후 6.026초, 후 6.322 / 전 6.127초로 일관된 이득이 없었다. **해당 구현과 전용 테스트는 원복**했다. 최종 코드는 기존 완전열거 방식이다.

## 검증

- `cargo test --manifest-path src-tauri/Cargo.toml -q`: PASS, 115개(31+31+9+44, 공유 모듈의 binary별 실행 포함).
- 추가 검사: 요구조건 타입/경계; 1,000개 결정적 sparse 입력의 네 그룹 합산·부호 있는 0·미등록 스탯·직렬화 동치; 작업자 thread ID 재사용; checkpoint에서 풀 재생성; worker 오류 시 부모 공간 보존; 선택적 분할의 4,096조합 비중복 coverage·동점 상한.
- 기존 1~64스레드 동치, 순서 반전, cancel/deadline/pause/resume/checkpoint 회귀 유지.
- `node tools/test-d4-native-exact-p4.mjs`: PASS, exhaustive oracle 동치.
- `node tools/test-d4-rust-native-parity.mjs`: PASS, 1,488개에서 JS·Value·기존 map·새 NativeStats 경로 동치.
- `npm run verify:r9`: PASS(하위 Gate 포함).
- `npm run test:r0`: PASS, 70개 스크립트 집계. Native 저장 E2E는 `TORAM_E2E_CDP` 미설정으로 SKIP이며 실제 E2E 통과로 세지 않는다.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, S1 427/427.
- fmt / clippy `--all-targets -- -D warnings` / release exact·parallel 빌드: PASS.
- 세션 bridge에서 100ms 취소 측정: `cancelled`, solver 100ms, 외부 wall 282ms. 취소는 exact나 인증 upper로 표시하지 않는다.

설치본 배포, WebView/IPC E2E, 전체 필수 fixture의 cold 10회 P95는 미실행이다. 특정 P6 입력이 10초 미만이라는 결과를 모든 입력의 10초 exact 달성으로 일반화하지 않는다.
