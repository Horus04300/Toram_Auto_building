# D4 개별 유틸리티 목표 상한

2026-09-24. 사용자가 지정한 목표 판정 규칙을 JS와 Native에 동일하게 적용했다. 일반 계산 결과와 대미지용 원시 스탯은 유지한다.

## 목표 계약과 근거

| 목표 | 판정 |
| --- | --- |
| HP | 고정 숫자를 추정하지 않는다. 현재 스탯·버프·네 부위의 실제 2슬롯 패키지로 가능한 상한을 검사한다. |
| MP | 2000까지. 신속의 수도 습득 시 3스택 여유분을 포함한 목표 상한은 2300. 실제 MP 시스템 상한을 2300으로 변경하는 처리는 아니다. |
| AMPR | MP 기여분은 2000에서 포화하고 AMPR% 옵션을 제외한다. 기존 평타 패시브·액티브 효과와 듀얼 적용 전 기준은 유지한다. |
| 평타 크리티컬 | 보스 저항 적용 후 확률을 0~100으로 제한한다. |
| ASPD | 1000 미만은 평타 지연 구간. 이후 기존 계산식의 `floor((ASPD-1000)/180)`과 직접 행동속도를 합쳐 50%까지 비교한다. 목표도 같은 180 단위로 변환한다. 음수 행동속도는 목표 좌표에서 0으로 제한하며 원시 계산은 유지한다. |

MP·AMPR% 제외·크리티컬·ASPD/행동속도 한계의 근거는 이번 사용자 요구사항이다. 신속의 수도의 기존 스택 효과 연결은 `assets/js/data/skills/halberd.js` 및 `docs/sources/skills/Halberd.txt`, ASPD 반올림과 행동속도 합산은 `assets/js/calculator.js`의 기존 계산을 따른다. 새로운 스킬 수치를 추정하지 않았다.

목표 2001 MP(신속의 수도 미습득), 101 크리티컬, 10001 ASPD를 자동으로 낮추지 않는다. 해당 목표는 충족 불가다. ASPD 1001~1179는 기존 내림 계산상 행동속도 0%p 구간이므로 1000과 동일하게 판정한다. 직접 행동속도 50%가 있더라도 ASPD 1000 미만의 평타 지연을 충족한 것으로 보지 않는다.

## 탐색 처리

- JS `d4UtilityValues`와 Native utility 평가를 별도로 두고, raw 결과·대미지 계산과 분리했다. 표시되는 원시 AMPR/ASPD와 목표 판정 수치는 다를 수 있어 요구조건 창에 기준을 안내한다.
- Native는 대미지 탐색 전에 목표별 안전 상한을 검사한다. 루트의 옵션별 최댓값으로 결론을 못 내리면 실제 후보 트리를 분할해 해당 목표를 달성할 조합이 있는지 확인한다. 이미 가능한 초기해가 있으면 추가 증명을 생략한다.
- 목표당 최대 256개 박스를 처리한다. 예산 소진은 **불명**이며 이후 일반 탐색으로 넘긴다. 큐 전체의 안전 상한이 목표보다 작다는 증거가 있을 때만 불가능 판정한다. 모든 입력의 정확한 수치 최댓값을 사전 계산하는 기능은 아니다.
- 개별 목표가 각각 가능하다는 사실로 동시 충족을 가정하지 않는다. 최종 조합은 기존 정확 탐색에서 모든 목표를 검사한다.
- JS fallback도 목표 좌표를 사용한다. 추가 개별 가능성 사전 탐색은 Native에 적용한다.
- 시나리오 `utilityPolicyVersion:2`, Native 엔진/checkpoint v6로 이전 결과·continuation을 구분한다. raw 계산 v2와 split v3는 유지한다. v4/v5 checkpoint 거부 회귀를 포함한다.

## 검증

- `npm run test:r0`: 71/71 프로세스 성공. 실제 Native 저장 E2E는 CDP 미설정으로 SKIP이며 실행 통과로 간주하지 않는다.
- `node tools/test-d4-utility-caps.mjs`: 13개 경계, 105개 JS 완전 탐색/Native score·최적 ID·상태 일치, 트리 상한 및 단조성 검사 통과. R0 정상값 fixture에 등록했다. 단독 실행 전 `cargo build --release --manifest-path src-tauri/Cargo.toml --bin d4_native_exact`로 브리지를 준비한다.
- `cargo test --manifest-path src-tauri/Cargo.toml`: 실행 대상별 45+45+14+58=162개 통과. 동일 모듈이 여러 바이너리에서 검사되는 수를 포함한다.
- HP 회귀: VIT 1, 옵션별 루트 상한 8365지만 실제 조합 최대는 4873인 입력에서 목표 5000을 대미지 탐색 노드 방문 0회로 배제한다. 목표 4873은 exact로 도달한다.
- `npm run verify:r9`, `cargo clippy --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`, S1 출처 연결 427/427 통과. raw JS/Rust parity 1938개는 R0에서 통과했다.
- 큰 입력 smoke: `profile-d4-slow-inputs.mjs build` 후 `D4_PROFILE_FIXTURES=revenir,dual`, threads 16, budget 3000으로 계측. 제품 경로 복사본에서 루브닐 23,192,126회 평가, score 1,123,905.36 / upper 1,261,878.72; 듀얼 25,307,074회 평가, score 21,440 / upper 24,020. 모두 bounded이며 최적성 또는 이전 대비 성능 향상을 주장하지 않는다. 계측 삽입본도 같은 incumbent를 얻었다. 상세: `d4-individual-utility-measurements.json`.

이전 계측은 `d4-utility-conflict.md`, 4진 힙 변경은 `d4-frontier-heap.md`에 보존한다. 목표 의미가 바뀌었으므로 이전 synthetic 결과와 이번 실행 시간을 직접 개선율로 비교하지 않는다. 설치본 UI 및 실제 Native 저장 E2E는 이번에 실행하지 않았다.
