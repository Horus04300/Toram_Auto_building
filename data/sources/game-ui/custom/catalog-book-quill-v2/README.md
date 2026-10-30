# 도감용 책과 깃펜

- `icon.png`: 현재 메뉴에 사용하는 79×69 RGBA PNG. 투명 배경을 유지한다.
- `master.png`: 내장 image_gen 편집 원본. `icon.png`는 비율 유지 축소와 투명 여백으로 캔버스를 맞췄다.
- `../catalog-book-quill-v1/`의 승인 이미지를 바탕으로 책 테두리·페이지의 대비와 깃펜 크기를 높였다. 게임 추출본이 아닌 AI 재구성 이미지다.
- 생성 지시는 `prompt.txt`에 보존한다. 배포본은 `web/public/icons/ui/menu/catalog.png`, 원본/해시는 `../../menu-icons.json`에 기록한다.

검증: 최종 PNG의 79×69 크기·RGBA·완전 투명/불투명 픽셀과 배포 파일 일치를 확인한다. 실제 공통 메뉴와 홈 최근 메뉴의 PC/모바일 표시를 `verify-inventory-browser.mjs`로 확인한다.
