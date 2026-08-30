import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const profile = require(resolve(root, 'assets/js/d4-source-profile.js'));

const requirements = { maxHp:10000, maxMp:2000, amprBeforeDual:100, normalAttackCrit:100, aspd:1000 };
const dependencies = profile.utilityDependencyMetadata({ requirements });

assert.equal(profile.utilityDependencyPolicyVersion, 'd4-utility-dependency.v1', 'Gate A policy version must be explicit.');
assert.equal(profile.supplyDifficultyPolicyVersion, 'd4-supply-difficulty.v1', 'Gate B policy version must be explicit.');
assert.equal(dependencies.maxHp.constraintOnly, true, 'MAXHP is residual-cappable when no HP condition is active.');
assert.equal(dependencies.maxHp.saturationRule, 'cap-to-residual', 'Pure MAXHP must declare residual saturation.');
assert.equal(profile.capUtilityContribution(dependencies.maxHp, 7000, 2000), 2000, 'Positive pure Utility contribution must cap at the residual.');
assert.equal(profile.capUtilityContribution(dependencies.maxHp, -7000, 2000), -7000, 'Negative Utility contribution must remain visible after capping.');

assert.equal(dependencies.maxMp.constraintOnly, false, 'MAXMP feeds AMPR and must retain its raw value.');
assert.ok(dependencies.maxMp.derivedDependencies.includes('amprBeforeDual'), 'MAXMP dependency on AMPR must be explicit.');
assert.equal(dependencies.amprBeforeDual.rawRequired, true, 'AMPR must retain raw value through normal-attack and dual-sword branches.');
assert.equal(dependencies.normalAttackCrit.objectiveDependent, true, 'Critical rate must remain an objective coordinate.');
assert.equal(dependencies.aspd.rawRequired, true, 'ASPD-derived motion speed must not be residual-capped.');

const hpConditionDependencies = profile.utilityDependencyMetadata({
  requirements,
  metadata:{ utilityDependencyOverrides:{ maxHp:{ conditionDependencies:['hpSkillMultiplier'] } } }
});
assert.equal(hpConditionDependencies.maxHp.constraintOnly, false, 'Declared HP-dependent damage must disable MAXHP saturation.');
assert.equal(hpConditionDependencies.maxHp.saturationRule, 'preserve-raw', 'HP-dependent scenarios must preserve raw MAXHP.');

const residual = profile.residualRequirements({
  utility:{ maxHp:8000, maxMpBeforeBuff:2100, amprBeforeDual:90, aspd:1200 },
  offense:{ normalAttackCrit:110 }
}, requirements);
assert.equal(residual.residual.maxHp, 2000, 'Residual MAXHP must remain in outcome units.');
assert.equal(residual.residual.maxMp, 0, 'Satisfied MAXMP residual must be zero.');
assert.equal(residual.dependencies.maxHp.saturationRule, 'cap-to-residual', 'Residual report must carry the Gate A dependency classification.');

const supplyProblem = {
  scenarioSnapshot:{ requirements:{ maxHp:10000, maxMp:2000, amprBeforeDual:null, normalAttackCrit:null, aspd:null } },
  groups:[
    { id:'armor', packages:[{ id:'armor-hp-dps', statDelta:{ MAXHP:7000, ATKP:4 } }] },
    { id:'weapon', packages:[{ id:'weapon-hp', statDelta:{ MAXHP:2000 } }] },
    { id:'special', packages:[{ id:'special-hp-mp', statDelta:{ MAXHP:1000, MAXMP:1000 } }] }
  ]
};
function supplyEvaluator(stats) {
  const values = stats || {};
  return {
    damage:{ expected:100 + Number(values.ATKP || 0) },
    utility:{ maxHp:8000 + Number(values.MAXHP || 0), maxMpBeforeBuff:1500 + Number(values.MAXMP || 0), amprBeforeDual:100, aspd:1000 },
    offense:{ normalAttackCrit:100 }
  };
}
const supply = profile.analyzeSupplyDifficulty(supplyProblem, supplyEvaluator);
assert.equal(supply.policyVersion, 'd4-supply-difficulty.v1', 'SupplyDifficulty report must carry its policy version.');
assert.equal(supply.measurementMode, 'single-package-delta-heuristic', 'SupplyDifficulty must state that it is not a deletion proof.');
assert.equal(supply.utilities.maxHp.residual, 2000, 'SupplyDifficulty must use the baseline residual.');
assert.equal(supply.utilities.maxHp.maximumSupply, 10000, 'Group maxima must retain the best reachable supply per group.');
assert.equal(supply.utilities.maxHp.satisfyingSourceCount, 2, 'Two single packages can satisfy the HP residual.');
assert.equal(supply.utilities.maxHp.concentration, .7, 'Armor supply concentration must be measured from group maxima.');
assert.equal(supply.utilities.maxHp.dpsOverlapCount, 1, 'HP plus DPS sources must be counted without deleting them.');
assert.equal(supply.utilities.maxHp.otherUtilityOverlapCount, 1, 'Sources shared with another Utility must be measured.');

const proofDependencies = { maxHp:dependencies.maxHp };
const proofInput = { objectiveKeys:['damage'], dependencies:proofDependencies, residual:{ maxHp:2000 }, rawUtilityKeys:['maxMp','amprBeforeDual','normalAttackCrit','aspd'] };
const proven = profile.safeResidualDominance(
  { id:'a', signatures:{ structure:'s', condition:'c', conflict:'x', lineage:'l' }, slotCost:1, objective:{ damage:10 }, utilityContribution:{ maxHp:7000 }, rawUtility:{ maxMp:0, amprBeforeDual:0, normalAttackCrit:0, aspd:0 } },
  { id:'b', signatures:{ structure:'s', condition:'c', conflict:'x', lineage:'l' }, slotCost:1, objective:{ damage:9 }, utilityContribution:{ maxHp:2000 }, rawUtility:{ maxMp:0, amprBeforeDual:0, normalAttackCrit:0, aspd:0 } },
  proofInput
);
assert.equal(proven.proven, true, 'Capped MAXHP plus a stronger objective may be proven dominant.');

const rawPreserved = profile.safeResidualDominance(
  { id:'a', signatures:{ structure:'s', condition:'c', conflict:'x', lineage:'l' }, slotCost:1, objective:{ damage:10 }, utilityContribution:{ maxHp:7000 }, rawUtility:{ maxMp:0, amprBeforeDual:0, normalAttackCrit:0, aspd:0 } },
  { id:'b', signatures:{ structure:'s', condition:'c', conflict:'x', lineage:'l' }, slotCost:1, objective:{ damage:9 }, utilityContribution:{ maxHp:2000 }, rawUtility:{ maxMp:500, amprBeforeDual:0, normalAttackCrit:0, aspd:0 } },
  proofInput
);
assert.equal(rawPreserved.proven, false, 'MAXMP raw dependency must prevent unsafe dominance.');

const signatureMismatch = profile.safeResidualDominance(
  { id:'a', signatures:{ structure:'s1', condition:'c', conflict:'x', lineage:'l' }, slotCost:1, objective:{ damage:10 }, utilityContribution:{ maxHp:7000 }, rawUtility:{ maxMp:0, amprBeforeDual:0, normalAttackCrit:0, aspd:0 } },
  { id:'b', signatures:{ structure:'s2', condition:'c', conflict:'x', lineage:'l' }, slotCost:1, objective:{ damage:9 }, utilityContribution:{ maxHp:2000 }, rawUtility:{ maxMp:0, amprBeforeDual:0, normalAttackCrit:0, aspd:0 } },
  proofInput
);
assert.equal(signatureMismatch.proven, false, 'Different structural signatures must prevent dominance.');
console.log('D4 utility dependency regressions: PASS');
