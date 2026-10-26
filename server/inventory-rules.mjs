import { createRequire } from 'node:module';
import { readFileSync } from 'node:fs';
import { SUB_WEAPON_RULES } from '../web/src/application/equipment-object.mjs';

const require = createRequire(import.meta.url);
// The tree source is a JSON assignment; no user code or calculation engine runs on the server.
const trees = JSON.parse(readFileSync(new URL('../web/src/data/skill-tree-data.js',import.meta.url),'utf8').replace(/^window\.SKILL_TREE_DATA\s*=\s*/u,'').trim().replace(/;$/u,''));
export const inventoryRules = Object.freeze({trees, registry:require('../web/src/calculation/stat-registry.js'), food:require('../web/src/data/my-room-food.js'), subWeaponRules:SUB_WEAPON_RULES});
