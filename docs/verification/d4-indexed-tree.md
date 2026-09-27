# 인덱스 기반 CandidateTree와 대기 큐

2026-09-27. `d4-structure-audit.md`의 1순위 작업을 구현했다. 이번 범위는 트리 소유권과 대기 작업 표현이며, 2~6순위의 버퍼/전송/입력 공유/캐시 작업을 함께 적용하지 않았다.

## 구현

- 네 장비 트리의 노드를 하나의 `TreeArena.nodes` 연속 배열에 저장한다. `Arc<TreeNode>`를 제거하고 자식 연결은 `NodeId(u32)`로 표현한다. 준비된 불변 arena 하나를 세션과 작업자가 공유한다.
- `WorkItem`은 안전 상한 `f64`와 네 노드 인덱스만 보유한다. 크기는 **40→24바이트**이며, 자식 생성·대기 항목 이동·폐기에서 트리 노드마다 참조 카운트를 갱신하지 않는다.
- 노드를 기존 트리와 동일한 preorder 순서로 배치한다. 장비별 오프셋은 해당 비교 차원에서 일정하므로 숫자 인덱스 비교가 기존 `r`, `r0`, `r00`, … 문자열 경로 순서와 같다. 큐 비교는 트리 역참조 없이 상한·인덱스만 읽는다.
- 좌표 envelope, 분할 차원·후보 정렬, heuristic, lookahead, 작은 박스 열거, 동점 build ID와 원본 옵션 반환은 그대로 유지한다. 후보 삭제나 새 상한을 도입하지 않았다.
- 준비 시 노드 수를 checked 연산으로 계산하고 `u32` 범위를 확인한다. 배열 확보 실패는 오류로 반환한다. 노드 인덱스를 잘라서 저장하지 않는다.
- 직렬·공유 세션·standalone 병렬 탐색이 같은 트리 준비 함수를 사용한다. arena는 JSON/체크포인트에 포함하지 않고 복원 시 다시 만든다.
- 체크포인트의 문자열 경로와 Native/checkpoint v8 계약을 유지한다. 경로 복원은 재생성한 트리의 자식 인덱스를 따라가며, 잘못된 문자나 존재하지 않는 경로를 거부한다. 숫자 인덱스를 외부 영속 데이터로 저장하지 않는다.

## 정확성·호환성

- 기존 51개 Native 병렬 모듈 테스트를 새 표현에 연결하고 모두 통과했다. 작은 박스 coverage, 추가 분할 삭제 안전성, 사전 취소·deadline·오류의 부모 재등록, 1~64 작업자 exact/동점, checkpoint/resume 검사가 포함된다.
- 추가 검사: WorkItem 24바이트, 용량 계산 overflow, 4개 트리의 preorder/자식 연결/크기/경로 복원, 잘못된 경로 거부, arena 공유와 JSON 제외. 기존 숫자·문자열 정렬 동치 검사도 유지한다.
- 풀 단위 테스트는 준비된 세션의 트리와 문제를 함께 전달하도록 수정했다. 초기 연결 중 원본 문제의 빈 arena를 전달한 테스트 실패를 수정했으며, 작업 공간 보존 assertion은 약화하지 않았다.
- 변경 전 소스와 변경 후 소스를 격리 bridge로 빌드했다. 동일 입력을 직렬 3노드만 진행한 중간 체크포인트는 elapsedMs를 제외한 전체 JSON이 일치한다. 전→전, 전→후, 후→전, 후→후의 4가지 복원이 모두 같은 exact 점수·조합·전체 원본 옵션을 반환한다. 기록: `d4-indexed-tree-checkpoint.json`.

검증 명령:

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: **52+52+16+65=185개 통과**(공통 모듈의 바이너리별 중복 포함).
- `npm run test:r0`: **71/71 프로세스 성공**. 실제 저장 E2E는 `TORAM_E2E_CDP` 미설정 SKIP이며 통과로 세지 않는다.
- `npm run verify:r9`, `cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: 통과.
- `node tools/check-d4-tree-checkpoint.mjs`: 중간 wire 상태 동치와 네 방향 복원 통과.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `node tools/audit-stack-source-links.mjs --require-s1`: 통과(S1 427/427).

## 성능 비교 방법

수정 전 solver/source 해시/control 바이너리는 `target/indexed-tree/before.rs`, `before-source-hashes.json`, `before.exe`에 보존했다. 수정 후 `profile-d4-slow-inputs.mjs build`가 생성한 control 바이너리와 비교한다. profile 도구는 arena를 받는 box_stats 함수의 새 시그니처에 맞춰 연결했다.

```powershell
node tools/profile-d4-slow-inputs.mjs build
$env:D4_EVALUATION_EXPERIMENT='indexed-tree'
$env:D4_COMPARE_REPEATS='2'
node tools/benchmark-d4-partial-utility.mjs
```

동일 준비 입력 3개, 16작업자, 새 프로세스로 전→후/후→전 각 2회, 총 12회를 실행한다. 빌드·회귀 테스트와 겹치지 않는다. Native 준비와 세션 시간을 포함하고 JS 후보 준비·UI/IPC는 제외한다. 점수·선택 패키지·전체 반환 옵션 동치, 원본 합산 및 JS 최종 재평가, 진행 상한의 최적값 포함을 검사한다. 2회 반복은 P95/전 입력 속도 보장이 아니다.

## 결과와 채택

| 입력 | 변경 전 2회 | 변경 후 2회 | 평균 시간 감소 | 평균 peak working set 전→후 |
| --- | --- | --- | --- | --- |
| 루브닐 | 5.524 / 5.564초 | 4.927 / 4.763초 | **12.6%** (5.544→4.845초) | 135.8→91.6MiB |
| 듀얼 | 9.067 / 9.238초 | 8.276 / 8.262초 | **9.7%** (9.153→8.269초) | 166.3→108.4MiB |
| 유틸리티 충돌 | 4.010 / 3.953초 | 3.494 / 3.517초 | **12.0%** (3.981→3.505초) | 127.8→81.9MiB |

메모리 관측 감소는 약 44.2 / 58.0 / 45.9MiB다. 배열의 여유 용량·다른 데이터도 포함하는 프로세스 working set 측정이므로 항목 크기 40% 감소와 전체 메모리 감소율을 동일시하지 않는다.

12회 모두 exact이며 입력별 최적 점수·ID·전체 반환 옵션·최종 upper가 일치했다. 반환 옵션을 원본 패키지 합산과 대조하고 JS로 재평가해 점수 및 목표 충족을 확인했다. 수정 후 진행 snapshot의 모든 상한도 최적값을 포함했다. 듀얼의 열거 조합 수는 전후 모두 50,924,398이다. Native 준비 시간은 루브닐 약 43ms, 듀얼 51~56ms, 충돌 8.3~8.5ms였다.

현재 제품 경로에 인덱스 기반 트리·큐를 채택한다. 전후 바이너리/입력/소스 해시와 12회 기록은 `d4-indexed-tree-measurements.json`에 보존했다. 측정 소스가 최종 제품 소스와 일치하는 검사도 통과했다. 이전 날짜·다른 작업의 실행 시간과 직접 개선율을 계산하지 않았다.

도구 문법 검사, `npm run ai:audit`, `git diff --check` 통과. 설치본 UI 및 실제 Native 저장 E2E는 실행하지 않았다. 다음 순위는 작은 박스 후보·작업자 결과의 반복 할당 감소이며 이번 변경에는 포함하지 않았다.
