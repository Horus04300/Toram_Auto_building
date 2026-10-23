# Coryn 몬스터 API 교차 대조

확인: 2026-10-18. [공식 API 문서](https://coryn.club/api/)와 공개 GET 응답을 확인했다. `GET /api/v1/monsters.php`는 `id`, `name`, `map_id` 조회를 제공하며, 기본 limit 20·최대 100이다. 이름 검색은 배열, ID 조회는 객체다. 아래는 참고 후보이며 실제 게임 ID 결합을 확정하지 않는다.

| 게임 Enemy 텍스트 ID | 한국어 / 영어 이름 | Coryn ID | API level / mode | API 분류·위치 |
| --- | --- | --- | --- | --- |
| 1001 | 알타달 / Altadar | [3106](https://coryn.club/api/v1/monsters.php?id=3106) | 290 / Normal | B / Boss, map 404 High Difficulty Boss Battle Event Venue |
| 1187 | 메르제하르 / Merzehal | [3514](https://coryn.club/api/v1/monsters.php?id=3514) | 325 / ??? | B / Boss, map 404 High Difficulty Boss Battle Event Venue |
| 540 | 기드론 / Grimuckus | [1742](https://coryn.club/api/v1/monsters.php?id=1742) | 195 / Normal | M / Mini Boss, map 300 Wazeero Street |
| 974 | 폴버로스 / Falburrows | [3059–3063](https://coryn.club/api/v1/monsters.php?name=Falburrows) | 205, 215, 225, 235, 255 / Easy, Normal, Hard, Nightmare, Ultimate | B / Boss, map 539 Saltau's Beach (Night), limited true |
| 974 후보 | Falburrows (High Difficulty) | [3068–3072](https://coryn.club/api/v1/monsters.php?name=Falburrows) | 245, 255, 265, 275, 295 / Easy, Normal, Hard, Nightmare, Ultimate | B / Boss, map 539, limited true |
| 888 | 기룡 미뮤가 / Trickster Dragon Mimyugon | [2795–2799](https://coryn.club/api/v1/monsters.php?name=Trickster%20Dragon%20Mimyugon) | 228, 238, 248, 258, 278 / Easy, Normal, Hard, Nightmare, Ultimate | B / Boss, map 494 Operation Zone: Cockpit Area |

## 제공 필드와 한계

다섯 이름 검색 5건과 반환된 18개 ID 상세 조회를 모두 검사했다. 공통 필드는 `id`, `name`, `level`, `map_id`, `map_name`, `type_code`, `type_label`, `mode`, `hp`, `exp`, `element_id`, `element_label`, `tameable`, `limited`, `meta.badge`, `meta.note`이며 상세 조회는 `drops`를 더한다. `drops`의 ID도 Coryn 아이템 ID다.

- 이 18개 상세 응답에는 DEF·MDEF·물리/마법 내성·크리티컬 내성·회피·관성 수치와 공식 게임 ID 필드가 없다. API 문서에도 이 필드들은 명시되지 않았다. 다른 미조사 응답까지 부재를 증명하는 것은 아니다.
- `id`·`map_id`·`element_id`는 사이트 계약의 ID다. 게임 `Enemy` 텍스트 ID, `MobMaster` ID, 게임 필드/속성 enum으로 복사하지 않는다. 위 표의 좌우 ID는 이름으로 교차 대조한 후보 연결이다.
- `type_code=B/M`은 사이트의 Boss/Mini Boss 구분이다. 고난이도는 별도 정규화 필드가 없고 위치·이름에 표현된다. 이름의 High Difficulty 또는 `limited`만으로 게임 내부 분류를 확정하지 않는다.
- Altadar·Grimuckus의 `hp=-1`, Merzehal의 `hp=0` 및 `mode=???`를 유효 전투 수치나 Normal 난이도로 대체하지 않는다. 원형을 보존하고 계산 입력에서는 미확인으로 처리한다.
- 한 이름이 난이도·이벤트 버전별 여러 사이트 ID를 가진다. 이름만으로 중복 제거하거나 실제 게임 객체 하나에 모두 합치지 않는다.

## 재현 자료

원시 JSON과 각 요청 URL·수집 시각·SHA-256은 `build/tmp/toram-monster-extraction/coryn/requests.json` 및 같은 디렉터리에 보존했다. 수집 코드는 scratch `fetch-coryn-samples.mjs`이며 기존 아이템 수집기와 같은 Node `fetch`를 사용했다. Python urllib는 HTTP 403으로 실패했고, Node 공개 GET은 HTTP 200이었다. 사이트 API는 별도 출처로 표시하는 보조 목록/교차 검증에만 사용한다.
