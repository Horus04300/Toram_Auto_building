# D4 Native 전송 객체 분리

2026-09-27 구조 개선 3순위. 이전 구조 감사는 `d4-structure-audit.md`, 직전 버퍼 개선은 `d4-small-box-buffers.md`에 기록했다.

## 변경과 유지 계약

`assets/js/d4-native-client.js`는 준비된 문제 전체 대신 Rust의 역직렬화 필드에 맞춘 객체를 `d4_optimize_parallel`에 전달한다.

| 범위 | 전달하는 필드 |
| --- | --- |
| 문제 | baseContext 전체, scenarioSnapshot 전체, metadata, groups |
| metadata | modeledKeys, initialPackageIds |
| 그룹 | id, packages |
| 패키지 | id, statDelta 전체 |

후보 이름·슬롯·조건·계보·개별 크리스타 객체·Pareto 보고서 등 Rust가 읽지 않는 중복 정보만 요청에서 제외한다. 옵션을 modeledKeys로 제한하지 않으므로 음수·0·미래 옵션과 평가 의존 값, 최종 반환 원본 옵션을 유지한다. 후보/그룹 순서 및 ID를 바꾸지 않는다. baseContext와 scenarioSnapshot도 필드별로 축소하지 않는다.

준비·잠금 진단은 기존 prepare 경로에서 처리한다. JS는 원본 prepared problem을 보유해 결과·진행 후 완료·resume의 패키지 ID를 표시/추천 적용에 필요한 후보 객체로 복원한다. 전송 객체는 원본에 쓰지 않으며, 값이 큰 context·statDelta는 참조만 연결하고 직렬화는 IPC가 수행한다. 요청 객체 생성 시간은 remainingBudgetMs 계산 전에 반영한다.

캐시 키는 기존 prepared problem 전체를 계속 사용한다. 표시 전용 데이터가 바뀌었는데 예전 normalized 결과를 재사용하지 않도록 하기 위한 경계이며, 캐시 준비/서명 재사용은 별도 6순위다. 캐시 적중 시 전송 객체를 만들지 않고, 일반 resume에도 문제를 다시 보내지 않는다. Native/checkpoint v8·계산 v2·분할 v3·Utility 정책 v2는 유지한다.

## 회귀·의미 동치 검증

- Native client mock: 요청에 허용 필드만 있는지, raw 옵션 전체·초기해·modeledKeys·중첩 context·scenario가 보존되는지, 원본이 수정되지 않는지 검사했다.
- exact/bounded/resume 결과가 원본 패키지를 복원하는지, 같은 입력 캐시 적중, 표시 정보만 변경한 입력의 캐시 분리, 선택 필드 누락 시 serde 기본값 유지, 준비 오류 진단과 invoke 차단을 검사했다.
- 기존 Native exact 테스트에 실제 client 변환 함수를 연결했다. 소형 fixture 및 실제 후보 fixture의 원본/축약 요청 결과를 비교한다. R0에서는 기존 소형 실행 범위에 따라 소형 비교를 실행한다.
- 격리 Rust bridge가 실제 NativeProblem 정의로 원본과 축약 JSON을 각각 읽고 직렬화한 **전체 값의 동치**를 검사했다. 실제 입력 3개 모두 일치했다. 제품 Rust 소스를 수정하지 않았다.

실행한 명령:

- `node tools/test-d4-native-client.mjs`: 통과.
- `npm run test:r0`: 71/71 프로세스 성공. 실제 저장 E2E는 `TORAM_E2E_CDP` 미설정 SKIP.
- `npm run verify:r9`: 통과.
- `node tools/audit-stack-source-links.mjs --require-s1`: S1 427/427 통과.
- `node tools/benchmark-d4-native-payload.mjs`: 실제 입력 3개의 NativeProblem 값 동치와 아래 직렬화/파싱 측정 통과.

## 전송 크기·직렬화·파싱

실제 client 함수를 테스트 복사본에서 노출해 측정한다. 필드 목록을 도구에서 재구현하지 않는다. 같은 Node realm에서 2회 준비 후 전후 순서를 교대해 20회 측정한 중앙값이다. 축약 직렬화에는 전송 객체 생성 시간을 포함한다. Rust 파싱은 동일 release 빌드의 serde_json→NativeProblem이며 stdin·도구의 바깥 JSON·결과 파괴 시간은 제외한다. WebView/Tauri IPC 지연 자체를 측정한 결과는 아니다.

| 입력 | JSON 크기 전→후 | 감소 | JS 직렬화 전→후 | Rust 파싱 전→후 |
| --- | --- | --- | --- | --- |
| 루브닐 | 3,116,706→627,068B | 79.9% | 8.32→2.21ms | 5.55→3.86ms |
| 듀얼 | 2,718,336→536,136B | 80.3% | 7.34→1.49ms | 4.55→3.23ms |
| 유틸리티 충돌 | 1,141,391→178,535B | 84.4% | 2.96→0.61ms | 1.54→0.91ms |

상세 표본·입력/소스 해시·실행 환경은 `d4-native-payload-serialization.json`에 저장했다. 이번 개선은 입력 경계의 중복 직렬화·파싱을 줄이며 탐색 노드당 계산 비용을 바꾸지 않는다.

## 전체 추천 결과 비교

동일한 Rust control 바이너리에 원본/축약 요청을 보내 입력별 2회씩, 총 12회를 새 프로세스로 실행했다. 16작업자·120초 예산·전후 교대 순서이며 다른 빌드/테스트와 겹치지 않는다.

```powershell
# 현재 소스와 control 바이너리의 source-hashes.json 일치를 먼저 확인한다.
Copy-Item src-tauri/target/slow-profile/control.exe src-tauri/target/native-payload/before.exe
$env:D4_EVALUATION_EXPERIMENT='native-payload'
$env:D4_COMPARE_NATIVE_PAYLOAD='1'
$env:D4_COMPARE_REPEATS='2'
node tools/benchmark-d4-partial-utility.mjs
```

| 입력 | Native 세션 평균 전→후 | peak working set 평균 전→후 |
| --- | --- | --- |
| 루브닐 | 5.307→5.403초 | 90.1→86.6MiB |
| 듀얼 | 9.407→8.884초 | 107.8→104.4MiB |
| 유틸리티 충돌 | 3.804→3.822초 | 93.9→78.4MiB |

12회 모두 exact, 입력별 점수·패키지 ID·전체 반환 옵션·최종 upper가 일치했다. 반환 옵션을 원본 후보 합산 및 JS로 재평가해 목표 충족과 점수를 확인했다. 변경 후 모든 진행 상한도 최적값을 포함했다. 기록: `d4-native-payload-measurements.json`.

CLI의 세션 타이머는 요청 파싱 후 시작하므로 위 세션 시간 차이를 전송 최적화의 속도 개선율로 해석하지 않는다. CLI는 flattened request를 역직렬화하므로 메모리 차이를 Tauri 설치본 절감량으로 일반화하지 않는다. 채택 근거는 전송 크기 감소, 변환을 포함한 직렬화/파싱 비용 감소, 읽힌 NativeProblem과 최종 추천 결과의 동치다.

제품 Rust 소스는 불변이고 측정 바이너리·최종 소스 해시 일치 검사를 통과했다. 도구 문법, `npm run ai:audit`, `git diff --check`를 확인했다. 실제 설치본 WebView IPC/화면 E2E는 실행하지 않았다.
