# 스킬 내용 누락 검증 인수인계 브리프

## 목적과 범위

이 문서는 토람 자동 빌드 계산기의 **스킬 원문 누락 검증과 데이터화**만 이어받기 위한 인수인계다. UI 재설계, 배포·버전, 아이콘/에셋 정리는 범위 밖이다.

목표는 각 스킬트리의 원문 캐시를 기준으로 모든 카탈로그 스킬을 최소 S1(출처 연결)까지 올리고, 계산 가능한 규칙을 데이터·엔진에 연결하는 것이다. 원문에 없는 수치나 상한은 추정하지 않는다.

## 반드시 알아야 할 현재 사실

이전 작업에서는 일부 스킬을 원문 대조해 보완했지만, 이를 “스킬트리 전체 검증 완료”처럼 표현한 오류가 있었다. 실제로는 각 트리의 일부만 S1 이상이다.

현재 검증 도구 기준 예시:

- Blade: S1 출처 연결 9/24, 미완료 15개
- Martial: S1 출처 연결 1/22, 미완료 21개
- 그 외 트리도 기존 상세 정의가 있는 일부만 S1 이상일 가능성이 높다.

따라서 “특정 스킬을 반영했다”와 “스킬트리 전체가 검증됐다”를 절대 혼동하지 않는다. 트리 전체에 대해 `--require-s1`이 통과하기 전에는 전자를 넘는 표현을 쓰지 않는다.

## 원문·카탈로그·정의의 위치

- 원문 링크 목록: `skill_effect_source_links.json`
- 원문 캐시: `docs/sources/skills/<TreeId>.txt`
- 캐시 무결성/출처 목록: `docs/sources/skills/manifest.json`
- 캐시 갱신 도구: `tools/cache-skill-sources.ps1`
- 전체 스킬 카탈로그: `assets/js/data/skill-tree-data.js`
- 계산 대상 카탈로그: `assets/js/data/skill-combat-catalog.js`
- 중앙 상세 정의: `assets/js/data/skill-effect-data.js`
- 트리/주제별 상세 정의: `assets/js/data/skills/*.js`
- 등록기: `assets/js/data/skill-effect-registry.js`
- 효과/조건 AST 엔진: `assets/js/skill-effect-engine.js`
- 스킬트리별 검증 기록: `docs/verification/*.md`
- 기준 문서: `docs/skill-tree-verification-standard.md`

`assets/js/data/skill-catalog-registration.js`가 상세 정의가 없는 카탈로그 스킬에도 뼈대 정의를 만들 수 있다. 따라서 “정의가 존재한다”만으로 원문 검증이 끝난 것이 아니다. `sourceRef`가 있어야 S1이다.

## 현재 감사 도구와 사용법

도구: `node tools/audit-stack-source-links.mjs`

검사 범위:

1. 모든 원문 캐시의 SHA-256이 `manifest.json`과 일치하는지
2. 등록된 모든 `sourceRef.file`과 `sourceRef.anchor`가 실제 원문에 존재하는지
3. 기존 스택 정의의 특정 상한/예외가 유지되는지
4. 전체 또는 선택 스킬트리의 카탈로그 항목이 S1 출처 연결됐는지 범위와 누락 목록을 표시

명령:

```powershell
# 전체 범위 현황만 출력한다. 미완료가 있어도 종료 실패는 하지 않는다.
node tools/audit-stack-source-links.mjs

# 한 스킬트리의 S1 현황과 누락 목록을 출력한다.
node tools/audit-stack-source-links.mjs --tree Martial

# 대상 트리가 모든 스킬을 S1로 연결하지 못했으면 실패한다.
node tools/audit-stack-source-links.mjs --tree Martial --require-s1
```

`--require-s1`은 해당 트리의 모든 카탈로그 스킬이 출처 연결될 때까지 실패해야 정상이다. 이 검사는 S1까지만 보장하며, 수식·상태 전이·엔진 연결·사례 검증(S2~S5)은 별도다.

## 확정된 데이터화 규칙

### 판정 단계

- S0: 카탈로그만 있거나 `sourceRef`가 없는 상태
- S1: 원문 파일과 정확한 anchor를 `sourceRef`로 연결
- S2: 스킬 유형(패시브/공격/버프), 무기·대상·장비 조건 확인
- S3: 원문에 근거한 비용, 수식, 스택, 상태 전이를 모두 기록
- S4: 엔진이 해당 규칙을 실제 계산에 사용
- S5: 정상/경계/조건 변경 사례로 결과 검증

`dataStatus: 'verified'`는 S1~S5 전체 충족 때만 사용한다. 현재 대부분은 `partial`이다.

### 데이터와 UI의 경계

- 데이터 정의가 게임 규칙의 원본이다. UI가 아직 없다고 원문 규칙을 단순화하지 않는다.
- UI가 표현하지 못하는 시간 경과, 피격, 다음 스킬 1회, 전투 자원 변화는 `stateTransitions`, `stackModel`, `notes` 등으로 보존하고 `partial`로 남긴다.
- 스택 UI의 최대치와 효과 상한은 별개다. 원문이 무제한이면 임의의 UI 상한을 넣지 않는다.
- 일반적으로 `requirements.when`에 무기/서브장비 조건을 둔다. 패시브 계산 경로도 이제 이 조건을 검사한다.

### AST/엔진 규칙

`assets/js/skill-effect-engine.js`는 수치/조건 AST를 해석한다. 자주 쓰는 형태:

```js
{ op: 'value', value: 10 }
{ op: 'ref', path: 'skill.level' }
{ op: 'add', args: [/* 식 */] }
{ op: 'multiply', args: [/* 식 */] }
{ op: 'subtract', left: /* 식 */, right: /* 식 */ }
{ op: 'divide', left: /* 식 */, right: /* 식 */ }
{ op: 'tier', cases: [{ when: /* 조건 */, value: /* 식 */ }] }
{ op: 'if', when: /* 조건 */, then: /* 식 */, else: /* 식 */ }
```

조건은 `eq`, `ne`, `all`, `any`, `not`, `gt/gte/lt/lte`, `truthy` 등을 쓴다. 장비 입력의 실제 값은 한국어다. 예: 메인 발도검=`발도검`, 권갑=`권갑`, 선풍창=`선풍창`, 듀얼소드는 메인 `한손검` + 서브 `한손검(듀얼소드)`, 보조 없음=`없음`.

`passiveStatChanges()`는 2026-08-19에 스킬의 `requirements.when`을 확인하도록 보완됐다. 새 패시브는 반드시 보조장비/무기 조건 변경 사례를 테스트한다.

### 상태/스택 규칙

- `stackControl`: 버프 UI가 현재 스택을 수동 입력할 수 있는 유한 스택 상태
- `stackModel`: 시간·피격·HP 등 전투 상태 엔진이 아직 처리하지 못하는 규칙의 원문 보존
- `stateTransitions`: 시전/피격/시간 경과/다음 스킬 등 이벤트 단위 전이
- 전투 자원형 스택은 UI에 넣는 것만으로 자동 누적되는 것이 아니다. 자동 전이는 아직 엔진 과제다.

## 이미 원문 대조·반영한 데이터

아래는 **트리 전체 완료가 아닌**, 실제로 반영된 일부 스킬이다.

### Blade

- 중앙 데이터의 어스투트, 트리거 슬래시, 스파이럴 에어, 일부 패시브, 워 크라이
- 별도 `assets/js/data/skills/blade.js`의 오라 블레이드, 램페이지
- 워 크라이: 양손검 ATK% 보정과 한손검 지속시간 +50초 보정 기록
- 오라 블레이드: 한손검/양손검/듀얼소드 조건 구분
- 주의: Blade S1은 9/24일 뿐이며, 15개는 출처 미연결

### Shot

- 크로스 파이어, 퀵 로더 등 일부
- 크로스 파이어 충전 입력은 레벨별 최대 스택으로 clamp됨
- 다음 스킬/은신 상태 소비 등은 부분 메타데이터이며 자동 전이는 미완성

### Magic

- 랜서, 피날레, 매직 마스터리 일부
- 랜서/피날레 MP, 영창/사거리/핵심 타격 메타데이터 일부 기록

### Martial

- `Martial:11` 아수라 오라만 상세 대조
- ON/OFF, 권갑 조건, 최대 40스택, OFF 스택 보존, CRIT/상수 효과 등 일부
- `Martial:18` 화경은 **미등록(S0)** 이다.
- 화경 원문 핵심: 권갑 전용 MP 100; 모션 중 피해를 0으로 막는 데 성공하면 화경+차크라 버프 획득; 화경은 안정률 +10% 및 메인 권갑 시 WATKP `5 × 레벨%`; 파괴자와 WATKP 합산 최대 50%.

### Halberd

- `Halberd:19` 신속의 수도
- 최대 3스택, 재시전 `addStacks`, 피격 종료, 선풍창 지속시간 +30초, 스택별 ASPD/행동속도/Avoid 회복/MP·내성 페널티 기록

### Mononofu

- `Mononofu:11` 무사도, `Mononofu:14` 양손쥐기
- 발도검/무보조 조건과 정적 패시브 일부

### DualSword

- `DualSword:0` 듀얼 마스터리, `14` 쌍검 단련, `15` 신속의 저력, `16` 세이버 오라
- 세이버 오라는 원문상 고정 최대 스택이 없으므로 `hardCap: null`; HP 5% 미만 종료 모델

### Crusher

- `Crusher:8` 파괴자 버프
- 권갑 조건, MP 100, 600초, WATKP `5 × 레벨%`, 안정률 -10 기록
- 화경과 합산 WATKP 최대 50%는 아직 엔진 미연결

### 기존 스택 데이터

다크 파워 리그렛, 듀얼소드 세이버 오라, 댄서, 민스트럴, 할버드, 기사, 마셜 아수라, 슛 퀵 로더, 스프라이트, 어새신 등에 일부 스택 정의가 있다. 이전에 잘못된 스택 상한을 바로잡은 항목도 있으므로, 새 작업 전에 원문과 개별 대조한다.

특히:

- 이터널 나이트메어는 스택형으로 등록하면 안 됨
- 리그렛의 이로운 효과 상한은 10, 실사용 UI 상한은 15, HP 감소/지속시간은 원문상 별도 취급
- 세이버 오라는 고정 최대 스택이 없음

## 다음 스레드의 우선 작업

1. **먼저 화경을 정확히 등록한다.**
   - `Martial:18`, 원문 anchor `화경 버프 / 권갑 전용`
   - 피해 감소 성공 이벤트 → 화경 및 차크라 버프 부여를 `stateTransitions`로 기록
   - 화경 WATKP와 파괴자 WATKP의 합산 최대 50%를 공통 상태/효과 상한 설계로 결정
   - 차크라의 “낮은 쪽 레벨”, MP 즉시 회복 미발생, 다단히트 시 종료 등은 자동 처리 불가 항목을 명시
   - 추가 후 `node tools/audit-stack-source-links.mjs --tree Martial`로 S1이 2/22가 되는지 확인

2. **트리별로 S1 완결을 먼저 만든다.**
   - 권장 순서: Martial → Blade → Shot → Magic → Halberd → Mononofu → DualSword → Crusher
   - 한 트리 안에서는 원문 순서대로 모든 스킬에 최소 `sourceRef`와 S2 분류를 부여한다.
   - 수식 구현이 어려워도 `sourceRef`, `kind`, `requirements`, `notes`를 먼저 넣어 S1/S2를 완료한다.
   - 완료 판정은 반드시 `node tools/audit-stack-source-links.mjs --tree <TreeId> --require-s1` 통과다.

3. **그 다음 S3~S5로 승격한다.**
   - 패시브 → 단순 버프 → 단순 공격 → 조건부 공격 → 스택/상태 → 콤보 의존 순서
   - 각 변경마다 정상·경계·무기/서브/ON-OFF 조건 변경 테스트를 Node VM으로 작성해 실행한다.
   - 현재 전투 상태 엔진이 지원하지 않는 규칙은 원문 수치를 추정하지 말고 `partial` 및 미지원 이유를 검증 기록에 남긴다.

4. **감사 도구를 계속 확장한다.**
   - 다음 확장 우선순위: S2에서 kind/requirements 존재 여부, S3에서 비용/공격/버프 기본 구조, S4에서 지원하지 않는 효과 타입의 명시적 목록, S5에서 트리별 대표 사례 자동 실행
   - 도구의 “무결성 통과”는 원문 해시·이미 등록된 출처의 정합성이고, S1 범위와 별개임을 출력에서 유지한다.

## 작업 시 지켜야 할 보고 방식

- “트리 검증 완료”는 그 트리의 `--require-s1` 통과 이후에만 사용한다.
- S1 통과도 원문 위치 연결 완료일 뿐, 계산 정확도 완료가 아니다. S2~S5 현황을 함께 쓴다.
- 원문과 데이터가 다른 경우에는 원문 문구, 현재 정의, 수정 사항, 엔진 미지원 여부를 구분해 보고한다.
- 한 번에 여러 트리를 추정으로 채우지 않는다. 한 트리씩 원문과 대조하고 반영·감사·기록한다.
