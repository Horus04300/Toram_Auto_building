# 입력 저장·복원 계약

BuildDraft/Scenario는 schema v2와 저장 키를 공유한다. 장비 종류·제련 선택지를 먼저 초기화한 뒤 저장값을 복원하고 화면 재초기화가 입력을 덮어쓰지 않게 한다.

- 새 빌드의 장비 옵션은 빈 목록이다. 수동 옵션·빈 목록·장비 종류/수치·제련을 그대로 보존한다.
- 자동 저장은 실제 입력 이벤트를 반영한다. 복원·탭 전환·재열기로 기본 옵션을 추가하지 않는다.
- 이미 저장된 중복 옵션이나 손실된 값을 추정해 정리/복구하지 않는다.
- JSON 가져오기/내보내기·앱 파일 저장·localStorage 자동 복원은 같은 문서 계약을 사용한다. 앱 설치 경로와 사용자 세팅 경로는 별개다.

## 검사

CODEX_PLAYWRIGHT_PATH를 지정하고 `node tools/verification/verify-session-restore-browser.mjs`를 실행한다. npm test -- browser가 웹 준비와 이 검사도 실행한다.

검사는 전체 BuildDraft/Scenario·빈 옵션·제련0/11·크리스타/잠금·스킬/버프/콤보/음식·타겟/거리/요구조건/금지를 비교한다. 방패와 듀얼/활/마법/두루마리/단검/맨손 조합, 탭 닫기·재열기·새로고침을 다룬다. 명시적 저장 flush로 입력 이벤트를 대체하지 않는다.

실제 앱의 파일 저장·재시작은 tools/verification/audit-desktop-e2e.mjs로 별도 검사한다. 마지막 실행 결과는 ../handoff/current-development-handoff.md를 따른다.
