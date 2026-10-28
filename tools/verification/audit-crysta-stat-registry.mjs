import {loadSavedBuildEnvironment} from '../support/saved-build-headless-environment.mjs';
const context=await loadSavedBuildEnvironment(), registry=context.ToramStatRegistry;
const skillKeys = new Set();
function visit(value) {
  if (!value || typeof value !== 'object') return;
  if (value.type === 'stat' && typeof value.key === 'string') skillKeys.add(value.key);
  if (Array.isArray(value)) value.forEach(visit);
  else Object.values(value).forEach(visit);
}
visit(context.window.ToramSkillEffectRegistry.definitions());
const crystaKeys = registry.collectCrystaKeys(context.ToramCrystaCatalog.items);
if (!crystaKeys.length) throw new Error('Crysta stat audit requires the live catalog');
const keys = Array.from(new Set([...crystaKeys, ...skillKeys])).sort();
const audit = registry.auditKeys(keys);
console.log(`CrystaOptimization StatRegistry audit: crysta=${crystaKeys.length}, skillStat=${skillKeys.size}, combined=${keys.length}, modeled=${audit.modeled.length}, preserved=${audit.preserved.length}, unknown=${audit.unknown.length}`);
if (audit.unknown.length) {
  console.error(`Unknown stat keys: ${audit.unknown.join(', ')}`);
  process.exit(1);
}
