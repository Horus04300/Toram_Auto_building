# 공통 웹 화면

웹과 데스크톱이 같은 화면 원본을 사용합니다. 데스크톱 전용 기능은 ../desktop/에 있습니다.

| 위치 | 고치는 내용 |
| --- | --- |
| index.html | 화면 구조·입력 요소 |
| src/ui/ | 화면 표시·이벤트 |
| src/application/ | 입력 상태·사용자 동작·계산 조립 |
| src/calculation/ | JS 계산식·효과 적용·최종 결과 평가 |
| src/optimization/ | 추천 입력 준비·Rust/WASM 연결·실행 선택 |
| src/storage/ | 공통 저장 형식·자동 복원·JSON 가져오기/내보내기 |
| src/data/ | 스킬·게임 규칙 정의 |
| src/domain/, src/contracts/ | TypeScript 타입·경계 계약 |
| public/ | CSS·폰트·아이콘·발행된 아이템/보스 데이터 |

실행은 저장소 루트에서 npm run web:dev, 배포본 생성은 npm run web:build입니다. index.html의 assets/... URL은 개발 서버와 배포 도구가 원본 위치에 연결합니다. src/app-entry.mjs가 진입점, src/classic-script-manifest.mjs가 classic 스크립트 로딩 순서입니다.

build/web/와 build/desktop/는 생성물이므로 직접 수정하지 않습니다.
