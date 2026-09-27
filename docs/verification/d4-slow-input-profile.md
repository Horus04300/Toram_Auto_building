# 오래 걸리는 D4 입력의 병목 측정

2026-09-23. 제품 Rust는 수정하지 않고 현재 세션 실행 경로의 복사본을 측정했다. 과거 사용자의 26분 보고는 입력의 출처이며 현재 실행 시간으로 사용하지 않는다.

## 입력과 방법

- 실제 보고 입력: `tools/fixtures/d4-native-runtime-26min-revenir.json`의 resolvedExecutionContext. 루브닐, 8슬롯 잠금 해제, MP 2000·AMPR 100·일반 공격 크리티컬 100·ASPD 1000 제한. 준비된 그룹 크기 1141/1017/871/1121.
- 비교 입력: 이전 회귀 감사의 듀얼 fixture. 실제 사용자 보고 입력은 아니며, 현재 코드에서 상대적으로 느린 재현 입력이다.
- AMD Ryzen 7 9800X3D, 논리 프로세서 16개, Windows 10.0.26200, Node 24.17.0. 실행은 순차 진행했다.
- `tools/profile-d4-slow-inputs.mjs`가 Rust 파일 5개를 target 아래 격리 crate로 복사하고 control/profile release 바이너리를 만든다. 입력·제품 코드 해시를 기록한다. 제품 Native/checkpoint v5, split v3, 계산 v2 계약은 바꾸지 않는다.
- control에도 초당 최대 1회의 진행 snapshot을 넣었다. 따라서 앱 전체 UI/IPC 시간이나 완전히 무계측인 제품 바이너리의 벤치마크는 아니다.
- evaluator와 boxStats는 작업자별 1024회 중 1회 시간 표본을 수집한다. workerJob/poolRun/frontierPop/frontierMerge는 구간 전체를 잰다. 작업자 통계는 스레드 종료 때 한 번 합친다.
- poolRun은 전달·실행·대기·수신을 모두 포함한다. workerJob에는 평가·통계 병합·메모리 처리 등이 포함되며 OS 선점 시간도 들어간다. 두 값의 차이를 순수 잠금 대기로 해석하지 않는다.
- evaluator/boxStats의 추정 시간은 `표본 시간 × 호출 수 / 표본 수`다. 서로 중첩되지 않지만 workerJob 내부 값이므로 workerJob에 더하지 않는다. 스레드별 시간의 합은 벽시계 시간과 다르다. 짧은 함수의 타이머 비용과 결정적 샘플링 편향이 있어 정밀 CPU 프로파일 비율은 아니다.
- 30초 탐색 측정 뒤 120초 예산으로 완료 측정을 진행했다. 30초 탐색 중 16작업자 control 일부와 JS oracle 준비가 겹쳤으므로 해당 실행의 속도 비교는 참고용이다. 이후 완료 측정 중에는 다른 빌드/검증을 병행하지 않았다.

## 측정 결과

16작업자, 완료까지 2회씩 측정한 범위다. control은 구간 타이머 없이 진행 snapshot만 수집한다. JS 후보 준비 시간은 별도 1.28초(루브닐 export 1회), Native 세션 준비는 약 47ms였다. 아래 시간에 JS 준비·UI·IPC는 포함되지 않는다.

| 항목 | 루브닐 | 듀얼 |
| --- | ---: | ---: |
| control 완료 시간 | 35.89~38.34초 | 20.02~21.96초 |
| profile 완료 시간 | 38.49~38.74초 | 20.73~22.31초 |
| 동일 반복의 계측 시간 증가 | 0.4~7.9% | 1.6~3.5% |
| profile 큐 pop + batch 채우기 | 22.06~22.12초, **57.1~57.3%** | 6.62~7.00초, **31.4~31.9%** |
| profile 결과의 큐 재삽입 | 1.76~1.77초 | 0.53초 |
| profile poolRun 전체 | 14.53~14.71초 | 13.48~14.68초 |
| 전체 평가 | 약 1억 7355만 회 | 약 1억 995만 회 |
| 완성 조합 열거 | 1513만 8211회 | 5092만 4398회 |
| 제약으로 제거 | 약 9393만 회 | 0회 |
| 초당 snapshot에서 관측한 최대 대기 후보 | 약 856만 | 약 377만 |
| control 프로세스 평균 CPU 사용량 | 3.55~3.62 코어 상당 | 5.99~6.35 코어 상당 |
| control 관측 peak working set | 533~583 MiB | 약 164 MiB |
| 최종 점수 | 1123905.36 | 21458 |

CPU 사용량은 OS 프로세스 누적 CPU 시간 / 프로세스 벽시계 시간이며 16작업자가 항상 16코어를 사용하는 것은 아니다. 메모리와 최대 대기 후보는 샘플에서 관측한 값이다. 제품에 새 메모리 보장이 생긴 것은 아니다. 반복 2회뿐이므로 작은 성능 차이를 확정하지 않는다.

profile의 작업자 구간 합은 루브닐 110.3~111.3초, 듀얼 144.3~149.5초다. 그 안의 evaluator 추정 합은 각각 52.9~53.0초와 71.0~73.4초, boxStats 추정 합은 24.3~24.7초와 9.5~9.8초였다. **벽시계 시간에 이 합을 더해서는 안 된다.** 평가 계산은 여전히 큰 비용이지만, 루브닐에서는 중앙 큐 pop만으로 벽시계의 절반을 넘는다.

루브닐 control은 유효 해가 약 7초 snapshot에서 처음 관측되고 최종 점수가 약 12초 snapshot에서 관측됐다. 이후 약 24~26초는 더 좋은 해가 없음을 증명하는 데 쓰였다. snapshot 간격 때문에 정확한 발견 순간은 알 수 없다. 30초 탐색은 bounded였지만, 이후 exact 점수가 모두 당시 lower/upper 사이에 포함되는 것을 확인했다. 과거 26분 보고와 현재 약 36~38초를 같은 버전·환경의 개선 배수로 비교하지 않는다.

## 검증과 산출물

- 30초 탐색 8회, 완료 측정 8회, JS oracle 대조 4회. 완료된 실행끼리 점수·최적 조합 ID·upper 일치, bounded 구간의 최적점 포함 검사 통과. 병렬 incumbent 공유 시점에 따라 평가 횟수에는 소폭 차이가 있다.
- 그룹당 16개씩 샘플링한 두 입력의 JS 완전 탐색(각 65,536조합)과 control/profile 모두 일치했다. 이는 전체 입력에 대한 독립 완전 탐색 검증은 아니다.
- `cargo test --offline --release --manifest-path src-tauri/target/slow-profile/crate/Cargo.toml --bin d4_native_parallel`: **43/43 통과**.
- `node --check tools/profile-d4-slow-inputs.mjs`, `node --check tools/benchmark-d4-native-p6.mjs`, `npm run ai:audit`, `git diff --check`: 통과.
- 제품 Rust diff 없음. 전체 앱 R0/R9/S1·UI E2E·배포는 이번 계측 작업에서 재실행하지 않았다. 이전 실행 결과는 이전 감사 문서에 구분해 남긴다.
- 원자료 요약: `d4-slow-input-profile-measurements.json`. 소스/입력 SHA-256, 최종 결과, 초당 frontier/점수/상한, 스레드별 계측 합을 보존했다. OS 25ms 원시 샘플은 target/slow-profile의 원본 JSON에 남고 문서 산출물에는 집계값을 담았다.

## 병목 해석과 후속 순서

1. **큰 frontier의 우선순위 큐 pop 비용부터 실험한다.** 문자열 비교는 이미 숫자 path_rank 비교로 바뀌었지만, 현재 WorkItem 비교는 동점일 때 Arc가 가리키는 네 TreeNode를 따라간다. 캐시 지역성·힙 항목 크기·힙 구조를 함께 비교할 가치가 있다. 계측한 pop 구간에는 힙 비교/이동과 batch Vec 채우기가 함께 포함되므로, 이번 결과만으로 Arc 역참조가 원인이라고 확정하지 않는다. 정렬 키를 복제하면 항목 크기와 메모리가 증가하므로 속도 향상은 별도 검증해야 한다.
2. **루브닐은 서로 양립할 수 없는 옵션을 함께 낙관하는 상한을 좁히는 방향을 검토한다.** 수백만 frontier와 대량의 제약 탈락은 후보를 더 일찍 제거할 여지가 있다는 근거다. 특정 새 상한이 안전하거나 효과적이라는 증명은 아니다. 정확성 Gate와 추가 평가 비용을 함께 비교한다.
3. **듀얼의 작은 박스 완전 열거 비용을 별도로 검토한다.** 약 5천만 완성 조합 평가가 발생하므로, 열거 중 부분합 재사용이나 안전한 조기 제약/상한 검사의 손익을 측정할 수 있다. 루브닐과 다른 비용 구조이므로 한 설정을 모든 입력에 일괄 적용하지 않는다.

단순히 작업자 수나 메시지 묶음을 더 늘리는 것을 첫 개선으로 권하지 않는다. 중앙 큐 처리 시간에는 추가 작업자가 도움을 주지 못한다. 이번 구간 계측은 채널 잠금 대기만을 분리하지 않았으므로, 잠금 비용이 없다고 결론 내리지도 않는다.

## 재현

```powershell
node tools/audit-d4-performance-regressions.mjs prepare
$env:D4_P6_REVENIR='1'
$env:D4_P6_THREAD='16'
$env:D4_P6_EXPORT_INPUT='src-tauri/target/regression-audit/revenir.json'
node tools/benchmark-d4-native-p6.mjs
Remove-Item Env:D4_P6_REVENIR,Env:D4_P6_THREAD,Env:D4_P6_EXPORT_INPUT
node tools/profile-d4-slow-inputs.mjs build
node tools/profile-d4-slow-inputs.mjs run
$env:D4_PROFILE_THREADS='16'
$env:D4_PROFILE_REPEATS='2'
$env:D4_PROFILE_BUDGET='120000'
$env:D4_PROFILE_REPORT='complete.json'
node tools/profile-d4-slow-inputs.mjs run
```

JS oracle용 입력은 같은 export 명령에 `D4_P6_PACKAGE_LIMIT=16`을 더하고 `revenir-oracle.json`으로 저장한다. 듀얼 oracle은 이전 감사의 `verify` 준비 입력을 사용했다. profiler 실행 시 `D4_PROFILE_FIXTURES=revenir-oracle,dual-oracle`로 두 바이너리를 JS 완전 탐색 결과와 비교할 수 있다.

oracle 실행에는 `D4_PROFILE_REPORT=oracle.json`, `D4_PROFILE_REPEATS=1`을 사용한다. 세 측정 파일이 준비되면 `node tools/profile-d4-slow-inputs.mjs report`로 문서용 JSON과 구간/결과 일치 검사를 재생성한다.

이전 6·7·12 회귀 감사와 제품 유지 결정은 `d4-regression-audit.md`를 참조한다.
