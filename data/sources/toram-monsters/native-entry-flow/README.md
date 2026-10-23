# 퀘스트 분기 뒤 보스 메뉴 (2026-10-23)

사용자 제보의 콜론 보스/조성중 지구를 보존된 releaseC script_3300.bin과 대조했다. 이벤트10의 시작5695는 ProgressQuest(38), 다음5703은 Check(20), true 분기5719는 BossMenu(130)/field3300/room0이다. 첫 명령만 읽던 추출 범위가 누락 원인이다. UUID41/master10의 3300:10만 이 메뉴에 연결하며 다른 맵의 같은 UUID에 복사하지 않는다.

이미 보존한 snapshot SHA49cce5c641aa2077c0395f24640f87ec9925d8919bbfb137638d65b7c6e8eb0d 및 metadata SHA c5cb57c13fb2f4ba9258b8cf155ee866a8f67eee30f32d043e1fd854bba2eec9로 Ghidra 선택 함수를 분석했다. 게임을 실행하거나 프로세스에 새로 접근하지 않았다. command-enum.json은 metadata의 정확한 opcode를 보존한다.

OnProgressQuestCommand는 byte+byte 뒤 ReadInt(first&1)를 읽고 work 값0에 조건 결과를 기록한다. OnCheckCommand는 byte+byte 뒤 ReadInt(flags>>7)를 읽고, 조건에 따라 두 int32 절대 오프셋 중 하나를 loader.Position(+0x2c)에 쓴다. ReadInt(val=0)는 정확히4바이트를 읽는다. 추출기는 scriptVersion16의 이 두 opcode와 직접 BossMenu만 따라간다. 동적 ReadInt 형식, 미검토 opcode는 그 경로에서 멈춘다. Check의 두 분기 모두 가능한 출처 경로로 탐색하며 현재 퀘스트 상태나 입장 해금 여부는 판단하지 않는다. offset 범위·중복 방문·잘린 입력을 검사하고 payload 임의 검색은 하지 않는다.

이는 저장 코드/데이터의 정적 연결 근거이며 게임에서 실제 입장/전투를 실행한 관측이 아니다. TraceColonMenu.java와 method-map.json으로 같은 보존 이미지에 재현한다.
