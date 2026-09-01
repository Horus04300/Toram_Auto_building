import type { BuildDraft, CalculationSnapshot, EquipmentSlot } from '../domain/calculation-contracts';

export interface SavedBuildSummary {
  readonly id: string;
  readonly name: string;
  readonly updatedAtEpochMs: number;
}

export interface SavedBuild extends SavedBuildSummary {
  readonly draft: BuildDraft;
}

/** External persistence boundary. File, JSON, Tauri, and browser APIs stay in Infrastructure. */
export interface SettingsRepository {
  list(): Promise<readonly SavedBuildSummary[]>;
  load(id: string): Promise<SavedBuild>;
  save(build: SavedBuild): Promise<SavedBuildSummary>;
  delete(id: string): Promise<void>;
}

/** A compiled D4 request. It contains calculation inputs, never DOM or execution details. */
export interface OptimizationProblem {
  readonly snapshot: CalculationSnapshot;
  readonly excludedCrystaIds: readonly string[];
  readonly lockedCrystas: Readonly<Partial<Record<EquipmentSlot, readonly string[]>>>;
  readonly timeLimitMs: number;
}

export type OptimizationTerminalStatus = 'exact' | 'bounded' | 'no-incumbent-yet' | 'paused' | 'cancelled' | 'invalid';

export interface OptimizationProgress {
  readonly status: 'preparing' | 'running' | OptimizationTerminalStatus;
  readonly elapsedMs: number;
  readonly lowerBound: number | null;
  readonly upperBound: number | null;
  readonly evaluations: number;
  readonly visitedNodes?: number;
  readonly readyWorkItems?: number;
}

export interface OptimizationResult {
  readonly status: OptimizationTerminalStatus;
  readonly recommendedCrystas: Readonly<Partial<Record<EquipmentSlot, readonly string[]>>>;
  readonly lowerBound: number | null;
  readonly upperBound: number | null;
  readonly continuationId: string | null;
  readonly diagnostics: readonly { readonly code: string; readonly message: string }[];
}

/** External Worker/Rust execution boundary; calculation kernel itself is not a Port. */
export interface OptimizationRunner {
  optimize(problem: OptimizationProblem, onProgress: (progress: OptimizationProgress) => void): Promise<OptimizationResult>;
  cancel(reason: string): void;
  pause?(): void;
  resume?(onProgress: (progress: OptimizationProgress) => void): Promise<OptimizationResult>;
  disposeContinuation?(): Promise<void>;
}
