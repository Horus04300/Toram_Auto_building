# 크리스타 ID 카탈로그 계약

이름·설명·옵션·조건·강화 전 ID는 게임 ID별 단일 shard를 사용한다. 화면·계산·추천은 같은 객체를 읽고, 저장/잠금/금지 문자열은 명시적 alias로 해석한다. 전체 계약은 ../architecture/item-data-format.md, 발행 건수와 마지막 검사는 ../handoff/current-development-handoff.md를 따른다.

## 데이터와 계산

- 일반/조건 cap·operand·float32와6언어 원문을 options에 보존한다. previousId는 부모 존재·동일 카테고리·cycle을 검사한다. type36 빈 아이템은 선택/추천에서 제외한다.
- 댄드라이언9776은 MAXMP500·AMPR4·CSPD300, 경량옷 STABILITY6, 이전9900이다. G이코노스9911의 CHARGE_RED는 원본10을 사용한다. 이름 alias는 수치 보정용이 아니다.
- 번역 이름 충돌은 별칭 조회에서 제외하고 ID 객체는 보존한다. 이름 유사도/스탯으로 ID를 추정하지 않는다.
- cap168/174는 ATK_UP_VIT/MATK_UP_AGI다. cap164/165는 넘어짐/기절 부여정지이며 속성 각성/마력속성으로 해석하지 않는다. 미소비 효과는 notModeled로 보존·표시한다.
- fullyMapped는 키 연결 범위다. 피격/전투 사건 지원이나 모든 효과의 수식 완료를 뜻하지 않는다.

원문 계보·token·pointer·스냅샷 해시는 data/sources/toram-items/native-crysta-lineage/를 따른다. 실제 설치 코드/규칙/미연결 효과가 바뀌면 발행을 차단하고 기존 manifest를 유지한다.

## 검증

- npm test: 전수 ID/옵션/조건·이전 이름·부모/순환·float32·발행 hash·장비/소모품.
- test-crysta-catalog.mjs: 원본/Application/compiler 동치, ID/영문 잠금·금지, raw 소형 완전탐색과 실제 WASM의 점수/동점 ID.
- test-evaluator-integration.mjs·test-crysta-rust-native-parity.mjs: 독립 JS oracle과 full/summary/supply·Native.
- web:build 뒤 npm test -- browser: 실제 UI/Worker exact·중단/재개/취소·JSON/재열기·하위 경로·병렬/단일 fallback.

검사 파일은 tools/tests/ 아래에 있다. 기능 검증과 전체 입력의10초 exact/P95 보증을 구분한다.
