import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';

const root=resolve(import.meta.dirname,'..');
const require=createRequire(import.meta.url);
const marginal=require(resolve(root,'assets/js/d4-dynamic-marginal.js'));
const seed=require(resolve(root,'assets/js/d4-dynamic-seed.js'));

function pkg(id,stats){return Object.freeze({id,slot:id.split('-')[0],statDelta:Object.freeze(stats),candidateNames:[id]});}
function evaluateStats(stats) {
  const atk=Number(stats.ATKP)||0,cdmg=Number(stats.CDMG)||0,hp=Number(stats.MAXHP)||0,mp=Number(stats.MAXMP)||0;
  const expected=1000+atk*20+cdmg*10;
  return Object.freeze({
    damage:{base:expected,triggered:expected,expected},
    offense:{atk:atk,matk:0,criticalDamage:cdmg,selectedAttackCritical:0,normalAttackCrit:100,stability:100,physicalPierce:0,magicPierce:0},
    utility:{maxHp:hp,maxMpBeforeBuff:mp,maxMpAfterBuff:mp,baseAmpr:0,amprBeforeDual:0,finalAmpr:0,aspd:1000,motionSpeed:0,cspd:0,castReduction:0},
    constraints:{feasible:hp>=100&&mp>=100,violations:hp>=100&&mp>=100?[]:['utility']}
  });
}
function problem(groups) {
  return Object.freeze({
    baseContext:{atkType:'PHYS',rangeType:'SHORT',bossDef:0,bossMdef:0,chkIsUnsheathe:false,activeBuildConversions:[]},
    scenarioSnapshot:{schema:'fixture',hash:'s3-fixture',basisName:'S3 fixture',requirements:{maxHp:100,maxMp:100,amprBeforeDual:null,normalAttackCrit:null,aspd:null},metadata:{}},
    metadata:{},groups:Object.freeze(groups)
  });
}
const groups=Object.freeze([
  Object.freeze({id:'weapon',packages:Object.freeze([pkg('weapon-damage',{ATKP:20}),pkg('weapon-hp',{MAXHP:100})])}),
  Object.freeze({id:'armor',packages:Object.freeze([pkg('armor-damage',{CDMG:20}),pkg('armor-mp',{MAXMP:100})])}),
  Object.freeze({id:'additional',packages:Object.freeze([pkg('additional-damage',{ATKP:10}),pkg('additional-neutral',{})])}),
  Object.freeze({id:'special',packages:Object.freeze([pkg('special-damage',{CDMG:10}),pkg('special-neutral',{})])})
]);
const input=problem(groups);
const profile=marginal.createDynamicMarginalProfile(input,{evaluateStats});
const pool=seed.createDynamicSeedPool(input,{profile,perSeedLimit:2,mergedGroupLimit:2});
const cartesian=seed.createDynamicSeedBuilds(input,{profile,pool,evaluateStats,cartesianLimit:32,seedEvaluationLimit:200,repairInputLimit:1,repairPerGroupLimit:1,repairPairLimit:1});
assert.equal(cartesian.mode,'cartesian','small multi-seed pool must enumerate complete package combinations');
assert.equal(cartesian.sourcePoolProduct,16,'small fixture should contain all four-group combinations');
assert.ok(cartesian.completeCandidates.every(item=>item.selections.length===4),'every S3 candidate must be a complete four-group build');
assert.ok(cartesian.completeCandidates.every(item=>item.outcome.damage.expected===evaluateStats(item.statDelta).damage.expected),'reported S3 score must come from direct complete evaluation');
assert.ok(cartesian.completeCandidates.every(item=>item.selections.every((choice,index)=>choice.slot===groups[index].id)),'S3 selections must preserve compiler group structure');
assert.ok(cartesian.repairEvaluations>0,'infeasible high-damage complete candidates must trigger repair attempts');
assert.ok(cartesian.repairAttemptIds.includes('weapon-hp||armor-mp||additional-damage||special-damage'),'two-group Utility repair must evaluate the jointly repaired complete build');

const beamGroups=Object.freeze(groups.map(group=>Object.freeze({id:group.id,packages:Object.freeze([...group.packages,pkg(group.id+'-third',{ATKP:1})])})));
const beamInput=problem(beamGroups);
const beamProfile=marginal.createDynamicMarginalProfile(beamInput,{evaluateStats});
const beamPool=seed.createDynamicSeedPool(beamInput,{profile:beamProfile,perSeedLimit:3,mergedGroupLimit:3});
const beam=seed.createDynamicSeedBuilds(beamInput,{profile:beamProfile,pool:beamPool,evaluateStats,cartesianLimit:4,beamWidth:3,seedEvaluationLimit:200,repairInputLimit:0});
assert.equal(beam.mode,'beam','large pool must use the bounded partial-outcome beam');
assert.ok(beam.completeCandidates.length>0&&beam.completeCandidates.every(item=>item.selections.length===4),'beam must emit only actual complete builds');
assert.ok(beam.completeCandidates.every(item=>item.outcome.damage.expected===evaluateStats(item.statDelta).damage.expected),'beam outcome must equal a direct evaluator result');

const cancelled=seed.createDynamicSeedBuilds(input,{profile,pool,evaluateStats,shouldCancel:()=>true});
assert.equal(cancelled.stoppedBy,'cancelled','S3 must honor cancellation before evaluating a seed build');
assert.equal(cancelled.evaluations,0,'cancelled S3 must not evaluate after cancellation');

const lowSeed=cartesian.feasibleCandidates.find(item=>item.id==='weapon-hp||armor-mp||additional-neutral||special-neutral');
const local=seed.improveDynamicSeedBuilds(input,{profile,pool,seedBuilds:{feasibleCandidates:[lowSeed]},evaluateStats,localStartLimit:1,localPassLimit:2,localCandidateLimit:2,localPairCandidateLimit:0});
assert.ok(local.best&&local.endLowerBound>local.startLowerBound,'S4 single-slot local improvement must retain and improve the feasible seed');
assert.ok(local.paths[0].steps.some(step=>step.kind==='single'),'S4 must record each successful single-slot improvement');
assert.equal(local.best.outcome.damage.expected,evaluateStats(local.best.statDelta).damage.expected,'S4 best outcome must equal direct evaluation');

const pairGroups=Object.freeze([
  Object.freeze({id:'weapon',packages:Object.freeze([pkg('weapon-base',{MAXHP:100}),pkg('weapon-pair',{ATKP:10,MAXMP:100})])}),
  Object.freeze({id:'armor',packages:Object.freeze([pkg('armor-base',{MAXMP:100}),pkg('armor-pair',{CDMG:10,MAXHP:100})])}),
  Object.freeze({id:'additional',packages:Object.freeze([pkg('additional-base',{})])}),
  Object.freeze({id:'special',packages:Object.freeze([pkg('special-base',{})])})
]);
const pairInput=problem(pairGroups);
const pairProfile=marginal.createDynamicMarginalProfile(pairInput,{evaluateStats});
const pairPool=seed.createDynamicSeedPool(pairInput,{profile:pairProfile,perSeedLimit:2,mergedGroupLimit:2});
const pairBuilds=seed.createDynamicSeedBuilds(pairInput,{profile:pairProfile,pool:pairPool,evaluateStats,cartesianLimit:32,repairInputLimit:0});
const pairStart=pairBuilds.feasibleCandidates.find(item=>item.id==='weapon-base||armor-base||additional-base||special-base');
const pairLocal=seed.improveDynamicSeedBuilds(pairInput,{profile:pairProfile,pool:pairPool,seedBuilds:{feasibleCandidates:[pairStart]},evaluateStats,localStartLimit:1,localPassLimit:1,localCandidateLimit:1,localPairCandidateLimit:1});
assert.ok(pairLocal.best&&pairLocal.endLowerBound>pairLocal.startLowerBound,'S4 pair local improvement must improve a complementary feasible exchange');
assert.ok(pairLocal.paths[0].steps.some(step=>step.kind==='pair'),'S4 must record a pair improvement when neither single exchange is feasible');

console.log('D4 dynamic seed builds S3-S4: PASS (cartesian, beam, repair, local single/pair improvement, cancellation)');
