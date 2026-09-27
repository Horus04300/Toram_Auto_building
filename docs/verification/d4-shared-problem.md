# D4 세션·작업자 풀의 불변 입력 공유

2026-09-27 구조 개선 4순위의 **롤백된 실험 기록**. 기준은 `d4-native-payload.md`까지 적용된 제품 코드다. 사용자 지시로 입력 공유 변경을 전부 되돌렸으며 1~3순위 개선은 유지한다. 탐색 시간 증가를 확인한 변경은 메모리 절감만으로 채택하지 않는다.

## 실험했던 변경(롤백)

- 세션은 평가 옵션·트리·초기해 준비를 끝낸 NativeProblem을 Arc 하나로 소유한다. NodePool::new는 이 Arc를 받아 작업자에게 참조 소유권만 나누며 전체 문제를 clone하지 않는다.
- 작업자 수 변경으로 풀을 재생성해도 같은 입력·패키지 배열을 사용한다. 작업자 종료와 함께 이전 소유권을 반납한다. 입력에 Mutex나 변경 가능한 공유 상태를 추가하지 않았다.
- 체크포인트는 기존처럼 독립된 NativeProblem 복사본을 소유한다. 복원은 이미 소유한 문제를 새 세션에 이동해 불필요한 추가 clone을 없앴다. 일반 pause/resume은 기존 세션을 유지한다.
- 계산식·후보·상한·동점 순서·Native/checkpoint v8·전체 원본 옵션 반환 계약은 유지한다. 5순위 JS 크리스타 객체 공유와 6순위 캐시 작업은 포함하지 않는다.

## 정확성·수명 검증

새 테스트는 1→8→2→16→1 작업자로 풀을 교체하면서 입력 및 패키지 배열 주소 불변, 참조 수가 정확히 세션+현재 작업자 수인지, 입력 불변, 체크포인트 변경의 격리, 풀/세션 종료 후 소유권 해제를 검사한다. 취소된 작업은 원래 frontier를 유지해 여러 풀 세대에 같은 입력을 사용한다.

기존 취소·deadline·오류 rollback, 1~64 작업자 exact/동점, 버퍼 재사용, 원본 옵션, 체크포인트·서비스 pause/resume 검사를 유지했다. 변경 전후 bridge의 3노드 직렬 체크포인트는 elapsedMs를 제외한 전체 wire JSON이 같다. 전→전, 전→후, 후→전, 후→후 모두 같은 exact 점수·전체 build·상한으로 복원됐다.

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: **55+55+16+68=194개 통과**(공통 모듈 중복 포함).
- `npm run test:r0`: **71/71 프로세스 성공**. 실제 저장 E2E는 `TORAM_E2E_CDP` 미설정 SKIP.
- `npm run verify:r9`, `cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: 통과.
- `D4_EVALUATION_EXPERIMENT=shared-problem`에서 `node tools/check-d4-tree-checkpoint.mjs`: wire 동치·4방향 복원 통과. 기록: `d4-shared-problem-checkpoint.json`.
- `node tools/audit-stack-source-links.mjs --require-s1`: S1 427/427 통과.

## 풀 생성 비용

`node tools/audit-d4-shared-problem.mjs`는 변경 전후 solver를 별도 release crate로 빌드하고 실제 준비 입력 3개를 사용한다. 세션 준비 후 16작업자 풀 생성만 측정한다. 2회 준비·8회 중앙값이며, allocator 계측은 호출 스레드에서 요청한 allocation/reallocation의 횟수·바이트다. 작업자 스레드의 할당, OS 스택, 전체 프로세스 상주 메모리를 의미하지 않는다. Arc 본체 할당은 세션 생성에 한 번 남는다.

| 입력 | 할당 요청 횟수 전→후 | 할당 요청 바이트 전→후 | 풀 생성 중앙값 전→후 |
| --- | --- | --- | --- |
| 루브닐 | 17,065→85 | 4,495,733→4,856B | 1.299→0.191ms |
| 듀얼 | 14,785→85 | 3,835,873→4,856B | 1.203→0.193ms |
| 유틸리티 충돌 | 2,055→85 | 1,302,060→4,856B | 0.475→0.200ms |

원본 및 파생 옵션·문자열·컨텍스트의 중복 복사 비용이 제거됐다. 기록: `d4-shared-problem-pool.json`.

## 전체 탐색 비교와 한계

수정 전 solver·control·source 해시는 `target/shared-problem/before.rs`, `before.exe`, `before-source-hashes.json`에 보존했다. 현재 소스와 일치하는 새 control과 16작업자·입력별 각 2회·전후 교대·새 프로세스로 비교했다. 빌드·테스트와 겹치지 않았다.

```powershell
node tools/profile-d4-slow-inputs.mjs build
$env:D4_EVALUATION_EXPERIMENT='shared-problem'
$env:D4_COMPARE_NATIVE_PAYLOAD='0'
$env:D4_COMPARE_REPEATS='2'
node tools/benchmark-d4-partial-utility.mjs
```

| 입력 | 세션 평균 전→후 | 시간 증가 | peak working set 평균 전→후 |
| --- | --- | --- | --- |
| 루브닐 | 4.464→4.915초 | 10.1% | 89.9→85.4MiB |
| 듀얼 | 7.737→7.937초 | 2.6% | 107.7→103.7MiB |
| 유틸리티 충돌 | 3.229→3.324초 | 2.9% | 80.9→79.4MiB |

12회 모두 exact이며 최적 점수·패키지 ID·전체 원본 옵션·최종 upper가 일치했다. 원본 옵션 합산·JS 재평가·목표 충족·진행 상한의 최적값 포함을 검사했다. CPU/exitCode sampler의 누락 필드는 성공 코드나 0 사용량으로 해석하지 않는다.

루브닐 추가 4회에서는 전 5.543/4.689초, 후 6.237/5.120초로 시간 증가가 다시 관측됐다. 별도 control/profile 비교도 전 4.510/4.680초, 후 4.641/4.877초였다. 계측한 평가 횟수는 유사하고 큐 pop 및 작업자 실행 시간 모두 증가했으며, 증가 원인을 공유 입력 자체·메모리 배치·실행 환경으로 분리하지는 못했다. profile 항목은 중첩되고 작업자 합산 시간이므로 wall time과 직접 합산하지 않는다.

이 변경은 **탐색 시간 증가로 채택 철회·롤백**했다. 메모리 절감만으로 탐색 성능 회귀를 허용하지 않는다는 사용자 기준을 따른다. 최초 12회·추가 4회·진단 profile·해시는 `d4-shared-problem-measurements.json`에 실험 기록으로 보존했다. 이 기록의 after는 현재 제품 코드가 아니다. 진단용 profile 도구 옵션도 되돌렸으며, 풀 할당 감사 도구는 보관한 before.rs/after.rs만 비교하도록 한정했다.

fmt·도구 문법·`npm run ai:audit`·`git diff --check` 통과. 실제 설치본 UI·Native 저장 E2E는 실행하지 않았다.

## 롤백 검증

롤백 직전 solver가 실험 after 해시와 같은지 확인한 뒤, 보존된 before.rs로 복원했다. 복원한 solver의 SHA-256이 4순위 착수 전과 정확히 일치한다. NativeProblem 소유 방식, 풀 생성 clone, 체크포인트 복원 및 해당 테스트까지 4순위 이전 상태다. 1~3순위 소스는 되돌리지 않았다. 동일 가설을 재시도하려면 탐색 시간 회귀를 해소한 새 근거가 필요하다.

롤백 후 `cargo test --offline --manifest-path src-tauri/Cargo.toml` 54+54+16+67=191개, `npm run test:r0` 71/71 프로세스, `npm run verify:r9`, Clippy -D warnings, fmt·ai:audit·diff 검사가 통과했다. 저장 E2E는 CDP 미설정 SKIP이다. 3순위 완료 때 기록한 JS client 및 Rust 소스 전체 해시와 현재 소스가 일치하며, control/profile 바이너리도 복원 소스로 다시 빌드했다. 전체 성능 반복 측정은 동일 소스 복원이므로 다시 실행하지 않았다.
