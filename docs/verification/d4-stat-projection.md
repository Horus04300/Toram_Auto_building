# 탐색용 옵션 벡터 분리

2026-09-27. `d4-next-candidates.md`의 첫 번째 후보를 Native 탐색에 구현했다. 앞선 입력 축소 실험과 달리 제품 입력과 반환 옵션을 보존한다.

## 구현과 유지하는 계약

- 패키지의 원본 `stat_delta`는 그대로 유지하고, 탐색 시작 시 `evaluation_delta`를 별도로 준비한다. Native 평가기가 읽는 37개 옵션을 모두 보존한다. `modeledKeys`가 유틸리티 의존성을 모두 포함한다고 가정하지 않는다.
- 직렬·병렬·공유 세션의 초기해/좌표 개선과 작은 박스 열거에서 계산 벡터만 합산한다. 최종 추천 및 진행 snapshot의 `NativeBuild.statDelta`는 선택된 원본 패키지를 기존 장비 순서대로 합산한다.
- `MOTIONSPEED`도 조밀 배열에 넣어 평가용 벡터에는 sparse 옵션이 남지 않게 한다. 원본의 저항·드롭률·경험치·미지 옵션은 sparse 저장과 JSON 직렬화에 그대로 남는다.
- 값의 존재 여부, 음수, signed zero, 합산 순서를 유지한다. 후보 목록·트리 분할/상한·동점 우선순위·수식은 변경하지 않는다. 준비하지 않은 내부 helper는 원본 옵션으로 평가한다.
- 계산 벡터는 JSON/체크포인트에 저장하지 않으며, 시작·복원 시 원본으로부터 다시 만든다. Native/checkpoint v8, 계산 v2·split v3·utility policy 2 계약을 유지한다.
- 탐색에서 읽는 옵션을 추가할 때는 조밀 좌표 목록도 갱신해야 한다. evaluator의 `stat` 및 `stat_total` 의존성이 projection에 포함되는지 검사하는 회귀를 추가했다.

## 정확성 검증

- Rust 옵션 병합 property: 1,000회, 각 4회 합산에서 sparse 원본 대비 계산 좌표의 값/부호 비트/존재 여부 비교. MOTIONSPEED와 알 수 없는 옵션 직렬화도 기존 roundtrip에 포함한다.
- 물리/마법·변환·듀얼 브링거 평가 계획 경계에서 전체 옵션과 계산 벡터의 summary 및 유틸리티 목표 값 비교.
- 8×8×8×8 동점 후보에 계산 외 옵션을 넣고 직렬, 1/4/64 작업자, 체크포인트 직렬화·복원을 검사한다. 최적 점수·ID·원본 반환 옵션·준비 캐시 재생성·입력 불변을 확인한다.
- 기존 JS oracle 회귀에 물리, 마법+변환+듀얼 브링거, 듀얼+VIT 스킬 계수 입력을 추가했다. HP/MP 음수, MOTIONSPEED 목표, 드롭률/저항/경험치가 있는 4⁴ 조합을 완전 탐색하고 Native 직렬·병렬·공유 세션 9회와 비교한다. 반환된 전체 옵션을 JS로 다시 평가한다.
- 첫 JS 회귀에 넣은 미등록 `FUTURE_OPTION`은 JS 진단 계약상 infeasible이어서, JS 대조에는 등록된 보존 옵션 `EXP`를 사용했다. 미지 옵션 원본 보존은 Rust 회귀로 검사한다. 진단 계약은 변경하지 않았다.

실행 명령과 결과:

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: 51+51+16+64=182개 통과(바이너리별 공통 모듈 중복 포함).
- `npm run test:r0`: 71/71 프로세스 성공. JS exhaustive/상한/property, JS/Rust parity, 잠금·추천 적용 및 유틸리티 105개 대조 포함. 실제 Native 저장 E2E는 `TORAM_E2E_CDP` 미설정 SKIP.
- `npm run verify:r9`, `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: 통과.
- `node tools/audit-stack-source-links.mjs --require-s1`: 427/427 출처 연결 통과. 스킬 수식/데이터는 변경하지 않았다.

## 성능 계측 방법

수정 직전 제품 소스의 control 바이너리를 `src-tauri/target/stat-projection/before.exe`에 보존하고, 수정 후 같은 도구의 control을 사용한다. 두 바이너리는 같은 진행 snapshot 계측을 포함한다.

```powershell
node tools/profile-d4-slow-inputs.mjs build
$env:D4_EVALUATION_EXPERIMENT='stat-projection'
$env:D4_COMPARE_REPEATS='2'
node tools/benchmark-d4-partial-utility.mjs
```

동일한 준비 입력 3개, 16작업자, 120초 예산, 변경 전→후/후→전 순서의 새 프로세스 12회를 순차 실행한다. 다른 빌드/테스트와 겹치지 않는다. Native 세션 준비 비용은 포함하며 JS 후보 준비·UI/IPC는 제외한다. 원본 옵션 재합산·반환값 및 JS 최종 재평가는 계측 도구에서 별도로 검증한다. 두 번 반복은 P95 인증이나 모든 입력의 개선 보장이 아니다.

## 측정 결과

| 입력 | 변경 전 2회 | 변경 후 2회 | 평균 시간 변화 |
| --- | --- | --- | --- |
| 루브닐 | 8.842 / 8.870초 | 8.311 / 8.102초 | 8.856→8.206초, 7.3% 감소 |
| 듀얼 | 18.817 / 19.369초 | 14.153 / 13.607초 | 19.093→13.880초, 27.3% 감소 |
| 유틸리티 충돌 | 5.707 / 5.671초 | 5.538 / 5.548초 | 5.689→5.543초, 2.6% 감소 |

12회 모두 exact이며 최적 점수·package ID·반환 `statDelta` 전체가 일치했다. 모든 반환 옵션을 원본 패키지와 대조하고 JS로 재평가해 점수·목표 충족을 확인했다. 수정 후 진행 snapshot 상한도 최종 최적값을 포함했다. 듀얼의 완성 조합 열거 수는 모든 실행에서 50,924,398로 같다.

원본과 계산용 배열을 함께 보관하므로 관측 peak working set은 평균 약 1~3 MiB 늘었다. 루브닐 약 133→136 MiB, 듀얼 약 164→166 MiB, 충돌 약 126→127 MiB다. 준비 시간은 루브닐 약 47~55ms, 듀얼 약 59~64ms, 충돌 약 10~12ms 범위다. 메모리 감소를 주장하지 않는다.

충돌 입력에는 제거할 sparse 옵션이 없으므로 2.6% 차이를 이 분리만의 효과로 일반화하지 않는다. MOTIONSPEED 조밀화와 실행 변동도 포함된다. 원본 sparse 옵션이 많은 루브닐·듀얼에서 효과를 확인해 제품 경로에 채택한다.

상세 데이터·전후 소스/바이너리 SHA-256·입력 해시·진행 snapshot·메모리: `d4-stat-projection-measurements.json`. AI 문서 감사와 diff 검사 통과. 설치본 UI 및 실제 저장 E2E는 이번에 실행하지 않았다.

후속 데이터 형식·소유권·작업 표현 조사: `d4-structure-audit.md`.
