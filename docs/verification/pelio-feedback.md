# 사용자 샘플 검증 범위

입력은 samples/의 빌드 JSON과 사용자 원문이다. 제공되지 않은 당시 조합·타격·설치 버전의 화면 결과를 추정하지 않는다. 현재 알려진 스킬 계산 전달 문제는 skill-calculation-wiring-audit.md, 기능 결정/보류는 unimplemented.md를 따른다.

- 매직 캐논은 충전량을 타격별20단위로 분배하고100 초과는 첫 타격부터 순환한다. 200충전 지팡이 샘플의 패시브·콤보 포함 타당 계수28.215와 전체 합은 다른 값이다. 원문은 ../sources/skills/Magic.txt다.
- 라지 페루루·죠코 비교는 같은 입력에서 해당 효과만 바꿔 확인한다. 추천 전체 교체는 다른 크리스타의 CRIT/CRIT%까지 함께 바뀌므로 단순 옵션 차이와 구분한다.
- 결계는 지팡이/메인 마도구·수동 ON의 행동속도를 빌드/추천에 전달한다. 콤보는9칸이며 포인트·레벨/전투 사건은 별도 보류다.
- 요구조건은 사용자 수치 입력·적용·저장·복원을 지원한다. 결과 탭 복귀·이름/검색 편집 같은 비계산 사건은 정밀 결과/continuation을 폐기하지 않는다.

`node tools/verification/check-pelio-feedback.mjs`는 실제 저장 파서·Application·커널을 사용하는 샘플 검사를 실행한다. 콤보/결계는 test-combo-ui-loading.mjs·test-magic-regression.mjs, 추천 수명은 test-crysta-resume-ui.mjs가 검사한다. 개별 계산 검사에는 node tools/build-wasm.mjs 선행 실행이 필요하다. 위자드 S1 연결을 누락 수식의 S4/S5 완료로 해석하지 않는다.

MEL/LUK, 공격 카드의 보존 스탯 표시 확대와 탱커 추천은 현재 지원 범위 밖이며 별도 기능 결정이 필요하다.
