# R2 계산 계약과 Port 정의

## 순수 계약

[calculation-contracts.ts](../../frontend/domain/calculation-contracts.ts)는 UI·DOM·Tauri·Worker·localStorage·JSON 저장 형식에 의존하지 않는 TypeScript 계약이다.

| 계약 | 책임 |
| --- | --- |
| `BuildDraft` | 사용자가 저장 가능한 캐릭터·장비·스킬·액티브 버프·콤보 구성만 보유한다. 탭, 드래그, 자동완성, D4 진행·취소·캐시는 포함하지 않는다. |
| `CalculationSnapshot` | `BuildDraft`, `ScenarioContext`, `CalculationRequest`을 하나의 계산 입력으로 묶는다. |
| `CalculationRequest` | 선택 스킬/타격과 일회성 override를 보유한다. 영속 `BuildDraft`에 넣지 않는다. |
| `CalculationResult` | 상태, 같은 snapshot, 수치 결과, 진단을 보유한다. |

`BuildDraft`는 현 localStorage 키나 legacy JSON 파일의 직렬화 모델이 아니다. R6에서 새 저장 계약을 설계할 때 이 타입을 저장 포맷으로 직접 간주하지 않는다.

## Port

[ports.ts](../../frontend/application/ports.ts)는 외부 구현을 교체할 필요가 있는 두 경계만 정의한다.

- `SettingsRepository`: 이름 붙인 빌드의 목록·읽기·저장·삭제. 현재 Tauri 파일 명령, 이후의 새 저장소는 이 인터페이스의 구현 후보다.
- `OptimizationRunner`: Worker/Rust D4 실행과 진행 보고를 위한 외부 실행 경계.

`CalculationGateway` 또는 계산 커널 추상화는 추가하지 않았다. 계산기는 이후 Application 서비스가 직접 호출하는 Domain 내부 구현으로 유지한다. 이 단계에서 기존 Tauri 저장 adapter, BuildEvaluator, D4 Worker/Native client는 Port를 아직 구현하지 않으며, 파일 이동·통합·계산식 변경도 없다.

## 검증

```powershell
npm run verify:r2
npm run test:r0
cargo test --manifest-path src-tauri/Cargo.toml
npm run desktop:build:exe
```

2026-08-31 결과:

- strict TypeScript 검사와 R2 순수성·Port 제한 검사 통과
- R0 65/65 성공. 네이티브 저장 E2E는 기존처럼 `TORAM_E2E_CDP` 미설정으로 `SKIP`
- Rust 72개 테스트 및 Tauri no-bundle 빌드 통과
