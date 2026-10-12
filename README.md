# Toram Auto Building 개발 소스

현재 개발 버전은 Tauri v2 데스크톱 앱 `v0.7.3`입니다. 계산기 원본은 루트의 `index.html`과 `assets/`에서 관리하고 빌드할 때 `dist/`로 복사합니다.
.
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
- `assets/js/optimization-results.js`: 크리스타 추천·결과 렌더링
- `assets/js/status-points.js`: 스테이터스 포인트 제어
- `assets/js/skill-tree.js`: 스킬트리 시뮬레이터·저장 기능
- `assets/js/tabs.js`: 상단 탭 구성
- `assets/js/ui-bootstrap.js`: 화면 이벤트 연결 및 기능별 공개 API 호출
- `assets/icons/skills/`: Coryn 기반 스킬 트리 아이콘
- `assets/game-data/ui/`: 이름 미정의 인게임 UI 스프라이트 원본
- `assets/source-data/coryn-skill-simulator/`: Coryn 아이콘 매니페스트·생성 원본
- `assets/source-data/game-icon-skill-duplicates.json`: 삭제 확정된 채굴·스킬 아이콘 매칭 기록
- `assets/source-data/game-icon-skill-match-candidates.json`: 남은 채굴 아이콘의 상위 스킬 후보표
- `assets/source-data/skill-registration/`: 427개 스킬 등록 메타데이터의 생성 원본
- `tools/generate-skill-registration.mjs`: 등록 메타데이터 재생성 도구
- `tools/read-skill-source.mjs`: 트리별 스킬 원문 조회 도구
- `tools/audit-game-icon-matches.ps1`: 채굴 게임 아이콘과 스킬 아이콘의 후보 매칭 감사 도구
- `docs/skill-data-schema.md`: 전투 스킬 데이터 계약
- `docs/skill-tree-verification-standard.md`: S1~S5 검증 기준
- `docs/handoff/current-development-handoff.md`: 현재 구현·검증·배포 상태의 단일 인계 기준
- `docs/ai-context-guide.md`: AI 작업별 진입점·검색 제외·토큰 소모 구조 감사 (`npm run ai:audit`로 검증)

## 브라우저 프론트엔드 개발

`index.html`을 브라우저에서 열어 확인합니다. 기능별 JavaScript는 위 순서대로 로드되므로, 다른 파일의 함수를 사용하려면 해당 파일보다 뒤에 배치해야 합니다.

## Tauri 데스크톱 개발

Windows에서는 Rust `stable-msvc`, Microsoft C++ Build Tools와 WebView2가 필요합니다.

```powershell
Set-Location -LiteralPath 'C:\Users\조연우\Documents\GitHub\Toram_Auto_building'
npm install
npm run desktop:dev
```

폴더를 옮기면서 `src-tauri/target/`도 함께 옮겼다면 먼저 `npm run desktop:clean`을 실행합니다. Tauri 권한 파일의 이전 절대 경로가 남아 있는 Tauri·업데이터·앱 패키지의 개발·릴리스·Windows x64 릴리스 캐시만 정리합니다. 나머지 의존성 캐시와 계측 기록, 사용자 세팅은 유지하며, 다음 개발 실행이나 빌드에서 해당 패키지를 다시 컴파일합니다.

모든 npm 명령은 저장소 루트를 기준으로 실행하므로 폴더를 다시 옮겨도 `package.json`의 경로를 수정할 필요가 없습니다. 다른 폴더에서 실행하려면 `npm --prefix "C:\Users\조연우\Documents\GitHub\Toram_Auto_building" run desktop:dev`처럼 현재 저장소 경로를 지정합니다.

| 명령 | 용도 |
| --- | --- |
| `npm run desktop:clean` | 폴더 이동 후 Tauri·업데이터·앱 빌드 캐시 정리 |
| `npm run desktop:prepare` | TypeScript 런타임 생성 및 `dist/` 준비 |
| `npm run desktop:dev` | 개발 앱 실행 |
| `npm run desktop:build` | NSIS 설치 파일 빌드 |
| `npm run desktop:build:exe` | 설치 없는 실행 파일 빌드 |
| `npm run types:check` | TypeScript 타입 검사 |
| `npm run types:emit` | 저장·업데이트 어댑터 JavaScript 생성 |
| `npm run verify:architecture` | 구조·계약·어댑터 검사 |
| `npm run verify:entry` | 소스 로딩 진입점 검사 |
| `npm run verify:entry:dist` | 준비된 배포본 로딩 검사 (`desktop:prepare` 후) |
| `npm run test:regression` | 전체 계산 회귀 검사 |
| `npm run test:regression:normal` | 정상값 회귀 검사 |
| `npm run test:regression:characterization` | 기존 동작 회귀 검사 |
| `npm run bench:optimization:build` | Native 계측 실행 파일 빌드 |
| `npm run bench:optimization` | 최적화 계측 (`bench:optimization:build` 후) |
| `npm run ai:files` | AI 검색용 파일 목록 |
| `npm run ai:search -- "패턴" 경로` | AI 검색용 내용 검색 |
| `npm run ai:audit` | AI 검색 설정·문서 감사 |

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

## 생성 원본과 빌드 산출물

- `assets/source-data/`, `assets/game-data/`, `docs/sources/skills/`는 아이콘·게임 자료·검증 원문이므로 정리 대상으로 취급하지 않습니다.
- `dist/`, `src-tauri/target/`, `src-tauri/gen/`은 재생성 가능한 로컬 산출물이며 Git에서 추적하지 않습니다.
- `node_modules/`는 `npm install`로 복구할 수 있지만 현재 개발 명령에 사용하므로 일반 정리에서는 유지합니다.
