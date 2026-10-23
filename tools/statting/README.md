# 옵션 부여 가상 입력과 경로 실험

게임 실행·쓰기·네트워크 요청 없이 저장된 원형 계산을 재현한다. 앱의 추천 기능과 별도다. Python 표준 라이브러리만 필요하며 전투 점수 검사는 기존 Node 앱 계산기를 사용한다.

```powershell
python tools/statting/self_check.py
python tools/statting/simulate.py tools/statting/example-input.json --output build/tmp/statting-trace.json
python tools/statting/experiment.py --samples 24 --seed 20261021 --output data/sources/toram-statting/experiments/2026-10-21
python tools/statting/experiment.py --samples 12 --equipment 20 --frames armor-atk-crit armor-atk-crit-stat armor-matk-crit armor-atk-dte armor-matk-dte armor-atk-crit-four-neg armor-matk-crit-four-neg --output data/sources/toram-statting/experiments/2026-10-21/armor
python tools/statting/catalog_sweep.py --output data/sources/toram-statting/experiments/2026-10-21/catalog-sweep.json
node tools/statting/score_probe.mjs data/sources/toram-statting/experiments/2026-10-21
python tools/statting/review_results.py data/sources/toram-statting/experiments/2026-10-21
```

이 PC에서는 `python`이 Windows Store 별칭이라 번들 인터프리터를 사용했다. [실험 보고서의 PowerShell 명령](../../docs/verification/toram-statting-experiments.md#7-재현과-검증)을 참고한다. 재실험은 다른 출력 폴더를 지정하면 기존 실행 결과를 유지할 수 있다. 기본/몸 결과에 사용한 Python 원본은 각 결과의 `implementation/`에 해시와 함께 보존했다.

실제 조사1,753개 입력·입력 내 중복 제거1,211,496경로, 소형 기준12건의 최대 경고율 일치다. 이는 최종 수치 추천의 전역 최적성 검증이 아니다. `review_results.py`는 저장 통계·입력 상한·원본/실행 코드 해시·예시 추적 재생을 검산한다. 기본과 몸 추가 결과 및 전투 probe가 모두 있는 폴더를 받는다.

`simulate.py` 입력의 한 `steps` 항목은 한 번의 실제 부여 행동이다. 각 항목은 `{bonusId,value}`의 변경 목록이며 값은 **부여 후 내부 옵션 값**이다. 증분이나 표시 문자열을 넣지 않는다. 같은 옵션을 여러 행동으로 나누려면 각 행동에 누적 목표 값을 적는다. 예를 들어 CR+1을 세 번 넣는 입력은 각 단계의 value가1,2,3이다. 반복은 실제로 한 번씩 계산한다.

장비 종류는8발도·9창·10한손·11양손·12활·13자동활·14지팡이·15마도구·16권갑·20몸이다. 시작 잠재력은 카테고리별 최고 기초 잠재력과 앱 예산840의 제작 스탯 배분에서 파생하며 직접 덮어쓰지 못한다. 부여자는325/TEC255, 세 강화 스킬은10/10/10, 가용8줄이다. 현재는 빈 제작품부터 시작한다.

중요: 제작 보정 +30%의 **정확한 원형 절삭 순서는 미확정**이다. `combined-floor`는 로컬 Smith 원문의 합산 설명을 통합 절삭으로 해석한 모델이고, `separate-floor`는 민감도 비교용이다. 단일/쌍 무기 시작값은138/128 대137/127, 몸은두모델132다. 둘 중 하나를 실제 게임 최대값이라고 증명한 것이 아니며, 모든 미확정 구현을 이 두 모델이 덮는다고 주장하지 않는다. 추적 JSON에 `startingPotentialNativeVerified:false`가 항상 들어간다.

부여 단계의 단위 비용·구간별 처리·TEC 반환·카테고리·각 연산의float32·절삭·실행 전 경고는 원형 번역을 사용한다. 방향별325상한·점유8줄·행동 전 잠재력1 이상도 검사한다. 기존8줄로 재진입, typed-zero/삭제, 부호 교차, cap 초과, overflow는 허용하지 않는다. 특수7타입12/22/24/26/28/30/32와 속성65의 요청 operand 왕복이 미확정이어서 거부한다. 이것이 게임에서 해당 기능이 불가능하다는 의미는 아니다.

`experiment.py`는 합법적인 고정 최종 옵션을 대상으로 경로를 비교한다. 마이너스 일괄/분할 선부여, 양수 선소진, 1pt 계열 분할, 소량 음수와 양수의 혼합 단계를 조사한다. 큰 도메인의 prefix 대표 선택은 근사이며, 선택되지 않은 경로를 불가능하다고 판정하지 않는다. `oracle.json`은 작은 단조 도메인의 모든 행동을 동적 계획으로 비교한 기준이다. 같은 옵션 상태에서 남은 잠재력이 큰 경로가 bounded 경고율을 악화시키지 않는 성질을 사용하며, 반전 확률·최소 행동 수의 최적성까지 증명하지 않는다.

`cases.jsonl`은 모든 조사 입력과 계열별 점수, 예시 JSON은 실제 입력과 펼쳐진 단계별 추적이다. summary의 `completedRoutes`는 중복 포함, `uniqueCompletedRoutes`는 같은 입력 안에서 행동열을 중복 제거한 수다. 서로 다른 입력·장비 간 동일 구조는 별도 사례로 센다. `noRouteFound`는 제한된 탐색의 미발견이며 불가능 증명이 아니다. 0으로 기록한 비교 점수에는 실행 불가/경로 미발견이 포함되므로 모두 성공률0이라고 해석하지 않는다.

경고율은 클라이언트 실행 전 판정이며 서버 완성 확률이 아니다. 실험은 실패·반전·슬롯 보호·소재 사용·실제 제작 RNG를 모사하지 않는다. 전투 점수 probe는 기존 앱 평가기를 사용하며, DTE 원시 키를 자동으로 ELEM_P로 바꾸지 않는다. 대상 속성 연결이 확인되기 전까지 DTE의 대미지 순위는 보류한다.
