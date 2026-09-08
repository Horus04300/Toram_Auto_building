type ApplicationUpdateService = import('../application/ports').UpdateService;
type ApplicationUpdateInfo = import('../application/ports').UpdateInfo;
type ApplicationUpdateProgress = import('../application/ports').UpdateProgress;

interface UpdateChannel {
  onmessage: (value: unknown) => void;
}
interface UpdateTauriWindow extends Window {
  __TAURI__?: { readonly core?: {
    invoke(command: string, args?: Readonly<Record<string, unknown>>): Promise<unknown>;
    Channel: new () => UpdateChannel;
  } };
  ToramUpdateService?: ApplicationUpdateService;
}
