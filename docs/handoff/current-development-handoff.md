# 현재 개발 상태 및 AI 인수인계

- 기준일: 2026-08-22
- 저장소: Horus04300/Toram_Auto_building
- 제품: 토람 온라인 대미지 계산기 및 빌드 시뮬레이터
- 현재 브랜치: main
- 역할: 동료 개발자와 동료 AI가 가장 먼저 확인할 현재 상태의 단일 인계 기준

## 1. 반드시 먼저 이해할 결론

1. 기존 브라우저 계산기는 Tauri v2 기반 Windows 데스크톱 앱으로 전환되었다.
2. 현재 앱 버전은 0.5.0이며 Windows NSIS 설치 파일이 GitHub Pre-release로 공개되어 있다.
3. 이름을 붙인 세팅 JSON은 정확히 %LOCALAPPDATA%\ToramOnlineAutoBuildCalculator 에 저장한다. settings 하위 폴더를 추가하지 않는다.
4. localStorage는 마지막 작업 상태 자동 복원용이고, 네이티브 JSON은 저장·불러오기·덮어쓰기·삭제용이다.
5. 전역 S1 출처 연결 감사 결과는 427/427이다. 이것은 모든 스킬의 S2~S5 계산과 모든 전투 상태 시뮬레이션이 완전하다는 뜻이 아니다.
6. 피격 시뮬레이션은 이 계산기의 우선 목표가 아니므로 사용자가 보류했다. 다음 스킬 한정 효과, 사용 후 소멸, MP 흐름, 직접 피해와 버프 계산이 우선이다.
7. 과거 인계 문서의 Blade 9/24, Martial 1/22 같은 수치는 초기 감사 당시 기록이다. 현재 상태 판단에 그대로 사용하지 않는다.

## 2. 문서 우선순위

1. 이 문서
2. 실제 코드와 현재 실행한 감사·회귀 테스트
3. docs/handoff/skill-content-verification-runbook.md의 검증 절차
4. docs/verification/unimplemented.md의 항목별 후속 목록
5. docs/handoff/skill-content-coverage-handoff.md의 역사적 초기 기준선

과거 문서는 출처와 작업 맥락을 보존하기 위해 남겼다. 숫자와 완료 상태가 충돌하면 최신 코드와 실행 결과를 우선한다.

## 3. Git, 버전, 배포 상태

- 릴리스 구현 커밋: 046ea64 release: Tauri Windows app v0.5.0
- 태그: v0.5.0, 대상 커밋 046ea64
- package.json, src-tauri/Cargo.toml, src-tauri/tauri.conf.json 버전: 0.5.0
- 제품명: Toram Online Auto Build Calculator
- 앱 식별자: com.toramonline.autobuildcalculator
- Release: https://github.com/Horus04300/Toram_Auto_building/releases/tag/v0.5.0
- 상태: Draft 아님, Pre-release
- 자산: Toram.Online.Auto.Build.Calculator_0.5.0_x64-setup.exe 및 SHA-256 파일
- 설치 파일 SHA-256: 49FF2632623146B20C9C92212EEBD2C04FD856AD2F0BD22A56291BC68179E3C5
- 현재 설치 파일은 코드 서명이 없다. 서명 배포에는 별도 인증서가 필요하다.

이 인계 문서는 릴리스 태그 이후 main에 추가되는 문서다. v0.5.0 태그를 이 문서 커밋으로 이동하지 않는다.

## 4. Tauri 데스크톱 구조

주요 파일:

- src-tauri/src/main.rs: 네이티브 세팅 저장 명령과 검증
- src-tauri/tauri.conf.json: 창, 번들, NSIS 설정
- src-tauri/Cargo.toml: Rust 패키지
- tools/prepare-tauri-frontend.mjs: 기존 웹 프론트엔드를 dist로 준비
- assets/js/tauri-build-storage-adapter.js: 프론트와 Rust 명령 연결
- assets/js/build-setting-snapshot.js: 전체 세팅 스냅샷 형식
- assets/js/build-file-storage.js: 저장 오버레이 UI와 백업 입출력

명령:

- npm run desktop:dev
- npm run desktop:build
- npm run desktop:build:exe

산출물:

- NSIS: src-tauri/target/release/bundle/nsis/Toram Online Auto Build Calculator_0.5.0_x64-setup.exe
- 실행 파일: src-tauri/target/release/toram-online-auto-build-calculator.exe

NSIS는 currentUser 설치이며 WebView2 downloadBootstrapper를 사용한다. 실제 무인 설치·실행·제거를 검증했고 제거 뒤에도 사용자 세팅 폴더가 보존되는 것을 확인했다.

## 5. 저장 계층 계약

### 경로

- 설치 폴더: LocalAppData 아래 제품명 Toram Online Auto Build Calculator 폴더
- 사용자 세팅: %LOCALAPPDATA%\ToramOnlineAutoBuildCalculator
- 두 경로는 의도적으로 다르다. 설치 제거가 사용자 세팅을 삭제하지 않게 하기 위한 분리다.

### Rust 명령

src-tauri/src/main.rs에 다음 명령이 등록되어 있다.

- settings_directory
- list_settings
- save_setting
- load_setting
- overwrite_setting
- delete_setting

앱이 저장소에 접근하면 세팅 폴더를 자동 생성한다. 파일명은 빈 값, 80자 초과, 제어 문자, Windows 금지 문자, 끝의 점·공백, 예약 장치명, 경로 이동을 차단한다. 기존 파일도 JSON이 아니거나 심볼릭 링크·비정규 파일이면 거부한다.

### 스냅샷 범위

- toram-auto-building.build-state.v1
- toram-auto-building.skill-tree.v1
- toram-auto-building.skill-tree-ui.v1
- toram-auto-active-buffs-v1
- toram.combo-sequence.v1

JSON은 format toram-auto-build-setting, schema 1을 검증한다.

- localStorage: 마지막 작업 상태 자동 복원
- 네이티브 JSON: 이름을 붙인 저장, 목록, 불러오기, 덮어쓰기, 삭제
- JSON 내보내기·불러오기: PC 이전과 수동 백업

기존 File System Access API, showDirectoryPicker, IndexedDB 폴더 핸들 방식은 제거됐다.

## 6. 계산기 및 UI 주요 변경

### 상태와 입력 연동

- 스테이터스, 장비, 스킬, 버프, 콤보를 자동 저장·복원한다.
- 이미 장비·스킬 탭에 입력한 값을 콤보에서 다시 요구하지 않게 연결했다.
- 버스터 블레이드의 오라 블레이드 레벨, 방패 제련치 같은 값도 기존 입력을 사용한다.
- 결과의 부동소수점 노출을 정리했고 damage_p 표시는 액티브 버프%로 바꿨다.

### 스테이터스와 장비

- 수동 공격/거리 유형, 스킬 계수, 스킬 상수, 스탯 보정 추가 입력을 제거했다.
- 약점 속성으로 공격 체크박스와 빈 특수 스킬/패시브 조건 패널을 제거했다.
- 주무기에 맨손을 추가했다. 맨손이면 무기 ATK와 제련치는 0, 안정률은 1이다.
- 속성 각성과 마력 속성을 분리했다.
  - 속성 각성은 약점 속성 공격을 가능하게 해 기본 속성 유리 25% 조건을 만든다.
  - 마력 속성은 약점 속성 공격 자체를 만들지 않는다.
  - 둘 다 INT 비례 속성 보너스 계산 대상이다.
- 명칭 속성데미지를 속성에 유리로 변경했다.
- 최대 MP 공식: floor(100 + 레벨 + 총 INT × 0.1 + 고정 최대 MP 보정)

### 스킬과 버프

- 양손검 오라 블레이드는 지속 버프가 아니라 일회성 다음 공격 효과라 액티브 지속 버프 목록에 표시하지 않는다.
- 다음 스킬에만 적용되는 효과와 사용 후 소멸을 중요 상태로 취급한다.
- 듀얼 브링어 자체는 대상 쇠약과 무관하다. 둘은 마법 크리티컬 계산의 독립 요소다.
- 선택 스킬의 발도 공격 지원 여부를 스킬 프로필에서 자동 반영한다.

### 콤보

- 스킬 아이콘을 가로로 연결하고 선택한 순번을 한 줄의 편집 UI에 반영한다.
- 데스크톱 드래그 및 포인터·터치 드래그로 순서를 바꾼다.
- 기점 스킬은 콤보 효과를 설정하지 못하며 불필요한 안내 문구는 제거했다.
- 현재 MP보다 필요 MP가 크면 해당 스킬에서 콤보를 취소한다.
- 취소 전은 정상 계산하고 취소된 스킬과 이후 스킬의 피해·버프는 계산하지 않는다.
- 콤보 상태도 전체 세팅에 저장한다.

콤보 태그의 상세 구현·부분 구현·미구현 목록은 docs/verification/unimplemented.md를 참고하되 현재 코드와 테스트로 재확인한다.

## 7. 스킬 검증 상태 해석

- S1: 카탈로그 스킬과 원문 출처 연결
- S2: 유형, 무기 조건, 입력 조건 정리
- S3: 계산 가능한 수식과 규칙 데이터화
- S4: 공통 계산 엔진과 상태 흐름 연결
- S5: 대표 사례와 회귀 테스트

현재 전역 사실:

- 명령: node tools/audit-stack-source-links.mjs --require-s1
- 결과: 카탈로그 캐시 32, 출처 연결 정의 437, 스택 정의 53, S1 427/427

여러 스킬트리에 S3~S5 작업과 tools/test-*-s5.mjs 및 S3/S4-S5 회귀 스크립트가 추가됐다. 개별 S5 통과는 모든 시간축·피격·저항·AI 행동을 시뮬레이션한다는 뜻이 아니다.

화경의 파괴자 스킬 레벨에 따른 무기 공격력 증가처럼 다른 스킬 레벨을 참조하는 규칙도 검증 대상이었다. 현재 적용 여부를 답할 때 해당 데이터와 회귀 테스트를 함께 확인한다.

## 8. 보류된 경계

상세 목록은 docs/verification/unimplemented.md에 있다. 다음은 사용자 결정이다.

- 피격 시뮬레이션은 핵심이 아니므로 우선 구현하지 않는다.
- 받는 피해, 피격 여부, 저항 시간 같은 전투 이벤트 의존 효과는 metadata 또는 partial로 남을 수 있다.
- 다음 스킬 한정 효과, 사용 후 소멸, MP 소비·회복, 콤보 취소, 직접 피해와 버프는 우선한다.
- Rampage는 통상 공격 변화보다 공격 MP 회복 증가가 실용적으로 더 중요하나 이미 구현된 범위를 임의로 제거하지 않는다.
- 콤보 포인트·레벨, 일부 고급 태그와 피격 의존 규칙은 별도 승인 없이 확장 구현하지 않는다.

문서 문구만 복사해 미구현으로 단정하지 말고 엔진, 데이터, 테스트를 검색해 재판정한다.

## 9. 검증 명령

핵심 JavaScript 검증:

- node tools/audit-stack-source-links.mjs --require-s1
- node tools/test-build-setting-snapshot.mjs
- node tools/test-tauri-build-storage-adapter.mjs
- 영향받는 tools/test-*-s5.mjs 및 S3/S4-S5 테스트

전환 최종 검증 당시 JavaScript 테스트 파일 34개가 통과했다. 네이티브 환경이 없으면 Tauri E2E는 안전하게 skip한다.

Rust 및 빌드:

- cargo fmt --manifest-path src-tauri/Cargo.toml --check
- cargo test --manifest-path src-tauri/Cargo.toml
- npm run desktop:build

Rust 단위 테스트 3/3이 통과했다. 실제 네이티브 E2E에서 저장, 중복 차단, 덮어쓰기, 불러오기, 삭제, 백업 가져오기를 확인했다.

변경 전후 필수:

- git status --short
- git diff --check
- S1 감사와 영향받는 회귀 테스트
- 저장 변경이면 Rust 단위·스냅샷·어댑터 테스트
- 배포 변경이면 NSIS 설치·실행·제거와 사용자 데이터 보존

## 10. 다음 작업자가 하면 안 되는 것

- 과거 Blade 9/24 같은 숫자를 최신 상태로 보고하지 않는다.
- S1 427/427을 전체 계산 또는 전투 시뮬레이션 완성으로 표현하지 않는다.
- 기존 입력으로 알 수 있는 값을 콤보에서 다시 묻지 않는다.
- 세팅 경로 뒤에 settings 폴더를 붙이지 않는다.
- 설치 폴더와 사용자 데이터 폴더를 같게 만들지 않는다.
- v0.5.0 태그를 후속 문서나 기능 커밋으로 이동하지 않는다.
- 원문에 없는 수치나 상한을 추정하지 않는다.
- 보류된 피격 중심 엔진을 별도 승인 없이 구현하지 않는다.
- 사용자 작업 트리를 초기화하거나 무관한 변경을 덮어쓰지 않는다.

## 11. 다음 우선순위

1. v0.5.0 Pre-release 실사용 피드백과 재현 가능한 버그 수정
2. 필요 시 Windows 코드 서명 인증서 준비
3. 반복 가능한 Windows 빌드·릴리스 자동화
4. docs/verification/unimplemented.md에서 사용자가 선택한 항목만 구현
5. 중요한 상태 변경마다 이 문서 갱신
