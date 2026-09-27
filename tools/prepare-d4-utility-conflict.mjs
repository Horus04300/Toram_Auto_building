import assert from 'node:assert/strict';
import {readFile,writeFile,mkdir} from 'node:fs/promises';
import {createRequire} from 'node:module';
import {createHash} from 'node:crypto';
import {resolve} from 'node:path';
import vm from 'node:vm';
const root=resolve(import.meta.dirname,'..'),require=createRequire(import.meta.url);
const registry=require('../assets/js/stat-registry.js'),evaluator=require('../assets/js/build-evaluator.js');
const compiler=require('../assets/js/d4-problem-compiler.js'),optimizer=require('../assets/js/d4-global-optimizer.js');
const spec=JSON.parse(await readFile(resolve(root,'tools/fixtures/d4-synthetic-utility-conflict.json'),'utf8'));
const base=spec.baseContext, context={window:{ToramStatRegistry:registry},console};context.window.window=context.window;
vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};',context);
for(const file of ['calculation-policies.js','calculator.js'])vm.runInContext(await readFile(resolve(root,'assets/js',file),'utf8'),context);
const kernel=context.window.ToramCalculationKernel.evaluateContext;
const empty={maxHp:null,maxMp:null,amprBeforeDual:null,normalAttackCrit:null,aspd:null};
const scenario=requirements=>evaluator.createScenarioSnapshot(base,{requirements});
const evaluate=(stats,s=scenario(empty))=>evaluator.evaluateAggregate(base,s,stats,kernel);
const utility=r=>({maxMp:r.utility.maxMpBeforeBuff,amprBeforeDual:r.utility.amprBeforeDual,normalAttackCrit:r.offense.normalAttackCrit,aspd:r.utility.aspd});
const categories=['무기','방어구','추가','특수'];
const name=(g,r,i)=>`SYN-${g}-${r}-${i}`;
const crystas=categories.flatMap((category,g)=>spec.roles.flatMap(({key,unit},r)=>Array.from({length:spec.variantsPerRole},(_,i)=>({name:name(g,r,i),category,stats:{[key]:unit*(i+2),ATKP:18-i,CDMG:(i*7+g*3+r*5)%17,SRW:(i+g+r)%3}}))));
const witnessNames=categories.map((_,g)=>[name(g,g,3),name(g,(g+1)%4,3)]);
const witnessStats={};for(const n of witnessNames.flat())for(const [k,v] of Object.entries(crystas.find(c=>c.name===n).stats))witnessStats[k]=(witnessStats[k]||0)+v;
const baseline=utility(evaluate({})),witness=utility(evaluate(witnessStats));
const scenarios=Object.fromEntries(Object.entries(spec.requirementFractions).map(([key,f])=>[key,scenario({...empty,...Object.fromEntries(Object.keys(baseline).map(k=>[k,Math.floor(baseline[k]+f*(witness[k]-baseline[k]))]))})]));
// Prepare once with all four utility coordinates active. Only requirements vary below.
const compiled=compiler.compileCrystaProblem({crystas,registry,baseContext:base,scenarioSnapshot:scenarios.tight,currentCrystas:[],locks:[]});
assert.deepEqual(compiled.diagnostics,[]);
const relevantKeys=optimizer.deriveRelevantKeys(compiled,registry,stats=>evaluate(stats,scenarios.tight));
const prepared=optimizer.prepareProblem(compiled,{registry,relevantKeys,evaluateStats:(stats,meta)=>meta?.summaryOnly?evaluator.evaluateAggregateSummary(base,scenarios.tight,stats,kernel):evaluate(stats,scenarios.tight),pareto:{maxComparisons:1000000}});
assert.ok(prepared.metadata.paretoReports.every(r=>r.complete));
const witnessPackages=prepared.groups.map((g,i)=>g.packages.find(p=>witnessNames[i].every(n=>p.candidateNames.includes(n))));
assert.ok(witnessPackages.every(Boolean),'known feasible witness must survive preparation');
const smallGroups=prepared.groups.map((g,i)=>{const chosen=new Map([[witnessPackages[i].id,witnessPackages[i]]]);for(let j=0;chosen.size<8;j++){const p=g.packages[Math.floor(j*g.packages.length/8)];assert.ok(p);chosen.set(p.id,p);}return {...g,packages:[...chosen.values()]};});
const dir=resolve(root,'src-tauri/target/regression-audit');await mkdir(dir,{recursive:true});
const report={spec,baseline,witness,witnessNames,crystaCount:crystas.length,packages:prepared.groups.map(g=>g.packages.length),groupsHash:createHash('sha256').update(JSON.stringify(prepared.groups)).digest('hex'),variants:[]};
for(const [level,s] of Object.entries(scenarios)){
 assert.ok(evaluate(witnessStats,s).constraints.feasible);
 const problem={...prepared,scenarioSnapshot:s};
 const small={...problem,groups:smallGroups};let feasible=0,total=0;
 const oracle=optimizer.exhaustiveSearch(small,{prepared:small,evaluateStats:stats=>{const r=evaluate(stats,s);total++;if(r.constraints.feasible)feasible++;return r;}});
 assert.equal(total,8**4);assert.ok(feasible>0);
 const auditOracle={score:oracle.score,id:oracle.bestBuild.id};
 const boundCheck=optimizer.verifyCandidateTreeUpperBounds(small,{prepared:small,registry,evaluateStats:stats=>evaluate(stats,s)});
 const monotonicity=optimizer.verifyEnvelopeMonotonicity(small,{prepared:small,registry,evaluateStats:stats=>evaluate(stats,s)});
 assert.deepEqual(boundCheck.violations,[]);assert.deepEqual(monotonicity.violations,[]);
 await writeFile(resolve(dir,`utility-${level}.json`),JSON.stringify(problem));
 await writeFile(resolve(dir,`utility-${level}-oracle.json`),JSON.stringify({...small,auditOracle}));
 report.variants.push({level,requirements:s.requirements,small:{total,feasible,...auditOracle},boundCheck,monotonicity});
}
await writeFile(resolve(root,'docs/verification/d4-utility-conflict-inputs.json'),JSON.stringify(report,null,2)+'\n');
if(process.argv[2]==='verify'){
 const results=JSON.parse(await readFile(resolve(root,'src-tauri/target/slow-profile/utility-complete.json'),'utf8'));
 for(const run of results.runs){
  const level=run.fixture.slice('utility-'.length);
  const selected=prepared.groups.map((g,i)=>g.packages.find(p=>p.id===run.result.bestBuild.packageIds[i]));
  assert.ok(selected.every(Boolean));assert.equal(selected.map(p=>p.id).join('||'),run.result.bestBuild.id);
  const stats=selected.reduce((s,p)=>optimizer.addStats(s,p.statDelta),{});
  const outcome=evaluate(stats,scenarios[level]);assert.ok(outcome.constraints.feasible);assert.equal(outcome.damage.expected,run.result.score);
 }
 console.log(`Final JS reevaluation: PASS (${results.runs.length} complete runs)`);
}
console.log(JSON.stringify(report,null,2));
