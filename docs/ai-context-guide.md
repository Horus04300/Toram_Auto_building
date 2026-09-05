# AI 컨텍스트 탐색 가이드

필독은 `AGENTS.md`와 `docs/handoff/current-development-handoff.md` 및 작업별 지정 문서다. 이 가이드는 필요한 행만 참고하며 매 작업 전체 읽기를 요구하지 않는다.

## 작업별 진입점

| 작업 | 먼저 볼 코드 | 추가 문서·검증 |
| --- | --- | --- |
| UI/입력 | `assets/js/ui-feature-registry.js`, `assets/js/build-draft-store.js`, 해당 `*-ui*.js` | `docs/architecture/current-webapp-feature-map.md`, 해당 기능 테스트 |
| 계산 조립 | `assets/js/application-use-cases.js`, `assets/js/calculation-policies.js` | 스킬 검증 기준, 영향받는 계산 회귀 |
| 계산식 | `assets/js/calculator.js`, `assets/js/stat-registry.js` | `docs/skill-tree-verification-standard.md`, 해당 원문·S5 테스트 |
| 스킬/콤보 | `assets/js/skill-effect-engine.js`, `assets/js/combo-sequence-engine.js`, 해당 `assets/js/data/skills/` 파일 | S1 감사 및 해당 트리 회귀; 미구현 판단 시 unimplemented 문서 |
| D4 | `assets/js/d4-execution-adapter.js`, `assets/js/d4-problem-compiler.js`, `assets/js/d4-global-optimizer.js` | `docs/architecture/d4-exact-optimization-plan.md`; 실행 제어는 `docs/architecture/d4-native-runtime-correction-plan.md` |
| Rust | `src-tauri/src/main.rs`, `src-tauri/src/tauri_commands.rs`, 해당 service/solver | 관련 Rust 테스트; 수식 변경이면 JS/Rust parity |
| 저장 | `assets/js/settings-repository.js`, `frontend/runtime/tauri-build-storage-adapter.ts`, `src-tauri/src/settings_repository.rs` | 현재 handoff의 저장 계약, snapshot/adapter/Rust 테스트 |
| 로딩/빌드 | `assets/js/app-entry.mjs`, `assets/js/legacy-script-manifest.mjs`, `tools/prepare-tauri-frontend.mjs` | `npm run verify:r1a`, 필요 시 desktop:prepare 및 dist 검증 |
| AI 문서/검색 | `.aiignore`, `AGENTS.md`, 이 문서 | `npm run ai:audit`, `git diff --check` |

## 검색 방법과 제외의 의미

```powershell
npm run ai:files
npm run ai:search -- "ResolveActiveBuffs" assets/js
rg -l --ignore-file .aiignore "Knight:11" assets/js tools
rg -n "version" package-lock.json
```

`.aiignore`를 Codex가 자동 적용한다고 가정하지 않는다. 이 저장소는 위 명령이 `rg --ignore-file .aiignore`를 호출하도록 연결했다. npm 검색 명령은 PATH의 ripgrep(`rg`)이 필요하다. 검색 일치가 없을 때 rg 종료 코드 1은 정상이다. 일반 `rg`와 다른 AI 도구에는 별도 적용이 필요하다. 기본 검색에서 제외해도 정확한 파일 경로로 직접 읽거나 검색할 수 있으며, 접근 권한이나 비밀 보호 장치가 아니다.

의존성·빌드 산출물, 바이너리, 대량 아이콘 매칭 결과, 잠금 파일을 기본 검색에서 제외한다. 아이콘 작업에는 이미지와 manifest를, 의존성 작업에는 lockfile을 직접 연다. `docs/sources/`, 스킬 등록 원본, 런타임 데이터, 회귀 fixture는 검색에 남긴다. `docs/`나 JSON 전체를 제외하지 않는다. `.gitignore`와 일반 개발자 검색 동작은 바꾸지 않았다.

## 생성물의 수정 위치

- `assets/js/tauri-build-storage-adapter.js`는 `frontend/runtime/tauri-build-storage-adapter.ts`에서 `npm run types:emit`으로 생성한다.
- `assets/js/data/skill-registration-metadata.js`의 원본은 `assets/source-data/skill-registration/`이고 생성기는 `tools/generate-skill-registration.mjs`다.
- `dist/`는 `npm run desktop:prepare`의 복사 산출물이다. 원본 `index.html`과 `assets/`를 수정한다.
- 다른 데이터는 생성물이라고 추정하지 않는다. 원문/런타임 데이터 중복은 출처 추적과 회귀에 필요할 수 있다.

## 구조 감사: 토큰을 늘리는 요인과 처리

2026-09-05 작업 시작 시 추적 파일 1,759개, assets 1,456개, docs 89개였다. 파일 수·바이트는 실제 청구 토큰이나 자동으로 읽히는 양이 아니다.

1. **필수 handoff에 이력 누적:** 85,902바이트에 R0~R9, D4 Gate/P/N/S 실험과 과거 테스트 수가 섞여 있었다. 짧은 현재 상태 문서로 교체했다. 오래된 AI 전달문·전체 이력 복사본·R1~R9 단계 보고서는 삭제했다. 현재 안내와 검증 코드에 있는 내용을 별도 완료 보고서로 반복하지 않는다.
2. **대량 리소스가 파일 목록에 노출:** 2,057,688바이트 폰트, 268,599바이트 아이콘 매칭 JSON 등이 있었다. 검색 프로필로 제외했다. 소스 증거는 유지한다.
3. **큰 파일과 전역 로더 의존:** `assets/js/d4-global-optimizer.js` 83,070바이트, `src-tauri/src/d4_native_solver.rs` 75,014바이트, `assets/js/optimizer.js` 59,082바이트였다. classic script manifest는 순서/전역 계약을 갖고 있어 한 기능을 이해할 때 여러 파일을 확인해야 한다. 이번에는 진입점 지도를 제공했다. 후속 기능 수정 시 책임 단위 추출과 명시적 import 전환을 검토하되 계산·동점·Worker 계약 회귀를 먼저 확보한다. 토큰 절약만을 위한 일괄 분할은 하지 않았다.
4. **중첩 검증:** `verify:r9`는 r8→r7→…→r2를 포함한다. r2~r9를 각각 실행하면 하위 검증과 로그가 반복된다. 필요한 최상위 검증 한 번과 영향받는 별도 테스트를 선택한다. `test:r0` 등 다른 묶음과의 중복도 확인한다. 필수 Gate 자체는 줄이지 않는다.
5. **원본과 배포 복사본 공존:** 빌드 준비가 assets 전체를 dist에 복사한다. dist는 이미 Git에서 제외돼 있었다. 새 검색 프로필에도 명시했다. 배포 리소스 축소는 로딩 경로 검증을 수반하는 별도 개선 사항이다.

측정은 `npm run ai:audit`로 재현한다. 기본 rg 검색과 AI 검색의 파일 수·바이트, handoff 크기, 필수 증거 노출·잡음 제외·문서 경로를 확인한다. 범용 토큰 환산 비율은 사용하지 않는다.

## 유지할 구현 경계

- TypeScript는 `frontend/`를 strict 검사하고 명시적 `any`를 금지한다. 기존 JS 전체를 임의로 `checkJs`에 편입하지 않는다. 외부 Port는 SettingsRepository·OptimizationRunner이며 계산 커널용 Gateway를 추가하지 않는다.
- Application은 Store에서 계산 입력을 읽는다. `ToramCalculationInputScope`는 명시 입력을 기존 커널에 전달하는 호출 중 스코프이며 호출 뒤 복원/제거한다. 이름만 보고 legacy로 삭제하지 않는다.
- 효과 엔진·콤보는 첫 유효 스킬 정의를, 버프 카드만 명시적 `preferStackControl` 정책으로 스택 보강 정의를 선택한다.
- UI 계산·저장은 Application을 거친다. 탭 재배치는 제목 문자열 대신 `data-ui-section`을 사용한다.
- D4 실행 Adapter는 Native 우선/Worker fallback과 제어만 담당하며 컴파일·후보 삭제·상한·정렬을 수행하지 않는다. 오래된 요청은 fallback을 시작하지 않는다. 일시정지·재개는 Native 세션에만 있고 Worker에 가짜 continuation을 만들지 않는다.
- Rust `main.rs`는 조립·명령 등록, `tauri_commands.rs`는 IPC, `d4_service.rs`는 작업/세션 수명, `settings_service.rs`는 저장 위임, `settings_repository.rs`는 검증·파일 접근을 담당한다. D4는 `spawn_blocking`을 사용하고 continuation은 최대 4개/oldest eviction을 유지한다.
- classic manifest, Native/Worker client, Settings File Repository Adapter는 실제 소비자가 있는 경계다. 전체 ESM 전환 전에 임의로 제거하지 않는다. 저장 포맷의 현재 기준은 handoff의 v2 계약이며 과거 v1 단계 보고서를 기준으로 되돌리지 않는다.

## 도구 근거와 적용 한계

2026-09-05 확인: [공식 AGENTS.md 문서](https://learn.chatgpt.com/docs/agent-configuration/agents-md)는 프로젝트 지침의 발견·합성 방식을 설명한다. [공식 설정 참조](https://learn.chatgpt.com/docs/config-file/config-reference)에서 `.aiignore` 자동 지원을 확인하지 못했다. 따라서 효과를 파일명 자체에 의존하지 않고 명시적 검색 명령과 지침으로 구현했다. 새 작업에서 갱신한 지침을 확인한다. 이미 대화에 입력된 긴 컨텍스트는 이 변경으로 제거되지 않는다.
