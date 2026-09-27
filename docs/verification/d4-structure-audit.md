# D4 데이터 형식·코드 구조 비효율 조사

2026-09-27. 탐색용 옵션 벡터 분리 이후의 제품 소스를 조사했다. 이번 작업은 계측·후보 탐색이며 제품 코드 변경은 없다. 실제 변경 전후 성능 개선율을 새로 주장하지 않는다.

후속 구현: 1순위 트리·큐는 `d4-indexed-tree.md`, 2순위 결과 버퍼는 `d4-small-box-buffers.md`, 3순위 전송 객체는 `d4-native-payload.md`에 기록했다. 4순위 입력 공유는 탐색 시간 증가로 롤백했다(`d4-shared-problem.md`). 아래 표와 계측은 적용 전 구조를 조사한 기록이다.

## 우선순위

| 순위 | 구조적 비용과 근거 | 개선 방향 | 영향·검증 |
| --- | --- | --- | --- |
| 1 | `WorkItem`은 상한+4개 `Arc<TreeNode>`로 40바이트다. 자식 생성/폐기마다 참조 카운트를 갱신하고, 동점 큐 비교는 각 노드를 역참조한다. 현재 계측에서도 큐 pop이 세션 시간의 루브닐 35.1%, 듀얼 26.4%다. | 트리를 세션이 소유하는 연속 배열로 만들고 작업에는 4개 노드 인덱스만 저장한다. preorder 인덱스로 기존 사전식 동점 순서를 유지할 수 있는지 검증한다. | 장시간 탐색·메모리 우선 후보. `u32` 인덱스 제안의 항목 크기는 24바이트지만 속도 향상은 미검증이다. 인덱스 범위 검사, 전체 coverage·상한·동점·취소·checkpoint Gate 필요. |
| 2 | 작은 박스마다 `box_candidate_indices`가 4개의 `Vec`를 할당하고 트리를 다시 순회한다. 작업자는 메시지마다 결과 Vec를 새로 만들고, 살아남는 자식들은 재귀 단계별 Vec로 반환한다. | 작은 박스 후보를 재사용 버퍼/고정 배열 또는 트리의 연속 leaf 구간으로 표현한다. 작업자 결과도 공용 평탄 버퍼와 구간으로 돌려주는 방식을 비교한다. | 반복 할당·복사 감소 후보. 개별 할당 시간/횟수는 아직 분리 측정하지 않았다. `Vec::new()`만으로 할당된다고 계산하면 안 되며, 제거된 박스의 빈 결과는 힙 할당이 없다. 취소·오류 시 원래 부모 복원을 보존한다. |
| 3 | Native client가 표시·계보·조건·개별 크리스타 정보를 담은 prepared problem 전체를 IPC로 보낸다. Rust `NativePackage`가 입력에서 읽는 것은 id/statDelta뿐이다. | JS에는 원본을 보존하고 Native 요청에는 명시적인 전송용 객체를 만든다. 원본 옵션 값은 모두 유지하고 사용하지 않는 바깥 메타데이터만 제외한다. | 입력 준비·직렬화·파싱 비용. 측정 JSON 크기는 약 80~84% 감소 가능. 실제 WebView IPC 시간은 미측정. 반환 ID 복원, 원본 옵션·입력 진단과 버전 계약을 보존해야 한다. |
| 4 | `NodePool::new`가 세션의 `NativeProblem` 전체를 한 번 더 clone한다. 현재 패키지는 원본+평가 벡터를 담아 inline 688바이트이며, 패키지 배열 복제만 1.2~2.7MiB다. | 세션과 풀에서 동일한 불변 문제를 `Arc<NativeProblem>` 하나로 공유한다. 원본 출력 책임은 유지한다. | 메모리·풀 생성 비용. 매 노드 복사가 아니라 풀 생성/작업자 수 변경 시 복사이므로 탐색 전체의 주요 CPU 병목으로 과장하지 않는다. 위 용량은 문자열·sparse heap 제외. |
| 5 | compiler는 두 슬롯 조합마다 `evaluatorCandidate`를 clone한다. 루브닐 prepared 입력에 복제된 후보 객체가 8,292개, 듀얼 7,054개다. | 이미 불변인 크리스타 해석 결과를 참조/ID로 공유하고, 최종 선택에서 평가·표시 객체를 조립한다. | JS 준비 시간·메모리 후보. 객체 공유만으로 JSON 중복은 줄지 않으므로 3번 전송 객체 분리와 구분한다. 정확성·Worker 구조화 복사·추천 적용을 검증한다. |
| 6 | `optimize()`는 Pareto 준비를 수행한 뒤 prepared problem 전체를 정렬 직렬화해 캐시를 조회한다. 캐시 적중도 이 비용을 먼저 낸다. resume 반환에서도 같은 문제의 키를 다시 계산한다. | 입력의 불변 서명을 먼저 만들고 준비 결과/기존 키를 재사용한다. Native 실행용 의미와 표시용 원본의 수명을 분리한다. | 반복 요청·준비 지연 후보. 원본의 모든 계산 의존성, 잠금·금지·옵션·버전·프로필을 서명에 포함해야 한다. 축약 키로 과거 표시 객체를 그대로 돌려주면 안 된다. |

주요 코드 위치: `src-tauri/src/d4_native_solver.rs`의 WorkItem/Ord, NodePool::new/run, box_candidate_indices, expand_parallel_node_inner; `assets/js/d4-native-client.js`의 prepare/cacheKey/optimize/resume; `assets/js/d4-problem-compiler.js`의 makePackage.

## 현재 코드 계측

같은 제품 소스로 만든 control/profile, 루브닐·듀얼 각 1회, 16작업자, 120초 예산. 4회 모두 exact이며 입력별 점수·최종 상한·전체 bestBuild가 일치했다. 모든 진행 상한이 최적값을 포함했다. 다른 빌드/테스트와 겹치지 않았다.

| 항목 | 루브닐 | 듀얼 |
| --- | ---: | ---: |
| control / profile 세션 시간 | 7.471 / 7.793초 | 12.764 / 13.007초 |
| profile 큐 pop 시간 | 2.733초 (35.1%) | 3.436초 (26.4%) |
| profile 큐 병합 시간 | 0.464초 | 0.485초 |
| 최대 대기 작업 수 (profile) | 2,891,483 | 3,766,630 |
| 40바이트 항목의 활성 데이터 크기 | 110.3MiB | 143.7MiB |
| 24바이트 인덱스 제안의 같은 항목 수 | 66.2MiB | 86.2MiB |

마지막 두 행은 실제 Rust 레이아웃과 관측 작업 수로 계산한 **이론적 활성 데이터 크기**다. Vec 여유 용량·트리·allocator·프로세스 전체 메모리를 포함하지 않으며, 실제 메모리를 44~57MiB 절감했다고 주장하지 않는다. profile의 평가/박스 합산 시간은 작업자 합계이고 중첩 측정이므로 서로 더해 wall time 비중으로 읽으면 안 된다.

추가 레이아웃: NativeStats 328바이트, TreeNode 408바이트, NativePackage 688바이트, PreparedContext 5,128바이트. 37개 계산 값+presence만 따로 표현하면 304바이트지만 현재 328바이트의 빈 BTreeMap 제거만으로 큰 개선을 보장하지 않는다. 문자열 key 호출도 상수 인라인 최적화가 가능하므로 외형만 보고 매번 문자열 검색 비용을 지불한다고 단정하지 않는다.

## 전송 데이터·캐시 키 실험

전송 제안은 baseContext/scenarioSnapshot 전체, modeledKeys/initialPackageIds, 그룹 id와 패키지 id/statDelta를 보존한다. 실제 제품 전송이나 캐시 정책에는 적용하지 않았다.

| 입력 | 현재 JSON | 전송 제안 JSON | 감소 | 현재 캐시 키 / 전송 제안 키 중앙값 |
| --- | ---: | ---: | ---: | ---: |
| 루브닐 | 3,116,706B | 627,068B | 79.9% | 40.65 / 8.67ms |
| 듀얼 | 2,718,336B | 536,136B | 80.3% | 31.61 / 7.43ms |
| 유틸리티 충돌 | 1,141,391B | 178,535B | 84.4% | 12.94 / 1.94ms |

캐시 키는 실제 client 함수의 복사본을 Node 24.17.0에서 호출했다. 2회 준비 후 10회 중앙값이며 WebView/IPC 측정이 아니다. 최초 VM 문맥 실행은 문자별 Math 전역 조회 비용을 부풀리므로 버리고 일반 Node 실행 문맥으로 다시 측정했다. 준비 함수/Pareto 비용까지 이 숫자에 포함된 것은 아니다.

## 우선순위에서 제외한 항목

- 일반 pause/resume은 서비스에 보관한 세션을 그대로 사용한다. `from_checkpoint`의 트리 재생성/경로 DFS는 존재하지만 현재 일반 재개의 반복 비용으로 보고하지 않는다.
- `NativeStats::iter()`는 임시 Vec 생성·정렬을 하지만 주요 합산/평가는 get/add_assign으로 처리한다. 준비·직렬화 비용 후보이지 현재 열거 평가마다 정렬한다고 해석하지 않는다.
- PreparedContext의 원본 Value/개별 필드/효과 캐시 중복은 존재한다. 객체 몇 개의 절감이며 수백만 WorkItem의 메모리 문제보다 우선하지 않는다.
- 노드마다 통계를 atomic으로 갱신하는 문제, 노드마다 메시지를 보내는 문제, 매 batch 스레드를 새로 만드는 문제는 이미 개선된 경로다. 남은 비용은 노드 claim atomic, batch별 채널·결과 버퍼 등으로 구분해야 한다.

## 재현·검증 범위

```powershell
$env:D4_PROFILE_FIXTURES='revenir,dual'
$env:D4_PROFILE_THREADS='16'
$env:D4_PROFILE_REPEATS='1'
$env:D4_PROFILE_BUDGET='120000'
$env:D4_PROFILE_REPORT='structure-audit.json'
node tools/profile-d4-slow-inputs.mjs run
node tools/audit-d4-structure.mjs
```

profile 바이너리가 현재 소스와 다르면 먼저 `node tools/profile-d4-slow-inputs.mjs build`가 필요하다. 조사 도구는 `target/structure-audit`의 격리 crate에서 레이아웃만 출력하며, 제품 소스 SHA-256 불변을 검사한다. 상세 수치: `d4-structure-audit-measurements.json`.

새 계측·원본 불변 검사, 도구 문법 검사, `npm run ai:audit`, `git diff --check` 통과. 제품 코드를 변경하지 않아 R0/R9/Rust 전체 회귀와 실제 설치본 E2E를 이번 조사에서 재실행하지 않았다. 다음 구현은 후보별 정확성 Gate와 동일 환경 전후 반복 비교가 필요하다.
