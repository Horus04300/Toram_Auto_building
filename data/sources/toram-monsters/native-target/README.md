# 대상 기본 스탯 연결 근거

2026-10-18. 동의받아 이전에 보존한 GameAssembly 모듈의 PE 스냅샷을 정적으로 분석했다. 이번 분석은 게임 실행·프로세스 접근을 하지 않았다. `index.json`은 메타데이터 토큰/함수 주소/파일 SHA-256, `metadata.json`은 선언과 enum의 원본 위치를 보존한다. 직접 실행한 scoped Ghidra 결과이며 REA Evidence ID는 없다.

## 내성 단위

`IMobStatusCalculator`의 메타데이터 선언 순서는 MaxHp(0), Level(1), NecessaryHit(2), Def(3), MagicDef(4), CutAttack(5), CutMagicAttack(6)이다. `PlayerAttackBase.calcBaseDamage`(0xd6cd60)는 물리 계열에서 슬롯 5, 마법 계열에서 슬롯 6을 조회하고 `(100-cut)/100`을 피해에 곱한다. 정적 overload(0xd6cd20)의 인자 이름도 `atk, lv, targetLv, cut, mobPropCut`이며 동일 식을 사용한다. 따라서 CutAttack/CutMagicAttack은 앱의 물리/마법 내성 입력에 쓰는 백분율 포인트다. 100 분모 상수는 저장 모듈의 VA 0x7fff61b52cfc에서 float32 100으로 확인했다.

`MobBattleStatus`의 두 getter는 마스터의 +0x44/+0x48을 바로 반환한다. 필드 보스에 일반 입장 보스의 부위 합산이나 난이도 배율을 적용하지 않는다.

## 일반 입장 보스의 부위

`BossMobBattleStatus.get_Def/get_MagicDef`는 난이도로 스케일한 본체 값에 등록된 미파괴 부위의 getter 결과를 더한다. `MobPartsStatus.get_Def/get_MagicDef`도 동일한 난이도 배율을 사용한다. 각 항을 따로 float32 곱셈 후 int32 절삭하므로 합계를 한 번에 스케일하면 Easy 등의 경계에서 달라질 수 있다. 그 뒤 버프 배율과 상태이상 처리를 거친다. 앱 기본값은 버프·상태이상이 없는 정적 상태다.

`MobPartsStatus` 생성자는 type 8(BodyCutCorrection)을 bodyCut(+0x20), type 7(PartCutCorrection)을 partsCut(+0x18)에 연결한다. 보스 본체의 CutAttack/CutMagicAttack getter는 미파괴 부위의 **bodyCut**을 합산한다. `MobPropertyCut`은 등록된 보정 속성 전부의 Values[0](물리)/Values[1](마법)을 합한다. 부위 마스터의 원시 cutAttack/cutMagicAttack을 더하는 식이 아니다. 보스 본체 마스터에 붙은 type 8도 이 getter가 직접 더하지 않는다.

부위의 `IsDead`는 Hp==0이다. `BossMobBattleStatus.SetPartsMaster`는 본체 PartsList에 존재하는 부위 ID만 등록한다. 그 생성/활성 상태가 모든 스크립트 단계에서 관측된 것은 아니므로, 전체 참조 부위를 합산하는 앱 상태는 "등록 부위 전체 미파괴"라는 정적 시나리오로 표시해야 한다. 본체 PartsList의 value는 같은 필드의 부위 마스터 참조이며, 연결 실패를 0으로 대신하면 안 된다.

고난도 부위는 별도 클래스다. `HighRaidMobPartsStatus.get_Def/get_MagicDef`는 해당 부위의 type 32 고정 플래그를 먼저 검사하고, 없으면 `trunc(f32(f32(partDef)/100)*f32(selectedLevel))`를 쓴다. 일반 난이도 배율을 이 클래스에 확장하지 않는다. 다른 고난도 규칙은 해당 클래스의 별도 근거를 따라야 한다.

## 크리티컬 저항

`PlayerAttackBase.checkCriticalPercent`는 대상에서 property type 6을 조회한 경우만 `MobPropertyCriticalResist.TryGetValue`를 호출한다. 없으면 원래 확률을 유지하므로 기본 저항 0이다. 관리자는 같은 type의 속성을 원본 순서대로 모으며 UID로 스탯 적용 여부를 필터하지 않는다. 이 크리티컬 경로는 해당 목록의 첫 속성 Values[0]을 쓴다. UID를 난이도나 단계 선택자로 해석하면 안 된다. 상태이상·버프에 의한 저항 감소는 별도 전투 상태다.

현재 보존된 Boss 비트 5,196변종 중 type 6은 2,274개에 하나씩, type 32는 158개에 하나씩 있다. 이 두 속성의 중복 행은 없다. 이 수는 최신 스냅샷에 대한 감사 결과이며 미래 입력의 중복 검증을 생략하는 근거가 아니다.

## 관성 변동률

`EnemyMobActionManagerBase.Damaged`는 조건을 만족하는 타격에서 마스터의 +0x34/+0x35/+0x36 byte(ExpDefNormal/Skill/Magic)를 `MobStatus.CalcExpDef`에 전달한다. 해당 함수는 맞은 계열의 값은 빼고 다른 계열은 더한 뒤 각각 50~250으로 제한한다. 이는 관성 피해 배율의 백분율 포인트 변동량이다. 원시 byte를 현재 관성 배율로 표시하면 안 된다. 실제 타격 이벤트·동기화·예외 스킬의 자동 재현은 이 기본 데이터 연결 범위에 포함되지 않는다.

## 재현

`TraceToramTarget.java`는 PE SHA-256과 image base를 검사하고 `index.json`의 선택 함수만 분석한다. `index.json.reproduction`에 실행 형식이 있다. JVM 설정/캐시/임시 폴더는 `build/tmp/toram-target-native` 아래로 한정했다. 전체 모듈 자동 분석, 모듈/메타데이터 수정, 게임에 대한 쓰기는 수행하지 않았다.
