# R3 Application / 계산 정책 추출

## 범위

R3는 계산식과 D4 후보·상한·동점 규칙을 바꾸지 않는다. 기존 classic JavaScript를 유지한 채, UI에 분산된 계산 조립 순서만 Application 유스케이스로 모은다.

- [application-use-cases.js](../../assets/js/application-use-cases.js)는 `CaptureCurrentInput` → `CreateCalculationSnapshot` → `CalculateBuild` 흐름을 제공한다.
- `CreateCalculationSnapshot`은 현재 레거시 DOM 입력 어댑터를 한 곳에서 호출하고 패시브 스탯 적용을 정확히 한 번 수행한다. R4에서는 이 임시 입력 어댑터를 `BuildDraft` 변환기로 교체한다.
- `CalculateBuild`는 같은 snapshot과 최종 계산·콤보에 쓰는 전투 컨텍스트를 반환한다. 영속 상태는 snapshot에 넣지 않는다.
- `ResolveActiveBuffs`는 활성 버프 선택을 복사해 계산 요청에 전달한다. 탭·드래그·진행률·취소 상태는 포함하지 않는다.
- `ApplyComboHit`은 선택 타격의 계수, 상수, 공격 프로필, 플래그, 확률 효과를 기존과 같은 모양으로 만든다.

## 단일 정책 경로

[calculation-policies.js](../../assets/js/calculation-policies.js)는 세 정책을 한 경로로 정의한다.

- `StatRegistry` 적용: 실제 앱 계산은 `ToramCalculationPolicies.applyStat`을 통해 기존 registry를 사용한다. 계산기 단독 테스트를 위한 legacy fallback은 명시적으로 남겨 두었다.
- 크리스타 조건: `main`·`sub`·`armor` 조건은 `matchesCrystaCondition`으로 통일했다.
- 스킬 정의: 효과 엔진·콤보는 기존과 같은 첫 등록 정의를, 버프 표시만 명시적으로 `preferStackControl`을 지정해 기존의 스택 보강 카드 우선 규칙을 유지한다. 이는 서로 다른 선택 규칙을 묵시적으로 복제하지 않기 위한 하나의 parameterized 정책이다.

## UI 경계

- 최적화 UI는 직접 `getBaseContext`와 `applyPassiveSkillStats`를 조립하지 않고 `CreateCalculationSnapshot`을 사용한다.
- 액티브 버프와 콤보 UI는 직접 `getBaseContext` → 패시브 → `simulateWithCrystas` 순서를 조립하지 않고 `CalculateBuild`를 사용한다.
- 콤보 타격 선택은 `ApplyComboHit`으로 이동했다.

## 검증

```powershell
npm run verify:r3
npm run test:r0
cargo test --manifest-path src-tauri/Cargo.toml
npm run desktop:build:exe
```

2026-08-31 결과:

- R3 유스케이스·정책 단위 검증 통과
- R0 기준선 65/65 성공. `test-tauri-native-storage-e2e.mjs`는 `TORAM_E2E_CDP` 미설정으로 기존과 같이 `SKIP`
- Rust 72개 테스트 통과(19 + 19 + 5 + 29). 비ASCII 사용자 경로 canonicalize 경고는 결과에 영향이 없었다.
- `npm run desktop:build:exe` 통과. `types:emit`, Tauri frontend 준비, release 실행 파일 생성까지 확인했다.
