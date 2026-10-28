import assert from 'node:assert/strict';
import {readFile,readdir} from 'node:fs/promises';
import {loadSavedBuildEnvironment} from '../../support/saved-build-headless-environment.mjs';
import * as oracle from '../../fixtures/calculation-oracle.mjs';
import {calculationKernel} from '../../../web/src/calculation/calculator.js';
const env=await loadSavedBuildEnvironment(),cases=[];
const clean=v=>JSON.parse(JSON.stringify(v));
let seed=76543;const random=()=>((seed=Math.imul(seed,1664525)+1013904223>>>0)/2**32);
for(const file of (await readdir('samples')).filter(f=>f.endsWith('.json'))) {
 const saved=JSON.parse(await readFile('samples/'+file,'utf8'));
 for(let n=0;n<26;n++) {
  const input=structuredClone(saved);
  if(n){for(const key of Object.keys(input.build.character.attributes))input.build.character.attributes[key]=Math.floor(random()*501);input.build.character.level=1+Math.floor(random()*325);input.scenario.target.bossDef=Math.floor(random()*3001);input.scenario.target.bossMdef=Math.floor(random()*3001);for(const levels of Object.values(input.build.skillLevels))for(const key of Object.keys(levels))levels[key]=Math.floor(random()*11);}
  const snapshot=env.ToramApplication.CreateCalculationSnapshot(input),base=clean(snapshot.baseContext);
  for(const c of snapshot.crystas){if(!c)continue;for(const [k,v] of Object.entries(c.stats||{}))env.applyStat(base,k,parseFloat(v)||0);for(const conditional of c.conditionalStats||[])if(env.ToramCalculationPolicies.matchesCrystaCondition(base,conditional.when))for(const [k,v] of Object.entries(conditional.stats))env.applyStat(base,k,parseFloat(v)||0);}
  cases.push({id:file+':'+n,baseContext:base,expected:clean(oracle.simulateWithCrystas(snapshot.baseContext,snapshot.crystas))});
 }
}
const base=cases[0].baseContext;
for(const mainType of ['한손검','양손검','활','자동활','지팡이','마도구','권갑','선풍창','발도검','맨손'])for(const atkType of ['PHY','MAG'])for(const subType of ['없음','마도구','화살','한손검(듀얼소드)']) {
 const context={...base,mainType,atkType,subType,subAtk:101,subRefine:15,subStab:83,conversionLevel:10};
 cases.push({id:`weapons:${mainType}:${atkType}:${subType}`,baseContext:context,expected:clean(oracle.simulateWithCrystas(context,[]))});
}
const edges=[
 ['fractional-hp',{maxHpF:.75}],['fractional-mp',{maxMpF:.75}],['fractional-crit',{critF:.75}],['fractional-aspd',{aspdF:.75}],
 ['fractional-percent',{strP:16.48,intP:-25.25,dexF:.75,agiBase:25,skillMult:1.1648}],
 ['ampr-ties',{normalAttackAmprProfile:{passive:[{percent:13.7,flat:-2.5,multiplier:1.2}],activeCandidates:[{id:'a!',multiplier:2},{id:'a',multiplier:2}]}}],
 ['proc-poison',{poisonSources:[{source:'test',level:10}],procDamageModifiers:[{source:'proc',chancePercent:33.3,multiplier:1.3,level:4},{source:'proc2',chancePercent:60,multiplier:.8}],additionalTargetResistances:[13,-7,2.5]}],
 ['negative-stability',{stability:-300,skillStats:[{stat:'totalSTR',target:'mult',ratio:.01},{stat:'totalINT',target:'const',ratio:.5}]}],
 ['conversion',{activeBuildConversions:[{conversion:'unsheatheToAtk',value:1.25}],unsheatheP:35.75,unsheatheF:23.5}],
 ['magic-element',{mainType:'지팡이',atkType:'MAG',intBase:327,targetElement:4,weaponElement:1,spellBurstLevel:7,targetWeakened:true,dualBringerActive:true,dualBringerLevel:10}],
 ['guaranteed-no-crit',{chkGuaranteedCrit:true,noCritical:true}],['near-boundary',{atkP:15.999999999999,skillMult:1.1599999999999}],
 ['zero-resistance-cap',{bossLevel:0,bossDef:0,bossMdef:0,bossPhysResist:120,bossMagResist:-20,poisonSources:[{id:'poison'}]}]
];
for(const [id,patch] of edges){const context={...base,...patch};cases.push({id,baseContext:context,expected:clean(oracle.simulateWithCrystas(context,[]))});}

for(const c of cases){
    assert.deepEqual(clean(calculationKernel.evaluateContext(c.baseContext,[])),c.expected,c.id+' full');
    assert.deepEqual(calculationKernel.evaluateContext(c.baseContext,[],true),oracle.calculationKernel.evaluateContext(c.baseContext,[],true),c.id+' summary');
    assert.deepEqual(calculationKernel.candidateSupplyBases(c.baseContext,{}),oracle.calculationKernel.candidateSupplyBases(c.baseContext,{}),c.id+' supply');
}
console.log(`Integrated Rust evaluation: PASS (${cases.length} full+summary+supply comparisons against frozen independent JS oracle)`);
