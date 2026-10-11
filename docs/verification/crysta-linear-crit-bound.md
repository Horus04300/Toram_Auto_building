# CRIT·CRIT%의 같은 후보 공급량을 보존한 상한

2026-10-11. Native v17→v18 비교다. 현재 제품 상태는 [handoff](../handoff/current-development-handoff.md), 입력·소스/실행파일 hash·100회 결과·진단/과정 로그는 [측정 원본](crysta-linear-crit-bound-measurements.json)을 따른다. 이전 [두 장비 교환 초기해](crysta-pair-seed.md)를 유지한 상태에서 상한만 강화했다.

## 남은 병목과 변경

초기해는 실제 잠금 해제 검방의 최적 점수 약 99%까지 올라왔지만, v17은 exact 증명까지 약 281만 노드를 방문했다. 별도 직렬 진단에서 **알고 있는 최적 조합을 초기해로 넣어도** 2,812,033→2,527,969개 방문에 그쳤다. 이 대조 실험은 초기해만 더 높이는 것보다 상한의 느슨함을 줄이는 방향을 선택한 근거다. 다른 초기해/분기 정책의 개선율에 대한 수학적 한계는 아니다. 최적 조합을 제품에 주입하지 않는다.

기존 critical 상한은 현재 상자의 최고 CRIT%로 최소 flat CRIT 필요량을 정하고, 실제 패키지의 AMPR/flat CRIT/공격 옵션 지지값을 사용했다. 최고 CRIT%와 높은 flat CRIT가 서로 다른 패키지에 있어도 동시에 공급할 수 있는 것처럼 완화될 수 있었다.

v18은 지원하는 정수 입력에서 **flat CRIT와 CRIT%의 공동 공급량**을 패키지별로 계산해 같은 지지값 캐시에 넣는다. 자식 노드도 실제 패키지에서 얻은 공급량을 유지한다. AMPR 혼합 제약뿐 아니라 ATK%/MATK%·거리 대미지·CDMG 조건부 상한에 같은 관계를 반영한다. 별도의 대규모 Pair frontier나 새 방향 배열을 추가하지 않는다.

후보·raw 옵션·대미지/스킬 계산식·median 트리·두 축 분기·lookahead·smallbox 64·두 장비 초기해는 유지한다. 강화한 안전 상한으로 큐 순서와 살아남는 공간이 달라진다. 직렬·독립 병렬·제품 shared session의 공통 경로에 적용했다. Native engine/checkpoint v18, split policy v6이며 v4~v17의 현재/과거 checkpoint와 JS exact cache를 구분한다. 제품/앱 저장 버전은 유지했다.

## 증명과 적용 범위

평타 critical의 기존 evaluator를 기준으로 B는 준비한 base critical, p/f/r는 문맥의 critP/critF/bossCritResist, C/P는 후보들의 flat CRIT/CRITP 합이다. 양수의 유효 요구조건을 올림한 K에 대해:

```text
normalCritical = trunc(floor(B × (100 + p + P) / 100) + f + C − r)
goalCritical = clamp(normalCritical, 0, 100)
```

flat CRIT·f·r가 정수이고 요구조건이 0 초과 100 이하일 때, 만족 조건은 다음 선형 부등식과 동치다. 양수 목표 때문에 trunc가 음수를 0 쪽으로 당기는 경우는 만족 해가 될 수 없다.

```text
100C + BP ≥ 100(K + r − f) − B(100 + p)
g = gcd(100, abs(B)), s = 100/g, t = B/g
E = sC + tP
E ≥ R = s(K + r − f) − t(100 + p)
```

각 실제 패키지의 E를 먼저 계산한다. B가 음수여도 해당 패키지의 실제 P를 사용하므로 음수 계수의 방향을 잘못 뒤집지 않는다. B=0이면 s=1, t=0이다. B는 evaluator의 기존 준비 불변값을 읽으며 계산식을 별도로 복제하지 않는다.

기존 AMPR 필요량 A와 인코딩한 AMPR M, 공격 좌표 D에 대해 각 노드에 다음을 저장한다. k는 기존 1/2/4, a/c는 기존 7개 방향이다.

```text
U_g = max_package(k·s·D + a·s·M + c·E)
feasible: M ≥ A, E ≥ R
D ≤ floor((Σ U_g − a·s·A − c·R) / (k·s)) × coordinateUnit
```

공격/AMPR에 같은 s를 곱해 기존 방향의 상대 단위를 유지한다. Utility-only 지지값도 같은 E를 사용한다. 기존 raw envelope와 조건부 상한의 최솟값을 사용하며, 동점과 등호를 보존한다.

적용 조건은 B/p/f/r의 유한 정수·절댓값 1,000,000 이하, flat CRIT/CRITP 패키지 좌표의 기존 unit=1 정수 예산이다. 목표는 소수여도 올림해 처리한다. 필드의 누락/타입 기본값은 기존 evaluator와 같다. 소수·큰 값·기타 적용 조건 밖에서는 기존 CRITP bucket/외향 정수 완화 상한을 그대로 사용한다. 원시 값을 반올림하거나 제한하지 않는다. 비단조 AMPR은 기존처럼 CRIT 제약만 이용한다.

지원 예산에서 지지값·합·차는 절댓값 2⁴⁵ 미만의 정확한 정수이며 나눗셈의 정수 제수는 최대 400이다. 비정수 몫의 간격 1/제수는 해당 범위의 f64 ULP보다 충분히 크고, 정수 몫은 정확히 표현되므로 내림을 보존한다. 모든 제수 1~400의 큰 양수/음수 배수와 ±1 경계를 정수 `div_euclid` oracle로 검사했다. 최종 coordinateUnit은 기존 power-of-two다.

## exact 완료까지의 연산량

같은 현재 JS로 원시 입력을 컴파일·준비하고 Native client/service를 실행한 뒤 결과 복원·최종 JS 재평가까지 수행했다. AMD Ryzen 7 9800X3D / 16 logical threads / Node v24.17.0 / Windows release. 다섯 입력에서 전후 각 10회, 총 100회 새 Node/Native 프로세스를 순차 실행하며 순서를 번갈았다. 측정 중 테스트·빌드를 실행하지 않았다.

| 입력 | 방문 노드 평균 v17→v18 | 감소 | evaluations 평균 v17→v18 | 감소 |
| --- | ---: | ---: | ---: | ---: |
| 실제 루브닐·단일 에투왈 잠금 | 425,498.9→321,891.3 | 24.35% | 1,989,129.2→1,540,279.5 | 22.57% |
| 실제 평타·단일 잠금 | 406,288.9→308,793.7 | 24.00% | 1,895,221.4→1,474,390.5 | 22.20% |
| 실제 루브닐·잠금 해제 | **2,812,019.1→1,697,472.8** | **39.64%** | **11,422,067.7→6,924,626.6** | **39.38%** |
| 과거 unlocked 회귀 | 1,442,202.5→201,806.0 | 86.01% | 4,154,335.9→560,842.7 | 86.50% |
| 과거 locked 회귀 | 122,138.3→29,209.3 | 76.09% | 335,087.7→79,751.6 | 76.20% |

실제 잠금 해제 입력에서 약 **111만 방문·450만 평가 호출**을 추가로 절약했다. evaluations는 기존 제품 카운터이며 지원값 캐시의 산술·준비·정렬을 모두 세는 원시 명령 수가 아니다. 이 비율을 전체 CPU 연산의 낭비율로 해석하지 않는다. 이전 초기해 개선율과 더하지 않는다.

100회 모두 exact 점수·전체 bestBuild·compiled/prepared 입력 hash·raw 옵션 합·최종 JS feasibility/점수가 같았다. 실제 잠금 해제 점수 1,910,660.94, 단일 잠금 루브닐 1,753,977.72, 평타 67,120을 유지했다. 실제 saved fixture의 스탯·콤보·요구조건·잠금·금지를 변경하지 않았다.

과거 두 입력은 이전 불완전 콤보 회귀다. 이들의 76~86% 감소를 현재 사용자 빌드나 다른 무기의 대표 성능으로 사용하지 않는다. 현재 앱에서 편집 중인 입력이나 실제 듀얼 사용자 입력은 이번 측정에 포함하지 않았다.

## 과정 로그

같은 잠금 해제 입력·1 worker·10,000묶음 작업량 제한 trace를 비교했다. 초기해는 양쪽 모두 1,891,701.18로 같다.

| 항목 | v17 | v18 |
| --- | ---: | ---: |
| 루트 대미지 상한 | 4,787,082.36 | 4,431,465.48 |
| 관측 최대 미해결 상자 | 543,726 | 336,350 |
| 중단 시 frontier 상한 | 2,135,461.80 | 2,070,530.64 |
| 자식 점수 상한 탈락 | 1,194,592 | 1,764,947 |
| lookahead 재귀 | 335,843 | 459,711 |
| 방문 노드 | 656,693 | 780,352 |
| evaluations | 2,650,786 | 3,146,718 |

미해결 큐는 38.14% 줄었다. 그러나 묶음당 lookahead 실행량이 달라져 prefix 방문/평가는 늘었다. **39.64% 방문 감소의 근거는 같은 최적성 증명 완료까지의 전체 실행**이다. 이 제한 실행은 bounded이며, 전후 최선 점수는 초기해와 같다. `seedImproved`는 순위 계산의 임시 상태도 세므로 전역 incumbent 갱신 횟수로 쓰지 않는다.

## 시간·메모리 Gate

사용자의 과정/연산량 분석과 별도로 변경 Gate를 확인했다. 전체 시간은 원시 입력의 JS 컴파일·준비부터 결과 복원·최종 JS 평가까지이며 UI/WebView를 제외한다. peak working set은 Native만 25ms 간격으로 관측한 근사값이며 Node/JS 메모리를 제외한다.

| 입력 | Native 평균 ms 전→후 | 전체 평균 ms 전→후 | 전체 P95 ms 전→후 | Native peak MiB 전→후 |
| --- | ---: | ---: | ---: | ---: |
| 실제 루브닐·단일 잠금 | 178.5→145.4 | 816.1→783.0 | 851.6→829.2 | 26.03→25.98 |
| 실제 평타·단일 잠금 | 174.6→143.0 | 807.3→773.9 | 818.9→781.4 | 25.82→25.97 |
| 실제 루브닐·잠금 해제 | **1050.6→681.2** | **1992.1→1618.3** | **2020.9→1630.1** | **57.93→45.93** |
| 과거 unlocked 회귀 | 510.5→103.2 | 1250.9→843.5 | 1281.5→853.7 | 49.36→28.54 |
| 과거 locked 회귀 | 66.8→41.2 | 631.2→604.3 | 645.6→612.6 | 22.40→20.96 |

실제 잠금 해제에서 Native 평균 35.16%·전체 평균 18.77%·Native peak 약 12.00MiB/20.72% 감소했다. 같은 입력의 실제 UI 시간이나 모든 빌드의 개선율은 인증하지 않는다. 짧은 실행의 작은 peak 차이는 정밀한 메모리 변화로 해석하지 않는다.

## 검증·재현

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: 357개 PASS(86+79+79+21+92, 공유 모듈 중복 포함). 새 테스트는 공급자 충돌/새 infeasible 증명, feasible 추가 후 독립 완전 열거 oracle·1/2/8/64 threads 동치를 확인한다. 양수/음수/0 base critical·소수 목표의 선형 조건을 evaluator와 비교하고 소수/큰 좌표·기본 필드 fallback 및 나눗셈 내림 경계를 검사한다.
- 기존 모든 feasible 완성 조합의 모든 조상 상자에서 좌표/대미지 상한 coverage·reference bit parity, 물리/마법/원거리/발도/듀얼/AMPR 보정·비단조·소수/큰 옵션 property, 역순 입력·동점·1~64 threads·cancel/deadline/checkpoint/pause/resume Gate가 통과했다.
- `npm run test:regression`: 76/76 PASS. Native 저장 실기기 E2E는 CDP 미설정 SKIP이다. `npm run verify:architecture`, `cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`, fmt 및 S1 427/427 PASS.
- `npm run ai:audit`, `git diff --check`: PASS. handoff 12,253 bytes로 12 KiB 예산을 만족한다.
- `npm run bench:optimization:build`로 최종 release headless를 만들었다. 전후 반복 스크립트 원문·입력·소스/실행파일 hash와 결과를 측정 JSON에 보존했다. 로컬 원본은 `src-tauri/target/dramatic-bound/`이다. 기존 변경을 포함한 v17 baseline을 별도로 보존했으며 Git reset을 하지 않았다.
- `node tools/benchmarks/trace-crysta-search.mjs build` 및 `run`: control/trace 결과·직렬 카운터·회계·최종 JS 재평가 PASS. 생성 경로는 재실행 시 덮어쓰므로 고정 발췌는 측정 JSON의 `processTrace`를 따른다.
- `npm run bench:optimization -- --input tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json --repeats 1 --slice-ms 250 --output src-tauri/target/dramatic-bound/resume-actual.json`: 4 slice/3회 재개 후 exact 전체 조합·최종 JS 평가·현재 소스 hash 동치 PASS. 재개 시간은 일반 cold 평균에 합산하지 않았다.

설치 앱의 배포/재설치나 실제 화면 시간 측정은 이번 작업에 포함하지 않았다.
