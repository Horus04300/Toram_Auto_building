// Probe the existing evaluator; this is not a second damage formula or optimizer.
import assert from 'node:assert/strict';
import { readFile, writeFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { createHash } from 'node:crypto';
import { loadSavedBuildEnvironment } from '../support/saved-build-headless-environment.mjs';

const directory = resolve(process.argv[2] || 'data/sources/toram-statting/experiments/2026-10-21');
const cases = (await readFile(resolve(directory, 'cases.jsonl'), 'utf8')).trim().split('\n').map(JSON.parse)
  .filter(row => row.equipmentType === 10 && row.rounding === 'combined-floor'
    && ['atk-crit-stat', 'atk-four-crit'].includes(row.frame));
const catalog = JSON.parse(await readFile('data/sources/toram-statting/catalog.json', 'utf8'));
const definitions = new Map(catalog.options.filter(row => row.dictionary === 'EnhanceCost').map(row => [row.id, row]));
const environment = await loadSavedBuildEnvironment();
const piece = type => ({ type, attack:0, refinement:0, stability:0, options:[], crystas:[], lockedCrystaSlots:[] });
const records = [], marginal = [];
for (const fixedCrit of [0, 50, 80]) {
  const input = { build:{ character:{ level:325, attributes:{ STR:510, INT:1, VIT:1, AGI:1, DEX:327, CRT:0 } },
    equipment:{ mainWeapon:{ ...piece('한손검'), attack:730, stability:80 }, subWeapon:piece('없음'),
      armor:piece('일반옷'), additional:piece(null), special:piece(null) },
    externalOptions:[{ key:'CRIT', value:fixedCrit }], skillLevels:{}, activeBuffs:{}, combo:[], guildFoodBuff:false },
    scenario:{ target:{ bossLevel:325, bossDef:1000, bossMdef:500, bossCritResist:0, bossPhysResist:0, bossMagResist:0 }, conditions:{} },
    request:{ selectedSkillId:null, selectedHitId:null, overrides:{} } };
  const calculation = environment.ToramApplication.CalculateBuild(input);
  const base = calculation.snapshot.baseContext;
  const original = JSON.stringify(base);
  const scenario = environment.ToramBuildEvaluator.createScenarioSnapshot(base, {
    requirements:{ maxHp:null, maxMp:null, amprBeforeDual:null, normalAttackCrit:100, aspd:null }
  });
  function evaluate(positive, negative) {
    const stats = {};
    for (const [id, value] of Object.entries({ ...positive, ...negative })) {
      const definition = definitions.get(Number(id));
      assert.ok(definition?.projectStatId, 'Never silently discard an unmapped option');
      const key = definition.projectStatId;
      assert.ok(environment.ToramStatRegistry.get(key));
      stats[key] = (stats[key] || 0) + Math.fround(Math.fround(value) * definition.displayMultiplierFloat32);
    }
    const result = environment.ToramBuildEvaluator.evaluateAggregate(base, scenario, stats,
      environment.ToramCalculationKernel.evaluateContext);
    assert.ok(Number.isFinite(result.damage.expected));
    assert.equal(result.diagnostics.length, 0);
    assert.equal(JSON.stringify(base), original, 'Candidate evaluation must not alter the fixed reference');
    return { expectedDamageFactor:result.damage.expected, normalAttackCrit:result.offense.normalAttackCrit,
      criticalDamage:result.offense.criticalDamage, meetsCrit100:result.constraints.feasible };
  }
  for (const row of cases) {
    records.push({ fixedCrit, frame:row.frame, positives:row.positives, negatives:row.negatives,
      recipeWarningPercent:row.combined, ...evaluate(row.positives, row.negatives) });
  }
  const found = cases.find(row => row.combined >= 90 && Number(row.positives['40']) < 32);
  if (found) {
    const before = evaluate(found.positives, found.negatives);
    const after = evaluate({ ...found.positives, 40:found.positives['40']+1 }, found.negatives);
    marginal.push({ fixedCrit, before, after, deltaDamage:after.expectedDamageFactor-before.expectedDamageFactor,
      scope:'battle marginal only; the modified recipe has not been re-planned' });
    if (fixedCrit === 80) assert.equal(after.expectedDamageFactor, before.expectedDamageFactor);
  }
}
const selected = [];
for (const fixedCrit of [0, 50, 80]) for (const minimumWarning of [90, 100]) {
  const feasible = records.filter(row => row.fixedCrit === fixedCrit && row.recipeWarningPercent >= minimumWarning && row.meetsCrit100)
    .sort((a,b) => b.expectedDamageFactor-a.expectedDamageFactor || b.recipeWarningPercent-a.recipeWarningPercent);
  selected.push({ fixedCrit, minimumWarning, eligibleCandidates:feasible.length, best:feasible[0] || null });
}
const report = { schema:'toram.statting-existing-evaluator-probe.v1',
  scope:'physical normal attack, one-hand reference; candidate recipes filtered after exact arithmetic replay. No crysta optimization and no global build claim.',
  reference:{ level:325, fiveStatSum:840, attributes:{ STR:510, DEX:327, INT:1, VIT:1, AGI:1 },
    weaponBaseItemId:10188, weaponAttack:730, refinement:0, stability:80, bossDef:1000,
    fixedCritContributions:[0,50,80], otherUtilityRequirements:'disabled for this isolated probe' },
  evaluations:records.length, selected, marginal,
  elementalGate:{ FIRE_DMG:environment.ToramStatRegistry.get('FIRE_DMG').status,
    ELEM_P:environment.ToramStatRegistry.get('ELEM_P').status,
    note:'Raw DTE keys are preserved, not the generic ELEM_P contribution; target-element conversion must be verified before damage-ranked DTE recommendations.' },
  sourceHashes:Object.fromEntries(await Promise.all([
    'web/src/application/application-use-cases.js', 'web/src/calculation/calculator.js',
    'web/src/calculation/build-evaluator.js', 'web/src/calculation/stat-registry.js'
  ].map(async path => [path, createHash('sha256').update(await readFile(path)).digest('hex')]))) };
await writeFile(resolve(directory, 'score-probe.json'), JSON.stringify(report, null, 2)+'\n');
console.log(`PASS: ${records.length} existing-evaluator calls; fixed input preserved, saturated crit marginal checked, DTE gate explicit`);
