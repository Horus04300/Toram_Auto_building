# 역할 기준 구조 정리 결과

- 완료 정리: 2026-10-01. 계획: [역할 기준 리팩토링](../architecture/role-based-refactoring-plan.md).
- 기존 작업 트리의 계산·정수 내림·최적화·계측·v0.7.2 변경을 기준으로 진행했다. 사용자 변경을 초기화하거나 커밋하지 않았다.
- 기능·릴리스의 현재 기준은 [handoff](../handoff/current-development-handoff.md)다. 이 문서는 이번 변경과 검증 기록이다.

## 변경

| 범위 | 결과 |
| --- | --- |
| 런타임 JS/MJS | 91→81개. UI 등록/이벤트 연결을 `ui-bootstrap.js`로 통합하고 스킬트리의 본체/보강 9쌍을 통합 |
| 스킬트리 데이터 | 38→29개. 스킬 ID·수식·원문·dataStatus·기본/스택 제어 정의 선택을 유지 |
| Rust | 15→14개. `settings.rs` 안에 SettingsService/SettingsRepository를 함께 배치 |
| 최적화 | JS/Rust의 `optimization/`에 compiler/solver/evaluator/client/runtime/service 역할별 배치. Native/Worker·실행 adapter·추천 적용의 책임은 유지 |
| 도구 | tests/application·skills·optimization, verification, benchmarks, support로 분류. 단계별 파일명·npm 명령·환경변수를 역할명으로 교체 |
| 로딩/빌드 | classic manifest, Worker 상대 import, Node import/루트 탐색, Rust 경로 모듈·개발용 bin·실험용 독립 crate, Tauri 등록, CI 참조 갱신 |
| 배포 원본 | prepare가 소스에서 제거된 파일을 dist/assets에서 제거. 검증된 출력 디렉터리의 일반 파일만 삭제하며 사용자 세팅은 접근하지 않음 |
| 문서 | 현재 계약·구조도·AI 가이드·AGENTS·README를 새 경로/명령으로 갱신. 원문·과거 계측 JSON·재현 fixture 내용은 보존 |

런타임 소스는 합계 106→95개로 11개 줄었다. 검증 도구·문서·스냅샷 추가는 이 수치에 포함하지 않는다. 전체 경로 대응은 [경로 변경 기록](role-refactoring-paths.json)에 있다.

## 동작과 호환성

- 모든 스킬 등록 그룹의 우선순위를 등록기에 명시했다. 보강 파일이 다른 파일과 떨어져 로드됐던 순서까지 `all()` 결과에 보존한다. 트리별 `:calculation-rules`는 계산 정의 묶음 이름이며 검증 완료를 뜻하지 않는다.
- 변경 전 작업 트리의 전체 정의·기본 선택·stack-control 선택을 JSON으로 직접 비교해 동일함을 확인했다. 그 결과의 SHA-256·개수를 fixture로 남겼고 `test-definition-precedence.mjs`가 검증한다.
- Guard 및 평타 AMPR 테스트는 이전처럼 보강 정의만 검사하는 범위를 명시했다. 이 테스트의 기대값은 변경하지 않았다. 전체 앱의 정의 선택은 별도 전체 스냅샷과 브라우저 회귀로 확인한다.
- `test-ui-bootstrap.mjs`는 DOM 준비 전/후, 중복 준비 알림, 설정/업데이트 registry, 단일 이벤트 연결을 검증한다.
- 최적화 schema는 `toram.crysta-*`, IPC는 `crysta_*` 및 `*_crysta_optimization`, runtime 키는 `crystaOptimization`으로 변경했다. JS/Rust/Worker/headless/모의 IPC를 함께 갱신했다.
- checkpoint v9의 새 이름은 `toram.crysta-native-search-checkpoint.v9`다. 과거 `toram.d4-native-search-checkpoint.v9`는 동일한 v9 의미를 갖는 입력으로만 수용하고 새 이름으로 출력한다. 새 Rust 테스트가 이전 이름 복원·진행 상태·exact 점수/ID를 비교한다. 이전 정책 v4~v8 거부 검사는 유지한다.
- 보존된 재현/계측 fixture의 옛 schema와 단계명은 역사적 증거다. 이를 읽는 테스트의 schema 상수도 유지한다. 원문·릴리스 기록·실험 보고서·사전 계획의 단계명은 현재 명명 규칙의 예외다.
- 위 checkpoint 읽기 호환성은 구형 v9 입력 지원을 종료한다고 별도 결정하고 소비자를 조사하기 전까지 유지한다. 내부 구명칭 함수/파일/npm 별칭은 남기지 않았다.
- 앱 저장 format/schema v2·세팅 경로·제품 식별자·버전은 변경하지 않았다. 스킬 S1~S5는 출처/계산 검증 기준으로 유지한다.

계획의 Rust `mod.rs` 대신 실행 파일과 개발 도구의 기존 경로 모듈 방식을 유지했다. 동일 소스를 복사해 쓰는 독립 감사 crate가 있으므로 추가 전달 모듈 없이 역할별 폴더를 공유하도록 했다. 조건부 후보였던 Build UI, 동적 점수/초기해, 업데이트 책임, 대형 solver/evaluator 추가 병합은 하지 않았다.

## 검증

| 실행 | 결과 |
| --- | --- |
| 변경 전 `verify:r9`, `test:r0` | 구조 통과. 기존 74개 fixture 실행, 73 PASS + 저장 실기기 1 SKIP |
| `npm run verify:architecture` | 타입/계산/Application/Store/UI/저장/실행/Native/런타임/역할별 배치 통과 |
| `npm run test:regression` | 76개 fixture 실행, 75 PASS + 저장 실기기 1 SKIP. solver oracle·상한 property·JS/Rust parity·실제 Worker·입력/재개·스킬·저장 회귀 포함 |
| `node tools/verification/audit-stack-source-links.mjs --require-s1` | 원문 캐시 32개, 출처 연결 정의 437개, 스택 정의 53개, S1 427/427 |
| `cargo fmt --manifest-path src-tauri/Cargo.toml --check` | 통과 |
| `cargo test --manifest-path src-tauri/Cargo.toml` | 모든 바이너리 타깃 통과, 실패 0. 타깃 간 공유 모듈 테스트의 중복 실행을 별도 기능 개수로 세지 않음 |
| `cargo clippy --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings` | 통과 |
| `npm run verify:entry`, `npm run desktop:prepare`, `npm run verify:entry:dist` | 원본·dist의 76개 classic script 로딩 순서와 브라우저/Tauri URL 검사 통과 |
| `node tools/verification/verify-role-layout.mjs` | 단계명 파일 제거, 상대 import, Worker 실제 경로, 단일 bootstrap, 29개 트리 통과 |
| `npm run desktop:build:exe` | v0.7.2 Windows release 실행 파일 빌드 통과. 설치/배포하지 않음 |
| `npm run ai:audit`, `git diff --check` | 문서 경로·필수 증거·크기·공백 검사 통과 |
| JS/MJS/CJS 전체 `node --check` | 210개 통과 |
| `node tools/verification/audit-browser-e2e.mjs` | 실제 headless Edge 15개 검사 통과. 예외·실패 리소스 0. 실제 Worker의 8개 고정 슬롯 exact 포함 |
| `node tools/verification/verify-update-browser.mjs` | 실제 브라우저의 웹 미지원·시작 확인·동의/취소·다운로드 중 편집·최종 flush 통과. Native 설치는 모의 처리 |
| `node tools/verification/verify-food-browser.mjs` | 실제 Edge의 5칸·단축 선택·중복·레벨·복원·계산·기존 세팅·모바일 통과 |

브라우저 도구는 설치된 Playwright 경로를 `CODEX_PLAYWRIGHT_PATH`로 지정해 실행했다. `TORAM_E2E_CDP` 미지정으로 실제 Tauri 저장 E2E는 SKIP이다. 실제 설치/제거·업그레이드·서명 릴리스는 이번 작업 범위에서 실행하지 않았다.

기존 타입 경계 검사는 폐기된 DTO 이름을 요구하고 있었고, Native 구조 검사는 `SETTING_SCHEMA_VERSION` 정규식이 `LEGACY_SETTING_SCHEMA_VERSION`의 일부에도 일치했다. 각각 현행 DTO와 공개 v2/이전 v1 상수를 명시하도록 수정했다. 계약 검사를 삭제하거나 저장 버전을 낮추지 않았다.

## 성능 확인

`bench:optimization:build` 후 `bench:optimization -- --repeats 3 --max-ms 120000`으로 UI 제외·최종 JS 재평가 포함 시간을 비교했다. 최초 병행 측정 대신, 보존한 이전 소스·바이너리의 해시를 검증하고 회귀 작업과 겹치지 않게 이전/이후를 각각 새 프로세스로 3회 실행했다.

| 항목 | 변경 전 | 변경 후 |
| --- | --- | --- |
| 완료 | 3/3 exact | 3/3 exact |
| 중앙 totalMs | 5893.47 | 5682.40 |
| 평균 totalMs | 5863.27 | 5684.88 |
| 점수 | 1123905.36 | 1123905.36 |
| 선택 빌드/옵션 | 동일 | 동일 |

입력 파일 해시도 동일하다. 환경은 Node v24.17.0, Windows x64, Ryzen 7 9800X3D다. 원시 요약: [측정 기록](role-refactoring-measurements.json). 이 한 입력에서는 시간 회귀를 관측하지 않았다. 3회 결과를 일반적인 속도 향상이나 모든 입력의 10초 exact로 해석하지 않는다. peak memory 비교는 별도 수행하지 않았다.
