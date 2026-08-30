import assert from 'node:assert/strict';

import sourceProfile from '../assets/js/d4-source-profile.js';
import optimizer from '../assets/js/d4-global-optimizer.js';

function packageOf(id, stats, condition = { active:[], inactive:[] }) {
  return Object.freeze({
    id,
    slot:'weapon',
    structureSignature:'onehanded|none|light',
    resolvedConditionMetadata:condition,
    statDelta:Object.freeze(stats),
    resourceCost:Object.freeze({ sockets:2 }),
    candidateIds:Object.freeze([id]),
    candidateNames:Object.freeze([id]),
    evaluatorCandidates:Object.freeze([])
  });
}

function evaluateStats(stats) {
  const values = stats || {};
  return Object.freeze({
    damage:Object.freeze({ expected:100 + (Number(values.ATKP) || 0) }),
    utility:Object.freeze({ maxHp:10000, maxMpBeforeBuff:Number(values.MAXMP) || 0, amprBeforeDual:0, aspd:0 }),
    offense:Object.freeze({ normalAttackCrit:0 }),
    constraints:Object.freeze({ feasible:true, violations:Object.freeze([]) })
  });
}

const normalCondition = Object.freeze({ active:Object.freeze([]), inactive:Object.freeze([]) });
const differentCondition = Object.freeze({ active:Object.freeze([{ main:'staff' }]), inactive:Object.freeze([]) });
const weaponPackages = Object.freeze([
  packageOf('weapon:a-tie-witness', { ATKP:5 }, normalCondition),
  packageOf('weapon:z-tie-drop', { ATKP:5 }, normalCondition),
  packageOf('weapon:z-raw-utility', { ATKP:1, MAXMP:200 }, normalCondition),
  packageOf('weapon:z-condition', { ATKP:1 }, differentCondition)
]);
const armorPackage = Object.freeze({ ...packageOf('armor:neutral', {}, normalCondition), id:'armor:neutral', slot:'armor' });
const problem = Object.freeze({
  schema:'toram.d4-crysta-problem.v1',
  baseContext:{}, structure:{ signature:'onehanded|none|light' },
  scenarioSnapshot:Object.freeze({ hash:'replacement-proof-fixture', requirements:Object.freeze({ maxHp:null, maxMp:null, amprBeforeDual:null, normalAttackCrit:null, aspd:null }), metadata:Object.freeze({}) }),
  metadata:Object.freeze({ modeledKeys:Object.freeze(['ATKP']) }), diagnostics:Object.freeze([]),
  groups:Object.freeze([
    Object.freeze({ id:'weapon', slots:Object.freeze([0,1]), packages:weaponPackages }),
    Object.freeze({ id:'armor', slots:Object.freeze([2,3]), packages:Object.freeze([armorPackage]) })
  ])
});

const report = sourceProfile.createReplacementProofReport(problem, evaluateStats, { objectiveKeys:['ATKP'], rawUtilityKeys:['maxMp'] });
assert.equal(report.schema, 'toram.d4-replacement-proof-report.v1');
assert.equal(report.complete, true, 'small S6 proof fixture must exhaust its replacement comparison space');
assert.ok(report.provenDrops.includes('weapon:z-tie-drop'), 'same-vector package with a later ID must receive a Proven Drop certificate');
assert.ok(report.certificates.every(certificate => certificate.schema === 'd4-pruning-certificate.v1' && certificate.certificateHash && certificate.objectiveProof && certificate.utilityProof && certificate.feasibilityProof && certificate.replacementProof && certificate.tieBreakProof), 'every Proven Drop must carry a complete reproducible certificate');
assert.ok(report.unprovenWitnesses.some(witness => witness.removedId === 'weapon:z-raw-utility'), 'raw MAXMP loss must stay as an unproven witness instead of becoming a drop');
assert.ok(!report.provenDrops.includes('weapon:z-raw-utility'), 'raw Utility dependency must block an unsafe replacement drop');
assert.ok(!report.provenDrops.includes('weapon:z-condition'), 'different resolved condition signatures must block replacement');

const reduced = sourceProfile.applyProvenDropsForAudit(problem, report);
assert.ok(!reduced.groups[0].packages.some(item => item.id === 'weapon:z-tie-drop'), 'audit reduction must remove only certified packages');
const originalOracle = optimizer.exhaustiveSearch(problem, { evaluateStats, prepared:true });
const reducedOracle = optimizer.exhaustiveSearch(reduced, { evaluateStats, prepared:true });
assert.equal(reducedOracle.score, originalOracle.score, 'S6 audit reduction must preserve exhaustive exact score');
assert.equal(reducedOracle.bestBuild.id, originalOracle.bestBuild.id, 'S6 audit reduction must preserve exhaustive tie ID');

const permuted = Object.freeze({ ...problem, groups:Object.freeze(problem.groups.map(group => Object.freeze({ ...group, packages:Object.freeze([...group.packages].reverse()) }))) });
const repeated = sourceProfile.createReplacementProofReport(permuted, evaluateStats, { objectiveKeys:['ATKP'], rawUtilityKeys:['maxMp'] });
assert.equal(repeated.reportHash, report.reportHash, 'S6 certificate report must be invariant to package input order');
assert.deepEqual(repeated.provenDrops, report.provenDrops, 'S6 Proven Drop list must be deterministic');

console.log(`D4 replacement proof S6: PASS (${report.provenDrops.length} certificates, ${report.unprovenWitnesses.length} unproven witnesses)`);
