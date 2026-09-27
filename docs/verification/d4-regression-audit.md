# 후보 8: 6·7·12번 성능 회귀 감사

- 날짜: 2026-09-22. 기준 소스 v0.7.1. 시작 시 작업 트리는 깨끗했다.
- 사용자 요청: 기본·강한 유틸리티 제한·마법·듀얼 입력으로 유지/되돌림을 판단한다.
- 재현 도구: tools/audit-d4-performance-regressions.mjs. P6의 export-only context patch 기능을 사용한다.

## 비교 설계

최신 코드를 target/regression-audit/crate에 복사한 최소 Rust crate에서 모든 변형을 같은 Cargo.lock·release 설정으로 빌드한다. 제품 Rust 파일은 수정하지 않는다. 예전 변경 전 바이너리와 비교하여 다른 최적화의 효과를 섞지 않는다.

| 변형 | 변경한 부분 |
| --- | --- |
| current | 현재 6·7·12번 모두 유지 |
| no12 | 다섯 유틸리티 값을 모은 후 조건 검사. 통과할 때만 피해 계산(6번 유지) |
| no6 | 전체 summary 계산 후 조건 검사. 12번은 6번의 세분화이므로 함께 해제 |
| no7 | bridge의 매 배치에서 snapshot을 만드는 호환 메서드 호출. 계산/탐색 코드는 유지 |

no12는 단계별 종료만 비교하며 이미 바뀐 독립 스탯 계산 순서까지 과거 코드로 되돌리지 않는다. no7은 실제 서비스 UI/IPC·진행 알림을 재현하지 않는 bridge 비교다. snapshot 생성 절감이 모든 스레드 수의 실행 시간 개선을 보장하지는 않는다.

기본/HP 40,000/마법/듀얼 전체 후보를 P6 compiler·Pareto로 준비한다. 마법·듀얼은 기존 parity 사례의 입력 패치를 P6에 적용한 고정 시나리오이며 사용자의 실제 저장 빌드를 대표한다고 주장하지 않는다. HP 제한은 다른 요구조건을 null로 해제한다. 8·16스레드, 변형별 새 프로세스 3회. 각 회차에서 실행 순서를 정방향/역방향/정방향으로 바꾼다. 30초 세션 예산에 exact가 아닌 결과는 시간 비교에서 탈락시키도록 도구가 실패한다.

빌드·테스트와 성능 측정은 겹치지 않는다. 점수·ID·상한은 입력별 전 변형·스레드에서 같아야 한다. 평균과 중앙값을 함께 기록하여 한 번 느린 실행이 평균을 왜곡하는지 구분한다. 실측 데이터·소스 해시는 d4-regression-audit-measurements.json에 기록한다. 세션 wall은 JS 준비/IPC를 제외한다. cold 10회 P95나 모든 입력의 10초 exact 검증이 아니다.

재현 명령: node tools/audit-d4-performance-regressions.mjs build → prepare → run → verify. 생성 binary/input은 src-tauri/target/regression-audit에만 둔다. verify는 각 입력에서 16개씩 뽑은 65,536조합 JS exhaustive oracle과 네 변형의 점수·ID를 비교한다.

## 측정 결과와 판단

시간 단위는 ms. 다음은 중앙값이며 평균·범위·원본 96회는 JSON에 보존했다.

| 입력 | 스레드 | 현재 | 12 해제 | 6·12 해제 | 7 해제(별도 binary) |
| --- | ---: | ---: | ---: | ---: | ---: |
| basic | 8 | 3663.3 | 3464.7 | 3369.4 | 3452.2 |
| basic | 16 | 2797.2 | 2762.2 | 2711.7 | 2782.3 |
| hp40000 | 8 | 1369.0 | 1422.0 | 1444.9 | 1369.3 |
| hp40000 | 16 | 1141.4 | 1193.8 | 1211.5 | 1134.4 |
| magic | 8 | 834.9 | 837.5 | 806.5 | 834.7 |
| magic | 16 | 692.1 | 695.1 | 682.2 | 691.4 |
| dual | 8 | 18313.3 | 17886.5 | 17416.3 | 17560.7 |
| dual | 16 | 14588.8 | 14469.6 | 14157.3 | 14421.6 |

기본·HP 제한·마법·듀얼의 exact 점수는 각각 14,097 / 13,051 / 5,580 / 21,458이다. 96회 모두 입력별 추천 ID와 upper가 같았다. 기본/마법/듀얼은 constraint 가지치기 0회, HP 제한은 약 295만 회였다. 이는 envelope 제거 수이며 모든 완성 조합 탈락 수를 뜻하지 않는다.

6·12번을 함께 제거하면 기본·마법·듀얼에서는 중앙값이 약 1.4~8.0% 줄지만, HP 제한에서는 약 5.5~6.1% 증가한다. 12번만 제거해도 HP 제한 중앙값이 약 3.9~4.6% 증가한다. 따라서 두 변경을 유지한다. 기본 입력의 선검사 비용은 실제로 남으며, 이번 감사로 회귀를 전부 해결했다고 표시하지 않는다. 사용자의 실제 입력 분포를 모르는 상태에서 모든 입력의 승자를 임의로 정하거나 HP 값에 맞춘 분기 정책을 추가하지 않는다.

7번의 별도 binary 비교는 코드 생성·배치 및 실행 편차가 섞인다. 이를 구분하기 위해 build-snapshot 모드로 동일 binary에서 런타임 플래그 하나로 snapshot 생성만 바꾸고 정/역순 각 2쌍을 추가 비교했다. 지연 생성과 즉시 생성에서 계산 함수는 동일하며, 즉시 생성은 black_box로 반환 객체의 생성을 보장한다. 이 보조 검사는 이전 앱 binary 자체의 재현이 아니라 결과 생성 비용을 구분하는 검사다.

| 스레드 | 지연 생성 평균 / 중앙값 | 매 배치 생성 평균 / 중앙값 |
| --- | ---: | ---: |
| 8 | 3486.6 / 3485.1 | 3610.1 / 3544.9 |
| 16 | 2762.0 / 2759.6 | 2787.4 / 2789.3 |

매 배치 생성이 8·16스레드 각각 네 쌍 모두 느렸고, 16회 모두 exact 결과는 동일했다. 7번을 유지한다. 과거의 16스레드 회귀를 결과 생성 생략 자체의 보편적 문제로 재현하지 못했다. 몇 퍼센트 차이에 대해 통계적 유의성이나 모든 PC에서의 속도 향상을 주장하지 않는다.

## 결론

6·7·12번을 유지하고 제품 Rust 코드는 되돌리지 않았다. 이번 변경은 재현 가능한 비교/JS oracle 도구와 검증 기록이다. 입력별 성능 손익을 확인한 8번 감사는 완료했지만, 조건을 대부분 통과하는 입력의 비용 감소는 미해결이다. 자동 평가 경로 선택이나 새로운 상한·탐색 표현은 이번 범위에 넣지 않았다.

추가 비교 재현: build-snapshot 실행 후 D4_AUDIT_SNAPSHOT_CONTROL=1, D4_AUDIT_VARIANTS=current,no7, D4_AUDIT_FIXTURES=basic, D4_AUDIT_REPEATS=4, D4_AUDIT_REPORT=snapshot-control.json으로 run. 기본 run은 8·16스레드/4입력/4변형/각 3회다.

## 최종 검증

- 전체 후보 cold 측정 96회 + 동일 binary snapshot 비교 16회: 입력별 exact 점수·ID·upper 일치.
- node tools/audit-d4-performance-regressions.mjs verify: 4입력 × 4변형 PASS. 입력별 65,536조합 JS exhaustive oracle과 일치.
- cargo test --manifest-path src-tauri/Cargo.toml -q: PASS 156개(43+43+14+56). fmt --check PASS. 제품 Rust 변경은 없다.
- npm run test:r0: PASS 70/70 스크립트. Native 저장 E2E는 CDP 미설정 SKIP.
- npm run verify:r9: PASS. node tools/audit-stack-source-links.mjs --require-s1: PASS 427/427.
- node --check(두 도구), npm run ai:audit, git diff --check: PASS.

Windows x64 / Ryzen 7 9800X3D 16논리 CPU / Node v24.17.0 / rustc 1.98.0. 실제 UI/IPC E2E와 배포는 미실행이다. 실측 입력은 기본/제약/마법/듀얼 네 개뿐이며 사용자의 전체 세팅 분포로 일반화하지 않는다.
