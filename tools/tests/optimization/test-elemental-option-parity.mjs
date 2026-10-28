import {statRegistry} from '../../../web/src/calculation/stat-registry.js';
import {candidatePreparation} from '../../../web/src/optimization/candidate-preparation.js';
import {calculationKernel,ToramExactMath,applyAttackProfileToContext} from '../../../web/src/calculation/calculator.js';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {spawn} from 'node:child_process';
import {resolve} from 'node:path';

const root = resolve(import.meta.dirname, '../../..');
const context = { console };
context.window = context;
const fixture = JSON.parse(await readFile(resolve(root, 'tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json'), 'utf8'));
const saved = fixture.resolvedExecutionContext.baseContext;
function base(overrides={}) {
  return { ...saved, mainType:'한손검',subType:'없음',atkType:'PHYS',attackPowerMode:'default',attackElement:'none',
    strBase:111,intBase:444,vitBase:555,agiBase:333,dexBase:222,strP:0,strF:0,intP:0,intF:0,vitP:0,vitF:0,agiP:0,agiF:0,dexP:0,dexF:0,
    activeBuildConversions:[],skillStats:[],procDamageModifiers:[],damageMultiplierLayers:null,skillMult:1,skillConst:0,weaponElement:0,subWeaponElement:0,targetElement:0,
    fireDmg:0,waterDmg:0,windDmg:0,earthDmg:0,lightDmg:0,darkDmg:0,neutralDmg:0,
    atkUpSTR:0,atkUpINT:0,atkUpVIT:0,atkUpAGI:0,atkUpDEX:0,matkUpSTR:0,matkUpINT:0,matkUpVIT:0,matkUpAGI:0,matkUpDEX:0,
    elementAwakening:false,magicElement:false,elemP:0,elemDmg:0,elemDmgP:0,atkP:0,matkP:0, ...overrides };
}
const evaluate = (input, stats={}) => calculationKernel.evaluateContext(input,[{stats}],false);
const cases = [];
function add(id, input, stats={}) {
  const expected=evaluate(input,stats);
  assert.ok(Number.isFinite(expected.optimizationDamageFactor),id);
  cases.push({id,baseContext:input,stats,expected});
  return expected;
}
const elements=['FIRE','WATER','WIND','EARTH','LIGHT','DARK','NEUTRAL'];
for(const atkType of ['PHYS','MAG']) for(let target=0;target<=7;target++) {
  const input=base({atkType,targetElement:target});
  const stats=Object.fromEntries(elements.map((element,index)=>[element+'_DMG',index%2?-13:17]));
  const output=add(`${atkType}:target:${target}`,input,stats);
  const bonus=target?stats[elements[target-1]+'_DMG']:0;
  assert.equal(output.ctx.elemP,bonus,'Only the target-matching element option applies');
  assert.equal(output.optimizationDamageFactor,evaluate(input,{ELEM_P:bonus}).optimizationDamageFactor);
  const relevant=candidatePreparation.deriveRelevantKeys({baseContext:input,groups:[{packages:[{statDelta:stats}]}]},statRegistry,()=>({utility:{}}));
  assert.deepEqual(Array.from(relevant),target?[elements[target-1]+'_DMG']:[]);
}
for(let weapon=1;weapon<=8;weapon++) for(let target=0;target<=7;target++) {
  const weakness=[0,4,1,2,3,6,5][weapon];
  for(const [mainType,atkType] of [['한손검','PHYS'],['지팡이','MAG'],['마도구','MAG']]) {
    const input=base({mainType,atkType,weaponElement:weapon,targetElement:target});
    const result=add(`${mainType}:${weapon}:${target}`,input);
    const expected=(weakness&&weakness===target?25:0)+(atkType==='MAG'&&weapon!==7?44:0);
    assert.equal(result.ctx.elemP,expected);
  }
}
for(const mainType of ['활','자동활','한손검']) for(const subType of ['화살','마도구']) {
  const input=base({mainType,subType,weaponElement:1,subWeaponElement:2,targetElement:1});
  assert.equal(add(`arrow:${mainType}:${subType}`,input).ctx.elemP,(mainType==='활'||mainType==='자동활')&&subType==='화살'?25:0);
}
for(const sign of [-1,1]) {
  const input=base({strBase:3,intBase:3,vitBase:0,agiBase:0,dexBase:0});
  const stats={ATK_UP_STR:sign*25,ATK_UP_INT:sign*25,MATK_UP_STR:sign*25,MATK_UP_INT:sign*25};
  const result=add(`reflection:${sign}`,input,stats), without=evaluate(input);
  assert.equal(result.finalATK-without.finalATK,sign);
  assert.equal(result.finalMATK-without.finalMATK,sign);
}
const published=Math.fround(27*Math.fround(.1));
for(const attribute of [1,3,999,1000,10001,65535]) for(let raw=-32768;raw<=32767;raw++) {
  const displayed=Math.fround(raw*Math.fround(.1));
  const expected=Math.trunc(Math.fround(Math.fround(raw/1000)*Math.fround(attribute)))||0;
  assert.equal(ToramExactMath.proportionalAttack({strBase:attribute,atkUpSTR:displayed},'atk'),expected,`native raw ${raw}, attribute ${attribute}`);
}
for(let raw=-32768;raw<=32767;raw++) {
  const displayed=Math.fround(raw*Math.fround(.1));
  const opposite=Math.fround(-raw*Math.fround(.1));
  assert.equal(ToramExactMath.proportionalAttack({strBase:12345,intBase:12345,atkUpSTR:displayed,atkUpINT:opposite},'atk'),0);
  const aggregate=statRegistry.normalizeValue('ATK_UP_STR',displayed)+statRegistry.normalizeValue('ATK_UP_STR',Math.fround((-raw+1)*Math.fround(.1)));
  assert.equal(ToramExactMath.proportionalAttack({strBase:2999,atkUpSTR:aggregate},'atk'),2);
}
const rawSources=[32767,-32768].map(raw=>Math.fround(raw*Math.fround(.1)));
const normalized=rawSources.reduce((sum,value)=>sum+statRegistry.normalizeValue('ATK_UP_STR',value),0);
assert.equal(ToramExactMath.proportionalAttack({strBase:2999,atkUpSTR:normalized},'atk'),-2);
const cancellationBase=base({strBase:2999});
const cancellation=evaluate(cancellationBase,{});
const fromSources=calculationKernel.evaluateContext(cancellationBase,rawSources.map(value=>({stats:{ATK_UP_STR:value}})),false);
assert.equal(fromSources.finalATK-cancellation.finalATK,-2);
add('reflection:normalized-cancellation',base({strBase:2999}),{ATK_UP_STR:normalized});
add('reflection:published-f32',base({strBase:10000,atkUpSTR:published,matkUpSTR:published}));
add('reflection:mixed',base({atkUpSTR:1,atkUpINT:4,atkUpVIT:5,atkUpAGI:3,atkUpDEX:2}),{
  ATK_UP_STR:12.5,ATK_UP_INT:200,ATK_UP_VIT:.1,ATK_UP_AGI:-50,ATK_UP_DEX:25
});
for(const attackElement of ['fire','water','wind','earth','light','dark','neutral','mana','weakness']) for(const atkType of ['PHYS','MAG']) {
  for(const mainType of ['한손검','지팡이']) for(const targetElement of [1,4,5,6,7]) {
    add(`fixed:${attackElement}:${atkType}:${mainType}:${targetElement}`,base({attackElement,atkType,mainType,targetElement,weaponElement:2}));
  }
}
const adapted={};applyAttackProfileToContext(adapted,{hitProfile:{flags:{element:'none'}}});assert.equal(adapted.attackElement,'neutral');
for(const targetElement of [0,1,2,3,4,5,6,7]) for(const atkType of ['PHYS','MAG']) for(const mainType of ['한손검','지팡이']) {
  const output=add(`advantage:${targetElement}:${atkType}:${mainType}`,base({attackElement:'targetAdvantage',targetElement,atkType,mainType,weaponElement:1}));
  assert.equal(output.ctx.elemP,targetElement>=1&&targetElement<=6?25+(atkType==='MAG'?44:0):0);
}
add('json:roundtrip-1.3499999999999999',base({weaponElement:1,targetElement:4,damageMultiplierLayers:saved.damageMultiplierLayers,skillMult:saved.skillMult,skillConst:saved.skillConst}));
for(const [key,unit] of Object.entries({METEOR_RES:'percent',SUCTION_RES:'percent',PET_EXP:'percent',GEM_DUST_DROP:'percent',HELP_INVINCIBILITY:'seconds',STOP_FLINCH:'boolean'})) {
  assert.equal(statRegistry.get(key).status,'notModeled');
  assert.equal(statRegistry.get(key).unit,unit);
  const result={};statRegistry.apply(result,key,3);assert.equal(result.preservedStats[key],3);
}
const response=await new Promise((resolvePromise,reject)=>{
  const child=spawn('cargo',['run','--quiet','--manifest-path','engine/Cargo.toml','--bin','crysta_native_summary'],{cwd:root,stdio:['pipe','pipe','pipe']});
  let stdout='',stderr='';child.stdout.on('data',chunk=>stdout+=chunk);child.stderr.on('data',chunk=>stderr+=chunk);
  child.stdin.on('error',()=>{}); // Report cargo's compiler error from close.
  child.on('error',reject);child.on('close',code=>{if(code)return reject(new Error(stderr));try{resolvePromise(JSON.parse(stdout));}catch(error){reject(error);}});
  child.stdin.end(JSON.stringify({cases:cases.map(({expected,...input})=>input)}));
});
assert.equal(response.results.length,cases.length);
for(const result of response.results) {
  const expected=cases.find(input=>input.id===result.id).expected;
  for(const key of ['optimizationDamageFactor','finalMaxHP','finalMaxMP','amprBeforeDual','normalAttackCrit','finalASPD'])assert.equal(result.summary[key],expected[key],`${result.id}:${key}`);
}
console.log(`Elemental options and native proportional attack: PASS (${cases.length} JS/Rust cases)`);
