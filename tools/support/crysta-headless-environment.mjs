import { readCrystaDataSource } from './crysta-catalog-source.mjs';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';
import { frontendSourcePath } from './frontend-paths.mjs';

export const root = resolve(import.meta.dirname, '../..');
export const jsSources = [
  'calculation/supplemental-stats.js', 'calculation/option-event-calculator.js', 'calculation/stat-registry.js', 'calculation/calculation-policies.js', 'calculation/calculator.js', 'calculation/build-evaluator.js',
  'optimization/problem-compiler.js', 'optimization/candidate-preparation.js', 'optimization/rust-bridge.js', 'optimization/native-client.js', 'data/crysta-data.js'
];

// Load code/data before timing, just as an already-open application would.
export async function loadHeadlessEnvironment(core, sourceRoot = root) {
  const context = { console, __TAURI__:{ core } };
  context.window = context;
  vm.createContext(context);
  const worker = await readFile(resolve(sourceRoot, 'web/src/ui/crysta-ui.js'), 'utf8');
  const aspdDeclaration = worker.match(/const BASE_ASPD_MAP = \{[^}]+\};/u)?.[0];
  assert.ok(aspdDeclaration, 'Use the existing headless evaluator constants');
  vm.runInContext(aspdDeclaration, context);
  for (const source of jsSources) {
    vm.runInContext(source === 'data/crysta-data.js' ? await readCrystaDataSource(sourceRoot) : await readFile(resolve(sourceRoot, frontendSourcePath('assets/js/' + source)), 'utf8'), context, { filename:source });
  }
  const crystas = vm.runInContext('crystaDataJson', context);
  return {
    context,
    client:context.ToramCrystaOptimizationNativeClient,
    candidates:context.ToramCrystaOptimizationCandidates,
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
