// Source UI integration; requires CODEX_PLAYWRIGHT_PATH, runs headless Chrome.
import assert from 'node:assert/strict';
import { createWebDevServer } from '../web-dev.mjs';
import { mkdir } from 'node:fs/promises';
import { resolve } from 'node:path';
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
const { chromium } = require(process.env.CODEX_PLAYWRIGHT_PATH);
const server = createWebDevServer();
await new Promise(done => server.listen(0,'127.0.0.1',done));
let browser;
try {
  browser = await chromium.launch({channel:'chrome',headless:true});
  const page = await browser.newPage({viewport:{width:1280,height:900}});
  const errors = []; page.on('pageerror',error => errors.push(error.message));
  await page.goto(`http://127.0.0.1:${server.address().port}/?view=calculator`);
  await page.waitForFunction(() => window.ToramApp.settingsRepository && window.ToramApp.myRoomFood);
  await page.getByRole('tab',{name:'버프',exact:true}).click();
  const rows = page.locator('#myRoomFoodSlots .food-row');
  assert.equal(await rows.count(),5);
  assert.equal(await page.locator('#myRoomFoodSlots small').count(),0);
  assert.deepEqual(await page.locator('.food-quick-btn').evaluateAll(nodes => nodes.map(n => n.dataset.food)), ['CRIT','WATK','AMPR','ELEM_P','MAXHP','MAXMP','AGGRO_MINUS','STR','INT','VIT','AGI','DEX']);
  assert.ok(await page.locator('.food-quick-btn').evaluateAll(nodes => new Set(nodes.map(n => Math.round(n.getBoundingClientRect().width))).size === 1));
  assert.ok((await rows.nth(0).locator('select').boundingBox()).width < 300);
  const guild = page.locator('#guildFoodBuff');
  assert.equal(await guild.isChecked(),true);
  const guildDelta = await page.evaluate(() => {
    const source = window.ToramApp.buildStore.syncFromUi();
    const on = window.ToramApp.calculation.CalculateBuild(source).calculation;
    const off = window.ToramApp.calculation.CalculateBuild({...source,build:{...source.build,guildFoodBuff:false}}).calculation;
    return [on.finalMaxHP-off.finalMaxHP,on.finalMaxMP-off.finalMaxMP];
  });
  assert.deepEqual(guildDelta,[1000,100]);
  await guild.uncheck();
  for (const id of ['CRIT','MAXHP','MAXMP','AMPR','ELEM_P']) await page.locator(`[data-food="${id}"]`).click();
  assert.equal(await page.locator('.food-quick-btn:not(:disabled)').count(),5);
  await page.locator('[data-food="CRIT"]').click();
  assert.equal(await rows.nth(0).locator('select').inputValue(),'');
  await page.locator('[data-food="CRIT"]').click();
  assert.deepEqual(await rows.locator('.food-amount').evaluateAll(nodes => nodes.map(n => n.value)),['+30','+5000','+1000','+30','+15%']);
  assert.ok(await rows.locator('.food-amount').evaluateAll(nodes => nodes.every(n => n.readOnly)));
  assert.equal(await rows.nth(1).locator('option[value="CRIT"]').isDisabled(),true);
  const level = rows.nth(0).locator('input[type="number"]');
  await level.fill('6'); await level.press('Tab');
  assert.equal(await rows.nth(0).locator('.food-amount').inputValue(),'+14');
  await level.fill('99'); await level.press('Tab');
  assert.equal(await rows.nth(0).locator('input[type="number"]').inputValue(),'10');
  await rows.nth(1).locator('.food-clear').click();
  await page.locator('[data-food="STR"]').click();
  assert.equal(await rows.nth(1).locator('select').inputValue(),'STR');
  const before = await page.evaluate(() => {
    window.ToramApp.settingsRepository.flushApplicationState();
    return window.ToramApp.buildStore.read().build.myRoomFood;
  });
  await page.reload(); await page.waitForFunction(() => window.ToramApp.settingsRepository && window.ToramApp.myRoomFood);
  assert.deepEqual(await page.evaluate(() => window.ToramApp.myRoomFood.getSelections()),before);
  assert.equal(await page.locator('#guildFoodBuff').isChecked(),false);
  await page.getByRole('tab',{name:'버프',exact:true}).click();
  const result = await page.evaluate(() => {
    const source = window.ToramApp.buildStore.syncFromUi();
    const without = window.ToramApp.calculation.CalculateBuild({...source,build:{...source.build,myRoomFood:[null,null,null,null,null]}});
    const withFood = window.ToramApp.calculation.CalculateBuild(source);
    return {str:withFood.snapshot.baseContext.strF-without.snapshot.baseContext.strF,crit:withFood.snapshot.baseContext.critF-without.snapshot.baseContext.critF,mp:withFood.calculation.finalMaxMP-without.calculation.finalMaxMP,elem:withFood.snapshot.baseContext.elemP-without.snapshot.baseContext.elemP};
  });
  assert.deepEqual(result,{str:30,crit:30,mp:1000,elem:15});
  await rows.nth(1).locator('select').selectOption('PHYS_RES');
  assert.equal(await rows.nth(1).locator('.food-amount').inputValue(),'+50%');
  assert.equal(await page.evaluate(() => {
    const state = window.ToramApp.buildStore.syncFromUi();
    return window.ToramApp.calculation.CreateCalculationSnapshot(state).baseContext.preservedStats.PHYS_RES;
  }),undefined);
  const output = process.env.FOOD_QA_DIR;
  if (output) {
    await mkdir(output,{recursive:true});
    await page.screenshot({path:resolve(output,'desktop.png'),fullPage:true});
  }
  await page.setViewportSize({width:390,height:844});
  if (output) await page.screenshot({path:resolve(output,'mobile.png'),fullPage:true});
  assert.equal(await page.evaluate(() => document.documentElement.scrollWidth <= innerWidth),true);
  assert.ok(await rows.locator('.food-amount').evaluateAll(nodes => nodes.every(n => n.getBoundingClientRect().right <= innerWidth)));
  await page.evaluate(() => {
    const source = window.ToramApp.buildStore.read();
    const oldBuild = {...source.build}; delete oldBuild.myRoomFood; delete oldBuild.guildFoodBuff;
    window.ToramApp.buildStore.restoreSession({...source,build:oldBuild});
  });
  assert.deepEqual(await page.evaluate(() => window.ToramApp.myRoomFood.getSelections()),[null,null,null,null,null]);
  assert.equal(await guild.isChecked(),true);
  assert.deepEqual(errors,[]);
  console.log('Food Chrome UI: PASS (five slots, shortcuts, duplicates, levels, read-only values, reload, calculation, disconnected effects, old saves, mobile)');
} finally { await browser?.close(); server.close(); }
