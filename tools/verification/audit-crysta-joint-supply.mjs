import {loadHeadlessEnvironment} from '../support/crysta-headless-environment.mjs';
// Inventory only: formula families do not enable pruning or change candidates.
import assert from 'node:assert/strict';
import { readFile, writeFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import vm from 'node:vm';
import { root, jsSources } from '../support/crysta-headless-environment.mjs';
import { resolve } from 'node:path';

const pairs = [
  ['atk', 'ATKP', 'ATK'], ['matk', 'MATKP', 'MATK'], ['weapon', 'WATKP', 'WATK'],
  ['criticalDamage', 'CDMGP', 'CDMG'], ['criticalRate', 'CRITP', 'CRIT'],
  ['unsheathe', 'UNSHEATHEP', 'UNSHEATHE'], ['hp', 'MAXHPP', 'MAXHP'],
  ['attackSpeed', 'ASPD_P', 'ASPD'], ['castSpeed', 'CSPD_P', 'CSPD'],
  ...['STR', 'DEX', 'AGI', 'INT', 'VIT'].map(key => [key.toLowerCase(), `${key}P`, key])
];
const classifiedOnly = {
  ...Object.fromEntries(['FIRE','WATER','WIND','EARTH','LIGHT','DARK','NEUTRAL'].map(element=>[element+'_DMG','target element multiplier'])),
  PHYS_PIERCE:'physical raw power', MAG_PIERCE:'magic raw power', MAXMP:'INT -> MP -> AMPR',
  AMPR:'MP -> AMPR', AMPRP:'raw display; excluded from optimization goal',
  MOTIONSPEED:'ASPD -> motion goal', CAST_RED:'CSPD -> cast reduction; display only',
  SRW:'range multiplier', LRW:'range multiplier', STABILITY:'stability/dual power',
  ELEM_P:'element multiplier', DAMAGE_P:'damage multiplier',
  ELEM_AWAKENING:'boolean element branch; Native candidate coordinate and outer bound supported',
  MAGIC_ELEMENT:'boolean element branch; Native candidate coordinate and outer bound supported',
  ...Object.fromEntries(['ATK', 'MATK'].flatMap(kind => ['STR', 'DEX', 'AGI', 'INT', 'VIT']
    .map(stat => [`${kind}_UP_${stat}`, `${kind} stat-up; Native candidate evaluation and outer bound supported`])))
};
const sourcePaths = ['web/src/calculation/stat-registry.js', 'web/src/data/crysta-data.js',
  'engine/src/stats.rs', 'engine/src/evaluator.rs',
  'web/src/calculation/calculator.js', 'engine/src/solver.rs', 'engine/src/joint_supply.rs',
  'web/src/optimization/problem-compiler.js', 'web/src/optimization/candidate-preparation.js',
  'tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json'];
const sources = await Promise.all(sourcePaths.map(async path => {
  const content = await readFile(resolve(root,path),'utf8');
  return { path, content, sha256:createHash('sha256').update(content).digest('hex') };
}));
const env=await loadHeadlessEnvironment(), sandbox=env.context, registry=env.registry, crystas=sandbox.ToramCrystaCatalog.items;
const nativeKeys = sources[2].content.match(/stat_keys!\s*\{([^}]+)\}/u)[1]
  .split(',').map(key => key.trim()).filter(Boolean).sort();
const classifications = Object.fromEntries(pairs.flatMap(([family, ...keys]) => keys.map(key => [key, family])));
Object.assign(classifications, classifiedOnly);
const modeled = Array.from(registry.entries(), entry => entry).filter(entry => entry.status !== 'notModeled').map(entry => entry.id);
assert.deepEqual(modeled.filter(key => !classifications[key]), [], 'Every modeled registry key needs a disposition');
assert.deepEqual(nativeKeys.filter(key => !classifications[key]), [], 'Every Native coordinate needs a disposition');
assert.equal(pairs.length, 14);

// Conditional rows are counted separately; mutually exclusive conditions are
// never merged into a fictional candidate for the raw-data co-occurrence count.
const rawRows = crystas.flatMap(crysta => [
  { name:crysta.name, conditional:Boolean(crysta.cond), stats:crysta.stats || {} },
  ...(crysta.conditionalStats || []).map(row => ({ name:crysta.name, conditional:true, stats:row.stats || {} }))
]).map(row => ({ ...row, stats:Object.fromEntries(Object.entries(row.stats)
  .map(([key, value]) => [registry.normalize(key) || key, Number(value)])) }));
const rawKeys = [...new Set(rawRows.flatMap(row => Object.keys(row.stats)))].sort();
const fixture = JSON.parse(sources.at(-1).content).resolvedExecutionContext;
const evaluator = sandbox.ToramBuildEvaluator;
const scenario = evaluator.createScenarioSnapshot(fixture.baseContext, { requirements:fixture.scenarioRequirements });
const compiled = sandbox.ToramCrystaOptimizationProblemCompiler.compileCrystaProblem({
  registry, crystas, ...fixture, scenarioSnapshot:scenario
});
const evaluate = stats => evaluator.evaluateAggregate(compiled.baseContext, scenario, stats,
  sandbox.ToramCalculationKernel.evaluateContext);
const optimizer = sandbox.ToramCrystaOptimizationCandidates;
const prepared = optimizer.prepareProblem(compiled, { registry,
  relevantKeys:optimizer.deriveRelevantKeys(compiled, registry, evaluate),
  pareto:{ maxComparisons:1000000 } });
function summary(rows, keys) {
  const nonzero = (row, key) => Number(row.stats[key]) !== 0 && Number.isFinite(Number(row.stats[key]));
  return {
    rows:rows.length,
    keyPresence:Object.fromEntries(keys.map(key => [key, rows.filter(row => nonzero(row, key)).length])),
    bothNonzero:rows.filter(row => keys.every(key => nonzero(row, key))).length,
    examples:rows.filter(row => keys.every(key => nonzero(row, key))).slice(0, 3)
      .map(row => ({ name:row.name, values:Object.fromEntries(keys.map(key => [key, row.stats[key]])) }))
  };
}
const packageRows = group => group.packages.map(item => ({ name:item.id, stats:item.statDelta }));
const bundles = pairs.map(([id, ...keys]) => ({ id, keys, raw:summary(rawRows, keys),
  prepared:prepared.groups.map(group => ({ group:group.id, ...summary(packageRows(group), keys) })) }));
const triples = [['physicalRaw', 'ATKP', 'ATK', 'PHYS_PIERCE'], ['magicRaw', 'MATKP', 'MATK', 'MAG_PIERCE']]
  .map(([id, ...keys]) => ({ id, keys, raw:summary(rawRows, keys),
    prepared:prepared.groups.map(group => ({ group:group.id, ...summary(packageRows(group), keys) })) }));
const keyAudit = rawKeys.map(key => ({ key, status:registry.get(key)?.status || 'unknown',
  classification:classifications[key] || 'preserved; not used by optimization',
  nativeCoordinate:nativeKeys.includes(key), ...summary(rawRows, [key]) }));
assert.equal(keyAudit.filter(row => row.status === 'unknown').length, 0, 'Unknown data keys need explicit review');
const output = {
  schema:'toram.crysta-joint-supply-inventory.v1',
  scope:'Current registry, complete raw data including condition rows, Native coordinates, and one unchanged saved input. No search or speed claims.',
  sources:sources.map(({ path, sha256 }) => ({ path, sha256 })),
  coverage:{ crystas:crystas.length, rawKeys:rawKeys.length, registryModeledKeys:modeled.length,
    nativeKeys:nativeKeys.length, directPairs:pairs.length, unclassifiedModeledKeys:[] },
  nativeKeys, classifications, bundles, triples, keyAudit,
  savedInput:{ path:sourcePaths.at(-1), compiledPackages:compiled.groups.map(group => ({ group:group.id, count:group.packages.length })),
    preparedPackages:prepared.groups.map(group => ({ group:group.id, count:group.packages.length })),
    relevantKeys:prepared.metadata.modeledKeys }
};
await writeFile(resolve(root, 'desktop/target/crysta-joint-supply-inventory.json'), JSON.stringify(output, null, 2) + '\n');
console.log(JSON.stringify({ ...output.coverage, pairs:bundles.map(bundle => ({ id:bundle.id,
  raw:bundle.raw.keyPresence, both:bundle.raw.bothNonzero,
  preparedBoth:bundle.prepared.reduce((count, group) => count + group.bothNonzero, 0) })),
  triples:triples.map(bundle => ({ id:bundle.id, raw:bundle.raw.bothNonzero,
    prepared:bundle.prepared.reduce((count, group) => count + group.bothNonzero, 0) })),
  savedInput:output.savedInput }, null, 2));
