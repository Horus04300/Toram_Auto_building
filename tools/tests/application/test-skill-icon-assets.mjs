import assert from 'node:assert/strict';
import {access,readFile} from 'node:fs/promises';
import {createHash} from 'node:crypto';
import {resolve} from 'node:path';
import {skillTreeData} from '../../../web/src/data/skill-tree-data.js';
import {frontendSourcePath} from '../../support/frontend-paths.mjs';
import {EQUIPMENT_ICONS,EQUIPMENT_ITEM_ICONS,EQUIPMENT_SLOT_ICONS,CRYSTA_ICONS} from '../../../web/src/ui/equipment-icons.mjs';
import {WEAPON_ITEM_TYPES} from '../../../web/src/application/item-catalog.mjs';
import {inventoryGroups,inventoryLeaves} from '../../../web/src/pages/inventory/inventory-navigation.mjs';
import {ITEM_MENU_ICON,BOARD_MENU_ICON,CATALOG_MENU_ICON} from '../../../web/src/ui/game-menu-icons.mjs';
import {platformIcon} from '../../../web/src/layout/platform-shell.mjs';
const root=resolve(import.meta.dirname,'../../..'),paths=[];
function visit(value) {
  if(!value||typeof value!=='object')return;
  if(typeof value.icon==='string')paths.push(value.icon);
  Object.values(value).forEach(visit);
}
visit(skillTreeData);
assert.ok(paths.length,'Skill data must reference usable icons');
for(const path of paths) await access(resolve(root,frontendSourcePath(path)));
console.log(`Skill icon assets: PASS (${paths.length} referenced files exist)`);
const equipment = JSON.parse(await readFile(resolve(root,'data/sources/game-ui/equipment-icons.json'),'utf8'));
assert.deepEqual(Object.keys(EQUIPMENT_ICONS).sort(),Object.keys(equipment.icons).sort());
for (const [name,record] of Object.entries(equipment.icons)) {
  const source = await readFile(resolve(root,'data/sources/game-ui',record.source));
  assert.equal(createHash('sha256').update(source).digest('hex'),record.sha256);
  assert.deepEqual(await readFile(resolve(root,frontendSourcePath(EQUIPMENT_ICONS[name]))),source,'Published icons preserve the game pixels');
}
for (const type of [...Object.keys(WEAPON_ITEM_TYPES),20,21,22]) assert.ok(EQUIPMENT_ITEM_ICONS[type],`Missing equipment icon for game type ${type}`);
for (const group of inventoryGroups({type:'equipment'})) assert.ok(group.icon);
for (const slot of ['mainWeapon','subWeapon']) for (const leaf of inventoryLeaves({type:'equipment',slot})) {
  assert.equal(leaf.icon,EQUIPMENT_ICONS[leaf.id]);
  if (!['none','unarmed'].includes(leaf.id)) assert.ok(leaf.icon);
}
assert.equal(EQUIPMENT_ITEM_ICONS[999],undefined);
assert.equal(EQUIPMENT_ICONS.none,undefined);
assert.ok(Object.values(EQUIPMENT_SLOT_ICONS).every(path => Object.values(EQUIPMENT_ICONS).includes(path)));
console.log('Equipment icon assets: PASS (17 source-identical assets, 16 game equipment types, inventory slots/leaves)');
const crystas = JSON.parse(await readFile(resolve(root,'data/sources/game-ui/crysta-icons.json'),'utf8'));
assert.deepEqual(Object.keys(CRYSTA_ICONS).sort(),['all','노말','무기','방어구','추가','특수'].sort());
for (const [category,record] of Object.entries(crystas.icons)) {
  const source = await readFile(resolve(root,'data/sources/game-ui',record.source));
  assert.equal(CRYSTA_ICONS[category],record.asset);
  assert.equal(createHash('sha256').update(source).digest('hex'),record.sha256);
  assert.deepEqual(await readFile(resolve(root,frontendSourcePath(CRYSTA_ICONS[category]))),source);
}
assert.ok(crystas.icons.all.source.includes('sprite_0666_'),'The representative icon is the original empty gray crysta');
console.log('Crysta icon assets: PASS (5 market categories and empty gray representative, source-identical assets)');
const menu = JSON.parse(await readFile(resolve(root,'data/sources/game-ui/menu-icons.json'),'utf8')).icons;
for (const [key,name,path] of [['items','bag',ITEM_MENU_ICON],['board','board',BOARD_MENU_ICON],['catalog','book',CATALOG_MENU_ICON]]) {
  const source = await readFile(resolve(root,'data/sources/game-ui',menu[key].source));
  assert.equal(path,menu[key].asset);
  assert.equal(createHash('sha256').update(source).digest('hex'),menu[key].sha256);
  assert.deepEqual(await readFile(resolve(root,frontendSourcePath(path))),source);
  assert.ok(platformIcon(name).includes(`src="${path}"`));
  assert.ok(platformIcon(name).includes('alt="" aria-hidden="true"'));
  if (key === 'catalog') assert.deepEqual([source.readUInt32BE(16),source.readUInt32BE(20)],[79,69],'Use the approved small icon, not its large master');
}
assert.ok(platformIcon('home').startsWith('<svg'));
console.log('Menu icon assets: PASS (ESC Items backpack, Guild Notice board, approved 79x69 catalog book/quill, source-identical pixels)');
