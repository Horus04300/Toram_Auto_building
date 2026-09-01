import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root=resolve(import.meta.dirname,'..');
const require=createRequire(import.meta.url);
const registry=require(resolve(root,'assets/js/stat-registry.js'));
const evaluator=require(resolve(root,'assets/js/build-evaluator.js'));
const compiler=require(resolve(root,'assets/js/d4-problem-compiler.js'));
const sourceProfile=require(resolve(root,'assets/js/d4-source-profile.js'));
const dynamicMarginal=require(resolve(root,'assets/js/d4-dynamic-marginal.js'));
const dynamicSeed=require(resolve(root,'assets/js/d4-dynamic-seed.js'));
const optimizer=require(resolve(root,'assets/js/d4-global-optimizer.js'));
const context={window:{ToramStatRegistry:registry},console};
context.window.window=context.window;
vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};',context);
vm.runInContext(await readFile(resolve(root,'assets/js/calculation-policies.js'),'utf8'),context,{filename:'calculation-policies.js'});
vm.runInContext(await readFile(resolve(root,'assets/js/calculator.js'),'utf8'),context,{filename:'calculator.js'});
const kernel=context.window.ToramCalculationKernel.evaluateContext;

function base(overrides={}) {
  return Object.assign({
    level:100,strBase:200,intBase:0,vitBase:0,agiBase:0,dexBase:200,crtBase:0,
    mainType:'한손검',wpnAtk:200,wpnRefine:0,wpnStab:100,subType:'없음',subAtk:0,subRefine:0,subStab:0,armorType:'경량옷',
    bossLevel:100,bossDef:100,bossMdef:100,bossCritResist:0,bossPhysResist:0,bossMagResist:0,
    skillMult:1,skillConst:0,procDamageModifiers:[],atkType:'PHYS',rangeType:'SHORT',optimizationBasisName:'S1 dynamic marginal fixture',
    chkIsUnsheathe:true,chkGuaranteedCrit:false,conversionLevel:0,conversionActive:false,dualBringerLevel:0,dualBringerActive:false,spellBurstLevel:0,godspeedWieldLevel:0,
    poisonSources:[],weakenSources:[],targetWeakened:false,attackElement:'none',attackPowerMode:'default',useHigherRangeDamage:false,
    noCritical:false,criticalChanceBonus:0,criticalChanceMultiplier:1,fixedCriticalChance:null,minimumCriticalDamage:0,
    stabilityBonus:0,physicalPierceSkillBonus:0,magicPierceSkillBonus:0,ignoreDefense:false,ignoreMdef:false,halfMdefIgnored:false,
    strP:0,strF:0,dexP:0,dexF:0,intP:0,intF:0,agiP:0,agiF:0,vitP:0,vitF:0,
    atkP:0,atkF:0,matkP:0,matkF:0,cdmgP:0,cdmgF:0,critP:0,critF:0,srw:0,lrw:0,unsheatheP:0,unsheatheF:0,elemP:0,damageP:0,watkP:0,watkF:0,
    physPierce:0,magPierce:0,aspdF:0,aspdP:0,cspdF:0,cspdP:0,stability:0,motionSpeed:0,castRed:0,
    maxHpF:10000,maxHpP:0,maxMpF:1800,amprF:70,amprP:0,elementAwakening:false,magicElement:false,
    atkUpSTR:0,atkUpDEX:0,atkUpINT:0,atkUpAGI:0,atkUpVIT:0,matkUpSTR:0,matkUpDEX:0,matkUpINT:0,matkUpAGI:0,matkUpVIT:0,
    preservedStats:{},statDiagnostics:[],activeBuildConversions:[]
  },overrides);
}
function pkg(id,slot,statDelta){return Object.freeze({id,slot,statDelta:Object.freeze(statDelta),candidateNames:[id],evaluatorCandidates:[]});}
function makeProblem(ctx,groups) {
  return Object.freeze({
    schema:compiler.schema,baseContext:ctx,
    scenarioSnapshot:evaluator.createScenarioSnapshot(ctx,{requirements:{maxHp:12000,maxMp:2200,amprBeforeDual:100,normalAttackCrit:100,aspd:1000}}),
    diagnostics:[],metadata:{},groups:Object.freeze(groups)
  });
}
const baseContext=base();
const groups=Object.freeze([
  Object.freeze({id:'weapon',packages:Object.freeze([
    pkg('weapon-mixed','weapon',{ATKP:10,PHYS_PIERCE:5,SRW:6,CRIT:15,CDMG:10,UNSHEATHEP:8,MAXMP:400,AMPR:15,ASPD:150}),
    pkg('weapon-magic','weapon',{MATKP:10,MAG_PIERCE:8,INTP:5}),
    pkg('weapon-low','weapon',{FLEE:1})
  ])}),
  Object.freeze({id:'armor',packages:Object.freeze([
    pkg('armor-utility','armor',{MAXHP:3000,MAXMP:500,AMPR:30,ASPD:300}),
    pkg('armor-physical','armor',{ATKP:8,CDMG:15})
  ])})
]);
const problem=makeProblem(baseContext,groups);
const options={evaluator,kernel,sourceProfile};
const profile=dynamicMarginal.createDynamicMarginalProfile(problem,options);
assert.equal(profile.schema,'toram.d4-dynamic-marginal.v1');
assert.equal(profile.groups[0].groupId,'armor','groups must be ordered deterministically');
assert.equal(profile.groups[0].packages[0].packageId,'armor-physical','packages must be ordered deterministically');
assert.ok(profile.evaluationCount>1,'baseline and package measurements must be counted');

function add(left,right){const result={...left};for(const [key,value] of Object.entries(right))result[key]=(Number(result[key])||0)+(Number(value)||0);return result;}
function direct(stats){return evaluator.evaluateAggregate(baseContext,problem.scenarioSnapshot,stats,kernel);}
for (const group of profile.groups) for (const record of group.packages) {
  const after=direct(record.statDelta);
  const expectedScore=100*Math.log(after.damage.expected/profile.baseline.outcome.damage.expected);
  assert.ok(Math.abs(record.damageScore-expectedScore)<1e-12,record.packageId+' damage score must equal direct evaluator log delta');
  assert.equal(record.outcome.damage.expected,after.damage.expected,record.packageId+' outcome must equal direct evaluator');
  assert.equal(record.outcomeDelta.utility.maxHp,Number(after.utility.maxHp)-Number(profile.baseline.outcome.utility.maxHp));
}
const mixed=profile.groups.flatMap(group=>group.packages).find(record=>record.packageId==='weapon-mixed');
for (const axis of ['physicalAttack','range','critical','unsheathe','other']) {
  assert.ok(mixed.axisMarginals[axis],axis+' axis must be evaluated for mixed package');
  const after=direct(mixed.axisMarginals[axis].statDelta);
  const expected=100*Math.log(after.damage.expected/profile.baseline.outcome.damage.expected);
  assert.ok(Math.abs(mixed.axisMarginals[axis].damageScore-expected)<1e-12,axis+' axis must equal direct evaluator');
}
const directBaselineResidual=sourceProfile.residualRequirements(direct({}),problem.scenarioSnapshot.requirements).residual;
const directMixedResidual=sourceProfile.residualRequirements(direct(mixed.statDelta),problem.scenarioSnapshot.requirements).residual;
assert.equal(mixed.residualReduction.maxMp,directBaselineResidual.maxMp-directMixedResidual.maxMp,'MAXMP residual reduction must use evaluator output');
assert.equal(mixed.residualReduction.amprBeforeDual,directBaselineResidual.amprBeforeDual-directMixedResidual.amprBeforeDual,'AMPR residual reduction must use evaluator output');

const reversed=makeProblem(baseContext,Object.freeze([...groups].reverse().map(group=>Object.freeze({id:group.id,packages:Object.freeze([...group.packages].reverse())}))));
const repeat=dynamicMarginal.createDynamicMarginalProfile(reversed,options);
assert.equal(repeat.profileHash,profile.profileHash,'package input order must not affect profile identity');
const candidateOrder=dynamicSeed.createDynamicCandidateOrder(profile),repeatCandidateOrder=dynamicSeed.createDynamicCandidateOrder(repeat);
assert.equal(candidateOrder.schema,'toram.d4-dynamic-candidate-order.v1','S5 must return a versioned candidate-order view');
assert.equal(candidateOrder.orderHash,repeatCandidateOrder.orderHash,'S5 candidate order must be invariant to package input order');
assert.ok(candidateOrder.groups.every(group=>group.packageIds.length===groups.find(source=>source.id===group.groupId).packages.length),'S5 order must retain every package in every group');
const changed=dynamicMarginal.createDynamicMarginalProfile(makeProblem(base({bossDef:101}),groups),options);
assert.notEqual(changed.scenarioSignature.hash,profile.scenarioSignature.hash,'boss defense boundary must be part of the signature');

const pool=dynamicSeed.createDynamicSeedPool(problem,{profile,perSeedLimit:1,mergedGroupLimit:1});
assert.equal(pool.schema,'toram.d4-dynamic-seed-pool.v1','S2 must return a versioned multi-seed pool');
assert.ok(pool.groups.every(group=>group.poolPackageCount>0&&group.poolPackageCount<=group.sourcePackageCount),'every group pool must be a non-empty subset of the original candidate domain');
const weaponPool=pool.groups.find(group=>group.groupId==='weapon');
assert.ok(!weaponPool.packageIds.includes('weapon-low'),'a low-value candidate may stay outside the seed pool');
assert.equal(problem.groups.find(group=>group.id==='weapon').packages.length,3,'S2 must not remove candidates from the exact problem');
for (const utilityId of pool.activeUtilities) {
  const supplied=pool.groups.flatMap(group=>group.packages).some(item=>item.reasons.some(reason=>reason.seed.indexOf('utility:'+utilityId)===0||reason.seed.indexOf('frontier:'+utilityId+':')===0));
  assert.ok(supplied,utilityId+' active Utility must retain a supply representative');
}
const repeatPool=dynamicSeed.createDynamicSeedPool(reversed,{profile:repeat,perSeedLimit:1,mergedGroupLimit:1});
assert.equal(repeatPool.poolHash,pool.poolHash,'input order must not affect multi-seed pool identity');
const unconstrainedProblem=Object.freeze(Object.assign({},problem,{scenarioSnapshot:evaluator.createScenarioSnapshot(baseContext,{requirements:{maxHp:null,maxMp:null,amprBeforeDual:null,normalAttackCrit:null,aspd:null}})}));
const poolOracle=optimizer.exhaustiveSearch(unconstrainedProblem,{registry,evaluator,kernel,sourceProfile});
const poolSolved=optimizer.optimize(unconstrainedProblem,{registry,evaluator,kernel,sourceProfile});
assert.equal(poolSolved.status,'exact','S2 must leave exact solving available on the unchanged full candidate groups');
assert.equal(poolSolved.bestBuild.id,poolOracle.bestBuild.id,'S2 pool membership must not alter the full exact candidate result');

const crystaSource=await readFile(resolve(root,'assets/js/data/crysta-data.js'),'utf8');
const dataContext={};vm.createContext(dataContext);vm.runInContext(crystaSource+'\nglobalThis.__crystas=crystaDataJson;',dataContext);
const fullCompiled=compiler.compileCrystaProblem({crystas:dataContext.__crystas,registry,baseContext,scenarioSnapshot:evaluator.createScenarioSnapshot(baseContext),currentCrystas:[],locks:[],banned:{'오로로 콜론':true}});
assert.equal(fullCompiled.diagnostics.length,0,'actual crysta fixture must compile without diagnostics');
const fullPrepared=optimizer.prepareProblem(fullCompiled,{registry,pareto:{maxComparisons:1000000}});
const fullReplacementAdapter=stats=>evaluator.evaluateAggregate(baseContext,fullPrepared.scenarioSnapshot,stats,kernel);
const fullReplacementReport=sourceProfile.createReplacementProofReport(fullPrepared,fullReplacementAdapter,{maxComparisons:5000000});
const reversedPrepared=Object.freeze({...fullPrepared,groups:Object.freeze(fullPrepared.groups.map(group=>Object.freeze({...group,packages:Object.freeze([...group.packages].reverse())})))});
const reversedReplacementReport=sourceProfile.createReplacementProofReport(reversedPrepared,fullReplacementAdapter,{maxComparisons:5000000});
assert.equal(fullReplacementReport.complete,true,'actual prepared packages must complete the S6 proof scan without a truncated comparison budget');
assert.equal(fullReplacementReport.groups.reduce((sum,group)=>sum+group.packageCount,0),fullPrepared.groups.reduce((sum,group)=>sum+group.packages.length,0),'S6 must analyze every prepared actual package');
assert.equal(reversedReplacementReport.reportHash,fullReplacementReport.reportHash,'actual S6 proof report must be invariant to package input order');
assert.ok(fullReplacementReport.certificates.every(certificate=>certificate.schema==='d4-pruning-certificate.v1'&&certificate.certificateHash),'actual S6 Proven Drops must all carry certificates');
const fullProfile=dynamicMarginal.createDynamicMarginalProfile(fullCompiled,options);
const packageCount=fullCompiled.groups.reduce((sum,group)=>sum+group.packages.length,0);
assert.equal(fullProfile.groups.reduce((sum,group)=>sum+group.packages.length,0),packageCount,'all actual candidate packages must receive a profile');
assert.ok(fullProfile.evaluationCount>packageCount,'axis measurements must be included for actual candidate packages');
assert.ok(fullProfile.groups.flatMap(group=>group.packages).every(record=>Number.isFinite(record.outcome.damage.expected)),'all actual package profiles must record finite evaluator outcomes');
const fullPool=dynamicSeed.createDynamicSeedPool(fullCompiled,{profile:fullProfile});
assert.equal(fullPool.groups.length,4,'actual crysta profile must create one pool per equipment group');
assert.ok(fullPool.groups.every(group=>group.poolPackageCount>0&&group.poolPackageCount<=group.sourcePackageCount),'actual pool must be a non-empty subset without modifying source domains');
assert.ok(fullPool.groups.flatMap(group=>group.packages).every(item=>item.reasons.length>0),'every actual pool package must have an inclusion reason');
const fullBuildSeeds=dynamicSeed.createDynamicSeedBuilds(fullCompiled,{profile:fullProfile,pool:fullPool,evaluator,kernel,sourceProfile,cartesianLimit:64,beamWidth:32,seedTimeLimitMs:2000,seedEvaluationLimit:10000,repairInputLimit:2,repairPerGroupLimit:4,repairPairLimit:3});
assert.equal(fullBuildSeeds.mode,'beam','actual S3 pool must use bounded beam rather than an uncontrolled Cartesian product');
assert.ok(fullBuildSeeds.completeCandidates.length>0&&fullBuildSeeds.completeCandidates.every(item=>item.selections.length===4),'actual S3 must emit only complete four-group builds');
assert.ok(fullBuildSeeds.best&&fullBuildSeeds.best.feasible,'actual S3 must retain at least one feasible complete seed');
assert.ok(fullBuildSeeds.completeCandidates.every(item=>item.outcome.damage.expected===evaluator.evaluateAggregate(baseContext,fullCompiled.scenarioSnapshot,item.statDelta,kernel).damage.expected),'actual S3 reported outcome must equal a direct evaluator result');

console.log('D4 dynamic marginal / S2-S3: PASS ('+packageCount+' actual packages, '+fullProfile.evaluationCount+' evaluator measurements, pool '+fullPool.groups.map(group=>group.groupId+':'+group.poolPackageCount).join(',')+', '+fullBuildSeeds.mode+' '+fullBuildSeeds.evaluations+' evaluations)');
