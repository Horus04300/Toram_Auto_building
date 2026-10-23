# 길드 레이드 대상 수치 근거

2026-10-19. 동의받아 보존했던 GameAssembly PE 스냅샷을 scoped Ghidra로 정적 분석했다. 현재 게임 실행·프로세스 접근·서버 요청은 하지 않았다. REA Evidence ID는 없으며, `index.json`에 선언 토큰·네이티브 주소·파일 해시, `report.json`에 정확 연산 순서와 미확인 범위를 보존했다. 이전 고난도 근거와 frozen contract는 수정하지 않았다.

## 현재 전투 레벨과 레이드 레벨

`GuildRaidRoomData.SetCurrentHpCount(byte n)`은 `CurrentLevel = max(40,n*4)`를 설정한다. `ReceiveBossSymbolData`도 남은 HP 게이지 수로 현재 레벨을 만들고, 최대 HP 게이지 수로 별도 `GuildRaidLevel = max(40,maxHpGauge*4)`를 만든다. `GuildRaidBossMobActionManager.SetMobLevel`과 상태 생성자는 전달된 정수 레벨을 그대로 보관한다. 일반 입장 난이도나 HighRaid 레벨식을 대신 쓰면 안 된다.

40~1020 및 4 단위는 byte HP 게이지 수에서 유도한 표현 범위다. 실제 서버 입장 상한을 확인한 것이 아니다. 클리어 후 다음 최대 게이지 수는 서버의 held/symbol/sync 자료로 전달된다. 이번에 본 클라이언트 경로만으로 모든 성공에 동일한 증가량을 대입하는 공식은 확정할 수 없다.

## 정적 기본 수치

연산마다 float32를 유지하고 최종 int 변환은 0 방향으로 절삭한다.

- DEF/MDEF: `trunc(float32(int32(raw * Level)) * float32(0.01))`. 곱셈은 먼저 정수이며, 고난도 `raw/100*Level`과 연산 순서가 다르다.
- 명중 요구치: `trunc(float32(float32(float32(Level)*1.5)*float32(rawHit))*float32(0.01))`.
- 물리/마법 내성: `rawCut + trunc(Level/10) + 미파괴 부위 BodyCut 합계`. 이 getter는 고난도 property32 고정 플래그나 property40 배율을 직접 사용하지 않는다.
- 크리티컬 저항: 공통 getter는 첫 type6 속성의 Values[0]을 사용한다. 레벨이나 길드 전용 배율을 직접 더하지 않는다. 동적 버프/상태의 감소는 별도다.
- property40은 DEF/MDEF/명중의 비율·고정 보정을 제공한다. 원본 속성 뒤에 서버 randomProperty가 추가되므로, 서버 옵션 미확보 상태를 실제 옵션 적용 완료로 설명하면 안 된다.

소테리아는 UUID1195를 공유해도 `100500:1`과 `100500:2`가 다른 원본 개체다. 첫 개체의 DEF/MDEF는 175/350, 둘째는 300/125다. 기본 크리티컬 저항은 둘 다10이다. 서버 보정·부위 없는 사례:

| 개체 | 레벨100 DEF/MDEF | 레벨104 DEF/MDEF | 레벨200 DEF/MDEF | 레벨100 물리/마법 내성 |
| --- | --- | --- | --- | --- |
| 100500:1 | 175/350 | 182/364 | 350/700 | 25/40 |
| 100500:2 | 300/125 | 312/130 | 600/250 | 40/25 |

## HP와 부위

HP는 raw MaxHp와 선택 레벨을 직접 사용하지 않고 별도 `hpGage`를 사용한다. 정확 식은 report.json과 `self-check.py`에 있다. 현재 레벨44 이상 4배수라면 게이지 수를 Level/4로 역산할 수 있다. 레벨40은 n0~10이 겹치므로 HP를 하나로 확정할 수 없다. n25/레벨100 HP9,780,750, n26/레벨104 HP10,756,951이다. n132/레벨528부터 계산 결과가 signed int32를 초과하므로 양의 HP로 확장하지 않는다.

길드 부위는 일반 `MobPartsStatus`를 생성하며, 해당 방의 난이도 값을 받는다. HighRaid 부위의 레벨 보정은 적용하지 않는다. 이번 주본체6계열에는 부위가 없으며, 향후 부위가 생기면 방 난이도·활성 상태를 추가 확인해야 한다. 미확인 값을 0으로 대신하지 않는다.

`python self-check.py`는 float32 사례와 byte범위 HP 반올림, 모든 index 파일 해시를 검사한다. 이는 정적 번역 검증이며 실제 게임 전투 관측이 아니다. 앱·추출 파이프라인·기존 근거 파일은 수정하지 않았다.
