import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const selectorSource = await readFile(resolve(root, 'assets/js/crysta-ui.js'), 'utf8');
const registrySource = await readFile(resolve(root, 'assets/js/stat-registry.js'), 'utf8');
const context = { globalThis:{} };
vm.createContext(context);
vm.runInContext(registrySource, context, { filename:'assets/js/stat-registry.js' });
const registry = context.globalThis.ToramStatRegistry;

const expected = ['VITP', 'VIT', 'MAXHP', 'MAXHPP', 'MAXMP', 'AMPR', 'AMPRP', 'PHYS_RES', 'MAG_RES', 'DEF', 'DEFP', 'MDEF', 'MDEFP', 'FLEE', 'FLEEP', 'ACC', 'ACCP', 'HP_REGEN', 'HP_REGENP', 'MP_REGEN', 'MP_REGENP'];
const modeled = new Set(['VITP', 'VIT', 'MAXHP', 'MAXHPP', 'MAXMP', 'AMPR', 'AMPRP']);
for (const key of expected) {
  assert.match(selectorSource, new RegExp(`<option value="${key}">`), `${key} must be selectable in equipment options.`);
  const definition = registry.get(key);
  assert.ok(definition, `${key} must remain registered.`);
  if (modeled.has(key)) assert.notEqual(definition.status, 'notModeled', `${key} must affect the calculator when selected.`);
}
assert.doesNotMatch(selectorSource, /<option value="(?:CAST_RED|DAMAGE_P)">/, '장비 옵션이 아닌 시전 시간 감소와 대미지 보정은 선택지에 포함하면 안 됩니다.');

console.log('Equipment option selector: PASS (modeled and preserved equipment stats are selectable)');
