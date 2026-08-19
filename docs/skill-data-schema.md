# 전투 스킬 데이터 스키마 v2

## 범위와 출처

- 대상: 플레이어 빌드·전투·대미지·MP·콤보에 영향을 주는 427개 스킬
- 제외: `Smith`, `Alchemy`, `Tamer` 트리. 제작·합성·펫 전용 기능은 현재 계산 범위 밖이다.
- 출처: `skill_effect_source_links.json`의 트리별 원문 URL. 값·조건·패치 시점이 확인되지 않은 데이터는 추정하지 않는다.
- 카탈로그: `assets/js/data/skill-combat-catalog.js`가 스킬트리 원본에서 모든 대상의 ID·이름·출처를 생성한다.

## 데이터 상태

- `unreviewed`: 카탈로그에는 있으나 효과 원문을 아직 구조화하지 않음
- `partial`: 원문 일부 또는 대표 효과만 구조화됨. 기록된 개별 효과만 계산에 사용할 수 있으며, 빠진 조건·효과는 추정하지 않음
- `verified`: MP, 조건, 효과, 공격 프로필, 상태 전이가 출처 기준으로 확인됨

## 스킬 정의 계약

기본 정의는 `skill-effect-data.js`의 `skills`에 두고, 트리별 정의는 `assets/js/data/skills/*.js`가 등록기(`skill-effect-registry.js`)에 추가한다. 두 집합은 합쳐서 카탈로그 ID와 정확히 하나씩 대응한다. `verified`가 되려면 아래 항목 중 해당하는 모든 항목을 기록한다.

```js
{
  id: 'Tree:skillId',
  treeId: 'Tree',
  skillId: 0,
  nameKo: '스킬명',
  kind: 'attack' | 'passive' | 'buff' | 'utility',
  activeBuff: true, // 공격·유틸리티 스킬도 시전 후 지속 버프가 있으면 사용
  dataStatus: 'unreviewed' | 'partial' | 'verified',
  source: 'treeSourceKey',
  requirements: { mainWeapons: [], subWeapons: [], states: [] },
  cost: {
    mp: { timing: 'cast', value: { op: 'value', value: 100 } },
    items: []
  },
  combo: { canStart: true, canReceiveTag: true, restrictions: [] },
  stateTransitions: [],
  effects: [],
  attacks: []
}
```

식과 조건은 임의 JavaScript가 아니라 `skill-effect-engine.js`의 제한된 AST로만 표현한다. 이 방식은 출처 검증, 안전한 계산, 테스트를 가능하게 한다.

## 적용 단계

| 단계 | 용도 | 예시 |
|---|---|---|
| `build` | 장비·크리스타와 합산되는 지속 패시브 | ATK%, 무기 ATK%, 스탯 증가 |
| `combat` | 활성 버프를 포함한 전투 시점 능력치 | 워 크라이, 오라류 |
| `cast` | 스킬 발동 순간 | MP 소모, 스택 소비, 버프 획득 |
| `hit` | 타격별 판정 | 타수, 피해, MP 회복, 상태 부여 |
| `afterHit` | 타격 완료 후 | 후속타 예약, 누적 스택 증가 |
| `expiration` | 버프 만료 | 효과·상태 제거 |

## 상태 전이

공격하면서 버프·스택을 얻거나 소모하는 스킬은 `stateTransitions`로 기록한다. 버프와 스택은 단순 체크박스가 아니라 계산 가능한 런타임 상태다.

```js
{
  event: 'cast' | 'hit' | 'afterHit' | 'expiration',
  operation: 'grant' | 'addStacks' | 'consumeStacks' | 'setStacks' | 'remove',
  stateId: 'unique.state.id',
  stacks: { op: 'value', value: 1 },
  maxStacks: 5,
  durationSeconds: { op: 'value', value: 30 },
  effects: [{ phase: 'combat', type: 'stat', key: 'CRIT', value: { op: 'value', value: 25 } }],
  when: { op: 'truthy', value: { op: 'ref', path: '...' } }
}
```

상태가 대미지에 영향을 주면 효과 조건에서 `states.<stateId>.stacks`, `states.<stateId>.active`를 참조한다. 따라서 같은 스킬이 공격과 버프를 동시에 수행해도 발동 순서가 보존된다.

## 자원·공격·콤보

- MP는 `cast` 시점의 조건식 비용으로 기록한다. 무료 발동, 연속 사용, 스택·버프에 따른 할인도 조건식으로 표현한다.
- MP 회복·HP 소모·아이템 소모는 자원 전이로 기록한다. 타격 수에 비례하는 회복은 `hit` 단계에 둔다.
- 공격 스킬은 각각의 타격을 독립 `attacks` 항목으로 둔다. 타수, 계수, 상수, 물리/마법, 거리·발도 판정, 조건, 후속 상태 전이를 포함한다.
- 콤보 태그의 공통 규칙은 별도 `combo-rule` 데이터에 둔다. 스킬별 데이터에는 콤보 시작 가능 여부, 태그 수신 제한, 연속 사용·콤보 불가 조건만 둔다.

## 콤보 공통 규칙

`assets/js/data/combo-rule-data.js`는 사용자가 제공한 게임 내 콤보 도움말 본문을 구조화한 데이터다. 다음 10개 태그를 저장한다: 연속공격, 충전, 신속, 강타, 심안, 집념, 무적, 흡혈, 강인, 반사.

- 두 번째 스킬부터 태그를 붙일 수 있고, 대미지 태그는 버프 스킬에 적용하지 않는다.
- 태그가 적용된 공격의 대미지 배율은 모든 증감 반영 뒤 10%~150%로 제한한다.
- 충전은 MP 저장량을 새 충전으로 덮어쓰되, 대미지 감소는 누적한다. 콤보 종료 시 남은 저장 MP를 정산한다.
- 콤보 포인트의 정확한 최대치 공식은 제공된 본문에 없으므로 수치를 추정하지 않는다. 현재 데이터에는 역할과 마지막 스킬 실행 시 경험치 획득 조건만 기록한다.

실제 콤보 계산기는 스킬의 `cost`, `kind`, `combo` 속성과 이 공통 데이터가 모두 `verified`인 경우에만 결과 계산에 연결한다.
## 입력 순서

1. 패시브와 상시 전투 보정
2. 활성 버프와 상태 전이
3. 공격 스킬의 MP·공격·스택 소비/획득
4. 콤보 태그 규칙
5. 계산기와 결과 UI 연결

상세 데이터가 `verified`가 되기 전에는 계산기 자동 반영 대상으로 승격하지 않는다.