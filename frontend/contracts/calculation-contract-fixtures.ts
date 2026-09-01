import type {
  BuildDraft,
  CalculationResult,
  CalculationSnapshot,
  EquipmentSlot
} from '../domain/calculation-contracts';
import type {
  OptimizationRunner,
  SavedBuild,
  SettingsRepository
} from '../application/ports';

const emptyPiece = {
  type: null,
  attack: null,
  refinement: null,
  stability: null,
  options: [],
  crystas: [],
  lockedCrystaSlots: []
} as const;

const equipment: Record<EquipmentSlot, typeof emptyPiece> = {
  mainWeapon: emptyPiece,
  subWeapon: emptyPiece,
  armor: emptyPiece,
  additional: emptyPiece,
  special: emptyPiece
};

const build: BuildDraft = {
  character: { level: 300, attributes: { STR: 1, INT: 1, VIT: 1, AGI: 1, DEX: 1, CRT: 1 } },
  equipment,
  skillLevels: { 'Blade:0': 10 },
  activeBuffs: { 'Blade:16': { active: true, stacks: 0 } },
  externalOptions: [],
  combo: [{ skillId: 'Blade:0', tag: 'none', includeSpecialAttack: false, inputs: {} }]
};

const snapshot: CalculationSnapshot = {
  build,
  scenario: { target: { level: 300, defense: 1000 }, conditions: { targetWeakened: false } },
  request: { selectedSkillId: 'Blade:0', selectedHitId: 'main', overrides: {} }
};

const result: CalculationResult = {
  status: 'ok',
  snapshot,
  values: { expectedDamage: 14089 },
  diagnostics: []
};

const savedBuild: SavedBuild = { id: 'r2-fixture', name: 'R2 fixture', updatedAtEpochMs: 0, draft: build };

const settingsRepository: SettingsRepository = {
  list: async () => [savedBuild],
  load: async () => savedBuild,
  save: async (entry) => entry,
  delete: async () => undefined
};

const optimizationRunner: OptimizationRunner = {
  optimize: async (problem, onProgress) => {
    onProgress({ status: 'preparing', elapsedMs: 0, lowerBound: null, upperBound: null, evaluations: 0 });
    return {
      status: 'bounded',
      recommendedCrystas: problem.lockedCrystas,
      lowerBound: 14089,
      upperBound: 20375,
      continuationId: 'r2-fixture',
      diagnostics: []
    };
  },
  cancel: () => undefined,
  pause: () => undefined,
  resume: async onProgress => {
    onProgress({ status: 'running', elapsedMs: 1, lowerBound: 14089, upperBound: 20375, evaluations: 1 });
    return { status: 'exact', recommendedCrystas: {}, lowerBound: 14089, upperBound: 14089, continuationId: null, diagnostics: [] };
  },
  disposeContinuation: async () => undefined
};

void [result, settingsRepository, optimizationRunner];
