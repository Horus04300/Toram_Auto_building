import { CLASSIC_SCRIPT_PATHS, WEB_CLASSIC_SCRIPT_PATHS } from '../../classic-script-manifest.mjs';
import { createEquipmentItemUi } from '../../ui/item-equipment-ui.mjs';
import { createConsumableBuffUi } from '../../ui/item-consumable-ui.mjs';
import { createBossTargetUi } from '../../ui/boss-target-ui.mjs';

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

export async function loadCalculatorScripts(documentRef, paths = documentRef.documentElement.dataset.runtime === 'desktop' ? CLASSIC_SCRIPT_PATHS : WEB_CLASSIC_SCRIPT_PATHS) {
  for (const path of paths) await loadClassicScript(documentRef,path);
}

export async function initializeCalculator(documentRef, app, workspace) {
  const root = documentRef.defaultView;
  const response = await root.fetch(new URL('../../../pages/calculator.html',import.meta.url));
  if (!response.ok) throw new Error('계산기 화면을 불러오지 못했습니다.');
  workspace.insertAdjacentHTML('beforeend',await response.text());
  app.bossTarget = createBossTargetUi(documentRef,app.bosses);
  app.equipmentItems = createEquipmentItemUi(documentRef,app.items);
  app.consumableBuffs = createConsumableBuffUi(documentRef,app.items);
  root.TORAM_CRYSTA_CATALOG_DATA = await app.items.getCrystaCatalog();
  await loadCalculatorScripts(documentRef);
  app.crystas = root.ToramCrystaCatalog;
  app.equipmentItems.bind(); app.consumableBuffs.bind(); app.bossTarget.bind();
  app.calculatorReady = true;
}
