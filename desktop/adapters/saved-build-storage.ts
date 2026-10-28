export function createSavedBuildFileAdapter(core: NonNullable<SettingsRepositoryTauriWindow['__TAURI__']>['core']): SettingsFileRepositoryAdapter | null {
  'use strict';

  const invoke = core?.invoke;
  if (typeof invoke !== 'function') return null;
  const adapter: SettingsFileRepositoryAdapter = Object.freeze({
    directory: () => invoke('settings_directory'),
    list: () => invoke('list_settings'),
    save: (name: string, content: string) => invoke('save_setting', { name, content }),
    load: (name: string) => invoke('load_setting', { name }),
    overwrite: (name: string, content: string) => invoke('overwrite_setting', { name, content }),
    delete: (name: string) => invoke('delete_setting', { name })
  });

  return adapter;
}
