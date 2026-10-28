/** Native settings IPC used by saved-build-storage.ts. */
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

interface SettingsTauriCore {
  invoke(command: 'settings_directory'): Promise<string>;
  invoke(command: 'list_settings'): Promise<readonly TauriSettingFileDto[]>;
  invoke(command: 'save_setting', args: { readonly name: string; readonly content: string }): Promise<void>;
  invoke(command: 'load_setting', args: { readonly name: string }): Promise<string>;
  invoke(command: 'overwrite_setting', args: { readonly name: string; readonly content: string }): Promise<void>;
  invoke(command: 'delete_setting', args: { readonly name: string }): Promise<void>;
}

interface SettingsRepositoryTauriWindow extends Window {
  __TAURI__?: { readonly core?: SettingsTauriCore };
  ToramSettingsFileRepositoryAdapter?: SettingsFileRepositoryAdapter;
}
