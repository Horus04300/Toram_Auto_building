# R1b TypeScript 점진 도입

## 적용 범위

- 개발 의존성: TypeScript `5.9.3`
- 기본 검사: `tsconfig.json`의 `strict`, `noUncheckedIndexedAccess`, `exactOptionalPropertyTypes`, `useUnknownInCatchVariables`, `noEmit`
- 검사 대상: 새 `frontend/**/*.ts` 파일만. 기존 classic JavaScript 전체를 `checkJs`로 억지 편입하지 않는다.
- `frontend/contracts/boundary-dtos.d.ts`는 현재 legacy 경계의 DTO를 정의한다.
  - Build: `LegacyBuildSettingsSnapshotDto`
  - 계산: `CalculationRequestDto`, `CalculationResultDto`
  - D4: `D4OptimizationRequestDto`, `D4OptimizationResultDto`
  - 저장: `LegacyBuildStorageAdapter`, `TauriSettingFileDto`
- `frontend/contracts/boundary-dto-fixtures.ts`는 위 DTO의 컴파일 시점 사용 사례를 검증한다. 이는 R2의 최종 Domain/Application 계약을 미리 확정하지 않는다.

## 실제 런타임 전환

Tauri 저장 어댑터만 작은 단위로 TypeScript 소스 [tauri-build-storage-adapter.ts](../../frontend/runtime/tauri-build-storage-adapter.ts)로 전환했다.

- `tsconfig.runtime.json`은 이 파일만 classic JavaScript [tauri-build-storage-adapter.js](../../assets/js/tauri-build-storage-adapter.js)로 출력한다.
- 출력물은 기존과 같은 `window.ToramBuildStorageAdapter` API, 여섯 Tauri 명령, 브라우저에서의 adapter 미노출 조건을 유지한다.
- `npm run desktop:prepare`는 assets를 `dist`로 복사하기 전에 `types:emit`을 실행한다. 따라서 개발·Tauri 빌드 모두 같은 생성 JavaScript를 사용한다.

## 안전장치와 남은 범위

- 새 TypeScript 파일에는 명시적 `any`를 허용하지 않으며, `verify:r1b`가 이를 검사한다.
- 첫 strict 컴파일에서 저장 adapter 콜백의 암시적 `any` 6개가 발견됐고, 모두 명시적 `string` 매개변수 타입으로 해결했다.
- 계산기·BuildEvaluator·D4 Worker/Native client의 구현은 아직 classic JavaScript다. 이번 단계에서는 해당 경계의 DTO만 먼저 고정했으며, 계산식·후보·상한·동점 규칙은 바꾸지 않았다.

## 검증

```powershell
npm run types:check
npm run types:emit
npm run verify:r1b
npm run test:r0
cargo test --manifest-path src-tauri/Cargo.toml
npm run desktop:build:exe
```

2026-08-31 결과:

- TypeScript strict 검사와 DTO 검증 통과
- 저장 adapter 회귀 및 저장 snapshot 회귀 통과
- R0 65/65 성공. 네이티브 저장 E2E 1건은 기존과 같이 `TORAM_E2E_CDP` 미설정으로 `SKIP`
- Rust 72개 테스트와 Tauri no-bundle 빌드 통과
