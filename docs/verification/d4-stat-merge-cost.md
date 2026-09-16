# D4 스탯 합산 할당 비용 개선

- 날짜: 2026-09-15. 유틸리티 하위호환 강화는 사용자 요청으로 보류하고 실행 비용 개선으로 전환했다.
- 변경 대상: `src-tauri/src/d4_native_solver.rs`의 `add_stats`, `box_stats`.

## 변경

기존 `entry(key.clone())`는 이미 존재하는 스탯 키도 문자열을 할당했다. 네 장비의 상한 벡터를 합칠 때 중복 좌표가 반복되므로, 존재하는 키는 `get_mut`으로 갱신하고 새 키만 복사한다.

상자 합산은 첫 그룹의 BTreeMap을 직접 복사하고 나머지 세 그룹을 순서대로 더한다. 빈 맵에 첫 그룹의 모든 키를 하나씩 삽입하는 작업을 줄인다. 후보·상한 수식·초기해·분기·동점 정책은 그대로다. 합산 순서를 바꾸거나 부모 상한에서 값을 빼는 방식은 사용하지 않는다. 삽입 시 `0.0 + value`도 유지해 음수 0의 처리를 보존한다.

직렬 exact, 병렬 exact, NativeSearchSession slice에서 공통 함수를 사용한다. 저장·checkpoint 형태는 바뀌지 않아 solver/checkpoint v2를 유지한다.

## 검증

- `cargo test --manifest-path src-tauri/Cargo.toml`: PASS, 88개(공유 모듈의 binary별 테스트 포함). 큰 부동소수점 상쇄의 합산 순서, 희소 음수 MP, 음수 0 검사를 추가했다. 기존 exact·동점·1~64스레드·취소·재개·checkpoint 회귀 포함.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`: PASS.
- `cargo clippy --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: PASS.
- `cargo build --release --manifest-path src-tauri/Cargo.toml --bin d4_native_exact --bin d4_native_parallel`: PASS.

## 성능 비교 방법

이전 signed envelope/분기 캐시까지 반영한 release binary를 `d4_native_parallel-before-map-merge.exe`로 보존했다. 이전 개선 전 수치를 이번 변경의 baseline으로 사용하지 않는다.

Windows / Ryzen 7 9800X3D / Node v24.17.0 / rustc 1.98.0, P6 물리 근거리 전체 후보, 8스레드. 패키지 수 992/844/724/929. `D4_P6_THREAD=8`과 `D4_NATIVE_BINARY`로 전/후를 번갈아 각 3회 새 프로세스 실행하고, 환경 변동 확인을 위해 마지막 한 쌍은 후→전 순서로 추가 실행했다. 실행 명령은 `node tools/benchmark-d4-native-p6.mjs`다. 유틸리티 감사는 비활성이다.

solver 시간은 JS compile/Pareto를 제외한다. 외부 wall에는 Native 프로세스 실행 비용이 포함된다. PowerShell 종료 CPU/exitCode가 일부 0/null로 반환되는 기존 계측 한계가 있어 해당 필드로 성능을 판정하지 않는다. JSON의 exact·점수·최종 ID·완료 shard와 실제 시간/메모리를 비교한다.

| 비교 | 순서 | 기존 solver ms | 변경 solver ms | 기존 wall ms | 변경 wall ms |
| --- | --- | ---: | ---: | ---: | ---: |
| 1 | 전→후 | 24,736 | 23,001 | 24,977.890 | 23,217.328 |
| 2 | 전→후 | 24,686 | 20,449 | 24,865.174 | 20,630.435 |
| 3 | 전→후 | 19,267 | 17,705 | 19,454.129 | 17,882.752 |
| 4 | 후→전 | 19,278 | 17,463 | 19,456.432 | 17,647.660 |

각 짝의 solver 단축률은 약 7.0%, 17.2%, 8.1%, 9.4%다. 환경 변화로 baseline 자체가 달라져 중앙값 하나로 일반화하지 않는다. 순서를 반전한 마지막 비교에서도 9.4% 단축됐다.

8회 모두 exact 14,097, 64/64 shard 완료, 평가 25,872,175회, 동일 최적 ID(`weapon:도이+후빗||armor:알타달+칼레리프||additional:카나요간+칼레리프||special:저편의 잔영+칼레리프`)였다. 방문 노드는 병렬 타이밍에 따라 4,453,142~4,453,143으로 1개 차이가 났다.

peak working set은 기존 89,776,128~91,070,464 bytes, 변경 89,972,736~94,285,824 bytes였다. 한 변경 실행에서 peak가 더 높아 메모리 감소 효과는 주장하지 않는다.

추가 회귀: `node tools/test-d4-native-exact-p4.mjs`, `node tools/test-d4-global-optimizer-stage2.mjs`, `node tools/test-d4-worker-stage3.mjs`, `node tools/test-d4-native-client.mjs`, `node tools/test-d4-native-resume-ui-n5.mjs`, `node tools/test-d4-utility-dependencies.mjs`, `node tools/test-d4-replacement-proof.mjs`, `node tools/audit-stack-source-links.mjs --require-s1` 모두 PASS(S1 427/427).

실제 서비스의 30초 slice 전체/WebView/설치본 E2E, 배포, 모든 필수 fixture의 cold 10회 P95는 미실행이다. 모든 입력에서 10초 exact를 달성했다는 의미가 아니다.
