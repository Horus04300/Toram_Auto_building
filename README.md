# Toram Auto Building 개발 소스

`v0.2.1.html`은 기존 배포본 보존용 원본입니다. 새 기능은 분리된 개발판 `index.html`에서 작업합니다. 현재 데스크톱 개발 기준선은 `v0.5.0`입니다.

## 구조

- `index.html`: 개발판 진입점과 화면 마크업
- `assets/css/style.css`: 전체 스타일
- `assets/fonts/`: Pretendard v1.3.9 가변 WOFF2와 SIL OFL 라이선스
- `assets/js/data/`: 스킬트리·전투 스킬 카탈로그·크리스타 데이터
- `assets/js/data/skill-combat-catalog.js`: 전투 대상 427개 스킬과 원문 출처 연결
- `assets/js/data/combo-rule-data.js`: 사용자 제공 게임 내 콤보 태그 규칙
- `assets/js/data/skill-effect-data.js`: 스킬 효과·MP·공격·버프·상태 전이 정의
- `assets/js/skill-effect-engine.js`: 제한된 조건식과 스킬 상태 전이 해석
- `assets/js/skill-data-validator.js`: 스킬 데이터 커버리지·정합성 검사
- `assets/js/crysta-ui.js`: 크리스타 입력·자동완성·장비 옵션 UI
- `assets/js/calculator.js`: 스탯과 전투 수치 계산
- `assets/js/optimizer.js`: 크리스타 추천·결과 렌더링
- `assets/js/status-points.js`: 스테이터스 포인트 제어
- `assets/js/skill-tree.js`: 스킬트리 시뮬레이터·저장 기능
- `assets/js/tabs.js`: 상단 탭 구성
- `assets/js/ui-bindings.js`: 화면 이벤트 연결 및 기능별 공개 API 호출
- `assets/icons/skills/`: Coryn 기반 스킬 트리 아이콘
- `assets/game-data/ui/`: 이름 미정의 인게임 UI 스프라이트 원본
- `assets/source-data/coryn-skill-simulator/`: Coryn 아이콘 매니페스트·생성 원본
- `assets/source-data/game-icon-skill-duplicates.json`: 삭제 확정된 채굴·스킬 아이콘 매칭 기록
- `assets/source-data/game-icon-skill-match-candidates.json`: 남은 채굴 아이콘의 상위 스킬 후보표
- `tools/build-release.mjs`: 배포용 단일 HTML 생성기
- `tools/read-skill-source.mjs`: 트리별 스킬 원문 조회 도구
- `tools/audit-game-icon-matches.ps1`: 채굴 게임 아이콘과 스킬 아이콘의 후보 매칭 감사 도구
- docs/skill-data-schema.md: 전투 스킬 데이터 계약
- Versions/: 생성된 단일 HTML 배포판 보관 위치

## 개발

`index.html`을 브라우저에서 열어 확인합니다. 기능별 JavaScript는 위 순서대로 로드되므로, 다른 파일의 함수를 사용하려면 해당 파일보다 뒤에 배치해야 합니다.

## Tauri 데스크톱 개발

Windows에서는 Rust `stable-msvc`, Microsoft C++ Build Tools와 WebView2가 필요합니다.

```powershell
npm install
npm run desktop:dev
```

Windows NSIS 설치 파일을 빌드하려면 다음 명령을 사용합니다.

```powershell
npm run desktop:build
```

설치 파일 없이 실행 파일만 빌드하려면 `npm run desktop:build:exe`를 사용합니다.

빌드 전 `tools/prepare-tauri-frontend.mjs`가 기존 `index.html`과 `assets/`를 `dist/`에 준비합니다. 계산기 원본은 계속 루트의 웹 소스에서 관리합니다.

이름을 붙인 세팅 JSON은 `%LOCALAPPDATA%\ToramOnlineAutoBuildCalculator`에 저장됩니다. 폴더는 앱에서 자동 생성하며, `localStorage`는 직전 작업 상태의 자동 복원에 계속 사용합니다.

- `저장`·`불러오기`·`덮어쓰기`·`삭제`: 앱의 네이티브 세팅 폴더 사용
- `JSON 내보내기`·`JSON 불러오기`: 다른 PC 이전과 별도 백업용
- NSIS 설치본: `src-tauri/target/release/bundle/nsis/`
- 설치 없는 실행 파일: `src-tauri/target/release/toram-online-auto-build-calculator.exe`

현재 사용자용 NSIS 설치 폴더와 세팅 폴더는 서로 분리되어 있으며, 앱을 제거해도 세팅 JSON은 보존됩니다.

## 단일 파일 배포판 생성

Node.js 18 이상에서 다음 명령을 실행합니다.

```powershell
node tools/build-release.mjs vX.Y.Z
```

명령의 버전값은 제목·화면 헤더·`application-version` 메타데이터에 자동 반영됩니다. 명령은 CSS·JavaScript·스킬 아이콘을 하나의 HTML로 합쳐 `Versions/v0.4.0.html`을 만듭니다. 아이콘과 Pretendard 가변 폰트는 Base64 데이터 URL로 포함되므로 배포판은 외부 폴더나 인터넷 연결 없이 동작합니다. 폰트 재배포 조건은 `assets/fonts/OFL.txt`에 보관합니다.