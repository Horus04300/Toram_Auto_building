// Deployment URLs stay stable while editable sources live under their owning product.
const desktopSources = {
  'assets/js/optimization/native-client.js':'desktop/adapters/optimization-client.js',
  'assets/js/storage/tauri-build-storage-adapter.js':'build/generated/desktop/saved-build-storage.js',
  'assets/js/update/tauri-update-adapter.js':'build/generated/desktop/update.js',
  'assets/js/ui/update-ui-controller.js':'desktop/adapters/update/ui-controller.js'
};

export const FRONTEND_MODULE_PATHS = Object.freeze([
  'assets/js/ui/bookmark-button.mjs',
  'assets/js/ui/skill-tree-simulator.mjs', 'assets/js/pages/inventory/inventory-skill-editor.mjs',
  'assets/js/pages/inventory/inventory-navigation.mjs', 'assets/js/pages/inventory/inventory-equipment-editor.mjs', 'assets/js/application/inventory-equipment-draft.mjs',
  'assets/js/pages/calculator/calculator-page.mjs', 'assets/js/application/stat-labels.mjs', 'assets/js/calculation/stat-registry.js',
  'assets/js/app-entry.mjs', 'assets/js/classic-script-manifest.mjs', 'assets/js/optimization/wasm-worker.js',
  'assets/js/application/item-catalog.mjs', 'assets/js/ui/item-equipment-ui.mjs', 'assets/js/ui/item-consumable-ui.mjs',
  'assets/js/application/boss-catalog.mjs', 'assets/js/application/boss-target.mjs', 'assets/js/ui/boss-target-ui.mjs',
  'assets/js/application/account-client.mjs', 'assets/js/ui/account-ui.mjs',
  'assets/js/application/equipment-object.mjs', 'assets/js/pages/inventory/inventory-page.mjs',
  'assets/js/application/inventory-objects.mjs', 'assets/js/application/inventory-merge.mjs', 'assets/js/pages/inventory/inventory-merge-ui.mjs',
  'assets/js/layout/platform-shell.mjs', 'assets/js/pages/home/home-page.mjs',
  'assets/js/application/inventory-summary.mjs', 'assets/js/pages/board/board-page.mjs', 'assets/js/pages/board/publish-dialog.mjs',
  'assets/js/application/catalog-browser.mjs', 'assets/js/pages/catalog/catalog-page.mjs'
]);

export const FRONTEND_PAGE_PATHS = Object.freeze(['assets/pages/calculator.html']);

export function frontendSourcePath(path) {
  if (desktopSources[path]) return desktopSources[path];
  if (path.startsWith('assets/js/update/')) return path.replace('assets/js/update/', 'desktop/adapters/update/');
  if (path.startsWith('assets/js/')) return path.replace('assets/js/', 'web/src/');
  if (path === 'assets/pages/calculator.html') return 'web/src/pages/calculator/calculator.html';
  if (path.startsWith('assets/wasm/')) return path.replace('assets/wasm/', 'build/generated/wasm/');
  if (path.startsWith('assets/')) return path.replace('assets/', 'web/public/');
  return path;
}
