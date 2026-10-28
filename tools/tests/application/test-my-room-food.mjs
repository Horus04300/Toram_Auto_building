import {application} from '../../../web/src/application/application-use-cases.js';
import assert from 'node:assert/strict';
import {createRequire} from 'node:module';
import {readFile} from 'node:fs/promises';
const require = createRequire(import.meta.url);
const food = require('../../../web/src/data/my-room-food.js');
assert.equal(food.recipes.length, 33);
assert.equal(food.recipes.flatMap(r => r.names).length, 39);
assert.deepEqual(food.get('CRIT').values, [2,4,6,8,10,14,18,22,26,30]);
assert.deepEqual(food.get('MAXMP').values, [60,120,180,240,300,440,580,720,860,1000]);
assert.deepEqual(food.get('ELEM_P').values, [1,2,3,4,5,7,9,11,13,15]);
assert.equal(food.get('ELEM_P').names.length, 7);
assert.deepEqual(food.normalize([{id:'STR',level:99},{id:'STR',level:2},{id:'INT',level:-1},{id:'bad',level:1}]), [{id:'STR',level:10},null,{id:'INT',level:1},null,null]);
assert.equal(food.normalize([{id:'AGGRO',level:10},{id:'AGGRO_MINUS',level:10}])[1], null);
assert.equal(food.normalize(Array(9).fill(null)).length, 5);
for (const recipe of food.recipes) {
  assert.equal(recipe.values.length, 10);
  for (let level=1; level<=10; level++) {
    assert.deepEqual(food.options([{id:recipe.id,level}]), recipe.connected ? [{key:recipe.key,value:recipe.values[level-1]}] : []);
  }
}
const saved=JSON.parse(await readFile(new URL('../../../samples/마법) 지팡이 크법 세팅 - pelio s.json',import.meta.url),'utf8'));
const input=structuredClone(saved);
Object.assign(input.build,{externalOptions:[{key:'STR',value:5}],skillLevels:{},activeBuffs:{},combo:[],myRoomFood:[{id:'STR',level:10},{id:'ELEM_P',level:10},{id:'MAXHP',level:6},{id:'AGGRO_MINUS',level:10},{id:'PHYS_RES',level:10}]});
delete input.build.consumableBuffs;
for(const [slot,piece] of Object.entries(input.build.equipment)){piece.options=[];piece.crystas=slot==='subWeapon'?[]:['',''];delete piece.catalogItem;}
const snapshot=application.CreateCalculationSnapshot(input);
assert.equal(snapshot.baseContext.strF,35);
assert.equal(snapshot.baseContext.elemP,15);
assert.equal(snapshot.baseContext.maxHpF,3600);
assert.equal(snapshot.baseContext.maxMpF,100);
assert.equal(snapshot.baseContext.preservedStats.PHYS_RES,undefined,'Disconnected recipes remain display-only');
const empty=structuredClone(input);empty.build.myRoomFood=[null,null,null,null,null];empty.build.externalOptions=[];
assert.equal(application.CreateCalculationSnapshot(empty).baseContext.maxHpF,1000);
empty.build.guildFoodBuff=false;
assert.equal(application.CreateCalculationSnapshot(empty).baseContext.maxHpF,0);
assert.equal(application.CreateCalculationSnapshot(empty).baseContext.maxMpF,0);
console.log('My room food: PASS (33 effects, 39 names, 330 levels, deduplication/bounds, real Application options, guild defaults and disconnected effects)');
