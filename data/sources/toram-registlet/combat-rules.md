# 레지스트렛 전투 규칙 검토

166개 ID의 전투 producer를 표시식과 분리한다. `L`은 장착한 젬 레벨, `q`는 `GemCartBufferId` selector다. `Value`라는 이름만으로 백분율·확률·초 단위를 붙이지 않는다. 공통 GetValue는 값이0이 아니고 쿨다운이 끝나며 CheckTrigger가 참일 때만 값을 돌려준다.

원문·producer 연결과 소비 분기 검토는 별개다. JSON의 `nativeQueryRules`는 네이티브 반환식이며 `semanticReview`는 별도로 확인한 소비 규칙이다. `OnGetValue=0`은 효과 없음이 아니다. 장착 유무를 직접 확인하는 소비 경로가 있다.

쿨다운은 `UnityEngine.Time.deltaTime` 연결을 확인해 초 단위다. 화둔술・용염1031의 캐시식은 `ceil(f32(2.5L))`다. `System.Math.Ceiling` 메서드 포인터의 상대 점프가 실제 helper 주소를 가리킴을 바이트로 검증했다. BonusType12/14 등의 반환값은 내부 값이며 HP/MP 최종 표시 단위와 구분한다.

## 사용자 예시

- 맹독 회복12: producer `q=2 → L`, 원문 확률 `L%`, 최대Lv30. 실제 맹독 틱/난수 분모 소비 함수는 아직 미연결이다.
- 스파이크18: producer `q=2 → 5L`, 최대Lv10. 둔족 상태에서 이동 배율은 `0.5 × (1 + 0.01 × 5L)`로 Lv1=0.525, Lv10=0.75다. 다른 스킬 분기가 이를1로 바꿀 수 있다.
- 어보이드 세트50: 장착 여부 `ContainsBuffer(50)`가 장비 제한 검사에 true를 반환한다. `OnGetValue=0`이며 확률식이 아니다.
- 프로텍션 이지스1036: 장착 여부를 확인하고 반대 스킬을 배웠을 때 그 습득 레벨의 버프도 추가한다. 프로텍션263↔이지스264. 두 ActionHit 경로는 두 번째 전체 스킬 동작을 호출하지 않는다.

## 전체 ID

| ID | 이름 | producer 반환/분기 | 상태 |
| ---: | --- | --- | --- |
| 1 | 물리 공격 UP | [BonusType17: L](native/75359.c) | bonus-producer-formula |
| 2 | 마법 공격 UP | [BonusType19: L](native/75444.c) | bonus-producer-formula |
| 3 | 최대 HP UP | [BonusType12: L](native/75448.c) | bonus-producer-formula |
| 4 | 최대 MP UP | [BonusType14: L](native/75452.c) | bonus-producer-formula |
| 5 | 물리 방어 UP | [BonusType26: L](native/75389.c) | bonus-producer-formula |
| 6 | 마법 방어 UP | [BonusType28: L](native/75456.c) | bonus-producer-formula |
| 7 | 명중 UP | [BonusType22: L](native/75419.c) | bonus-producer-formula |
| 8 | 회피 UP | [BonusType24: L](native/75409.c) | bonus-producer-formula |
| 9 | 공격 속도 UP | [BonusType30: L](native/75355.c) | bonus-producer-formula |
| 10 | 마법 속도 UP | [BonusType32: L](native/75385.c) | bonus-producer-formula |
| 11 | 연타 경감 | [q=1: L](native/75494.c) | producer-formula |
| 12 | 맹독 회복 | [q=2: L](native/75487.c) | producer-formula |
| 13 | 불타는 투지 | [q=2: L * 5](native/75374.c) | producer-formula |
| 14 | 신경 제어 | [q=2: L * 2](native/75467.c) | producer-formula |
| 15 | 고양이 눈 | [q=2: 1](native/75378.c) | producer-formula |
| 16 | 고체온 | [q=2: L * 5](native/75423.c) | producer-formula |
| 17 | 응급 수리 | [q=2: L * 5](native/75530.c) | producer-formula |
| 18 | 스파이크 | [q=2: L * 5](native/75516.c) | producer-formula |
| 19 | 우뚝 버티고 서다 | [q=1: L * 3](native/75520.c) | producer-formula |
| 20 | 피투성이 전사 | [q=3: 5 * L; q=7: 5 * L](native/75371.c) | producer-formula |
| 21 | 사일런트 리차지 | [q=7: L * 5](native/75511.c) | producer-formula |
| 22 | 쇼트 슬리퍼 | [q=2: L * 10](native/75508.c) | producer-formula |
| 23 | 마력 불발 | [q=2: 100](native/75441.c) | producer-formula |
| 24 | 몬스터 헌트 | [q=2: 100](native/75464.c) | producer-formula |
| 25 | 커피 브레이크 | [q=2: 10](native/75382.c) | producer-formula |
| 26 | 수행자 | [q=6: 15 - L](native/75490.c) | producer-formula |
| 27 | 펫 오브 어태커 | [q=5: 3 * L; q=6: 30](native/75481.c) | producer-formula |
| 28 | 펫 오브 탱커 | [q=0: 30; q=1: L * 3](native/75484.c) | producer-formula |
| 29 | 긴급 HP 회복 | [q=2: L + 10](native/75399.c) | producer-formula |
| 30 | 긴급 MP 회복 | [q=2: L * 10](native/75403.c) | producer-formula |
| 31 | 마력 후려치기 | [q=3: trunc0(native-stat-query(26) / 2)](native/75438.c) | producer-formula |
| 32 | 절약술 | [q=2: 1](native/75501.c) | producer-formula |
| 33 | 라스트 히어로 | [q=2: L + 10](native/75427.c) | producer-formula |
| 34 | 외로움쟁이 | [q=2: 100](native/75435.c) | producer-formula |
| 35 | 스타트 대시 | [q=2: self.activeRemainingTime (+0x18 float) > 0 ? 1 : 0](native/75526.c) | producer-formula |
| 36 | 햇볕 쬐기 | [q=2: L * 25](native/75366.c) | producer-formula |
| 37 | 운명 공동체 | [q=2: max(0, PartyManager.get_LoginFieldUserPartyMemberNum() - 1)](native/75533.c) | producer-formula |
| 38 | 최후의 저항 | [q=2: L + 5](native/75431.c) | producer-formula |
| 39 | 후방 경계 | [q=1: L](native/75363.c) | producer-formula |
| 40 | 구세주 | [q=2: 1](native/75505.c) | producer-formula |
| 41 | 패닉 | [q=2: L + 10](native/75478.c) | producer-formula |
| 42 | 트랜스퍼 | [BonusType14: (L + -11) * 100](native/75536.c) | bonus-producer-formula |
| 43 | 하이드 콤보 | [직접 장착/소비 경로](native/75416.c) | presence-or-direct-consumer |
| 44 | 무의 자세 | [q=2: L](native/75473.c) | producer-formula |
| 45 | 페일 트래퍼 | [직접 장착/소비 경로](native/75406.c) | presence-or-direct-consumer |
| 46 | 기타리스트 | [q=2: L](native/75413.c) | producer-formula |
| 47 | 쇼트 퍼포먼스 | [q=2: 5](native/75497.c) | producer-formula |
| 50 | 어보이드 세트 | [직접 장착/소비 경로](native-extra/19888.c) | presence-or-direct-consumer |
| 53 | 파이어 달란트 | [직접 장착/소비 경로](native-extra/19909.c) | presence-or-direct-consumer |
| 54 | 워터 달란트 | [직접 장착/소비 경로](native-extra/19945.c) | presence-or-direct-consumer |
| 55 | 윈드 달란트 | [직접 장착/소비 경로](native-extra/19951.c) | presence-or-direct-consumer |
| 56 | 랜드 달란트 | [직접 장착/소비 경로](native-extra/19924.c) | presence-or-direct-consumer |
| 57 | 라이트 달란트 | [직접 장착/소비 경로](native-extra/19933.c) | presence-or-direct-consumer |
| 58 | 다크 달란트 | [직접 장착/소비 경로](native-extra/19900.c) | presence-or-direct-consumer |
| 59 | 구명구급 | Buff subclass 없음 | no-buffer-subclass-in-reviewed-native-map |
| 61 | 타깃 신고 | [직접 장착/소비 경로](native-extra/19942.c) | presence-or-direct-consumer |
| 62 | 퇴근 연락 | [직접 장착/소비 경로](native-extra/19930.c) | presence-or-direct-consumer |
| 63 | 대미지 체크 | [직접 장착/소비 경로](native-extra/19897.c) | presence-or-direct-consumer |
| 68 | 교관 | Buff subclass 없음 | no-buffer-subclass-in-reviewed-native-map |
| 69 | 실력 확인 | [직접 장착/소비 경로](native-extra/19894.c) | presence-or-direct-consumer |
| 70 | 기사의 감 | [직접 장착/소비 경로](native-extra/19921.c) | presence-or-direct-consumer |
| 71 | 치유의 손길 | [직접 장착/소비 경로](native-extra/19915.c) | presence-or-direct-consumer |
| 72 | 철권 | [직접 장착/소비 경로](native-extra/19918.c) | presence-or-direct-consumer |
| 73 | 전속 경호원 | [q=2: L * 3](native-extra/19906.c) | producer-formula |
| 74 | 레드 에리어 실드 | [q=2: L](native-extra/19939.c) | producer-formula |
| 75 | 블루 에리어 실드 | [q=2: L](native-extra/19891.c) | producer-formula |
| 76 | 석화 무적 | [q=2: L](native/75460.c) | producer-formula |
| 77 | 빨리 먹기 | [q=2: L [self.IsActive (+0x18 byte) != 0]](native/75395.c) | producer-formula |
| 78 | 미끄럼 방지 | [q=2: L](native/75470.c) | producer-formula |
| 101 | 하드 히트・강화 | [q=4: L * 5](native/75231.c) | producer-formula |
| 102 | 액셀 블레이드・연장 | [q=2: L](native/75219.c) | producer-formula |
| 103 | 파워 슈트・강격 | [q=4: L * 15](native/75246.c) | producer-formula |
| 104 | 윈 휠・강화 | [q=4: L * 5](native/75240.c) | producer-formula |
| 105 | 술식/애로・추격 | [q=2: L](native/75234.c) | producer-formula |
| 106 | 술식/월・강화 | [q=4: L * 5](native/75237.c) | producer-formula |
| 107 | 스매시・강화 | [q=4: L * 5](native/75249.c) | producer-formula |
| 108 | 소닉 웨이브・강화 | [q=4: L * 5](native/75252.c) | producer-formula |
| 109 | 트윈 슬래쉬・강화 | [q=2: L](native/75258.c) | producer-formula |
| 110 | 패링 소드・강화 | [q=4: L * 5](native/75243.c) | producer-formula |
| 111 | 플래쉬 스탭・강화 | [q=4: L * 5](native/75228.c) | producer-formula |
| 112 | 캐논 스피어・방해 | [q=2: L * 10](native/75222.c) | producer-formula |
| 113 | 일섬・강화 | [q=4: L * 5](native/75225.c) | producer-formula |
| 114 | 칼자루치기・방해 | [q=2: L](native/75255.c) | producer-formula |
| 201 | 트리거 슬래시・속성 | [직접 장착/소비 경로](native/75309.c) | presence-or-direct-consumer |
| 202 | 스파이럴 에어・강화 | [q=4: L * 2](native/75303.c) | producer-formula |
| 203 | 애로 레인・추격 | [q=2: L](native/75267.c) | producer-formula |
| 204 | 패럴라이즈 샷・연장 | [q=2: L](native/75291.c) | producer-formula |
| 205 | 술식/랜서・가속 | [q=2: L](native/75288.c) | producer-formula |
| 206 | 술식/블래스트・가속 | [q=2: L * 2](native/75285.c) | producer-formula |
| 207 | 파워 웨이브・변화 | [q=3: trunc0((GetSkillLevel(107, true) + L) / 2)](native/75294.c) | producer-formula |
| 208 | 셸 브레이크・강화 | [q=2: L * 5](native/75297.c) | producer-formula |
| 209 | 어스바인드・강화 | [q=2: L * 5](native/75282.c) | producer-formula |
| 210 | 에어 슬라이드・압축 | [q=2: 50; q=4: L * 5](native/75264.c) | producer-formula |
| 211 | 드래곤 소드・회심 | [q=4: (L + -11) * 10](native/75279.c) | producer-formula |
| 212 | 드래곤 테일・강화 | [q=4: L * 5](native/75276.c) | producer-formula |
| 213 | 역경의 사자후・적의 | [q=2: L * 300](native/75261.c) | producer-formula |
| 214 | 삼단뚫기・부동 | [직접 장착/소비 경로](native/75306.c) | presence-or-direct-consumer |
| 215 | 재앙베기・부적 | [q=2: L * 5](native/75273.c) | producer-formula |
| 216 | 명경지수・상투 | [직접 장착/소비 경로](native/75270.c) | presence-or-direct-consumer |
| 217 | 소닉 슬라스트・직격 | [직접 장착/소비 경로](native/75300.c) | presence-or-direct-consumer |
| 301 | 소드 템페스트・연장 | [직접 장착/소비 경로](native/75333.c) | presence-or-direct-consumer |
| 302 | 램페이지・회복 | [q=2: L * 50](native/75324.c) | producer-formula |
| 303 | 스모크 더스트・연장 | [q=2: L](native/75327.c) | producer-formula |
| 304 | 헤비 스매시・관통 | [q=2: L * 5](native/75315.c) | producer-formula |
| 305 | 팬텀 레이브・강화 | [q=4: L * 5](native/75321.c) | producer-formula |
| 306 | 다이브 임팩트・수속 | [q=2: L * 2](native/75312.c) | producer-formula |
| 308 | 술식/스톰・연장 | [q=2: L](native/75318.c) | producer-formula |
| 309 | 스톰 블레이저・받아넘기기 | [직접 장착/소비 경로](native/75330.c) | presence-or-direct-consumer |
| 401 | 버서크・억제 | [직접 장착/소비 경로](native/75339.c) | presence-or-direct-consumer |
| 402 | 디코이 슈터・압축 | [q=4: L * 10](native/75346.c) | producer-formula |
| 403 | 술식/임팩트・투기 | [직접 장착/소비 경로](native-extra/19878.c) | presence-or-direct-consumer |
| 404 | 맥시마이저・전환 | [직접 장착/소비 경로](native-extra/19881.c) | presence-or-direct-consumer |
| 405 | 삼단뚫기・회피 | [직접 장착/소비 경로](native-extra/19885.c) | presence-or-direct-consumer |
| 407 | 납도 이동・삭제 | [직접 장착/소비 경로](native/75349.c) | presence-or-direct-consumer |
| 408 | 버서크 ・맹진 | [q=2: L](native/75336.c) | producer-formula |
| 409 | 크로노스 드라이브 강철심 | [직접 장착/소비 경로](native/75343.c) | presence-or-direct-consumer |
| 410 | 수둔술・수경 | [직접 장착/소비 경로](native/75352.c) | presence-or-direct-consumer |
| 1001 | 실드 배쉬・절약 | [q=2: L * 10](native/75663.c) | producer-formula |
| 1002 | 어솔트 어택・급행 | [q=4: L * 10](native/75546.c) | producer-formula |
| 1003 | 마나 크리스탈・가속 | [q=2: (10 - L) * 10](native/75612.c) | producer-formula |
| 1004 | 어새신 스탭・강화 | [q=2: L * 10; q=4: L](native/75543.c) | producer-formula |
| 1005 | 홀리 라이트・신벌 | [q=2: L](native/75595.c) | producer-formula |
| 1006 | 리커버리・회복 | [q=2: L * 10](native/75630.c) | producer-formula |
| 1007 | 힐・절약 | [직접 장착/소비 경로](native/75582.c) | presence-or-direct-consumer |
| 1008 | 강타・극의 | [q=2: L](native/75589.c) | producer-formula |
| 1009 | 집중・극의 | [q=2: L](native/75567.c) | producer-formula |
| 1010 | 추격의 극의・강화 | [직접 장착/소비 경로](native/75648.c) | presence-or-direct-consumer |
| 1011 | 레조난스・화력 | [q=2: (L + 1) * 5](native/75639.c) | producer-formula |
| 1012 | 레조난스・가속 | [q=2: (L + 1) * 5](native/75633.c) | producer-formula |
| 1013 | 레조난스・집중 | [q=2: (L + 1) * 5](native/75636.c) | producer-formula |
| 1014 | 에텔 플레아・연장 | [직접 장착/소비 경로](native/75576.c) | presence-or-direct-consumer |
| 1015 | 블러드 바이트・강화 | [q=4: L * 10](native/75555.c) | producer-formula |
| 1016 | 데몬 크로우・수속 | [직접 장착/소비 경로](native/75573.c) | presence-or-direct-consumer |
| 1017 | 워 크라이・극복 | [직접 장착/소비 경로](native/75657.c) | presence-or-direct-consumer |
| 1018 | 집기공・전력 | [q=2: L * 10](native/75564.c) | producer-formula |
| 1019 | 레이지 소드・강화 | [q=4: L * 10](native/75627.c) | producer-formula |
| 1020 | P 디펜스・저소음 | [q=2: L * 10](native/75624.c) | producer-formula |
| 1021 | 바인드 스트라이크・변화 | [직접 장착/소비 경로](native/75552.c) | presence-or-direct-consumer |
| 1022 | 메테오 스트라이크・단발 | [직접 장착/소비 경로](native/75615.c) | presence-or-direct-consumer |
| 1023 | 패밀리어・전우 | [직접 장착/소비 경로](native/75579.c) | presence-or-direct-consumer |
| 1024 | 쉐도우 워크・환혹 | [직접 장착/소비 경로](native/75642.c) | presence-or-direct-consumer |
| 1025 | 하이네스 힐・확대 | [q=2: L](native/75592.c) | producer-formula |
| 1026 | 힐・비축 | [직접 장착/소비 경로](native/75586.c) | presence-or-direct-consumer |
| 1028 | 플로팅 킥・회피 | [직접 장착/소비 경로](native-extra/19963.c) | presence-or-direct-consumer |
| 1029 | 하이드 어택・시한 | [직접 장착/소비 경로](native-extra/19972.c) | presence-or-direct-consumer |
| 1030 | 풍마 수리검・강화 | [q=2: max(100, (3 - L) * 100)](native-extra/19966.c) | producer-formula |
| 1031 | 화둔술・용염 | [q=2: ceil(f32(2.5 * L))](native-extra/19960.c) | producer-formula |
| 1036 | 프로텍션 이지스 | [직접 장착/소비 경로](native-extra/19975.c) | presence-or-direct-consumer |
| 1037 | 호흡법・절약 | [직접 장착/소비 경로](native-extra/19957.c) | presence-or-direct-consumer |
| 1038 | 풍둔술・발도 | [q=2: L * 5](native/75660.c) | producer-formula |
| 1039 | 크로노스 시프트・집념 | [q=2: (6 - L) * 10](native/75561.c) | producer-formula |
| 1040 | 루나 디재스터・절약 | [직접 장착/소비 경로](native/75606.c) | presence-or-direct-consumer |
| 1041 | 오라 블레이드・검압 | [q=2: L * 10](native/75549.c) | producer-formula |
| 1042 | 술식/폴・유성 | [q=2: L](native/75609.c) | producer-formula |
| 1043 | 아크 세이버・월영 | [직접 장착/소비 경로](native/75540.c) | presence-or-direct-consumer |
| 1044 | 버스터랜스・멀리 던지기 | [q=4: L * 10](native/75558.c) | producer-formula |
| 1045 | 불요불굴・불패 | [q=2: max(3, (4 - L) * 3)](native/75598.c) | producer-formula |
| 1046 | 디코이 슈터・유도 | Buff subclass 없음 | no-buffer-subclass-in-reviewed-native-map |
| 1047 | 루나 디재스터・급습 | [q=2: L](native/75603.c) | producer-formula |
| 1048 | 트윈 버스터 블레이드・정화 | [q=2: L](native/75654.c) | producer-formula |
| 1049 | 파라볼라 카논・식별 | [직접 장착/소비 경로](native/75621.c) | presence-or-direct-consumer |
| 1050 | 문 슬래시・흡마 | [q=2: L](native/75618.c) | producer-formula |
| 1051 | 뇌둔술・방해 | [q=2: (L + -10) * 10](native/75651.c) | producer-formula |
| 1052 | 콘퀘스터・마법 | [직접 장착/소비 경로](native/75570.c) | presence-or-direct-consumer |
| 1053 | 스컬 셰이커・정지 | [q=2: L](native/75645.c) | producer-formula |
| 1054 | 신속의 호수 | [직접 장착/소비 경로](native-extra/19969.c) | presence-or-direct-consumer |

JSON은 함수별 SHA-256·조건/쿨다운/상태 함수 연결과 미확정 범위를 보존한다. 59·68·1046은 검토한 네이티브 매핑에서 Buff subclass가 없으므로 원문만으로 식을 보충하지 않는다. 정적 결과이며 서버 추첨·실제 시간 전이·피격 시뮬레이션 검증은 하지 않았다.
