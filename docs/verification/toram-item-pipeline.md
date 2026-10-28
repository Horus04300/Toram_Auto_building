# 게임 아이템 업데이트 파이프라인

2026-10-22. 수동 실행 명령 하나로 변경 확인 → 추출 → 검증/변환 → 개발판 데이터 적용까지 처리한다. 게임 실행·프로세스 읽기·설치 파일 변경은 하지 않는다. 검토한 출처 계약은 `tools/extraction/toram-item-pipeline-contract.json`이며 기존 파서·조건/표시/분류 함수를 재사용한다.

## 실행

저장소 루트에서 다음 명령을 실행한다. Node는 프로젝트의 기존 실행 환경을 사용한다. 현재 PC에서는 번들 Python을 자동으로 찾고, 다른 환경은 `TORAM_ITEM_PYTHON`으로 Python 실행 파일을 지정하거나 PATH의 python을 사용한다. Python 3.12 이상·UnityPy 1.25.4가 필요하다.

```powershell
node tools/extraction/sync-toram-dev-items.mjs
node tools/extraction/sync-toram-dev-items.mjs --check
```

이 명령은 `update-toram-items.py`가 ready/unchanged로 끝났을 때만 검증된 `snapshot/project`를 `web/public/game-data/items/`에 적용한다. 재검토/실패 상태면 이전 개발판 manifest를 유지한다. 변환과 적용 사이에도 동시 sync 잠금을 유지한다. `items:publish`는 이미 검증된 latest의 개발판 재적용만 수행한다. 주기 실행이나 백그라운드 작업은 사용자 선택에 따라 설정하지 않았다.

단계별 확인이 필요한 경우 현재 Python으로 직접 실행할 수 있다. Python 단독 실행은 원본/가공 스냅샷까지만 만들며 개발판 교체는 위 sync 명령이 담당한다.

```powershell
$toramPython = "$env:USERPROFILE/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe"
& $toramPython tools/extraction/update-toram-items.py --check
& $toramPython tools/extraction/update-toram-items.py
```

`--check`는 manifest의 선택 리소스 revision과 현재 설치 파일의 hash를 비교한다. 일반 실행은 변경이 있으면 원본 번들·복호문·가공본·차이를 새 스냅샷으로 남긴다. 동일 revision·분석 계약·설치 파일·도구 코드이면 번들을 다시 받지 않고 `unchanged`로 종료한다. 첫 실행의 비교 기준은 기존 11,723개 통합 카탈로그이고, 이후에는 마지막 `ready` 스냅샷이다.

다른 Python 환경에서는 먼저 `python -m pip install -r tools/extraction/requirements-toram-items.txt`로 동일 버전을 설치한다. 현재 저장된 UnityPy 경로를 기본으로 사용하며, 다른 경로는 `--unitypy-path`로 지정할 수 있다. 게임 설치 경로를 바꿨다면 `--install`을 전달한다.

보존 파일만 사용하는 재현도 지원한다.

```powershell
& $toramPython tools/extraction/update-toram-items.py --offline build/tmp/toram-item-extraction/game/downloads/localizations --store build/tmp/별도검증저장소
& $toramPython tools/extraction/update-toram-items.py --offline '이전스냅샷/source' --store build/tmp/별도검증저장소
& $toramPython tools/extraction/update-toram-items.py --self-test
node tools/extraction/sync-toram-dev-items.mjs --offline build/tmp/toram-item-extraction/game/downloads/localizations
```

기존 다운로드 디렉터리에서는 선택한 release 하위 파일을 우선한다. 같은 이름의 다른 release 번들을 섞지 않는다. 기본 releaseC는 2026-10-22 블랑/할로윈 신규 데이터를 확인한 공개 분기다. releaseB는 이전 본문을 계속 제공했다. 실제 활성 서버 자동 판별이나 revision 숫자 정렬은 하지 않는다. 다른 분기/과거 재현은 `--application releaseB` 등으로 명시한다. 각 분기의 이력과 포인터는 분리된다.

## 저장과 결과

기본 저장소는 `data/sources/toram-items/pipeline/releaseC/`다. 로컬 원본·대형 이력은 Git과 AI 기본 검색에서 제외한다. **이 폴더는 별도로 백업한다.** 다른 영구 경로를 원하면 `--store`를 사용한다. 기존 스냅샷을 지우거나 덮어쓰는 정리 작업은 하지 않는다.

```text
releaseC/
  latest.json                      마지막 ready 스냅샷의 상대 경로·report hash
  observed.json                    마지막 완료 관측(검토 필요도 포함)
  snapshots/<master-cache-key>-<run-id>/
    source/manifest.bytes          공개 manifest 원본
    source/*.unity3d               선택 번들 원본 7개(현재)
    source/decoded/*.bin           대상 TextAsset 복호문
    items.raw.json                 원본 필드·10슬롯·다국어 이름/설명/템플릿
    items.connected.json           검증 통과 시의 표시/조건/분류/관계
    auxiliary.raw.json             최신 보조 표의 전체 원본 레코드
    auxiliary.connected.json       검증 통과 시의 비아이템 레시피 namespace·랜덤 옵션 이름
    project/                       종류별/언어별 앱 가공본·hash manifest
    delta.json                     추가 ID·삭제 ID·필드별 before/after
    added-items.json               새 게임 ID의 전체 아이템 데이터만
    report.json                    검증 상태·출처 URL/revision/hash·출력 hash
    failure.json                   도중 실패 시 이유(완료 report 대신)
```

`delta.json.optionTemplateChanges`는 언어·signed property ID별 템플릿 변경 전후를 기록한다. `resourceChanges`는 레시피·System·Skill 등 각 대상 표의 복호문 hash 변화를 기록한다. 아이템 비교에서는 파일 offset·레코드 hex·배열 순서를 제외해, 앞에 레코드가 삽입돼도 전 항목이 수정으로 오인되지 않는다. 삭제 ID는 이력에 기록하며 기존 파일이나 앱 데이터를 삭제하지 않는다.

소비자는 `latest.json.snapshot`을 읽고 해당 스냅샷의 `items.connected.json` 또는 `added-items.json`을 선택한다. 마지막으로 만들어진 폴더를 골라 사용하면 실패/검토 후보를 읽을 수 있으므로 포인터를 사용한다. `reportSha256`과 `report.outputHashes`로 무결성을 확인할 수 있다. 파이프라인도 다음 실행 전에 보존된 report와 파일 hash를 다시 확인한다.

실제 앱은 전체 추출본을 읽지 않고 `web/public/game-data/items/manifest.json`과 필요한 파일만 읽는다. [가공 계약](../architecture/item-data-format.md)을 참고한다. 개발판에서 `await window.ToramApp.items.getItem(9911, 'kr')`로 ID별 데이터를 사용할 수 있다. 새 페이지는 최신 manifest를 읽고, 열린 페이지는 `await window.ToramApp.items.refresh()` 후 다시 조회한다. 크리스타는 ID 기반 공통 카탈로그와 명시적 이전 이름 alias를 사용한다. 계보·저장·잠금 계약은 같은 가공 계약을 따른다.

장비 탭의 `게임 아이템에서 장비 옵션 불러오기`에서 주무기·보조·몸/추가/특수 장비를 ID로 선택해 기존 계산·저장에 사용할 수 있다. 갱신 뒤 화면을 새로 열면 새 항목도 목록에 나타난다. 전체 옵션 매핑을 통과한 장비만 적용한다. 보조의 일반 옵션은 native 분기에 따라 방패/단검/화살/두루마리만 합산하고 나머지 보조 무기의 일반 옵션은 제외한다. 기존 기본 ATK·안정률·제련·커스텀 입력은 유지한다. 속성·비례·크리스타 계보 검증은 가공 계약의 Gate를 따른다.

버프 탭의 `버프 소모품 선택`도 같은 가공본과 갱신 명령을 사용한다. 사용 가능한 type 2/50에서 단순 고정 스탯 스크립트만 연결하고 현재 209개를 지원한다. 지속시간 cap ID로 계열을 구분해 같은 계열은 교체하며, 수동 externalOptions는 유지·합산한다. ID·정의·지속시간·그룹을 빌드에 고정한다. 시간 경과·사용 사건·자동 만료는 실행하지 않는다. [native 코드와 실제 레코드 근거](../../data/sources/toram-items/item-use-rules.md), [저장/계산 계약](../architecture/item-data-format.md)을 참고한다.

기존 커스텀 옵션은 유지한다. 제작 장비는 원본 선택 없이 수동 옵션만 계산·저장하며, 원본 선택 시에는 원본과 수동 보정을 합산한다. 선택한 ID·버전·옵션 정의는 빌드에 고정해 업데이트가 저장 빌드의 값을 자동 변경하지 않는다. 원본 장비를 다시 적용해야 최신 정의를 사용한다. ATK·안정률·제련은 실제 장비의 입력값을 보존한다.

이번 출력의 계약 이름은 **toram-item-pipeline-v1**이다. 과거 `items.77596232.connected.json`과 자동으로 호환되는 앱 저장 계약은 아니다. 공통 경로는 `items[].gameItemId`, `names/descriptions`, 원본 `master`, `propertyRecord.caps`, `conditionGroups`, `display`, `references`다. 이번 가공본은 기본 슬롯을 `defaultSelectedEquipSlotValue`로, 숫자/특수 문구 후보를 `display.plainTextCandidates[locale]`로 제공한다. 원본 cap 값과 표시 환산값은 분리된다. 미해석 flag/type/모델 의미를 새로 확정하지 않는다.

## 검증과 실패 처리

1. 공개 manifest 전체 길이·EOF·그룹/행 경계·기존 6언어 존재를 확인한다. 번들마다 자신의 revision을 사용하므로 master cache key만으로 모든 언어의 버전을 가정하지 않는다.
2. 원본을 먼저 보존하고 master 37바이트·property 44바이트·10슬롯·signed ID·UTF-8·고유 ID·고아 property·각 표 EOF를 검사한다. 보조 표 5개는 독립 재인코딩으로 원문과 비교한다.
3. 검토한 GameAssembly.dll·메타데이터 hash, 고정한 근거 JSON hash, UnityPy 버전을 확인한다. 설치 코드 변경이면 원본 추출/차이만 남기고 가공본 확정을 중단한다.
   `itemUseRules`와 그 핵심 native 함수 파일의 hash도 변환/발행 단계에서 확인한다. 가공본의 `itemUseRulesSha256`이 현재 규칙과 다르면 재생성을 요구한다. 고정 원본과 가공 JSON은 Git 줄바꿈 변환을 막아 Windows checkout에서도 hash를 유지한다.
4. 조건 그룹의 잘림/중첩/겹침과 UI/실행 범위 불일치, 알 수 없는 cap/문구 형식/속성/아바타 참조, 레시피 namespace/재료 연결 오류도 검토 대상으로 남긴다. 최신 표로 관계를 새로 만들며 과거 레시피/모델 연결을 복사하지 않는다.
5. 다운로드 전후 선택 revision과 설치 파일 hash가 같아야 완료한다. 실행 잠금으로 동시 갱신을 막고 `latest.json`은 검증이 모두 끝난 뒤 임시 파일 교체로 갱신한다.

종료 코드: `0`은 ready/unchanged 또는 정상 check, `2`는 needs-review, `1`은 다운로드·파싱·무결성·실행 실패다. `needs-review`와 실패 모두 기존 latest를 유지한다. 원본 구조 자체가 바뀌어 파싱할 수 없으면 source와 failure를 남긴다. 실행이 강제로 종료되어 `.pipeline.lock`이 남으면 다른 파이프라인 실행이 없는지 확인한 뒤 그 **잠금 파일 하나만** 제거하고 재시도한다.

게임 코드가 바뀌었을 때는 새 로더·배율·조건·스킬/분류 경로를 확인한 후 관련 추출기/근거 JSON/출처 계약을 함께 갱신한다. **새 파일 hash만 계약에 넣어 검토를 생략하지 않는다.** 이후 같은 원본으로 다시 실행해 ready 결과를 만든다. 설치 파일 hash가 같더라도 미래 서버 리소스와 로컬 코드의 의미가 항상 같다는 보증은 없으므로, 새 형식·참조를 위 검증으로 중단시키고 원문을 유지한다.

최종 게임 UI의 숫자 지역 서식·색상·줄바꿈, 드롭 표의 미해석 필드, 모델 호출자의 변환, 보유 장비 인스턴스, 강화/전투 계산식은 기존 조사 경계 그대로다. 수동 명령에서 개발판 데이터까지 적용하고 화면 선택·계산·저장으로 연결한다. 자동 주기 실행·알림·공개 릴리스 배포는 하지 않는다.

## 검사와 근거

- npm test: 실제 ID·원문 옵션/조건·장비/보조/소모품·카탈로그·계보·저장 왕복.
- Python 추출기의 --self-test: 원본/차이·중도 갱신·검토 필요·변환/발행 실패 격리. wrapper 종료 코드는 test-toram-item-pipeline.py에서 검사한다.
- npm test -- browser와 verify-catalog-browser.mjs: 소스/하위 경로·장비/타겟 선택·JSON/재열기·읽기 전용 도감.

설치 코드/상수/formatter 검토 근거는 data/sources/toram-items/native-update-20261022/에 있다. reviewed_inputs는 파일 해시를 검사한다. 실행 로그와 수집 snapshot은 원본 pipeline에 보관하며 현재 발행 건수는 handoff와 manifest를 따른다. 실제 미래 게임 코드/서버 활성 분기/공개 배포를 미리 검증한 것으로 보지 않는다.
