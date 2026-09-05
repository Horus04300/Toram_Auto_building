# Repository AI instructions

이 저장소에서 작업하는 모든 AI 에이전트는 코드 수정, 상태 보고, 계획 수립 전에 다음 문서를 순서대로 끝까지 읽어야 한다.

1. docs/handoff/current-development-handoff.md
2. D4 전역 최적화의 정확성·성능·후보 탐색 작업이면 docs/architecture/d4-exact-optimization-plan.md
3. 스킬 데이터나 계산 규칙 작업이면 docs/skill-tree-verification-standard.md
4. 미구현 여부를 판단하거나 후속 구현을 하면 docs/verification/unimplemented.md

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

토큰 절약 규칙:

- 위 필독 순서는 유지한다. 짧은 current-development-handoff.md를 먼저 읽고 작업에 해당하는 문서만 추가로 읽는다. 과거 이력 전체를 기본 컨텍스트에 넣지 않는다.
- 일반 파일 탐색은 `npm run ai:files`, 내용 검색은 `npm run ai:search -- "패턴" 경로`를 사용한다. 직접 실행할 때는 `rg --ignore-file .aiignore`를 붙인다. `.aiignore`는 도구 공통 자동 차단 파일이 아니다.
- 파일을 찾을 때는 `rg --files`, 일치 파일명만 필요하면 `rg -l`, 내용은 `rg -n`으로 범위를 좁힌 뒤 필요한 부분을 읽는다. 긴 출력이 잘리면 동일한 전체 읽기를 반복하지 않는다.
- 제외 대상도 작업에 필요하면 정확한 파일 경로를 지정해 읽거나 검색한다. 원문·fixture·계산 코드를 토큰 절약 명목으로 생략하지 않는다.
- 진입점·생성 파일 원본·검증 선택은 `docs/ai-context-guide.md`에서 필요한 항목만 확인한다. 같은 세션에서 변경되지 않은 문서를 다시 읽지 않는다.
- 문서·검색 설정만 바꿀 때는 `npm run ai:audit`와 `git diff --check`로 검증한다. 계산 변경에는 기존 S1/회귀 Gate를 유지하고, 중첩된 `verify:r*` 명령을 전부 반복 실행하지 않는다.
- 현재 handoff는 12 KiB 이하의 현재 상태·계약·링크로 유지한다. 상세 작업 로그는 해당 주제 문서에 기록한다.
- 현재 기능/릴리스 판정은 handoff 한 곳, 설계 문서는 불변 계약·Gate, unimplemented는 남은 결정·보류 범위만 관리한다. 완료된 항목은 후속 목록에서 제거하고, 실험 기록의 과거 상태를 현재형으로 복사하지 않는다.
