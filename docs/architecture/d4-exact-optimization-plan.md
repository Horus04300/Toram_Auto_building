# D4 전역 최적화: 10초 exact 구현 계획

- 상태: Gate 0~D 완료, Gate E 상관관계 상한 1~4차 안전 검증 및 성능 Gate 종료(기본 비활성), Gate F 종료(10초 exact 미달). 병렬화는 P0/P1 완료·P2 JavaScript pool 불승격·P3~P8 Rust CPU 기본 경로 및 패키징 완료. 단, native runtime의 deadline·실제 progress·bounded checkpoint/resume·tail·잠금 크리스타 통합 Gate는 미완료이며 `d4-native-runtime-correction-plan.md`의 N0~N6를 따른다.
- 기준일: 2026-08-30
- 적용 범위: 현재 지원되는 425개 크리스타, 네 장비 부위, 각 2슬롯, 고정 Build/Scenario
- 상위 문서: d4-build-optimizer-design.md, d4-build-optimizer-prerequisites.md
- 참조 의무: D4 정확성·성능·후보 탐색 구현은 이 문서를 먼저 읽고 Gate 결과를 따른다.
- 후속 강한 초기해 계획: `d4-dynamic-score-exact-acceleration-plan.md`. 동적 점수는 feasible 하한과 탐색 순서에만 사용하고, 후보 삭제는 별도 Replacement Proof 또는 안전 상한 증명이 있을 때만 허용한다.

## 1. 목표와 불변 계약

목표는 좋은 추천이 아니라 전역 최적임을 증명한 exact를 콜드 캐시 기준 10초 안에 반환하는 것이다. 시간에는 후보 컴파일과 탐색을 포함한다. 측정 PC·Node/WebView 버전·후보 데이터 버전을 기록하고 동일 입력 10회 P95를 사용한다.

- exact는 탐색 큐가 비었거나 모든 미탐색 상한이 최고 실제 점수 이하일 때만 반환한다.
- 증명하지 못하면 bounded와 인증 gap을 반환한다. 거짓 exact는 금지한다.
- 지배 판정·상한·Pair Frontier는 소형 oracle 및 상한 property를 통과한 경우에만 활성화한다.
- 계산식·후보·제약·정책 버전 변경 시 캐시를 무효화한다. 학습 모델이나 과거 결과 추적은 사용하지 않는다.
- 입력 순서와 Worker 순서가 달라도 동점 ID 규칙과 최종 결과는 같아야 한다.

## 2. 현재 근거

기존 탐색은 실제 425개 기준 10초에도 bounded, gap 약 36.1%였고 60초에도 gap 약 19.1%였다. 병목은 서로 다른 후보의 ATK·크리티컬·관통·Utility 최고값을 하나의 가상 만능 후보처럼 합친 독립 envelope다. 실제로 불가능한 상한이 높게 남아 가지치기가 늦다.

방어구는 HP 공급이 강하고(2슬롯 조합 상위 10% +7,000, 최대 +20,000), 특수장비는 MAXMP·AMPR 공급이 집중돼 있다. 추가장비는 ASPD·크리티컬 공급이 강하다. 따라서 방어구+특수 / 무기+추가는 우선 검증 가설이나 모든 시나리오의 고정 규칙은 아니다.

### Gate 0 기준선 결과 (2026-08-25)

- 명령: node tools/benchmark-d4-exact.mjs
- fixture: full-425-physical-short-baseline — 실제 425개 크리스타, 물리 근거리, 발도 미사용, 기본 Utility 충족
- 환경: Node v24.17.0, Windows x64, AMD Ryzen 7 9800X3D(논리 16코어)
- 콜드 Node 프로세스 10회, 회차당 탐색 예산 10,000ms: exact 0/10, bounded 10/10
- compile + search P95: 10,152.0ms (외부 프로세스 시작 포함 P95: 10,239.5ms)
- 하한은 14,089로 같았고, 인증 gap 범위는 38.008%~39.385%였다.
- 판정: 현재 10초 예산은 정확해 목표를 달성하지 못한다. 이 결과는 실패 회귀가 아니라 Gate A~F 개선 전 비교 기준이며, 아직 D4_BENCH_REQUIRE_EXACT=1 또는 10초 P95 강제 조건을 켜지 않는다.

### Gate A 결과 (2026-08-25)

- 정책 버전: d4-utility-dependency.v1. d4-source-profile.js가 Utility별 stat 키, 목적함수·파생·조건 의존성, residual 포화 규칙을 반환한다.
- 현재 모델의 결론: 조건이 선언되지 않은 MAXHP만 cap-to-residual 후보이고, MAXMP는 AMPR 파생, AMPR은 통상·듀얼소드 분기, 크리티컬은 점수·제약, ASPD는 행동속도 파생 때문에 모두 preserve-raw다.
- 시나리오 metadata의 utilityDependencyOverrides는 HP/MP 비례 스킬 같은 조건 의존성을 선언하면 해당 축의 포화를 즉시 금지한다.
- 이 Gate는 후보 삭제·Pareto 축약·상한·캐시 키에 아직 적용하지 않는다. 따라서 추천 결과는 바꾸지 않으며, Gate B에서 residual 지배 증명에만 연결한다.
- 회귀: node tools/test-d4-utility-dependencies.mjs, node tools/test-d4-global-optimizer-stage2.mjs, node tools/test-d4-full-stage3.mjs 통과.

### Gate B 결과 (2026-08-25)

- 정책 버전: d4-supply-difficulty.v1. 실제 평가기로 각 부위 2슬롯 패키지를 단독 적용해 Utility 변화와 DeltaLogDamage를 측정한다. 결과는 pair 순서·초기해·후보 정렬용 heuristic이며, 독립 부위 최대값을 조합한 feasibleByIndependentGroupMax도 삭제·상한의 증거가 아니다.
- 의도적으로 Utility가 부족한 425개 후보 fixture에서 HP residual 7,480은 단독 충족 패키지가 290개, ASPD residual 286은 762개였다. 반면 MAXMP residual 1,575, AMPR residual 86, 평타 크리티컬 residual 75는 단독 충족 패키지가 모두 0개여서 부위 결합이 필요하다.
- 공급 집중도는 HP 0.4796, MAXMP 0.3333, AMPR 0.3509, 크리티컬 0.3291, ASPD 0.4096으로 기록했다. 각 Utility에 DPS/다른 Utility 중첩 공급원이 많으므로, HP 또는 Utility 상한만으로 후보를 삭제하면 안 된다.
- safeResidualDominance는 구조·조건·충돌·계보 서명, 슬롯 비용, 목적 좌표, capped Utility, raw Utility, 엄격 우위 또는 ID 동점 규칙이 모두 제공·충족될 때만 proven을 반환한다. 하나라도 빠지면 삭제를 거부한다.
- 이 Gate는 측정·증명 함수와 CLI만 추가했고 Pareto 삭제에는 연결하지 않았다. 다음 Gate C에서 세 Pair 분할을 실제로 비교한다.
- 회귀: node tools/test-d4-utility-dependencies.mjs, node tools/analyze-d4-supply-difficulty.mjs, node tools/test-d4-global-optimizer-stage2.mjs, node tools/test-d4-full-stage3.mjs, node tools/test-d4-browser-worker-runtime.mjs 통과.

### Gate C 결과 (2026-08-25)

- 정책 버전: d4-pair-partition.v1. 세 분할을 원시 후보 수·현재 시나리오의 Pareto 뒤 후보 수·활성 Utility가 단일 Pair에서 충족되는지로 비교하며, 동률은 최대 Pair 수 → 총 Pair 수 → coverage → ID 순으로 결정한다. 이 순서는 결과만 결정할 뿐 후보를 삭제하거나 상한을 낮추지 않는다.
- 실제 425개·Utility 부족 fixture: 원시 후보는 무기 4,000 / 방어구 3,319 / 추가 3,914 / 특수 3,740, 준비 후보는 1,672 / 1,310 / 1,648 / 1,572였다. 선택은 방어구+무기 / 추가+특수였다(최대 2,590,656, 총 4,780,976 prepared Pair). 사용자 가설 방어구+특수 / 무기+추가는 최대 2,755,456, 총 4,814,776이었다.
- 세 분할은 모두 활성 Utility 1개가 한 Pair만으로는 충족되지 않았고, 어느 Pair도 250,000 물질화 한계 안에 들지 않았다. 따라서 선택은 lazy-box이며 Pair Frontier를 만들거나 Frontier 크기를 추정하지 않았다. Gate D는 실제 지연 생성/상자 탐색을 구현한 뒤에만 Frontier 크기·시간을 측정한다.
- 분석 전체(공급 측정 + Pareto 준비 + 분할 비교)는 2,985.2ms였다. 현재 전역 탐색·추천 결과는 바꾸지 않았고, 이 값은 Gate D의 순서·분기 입력일 뿐 exact 증거가 아니다.
- 회귀: node tools/test-d4-pair-partition.mjs, node tools/analyze-d4-pair-partitions.mjs, node tools/test-d4-browser-worker-runtime.mjs, node tools/test-d4-global-optimizer-stage2.mjs, node tools/test-d4-full-stage3.mjs 통과.

### Gate D 결과 (2026-08-25)

- 전역 탐색기는 Pair Frontier 정책을 실제 하한 후보에 연결했다. Pair 후보 수가 8,192 이하이면 두 부위의 모든 합계를 만들고, strictParetoFrontier가 완결됐을 때만 축약된 Pair 후보를 평가한다. 이 후보는 초기 하한만 올리며, 탐색 공간·안전 상한·exact 판정은 바꾸지 않는다.
- Pair가 8,192개를 넘으면 기본값은 lazy-deferred다. 24×24 결정적 공동 시드(enableLazyPairSeeds:true)는 구현·oracle 검증을 마쳤지만, 실제 425개 fixture에서 1,250회 평가를 추가하고 하한을 14,089에서 올리지 못했다. 따라서 성능을 악화시키는 기본 활성화를 하지 않았으며 Worker 공개 옵션에도 넣지 않았다.
- 작은 Frontier, 큰 Pair 기본 보류, 명시적 lazy seed 각각은 소형 exhaustive oracle과 같은 점수·동점 ID로 회귀했다. 실제 425개는 Frontier가 모두 큰 분기여서 기존과 같은 초기 평가 1,511회·첫 유효해 61ms를 유지하고 bounded gap 45.539%였다. 이 결과는 시간 변동을 포함한 한 번의 확인값이며 10초 exact 개선 증거가 아니다.
- 다음 분기: Gate E가 Pair 상관관계를 보존하는 안전 상한을 제공해 실제 큰 Pair를 가지치기에 쓸 수 있을 때만 지연 Pair 생성 재측정·재활성화를 검토한다.
- 회귀: node tools/test-d4-pair-frontier.mjs, node tools/test-d4-full-stage3.mjs, node tools/test-d4-browser-worker-runtime.mjs, node tools/test-d4-global-optimizer-stage2.mjs 통과.

### Gate E 상관관계 상한 1차 결과 (2026-08-25)

- Pair 상관관계 2×2 상자는 선택된 두 부위 트리를 서로 겹치지 않게 분할하고, 각 상자가 포함하는 모든 완성 조합을 작은 exhaustive oracle로 대조했다. 새 verifyPairCorrelationUpperBounds와 Pair Frontier 회귀에서 상한 위반 0건, exact 점수·사전식 동점 ID 일치를 확인했다. 실제 425개 후보에서는 모든 그룹 트리의 부모·자식 envelope 단조성 19,732건도 위반 0건이었다.
- 루트 상자를 최댓값 하나로 합치지 않고 독립 큐 분기로 보존하는 실험도 oracle을 통과했다. 하지만 같은 5초 조건의 실제 fixture에서 기준 44.900% 대비 2×2 45.262%, 3×3 45.056%, 4×4 45.106% gap으로 개선이 재현되지 않았다.
- 따라서 이 정책은 Worker 기본 옵션·캐시 계약·추천 결과에 활성화하지 않는다. 안전 감사와 실험 옵션은 후속 상한 연구의 회귀 도구로만 유지하며, 다음 Gate E 분기는 계산식 경계 또는 실제 Pair 프로필을 이용해 상한 자체를 더 강하게 만드는 방식이다.
- 회귀: node tools/test-d4-pair-frontier.mjs, node tools/test-d4-global-optimizer-stage2.mjs, D4_AUDIT_ENVELOPE=1 node tools/test-d4-full-stage3.mjs 통과.

### Gate E 상관관계 상한 2차 결과 (2026-08-25)

- 실제 집계 상한을 직접 비교해 초기 두 분할 부위를 고르는 bound-guided 실험은 small exhaustive oracle의 exact·동점 규칙을 보존했다. 하지만 실제 425개 5초 gap은 깊이 1/2/3에서 각각 47.115% / 47.874% / 48.470%로 기준 44.900%보다 나빴다. 추가 상한 평가 비용이 탐색 수 감소보다 컸으므로 기본 Worker에는 비활성으로 유지한다.
- 실제 Pair 프로필 전체 물질화도 측정했다. Utility 부족 fixture의 선택 Pair는 방어구+무기 2,190,320개와 추가+특수 2,590,656개였고, 각각 생성 5,479.3ms / 6,129.2ms, 비교 100만회에서 중단한 Pareto 13,260.8ms / 17,700.6ms가 걸렸다. 축약은 불완전했고 후보도 1,755,855개 / 1,972,191개가 남았다.
- 따라서 전체 Pair Frontier 또는 전체 실제 Pair 프로필은 10초 exact 경로에서 금지한다. 다음 Gate E 후보는 모든 Pair를 물질화하지 않고 선형 시간과 고정 메모리 안에서 검증 가능한 상한을 만드는 요약 방식으로 제한한다.

### Gate E 상관관계 상한 3차 결과 (2026-08-25)

- 전체 Pair를 저장하지 않는 CRIT 기준 2·4상자 스트리밍 요약은 두 Pair 478만 조합을 고정 메모리로 약 114.9ms에 순회했다. 각 상자는 실제 Pair 조합의 좌표별 envelope이므로 small exhaustive oracle의 exact·동점 회귀를 통과했다.
- 하지만 이 구현은 루트 상한에만 적용되고 후속 일반 상자는 다시 독립 envelope을 사용한다. 실제 425개 5초 gap은 2상자 47.321%, 4상자 47.271%로 기준 44.900%보다 나빴다.
- 따라서 root-only 스트리밍 상한은 기본 Worker에 채택하지 않는다. 후속 검토는 필터를 분기 이후에도 보존하는 Pair 상자 노드가 동일한 안전·시간 계약을 만족할 때만 시작한다.


### Gate E 상관관계 상한 4차 결과 (2026-08-28, 불채택·Gate E 종료)

- Gate E3의 root-only 한계를 직접 검증하기 위해, CRIT 2-bucket Pair filter를 root node에 붙이고 자식 node에서도 해당 filter 아래의 실제 Pair envelope을 다시 계산하는 실험 경로를 구현했다. 후보 삭제·상한 완화·exact 종료 규칙은 바꾸지 않았고, 소형 Pair Frontier oracle에서 exact 점수와 동점 ID 일치를 확인했다.
- 그러나 네 부위 CandidateTree는 개별 부위 집합만 표현하므로, 두 부위의 `pivot sum bucket` 관계는 자식에서 독립 cluster로 분해되지 않는다. 이를 정확히 유지하려면 child bound마다 해당 Pair의 실제 조합을 재순회해야 하며, filter를 끄면 root filter별로 같은 자식 공간을 중복 탐색하게 된다.
- 실제 425개 물리 근거리·dynamic seed+ordering·5초에서 filter depth 1은 방문 노드 3개, 평가 17,033회, gap 189.389%였고, root-only fallback(depth 0)은 방문 노드 2개, 평가 17,029회, gap 207.488%였다. 두 경우 모두 기존 75% 회귀 한계를 크게 넘었다.
- 결론: 이 CandidateTree 표현 위에서 Pair bucket filter의 분기 후 보존은 시간·공간 계약을 만족하지 않는다. 실험 코드는 제거했고 Worker·캐시·추천 경로에는 연결하지 않았다. Gate E는 안전성 확인과 성능 불채택으로 종료하며, 다음 개선은 Gate F의 별도 병목(평가/큐/노드 표현)으로 넘긴다.

### Gate F 1차 결과 (2026-08-28, 계측·경량 상한 평가)

- 기본 경로를 바꾸지 않는 선택형 `collectSearchProfile`을 추가했다. 이 프로필은 평가 종류, 상자 통계 합산, 후보 트리, 분기 선택, 작은 상자 열거, 큐 조작의 시간·횟수를 반환한다. 시간은 중첩된 호출을 각각 포함하는 `overlapping-inclusive` 표기이므로 항목을 합산해 총 실행 시간으로 해석하지 않는다.
- S7(dynamic seed+ordering) 실제 425개 exact 계측은 1,015,239ms에 완료했다. 최적 점수 14,097, 방문 노드 3,398,827, 평가 21,485,595, 상한 가지치기 9,502,099, 완성 조합 8,573,324였다. 계측상 상한 평가는 12,895,255회·487.4초, 완성 조합 평가는 8,573,588회·328.1초, 상자 통계 합산은 92.2초였다. 이 실행은 계측 오버헤드를 포함하므로 기존 921.9초 exact 측정과 직접 성능 비교하지 않는다.
- `evaluateAggregateSummary`는 이제 계산 커널의 summary 전용 반환을 요청한다. full aggregate와 동일한 대미지·MAXHP·MAXMP·AMPR·평타 CRIT·ASPD·진단을 계산하되, 상한 판정에 사용하지 않는 중독 프로필·도구팁·상세 결과 객체의 생성은 생략한다. 후보 삭제·상한 수식·exact 종료·동점 규칙은 바꾸지 않았다.
- 회귀: evaluator stage 1에서 full aggregate와 summary의 점수·hard constraint 일치, stage 2 oracle 3,430/solver 144/상한 1,093, Pair Frontier, Browser Worker를 통과했다. S7 실제 425개 5초 콜드 10회는 exact 0/10, compile+search P95 5,118.8ms, 인증 gap 40.485%~42.104%였다.
- 판정: 경량 summary는 안전한 상한 평가 비용 절감으로 채택한다. 하지만 10초 exact 목표에는 필요한 규모보다 훨씬 작으므로, Gate F2는 Pair bucket 재시도가 아니라 실제 가능 결합을 보존하는 더 강한 상한 또는 후보 노드 표현 재설계의 oracle·성능 Gate로 한정한다.

### Gate F 2차 결과 (2026-08-28, 불채택·Gate F 종료)

- 완성 leaf도 summary 평가로 바꾸는 실험은 작은 oracle과 5초 회귀를 통과했지만, long exact에서 같은 최적 점수·탐색 구조를 유지하면서 985,639ms로 기존 921,871ms보다 느려졌다. 따라서 leaf는 full aggregate 평가로 되돌렸다.
- CandidateTree의 후보 rank 기반 분할은 실제 425개 5초 표준 gap 한계(75%)를 넘겨 제거했다. 기존 설정만으로 `splitDimensions` 1/2/3/4를 비교한 한 번의 5초 탐색은 gap 41.117% / 41.877% / 45.333% / 48.776%였고, 차원을 늘릴수록 자식 수 증가와 상한 완화가 커졌다. 시간 변동을 고려해 기본값 2를 변경할 만큼 일관된 개선은 없었다.
- 채택본의 long exact 재측정은 최적 점수 14,097, 방문 4,477,218, 평가 26,208,511, bound prune 12,643,673, 완성 조합 9,102,384, compile 112.4ms, solve 1,177,836ms였다. 이 결과는 계측을 켜지 않은 채택본의 실제 실행이며, 10초 exact에는 117.8배의 작업량 감소가 필요하다.
- Frontier 준비는 약 112ms로 주 병목이 아니고, F1 profile의 큐/상자 통계 합산도 중첩 시간이지만 상한·완성 평가보다 작았다. 16 논리 코어가 완벽히 선형 확장된다는 비현실적 가정에도 1,177.8초 / 16 = 73.6초이므로, 현 CandidateTree를 독립 Worker에 단순 분산하는 것만으로는 10초 목표를 달성할 수 없다. 전역 incumbent 병합 비용까지 고려하면 더 불리하다.
- 결론: F1의 summary 상한 경로와 계측만 유지한다. 나머지 Gate F의 점진적 경로(leaf summary, 후보 순위 분할, 분기 차원, 단순 Worker 병렬화)는 채택하지 않는다. 다음 개선은 Pair-native 또는 다른 실제 결합 보존 노드 표현을 설계하고, 그 표현의 oracle·상한 property·10회 P95 Gate를 새 Gate로 시작할 때만 재개한다. 실험 코드는 모두 제거했고 Worker·캐시·추천의 기본 계약은 변하지 않았다.

### 병렬화 선행 결정 (2026-08-28)

- 사용자 결정으로 Pair-native 노드 표현보다 병렬화를 먼저 진행한다. 목적은 10초 exact 보장이 아니라 현재 단일 Worker 탐색을 배포 PC의 모든 논리 CPU에서 사용할 수 있게 만드는 것이다.
- 현재 PC의 16스레드는 하드코딩하지 않는다. 실행 시 논리 프로세서·가용 메모리·GPU를 감지하고, CPU 스레드는 전부 사용하되 shard 수와 큐 메모리를 동적으로 조절한다.
- 1차는 기존 JavaScript 계산식을 유지한 Worker pool, 최종 기본 경로는 Tauri에 직접 연결한 Rust 공유 메모리 병렬 엔진이다. GPU는 CPU 엔진 완성 뒤 batch 비중·정확한 수치 계약·실측 speedup을 통과한 경우에만 보조 경로로 채택한다.
- 상세 단계·분할/병합 exact 계약·fallback·검증 기준은 `d4-parallel-exact-optimization-plan.md`를 따른다.
- P0/P1은 작은 exhaustive 및 실제 Browser Worker 프로토콜 회귀까지 통과했지만, 425개 후보의 wall time·메모리·모든 감지 스레드 사용 측정 전에는 결과 UI의 기본 단일 Worker 경로를 바꾸지 않는다.
- P2의 첫 425개 측정은 plan 생성 약 1.1초 뒤에도 Worker별 후보 복제·초기화가 5초 예산을 소진해 병렬 shard가 첫 결과를 반환하지 못했다. 안전 fallback을 추가했으나 speedup이 아니므로 JavaScript pool은 기본 경로 불채택이며, 공유 후보 저장소를 쓰는 Rust 병렬 엔진을 다음 구현 대상으로 한다.

## 3. 결정 흐름

```text
기준선 측정
  → Utility 의존성 분류
    ├ 순수 제약: 잔여 요구량까지만 포화 비교
    ├ 파생·공격·조건 의존: raw 값 보존
    └ 불명: 보수적으로 후보 보존
  → SupplyDifficulty 분석
    ├ 집중 공급: Utility 우선 Pair 후보
    └ 분산 공급: 공동 Frontier 유지
  → 세 Pair 분할 측정
    ├ 우세 분할: 선택
    ├ 시나리오별 차이: 결정적 동적 선택
    └ Frontier 폭발: 지연 생성/상자 탐색
  → residual 지배 + Pair Frontier + 상관관계 상한
    ├ oracle/property 실패: 해당 규칙 비활성화
    ├ 10초 exact: 종료
    ├ 노드 과다: 상한/Frontier 강화
    ├ 평가 과다: 조밀 벡터/증분 계산
    └ CPU 한계: 독립 상자 Worker 병렬화
```

## 4. Gate A — Utility 의존성과 residual

각 Utility는 constraintOnly, objectiveDependent, derivedDependencies, conditionDependencies, saturationRule로 분류한다.

- HP·ASPD는 대미지·파생·조건에 쓰이지 않을 때만 순수 제약이다.
- MAXMP는 AMPR에 영향을 주므로 MP 요구 충족만으로 제거하지 않는다.
- 크리티컬은 평타 100 제약과 선택 공격 기대 대미지 양쪽에 쓰일 수 있어 raw 값을 보존한다.
- 신속의 수도 Lv.10, 듀얼소드 AMPR, 행동속도 50%, HP/MP 비례 공격은 별도 분기다.
- 의존성이 불명이면 raw 값을 유지한다.

순수 제약 좌표만 residual R에 대해 min(contribution, R)로 포화한다. 이미 충족됐더라도 DPS·파생·조건 효과가 있으면 후보를 제거하지 않는다.

## 5. Gate B — SupplyDifficulty와 residual 지배

SupplyDifficulty는 드롭 난이도가 아니라 슬롯 기회비용이다. Utility별 residual, 최대 공급량, 충족 후보 비율, 공급 집중도, 충족 시 최소 로그 대미지 손실, 다른 Utility/DPS와의 중첩을 계산한다.

이 값은 Pair 순서, 초기해, 후보 정렬에만 사용한다. 후보 삭제에는 다음 residual 지배 증명이 필요하다.

1. 구조·조건·충돌·계보 서명이 같음
2. 슬롯 비용이 더 나쁘지 않음
3. 목적함수 관련 좌표가 같거나 우수
4. 미충족 Utility의 capped 기여가 같거나 우수
5. 파생 계산에 필요한 raw 좌표가 같거나 우수
6. 하나 이상 엄격히 우수
7. 동점 ID 계약을 보존

예외: HP를 초과해도 호뢰파섬처럼 DPS를 함께 주면 삭제하지 않는다. MAXMP→AMPR, 크리티컬 기대값, HP/MP 조건 효과는 포화 뒤에도 raw 좌표를 유지한다.

## 6. Gate C — Pair 분할 선택

모든 시나리오에서 다음 세 분할을 비교한다.

1. 방어구+특수 / 무기+추가
2. 방어구+무기 / 추가+특수
3. 방어구+추가 / 무기+특수

비교값은 원시 조합 수, 중복 제거 뒤 수, Pair Frontier 크기·생성 시간, Utility 충족 상태, 초기 하한, 루트 상한, 일정 노드당 상한 감소량, 메모리다.

- 방어구+특수가 우세하면 사용자 제안을 기본값으로 채택한다.
- 공격 유형·거리·발도/일진강풍·residual·장비 구조에 따라 우세 분할이 달라지면 시나리오 서명으로 결정적 선택을 한다.
- Pair 전체 물질화가 시간/메모리를 초과하면 지연 생성과 후보 상자 탐색으로 전환한다.

## 7. Gate D — Pair Frontier와 하한

선택된 두 부위의 실제 가능한 합계만 Pair 후보로 만들고 raw/capped Utility, 공격 좌표, 구조·충돌·계보 서명을 함께 보존한다. 안전 Pareto 축약 뒤 다음 실제 조합으로 하한을 만든다.

- 현재 장착
- Utility 최소 기회비용 조합
- 대미지 계열별 후보
- Pair Frontier 상위 조합
- 두 부위 동시 교환

Pair Frontier가 작으면 양쪽 Frontier를 직접 전수조사해 exact를 증명한다. 기존 단순 가중치 그리디는 빠른 시작값으로만 유지한다.

## 8. Gate E — 상관관계 보존 상한

실제 후보 하나를 상한으로 쓰지 않는다. 하나의 실제 후보는 다른 결합의 최적해보다 낮을 수 있다. 각각 안전한 상한의 최솟값을 쓴다.

```text
U = min(기존 독립 envelope,
        Pair 상관관계 envelope,
        계산식 경계 분할 envelope,
        작은 상자의 실제 최대값)
```

Pair Frontier는 실제 합계 프로필을 보존해 독립 최고값 혼합을 줄인다. 크리티컬 100, 물리 크뎀 300, 안정률/행동속도 상한, HP·MP·AMPR 요구치, 관통·방어력, 단계별 내림, 발도/일진강풍, MATK 무기 반영률은 필요할 때 별도 상자로 분리한다.

상한 property가 실패하면 해당 상한은 폐기하고 기존 안전 envelope만 사용한다. 상한 계산 비용이 가지치기 절감보다 크면 그 시나리오에서는 비활성화한다.

## 9. Gate F — 병목별 분기

| 계측 결과 | 대응 |
| --- | --- |
| 탐색 노드 과다 | residual 지배, Pair Frontier, 상한 경계 분할 강화 |
| Frontier 생성 과다 | 해시 중복 제거, 지연 생성, 상자 탐색 |
| 평가 호출 과다 | 정수 인덱스/TypedArray, 증분 합산, 요약 평가기 |
| 상한 평가 과다 | 상한 캐시, 경량 계산 경로 |
| 큐/메모리 과다 | best-bound와 깊이 우선 혼합, lazy node |
| 단일 CPU 한계 | 독립 상자를 Worker에 분산하고 전역 하한·상한 병합 |

탐색 순서는 고정 부위 순서가 아니라 예상 상한 감소량 / 상한 계산 비용으로 정한다. 병렬화는 단일 실행과 같은 동점 결과, 안전한 상한 병합 회귀 뒤에만 적용한다. Rust 재작성은 JS 계산식과의 전수 일치 계약 없이는 하지 않는다.

## 10. Gate G — 검증과 성능

소형 oracle/property는 Utility 없음·부족·충족, 음수 Utility 고DPS, HP+DPS 복합, MAXMP→AMPR, 크리티컬 100, 행동속도 50%, 물리 크뎀 300, 발도·일진강풍, 마법·듀얼소드, 잠금·금지·계보·중복, 동점, 유효 조합 없음을 포함한다.

필수 검증은 지배 전후 최적해 동일, Pair 분할별 exact 동일, 모든 상한이 실제 부분공간 최고값 이상, 입력/Worker 순서와 무관한 결과 동일이다.

실제 425개 성능 fixture는 물리 근거리 기본, HP 부족, MP·AMPR 부족, ASPD 부족, 크리티컬 부족, 발도, 일진강풍, 원거리, 마법, 듀얼소드, 잠금/금지, 음수 Utility, 유효 조합 없음을 포함한다. 필수 fixture 모두 콜드 10회 P95 10초 이하 exact여야 한다.

## 11. 구현 순서와 기록

1. 기준선/fixture와 성능 보고
2. Utility 의존성 메타데이터
3. residual·SupplyDifficulty
4. Pair 후보·서명
5. residual 지배 회귀와 Pair Frontier
6. 상관관계 상한·탐색 정책
7. 필요 시 Worker 병렬화
8. full/oracle/property/performance 회귀와 handoff 갱신

계산식, 후보 데이터, Utility 정책, Pair 정책, 상한 정책의 버전을 캐시 키에 포함한다. 채택한 분할, 폐기된 가설, 측정값은 current-development-handoff.md에 함께 기록한다.
