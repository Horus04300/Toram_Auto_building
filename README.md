# Toram Auto Building 개발 소스

`v1.2.1.html`은 기존 배포본 보존용 원본입니다. 새 기능은 분리된 개발판 `index.html`에서 작업합니다.

## 구조

- `index.html`: 개발판 진입점과 화면 마크업
- `assets/css/style.css`: 전체 스타일
- `assets/fonts/`: Pretendard v1.3.9 가변 WOFF2와 SIL OFL 라이선스
- `assets/js/data/`: 스킬트리와 크리스타 데이터
- `assets/js/crysta-ui.js`: 크리스타 입력·자동완성·장비 옵션 UI
- `assets/js/calculator.js`: 스탯과 전투 수치 계산
- `assets/js/optimizer.js`: 크리스타 추천·결과 렌더링
- `assets/js/status-points.js`: 스테이터스 포인트 제어
- `assets/js/skill-tree.js`: 스킬트리 시뮬레이터·저장 기능
- `assets/js/tabs.js`: 상단 탭 구성
- `assets/js/ui-bindings.js`: 화면 이벤트 연결 및 기능별 공개 API 호출
- `coryn_skill_icons/`: 개발용 스킬 아이콘 원본
- `tools/build-release.mjs`: 배포용 단일 HTML 생성기
- `Versions/`: 생성된 배포판 보관 위치

## 개발

`index.html`을 브라우저에서 열어 확인합니다. 기능별 JavaScript는 위 순서대로 로드되므로, 다른 파일의 함수를 사용하려면 해당 파일보다 뒤에 배치해야 합니다.

## 단일 파일 배포판 생성

Node.js 18 이상에서 다음 명령을 실행합니다.

```powershell
node tools/build-release.mjs vM.m.p
```

명령의 버전값은 제목·화면 헤더·`application-version` 메타데이터에 자동 반영됩니다. 명령은 CSS·JavaScript·스킬 아이콘을 하나의 HTML로 합쳐 `Versions/v1.2.2.html`을 만듭니다. 아이콘과 Pretendard 가변 폰트는 Base64 데이터 URL로 포함되므로 배포판은 외부 폴더나 인터넷 연결 없이 동작합니다. 폰트 재배포 조건은 `assets/fonts/OFL.txt`에 보관합니다.