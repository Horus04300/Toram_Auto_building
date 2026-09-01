# R6 저장 계약 재설계 검증

R6는 베타 시기의 다섯 localStorage 키와 `toram-auto-build-setting` JSON을 폐기한다. 이전 데이터의 읽기·변환·백업 호환은 제공하지 않는다.

새 계약은 모두 `format: "toram-auto-build-document"`, `schemaVersion: 1`을 사용한다.

- `saved-build`: 이름 있는 빌드 파일. `BuildDraft`, `ScenarioContext`, 생성·수정 시각을 포함하며 Tauri 파일 Repository가 저장한다.
- `application-state`: 단 하나의 브라우저 저장 키 `toram.auto-build.application-state.v1`에 저장된다. 앱 설정(`appSettings`)과 자동 복원용 마지막 세션(`lastSession`)만 보유한다.
- UI 상태와 D4 실행 상태는 저장하지 않는다. Runtime 상태를 포함하지 않는 BuildDraft와 Scenario만 자동 복원한다.

`settings-repository.js`가 저장·불러오기·덮어쓰기·삭제·내보내기·가져오기·자동 복원을 모두 담당한다. build, skills, buffs, combo UI는 저장소를 직접 읽거나 쓰지 않는다. Rust는 새 `saved-build` 문서만 파일 목록·읽기·쓰기에 허용하며 기존 JSON은 목록에서 제외한다.

검증 명령:

```powershell
npm run verify:r6
node tools/test-tauri-native-storage-e2e.mjs
```

두 번째 명령은 실행 중인 Tauri WebView2 CDP 연결이 제공될 때 새 계약의 저장·중복 차단·덮어쓰기·불러오기·삭제를 실제로 검증한다.
