import assert from 'node:assert/strict';
import path from 'node:path';
import { pathToFileURL } from 'node:url';

if (!process.env.TORAM_E2E_CDP) {
  console.log('Tauri native storage E2E: SKIP (TORAM_E2E_CDP is not set)');
  process.exit(0);
}

const playwrightPath = process.env.CODEX_PLAYWRIGHT_PATH;
if (!playwrightPath) throw new Error('CODEX_PLAYWRIGHT_PATH is required.');
const playwrightModule = await import(pathToFileURL(path.join(playwrightPath, 'index.js')).href);
const { chromium } = playwrightModule.default || playwrightModule;
const endpoint = process.env.TORAM_E2E_CDP || 'http://127.0.0.1:9224';
const expectedDirectory = process.env.TORAM_E2E_DIRECTORY;
const stateKeys = [
  'toram-auto-building.build-state.v1',
  'toram-auto-building.skill-tree.v1',
  'toram-auto-building.skill-tree-ui.v1',
  'toram-auto-active-buffs-v1',
  'toram.combo-sequence.v1'
];
const testName = 'CodexNativeStorageE2E-' + Date.now();
let browser;
let page;
let originalStorage;

function buildStateWithLevel(source, level) {
  let state;
  try { state = JSON.parse(source || 'null'); } catch { state = null; }
  if (!state || typeof state !== 'object' || Array.isArray(state)) {
    state = { controls:{}, options:{}, banned:[] };
  }
  if (!state.controls || typeof state.controls !== 'object') state.controls = {};
  state.controls.charLevel = String(level);
  return JSON.stringify(state);
}

try {
  browser = await chromium.connectOverCDP(endpoint);
  const context = browser.contexts()[0];
  assert.ok(context, 'Tauri WebView2 browser context was not found.');
  page = context.pages()[0];
  assert.ok(page, 'Tauri main page was not found.');
  await page.waitForLoadState('domcontentloaded');
  await page.waitForFunction(() => Boolean(window.ToramBuildStorageAdapter && window.ToramBuildSettings));

  const title = await page.title();
  assert.match(title, /v0\.5\.0/);
  const version = 'v0.5.0';

  originalStorage = await page.evaluate((keys) => Object.fromEntries(keys.map((key) => [key, localStorage.getItem(key)])), stateKeys);
  const firstState = buildStateWithLevel(originalStorage[stateKeys[0]], 111);
  await page.evaluate(({ key, value }) => localStorage.setItem(key, value), { key:stateKeys[0], value:firstState });

  await page.locator('#appBuildStorageButton').click();
  const nativeFunctions = page.locator('#buildNativeFileFunctions');
  await nativeFunctions.waitFor({ state:'visible' });
  const shownDirectory = await page.locator('#buildFileStorageStatus').textContent();
  assert.ok(shownDirectory?.includes(expectedDirectory), 'The exact native storage directory should be shown.');

  await page.locator('#buildSettingName').fill(testName);
  await page.locator('#buildSettingSave').click();
  await page.waitForFunction((name) => document.querySelector('#buildFileStorageStatus')?.textContent?.includes(name + '.json 저장 완료'), testName);

  await page.locator('#buildSettingSave').click();
  await page.waitForFunction(() => document.querySelector('#buildFileStorageStatus')?.textContent?.includes('같은 이름의 세팅이 이미 있습니다'));

  const secondState = buildStateWithLevel(firstState, 222);
  await page.evaluate(({ key, value }) => localStorage.setItem(key, value), { key:stateKeys[0], value:secondState });
  await page.locator('#buildSettingList').selectOption(testName + '.json');
  page.once('dialog', (dialog) => dialog.accept());
  await page.locator('#buildSettingOverwrite').click();
  await page.waitForFunction((name) => document.querySelector('#buildFileStorageStatus')?.textContent?.includes(name + '.json 덮어쓰기 완료'), testName);

  const thirdState = buildStateWithLevel(secondState, 333);
  await page.evaluate(({ key, value }) => localStorage.setItem(key, value), { key:stateKeys[0], value:thirdState });
  await page.locator('#buildSettingList').selectOption(testName + '.json');
  await page.locator('#buildSettingLoad').click();
  await page.waitForFunction((key) => {
    try { return JSON.parse(localStorage.getItem(key)).controls.charLevel === '222'; } catch { return false; }
  }, stateKeys[0]);
  await page.waitForLoadState('domcontentloaded');
  await page.waitForFunction(() => Boolean(window.ToramBuildSettings));

  const loadedLevel = await page.evaluate((key) => JSON.parse(localStorage.getItem(key)).controls.charLevel, stateKeys[0]);
  assert.equal(loadedLevel, '222');

  await page.locator('#appBuildStorageButton').click();
  await page.locator('#buildNativeFileFunctions').waitFor({ state:'visible' });
  await page.locator('#buildSettingList').selectOption(testName + '.json');
  page.once('dialog', (dialog) => dialog.accept());
  await page.locator('#buildSettingDelete').click();
  await page.waitForFunction((name) => document.querySelector('#buildFileStorageStatus')?.textContent?.includes(name + '.json 삭제 완료'), testName);
  assert.equal(await page.locator('#buildSettingList option', { hasText:testName + '.json' }).count(), 0);

  const backupText = await page.evaluate(() => window.ToramBuildSettings.serialize('E2E 백업'));
  const changedAfterBackup = buildStateWithLevel(secondState, 444);
  await page.evaluate(({ key, value }) => localStorage.setItem(key, value), { key:stateKeys[0], value:changedAfterBackup });
  await page.locator('#buildSettingImport').setInputFiles({
    name:'E2E-backup.json',
    mimeType:'application/json',
    buffer:Buffer.from(backupText)
  });
  await page.waitForFunction((key) => {
    try { return JSON.parse(localStorage.getItem(key)).controls.charLevel === '222'; } catch { return false; }
  }, stateKeys[0]);
  await page.waitForLoadState('domcontentloaded');

  console.log(JSON.stringify({
    title,
    version,
    directory:expectedDirectory,
    fileName:testName + '.json',
    duplicateBlocked:true,
    overwrittenLevel:loadedLevel,
    nativeUiVisible:true,
    deleted:true,
    backupImported:true
  }));
} finally {
  if (page && originalStorage) {
    await page.evaluate(({ keys, values }) => {
      keys.forEach((key) => {
        if (values[key] === null) localStorage.removeItem(key);
        else localStorage.setItem(key, values[key]);
      });
    }, { keys:stateKeys, values:originalStorage }).catch(() => {});
  }
  if (browser) await browser.close().catch(() => {});
}