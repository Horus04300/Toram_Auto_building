import {createNativeClient} from './optimization-client.js';
import {createSavedBuildFileAdapter} from '../../build/generated/desktop/saved-build-storage.js';
import {createUpdateService} from '../../build/generated/desktop/update.js';
import {createUpdateCoordinator} from './update/update-controller.js';
import {createUpdateUi} from './update/ui-controller.js';
export function createDesktopRuntime(root,app) {
  const core=root.__TAURI__?.core;
  const service=createUpdateService(core);
  return Object.freeze({nativeClient:createNativeClient(core),files:createSavedBuildFileAdapter(core),
    coordinator:createUpdateCoordinator(root,app),initializeUpdates:()=>createUpdateUi(root.document,app,service)});
}
