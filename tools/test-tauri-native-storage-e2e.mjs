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
const testName = 'CodexR6StorageE2E-' + Date.now();
let browser;

async function setLevel(page, level) {
  await page.locator('#charLevel').fill(String(level));
  await page.locator('#charLevel').dispatchEvent('input');
  await page.waitForFunction(value => Number(window.ToramBuildDraftStore.read().build.character.level) === value, level);
}

try {
  browser = await chromium.connectOverCDP(endpoint);
  const page = browser.contexts()[0]?.pages()[0];
  assert.ok(page, 'Tauri WebView2 browser context was not found.');
  await page.waitForLoadState('domcontentloaded');
  await page.waitForFunction(() => Boolean(window.ToramSettingsRepository && window.ToramSettingsFileRepositoryAdapter));
  assert.equal(await page.evaluate(() => window.ToramSettingsRepository.schemaVersion), 2);
  await setLevel(page, 111);
  await page.locator('#appBuildStorageButton').click();
  await page.locator('#buildNativeFileFunctions').waitFor({ state:'visible' });
  assert.ok((await page.locator('#buildFileStorageStatus').textContent())?.includes(expectedDirectory));
  await page.locator('#buildSettingName').fill(testName);
  await page.locator('#buildSettingSave').click();
  await page.waitForFunction(name => document.querySelector('#buildFileStorageStatus')?.textContent?.includes(name + '.json 저장 완료'), testName);
  await page.locator('#buildSettingSave').click();
  await page.waitForFunction(() => document.querySelector('#buildFileStorageStatus')?.textContent?.includes('같은 이름의 세팅이 이미 있습니다'));
  await setLevel(page, 222);
  await page.locator('#buildSettingList').selectOption(testName + '.json');
  page.once('dialog', dialog => dialog.accept());
  await page.locator('#buildSettingOverwrite').click();
  await page.waitForFunction(name => document.querySelector('#buildFileStorageStatus')?.textContent?.includes(name + '.json 덮어쓰기 완료'), testName);
  await setLevel(page, 333);
  await page.locator('#buildSettingList').selectOption(testName + '.json');
  await page.locator('#buildSettingLoad').click();
  await page.waitForFunction(() => Number(document.querySelector('#charLevel')?.value) === 222);
  assert.equal(await page.evaluate(() => window.ToramBuildDraftStore.read().build.character.level), 222);
  const documentContract = await page.evaluate(() => window.ToramSettingsRepository.serializeSavedBuild('E2E export'));
  assert.match(documentContract, /"documentType": "saved-build"/);
  assert.doesNotMatch(documentContract, /"storage"/);
  await page.locator('#buildSettingList').selectOption(testName + '.json');
  page.once('dialog', dialog => dialog.accept());
  await page.locator('#buildSettingDelete').click();
  await page.waitForFunction(name => document.querySelector('#buildFileStorageStatus')?.textContent?.includes(name + '.json 삭제 완료'), testName);
  assert.equal(await page.locator('#buildSettingList option', { hasText:testName + '.json' }).count(), 0);
  console.log(JSON.stringify({ directory:expectedDirectory, fileName:testName + '.json', schemaVersion:2, duplicateBlocked:true, overwrittenLevel:222, deleted:true }));
} finally {
  if (browser) await browser.close().catch(() => {});
}
