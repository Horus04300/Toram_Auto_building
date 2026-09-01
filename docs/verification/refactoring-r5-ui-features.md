# R5 UI 기능별 분리 검증

R5는 UI 프레임워크나 화면 디자인을 바꾸지 않고, 기존 classic-script 호환 경계 안에서 기능별 UI 진입점을 분리한다.

- `build-ui-controller.js`: 장비·크리스타·옵션 입력 이벤트
- `optimizer-ui-controller.js`: 효율 탭과 D4 취소·일시정지·재개 같은 비동기 화면 제어
- 기존 `skill-tree.js`, `active-buff-ui.js`, `combo-ui.js`, `build-file-storage.js`: 각각 skills, buffs, combo, settings 기능의 공개 UI 진입점
- `ui-feature-registry.js`: build, skills, buffs, combo, optimizer, settings의 명시적 UI 기능 목록

탭 재배치는 제목 문자열이 아니라 `data-ui-section` 식별자를 사용한다. 계산은 `ToramApplication` API로 조립하며, 저장 UI는 `ToramApplication.Settings`만 호출한다. 저장 계약·Tauri 어댑터는 UI 파일 밖에 남긴다.

검증 명령:

```powershell
npm run verify:r5
```

이 검증은 기능별 진입점의 로딩 순서, 제목 기반 탭 탐색 제거, 계산·저장 Application 경계, D4 비동기 제어 분리를 검사한다. 동작 회귀는 `npm run test:r0`로 별도 확인한다.
