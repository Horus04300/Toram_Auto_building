# AI 작업 연속 인수인계 — 2026-08-24

이 문서는 새 AI 컨텍스트에 **그대로 전달**하기 위한 압축 기준이다. 상세 근거는 아래 연결 문서를 읽고, 이 문서의 과거 문구보다 실제 코드와 최신 테스트 결과를 우선한다.

## 시작 순서

1. `AGENTS.md`
2. `docs/handoff/current-development-handoff.md`
3. 계산식·스킬 작업이면 `docs/skill-tree-verification-standard.md`
4. 미구현 판단·후속 구현이면 `docs/verification/unimplemented.md`
5. `git status --short`로 사용자 변경을 보존한다.

## Windows 네이티브 샌드박스 초기화 오류 대응

이 환경에서는 파일 패치 도구가 다음 오류로 실패할 수 있다.

```text
windows sandbox failed: helper_unknown_error: setup refresh had errors
```

이는 저장소 코드 오류가 아니라 Codex Windows 샌드박스 helper 초기화 실패다. 읽기·테스트·빌드 명령도 sandbox 권한으로 실패하면 `require_escalated`를 요청해 같은 작업을 다시 실행한다.

파일 수정은 먼저 `apply_patch`를 한 번 시도한다. 위 오류로 `apply_patch`가 실패한 경우에만 다음의 **범위 검증형 Node 우회**를 사용한다.

1. 수정할 파일과 기존 문자열을 읽어 정확한 대상인지 확인한다.
2. Node 스크립트가 기존 문자열의 일치 횟수가 정확히 1회인지 검사한다. 0회 또는 2회 이상이면 즉시 실패시키고 파일을 쓰지 않는다.
3. 그 한 구간만 교체하거나, 명시 경로에 새 문서를 쓴다. payload는 base64/hex로 전달해 PowerShell 인용 문제를 피한다.
4. 직후 파일 내용, `git diff --check`, 영향받는 테스트를 확인한다.

이 우회는 `rm`, `git reset`, 광범위 정규식 치환, 사용자 변경 덮어쓰기에는 사용하지 않는다. 대상 파일·기존 문구·교체 횟수를 모두 명시할 수 있을 때만 쓴다.

## 현재 제품 상태

- 앱: Tauri v2 데스크톱 계산기, 개발 버전 `0.6.0`.
- 사용자 세팅: `%LOCALAPPDATA%\ToramOnlineAutoBuildCalculator`.
- 스킬 원문 연결(S1): `427/427`.
- 스킬트리의 S1~S5 완료 표기는 계산기 범위의 수식·조건·회귀 완료를 뜻한다. 피격·시간·AI·저항 사건을 자동 전이하는 전투 상태 시뮬레이터 완료를 뜻하지 않는다.
- 피격 중심 시뮬레이션은 사용자 지시로 보류다. 다음 스킬 한정 효과·사용 후 소멸·MP 소비/회복·콤보 취소·직접 피해/버프를 우선한다.

## 현재 작업: 원문 대미지식 정합성

사용자가 제공한 ATK·MATK·발도공격·대미지 계산식을 현재 연결된 계산 경로에 맞추는 작업이 최우선이다. **원문에 있는 항목만** 다루며, UI·상태 엔진에 아직 없는 항목(무기 내성, 난이도·부위 파괴, 이터널 나이트메어 등)은 구현·추정 대상에서 제외한다.

- 완료: 발도공격%와 발도공격+를 분리했다. 일진강풍은 발도공격%를 ATK%와 기본 무기 공격력으로 전환하고, 기본 무기 공격력 증가는 무기 ATK%·재련 전 단계에서 적용한다. 발도공격+는 ATK+로 전환한다.
- 완료: ATK/MATK 업(스탯 %)은 기본 스탯만 사용하도록 고쳤고, 내성은 `(ATK + 레벨 차)`에 먼저 적용한다. 원문에서 곱셈인 계산 단계와 발도검·선풍창·듀얼소드 서브의 소수 계수는 단계별 내림을 적용했다.
- 완료: 권갑의 무기 MATK 반영률 50%, 컨버전의 무기·INT MATK(+) 단계, 마법 크리티컬 데미지 52.5% 경계·듀얼 브링거 INT>STR 조건, 스킬·패시브·버프·콤보 배율의 순차 내림을 회귀로 검증했다.
- 다음: 제공된 원문으로 판정 가능한 현재 연결 경로의 경계 회귀는 추가했다. 이후에는 새 원문 근거나 재현 가능한 오차가 제시될 때만 같은 방식으로 확장하며, 미구현 항목은 제외한다.
- 회귀: `tools/test-mononofu-s5.mjs`는 Lv10 발도공격% 50이 기본 무기 공격력 250을 300으로 만든 뒤 무기 ATK%·재련을 적용하는 사례를 고정한다.

## D4 전역 빌드 최적화: 구현 완료 범위

- 대상: 실제 크리스타 425개, 장비 네 부위·각 2슬롯의 전역 8슬롯 추천.
- 구현: 구조 조건 사전 물질화, 잠금·금지·부위·같은 장비 중복·강화 계보 제약, 완결 Pareto, Utility hard constraint, 전수조사 oracle, 안전 상한, JavaScript Worker 취소·진행·캐시, 결과 탭 `exact`/`bounded`/gap 표시.
- Utility 기본 요구: 근거리 MAXHP 10,000(원거리는 없음), MAXMP 2,000 또는 신속의 수도 Lv.10이면 2,300, 맥시마이저 Lv.10이면 듀얼소드 2배 전 AMPR 0·그 외 100, ASPD 1,000. 현재 활성화된 입력만 반영하며 자동 고정 획득처는 없다.
- AMPR: 램페이지·괴력난신·트윈 스톰은 각각 단독으로 평가해 가장 큰 하나만 적용하고, 축지법의 1회성 AMPR은 지속 Utility에서 제외한다.
- 성능 개선: 집계 평가, 상한 경량 결과, 두 부위 동시 분할, 64조합 이하 직접 전수조사.
- 최신 실측: 5초 약 9.2만 평가, 하한 14,090.0409, 인증 gap 약 44.7%. 30초 약 69.6만 평가, gap 24.604%. 따라서 실제 결과는 아직 `bounded`이며 exact로 표현하면 안 된다.

### D4 관련 핵심 파일

- `assets/js/stat-registry.js`
- `assets/js/build-evaluator.js`
- `assets/js/d4-problem-compiler.js`
- `assets/js/d4-global-optimizer.js`
- `assets/js/d4-optimizer-worker.js`
- `assets/js/d4-worker-client.js`
- `assets/js/d4-source-profile.js`
- `docs/architecture/d4-build-optimizer-design.md`
- `docs/architecture/d4-build-optimizer-prerequisites.md`

위 파일 중 다수는 현재 **untracked(`??`)** 다. 미구현으로 오인하거나 삭제하지 말고, 인수인계/커밋 시 반드시 포함한다.

## 사용자 결정으로 보류된 범위

- 유저 제작 장비의 옵션 자동 부여·잠재력 탐색.
- 피격·시간 경과·상태이상 저항·소환/파티 AI 중심 전투 상태 엔진.
- D2 중독 1회 피해의 결과 탭 화면 배치.
- 탱커 전용 옵션의 자동 최적화.

## 다음 작업 후보

현재 원문 대미지식 정합성 작업을 우선하며, 다음 후보는 사용자 선택 없이 임의로 시작하지 않는다.

1. 현재 연결된 MATK·마법 크리티컬·조건부 대미지 계층의 원문 경계값 검증. 미구현 항목은 제외한다.
2. 콤보 포인트·레벨로 임시 8칸 제한을 교체하는 작업. 정확한 최대치 원문 근거가 필요하다.
3. D4의 수식 구간별 정밀 상한 또는 동등한 증명 기법으로 인증 gap 추가 축소.
4. 고정 장비·완성 유저제 장비를 크리스타 후보와 전역으로 통합.
5. v0.5.0 실제 사용 피드백 버그 수정, Windows 코드서명·반복 가능한 릴리스 자동화.

## 최근 검증 결과

- JavaScript 테스트: 2026-08-24 원문 대미지식 반영 뒤 `49/49 PASS`.
- 콤보 충전·집념·심안 회귀: `node tools/test-combo-tags.mjs` PASS.
- D4 소형 oracle·무작위·음수 옵션 상한 검증 통과.
- S1 출처 연결: `427/427 PASS`.
- `npm run desktop:prepare` 통과.
- `cargo test --manifest-path src-tauri/Cargo.toml`: `3/3 PASS`.
- `TORAM_E2E_CDP`가 없으면 네이티브 저장 E2E는 안전하게 skip된다. 실제 인앱 육안 검증은 Windows 실행 보조기 초기화 오류로 자동 Worker/DOM 검증으로 대체했다.

## 최소 검증 명령

```powershell
node tools/audit-stack-source-links.mjs --require-s1
node tools/test-combo-tags.mjs
node tools/test-d4-evaluator-stage1.mjs
node tools/test-d4-global-optimizer-stage2.mjs
node tools/test-d4-worker-stage3.mjs
node tools/test-d4-full-stage3.mjs
npm run desktop:prepare
cargo test --manifest-path src-tauri/Cargo.toml
```

전역 회귀가 필요하면 `tools/test-*.mjs` 전체를 실행한다. 저장소는 현재 더티 상태이므로 다른 사용자의 변경을 초기화하거나 덮어쓰지 않는다.
