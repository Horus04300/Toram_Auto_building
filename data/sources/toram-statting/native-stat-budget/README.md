# Lv325 제작자 스탯 예산과 배분 근거

2026-10-21. 사용자 지시 **“앱 코드에 반영해놓은 값을 이용할 것”**에 따라 현행 앱의 포인트 예산을 채택한다. 게임 서버가 지급 가능한 모든 훈장 포인트를 전수 복구한 결과와는 구분한다. 제작자는 제작용 기본 스탯에 투자하며, 옵션 부여자(Lv325·TEC255)와 별도 캐릭터다.

## 채택한 예산

`assets/js/ui/status-points.js`의 실제 `ToramStatusPoints.pointBreakdown(325,325)` 호출 결과는 다음과 같다.

```text
레벨 포인트 = 325×2 = 650
레벨 훈장 = Math.round(325/10)×5 = 165
고정 보너스 = 25
합계 = 840
```

앱 UI는 STR/INT/VIT/AGI/DEX **다섯 기본 스탯 값의 합 자체**를 840과 비교한다. 각 기본 최소값1을 이미 포함한 예산이다. 따라서 여기에 기본값을 다시 더하지 않는다. 개인 스탯 네 개(CRT/LUK/MEN/TEC)를 기본값1에 두면 native 투자량 집계는 `840−5=835`다.

앱 소스 SHA와 실제 호출 결과는 index.json·budget.325.json에 연결했다. 앱의 공식 레벨 공지 출처가 최신 서버 상태를 새로 검증했다는 뜻은 아니다. 이 작업에서 현행 앱의 규칙을 바꾸지 않았다.

## 네이티브 배분 제한

저장된 GameAssembly 스냅샷의 선택 함수만 Ghidra로 정적 분석했다. 실행 중인 게임·프로세스·서버에는 접근하지 않았다. REA retained Evidence ID는 없다.

- `UIBuildPanel..cctor`: `DefaultMaxPoint=255`, `LimitBreakMaxPoint=510`, `StatusLimitBreakPoint=500`.
- `UIStatusBar.SetMaxPoint`: 한계돌파 후 첫 다섯 기본 스탯에510을 적용하며 개인 스탯은255를 유지한다.
- `PrimaryStatusData.IsOverStatus`: `Σ(min(아홉 스탯,255)−1)≥500`인지 확인한다. `System.Math.Min(Int16,Int16)` 토큰0x06000857→VA0x7fff61011120 및 원시 비교/cmovle 명령과 대조했다.
- `PlayerPrimaryStatus.GetAllStatusPoint`: `아홉 스탯 값의 합+남은 StatusPoint−9`를 집계한다. 레벨에서 지급 예산을 새로 계산하지 않는다.
- `UpdateStatusPoint`는 전달된 point를 저장한다. 따라서 이 클라이언트 함수만으로 서버 훈장의 최대 지급량을 확정하면 안 된다.

한계돌파는 Lv325라는 이유만으로 자동 허용되는 가정이 아니다. 다음 실제 배분 순서로 충족할 수 있다. A/B는 장비에 관련된 기본 스탯 또는 여유 포인트를 넣을 기본 스탯이고 나머지 기본 스탯은1이다.

| A | B | 사용 투자량 | 의미 |
|---:|---:|---:|---|
| 1 | 1 | 0 | 초기 최소값 |
| 255 | 1 | 254 | 기본 상한 도달 |
| 255 | 247 | 500 | 한계돌파 조건 충족 |
| 510 | 247 | 755 | 주력 스탯 확장 상한 도달 |
| 510 | 327 | 835 | 앱 예산 전부 투자 |

따라서 한 종류 스탯으로 잠재력을 올리는 장비는 **최대510→보너스51**, 두 종류 합으로 올리는 장비는 **510+327=837→보너스41**이다. 잠재력 보너스 공식의 소스는 사용자 문서 `docs/statting.md`이고 실제 제작 소비 코드의 전체 적용 순서는 별도 native-crafting 근거와 연결한다.

| 장비 | 관련 스탯 | 보너스 |
|---|---|---:|
| 한손검·활 | STR+DEX | 41 |
| 마도구 | INT+AGI | 41 |
| 발도검 | DEX+AGI | 41 |
| 선풍창 | STR+AGI | 41 |
| 지팡이 | INT | 51 |
| 양손검 | STR | 51 |
| 자동활 | DEX | 51 |
| 권갑 | AGI | 51 |
| 방어구 | VIT | 51 |

한 스탯 장비의 나머지327은 제작 잠재력에 더 기여하지 않지만, 모든 포인트를 합법적으로 투자할 수 있음을 보이는 용도다. 장비·버프의 보정 스탯을 기본 투자 스탯에 합산하지 않는다.

## 검증

```powershell
python assets/source-data/toram-statting/native-stat-budget/self-check.py
```

실제 앱 API의 Lv325 예산, 소스 SHA·9개 native 함수 SHA, Min helper 식별, 한계돌파를 거친 합법적 배분, 단일/쌍 보너스의 상한과 달성 가능성 검사가 PASS다. index.json·metadata.json·common-metadata.json은 주소/토큰/필드를 보존한다.

서버 훈장 최대값·계정 상태를 독립 검증하지 않았다. 앱 예산이 바뀌면 소스 SHA 검사에서 중단하고 재검토해야 한다.
