import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { spawnSync } from 'node:child_process';
import vm from 'node:vm';
const root = new URL('../../..', import.meta.url);
const read = path => readFile(new URL(path, root), 'utf8');
const context = { window:null, console };
context.window = context;
vm.createContext(context);
vm.runInContext((await read('web/src/ui/crysta-ui.js')).match(/const BASE_ASPD_MAP = \{[^}]+\};/)[0],context);
for (const name of ['calculation/stat-registry','calculation/calculation-policies','calculation/calculator']) vm.runInContext(await read(`web/src/${name}.js`),context);
const math = context.ToramExactMath;
for (const [a,p,expected] of [[25,16,29],[50,14,57],[45,40,63],[-25,16,-29],[25,16.48,29],[25,15.999999999999,28]]) {
  assert.equal(math.percent(a,p),expected,`${a} + ${p}%`);
}
for (const [v,n,d,f,expected] of [[100,0.29,1,0,29],[25,1.16,1,0,29],[25,1.1648,1,0,29],
  [28.99999999999999,1,1,0,28],[-25,1.1648,1,0,-30],[25,116,100,0.12,29],
  [1e30,1e30,1e60,0,1],[1e-100,1e100,1,0,1]]) assert.equal(math.ratio(v,n,d,f),expected);
// Independent integral numerator/denominator oracle, including negative floors.
for(let a=-150;a<=150;a++)for(let p=-99;p<=150;p++) {
  const numerator=BigInt(a)*BigInt(100+p), denominator=100n;
  const expected=Number(numerator/denominator-(numerator%denominator<0n?1n:0n));
  assert.equal(math.percent(a,p),expected);
}
const fixture=JSON.parse(await read('tools/fixtures/crysta-synthetic-utility-conflict.json'));
const base={...fixture.baseContext,level:1,bossLevel:1,mainType:'한손검',wpnAtk:24,wpnRefine:0,wpnStab:100,
  strBase:0,intBase:0,vitBase:0,agiBase:0,dexBase:0,bossDef:0,bossMdef:0,bossCritResist:0,
  noCritical:true,skillMult:1,skillConst:0,damageP:0,atkP:0};
const cases=[
  {id:'atk-percent-boundary',baseContext:{...base,atkP:16},stats:{},expected:29},
  {id:'damage-percent-boundary',baseContext:{...base,damageP:16},stats:{},expected:29},
  {id:'decimal-skill-boundary',baseContext:{...base,skillMult:1.16},stats:{},expected:29},
  {id:'decimal-skill-fraction',baseContext:{...base,skillMult:1.1648},stats:{},expected:29},
  {id:'real-near-boundary',baseContext:{...base,skillMult:1.1599999999999},stats:{},expected:28},
  {id:'fractional-option',baseContext:{...base,atkP:16.48},stats:{},expected:29},
  {id:'50-plus-14',baseContext:{...base,wpnAtk:49,atkP:14},stats:{},expected:57},
  // ATK=floor((1965+1160+325)*95/100)+20=3297; MATK=floor(1255*112/100)+50=1455.
  // raw=floor(4752*92/100)=4371; magic CDMG=100+170*70/100=219, not 218.
  // floor(4371*219/100)=9572; every remaining damage multiplier is 1.
  {id:'magic-cdmg-integral-reflection',baseContext:{...base,level:325,bossLevel:325,wpnAtk:600,wpnRefine:15,
    wpnStab:80,subType:'마도구',strBase:400,intBase:250,agiBase:80,dexBase:180,atkType:'MAG',attackPowerMode:'sum',
    bossMagResist:8,spellBurstLevel:8,targetWeakened:true,dualBringerActive:true,dualBringerLevel:10,ignoreMdef:true,
    criticalChanceMultiplier:1.1,noCritical:false,atkP:10,atkF:20,matkP:12,matkF:50,critF:280,cdmgF:40},stats:{},expected:9572}
];
for(const item of cases) {
  const result=context.ToramCalculationKernel.evaluateContext(item.baseContext,[]);
  assert.equal(result.optimizationDamageFactor,item.expected,item.id);
}
const native=spawnSync('cargo',['run','--offline','--quiet','--manifest-path','desktop/Cargo.toml','--bin','crysta_native_summary'],{
  cwd:new URL('../../..',import.meta.url), input:JSON.stringify({cases}),encoding:'utf8',maxBuffer:4*1024*1024
});
assert.equal(native.status,0,native.stderr);
const results=JSON.parse(native.stdout);
for(const item of cases) {
  const row=results.results.find(r=>r.id===item.id);
  assert.equal(row.summary.optimizationDamageFactor,item.expected,item.id);
}
console.log('Decimal integer-ratio floors: PASS (75250 integer oracles, decimal/negative/overflow boundaries, JS/Rust actual damage)');
