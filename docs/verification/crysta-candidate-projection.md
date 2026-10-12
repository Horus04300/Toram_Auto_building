# 후보 준비 단계의 공급량 좌표

2026-10-12. `optimization-candidate-projection.v1`, Native/checkpoint v21, split v7, Worker client/parallel v3. 출시 v0.7.3·저장 schema·평가 v4는 유지한다.

## 표현과 적용

`prepareProblem`은 raw 중복 제거 후 현재 입력 전체의 기초값 범위를 구한다. 공통 계산기의 `candidateSupplyBases`는 기존 계산식에서 이미 계산한 기초값을 반환한다. 별도의 무기 계수표나 스킬 계산식을 만들지 않는다. 후보에는 실행 중에만 쓰는 `searchProjection`을 추가하며 원본 `statDelta` 객체, ID, 크리스타, 잠금, 구조·소켓·비용·충돌 정보는 유지한다.

기초값 B가 고정이면 후보의 공급 좌표는 `(B/g)·P + (100/g)·F`, g는 100과 모든 B의 최대공약수다. 이는 개별 후보를 반올림한 최종 수치가 아니다. 원본 옵션은 합산 후 기존 계산식으로 평가한다. 정수 좌표가 같은 후보는 모든 나머지 선택에서 같은 값을 만든다. 서로 다른 듀얼 주/보조 기초값에는 각각의 좌표를 보존한다.

| 묶음 | 기초값 처리 |
| --- | --- |
| STR/DEX/AGI/INT/VIT %/+ | 입력의 기본 스탯으로 고정 좌표 |
| CRIT %/+ | 기본 CRIT으로 고정 좌표 |
| WATK %/+ | 주/보조 무기 기본 공격력; 발도→공격 변환이 후보에 따라 바뀌면 raw |
| ATK/MATK %/+ | 스탯·stat-up·무기 공격력·변환 공급이 고정된 경우만 결합 |
| CDMG/MAXHP/ASPD/CSPD %/+ | 고정이면 결합; 스탯에 따라 바뀌면 기초값 구간 양 끝의 함수 좌표 |
| UNSHEATHE %/+ | 계산 단계가 달라 raw 유지 |

ASPD는 무기·레벨·STR/AGI 등의 최종 스탯·방어구 정책을 공통 계산기에서 해석한다. 같은 후보의 `%/+` 함수 `B·P+100·F`를 기초값 구간 양 끝에서 보존하므로, 다른 부위의 AGI% 등의 선택으로 상대 가치가 뒤집히면 두 후보가 모두 남는다. CDMG의 STR/AGI 분기와 HP의 VIT도 동일하게 범위를 계산한다. 구간은 독립 좌표 extrema를 사용한 안전한 상위 집합이며 도달 가능한 조합만으로 좁혔다고 주장하지 않는다.

신규 우열 삭제는 **다른 모든 대미지·스탯 좌표가 같은 클래스 안에서 HP/ASPD 함수가 구간 전체에 걸쳐 열등한 경우**로 제한한다. 동등 후보와 열등 후보의 대체자는 lexical ID가 앞서야 한다. STR/INT 증가, 음수 배율, 마법 분기를 단조 대미지 개선으로 가정하지 않는다. 기존 raw Pareto는 별도로 유지한다. 구조·비용·충돌이 다른 후보는 신규 규칙으로 합치지 않는다.

후보/입력의 소수, 안전 정수 예산 밖의 값, 가변 ATK/MATK, 알려지지 않은 변환은 해당 묶음 또는 전체를 raw로 보존한다. 사용자 지정 kernel/registry/evaluator도 변환을 끈다. 투영 비교 예산이 끝나면 미처리 후보를 모두 보존한다. 제품에 특정 샘플 이름·무기·크리스타 ID를 넣지 않았다.

JS와 Native 트리는 공급 좌표로 분기축과 후보 정렬을 선택한다. **상한, 지지값, 가지치기, 완성 조합과 최종 JS 평가는 원본 옵션을 사용한다.** Native는 좌표 길이/유한성 검사가 실패하면 raw 축으로 돌아간다. checkpoint는 좌표를 보존하고 트리를 재생성하며 구 정책 checkpoint는 거부한다. 결과 캐시에서 후보별 파생 좌표는 중복 hash하지 않지만 원본 옵션·후보 목록·입력·버전·변환 계획은 포함한다.

## 검증

- `node tools/tests/optimization/test-crysta-candidate-projection.mjs`: 72개 조건, 3,711개 독립 완성 조합, 324개 유효 대체 검사 PASS. 13쌍, 여러 무기·마법·듀얼·변환, 음수/소수/큰 값, ASPD 단계, 구간 교차, 예산 소진, 비용 차이, 역순·동점·원본 보존을 포함한다. 실제 JS 트리의 완전탐색 동치와 조상 상한도 확인한다.
- `cargo test --manifest-path src-tauri/Cargo.toml --bin crysta_native_exact -- --test-threads=4`: 83 PASS. 새 ordering 전용 좌표의 1/2/8/64 thread·JSON 재개·원본 결과·역순·비정상 좌표 fallback 회귀 포함. 기존 1~64 thread·상한·coverage Gate 유지.
- `node tools/tests/optimization/test-crysta-rust-native-parity.mjs`: 1,986개 JS/Rust 평가 동치 PASS. `node tools/tests/optimization/test-crysta-native-exact.mjs`: 소형 독립 oracle/serial/parallel/session PASS.
- `npm run test:regression`: 77/77 PASS. `npm run verify:architecture`, Native exact 대상 clippy `-D warnings`, S1 427/427 PASS. Native 저장 E2E는 CDP 미설정 SKIP.

## 실제 입력 계측

영구 원본은 `crysta-candidate-projection-measurements.json`, 실행기는 `tools/benchmarks/benchmark-crysta-candidate-projection.mjs`다. 이전 실제 입력을 raw로 보존한 7개 케이스의 동일 최종 코드/바이너리에서 변환만 끄고 켠다. 각 10회, 총 140회 fresh Node/Native 프로세스로 전후 순서를 번갈아 실행한다. 소스·바이너리 hash, exact, 최종 JS 요구조건/점수, 전체 조합/동점 ID/raw 합산 동치를 검사한다. 따라서 기존 v20 기록과 시간을 직접 비교하는 표가 아니다.

시간은 raw 컴파일부터 최종 JS 재평가까지이며 UI는 제외한다. Native 메모리는 살아 있는 프로세스의 Windows `PeakWorkingSet64`, JS 메모리는 결과 시점의 heap이며 peak가 아니다. evaluations는 탐색 평가 횟수이지 모든 CPU 명령의 수가 아니다. 실제 UI/WebView·설치/업그레이드는 이번 검증에 포함하지 않는다. 이 샘플 집합의 결과를 모든 미래 입력의 성능 보장으로 사용하지 않는다.

AMD Ryzen 7 9800X3D / Windows / Node v24.17.0 / 16 logical threads, release Native. 비교 중 다른 테스트/빌드를 실행하지 않았다. 평균값은 다음과 같다.

| 입력 | 방문 노드 전→후 | 평가 횟수 변화 | Native ms 전→후 | 전체 ms 전→후 | Native peak MiB 전→후 |
| --- | ---: | ---: | ---: | ---: | ---: |
| 현재 에투왈 잠금·허용 | 162,228→143,054 (−11.82%) | −22.89% | 133.0→110.8 | 576.05→655.98 | 31.01→30.02 |
| 현재 에투왈 잠금·카나요간 금지 | 167,082→123,415 (−26.14%) | −30.54% | 135.6→102.1 | 573.34→643.92 | 31.69→29.91 |
| 기존 실제 루브닐·단일 잠금 | 163,265→144,321 (−11.60%) | −23.66% | 134.3→110.9 | 575.94→651.48 | 30.91→30.02 |
| 기존 실제 평타·단일 잠금 | 153,621→133,766 (−12.92%) | −24.42% | 130.1→108.2 | 568.45→651.38 | 30.93→29.93 |
| 실제 루브닐·잠금 해제 | 701,365→651,967 (−7.04%) | −10.44% | 408.1→366.8 | 1,021.69→1,133.76 | 46.14→45.14 |
| 이전 분석 루브닐 | 161,242→167,490 (+3.88%) | −4.14% | 118.0→114.1 | 641.54→772.86 | 34.33→37.59 |
| 이전 분석 루브닐·잠금 | 25,318→24,781 (−2.12%) | +4.12% | 56.3→52.9 | 460.49→558.87 | 26.31→27.45 |

현재 허용/금지는 탐색 축 **25→18**, 잠금 해제는 **27→20**이다. 현재 금지 후보는 `[1372,1155,1114,54]`→`[1186,1063,1029,52]`, 합계 **3,695→3,330 (−9.88%)**. 평가는 **804,722→558,987**이다. 금지 최적 점수 **1,726,210.26**, 허용 **1,753,977.72**와 전체 조합·동점 ID·raw 합산이 전후 140회 동일했다.

압축 준비·후보 분류·좌표 전달의 추가 비용 때문에 전체 평균은 **+10.97~+21.37%**다. 현재 금지는 **+70.58ms (+12.31%)**, 전체 P95는 **580.09→667.58ms**다. 반면 Native 평균은 **−24.71%**, Native peak는 **−1.78MiB**다. 오래된 두 입력은 거의 후보가 줄지 않고 좌표/전달 비용이 늘어 peak도 증가했다. 따라서 입력 차원 감소를 전역적인 시간·메모리 무퇴행이나 모든 입력의 방문 감소로 해석하지 않는다. 전처리 비용 감소는 남은 성능 과제다. 캐시 hit는 이 cold 비교에서 제외했다.

재현:

```powershell
node tools/benchmarks/benchmark-crysta-computation.mjs build
node tools/benchmarks/benchmark-crysta-candidate-projection.mjs --repeats 10
```
