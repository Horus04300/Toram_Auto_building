# R0 리팩토링 기준선

## 기준

- 기준 커밋: `37dae51` (`chore: checkpoint current development state`)
- 목적: 리팩토링 중 계산 결과와 현재 관찰 가능한 동작의 차이를 구분해 검토한다.
- 원칙: fixture가 실패해도 기대값을 테스트 통과용으로 갱신하지 않는다. 정상값은 원문 출처·계산식·명시된 불변식으로, characterization은 변경 승인으로만 갱신할 수 있다.

## fixture 분류

### 정상값 fixture

다음 fixture의 기대값은 스킬 원문·계산식, 데이터 감사 결과, 또는 D4의 명시된 알고리즘 불변식에 근거한다. 계산 계층을 옮긴 뒤에도 값과 명시적 제약을 유지해야 한다.

| 범위 | fixture |
| --- | --- |
| 계산·버프·콤보·크리스타 | `test-active-buff-context`, `test-combo-tags`, `test-d-sector`, `test-equipment-option-selector`, `test-normal-attack-ampr-priority`, `test-proc-damage-results`, `test-status-points` |
| 스킬 S1~S5 계산 | `test-assassin-s5`, `test-barehand-s5`, `test-battle-s5`, `test-blade-s4-s5`, `test-crusher-s5`, `test-dagger-s5`, `test-dancer-s5`, `test-dark-power-s5`, `test-dual-sword-s5`, `test-golem-s5`, `test-guard-s5`, `test-halberd-s3`, `test-halberd-s4-s5`, `test-hunter-s5`, `test-knight-s5`, `test-magic-blade-s5`, `test-magic-s3`, `test-magic-s4-s5`, `test-martial-s4-s5`, `test-minstrel-s5`, `test-mononofu-s5`, `test-necromancer-s5`, `test-ninja-s5`, `test-partisan-s5`, `test-priest-s5`, `test-shield-s5`, `test-shot-s4-s5`, `test-sprite-s5`, `test-support-s5`, `test-survival-s5`, `test-wizard-s5` |
| D4 계산·정확성 | `test-d4-evaluator-stage1`, `test-d4-global-optimizer-stage2`, `test-d4-native-exact-p4`, `test-d4-native-locks-n1`, `test-d4-pair-frontier`, `test-d4-pair-partition`, `test-d4-parallel-shards`, `test-d4-rust-native-parity`, `test-d4-utility-dependencies` |
| 데이터 | `test-skill-data-audit` |

### characterization fixture

다음 fixture는 기준 커밋에서 사용자가 관찰할 수 있는 동작이나 기존 경계를 기록한다. 이는 올바름을 새로 증명하는 테스트가 아니며, 기존 이상 동작도 고정할 수 있다. 의도적으로 바꿀 단계가 오기 전에는 결과를 보존한다.

| 범위 | fixture | 보존하는 현재 동작 |
| --- | --- | --- |
| UI·결합 | `test-active-buff-ui`, `test-combo-ui-loading`, `test-qa-edge-cases`, `test-skill-icon-assets` | 중복 표시 제거, 빈 정의 허용, 알려진 경계 조건, 아이콘 경로 |
| D4 실행 경계 | `test-d4-browser-worker-runtime`, `test-d4-dynamic-marginal`, `test-d4-dynamic-seed-builds`, `test-d4-execution-adapter`, `test-d4-full-stage3`, `test-d4-native-client`, `test-d4-native-resume-ui-n5`, `test-d4-native-runtime-n0`, `test-d4-parallel-worker-runtime`, `test-d4-replacement-proof`, `test-d4-worker-stage3` | Worker/Native 선택, 취소·재개·진행, bounded 실행, 현재 후보 탐색 경로 |
| 저장 | `test-build-setting-snapshot`, `test-tauri-build-storage-adapter`, `test-tauri-native-storage-e2e` | R6 단일 saved-build 계약과 Tauri IPC·파일 저장 흐름 |

저장 fixture는 R6에서 새 저장 계약으로 교체될 예정이다. R6 전까지는 characterization으로 유지하고, R6에서 명시적으로 제거·대체한 뒤에만 이 목록에서 제외한다. 저장 E2E는 `TORAM_E2E_CDP`가 설정된 데스크톱 세션에서만 실제 실행되며, 그렇지 않으면 테스트 자체가 `SKIP`을 보고한다.

## 실행

```powershell
npm run test:r0
npm run test:r0:normal
npm run test:r0:characterization
```

`tools/test-r0-baseline.mjs`는 실행기 자신을 제외한 `tools/test-*.mjs` 전체가 정확히 하나의 분류에 속하는지 먼저 확인한다. 새 회귀 테스트를 추가하면 `tools/r0-baseline-fixtures.mjs`에도 같은 변경에서 분류를 추가해야 한다.

## 기준선 실행 결과

2026-08-31에 기준 커밋 상태에서 기존 65개 테스트를 순차 실행했다.

- 결과: `65/65` 프로세스 성공
- 실제 실행: R0 runner 65/65 통과, `test-tauri-native-storage-e2e.mjs`는 `TORAM_E2E_CDP` 미설정으로 `SKIP`
- 확인된 실패: 없음

`SKIP`은 저장 기능 정상 동작의 증거가 아니다. R0 완료 검증에서는 분류·러너를 추가한 뒤 같은 전체 집합을 다시 실행하고, 네이티브 저장 E2E의 실행 가능 여부를 별도로 보고한다.

2026-09-01 R7에서는 `test-d4-execution-adapter.mjs`를 D4 실행 경계 characterization fixture로 추가했다. 현재 전체 fixture는 66개이며 `npm run test:r0`이 66/66을 통과했다. 이때도 네이티브 저장 E2E는 `TORAM_E2E_CDP` 미설정으로 `SKIP`했다.
