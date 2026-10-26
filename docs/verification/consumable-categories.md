# 소모품 카테고리 연결 검증 (2026-10-25)

보존된 releaseC/e99f6b32 원본의 카테고리 선언과 native 지속 계열을 연결했다. 게임 실행·소모품 사용·프로세스 추가 접근 없이 저장 자료만 읽었다. 공개 배포는 하지 않았다.

## 출처와 계약

- `data/sources/toram-items/consumable-categories.json`은15개 카테고리의 고정 ID·표시 이름·정규화 별칭·duration cap·원문 앵커를 보존한다. 각 앵커는 게임 ID와 한국어/일본어/영어 설명이며 원본 connected 카탈로그 SHA-256을 기록했다. 한국어는 번역을 새로 만들지 않고 실제 설명의 선언을 사용했다. 영문 원문이 없으면 null을 유지한다.
- 예: 플러스바이타Ⅰ/2000은 「HP 증가」, 애드매지클Ⅰ/2010은 「MP 증가」. 포무네 떡국3073의 `[마법력]` 선언도 읽는다. 전각 영숫자·공백·반각 가타카나는 NFKC로 비교하지만 원문/표시 이름은 보존한다.
- `convert-toram-project-items.mjs`는 사용할 수 있는 소모품의 한국어/일본어 설명에서 선언을 읽는다. 검토된 별칭이 일치하면 해당 카테고리, 선언이 없으면 duration cap에 연결한다. 언어별 선언이 충돌하면 변환을 차단한다. 미검토 선언·여러 duration 계열·계열 없는 즉시 회복은 카테고리 null을 유지한다.
- duration cap209~223의 이름/동작은 기존 `item-use-rules.json`과 `native-item-usage/BonusData`, `BonusScriptManager.funcSetTime`, `BonusManager.SetDurationBonus`의 해시 고정 근거를 재사용한다. 별도 서버 카테고리 마스터를 추출했다고 주장하지 않는다. REA Ghidra provider는 GHIDRA_INSTALL_DIR 미설정으로 사용할 수 없었으며, 새 native 분석 없이 기존 검토 C와 순수 파서로 대조했다. 이번 결과는 REA Evidence가 아니다.
- 카테고리 JSON은 pipeline contract의 `consumableCategories` 입력에 SHA-256으로 고정하고 가공 manifest의 `consumableCategoriesSha256`도 검사한다. 기존 원본/ready 보존·오류 시 이전 발행본 유지·오프라인 sync를 따른다.

## 검증 시점의 분류

| 표시 이름 | 연결 개수 | 기본 duration cap |
| --- | ---: | ---: |
| HP 회복 | 38 | 209 |
| MP회복 | 39 | 210 |
| HP 증가 | 38 | 211 |
| MP 증가 | 19 | 212 |
| 공격력 | 20 | 213 |
| 마법력 | 15 | 214 |
| 물리 방어 | 17 | 215 |
| 마법 방어 | 9 | 216 |
| 명중 | 14 | 217 |
| 회피 | 12 | 218 |
| 공격속도 | 13 | 219 |
| 영창속도 | 8 | 220 |
| 속성강화 | 8 | 221 |
| 속성방어 | 28 | 222 |
| 예방 | 12 | 223 |

합계290개이며 계산 가능한 단순 능력치 버프209개도 모두 카테고리를 가진다. 분류됐다고 미지원 스크립트를 계산 대상으로 승격하지 않는다. 예를 들어 예방 아이템2020은 도감에 분류를 보이되 기존 계산기 선택 범위는 유지한다.

**예외**: 라이브 바이타2965는 설명에 HP 증가라고 적혔으나 실제 duration cap은209다. 카테고리는 hp-boost로 연결하고 `durationCapId`·`buff.groupId=209`는 보존한다. 카테고리 이름으로 실제 중복 적용 키를 덮어쓰거나 게임에서 동시사용 가능성을 검증했다고 주장하지 않는다.

## 앱 연결과 검증

- `getItem(id)`와 `listBuffItems(locale)`에서 `consumableCategory`를 제공한다. 계산기 목록/미리보기는 `[HP 증가]`와 같이 표시하고 카테고리·이름·ID로 검색한다. 도감 정보 탭에도 카테고리를 표시한다. 저장 문서/계산 스냅샷에 표시용 메타데이터를 복제하지 않는다.
- `npm run items:test`:15개 카테고리의 모든 원문 앵커·209개 선택 가능한 버프 커버리지·플러스바이타/애드매지클·설명 없는 스피드 팟·미지원 예방·즉시 회복 제외·라이브 바이타 예외·언어 충돌/미검토 이름·category hash 거부·기존 계산/저장 동치 PASS.
- `node tools/tests/application/test-catalog-browser.mjs`:11,749개 상세·카테고리 표시 PASS. `npm run verify:architecture` PASS. `npm run test:regression`:78항목(77 PASS, 실제 앱 저장 E2E1 SKIP).
- Chrome1280×900 소스 및 배포 하위 경로: 카테고리 검색→HP/MP/마법력 목록·미리보기→적용→JSON 왕복 유지 PASS.390×844 폭 넘침 없음·카테고리 목록 표시 PASS. 도감 정보의 HP 증가 표시 PASS. pageerror/실행 assets 오류 없음. Browser plugin 부재로 설치된 Playwright를 사용했다.
- 개발/배포 가공본은 오프라인 sync 후 재실행 unchanged. 로그 `build/tmp/consumable-categories/`, 화면/검증 스크립트는 이 채팅의 `.codex/visualizations/2026/10/22/01a163bd-aabc-7c01-aa53-5a74fe86b873/`에 있다.

전체 소모품의 카테고리가 확보된 것은 아니다. 확인할 원문 선언/지속 계열이 없는 항목은 미분류로 남긴다. 실제 게임 소비·자동 만료·상태이상 사건은 이번 검증 범위가 아니다.
