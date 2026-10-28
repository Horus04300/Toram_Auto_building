import {rustBridge} from '../../web/src/optimization/rust-bridge.js';
import {resolve} from 'node:path';
import {sourceModuleFiles} from './frontend-paths.mjs';
import {loadSavedBuildEnvironment} from './saved-build-headless-environment.mjs';
import {createNativeClient} from '../../desktop/adapters/optimization-client.js';
import {candidatePreparation} from '../../web/src/optimization/candidate-preparation.js';
export const root=resolve(import.meta.dirname,'../..');
export const jsSources=await sourceModuleFiles(['web/src/application/application-use-cases.js','web/src/optimization/problem-compiler.js','web/src/optimization/candidate-preparation.js','desktop/adapters/optimization-client.js']);
export async function loadHeadlessEnvironment(core) {
  const context=await loadSavedBuildEnvironment(),client=createNativeClient(core);
  context.ToramCrystaOptimizationNativeClient=client;
  context.ToramCrystaOptimizationRustBridge=rustBridge;
  context.ToramCrystaOptimizationCandidates=candidatePreparation;
  return {context,client,rustBridge,candidates:candidatePreparation,registry:context.ToramStatRegistry,evaluator:context.ToramBuildEvaluator,kernel:context.ToramCalculationKernel,
    compile(input) {
      const scenario=context.ToramBuildEvaluator.createScenarioSnapshot(input.baseContext,{requirements:input.scenarioRequirements});
      return context.ToramCrystaOptimizationProblemCompiler.compileCrystaProblem({registry:context.ToramStatRegistry,crystas:input.crystas||context.ToramCrystaCatalog.items,
        baseContext:input.baseContext,scenarioSnapshot:scenario,currentCrystas:input.currentCrystas||[],locks:input.locks||[],banned:input.banned||{},excluded:input.excluded||[],keepLowerUpgrades:Boolean(input.keepLowerUpgrades)});
    }
  };
}
