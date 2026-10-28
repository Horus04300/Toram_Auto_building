import {statRegistry} from './calculation/stat-registry.js';
import * as buildValues from './application/build-values.mjs';
import { createItemCatalog, resolveEquipmentOptions, resolveEquipmentElement, validateEquipmentSelection, resolveConsumableBuffs } from './application/item-catalog.mjs';
import { createBossCatalog } from './application/boss-catalog.mjs';
import { validateBossSelection } from './application/boss-target.mjs';
import { createAccountClient } from './application/account-client.mjs';
import { createAccountUi } from './ui/account-ui.mjs';
import { createInventoryUi } from './pages/inventory/inventory-page.mjs';
import { createPlatformShell } from './layout/platform-shell.mjs';
import { createHomePage } from './pages/home/home-page.mjs';
import { createBoardPage } from './pages/board/board-page.mjs';
import { createCatalogPage } from './pages/catalog/catalog-page.mjs';
import { SUB_WEAPON_RULES } from './application/equipment-object.mjs';
import { STAT_LABELS } from './application/stat-labels.mjs';
import { createBookmarkButton } from './ui/bookmark-button.mjs';
import { createSkillTreeSimulator } from './ui/skill-tree-simulator.mjs';

export async function startApplication(documentRef = document) {
  const root = documentRef.defaultView, app = root.ToramApp ||= {};
  app.items = createItemCatalog(new URL('assets/game-data/items/manifest.json',documentRef.baseURI));
  app.bosses = createBossCatalog(new URL('assets/game-data/bosses/manifest.json',documentRef.baseURI));
  app.bossRules = Object.freeze({validateBossSelection});
  app.itemRules = Object.freeze({resolveEquipmentOptions,resolveEquipmentElement,validateEquipmentSelection,resolveConsumableBuffs,subWeaponRules:SUB_WEAPON_RULES});
  app.statLabels = STAT_LABELS;
  app.statRegistry=statRegistry;
  app.buildValues = buildValues;
  app.createBookmarkButton = createBookmarkButton;
  app.createSkillTreeSimulator = createSkillTreeSimulator;
  const shell = createPlatformShell(documentRef);
  let calculator;
  app.ensureCalculator = () => calculator ||= import('./pages/calculator/calculator-page.mjs').then(module => module.initializeCalculator(documentRef,app,shell.calculator));
  app.account = createAccountClient(documentRef);
  shell.register('calculator',shell.calculator,{prepare:app.ensureCalculator});
  createHomePage(documentRef,app.account,shell);
  createCatalogPage(documentRef,app,shell);
  const board = createBoardPage(documentRef,app.account,shell);
  createInventoryUi(documentRef,app.account,shell,board.publish).bind();
  createAccountUi(documentRef,app.account).bind();
  await shell.start();
}

try { await startApplication(); }
catch (error) {
  const status = document.querySelector('.platform-loading');
  if (status) {
    status.querySelector('span').textContent = '화면을 불러오지 못했습니다. 연결을 확인한 뒤 새로고침해 주세요.';
    status.setAttribute('role','alert'); status.hidden = false;
  }
  throw error;
}
