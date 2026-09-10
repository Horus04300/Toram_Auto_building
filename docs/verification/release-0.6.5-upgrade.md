# 0.6.5 릴리스와 실제 버전 상승 검증

## 릴리스 변경

- 권갑 STR→ATK, 선풍창·발도검 MATK 스탯 계수를 근거에 맞춰 JS/Rust에 동시 반영하고 Native 계산 캐시 버전을 v2로 변경했다.
- 빈 잠금 크리스타 슬롯을 유지하면서 추천을 적용한다.
- 빠른 추천 실패를 불가능 증명과 구분하고, 실패·취소 시 이전 추천 상세를 비운다.
- 크리스타 잠금/해제 아이콘을 상태에 맞춰 표시한다.
- package/Cargo/Tauri 및 두 lockfile 버전을 0.6.5로 통일했다.

## 2026-09-10 공개 전 검증

- `npm run verify:r9`: PASS.
- `npm run test:r0`: 69개 프로세스 종료 성공. 68개 통과, 실제 native 저장 E2E 1개는 `TORAM_E2E_CDP` 미설정으로 SKIP.
- `cargo fmt --manifest-path src-tauri/Cargo.toml --check`: PASS.
- `cargo test --locked --manifest-path src-tauri/Cargo.toml`: 79개 통과.
- `cargo clippy --locked --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`: PASS.
- `node tools/audit-stack-source-links.mjs --require-s1`: S1 427/427 통과.
- `npm run desktop:prepare`, `node tools/release-version.mjs`: PASS.
- `node tools/verify-update-browser.mjs`: 실제 Edge 화면 PASS, native 설치는 mock.
- `npm run ai:audit`: PASS.

로그는 `src-tauri/target/release-r0-0.6.5.log`, `release-rust-0.6.5.log`에 보관한다. GitHub Actions의 서명 NSIS 빌드·공개 자산 검증 후 Latest 공개를 진행한다.

## 실제 업데이트 Gate

0.6.4 공개 설치본에서 0.6.5 Latest 감지→사용자 동의→실제 다운로드·서명 검증→NSIS 설치→자동 재시작→버전 확인 및 named build/자동 복원/업데이트 설정 보존을 확인한다. 이 절차의 실행 결과는 공개 후 추가 기록한다. 현재 이 문서만으로 실제 버전 상승 통과를 주장하지 않는다.
