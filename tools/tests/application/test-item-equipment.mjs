import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { createRequire } from 'node:module';
import { createItemCatalog, createEquipmentSelection, resolveEquipmentOptions, validateEquipmentSelection,
  createConsumableBuffSelection, resolveConsumableBuffs } from '../../../web/src/application/item-catalog.mjs';
import { createEquipmentItemUi } from '../../../web/src/ui/item-equipment-ui.mjs';
import { createConsumableBuffUi } from '../../../web/src/ui/item-consumable-ui.mjs';
import { loadSavedBuildEnvironment } from '../../support/saved-build-headless-environment.mjs';

const root = resolve(import.meta.dirname, '../../..');
const registry = createRequire(import.meta.url)(resolve(root, 'web/src/calculation/stat-registry.js'));
const catalog = createItemCatalog('https://items.test/manifest.json', async url => ({ ok:true,
  json:async () => JSON.parse(await readFile(resolve(root, 'web/public/game-data/items', new URL(url).pathname.slice(1)))) }));
const item = await catalog.getItem(22001);
const ctx = { mainType:'한손검', subType:'없음', armorType:'일반옷' };
const selected = createEquipmentSelection(item, 'special', ctx, registry);
assert.equal(selected.gameItemId, 22001);
assert.deepEqual(resolveEquipmentOptions(selected, 'special', ctx, registry), [{key:'MAXMP', value:200}]);
assert.ok(Object.isFrozen(selected.stats));
assert.throws(() => createEquipmentSelection(item, 'armor', ctx, registry), /일치/u);
assert.throws(() => createEquipmentSelection(item, 'subWeapon', ctx, registry), /일치/u);
const crystal = await catalog.getItem(9911);
const blanc = await catalog.getItem(80453);
assert.equal(blanc.name, '블랑');
assert.equal(blanc.fullyMapped, true);
assert.deepEqual(blanc.stats, {SRW:10, STABILITY:5, AVOID_RECHARGE:5, LRW:-15});
assert.throws(() => createEquipmentSelection(crystal, 'special', ctx, registry), /종류/u);
assert.throws(() => createEquipmentSelection({...item, fullyMapped:false}, 'special', ctx, registry), /미연결/u);
const weapon = createEquipmentSelection(await catalog.getItem(10002), 'mainWeapon', ctx, registry);
assert.throws(() => resolveEquipmentOptions(weapon, 'mainWeapon', {...ctx,mainType:'활'}, registry), /종류/u);
const invalid = structuredClone(selected); invalid.stats.UNKNOWN = 3;
assert.throws(() => validateEquipmentSelection(invalid, registry), /등록되지/u);
assert.throws(() => validateEquipmentSelection({...selected,typeId:'22'}, registry), /종류/u);
assert.throws(() => validateEquipmentSelection({...selected,sourceSha256:'bad'}, registry), /해시/u);

const synthetic = {...selected, typeId:20, stats:{ATKP:5, MAXHP:1000, CHARGE_RED:10}, conditionalStats:[
  {when:{kind:'either-weapon-slot',types:['한손검','한손검(듀얼소드)']},stats:{CRIT:4},unresolved:[]},
  {when:{kind:'body-battle-customize',armor:'경량옷'},stats:{MAXMP:100},unresolved:[]}
]};
assert.deepEqual(resolveEquipmentOptions(synthetic, 'armor', {...ctx,subType:'한손검(듀얼소드)'}, registry).filter(option=>option.key==='CRIT'), [{key:'CRIT',value:4}]);
assert.equal(resolveEquipmentOptions(synthetic, 'armor', {...ctx,mainType:'활'}, registry).some(option=>option.key==='CRIT'), false);
assert.equal(resolveEquipmentOptions(synthetic, 'armor', {...ctx,armorType:'경량옷'}, registry).find(option=>option.key==='MAXMP').value, 100);
assert.throws(() => validateEquipmentSelection({...synthetic,conditionalStats:[{...synthetic.conditionalStats[0],unresolved:[{capId:999}]}]}, registry), /미연결/u);
assert.throws(() => validateEquipmentSelection({...synthetic,conditionalStats:[{...synthetic.conditionalStats[0],when:{kind:'unknown'}}]}, registry), /조건/u);

const environment = await loadSavedBuildEnvironment();
const piece = (type = null) => ({type,attack:null,refinement:null,stability:null,options:[],crystas:[],lockedCrystaSlots:[]});
const input = {build:{character:{level:300,attributes:{STR:100,INT:100,VIT:100,AGI:100,DEX:100,CRT:0}},
  equipment:{mainWeapon:{...piece('한손검'),attack:625,refinement:15,stability:80},subWeapon:{...piece('없음'),attack:0,refinement:0,stability:0},armor:piece('일반옷'),additional:piece(),special:piece()},
  externalOptions:[],skillLevels:{},activeBuffs:{},combo:[],guildFoodBuff:false}, scenario:{target:{bossLevel:300,bossDef:1000,bossMdef:500,bossCritResist:0,bossPhysResist:0,bossMagResist:0},conditions:{}},request:{selectedSkillId:null,selectedHitId:null,overrides:{}}};
for (const armorType of ['일반옷','경량옷','중량옷']) {
  input.build.equipment.armor = {...piece(armorType),catalogItem:synthetic,options:[{key:'ATK',value:7}]};
  input.build.equipment.special.catalogItem = selected;
  const gameResult = environment.ToramApplication.CalculateBuild(input);
  const manual = structuredClone(input);
  for (const slot of ['armor','special']) {
    const equipment = manual.build.equipment[slot];
    equipment.options.push(...resolveEquipmentOptions(equipment.catalogItem, slot, {...ctx,armorType}, registry));
    delete equipment.catalogItem;
  }
  assert.equal(JSON.stringify(gameResult.calculation), JSON.stringify(environment.ToramApplication.CalculateBuild(manual).calculation), 'Game selections must use the existing calculation kernel exactly once.');
  assert.equal(gameResult.snapshot.build.equipment.special.catalogItem.gameItemId, 22001);
}
environment.ToramBuildDraftStore = {read:()=>input};
const saved = JSON.parse(environment.ToramSettingsRepository.serializeSavedBuild('아이템 회귀'));
assert.equal(environment.ToramSettingsRepository.validateSavedBuild(saved), true);
const roundtrip = environment.ToramSettingsRepository.parseSavedBuild(JSON.stringify(saved));
assert.equal(roundtrip.build.equipment.special.catalogItem.stats.MAXMP, 200);
const broken = structuredClone(roundtrip); broken.build.equipment.special.catalogItem.stats.BAD = 9;
assert.equal(environment.ToramSettingsRepository.validateSavedBuild(broken), false);
assert.throws(() => environment.ToramSettingsRepository.parseSavedBuild(JSON.stringify(broken)));
const legacy = structuredClone(roundtrip);
for (const piece of Object.values(legacy.build.equipment)) delete piece.catalogItem;
assert.equal(environment.ToramSettingsRepository.validateSavedBuild(legacy), true, 'Old v2 builds still load.');

const ui = createEquipmentItemUi({defaultView:{ToramStatRegistry:registry}}, catalog);
ui.restoreSelection('special', selected);
assert.ok(Object.isFrozen(ui.getSelection('special').stats));
ui.restoreSelection('special', null);
assert.equal(ui.getSelection('special'), null);
assert.throws(() => ui.restoreSelection('subWeapon', selected), /일치/u);
for (const [id, subType, applies] of [[17002,'방패',true],[18001,'단검',true],[19001,'화살',true],[22901,'인술 두루마리',true],
  [15002,'마도구',false],[16002,'권갑',false],[25002,'발도검',false],[10002,'한손검(듀얼소드)',false]]) {
  const context = {...ctx,subType}, game = await catalog.getItem(id);
  const selection = createEquipmentSelection(game, 'subWeapon', context, registry);
  assert.equal(resolveEquipmentOptions(selection, 'subWeapon', context, registry).length > 0, applies, subType);
  ui.restoreSelection('subWeapon', selection);
  assert.equal(ui.getSelection('subWeapon').gameItemId, id);
  const build = structuredClone(input);
  build.build.equipment.subWeapon = {...piece(subType),attack:100,stability:20,refinement:11,options:[{key:'ATK',value:7}],catalogItem:selection};
  const result = environment.ToramApplication.CalculateBuild(build);
  const manual = structuredClone(build);
  manual.build.equipment.subWeapon.options.push(...resolveEquipmentOptions(selection, 'subWeapon', context, registry));
  delete manual.build.equipment.subWeapon.catalogItem;
  assert.equal(JSON.stringify(result.calculation), JSON.stringify(environment.ToramApplication.CalculateBuild(manual).calculation), 'Sub base inputs/manual options must remain independent of ordinary item bonuses.');
}
const vita = createConsumableBuffSelection(await catalog.getItem(2000), registry);
const vitaNext = createConsumableBuffSelection(await catalog.getItem(2001), registry);
const speed = createConsumableBuffSelection(await catalog.getItem(2537), registry);
const attack = createConsumableBuffSelection(await catalog.getItem(2505), registry);
assert.deepEqual(vita.stats, {MAXHP:500}); assert.equal(vita.durationSeconds, 1800);
assert.deepEqual(speed.stats, {ASPD:1000}); assert.equal(speed.buffGroupId, 219);
assert.deepEqual(attack.stats, {ATK:10,ATKP:1});
assert.ok(Object.isFrozen(vita.stats));
assert.throws(() => createConsumableBuffSelection(item, registry), /검증된/u);
assert.throws(() => createConsumableBuffSelection({...item,effectScope:'consumable-buff',fullyMapped:false}, registry), /검증된/u);
assert.throws(() => resolveConsumableBuffs([vita,vitaNext], registry), /같은 계열/u);
assert.throws(() => resolveConsumableBuffs([vita,vita], registry), /같은 계열/u);
assert.throws(() => resolveConsumableBuffs([{...vita,buffGroupId:9999}], registry), /계열/u);
assert.throws(() => resolveConsumableBuffs([{...vita,durationSeconds:-1}], registry), /지속시간/u);
assert.throws(() => resolveConsumableBuffs([{...vita,stats:{BAD:1}}], registry), /등록되지/u);
assert.throws(() => resolveConsumableBuffs([{...vita,stats:{MAXHP:0}}], registry), /동적/u);
const buffNames = await catalog.listBuffItems();
for (const {id} of buffNames) createConsumableBuffSelection(await catalog.getItem(id), registry);
assert.ok(buffNames.some(item => item.id === 2000));
assert.ok(!buffNames.some(item => item.id === 2560), 'Unmapped consumable scripts must stay out of the selectable list.');
const ampr = createConsumableBuffSelection(await catalog.getItem(2517), registry);
assert.deepEqual(ampr.stats, {AMPR:3}); assert.equal(ampr.buffGroupId, 210);
const tranquilizer = createConsumableBuffSelection(await catalog.getItem(108157), registry);
assert.equal(resolveConsumableBuffs([vita,tranquilizer], registry).filter(option => option.key === 'MAXHP').reduce((total, option) => total + option.value, 0), 1500, 'Different native groups may contribute the same stat.');
assert.equal(createConsumableBuffSelection(await catalog.getItem(2945), registry).typeId, 50);
const consumables = createConsumableBuffUi({defaultView:{ToramStatRegistry:registry}}, catalog);
consumables.restoreSelections([vita,speed]);
const copy = consumables.getSelections(); copy[0].stats.MAXHP = 99999;
assert.equal(consumables.getSelections()[0].stats.MAXHP, 500);
assert.throws(() => consumables.restoreSelections([vita,vitaNext]), /같은 계열/u);
assert.equal(consumables.getSelections().length, 2, 'Failed restoration must preserve previous selections.');
input.build.consumableBuffs = [vita,speed,attack];
input.build.externalOptions = [{key:'ATK',value:7}];
const withBuffs = environment.ToramApplication.CalculateBuild(input);
const manualBuffs = structuredClone(input);
manualBuffs.build.externalOptions.push(...resolveConsumableBuffs(input.build.consumableBuffs, registry));
delete manualBuffs.build.consumableBuffs;
assert.equal(JSON.stringify(withBuffs.calculation), JSON.stringify(environment.ToramApplication.CalculateBuild(manualBuffs).calculation));
const buffSave = environment.ToramSettingsRepository.parseSavedBuild(environment.ToramSettingsRepository.serializeSavedBuild('버프 소모품'));
assert.equal(buffSave.build.consumableBuffs[0].stats.MAXHP, 500);
assert.equal(buffSave.build.externalOptions[0].value, 7);
buffSave.build.consumableBuffs.push(vitaNext);
assert.equal(environment.ToramSettingsRepository.validateSavedBuild(buffSave), false);
consumables.restoreSelections([]); assert.deepEqual(consumables.getSelections(), []);
console.log('Item equipment/buffs: PASS (native sub types, ordinary-bonus exclusions, base/manual inputs preserved, buff units/groups, kernel parity, pinned v2 saves)');
