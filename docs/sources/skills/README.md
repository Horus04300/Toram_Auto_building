# 스킬 원문 캐시

`skill_effect_source_links.json`에 등록된 원문을 로컬에 보관한 사본이다. 스킬 효과 데이터는 `sourceRef.file`과 `sourceRef.anchor`로 이 파일의 근거 문구를 직접 가리킨다.

- 갱신: `powershell -ExecutionPolicy Bypass -File tools/cache-skill-sources.ps1`
- 스택 정의 대조: `node tools/audit-stack-source-links.mjs`

`manifest.json`에는 수집 시각, 원문 URL, 파일 경로, SHA-256 해시가 기록된다. 해시가 다르면 원문을 의도적으로 갱신하지 않은 한 데이터 검증이 실패한다.

원문은 수집 시점의 참고 사본이다. 게임 패치로 내용이 바뀔 수 있으므로 갱신 후에는 반드시 대조 도구를 다시 실행한다.
