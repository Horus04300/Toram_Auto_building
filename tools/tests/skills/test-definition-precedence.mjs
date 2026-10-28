import '../../../web/src/calculation/skill-effect-engine.js';
import {skillRegistry} from '../../../web/src/data/skill-effect-registry.js';
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {createHash} from 'node:crypto';
import {resolve} from 'node:path';

const root = resolve(import.meta.dirname, '../../..');
const baseline = JSON.parse(readFileSync(resolve(root, 'tools/fixtures/skill-definition-precedence.json'), 'utf8'));
const context = { window:{}, console };
context.window.window = context.window;
const registry = skillRegistry, definitions = registry.definitions();
const hash = value => createHash('sha256').update(JSON.stringify(value)).digest('hex');
assert.equal(definitions.length,baseline.count);
assert.equal(new Set(definitions.map(skill=>skill.id)).size,definitions.length);
assert.equal(hash(definitions.map(skill=>skill.id)),baseline.orderedIdsSha256,'Floating-point evaluation order must remain unchanged');
assert.equal(hash(definitions.map(({sourceRef,...value})=>value)),baseline.calculationSha256,'Every selected calculation value must match the pre-consolidation behavior');
assert.equal(Object.isFrozen(definitions),true);
for (const skill of definitions) {
  assert.equal(registry.get(skill.id),skill);
  assert.equal(Object.isFrozen(skill),true);
  assert.ok(skill.sourceRef,'Every canonical definition retains a source link');
}
assert.throws(()=>registry.register([{id:'fixture:0'},{id:definitions[0].id}]),/중복/);
assert.equal(registry.get('fixture:0'),undefined,'Rejected batches must be atomic');
assert.throws(()=>registry.register([{id:'fixture:0'},{id:'fixture:0'}]),/중복/);
assert.equal(registry.get('fixture:0'),undefined);
console.log('Skill ID registry: PASS (427 canonical definitions, exact calculation values/order, complete source links, atomic duplicate rejection)');
