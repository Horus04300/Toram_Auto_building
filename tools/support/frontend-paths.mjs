// Deployment URLs stay stable while editable sources live under their owning product.
const desktopSources = {
  'assets/js/optimization/native-client.js':'desktop/adapters/optimization-client.js',
  'assets/js/storage/tauri-build-storage-adapter.js':'build/generated/desktop/saved-build-storage.js',
  'assets/js/update/tauri-update-adapter.js':'build/generated/desktop/update.js',
  'assets/js/ui/update-ui-controller.js':'desktop/adapters/update/ui-controller.js'
};

export const FRONTEND_MODULE_PATHS = Object.freeze([
  'assets/js/app-entry.mjs', 'assets/js/classic-script-manifest.mjs', 'assets/js/optimization/wasm-worker.js',
  'assets/js/application/item-catalog.mjs', 'assets/js/ui/item-equipment-ui.mjs', 'assets/js/ui/item-consumable-ui.mjs',
  'assets/js/application/boss-catalog.mjs', 'assets/js/application/boss-target.mjs', 'assets/js/ui/boss-target-ui.mjs',
  'assets/js/application/account-client.mjs', 'assets/js/ui/account-ui.mjs'
]);

export function frontendSourcePath(path) {
  if (desktopSources[path]) return desktopSources[path];
  if (path.startsWith('assets/js/update/')) return path.replace('assets/js/update/', 'desktop/adapters/update/');
  if (path.startsWith('assets/js/')) return path.replace('assets/js/', 'web/src/');
  if (path.startsWith('assets/wasm/')) return path.replace('assets/wasm/', 'build/generated/wasm/');
  if (path.startsWith('assets/')) return path.replace('assets/', 'web/public/');
  return path;
}
