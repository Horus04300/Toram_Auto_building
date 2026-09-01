import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import vm from 'node:vm';
import { LEGACY_SCRIPT_PATHS } from '../assets/js/legacy-script-manifest.mjs';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const dataScripts = LEGACY_SCRIPT_PATHS.filter(path => path.startsWith('assets/js/data/'));
const context = { window:{ skillSimulatorState:{ getInvestments:() => ({}) } }, console };
context.window.window = context.window;
vm.createContext(context);
for (const path of dataScripts) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });

const skillKeys = new Set();
function visit(value) {
  if (!value || typeof value !== 'object') return;
  if (value.type === 'stat' && typeof value.key === 'string') skillKeys.add(value.key);
  if (Array.isArray(value)) value.forEach(visit);
  else Object.values(value).forEach(visit);
}
visit(context.window.ToramSkillEffectRegistry.all());
vm.runInContext('globalThis.__d4CrystaData = crystaDataJson;', context);
const crystaKeys = registry.collectCrystaKeys(context.__d4CrystaData);
const keys = Array.from(new Set([...crystaKeys, ...skillKeys])).sort();
const audit = registry.auditKeys(keys);
console.log(`D4 StatRegistry audit: crysta=${crystaKeys.length}, skillStat=${skillKeys.size}, combined=${keys.length}, modeled=${audit.modeled.length}, preserved=${audit.preserved.length}, unknown=${audit.unknown.length}`);
if (audit.unknown.length) {
  console.error(`Unknown stat keys: ${audit.unknown.join(', ')}`);
  process.exit(1);
}
