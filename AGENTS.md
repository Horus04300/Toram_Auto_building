# Repository AI instructions

이 저장소에서 작업하는 모든 AI 에이전트는 코드 수정, 상태 보고, 계획 수립 전에 다음 문서를 순서대로 끝까지 읽어야 한다.

1. docs/handoff/current-development-handoff.md
2. 스킬 데이터나 계산 규칙 작업이면 docs/handoff/skill-content-verification-runbook.md
3. 미구현 여부를 판단하거나 후속 구현을 하면 docs/verification/unimplemented.md

필수 원칙:

- 현재 상태의 단일 기준은 current-development-handoff.md, 실제 코드, 실행한 테스트 결과다.
- 기존 handoff 문서의 과거 수치나 “미완료” 표현을 현재 상태로 그대로 인용하지 않는다.
- 작업 시작 시 git status를 확인하고 사용자의 기존 변경을 보존한다.
- S1 출처 연결, S2~S5 계산 검증, 전투 상태 시뮬레이션을 서로 다른 완료 기준으로 구분한다.
- 추정으로 스킬 수치나 상한을 만들지 않는다. 원문 출처와 코드 연결을 확인한다.
- Windows 설치 경로와 사용자 세팅 저장 경로를 혼동하지 않는다.
  - 앱 설치: 현재 사용자 LocalAppData 아래의 공백 포함 제품명 폴더
  - 사용자 세팅: %LOCALAPPDATA%\ToramOnlineAutoBuildCalculator
- 사용자가 명시적으로 보류한 전투 피격 시뮬레이션과 콤보 후속 항목을 임의로 구현하지 않는다.
- 계산식, 저장 계약, 릴리스 상태 등 중요한 변경을 완료하면 current-development-handoff.md도 같은 변경에서 갱신한다.
- 상태를 보고할 때는 실행한 명령과 통과 결과를 근거로 제시한다.
