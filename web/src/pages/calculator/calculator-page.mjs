import {initializeCrystaCatalog} from '../../data/crysta-data.js';
import { createEquipmentItemUi } from '../../ui/item-equipment-ui.mjs';
import { createConsumableBuffUi } from '../../ui/item-consumable-ui.mjs';
import { createBossTargetUi } from '../../ui/boss-target-ui.mjs';

export async function initializeCalculator(documentRef, app, workspace) {
  const root = documentRef.defaultView;
  const response = await root.fetch(new URL('../../../pages/calculator.html',import.meta.url));
  if (!response.ok) throw new Error('계산기 화면을 불러오지 못했습니다.');
  workspace.insertAdjacentHTML('beforeend',await response.text());
  app.bossTarget = createBossTargetUi(documentRef,app.bosses);
  app.equipmentItems = createEquipmentItemUi(documentRef,app.items);
  app.consumableBuffs = createConsumableBuffUi(documentRef,app.items);
  app.crystas=initializeCrystaCatalog(await app.items.getCrystaCatalog());
  const desktop=documentRef.documentElement.dataset.runtime === 'desktop'
    ? (await import('../../../../desktop/adapters/calculator-runtime.mjs')).createDesktopRuntime(root,app) : null;
  const {initializeCalculatorUi}=await import('../../ui/ui-bootstrap.js');
  initializeCalculatorUi(documentRef,app,desktop);
  app.equipmentItems.bind(); app.consumableBuffs.bind(); app.bossTarget.bind();
  app.calculatorReady = true;
}
