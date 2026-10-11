# 역할 기준 파일 통합·명칭 정리 계획

- 작성: 2026-09-30.
- 상태: 2026-10-01 구현 완료. 아래는 사전 계획 원본이며, 실제 적용·조정·검증은 [구현 기록](../verification/role-based-refactoring.md)을 따른다.
- 목적: 같은 책임의 불필요한 파일 분리를 줄이고, 개발 단계 대신 기능과 역할로 코드를 찾을 수 있게 한다.
- 기준: 작업 시작 시점의 실제 파일과 호출 관계. 기능·릴리스 판정은 [현재 handoff](../handoff/current-development-handoff.md)를 따른다.

## 1. 권고안

파일 수만 줄이기보다 **동일한 책임은 통합하고, 실행 환경과 계약이 다른 책임은 유지**한다. 우선 통합 대상은 UI 시작 코드, Rust 설정 서비스의 단순 위임, 같은 스킬트리의 단계별 보강 파일이다. 최적화 평가기·탐색기·실행 서비스는 역할별로 이름과 위치를 정리한다.

JS와 Rust는 각각 브라우저/Worker와 Native 실행을 담당한다. 언어를 하나로 바꾸거나 두 구현을 한 파일로 만드는 작업은 포함하지 않는다. 전체 ESM 전환, 계산식 개선, 탐색 알고리즘 변경, 피격 시뮬레이션·보류 콤보 기능도 별도 범위다.

현재 작업 트리에 계산·최적화·벤치마크·버전 파일의 기존 수정과 미추적 파일이 있다. 실제 구현은 이 변경을 포함한 기준 상태를 먼저 기록하고 시작한다. 임의 stash/reset/일괄 덮어쓰기나 기존 변경의 무단 커밋은 하지 않는다.

## 2. 코드에서 확인한 근거

| 확인 대상 | 관찰 | 계획에 미치는 영향 |
| --- | --- | --- |
| `src-tauri/src/settings_service.rs` | 6개 메서드가 `SettingsRepository`에 그대로 위임하며 별도 상태·정책이 없음 | 같은 설정 모듈에 통합할 수 있음 |
| `assets/js/ui-bindings.js`, `ui-feature-registry.js` | 초기화 연결과 기능 API 등록을 각각 담당. registry는 업데이트 브라우저 검증에서도 사용 | 하나의 시작 파일로 합치되 공개 API와 초기화 시점을 유지 |
| `assets/js/data/skills/` | JS 38개. 본체와 `-s3/-s5` 보강 파일이 함께 있는 트리 9개 | 트리별 한 파일로 통합하면 38→29개. 나머지 단계 접미사는 이름 변경 |
| `calculation-policies.js` | 기본 정책은 동일 ID의 첫 정의 선택, `preferStackControl`은 다른 정의를 선택할 수 있음 | 보강 파일을 최신 정의로 덮어쓰면 동작이 달라짐 |
| `data/skills/guard.js`, `guard-s5.js` | 같은 스킬 ID에 서로 다른 효과 phase/내용이 존재 | 물리적 통합과 의미상 중복 제거를 분리해야 함 |
| `app-entry.mjs`, `legacy-script-manifest.mjs` | manifest는 앱과 여러 테스트·감사의 공통 로딩 출처 | 작다는 이유로 entry에 인라인하지 않음 |
| `d4-optimizer-worker.js` | `importScripts`로 계산·최적화 코드를 별도로 로딩 | 문서의 manifest만 수정하면 Worker가 깨질 수 있음 |
| `d4-recommendation-apply.js` | 잠금·빈 슬롯·부위 전체 검증 후 쓰기를 수행하고 독립 회귀가 있음 | 작은 파일이지만 별도 책임이 있어 유지 |
| Native 평가기/탐색기 | 약 79 KB/147 KB이며 평가와 탐색·checkpoint 책임이 다름 | 하나의 거대 파일로 병합하지 않음 |
| `tools/verify-r5-ui-features.mjs`, `verify-r8-rust-modules.mjs` | 파일명·별도 모듈 존재·기존 함수명을 정규식으로 검사 | 이름만 바꾸는 작업에도 구조 검증 갱신 필요 |
| `tools/benchmark-d4-s7.mjs` | 하위 테스트의 `D4 full stage 3: PASS` 문자열을 파싱 | 로그 문구도 소비자가 있는 인터페이스로 취급 |
| `d4_headless_service.rs`, `tools/d4-headless-*.mjs` | 별도 프로세스·표준입출력·준비 환경·측정 경계로 나뉨 | 최근 추가된 파일을 크기만 보고 합치지 않음 |

크기는 이 계획 작성 시점의 참고값이며 성능 측정값이 아니다. 수치보다 호출 관계와 소유 책임을 통합 판단에 사용한다.

## 3. 통합·유지 대상

### 우선 통합

| 현재 파일 | 목표 파일 | 통합 방식과 유지할 경계 |
| --- | --- | --- |
| `assets/js/ui-bindings.js` + `ui-feature-registry.js` | `assets/js/ui-bootstrap.js` | 기능 등록과 초기화 연결을 같은 파일에서 관리. 모든 기능이 준비된 뒤 한 번만 실행. `DOMContentLoaded` 이전/이후, 공개 `ToramUiFeatures`, 업데이트 기능 등록 유지 |
| `src-tauri/src/settings_service.rs` + `settings_repository.rs` | `src-tauri/src/settings.rs` | 먼저 `SettingsService`와 `SettingsRepository` 타입을 같은 모듈로 이동. IPC는 service API를 호출하고 검증·파일 접근은 repository에 남김. 필요성 없는 위임 타입 제거는 별도 검토 |
| 아래 9개 스킬트리의 본체 + 보강 | `assets/js/data/skills/<tree>.js` | 원래 코드 블록·스킬 ID·정의 선택 결과를 보존해 한 파일에 배치. 파일 통합과 데이터 재해석을 섞지 않음 |

해당 트리: `assassin`, `crusher`, `dark-power`, `dual-sword`, `guard`, `halberd`, `knight`, `mononofu`, `sprite`.

스킬 등록은 전체 순서까지 보존해야 한다. 현재 두 파일이 manifest에서 떨어져 있는 트리는 본체 바로 뒤에 보강을 옮기는 것만으로 registry 전체 순서가 달라진다. 각 파일이 정의 묶음을 준비하고 기존 `skill-catalog-registration.js`에서 기존 순서대로 등록하는 방식 등으로 순서를 보존한 뒤, 기본/stack-control 선택과 metadata 부착 결과의 동치를 확인한다. 트리 내부 상대 순서만 같다고 완료하지 않는다.

`Guard-s5` 같은 등록 키는 역할을 확인한 뒤 `Guard:combat-rules`처럼 실제 내용을 설명하는 이름으로 바꾼다. 모든 보강을 일률적으로 `advanced`나 `extra`로 바꾸지 않는다. S1 감사·생성기·트리 직접 조회 소비자도 함께 수정한다. 동일 ID 정의를 하나의 객체로 정규화하는 작업은 원문과 선택 정책 검증이 필요한 후속 계산 변경이며 이번 구조 통합의 필수 조건이 아니다.

위 세 묶음의 물리적 통합만 계산하면 11개 파일 감소다. 새 Rust 모듈 조립 파일이나 폴더 분류에 따른 전체 순감소는 별도로 측정한다. 파일 감소 수를 채우기 위한 추가 병합은 하지 않는다.

### 조건부 통합과 유지

| 대상 | 권고 | 이유/판정 조건 |
| --- | --- | --- |
| `build-ui-controller.js` + `crysta-ui.js` | 후순위 조건부 통합 | 같은 빌드 입력 책임이지만 후자는 이미 약 33 KB. `ToramApp.buildUi.bind()` 경계를 유지하면서 탐색이 실제로 쉬워질 때만 통합 |
| `d4-dynamic-marginal.js` + `d4-dynamic-seed.js` | 현재는 분리 유지 | 점수 프로필과 초기해 생성·개선은 별도로 검증되는 역할. 성급한 `heuristics.js` 대형 통합을 피함 |
| `d4_native_stats.rs` + evaluator | 분리 유지 | 조밀 스탯 표현과 계산식의 책임이 다르고, 큰 evaluator에 추가할 실익이 낮음 |
| Native client / Worker client / 실행 adapter | 분리 유지 | 전송·세션·fallback 책임이 다름. adapter에는 컴파일·후보 삭제·상한을 넣지 않음 |
| Rust solver / evaluator / parallel runtime / service / IPC | 분리 유지 | 탐색·수식·스레드 실행·세션 수명·외부 명령의 경계 |
| Application / Store / 계산 정책 / 저장 Repository | 분리 유지 | 입력 단일 출처·정책 공유·저장 계약의 경계. 이름과 위치만 정돈 |
| 업데이트 controller / 설치 coordinator / UI / adapter | 분리 유지 | 다운로드·설치 동의·계산 종료·저장·UI·전송 책임 보존 |
| Rust 개발용 `bin/d4_native_*` | 역할명 변경을 먼저 수행 | 단일 CLI 통합은 옵션·표준입출력·측정 경계를 바꾸므로 호출자 목록 확인 후 별도 판단 |
| TS 원본 + 생성 JS, 원문 + 런타임 데이터 | 통합 제외 | 컴파일 산출물과 출처 증거. 생성 JS 직접 수정 금지 |

## 4. 명명·분류 규칙

개발 작업 순번인 `D4`, `R0~R9`, `stage1/2/3`, `N0/N1/N5`, `P1/P4/P6`, 실험명 `S7`은 활성 파일명·식별자·명령·현재 안내에서 역할명으로 교체한다. `D1/D2/D3/D5/D6`도 실제 기능을 읽고 평타·중독·콤보 타격·마법 크리티컬·입력 검증 등으로 바꾼다.

S1~S5는 스킬 검증의 의미가 정의된 기준이므로 검증 문서의 출처/구조/규칙/계산/사례 구분은 유지한다. 대신 런타임 파일명의 `-s5`는 제거하고, 테스트 파일명은 `-regression`, `-rules` 등 검사 책임으로 바꾼다. `schemaVersion`, checkpoint 버전, 계산 정책 버전, 제품 버전은 작업 순번과 다르므로 일괄 삭제하지 않는다.

기본 단어는 기능 `crysta-optimization`(크리스타 최적화), 역할 `compiler`, `solver`, `evaluator`, `client`, `service`, `runtime`, `ui`다. 현재 탐색 범위가 크리스타이므로 장비 옵션 전체 최적화가 구현된 것처럼 이름 붙이지 않는다.

### 런타임 경로와 심볼 예시

| 현재 | 변경안 |
| --- | --- |
| `assets/js/d4-problem-compiler.js` | `assets/js/optimization/problem-compiler.js` |
| `assets/js/d4-global-optimizer.js` | `assets/js/optimization/exact-solver.js` |
| `assets/js/d4-source-profile.js` | `assets/js/optimization/source-profile.js` |
| `assets/js/d4-pair-partition.js` | `assets/js/optimization/pair-partition.js` |
| `assets/js/d4-dynamic-marginal.js`, `d4-dynamic-seed.js` | `assets/js/optimization/marginal-score.js`, `seed-search.js` |
| `assets/js/d4-native-client.js`, `d4-worker-client.js`, `d4-execution-adapter.js` | `assets/js/optimization/native-client.js`, `worker-client.js`, `execution-adapter.js` |
| `assets/js/d4-optimizer-worker.js` | `assets/js/optimization/solver-worker.js` |
| `assets/js/d4-recommendation-apply.js` | `assets/js/optimization/recommendation-apply.js` |
| `assets/js/optimizer.js` | `assets/js/optimization-results.js` (결과 렌더링·실행 요청 진입점) |
| `assets/js/legacy-script-manifest.mjs` | `assets/js/classic-script-manifest.mjs` |
| `src-tauri/src/d4_native_{solver,evaluator,stats}.rs` | `src-tauri/src/optimization/{solver,evaluator,stats}.rs` |
| `src-tauri/src/d4_parallel_runtime.rs`, `d4_service.rs` | `src-tauri/src/optimization/{parallel_runtime,service}.rs` |
| `D4OptimizationService`, `D4OptimizationRequestDto` | `CrystaOptimizationService`, `CrystaOptimizationRequestDto` |
| `ToramD4ExecutionAdapter`, `compileD4GlobalCrystaProblem` | `ToramCrystaOptimizationRunner`, `compileCrystaOptimizationProblem` |
| `runtime.d4`, `d4OptimizationPause`, `.d4-progress-panel` | `runtime.crystaOptimization`, `crystaOptimizationPause`, `.optimization-progress-panel` |
| `build-state-storage.js`, `build-file-storage.js` | `build-state-snapshot.js`, `settings-ui.js` (구현 책임 최종 확인 후) |

`optimization/`은 JS/Rust 각 실행 환경의 기능 분류다. 모든 JS를 깊은 폴더로 옮기지는 않는다. Rust는 `optimization/mod.rs`에서 모듈을 조립한다. 바이너리의 `#[path]`, Node의 `require`, 테스트의 `import.meta.dirname` 기준 상대 경로도 이동 단위로 갱신한다.

### 도구·테스트·문서

| 현재 | 역할명 예시 |
| --- | --- |
| `test-d4-evaluator-stage1.mjs` | `test-crysta-evaluator.mjs` |
| `test-d4-global-optimizer-stage2.mjs` | `test-crysta-search-oracle.mjs` |
| `test-d4-full-stage3.mjs`, `test-d4-worker-stage3.mjs` | `test-crysta-real-candidates.mjs`, `test-crysta-worker-protocol.mjs` |
| `test-d4-native-runtime-n0.mjs`, `test-d4-native-locks-n1.mjs` | `test-crysta-native-runtime-input.mjs`, `test-crysta-native-locks.mjs` |
| `test-d4-native-exact-p4.mjs`, `test-d4-native-resume-ui-n5.mjs` | `test-crysta-native-exact.mjs`, `test-crysta-resume-ui.mjs` |
| `benchmark-d4-s7.mjs`, `benchmark-d4-parallel-p1.mjs`, `benchmark-d4-native-p6.mjs` | `benchmark-crysta-real-candidates.mjs`, `benchmark-crysta-worker-parallel.mjs`, `benchmark-crysta-native-scaling.mjs` |
| `test-d-sector.mjs` | `test-combat-calculation-integration.mjs`. 기존 사례를 유지하고 개명만을 위해 분할하지 않음 |
| `test-r0-baseline.mjs`, `r0-baseline-fixtures.mjs` | `run-regression-suite.mjs`, `regression-fixtures.mjs` |
| `verify-r3-*`〜`verify-r9-*` | `verify-application-boundary` / `verify-build-state` / `verify-ui-boundaries` / `verify-storage-contract` / `verify-optimization-execution` / `verify-native-boundaries` / `verify-runtime-contracts` |
| `docs/architecture/d4-exact-optimization-plan.md` | `docs/architecture/crysta-optimization-contract.md` |
| `docs/architecture/d4-native-runtime-correction-plan.md` | `docs/architecture/native-optimization-runtime.md` |

도구는 `tools/tests/optimization/`, `tools/tests/skills/`, `tools/verification/`, `tools/benchmarks/`, `tools/support/`를 목표 분류로 삼는다. 남은 파일을 일괄 이동하지 않고 변경하는 기능 단위로 옮긴다. 고정된 `../` 깊이에 의존하는 루트 경로 계산도 함께 갱신한다.

과거 릴리스 노트·원문·실험 기록의 단계명은 증거로 유지한다. 현재 기능 안내에서는 역할명 문서로 연결한다. 과거 문서를 현재 설계로 복제하지 않는다.

## 5. 호환성과 일괄 치환 금지

1. **저장소 내부**: 함수명·전역·타입·DOM ID·CSS·테스트·로그 파서·npm scripts·CI·문서를 같은 변경 단위로 갱신한다. 색상 코드 `#d4...`, 원문·해시·게임 ID는 치환하지 않는다.
2. **JS/Rust 통신**: `d4_optimize_parallel` → `optimize_crysta_build`, `resume_d4_optimization` → `resume_crysta_optimization` 등으로 양쪽을 동시에 변경한다. Tauri 등록, Native client, headless dispatcher/transport, 테스트의 모의 invoke도 포함한다. pause/cancel/dispose/hardware에도 같은 규칙을 적용한다.
3. **버전 있는 데이터**: `toram.d4-problem.v1`, checkpoint schema, fixture schema, `cpu-only.p7` 등은 단순 표시명이 아니다. 발행자·독자·캐시 서명을 열거하고 의미와 세대 번호를 보존한 새 이름으로 옮긴다. 이전 checkpoint의 수용/명시적 거부는 기존 호환성 계약을 확인해 결정하며 묵시적으로 재개하지 않는다.
4. **저장 계약**: BuildDraft, ScenarioContext, schema v2, 앱 식별자, 저장 키, 사용자 세팅 디렉터리는 이 정리의 대상이 아니다. runtime 키 개명이 저장 항목으로 유입되지 않는지 확인한다.
5. **호환 이름**: 내부의 구명칭 별칭은 원칙적으로 남기지 않는다. 외부 사용이나 저장된 데이터 읽기에 필요하다고 확인한 것만 이유·소비자·제거 조건을 목록화한다. 최종 단계명 잔존은 이력·검증 기준·명시한 호환 대상으로 한정한다.

## 6. 実装順序

아래는 작업 순서이며 새 단계 코드를 파일명에 붙이지 않는다.

1. **기준 고정**: Git 차이·미추적 파일·사용할 입력 fixture·현재 명령 결과를 기록한다. 파일/심볼/통신/환경변수/출력 문자열의 구→신 대응표와 소비자를 확정한다.
2. **검증 진입점 개명**: `test:regression`, `verify:architecture`, `verify:entry`, `verify:entry:dist`, `bench:optimization`, `bench:optimization:build`를 마련한다. 현행 `verify:r9`의 하위 검사와 타입 검사를 빠짐없이 한 번씩 실행한다. fixture의 normal/characterization 분류와 누락 검사를 유지한다. 환경변수 개명은 CI/벤치마크도 함께 갱신한다.
3. **최적화 명칭·위치 정리**: runtime JS/Rust, DOM/CSS, IPC, headless, 현재 문서를 관련 기능 단위로 변경한다. 동작 변경·파일 통합과 별도 차이로 남긴다.
4. **작은 통합 실행**: UI bootstrap과 Rust settings를 각각 독립적으로 통합한다. 논리적 책임 경계는 유지하고 고정 파일명을 요구하는 구조 검사를 새 배치에 맞춘다.
5. **스킬트리별 통합**: 원문·생성 원본·등록 순서·정의 선택·버프 표시·계산 결과를 비교하면서 9쌍을 한 쌍씩 통합한다. 단독 `-s5` 파일도 트리명으로 바꾼다. 출처 연결이나 dataStatus는 재판정 없이 변경하지 않는다.
6. **분류와 마무리**: 테스트/벤치마크 역할별 배치, 잔존 명칭 감사, 불필요해진 참조 제거를 수행한다. AGENTS·handoff·ai-context-guide·구조 감사의 참조를 실제 파일과 같은 변경에서 갱신한다.

각 변경은 개별 검증·차이 확인·되돌리기가 가능한 단위로 만든다. 실패 시 해당 단위의 변경만 되돌리고 사용자의 기존 차이를 되돌리지 않는다.

## 7. 検証計画

구현 시 명령 이름은 위 대응표로 갱신한다. 아래는 현재 존재하는 진입점이며 이번에 실행했다는 뜻이 아니다.

| 変更 | 必須検証 |
| --- | --- |
| 본 계획만 | `npm run ai:audit`, `git diff --check` |
| 명칭/구조 전반 | `npm run verify:r9` 1회, `npm run test:r0` 1회. 중첩 r2~r8은 별도 실행하지 않음. 정적 검사의 개명으로 동작 검증을 삭제하지 않음 |
| manifest/폴더 이동 | `npm run verify:r1a`, `npm run desktop:prepare`, `npm run verify:r1a:dist`, 실제 Worker 로딩과 브라우저/Tauri URL 해석. 복사형 prepare는 삭제된 구파일이 dist에 남을 수 있어 전용 빈 출력 위치 또는 안전하게 확인한 dist로 검증 |
| UI 통합 | DOM 준비 전후 한 번만 초기화, 기능 registry, 미리보기/정밀 시작, 입력 변경 시 폐기, 추천 적용 잠금, 업데이트 전 계산 종료. 해당 기존 테스트 사용 |
| Rust/IPC/세팅 | `cargo fmt --manifest-path src-tauri/Cargo.toml --check`, `cargo test --manifest-path src-tauri/Cargo.toml`, 필요한 clippy/빌드. 저장 목록·save/load/overwrite/delete, schema v2, 알 수 없는 이름·오류의 기존 검증 |
| 최적화 | evaluator/oracle/상한 property, JS/Rust parity, 실제 후보, Worker, Native pause/resume/cancel/deadline, 동점 ID, 잠금, checkpoint. R0에 포함된 검증은 반복하지 않고 부족한 Gate만 추가 |
| 스킬 통합 | `node tools/audit-stack-source-links.mjs --require-s1` 및 대상 트리·버프·콤보 회귀. 기본/stack-control 선택 결과, metadata, 실제 등록 순서의 변경 전후 비교 |
| 성능 회귀 | `npm run bench:d4:build` → `npm run bench:d4`의 `timing.totalMs`를 같은 입력·환경·예산으로 전후 비교. 최종 JS 재평가까지의 범위를 유지하고 상태·점수·동점 ID·upper/gap·메모리도 기록 |

구조 정리로 새롭게 모든 입력의 10초 exact를 주장하지 않는다. 성능 목표 달성을 판정할 때는 [정확성 계약](d4-exact-optimization-plan.md)의 cold 반복·P95 조건을 추가한다. 실제 WebView와 저장 E2E는 실제 환경에서 확인하며 `TORAM_E2E_CDP` 미지정 등의 SKIP을 통과로 세지 않는다.

구현 전 검사에서 기존 실패가 나오면 이번 변경에서 발생한 실패와 구분해 기록한다. 오래된 문구나 고정 경로를 이유로 검사 자체를 삭제하지 않는다.

## 8. 완료 조건과 이번 범위

- 같은 트리의 단계별 파일을 해소하고 통합 대상에 구파일/이중 로딩이 남지 않는다.
- 활성 코드·실행 진입점·현재 안내가 역할명으로 정렬되고 단계명 잔존은 이유를 명시한 이력/검증 기준/호환 대상뿐이다.
- 이름/배치에 의존하는 모든 소비자, CI, 생성기, 로더, Worker, Rust bin이 새 경로로 동작한다.
- 계산 결과·최적성 의미·저장 계약·실행 제어를 유지하고 필요한 Gate의 PASS/SKIP/미실행을 명시한다.
- 대상 파일 수, 역할별 진입점, 측정 조건이 있는 성능 비교를 기록하고 handoff를 12 KiB 이내로 갱신한다.

이번 작업은 읽기 조사와 이 계획 추가뿐이다. 계산/Rust/실기기 회귀나 성능 측정은 실행하지 않았으며 기존 기능의 정상성을 새로 인증하지 않았다.
