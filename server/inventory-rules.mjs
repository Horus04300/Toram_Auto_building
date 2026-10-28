import {skillTreeData as trees} from '../web/src/data/skill-tree-data.js';
import {statRegistry as registry} from '../web/src/calculation/stat-registry.js';
import {foodCatalog as food} from '../web/src/data/my-room-food.js';
import {SUB_WEAPON_RULES as subWeaponRules} from '../web/src/application/equipment-object.mjs';
export const inventoryRules = Object.freeze({trees,registry,food,subWeaponRules});
