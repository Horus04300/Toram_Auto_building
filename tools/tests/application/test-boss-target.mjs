import assert from 'node:assert/strict';
import { createBossSelection, resolveBossTarget, validateBossSelection } from '../../../web/src/application/boss-target.mjs';

const sha = 'a'.repeat(64);
function boss(kind = 'field-boss') {
  const variant = { key:'10:1',gameMonsterId:540,fieldId:10,masterId:1,fieldName:'지역',classification:kind,
    entry:{model:({'field-boss':'single','entry-boss':'difficulty-select','high-raid-boss':'level-select','guild-raid-boss':'level-select',unresolved:'unresolved'})[kind]},
    baseStats:{level:195,maxHp:3949200,def:429,mdef:390,necessaryHit:584,cutAttack:7,cutMagicAttack:8,guard:6,avoid:2,elementRaw:2,expDefNormal:20,expDefSkill:30,expDefMagic:30},
    parts:[],partStats:[],properties:[],sourceSha256:sha,rawRecordSha256:sha };
  if (kind === 'high-raid-boss') variant.entry.levelParameters = {baseLevel:290,minLevel:290};
  if (kind === 'guild-raid-boss') { variant.entry.levelParameters = {baseLevel:40,minLevel:40,maxLevel:1020,step:4}; variant.entry.actor='male'; }
  return {gameMonsterId:540,revision:sha,name:'보스',variants:[variant]};
}
function select(value) { return createBossSelection(value,value.variants[0]); }
let input = boss(), selection = select(input);
assert.deepEqual(resolveBossTarget(selection).target,{bossLevel:195,bossDef:429,bossMdef:390,bossPhysResist:7,bossMagResist:8,bossCritResist:0});
input = boss('entry-boss');
input.variants[0].baseStats.def = 9; input.variants[0].baseStats.mdef = 21;
input.variants[0].parts = [{partId:1,value:10000}];
input.variants[0].partStats = [{partId:1,masterId:10000,sourceSha256:sha,stats:{def:9,mdef:19,cutAttack:99,cutMagicAttack:99},properties:[{uid:2,typeRaw:8,values:[5,6,0,0,0]}]}];
input.variants[0].properties = [{uid:9,typeRaw:6,values:[30,0,0,0,0]},{uid:1,typeRaw:6,values:[90,0,0,0,0]}];
selection = {...select(input),difficulty:-1};
assert.deepEqual(resolveBossTarget(selection).target,{bossLevel:185,bossDef:0,bossMdef:3,bossPhysResist:12,bossMagResist:14,bossCritResist:30}, 'Scale and truncate each unbroken part separately; type8 body correction is distinct from raw part cut and source order controls crit.');
selection.difficulty = 3;
assert.equal(resolveBossTarget(selection).target.bossDef,108);
assert.equal(resolveBossTarget(selection).target.bossMdef,240);
selection.variant.partStats[0].stats = null;
assert.equal(resolveBossTarget(selection).target.bossDef,null,'A missing part must preserve manual values, not silently remove its contribution.');
input = boss('high-raid-boss');
Object.assign(input.variants[0].baseStats,{level:290,maxHp:380,def:600,mdef:600,necessaryHit:175,cutAttack:14,cutMagicAttack:14});
selection = select(input);
assert.deepEqual(resolveBossTarget(selection).target,{bossLevel:290,bossDef:1740,bossMdef:1740,bossPhysResist:25,bossMagResist:25,bossCritResist:0});
assert.ok(resolveBossTarget(selection).details.some(([label,value])=>label==='본체 HP' && value===11909278));
assert.ok(resolveBossTarget(selection).details.some(([label,value])=>label==='본체 필요 명중' && value===761));
selection.level = 325; selection.variant.baseStats.maxHp=280;
assert.equal(resolveBossTarget(selection).target.bossDef,1950);
assert.equal(resolveBossTarget(selection).target.bossPhysResist,27);
assert.ok(resolveBossTarget(selection).details.some(([label,value])=>label==='본체 HP' && value===11659309));
selection.variant.properties = [{uid:1,typeRaw:32,values:[63,0,0,0,0]}];
assert.equal(resolveBossTarget(selection).target.bossDef,600);
assert.equal(resolveBossTarget(selection).target.bossPhysResist,14);
assert.ok(resolveBossTarget(selection).details.some(([label,value])=>label==='본체 HP' && value===280));
selection.variant.properties = [{uid:9,typeRaw:32,values:[4,0,0,0,0]},{uid:1,typeRaw:32,values:[8,0,0,0,0]}];
assert.equal(resolveBossTarget(selection).target.bossDef,600);
assert.equal(resolveBossTarget(selection).target.bossMdef,1950,'Use the first exception record; do not OR records or sort by UID.');
selection.variant.parts = [{partId:1,value:10000}];
selection.variant.partStats = [{partId:1,masterId:10000,sourceSha256:sha,stats:{def:125,mdef:50,cutAttack:99,cutMagicAttack:99},properties:[{uid:1,typeRaw:32,values:[4,0,0,0,0]},{uid:2,typeRaw:8,values:[3,5,0,0,0]}]}];
assert.equal(resolveBossTarget(selection).target.bossDef,725,'HighRaid part uses its own fixed-stat mask.');
assert.equal(resolveBossTarget(selection).target.bossMdef,2112,'HighRaid part scales and truncates before summation.');
assert.equal(resolveBossTarget(selection).target.bossMagResist,32,'Only body-cut corrections contribute from parts.');
assert.throws(()=>validateBossSelection({...selection,level:289}));
assert.throws(()=>validateBossSelection({...selection,level:32768}));
assert.throws(()=>validateBossSelection({...selection,difficulty:4}));
assert.throws(()=>validateBossSelection({...selection,revision:'../bad'}));
input=boss('unresolved');
assert.ok(Object.values(resolveBossTarget(select(input)).target).every(value=>value===null));
input=boss('guild-raid-boss');
Object.assign(input.variants[0].baseStats,{def:175,mdef:350,cutAttack:15,cutMagicAttack:30});
input.variants[0].properties=[{uid:3,typeRaw:6,values:[10,0,0,0,0]}];
selection=select(input);
assert.deepEqual(resolveBossTarget(selection).target,{bossLevel:40,bossDef:70,bossMdef:140,bossPhysResist:19,bossMagResist:34,bossCritResist:10});
assert.match(resolveBossTarget(selection).details.find(([label])=>label==='본체 HP')[1],/게이지 0~10/);
for (const [level,def,mdef,phys,magic,hp] of [[44,77,154,19,34,1640072],[100,175,350,25,40,9780750],[104,182,364,25,40,10756951],[200,350,700,35,50,63551250]]) {
  selection.level=level;
  assert.deepEqual(resolveBossTarget(selection).target,{bossLevel:level,bossDef:def,bossMdef:mdef,bossPhysResist:phys,bossMagResist:magic,bossCritResist:10});
  assert.equal(resolveBossTarget(selection).details.find(([label])=>label==='본체 HP')[1],hp);
}
selection.variant.baseStats.def=300; selection.variant.baseStats.mdef=125;
selection.variant.baseStats.cutAttack=30; selection.variant.baseStats.cutMagicAttack=15;
selection.variant.entry.actor='female';
assert.deepEqual(resolveBossTarget(selection).target,{bossLevel:200,bossDef:600,bossMdef:250,bossPhysResist:50,bossMagResist:35,bossCritResist:10});
selection.level=900; selection.variant.baseStats.def=13;
assert.equal(resolveBossTarget(selection).target.bossDef,117,'Guild integer multiplication then f32 percent differs from HighRaid (116).');
assert.match(resolveBossTarget(selection).details.find(([label])=>label==='본체 HP')[1],/int32/);
for (const level of [39,41,1024]) assert.throws(()=>validateBossSelection({...selection,level}));
console.log('Boss target: PASS (field, difficulty/parts, HighRaid, guild actors/level/HP/precision, missing sources and validation).');
