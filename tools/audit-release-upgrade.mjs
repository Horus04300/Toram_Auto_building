// Real installed Tauri upgrade gate. Requires an already installed, isolated old release.
// No updater IPC, downloaded bytes, signature, install, or restart is mocked.
import assert from 'node:assert/strict';
import { spawn } from 'node:child_process';
import { mkdir, readFile, writeFile, open } from 'node:fs/promises';
import { resolve } from 'node:path';
import { createRequire } from 'node:module';
import { createHash } from 'node:crypto';
const require = createRequire(import.meta.url);
assert.ok(process.env.CODEX_PLAYWRIGHT_PATH, 'Set CODEX_PLAYWRIGHT_PATH');
const { chromium } = require(process.env.CODEX_PLAYWRIGHT_PATH);
const mode = process.argv[2];
assert.ok(['prepare', 'upgrade', 'inspect'].includes(mode), 'Use prepare, upgrade, or inspect');
const root = resolve('src-tauri/target/upgrade-0.6.4-to-0.6.5');
const executable = resolve(root, 'Toram Online Auto Build Calculator/toram-online-auto-build-calculator.exe');
const local = resolve(root, 'local'), profile = resolve(root, 'webview');
const endpoint = 'http://127.0.0.1:9226';
const stateKey = 'toram.auto-build.application-state.v2';
const namedFile = resolve(local, 'ToramOnlineAutoBuildCalculator/UpgradePreservation.json');
const report = { mode, startedAt: new Date().toISOString(), executable, checks: [], errors: [] };
let child, browser, page;
const delay = ms => new Promise(r => setTimeout(r, ms));
const sha = bytes => createHash('sha256').update(bytes).digest('hex');
async function saveReport() { await writeFile(resolve(root, `${mode}-report.json`), JSON.stringify(report, null, 2)); }
async function connect(timeout = 30000) {
  const until = Date.now() + timeout;
  let error;
  while (Date.now() < until) {
    try {
      browser = await chromium.connectOverCDP(endpoint, { timeout: 1500 });
      page = browser.contexts()[0]?.pages()[0];
      if (!page) throw new Error('No app page yet');
      page.setDefaultTimeout(25000);
      await page.waitForFunction(() => window.ToramSettingsRepository && window.__TAURI__?.app, {}, { timeout: 5000 });
      page.on('pageerror', e => report.errors.push(e.message));
      return;
    } catch (e) { error = e; await browser?.close().catch(() => {}); await delay(500); }
  }
  throw error || new Error('No restarted WebView');
}
async function launch() {
  try {
    await fetch(endpoint + '/json/version');
    throw new Error('CDP port is already occupied; refusing to attach to an unrelated app');
  } catch (e) { if (e.message.includes('occupied')) throw e; }
  await mkdir(local, { recursive: true }); await mkdir(profile, { recursive: true });
  const log = await open(resolve(root, `${mode}-app.log`), 'a');
  child = spawn(executable, [], { detached: true, windowsHide: true,
    env: { ...process.env, LOCALAPPDATA: local, WEBVIEW2_USER_DATA_FOLDER: profile,
      WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS: '--remote-debugging-port=9226 --remote-debugging-address=127.0.0.1' },
    stdio: ['ignore', log.fd, log.fd] });
  child.on('error', e => report.errors.push(e.message));
  report.initialPid = child.pid; child.unref(); await log.close();
  await connect();
  const directory = await page.evaluate(() => window.ToramSettingsRepository.directory());
  assert.equal(directory, resolve(local, 'ToramOnlineAutoBuildCalculator'));
  report.checks.push({ name: 'isolated native settings directory', directory });
}
const version = () => page.evaluate(() => window.__TAURI__.app.getVersion());
const snapshot = () => page.evaluate(key => JSON.parse(localStorage.getItem(key)), stateKey);
try {
  await mkdir(root, { recursive: true });
  if (mode === 'inspect') { await connect(); report.version = await version(); report.state = await snapshot(); }
  else {
    await launch();
    assert.equal(await version(), '0.6.4');
    report.checks.push({ name: 'installed source version', version: '0.6.4', executableSha256: sha(await readFile(executable)) });
    if (mode === 'prepare') {
      await page.locator('#charLevel').fill('222');
      await page.locator('#appTabButton-stats-target').click();
      await page.locator('#bossDef').fill('123');
      await page.locator('#updateCheckOnStartup').check();
      await page.locator('#appTabButton-equipment').click();
      await page.locator('#lock_wpn_1').check();
      await page.locator('#appBuildStorageButton').click();
      await page.locator('#buildSettingName').fill('UpgradePreservation');
      await page.locator('#buildSettingSave').click();
      await page.waitForFunction(() => document.querySelector('#buildFileStorageStatus').textContent.includes('UpgradePreservation.json 저장 완료'));
      await page.locator('#buildFileDialogClose').click();
      await page.evaluate(() => window.ToramApplication.Settings.flush());
      const state = await snapshot(), bytes = await readFile(namedFile);
      assert.equal(state.lastSession.build.character.level, 222);
      assert.equal(state.lastSession.scenario.target.bossDef, 123);
      await writeFile(resolve(root, 'before.json'), JSON.stringify({ state, namedSha256: sha(bytes) }, null, 2));
      await page.screenshot({ path: resolve(root, '0.6.4-prepared.png') });
      report.checks.push({ name: 'old release saved build and session', namedSha256: sha(bytes) });
      // This owned process is stopped only during setup, after explicit persistence.
      await browser.close(); browser = null; child.kill(); await delay(1000);
    } else {
      const before = JSON.parse(await readFile(resolve(root, 'before.json'), 'utf8'));
      await page.locator('#updatePanel').waitFor({ state: 'visible' });
      await page.waitForFunction(() => document.querySelector('#updateTitle').textContent.includes('0.6.5'));
      report.checks.push({ name: 'automatic startup detects public 0.6.5', text: await page.locator('#updatePanel').innerText() });
      assert.equal(await page.locator('#charLevel').inputValue(), '222');
      assert.equal(await page.locator('#bossDef').inputValue(), '123');
      assert.equal(await page.locator('#lock_wpn_1').isChecked(), true);
      assert.equal(sha(await readFile(namedFile)), before.namedSha256);
      await page.locator('#updateCheckOnStartup').uncheck();
      await page.locator('#updateInstall').click();
      await page.locator('#updateConfirm[open]').waitFor();
      await page.locator('#updateConfirm button[value="cancel"]').click();
      assert.equal(await version(), '0.6.4');
      report.checks.push({ name: 'declining preserves running 0.6.4' });
      await page.locator('#charLevel').fill('321');
      await page.evaluate(() => window.ToramApplication.Settings.flush());
      const expectedState = await snapshot();
      await writeFile(resolve(root, 'expected-after.json'), JSON.stringify(expectedState, null, 2));
      await page.screenshot({ path: resolve(root, '0.6.4-update-available.png') });
      await page.locator('#updateInstall').click();
      await page.locator('#updateConfirmAccept').click();
      const statuses = new Set();
      const until = Date.now() + 180000;
      while (Date.now() < until && !page.isClosed() && browser.isConnected()) {
        try {
          const status = await page.locator('#updateStatus').textContent({ timeout: 1000 });
          statuses.add(status);
          if (/실패|못했습니다/.test(status)) throw new Error(status);
        } catch (e) {
          if (/실패|못했습니다/.test(e.message)) throw e;
          break;
        }
        await delay(100);
      }
      report.checks.push({ name: 'real native download and install', statuses: [...statuses] });
      assert.ok(!browser.isConnected() || page.isClosed(), 'Old app must exit for installer');
      // No executable launch here: NSIS must restart the application itself.
      await connect(120000);
      assert.equal(await version(), '0.6.5');
      assert.equal(await page.evaluate(() => window.ToramSettingsRepository.directory()), resolve(local, 'ToramOnlineAutoBuildCalculator'));
      const afterState = await snapshot();
      assert.deepEqual(afterState.lastSession.build, expectedState.lastSession.build);
      assert.deepEqual(afterState.lastSession.scenario, expectedState.lastSession.scenario);
      assert.deepEqual(afterState.appSettings.update, expectedState.appSettings.update);
      assert.equal(await page.locator('#updateCheckOnStartup').isChecked(), false);
      assert.equal(sha(await readFile(namedFile)), before.namedSha256);
      assert.equal(await page.locator('#charLevel').inputValue(), '321');
      assert.equal(await page.locator('#lock_wpn_1').isChecked(), true);
      await page.locator('#updateCheck').click();
      await page.waitForFunction(() => !document.querySelector('#updateCheck').disabled);
      assert.equal(await page.locator('#updateStatus').textContent(), '최신 버전입니다.');
      report.checks.push({ name: 'NSIS automatic restart and persisted data', version: '0.6.5', namedSha256: sha(await readFile(namedFile)), checkOnStartup: false, level: 321, bossDef: 123 });
      report.installedSha256 = sha(await readFile(executable));
      await writeFile(resolve(root, 'after.json'), JSON.stringify(afterState, null, 2));
      await page.screenshot({ path: resolve(root, '0.6.5-updated.png') });
    }
  }
  assert.deepEqual(report.errors, []);
  report.result = 'PASS';
} catch (e) { report.result = 'FAIL'; report.failure = e.stack; process.exitCode = 1; }
finally {
  await browser?.close().catch(() => {});
  report.finishedAt = new Date().toISOString(); await saveReport();
  console.log(JSON.stringify(report, null, 2));
}
