# D4 공통 페널티 상한 및 분기 점수 캐시

- 작업일: 2026-09-14. 공개 릴리스 변경 없음.
- 범위: Rust Native와 JavaScript Worker의 CandidateTree 상한 처리. 초기해·후보 삭제·계산식·장비 제약은 변경하지 않았다.

## 변경과 증명 범위

기존 envelope는 좌표별 최대값을 0에서 시작했다. 예를 들어 ATKP가 -12, -3인 두 패키지만 남은 노드에서도 상한 입력은 0이었다. 이제 실제 최대값 -3을 사용한다. 해당 좌표가 없는 패키지는 기존대로 0을 공급하며, 빈 후보군에 -Infinity를 내보내지 않는다.

각 완성 조합은 각 그룹에서 정확히 한 패키지를 선택하므로 실제 기여량은 해당 노드의 좌표별 최대값 이하이다. 기존 평가기의 단조 envelope 계약 아래에서 상한 안전성을 유지하며, 음수 공통 페널티가 있는 부분공간의 과대평가를 줄인다. 이는 좌표 간 상관관계를 완전히 표현하는 상한은 아니다. 평가기의 단조성 자체를 새롭게 일반 증명한 것도 아니다.

상한 변경을 분기용 heuristic에 그대로 전달한 첫 실험은 실제 후보 24개씩의 표본에서 평가 수가 7,065→7,487로 늘었다. 따라서 분기 우선순위는 기존 양수 envelope 기준을 유지한다. 트리를 만들 때 그 점수를 한 번 계산해 저장하고, 검색 중에는 부모·자식 점수의 차이만 읽는다. Rust 노드마다 여러 BTreeMap 조회를 반복하던 비용을 없앴다. JS의 일반 탐색·shard·상한 감사도 같은 점수를 사용한다. 점수 캐시는 가지치기 증거로 사용하지 않는다.

Native client engine은 `d4-native-solver.v2`, 직렬화 checkpoint는 `toram.d4-native-search-checkpoint.v2`로 바꿨다. v1 checkpoint 복원은 거부한다. 사용자 BuildDraft 저장 schema는 바뀌지 않는다.

## 검증

- `node tools/test-d4-global-optimizer-stage2.mjs`: PASS. 기존 oracle·상한 1,093개 외에 공통 음수/동점/역순 입력, 물리·마법·발도·듀얼의 exhaustive·부분공간 상한·단조성 검사 추가.
- `cargo test --manifest-path src-tauri/Cargo.toml`: PASS, 85개(여러 binary에 공유 모듈 테스트가 포함됨). 공통 페널티·누락 좌표·singleton·빈 집합 및 이전 checkpoint 거부 추가. 기존 1~64스레드·재개·취소·frontier 보존 테스트 유지.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo clippy --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: PASS.
- `node tools/test-d4-rust-native-parity.mjs`: PASS, 1,488개 평가 동치.
- `node tools/test-d4-evaluator-stage1.mjs`, `node tools/test-d4-utility-dependencies.mjs`, `node tools/test-d4-pair-frontier.mjs`, `node tools/test-d4-native-client.mjs`: PASS.
- `node tools/audit-stack-source-links.mjs --require-s1`: PASS, S1 427/427. 계산 규칙이나 전투 시뮬레이션 완성을 의미하지 않는다.
- `node tools/test-d4-native-exact-p4.mjs`: PASS. 물리·마법·발도·듀얼 공통 음수 패키지의 JS exhaustive와 Native 1/8/64스레드 점수·ID 동치 추가.
- `node tools/test-d4-worker-stage3.mjs`, `node tools/test-d4-parallel-shards.mjs`, `node tools/test-d4-parallel-worker-runtime.mjs`, `node tools/test-d4-native-resume-ui-n5.mjs`: PASS.
- `node tools/test-d4-full-stage3.mjs`: PASS, 5초 예산의 bounded 회귀. 최종 실행 lower 14,089 / upper 20,367이며 exact 통과로 해석하지 않는다.
- `npm run ai:audit`, `git diff --check`: PASS. 기존 handoff의 12 KiB 초과는 중복 과거 기록을 주제 링크로 축약해 해소했다.

## 측정 방법과 한계

환경: Windows, AMD Ryzen 7 9800X3D(논리 16개), Node v24.17.0, rustc 1.98.0. 현재 crysta-data와 기존 P6 물리 근거리 fixture 사용. Pareto 후 패키지 수는 무기 992/방어구 844/추가 724/특수 929.

기준 소스 HEAD `24534ac`, crysta-data Git blob `7ab81aeb06e421b7fb150a518b35f16ff9a50e95`.

변경 전 release binary를 보존하고 동일 입력·8스레드로 전/후를 번갈아 각 3회 새 프로세스에서 실행했다. `D4_P6_THREAD=8`, `D4_NATIVE_BINARY=<비교 binary>`, `D4_P6_REPORT=<결과 경로>`로 `node tools/benchmark-d4-native-p6.mjs`를 실행한다. 준비된 후보를 Native에 전달하며 solver 시간에는 JS compile/Pareto 시간이 포함되지 않는다. 외부 wall은 Native 프로세스 실행 비용을 포함한다.

첫 baseline 측정 일부에 Rust 검증이 겹쳤으므로 나머지 반복의 방향도 함께 확인한다. 전체 후보의 1스레드 초기 비교는 동시 실행/중단이 섞여 성능 근거에서 제외했다. PowerShell 측정의 종료 CPU 시간이 일부 0/null로 반환되어 CPU/exitCode 필드는 성능 근거로 사용하지 않는다. solver JSON의 exact·점수·ID와 완료 shard 수를 검증한다.

| 반복 | 기존 solver ms | 변경 solver ms | 기존 wall ms | 변경 wall ms |
| --- | ---: | ---: | ---: | ---: |
| 1 | 28,042 | 24,908 | 28,223.704 | 25,131.562 |
| 2 | 28,077 | 25,248 | 28,260.837 | 25,424.081 |
| 3 | 27,694 | 24,783 | 27,868.904 | 24,961.641 |

- solver 중앙값 28,042→24,908ms: 11.18% 감소. 첫 반복을 제외한 두 비교에서도 약 10~11% 감소.
- 각 반복의 방문 노드 4,486,561→4,453,143(0.74% 감소), 평가 26,198,199→25,872,175(1.24% 감소). 상한 강화의 탐색량 효과는 작으며, 시간 개선에는 분기 점수 재사용도 포함된다.
- peak working set 범위: 기존 90,238,976~90,316,800 bytes, 변경 89,223,168~89,964,544 bytes. 새로운 분기 점수는 Rust 트리 노드당 f64 하나를 추가하지만 전체 측정 메모리는 증가하지 않았다.
- 6회 모두 exact 14,097, 64/64 shard 완료. 동일 최적 ID: `weapon:도이+후빗||armor:알타달+칼레리프||additional:카나요간+칼레리프||special:저편의 잔영+칼레리프`.

`D4_P6_PACKAGE_LIMIT=12 또는 24`와 `D4_P6_THREAD=1`로 실제 후보를 결정적으로 표본 추출하고 JS exhaustive oracle과 비교할 수도 있다. 이 작은 표본의 결과는 전체 입력의 속도 보증이 아니다.

실제 앱 WebView/설치본 E2E, 모든 필수 fixture의 cold 10회 P95, 모든 입력의 10초 exact Gate는 실행하지 않았다. P6 bridge는 공통 solver를 사용하지만 서비스의 30초 slice 실행 전체를 측정한 것은 아니다.
