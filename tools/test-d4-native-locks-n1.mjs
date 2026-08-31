import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import { spawn } from 'node:child_process';

const root = resolve(import.meta.dirname, '..');
const fixture = JSON.parse(await readFile(resolve(root, 'tools/fixtures/d4-native-runtime-26min-revenir.json'), 'utf8'));
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const compiler = require(resolve(root, 'assets/js/d4-problem-compiler.js'));
const crystaSource = await readFile(resolve(root, 'assets/js/data/crysta-data.js'), 'utf8');
const crystas = Function(`${crystaSource}\nreturn crystaDataJson;`)();

function runNative(problem) {
  return new Promise((resolvePromise, reject) => {
    const child = spawn('cargo', ['run', '--release', '--quiet', '--manifest-path', 'src-tauri/Cargo.toml', '--bin', 'd4_native_parallel'], { cwd:root, stdio:['pipe', 'pipe', 'pipe'] });
    let stdout = '', stderr = '';
    child.stdout.on('data', chunk => { stdout += chunk; });
    child.stderr.on('data', chunk => { stderr += chunk; });
    child.on('error', reject);
    child.on('close', code => {
      if (code !== 0) return reject(new Error(`native lock regression exited ${code}: ${stderr}`));
      try { resolvePromise(JSON.parse(stdout)); } catch (error) { reject(new Error(`native lock regression returned invalid JSON: ${error.message}\n${stdout}\n${stderr}`)); }
    });
    child.stdin.end(JSON.stringify(problem));
  });
}

const input = fixture.resolvedExecutionContext;
const neutralScenario = { requirements:{ maxHp:null, maxMp:null, amprBeforeDual:null, normalAttackCrit:null, aspd:null } };
const emptySlots = Array(8).fill(null);
const specialEtowal = [...emptySlots]; specialEtowal[6] = '에투왈';
const specialPair = [...specialEtowal]; specialPair[7] = '오르그';
const cases = [
  { id:'unlocked', current:emptySlots, locks:Array(8).fill(false), expected:[] },
  { id:'one-special-lock', current:specialEtowal, locks:[false, false, false, false, false, false, true, false], expected:['에투왈'] },
  { id:'two-special-locks', current:specialPair, locks:[false, false, false, false, false, false, true, true], expected:['에투왈', '오르그'] },
  { id:'eight-empty-locks', current:emptySlots, locks:Array(8).fill(true), expected:[] }
];

for (const lockCase of cases) {
  const compiled = compiler.compileCrystaProblem({
    crystas,
    registry,
    baseContext:input.baseContext,
    scenarioSnapshot:neutralScenario,
    currentCrystas:lockCase.current,
    locks:lockCase.locks,
    banned:input.banned
  });
  assert.deepEqual(compiled.diagnostics, [], `${lockCase.id} must compile before native invocation`);
  const reduced = {
    baseContext:compiled.baseContext,
    scenarioSnapshot:neutralScenario,
    metadata:compiled.metadata,
    groups:compiled.groups.map(group => ({ id:group.id, packages:group.packages.slice(0, 2) }))
  };
  assert.ok(reduced.groups.every(group => group.packages.length > 0), `${lockCase.id} must retain a finite native candidate domain`);
  const native = await runNative(reduced);
  assert.equal(native.status, 'exact', `${lockCase.id} native result must finish exactly`);
  assert.ok(native.bestBuild, `${lockCase.id} native result must retain a build`);
  native.bestBuild.packageIds.forEach((packageId, groupIndex) => {
    assert.ok(reduced.groups[groupIndex].packages.some(candidate => candidate.id === packageId), `${lockCase.id} native result must restore a package from its input group`);
  });
  const expectedStatDelta = native.bestBuild.packageIds.reduce((total, packageId, groupIndex) => {
    const selected = reduced.groups[groupIndex].packages.find(candidate => candidate.id === packageId);
    Object.entries(selected.statDelta).forEach(([key, value]) => { total[key] = (total[key] || 0) + value; });
    return total;
  }, {});
  assert.deepEqual(native.bestBuild.statDelta, expectedStatDelta, `${lockCase.id} must add each selected package stat delta exactly once`);
  const specialPackage = compiled.groups[3].packages.find(candidate => candidate.id === native.bestBuild.packageIds[3]);
  assert.ok(specialPackage, `${lockCase.id} native special result must resolve to the compiler package`);
  const expectedNames = lockCase.expected;
  assert.ok(expectedNames.every(name => specialPackage.candidateNames.includes(name)), `${lockCase.id} must not replace a locked special crysta`);
}

const unknown = [...emptySlots]; unknown[6] = 'N1-unknown-locked-crysta';
const invalid = compiler.compileCrystaProblem({ crystas, registry, baseContext:input.baseContext, scenarioSnapshot:neutralScenario, currentCrystas:unknown, locks:[false, false, false, false, false, false, true, false], banned:input.banned });
assert.ok(invalid.diagnostics.some(item => item.code === 'UNKNOWN_LOCKED_CRYSTA'), 'an unknown locked crysta must be rejected before native invocation');

console.log('D4 native locks N1: PASS (0/1/2/8 locks retain compiler packages through exact native results)');
