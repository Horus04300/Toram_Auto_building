import { frontendSourcePath } from '../support/frontend-paths.mjs';
import assert from 'node:assert/strict';
import { readFile, writeFile, mkdir } from 'node:fs/promises';
import { resolve, dirname } from 'node:path';
import { spawn } from 'node:child_process';
import { createHash } from 'node:crypto';
import { cpus } from 'node:os';
import { parseArgs } from 'node:util';
import { root, jsSources, loadHeadlessEnvironment } from '../support/crysta-headless-environment.mjs';
import { loadSavedBuildEnvironment } from '../support/saved-build-headless-environment.mjs';
import { createHeadlessTransport } from '../support/crysta-headless-transport.mjs';
import { measureComputation } from '../support/crysta-computation-measurement.mjs';
import { CLASSIC_SCRIPT_PATHS as runtimeScripts } from '../../web/src/classic-script-manifest.mjs';
const CLASSIC_SCRIPT_PATHS = runtimeScripts.map(frontendSourcePath);

const { values } = parseArgs({ options:{ child:{type:'boolean'}, case:{type:'string'}, disabled:{type:'boolean'}, 'compare-projection':{type:'boolean'},
  repeats:{type:'string',default:'3'}, 'max-ms':{type:'string',default:'120000'},
  output:{type:'string',default:'desktop/target/user-sample-benchmark/latest.json'} } });
const directory = resolve(root, 'desktop/target/user-sample-benchmark');
const binary = resolve(root, 'desktop/target/release/crysta_headless_service' + (process.platform === 'win32' ? '.exe' : ''));
const hash = data => createHash('sha256').update(data).digest('hex');
const cases = ['magic-device', 'magic-staff', 'revenir'];
const maxDurationMs = Number(values['max-ms']);
assert.ok(maxDurationMs > 0 && maxDurationMs <= 3600000);
const inputPath = id => resolve(directory, `input-${id}.json`);
const sourcePaths = [...new Set([...jsSources.map(path => frontendSourcePath('assets/js/' + path)),
  ...CLASSIC_SCRIPT_PATHS.filter(path => path.startsWith('web/src/data/')),
  'web/src/classic-script-manifest.mjs', 'web/src/calculation/skill-effect-engine.js', 'web/src/ui/crysta-ui.js',
  'web/src/calculation/combo-sequence-engine.js', 'web/src/application/application-use-cases.js', 'web/src/storage/settings-repository.js',
  'tools/support/saved-build-headless-environment.mjs', 'tools/support/crysta-headless-environment.mjs',
  'tools/support/crysta-catalog-source.mjs', 'web/public/game-data/items/manifest.json',
  'tools/support/crysta-headless-transport.mjs', 'tools/support/crysta-computation-measurement.mjs',
  'tools/benchmarks/benchmark-crysta-user-samples.mjs'])];
async function hashes(paths) {
  return Object.fromEntries(await Promise.all(paths.map(async path => [path,
    hash((await readFile(resolve(root, path), 'utf8')).replaceAll('\r\n', '\n'))])));
}

if (values.child) {
  assert.ok(cases.includes(values.case));
  const input = JSON.parse(await readFile(inputPath(values.case), 'utf8')).resolvedExecutionContext;
  const transport = createHeadlessTransport(binary);
  let started, preparationSyncMs, compiled, prepared, invocationStarted, nativeReturned;
  const progress = [], commands = [];
  const core = { Channel:transport.core.Channel, async invoke(command, args) {
    const before = performance.now();
    if (command === 'crysta_optimize_parallel') { prepared = args.problem; invocationStarted = before; }
    const result = await transport.core.invoke(command, args);
    const after = performance.now();
    commands.push({ command, startedMs:before-started, durationMs:after-before });
    if (command === 'crysta_optimize_parallel' || command === 'resume_crysta_optimization') nativeReturned = after;
    return result;
  } };
  try {
    const env = await loadHeadlessEnvironment(core);
    function capture(callbacks) {
      return { ...callbacks, onProgress(event) { progress.push({ wallMs:performance.now()-started, ...event }); callbacks.onProgress(event); } };
    }
    const client = { ...env.client,
      optimize(problem, callbacks, options) {
        const before = performance.now();
        const pending = env.client.optimize(problem, capture(callbacks), { ...options, disableCandidateProjection:Boolean(values.disabled) });
        preparationSyncMs = performance.now()-before;
        return pending;
      },
      resume(callbacks, options) { return env.client.resume(capture(callbacks), options); }
    };
    started = performance.now();
    const { result, timing } = await measureComputation({ compile:() => (compiled = env.compile(input)), client, maxDurationMs });
    assert.equal(timing.cached, false);
    if (result.bestBuild) {
      assert.equal(result.outcomes.constraints.feasible, true);
      assert.equal(result.outcomes.damage.expected, result.score);
      const stats = {};
      for (const candidate of result.bestBuild.packages) for (const [key, value] of Object.entries(candidate.statDelta)) stats[key] = (stats[key] || 0) + value;
      assert.deepEqual(result.bestBuild.statDelta, stats);
    }
    if (result.exact) assert.equal(result.upperBound, result.score);
    await writeFile(resolve(directory, `prepared-${values.case}-${values.disabled ? 'off' : 'on'}.json`), JSON.stringify(prepared));
    console.log(JSON.stringify({ case:values.case, projectionEnabled:!values.disabled, timing,
      stages:{ clientPreparationSyncMs:preparationSyncMs, nativeInvocationStartMs:invocationStarted-started,
        finalRestorationMs:timing.totalMs-(nativeReturned-started) }, commands,
      status:result.status, exact:result.exact, nativeElapsedMs:result.elapsedMs, score:result.score,
      lowerBound:result.lowerBound, upperBound:result.upperBound, optimalityGap:result.optimalityGap,
      visitedNodes:result.visitedNodes, evaluations:result.evaluations, remainingNodes:result.remainingNodes,
      rawCounts:compiled.groups.map(group => group.packages.length), preparedCounts:prepared.groups.map(group => group.packages.length),
      frontierReports:result.frontierReports, projection:result.candidateProjectionReport,
      best:result.bestBuild && { id:result.bestBuild.id, stats:result.bestBuild.statDelta },
      progress, hardware:transport.metadata.hardwareProfile, versions:env.client.cachePolicy }));
  } finally { await transport.close(); }
} else {
  const repeats = Number(values.repeats);
  assert.ok(Number.isInteger(repeats) && repeats > 0 && repeats <= 100);
  const selected = values.case ? [values.case] : cases;
  assert.ok(selected.every(id => cases.includes(id)));
  const stamp = JSON.parse(await readFile(binary + '.measurement.json', 'utf8'));
  assert.deepEqual(await hashes(Object.keys(stamp.sources)), stamp.sources, 'Rebuild measurement service after Rust changes');
  assert.equal(hash(await readFile(binary)), stamp.binaryHash);
  await mkdir(directory, { recursive:true });
  const savedEnv = await loadSavedBuildEnvironment();
  const inputs = {};
  for (const [id, name] of [['magic-device','마법) 인힘 마도구'], ['magic-staff','마법) 지팡이 크법 세팅']]) {
    const file = `samples/${name} - pelio s.json`, text = await readFile(resolve(root, file), 'utf8');
    const sample = savedEnv.ToramSettingsRepository.parseSavedBuild(text);
    const original = JSON.stringify(sample);
    savedEnv.skillSimulatorState = { getInvestments:() => sample.build.skillLevels };
    const current = savedEnv.ToramApplication.CalculateBuild(sample);
    const combo = savedEnv.ToramComboSequence.evaluate(sample.build.combo, current.snapshot.baseContext, current.combat,
      { maxMp:current.calculation.finalMaxMP, activeBuffs:sample.build.activeBuffs });
    const entry = combo.entries.find(entry => entry.skillId === 'Magic:11');
    assert.equal(entry.executionStatus, 'executed');
    assert.equal(sample.build.combo.find(entry => entry.skillId === 'Magic:11').inputs.charge, 200);
    const hit = entry.hits[0];
    const appliedComboHit = savedEnv.ToramApplication.ApplyComboHit(hit, entry.damageMultiplier, entry.appliedNextSkillModifiers, entry.skill);
    const snapshot = savedEnv.ToramApplication.CreateCalculationSnapshot({ ...sample, request:{ overrides:{ appliedComboHit } } });
    assert.equal(snapshot.baseContext.atkType, 'MAG');
    assert.equal(snapshot.baseContext.appliedSkillId, 'Magic:11');
    assert.equal(JSON.stringify(sample), original, 'Preserve supplied sample');
    const slots = ['mainWeapon','armor','additional','special'];
    const requirements = Object.assign({}, savedEnv.ToramBuildEvaluator.defaultRequirements(snapshot.baseContext), sample.scenario.optimizationPreferences.requirements);
    inputs[id] = { provenance:{ file, sha256:hash(text), selectedSkill:'Magic:11', selectedHit:hit.id, charge:200, tag:'smite',
      scope:'one selected hit, identical to applying that hit in the app; original locks/requirements/bans retained' },
      resolvedExecutionContext:{ baseContext:snapshot.baseContext, scenarioRequirements:requirements,
        currentCrystas:slots.flatMap(slot => sample.build.equipment[slot].crystas),
        locks:slots.flatMap(slot => sample.build.equipment[slot].lockedCrystaSlots),
        banned:Object.fromEntries(sample.scenario.optimizationPreferences.bannedCrystas.map(name => [name,true])) } };
  }
  const revenirFile = 'tools/fixtures/crysta-saved-sword-shield-revenir-unlocked.json';
  const revenirText = await readFile(resolve(root, revenirFile), 'utf8');
  inputs.revenir = JSON.parse(revenirText);
  inputs.revenir.provenance = { ...inputs.revenir.provenance, file:revenirFile, fixtureHash:hash(revenirText) };
  for (const id of cases) await writeFile(inputPath(id), JSON.stringify(inputs[id], null, 2) + '\n');
  const sources = await hashes(sourcePaths);
  const report = { schema:'toram.crysta-user-sample-benchmark.v1', date:new Date().toISOString(),
    environment:{ node:process.version, cpu:cpus()[0]?.model, logicalThreads:cpus().length, platform:process.platform },
    method:{ repeats, maxDurationMs, projectionEnabled:values['compare-projection'] ? 'alternating OFF/ON' : !values.disabled, boundary:'raw compile through final product-client JS evaluation, UI excluded',
      cache:'fresh Node and Rust process per sample', threads:'product hardware default', progressIntervalMs:100 },
    binaryHash:stamp.binaryHash, rustSourceHashes:stamp.sources, jsSourceHashes:sources, inputs, runs:[], summary:{} };
  const output = resolve(root, values.output);
  await mkdir(dirname(output), { recursive:true });
  async function run(id, disabled) {
    return new Promise((yes,no) => {
      const child = spawn(process.execPath, [import.meta.filename,'--child','--case',id,'--max-ms',String(maxDurationMs), ...(disabled ? ['--disabled'] : [])],
        { cwd:root, windowsHide:true, stdio:['ignore','pipe','pipe'] });
      let out = '', err = '';
      const timer = setTimeout(() => {
        if (process.platform === 'win32') spawn('taskkill',['/pid',String(child.pid),'/t','/f'],{windowsHide:true,stdio:'ignore'}); else child.kill();
        no(new Error(`Watchdog expired: ${id}`));
      }, maxDurationMs + 90000);
      child.stdout.on('data',data => out += data); child.stderr.on('data',data => err += data);
      child.on('error',error => { clearTimeout(timer); no(error); });
      child.on('close',code => { clearTimeout(timer); if (code) no(new Error(err || out)); else { try { yes(JSON.parse(out)); } catch(error) { no(error); } } });
    });
  }
  for (let repeat = 1; repeat <= repeats; repeat++) for (const id of selected) for (const disabled of
    values['compare-projection'] ? (repeat % 2 ? [true,false] : [false,true]) : [Boolean(values.disabled)]) {
    const sample = await run(id, disabled);
    const prior = report.runs.find(run => run.case === id && run.exact);
    if (prior && sample.exact) { assert.equal(sample.score, prior.score); assert.deepEqual(sample.best, prior.best); }
    report.runs.push({ repeat, ...sample });
    const summaryKey = id + (values['compare-projection'] ? (disabled ? ':off' : ':on') : '');
    const runs = report.runs.filter(run => run.case === id && run.projectionEnabled === !disabled), times = runs.map(run => run.timing.totalMs).sort((a,b) => a-b);
    const mean = values => values.reduce((a,b) => a+b,0)/values.length;
    report.summary[summaryKey] = { count:runs.length, exactCount:runs.filter(run => run.exact).length, meanMs:mean(times),
      minMs:times[0], maxMs:times.at(-1), p95Ms:times[Math.ceil(times.length*.95)-1],
      compileMs:mean(runs.map(run => run.timing.compileMs)), preparationSyncMs:mean(runs.map(run => run.stages.clientPreparationSyncMs)),
      nativeMs:mean(runs.map(run => run.nativeElapsedMs)), visitedNodes:mean(runs.map(run => run.visitedNodes)),
      evaluations:mean(runs.map(run => run.evaluations)), score:sample.score, gap:sample.optimalityGap,
      rawCounts:sample.rawCounts, preparedCounts:sample.preparedCounts };
    assert.deepEqual(await hashes(sourcePaths), sources, 'JS changed during measurement');
    assert.deepEqual(await hashes(Object.keys(stamp.sources)), stamp.sources, 'Rust changed during measurement');
    await writeFile(output, JSON.stringify(report, null, 2) + '\n');
    console.log(JSON.stringify({ case:summaryKey, repeat, ...report.summary[summaryKey] }));
  }
  console.log(`Report: ${output}`);
}
