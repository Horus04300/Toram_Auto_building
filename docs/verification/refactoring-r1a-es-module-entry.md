# R1a ES Module 진입점

## 변경 경계

```text
index.html
  └─ assets/js/app-entry.mjs                (유일한 type="module" 진입점)
       └─ legacy-script-manifest.mjs        (순서 계약, 71개 경로)
            └─ 기존 classic JavaScript files (순차 로드, window 호환 유지)

D4 Worker
  └─ d4-optimizer-worker.js
       └─ importScripts(...)                (별도 classic Worker 경계, 변경 없음)
```

- `index.html`의 다수 classic `<script>` 태그를 단일 ES Module 진입점으로 교체했다.
- `app-entry.mjs`는 manifest의 파일을 `async = false` classic script로 하나씩 로드한다. 다음 파일은 앞 파일의 `load`가 끝난 뒤에만 삽입하므로 기존 의존 순서를 보존한다.
- manifest는 기존 HTML에 있던 71개 경로와 순서를 유일한 프런트엔드 로딩 계약으로 가진다.
- Tauri 준비 단계는 `assets/`를 그대로 `dist/assets/`로 복사하므로 `.mjs` entry와 manifest도 같은 상대 경로로 배포된다.

## 의도적으로 남긴 legacy 의존성

이번 단계는 로딩 진입점만 바꾸며, 기존 classic 스크립트를 ESM으로 직접 import하지 않는다. 현재 다음 전역 계약은 그대로 남아 있다.

- 데이터: `TORAM_SKILL_*`, `SKILL_TREE_DATA`, `ToramSkillEffectRegistry`
- 계산: `ToramSkillEffects`, `ToramStatRegistry`, `ToramCalculationKernel`, `ToramBuildEvaluator`, `simulateWithCrystas`, `getBaseContext`
- D4: `ToramD4*` 네임스페이스, `Worker`, `__TAURI__`
- UI·상태: `ToramApp`, `ToramActiveBuffs`, `ToramComboUi`, `skillSimulatorState`, `localStorage` 및 일부 `window.*` 함수·캐시

따라서 R1a는 모듈 기반 **진입점**이지 계산·UI의 실제 ESM 모듈화가 아니다. R1b 이후 각 책임을 명시적 import/export로 옮길 때에만 해당 전역을 제거한다.

## 검증

```powershell
npm run verify:r1a
npm run test:r0
npm run desktop:prepare
npm run verify:r1a:dist
npm run desktop:build:exe
```

2026-08-31 실행 결과:

- source와 `dist`에서 browser URL 및 `https://tauri.localhost/` URL의 71개 순차 경로를 모두 검증했다.
- D4 Worker URL과 Worker 내부 `importScripts` 경계를 검증했다.
- R0 fixture는 65/65 성공했다. 네이티브 저장 E2E 1건은 기존과 같이 `TORAM_E2E_CDP` 미설정으로 `SKIP`이다.
- Tauri no-bundle 빌드가 실행 파일 생성까지 성공했다.
