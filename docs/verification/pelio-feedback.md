# pelio s 피드백 확인

- 확인일: 2026-10-13. 현재 작업 트리와 `samples/`의 원본 3개를 사용했다.
- 원문: [계산기 돌리면서 느낀 거](<../../samples/계산기 돌리면서 느낀 거 - pelio s.txt>).
- 범위: 저장 문서 파싱, 실제 Application·계산 엔진·스킬/콤보 엔진, 일부 결과 전환 핸들러. 설치된 앱의 탭 클릭 E2E와 당시 추천 조합 전체 재현은 포함하지 않는다.
- 콤보 8→9칸 제한과 활성 결계 행동속도 전달을 수정했다(결계 추가 검증: 2026-10-14). 위자드 계산 누락과 결과 전환 문제는 남아 있다.

## 제보별 판정

| 제보 | 현재 확인 결과 |
| --- | --- |
| 매직 카논 Lv.10·200 충전의 타당 계수 28.215 | 지팡이 샘플에서 동일하게 재현. 원문 캐시의 타격별 충전 분배와 일치한다. 타당 60으로 바꿀 근거는 없다. |
| 라지 페루루의 근위·크율 미적용 | 계산 엔진에서는 미재현. 세 샘플 모두 제거 전후 SRW 차이 +10, CRIT% 차이 +50. 서폿 샘플은 실제 1슬롯에 장착돼 있다. 당시 화면 표시 문제는 별도 확인 필요. |
| 다른 탭에 다녀오면 정밀 결과 변경·추천 불가 | 결과 탭 클릭이 항상 빠른 추천을 요청하며, 빠른 추천 시작이 기존 정밀 결과·continuation을 폐기하는 경로를 확인했다. 실제 핸들러 실행에서도 폐기를 확인. 제보된 세 크리스타 교체와 추천 불가 문구까지는 미재현. |
| 죠코 2개인데 크리율 상승 표시 | 같은 입력에 죠코 2개의 효과만 더하면 고정 CRIT는 정확히 -18. 전체 교체 전후에는 다른 크리스타의 CRIT%·CRIT도 달라진다. 당시 추천 전체 조합·선택 타격이 없어 상승 표시 자체의 오류는 아직 확정하지 않는다. |
| 서폿 CSPD 10418 예상, 8610 표시 | 제공 샘플의 현재 계산은 8183으로 두 수치를 그대로 재현하지 못했다. 캐스트 마스터리와 오버리미트/가이드의 계산 누락은 확인했다. 아래 상세 참고. |
| 콤보 9칸인데 앱은 8칸 | 8칸 제한 확인 후 9칸으로 수정. 추가 버튼·복원은 같은 제한값을 사용한다. 9번째 입력 보존·재복원·10번째 제한 회귀 통과. 콤보 포인트·레벨은 별도 보류 범위다. |
| 결계 행동속도가 현재 세팅/결과에 미적용 | 누락 확인 후 수정. 두 마법 샘플의 OFF 행동속도는 36%, 25%, ON은 모두 50%다. Lv.10 +25%를 계산 스탯과 최적화 입력으로 전달한다. |
| MEL/LUK 선택 요청 | 현재 입력과 저장 타입은 STR/INT/VIT/AGI/DEX/CRT다. 새 개성 스탯 지원은 별도 기능 확장이다. |
| 추천 요구조건의 사용자 수치 설정 | 현재 코드는 HP/MP/AMPR/평타 CRIT/ASPD의 수치 입력·적용·저장·복원을 지원한다. 기본값 선택/해제만 지원한다는 설명은 현재 코드와 다르다. 당시 배포 버전·화면의 사용성은 별도 확인 필요. |
| 어그로·물마내·이상내성 결과 표시 요청 | 옵션은 StatRegistry의 보존 스탯으로 남지만 주요 공격/유틸리티 비교 카드에는 나오지 않는다. 표시 확장과 탱커 목적함수/추천은 서로 다른 작업이다. |
| 속성약점/속성유리·오버리미트 적용 여부 | 두 마법 샘플은 `ELEM_AWAKENING`으로 약점 +25와 기본 INT/10 보너스 +51을 받는다. 장비 속성유리 +25/+24를 합쳐 현재 +101/+100. 오버리미트 효과는 별도 계산 누락이다. 모든 입력에 약점이 기본 적용되는 것은 아니다. |

## 계산 근거와 누락 위치

### 매직 카논

`docs/sources/skills/Magic.txt`는 충전량을 타격마다 20씩 분배하고 100을 넘으면 첫 타격부터 다시 분배한다. 200 충전은 5타에 각각 40이다.

- 마도구 기본 타당 계수: `0.03 × 10 × 40 = 12`, 5타 기본 계수 합은 60.
- 지팡이 샘플의 기본 타당 계수: `12 + 510/100 = 17.1`.
- 지팡이 샘플의 패시브·강타 적용 타당 계수: `17.1 × 1.1 × 1.5 = 28.215`.

연결: `web/src/data/skills/magic.js`의 `cannonPortion`·`definitions[11]`, `tools/tests/skills/test-magic-regression.mjs`. 화면의 계수는 패시브·버프·콤보 배율이 포함될 수 있으므로 기본 타당 계수·전체 합과 구분한다.

### 결계·오버리미트·캐스트 마스터리

- 결계: 원문·정의의 Lv.10 행동속도는 +25. 효과 타입을 `stat`, 키를 `MOTIONSPEED`로 수정해 기존 `activeStatChanges` 경로에 연결했다. 지팡이/메인 마도구·수동 ON 조건을 유지한다. oo o 샘플의 이전 ASPD 불가능 판정도 이 누락 때문이었다. 정정: [Native 회귀](../../tools/tests/optimization/test-crysta-native-exact.mjs).
- 오버리미트/가이드: `overLimit`·`overLimitGuide` 메타데이터의 CSPD -1000/+500과 속성 피해 증가를 계산용 스탯/공격 효과로 연결하는 처리가 없다. ON/OFF에서 CSPD가 같았다. 피격·HP·침묵·시간 자동 전이와 단순 수치 적용을 구분해야 한다.
- 캐스트 마스터리: `states.wizardLearnedCount`를 참조하지만 일반 패시브 계산은 해당 상태를 공급하지 않는다. 서폿 샘플에서 +15%만 나온다. 원문 캐시의 식은 습득 15개·총 투자 79·마스터리 Lv.10에서 +85%, 고정 +790이다. 고정 CSPD 효과도 정의에 없다.
- 현재 엔진에 이 누락된 CSPD 항만 진단용으로 더하면 서폿 샘플은 10000이다. 제보의 인게임 10418과 남은 차이는 확정하지 않았다. 이 수치를 새 회귀 정답으로 승격하거나 계산식 수정에 사용하지 않았다.

연결: `web/src/data/skills/wizard.js`, `web/src/data/skills/magic.js`, `web/src/calculation/skill-effect-engine.js`, `web/src/calculation/calculator.js`, `docs/sources/skills/Wizard.txt`.

### 결과 탭 복귀

`tabs.js`의 결과 버튼 → `toram:preview` → `ui-bootstrap.js`의 `runPreviewSafe` → `runCalculation('preview')` → `startCrystaOptimizationGreedyPreview` 경로다. 마지막 함수는 정밀 작업 cancel, continuation dispose, `lastOptimizationResult = null`을 수행한다. 입력이 그대로인 결과 탭 복귀에서도 정밀 결과를 보존할 필요가 있다. 이번에는 동작을 변경하지 않았다.

## 검증

- `node tools/verification/check-pelio-feedback.mjs`: PASS. 실제 저장 파서·Application·엔진 실행, 라지 페루루 옵션 차이, 죠코 단순 합산 -18, 원본 입력 보존·스코프 복원, 빠른 추천 시작 시 정밀 결과 폐기 확인. 전체 피드백 해결을 의미하지 않는다.
- `node tools/tests/application/test-combo-ui-loading.mjs`: PASS. 9칸 복원·9번째 입력 보존·재복원·10번째 제한.
- `node tools/tests/application/test-combo-tags.mjs`, `node tools/tests/skills/test-magic-regression.mjs`, `node tools/tests/skills/test-wizard-regression.mjs`: PASS.
- `node tools/verification/audit-stack-source-links.mjs --tree Magic --require-s1`: PASS, S1 24/24.
- `node tools/verification/audit-stack-source-links.mjs --tree Wizard --require-s1`: PASS, S1 15/15. S1 통과는 위 계산 누락의 S4/S5 완료를 의미하지 않는다.
- `npm run test:regression`: 종료 0, runner 요약 77/77. `test-tauri-native-storage-e2e.mjs`는 `TORAM_E2E_CDP` 미설정으로 SKIP이며 실기기 저장 검증 통과를 뜻하지 않는다.
- `npm run ai:audit`, `git diff --check`: PASS.

다음 수정 우선순위는 결과 탭 복귀의 정밀 결과 보존, 위자드 수치 연결, 제공 샘플로 전체 추천 비교 재현이다. 사용자 보류인 피격 시뮬레이션·콤보 포인트/레벨을 함께 구현하지 않는다.
