import { readFile, writeFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const trees = {
  Guard:'가드', Golem:'골렘', Knight:'기사', Dagger:'나이프', Necromancer:'네크로맨서', Ninja:'닌자', DarkPower:'다크파워', Dancer:'댄서', DualSword:'듀얼소드', Martial:'마셜', Magic:'매직', MagicBlade:'매직블레이드', Mononofu:'무사', Minstrel:'민스트럴', Battle:'배틀', Barehand:'베어핸드', Blade:'블레이드', Survival:'서바이벌', Support:'서포터', Shot:'슛', Sprite:'스프라이트', Shield:'실드', Assassin:'어새신', Wizard:'위저드', Crusher:'크러셔', Partisan:'파르티잔', Priest:'프리스트', Halberd:'할버드', Hunter:'헌터'
};
const metadata = {};
for (const [treeId, fileName] of Object.entries(trees)) {
  const source = await readFile(resolve(root, '스킬', `${fileName}.js`), 'utf8');
  const pattern = /\{\s*"id":\s*(\d+),[\s\S]*?"type":\s*"([^"]+)",[\s\S]*?"damagetype":\s*"([^"]+)"/g;
  const matches = [...source.matchAll(pattern)];
  if (!matches.length) throw new Error(`No skill metadata parsed: ${treeId}`);
  for (const match of matches) {
    const id = Number(match[1]);
    const key = `${treeId}:${id}`;
    if (metadata[key]) throw new Error(`Duplicate skill metadata: ${key}`);
    metadata[key] = { type: match[2], damageType: match[3] };
  }
}
if (Object.keys(metadata).length !== 427) throw new Error(`Expected 427 skills, parsed ${Object.keys(metadata).length}`);
const output = `/* 동료 견본에서 추출한 스킬 분류 메타데이터. 계산식은 링크 원문 검증 모듈에서 별도로 추가한다. */\n(function () {\n  'use strict';\n  window.TORAM_SKILL_REGISTRATION_METADATA = Object.freeze(${JSON.stringify(metadata, null, 2)});\n}());\n`;
await writeFile(resolve(root, 'assets/js/data/skill-registration-metadata.js'), output, 'utf8');
console.log(`Generated metadata for ${Object.keys(metadata).length} skills.`);