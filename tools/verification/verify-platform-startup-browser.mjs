import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
import { mkdtemp } from 'node:fs/promises';
import { join } from 'node:path';
import { tmpdir } from 'node:os';
import { createWebDevServer } from '../web-dev.mjs';

if (!process.env.CODEX_PLAYWRIGHT_PATH) throw new Error('Set CODEX_PLAYWRIGHT_PATH to the installed playwright module.');
const {chromium} = createRequire(import.meta.url)(process.env.CODEX_PLAYWRIGHT_PATH);
const server = createWebDevServer(), directory = await mkdtemp(join(tmpdir(),'toram-startup-'));
let browser;
const errors = [];
try {
  await new Promise((done,reject) => {server.once('error',reject); server.listen(0,'127.0.0.1',done);});
  const origin = 'http://127.0.0.1:' + server.address().port;
  browser = await chromium.launch({channel:'chrome',headless:true});
  for (const [path,view] of [['/','home'],['/calculator','calculator'],['/?view=calculator','calculator'],['/catalog?selected=22001','catalog'],['/inventory?type=build','inventory'],['/board','board']]) {
    const page = await browser.newPage({viewport:{width:1280,height:900}}), requests = [];
    page.on('pageerror',error => errors.push(error.message));
    page.on('console',event => {if (['error','warning'].includes(event.type()) && !event.location().url.endsWith('/favicon.ico')) errors.push(event.text());});
    page.on('request',request => requests.push(new URL(request.url()).pathname));
    let releaseEntry, releaseCalculator, requestedCalculator;
    const entry = new Promise(done => {releaseEntry = done;}), calculator = new Promise(done => {releaseCalculator = done;});
    const requested = new Promise(done => {requestedCalculator = done;});
    await page.route('**/assets/js/app-entry.mjs',async route => {await entry; await route.continue();});
    await page.route('**/assets/pages/calculator.html',async route => {requestedCalculator(); await calculator; await route.continue();});
    await page.route('**/api/**',route => route.fulfill({json:route.request().url().includes('/posts') ? {items:[],total:0,page:1,pageSize:3} : {configured:false,user:null}}));
    await page.addInitScript(() => {
      window.calculatorFlash = false;
      function frame() {
        const calculator = document.querySelector('.container');
        if (calculator?.getClientRects().length && (document.body.dataset.page !== 'calculator' || !window.ToramApp.calculatorReady)) window.calculatorFlash = true;
        requestAnimationFrame(frame);
      }
      requestAnimationFrame(frame);
    });
    await page.goto(origin + path,{waitUntil:'commit'});
    await page.locator('.platform-loading').waitFor({state:'visible'});
    assert.equal(await page.locator('#charLevel').count(),0,'The entry document must not contain calculator markup');
    releaseEntry();
    await page.waitForFunction(view => document.body.dataset.page === view,view);
    const version = await page.locator('meta[name="application-version"]').getAttribute('content');
    assert.equal(await page.locator('.app-titlebar .platform-version').innerText(),version);
    assert.equal(await page.locator('.app-titlebar #appBuildStorageButton').count(),0);
    if (view !== 'calculator') {
      await page.locator('#' + view + 'Workspace').waitFor({state:'visible'});
      await page.waitForLoadState('networkidle');
      assert.equal(requests.some(path => path.endsWith('/calculator-page.mjs') || path === '/assets/pages/calculator.html' || path.endsWith('/ui-bootstrap.js')),false,'Other pages must not load the calculator');
      assert.equal(await page.locator('#charLevel').count(),0);
      assert.equal(await page.evaluate(() => Boolean(window.ToramUiFeatures)),false);
      if (view === 'home') {
        assert.equal(await page.locator('.home-login').isEnabled(),true);
        await page.screenshot({path:join(directory,'home-without-calculator.png')});
        await page.locator('#appAccountButton').click();
        await page.locator('.account-dialog[open]').waitFor();
        await page.locator('.account-close').click();
      }
      await page.locator('.platform-nav-button[data-page="calculator"]').click();
    }
    await requested;
    assert.equal(await page.locator('#calculatorWorkspace').isVisible(),false);
    await page.locator('#platformContent > .platform-loading').waitFor({state:'visible'});
    if (path === '/') {
      await page.locator('.platform-nav-button[data-page="home"]').click();
      releaseCalculator();
      await page.waitForFunction(() => window.ToramApp.calculatorReady);
      assert.equal(await page.locator('#homeWorkspace').isVisible(),true,'A completed background load must not replace the new route');
      await page.locator('.platform-nav-button[data-page="calculator"]').click();
    } else releaseCalculator();
    await page.waitForFunction(() => window.ToramApp.calculatorReady);
    await page.locator('#calculatorWorkspace').waitFor({state:'visible'});
    await page.locator('#calculatorWorkspace #appBuildStorageButton').click();
    await page.locator('.build-file-overlay:not([hidden]) #buildFileDialogClose').click();
    assert.equal(await page.locator('.app-titlebar .platform-version').innerText(),version,'Version must survive page navigation');
    assert.equal(await page.evaluate(() => window.calculatorFlash),false);
    await page.locator('#appTabButton-skills').click();
    assert.equal(await page.locator('#appTabPanel-skills > .skill-bookmark-section').count(),2);
    await page.locator('#appTabButton-stats-target').click();
    await page.locator('#charLevel').fill('300');
    await page.locator('.platform-nav-button[data-page="home"]').click();
    await page.locator('.platform-nav-button[data-page="calculator"]').click();
    await page.locator('#calculatorWorkspace').waitFor({state:'visible'});
    assert.equal(await page.locator('#charLevel').inputValue(),'300');
    assert.equal(requests.filter(path => path === '/assets/pages/calculator.html').length,1,'Repeated entries must share one calculator initialization');
    if (path === '/') {
      await page.setViewportSize({width:390,height:844});
      await page.goto(origin); await page.locator('#homeWorkspace').waitFor({state:'visible'});
      assert.equal(await page.locator('.app-titlebar .platform-version').isVisible(),true);
      assert.ok(await page.evaluate(() => document.documentElement.scrollWidth <= innerWidth),'The mobile titlebar must fit with the version');
      assert.equal(await page.locator('#charLevel').count(),0);
      assert.equal(await page.evaluate(() => Boolean(window.ToramApp.calculatorReady)),false);
      await page.screenshot({path:join(directory,'home-mobile.png')});
    }
    await page.close();
  }
  assert.deepEqual(errors,[]);
  const failed = await browser.newPage();
  await failed.route('**/assets/pages/calculator.html',route => route.fulfill({status:503,body:'Unavailable'}));
  await failed.route('**/api/**',route => route.fulfill({json:{items:[],total:0,page:1,pageSize:3,configured:false,user:null}}));
  await failed.goto(origin + '/calculator');
  const alert = failed.locator('#platformContent > .platform-loading[role="alert"]');
  await alert.waitFor({state:'visible'});
  assert.match(await alert.innerText(),/불러오지 못했습니다/);
  assert.equal(await alert.locator('a').getAttribute('href'),'');
  assert.equal(await failed.locator('#calculatorWorkspace').isVisible(),false);
  await failed.locator('.platform-nav-button[data-page="home"]').click();
  await failed.locator('#homeWorkspace').waitFor({state:'visible'});
  assert.equal(await failed.locator('.home-login').isEnabled(),true,'Calculator failure must not disable home/account');
  await failed.close();
  console.log('Platform startup: PASS (Chrome, home HTML, no calculator requests on other pages, lazy/direct entry, shared initialization, navigation race, mobile, tabs/state, isolated failure)');
  console.log('Screenshots: ' + directory);
} finally {await browser?.close(); await new Promise(done => server.close(done));}
