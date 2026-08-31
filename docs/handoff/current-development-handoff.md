# 현재 개발 상태 및 AI 인수인계

- 기준일: 2026-08-31
- 저장소: Horus04300/Toram_Auto_building
- 제품: 토람 온라인 대미지 계산기 및 빌드 시뮬레이터
- 현재 브랜치: main
- 역할: 동료 개발자와 동료 AI가 가장 먼저 확인할 현재 상태의 단일 인계 기준

## 1. 반드시 먼저 이해할 결론

1. 기존 브라우저 계산기는 Tauri v2 기반 Windows 데스크톱 앱으로 전환되었다.
2. 현재 개발 버전은 0.6.0이다. 공개된 Windows NSIS 설치 파일은 이전 v0.5.0 GitHub Pre-release이며, v0.6.0 설치 파일은 아직 생성·공개하지 않았다.
3. 이름을 붙인 세팅 JSON은 정확히 %LOCALAPPDATA%\ToramOnlineAutoBuildCalculator 에 저장한다. settings 하위 폴더를 추가하지 않는다.
4. localStorage는 마지막 작업 상태 자동 복원용이고, 네이티브 JSON은 저장·불러오기·덮어쓰기·삭제용이다.
5. 전역 S1 출처 연결 감사 결과는 427/427이다. 이것은 모든 스킬의 S2~S5 계산과 모든 전투 상태 시뮬레이션이 완전하다는 뜻이 아니다.
6. 피격 시뮬레이션은 이 계산기의 우선 목표가 아니므로 사용자가 보류했다. 다음 스킬 한정 효과, 사용 후 소멸, MP 흐름, 직접 피해와 버프 계산이 우선이다.
7. 과거 인계 문서의 Blade 9/24, Martial 1/22 같은 수치는 초기 감사 당시 기록이다. 현재 상태 판단에 그대로 사용하지 않는다.

## 2. 문서 우선순위

1. 이 문서
2. 실제 코드와 현재 실행한 감사·회귀 테스트
3. docs/skill-tree-verification-standard.md의 검증 절차
4. docs/verification/unimplemented.md의 항목별 후속 목록

숫자와 완료 상태가 충돌하면 최신 코드와 실행 결과를 우선한다. 초기 S1 누락 수치를 담았던 두 과거 인계 문서는 2026-08-22 저장소 정리에서 제거했다.

## 3. Git, 버전, 배포 상태

- 릴리스 구현 커밋: 046ea64 release: Tauri Windows app v0.5.0
- 태그: v0.5.0, 대상 커밋 046ea64
- package.json, package-lock.json, src-tauri/Cargo.toml, src-tauri/Cargo.lock, src-tauri/tauri.conf.json 버전: 0.6.0
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
- assets/source-data/skill-registration/: 427개 등록 메타데이터를 생성하는 동료 견본 원본
- tools/generate-skill-registration.mjs: 위 원본에서 등록 메타데이터 재생성

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
- 장비·외부 버프 옵션 선택에는 VIT/VIT%, 최대 HP/%, 최대 MP, 공격 MP 회복/%, 물리/마법 내성, DEF/MDEF·회피/명중·HP/MP 자연회복의 고정/% 값을 포함한다. 이 값은 기존 스냅샷 저장 계약으로 그대로 저장·복원된다.
- 설치본의 Tauri 리소스 로더가 공백 포함 스킬 아이콘 경로를 불러오지 못하므로, 아이콘 디렉터리와 모든 참조에 공백 없는 `*_Skills` 경로를 사용한다. 스킬 트리·버프·콤보가 같은 아이콘 데이터를 사용한다.
- 최대 MP 공식: floor(100 + 레벨 + 총 INT × 0.1 + 고정 최대 MP 보정)
- 스테이터스 포인트는 현재 캐릭터 레벨의 레벨업분(레벨당 2pt)과 계정 공유 플레이어 레벨 훈장분을 분리한다. 훈장은 최고 패러미터가 공식 최대 레벨을 달성했다고 보고 Lv.5부터 10레벨마다 +5pt를 적용한다. 현재 공식 상한 Lv.325에서는 훈장 +165pt이며, 낮은 레벨 캐릭터 설계에도 이 분량을 반영한다.
- `assets/js/official-level-cap.js`는 공식 공지 목록에서 실제 `Lv상한 개방`만 비동기로 재확인하고, 개방 예정 공지는 제외한다. 조회 실패 시 마지막 확인값 또는 번들된 공식 Lv.325를 유지한다. 상태 요약 툴팁에서 적용 상한과 훈장 포인트를 확인할 수 있다.

### 스킬과 버프

- 양손검 오라 블레이드는 지속 버프가 아니라 일회성 다음 공격 효과라 액티브 지속 버프 목록에 표시하지 않는다.
- 스택형 버프의 기본 정의와 스택 보강 정의가 같은 ID를 공유해도, 버프 UI는 스택 보강 정의를 우선해 카드 하나만 표시한다.
- 다음 스킬에만 적용되는 효과와 사용 후 소멸을 중요 상태로 취급한다.
- 듀얼 브링어 자체는 대상 쇠약과 무관하다. 둘은 마법 크리티컬 계산의 독립 요소다.
- 일진강풍 활성 시 발도위력%는 ATK%와 기본 무기 공격력으로, 발도위력+는 ATK로 각각 변환하며, 기본 무기 공격력 증가는 무기 ATK%·재련 보정 전에 적용한다. 발도검·선풍창의 소수 스탯 계수와 원문 대미지식의 각 곱연산은 단계마다 내림한다. 활성 중 재시전 무풍은 콤보·결과 탭에서 공격으로 계산한다.
- 선택 스킬의 발도 공격 지원 여부를 스킬 프로필에서 자동 반영한다.

### 콤보

- 스킬 아이콘을 가로로 연결하고 선택한 순번을 한 줄의 편집 UI에 반영한다.
- 데스크톱 드래그 및 포인터·터치 드래그로 순서를 바꾼다.
- 기점 스킬은 콤보 효과를 설정하지 못하며 불필요한 안내 문구는 제거했다.
- 현재 MP보다 필요 MP가 크면 해당 스킬에서 콤보를 취소한다.
- 충전은 태그 스킬의 기본 MP를 저장해 이후 비용에 우선 사용하고, 새 충전은 이전 저장분을 덮어쓴다. 콤보 종료 시 남은 저장 MP를 정산하며 후속 4개 스킬의 피해 감소는 누적한 뒤 10%~150% 공통 상한을 적용한다.
- 집념은 MP 부족으로 취소하기 전에 부족 MP 100당 최대 HP 10%를 HP 대체 비용으로 계산한다.
- 심안은 절대 명중과 콤보 위치당 명중 +10을 타격 플래그·콤보 결과에 반영한다. 상태이상 저항 시간 자동 판정은 보류한다.
- 취소 전은 정상 계산하고 취소된 스킬과 이후 스킬의 피해·버프는 계산하지 않는다.
- 트리별 정의 배열의 빈 슬롯은 콤보 목록·프로필 조회에서 제외해 탭 초기 렌더가 중단되지 않게 한다.
- 계산 효과가 없는 액티브 버프를 켜도 콤보 계산은 빈 효과로 처리한다. 계산 오류가 발생해도 콤보 아이콘 체인은 유지한다.
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
- node tools/test-combo-tags.mjs
- 영향받는 tools/test-*-s5.mjs 및 S3/S4-S5 테스트

2026-08-24 원문 대미지식 반영 기준 네이티브 저장 E2E를 제외한 JavaScript 테스트 파일 49/49개가 통과했다. 네이티브 환경이 없으면 Tauri E2E는 안전하게 skip한다.

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

1. 현재 연결된 ATK·MATK·마법 크리티컬·조건부 대미지 계층을 사용자 제공 원문과 경계값 회귀로 계속 대조한다. 마법 크리티컬 데미지는 `100 + floor((최종 물리 크뎀 - 100) × 반영률)`이며, 듀얼 브링거 활성·INT>STR이면 쇠약과 무관하게 `2.5% × 레벨`을 더한다. 컨버전의 무기·INT MATK 보정은 MATK% 뒤의 MATK(+)로 더한다. 무기 MATK 반영률은 지팡이·마도구 100%, 권갑 50%, 그 외 0%를 사용한다. 듀얼소드 서브 무기 ATK%·재련·안정률의 각 곱연산도 항별 내림한다. 원문에 없는 수치를 추정하지 않고, UI·상태 엔진에 없는 항목은 제외한다.
2. D4 전역 최적화의 10초 `exact` 목표는 `docs/architecture/d4-exact-optimization-plan.md`의 Gate·분기·안전성 계약을 먼저 따른다. 이 작업은 학습 모델이 아니라 결정적 Pair Frontier·잔여 Utility 지배·상관관계 보존 상한·분기 한정 개선이며, 어떤 최적화도 전수조사/oracle·상한 property·실제 425개 성능 게이트를 통과하기 전에는 활성화하지 않는다.
3. D4 Gate 0 기준선(2026-08-25): 실제 425개 물리 근거리 fixture를 새 Node 프로세스에서 10회 측정했다. 10,000ms 예산에서 exact 0/10, bounded 10/10, compile+search P95 10,152.0ms(외부 프로세스 시작 포함 P95 10,239.5ms), 인증 gap 38.008%~39.385%였다. 이 수치는 다음 Pair Frontier·residual·상관관계 상한 개선의 비교 기준이며, 현재 exact 목표 충족으로 표기하지 않는다.
4. D4 Gate A(2026-08-25): Utility 의존성 정책 d4-utility-dependency.v1을 추가했다. 조건 없는 MAXHP만 residual 포화 후보로 분류하고, MAXMP→AMPR, AMPR 통상/듀얼소드, 크리티컬 점수·제약, ASPD→행동속도는 원값 보존으로 고정했다. 시나리오가 HP/MP 비례 조건을 metadata로 선언하면 해당 축 포화를 금지한다. 이 단계는 후보 삭제·상한·추천 결과를 아직 바꾸지 않는다.
5. D4 Gate B(2026-08-25): d4-supply-difficulty.v1로 실제 425개 후보의 단독 패키지 공급을 측정했다. 부족 fixture에서 HP·ASPD는 단독 충족 후보가 각각 290·762개지만 MAXMP·AMPR·평타 크리티컬은 0개라 부위 결합이 필요하다. safeResidualDominance는 모든 구조·원값·동점 증거가 있을 때만 proven을 반환하며, 아직 Pareto 삭제에는 연결하지 않았다.
6. D4 Gate C(2026-08-25): d4-pair-partition.v1이 세 Pair 분할을 원시·Pareto 뒤 후보 수와 단일 Pair Utility 충족으로 결정적으로 비교한다. 실제 Utility 부족 425개 fixture에서는 세 분할 모두 큰 lazy-box 분기이며, 최대 prepared Pair 2,590,656인 방어구+무기/추가+특수가 선택됐다. 사용자 가설 분할은 고정 채택하지 않는다.
7. D4 Gate D(2026-08-25): 8,192개 이하의 작은 Pair는 완결 Pareto Frontier를 만들어 초기 하한에 연결했다. 큰 Pair의 24×24 lazy seed는 oracle은 통과했지만 실제 425개에서 하한을 올리지 못하고 1,250회 평가만 추가했으므로 기본 보류(lazy-deferred)로 유지한다. 후보 삭제·안전 상한·exact 판정은 바꾸지 않았고, 큰 Pair 활성화는 Gate E 상한 검증 뒤에만 재검토한다.
8. D4 Gate E 1차(2026-08-25): Pair 상관관계 2×2~4×4 분할 상자를 small exhaustive oracle과 실제 425개 envelope 단조성 19,732건으로 감사해 상한 위반 0건을 확인했다. 그러나 독립 초기 큐 분기 실험의 5초 gap은 기준 44.900%보다 45.056%~45.262%로 개선되지 않았다. 따라서 기본 Worker·캐시·추천 경로에는 활성화하지 않고, 다음 Gate E에서 계산식 경계 또는 실제 Pair 프로필 기반의 더 강한 상한을 검토한다.
9. D4 Gate E 2차(2026-08-25): 실제 상한을 이용한 bound-guided 초기 분할도 oracle은 통과했지만 5초 gap 47.115%~48.470%로 기준보다 나빴다. 실제 Pair 프로필 전체 물질화는 두 Pair 478만 조합에 생성 약 11.6초, 비교 100만회 제한 Pareto 약 31초가 걸리고도 불완전했다. 그러므로 두 방식 모두 기본 Worker에는 채택하지 않으며, 다음 후보는 선형 시간·고정 메모리 요약 상한으로 한정한다.
10. D4 Gate E 3차(2026-08-25): 고정 메모리 스트리밍 Pair envelope은 478만 조합을 약 114.9ms에 순회하고 small oracle을 통과했으나, 루트에만 적용되어 후속 상자가 다시 느슨해졌다. 실제 5초 gap은 47.271%~47.321%로 기준보다 나빠 기본 Worker에는 채택하지 않는다. 필터를 분기 이후에도 보존하는 Pair 상자 노드는 별도 안전·성능 Gate가 필요하다.
    - Gate E 4차(2026-08-28): CRIT 2-bucket Pair filter를 자식 CandidateTree node까지 보존해 실제 Pair envelope을 재계산하는 실험은 small oracle exact·동점 회귀를 통과했지만, 실제 425개 물리 근거리 5초에서 depth 1은 방문 노드 3개·17,033회 평가·gap 189.389%, root-only fallback은 방문 노드 2개·17,029회 평가·gap 207.488%였다. 개별 부위 tree가 pair pivot-sum 관계를 표현하지 못해 child마다 Pair 재순회가 필요하고, filter를 잃으면 root filter별 공간이 중복되는 것이 원인이다. 실험 코드는 제거했으며 Worker·캐시·추천에는 채택하지 않는다. Gate E는 안전성 검증 및 성능 불채택으로 종료하고, 다음 개선은 Gate F 병목으로 분리한다.
    - Gate 0부터 Gate E까지의 배경, 측정, 안전 계약, 실패 가설, 다음 설계 검토는 docs/handoff/d4-gate0-to-gatee-worklog.md를 함께 참조한다.
11. D4 Gate F(2026-08-28, 종료): 선택형 `collectSearchProfile`로 S7 실제 425개 exact를 계측했고, 계측 포함 1,015,239ms에서 상한 평가 12,895,255회·487.4초와 완성 조합 평가 8,573,588회·328.1초가 우세했다(중첩 inclusive 시간이라 합산 금지). `evaluateAggregateSummary`는 full aggregate와 같은 대미지·hard constraint를 보존하면서 중독·도구팁·상세 결과 생성을 생략하는 상한 전용 경로로 채택했다. 반대로 leaf summary는 long exact 985,639ms로 기존 921,871ms보다 느려 제거했고, 후보 rank 분할은 5초 gap 75% 한계를 넘어 제거했다. 기존 `splitDimensions` 1/2/3/4의 단발 5초 비교 gap은 41.117% / 41.877% / 45.333% / 48.776%로 기본값 2를 바꿀 일관된 근거가 없었다. 최종 채택본 long exact는 점수 14,097, 방문 4,477,218, 평가 26,208,511, bound prune 12,643,673, 완성 조합 9,102,384, compile 112.4ms, solve 1,177,836ms였다. 따라서 10초 exact에는 117.8배 작업량 감소가 필요하다. Frontier 준비·큐는 주 병목이 아니며, 16 논리 코어 완전 선형 가정의 단순 Worker 분산도 73.6초 하한이라 목표를 충족할 수 없다. F의 점진 경로는 종료하고, 다음은 Pair-native 등 실제 결합을 보존하는 새 노드 표현의 별도 oracle·상한 property·10회 P95 Gate다. evaluator stage 1, stage 2 oracle, Pair Frontier, Browser Worker 회귀를 통과했다.
    - 사용자 후속 결정(2026-08-28): 10초 달성 여부와 별개로 사용할 수 있는 병렬화를 먼저 구현한다. 배포 PC마다 논리 프로세서·가용 메모리·GPU를 동적으로 감지하고 CPU 스레드를 전부 사용한다. JavaScript Worker pool로 분할·병합 계약을 먼저 검증한 뒤, Tauri Rust 공유 메모리 병렬 엔진을 기본 경로로 전환한다. GPU는 CPU profile에서 대량 batch 병목이 확인되고 보수적 상한/최종 CPU 재평가 계약을 통과한 경우에만 사용한다. 상세 계획은 `docs/architecture/d4-parallel-exact-optimization-plan.md`를 따른다.
    - 병렬화 P0/P1 구현(2026-08-28): `d4-global-optimizer.js`에 결정론적 shard plan·전용 shard 문제·완전성 감사·안전 병합을, Worker/클라이언트에 planner→pool→merge 프로토콜과 동적 shard 배정을 추가했다. 작은 64개 조합은 8 shard에서 중복·누락 없이 단일 oracle과 같은 `exact 2255`·동점 ID를 반환했고, 실제 `d4-optimizer-worker.js`를 Node worker-thread에서 실행한 P1 회귀도 2 Worker·8 shard·`exact 2255`를 통과했다. `ParallelWorkerClient`는 명시 스레드 수 또는 `navigator.hardwareConcurrency`를 사용하며, 현재 결과 UI의 기본 단일 Worker는 P2 실제 425개 성능·메모리 Gate 전까지 유지한다. 부분/timeout/실패 shard가 있으면 plan upper를 포함해 `bounded` 또는 오류로 남기며 `exact`로 승격하지 않는다.
    - 병렬화 P2 1차(2026-08-28, 불승격): 실제 425개 물리 근거리 5초에서 8-shard plan 생성은 약 1.1초였지만 planner plan의 구조화 복사와 각 Worker 후보 복제·초기화가 남은 예산을 소진해 첫 shard 결과 전에 timeout됐다. 이때 유효한 추천을 `invalid`로 바꾸지 않도록 planner full-domain initial feasible lower bound를 병합에 보존하고, plan이 예산의 30%(최대 1.5초) 안에 준비되지 않으면 기존 단일 Worker로 남은 시간을 쓰는 fallback을 추가했다. 이 fallback은 안전한 `bounded`를 돌려주지만 병렬 speedup이 아니므로 JavaScript pool·UI 기본값은 불채택이다. 다음 병렬 구현은 후보 저장소를 Worker마다 복제하지 않는 Tauri Rust 공유 메모리(P3~P5)이며, GPU 검토는 그 CPU profile 이후다.
    - 병렬화 P3 착수(2026-08-28): Tauri `d4_hardware_profile`이 `std::thread::available_parallelism()`의 실제 가용 논리 스레드와 Windows `GlobalMemoryStatusEx`의 총/가용 물리 메모리를 `toram.d4-hardware-profile.v1`으로 반환한다. profile은 스레드 수를 줄이지 않고 `logicalThreads × 8` 초기 shard 목표와 `min(총 RAM × 60%, 가용 RAM × 75%) - 512MiB` 큐 메모리 예산을 함께 제공한다. `d4-worker-client.js`는 native profile을 비동기로 읽고, 일반 브라우저나 명령 실패에서는 `navigator.hardwareConcurrency` 기반 profile로 fallback한다. 이는 Rust ThreadPool·메모리 예산을 위한 입력 계약일 뿐 아직 JS 계산식/추천을 Rust에 이식하거나 UI 기본 엔진을 바꾸지 않았다. `cargo test --manifest-path src-tauri/Cargo.toml` 5/5 및 Worker client 회귀를 통과했다.
    - 병렬화 P3 runtime 기반(2026-08-28): `src-tauri/src/d4_parallel_runtime.rs`는 불변 task 저장소를 참조 공유하며 atomic work index로 모든 task를 정확히 한 번씩 배정한다. shard 병합은 global initial feasible lower bound, pending/failed shard upper, exact 조건, build ID 사전식 동점을 함께 보존한다. 1/2/16/64 thread task coverage와 pending·동점 병합을 Rust 단위 회귀로 확인했다. evaluator가 아직 Rust에 이식되지 않아 Tauri command/UI에는 연결하지 않으며, JS/Rust 평가기 동치 Gate 뒤에만 P4/P5로 승격한다. 현재 Rust 검증은 `cargo test` 8/8, `cargo clippy -- -D warnings` 통과다.
    - 병렬화 P3 Rust summary evaluator 확장(2026-08-28): `src-tauri/src/d4_native_evaluator.rs`는 기존 4개 fixture에 active AMPR 선택, 발도→ATK conversion, 다중 내성, fixed CRIT/minimum CDMG, 방어 무시·마방 절반 무시, skillStats·다층 배율, 확률 proc, 화살/서브 마도구, attack-power mode, dual-bringer 마법 반영을 더한 3개 경계 fixture까지 JS kernel summary와 일치시켰다. JS의 `x * (ratio / 100)`과 `x * ratio / 100`의 부동소수점 floor 경계 차이도 이 과정에서 발견·동일 순서로 수정했다. `tools/generate-d4-rust-evaluator-fixtures.mjs`, Rust unit test 13/13, `cargo clippy -- -D warnings`가 이를 검증한다. 단, 모든 실제 크리스타 단독·결정적 무작위 aggregate·조건부 후보와 BuildEvaluator feasible 판정의 property parity는 아직 없다. 이 전수 동치 Gate 전에는 native evaluator/runtime을 Tauri command·추천·상한에 연결하지 않는다.
    - 병렬화 P3 실제 데이터 parity(2026-08-28): Tauri 명령에는 등록하지 않은 `src-tauri/src/bin/d4_native_summary.rs` 개발용 JSON bridge와 `tools/test-d4-rust-native-parity.mjs`를 추가했다. 계보상 후속 강화가 없는 실제 최종 크리스타 216개를 물리·마법·듀얼·화살·방패 중량·두루마리 6 구조에 각각 적용하고, 같은 데이터로 결정적으로 만든 192개의 8개-stat aggregate도 대조했다. 총 1,488건에서 JS/Rust의 대미지·MAXHP·MAXMP·AMPR·평타 CRIT·ASPD 및 그 값에 기반한 기본 D4 feasible 판정이 일치했다. 조건부 옵션은 각 구조의 main/sub/armor 조건을 사전 적용해 canonical stat vector로 비교한다. 이 Gate는 단독 후보·조건부·aggregate 수식 동치를 자동으로 보호하지만, 계보/중복 제약을 포함한 full BuildEvaluator outcome와 Rust exact solver parity는 P4에서 별도로 검증한다. native evaluator/runtime은 그 전까지 Tauri command·추천·상한에 연결하지 않는다. 검증: `cargo test` 18/18(bridge target 포함), `cargo clippy -- -D warnings`, native parity 1,488/1,488 통과.
    - 병렬화 P4 Rust 단일 exact(2026-08-29, 완료): `d4_native_solver.rs`에 JavaScript prepared D4 탐색의 현재/Utility/Damage 초기해, 192개 pool·2회 coordinate pass, 정규화 CandidateTree, 2축 분할, envelope bound, 64개 이하 완전 열거 및 build ID 동점 규칙을 이식했다. work item은 고정 4슬롯 공유 노드 배열로, aggregate evaluator는 JSON object를 만들지 않는 Rust map 경로로 처리해 초기 프로토타입의 node별 Vec/path/JSON 할당을 제거했다. `D4_P4_REAL=1 D4_P4_VERIFY_JS=1 node tools/test-d4-native-exact-p4.mjs`가 실제 425개 fixture에서 현재 JS exact와 Rust exact를 모두 끝까지 실행해 점수 14,097 및 최종 build ID 일치를 확인했다. 동일 조건 재측정은 JS 1,015,641ms/26,208,511회 평가, Rust 148,833ms/26,198,199회 평가/4,486,581개 방문 노드였고 Rust가 6.82배 빠르며 85.3% 짧았다. 이 결과는 단일 스레드 언어 전환 동치 Gate이며 아직 Tauri command·추천 기본 경로에는 연결하지 않았다. 다음 단계는 P5의 공유 저장소 전체 CPU 병렬화와 취소·진행·메모리 예산 연결이다.
    - 병렬화 P5 core(2026-08-29): `solve_exact_parallel`과 `d4_native_parallel` 개발 bridge가 후보·CandidateTree를 한 번만 공유하고, `available_parallelism()` 기본값의 8배 target shard를 atomic work index로 동적 배정한다. worker는 local heap을 쓰고 global incumbent는 원자 점수 빠른 pruning과 mutex 기반 exact/tie 갱신을 조합한다. 실제 425개에서 자동 감지 16 논리 스레드/130 shard는 점수 14,097과 build ID를 단일 Rust와 일치시켰고, 단일 141,713ms 대비 병렬 20,811ms(6.81배 단축)를 기록했다. 소형 oracle은 요청 1/2/16/64 thread에서 모든 shard 완료 및 exact/tie 일치를 회귀한다.
    - 병렬화 P5 연결(2026-08-29, 완료): Tauri `d4_optimize_parallel(jobId, problem)`은 감지된 모든 논리 스레드로 Rust shared-memory 탐색을 실행하며, `cancel_d4_optimization(jobId)`는 원자 취소 신호만 설정한다. 취소는 현재 incumbent가 있어도 `cancelled`/`exact:false`/상한 없음으로 반환하므로 중단 결과를 최적 증명으로 표기하지 않는다. 결과 UI는 데스크톱에서 `assets/js/d4-native-client.js`를 우선 사용해 package ID를 원래 후보 객체와 JS `BuildEvaluator` outcome으로 복원하고, 명령 시작·직렬화·실행 오류에서는 기존 Worker 경로로 자동 fallback한다. `cargo test` 34개(메인 15 포함), `cargo clippy -- -D warnings`, native client bridge·browser runtime·P5 small oracle이 통과했다. 남은 P6/P8은 저메모리/peak working-set·실행 중 세밀 진행·Windows 설치본 E2E 계측이며, 아직 측정하지 않은 항목을 완료로 표현하지 않는다.
    - 병렬화 P6 CPU 검증·승격(2026-08-29, 완료): small scheduler 회귀는 요청 1/2/4/8/16/64 thread에서 exact·동점 ID를 유지한다. release `d4_native_parallel.exe`의 실제 425개 fixture cold 측정은 1 thread 141.36초/140.58초(peak 29.31MB/29.27MB), 8 thread 21.93초(40.32MB), 16 thread 21.78초·20.97초(42.94MB/42.89MB)였고 모두 score 14,097·같은 build ID·전 shard 완료다. 16 thread는 `threadsUsed:16`, 130 shard, 1-thread 대비 6.70~6.74배 speedup이며 CPU time 233.8초/wall 21.0초로 약 11.1 logical core 상당을 사용했다. 즉 Windows가 허용한 모든 논리 thread를 생성·스케줄하지만 이 fixture의 shard 불균형과 global bound 때문에 완전 선형 포화는 아니다. 100ms 취소 신호는 16-thread run을 wall 358~359ms, solver 177~180ms, peak 16.06~20.64MB에 `cancelled`/`exact:false`/0 of 130 shards로 끝냈다. JS exact 1,015.6초와 비교하면 Rust 16-thread는 약 48배 짧다. 그러므로 데스크톱 Rust CPU 경로를 기본으로 승격하고, 10초 exact 및 8→16 scaling은 다음 Pair-native 성능 과제로 남긴다. 계측 도구: `tools/benchmark-d4-native-p6.mjs`, `tools/measure-d4-native-p6.ps1`.
    - 병렬화 P7 GPU 타당성 Gate(2026-08-30, 완료·CPU-only): GPU prototype의 진입 조건은 CPU 병렬 profile에서 전체 시간의 50% 이상을 차지하는 동일 대량 batch를 찾는 것이다. Gate F의 상한 평가 487.4초와 완성 조합 평가 328.1초는 중첩 inclusive 시간이라 합산할 수 없고, 어느 하나를 독립적인 50% 이상 batch로 증명하지 못한다. P6 Rust 탐색도 shard별 동적 heap·`Stats` map·전역 incumbent/즉시 prune가 결합되어 있어 65,536개 단위로 이식 가능한 단일 커널이 아니다. f32 GPU 결과는 exact pruning에 쓸 수 없으며 CPU 재평가·전송·dispatch까지 포함한 P95 1.5배 및 전체 exact wall-time 개선을 현 상태에서 입증할 수 없다. 따라서 `wgpu` 의존성·GPU 실험 경로를 추가하지 않고 Rust CPU 기본 경로를 유지한다. 향후 독립 bound/leaf kernel이 50% 이상이라는 새 profile이 나오면, 전송 포함 CPU/GPU P95·보수 상한 property·최종 CPU 재평가 Gate로만 재개한다. 개발 환경의 GPU 조회는 Windows 권한 거부였으나, 이는 하드웨어 이름이 아닌 profile 조건으로 결정한다는 정책과 일치하며 CPU fallback의 결함으로 취급하지 않는다.
    - 병렬화 P8 배포·fallback(2026-08-30, 패키징 완료·runtime 미완료): native memory cache는 계산식 `d4-native-evaluator.v1`, 엔진 `d4-native-solver.v1`, CandidateTree 분할 정책, 감지 logical thread, GPU `cpu-only.p7`, time budget을 key에 포함해 다른 실행 계약의 결과를 재사용하지 않는다. 결과/진행 UI는 Rust CPU 엔진, 사용 스레드, GPU 미사용, 경과·평가·gap을 표시한다. native command의 시작·직렬화·실행 오류는 기존 JavaScript Worker로 안전하게 fallback하며 Worker 오류는 invalid-safe 결과로 남는다. P8 검증 중 Cargo가 개발용 `d4_native_exact`를 NSIS 기본 binary로 묶는 결함을 발견했고, `src-tauri/Cargo.toml`의 `default-run = "toram-online-auto-build-calculator"`로 실제 Tauri 앱을 고정했다. 새 release NSIS build log가 실제 앱 EXE를 선택한 것을 확인했고, 생성 설치 파일은 격리된 `C:\\Temp\\ToramD4P8-20260830`에 silent 설치→3초 실행→silent 제거를 모두 exit 0으로 완료했으며 임시 폴더도 삭제됐다. `cargo fmt --check`, Rust 37 tests, clippy, native cache/bridge·Worker UI fallback·small exact 회귀가 통과했다.
    - P8 native runtime 정정(2026-08-30, 당시 미완료): 패키징 smoke와 UI 필드 형식은 통과했지만 native command에 UI의 5초/30초 deadline이 전달되지 않아 exact까지 무제한 실행된다. 실제 Rust progress channel, deadline `bounded`와 인증 upper, frontier checkpoint/resume도 없다. 초기 약 130개 shard를 worker local heap이 독점해 장기 실행 중 24개 process thread 가운데 5초 CPU time이 5.03초만 증가하는 한 코어 tail을 확인했다. 고정 크리스타 기능 자체는 사용자 확인과 compiler 회귀에서 정상이며, 앞선 장기 실행은 고정 체크가 빠진 조작/표시 문제였다. 남은 것은 고정 기능의 재설계가 아니라 고정 효과 1회 반영·비교체·계보 충돌을 native/UI 통합 회귀로 계속 보존하는 Gate다. 이 시점의 요구와 교정 계획은 `docs/architecture/d4-native-runtime-correction-plan.md`에 보존하며, 현재 완료 상태는 아래 N0~N6 기록을 따른다.
    - native runtime N0(2026-08-30, 완료): 사용자 제공 실제 26분 입력을 `tools/fixtures/d4-native-runtime-26min-revenir.json`으로 고정하고 `node tools/test-d4-native-runtime-n0.mjs`로 검증했다. 이 fixture는 루브닐 3타(스택 2)·최종 계수 32.805·상수 400, 에투왈 현재 장착, 오로로 콜론·카나요간 금지, 화면의 MAX MP 2,275를 보존한다. 사용자가 에투왈을 포함한 8개 슬롯 모두 잠금 해제였으므로 fixture도 8개 슬롯 미고정이다. 같은 입력에서 에투왈 슬롯만 고정한 사용자 측정은 118.83초이며, 완료 모드와 결과는 자동 캡처하지 못했으므로 사용자 보고 경과 시간으로만 별도 기록했다. 회귀가 잠금 0/1/2/8개·잠긴 빈 슬롯·unknown lock compiler 진단과 현 bridge의 deadline/progress 부재를 재현한다. `tools/measure-d4-native-n0.mjs`가 기본 5초 명시 취소로 process 계측을 남기며, per-shard throughput/UI progress는 현 runtime에서 제공되지 않음을 명시한다. 같은 도구의 에투왈만 고정한 현 환경 완주은 16 threads exact, solver 12,348ms/wall 12,541.378ms/CPU 156,031.25ms/peak 25.81MiB였고 CPU는 처음 10초 약 13~14 logical cores에서 마지막 2초 9.41 cores(threads 20→9)로 하락했다. 이는 26분 실행의 한 코어 tail과 동일하다고 단정하지 않는다. 현 12.54초와 사용자 118.83초는 실행본·환경·입력 상태 차이가 미분리라 대체하지 않는다. prepared package 수는 무기/방어구/추가/특수 1,102/859/770/1,004이고 현재 에투왈 조합은 AMPR·평타 CRIT 제약을 충족하지 않아 탐색이 유효 incumbent를 먼저 찾아야 한다. 보고된 26분은 deadline 교정 전 기준선으로 보존하며, 같은 unbounded exact를 다시 장시간 실행해 기준 수치를 덮어쓰지 않는다.
    - native runtime N1(2026-08-30, 완료·기능 변경 없음): 사용자 확인대로 고정 크리스타는 정상 기능으로 유지하고 `tools/test-d4-native-locks-n1.mjs`를 추가했다. 실제 compiler 입력의 0/1/2/8 잠금을 축소한 결정적 domain으로 Rust `d4_native_parallel`에 전달해 모두 exact로 완료했으며, native package ID는 compiler package로 복원됐다. 에투왈 단일 고정과 에투왈/오르그 이중 고정은 최종 특수 package에서도 유지되고, native `statDelta`는 선택된 네 package의 합과 일치해 효과가 한 번만 반영된다. 알 수 없는 잠금은 native 호출 전에 `UNKNOWN_LOCKED_CRYSTA` diagnostic으로 차단한다. 이는 고정 로직의 교정이 아니라 정상 계약을 보존하는 integration Gate다.
    - native runtime N2(2026-08-30, 완료): `d4_native_solver::NativeSearchSession`이 tree·requirements·incumbent·frontier·counter를 독립 세션으로 보유하고, `run_slice(node_budget)`는 node 사이의 안전 경계에서 bounded 결과와 frontier upper를 반환한다. `NativeSearchCheckpoint`는 문제·상태·counter·frontier tree path/upper를 `toram.d4-native-search-checkpoint.v1` JSON으로 직렬화한다. 복원은 frontier의 중복/비유한 upper/없는 path를 거부하며 checkpoint 시점에는 active work가 없으므로 저장 frontier가 모든 미해결 work다. 작은 동점 oracle의 1-node slice 및 JSON checkpoint 왕복 재개가 무중단 exact와 같은 score/build ID를 Rust 회귀로 확인했다. Tauri continuation registry와 UI deadline/cancel 전달은 N4에서 이 session 기반에 연결한다.
    - native runtime N3(2026-08-31, 완료): parallel solver는 초기 shard별 local `BinaryHeap` 독점을 제거하고 모든 descendant를 하나의 shared max-priority frontier에 다시 넣는다. ready queue와 active worker가 모두 0일 때만 worker가 종료하므로, 실행 중 split된 work를 idle worker가 계속 처리한다. terminal result의 `scheduler`는 split/steal count, 총·worker별 busy microseconds, 최장 work-item 시간을 반환한다. wide 8^4 동점 oracle에서 serial/parallel exact의 score·build ID를 보존하고 initial shard보다 많은 descendant node가 drain됨을 회귀했다. 사용자의 26분 입력은 다시 unbounded로 실행하지 않고 16 thread·5초 explicit cancel로 계측했으며 solver 5,000ms, wall 5,262.213ms, CPU 71,953.125ms(약 13.7 logical cores), split 1,732,518회, worker busy 4.527~4.566초, longest work item 11.547ms였다. `stealCount:0`은 이 표본에서 shared frontier가 비지 않아 wait/reclaim이 발생하지 않았다는 뜻이다. 이는 5초 표본에서 one-core tail이 사라진 근거일 뿐 26분 사용자 실행과 동치라고 주장하지 않는다. N4는 이 frontier/session을 deadline·streaming progress·resume command/UI에 연결하는 단계다.
    - native runtime N4(2026-08-31, 완료): native client가 prepare 시작부터 30초 budget을 계산해 `remainingBudgetMs`와 Tauri `Channel` progress를 command로 보낸다. Rust에는 job cancel registry와 별도 continuation session registry(최대 4개·oldest eviction), `resume_d4_optimization`, `dispose_d4_optimization`을 추가했다. session coordinator는 safe node batch마다 lower/upper/평가/방문/ready work를 channel로 보내고 deadline에서 frontier를 보존해 bounded 또는 no-incumbent-yet continuation을 반환하며, cancel은 세션을 폐기한 cancelled 결과다. 각 batch는 shared immutable tree/incumbent를 전체 CPU task scheduler로 처리하고 모든 child를 return 전 persistent frontier에 병합한다. 취소·deadline은 leaf/분기 내부에서도 감지하고 중단 node를 frontier에 재삽입해 deadline continuation의 안전한 upper를 보존한다. 1/2/8/64 thread parallel session slice가 serial exact와 같은 score/build ID로 재개되고, deadline frontier 보존·cancelled 상한 제거·oldest session eviction도 Rust 회귀했다. native client mock은 실제 channel snapshot의 gap/thread/ready-work 전달을 검증한다. 개발 Tauri WebView에서 progress의 evaluation/visited/ready work 증가, 16/16 worker 표시와 30초 안의 no-incumbent-yet terminal 결과를 확인했다. 최종 cooperative-cancel 변경 뒤의 클릭 지연 재측정은 사용자가 불필요하다고 명시해 제외했다. `cargo fmt --check`, Rust 65 tests, `cargo clippy --all-targets -- -D warnings`, `cargo build`, `npm run desktop:prepare`, native client·N0 fixture·browser runtime 회귀가 통과했다. N5는 bounded 결과의 정밀 계산 버튼을 같은 continuation으로 재개하도록 UI를 연결하는 별도 단계다.
    - native runtime N5(2026-08-31, 완료): native client는 bounded 결과에서 받은 `continuationId`와 prepared problem/evaluator 문맥을 보존하고, 결과 UI는 그 token이 있는 native bounded 결과에만 “정밀 계산 계속”을 표시한다. 클릭은 `d4_optimize_parallel` 재시작이나 Worker fallback 없이 `resume_d4_optimization`에 새 30초 예산·progress channel을 전달하므로 Rust의 동일 frontier·incumbent·evaluation counter가 이어진다. exact 종료는 token을 제거하고 exact만 cache하며 bounded 결과는 stale token을 재사용하지 않도록 cache하지 않는다. 입력 변경·새 계산·창 종료는 active job cancel과 `dispose_d4_optimization` session 폐기를 수행한다. session eviction/만료는 새 Worker 계산으로 바꾸지 않고 새 전역 계산을 시작하라는 오류로 표시한다. `tools/test-d4-native-client.mjs`는 bounded→resume에서 새 optimize command가 호출되지 않는 점, token 전달, exact token 제거, 만료 오류를 확인한다. `tools/test-d4-native-resume-ui-n5.mjs`와 browser Worker runtime은 버튼 노출 조건·resume wiring·입력/창 종료 cleanup을 회귀한다. N6은 oracle/property·cold 반복/설치본 E2E를 묶는 승격 Gate다.
    - native runtime N6(2026-08-31, 완료): 사용자 N5 검증에서 재개 대기 시간이 elapsed에 섞이고 매 30초마다 다시 정밀 계산을 눌러야 하며 실행 중 일시정지가 없다는 결함이 확인됐다. `NativeSearchSession`은 이제 실제 준비·slice 실행 시간만 누적하고 checkpoint도 이를 보존한다. Tauri의 `pause_d4_optimization`은 cancel과 구분되어 safe batch 뒤 `paused`+continuation을 반환한다. UI는 일시정지/계산 재개를 제공하고, 한 번의 정밀 계산 요청이 bounded/no-incumbent-yet continuation을 자동으로 exact·일시정지·오류까지 연결한다. Rust 72 tests, clippy warning-free, JS/Rust parity 1,488 cases 및 N1 lock·native client·UI·Worker regressions가 통과했다. NSIS installer는 `C05C74B4FD932237CA5E369D2FF00134CAEC6560A6509F97CB8EFAB8B7739A0C`로 새로 build했다. 사용자가 설치본 UI에서 자동 연속, 일시정지·재개, inactive elapsed 제외를 확인해 N6을 완료 처리했다.
    - 결과 탭 추천 요약(2026-08-31, 완료): 전역 추천이 반환되면 기존의 수십 개 옵션·엔진 정보보다 먼저 현재/추천 대미지와 절대·백분율 변화, 4개 부위의 크리스타 교체, 주요 공격 스탯, 최대 HP·최대 MP·공격 MP 회복·ASPD·행동속도·CSPD·시전시간 감소의 현재→추천 변화를 표시한다. 값은 별도 추정이 아니라 `BuildEvaluator`가 현재·추천 aggregate를 같은 scenario에서 재평가한 outcome을 사용한다. 전체 추천 옵션, 현재 세팅 상세, 옵션 효율, 평가 수·상한·Rust CPU/thread 정보는 접이식 영역으로 이동했다. 현 native exact 결과 계약은 인증된 단일 최적해만 반환하므로, 가격/최소 교체 조건을 포함한 Top 3~5 대체 빌드는 가짜 순위를 표시하지 않고 별도 top-K 탐색 계약을 추가할 때 구현한다.
    - 폴버로스 조건부 옵션 교정(2026-08-31, 완료): 폴버로스의 원거리 위력 +9%는 무조건 효과로 유지하고, 누락됐던 `자동활 장비 시 근거리 위력 +9%`를 `condStats`에 연결했다. D4 compiler 회귀는 한손검에서 LRW만, 자동활에서 LRW·SRW 모두를 물질화하며 비활성 자동활 조건 메타데이터도 남기는지 검증한다. 그 밖의 스킬별 공격 사거리 일괄 검수는 별도 후속 작업으로 보류한다.
    - 루브닐 거리 판정 교정(2026-08-31, 완료): 사용자 확인에 따라 루브닐(`Knight:11`) 타격은 공통 기사 `hit()` 기본값과 무관하게 `longRange:false`를 명시해 근거리로 판정한다. 실제 26분 입력 fixture도 `rangeType:SHORT`로 갱신했고, 스킬 profile·D4 fixture 회귀가 각각 근거리 플래그와 SRW 포함/LRW 제외 관련 축을 검증한다. 다른 기사 스킬의 사거리 일괄 검수는 이 단일 교정에 포함하지 않고 후속으로 보류한다.
    - 버전 0.6.0 승격(2026-08-31, 완료): npm·Tauri·Cargo의 앱 패키지 버전을 모두 0.6.0으로 맞췄다. 이는 소스/다음 빌드의 버전 승격이며, 새 NSIS 설치 파일 생성·해시 산출·GitHub Release/태그 생성은 이 변경에 포함하지 않는다. 공개된 v0.5.0 Pre-release와 그 태그·자산 기록은 역사 정보로 유지한다.
12. v0.5.0 Pre-release 실사용 피드백과 재현 가능한 버그 수정
13. 필요 시 Windows 코드 서명 인증서 준비
14. 반복 가능한 Windows 빌드·릴리스 자동화
15. docs/verification/unimplemented.md에서 사용자가 선택한 항목만 구현
16. 중요한 상태 변경마다 이 문서 갱신

## 12. 2026-08-22 저장소 정리

- Tauri 전환 뒤 사용하지 않는 Versions/v0.2.1~v0.4.1 단일 HTML 배포물과 tools/build-release.mjs를 제거했다. 과거 내용은 Git 기록에서 복구할 수 있다.
- 오래된 S1 누락 수치와 재개 순서를 담은 두 초기 handoff 문서를 제거하고 현재 인계 문서와 검증 기준으로 통합했다.
- 루트 스킬 폴더는 삭제하지 않고 assets/source-data/skill-registration으로 이동했다. 이 자료는 skill-registration-metadata.js의 재생성 원본이다.
- dist, src-tauri/target, src-tauri/gen은 추적하지 않는 재생성 산출물이므로 로컬에서 제거했다. npm run desktop:prepare 또는 Tauri 빌드로 다시 만들 수 있다.
- node_modules는 현재 개발 명령에 필요한 설치 의존성이므로 유지했다.
- 이미지, 아이콘, assets/game-data, Coryn 자료, 게임 아이콘 매칭 자료, docs/sources/skills 원문 캐시는 모두 유지했다.

## 13. 2026-08-23 웹앱 QA 보강

상세 상황·원인·결과·후속 결정지는 `docs/verification/webapp-qa-blind-spots.md`를 기준으로 한다.

이번 변경에서 다음 명확한 결함을 수정했다.

- 조건부 `damageType`과 타격 플래그 AST를 실제 값으로 해석한다.
- 현재 무기·조건에서 사용 불가능한 스킬, 콤보 시동 불가 스킬, 태그 수신 불가 스킬에서 콤보 계산을 중단한다.
- `ignoresComboDamageChange` 타격은 콤보 태그 대미지 변화에서 제외한다.
- 액티브 버프 계산이 기존 방패 제련치·기본 스탯·최종 전투 스탯을 사용한다.
- 문자열·동적 기본값·기본 `true`를 포함한 콤보 입력을 엔진 정규화 값과 일치시킨다.
- 다음 스킬 1회 옵션은 자동 저장에서 제외하고, 관련 계산 입력이 바뀌면 과거 적용 타격을 무효화한다.
- VIT/VIT%, 최종 행동속도 50% 상한을 연결했다.
- 컨버전의 패시브 MATK를 액티브 토글과 분리했다. INT 기본 MATK는 MATK% 전, 최종 WATK 기반 증가는 원문대로 MATK(+) 단계에 적용한다.

- 전역 액티브 대미지 버프는 같은 `activeGlobalDamage` 계열 안에서 증가분을 합산하고, 다른 패시브·스킬 한정 계열과는 곱한다.
- 배틀 패시브 강타·집중은 물리/마법 타격에 각각 연결했다. 결과 탭은 확률 효과 미적용 기본 대미지·발동 시 대미지·확률 반영 기대 대미지를 모두 표시하며, 크리스타 최적화와 옵션 효율은 기대 대미지를 점수로 사용한다. 콤보 계수에 이미 내장된 전역 액티브 대미지는 결과 옵션에서 중복 적용하지 않는다.
- 같은 적용군의 내성 성분은 합산하고 `1 - 내성/100`을 적용한다. 현재 속성·탄환 내성은 UI 없이 향후 연결용 내부 성분 배열로만 준비했다.
- 스킬 엔진과 데이터 감사기는 레이어 등록 순서상 첫 유효 정의 427개를 동일하게 사용한다. 뒤의 보강 정의는 중복 계산하지 않고 진단 목록으로 보존하며 개발 회귀에서 감사한다.
- 음수 안정률은 정상 입력 계약 밖의 남용 값으로 보고 별도 보정하지 않는다.
D1·D2·D3·D5·D6의 방향은 확정되어 아래 14절에 반영했다. D4는 전역 8슬롯 탐색·Worker·결과 탭 연결까지 구현했으며, 제한 시간 결과는 전역 최적값이 아니라 반드시 `bounded`와 인증 gap으로 표시한다.

## 14. 2026-08-23 D 섹터 결정 반영

- 결과 대상이 없으면 평타를 계수 1·상수 0으로 계산하고, 결과 최상단에 `[평타] 기준 최적화됨`을 표시한다. 콤보 타격을 적용하면 해당 스킬 이름으로 바뀐다.
- 다단 타수는 빌드 최적화 점수에 곱하지 않는다. 중독 가능 스킬을 하나라도 습득한 경우에만 중독 1회 피해를 내부 결과로 계산하며 UI 배치는 보류했다.
  - `(총 DEX + (ATK + MATK) × min(0.5, (DEF+MDEF)/2/(적 레벨×6))) × (1 - (물리내성+마법내성)/2/100)`
- 콤보에서 선택한 타격은 계수·상수 몇 개가 아니라 타격 프로필 전체와 실행된 플래그를 결과 계산기에 전달한다. 공통 어댑터가 공격 유형, 거리, 발도, 크리티컬, 관통, 방어 무시, ATK/MATK 선택, 속성 판정을 한곳에서 해석한다.
- 속성 각성 또는 스킬 고유 `weakness` 속성만 약점 공격으로 판정한다. 마력 속성은 약점 25%를 만들지 않지만 기존 결정대로 기본 INT 비례 속성 보너스는 적용한다.
- 마법 크리티컬은 스펠 버스트 레벨을 `2.5% × 레벨`로 반영한다. 쇠약 가능 스킬 습득을 자동 판정하고, 지팡이·메인 마도구는 쇠약 시 +50%, 그 외 무기는 약점 공격일 때만 +50%를 더한다. 원문에 없던 미설정 무속성 지팡이 +25% 분기는 제거했다.
- 목록에 없는 크리스타 이름은 입력을 보존하고 슬롯에 인라인 오류를 표시하며 결과·최적화를 차단한다.
- D4는 2026-08-24 사용자 지시로 단계 구현을 시작했고, 공통 평가 기반·크리스타 전역 후보/oracle/안전 상한·Worker/진행 UI까지 연결했다. 결과 탭은 네 장비 8슬롯의 전역 결과를 표시하며 `exact`가 아닌 제한 시간 결과는 반드시 `bounded`와 인증 gap으로 구분한다.
- 잠금이 없을 때 단순 전역 조합 수는 약 `39,381,065,483,300,352`개다.
- D4 알고리즘은 `docs/architecture/d4-build-optimizer-design.md`에 전역 제약 기반 anytime Pareto branch-and-bound 방식으로 설계했다. 자동 장비 옵션 부여·잠재력 탐색은 사용자 결정으로 추후 구현하며, 현재 범위는 완성된 수동 장비 옵션을 입력값으로 사용한다.
- 1단계에서 `stat-registry.js`, `build-evaluator.js`, `ToramCalculationKernel`을 추가했다. 크리스타 87종과 스킬 stat 효과의 합친 원문 표기 111종을 감사해 미등록 키 0개를 확인했고, 범위 밖 스탯은 삭제하지 않고 보존한다.
- `OutcomeVector`는 대미지, 공격 지표, 평타 크리티컬률, MAXHP·MAXMP·AMPR·ASPD·행동속도·CSPD를 반환한다. 기본 Utility 요구치는 hard constraint로 적용되며, 이를 어긴 완성 빌드는 추천 하한으로 채택하지 않는다.
- 2026-08-24 최종 회귀에서 JavaScript 테스트 48/48, S1 출처 연결 427/427, Tauri 프런트엔드 준비, Rust 테스트 3/3이 통과했다. 네이티브 저장 E2E는 `TORAM_E2E_CDP`가 없어 안전하게 skip했다. 실제 브라우저 수동 검증은 Windows 실행 보조기 초기화 오류로 수행하지 못했으며 Worker 런타임·자동 DOM 회귀로 대체했다.
- `d4-problem-compiler.js`는 실제 425개 크리스타를 네 장비 2슬롯 후보로 약 100ms에 컴파일했다. 조건을 사전 물질화하고 하위 강화, 동일 장비 중복, 같은 시작점 분기 계보, 잠금·금지·부위 제한을 solver 제약으로 처리한다.
- `d4-global-optimizer.js`는 소형 8슬롯 합성 문제에서 전수조사 3,430개와 같은 조합을 찾는다. 20개 결정적 무작위 문제에서 solver·oracle·동점 순서가 일치하고, 기존 부분해 상한 1,093건과 새 계층형 후보 상한 property test 모두 위반 0건이다.
- `d4-source-profile.js`는 Utility 부족분, 로그 한계 대미지, 공격력·관통 등가축과 집중 획득처 비교를 제공한다. 이미 안전하게 충족된 MAXMP 같은 축은 후보 지배 판정에서 제외한다.
- 전역 엔진은 `ToramApp.optimizer.compileGlobalCrystaProblem`과 `solveGlobalCrystaProblem`으로 호출 가능하다. 결과 탭의 기존 부위별 독립 탐색은 실행하지 않으며, 네 장비 8슬롯을 하나의 문제로 컴파일해 JavaScript Worker에서 계산한다.
- Worker 요청은 스냅샷 버전으로 오래된 결과를 폐기하고, 새 계산이나 사용자 취소 시 Worker를 종료한다. 동일 입력·동일 시간 예산은 메모리 캐시를 재사용하며 5초 기본 계산과 30초 정밀 계산은 별도 캐시 키를 사용한다.
- 결과 탭은 `exact`, `bounded`, `heuristic`, `cancelled`, `invalid`를 구분한다. 진행률은 원시 조합 비율 대신 경과 시간·평가 횟수·탐색 노드·인증된 gap을 표시하며, `bounded`이면 정밀 계산 계속 버튼을 제공한다.
- 실제 425개 회귀는 공격 유형·거리·발도/일진강풍 변환에 따른 관련 축과 부위별 변동 축만 지배 비교에 사용하고, 사전식 ID 동점 계약에 맞춘 단방향 Pareto 비교를 수행한다. 부위당 비교 예산 100만 안에서 네 부위 Pareto가 모두 완결되며, 원본 후보 선형 초기해·부위당 192개 실수식 좌표 개선·네 부위 후보 상자 계층형 best-bound 탐색을 이어서 사용한다. 2026-08-24 개선에서 반복 스냅샷·해시 생성을 생략한 집계 평가 경로, 상한용 경량 결과, 상관관계를 빨리 드러내는 두 부위 동시 분할, 64조합 이하 상자의 직접 전수조사를 추가했다. 실제 측정은 컴파일 약 113~117ms, 첫 유효 추천 62~65ms, 5초 약 9.2만회 평가·하한 14,090.0409·상한 약 20,385·인증 gap 약 44.7%였고, 30초 정밀 모드는 약 69.6만회 평가·상한 17,556.75·gap 24.604%였다. 자동 회귀선은 첫 추천 500ms 이내·하한 13,500 이상·gap 75% 이하·네 부위 Pareto 완결이다. 후보 상자 상한이 아직 느슨해 `bounded`이며 exact로 표기하지 않는다. 실제 브라우저 수동 검증은 Windows 실행 보조기 초기화 오류로 대체했고 Worker importScripts 런타임·UI 계약 자동 회귀를 통과했다.
- D4의 기회비용은 강제 선택의 사후 점수 차이가 아니라 획득처 집중도와 슬롯 대체비용을 뜻한다. 고정·외부 획득량으로 Utility 부족분을 먼저 줄이고, ATK·크리티컬 대미지·거리 위력·발도공격 등 대미지 계열의 로그 한계효율과 부위별 획득 frontier로 명확한 우선순위를 증명한 뒤 애매한 후보만 전역 계산한다.
- 유저 제작 장비는 이미 제작됐다고 가정한다. 기본은 크리스타 2슬롯·옵션 8개이고 음수 옵션도 포함한다. 장비 제작·슬롯 생성·소재·옵션 부여 순서는 범위 밖이며, 잠재력·단일 성공률·최종 성공률은 사용자 입력이다. 성공률은 계산하지 않고 보존하며 잠재력만 8옵션 hard budget으로 사용한다.
- 잠긴 크리스타는 고정 효과로 먼저 합산하고 잠기지 않은 슬롯만 전역 후보로 남긴다. 크리스타 2슬롯과 장비 옵션 8개는 독립 제약이다. 옵션 1%p는 현재 완성 빌드의 `DeltaLogDamage / DeltaPotential`로 평가하고, 음수 옵션은 회복 잠재력 대비 대미지·Utility 손실과 옵션 한 칸의 비용을 함께 계산한다.
- 장비 옵션부여의 범위·입력·8옵션 제약·카탈로그 데이터 계약·D4 연결·검증 게이트는 `docs/architecture/equipment-option-assignment-spec.md`에 정리했다. 자동 옵션부여는 검증된 상한·잠재력 비용 카탈로그가 준비되기 전까지 구현하지 않는다.
- 크리티컬률 옵션은 강제로 한 줄 포함하지는 않지만, 평타 AMPR 운용 안정성을 위해 `평타 최종 크리티컬률 ≥ 100`을 기본 hard constraint로 사용한다. 선택 스킬이 확정 크리티컬이어도 이 제약을 면제하지 않는다. 대상 저항·스탯·버프·고정 장비·잠긴 크리스타를 반영한 평타 최종값으로 100을 먼저 만족시키고, 초과분은 선택 스킬의 기대 대미지에 기여할 때만 한계가치를 갖는다.
- 옵션 상한 기준 레벨은 온라인에서 최신 공식 레벨 상한 공지를 우선하고, 공식 확인이 불가능하면 사용자 입력 레벨로 fallback한다. 2026-08-24 확인 기준 공식 상한은 Lv.325다(`https://toram.jp/information/detail/?information_id=11036`).
- 현재 장비·크리스타의 조건부 옵션은 동적 탐색 변수가 아니다. 주무기·보조무기·방어구 구조를 먼저 확정하고 활성 효과를 일반 옵션 벡터에 합산한다. 예를 들어 경갑옷 물리관통은 경갑옷 분기에서 활성화한 뒤 고정 시나리오의 ATK% 등가축에 반영한다.
- D4 기본 Utility 요구치는 근거리 MAXHP 10,000·원거리 MAXHP 없음, 신속의 수도 Lv.10이면 버프 전 MAXMP 2,300/3중첩 후 2,000·그 외 2,000, AMPR 100(듀얼소드 2배 전), ASPD 1,000으로 확정했다. 명시 입력이 있으면 이를 덮어쓴다.
- AMPR은 `floor(10+MAXMP/100)`에 일반 AMPR%를 적용해 버린 뒤 일반 고정 AMPR을 더한다. 그 결과에 램페이지·괴력난신·트윈 스톰 같은 통상공격 변화 액티브를 각각 단독 적용하고 최종 AMPR이 가장 높은 하나만 채택하며, 동률은 스킬 ID 순으로 고정한다. 듀얼소드 2배는 후보 선택 뒤 한 번만 적용한다. 축지법의 사거리 밖 통상공격 1회 AMPR은 돌진용 하프 액티브 예외로 원문 데이터만 보존하고 지속 운용 AMPR·D4 Outcome에서는 제외한다.
- 자동 적용하는 고정 획득처는 없다. 요리·도핑·길드·스킬은 현재 세팅에서 명시적으로 활성화된 경우에만 비장비 획득량으로 반영하며 추후 SourceProfile 데이터로 확장한다.
- 같은 크리스타는 다른 장비에는 반복 장착할 수 있지만 같은 장비에는 중복할 수 없다. 부위 제한은 절대적이고 공용은 네 장비에 장착 가능하다. 하위 강화 후보는 최적화에서 제외하며, 강화 전후와 같은 시작점에서 갈라진 분기 강화는 배타 제약으로 처리한다.
- 1차 D4가 고려하지 않는 탱커·기타 옵션도 데이터에서 삭제하지 않고 향후 최적화를 위해 보존한다. Coryn v4.7 공개 스크립트의 MAXHP 식과 적용 순서를 BuildEvaluator·Outcome에 연결했다.
- 고정 시나리오의 공격력 등가축은 `100 × (ATK - DEF × (1-관통/100)) / BaseATK`이며 마법도 MATK/MDEF로 동일하게 계산한다. BaseATK 4000·DEF 2000은 50%p에서 시작하므로 ATK 90%p·거리 위력 40%를 더하면 두 계열이 140%p가 된다. 이 등가축은 후보 축약용이며 최종 순위는 원래 계산식으로 재평가한다.
- 원시 전수조사는 `O(Π m_s × T_F)`이고 현재 약 3.94경 조합은 초당 1억 평가를 가정해도 약 12.48년이므로, D4는 게임 규칙 기반 후보 축약과 안전한 상한이 필수다.
- 회귀: `node tools/test-d-sector.mjs`가 D1·D2·D3·D5·D6 계약을 검사한다.
- D4 동적 점수 강한 초기해의 S0 계측(2026-08-27)을 완료했다. `d4-initial-seed-telemetry.v1`은 raw/준비 후 초기 seed, coordinate·Pair 보강, heuristic 완료, root UB와 100ms·500ms·1s·5s·10s checkpoint의 LB·UB·gap·평가·노드·prune 수를 반환한다. 후보·상한·탐색 순서는 아직 바꾸지 않았고, `tools/benchmark-d4-exact.mjs` v2가 콜드 실행별 값을 보고한다. 실제 425개 10초 단일 확인은 raw 3회·LB 8,914, heuristic 1,511회·LB 14,089, root UB 49,037, bounded gap 35.794%였다. 이는 P95 성능 판정이 아니라 S0 출력 검증이다. 관련 회귀: `node tools/test-d4-global-optimizer-stage2.mjs`, `node tools/test-d4-full-stage3.mjs`, `node tools/test-d4-worker-stage3.mjs`, `node tools/test-d4-browser-worker-runtime.mjs`.

- D4 동적 점수 강한 초기해의 S1 동적 한계효용 계측(2026-08-27)을 완료했다. `assets/js/d4-dynamic-marginal.js`의 `toram.d4-dynamic-marginal.v1`은 baseline과 4부위 패키지별 `100 × ln(after/before)` 로그 한계 대미지, effect-vector 공격축(physical/magic/range/critical/unsheathe/other) 재평가, 공격·Utility 변화와 SourceProfile 잔여 요구량 감소를 결정적으로 기록한다. signature는 evaluator scenario hash만 믿지 않고 공격 유형·거리·발도 변환·DEF/MDEF·관통·크리티컬 경계·requirements·기본 stats까지 포함한다. 이 단계는 후보 삭제·상한·탐색 순서·추천 결과에 연결하지 않아 exact 계약을 바꾸지 않는다. `node tools/test-d4-dynamic-marginal.mjs`는 직접 evaluator 일치·입력 순서 결정성·DEF signature 분리를 확인하고 실제 425개에서 14,973 패키지, 58,309회 평가, 유한 expected damage 전부를 통과했다. Worker 로딩은 `node tools/test-d4-browser-worker-runtime.mjs`로 추가 검증했다.

- D4 동적 점수 강한 초기해의 S2 다중 seed pool(2026-08-27)을 완료했다. `assets/js/d4-dynamic-seed.js`의 `toram.d4-dynamic-seed-pool.v1`은 S1 profile을 이용해 부위별 순수 대미지·활성 공격축·Utility 공급·Supply Frontier 극점/무릎점·balanced 후보를 합치고, current와 활성 Utility landmark는 제한보다 우선 보존한다. 각 포함 패키지는 결정적 pool hash와 `current`·`damage`·`axis:*`·`utility:*`·`frontier:*`·`balanced` 근거를 반환한다. 원래 후보 domain, 후보 삭제, 상한, optimizer seed/탐색 순서는 아직 바꾸지 않았다(S3에서만 pool을 완성 조합에 사용). 실제 425개 14,973개 원본 패키지는 유지하고 pool은 무기 28·몸장비 25·추가 31·특수 29개로 생성됐다. `node tools/test-d4-dynamic-marginal.mjs`는 permutation 결정성·활성 Utility 대표·pool 밖 후보 보존 뒤 small oracle/solver exact 일치를 확인했고, `node tools/test-d4-browser-worker-runtime.mjs`가 Worker 로딩을 검증했다.

- D4 동적 점수 강한 초기해의 S3 완성 seed·repair(2026-08-27)를 완료했다. `createDynamicSeedBuilds`는 S2 부위 pool을 네 부위 실제 CandidatePackage 조합으로 완성하고, 작은 product는 전체 Cartesian 직접 평가, 큰 product는 partial BuildEvaluator 결과의 대미지/잔여 Utility 양쪽을 보존하는 결정적 beam으로 처리한다. infeasible complete build는 BuildEvaluator 잔여 요구량을 다시 읽어 1부위 뒤 제한 2부위 교환을 검사하며, 중복 조합도 `repairAttemptIds`로 audit한다. 시간·평가 예산·취소가 모든 loop에 적용된다. 이 단계도 incumbent·B&B·후보 domain에는 아직 연결하지 않았다. `node tools/test-d4-dynamic-seed-builds.mjs`가 Cartesian·beam·직접 outcome 일치·1/2부위 repair·취소를 통과했고, 실제 425개 S2 pool은 제한 beam에서 2,559회 평가로 네 부위 완성 build만 반환하며 직접 evaluator와 일치했다. Worker API 로딩은 `node tools/test-d4-browser-worker-runtime.mjs`로 검증했다.

- D4 동적 점수 강한 초기해의 S4 incumbent·국소 개선(2026-08-27)을 완료했다. `enableDynamicSeedIncumbent: true`와 `dynamicSeedTimeLimitMs`가 함께 명시된 실험에서만 S1~S3 feasible seed·S4 1/2부위 local 결과를 기존 `considerOutcome`으로 병합한다. 더 낮은 결과는 incumbent를 덮지 않으며 후보 domain·상한·exact 종료는 불변이다. `dynamicSeedReport`와 telemetry phase가 profile/pool hash, 시작/종료 LB, seed/local 평가, accepted 수, 중단 이유를 기록한다. S4 ON/OFF small oracle은 exact score·동점 ID가 같고 실제 425개 ON은 feasible report를 반환한다. 다만 1.5초 실제 실험은 추가 16,249회(profile 포함; seed 636/local 56) 뒤 coordinate와 같은 LB 14,089에 머물렀고 5초 gap 50.713%가 기본 단일 실행 49.294%보다 낫지 않았다. 따라서 당시에는 Worker 기본값을 OFF로 유지했으며, 이후 S7 성능 Gate 승격 결과는 아래를 따른다.

- D4 동적 점수 강한 초기해의 S5 탐색 순서(2026-08-28)를 완료했다. `toram.d4-dynamic-candidate-order.v1`은 S1의 모든 package ID를 유지한 채 full marginal DPS, 잔여 Utility 충족도, ID 순으로 결정적 `orderHash`를 만든다. `enableDynamicSeedOrdering: true` 실험에서만 이 순서로 candidate tree의 split 값 동점을 보조 정렬한다. candidate domain, split 축, envelope, 안전 상한, heap의 `upper → pathId` 우선순위, exact 종료는 불변이며 `dynamicSeedReport`가 order hash를 기록한다. S5 ON small exhaustive와 package 입력 반전은 oracle score·동점 ID가 같고, 같은 tree의 upper-bound/envelope audit도 위반 0건이었다. 실제 425개 1.5초 S4+S5 단일 5초 실행 두 번은 `7462a683` 순서표에서 bounded gap 42.594%·43.161%를 반환했지만 P95 승격 근거가 아니므로 당시 Worker 기본값은 OFF였고, 이후 S7 P95 결과는 아래를 따른다. 회귀: `node tools/test-d4-dynamic-marginal.mjs`, `node tools/test-d4-global-optimizer-stage2.mjs`, `node tools/test-d4-full-stage3.mjs`, `node tools/test-d4-browser-worker-runtime.mjs`.

- D4 동적 점수 강한 초기해의 S6 Replacement Proof(2026-08-28)를 완료했다. `createReplacementProofReport`는 동일 부위에서 compiler가 이미 내부 계보 충돌을 해결한 package끼리만 full stat effect vector·capped Utility·raw Utility·구조/조건/충돌/계보 서명·동점 ID를 모두 비교한다. 점수 차이 또는 평균 기회비용은 증명으로 쓰지 않으며, 미충족 항목은 `unprovenWitnesses`로만 기록한다. proven drop마다 scenario/witness/보존 서명/objective·utility·feasibility·replacement·tie-break proof/policy version/certificate hash를 가진 `d4-pruning-certificate.v1`을 남긴다. `applyProvenDropsForAudit`은 회귀용 복사본 축소일 뿐 compiler·Worker·기본 candidate domain에는 연결하지 않았다. 소형 fixture의 certificate 축소 전후 exhaustive score·동점 ID와 입력 순서 report hash가 같고, MAXMP raw·조건 서명 불일치는 제거를 거부한다. 실제 425개 prepared package 전체 proof scan도 comparison budget 안에 완료했다. 회귀: `node tools/test-d4-replacement-proof.mjs`, `node tools/test-d4-dynamic-marginal.mjs`, `node tools/test-d4-utility-dependencies.mjs`, `node tools/test-d4-browser-worker-runtime.mjs`.

- D4 동적 점수 강한 초기해의 S7 실제 425개 P95 승인(2026-08-28)을 완료했다. `tools/benchmark-d4-s7.mjs`가 실제 최종 강화 크리스타 425개 물리 근거리 fixture를 새 Node 프로세스 10회씩, 10초 제한으로 OFF·seed-only·seed+ordering·seed+ordering+proof-audit과 비교했다. core P95 / 인증 gap P95는 각각 OFF 10,146.5ms / 39.68%, seed-only 10,132.3ms / 40.34%, seed+ordering 10,133.3ms / 34.58%, proof-audit 18,490.0ms / 35.38%였다. 전부 bounded 10/10이고 exact·동점 oracle/property/determinism 위반 및 잘못된 삭제는 0건이다. seed+ordering은 core P95를 13.2ms 낮추면서 gap P95를 5.10%p 낮춰 승인됐으며, `d4-dynamic-seed-ordering.s7.v1`이 WorkerClient·Worker 기본값으로 S1~S5의 1.5초 bounded seed/결정적 split 동점 정렬을 연결한다. candidate domain·상한·heap·exact 종료는 불변이며, 명시 `enableDynamicSeedIncumbent:false`로 해제할 수 있다. proof audit은 report hash `f40f2179`, proven drop 0건과 약 8.3초 준비 비용이므로 계속 감사 전용이다. 회귀: `node tools/test-d4-worker-stage3.mjs`, `node tools/test-d4-browser-worker-runtime.mjs`, `node tools/test-d4-global-optimizer-stage2.mjs`, `node tools/test-d4-replacement-proof.mjs`, `node tools/test-d4-utility-dependencies.mjs`, `node tools/test-d4-dynamic-marginal.mjs`, 실제 425개 `test-d4-full-stage3.mjs`의 OFF·seed+ordering·proof-audit 실행.
