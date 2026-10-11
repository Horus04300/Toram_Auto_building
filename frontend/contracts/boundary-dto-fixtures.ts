const storageFixture: SavedBuildDocumentDto = {
  format: 'toram-auto-build-document',
  schemaVersion: 1,
  documentType: 'saved-build',
  name: 'Type boundary fixture',
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

const optimizationRequestFixture: CrystaOptimizationRequestDto = {
  schema: 'toram.crysta-problem.v1',
  baseContext: calculationFixture.baseContext,
  scenarioSnapshot: calculationFixture.scenario,
  groups: [{ id: 'weapon', packages: [{ id: 'weapon:empty', statDelta: {} }] }]
};

const optimizationResultFixture: CrystaOptimizationResultDto = {
  status: 'bounded',
  score: 14089,
  lowerBound: 14089,
  upperBound: 20375,
  continuationId: 'r1b-fixture',
  diagnostics: []
};

const storageAdapterFixture: SettingsFileRepositoryAdapter = {
  directory: async () => 'C:\\Settings',
  list: async () => [{ name: 'Type boundary fixture.json', lastModified: 0 }],
  save: async () => undefined,
  load: async () => JSON.stringify(storageFixture),
  overwrite: async () => undefined,
  delete: async () => undefined
};

void [storageFixture, calculationFixture, calculationResultFixture, optimizationRequestFixture, optimizationResultFixture, storageAdapterFixture];
