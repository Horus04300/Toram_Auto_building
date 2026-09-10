# 무기·스탯별 크리스타 추천 검증 — 2026-09-09

## 판정

2026-09-10 사용자 승인에 따라 외부 근거의 4개 계수를 JS·Rust 계산기에 반영했다. 권갑 STR→ATK는 0, 선풍창 MATK의 스탯 항은 INT×2+AGI+DEX, 발도검은 INT×1.5+DEX다. Native 계산 버전을 v2로 올려 기존 결과·continuation 캐시와 구분한다. 아래 초기 불일치는 수정 전 기록이며, 현재 검증 결과는 마지막 절에 구분한다.

## 독립 근거와 재현

- [Coryn Club 계산기](https://www.coryn.club/stat_calculator.php)의 공개 v4.7 JS: `https://www.coryn.club/stat_calculator_v4_7.js?v=1777279594`, 무기별 계산 분기 1467~1555행. 2026-09-09 다운로드 SHA-256 `2835016489F171BE378EFCF37A9A3987A3E2F552A11181BDE50CF2A312DEE6F2`.
- [무기별 스탯 직접 측정 기록](https://wikiwiki.jp/trm/武器とステータスの関係): 각 스탯을 1→255로 올렸을 때의 변화 기록. 권갑 STR의 ATK 증가 없음, 선풍창 INT의 MATK +508 및 AGI +254, 발도검 INT의 MATK +381로 위 계수와 일치한다. 오래된 직접 측정 기록이며 최신 게임 클라이언트 실측은 아니다.

수정 전, 다른 조건을 고정하고 해당 스탯을 1→101로 변경한 JS 계산 결과:

| 무기 | 입력 변화 | 수정 전 코드의 증가 | 외부 근거의 증가 |
| --- | --- | --- | --- |
| 권갑 | STR +100 | ATK +50 | ATK +0 |
| 선풍창 | INT +100 | MATK +300 | MATK +200 |
| 선풍창 | AGI +100 | MATK +0 | MATK +100 |
| 발도검 | INT +100 | MATK +300 | MATK +150 |

코드 위치: `assets/js/calculator.js:353`~355, `src-tauri/src/d4_native_evaluator.rs:177`~179. 수정 전 JS와 Rust가 같은 잘못된 계수를 사용했으므로 기존 parity만으로는 발견되지 않았다. 권갑 STR은 크리티컬 대미지에도 영향을 주므로 ATK 직접 기여가 0이라는 사실이 STR의 대미지 기여 전체가 0이라는 뜻은 아니다.

한손검·양손검·활·자동활·지팡이·마도구·맨손은 이번 **증가량** 비교에서 차이가 없었다. 기본 상수·모든 버프·무기 옵션·반올림 경계까지 외부 계산기와 일치한다는 판정은 아니다. 듀얼소드는 현재 엔진의 주/보조 ATK와 보조 안정률 합산을 대상으로 내부 검증에 포함했으며, 외부 일반 ATK 표와 직접 비교하지 않았다.

## 검증 설계

`node tools/audit-weapon-stat-recommendations.mjs`:

1. 10종 주무기 + 한손검/보조 한손검의 듀얼소드, STR/INT/VIT/AGI/DEX 집중 투자, PHYS/MAG 두 기준 = 110개 입력.
2. 각 입력에서 실제 데이터의 무기 크리스타 후보를 사용한다. 무기 슬롯 하나만 열고 나머지 7개는 빈 잠금으로 고정하여, 91개 패키지를 원시 전수조사한 최고 점수·동점 ID와 exact 추천을 비교한다.
3. 추천 패키지의 실제 크리스타를 full 계산기로 재평가하여 표시용 ATK/MATK와 목적 점수를 확인한다.
4. 같은 110개 입력에서 8슬롯 전체 잠금을 풀고 실제 후보 전체를 사용하는 빠른 추천을 생성해 다시 full 계산한다. 빠른 추천은 heuristic이며 전체 후보 최적성 증명은 아니다.
5. 91개 패키지 × 110 입력 = 10,010건을 Rust summary bridge에 보내 기대 대미지·HP/MP/AMPR/평타 크리/ASPD를 JS와 비교한다. 이 native bridge는 개발용 프로세스이며 이번 검사는 WebView UI E2E가 아니다.
6. 외부 자료에서 독립적으로 옮긴 계수 표와 실제 계산기의 증가량을 비교한다. 110개 단일 슬롯 문제의 모든 부분해 상한도 검사한다. 수정 전 민감도 분석용 복제 계산기는 제거했다.

중립 fixture는 기존 native parity의 base를 재사용한다. 레벨 325, 기준 스탯 1, 집중 스탯 500, 물리/마법 방어 0, 스킬·버프 변환 없음, 모든 Utility 요구조건 해제다. 무기 ATK/제련 등은 무기 간 현실적인 장비 세팅 비교가 아니라 동일 조건의 계산 경로 검사용 값이다. 특히 맨손을 실제 장착 가능 장비와 비교하는 추천표가 아니다. 일반 사용자의 복합 스탯·보스·스킬·버프·요구조건에 대한 모든 조합을 대표하지 않는다.

추천 목적은 ATK 또는 MATK 수치 자체의 최대화가 아니라 **선택 타격의 기대 대미지**다. 물리 기본은 ATK, 마법 기본은 MATK를 사용하며 `sum`, `higher`, `atk`, `wizardBlend` 등 스킬별 예외가 있다. 따라서 지팡이라고 무조건 MATK 크리스타만 추천해야 하는 것은 아니다. 이번 매트릭스는 기본 PHYS/MAG이며 특수 혼합 타격 전체는 별도다.

## 수정 전 실행 기록

- 신규 매트릭스: 단일 슬롯 exact/oracle/full 재평가 110건 일치, 전체 8슬롯 빠른 추천/full 재평가 110건 일치, Rust summary 10,010건 불일치 0. 독립 계수 4건이 달라 감사 명령은 종료 코드 1이다.
- `node tools/audit-weapon-stat-recommendations.mjs --single-slot`: 전체 8슬롯 빠른 추천을 생략하고 후보 쌍의 순위를 추가 비교했다. 110개 중 10개 입력에서 두 후보의 우열이 뒤집혔다. 단일 슬롯 전체 후보의 1위가 바뀐 입력은 0개였다. 이 둘을 혼동하지 않는다.
- 예: 권갑/STR 500/PHYS에서 `고블린 형님`과 `라갈 브라조`의 현재 점수는 3173/3174다. 권갑 STR→ATK 계수만 0으로 바꾸면 2861/2853이어서 우열이 뒤집힌다. 이들은 전체 후보 1위가 아니며, 최종 8슬롯 추천이 실제로 바뀌었다고 주장하지 않는다.
- 다른 예: 권갑/AGI 500/PHYS의 `드라케올`/`블라미스`가 3816/3812에서 3811/3812로 역전됐다. 집중 투자하지 않은 STR도 크리스타의 STR 옵션에 의해 차이를 만들 수 있다.
- `node tools/test-d4-rust-native-parity.mjs`: 기존 1,488건 통과.
- `node tools/test-d4-recommendation-apply.mjs`: 빈/값 있는 잠금·용량 검증 통과.
- 전체 원본 결과는 `src-tauri/target/weapon-audit/report.json`, 후보 쌍 분석은 `ranking-analysis.json`, 공개 근거 캐시는 같은 폴더의 `coryn.js`와 `coryn.html`이다. Git 제외 산출물이다.

## 수정 후 검증 — 2026-09-10

- `node tools/audit-weapon-stat-recommendations.mjs --single-slot`: 외부 계수 불일치 0, 110개 exact/oracle/재계산·상한 검사 통과, Rust 10,010건 불일치 0. 결과는 `single-slot-regression.json`.
- 발도검 MATK 업 회귀 기대값: 레벨 100 + 전체 INT 200×1.5 + 기본 INT 100×10% = 410. 스킬 적용 대상은 그대로다. INT 1/2/255/500의 최종 내림 경계와 Rust 스탯 항도 고정 기대값으로 검증했다.
- `node tools/audit-stack-source-links.mjs --require-s1`: 427/427 출처 연결 통과. 이는 스킬 수치 전체나 전투 시뮬레이션 완료 판정이 아니다.
- `cargo test --manifest-path src-tauri/Cargo.toml`: 79건 통과(여러 실행 대상의 합계).
- 이번 수정 후 설치 파일 빌드·실제 WebView E2E는 재실행하지 않았다. 앞선 데스크톱 E2E는 수정 전 빌드의 기록이다.

- 전체 매트릭스: 수정된 제품 계산기로 단일 슬롯 exact/oracle/재계산 110건, 전체 8슬롯 빠른 추천 재계산 110건, Rust 10,010건 통과. 이 실행은 민감도 검사 제거 전 감사 스크립트로 실행했으므로 `report.json`의 rankingChanges/pairOrderChanges=0은 수정 전후 순위 비교 결과로 해석하지 않는다.
- `npm run test:r0`: 69개 프로세스 종료 성공(68개 통과, native 저장 E2E 1개 SKIP). 기존 D4 oracle·상한·parity 포함. `cargo fmt --manifest-path src-tauri/Cargo.toml --check` 통과.
