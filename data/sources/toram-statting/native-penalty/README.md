# 옵션부여 범주 페널티·상한·슬롯 근거

2026-10-20. 현재 조사 결과이며 앱 계산·저장·최적화는 수정하지 않았다. 저장된 PE 스냅샷/메타데이터의 지정 함수만 Ghidra 12.1.4 `-noanalysis`로 분석했다. REA provider 환경을 사용할 수 없어 직접 Ghidra를 사용했으며 REA Evidence ID는 없다. 게임 프로세스 접근·옵션 부여 실행은 하지 않았다.

원문은 이 폴더의 C 파일, 함수 토큰·주소·SHA-256·상수 원시 바이트는 `index.json`, 짧은 규칙은 `rules.json`이다. 튜플 필드명은 `../native-schema/report.json` 및 `EnhanceProperties2` 생성자의 원시 저장 위치와 연결했다. `Coefficient` 필드의 소재 소비 의미는 이 조사에서 검증하지 않았다.

## 범주 페널티

`SmithGrant.GetUsePotentialPoint` → `EnhanceGetPropertyPosition` → `CalcUsePotentialPoint` 순서다. 가운데 함수는 기존 옵션과 UI 선택을 대조하여 **변경량 배열**과 **부여 후 전체 옵션 배열**을 별도로 만든다. 실제 비용은 변경량으로, 범주 개수는 부여 후 전체 배열로 계산한다.

범주는 일반 옵션 `EnhanceCost[Type].AbilityCategory`, 속성(Type65)은 `EnhanceElementCost[Value].AbilityCategory`다. 부여 후 옵션의 Type이 0이거나 exclusionType이면 제외한다. 부호·수치·변경 여부를 검사하지 않으므로 양수·음수·기존 유지·새 옵션·변경 옵션이 함께 센다. **직접 계산 함수에 Type이 남은 값0을 전달하면 이것도 센다.** UI가 값0을 지우는 모든 경로까지 확인한 것은 아니다.

각 범주의 개수를 n이라고 할 때 n≥2인 범주만 `n²×0.05`를 가산한다. 두 개는20%, 세 개는45%, 다른 범주의 두 개가 더 있으면 합계65%다. 서로 다른 범주에 하나씩 있는 옵션끼리 별도 페널티가 생기는 식이 아니다.

개별 비용/반환량을 signed short에 누적한 뒤 총합에 배율 `1+범주 가산합`을 **한 번** 곱하고 int로 0 방향 절삭한 후 short로 변환한다. 양수와 음수를 따로 계산해 페널티를 곱하거나 줄마다 페널티를 먼저 절삭하면 달라질 수 있다. 예를 들어 원래 비용3인 두 줄에20%이면 전체 비용은7이고 줄마다 절삭한 합6과 다르다. 모든 부동소수점 연산은 float32이며 `.05`도 정확한 실수0.05와 구분한다.

## 수치 상한: 장비 레벨이나 전역 레벨 상한이 아님

`SmithGrantInfoWindow.getEnhanceMax(isUpper, checkType)`는 `IPlayerStatusCalculator.get_Lv`인 **해당 캐릭터 레벨 L**과 다음 스킬의 현재 레벨을 읽는다. 이름은 저장된 한국어/영어 Skill 텍스트의 같은 ID·kind0을 직접 대조했다(`skill-links.json`).

| 게임 스킬 ID | 이름 | 식의 기호 |
| --- | --- | --- |
| 365 | 장비 강화 / Customize Equipment | s1 |
| 366 | 정확한 강화 / Accurate Customization | s2 |
| 367 | 장인의 강화기술 / Expert's Customization | s3 |

세 스킬의 음수 레벨을0으로 보정한다. `r=(10+3s1+3s2+3s3)/100`이며 식의 매 연산은 float32다. `B=BaseMax`, `S=OverRate`, `R=Rate`, `M=isUpper ? UpperMax : LowerMax`라 두면 다음과 같다. `trunc`와 정수 나눗셈은 0 방향 절삭이다.

```text
L < 210:
  max(1, min(trunc(float32(r*B)), trunc(L/10), B))

L >= 210:
  n = max(0, trunc(L/10)-20)
  increment = trunc(float32(R*n))*S
  hardLimit = (M-B)*S+B
  value = min(trunc(float32((increment+B)*r)), hardLimit)
  Type가 12,22,24,26,28,30,32이고 value>B이면:
    value = B+trunc((value-B)/S)
  max(1,value)
```

반환값은 양수/음수 방향의 **정규화된 선택기 절댓값 한도**다. 속성(Type65)은 별도 선택 목록이며 위 일반 수치 도메인으로 계산하지 않는다. 실제 67개 일반 옵션으로 만든 캐릭터 Lv300·세 스킬 Lv10 예시는 `cap-examples.json`에 selector magnitude로 보존했다. 예: STR +30/-30, STR% +10/-10이다. HP/명중/회피/DEF/MDEF/ASPD/CSPD는 상세 화면에서 경계 초과분에 OverRate를 곱하는 변환을 거친다. 따라서 이 반환값에 표시 배율만 곱해 raw operand나 최종 화면 수치라 부르면 안 된다. UpdateDetailVal의 라벨 경로와 실제 grant operand 왕복·실행 검증은 구분한다.

초벌 분석은 Math.Max/Min 꼬리 호출을 PIC로 오인해 하단 분기를 누락했다. 최종 파일은 mscorlib의 Max/Min 토큰→주소를 대조하고 함수 경계를 정의하여 재분석했다. 누락 블록/PIC 경고가 있는 초벌 C는 최종 근거에 포함하지 않았다.

## 사용 가능 슬롯

```text
3 + floor(float32((s2+2)*float32(.3)))
  + floor(float32((s3+4)*float32(.2)))
```

native 함수는 s1도 읽지만 반환식에 사용하지 않는다. s2/s3 Lv0일 때3, Lv10/10일 때8이다. s2는 Lv2/5/8에서1/2/3칸, s3는 Lv1/6에서1/2칸을 더한다. 실제 배열10칸과 스킬로 쓸 수 있는 슬롯을 혼동하지 않는다. Floor는 mscorlib 토큰0x06000871의 함수와 thunk의 원시 jump 대상으로 대조했다. 기존 제품 명세의 정확히8옵션은 별도의 제품 계약이다.

## 성공률의 이번 확인 범위

`getSuccessSkillRate`는 `max(s1,0)+(s2>0 ? 10+s2 : 0)+(s3>0 ? 20+s3 : 0)`이다. Lv10/10/10은60, Lv1/1/1은33이다. 로컬 Smith 원문의 단순 `s1+2s2+3s3`와 저레벨에서는 다르므로 해당 원문만으로 코드를 바꾸면 안 된다.

`OnGrantCheckButton`은 소재 보유량을 검사하고 확인 창을 연다. 전체 성공률 식·확률 clamp·서버 난수/개별 옵션 판정은 이번 결과로 확정하지 않는다.

## 검증과 재현

```powershell
python assets/source-data/toram-statting/native-penalty/self-check.py
```

12개 함수 SHA·상수, 부호/값0/제외/범주별 개수, 합산 뒤 절삭, 스킬 슬롯, Lv209/210/300 경계·스킬계수·기본 성공 보너스 검사가 PASS다. 같은 명령이 현재 catalog.json으로 `cap-examples.json`을 생성한다. 게임 실행 검증이 아닌 보존 코드와 소형 재구성 사례 검사다.

`TraceToramPenalty.java`는 고정 PE SHA/image base를 검사한다. 기존 saved PE를 private Ghidra 프로젝트에 `-import ... -noanalysis -scriptPath <이 폴더> -postScript TraceToramPenalty.java <index.json> <새 출력폴더>`로 넣는다. 설정/캐시/임시 경로는 작업용 build/tmp로 지정하고 사용자/REA 전역 설정은 변경하지 않았다.

유효 범위 밖 short/int 오버플로, 서버에서 허용하는 전체 입력, UI 값0 정규화 전수, 완성 옵션 집합만으로 실제 다단계 소비량을 대체할 수 있는지는 보장하지 않는다. 다단계 반환량·잠재력 본식은 `../native-potential/`의 별도 근거를 따른다.
