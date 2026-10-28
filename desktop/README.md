# Tauri 데스크톱

Windows 앱 전용 기능을 소유합니다. 화면 원본은 ../web/, 추천 알고리즘은 ../engine/에서 공유합니다.

| 위치 | 역할 |
| --- | --- |
| src/main.rs, tauri.conf.json | 앱 조립·창·패키징 설정 |
| src/optimization/ | Native 작업·병렬 실행·취소/재개 수명 |
| src/settings.rs, src/update_service.rs | 파일 저장·업데이트 |
| adapters/optimization-client.js | 공통 화면에서 Native 추천 호출 |
| adapters/saved-build-storage.ts | 이름 있는 캐릭터 빌드의 파일 저장 연결 |
| adapters/update.ts, adapters/update/ | 업데이트 연결·동의·화면 제어 |
| tsconfig.json | 어댑터 JS 생성 설정 |

명령은 저장소 루트에서 npm run desktop:dev / desktop:build를 실행합니다. EXE만 빌드하려면 desktop:build에 -- --no-bundle을 전달합니다. Tauri hook이 tools/prepare-frontend.mjs desktop을 직접 실행해 WASM·TS·프론트엔드를 준비합니다. frontendDist는 ../build/desktop입니다.

TS 출력은 ../build/generated/desktop/, 앱에 포함되는 화면은 ../build/desktop/, Cargo 출력은 target/입니다. 생성물을 직접 고치지 않습니다. 폴더 이동 후 캐시 경로 오류가 나면 Cargo의 해당 manifest/package 캐시를 정리하고 다시 빌드합니다.

사용자 저장 위치 %LOCALAPPDATA%\ToramOnlineAutoBuildCalculator는 이 소스 폴더와 별개입니다.
