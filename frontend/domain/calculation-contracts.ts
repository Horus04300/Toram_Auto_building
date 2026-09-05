/**
 * R2 pure calculation contracts.
 *
 * These types deliberately contain no DOM, Tauri, storage-format, Worker, or
 * UI-runtime state. They describe the values Application code may pass to the
 * calculation kernel in later phases without moving that kernel today.
 */
export interface BuildValueMap {
  readonly [key: string]: BuildValue;
}

export type BuildValue = string | number | boolean | null | readonly BuildValue[] | BuildValueMap;

export type EquipmentSlot = 'mainWeapon' | 'subWeapon' | 'armor' | 'additional' | 'special';

export interface StatOptionDraft {
  readonly key: string;
  readonly value: number;
}

export interface EquipmentPieceDraft {
  readonly type: string | null;
  readonly attack: number | null;
  readonly refinement: number | null;
  readonly stability: number | null;
  readonly options: readonly StatOptionDraft[];
  readonly crystas: readonly string[];
  readonly lockedCrystaSlots: readonly boolean[];
}

export interface BuildDraft {
  /** Persistable player-selected build data only; never UI or task runtime state. */
  readonly character: {
    readonly level: number;
    readonly attributes: Readonly<Record<'STR' | 'INT' | 'VIT' | 'AGI' | 'DEX' | 'CRT', number>>;
  };
  readonly equipment: Readonly<Record<EquipmentSlot, EquipmentPieceDraft>>;
  readonly skillLevels: Readonly<Record<string, number>>;
  readonly activeBuffs: Readonly<Record<string, { readonly active: boolean; readonly stacks: number }>>;
  readonly externalOptions: readonly StatOptionDraft[];
  readonly combo: readonly {
    readonly skillId: string;
    readonly tag: string;
    readonly includeSpecialAttack: boolean;
    readonly inputs: Readonly<Record<string, BuildValue>>;
  }[];
}

export interface ScenarioContext {
  readonly target: Readonly<Record<string, number | boolean | string>>;
  readonly conditions: Readonly<Record<string, BuildValue>>;
  readonly optimizationPreferences?: {
    readonly rangeOverride: 'SHORT' | 'LONG' | null;
    /** null disables the corresponding hard constraint; an omitted key follows the dynamic default. */
    readonly requirements: Readonly<Record<string, number | null>>;
    readonly bannedCrystas: readonly string[];
  };
}

/** Conditions for one calculation only; they must not be persisted in BuildDraft. */
export interface CalculationRequest {
  readonly selectedSkillId: string | null;
  readonly selectedHitId: string | null;
  readonly overrides: Readonly<Record<string, BuildValue>>;
}

export interface CalculationSnapshot {
  readonly build: BuildDraft;
  readonly scenario: ScenarioContext;
  readonly request: CalculationRequest;
}

export interface CalculationDiagnostic {
  readonly code: string;
  readonly message: string;
}

export interface CalculationResult {
  readonly status: 'ok' | 'invalid';
  readonly snapshot: CalculationSnapshot;
  readonly values: Readonly<Record<string, number>>;
  readonly diagnostics: readonly CalculationDiagnostic[];
}
