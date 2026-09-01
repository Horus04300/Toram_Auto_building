const storageFixture: SavedBuildDocumentDto = {
  format: 'toram-auto-build-document',
  schemaVersion: 1,
  documentType: 'saved-build',
  name: 'R1b fixture',
  createdAt: '2026-09-01T00:00:00.000Z',
  updatedAt: '2026-09-01T00:00:00.000Z',
  build: { character: { level:300 }, equipment: {}, skillLevels: {}, activeBuffs: {}, externalOptions: [], combo: [] },
  scenario: { target: {} }
};

const calculationFixture: CalculationRequestDto = {
  baseContext: { level: 300, mainType: '한손검' },
  scenario: { attackType: 'PHYS', rangeType: 'SHORT' },
  statDelta: { ATKP: 10, CRIT: 5 }
};

const calculationResultFixture: CalculationResultDto = {
  score: 14089,
  diagnostics: [],
  aggregate: { expectedDamage: 14089 }
};

const d4RequestFixture: D4OptimizationRequestDto = {
  schema: 'toram.d4-problem.v1',
  baseContext: calculationFixture.baseContext,
  scenarioSnapshot: calculationFixture.scenario,
  groups: [{ id: 'weapon', packages: [{ id: 'weapon:empty', statDelta: {} }] }]
};

const d4ResultFixture: D4OptimizationResultDto = {
  status: 'bounded',
  score: 14089,
  lowerBound: 14089,
  upperBound: 20375,
  continuationId: 'r1b-fixture',
  diagnostics: []
};

const storageAdapterFixture: SettingsFileRepositoryAdapter = {
  directory: async () => 'C:\\Settings',
  list: async () => [{ name: 'R1b fixture.json', lastModified: 0 }],
  save: async () => undefined,
  load: async () => JSON.stringify(storageFixture),
  overwrite: async () => undefined,
  delete: async () => undefined
};

void [storageFixture, calculationFixture, calculationResultFixture, d4RequestFixture, d4ResultFixture, storageAdapterFixture];
