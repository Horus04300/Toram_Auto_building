import { frontendSourcePath } from '../../support/frontend-paths.mjs';
import { readCrystaDataSource } from '../../support/crysta-catalog-source.mjs';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { createHash } from 'node:crypto';
import { resolve } from 'node:path';
import vm from 'node:vm';
import { CLASSIC_SCRIPT_PATHS as runtimeScripts } from '../../../web/src/classic-script-manifest.mjs';
const CLASSIC_SCRIPT_PATHS = runtimeScripts.map(frontendSourcePath);

const root = resolve(import.meta.dirname, '../../..');
const baseline = JSON.parse(readFileSync(resolve(root, 'tools/fixtures/skill-definition-precedence.json'), 'utf8'));
const context = { window:{}, console };
context.window.window = context.window;
vm.createContext(context);
assert.equal(new Set(CLASSIC_SCRIPT_PATHS).size, CLASSIC_SCRIPT_PATHS.length, 'Each runtime file must load once');
for (const path of [...CLASSIC_SCRIPT_PATHS.filter(p => p.startsWith('web/src/data/')), 'web/src/calculation/calculation-policies.js']) {
  vm.runInContext(path === 'web/src/data/crysta-data.js' ? await readCrystaDataSource(root) : readFileSync(resolve(root, path), 'utf8'), context, { filename:path });
}
const snapshots = {
  all:context.window.ToramSkillEffectRegistry.all(),
  normal:context.window.ToramCalculationPolicies.resolveSkillDefinitions(),
  stack:context.window.ToramCalculationPolicies.resolveSkillDefinitions({ preferStackControl:true })
};
assert.deepEqual(Object.keys(context.window.TORAM_SKILL_EFFECT_TREE_DATA).sort(), [...baseline.groups].sort());
for (const [name, definitions] of Object.entries(snapshots)) {
  assert.equal(definitions.length, baseline.snapshots[name].count);
  assert.equal(createHash('sha256').update(JSON.stringify(definitions)).digest('hex'), baseline.snapshots[name].sha256,
    `${name}: definition values and precedence must match the approved baseline`);
}
console.log('Skill definition precedence: PASS (full registry, default selection, stack-control selection)');
