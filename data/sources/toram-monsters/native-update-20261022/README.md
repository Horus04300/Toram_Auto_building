# 2026-10-22 보스 네이티브 갱신 검토

최신 설치의 읽기 전용 모듈 캡처와 메타데이터를 이전 보존본과 대조했다. 보스 원본 파서·분류·정적 대상 계산에서 기존 추출 계약을 바꿔야 하는 신규 의미 변경은 발견하지 않았다. 게임 전투 결과를 관측한 검증은 아니다.

## 근거와 범위

- 부모 작업의 `ghidra-review-5.log` 마지막 `Save succeeded` 이후 결과를 사용했다. 함수 221개(Assembly-CSharp 및 Toram.Common 난이도 함수 10개)를 `index.json`의 이전 경로·메타데이터 인덱스·새 runtime VA·이전/새 SHA-256으로 연결했다. `functions/`는 최종 새 C의 원본 바이트다. REA retained Evidence ID는 없으며 scoped Ghidra 12.1.4 결과다.
- 새 mapped image SHA-256: `33fa1bc4a533cba3f99f0d711fb14ca6e9a2bee06b834484c98af2d2336767b1`. 새 PE snapshot SHA-256: `49cce5c641aa2077c0395f24640f87ec9925d8919bbfb137638d65b7c6e8eb0d`.
- 주소 정규화 후 137개 본문이 같았다. 나머지 84개는 원본 C와 `diffs/`를 함께 검토했다. 주소 정규화는 분기·필드 오프셋·연산 순서 비교를 돕는 도구이며, 간접 호출이나 전역 데이터 의미의 자동 증명이 아니다.

## 검토 결과

| 계약 | 관찰 |
| --- | --- |
| 몬스터 원본 | `MobMaster.ReadMaster`, `MobStatusMaster.CreateStatusMaster`, `MobActionPattern.CreateActionPattern`, `MobModeData.CreateModeData`, `MobPropertyMaster`의 읽기 순서·가변 반복·필드 오프셋이 유지된다. 마스터 getter와 multiFlag 판정도 유지된다. GC write-barrier, 공유된 빈 메서드와 객체 생성 표현, 지역 변수 복구 차이를 데이터 형식 변경으로 세지 않았다. |
| 필드·분류 | FieldScript byte/int/short/event-index reader, MMO/MO 구분, PopPoint 경로가 유지된다. BossMenu·ScriptThread와 HighRaid 표 로더의 명령 읽기·필드/방/개체 연결·난이도 선택 구조에서 신규 분기를 발견하지 않았다. 자동 분류가 미연결 경로를 새로 확정한다는 뜻은 아니다. |
| 일반 타겟 | 난이도 clamp -1..3, 미파괴 부위 합산, DEF/MDEF·내성·크리티컬 속성 접근이 유지된다. `difficulty-tables.json`은 `.cctor`의 FieldInfo metadata usage를 `field_refs` → 정확 선언 타입/필드 → `default_data`로 연결한 배열 10개×5원소의 이전/새 원본 20바이트와 위치를 담는다. 전부 동일하다. HP 배율 0.1/1/2/5/10, 스탯 배율 0.1/1/2/4/6, 레벨 가산 -10/0/10/20/40도 유지된다. |
| HighRaid | property32 고정 비트, float32 나눗셈/곱셈 후 절삭, HP 연산 순서, 레벨 기반 내성 식이 유지된다. 현재 선택 레벨·서버 상한 구분을 유지한다. |
| 길드 | `max(40, gauge*4)` 레벨, 정수 raw×level 후 float32 0.01배 DEF/MDEF, level/10 내성, property40 보정 및 서버 randomProperty 연결 순서가 유지된다. HP는 `Math.Round(double, 2, MidpointRounding=0)` 선언을 복구한 최종 출력에서 이전과 동일하며, 초기 무인자 호출 디컴파일을 의미 변경으로 판단하지 않았다. |

`constants.json`은 HighRaid/길드 근거의 수치 상수 15건을 새 mapped image에서 직접 읽고 새 C 참조와 연결한다. 전부 이전 원본 바이트와 같다. `-0.04f`와 `50.0(double)`은 다른 상수처럼 일괄 주소 이동하지 않아 개별 새 참조 주소로 확인했다.

## 한계와 기존 주의점

- 이 검토는 선택 함수와 해당 데이터 계약의 정적 비교다. 모든 엔진·제네릭 간접 호출·게임플레이 동작의 동등성을 증명하지 않는다. 서버 입장 상한·랜덤 보정·활성 부위·전투 상태는 확보하지 않았다.
- shared getter/빈 메서드는 여러 메타데이터 선언이 같은 네이티브 주소를 공유한다. 함수 이름이나 잘못 유추된 pointer/enum prototype만으로 동작 변경을 주장하지 않는다.
- HighRaid의 물리 내성 getter가 부위 `MobPropertyCut.get_CutMagicAttack`을 부르는 것은 이전과 새 출력 모두에서 확인되는 기존 동작이다. 미래 HighRaid 부위 연결 때 일반 보스의 물리 BodyCut 규칙을 무조건 확장하면 안 된다. 이번 갱신의 새 의미 변경은 아니다.
- 파이프라인 계약·latest·개발판 데이터는 이 검토에서 변경하지 않았다. 후보/실제 발행 검증과 계약 승인은 부모 작업이 별도로 수행한다.

재현 스크립트 `compare-boss-native.py`, `check-boss-constants.py`, `check-boss-difficulty.py`는 저장소 루트에서 실행하며 `build/tmp/update-pipeline-20261022/`의 보존된 최종 입력을 사용한다. 메타데이터/모듈 원본의 전체 해시를 검사하며 게임 프로세스에 접근하지 않는다.
