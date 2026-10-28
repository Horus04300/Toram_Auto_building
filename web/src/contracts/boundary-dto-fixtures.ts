declare const storageBoundary: SettingsFileRepositoryAdapter;
storageBoundary.save('build', '{}');
// @ts-expect-error Native file writes require serialized JSON.
storageBoundary.save('build', {});

declare const settingsIpc: SettingsTauriCore;
settingsIpc.invoke('save_setting', {name:'build', content:'{}'});
// @ts-expect-error Settings IPC must retain its command argument contract.
settingsIpc.invoke('save_setting', {name:'build'});
// @ts-expect-error Unknown commands cannot cross the settings adapter.
settingsIpc.invoke('save_anything', {});

declare const updateBoundary: UpdateService;
updateBoundary.install('0.7.3', progress => { void progress.downloaded; }, async () => {});
// @ts-expect-error Download counters must be numeric.
const invalidProgress: UpdateProgress = {downloaded:'1', total:null};
void invalidProgress;
