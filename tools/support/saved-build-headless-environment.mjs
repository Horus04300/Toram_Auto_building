import * as kernel from '../../web/src/calculation/calculator.js';
import {application,createCalculationContext,applyPassiveSkillStats} from '../../web/src/application/application-use-cases.js';
import {buildStore} from '../../web/src/application/build-draft-store.js';
import {skillEffects} from '../../web/src/calculation/skill-effect-engine.js';
import {skillRegistry} from '../../web/src/data/skill-effect-registry.js';
import {skillCatalog} from '../../web/src/data/skill-combat-catalog.js';
import {skillTreeData} from '../../web/src/data/skill-tree-data.js';
import {foodCatalog} from '../../web/src/data/my-room-food.js';
import {policies} from '../../web/src/calculation/calculation-policies.js';
import {statRegistry} from '../../web/src/calculation/stat-registry.js';
import {buildEvaluator} from '../../web/src/calculation/build-evaluator.js';
import {comboSequence} from '../../web/src/calculation/combo-sequence-engine.js';
import {problemCompiler} from '../../web/src/optimization/problem-compiler.js';
import {initializeCrystaCatalog} from '../../web/src/data/crysta-data.js';
import {createSettingsRepository} from '../../web/src/storage/settings-repository.js';
import {readCrystaCatalog} from './crysta-catalog-source.mjs';

// These are real module exports. The object is a convenient test/benchmark handle, not a VM or browser global.
export async function loadSavedBuildEnvironment() {
  const catalog=initializeCrystaCatalog(await readCrystaCatalog());
  const context={...kernel,createCalculationContext,applyPassiveSkillStats,ToramCalculationKernel:kernel.calculationKernel,ToramApplication:application,ToramBuildDraftStore:buildStore,ToramSkillEffects:skillEffects,
    ToramSkillEffectRegistry:skillRegistry,TORAM_SKILL_COMBAT_CATALOG:skillCatalog,SKILL_TREE_DATA:skillTreeData,
    ToramFoodCatalog:foodCatalog,ToramCalculationPolicies:policies,ToramStatRegistry:statRegistry,ToramBuildEvaluator:buildEvaluator,
    ToramComboSequence:comboSequence,ToramCrystaOptimizationProblemCompiler:problemCompiler,ToramCrystaCatalog:catalog};
  context.window=context;
  context.ToramSettingsRepository=createSettingsRepository(context,{read:()=>context.ToramBuildDraftStore.read(),syncFromUi:()=>context.ToramBuildDraftStore.syncFromUi(),restoreSession:session=>context.ToramBuildDraftStore.restoreSession(session)});
  return context;
}
