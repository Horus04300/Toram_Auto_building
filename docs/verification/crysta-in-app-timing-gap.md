# 인앱 경과 시간과 기존 재현 입력의 차이 조사

> 아래는 v12 당시의 구현·측정 기록이다. v13에서 적용 범위를 확장한 현재 결과는 [공통 상한 확대 검증](crysta-general-upper-bound.md)을 따른다.

2026-10-03. **사용자가 저장 파일을 다시 불러와 루브닐·에투왈 단일 잠금으로 실행한 10.90초를 debug Native 10.985초로 재현했다.** 같은 입력의 3회 평균은 debug Native 10.399초, release Native 0.885초다. 초기 22.44초/24.21초의 당시 입력은 수집되지 않아 이 재실행과 구분한다. 기존 빠른 fixture의 결과를 현재 저장 빌드의 성능으로 사용하지 않는다.

## 현재 저장 입력으로 확인한 원인

사용자는 기존 딜검방 파일을 불러왔고, 10.90초는 루브닐 기준임을 확인했다. 저장 폴더의 파일은 `딜검방 샘플.json`이며 SHA-256은 `97c8ddb048cb92687bb2a0746071b72006d6f3f1dcc44d859c19a0a5acca3f11`이다. 저장 원본은 수정하지 않았다.

`ToramApplication.CreateCalculationSnapshot`으로 장비·외부 옵션·투자 스킬·활성 버프·길드 요리 기본값을 조립했다. 저장된 콤보를 `ToramComboSequence.evaluate`로 평가하고 `Knight:11`의 `main` 타격을 `ToramApplication.ApplyComboHit`로 적용했다. 타격은 소모 스택 2에 따른 3타, 기본 계수 16.2, 활성 배율 1.35, 강타 태그 배율 1.5, 상수 400이다. 수치를 임의로 입력하지 않았다. 요구조건은 앱 기본값 HP 10,000 / MP 2,000 / 듀얼 적용 전 AMPR 100 / 평타 CRIT 100 / ASPD 1,000이다. 사용자 지시에 따라 잠금만 `[false,false,false,false,false,false,true,false]`로 설정했다. 현재 갑옷 크리스타는 초기해 입력에 보존했다.

확인된 차이는 다음과 같다.

1. **개발 빌드의 연산 비용:** 같은 루브닐 입력·클라이언트·서비스에서 Native debug 평균 10.399초, release 평균 0.885초다. 비율은 약 11.75배다. 앱의 10.90초는 debug 재현 범위와 같은 수준이다.
2. **새 상한 적용 제외:** 실제 입력의 `normalAttackAmprProfile.activeCandidates`에는 램페이지(`Blade:8`, flat 25, percent 0, multiplier 1)가 있다. 현재 `JointUtilityBounds::new`는 비어 있지 않은 AMPR 보정 프로필을 발견하면 `None`을 반환한다. 이에 의존하는 조건부 공격 상한도 생성되지 않는다. 지원하지 않는 경우 기존 안전 상한으로 탐색하기 때문에 이번 AMPR·CRIT 결합/공격 상한 개선이 이 입력에서는 동작하지 않는다. 실제 보정을 제거해서 빠르게 만드는 것은 같은 문제의 성능 개선이 아니다.
3. **기존 fixture의 입력 불일치:** 무기 공격력 625→690, ATK% 20→33, ATK 고정 0→162.5, CRIT 고정 90→120, HP 고정 0→7400, MP 고정 1850→1950 등의 차이가 있다. 기존 fixture에는 AMPR 보정이 없고 HP 요구조건도 해제돼 있었다. 실제 조립된 수치는 스킬·장비에서 생성됐으며 임의 가산이 아니다. 기존 최적 점수 1,048,419.24와 현재 저장 루브닐의 1,753,977.72도 다르다.

모든 실제 저장 입력 실행은 fresh Node/Native 프로세스, 캐시 없음, 동일 PC 16 threads, 30초 slice다. UI처럼 progress 32ms를 요청했으며 제품 JS가 최소 50ms로 보정하므로 **Native에 전달된 값은 50ms**다. 진행 간격을 이유로 차이를 단정하지 않는다.

| 루브닐 빌드 | Native 경과 3회(ms) | Native 평균(ms) | JS 처리 포함 전체 평균(ms) |
|---|---|---:|---:|
| debug v12 | 10602 / 10279 / 10316 | 10399.000 | 11271.256 |
| release v12 | 889 / 876 / 889 | 884.667 | 1717.338 |
| release v11 비교 | 938 / 865 / 878 | 893.667 | 1724.369 |

별도 debug 첫 실행은 Native 10985ms, 전체 11873.679ms였다. 앱 10900ms와 차이는 85ms(약 0.8%)이며 이 단회 표본은 위 3회 평균에 합치지 않았다. v11/v12는 이 입력에서 둘 다 새 공격 상한을 사용하지 않으며 작은 시간 차이를 개선 증거로 해석하지 않는다. 루브닐 9회와 별도 평타 9회에서 basis별 exact 점수·전체 `bestBuild` 일치, raw 옵션 합·JS 요구조건 만족·최종 점수 검사를 통과했다. 루브닐은 약 1,116만 평가, 220만 노드이며, 기존 잠금 fixture v12의 약 47만 평가·15.5만 노드와 탐색량도 다르다.

**처음 보고된 22.44초/24.21초까지 동일 입력으로 설명됐다는 뜻은 아니다.** 최근 10.90초 실행은 현재 저장 파일로 재현했지만, 그 이전 실행에서 어떤 입력/버프/요구조건이 달랐는지는 증거가 없다. 또한 headless release 시간을 실제 release 앱의 버튼→화면 시간으로 주장하지 않는다.

추적 가능한 산출물:

- `tools/fixtures/crysta-saved-sword-shield-revenir-etowal.json`: 이번 앱 코드로 해석한 루브닐 입력과 저장 원본 hash, 잠금/콤보 적용의 출처. 이전 fixture를 덮어쓰지 않는다.
- `docs/verification/crysta-in-app-timing-gap-measurements.json`: 평타/루브닐 각 debug·release·v11 비교 3회, 점수·조합·카운터·전체/Native 시간, source/input/binary hash와 profile 미적용 사유.
- Git 제외 `src-tauri/target/in-app-gap/prepare-saved.mjs`, `sample.mjs`, `summarize-saved.mjs`: 실제 저장 파일 조립, fresh 반복과 결과 동치 검사.

이 조사는 계산식·스킬 값·상한·앱 실행을 변경하지 않았다. 다음 상한 개선은 실제 AMPR 보정을 보존한 입력을 대상으로 지원 범위/안전성 증명부터 해야 한다.

## 사용자 관측과 실행 환경

- 개발 실행(`npm run desktop:dev` / `tauri dev`), 에투왈만 잠금.
- 평타 기준 22.44초, 루브닐 기준 24.21초.
- `Get-Process toram-online-auto-build-calculator`로 실행 중인 PID 2148의 경로가 저장소의 `src-tauri/target/debug/toram-online-auto-build-calculator.exe`임을 확인했다. 시작 시각은 08:34:19, 실행 파일 수정 시각은 08:34:18이다. 앱을 종료하거나 재시작하지 않았다.
- 현재 `Cargo.toml`에는 개발 최적화 profile override가 없다. 동일 소스의 headless debug 빌드 JSON artifact는 `opt_level: "0"`, `debuginfo: 2`, `debug_assertions: true`, `overflow_checks: true`다. 실행 중인 앱 자체의 artifact를 새로 생성한 것은 아니다.
- solver 소스 수정 시각은 07:51:58이다. 실행 파일 시각만으로 내부 코드 버전을 확정하지 않는다.

## 시간 표시 범위

`assets/js/optimization-results.js`는 Native 결과의 `elapsedMs`를 그대로 초로 표시한다. `assets/js/optimization/native-client.js`도 이 필드에 UI 시간을 더하지 않는다.

`NativeSearchSession::new`는 스탯·트리 준비, 초기해, 루트 평가 시간을 누적한다. 이어서 실제 탐색 slice 실행 시간을 누적하며 결과의 `elapsedMs`로 반환한다. slice 사이 사용자 대기 시간, JS 컴파일·전송·결과 복원·렌더링은 이 필드에 포함되지 않는다. Native 실행에 대한 설명이며 Worker fallback의 시간 계약과 혼합하지 않는다.

기존 성능 표의 `timing.totalMs`는 JS 컴파일부터 Native 실행·결과 복원·최종 JS 평가까지다. 따라서 앱의 ‘경과’와 비교할 때는 동일 입력의 Native `elapsedMs`도 함께 기록해야 한다.

## 기존 잠금 fixture의 debug/release 대조

입력은 기존 `resolvedExecutionContext`에서 에투왈 첫 슬롯만 잠근 재현 fixture다. 현재 실행 입력을 새로 수집한 자료가 아니다. 스킬은 루브닐, `normalAttackAmprProfile` 두 배열은 비어 있고 HP 요구조건은 `null`이다.

같은 JS 클라이언트·Rust 서비스·30초 slice·100ms progress 조건에서 새 Node/Native 프로세스를 순차 실행했다. release/debug 실행을 각 3회 번갈아 측정했다. 모든 실행은 `exact`, 점수 1,048,419.24이며 전체 `bestBuild` 일치, JS 요구조건 만족·점수·raw 옵션 합 검사를 통과했다.

| 빌드 | 전체 시간 3회(ms) | Native 경과 3회(ms) | 전체 평균(ms) | Native 평균(ms) |
|---|---|---|---:|---:|
| debug | 1739.392 / 1752.903 / 1738.362 | 959 / 957 / 957 | 1743.552 | 957.667 |
| release | 863.542 / 849.510 / 842.703 | 88 / 88 / 89 | 851.919 | 88.333 |

이 입력에서 개발 빌드의 Native 연산은 release의 약 10.84배였다. 그러나 debug Native 경과도 약 0.96초이므로 이 결과로 실제 앱의 24.21초를 설명할 수 없다. 앞선 debug 탐색 1회 전체 시간 3367.013ms는 환경 부하를 통제하지 않은 단회 관측이며 위 3회 평균에 합치지 않았다.

입력 SHA-256: `15565778FAA4DF5747D9B463F4AB23842BBB4FC07C4D4B6356751D9A65233CAD`.

실행 파일 SHA-256:

- debug headless: `FA80FF6FD0981480481F8FC546CD91E6616A85E77A320E0075509CED90680FD7`
- release headless: `A18A452ACB19F83B312185FBA96B8FDE44AC873D4BE9F131B2D3C07C4E8484BF`

## 초기 조사 기록: 저장 파일 확인 전의 적용 조건

1. 앱의 근거리 기본 HP 요구조건은 10,000인데 기존 fixture는 HP 제한을 해제했다. 실제 앱의 override 여부는 아직 확인하지 않았다. 기존 fixture에서 HP 요구조건만 코드의 기본값 10,000으로 바꾼 **원인 분리용 실험**은 debug 전체 2563.013ms / Native 1596ms, release 전체 1068.562ms / Native 142ms였다. 모두 exact이며 점수 994,178.7과 전체 선택 조합이 일치했다. 이 실험도 실제 24.21초 실행을 재현한 것은 아니다.
2. 결합 유틸리티 상한과 이에 의존하는 조건부 공격 상한은 `normalAttackAmprProfile.passive` 또는 `activeCandidates`가 비어 있지 않으면 안전성 지원 범위 밖으로 처리하여 사용하지 않는다. 실제 앱은 투자 스킬·활성 버프에서 이 프로필을 생성하지만 기존 fixture에는 보정이 없다. 실제 실행에서 상한이 비활성화됐는지는 아직 확인하지 않았다.
3. AMPR/CRIT 요구조건 누락·지원 범위 밖 옵션·최소 AMPR에서 이미 요구조건 충족 등도 상한 적용 여부에 영향을 준다. 현재 요구조건 전체와 해석된 Context 확인이 필요하다.
4. 초기 headless는 100ms, UI는 32ms를 요청한다. 제품 JS의 최소값 보정으로 UI의 Native 전달 간격은 50ms다. 이것만으로 22초 차이가 발생했다고 판단할 근거는 없다.

초기 조사에서 저장 폴더의 `딜검방 샘플.json`(2026-09-01 저장)은 에투왈 외 갑옷 크리스타 2개도 잠겨 있어 바로 대체하지 않았다. 이후 사용자가 이 기존 파일 재실행과 에투왈 단일 잠금을 확인했으므로 해당 파일의 장비·스킬·버프를 사용하고 잠금만 지시대로 풀었다. 결과는 위 현재 저장 입력 절에 기록한다.

## 재현 명령

이번 실행:

```powershell
cargo build --offline --manifest-path src-tauri/Cargo.toml --bin crysta_headless_service --message-format=json
node src-tauri/target/in-app-gap/sample.mjs src-tauri/target/debug/crysta_headless_service.exe src-tauri/target/constrained-upper-bound/revenir-locked.json
node src-tauri/target/in-app-gap/sample.mjs src-tauri/target/release/crysta_headless_service.exe src-tauri/target/constrained-upper-bound/revenir-locked.json
```

기존 fixture 각 3회와 기본 HP 민감도 실험 각 1회를 완료했다. 현재 저장 입력은 다음 명령으로 추가 조립·측정했다. 비교 반복별 명령은 `saved-revenir-debug-1.json` 등의 로그로 보존한다.

```powershell
node src-tauri/target/in-app-gap/prepare-saved.mjs "$env:LOCALAPPDATA\ToramOnlineAutoBuildCalculator\딜검방 샘플.json" src-tauri/target/in-app-gap/saved-revenir-etowal.json revenir
node src-tauri/target/in-app-gap/sample.mjs src-tauri/target/debug/crysta_headless_service.exe src-tauri/target/in-app-gap/saved-revenir-etowal.json 32
node src-tauri/target/in-app-gap/sample.mjs src-tauri/target/release/crysta_headless_service.exe src-tauri/target/in-app-gap/saved-revenir-etowal.json 32
node src-tauri/target/in-app-gap/summarize-saved.mjs
```

`summarize-saved.mjs`는 18개 반복의 basis별 점수·전체 조합 일치를 검사해 PASS했다. 추적 fixture를 공식 측정 명령으로 읽는 검증도 완료했다.

```powershell
npm run bench:optimization -- --input tools/fixtures/crysta-saved-sword-shield-revenir-etowal.json --repeats 1 --output src-tauri/target/in-app-gap/saved-official-release.json
```

이 추가 실행은 빌드 hash 검사를 거쳐 exact, 전체 1726.925ms로 완료됐으며 위 3회 평균에는 합치지 않았다. 문서 변경의 `npm run ai:audit`, `git diff --check`도 PASS했다. 기존 fixture의 속도를 현재 앱 성능으로 단정하지 않는다.
