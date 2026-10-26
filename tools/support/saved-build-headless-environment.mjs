import { frontendSourcePath } from './frontend-paths.mjs';
import { readCrystaDataSource } from './crysta-catalog-source.mjs';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';
import { CLASSIC_SCRIPT_PATHS as runtimeScripts } from '../../web/src/classic-script-manifest.mjs';
const CLASSIC_SCRIPT_PATHS = runtimeScripts.map(frontendSourcePath);
import { root } from './crysta-headless-environment.mjs';
import { resolveEquipmentOptions, resolveEquipmentElement, validateEquipmentSelection, resolveConsumableBuffs } from '../../web/src/application/item-catalog.mjs';
import { SUB_WEAPON_RULES } from '../../web/src/application/equipment-object.mjs';
import { STAT_LABELS } from '../../web/src/application/stat-labels.mjs';

// Calculation uses Application's explicit input scope; UI listeners are inactive.
export async function loadSavedBuildEnvironment() {
  const context = { console, document:{ readyState:'loading', getElementById:() => ({ value:'', addEventListener() {} }), querySelector:() => null, addEventListener() {} } };
  context.window = context;
  context.ToramApp = { statLabels:STAT_LABELS, itemRules:{ resolveEquipmentOptions, resolveEquipmentElement, validateEquipmentSelection, resolveConsumableBuffs, subWeaponRules:SUB_WEAPON_RULES } };
  vm.createContext(context);
  for (const path of [...CLASSIC_SCRIPT_PATHS.filter(path => path.startsWith('web/src/data/')),
    'web/src/calculation/stat-registry.js', 'web/src/calculation/calculation-policies.js', 'web/src/calculation/skill-effect-engine.js',
    'web/src/calculation/supplemental-stats.js','web/src/calculation/option-event-calculator.js',
    'web/src/ui/crysta-ui.js', 'web/src/calculation/combo-sequence-engine.js', 'web/src/calculation/calculator.js',
    'web/src/application/application-use-cases.js', 'web/src/calculation/build-evaluator.js', 'web/src/storage/settings-repository.js']) {
    vm.runInContext(path === 'web/src/data/crysta-data.js' ? await readCrystaDataSource(root) : await readFile(resolve(root, path), 'utf8'), context, { filename:path });
  }
  return context;
}
