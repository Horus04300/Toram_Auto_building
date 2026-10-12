import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

export const root = resolve(import.meta.dirname, '../..');
export const jsSources = [
  'stat-registry.js', 'calculation-policies.js', 'calculator.js', 'build-evaluator.js',
  'optimization/source-profile.js', 'optimization/marginal-score.js', 'optimization/seed-search.js', 'optimization/pair-partition.js',
  'optimization/problem-compiler.js', 'optimization/exact-solver.js', 'optimization/native-client.js', 'data/crysta-data.js'
];

// Load code/data before timing, just as an already-open application would.
export async function loadHeadlessEnvironment(core) {
  const context = { console, __TAURI__:{ core } };
  context.window = context;
  vm.createContext(context);
  const worker = await readFile(resolve(root, 'assets/js/optimization/solver-worker.js'), 'utf8');
  const aspdDeclaration = worker.match(/const BASE_ASPD_MAP = \{[^}]+\};/u)?.[0];
  assert.ok(aspdDeclaration, 'Use the existing headless evaluator constants');
  vm.runInContext(aspdDeclaration, context);
  for (const source of jsSources) {
    vm.runInContext(await readFile(resolve(root, 'assets/js', source), 'utf8'), context, { filename:source });
  }
  const crystas = vm.runInContext('crystaDataJson', context);
  return {
    client:context.ToramCrystaOptimizationNativeClient,
    optimizer:context.ToramCrystaOptimizationGlobalOptimizer,
    registry:context.ToramStatRegistry, evaluator:context.ToramBuildEvaluator, kernel:context.ToramCalculationKernel,
    compile(input) {
      const scenario = context.ToramBuildEvaluator.createScenarioSnapshot(input.baseContext, {
        requirements:input.scenarioRequirements
      });
      return context.ToramCrystaOptimizationProblemCompiler.compileCrystaProblem({
        registry:context.ToramStatRegistry, crystas:input.crystas || crystas,
        baseContext:input.baseContext, scenarioSnapshot:scenario,
        currentCrystas:input.currentCrystas || [], locks:input.locks || [],
        banned:input.banned || {}, excluded:input.excluded || [], keepLowerUpgrades:Boolean(input.keepLowerUpgrades)
      });
    }
  };
}
