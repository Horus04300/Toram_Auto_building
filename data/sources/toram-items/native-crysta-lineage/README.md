# 크리스타 ID 결합 근거 (2026-10-22)

이미 보존한 GameAssembly 모듈/metadata만 읽어 Ghidra 12.1.4로 선택13함수를 분석했다. 게임 실행/프로세스 추가 접근 없이 기존 snapshot SHA49cce5c641aa2077c0395f24640f87ec9925d8919bbfb137638d65b7c6e8eb0d를 사용했다.

UIEquipCristaPanel.GetPowerUpCristaOrderList는 ItemData.master(+0x28)의 Model(+0x48)을 다음 조회 ID로 사용해 사슬을 추적한다. ItemDBData.get_Model의 token/pointer와 getter +0x48, 기존 CreateItemData의 마지막 model:i32 로더를 함께 대조했다. type61~65에서만 model을 previousId로 해석한다. 일반 장비 model이나 type36 placeholder에는 적용하지 않는다. 변환기는 모든 부모의 존재/동일 카테고리와 cycle을 검증한다. 댄드라이언9776→9900(슈퍼 데스 버섯)이 한 예다. 이름은 연결 키가 아니다.

crysta-legacy-aliases.json은 이전425개 화면/저장 이름을 ID에 연결한 검토 목록이다. 기존 단일 이름/정규화 후보와 category, 원본 옵션/계보를 대조하고 오탈자/로마자/번역 명칭을 명시적 alias로 보존했다. 별도 검토한 미노타우르스→미노타우로스9804도 포함한다. 런타임에 유사 이름이나 스탯 fingerprint로 신원을 추측하지 않는다. 기존 수치는 별도 fixture로 보존하며 새 수치를 덮어쓰는 보정에 쓰지 않는다.

project-stat-mapping.json의 추가 cap 연결은 기존 BonusType ID·enum·옵션 원문의 환산값을 사용한다.48 bRespawn→REVIVE_TIME,155 bDamageReflection→REFLECT는 기존 보존 키다.168 bVitToAtk→ATK_UP_VIT/174 bAgiToMAtk→MATK_UP_AGI는 기존 비례 계산 필드에 percent를 전달한다.127/129/130/137/140/164/165는 서로 다른 효과를 새 notModeled 키로 보존한다. 특히164/165의 넘어짐/기절 부여정지를 속성각성/마력속성으로 해석하지 않는다. 불명 효과의 전투식을 새로 만들지 않는다.

정적 함수 해석과 ID/데이터 연결을 확인한 결과이며 실제 강화 실행·전투 사건·전투식 전체 검증을 뜻하지 않는다. 전체 원본·거부 항목은 source pipeline 이력에 유지한다.
