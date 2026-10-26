# 장비 옵션의 정적 계산 근거

2026-10-26. 저장된 2026-10-22 GameAssembly 스냅샷과 같은 버전의 IL2CPP 메타데이터에서 선택한 **53개 함수**를 Ghidra 12.1.4로 디컴파일했다. 게임 실행·프로세스 연결·현재 이벤트 조회는 하지 않았다. 이 자료는 직접 실행한 Ghidra 산출물이며 REA MCP Evidence ID를 발급받은 자료가 아니다.

`index.json`은 입력 경로·SHA-256, 상수의 VA/원시 바이트/float32 값, 메서드 토큰·VA, C 파일 해시와 성공 여부를 기록한다. `method-map.json`은 재현 입력이며 `metadata-bindings.json`은 ElementType, BonusType, IPlayerStatusCalculator, GameEventManager의 원문 메타데이터 선언을 보존한다. `oldIndex`와 `newIndex`는 이 폴더에서는 모두 현재 메타데이터 인덱스다.

## 입력 식별

| 입력 | SHA-256 |
| --- | --- |
| `build/tmp/update-pipeline-20261022/snapshot/GameAssembly.snapshot.dll` | `49cce5c641aa2077c0395f24640f87ec9925d8919bbfb137638d65b7c6e8eb0d` |
| `build/tmp/update-pipeline-20261022/snapshot/GameAssembly.mapped.bin` | `33fa1bc4a533cba3f99f0d711fb14ca6e9a2bee06b834484c98af2d2336767b1` |
| `build/tmp/update-pipeline-20261022/installed-source/global-metadata.dat` | `c5cb57c13fb2f4ba9258b8cf155ee866a8f67eee30f32d043e1fd854bba2eec9` |

Image base는 `0x7ffe99740000`, Assembly-CSharp 메서드 포인터 테이블의 mapped 파일 오프셋은 `0x31036b0`이다. 토큰 RID에 대해 `table + (RID - 1) * 8`의 u64 포인터를 읽는다. 이 테이블을 다른 어셈블리의 동일 RID에 적용하면 안 된다.

## 수치 단위와 반올림

- `BonusManager.GetBonusValue`(15733, `0x7ffe9a4eb350`)와 `getDataBonusValue`(15736, `0x7ffe9a4eeb50`)는 일치하는 bonus type의 정수 value를 합산한다. `/10`이나 `/100`을 하지 않는다.
- `GetBonusPercentValue`(15734, `0x7ffe9a4eb220`)는 위 정수 합계를 float32로 바꿔 **100.0f로 나눈다**. 이것은 도감 문구의 배율과 별개다.
- `GetBonusConstant_Rate`(15739)는 constant를 정수 합산하고 rate를 `1.0f`에서 시작해 각 `f32(value) * f32(0.01)`을 더한다. 합계를 마지막에 한 번 나누는 방식과 float32 경계가 다를 수 있다.
- 원문 옵션 표시 배율은 상위 폴더 `option-display-rules.json`과 `native-update-20261022`에 별도 보존한다. 표시 단위와 계산 소비 함수를 하나로 간주하지 않는다.

## 스탯 비례 ATK·MATK: cap166~175

`BonusManager.CulcConvertAtk`(15744, `0x7ffe9a4e9e90`)는 cap166~170, `CulcConvertMAtk`(15745, `0x7ffe9a4ea180`)는 cap171~175를 소비한다. 입력은 PlayerPrimaryStatus의 **기초** STR/INT/VIT/AGI/DEX(+0x14/+0x18/+0x1c/+0x20/+0x24)이며 장비 반영 후 스탯이 아니다. 대응하는 getter의 현재 토큰과 본문도 함께 보존했다.

각 계열은 STR→INT→VIT→AGI→DEX 순서로 딕셔너리에 추가되어 열거된다. 정상적인 이 딕셔너리 구성의 순서에서 계산은 다음과 같다. `f32`는 매 연산의 IEEE754 binary32 반올림, `trunc`는 0 방향 정수 변환이다.

```text
term[i] = f32(f32(f32(rawBonusTotal[i]) / 1000.0f) * f32(basePrimary[i]))
total = f32(...f32(f32(0 + term[STR]) + term[INT]) ... + term[DEX])
return trunc(total)
```

각 항을 먼저 floor하지 않는다. 양수 항 합계와 음수 항 합계를 따로 float32로 누적해 각각 trunc한 값은 별도 out 인자다. 반환 total을 `trunc(positive) + trunc(negative)`로 치환하지 않는다. 예를 들어 각각 0.6인 두 항의 반환은 1이며, 음수 -0.6 한 항의 반환은 0이다.

표시 퍼센트는 `f32(raw * f32(0.1))`지만 실제 계산은 **raw / 1000.0f**다. 표시 퍼센트를 100으로 나누는 경로는 같은 연산이 아니다. 경계 예: raw=7, 기초 스탯=1000이면 native 항은 정확히 7.0이고 반환은 7이다. 표시값 0.699999988079071을 100으로 나눠 float32 곱셈하면 6.999999523162842가 되어 trunc 결과가 6이 될 수 있다. 원시 tenths를 보존하거나 확인된 정수 격자에서 복원해야 이 차이를 피할 수 있다. 수동 입력의 격자 밖 임의 소수나 i32 범위 밖 값까지 게임과 동일하다고 주장하지 않는다.

divisor1000.0f는 VA `0x7ffe9c049c90`, 바이트 `00007a44`다. index에는 100.0f, 0.01f, 10.0f 등 함께 읽은 12개 상수를 기록했다.

## 속성 및 대상 속성 피해: cap65·53~59

메타데이터 ElementType은 None0, Fire1, Water2, Wind3, Earth4, Light5, Dark6, Normal7, Mana8이며 특수 값 Frame11/Ice12/Thunder13/Rock14도 존재한다.

- `BonusManager.GetElementKiller`(15749, `0x7ffe9a4eb860`)는 대상 Fire1~Normal7을 각각 cap53~59에 연결한다. 다른 값은 0이다.
- `CalcElementKillerBonus`(14280, `0x7ffe9a4a96d0`)는 그 대상에 맞는 cap의 **GetBonusValue 정수 합계**에 별도 스킬 버퍼0x44a의 파라미터0x34를 더한다. cap53~59 원시값은 표시 퍼센트와 같은 정수 percentage point이며 raw tenths가 아니다.
- `CalcElementBonus`의 두 overload(14278/14279)는 기본100·약점25·조건에 맞는 ElementPower·대상 killer·별도 버프를 같은 퍼센트 합계에 더한 후 float32 0.01f를 곱한다. 대상 killer는 공격의 약점 여부와 독립적으로 해당 대상에만 더해진다. 모든 속성 피해를 무조건 일반 ELEM_P에 더하면 안 된다.
- `SkillUtil.CheckWeakElemet`(31357, `0x7ffe9a812710`)의 정확한 공격→대상 약점 관계는 Fire→Earth, Water→Fire, Wind→Water, Earth→Wind, Light↔Dark다. Mana8·Normal7·기타 값에는 false다. `GetWeakElement`(31359)는 그 역관계를 반환하고 나머지는 None0이다.
- main staff14/MD15의 magic attackType2는 공격 속성이 None0/Normal7 이외이면 ElementPower를 더하고, 약점이면 별도로25를 더한다. 그 외 무기도 **약점인 magic attackType2**에서는 같은 ElementPower를 더한다. 양쪽 분기는 동일한 인터페이스 helper를 slot0x1e로 호출한다. 메타데이터 IPlayerStatusCalculator의 zero-based slot30은 get_ElementPower다. helper의 원본 제네릭 이름과 전체 interface thunk는 별도로 복구하지 않았다.
- `PlayerSecondaryStatus.get_ElementPower`(13591)는 `floor(f32(baseINT / 10.0f))`에 별도 버퍼0x40b 파라미터0x32를 더한다. 이 스킬 버퍼까지 모든 장비 효과로 간주하면 안 된다.
- `PlayerStatusBase.GetEquipElement`(13760)는 main cap65를 사용하며 main bow12/bowgun13 + sub arrow19에서 arrow cap65가 0이 아니면 화살 속성을 우선한다. 최종0은 Normal7이 된다. `GetEquipSubWeaponElement`(13761)는 별도 보조 cap65를 읽고 없으면 Normal7이다.
- `InitializeElement`(14288)와 `GetWeaponElementType`(14289)의 조사 경로에는 Mana8을 대상 약점으로 바꾸는 정규화가 없다. 개별 스킬의 속성 override 전부를 조사했다는 뜻은 아니다.

## 남은 scalar·이벤트 분류 원장

이 표는 원시 옵션의 보존·정적 합산과 실제 전투/보상 소비를 구분한다. 옵션의 명칭만으로 미확인 소비 공식을 만들지 않는다.

| cap | 메타데이터 이름 | 이번 근거로 확인한 범위 | 후속 소비/한계 |
| --- | --- | --- | --- |
| 48 | bRespawn | get_Respawn(13599)은 `trunc(f32(f32(1-avatar188/100)*300)-cap48)`를 반환. GetRespawnRate(13624)는 별도 비율 getter | 부활 사건·시간 진행은 별도. cap48 정수를 비율로 일괄 치환하지 않음 |
| 125 | bVerticalResist | scalar 등록 범위121~131, signed i16 값→AddBonus, 일반 GetBonusValue 정수 합산 | 피격 유형 판정·최종 경감식 미추출. 원시 연결 가능, 전투 소비는 notModeled |
| 131 | bBlackholeResist | 위와 같은 scalar 경로 | 블랙홀 피격 사건·최종 경감식 미추출. 전투 소비는 notModeled |
| 143 | bHelpMaster | scalar 등록 범위135~165, funcSetInstantBonus는 signed i16 값→AddBonus(...,instant=true) | 도움 행동의 시간/효과 소비 미추출. 전투 소비는 notModeled |
| 163 | bGrantStopFlinch | 위와 같은 instant scalar 경로 | 움찔 부여 성공/차단 사건 미추출. 전투 소비는 notModeled |
| 176 | bPetExpRate | 명시적 일반 scalar handler 등록, signed i16 값·정수 합계 보존 | 펫 경험치 보상식/서버 반영 미추출. 보상 소비는 notModeled |
| 177 | bGemDustDropRate | cap176과 같은 handler 등록·합산 | 마소 보상식/서버 반영 미추출. 보상 소비는 notModeled |
| 114 | bEventCheck | 전용 eventCheck handler. low byte(raw value)를 이벤트 type로 검사. false이면 현 스크립트의 나머지를 종료, true이면 다음 줄 진행 | 현재 활성 이벤트 집합은 외부 입력. 캘린더·날짜·활성 여부는 추정하지 않음 |

scalar handler의 `raw value == 0`은 내부 calcValue(+0x6c)를 대신 사용하는 특수 경로다. 일반 정적 장비의 비영 값은 signed i16 그대로 AddBonus에 전달한다. `funcSetBonus`와 `funcSetInstantBonus`(15864/15865), ctor(15855), GetBonusValue를 근거로 삼는다. 원시 연결이 가능하다는 판단은 피해식·보상식까지 확정했다는 뜻이 아니다.

cap114의 정확한 흐름은 다음과 같다.

1. ctor는 0x72를 eventCheck(15875, token0x06003e04, VA0x7ffe9a4f8410)에 따로 연결한다. 일반 숫자 옵션 루프의 대상이 아니다.
2. eventCheck는 `GameEventManager.CheckOngoingGameEventType((byte)line.value)`(16664, token0x06004119, VA0x7ffe9a526960)를 호출한다. signed i16의 unsigned low byte이므로 `raw & 255`이며 0과 음수에도 같은 규칙이다. 일반 scalar handler의 0→calcValue 치환을 여기에 적용하지 않는다. raw9는 **이벤트 type9**이며 다음9줄의 개수가 아니다.
3. CheckOngoingGameEventType은 ongoingEventList(+0x40)가 비었으면 false, 아니면 그 byte의 membership을 반환한다. SetOngoingGameEventType(16663)은 제공된 enumerable로 목록을 교체한다.
4. true→handler 반환0→Run(15857)의 index(+0x3c)가1 증가한다. 이후의 일반 조건·제어 줄을 포함한 스크립트 진행을 계속한다. false→반환2→finished(+0x38)=true→해당 bonusScript 처리를 끝낸다. 앞에서 이미 추가한 효과는 되돌리지 않는다. 후행 이벤트 marker가 있어도 false 뒤에 도달하지 않는다. 앞선 장비 조건의 jump가 event marker 자체를 건너뛴 경우 그 marker를 실행하지 않으므로 원시 줄 순서를 보존해야 한다.

따라서 재현 입력은 명시적인 활성 event type 집합일 수 있다. 저장된 코드에서 현재 서버의 집합이나 계절 날짜를 알아낸 것으로 설명하지 않는다. 입력이 없다고 활성으로 간주하지 않는다.

## 재현

저장된 `ghidra-review-3` 프로젝트의 같은 program을 `-readOnly -noanalysis`로 사용했다. 정상 실행한 명령과 같은 형태는 다음과 같다. 출력 폴더는 새 경로를 사용한다. Java/Ghidra 설치·MCP 설정·게임 실행은 필요하지 않다. Ghidra는 기존 사용자 OSGi 캐시·로그를 쓸 수 있어야 한다. 이 실행에서 프로젝트 수정은 폐기된다.

```powershell
$repo = (Get-Location).Path.Replace('\', '/')
$evidence = "$repo/data/sources/toram-items/native-option-calculation"
$out = "$repo/build/tmp/option-native-reproduce"
& 'C:/Program Files/Eclipse Adoptium/jdk-25.0.1.8-hotspot/bin/java.exe' `
  '-Djava.system.class.loader=ghidra.GhidraClassLoader' `
  "-Duser.home=$repo/build/tmp/option-native-20261025/home" `
  '-Dfile.encoding=UTF-8' '--enable-native-access=ALL-UNNAMED' '-Xmx2G' `
  -cp 'C:/ghidra_12.1.4_PUBLIC/Ghidra/Framework/Utility/lib/Utility.jar' `
  ghidra.Ghidra ghidra.app.util.headless.AnalyzeHeadless `
  "$repo/build/tmp/update-pipeline-20261022" ghidra-review-3 `
  -process GameAssembly.snapshot.dll -readOnly -noanalysis `
  -scriptPath $evidence -postScript TraceToramOptionCalculations.java `
  "$evidence/method-map.json" $out -log "$out.log"
```

## 한계

디컴파일 C는 원래 C# 소스가 아니다. 공용 native 함수는 먼저 붙은 다른 타입의 alias를 함수명으로 표시할 수 있으므로 index의 메타데이터 토큰·VA·선언을 기준으로 식별한다. 재사용한 signature helper는 일부 enum을 pointer로 표시한다. 반환 타입이 pointer로 보이는 handler 결과0/2도 원본 enum 선언과 구분한다. 모든 버프·모든 스킬 override·실제 피격·보상 결과를 전수 검증하지 않았다. 확정한 정적 수치/분기와 notModeled 사건을 구분한다.
