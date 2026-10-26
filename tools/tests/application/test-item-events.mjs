import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import vm from 'node:vm';
import { convertCatalog } from '../../extraction/convert-toram-project-items.mjs';
import { createEquipmentSelection, resolveEquipmentOptions, validateEquipmentSelection } from '../../../web/src/application/item-catalog.mjs';
import { validateEquipmentObject } from '../../../web/src/application/equipment-object.mjs';
import { loadSavedBuildEnvironment } from '../../support/saved-build-headless-environment.mjs';

const read = async path => JSON.parse(await readFile(new URL(`../../../${path}`, import.meta.url), 'utf8'));
const registry = createRequire(import.meta.url)('../../../web/src/calculation/stat-registry.js');
const source = await read('data/sources/toram-items/items.77596232.connected.json');
const mapping = (await read('data/sources/toram-items/project-stat-mapping.json')).statMapping;
const rows = source.items.filter(item => [17035,21095,21096].includes(item.gameItemId));
assert.equal(rows.length,3);
const convert = items => convertCatalog({...source,nativeRulesApplied:true,items},mapping);
const converted = convert(rows);
const ctx = {mainType:'한손검',subType:'방패',armorType:'일반옷'};
const selections = new Map();
for (const [id,eventType,slot,tailKey,tailValue] of [[17035,3,'subWeapon','MAXHPP',15],[21095,9,'additional','EXP',10],[21096,9,'additional','DROP_RATE',10]]) {
  const row = converted.kinds[id === 17035 ? 'weapons' : 'additional'][id];
  assert.equal(row.fullyMapped,true);
  assert.equal(row.unresolved.length,0);
  const selected = createEquipmentSelection({...row,id,cacheVersion:'77596232',sourceSha256:'a'.repeat(64),name:String(id)},slot,ctx,registry);
  selections.set(id,selected);
  const off = resolveEquipmentOptions(selected,slot,ctx,registry);
  const on = resolveEquipmentOptions(selected,slot,{...ctx,activeItemEventTypes:[eventType]},registry);
  assert.ok(!off.some(option => option.key === tailKey));
  assert.equal(on.find(option => option.key === tailKey).value,tailValue);
  for (const [key,value] of Object.entries(row.stats)) assert.equal(off.find(option=>option.key===key).value,value,'Earlier bonuses survive a failed event check');
  const piece={type:slot==='subWeapon'?'방패':null,attack:slot==='subWeapon'?0:null,refinement:slot==='subWeapon'?0:null,stability:slot==='subWeapon'?0:null,options:[],crystas:slot==='subWeapon'?[]:['',''],lockedCrystaSlots:slot==='subWeapon'?[]:[false,false],catalogItem:selected};
  validateEquipmentObject({slot,equipment:piece},registry);
}
// Signed i16 operands are read as unsigned low bytes, not numeric event amounts.
for (const operand of [-1,0,259]) {
  const row=structuredClone(rows[1]); row.propertyRecord.caps.find(cap=>cap.cap_id===114).value=operand;
  const item=convert([row]).kinds.additional[21095];
  assert.equal(item.conditionalStats[0].when.eventType,operand & 255);
}
// A skipped equipment block never executes its event check. An executed failed
// marker stops everything after it, including options outside that block.
const nested=structuredClone(rows[1]);
const marker=nested.propertyRecord.caps.find(cap=>cap.cap_id===114);
marker.conditionMarkerSlot=1;
const equipmentMarker={...structuredClone(marker),slot:1,cap_id:101,value:1,role:'equipment-condition-marker',conditionMarkerSlot:null};
nested.propertyRecord.caps=[equipmentMarker,{...marker,slot:2}, {...structuredClone(nested.propertyRecord.caps.find(cap=>cap.cap_id===63)),slot:3}];
nested.propertyRecord.conditionGroups=[{markerSlot:1,capId:101,instructionCount:1,targetSlots:[2],uiScopeMatchesBonusScope:true}];
const nestedItem=convert([nested]).kinds.additional[21095];
assert.equal(resolveEquipmentOptions(createEquipmentSelection({...nestedItem,id:21095,cacheVersion:'77596232',sourceSha256:'a'.repeat(64),name:'event'},'additional',ctx,registry),'additional',ctx,registry).find(option=>option.key==='EXP').value,10);
const when=nestedItem.conditionalStats.at(-1).when;
const matching={...ctx,mainType:'지팡이',subType:'없음'};
const nestedSelection=createEquipmentSelection({...nestedItem,id:21095,cacheVersion:'77596232',sourceSha256:'a'.repeat(64),name:'event'},'additional',matching,registry);
assert.deepEqual(resolveEquipmentOptions(nestedSelection,'additional',matching,registry),[]);
assert.equal(resolveEquipmentOptions(nestedSelection,'additional',{...matching,activeItemEventTypes:[9]},registry)[0].value,10);
assert.equal(when.kind,'any');
for (const eventType of [-1,256,1.5,'3']) assert.throws(()=>validateEquipmentSelection({...selections.get(21095),conditionalStats:[{when:{kind:'item-event',eventType},stats:{},unresolved:[]}]},registry),/이벤트/u);

const environment=await loadSavedBuildEnvironment();
const piece=(type=null)=>({type,attack:0,refinement:0,stability:0,options:[],crystas:[],lockedCrystaSlots:[]});
const input={build:{character:{level:300,attributes:{STR:100,INT:100,VIT:100,AGI:100,DEX:100,CRT:0}},equipment:{mainWeapon:{...piece('한손검'),attack:625,stability:80},subWeapon:{...piece('방패'),catalogItem:selections.get(17035)},armor:piece('일반옷'),additional:piece(),special:piece()},externalOptions:[],skillLevels:{},activeBuffs:{},combo:[],guildFoodBuff:false},scenario:{target:{bossLevel:300,bossDef:1000,bossMdef:500,bossCritResist:0,bossPhysResist:0,bossMagResist:0},conditions:{}},request:{overrides:{}}};
for(const active of [[],[3]]) {
  input.scenario.conditions.activeItemEventTypes=active;
  const result=environment.ToramApplication.CalculateBuild(input);
  const manual=structuredClone(input), sub=manual.build.equipment.subWeapon;
  sub.options=resolveEquipmentOptions(sub.catalogItem,'subWeapon',{...ctx,activeItemEventTypes:active},registry); delete sub.catalogItem;
  assert.equal(JSON.stringify(result.calculation),JSON.stringify(environment.ToramApplication.CalculateBuild(manual).calculation));
}
environment.ToramBuildDraftStore={read:()=>input};
const saved=JSON.parse(environment.ToramSettingsRepository.serializeSavedBuild('이벤트 장비'));
assert.deepEqual(Array.from(environment.ToramSettingsRepository.parseSavedBuild(JSON.stringify(saved)).scenario.conditions.activeItemEventTypes),[3]);
for(const bad of [[3,3],[-1],[256],[1.2],['3'],3,null]) {
  const broken=structuredClone(saved); broken.scenario.conditions.activeItemEventTypes=bad;
  assert.equal(environment.ToramSettingsRepository.validateSavedBuild(broken),false);
}
delete saved.scenario.conditions.activeItemEventTypes;
assert.equal(environment.ToramSettingsRepository.validateSavedBuild(saved),true,'Older saves default to no active event');

const nodes=Object.fromEntries(['itemEvent3','itemEvent9'].map(id=>[id,{checked:true,type:'checkbox',nodeType:1,id}]));
const ui={window:null,document:{readyState:'loading',getElementById:id=>nodes[id],addEventListener(){}},ToramBuildDraftStore:{syncFromUi(){}}}; ui.window=ui;
vm.createContext(ui);
vm.runInContext(await readFile(new URL('../../../web/src/storage/build-state-snapshot.js',import.meta.url),'utf8'),ui);
ui.ToramBuildStateUi.restoreSession({build:{},scenario:{conditions:{activeItemEventTypes:[9]}}});
assert.equal(nodes.itemEvent3.checked,false); assert.equal(nodes.itemEvent9.checked,true);
ui.ToramBuildStateUi.restoreSession({build:{},scenario:{conditions:{}}});
assert.equal(nodes.itemEvent9.checked,false);
assert.equal(ui.ToramBuildStateUi.isCalculationInput(nodes.itemEvent3),true);
console.log('Item events: PASS (native ordered gates, byte operands, equipment/kernel/save/restore, default inactive)');
