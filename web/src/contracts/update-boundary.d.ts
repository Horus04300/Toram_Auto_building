interface UpdateInfo {
  readonly currentVersion: string;
  readonly version: string;
  readonly notes: string | null;
  readonly publishedAt: string | null;
}

interface UpdateProgress {
  readonly downloaded: number;
  readonly total: number | null;
}

/** Desktop updates are independent of calculation inputs and results. */
interface UpdateService {
  isAvailable(): boolean;
  check(): Promise<UpdateInfo | null>;
  install(version: string, onProgress: (progress: UpdateProgress) => void,
    beforeInstall: () => Promise<void>): Promise<void>;
}

interface UpdateChannel {
  onmessage: (value: unknown) => void;
}
interface UpdateTauriWindow extends Window {
  __TAURI__?: { readonly core?: {
    invoke(command: string, args?: Readonly<Record<string, unknown>>): Promise<unknown>;
    Channel: new () => UpdateChannel;
  } };
  ToramUpdateService?: UpdateService;
}
