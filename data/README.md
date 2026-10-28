# 데이터 원문과 가공 근거

sources/에는 게임에서 추출한 원문·네이티브 근거·등록 자료를 보관합니다. 실행용 스킬 정의는 ../web/src/data/, 발행된 아이템·보스 JSON은 ../web/public/game-data/, 스킬 원문 문서는 ../docs/sources/에 있습니다.

sources/game-ui/는 비교·추출용 원본 이미지와 목록이며 배포 리소스가 아닙니다. 실제 화면에서 쓰는 아이콘은 ../web/public/icons/입니다.

가공 도구는 ../tools/extraction/, 수동 갱신은 루트에서 tools/extraction/sync-toram-dev-items.mjs 또는 sync-toram-dev-bosses.mjs를 node로 실행합니다. 이 폴더 자체를 웹에 배포하지 않습니다.

고정된 pipeline 계약·과거 근거 JSON·발행 snapshot의 경로 문자열과 해시는 보존합니다. 그 안의 assets/source-data/ 경로는 검사 도구가 현재 data/sources/로 연결한 뒤 원본 해시를 검증합니다. 폴더 이동을 이유로 게임 수치나 발행 이력을 다시 만들지 않습니다.

sources/toram-items/pipeline/과 sources/toram-monsters/pipeline/은 Git 제외 이력이므로 별도로 백업합니다.
