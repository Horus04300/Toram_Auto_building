// Optional real-browser integration gate. Native install is mocked; this is not upgrade E2E.
import assert from 'node:assert/strict';
import { createServer } from 'node:http';
import { readFile } from 'node:fs/promises';
import { resolve, extname, sep } from 'node:path';
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
if (!process.env.CODEX_PLAYWRIGHT_PATH) throw new Error('Set CODEX_PLAYWRIGHT_PATH to the installed playwright module.');
const { chromium } = require(process.env.CODEX_PLAYWRIGHT_PATH);
const root = resolve(import.meta.dirname, '..', 'dist');
const mime = { '.html':'text/html', '.js':'text/javascript', '.mjs':'text/javascript', '.css':'text/css', '.json':'application/json', '.svg':'image/svg+xml' };
const server = createServer(async (req, res) => {
  try {
    const path = resolve(root, '.' + new URL(req.url, 'http://localhost').pathname.replace(/\/$/, '/index.html'));
    if (!path.startsWith(root + sep)) throw new Error('path');
    res.setHeader('Content-Type', mime[extname(path)] || 'application/octet-stream');
    res.end(await readFile(path));
  } catch { res.writeHead(404); res.end(); }
});
await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));
let browser;
try {
  browser = await chromium.launch({ channel:'msedge', headless:true });
  const page = await browser.newPage({ viewport:{ width:1280, height:900 } });
  const errors = [];
  page.on('pageerror', error => errors.push(error.message));
  const url = `http://127.0.0.1:${server.address().port}`;
  await page.goto(url);
  await page.waitForFunction(() => window.ToramUiFeatures?.updates);
  assert.equal(await page.locator('#updateCheck').isDisabled(), true);
  await page.close();
  const native = await browser.newPage({ viewport:{ width:1280, height:900 } });
  native.on('pageerror', error => errors.push(error.message));
  await native.addInitScript(() => {
    window.installCalls = 0;
    window.__TAURI__ = { core:{ Channel:class {}, invoke:async (command, args) => {
      if (command === 'settings_directory') return 'test-only';
      if (command === 'list_settings') return [];
      if (command === 'check_for_update') return { currentVersion:'0.6.4', version:'0.6.5', notes:'변경사항\n<script>window.bad = true</script>', publishedAt:null };
      if (command === 'download_update') {
        args.progress.onmessage({ downloaded:50, total:100 });
        await new Promise(resolve => { window.finishUpdateDownload = resolve; });
      }
      if (command === 'install_update') window.installCalls++;
      return null;
    } } };
  });
  await native.goto(url);
  await native.locator('#updatePanel').waitFor({ state:'visible' });
  assert.match(await native.locator('#updateNotes').textContent(), /<script>/);
  assert.equal(await native.evaluate(() => window.bad), undefined);
  await native.evaluate(() => {
    window.pausedTestWork = true;
    window.ToramD4ExecutionAdapter = {
      isAvailable:() => true, isRunning:() => false, hasContinuation:() => window.pausedTestWork,
      cancel:() => {}, disposeContinuation:async () => { window.pausedTestWork = false; }
    };
  });
  await native.locator('#updateInstall').click();
  await native.locator('#updateConfirm[open]').waitFor();
  assert.match(await native.locator('#updateConfirmAccept').textContent(), /계산을 종료/);
  await native.locator('#updateConfirm button[value="cancel"]').click();
  assert.equal(await native.evaluate(() => window.pausedTestWork), true);
  assert.equal(await native.evaluate(() => window.installCalls), 0);
  await native.locator('#updateInstall').click();
  await native.locator('#updateConfirmAccept').click();
  await native.waitForFunction(() => typeof window.finishUpdateDownload === 'function');
  assert.equal(await native.evaluate(() => document.body.inert), false);
  await native.locator('#charLevel').fill('321');
  await native.evaluate(() => window.finishUpdateDownload());
  await native.waitForFunction(() => window.installCalls === 1);
  const saved = await native.evaluate(() => JSON.parse(localStorage.getItem('toram.auto-build.application-state.v2')));
  assert.equal(saved.lastSession.build.character.level, 321);
  assert.equal(saved.lastSession.update, undefined);
  assert.equal(await native.evaluate(() => document.body.inert), false);
  await native.screenshot({ path:resolve(root, 'update-ui-check.png') });
  assert.deepEqual(errors, []);
  console.log('Real browser update UI: PASS (web unavailable, startup, text-only notes, paused consent/cancel, download editing, final flush; native install mocked)');
} finally {
  if (browser) await browser.close();
  await new Promise(resolve => server.close(resolve));
}
