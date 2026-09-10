import assert from 'node:assert/strict';
import {readFile,writeFile,mkdir} from 'node:fs/promises';
import {createRequire} from 'node:module';
import {resolve} from 'node:path';
import {spawn} from 'node:child_process';
import vm from 'node:vm';
const root=resolve(import.meta.dirname,'..'),require=createRequire(import.meta.url);
const registry=require(resolve(root,'assets/js/stat-registry.js'));
const evaluator=require(resolve(root,'assets/js/build-evaluator.js'));
const compiler=require(resolve(root,'assets/js/d4-problem-compiler.js'));
const optimizer=require(resolve(root,'assets/js/d4-global-optimizer.js'));
const fixtureSource=await readFile(resolve(root,'tools/test-d4-rust-native-parity.mjs'),'utf8');
// Reuse the established neutral fixture and native transport; no product functions are replaced.
const base=vm.runInNewContext('('+fixtureSource.slice(fixtureSource.indexOf('function base('),fixtureSource.indexOf('\nfunction matchesCondition'))+')');
const runNative=eval('('+fixtureSource.slice(fixtureSource.indexOf('function runNative('),fixtureSource.indexOf('\nfunction isDefaultD4Feasible'))+')');
const ctx={window:{ToramStatRegistry:registry},console};ctx.window.window=ctx.window;vm.createContext(ctx);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};',ctx);
for(const name of ['calculation-policies','calculator'])vm.runInContext(await readFile(resolve(root,`assets/js/${name}.js`),'utf8'),ctx);
const kernel=ctx.window.ToramCalculationKernel.evaluateContext;
const dc={};vm.createContext(dc);vm.runInContext((await readFile(resolve(root,'assets/js/data/crysta-data.js'),'utf8'))+';globalThis.items=crystaDataJson;',dc);
const weapons=['한손검','양손검','활','자동활','지팡이','마도구','권갑','선풍창','발도검','맨손','듀얼소드'];
const stats=['str','int','vit','agi','dex'];
// Independently transcribed stat increments from Coryn Club v4.7, retrieved 2026-09-09.
const coefficients={
 '한손검':[[2,0,0,0,2],[0,3,0,0,1]],'양손검':[[3,0,0,0,1],[0,3,0,0,1]],
 '활':[[1,0,0,0,3],[0,3,0,0,1]],'자동활':[[0,0,0,0,4],[0,3,0,0,1]],
 '지팡이':[[3,1,0,0,0],[0,4,0,0,1]],'마도구':[[0,2,0,2,0],[0,4,0,0,1]],
 '권갑':[[0,0,0,2,.5],[0,4,0,0,1]],'선풍창':[[2.5,0,0,1.5,0],[0,2,0,1,1]],
 '발도검':[[1.5,0,0,0,2.5],[0,1.5,0,0,1]],'맨손':[[1,0,0,0,0],[0,3,0,0,1]]
};
const singleOnly=process.argv.includes('--single-slot');
const report={reference:'https://www.coryn.club/stat_calculator_v4_7.js?v=1777279594',coefficientDifferences:[],matrix:[],nativeDifferences:[]};
const nativeCases=[],expected=new Map();
for(const weapon of weapons){
 const neutral=base({mainType:weapon==='듀얼소드'?'한손검':weapon,subType:weapon==='듀얼소드'?'한손검(듀얼소드)':'없음',subAtk:300,subStab:50,bossDef:0,bossMdef:0,strBase:1,intBase:1,vitBase:1,agiBase:1,dexBase:1,critF:0});
 const zero=kernel(neutral,[],false);
 for(const [index,stat] of stats.entries()){
  const probe=kernel({...neutral,[stat+'Base']:101},[],false);
  if(coefficients[weapon])for(const [axis,key] of ['finalATK','finalMATK'].entries()){
   const observed=probe[key]-zero[key],reference=coefficients[weapon][axis][index]*100;
   if(observed!==reference)report.coefficientDifferences.push({weapon,stat,key,delta:100,observed,reference});
  }
  for(const attackType of ['PHYS','MAG']){
   const b={...neutral,[stat+'Base']:500,atkType:attackType};
   const scenario=evaluator.createScenarioSnapshot(b,{requirements:{maxHp:null,maxMp:null,amprBeforeDual:null,normalAttackCrit:null,aspd:null}});
   const problem=compiler.compileCrystaProblem({crystas:dc.items,registry,baseContext:b,scenarioSnapshot:scenario,currentCrystas:Array(8).fill(null),locks:[false,true,true,true,true,true,true,true],banned:{}});
   const opts={registry,evaluator,kernel};
   assert.equal(optimizer.verifyUpperBounds(problem,opts).violations.length,0,`${weapon}/${stat}/${attackType} safe upper bounds`);
   const oracle=optimizer.exhaustiveSearch(problem,opts),solved=optimizer.optimize(problem,opts);
   assert.equal(solved.status,'exact');assert.equal(solved.score,oracle.score);assert.equal(solved.bestBuild.id,oracle.bestBuild.id);
   const full=kernel(b,solved.bestBuild.packages.flatMap(p=>p.evaluatorCandidates),false);
   assert.equal(full.optimizationDamageFactor,solved.score,`${weapon}/${stat}/${attackType} final recomputation`);
   const id=`${weapon}/${stat}/${attackType}`;
   let preview=null;
   if(!singleOnly){
   const fullProblem=compiler.compileCrystaProblem({crystas:dc.items,registry,baseContext:b,scenarioSnapshot:scenario,currentCrystas:Array(8).fill(null),locks:Array(8).fill(false),banned:{}});
   preview=optimizer.findGreedyInitialSolution(fullProblem,{...opts,skipParetoPreparation:true,heuristicCandidateLimit:96,heuristicPasses:2});
   assert.equal(preview.status,'heuristic');
   const previewCheck=kernel(b,preview.bestBuild.packages.flatMap(p=>p.evaluatorCandidates),false);
   assert.equal(previewCheck.optimizationDamageFactor,preview.score,id+' full-pool preview recomputation');
   }
   for(const p of problem.groups[0].packages){
    const cid=String(nativeCases.length);nativeCases.push({id:cid,baseContext:b,stats:p.statDelta});expected.set(cid,kernel(b,[{name:'aggregate',stats:p.statDelta}],true));
   }
   report.matrix.push({id,atk:full.finalATK,matk:full.finalMATK,score:solved.score,recommended:solved.bestBuild.packages[0].candidateNames,rawWeaponCandidates:problem.groups[0].packages.length,fullPreviewScore:preview?.score,fullPreview:preview?.bestBuild.packages.map(p=>p.candidateNames)});
  }
 }
 console.log(`${weapon}: stat probes and 10 exact/oracle/recomputation cases checked`);
}
const native=await runNative(nativeCases);
for(const result of native.results){const js=expected.get(result.id);for(const key of ['optimizationDamageFactor','finalMaxHP','finalMaxMP','amprBeforeDual','normalAttackCrit','finalASPD'])if(result.summary[key]!==js[key])report.nativeDifferences.push({id:result.id,key,js:js[key],native:result.summary[key]});}
report.summary={matrixCases:report.matrix.length,fullPreviewCases:singleOnly?0:report.matrix.length,nativeCases:nativeCases.length,coefficientDifferences:report.coefficientDifferences.length,nativeDifferences:report.nativeDifferences.length,upperBoundCases:report.matrix.length};
await mkdir(resolve(root,'src-tauri/target/weapon-audit'),{recursive:true});await writeFile(resolve(root,'src-tauri/target/weapon-audit',singleOnly?'single-slot-regression.json':'report.json'),JSON.stringify(report,null,2));
console.log(JSON.stringify(report.summary));console.log(JSON.stringify(report.coefficientDifferences));
if(report.coefficientDifferences.length||report.nativeDifferences.length)process.exitCode=1;
