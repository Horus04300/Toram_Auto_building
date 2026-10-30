# 보스 회피 수치와 플레이어 명중의 연결

`report.json`은 2026-10-22 저장된 GameAssembly/metadata의 SHA-256, 원본 필드·인터페이스 순서·가상 슬롯, 직접 읽은 float32 상수와 Ghidra 12.1.4 산출물 해시를 고정한다. REA 서버에 deep provider 경로가 없어 기존 Ghidra를 직접 호출했다. REA MCP Evidence ID가 발급된 자료가 아니며 게임 실행·프로세스 연결·실전 명중률 측정은 하지 않았다.

## 확인된 연결

- `MobStatusMaster.necessaryHit`은 실제 metadata 필드다. `get_NecessaryHit`은 본체 `+0x38`의 정수를 반환한다. 플레이어 명중으로 역산해 마스터에 저장한 값이 아니다.
- `IMobStatusCalculator` zero-based slot2는 `get_NecessaryHit`, slot7/8은 별도의 가드율/어보이드율이다. `IPlayerStatusCalculator` slot17(0x11)은 `get_Hit`이다.
- `NormalAttackAction.calcPlayerToMobDamage`는 몬스터 slot2 값을 읽고 전투 보정을 거쳐 `PlayerAttackBase.CheckHit` 가상 slot85(+0x688)의 `needHit` 인자로 전달한다. `mp`에는 가상 slot22(+0x298)의 `get_Mp` 반환을 전달한다. 이 인자를 콤보 후 실제 지불 MP와 무조건 동일하다고 설명하지 않는다.
- `PlayerAttackBase.CheckHit`의 재디컴파일 결과는 기존 `native-option-calculation/extended-consumption/14274-PlayerAttackBase-CheckHit.c`와 바이트 단위로 동일하다. 플레이어 slot17의 HIT를 읽어 아래 기본 판정값을 구한다.

```text
E = 호출자가 전달한 보스 측 needHit
H = 플레이어 get_Hit()
Q = min(100, (trunc(mp / 100) + 10) * 10
             - trunc(f32(f32(i32(E - H)) / 3.0f)))
```

`3.0f`는 VA `0x7ffe9c049b74`, 바이트 `00004040`이다. `trunc`는 0 방향 절삭이다. 기본 코드에는 Q의 하한0 clamp가 없다. `mp=0`, 다른 보정 전 E600/H450은 Q50, E600/H597은 Q99, E600/H598은 Q100이다. 따라서 E를 그대로 ‘모든 공격에 필요한 플레이어 명중’이라고 부르면 부정확하다.

이후 상태7 분기는 공격 거리8을 기준으로 Q에0.8f/0.6f를 곱한다. `isFlash` 보정, 절대명중/별도 버퍼, 공격 종류의 반환 예외가 이어진다. 0~99 난수와 Q의 비교는 반환값뿐 아니라 `correct` 출력에도 사용된다. 일반 공격 호출자는 크리티컬 결과와 반환값을 함께 처리하고 별도 `CalcHitReaction`을 호출한다. 위 식을 모든 스킬의 최종 명중 확률이나 Graze·Avoid·Guard까지 포함한 확률로 승격하지 않는다. 이번 도감에는 최종 명중률 계산을 추가하지 않는다.

## 본체와 부위의 경계

필드 일반 `MobBattleStatus`는 본체 원본 값을 사용한다. 일반 `BossMobBattleStatus`는 본체에 난이도 StatusRate를 적용하고 살아 있는 부위의 `get_NecessaryHit`을 더한다. 부위도 자신의 원본값에 같은 난이도 배율을 적용한 뒤 절삭한다. HighRaid도 별도 레벨식/고정 플래그로 구한 본체 값에 살아 있는 부위를 더하며 길드 레이드는 별도 레벨식·서버 보정 경로를 가진다.

현재 발행 `partStats`는 부위의 necessaryHit·guard·avoid를 포함하지 않는다. 도감 표시명은 사용자가 지정한 **회피**, **어보이드율**, **가드율**이다. 회피에는 본체의 확인된 난이도/레벨식을 적용하되 부위 가산·전투 중 보정은 포함하지 않는다. 어보이드·가드는 본체 값이다. 화면에는 시스템 설명이나 ‘원본’ 접미사를 붙이지 않는다. 저장 스냅샷이나 원본 데이터 필드 이름을 바꾸지 않는다.

## 재현·검증

`report.json.methods`는 metadata/token으로 고른10개 함수 선언이다. 기존 `data/sources/toram-items/native-option-calculation/extended-consumption/method-map.json`을 읽고 그 기존 methods를 callees에, report의 methods를 methods에 넣으면 재현 입력이 된다. 기존 `TraceToramOptionCalculations.java`에 이 입력과 새 출력 폴더를 전달해 `analyzeHeadless ... -import <source.snapshotPath> -noanalysis -scriptPath <native-option-calculation> -postScript TraceToramOptionCalculations.java <map> <new-output> -deleteProject`로 실행한다. 설정·캐시·임시 폴더는 작업용 폴더로 지정한다. 템플릿 overload2개는 조사 입력으로만 남기고 본문은 제품 근거에 추가하지 않았다. 공유 generic 함수의 임의 대표 라벨을 의미 연결의 증거로 사용하지 않는다.

`test-boss-target.mjs`는 출처/상수/선언/본문 해시를, `test-catalog-browser.mjs`와 `verify-catalog-browser.mjs [--web]`는 회피/어보이드율의 표시 구분·불필요한 설명/접미사 부재·난이도별 수치를 검사한다. 재현에 필요한 원본 스냅샷은 Git 제외이므로 기존 백업 계약을 따른다.
