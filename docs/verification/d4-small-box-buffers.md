# D4 작은 박스와 작업자 결과 버퍼

2026-09-27 구조 개선 2순위. 기준은 인덱스 기반 트리·큐 적용 직후이며, 해당 변경은 `d4-indexed-tree.md`에 기록되어 있다.

## 변경과 계약

- 작은 박스의 그룹별 `Vec` 4개를 스택의 후보 인덱스 배열과 slice로 교체했다. 양의 그룹 크기에서 합은 곱+3 이하이므로, 최대 64조합에는 최대 67개 인덱스면 충분하다. 64×1×1×1과 그 순열도 수용한다. 트리의 왼쪽→오른쪽 방문 및 그룹별 옵션 합산 순서를 유지한다.
- 분할과 재귀 lookahead는 작업자 결과 버퍼 하나에 이어 쓴다. 각 입력 노드는 자신의 결과 범위만 기록하므로 노드별·재귀별 자식 `Vec`을 생성하지 않는다. 삭제되지 않은 제약 lookahead는 해당 범위를 되돌리고 기존 박스를 유지한다.
- 작업자가 반환한 자식 버퍼와 결과 목록은 pool이 보관했다가 다음 batch에 소유권을 넘겨 재사용한다. 완료 순서에 상관없이 입력 노드 순서대로 버퍼 범위를 공통 큐에 합친다. 작업자 간 가변 버퍼 공유나 새로운 잠금을 추가하지 않았다. 용량은 필요할 때 증가하고 pool 수명 동안 유지한다.
- 취소·deadline·평가 오류는 현재 노드의 결과 범위만 되돌린다. pool의 panic 포착 뒤에도 같은 rollback을 수행한다. 부분 결과 대신 원래 부모를 재등록하며 batch 오류 시 부모 전체를 복원하는 계약을 유지한다.
- 독립 병렬 실행 경로도 작업자별 자식 버퍼를 재사용한다. 계산식·안전 상한·탐색 우선순위·Native/checkpoint v8 계약은 유지한다.

## 정확성 검증

- 후보 배열이 기존 트리 순서와 일치하며 64개가 어느 그룹에 몰려도 완전 열거 결과·동점·열거 수가 같음을 검사했다.
- 7개 노드의 64개 자식 결과를 3개 batch에 걸쳐 반복 처리해 범위별 자식 순서와 두 버퍼의 주소 재사용을 검사했다.
- 재귀 분할로 자식을 기록한 뒤 7번째 평가에서 취소시켜 현재 결과만 rollback하고 이전 노드의 버퍼 내용은 보존하는지 검사했다.
- 기존 1~64 작업자, 들쭉날쭉한 batch 크기, 취소·deadline·오류, coverage, 추가 분할, exact 동점, 체크포인트 회귀를 유지했다.
- 변경 전후 격리 bridge의 3노드 직렬 진행 체크포인트는 elapsedMs 제외 전체 JSON이 같다. 전→전, 전→후, 후→전, 후→후 4가지 복원이 같은 exact 점수·전체 원본 옵션·상한을 반환했다. `d4-small-box-buffers-checkpoint.json` 참조.

실행한 검증:

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: **54+54+16+67=191개 통과**(공통 모듈 중복 포함).
- `npm run test:r0`: **71/71 프로세스 성공**. 실제 저장 E2E는 `TORAM_E2E_CDP` 미설정 SKIP.
- `npm run verify:r9`: 통과.
- `cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: 통과.
- `node tools/audit-stack-source-links.mjs --require-s1`: S1 427/427 통과.
- `D4_EVALUATION_EXPERIMENT=small-box-buffers`에서 `node tools/check-d4-tree-checkpoint.mjs`: 위 wire 동치와 4가지 복원 통과. 도구는 실험명을 받아 기존 인덱스 트리 기록을 보존하도록 변경했다.

## 성능 비교

수정 전 solver·source 해시·control 바이너리는 `target/small-box-buffers/before.rs`, `before-source-hashes.json`, `before.exe`로 보존했다. 동일한 sparse progress 계측을 넣은 변경 후 control과 비교했다.

```powershell
node tools/profile-d4-slow-inputs.mjs build
$env:D4_EVALUATION_EXPERIMENT='small-box-buffers'
$env:D4_COMPARE_REPEATS='2'
node tools/benchmark-d4-partial-utility.mjs
```

준비된 동일 입력 3개·16작업자·새 프로세스·전후 순서 교대 각 2회다. 회귀 테스트·빌드와 겹치지 않는다. 시간은 Native 준비 및 세션 실행을 포함하며 JS 후보 준비와 UI/IPC는 제외한다. 2회 반복은 P95 또는 모든 입력의 속도 보장이 아니다.

| 입력 | 변경 전 2회 | 변경 후 2회 | 평균 시간 전→후 | 평균 감소 | 평균 peak working set 전→후 |
| --- | --- | --- | --- | --- | --- |
| 루브닐 | 4.724 / 4.840초 | 4.708 / 4.592초 | 4.782→4.650초 | 2.8% | 90.5→102.2MiB |
| 듀얼 | 7.908 / 8.312초 | 7.697 / 7.701초 | 8.110→7.699초 | 5.1% | 107.6→107.3MiB |
| 유틸리티 충돌 | 3.423 / 3.469초 | 3.271 / 3.399초 | 3.446→3.335초 | 3.2% | 86.2→80.3MiB |

12회 모두 exact이고 입력별 점수·선택 패키지·전체 반환 옵션·최종 upper가 일치했다. 반환 옵션은 원본 패키지 합산 및 JS 재평가와 대조했고 목표 충족과 최적 점수를 확인했다. 변경 후 진행 snapshot의 모든 upper도 최적값을 포함했다. 듀얼은 4회 모두 50,924,398조합을 열거했다. 다른 입력의 방문·평가 수는 병렬 실행 시점과 작업자별 제약 제거율에 따라 조금 달라진다.

반복 할당 감소와 평균 실행 시간 개선을 근거로 채택했다. 전체 메모리 감소는 주장하지 않는다. 특히 루브닐 peak working set은 평균 11.7MiB 늘었다. 재사용 버퍼의 용량 유지와 allocator·frontier 상태를 포함한 관측값이며 원인별 기여율은 따로 분리하지 않았다. CPU/exitCode sampler 필드의 누락은 0 사용량이나 프로세스 성공 코드로 해석하지 않고 bridge의 JSON 결과 및 정확성 assertion으로 실행 완료를 검증했다.

전후 바이너리·입력·소스 해시, 환경, 12회 결과는 `d4-small-box-buffers-measurements.json`에 저장했다. 최종 제품 소스 해시와 측정한 변경 후 해시가 일치한다. 설치본 UI와 실제 Native 저장 E2E는 실행하지 않았다.
