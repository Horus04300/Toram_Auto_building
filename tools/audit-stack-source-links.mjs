import { createHash } from 'node:crypto';
import { existsSync } from 'node:fs';
import { readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const fail = [];
const assert = (condition, message) => { if (!condition) fail.push(message); };
const context = { window: {}, console };
context.window.window = context.window;
vm.createContext(context);
async function load(relativePath) {
  const path = resolve(root, relativePath);
  assert(existsSync(path), `로드 파일 누락: ${relativePath}`);
  if (existsSync(path)) vm.runInContext(await readFile(path, 'utf8'), context, { filename: relativePath });
}

for (const path of [
  'assets/js/data/skill-tree-data.js',
  'assets/js/data/skill-combat-catalog.js',
  'assets/js/data/skill-effect-registry.js',
  'assets/js/data/skill-effect-data.js',
  'assets/js/data/skills/battle.js',
  'assets/js/data/skills/survival.js',
  'assets/js/data/skills/guard.js',
  'assets/js/data/skills/support.js',
  'assets/js/data/skills/dark-power.js',
  'assets/js/data/skills/dancer.js',
  'assets/js/data/skills/minstrel.js',
  'assets/js/data/skills/blade.js',
  'assets/js/data/skills/dual-sword.js',
  'assets/js/data/skills/halberd.js',
  'assets/js/data/skills/crusher.js',
  'assets/js/data/skills/mononofu.js',
  'assets/js/data/skills/knight.js',
  'assets/js/data/skills/martial.js',
  'assets/js/data/skills/shot.js',
  'assets/js/data/skills/sprite.js',
  'assets/js/data/skills/assassin.js',
  'assets/js/data/skill-registration-metadata.js',
  'assets/js/data/skill-catalog-registration.js'
]) await load(path);

const manifest = JSON.parse(await readFile(resolve(root, 'docs/sources/skills/manifest.json'), 'utf8'));
for (const entry of manifest) {
  const path = resolve(root, entry.file);
  assert(existsSync(path), `원문 캐시 누락: ${entry.file}`);
  if (existsSync(path)) {
    const text = await readFile(path, 'utf8');
    const digest = createHash('sha256').update(text).digest('hex');
    assert(digest === entry.sha256, `원문 캐시 해시 불일치: ${entry.file}`);
  }
}

const rootSkills = context.window.TORAM_SKILL_EFFECT_DATA && context.window.TORAM_SKILL_EFFECT_DATA.skills || [];
const skills = rootSkills.concat(context.window.ToramSkillEffectRegistry.all());
const catalogSkills = context.window.TORAM_SKILL_COMBAT_CATALOG && context.window.TORAM_SKILL_COMBAT_CATALOG.skills || [];
const args = process.argv.slice(2);
const treeIndex = args.indexOf('--tree');
const selectedTreeId = treeIndex >= 0 ? args[treeIndex + 1] : null;
if (treeIndex >= 0 && !selectedTreeId) fail.push('--tree 뒤에 스킬트리 ID가 필요합니다.');
const requireS1 = args.includes('--require-s1');
const definitionsById = new Map();
for (const skill of skills) {
  const definitions = definitionsById.get(skill.id) || [];
  definitions.push(skill);
  definitionsById.set(skill.id, definitions);
}
const selectedCatalogSkills = catalogSkills.filter((skill) => !selectedTreeId || skill.treeId === selectedTreeId);
if (selectedTreeId && !selectedCatalogSkills.length) fail.push(`알 수 없는 스킬트리 ID: ${selectedTreeId}`);
const sourceCoverage = selectedCatalogSkills.map((catalogSkill) => {
  const definitions = definitionsById.get(catalogSkill.id) || [];
  const sourced = definitions.find((definition) => definition.sourceRef);
  return { catalogSkill, definitions, sourced, status:sourced ? 'S1' : (definitions.length ? 'missing-sourceRef' : 'S0') };
});
const uncoveredSkills = sourceCoverage.filter((item) => item.status !== 'S1');
if (requireS1 && uncoveredSkills.length) fail.push(`S1 출처 연결 미완료: ${uncoveredSkills.length}개 (${uncoveredSkills.map((item) => item.catalogSkill.id).join(', ')})`);
const referencedSkills = skills.filter((skill) => skill.sourceRef);
for (const skill of referencedSkills) {
  const ref = skill.sourceRef;
  assert(ref && ref.file && ref.anchor, `${skill.id}: sourceRef가 필요합니다.`);
  if (ref && ref.file && ref.anchor) {
    const path = resolve(root, ref.file);
    assert(existsSync(path), `${skill.id}: 원문 파일이 없습니다 (${ref.file}).`);
    if (existsSync(path)) assert((await readFile(path, 'utf8')).includes(ref.anchor), `${skill.id}: 원문의 근거 문구를 찾지 못했습니다.`);
  }
}
const stackSkills = skills.filter((skill) => skill.stackControl || skill.stackModel);
const requiredStackIds = [
  'Assassin:8', 'Blade:8', 'Dancer:0', 'Dancer:1', 'Dancer:2', 'Dancer:3', 'Dancer:4',
  'DarkPower:6', 'DualSword:16', 'Halberd:19', 'Knight:3', 'Martial:11', 'Minstrel:4',
  'Minstrel:5', 'Shot:9', 'Sprite:9'
];
for (const id of requiredStackIds) assert(stackSkills.some((skill) => skill.id === id), `기존 스택 정의 누락: ${id}`);

function literal(expr) { return expr && expr.op === 'value' ? expr.value : undefined; }
const fixedCaps = new Map([
  ['DarkPower:6', 15], ['Blade:8', 11],
  ['Dancer:0', 10], ['Dancer:1', 10], ['Dancer:2', 10], ['Dancer:3', 10], ['Dancer:4', 10],
  ['Minstrel:4', 50], ['Minstrel:5', 9], ['Halberd:19', 3], ['Knight:3', 5], ['Martial:11', 40], ['Sprite:9', 5]
]);
for (const [id, expected] of fixedCaps) {
  const skill = stackSkills.find((item) => item.id === id);
  assert(skill, `${id}: 스택 정의가 없습니다.`);
  if (skill) assert(literal(skill.stackControl.maxStacks) === expected, `${id}: 최대 스택이 ${expected}가 아닙니다.`);
}
const regret = stackSkills.find((skill) => skill.id === 'DarkPower:6');
if (regret) {
  const effects = JSON.stringify(regret.effects);
  assert(effects.includes('"op":"min"') && effects.includes('"value":10'), 'DarkPower:6: 이로운 효과의 10스택 상한이 없습니다.');
  assert(effects.includes('"key":"MAXHP_P"') && effects.includes('"path":"buff.stacks"'), 'DarkPower:6: 최대 HP 감소가 무제한 스택을 사용하지 않습니다.');
}
const eternal = skills.find((skill) => skill.id === 'DarkPower:7');
assert(eternal && !eternal.stackControl && !eternal.stackModel, 'DarkPower:7 이터널 나이트메어는 스택형으로 등록하면 안 됩니다.');
const saber = stackSkills.find((skill) => skill.id === 'DualSword:16');
assert(saber && saber.stackModel && saber.stackModel.hardCap === null && !saber.stackControl, 'DualSword:16 세이버 오라는 고정 최대 스택 UI를 가지면 안 됩니다.');

if (fail.length) {
  console.error('스킬 원문 대조 실패:');
  for (const message of fail) console.error(`- ${message}`);
  process.exitCode = 1;
} else {
  const label = selectedTreeId ? ` (${selectedTreeId})` : '';
  const covered = sourceCoverage.length - uncoveredSkills.length;
  console.log(`원문 연결 무결성 통과${label}: 캐시 ${manifest.length}개, 출처 연결 정의 ${referencedSkills.length}개, 스택 정의 ${stackSkills.length}개.`);
  console.log(`S1 출처 연결 범위${label}: ${covered}/${sourceCoverage.length}개.`);
  if (uncoveredSkills.length) {
    const preview = uncoveredSkills.slice(0, 20).map((item) => `${item.catalogSkill.id}(${item.catalogSkill.nameKo}, ${item.status})`).join(', ');
    const suffix = uncoveredSkills.length > 20 ? ` 외 ${uncoveredSkills.length - 20}개` : '';
    console.log(`S1 미완료${label}: ${preview}${suffix}`);
    if (!requireS1) console.log('완결 검사가 필요하면 --require-s1을, 특정 트리만 보려면 --tree <TreeId>를 사용하세요.');
  }
}




