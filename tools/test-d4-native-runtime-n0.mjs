import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const fixture = JSON.parse(await readFile(resolve(root, 'tools/fixtures/d4-native-runtime-26min-revenir.json'), 'utf8'));
const nativeClientSource = await readFile(resolve(root, 'assets/js/d4-native-client.js'), 'utf8');
const nativeCommandSource = (await Promise.all([
  readFile(resolve(root, 'src-tauri/src/tauri_commands.rs'), 'utf8'),
  readFile(resolve(root, 'src-tauri/src/d4_service.rs'), 'utf8')
])).join('\n');
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const evaluator = require(resolve(root, 'assets/js/build-evaluator.js'));
const compiler = require(resolve(root, 'assets/js/d4-problem-compiler.js'));
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));

const context = { window:{ ToramStatRegistry:registry }, console };
context.window.window = context.window;
vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', context);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculation-policies.js'), 'utf8'), context, { filename:'calculation-policies.js' });
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'calculator.js' });
const kernel = context.window.ToramCalculationKernel.evaluateContext;

const dataContext = {};
vm.createContext(dataContext);
vm.runInContext(`${await readFile(resolve(root, 'assets/js/data/crysta-data.js'), 'utf8')}\nglobalThis.__crystas=crystaDataJson;`, dataContext);

assert.equal(fixture.schema, 'toram.d4-native-runtime-fixture.v1');
assert.equal(fixture.evidence.reportedWallTimeMinutes, 26);
assert.equal(fixture.evidence.reportedLockedEtowalWallTimeMs, 118830);
assert.equal(fixture.evidence.selectedSkillId, 'Knight:11');
assert.deepEqual(Object.keys(fixture.resolvedExecutionContext.banned).sort(), ['오로로 콜론', '카나요간'].sort());
assert.deepEqual(fixture.resolvedExecutionContext.locks, Array(8).fill(false), 'screenshot lock controls are not active locks in this fixture');
const lockedEtowalMeasurement = fixture.measurements.find(item => item.id === 'locked-etowal-variant');
assert.ok(lockedEtowalMeasurement, 'N0 fixture must retain the locked Etowal measurement separately from the unlocked baseline');
assert.deepEqual(lockedEtowalMeasurement.locks, [false, false, false, false, false, false, true, false]);
assert.equal(lockedEtowalMeasurement.reportedWallTimeMs, 118830);
assert.match(nativeClientSource, /remainingBudgetMs:remainingBudget/, 'native bridge must pass the UI-preparation-adjusted deadline budget to Tauri');
assert.match(nativeClientSource, /progressChannel\(/, 'native bridge must create a Tauri progress channel when the runtime exposes Channel');
assert.match(nativeCommandSource, /run_budget/, 'native command service must coordinate bounded session slices instead of an unbounded terminal-only solve');
assert.match(nativeCommandSource, /resume_d4_optimization/, 'native command must expose a continuation resume entry point');

const input = fixture.resolvedExecutionContext;
assert.equal(input.baseContext.rangeType, 'SHORT', '루브닐 기준 D4 입력은 근거리 공격이어야 한다');
const scenario = evaluator.createScenarioSnapshot(input.baseContext, { basisName:'루브닐', requirements:input.scenarioRequirements, combo:fixture.rawInput.combo });
function compileWith(currentCrystas, locks) {
  return compiler.compileCrystaProblem({
    crystas:dataContext.__crystas,
    registry,
    baseContext:input.baseContext,
    scenarioSnapshot:scenario,
    currentCrystas,
    locks,
    banned:input.banned
  });
}
const compiled = compileWith(input.currentCrystas, input.locks);
assert.deepEqual(compiled.diagnostics, [], 'N0 fixture must reach native compilation without input diagnostics');
assert.equal(compiled.metadata.lockedSlotCount, 0);
assert.equal(compiled.metadata.initialPackageIds[3].includes('에투왈'), true, 'current special crysta must be represented in the initial package');
const adapter = stats => evaluator.evaluateAggregate(input.baseContext, scenario, stats, kernel);
const current = adapter({ CRITP:40, ASPD:1100, MOTIONSPEED:5, CSPD_P:-70 });
assert.equal(current.utility.maxMpBeforeBuff, 2275, 'resolved N0 input must retain the displayed maximum MP');
assert.equal(current.constraints.feasible, false, 'the current Etowal build must preserve the user-reported hard-constraint shortfall');
assert.ok(current.constraints.violations.length > 0, 'the fixture must show why the solver needs a searched feasible incumbent');

const polveros = dataContext.__crystas.find(item => item.name === '폴버로스');
assert.ok(polveros, 'Polveros must remain in the crysta dataset');
const lineageIndex = compiler.buildLineageIndex(dataContext.__crystas);
function resolvePolveros(mainType) {
  return compiler.resolveCrysta(
    polveros,
    compiler.createStructure({ ...input.baseContext, mainType }),
    registry,
    lineageIndex,
    []
  );
}
const oneHandPolveros = resolvePolveros('한손검');
assert.equal(oneHandPolveros.statDelta.LRW, 9, 'Polveros long-range damage is unconditional');
assert.equal(oneHandPolveros.statDelta.SRW, undefined, 'Polveros short-range damage must not apply to a one-hand sword');
assert.ok(oneHandPolveros.resolvedConditionMetadata.inactive.some(condition => condition.main === '자동활'), 'the inactive bow-only condition must be retained for audit');
const bowPolveros = resolvePolveros('자동활');
assert.equal(bowPolveros.statDelta.LRW, 9, 'Polveros long-range damage remains active with a bow');
assert.equal(bowPolveros.statDelta.SRW, 9, 'Polveros short-range damage applies only with a bow');

const emptySlots = Array(8).fill(null);
const specialEtowal = [...emptySlots]; specialEtowal[6] = '에투왈';
const oneLocked = compileWith(specialEtowal, [false, false, false, false, false, false, true, false]);
assert.deepEqual(oneLocked.diagnostics, [], 'one known locked crysta must compile without diagnostics');
assert.ok(oneLocked.groups[3].packages.every(item => item.candidateNames.includes('에투왈')), 'one locked crysta must remain in every special package');
const twoSpecial = [...specialEtowal]; twoSpecial[7] = '오르그';
const twoLocked = compileWith(twoSpecial, [false, false, false, false, false, false, true, true]);
assert.deepEqual(twoLocked.diagnostics, [], 'two compatible locked crystas must compile without diagnostics');
assert.equal(twoLocked.groups[3].packages.length, 1, 'two locked special slots must produce one fixed package');
assert.deepEqual(twoLocked.groups[3].packages[0].candidateNames.slice().sort(), ['에투왈', '오르그'].sort());
const allEmptyLocked = compileWith(emptySlots, Array(8).fill(true));
assert.deepEqual(allEmptyLocked.diagnostics, [], 'locked empty slots must be valid explicit inputs');
assert.deepEqual(allEmptyLocked.groups.map(group => group.packages.length), [1, 1, 1, 1], 'eight locked empty slots must remove every search candidate');
const unknownSlots = [...emptySlots]; unknownSlots[6] = 'N0-unknown-locked-crysta';
const unknownLocked = compileWith(unknownSlots, [false, false, false, false, false, false, true, false]);
assert.ok(unknownLocked.diagnostics.some(item => item.code === 'UNKNOWN_LOCKED_CRYSTA'), 'unknown locked crysta must remain visible as a compiler diagnostic for N1');
const relevantKeys = optimizer.deriveRelevantKeys(compiled, registry, adapter);
assert.ok(relevantKeys.includes('SRW') && !relevantKeys.includes('LRW'), '근거리 루브닐 최적화는 SRW만 거리 대미지 축으로 사용해야 한다');
const prepared = optimizer.prepareProblem(compiled, { registry, relevantKeys, pareto:{ maxComparisons:1000000 } });
assert.ok(prepared.metadata.paretoReports.every(report => report.complete), 'N0 fixture requires complete Pareto preparation before runtime measurements');
console.log(`D4 native runtime N0 fixture: PASS (${prepared.groups.map(group => group.packages.length).join('/') } prepared packages, current score ${current.damage.expected}, current violations ${current.constraints.violations.map(item => item.metric).join('/')})`);
