import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { loadHeadlessEnvironment, root } from '../../support/crysta-headless-environment.mjs';

const env = await loadHeadlessEnvironment({ invoke() { throw new Error('No native calls in projection oracle'); } });
const { optimizer, registry, evaluator, kernel } = env;
const fixture = JSON.parse(await readFile(resolve(root, 'tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json'), 'utf8'));
const ctx = { ...fixture.resolvedExecutionContext.baseContext, strBase:500, dexBase:200, agiBase:100, intBase:100, vitBase:50, crtBase:0,
  mainType:'한손검', subType:'없음', armorType:'일반옷', wpnAtk:300, baseWpnAtkF:0,
  strP:0, strF:0, dexP:0, dexF:0, agiP:0, agiF:0, intP:0, intF:0, vitP:0, vitF:0,
  atkF:0, maxHpF:20000, maxMpF:2200, amprF:150,
  activeBuildConversions:[], skillStats:[], critP:0, critF:100, bossCritResist:0,
  normalAttackAmprProfile:{passive:[],activeCandidates:[]} };
const keys = optimizer.modeledKeys(registry);
const requirements = { maxHp:10000, maxMp:2000, amprBeforeDual:100, normalAttackCrit:100, aspd:1000 };
const plain = value => JSON.parse(JSON.stringify(value));
let cases = 0, completions = 0, removedChecked = 0;
function problem(context, choices, goals=requirements) {
  return { baseContext:context, scenarioSnapshot:evaluator.createScenarioSnapshot(context, {requirements:goals}), metadata:{},
    groups:['weapon','armor','additional','special'].map((id, index) => ({id,packages:(choices[index] || [{}]).map((stats,i) => ({
      id:`${id}:${String.fromCharCode(97+i)}`,slot:id,source:'crysta',structureSignature:'test',sockets:2,
      resourceCost:{sockets:2},conflicts:[],statDelta:stats
    }))})) };
}
function visitOthers(input, omitted, visit) {
  function walk(index, stats) {
    if(index===input.groups.length) { visit(stats); return; }
    if(index===omitted) { walk(index+1,stats); return; }
    for(const candidate of input.groups[index].packages) walk(index+1,optimizer.addStats(stats,candidate.statDelta));
  }
  walk(0,{});
}
function check(input, budget=1000000) {
  const untouched = plain(input);
  const settings = {registry,relevantKeys:keys,pareto:{maxComparisons:budget}};
  const before = optimizer.prepareProblem(input,{...settings,disableCandidateProjection:true});
  const after = optimizer.prepareProblem(input,settings);
  assert.deepEqual(plain(input),untouched,'Projection cannot mutate raw input');
  const evaluate = stats => {
    const outcome=evaluator.evaluateAggregate(input.baseContext,input.scenarioSnapshot,stats,kernel.evaluateContext);
    assert.ok(Number.isFinite(outcome.damage.expected),'Oracle input must produce a finite score');
    return outcome;
  };
  const original = optimizer.exhaustiveSearch(input,{prepared:true,evaluateStats:evaluate});
  const reduced = optimizer.exhaustiveSearch(after,{prepared:true,evaluateStats:evaluate});
  assert.equal(reduced.score,original.score);
  assert.equal(reduced.bestBuild?.id,original.bestBuild?.id,'Projection must preserve the lexical optimum');
  completions += original.evaluations;
  for(const [index, group] of before.groups.entries()) {
    const survivors=after.groups[index].packages;
    for(const candidate of group.packages.filter(p => !survivors.some(s => s.id===p.id))) {
      visitOthers(input,index,remaining => {
        const value=evaluate(optimizer.addStats(remaining,candidate.statDelta));
        if(!value.constraints.feasible)return;
        assert.ok(survivors.some(replacement => {
          if(replacement.id>candidate.id)return false;
          const other=evaluate(optimizer.addStats(remaining,replacement.statDelta));
          return other.constraints.feasible&&other.damage.expected>=value.damage.expected;
        }),JSON.stringify({candidate:candidate.id,stats:candidate.statDelta,score:value.damage.expected,replacements:survivors.map(p => ({id:p.id,stats:p.statDelta,score:evaluate(optimizer.addStats(remaining,p.statDelta)).damage.expected}))}));
        removedChecked++;
      });
    }
    for(const candidate of survivors) {
      const raw=input.groups[index].packages.find(p => p.id===candidate.id);
      assert.equal(candidate.statDelta,raw.statDelta,'Final evaluation keeps the original options');
      if(candidate.searchProjection)assert.ok(Object.isFrozen(candidate.searchProjection));
    }
  }
  const reversed={...input,groups:input.groups.map(group => ({...group,packages:group.packages.toReversed()}))};
  assert.deepEqual(plain(optimizer.prepareProblem(reversed,settings).groups),plain(after.groups));
  cases++;
  return after;
}

const pairs=[['STR','STRP'],['DEX','DEXP'],['AGI','AGIP'],['INT','INTP'],['VIT','VITP'],
  ['CRIT','CRITP'],['WATK','WATKP'],['ATK','ATKP'],['MATK','MATKP'],['CDMG','CDMGP'],
  ['MAXHP','MAXHPP'],['ASPD','ASPD_P'],['CSPD','CSPD_P']];
const bases=kernel.candidateSupplyBases(ctx,{});
for(const [flat,percent] of pairs) {
  const base=[].concat(bases[flat])[0];
  const input=problem(ctx,[[{[percent]:100},{[flat]:base},{[percent]:100}]],{maxHp:null,maxMp:null,amprBeforeDual:null,normalAttackCrit:null,aspd:null});
  const after=check(input);
  assert.equal(after.groups[0].packages.length,1,`${flat} fixed-base equivalents must collapse`);
  assert.equal(after.metadata.candidateProjection.bundles.find(b => b.id===flat).mode,'fixed-base');
}
const fixedStat=check(problem(ctx,[[{STRP:2},{STR:10}], [{CRITP:20},{CRIT:5}]]));
assert.equal(fixedStat.groups[0].packages.length,1);
assert.equal(fixedStat.groups[1].packages.length,1);
const negative=check(problem({...ctx,strBase:-500},[[{STRP:2},{STR:-10}]]));
assert.equal(negative.groups[0].packages.length,1,'Negative base keeps signed supply equivalence');

// Opposing %/+ suppliers change order as another group supplies AGI/STR.
const variable=problem(ctx,[[{ASPD_P:100},{ASPD:1000},{MAXHPP:50},{MAXHP:500}],
  [{AGIP:100},{AGI:200},{STRP:40},{VIT:100}], [{CDMGP:20},{CDMG:40}], [{ATKP:10},{ATK:80}]]);
const variableAfter=check(variable);
for(const input of [variable,problem(ctx,[[{STRP:2},{STR:10}],[{CRITP:20},{CRIT:5}],[{ATKP:5},{ATK:100}]])]) {
  const prepared=optimizer.prepareProblem(input,{registry,relevantKeys:keys});
  const evaluate=stats=>evaluator.evaluateAggregate(input.baseContext,input.scenarioSnapshot,stats,kernel.evaluateContext);
  const oracle=optimizer.exhaustiveSearch(input,{prepared:true,evaluateStats:evaluate});
  const actual=optimizer.optimize(prepared,{prepared:true,registry,relevantKeys:keys,timeLimitMs:30000});
  assert.equal(actual.status,'exact');
  assert.equal(actual.score,oracle.score);
  assert.equal(actual.bestBuild?.id,oracle.bestBuild?.id,'Projected tree preserves lexical optimum');
  const bounds=optimizer.verifyCandidateTreeUpperBounds(prepared,{prepared:true,registry,relevantKeys:keys});
  assert.equal(bounds.violations.length,0,'Projected ordering must preserve raw ancestor upper bounds');
}
for(const id of ['ASPD','MAXHP','CDMG'])assert.equal(variableAfter.metadata.candidateProjection.bundles.find(b => b.id===id).mode,'base-function');
assert.equal(variableAfter.metadata.candidateProjection.bundles.find(b => b.id==='ATK').mode,'raw');
for(const value of [999,1000,1179,1180,10000])check(problem({...ctx,aspdF:value},variable.groups.map(g => g.packages.map(p => p.statDelta)),{...requirements,aspd:value}));
check(variable,1);
const lowestAspd=bases.ASPD;
const intervalDominance=check(problem(ctx,[[{ASPD_P:100},{ASPD:lowestAspd-1}],[{AGIP:0},{AGIP:100}]]));
assert.equal(intervalDominance.groups[0].packages.length,1,'ASPD function dominance holds throughout changing AGI');
const intervalCrossing=check(problem(ctx,[[{ASPD_P:100},{ASPD:lowestAspd+200}],[{AGIP:0},{AGIP:100}]]));
assert.equal(intervalCrossing.groups[0].packages.length,2,'Crossing ASPD suppliers must both survive');

// HP/ASPD tradeoffs can be dominated throughout their base interval without
// changing any damage/stat expression, even though raw coordinates cross.
const hpBase=bases.MAXHP;
const stronger=check(problem(ctx,[[{MAXHPP:100},{MAXHP:hpBase-1}]],{...requirements,maxHp:1}));
assert.equal(stronger.groups[0].packages.length,1);
assert.equal(stronger.groups[0].packages[0].id,'weapon:a');
const cheaper=problem(ctx,[[{MAXHPP:100},{MAXHP:hpBase}]]);
cheaper.groups[0].packages[1].resourceCost={sockets:1};
assert.equal(check(cheaper).groups[0].packages.length,2,'Different slot costs do not merge by new projection');

for(const overrides of [
  {mainType:'양손검'}, {mainType:'활',subType:'화살',rangeType:'LONG'}, {mainType:'자동활'},
  {mainType:'지팡이',atkType:'MAG',spellBurstLevel:10,targetWeakened:true,dualBringerActive:true,subType:'마도구'},
  {mainType:'마도구',atkType:'MAG',attackPowerMode:'higher'}, {mainType:'권갑',conversionLevel:10},
  {mainType:'선풍창'}, {mainType:'발도검',chkIsUnsheathe:true,activeBuildConversions:[{conversion:'unsheatheToAtk',value:1}]},
  {mainType:'一未知武器',armorType:'중량옷'}, {subType:'한손검(듀얼소드)',subAtk:400,subStab:80},
  {bossPhysResist:150,skillMult:-1}, {atkType:'MAG',dualBringerActive:true,criticalChanceMultiplier:-1}
])check(problem({...ctx,...overrides},variable.groups.map(g => g.packages.map(p => p.statDelta))));

for(const [context,stats,id] of [
  [ctx,[{STRP:2},{STR:10.25}],'STR'], [{...ctx,strBase:1e7},[{STRP:2},{STR:200000}],'STR'],
  [{...ctx,strP:0.5},[{STRP:2},{STR:10}],'STR'], [ctx,[{CRITP:1e7},{CRIT:1}],'CRIT']
]) {
  const after=check(problem(context,[stats]));
  assert.equal(after.metadata.candidateProjection.bundles.find(b => b.id===id).mode,'raw');
}
const unsupported=problem({...ctx,activeBuildConversions:[{conversion:'unknown'}]},[[{STRP:2},{STR:10}]]);
assert.equal(optimizer.prepareProblem(unsupported,{registry,relevantKeys:keys}).metadata.candidateProjection,null);
assert.equal(optimizer.prepareProblem(variable,{registry,relevantKeys:keys,evaluateStats:()=>({})}).metadata.candidateProjection,null);
assert.equal(optimizer.prepareProblem(variable,{registry:{entries:()=>registry.entries()},relevantKeys:keys}).metadata.candidateProjection,null);
assert.equal(optimizer.prepareProblem(variable,{registry,relevantKeys:keys,evaluator:{}}).metadata.candidateProjection,null);

let state=18273;
const random=() => { state=(Math.imul(state,1664525)+1013904223)>>>0;return state; };
for(let trial=0;trial<30;trial++) {
  const choices=Array.from({length:4},()=>Array.from({length:3},()=>({
    STRP:random()%11-5,STR:random()%21-10,AGIP:random()%11-5,AGI:random()%21-10,
    CRITP:random()%21,CRIT:random()%11,MAXHPP:random()%41-20,MAXHP:random()%1001,
    ASPD_P:random()%41-20,ASPD:random()%2001-1000,ATKP:random()%21-10,ATK:random()%101-50
  })));
  check(problem({...ctx,atkType:trial%2?'MAG':'PHYS',mainType:trial%2?'지팡이':'한손검'},choices));
}
console.log(`Crysta candidate projection: PASS (${cases} contexts, ${completions} exhaustive completions, ${removedChecked} replacement checks; raw options, ties, intervals, decimal fallback)`);
