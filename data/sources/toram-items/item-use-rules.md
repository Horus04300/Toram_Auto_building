# 소모품 버프·보조 장비 원본 옵션 연결 근거

2026-10-18, 캐시 77596232. 규칙은 `item-use-rules.json`, 보존된 함수·SHA-256은 `native-item-usage/index.json`에 있다. 앱·변환기 수정은 이 조사에 포함하지 않았다.

## 확인한 경로

- `MainPlayer.localUseItem`은 아이템의 BonusLines → `CreateBonus(exec=1)` → 활성 duration이 있으면 `SetDurationBonus`로 연결한다. 이 경로 안에 type 2 전용 분기는 없다. 기존 `CheckUseItem`의 type 50도 사용할 수 있으므로 변환 대상은 `[2, 50]`이다. type 3의 동일한 형태 레코드는 사용 가능하다고 보지 않는다.
- `BonusData..cctor`는 209~224 및 255를 duration 목록으로 만든다. `.ctor`는 그 목록의 cap ID를 `DurationBonusType`(+0x44)에 기록한다. `SetDurationBonus`는 이 ID를 dictionary key로 사용하며, 같은 key의 기존 버프를 목록에서 제거하고 교체한다. 스탯 키가 같아도 duration ID가 다르면 이 조사로 중복 금지를 추가하지 않는다.
- `BonusScriptManager.funcSetTime`은 cap ID를 script Type(+0x30), i16 operand를 duration(+0x48/0x4c)에 넣는다. `timeCheck`는 엔진 경과 시간을 차감한다. 아이템 원문 1800=30분, 900=15분도 이를 뒷받침한다.
- `funcSetBonus`는 nonzero i16을 부호 그대로 `AddBonus`로 보낸다. 0은 현재 script workvalue를 참조하므로 단순 고정 스탯 0으로 처리하면 안 된다. 음수는 페널티로 보존한다.
- 최소 지원 문법은 **첫 유효 slot에 duration marker 하나(209~223), 뒤에는 기존 statMapping으로 확인된 양의 cap ID + 0이 아닌 부호 있는 값만**이다. 조건, 반복, 회복, 상태 명령, 미연결 옵션은 전체 아이템을 미지원으로 남긴다.

## 실제 데이터 대조

원본 11,723개 중 runn marker가 있는 항목은 289개이고, 모두 marker가 하나다. 기존 90개 스탯 매핑 기준 단순 문법에 맞는 항목은 208개다. type 3 두 항목(108002, 108494)을 제외하면 type 2의 204개와 type 50의 2개, **206개**가 남는다. 이 중 3999는 이름이 없으며 이름을 추정하지 않는다. 현재 206개에는 값 0인 스탯 operand가 없다. 이 수치는 상태 전투식 검증 수가 아니다.

| 게임 ID | 이름 | 그룹 / 초 | 후속 cap | 적용 후보 |
| --- | --- | --- | --- | --- |
| 2000 | 플러스바이타 Ⅰ | 211 / 1800 | 12:50 | MAXHP +500 |
| 2537 | 테라 스피드 팟 | 219 / 1800 | 30:1000 | ASPD +1000 |
| 2505 | 불끈 버섯 | 213 / 1800 | 17:10, 18:1 | ATK +10, ATK% +1 |
| 2517 | 마력충전의 마석 | 210 / 1800 | 38:3 | AMPR +3 |
| 108157 | 류아크 진통제 | 209 / 1800 | 12:100, 49:5 | MAXHP +1000, 물리내성 +5 |
| 2945 | 축의금 | 209 / 1800 | 35:100, 64:1 | 자연 HP 회복 +100%, 드롭 +1% |

그룹 이름이 `runn_hp_heal`/`runn_mp_heal`이어도 후속 명령이 고정 스탯만이면 순수 스탯 버프다. 반대로 2913의 `repeatwait` + `mp_heal`은 MP 회복 사건이므로 AMPR 버프로 바꾸지 않는다. 2554는 영문 설명 MDEF +15%와 raw cap29:10이 다르므로 prose를 계산 수치로 쓰지 않는다.

## 보조 장비

`PlayerStatusBase.SetEquip`과 `BonusManager.SetEquipBonus`를 함께 확인했다. sub type 17(방패)·18(단검)·19(화살)·23(두루마리)은 일반 옵션 경로다. sub 15(마도구)·16(권갑)은 옵션 목록을 비운다. sub 10(한손검)은 cap65(속성)만 남긴다. sub 8(발도검)은 skill 0x56>0 및 0x53>9일 때 cap65만 남기고, 나머지 경우 비운다. 필터 predicate는 `__c__DisplayClass59_0.<SetEquip>b__0`에 보존했다. ATK·DEF·제련·안정률 같은 기본값 경로는 이 일반 옵션 허용 목록과 구별한다.

## 근거 한계

성공한 결과는 저장된 PE 스냅샷과 메타데이터 토큰 매핑을 사용하는 Ghidra 12.1.4 지정 함수 분석이다. REA MCP는 provider 환경 누락이 있었고, 프로세스 한정 환경으로 연 private REA 세션은 전체 분석 초기화 시간 초과 후 정상 종료했다. 이 함수들에 대한 REA Evidence ID는 없다. 기존 게임 프로세스에 다시 접근하지 않았다.

스냅샷의 delegate MethodInfo 포인터는 모듈 밖 heap을 가리켜 정확한 heap 바인딩을 복원하지 못했다. constructor의 동일 핸들러 등록, duration 분류/필드 갱신, enum, 아이템 설명을 함께 근거로 삼았다. 아이템 사용 시점·만료 시뮬레이션·이벤트 기간 배율·실제 게임 UI 및 전투식 전수 검증은 수행하지 않았다.

