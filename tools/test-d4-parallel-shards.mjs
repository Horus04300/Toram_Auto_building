import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const evaluator = require(resolve(root, 'assets/js/build-evaluator.js'));
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));

const context = { window:{ ToramStatRegistry:registry }, console };
context.window.window = context.window;
vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', context);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'calculator.js' });

function base(overrides={}) {
  return Object.assign({
    level:100, strBase:200, intBase:0, vitBase:0, agiBase:0, dexBase:200, crtBase:0,
    mainType:'한손검', wpnAtk:200, wpnRefine:0, wpnStab:100, subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'경량옷',
    bossLevel:100, bossDef:100, bossMdef:100, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
    skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'SHORT', optimizationBasisName:'Parallel shard fixture',
    chkIsUnsheathe:false, chkGuaranteedCrit:false, conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false, spellBurstLevel:0, godspeedWieldLevel:0,
    poisonSources:[], weakenSources:[], targetWeakened:false, attackElement:'none', attackPowerMode:'default', useHigherRangeDamage:false,
    noCritical:false, criticalChanceBonus:0, criticalChanceMultiplier:1, fixedCriticalChance:null, minimumCriticalDamage:0,
    stabilityBonus:0, physicalPierceSkillBonus:0, magicPierceSkillBonus:0, ignoreDefense:false, ignoreMdef:false, halfMdefIgnored:false,
    strP:0, strF:0, dexP:0, dexF:0, intP:0, intF:0, agiP:0, agiF:0, vitP:0, vitF:0,
    atkP:0, atkF:0, matkP:0, matkF:0, cdmgP:0, cdmgF:0, critP:0, critF:75, srw:0, lrw:0, unsheatheP:0, unsheatheF:0, elemP:0, damageP:0, watkP:0, watkF:0,
    physPierce:0, magPierce:0, aspdF:1000, aspdP:0, cspdF:0, cspdP:0, stability:0, motionSpeed:0, castRed:0,
    maxHpF:10000, maxHpP:0, maxMpF:1800, amprF:70, amprP:0, elementAwakening:false, magicElement:false,
    atkUpSTR:0, atkUpDEX:0, atkUpINT:0, atkUpAGI:0, atkUpVIT:0, matkUpSTR:0, matkUpDEX:0, matkUpINT:0, matkUpAGI:0, matkUpVIT:0,
    preservedStats:{}, statDiagnostics:[], activeBuildConversions:[]
  }, overrides);
}
function pkg(id, slot, stats) { return Object.freeze({ id, slot, statDelta:Object.freeze(stats), evaluatorCandidates:[], candidateNames:[id] }); }

const baseContext = base();
const scenario = evaluator.createScenarioSnapshot(baseContext, { requirements:{ maxHp:null, maxMp:null, amprBeforeDual:null, normalAttackCrit:null, aspd:null } });
const problem = Object.freeze({
  schema:'toram.d4-problem.v1', baseContext, scenarioSnapshot:scenario, diagnostics:[], metadata:{},
  groups:Object.freeze([
    Object.freeze({ id:'weapon', packages:Object.freeze([pkg('w0','weapon',{ATKP:1}),pkg('w1','weapon',{ATKP:4}),pkg('w2','weapon',{CDMG:8}),pkg('w3','weapon',{SRW:3})]) }),
    Object.freeze({ id:'armor', packages:Object.freeze([pkg('a0','armor',{ATKP:2}),pkg('a1','armor',{CDMG:12}),pkg('a2','armor',{SRW:5}),pkg('a3','armor',{PHYS_PIERCE:4})]) }),
    Object.freeze({ id:'special', packages:Object.freeze([pkg('s0','special',{ATKP:3}),pkg('s1','special',{CDMG:6}),pkg('s2','special',{SRW:7}),pkg('s3','special',{PHYS_PIERCE:6})]) })
  ])
});
const commonOptions = { registry, evaluator, kernel:context.window.ToramCalculationKernel.evaluateContext, disablePareto:true };
const prepared = optimizer.prepareProblem(problem, commonOptions);
const oracle = optimizer.exhaustiveSearch(prepared, Object.assign({}, commonOptions, { prepared:true }));
const single = optimizer.optimize(prepared, Object.assign({}, commonOptions, { prepared:true }));
assert.equal(single.status, 'exact', 'P0 기준 fixture는 단일 solver가 exact를 증명해야 합니다.');
assert.equal(single.score, oracle.score, 'P0 기준 fixture의 단일 solver는 oracle 점수와 같아야 합니다.');

const plan = optimizer.createParallelShardPlan(prepared, Object.assign({}, commonOptions, { prepared:true, targetShards:8 }));
assert.equal(plan.schema, optimizer.parallelShardSchema, '병렬 plan은 고정된 schema를 가져야 합니다.');
assert.equal(plan.status, 'ready', '유효한 문제는 병렬 shard 계획을 생성해야 합니다.');
assert.equal(plan.shards.length, 8, '분할 가능한 fixture는 요청한 shard 수까지 결정적으로 분할해야 합니다.');
assert.equal(plan.totalCombinations, oracle.evaluations, 'shard 예상 조합 수의 합은 원래 exhaustive 조합 수와 같아야 합니다.');
const audit = optimizer.verifyParallelShardPlan(plan, { maxCompletions:1000 });
assert.equal(audit.complete, true, '작은 fixture는 shard 완전성 감사를 끝까지 수행해야 합니다.');
assert.equal(audit.valid, true, 'shard는 겹치지 않고 원래 조합 공간을 모두 포함해야 합니다.');
assert.equal(audit.coveredCompletions, oracle.evaluations, 'shard 감사의 완성 조합 수는 oracle과 같아야 합니다.');
assert.equal(audit.duplicateCompletions, 0, '서로 다른 shard가 같은 완성 조합을 포함하면 안 됩니다.');
assert.equal(audit.missingCompletions, 0, '어떤 완성 조합도 shard 밖으로 빠지면 안 됩니다.');

const shardResults = plan.shards.map(shard => ({
  shardId:shard.id,
  result:optimizer.optimize(optimizer.createParallelShardProblem(plan, shard), Object.assign({}, commonOptions, { prepared:true }))
}));
assert.ok(shardResults.every(entry => entry.result.status === 'exact'), '작은 shard는 각각 exact로 완료해야 합니다.');
const merged = optimizer.mergeParallelShardResults(plan, shardResults);
assert.equal(merged.status, 'exact', '모든 exact shard의 병합도 exact여야 합니다.');
assert.equal(merged.score, oracle.score, '병합 점수는 단일 oracle과 같아야 합니다.');
assert.equal(merged.bestBuild.id, oracle.bestBuild.id, '병합은 기존 사전식 동점 build ID를 보존해야 합니다.');
assert.equal(merged.unresolvedShardCount, 0, '완료 shard 병합에는 미해결 shard가 없어야 합니다.');

const partial = optimizer.mergeParallelShardResults(plan, shardResults.slice(0, 1));
assert.notEqual(partial.status, 'exact', '실행하지 않은 feasible shard가 남아 있으면 exact를 선언하면 안 됩니다.');
assert.ok(partial.unresolvedShardCount > 0, '부분 병합은 미해결 shard 수를 반환해야 합니다.');

const permutedPrepared = Object.freeze(Object.assign({}, prepared, {
  groups:Object.freeze(prepared.groups.map(group => Object.freeze(Object.assign({}, group, { packages:Object.freeze([...group.packages].reverse()) }))))
}));
const permutedPlan = optimizer.createParallelShardPlan(permutedPrepared, Object.assign({}, commonOptions, { prepared:true, targetShards:8 }));
assert.deepEqual(permutedPlan.shards.map(shard => [shard.id, shard.estimatedCombinations]), plan.shards.map(shard => [shard.id, shard.estimatedCombinations]), 'package 입력 순서를 바꿔도 shard 경계와 조합 수는 같아야 합니다.');

console.log(`D4 parallel shard P0: PASS (${plan.shards.length} shards, ${plan.totalCombinations} completions, exact ${merged.score})`);
