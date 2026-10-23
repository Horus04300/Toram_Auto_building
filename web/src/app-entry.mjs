import { CLASSIC_SCRIPT_PATHS, WEB_CLASSIC_SCRIPT_PATHS } from './classic-script-manifest.mjs';
import { createItemCatalog, resolveEquipmentOptions, validateEquipmentSelection, resolveConsumableBuffs } from './application/item-catalog.mjs';
import { createEquipmentItemUi } from './ui/item-equipment-ui.mjs';
import { createConsumableBuffUi } from './ui/item-consumable-ui.mjs';
import { createBossCatalog } from './application/boss-catalog.mjs';
import { validateBossSelection } from './application/boss-target.mjs';
import { createBossTargetUi } from './ui/boss-target-ui.mjs';
import { createAccountClient } from './application/account-client.mjs';
import { createAccountUi } from './ui/account-ui.mjs';

export function loadClassicScript(documentRef, path) {
  return new Promise((resolve, reject) => {
    const script = documentRef.createElement('script');
    script.type = 'text/javascript';
    script.async = false;
    script.src = new URL(path, documentRef.baseURI).href;
    script.onload = () => resolve();
    script.onerror = () => reject(new Error(`Classic script failed to load: ${path}`));
    const target = documentRef.head || documentRef.body || documentRef.documentElement;
    if (!target) throw new Error('A document insertion target is required to load legacy scripts.');
    target.appendChild(script);
  });
}

export async function startApplication(documentRef = document, paths = (
  documentRef.documentElement.dataset.runtime === 'desktop' ? CLASSIC_SCRIPT_PATHS : WEB_CLASSIC_SCRIPT_PATHS
)) {
  const windowRef = documentRef.defaultView;
  if (windowRef) {
    windowRef.ToramApp ||= {};
    windowRef.ToramApp.items = createItemCatalog(new URL('assets/game-data/items/manifest.json', documentRef.baseURI));
    windowRef.TORAM_CRYSTA_CATALOG_DATA = await windowRef.ToramApp.items.getCrystaCatalog();
    windowRef.ToramApp.bosses = createBossCatalog(new URL('assets/game-data/bosses/manifest.json', documentRef.baseURI));
    windowRef.ToramApp.bossRules = Object.freeze({ validateBossSelection });
    windowRef.ToramApp.bossTarget = createBossTargetUi(documentRef, windowRef.ToramApp.bosses);
    windowRef.ToramApp.itemRules = Object.freeze({ resolveEquipmentOptions, validateEquipmentSelection, resolveConsumableBuffs });
    windowRef.ToramApp.equipmentItems = createEquipmentItemUi(documentRef, windowRef.ToramApp.items);
    windowRef.ToramApp.consumableBuffs = createConsumableBuffUi(documentRef, windowRef.ToramApp.items);
  }
  for (const path of paths) await loadClassicScript(documentRef, path);
  if (windowRef) windowRef.ToramApp.crystas = windowRef.ToramCrystaCatalog;
  windowRef?.ToramApp.equipmentItems.bind();
  windowRef?.ToramApp.consumableBuffs.bind();
  windowRef?.ToramApp.bossTarget.bind();
  if (documentRef.getElementById('appAccountButton')) {
    windowRef.ToramApp.account = createAccountClient(documentRef);
    createAccountUi(documentRef, windowRef.ToramApp.account).bind();
  }
}

await startApplication();
