import assert from 'node:assert/strict';
import { mkdtemp, readFile, rm, writeFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { availableParallelism, tmpdir } from 'node:os';
import { join, resolve } from 'node:path';
import { spawn } from 'node:child_process';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const evaluator = require(resolve(root, 'assets/js/build-evaluator.js'));
const compiler = require(resolve(root, 'assets/js/d4-problem-compiler.js'));
const optimizer = require(resolve(root, 'assets/js/d4-global-optimizer.js'));
const binary = process.env.D4_NATIVE_BINARY || resolve(root, 'src-tauri/target/release/d4_native_parallel.exe');
const logicalThreads = Math.max(1, Number(process.env.NUMBER_OF_PROCESSORS) || availableParallelism());
const requestedThreads = (process.env.D4_P6_THREADS || [1, Math.max(1, Math.floor(logicalThreads / 2)), logicalThreads].join(','))
  .split(',').map(Number).filter(value => Number.isInteger(value) && value > 0)
  .filter((value, index, values) => values.indexOf(value) === index);

function run(command, args) {
  return new Promise((resolvePromise, reject) => {
    const child = spawn(command, args, { cwd:root, stdio:['ignore', 'pipe', 'pipe'] });
    let stdout = '', stderr = '';
    child.stdout.on('data', chunk => { stdout += chunk; });
    child.stderr.on('data', chunk => { stderr += chunk; });
    child.on('error', reject);
    child.on('close', code => code === 0 ? resolvePromise(stdout.trim()) : reject(new Error(`${command} failed (${code}): ${stderr || stdout}`)));
  });
}

const calculationContext = { window:{ ToramStatRegistry:registry }, console };
calculationContext.window.window = calculationContext.window;
vm.createContext(calculationContext);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculation-policies.js'), 'utf8'), calculationContext, { filename:'calculation-policies.js' });
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', calculationContext);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), calculationContext, { filename:'calculator.js' });
const kernel = calculationContext.window.ToramCalculationKernel.evaluateContext;
const baseContext = {
  level:325, strBase:255, intBase:0, vitBase:0, agiBase:0, dexBase:500, crtBase:0,
  mainType:'한손검', wpnAtk:600, wpnRefine:15, wpnStab:80, subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'경량옷',
  bossLevel:325, bossDef:2000, bossMdef:2000, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
  skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'SHORT', chkIsUnsheathe:false, chkGuaranteedCrit:false,
  conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false, spellBurstLevel:0, godspeedWieldLevel:0,
  poisonSources:[], weakenSources:[], targetWeakened:false, attackElement:'none', attackPowerMode:'default', useHigherRangeDamage:false,
  noCritical:false, criticalChanceBonus:0, criticalChanceMultiplier:1, fixedCriticalChance:null, minimumCriticalDamage:0, stabilityBonus:0, physicalPierceSkillBonus:0, magicPierceSkillBonus:0, ignoreDefense:false, ignoreMdef:false, halfMdefIgnored:false,
  strP:0,strF:0,dexP:0,dexF:0,intP:0,intF:0,agiP:0,agiF:0,vitP:0,vitF:0,atkP:0,atkF:0,matkP:0,matkF:0,cdmgP:0,cdmgF:0,critP:0,critF:200,srw:0,lrw:0,unsheatheP:0,unsheatheF:0,elemP:0,damageP:0,watkP:0,watkF:0,baseWpnAtkF:0,physPierce:0,magPierce:0,aspdF:3000,aspdP:0,cspdF:0,cspdP:0,stability:0,motionSpeed:0,castRed:0,maxHpF:20000,maxHpP:0,maxMpF:3000,amprF:200,amprP:0,elementAwakening:false,magicElement:false,
  atkUpSTR:0,atkUpDEX:0,atkUpINT:0,atkUpAGI:0,atkUpVIT:0,matkUpSTR:0,matkUpDEX:0,matkUpINT:0,matkUpAGI:0,matkUpVIT:0,preservedStats:{},statDiagnostics:[],activeBuildConversions:[]
};
const dataContext = {};
vm.createContext(dataContext);
vm.runInContext(`${await readFile(resolve(root, 'assets/js/data/crysta-data.js'), 'utf8')}\nglobalThis.__crystas=crystaDataJson;`, dataContext);
const runtimeFixture=process.env.D4_P6_REVENIR==='1'?JSON.parse(await readFile(resolve(root,'tools/fixtures/d4-native-runtime-26min-revenir.json'),'utf8')).resolvedExecutionContext:null;
if(runtimeFixture)assert.equal(process.env.D4_PROOF_ONLY,'1','Revenir currently supports preparation/proof auditing only; the P6 exact-score oracle is a different fixture');
if(runtimeFixture)Object.assign(baseContext,runtimeFixture.baseContext);
const utilityRequirements = process.env.D4_P6_REQUIREMENTS ? JSON.parse(process.env.D4_P6_REQUIREMENTS) : null;
if (utilityRequirements) assert.ok(process.env.D4_P6_THREAD && (Number(process.env.D4_P6_PACKAGE_LIMIT) > 0 || process.env.D4_P6_REFERENCE_BINARY),
  'custom requirements require sampled exhaustive oracle or a reference binary');
const scenario = evaluator.createScenarioSnapshot(baseContext,utilityRequirements?{requirements:utilityRequirements}:runtimeFixture?{requirements:runtimeFixture.scenarioRequirements}:undefined);
const compiled = compiler.compileCrystaProblem({ crystas:dataContext.__crystas, registry, baseContext, scenarioSnapshot:scenario, currentCrystas:runtimeFixture?runtimeFixture.currentCrystas:[], locks:runtimeFixture?runtimeFixture.locks:[], banned:runtimeFixture?runtimeFixture.banned:{'오로로 콜론':true} });
const adapter = stats => evaluator.evaluateAggregate(baseContext, scenario, stats, kernel);
const relevantKeys = optimizer.deriveRelevantKeys(compiled, registry, adapter);
const preparationStarted = performance.now();
let prepared = optimizer.prepareProblem(compiled, { registry, relevantKeys, evaluateStats:(stats,meta) => meta?.summaryOnly ? evaluator.evaluateAggregateSummary(baseContext,scenario,stats,kernel) : adapter(stats), enableUtilityDominanceAudit:process.env.D4_UTILITY_DOMINANCE_AUDIT === '1', utilityProofNodeLimit:process.env.D4_PROOF_NODES,utilityProofEvaluationLimit:process.env.D4_PROOF_EVALUATIONS,utilityProofComparisonLimit:process.env.D4_PROOF_COMPARISONS, pareto:{maxComparisons:1000000} });
const preparationMs = performance.now()-preparationStarted;
if (prepared.metadata.utilityDominanceAudit) {
  console.log('Utility dominance audit: '+JSON.stringify({...prepared.metadata.utilityDominanceAudit,certificates:undefined,retainedExamples:undefined}));
  if(process.env.D4_PROOF_REPORT)await writeFile(resolve(root,process.env.D4_PROOF_REPORT),JSON.stringify(prepared.metadata.utilityDominanceAudit,null,2));
}
if(process.env.D4_PROOF_ONLY==='1'){console.log(JSON.stringify({preparationMs,packages:prepared.groups.map(group=>group.packages.length)}));process.exit(0);}
assert.ok(prepared.metadata.paretoReports.every(report => report.complete), 'P6 requires a complete prepared fixture');
const packageLimit = Math.floor(Number(process.env.D4_P6_PACKAGE_LIMIT) || 0);
if (packageLimit > 0) {
  assert.ok(process.env.D4_P6_THREAD, 'sampled fixtures require the single measurement/oracle path');
  prepared = {
    ...prepared,
    groups:prepared.groups.map(group => ({
      ...group,
      packages:group.packages.filter((_,index) => index % Math.max(1,Math.floor(group.packages.length/packageLimit)) === 0).slice(0,packageLimit)
    }))
  };
}

const temp = await mkdtemp(join(tmpdir(), 'toram-d4-p6-'));
async function measuredRun(threads, cancelAfterMs, selectedBinary = binary) {
  const tag = cancelAfterMs === null ? `exact-${threads}` : `cancel-${threads}`;
  const input = join(temp, `${tag}.json`), output = join(temp, `${tag}.out`), errorOutput = join(temp, `${tag}.err`);
  await writeFile(input, JSON.stringify({ ...prepared, threads, ...(cancelAfterMs === null ? {} : { cancelAfterMs }) }));
  const measure = JSON.parse(await run('powershell.exe', ['-NoProfile', '-NonInteractive', '-ExecutionPolicy', 'Bypass', '-File', resolve(root, 'tools/measure-d4-native-p6.ps1'), '-Binary', selectedBinary, '-InputPath', input, '-Output', output, '-ErrorOutput', errorOutput]));
  const stderr = await readFile(errorOutput, 'utf8').catch(error => error && error.code === 'ENOENT' ? '' : Promise.reject(error));
  const resultText = await readFile(output, 'utf8');
  let result;
  try { result = JSON.parse(resultText); } catch (error) { throw new Error(`native ${tag} returned invalid JSON: ${stderr || resultText || error.message}`); }
  if (measure.exitCode !== 0 && result.status !== 'exact' && result.status !== 'cancelled' && !(process.env.D4_SESSION_BENCH_MS && result.status === 'bounded')) throw new Error(`native ${tag} failed: ${stderr || resultText}`);
  return { threads, cancelAfterMs, ...measure, result };
}

try {
  if (process.env.D4_P6_THREAD) {
    const threads = Number(process.env.D4_P6_THREAD);
    assert.ok(Number.isInteger(threads) && threads > 0, 'D4_P6_THREAD must be a positive integer');
    const entry = await measuredRun(threads, null);
    const reference = utilityRequirements && !packageLimit
      ? await measuredRun(threads, null, process.env.D4_P6_REFERENCE_BINARY) : null;
    if (reference) {
      assert.equal(entry.result.status, 'exact', 'custom full fixture must finish exactly');
      assert.equal(reference.result.status, 'exact', 'reference must finish exactly');
      assert.equal(entry.result.score, reference.result.score);
      assert.equal(entry.result.bestBuild?.id, reference.result.bestBuild?.id);
      assert.equal(entry.result.upperBound, reference.result.upperBound);
    }
    if (process.env.D4_SESSION_BENCH_MS && entry.result.status === 'bounded') {
      assert.ok(entry.result.upperBound >= 14097);
      assert.ok(entry.result.score === null || entry.result.score <= 14097);
    } else assert.equal(entry.result.status, 'exact', 'single P6 measurement must finish exactly');
    if (!packageLimit) { if (!reference && entry.result.status === 'exact') assert.equal(entry.result.score, 14097, 'single P6 measurement must match the oracle'); }
    else {
      const oracle = optimizer.exhaustiveSearch(prepared,{prepared,evaluateStats:adapter});
      assert.equal(entry.result.score,oracle.score);
      assert.equal(entry.result.bestBuild?.id,oracle.bestBuild?.id);
    }
    const summary = { schema:'toram.d4-native-p6-single.v1', ...(utilityRequirements ? {utilityRequirements, reference} : {}), packageLimit, packages:prepared.groups.map(group => group.packages.length), threads, status:entry.result.status, upperBound:entry.result.upperBound, sessionPreparationMs:entry.result.sessionPreparationMs, sessionWallMs:entry.result.sessionWallMs, sessionBatches:entry.result.sessionBatches, exitCode:entry.exitCode, solverMs:entry.result.elapsedMs, wallMs:entry.wallMs, cpuMs:entry.cpuMs, peakWorkingSetBytes:entry.peakWorkingSetBytes, score:entry.result.score, id:entry.result.bestBuild?.id, visitedNodes:entry.result.visitedNodes, evaluations:entry.result.evaluations, prunedByBound:entry.result.prunedByBound, prunedByConstraint:entry.result.prunedByConstraint, scheduledShards:entry.result.scheduledShards, completedShards:entry.result.completedShards };
    if (process.env.D4_P6_REPORT) await writeFile(resolve(root, process.env.D4_P6_REPORT), JSON.stringify(summary, null, 2));
    console.log(JSON.stringify(summary));
    process.exit(0);
  }
  if (process.env.D4_P6_CANCEL_ONLY === '1') {
    const cancellation = await measuredRun(requestedThreads.at(-1), 100);
    assert.equal(cancellation.result.status, 'cancelled', 'timed cancellation must report cancelled');
    assert.equal(cancellation.result.exact, false, 'cancelled search must never report exact');
    assert.equal(cancellation.result.upperBound, null, 'cancelled search must not expose a proof upper bound');
    const summary = { schema:'toram.d4-native-p6-cancel.v1', threads:requestedThreads.at(-1), wallMs:cancellation.wallMs, solverMs:cancellation.result.elapsedMs, peakWorkingSetBytes:cancellation.peakWorkingSetBytes, status:cancellation.result.status, completedShards:cancellation.result.completedShards, scheduledShards:cancellation.result.scheduledShards };
    if (process.env.D4_P6_REPORT) await writeFile(resolve(root, process.env.D4_P6_REPORT), JSON.stringify(summary, null, 2));
    console.log(JSON.stringify(summary));
    process.exit(0);
  }
  const exact = [];
  for (const threads of requestedThreads) exact.push(await measuredRun(threads, null));
  const cancellation = await measuredRun(requestedThreads.at(-1), 100);
  exact.forEach(entry => {
    assert.equal(entry.result.status, 'exact', `${entry.threads}-thread run must finish exactly`);
    assert.equal(entry.result.score, 14097, `${entry.threads}-thread score must match the oracle`);
    assert.equal(entry.result.bestBuild.id, exact[0].result.bestBuild.id, `${entry.threads}-thread tie result must match`);
    assert.equal(entry.result.completedShards, entry.result.scheduledShards, `${entry.threads}-thread run must complete all shards`);
  });
  assert.equal(cancellation.result.status, 'cancelled', 'timed cancellation must report cancelled');
  assert.equal(cancellation.result.exact, false, 'cancelled search must never report exact');
  assert.equal(cancellation.result.upperBound, null, 'cancelled search must not expose a proof upper bound');
  const baseline = exact.find(entry => entry.threads === 1) || exact[0];
  const full = exact[exact.length - 1];
  assert.ok(full.wallMs < baseline.wallMs, 'full CPU run must beat the single-thread run');
  const summary = {
    schema:'toram.d4-native-p6-benchmark.v1', logicalThreads, fixture:'425 physical-short final-crysta candidates',
    exact:exact.map(entry => ({ threads:entry.threads, exitCode:entry.exitCode, solverMs:entry.result.elapsedMs, wallMs:entry.wallMs, cpuMs:entry.cpuMs, peakWorkingSetBytes:entry.peakWorkingSetBytes, score:entry.result.score, id:entry.result.bestBuild.id, scheduledShards:entry.result.scheduledShards })),
    speedup:Number((baseline.wallMs / full.wallMs).toFixed(3)),
    cancellation:{ wallMs:cancellation.wallMs, solverMs:cancellation.result.elapsedMs, peakWorkingSetBytes:cancellation.peakWorkingSetBytes, status:cancellation.result.status, completedShards:cancellation.result.completedShards, scheduledShards:cancellation.result.scheduledShards }
  };
  if (process.env.D4_P6_REPORT) await writeFile(resolve(root, process.env.D4_P6_REPORT), JSON.stringify(summary, null, 2));
  console.log(JSON.stringify(summary));
} finally {
  await rm(temp, { recursive:true, force:true });
}
