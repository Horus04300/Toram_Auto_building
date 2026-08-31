import assert from 'node:assert/strict';
import { access, readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const dataSource = await readFile(resolve(root, 'assets/js/data/skill-tree-data.js'), 'utf8');
const treeSource = await readFile(resolve(root, 'assets/js/skill-tree.js'), 'utf8');
const paths = [...dataSource.matchAll(/"icon"\s*:\s*"([^"]+)"/g)].map(match => match[1]);

assert.ok(paths.length > 0, '스킬 아이콘 경로가 있어야 합니다.');
assert.ok(paths.every(path => !path.includes(' ')), '설치본에서 실패하는 공백 포함 아이콘 경로가 없어야 합니다.');
assert.doesNotMatch(treeSource, /(?:Weapon|Buff|Assist|Other) Skills/, '스킬 UI가 공백 포함 디렉터리를 참조하면 안 됩니다.');
for (const path of paths) await access(resolve(root, path));

console.log(`Skill icon asset paths: PASS (${paths.length} icons, no spaces)`);
