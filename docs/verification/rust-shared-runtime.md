# Rust 공용 추천 코어

현재 상태는 [handoff](../handoff/current-development-handoff.md), 정확성 기준은 [추천 계약](../architecture/crysta-optimization-contract.md)을 따른다.

## 구현

engine/src/의 evaluator.rs·solver.rs·stats.rs·joint_supply.rs가 유일한 추천 코어다. 앱·개발용 Native 바이너리와 WASM이 같은 crate를 사용한다. 앱 디렉터리로 돌아가는 path include와 테스트 바이너리별 소스 복제를 제거했다.

평가·탐색 테스트는 evaluator_tests.rs·solver_tests.rs로 분리해 기존 private 접근·테스트 이름·89개 검사를 유지했다. 실행 알고리즘은 변경하지 않았다. JS는 ui/calculation/application/storage/update/optimization/data로 배치했다. Worker의 계산 모듈 import·manifest·TypeScript 출력·도구/문서 경로도 함께 갱신했다.

web/src/optimization/은 문제 compile·보수적 후보 준비·전송·결과 복원·JS 최종 평가·실행 제어를 담당한다. 빠른 추천은 Rust 초기해, 정밀 실행은 앱 Native 또는 웹의 동일 WASM 세션이다. 취소·중단/재개·인증 gap을 유지한다.

기존 JS 탐색기·seed·한계효용·pair·Worker pool 7개와 이에 종속된 테스트·실험 도구는 삭제했다. 대량 과거 계측 JSON·실험 설계 문서도 제거했다. 생성 로그는 desktop/target/에 쓴다. UI·저장 JSON v2·원문·스킬 데이터·사용자 샘플은 유지한다.

정확성 검사는 공용 Rust 단위 테스트, 실제 Native/WASM, 제품 후보 준비, 테스트 전용 소형 완전탐색으로 구성한다. 소형 완전탐색은 모든 조합의 점수와 동점 ID만 확인하며 추천 정책·가지치기·초기해·캐시가 없다.

## 사용자 입력 확인

2026-10-16, 정리 전 공용 Rust 전환에서 확인한 결과다. 모두 Native/WASM exact 점수·크리스타 ID·raw 옵션과 JS 최종 평가가 일치했다. 과거 수치를 정리 후 성능 향상으로 주장하지 않는다.

| 입력 | 최종 기대 대미지 | 웹 WASM 측정 |
| --- | --- | --- |
| 루브닐 재현 fixture | 1,123,905.36 | 875.9~964.8 ms |
| 인힘 마도구 사용자 샘플 | 737,214.9525 | 225.8~241.2 ms |
| 지팡이 크법 사용자 샘플 | 910,857.5775 | 1,375.2~1,437.6 ms |

Edge의 새 Worker 3회다. 루브닐은 초기 문제 compile을 제외하고 WASM 로딩~최종 재평가, 마법은 compile부터 최종 재평가까지이며 UI 렌더링은 제외했다. Native 마법 입력은 새 프로세스 3회, 마도구 357.1~362.2 ms·지팡이 535.6~540.0 ms였다. 런타임·스레드·계측 경계가 달라 코어 자체 속도 우열을 뜻하지 않는다.

마법 샘플은 원본 잠금·금지·요구조건을 유지한 차지 200%·강타 매직 캐논의 첫 타격 cannon1이다. 전체 콤보 대미지와 구분한다. 두 마법 입력의 빠른 초기해는 최종 조합과 같았으며 지팡이의 추가 정밀 시간은 최적성 증명에 사용됐다. 전체 입력의 10초 exact·모바일·P95·메모리 개선을 보증하지 않는다.

## 검증·재현

- npm run verify:architecture: 타입·저장·계산·실행·Native 경계.
- npm run test:regression: 현재 계산·입력·Native/WASM 회귀. 실제 앱 저장 E2E는 CDP 미설정 시 SKIP이다.
- cargo test --offline --manifest-path engine/Cargo.toml --lib: 89개 평가·상한·동점·직렬/병렬·중단/재개 테스트.
- test-crysta-wasm.mjs: 실제 WASM 40개 문제와 raw 완전탐색, 물리/마법·불가능 조건·동점·재개·최종 JS 평가.
- test-crysta-candidate-projection.mjs: 120개 context·5,426 완전탐색 completion·332 replacement 검사. 실제 제품 후보 준비를 사용한다.
- npm run verify:web:browser: Edge 개발/하위 경로·JSON 백업/복원·실제 Worker 완료/취소/재개·세션 재열기.
- npm run bench:optimization:build 후 node tools/benchmarks/benchmark-crysta-magic-wasm.mjs: 사용자 마법 두 입력의 Native/Edge 3회 동치·시간. CODEX_PLAYWRIGHT_PATH와 Edge가 필요하다. 결과는 desktop/target/rust-wasm-magic-comparison.json에 쓴다.

코어와 앱 두 manifest의 fmt/test/clippy를 확인한다. CI도 코어 테스트를 별도로 실행한다. 실제 설치·업그레이드 검증과 브라우저 검증은 구분한다.

2026-10-16 정리 후 실행: architecture·전체 회귀 67개 명령(실제 통과 66개, 저장 E2E 1개 SKIP), 공용 Rust 89개·앱 17개, 두 manifest fmt/clippy 및 WASM clippy, 웹/앱 배포 준비·진입점·실제 Edge·마법 두 입력 3회 동치·S1 427/427 통과. 생성 로그와 계측 JSON은 desktop/target/에 있으며 docs에 다시 쌓지 않는다. 이번 정리는 설치본을 배포하지 않았다.

추가 배치/배포 정리 후 architecture·67개 회귀 명령(66 PASS·1 SKIP)·공용 Rust 89개·두 manifest clippy·웹/앱 prepare·진입점·실제 Edge·S1 427/427을 확인했다. 웹 회귀는 원본 자료/로그/이전 파일 제거, 웹의 Native JS 제외, 라이선스·472개 데이터 아이콘과 동적 on/off 아이콘 보존을 검사한다. 실제 브라우저는 web/public HTTP 오류도 실패로 처리한다. 로그는 desktop/target/layout-*.log에 있다.

## 2026-10-24 웹 추천 초기 조합 전송 오류

루브닐 입력에서 `invalid type: null, expected a string`을 재현했다. compiler의 metadata.initialPackageIds는 현재 장착 조합을 후보에서 찾지 못하면 해당 장비에 null을 넣는다. 이전 이름 별칭·제외된 하위 강화·금지된 현재 크리스타가 재현 조건이다. Rust의 Vec<String>과 맞지 않아 WASM 세션 생성이 실패했으며, 같은 전송을 쓰는 Native도 영향을 받는다.

rust-bridge.js의 공통 projectProblem에서 장비 수와 일치하는 문자열 ID 배열만 초기해로 전달한다. 불완전 초기해는 생략해 Rust의 기존 초기해 준비를 사용한다. null 원소를 필터링해 장비 인덱스를 옮기지 않는다. 후보·잠금·금지·요구조건·raw 옵션·계산식은 그대로다. 완전한 초기해는 계속 전달한다.

검증 결과:

- `node tools/tests/application/test-crysta-catalog.mjs`: 수정 전 회귀 실패 확인, 수정 후 PASS. 실제 크리스타 5종·갑옷 3종에서 기존/별칭/하위 강화 제외/금지 초기해 12문제의 WASM exact 점수·조합 ID가 독립 완전탐색과 일치했다. 원본 불변·완전 초기해 보존도 검사했다.
- `node tools/tests/optimization/test-crysta-native-client.mjs`: PASS. 네 장비 각각의 null 초기 ID가 전송에서 생략되고 원본·후보는 보존된다.
- `node tools/tests/optimization/test-crysta-wasm.mjs`: PASS, 기존 40개 완전탐색 비교.
- `npm run verify:architecture`, `npm run web:build`: PASS.
- `npm run test:regression`: 74개 중 71 PASS·저장 E2E 1 SKIP, web-runtime/account-server 2개는 sandbox의 localhost EACCES로 실패했다. 해당 두 파일만 격리 밖에서 재실행해 모두 PASS했다. 합산 73 PASS·1 SKIP이며 전체 명령이 한 번에 성공했다고 보고하지 않는다.
- Playwright/Edge 1280×900: 실제 콤보의 루브닐 타격 선택→결과 탭→빠른 추천→정밀 계산. 현재 장착 댄드라이언을 추천에서 금지해 초기 ID null을 발생시켰다. 수정 전 브리지를 Worker에 제공하면 같은 오류가 발생하고, 수정 후 개발 웹과 /calculator/ 배포본에서 모두 exact 542,558·feasible·금지 준수·단일 Worker 재사용을 확인했다. 페이지 오류·HTTP 오류 없음. Browser plugin이 없어 설치된 Playwright를 사용했다.

브라우저 재현은 방어구 2슬롯만 열고 나머지 6슬롯은 빈 잠금, 요구조건은 null로 둔 기능 검사다. 전체 후보의 성능 Gate·사용자의 정확한 저장 입력·모바일·공개 배포는 이번 검증 범위가 아니다. 스크립트와 화면은 저장소 밖 Codex visualizations의 verify-revenir-web.mjs·revenir-web-fixed-{dev,built}.png에 보관했다.

## 2026-10-24 전체 후보 웹 지연 수정

사용자는 같은 세팅의 http://127.0.0.1:5173/에서 이전 2~3초보다 느려지고 정밀 계산 초기에 보장 오차가 80%를 넘는다고 보고했다. 전체 슬롯 루브닐 fixture로 재현했다. 이전 변경의 두 슬롯 기능 검사는 전체 후보 성능을 보증하지 않았다.

원인은 두 가지였다. 첫째, ID 통합으로 일반 크리스타가 81개에서 182개로 증가했다. 추가된 기초 고정 스탯 계열 99종 때문에 원시 조합이 장비별 약 3~4천 개에서 1.6~1.8만 개로 커졌고, 기존 Pareto 비교 한도에 걸려 준비 후보도 증가했다. 둘째, 새 리틀 해머의 ATK_UP_VIT=25가 하나라도 있으면 기존 단조 좌표 상한을 전체 탐색에서 비활성화했다. VIT 기본값 1에서는 이 옵션의 기여가 절삭 후 항상 0인데도 느슨한 공급 상한만 사용하게 됐다.

### 기본 스탯 비례의 안전성 판정

JS calculator.js의 statAtkUp/statMatkUp와 Rust evaluator.rs의 candidate_stat_up은 기본 STR/DEX/AGI/INT/VIT만 참조한다. 스탯%와 스탯+로 늘어난 총 스탯을 비례 옵션에 다시 곱하지 않는다. 이 계산식은 바꾸지 않았다. 한손검 STR/DEX의 기본 ATK 기여는 기존 무기 계수 검증을 유지한다.

joint_supply.rs에서는 각 비례 좌표의 네 장비별 최솟값/최댓값을 합산해 전체 비율 구간을 구한다. 고정 기본 스탯 B와 기존 비율 r에 대해 두 끝점의 floor_ratio(B,r+합계,100,0)가 같으면 구간 전체의 추가 ATK/MATK가 상수다. 이 경우에만 기존 단조 상한의 비례 옵션 조건을 통과한다. 음수·분수와 절삭 경계를 포함하며 결과가 변하는 비례, 음수 기본값, 기존 비율/불리언 등 다른 안전 조건은 그대로 fallback한다. B=1·25%는 0, B=1·200%는 2다. 네 장비에 25%씩 있으면 먼저 100%를 합산하므로 B=1에서도 1이 될 수 있다는 경계를 검사한다.

스탯 비례 조건의 전면 제거는 자동 승인 검토에서 정확성 위험으로 거절됐다. 이후 위 상수 증명으로 범위를 제한했고, 조건부 적용을 검증했다. Pareto 비교 한도 1M→40M 변경도 자원 사용 위험으로 거절돼 적용하지 않았다. 기본 한도·후보 축소 알고리즘·트리 분할·게임 계산식은 유지했다.

### 사용자 지정 추천 후보 범위

사용자는 STR+1/STR+2와 같은 단순 기초 크리스타를 자동 추천에서 제외하도록 명시했다. 현재 catalog에서 ID9401~9504에 존재하는 99종을 대조했다. STR/INT/VIT/AGI/DEX, HP/MP, 명중/회피, ASPD/CSPD, 크리티컬률의 단일 고정값 계열이며 조건 옵션이 없다. 튜토리얼 용도라는 분류는 사용자 지시이며 게임 코드에서 별도 튜토리얼 플래그를 추출했다는 뜻이 아니다.

problem-compiler.js의 자동 pool에서만 해당 ID 계열을 제외한다. 전체 553개 원본 데이터·수동 장착/계산·이름/ID 저장 호환·명시 잠금은 유지한다. 제외한 크리스타가 현재 장착돼 있지만 잠기지 않았다면 교체할 수 있다. exact는 이 허용 범위와 잠금에 대한 최적성이다. 계산 기준 접기에 해당 범위를 표시했다. 최적성 수학으로 약한 크리스타를 임의 삭제한 것이 아니다.

두 전체 슬롯 루브닐 입력의 원시 후보 수는 각각 17,572/16,288/18,332/17,390→3,910/3,319/4,274/3,827 및 17,572/16,288/18,524/17,390→3,910/3,319/4,367/3,827이다. Native/checkpoint v24·실행 정책 v9로 이전 상한의 캐시/체크포인트를 무효화했다. 제품 버전은 v0.7.3을 유지한다.

검증:

- 공용 Rust `cargo test --offline --manifest-path engine/Cargo.toml --lib`: 90개 PASS. 이어 추가한 기본 스탯 독립성 테스트와 상수 비례 테스트를 `--lib stat_reflection`으로 실행해 2개 PASS(신규 기본 스탯 독립성 1개 포함). 비례 좌표 10개×기본값4×기존비율4×증분3=480개 경계와 4장비 합산을 확인했다.
- 공용/앱 fmt·clippy PASS. `cargo test --offline --manifest-path desktop/Cargo.toml`: 앱18·headless11·parallel4 PASS. 앱 crate는 lib target이 없어 최초 `--lib` 명령은 실패했고, 전체 manifest 명령으로 재검증했다.
- `test-crysta-wasm.mjs`: 비례 기여가 일정/변하는 물리·마법 조건을 기존 40개 raw 완전탐색 비교에 포함해 PASS. 실제 JS 최종 평가·exact 점수/ID·재개 동치 유지.
- `test-crysta-catalog.mjs`: 기초 계열99종 전수·자동 pool 제외·keepLowerUpgrades와 독립·STR+1 이름/ID 잠금·수동 옵션 보존 PASS. 기존 7,742개 옵션 대조·소형 WASM oracle 유지.
- `npm run verify:architecture`, `npm run web:build`, `npm run test:regression`: PASS. 회귀74개 중 실제73 PASS·앱 저장E2E1 SKIP. S1 427/427 PASS.
- `npm run verify:web:browser`: 개발/하위 경로·전체 후보 루브닐 exact·단일 Worker 재사용·취소/중단/재개·JSON/세션 재열기 PASS. 기초 계열 제외 후 fresh Worker 3회는 preview+precision 1,195.9~1,214.6ms, 정밀643.3~674.1ms였다. 이 명령의 시간은 최초 문제 compile/UI 렌더링을 제외한다.

최종 http://127.0.0.1:5173/ 비교는 새 Edge 프로세스로 기존 compiler/WASM 각1회(정밀8초 제한), 최종 compiler/WASM 각3회다. 원시 compile·preview·정밀·JS 최종 평가를 포함한다. 첫 fixture는 최종 1,016.6~1,029.9ms(정밀627.4~638.2ms), 저장 fixture는 2,501.9~2,536.0ms(정밀2,036.9~2,069.1ms)로 모두 exact였다. 수정 전에는 둘 다 정밀8초 후 bounded, 각각 gap90.7%/64.8%였다. 최종 점수1,149,067.74/1,951,026.42·조합ID는 수정 전의 최선 조합과 일치하고 feasible·JS 재평가도 통과했다. 페이지 오류 없음·preview/정밀 Worker1개 재사용을 검사했다. 로그는 desktop/target/web-reflection-bound-comparison.json, 기초 계열 제외 전 상한 수정만의 비교는 web-reflection-bound-only-comparison.json에 있다. 실행 도중 기존5173 서버 종료를 확인해 같은 주소로 개발 서버를 다시 실행했다. 이미 열린 페이지는 새로고침해 새 WASM/후보 정책을 로드해야 한다.

## 2026-10-24 웹 공유 메모리 병렬화

- WASM의 wasm-threads feature에서 wasm-bindgen-rayon 1.3.0/no-bundler를 사용한다. stable 단일 WASM과 nightly-2025-11-15 + rust-src/atomics/bulk-memory 공유 WASM을 별도 산출한다. 최대 공유 메모리1GiB. CLI는 기존0.2.127이며 CI/설치 문서도 같은 명령을 사용한다.
- coordinator가 초기 세션·트리·frontier를 보존하고 정밀 실행에서만 논리 코어1~64의 풀을 연다. Native의 노드 claim·평가·동점 incumbent·중단 부모 재삽입·배치 병합을 재사용한다. 후보를 Worker마다 compile하지 않는다. deadline16ms 요청 후 join 경계에서 진행/중단을 발행한다. 브라우저 격리 미지원은 기존 단일 WASM이며 JS 탐색은 없다.
- dev/account 서버에 COOP same-origin·COEP require-corp를 적용하고 parallel 모듈/snippets를 하위 배포 경로까지 복사한다. 외부 호스트도 헤더 설정이 필요하다. 설정은 web/README.md, 제어 계약은 native-optimization-runtime.md를 따른다.
- 최초16스레드 구현은 단일보다 느렸다. Edge CPU 프로파일에서 스탯 반영 키 format/소문자 변환, box_stats의 이미 존재하는 키 삽입, decimal 변환의 임시 String 할당/해제가 대부분을 차지했다. 상수 키·기존 값 변경·스레드별 문자열 버퍼 재사용으로 할당 경합을 제거했다. 계산식·합산/내림 순서·BigInt fallback·후보·분할 정책은 그대로다. 문자열 재사용은 원래 변환과2,867개 입력/캐시 eviction을 대조한다.

검증 명령/결과:

- `cargo test --manifest-path engine/Cargo.toml --lib`: 93 PASS. `cargo test --manifest-path desktop/Cargo.toml --no-default-features`: headless11/parallel4/app18 PASS. 양쪽 fmt/clippy PASS. atomics nightly 경고와 파일시스템 hardlink cache 경고는 빌드 실패가 아니다.
- `npm run verify:architecture`, `npm run test:regression`: PASS(74개 실행,73 PASS/Native storage E2E1 SKIP). 실제 앱 저장 E2E는 TORAM_E2E_CDP 없음.
- `npm run verify:web:browser`: 개발/하위 배포 경로·UI·JSON/세션 복원·preview coordinator 재사용. verify-web-parallel은1~64의 각 요청 스레드에서12개 소형 문제, 총768개 raw 완전탐색의 점수/동점ID·불가능 결과 동치. deadline/paused/resume/cancel·하위 Worker 전부 종료·격리 없는 단일 fallback PASS.64-thread oracle의 공유 메모리 high-water는137,560,064bytes; 초기1,310,720bytes. 전체 문제의 메모리 상한 측정은 아니다.
- `node tools/verification/audit-stack-source-links.mjs --require-s1`:427/427 PASS. `npm run ai:audit`, `git diff --check`: PASS.

스레드 비교는 Edge156.0.4314.42 한 프로세스의 fresh Worker 각3회다. 최종 전체 슬롯 fixture의 정밀 시간은 단일544~552ms,2개428~448ms,4개251~259ms,8개150~164ms,16개129~141ms였다. preview는 별도이며 Node compile은 제외한다. 모든 실행에서 점수1,149,067.74와 ID가 일치했다. 로그는 build/tmp/wasm-parallel-measurements.json에 쓴다. Browser plugin이 없어 설치된 Playwright/Edge를 사용했다.

실제5173도 헤더가 적용된 서버로 재시작했다. 새 페이지/Worker 각3회, raw compile→preview→정밀→JS 재평가를 포함한 전체 시간은 첫 fixture567~589ms(정밀146~147ms), 저장 sword-shield fixture776~849ms(정밀281~326ms). 둘 다 crossOriginIsolated=true·hardwareConcurrency=16·threadsUsed=16·exact이며 이전 점수/조합ID와 일치했다. 로그 build/tmp/web-parallel-local.json. 이 측정은 한 Edge 프로세스 내 반복이며 새 프로세스10회/P95나 모든 입력10초 exact 보증이 아니다. 실제 사용자 탭은 새로고침해야 한다. 외부 배포·다른 브라우저/기기는 미검증이다.

전체 입력의 10초 exact·10회 새 프로세스 P95·메모리 개선을 주장하지 않는다. 실제 사용자 저장 파일을 받지 않았으므로 보존된 루브닐 fixture 두 개로 검증했다. 공개 배포·모바일은 미검증이다.
