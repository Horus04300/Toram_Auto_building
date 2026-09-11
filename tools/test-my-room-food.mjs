import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
import { readFile } from 'node:fs/promises';
import vm from 'node:vm';
const require = createRequire(import.meta.url);
const food = require('../assets/js/data/my-room-food.js');
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
const window = { ToramFoodCatalog:food, getBaseContext() { return { options:this.ToramCalculationInputScope.kernelInput.options }; } };
vm.runInNewContext(await readFile(new URL('../assets/js/application-use-cases.js', import.meta.url),'utf8'), {window});
const input = {build:{equipment:{},externalOptions:[{key:'STR',value:5}],myRoomFood:[{id:'STR',level:10},{id:'ELEM_P',level:10},{id:'MAXHP',level:6},{id:'AGGRO_MINUS',level:10},{id:'PHYS_RES',level:10}]}};
const snapshot = window.ToramApplication.CreateCalculationSnapshot(input);
assert.deepEqual(JSON.parse(JSON.stringify(snapshot.baseContext.options)), [{key:'STR',value:5},{key:'STR',value:30},{key:'ELEM_P',value:15},{key:'MAXHP',value:2600},{key:'MAXHP',value:1000},{key:'MAXMP',value:100}]);
assert.deepEqual(JSON.parse(JSON.stringify(window.ToramApplication.CreateCalculationSnapshot({build:{equipment:{},externalOptions:[]}}).baseContext.options)), [{key:'MAXHP',value:1000},{key:'MAXMP',value:100}]);
assert.deepEqual(JSON.parse(JSON.stringify(window.ToramApplication.CreateCalculationSnapshot({build:{equipment:{},externalOptions:[],guildFoodBuff:false}}).baseContext.options)), []);
console.log('My room food: PASS (33 effects, 39 names, 330 level cases, deduplication, bounds, explicit snapshot and disconnected effects)');
