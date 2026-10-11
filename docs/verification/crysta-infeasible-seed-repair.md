# 유효 초기해가 없는 경우의 수리

2026-10-11. Native v20. 계산·상한·후보 삭제 정책은 유지하고 초기해 경로를 보강했다. 카나요간 금지의 간헐적인 급격한 악화 자체는 원인 미확정이며, 이번 변경으로 그 현상이 해결됐다고 판정하지 않는다.

## 변경

기존 `initial_selections`의 시작 조합이 모두 요구조건을 못 채우면 단일 교환과 두 부위 초기해 개선을 건너뛰었다. `repair_infeasible_seed`는 이 경우에도 기존 damage/utility 후보 풀에서 실제 완성 조합을 평가한다. 다섯 Utility 목표의 정규화된 부족량을 줄이는 단일 교환, 제한된 두 부위 교환을 시도한다. HP/MP/AMPR/CRIT/ASPD의 파생·포화는 공통 `utility_values`를 사용한다.

부족량은 수리 순서에만 사용한다. 실수/음수/단계 경계를 반올림하거나 요구조건을 완화하지 않는다. 유효 조합은 기존 `consider`의 실제 요구조건·대미지 검사로만 하한에 채택한다. 유효해를 찾으면 기존 단일 교환·두 부위 대미지 개선도 수행한다.

기존 192개 후보 풀과 16개 pair 후보, 2회 개선 예산을 재사용했다. 제한된 수리에 실패하면 전체 exact 탐색을 유지한다. 수리 후보 밖의 실제 후보를 삭제하거나 불가능으로 판정하지 않는다. 이미 유효한 초기해가 있으면 수리 자체는 실행하지 않는다.

같은 후보의 고정 휴리스틱 점수를 정렬 비교마다 재계산하던 두 곳은 후보당 한 번 계산하도록 변경했다. 점수·정렬·동점 기준은 동일하다. 첫 구현의 전 후보 수리·정렬은 초기화 비용이 컸으므로 최종안으로 채택하지 않았다.

serial, standalone parallel, shared session 세 초기화 경로가 같은 함수를 호출한다. Native exact cache·checkpoint는 v20으로 구분하고 v19 이하 checkpoint를 거부한다. 평가 버전 v4·분기 정책 v6·앱 저장 schema·출시 버전은 유지한다.

## 실제 에투왈 잠금 입력

`%LOCALAPPDATA%/ToramOnlineAutoBuildCalculator/딜검방 샘플.json`을 읽기 전용 복사하고 Application/콤보 엔진으로 루브닐 타격을 조립했다. 에투왈 한 슬롯만 잠그고 HP 10,000 / MP 2,000 / AMPR 100 / 평타 CRIT 100 / ASPD 1,000을 유지했다. 금지는 기존 오로로 콜론에 카나요간만 추가한 입력이다. 저장 파일 hash와 분석은 `src-tauri/target/kanayogan-analysis/analysis.md`에 있다. 영구 측정 JSON에도 두 실행 입력을 보존했다.

1-worker 과정 로그에서 전에는 두 입력 모두 초기 `no-incumbent-yet`이었다. 수정 후에는 **방문 노드 0에서 이미 유효 초기해**가 있다.

| 초기 상태 | 허용 | 카나요간 금지 |
| --- | ---: | ---: |
| 초기해 점수 | 1,731,840.66 | 1,629,951.84 |
| 초기 evaluations | 17,529 | 17,519 |
| exact 최종 점수 | 1,753,977.72 | 1,726,210.26 |

최종 점수·전체 조합·raw 옵션은 기존과 같다. 금지 후 실제 최고점은 추가 고블린 주코토+로열 옥스킹 II / 특수 에투왈+저편의 잔영을 사용한다. root 상한은 변경하지 않았으며 초기해가 있어도 초기 인증 gap이 크거나 증명 완료까지 노드가 많이 필요할 수 있다.

## 동일 입력 반복 비교

원본: `crysta-infeasible-seed-repair-measurements.json`. AMD Ryzen 7 9800X3D / Node v24.17.0 / Windows release / 16 logical threads. 일곱 입력에서 전후 각각 10회, 총 140회 fresh Node/Native 프로세스를 순차·교대 실행했다. 측정 중 테스트·빌드는 실행하지 않았다. 아래는 v19→최종 v20 평균이다.

| 입력 | 방문 노드 | evaluations | Native 평균 ms |
| --- | ---: | ---: | ---: |
| 현재 저장·에투왈 잠금·허용 | 176,950.1→162,228.1 (−8.32%) | 827,743.7→798,995.9 (−3.47%) | 134.4→133.7 |
| 현재 저장·에투왈 잠금·카나요간 금지 | 174,004.6→167,083.8 (−3.98%) | 806,283.2→804,791.5 (−0.19%) | 131.5→138.1 |
| 기존 실제 루브닐·단일 잠금 | 177,943.3→163,257.8 (−8.25%) | 847,632.7→821,267.1 (−3.11%) | 136.5→139.8 |
| 기존 실제 평타·단일 잠금 | 167,663.0→153,627.8 (−8.37%) | 794,645.5→772,661.8 (−2.77%) | 134.0→135.4 |
| 기존 실제 루브닐·잠금 해제 | 701,366.9→701,364.6 (거의 동일) | 2,875,387.1→2,875,656.2 (거의 동일) | 490.1→418.9 |
| 과거 unlocked 회귀 | 166,377.1→161,250.4 (−3.08%) | 436,395.3→399,199.4 (−8.52%) | 117.0→119.5 |
| 과거 locked 회귀 | 25,487.9→25,313.0 (−0.69%) | 62,484.3→65,159.0 (+4.28%) | 53.4→56.3 |

140회 모두 exact 점수·전체 bestBuild·compiled/prepared hash·raw 합·최종 JS feasibility/점수가 같았다. 측정 스크립트는 이 동치와 전후 바이너리·소스 hash를 검증한다.

현재 금지 입력은 초기해 수리 비용으로 Native 평균 **6.6ms**, UI 제외 전체 평균 **6.87ms(+0.89%)** 늘었다. 초기 유효해 확보와 노드 감소가 모든 입력의 전체 시간 감소를 뜻하지 않는다. 잠금 해제 입력은 유효 초기해가 이미 있어 수리를 건너뛰고, 점수 정렬 재계산 제거로 Native 평균 **14.53%**, 전체 평균 **5.04%** 줄었다. 전체 P95와 메모리는 원본에 보존했다. 기존 실제 단일 잠금의 전체 P95 785.35→959.78ms도 포함하므로 전역적인 무퇴행을 주장하지 않는다.

Native peak 변화는 현재 금지 입력 +0.14MiB, 다른 입력 −0.16~−1.52MiB다. 25ms 간격 working set 관측이며 Node/JS와 UI 메모리는 제외한다. 평가 횟수를 전체 CPU 연산 수로 해석하지 않는다.

## 검증과 재현

- `cargo test --bin crysta_native_exact -- --test-threads=4`: 82 PASS. 두 시작 후보가 모두 infeasible이며 단일 교환으로 부족량도 줄일 수 없는 상호 보완 회귀를 추가했다. 방문 전 유효 초기해, 256개 전수조사·점수/동점 ID·후보 보존·역순 입력·1/2/4/8/16/64 thread·JSON checkpoint 재개·불가능 판정 확인.
- `node tools/tests/optimization/test-crysta-native-exact.mjs`: 소형 독립 JS oracle/미래 옵션/serial/parallel/shared session PASS. 기본 실행은 소형 검증이며 별도 실제 synthetic 모드는 이번 명령에서 실행하지 않았다. 실제 입력 exact는 위 반복 비교로 확인했다.
- `node tools/tests/optimization/test-crysta-native-client.mjs`: v20 cache/continuation 계약 PASS.
- `npm run test:regression`: 76/76 PASS. Native 저장 E2E는 CDP 미설정 SKIP.
- `npm run verify:architecture`, `cargo clippy --all-targets -- -D warnings`: PASS. evaluator/스킬/계산식 소스는 변경하지 않았다.
- `node tools/benchmarks/trace-crysta-search.mjs build` 후 `run --input ... --threads 1 --max-batches 100000`: 현재 허용·금지 모두 control/trace score·ID·방문/평가 동치, 사건 회계·최종 JS 재평가 PASS.

계측의 평가 회계는 초기화 전체 카운터를 기준으로 바꿔 초기해 수리·유효 초기해 없음의 개별 목표 검사를 포함한다. 이 회계 수정은 제품 카운터나 계산 결과를 변경하지 않는다.

비교 driver·원본 로그는 `src-tauri/target/seed-repair/`에 있다. `node tools/verification/summarize-crysta-seed-repair.mjs`로 전후 140회·최종 trace·소스 hash를 검증해 영구 JSON을 다시 생성한다. 예전 v19 공동 공급량 측정은 당시 기록으로 보존한다.

실제 UI/WebView 조작·설치/업그레이드·간헐 문제 자체의 해결 여부는 이번 검증에 포함하지 않는다. 어려운 입력에서는 제한된 수리가 유효해를 찾지 못할 수 있으며 그때도 기존 exact 탐색이 계속된다.
