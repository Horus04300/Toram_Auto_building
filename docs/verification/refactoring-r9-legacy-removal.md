# R9 Legacy 제거 검증

## 제거한 전환 코드

- `calculator.js`의 `applyStatLegacy`와 크리스타 조건 fallback을 삭제했다. 계산기의 stat 적용과 조건 판정은 `ToramCalculationPolicies`만 사용한다.
- `crysta-ui.js`의 중복 크리스타 조건 fallback을 삭제하고 같은 정책으로 위임했다.
- Application의 임시 입력 객체 이름을 `legacyInput`에서 `kernelInput`으로 바꿨다. 이는 기존 계산 커널의 입력 어댑터이며, 계산 호출 후 전역 scope를 남기지 않는다.
- D4 Worker와 독립 계산 회귀도 `stat-registry.js → calculation-policies.js → calculator.js` 순서를 사용하도록 맞췄다.

## 유지한 경계와 근거

다음은 이름에 `Toram`이 남아도 legacy 제거 대상이 아니다. 현재 제품 경로와 회귀가 직접 사용한다.

| 경계 | 유지 이유 |
| --- | --- |
| `ToramCalculationInputScope` | BuildDraft/Scenario/Request를 기존 계산 커널에 명시적으로 전달하고 호출 뒤 제거하는 격리 scope |
| `ToramD4ExecutionAdapter` | Native 우선, Worker fallback, 취소·일시정지·재개를 소유하는 R7 실행 Port |
| `ToramD4NativeClient`, `ToramD4WorkerClient` | 실행 Adapter가 실제 위임하는 구현체 |
| `ToramSettingsFileRepositoryAdapter` | Settings Repository가 Tauri 파일 명령에 연결하는 실제 Port |
| `legacy-script-manifest.mjs` | 아직 classic script 형식인 데이터·UI 모듈의 의존 순서를 보장하는 R1a 로더 계약 |

이 전역/classic script 계층 전체를 제거하려면 남은 소비자를 ESM으로 옮기는 별도 마이그레이션이 필요하다. R9에서는 실제 참조를 가진 코드를 추정으로 삭제하지 않는다.

## 저장 경로

- 이름 있는 빌드: R6 `saved-build`, `schemaVersion: 1` 파일 계약만 사용한다.
- 마지막 세션: `toram.auto-build.application-state.v1` 하나만 사용한다.
- `toram-auto-build-setting`, File System Access API, IndexedDB 폴더 경로는 다시 도입하지 않는다.

## 검증

- `npm run verify:r9`
- `npm run test:r0`
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`
- `cargo test --manifest-path src-tauri/Cargo.toml`
- `cargo clippy --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`
- `npm run desktop:build:exe`

실제 Tauri WebView2 저장 E2E는 `TORAM_E2E_CDP`가 설정됐을 때만 실행된다. 미설정 환경의 skip은 통과로 해석하지 않는다.
