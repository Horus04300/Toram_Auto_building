# AMPR·크리티컬 단독 제약을 반영한 공격 상한

2026-10-06. 현재 제품 판정은 `../handoff/current-development-handoff.md`, 측정 원본은 [전후 기록](crysta-axis-upper-bound-measurements.json)을 따른다.

## 바꾼 부분

기존 공격 상한은 ATK%/MATK%, 거리 대미지, CDMG 각각에 대해 AMPR·CRIT의 가중치가 모두 양수인 15개 방향을 검사했다. 한 요구조건에 여유가 많은 경우, 그 공급량이 지지값을 높여 다른 요구조건과 공격 옵션의 충돌을 가릴 수 있었다.

AMPR만 반영하는 `(1,0)`과 CRIT만 반영하는 `(0,1)` 방향을 추가했다. 공격 계수 1/2/4를 유지하므로 좌표당 추가 방향은 6개다. 각 트리 노드의 실제 패키지에서 지지값을 준비하고, 모든 자식 부분공간에서도 해당 노드의 지지값을 사용한다. 루트에서만 조이는 상한이 아니다.

추가 방향은 좌표별로 루트에서 기존 방향보다 낮은 상한을 만드는 경우에 활성화한다. 정수 내림과 원래 좌표 상한의 cap까지 적용한 뒤 비교한다. 이 선택은 추가 계산의 예산을 정하는 정책이며, 후보 삭제의 근거가 아니다. 루트에서 효과가 없던 방향이 자식에서 도움이 될 가능성은 있지만, 선택하지 않으면 기존 15개 방향을 그대로 사용한다. 활성화한 경우에도 기존 15개 방향을 모두 유지한다.

Utility 가능성 검사의 기존 혼합 방향 5개와 분기 트리·분할 점수·초기해·동점 비교는 유지했다. 대미지 상한과 큐 순서가 달라질 수 있다. 직렬·독립 병렬·제품 shared session의 `box_stats`에 같은 상한을 적용한다. 스킬 수치·계산식·장비/스탯/요구조건·후보 목록을 수정하지 않았다. 장비 이름이나 특정 스킬 ID에 따른 선택 규칙은 없다.

## 안전성

인코딩한 공격 옵션을 D, flat AMPR·CRIT을 M·C, 기존 안전한 최소 필요량을 A·C_min(P)라고 하자. k는 양수, a·c는 0 이상이다. 실제 패키지의 `kD+aM+cC` 최댓값을 각 노드에 저장하면 모든 feasible 완성 조합에 대해 다음이 성립한다.

```text
kD+aM+cC ≤ Σ U_g(k,a,c)
M ≥ A, C ≥ C_min(P)
D ≤ [Σ U_g(k,a,c) − aA − cC_min(P)] / k
```

a 또는 c가 0이어도 증명은 동일하다. 기존 방향과 추가 방향의 상한 중 최솟값을 사용할 수 있다. 외향 정수 완화, 소수·큰 좌표, 넓은 CRITP bucket, 비단조 AMPR의 CRIT-only fallback, 누락된 modeled 좌표의 보존은 기존 계약을 따른다. raw 옵션을 양자화하거나 삭제하지 않는다.

상한 정책 변경에 맞춰 Native 엔진·checkpoint를 v14로 갱신했다. v13 이하의 현재/과거 checkpoint를 거부하고 JS exact cache도 구분한다. split policy v4, 계산 v3, 앱 저장 schema 및 제품 버전 v0.7.2는 유지한다. 추가 캐시는 checkpoint 복원 때 원시 패키지에서 다시 만든다.

## 성능 비교

실제 저장 딜검방의 루브닐·실제 콤보와 평타, 에투왈 단일 잠금을 사용했다. `tools/fixtures/crysta-saved-sword-shield-revenir-etowal.json`과 기존 실제 평타 입력을 그대로 읽었다. 인위적인 AMPR/CRIT 가산은 없다. 과거 불완전 루브닐 두 입력은 회귀용으로만 비교하며 현재 사용자 빌드나 서로 다른 직업의 대표 사례로 세지 않는다. 실제 듀얼소드 사용자 입력은 아직 없다.

AMD Ryzen 7 9800X3D / Node v24.17.0 / Native 16 threads. 최종 5개 case·mode에서 전후 각각 10회씩 총 100회, 새 Node·Native 프로세스를 순차 실행하고 전후 순서를 번갈았다. 측정 중 컴파일·회귀 테스트를 실행하지 않았다. 같은 현재 JS를 양쪽 바이너리에 사용하고 cache를 사용하지 않았다. baseline 바이너리는 직전 채택한 공격 상한 커널의 제품 산출물과 hash가 같으며 baseline Rust 소스도 일치한다.

| 입력·실행 | Native 평균 전→후(ms) | 전체 평균 전→후(ms) | 전체 P95 전→후(ms) | 전체 단축 |
| --- | ---: | ---: | ---: | ---: |
| 실제 루브닐 release | 388.2→350.1 | 1032.1→993.9 | 1072.9→1038.6 | 3.7% |
| 실제 평타 release | 396.4→360.9 | 1040.8→1002.3 | 1095.0→1049.1 | 3.7% |
| 과거 unlocked 회귀 release | 480.2→486.0 | 1219.2→1228.2 | 1233.4→1263.0 | -0.7% |
| 과거 locked 회귀 release | 75.4→74.8 | 642.5→639.8 | 647.8→648.9 | 0.4% |
| 실제 루브닐 debug | 1896.8→1688.7 | 2570.3→2361.3 | 2642.9→2418.8 | 8.1% |

실제 루브닐 release 방문 노드는 평균 1083549.5→925892.8(14.6% 감소), 평타도 약 14.8% 감소했다. Native peak working set의 50ms 표본은 실제 두 입력에서 약 1MiB 증가했다. 짧은 실행의 peak 표본은 불안정하며 Node 메모리는 제외한다. 과거 unlocked 회귀는 방문 노드가 줄어도 추가 계산 비용으로 Native 1.2%, 전체 0.7% 늘었다. 모든 입력에서 실행시간이 감소했다고 주장하지 않는다.


전체 시간은 JS 후보 생성·준비부터 Native 결과 복원·최종 JS 재평가까지이며 UI/WebView는 제외한다. 개발 실행은 debug로 따로 측정했다. 인앱의 10.90초를 이번 headless 수치와 직접 비교하지 않는다.

100회 모두 exact 점수·전체 bestBuild·원시 옵션 합·compiled/prepared problem hash가 같았다. 실제 루브닐 1,753,977.72, 평타 67,120을 보존했고 최종 JS 재평가도 통과했다. 필수 실제 입력 전체의 성능이나 모든 빌드의 같은 개선율을 인증하지 않는다.

## 버린 구현과 검증

모든 좌표에 추가 방향을 무조건 계산한 첫 100회 실험은 실제 입력에서는 개선됐지만 과거 unlocked 회귀 입력의 Native 평균이 494.7→522.8ms로 늘었다. 추가 Utility 단독 가능성 검사와 모든 좌표의 추가 계산을 제품에 그대로 채택하지 않았다. 좌표별 루트 상한 비교와 기존 5개 Utility 방향을 사용한 최종 코드로 다시 측정했다.

모든 조합의 최소 utility 공급량을 캐시해서 중복 방향을 생략하는 구현도 검증했으나 검사 비용을 뚜렷하게 회수하지 못해 제거했다. 탐색용 단발 비교 중 테스트와 겹친 3회는 최종 계측에서 제외했다. 각 실험의 로컬 자료는 `src-tauri/target/axis-bound/`에 보존한다.

- `cargo test --offline --manifest-path src-tauri/Cargo.toml`: 325개 PASS(78+71+71+21+84, 공유 모듈 중복 포함). 모든 feasible 완성 조합의 모든 조상 상자에서 좌표·대미지 상한이 실제 값 이상인지 확인한다. 물리·마법·원거리/발도·듀얼·소수·큰 좌표·음수 기본값·한쪽 요구조건 해제·비단조 AMPR를 포함한다.
- 추가 방향의 모든 위치, enabled/누락 좌표, 단위, 음수/0/raw cap에서 계산 커널과 반복 reference의 bit 일치를 확인한다. AMPR·CRIT 각각이 제한하는 별도 합성 증명 fixture에서 이전 상한보다 낮아지고 exhaustive oracle의 점수·전체 build ID가 같은지 검사한다. 이 합성 fixture를 사용자 성능 근거로 사용하지 않는다.
- 기존 후보 순서 반전·잠금/계보/동점·1~64 threads·cancel/deadline/checkpoint/resume·분기 coverage를 유지한다. v4~v13 현재/과거 checkpoint 거부를 확인한다.
- `npm run test:regression`: 76/76 프로세스 PASS. Native 저장 E2E는 CDP 미설정 SKIP이다.
- `npm run verify:architecture`, `cargo clippy --offline --manifest-path src-tauri/Cargo.toml --all-targets -- -D warnings`, S1 출처 427/427, fmt PASS. `npm run desktop:prepare`, dist entry 검증과 개발용 앱·headless, release headless 재빌드도 완료했다.
- 실제 입력의 250ms slice/reuse 결과: 3개 slice·재개 2회, 같은 전체 exact 조합/점수 PASS. 이 시간은 일반 반복 평균에 섞지 않았다.
- `npm run ai:audit`, `git diff --check`: PASS.

## 재현

```powershell
npm run bench:optimization:build
npm run bench:optimization -- --input tools/fixtures/crysta-saved-sword-shield-revenir-etowal.json --repeats 10 --output src-tauri/target/axis-bound/official.json
npm run bench:optimization -- --input tools/fixtures/crysta-saved-sword-shield-revenir-etowal.json --repeats 1 --slice-ms 250 --output src-tauri/target/axis-bound/resume-actual.json
```

로컬 전후 비교는 `src-tauri/target/axis-bound/compare.ps1`과 `sample.mjs`, 집계는 `summarize.mjs`다. 새 checkout에는 과거 baseline 실행파일이 자동 제공되지 않는다. 측정 JSON에는 입력·출처·전체 결과·개별 시간/카운터·peak memory·환경·소스/바이너리 hash를 보존한다. 앱을 강제 종료하거나 재시작하지 않았으며 실제 화면 시간은 측정하지 않았다.
