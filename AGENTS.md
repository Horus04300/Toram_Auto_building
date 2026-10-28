# Repository AI instructions

수정·상태 보고·계획 전에 다음 문서를 순서대로 끝까지 읽는다.

1. `docs/handoff/current-development-handoff.md`
2. 크리스타 정확성·성능·후보 탐색: `docs/architecture/crysta-optimization-contract.md`
3. 스킬 데이터·계산 규칙: `docs/skill-tree-verification-standard.md`
4. 미구현 판단·후속 구현: `docs/verification/unimplemented.md`

필수 규칙:

- 시작 시 `git status` 확인. 사용자 변경·데이터·Git 기록을 보존한다.
- 현재 상태는 handoff·실제 코드·실행한 테스트로 판단한다. 과거 수치·미완료 표현을 현재 상태로 복사하지 않는다. 상태 보고에는 명령과 결과를 제시한다.
- S1 출처 연결, S2~S5 계산 검증, 전투 상태 시뮬레이션은 별개다. 스킬 수치·상한은 추정하지 않고 원문과 코드 연결을 확인한다.
- 보류된 피격 시뮬레이션·콤보 후속은 임의 구현하지 않는다.
- 앱 설치는 LocalAppData 아래 공백 포함 제품명 폴더, 사용자 세팅은 `%LOCALAPPDATA%\ToramOnlineAutoBuildCalculator`다.
- 계산·저장 계약·릴리스 등 중요 변경 시 handoff도 갱신한다. 현재 기능/릴리스는 handoff, 설계 문서는 불변 계약·Gate, unimplemented는 남은 결정·보류만 관리한다. 완료 항목은 후속 목록에서 제거한다.
- handoff는 12 KiB 이하로 유지하고 상세 근거는 해당 주제 문서에 둔다. 문서는 현재 계약·검증 방법·미결정만 유지하며 완료 작업·수정 전후·단계별 로그를 누적하지 않는다. 원문·fixture·추출/실험 근거는 보존한다.

탐색·검증:

- 진입점·원본·검증 선택은 `docs/ai-context-guide.md`의 해당 항목만 확인한다. 변경되지 않은 문서나 과거 이력 전체를 반복해서 읽지 않는다.
- 파일 목록은 `rg --files --hidden --ignore-file .aiignore`, 내용은 `rg -n --hidden --ignore-file .aiignore -- "패턴" 경로`로 찾는다. `--files` → `-l` → `-n`으로 범위를 좁힌다. `.aiignore`는 자동 접근 차단이 아니며 필요한 원문·fixture·제외 파일은 정확한 경로로 읽는다. 잘린 전체 출력을 반복하지 않는다.
- 문서·검색 설정만 변경하면 `node tools/verification/audit-ai-context.mjs`, `git diff --check`. 코드는 관련 회귀, 최종 통합은 `npm test`로 검사한다. 계산 변경은 기존 S1/회귀 Gate를 유지하고 중첩 검사를 반복하지 않는다.
