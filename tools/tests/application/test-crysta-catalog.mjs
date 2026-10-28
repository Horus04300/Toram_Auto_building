import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {createItemCatalog,resolveItemOptions} from '../../../web/src/application/item-catalog.mjs';
import {loadSavedBuildEnvironment} from '../../support/saved-build-headless-environment.mjs';
import {loadHeadlessEnvironment,root} from '../../support/crysta-headless-environment.mjs';
import {exhaustiveSearch} from '../../support/crysta-exhaustive-oracle.mjs';
import {loadWasmModule} from '../../support/crysta-wasm-module.mjs';

const plain = value => JSON.parse(JSON.stringify(value));
const catalog = createItemCatalog('https://items.test/manifest.json', async url => ({ok:true,
  json:async () => JSON.parse(await readFile(resolve(root,'web/public/game-data/items',url.pathname.slice(1))))}));
const records = await catalog.getCrystaCatalog();
const env = await loadSavedBuildEnvironment();
const compiler = (await loadHeadlessEnvironment()).context.ToramCrystaOptimizationProblemCompiler;
const crystas = Object.values(records).filter(item => item.category);
assert.equal(crystas.length,553);
assert.equal(Object.values(records).filter(item => !item.category).length,5,'Blank item placeholders are not selectable crystas');
assert.ok(crystas.every(item => item.fullyMapped));
assert.equal(crystas.filter(item => item.previousId !== null).length,246);
const aliases = JSON.parse(await readFile(resolve(root,'data/sources/toram-items/crysta-legacy-aliases.json'))).aliases;
assert.equal(Object.values(aliases).flat().length,425);
for (const [id,names] of Object.entries(aliases)) for (const name of names) {
  assert.equal(env.ToramCrystaCatalog.resolve(name),env.ToramCrystaCatalog.getById(id),'Legacy names resolve to the same ID object');
}
for (const item of crystas) {
  const view = env.ToramCrystaCatalog.getById(item.gameItemId);
  assert.equal(env.ToramCrystaCatalog.resolve(String(item.gameItemId)),view);
  assert.equal(view.gameItemId,item.gameItemId);
  assert.deepEqual(plain(view.stats),item.stats);
  assert.equal(view.previousId,item.previousId);
  assert.equal(Object.keys(item.names).length,6);
  assert.ok(item.options.every(option => option.texts && Number.isFinite(option.rawValue)));
}
assert.equal(env.ToramCrystaCatalog.resolve('บีมอซ'),null,'An ambiguous translation must never select an arbitrary ID');
assert.equal(env.ToramCrystaCatalog.resolve('댄드라이'),null,'No fuzzy identity joins');
const dandelion = records[9776];
assert.equal(dandelion.names.kr,'댄드라이언');
assert.deepEqual(dandelion.stats,{MAXMP:500,AMPR:4,CSPD:300});
assert.equal(dandelion.previousId,9900);
assert.deepEqual(dandelion.conditionalStats,[{when:{kind:'body-battle-customize',armor:'경량옷'},stats:{STABILITY:6},unresolved:[]}]);
const contexts = ['한손검','양손검','활','자동활','지팡이','마도구','권갑','선풍창','발도검','맨손']
  .map(mainType => ({mainType,subType:'없음',armorType:'일반옷'}));
contexts.push({mainType:'한손검',subType:'한손검(듀얼소드)',armorType:'경량옷'},
  {mainType:'지팡이',subType:'권갑',armorType:'중량옷'},
  {mainType:'한손검',subType:'마도구',armorType:'경량옷'},
  {mainType:'활',subType:'발도검',armorType:'중량옷'});
const views = crystas.map(item => env.ToramCrystaCatalog.getById(item.gameItemId));
const lineage = compiler.buildLineageIndex(views);
let comparisons = 0;
for (const context of contexts) for (const item of crystas) {
  const expected = Object.fromEntries(resolveItemOptions(item,context).map(row => [row.key,row.value]));
  const diagnostics = [];
  const resolved = compiler.resolveCrysta(env.ToramCrystaCatalog.getById(item.gameItemId),context,env.ToramStatRegistry,lineage,diagnostics);
  assert.deepEqual(plain(resolved.statDelta),expected,`Native options/compiler ${item.gameItemId} ${JSON.stringify(context)}`);
  const actual = {...item.stats};
  for (const group of env.ToramCrystaCatalog.getById(item.gameItemId).conditionalStats) {
    if (env.ToramCalculationPolicies.matchesCrystaCondition(context,group.when)) {
      for (const [key,value] of Object.entries(group.stats)) actual[key]=(actual[key]||0)+value;
    }
  }
  assert.deepEqual(actual,expected,'Application and compiler must agree with the source item conditions');
  assert.deepEqual(plain(diagnostics),[]);
  comparisons++;
}
assert.ok(lineage.conflict(env.ToramCrystaCatalog.resolve('댄드라이언'),env.ToramCrystaCatalog.getById(9900)));
const ancestor = env.ToramCrystaCatalog.getById(9631), sibling1 = env.ToramCrystaCatalog.getById(9632), sibling2 = env.ToramCrystaCatalog.getById(9633);
assert.ok(lineage.conflict(sibling1,sibling2),'Automatic recommendation preserves shared-ancestor exclusion');
assert.equal(env.ToramCrystaCatalog.conflict(sibling1,sibling2),false,'Manual equipment preserves sibling acceptance');
assert.ok(env.ToramCrystaCatalog.conflict(ancestor,sibling1),'Manual equipment excludes direct ancestors');
const fixture = JSON.parse(await readFile(resolve(root,'tools/fixtures/crysta-native-runtime-26min-revenir.json')));
const search = await loadHeadlessEnvironment(), wasm = await loadWasmModule();
const tutorials = views.filter(item => item.gameItemId >= 9401 && item.gameItemId <= 9504);
assert.equal(tutorials.length,99,'Reviewed flat-stat tutorial ID family');
assert.ok(tutorials.every(item => item.category === '노말' && Object.keys(item.stats).length === 1 && !item.conditionalStats.length));
const tutorialNames = new Set(tutorials.map(item => item.name));
for (const keepLowerUpgrades of [false,true]) {
  const scoped = search.compile({...fixture.resolvedExecutionContext,keepLowerUpgrades});
  assert.ok(scoped.groups.every(group => group.packages.every(pack => !pack.candidateNames.some(name => tutorialNames.has(name)))),
    'Tutorial crystals must never enter the automatic candidate combinations');
}
for (const current of ['STR+1','9401']) {
  const locked = search.compile({...fixture.resolvedExecutionContext,crystas:[...tutorials,env.ToramCrystaCatalog.resolve('블랑')],
    currentCrystas:[current],locks:[true,false]});
  assert.deepEqual(plain(locked.diagnostics),[]);
  assert.ok(locked.groups[0].packages.every(pack => pack.candidateNames.includes('STR+1')),'Explicit tutorial locks must be preserved');
  assert.ok(locked.groups.flatMap(group => group.packages).every(pack => pack.candidateNames.every(name => name === 'STR+1' || !tutorialNames.has(name))));
}
assert.deepEqual(plain(env.ToramCrystaCatalog.resolve('STR+1').stats),{STR:1},'Manual selection and saved tutorial options remain available');
const subset = [9776,9900,80453,9911,9804].map(id => env.ToramCrystaCatalog.getById(id));
for (const armorType of ['일반옷','경량옷','중량옷']) {
  const baseContext = {...fixture.resolvedExecutionContext.baseContext,armorType};
  const input = {baseContext,crystas:subset,keepLowerUpgrades:true,scenarioRequirements:{maxHp:null,maxMp:null,amprBeforeDual:null,normalAttackCrit:null,aspd:null}};
  for (const seed of [
    {},
    {currentCrystas:[null,null,'Dandolion']},
    {currentCrystas:[null,null,env.ToramCrystaCatalog.getById(9900).name],keepLowerUpgrades:false},
    {currentCrystas:[null,null,'댄드라이언'],banned:{'댄드라이언':true}}
  ]) {
    const problem = search.compile({...input,...seed}), bridge = search.context.ToramCrystaOptimizationRustBridge;
    const before = JSON.stringify(problem);
    const oracle = exhaustiveSearch(problem,{prepared:true,evaluateStats:bridge.evaluate(problem)});
    const setup = bridge.prepare(problem,{}), wire = bridge.projectProblem(setup.problem);
    if (seed.currentCrystas) {
      assert.equal(problem.metadata.initialPackageIds[1],null,'Unavailable current packages are optional warm starts');
      assert.equal(wire.metadata.initialPackageIds,undefined,'Incomplete warm starts must not send null IDs to Rust');
    } else assert.deepEqual(plain(wire.metadata.initialPackageIds),plain(problem.metadata.initialPackageIds));
    assert.equal(JSON.stringify(problem),before,'Projection must preserve the input and constraints');
    const session = new wasm.SearchSession(JSON.stringify(wire));
    try {
      while (!session.is_complete()) session.step(1000);
      const result = JSON.parse(session.snapshot());
      assert.equal(result.status,oracle.status); assert.equal(result.score,oracle.score); assert.equal(result.bestBuild?.id,oracle.bestBuild?.id);
    } finally {session.free();}
  }
  const banned = search.compile({...input,banned:{'9776':true},excluded:['Dandolion']});
  assert.ok(banned.groups.every(group => group.packages.every(pack => !pack.candidateNames.includes('댄드라이언'))));
  const locked = search.compile({...input,currentCrystas:[null,null,'Dandolion'],locks:[false,false,true]});
  assert.deepEqual(plain(locked.diagnostics),[]);
  assert.ok(locked.groups[1].packages.every(pack => pack.candidateNames.includes('댄드라이언')));
}
console.log(`Crysta ID catalog: PASS (553 real/5 placeholders, 425 legacy aliases, 246 predecessor IDs, ${comparisons} native/application/compiler option comparisons, real WASM exhaustive score/ID, aliases/locks/bans)`);
