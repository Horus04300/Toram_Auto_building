/**
 * R1b legacy boundary DTOs.
 *
 * These describe only the data that currently crosses build, calculation,
 * storage, and D4 boundaries. R2 owns the future application/domain contracts.
 */
interface SavedBuildDocumentDto {
  readonly format: 'toram-auto-build-document';
  readonly schemaVersion: 1;
  readonly documentType: 'saved-build';
  readonly name: string;
  readonly createdAt: string;
  readonly updatedAt: string;
  readonly build: Readonly<Record<string, unknown>>;
  readonly scenario: Readonly<Record<string, unknown>>;
}

interface CalculationRequestDto {
  readonly baseContext: Readonly<Record<string, unknown>>;
  readonly scenario: Readonly<Record<string, unknown>>;
  readonly statDelta: Readonly<Record<string, number>>;
}

interface CalculationResultDto {
  readonly score: number | null;
  readonly diagnostics: readonly { readonly code: string; readonly message: string }[];
  readonly aggregate: Readonly<Record<string, unknown>>;
}

type D4OptimizationStatus = 'exact' | 'bounded' | 'heuristic' | 'no-incumbent-yet' | 'paused' | 'cancelled' | 'invalid';

interface D4CandidatePackageDto {
  readonly id: string;
  readonly statDelta: Readonly<Record<string, number>>;
}

interface D4OptimizationRequestDto {
  readonly schema: string;
  readonly baseContext: Readonly<Record<string, unknown>>;
  readonly scenarioSnapshot: Readonly<Record<string, unknown>>;
  readonly groups: readonly {
    readonly id: string;
    readonly packages: readonly D4CandidatePackageDto[];
  }[];
}

interface D4OptimizationResultDto {
  readonly status: D4OptimizationStatus;
  readonly score: number | null;
  readonly lowerBound: number | null;
  readonly upperBound: number | null;
  readonly continuationId: string | null;
  readonly diagnostics: readonly { readonly code: string; readonly message: string }[];
}

interface TauriSettingFileDto {
  readonly name: string;
  readonly lastModified: number;
}

interface SettingsFileRepositoryAdapter {
  directory(): Promise<string>;
  list(): Promise<readonly TauriSettingFileDto[]>;
  save(name: string, content: string): Promise<void>;
  load(name: string): Promise<string>;
  overwrite(name: string, content: string): Promise<void>;
  delete(name: string): Promise<void>;
}

interface LegacyTauriCore {
  invoke(command: 'settings_directory'): Promise<string>;
  invoke(command: 'list_settings'): Promise<readonly TauriSettingFileDto[]>;
  invoke(command: 'save_setting', args: { readonly name: string; readonly content: string }): Promise<void>;
  invoke(command: 'load_setting', args: { readonly name: string }): Promise<string>;
  invoke(command: 'overwrite_setting', args: { readonly name: string; readonly content: string }): Promise<void>;
  invoke(command: 'delete_setting', args: { readonly name: string }): Promise<void>;
}

interface SettingsRepositoryTauriWindow extends Window {
  __TAURI__?: { readonly core?: LegacyTauriCore };
  ToramSettingsFileRepositoryAdapter?: SettingsFileRepositoryAdapter;
}
