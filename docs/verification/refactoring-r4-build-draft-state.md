# R4 계산 상태 단일 출처

## 상태 경계

[build-draft-store.js](../../assets/js/build-draft-store.js)는 세 상태를 분리한다.

- `BuildDraft`: 캐릭터, 장비·옵션·크리스타 잠금, 외부 옵션, 스킬 투자, 활성 버프, 저장 가능한 콤보 구성만 보유한다.
- `ScenarioContext`: 보스 방어력·내성 등 계산 대상 조건을 별도 전달한다.
- `CalculationRequest`: 선택 타격과 일회성 콤보 효과를 별도 전달한다. 적용 타격은 `toram:combo-hit-selected` 이벤트로 request만 갱신한다.
- `ToramUiState`: 콤보 선택 인덱스처럼 화면에만 필요한 값을 위한 별도 컨테이너다.
- `ToramRuntimeState`: D4 실행 버전, 이어하기 요청, 마지막 결과, 계산 대기 상태를 보유한다. 어떤 값도 BuildDraft에 저장하지 않는다.

`BuildDraft` 계약에는 기존의 영속 빌드 구성에 필요한 `externalOptions`와 콤보의 `includeSpecialAttack`를 추가했다. 보스 조건, 콤보 선택 인덱스, D4 진행·취소·캐시는 넣지 않았다.

## 계산 입력

[application-use-cases.js](../../assets/js/application-use-cases.js)는 `ToramBuildDraftStore.read()`로만 입력을 받는다. DOM, `ToramComboUi`, `ToramActiveBuffs`, `getCurrentCrystas`를 직접 읽지 않는다.

기존 classic 계산 엔진은 호환을 위해 `ToramCalculationInputScope`를 계산 호출 동안만 사용한다. 이 스코프는 BuildDraft의 스킬 투자·활성 버프·장비 옵션과 explicit Scenario/Request에서 구성되고, 계산이 끝나면 복원 또는 제거된다. 따라서 기존 `getBaseContext`·스킬 효과 엔진을 유지하면서도 계산 중 전역 UI 값이 결과를 바꾸지 않는다.

UI 입력·스킬 투자·버프·콤보 편집은 중앙 Store를 갱신한다. 액티브 버프가 파생한 옵션 행도 `toram:build-options-changed`로 다시 동기화한다.

## 검증

```powershell
npm run verify:r4
npm run test:r0
cargo test --manifest-path src-tauri/Cargo.toml
npm run desktop:build:exe
```

2026-08-31 결과:

- R4 단위 검증: Draft Snapshot 불변성, explicit Scope, UI/Runtime 분리, DOM·암묵 UI 전역 비의존 통과
- R0 기준선: 65/65 성공. 네이티브 저장 E2E는 `TORAM_E2E_CDP` 미설정으로 기존처럼 `SKIP`
- Rust 72개 테스트 통과(19 + 19 + 5 + 29). 비ASCII 사용자 경로 canonicalize 경고는 결과에 영향이 없었다.
- `npm run desktop:build:exe` 통과. `types:emit`, Tauri frontend 준비, release 실행 파일 생성을 확인했다.
