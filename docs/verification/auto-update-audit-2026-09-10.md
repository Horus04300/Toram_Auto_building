# 자동 업데이트 검증 — 2026-09-10

현재 작업 트리의 업데이트 코드와 공개 배포 자산을 검증했다. 시작 시 기존 계산 코드·검증 도구·handoff 변경을 확인하고 보존했다. 제품 코드는 수정하지 않았다.

## 실행 결과

| 명령/검증 | 결과 |
| --- | --- |
| `node tools/test-updates.mjs` | PASS: 메타데이터, 자동 확인 실패의 조용한 처리, 동의 거부, 진행 표시, 저장/서명 실패 시 설치 차단, 재시도, 동시 요청 차단, 실행/일시정지 계산 동의, 최종 재저장·UI 잠금 해제 |
| `node tools/test-update-release.mjs` | PASS: 소스·lockfile·태그 버전 불일치 및 잘못된 공개키 차단 |
| `node tools/test-build-setting-snapshot.mjs` | PASS: 업데이트 설정 저장 계약과 설치 전 strict flush |
| `cargo test --manifest-path src-tauri/Cargo.toml update_service -- --nocapture` | updater Rust 단위 테스트 3개 PASS; 나머지 테스트는 필터 제외 |
| `npm run desktop:prepare` | PASS: TypeScript 생성과 현재 소스 dist 준비 |
| `node tools/verify-update-browser.mjs` | 실제 Edge PASS: 웹에서 사용 불가, 시작 알림, 릴리스 노트의 텍스트 표시, 일시정지 계산 유지/동의, 다운로드 중 입력 편집, 최신 입력 저장. Native 다운로드·설치는 mock |
| 공개 Latest manifest 및 설치 파일 다운로드 | 성공: version `0.6.4`, platform `windows-x86_64` |
| `src-tauri/target/debug/verify_updater_artifact.exe src-tauri/tauri.conf.json src-tauri/target/update-audit-2026-09-10/installer.exe src-tauri/target/update-audit-2026-09-10/installer.exe.sig` | PASS: 공개 설치 파일을 현재 앱 공개키와 manifest 서명으로 검증 |
| 같은 검증기에 설치 파일의 1024번 바이트를 반전한 사본 입력 | `InvalidSignature`, 비정상 종료로 거부됨: PASS |

브라우저 실행 시 `CODEX_PLAYWRIGHT_PATH`는 번들 런타임의 `dependencies/node/node_modules/playwright`로 지정했다. 화면 증거는 `dist/update-ui-check.png`, 공개 자산과 변조 사본은 `src-tauri/target/update-audit-2026-09-10/`에 있다. 설치 파일을 실행하지 않았다.

공개 확인 경로: https://github.com/Horus04300/Toram_Auto_building/releases/latest/download/latest.json

최초 다운로드는 샌드박스 소켓 제한으로 실패했으며, 네트워크 권한을 적용한 재실행에서 다운로드 및 서명 검증이 성공했다. 초기 실패는 제품 서명 오류가 아니다.

## 판정과 미실행 범위

실행한 회귀·화면·공개 자산 서명 검증에서 기능 결함은 발견하지 못했다. 현재 소스와 공개 Latest가 모두 0.6.4이므로 같은 버전에서는 새 업데이트가 없는 것이 정상이다.

실제 Tauri 프로세스에서 vN→vN+1 감지·다운로드·설치·재시작 및 설치 전후 named build/자동 복원 데이터 보존은 이번에 실행하지 않았다. 전체 자동 업데이트 완료로 판정하지 않는다. 신규 릴리스 공개, 버전 변경, 사용자 설치 교체는 수행하지 않았다. 전체 R9/R0와 Rust 전체 테스트도 이번 범위에서 재실행하지 않았다.
