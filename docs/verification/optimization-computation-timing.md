# D4 UI 독립 연산 시간 측정

## 고정 계약

앞으로 UI와 무관한 전체 연산 비교에는 `npm run bench:optimization`의 **`timing.totalMs`**를 사용한다. 기존 `sessionWallMs`나 5순위 실험의 `frontendMs + nativeProcessMs`와 측정 범위가 다르므로 직접 전후 비교하지 않는다.

입력은 이미 해석된 `baseContext`와 요구조건·잠금·현재 크리스타·금지 목록이다. 타이머는 `performance.now()` 하나를 사용하며 구간 사이에 멈추지 않는다.

```text
타이머 시작
  시나리오 생성 → 크리스타 후보 컴파일
  실제 d4-native-client.js의 optimize
    관련 옵션 도출·후보 준비 → 하드웨어 조회·캐시 키 생성
    전송 객체 축약 → JSON 직렬화·전송·Rust 파싱
    실제 D4OptimizationService → Native 세션 준비·탐색·결과 생성
    결과 직렬화·수신·JS 파싱 → 패키지 복원·최종 JS 재평가
  bounded + continuation이면 같은 서비스의 resume을 자동 연결
    (각 slice의 결과 복원·재평가·캐시 처리를 포함)
최종 결과 객체를 받은 뒤 타이머 종료
```

- `compileMs`: 시나리오 생성과 컴파일. `executionAndResultMs`: 그 이후 최종 결과까지. 두 값의 합은 `totalMs`다.
- Rust가 반환한 `nativeElapsedMs`는 참고값이며 전체 시간에 다시 더하지 않는다.
- 실제 경과 시간이다. 작업자 CPU 시간의 합이나 순수 산술 연산 시간은 아니다. 직렬화·프로세스 시작·통신·대기·GC도 측정 구간에 있으면 포함한다.
- 반복마다 새 Node 프로세스·새 Native 클라이언트·새 Rust 서비스를 사용한다. Native 프로세스는 첫 하드웨어 조회에서 지연 실행하므로 그 시작 비용도 포함한다. OS 파일 캐시까지 초기화했다는 뜻은 아니다.
- 실행 파일 빌드, Node 시작/모듈 로딩, 원시 fixture·크리스타 데이터 로딩은 타이머 앞이다. 종료 후 검증·보고서 직렬화/저장·프로세스 정리는 밖이다. UI 입력 수집·BuildDraft 조립·빠른 추천 화면 계산·렌더링은 측정하지 않는다.
- 앱의 JS Native 클라이언트와 Rust 서비스를 수정 없이 사용하되 **WebView/Tauri 명령 전송 대신 표준입출력 JSON lines**로 연결한다. 앱 버튼 클릭부터 화면 표시까지의 시간이 아니며 WebView의 실제 IPC 비용도 아니다. Worker fallback은 이 Native 기준 측정에 섞지 않는다.

## 재현

```powershell
npm run bench:optimization:build
npm run bench:optimization -- --repeats 3 --output desktop/target/computation-benchmark/revenir.json
```

기본 입력은 추적 중인 `tools/fixtures/crysta-native-runtime-26min-revenir.json`의 `resolvedExecutionContext`다. 다른 입력은 `--input path/to/input.json`으로 전달한다. 동일한 raw 필드 또는 `resolvedExecutionContext` 래퍼를 사용한다. 선택적 `crystas`로 가상 후보를 제공할 수 있다. 이미 준비된 `groups` 입력은 거부한다.

기본 slice는 30초이며 `--slice-ms`로 줄일 수 있다. `--max-ms` 기본값은 120000이며 **현재 slice를 마친 뒤** 재개 여부를 판단하는 soft cap이다. exact가 아니면 보고서를 남기고 실패 종료하며 평균에 넣지 않는다. 서비스 오류도 성공 시간으로 집계하지 않는다. 테스트용 짧은 slice 결과를 기본 30초 성능 표본과 합치지 않는다.

Rust 소스/의존성 및 실행 파일 해시가 빌드 기록과 다르면 재빌드를 요구한다. 보고서는 JS/Rust 소스·입력·실행 파일 해시, Node/CPU, 실제 스레드 수, 캐시 여부, 재개 횟수, 상태, 점수와 선택 조합을 포함한다. 반복 간 exact 조합·점수가 같아야 한다. 결과 raw 옵션과 복원 패키지의 합, 최종 JS feasibility·점수도 검사한다.

평균·중앙값·최솟값·최댓값을 함께 기록한다. 3회 표본으로 P95나 작은 차이의 유의성을 주장하지 않는다. 전후 비교는 동일 입력·slice·환경·측정 스키마로 각각 빌드/보고서를 보존해 수행한다.

## 2026-09-28 최초 기준

루브닐, 기본 30초 slice, 새 프로세스 3회: **10.102 / 9.778 / 9.764초**, 평균 **9.882초**, 중앙값 **9.778초**. 모두 exact이며 최적 점수·전체 선택 조합 일치. 이전 실험 대비 개선율이 아닌 새 측정 범위의 기준이다.

같은 입력의 250ms slice 연결 검사: 20개 slice(최초 실행 + 19회 resume), 15.608초, exact 점수 1,123,905.36. 기본 측정과 점수·전체 조합이 같으며 재개와 중간 결과 처리 비용이 전체 시간에 포함된다. 이 검사는 기본 성능 평균에서 제외한다.

상세 로컬 산출물: `desktop/target/computation-benchmark/revenir-2026-09-28.json` (빌드 산출물과 함께 Git 제외). 측정 구간 회귀: `node tools/tests/optimization/test-crysta-computation-measurement.mjs`는 실제 Native 클라이언트를 가상 transport/clock으로 실행해 비동기 전달·재개·결과 복원·JS 평가·캐시·오류 경계를 검사한다. 실제 Rust 연결 검증과 구분한다.

이번 검증:

- `npm run bench:optimization:build`: release 빌드와 소스/바이너리 해시 기록 성공.
- 위 기본 3회 및 `--repeats 1 --slice-ms 250`: 실제 Rust 서비스 연결, exact·JS 평가·패키지 옵션 합 검증 통과. 두 보고서의 전체 bestBuild도 별도로 비교해 일치 확인.
- `--repeats 1 --max-ms 1 --slice-ms 1`: `no-incumbent-yet` 기록, 평균 null, 종료 코드 1. 미완료를 성능 성공으로 집계하지 않는 계약 확인.
- `npm run test:regression`: 72개 프로세스 성공 종료. Native 저장 E2E 1개는 `TORAM_E2E_CDP` 미설정 SKIP이며 실제 화면 검증 통과로 해석하지 않는다.
- `npm run verify:architecture`, `cargo test --offline --manifest-path desktop/Cargo.toml`, `cargo fmt --manifest-path desktop/Cargo.toml --check`, `cargo clippy --offline --manifest-path desktop/Cargo.toml --bin d4_headless_service -- -D warnings`, `npm run ai:audit`, `git diff --check`: 통과.
