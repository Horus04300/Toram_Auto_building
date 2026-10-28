import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {DatabaseSync} from 'node:sqlite';
import {validateBuild,validateScenario} from '../../../web/src/application/build-values.mjs';
import {captureObject,applyObject} from '../../../web/src/application/inventory-objects.mjs';
import {createInventoryStore} from '../../../server/inventory-store.mjs';
import {inventoryRules as rules} from '../../../server/inventory-rules.mjs';
import {loadSavedBuildEnvironment} from '../../support/saved-build-headless-environment.mjs';

const env = await loadSavedBuildEnvironment();
const saved = JSON.parse(await readFile(new URL('../../../samples/마법) 지팡이 크법 세팅 - pelio s.json',import.meta.url),'utf8'));
saved.scenario.target.targetElement = 0;
saved.scenario.conditions.activeItemEventTypes = [];
validateBuild(saved.build,rules); validateScenario(saved.scenario);
assert.equal(env.ToramSettingsRepository.validateSavedBuild(saved),true);
Object.defineProperty(env,'document',{get() {throw new Error('Calculation must not read the DOM');}});
env.skillSimulatorState = {getInvestments() {throw new Error('Calculation must use explicit skill levels');}};
env.ToramActiveBuffs = {getSelections() {throw new Error('Calculation must use explicit buff selections');}};
const calculated = env.ToramApplication.CalculateBuild(saved);
assert.equal(calculated.snapshot.baseContext.skillLevels.Magic[13],saved.build.skillLevels.Magic[13]);
assert.ok(Number.isFinite(calculated.calculation.finalMATK));
for (const preferences of [{},{requirements:{maxHp:null}},{rangeOverride:'LONG'},{bannedCrystas:[]},saved.scenario.optimizationPreferences]) for (const events of [[],[3],[3,9]]) {
  const session = structuredClone(saved); session.scenario.conditions.activeItemEventTypes = events;
  session.scenario.optimizationPreferences = preferences;
  const db = new DatabaseSync(':memory:');
  try {
    db.exec("PRAGMA foreign_keys=ON; CREATE TABLE users(id TEXT PRIMARY KEY); INSERT INTO users VALUES ('owner');");
    const store = createInventoryStore(db);
    const data = captureObject('build',session);
    const record = store.create('owner',{name:'roundtrip',type:'build',schemaVersion:1,data});
    const applied = applyObject(record,session,rules);
    assert.deepEqual(applied.scenario,session.scenario);
    assert.deepEqual(applied.build.equipment,session.build.equipment);
    assert.equal(env.ToramSettingsRepository.validateSavedBuild({...saved,...applied}),true);
  } finally { db.close(); }
}
for (const change of [
  value => {value.target.targetElement = 8;},
  value => {value.target.bossDef = NaN;},
  value => {value.target.extra = 1;},
  value => {value.conditions.activeItemEventTypes = [3,3];},
  value => {value.conditions.activeItemEventTypes = [256];},
  value => {value.conditions.extra = [];}
]) {
  const bad = structuredClone(saved.scenario); change(bad);
  assert.throws(() => validateScenario(bad));
  assert.equal(env.ToramSettingsRepository.validateSavedBuild({...saved,scenario:bad}),false);
  assert.throws(() => {
    const db = new DatabaseSync(':memory:');
    try {db.exec("CREATE TABLE users(id TEXT PRIMARY KEY); INSERT INTO users VALUES ('owner');"); createInventoryStore(db).create('owner',{name:'bad',type:'build',schemaVersion:1,data:{context:{externalOptions:[],scenario:bad}}});}
    finally {db.close();}
  });
}
console.log('Build values: PASS (shared validation, current fields, SQLite capture/apply roundtrip, invalid inputs)');
