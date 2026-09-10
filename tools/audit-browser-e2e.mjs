// Real Edge UI audit. Uses an isolated browser context and never installs updates.
import assert from 'node:assert/strict';
import { createServer } from 'node:http';
import { readFile, mkdir, writeFile } from 'node:fs/promises';
import { resolve, extname, sep } from 'node:path';
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
if (!process.env.CODEX_PLAYWRIGHT_PATH) throw new Error('Set CODEX_PLAYWRIGHT_PATH');
const { chromium } = require(process.env.CODEX_PLAYWRIGHT_PATH);
const root = resolve('dist'), output = resolve('dist/e2e-audit');
await mkdir(output, { recursive:true });
const server = createServer(async (req,res) => {
  try {
    const file = resolve(root, '.' + new URL(req.url,'http://localhost').pathname.replace(/\/$/,'/index.html'));
    if (!file.startsWith(root + sep)) throw new Error('path');
    res.setHeader('Content-Type', ({'.html':'text/html','.js':'text/javascript','.mjs':'text/javascript','.css':'text/css','.json':'application/json','.svg':'image/svg+xml'})[extname(file)] || 'application/octet-stream');
    res.end(await readFile(file));
  } catch { res.writeHead(404); res.end(); }
});
await new Promise(r => server.listen(0,'127.0.0.1',r));
const browser = await chromium.launch({ channel:'msedge',headless:true });
const context = await browser.newContext({ viewport:{width:1280,height:900} });
const page = await context.newPage();
const report = { checks:[], errors:[], failedRequests:[] };
report.dialogs=[];
page.on('dialog',async d=>{report.dialogs.push(d.message());await d.accept();});
page.on('pageerror',e => report.errors.push(e.message));
page.on('response',r => { if(r.status() >= 400) report.failedRequests.push({url:r.url(),status:r.status()}); });
const url = `http://127.0.0.1:${server.address().port}`;
async function check(name, fn) {
  try { const detail = await fn(); report.checks.push({name,status:'PASS',detail}); }
  catch(e) { report.checks.push({name,status:'FAIL',error:e.message}); await page.screenshot({path:resolve(output,`failure-${report.checks.length}.png`)}).catch(()=>{}); }
  console.log(JSON.stringify(report.checks.at(-1)));
}
async function ready() { await page.waitForFunction(() => window.ToramSettingsRepository && document.querySelector('#appTabButton-results')); }
const tab = id => page.locator('#appTabButton-' + id).click();
try {
  await page.goto(url); await ready();
  await check('six tabs render without runtime errors',async()=>{
    for(const id of ['stats-target','equipment','skills','buffs','combo','results']) {
      await tab(id); await page.locator('#appTabPanel-'+id).waitFor({state:'visible'});
    }
    await page.locator('#resultArea').waitFor({state:'visible'});
    assert.deepEqual(report.errors,[]);
    return (await page.locator('#appTabPanel-results').innerText()).slice(0,1600);
  });
  await check('input and lock survive reload',async()=>{
    await tab('stats-target'); await page.locator('#charLevel').fill('222'); await page.locator('#bossDef').fill('123');
    await tab('equipment'); await page.locator('#wpnAtk').fill('777'); await page.locator('#lock_wpn_1').check();
    await page.waitForFunction(()=>JSON.parse(localStorage.getItem('toram.auto-build.application-state.v2'))?.lastSession.build.equipment.mainWeapon.attack === 777);
    await page.reload(); await ready();
    assert.equal(await page.locator('#charLevel').inputValue(),'222'); assert.equal(await page.locator('#bossDef').inputValue(),'123');
    await tab('equipment'); assert.equal(await page.locator('#wpnAtk').inputValue(),'777'); assert.equal(await page.locator('#lock_wpn_1').isChecked(),true);
  });
  await check('all weapon types allow tab navigation and restoration',async()=>{
    await tab('equipment');
    const options=await page.locator('#mainWeaponType option').evaluateAll(es=>es.map(e=>e.value));
    for(const value of options) {
      await page.locator('#mainWeaponType').selectOption(value);
      await tab('buffs'); await tab('combo'); await tab('equipment');
      assert.equal(await page.locator('#mainWeaponType').inputValue(),value);
    }
    return options;
  });
  await check('requirements cancel leaves saved preferences unchanged',async()=>{
    await tab('results'); await page.locator('#optimizationRequirementsButton').click();
    const before=await page.evaluate(()=>window.ToramBuildDraftStore.read().scenario.optimizationPreferences);
    const fields=await page.locator('#optimizationRequirementsOverlay input').evaluateAll(es=>es.map(e=>({id:e.id,type:e.type,value:e.value,checked:e.checked})));
    const number=page.locator('#optimizationRequirementsOverlay input[type=number]').first();
    if(await number.isEnabled()) await number.fill('12345');
    await page.locator('#optimizationRequirementsCancel').click();
    assert.deepEqual(await page.evaluate(()=>window.ToramBuildDraftStore.read().scenario.optimizationPreferences),before);
    return fields;
  });
  await check('setting modal controls',async()=>{
    await page.locator('#appBuildStorageButton').click();
    return await page.locator('.build-file-overlay').evaluateAll(es=>es.filter(e=>!e.hidden).map(e=>({text:e.innerText,controls:[...e.querySelectorAll('button,input')].map(x=>({id:x.id,text:x.textContent,type:x.type}))})));
  });
  await page.keyboard.press('Escape');
  await check('JSON export/import round trip through file picker',async()=>{
    await page.locator('#appBuildStorageButton').click();
    await page.locator('#buildBackupName').fill('e2e-roundtrip');
    const downloadPromise=page.waitForEvent('download');
    await page.locator('#buildSettingExport').click();
    const download=await downloadPromise, file=resolve(output,'roundtrip.json'); await download.saveAs(file);
    const exported=JSON.parse(await readFile(file,'utf8')); assert.equal(exported.build.character.level,222);
    await page.locator('#buildFileDialogClose').click(); await tab('stats-target'); await page.locator('#charLevel').fill('111');
    await page.locator('#appBuildStorageButton').click(); await page.locator('#buildSettingImport').setInputFiles(file);
    await page.waitForFunction(()=>document.querySelector('#charLevel').value==='222');
    await page.locator('#buildFileDialogClose').click();
  });
  await check('skill investment and combo survive reload',async()=>{
    await tab('equipment'); await page.locator('#mainWeaponType').selectOption('한손검');
    await tab('skills'); await page.locator('#combatSkillStage .skill-node').first().click();
    const invested=await page.evaluate(()=>window.ToramBuildDraftStore.read().build.skillLevels);
    assert.ok(Object.values(invested).some(tree=>Object.values(tree).some(v=>v>0)));
    await tab('combo'); await page.locator('#comboAddEntry').click();
    assert.equal(await page.locator('.combo-chain-node').count(),2);
    await page.locator('#comboRangeShort').check(); await page.locator('#comboRangeLong').check();
    assert.equal(await page.locator('#comboRangeShort').isChecked(),false);
    await tab('stats-target'); await page.reload(); await ready();
    assert.deepEqual(await page.evaluate(()=>window.ToramBuildDraftStore.read().build.skillLevels),invested);
    await tab('combo'); assert.equal(await page.locator('.combo-chain-node').count(),2);
    assert.equal(await page.locator('#comboRangeLong').isChecked(),true);
  });
  await check('requirements apply and reload',async()=>{
    await tab('results'); await page.locator('#optimizationRequirementsButton').click();
    const checks=page.locator('#optimizationRequirementsOverlay input[type=checkbox]');
    for(let i=0;i<await checks.count();i++) await checks.nth(i).uncheck();
    await page.locator('#optimizationRequirementsApply').click();
    await tab('stats-target'); await page.reload(); await ready(); await tab('results');
    await page.locator('#optimizationRequirementsButton').click();
    assert.equal(await page.locator('#optimizationRequirementsOverlay input[type=checkbox]:checked').count(),0);
    await page.locator('#optimizationRequirementsCancel').click();
    return (await page.locator('#resultArea').innerText()).slice(0,1800);
  });
  await check('no uncaught exceptions or missing local assets',async()=>{assert.deepEqual(report.errors,[]);assert.deepEqual(report.failedRequests.filter(r=>r.url.startsWith(url)),[]);});
  await check('clamped level agrees with store and autosave',async()=>{
    await tab('stats-target'); await page.locator('#charLevel').fill('999');
    await page.waitForFunction(()=>JSON.parse(localStorage.getItem('toram.auto-build.application-state.v2'))?.lastSession.build.character.level !== 222);
    const values=await page.evaluate(()=>({ui:Number(document.querySelector('#charLevel').value),store:window.ToramBuildDraftStore.read().build.character.level,saved:JSON.parse(localStorage.getItem('toram.auto-build.application-state.v2')).lastSession.build.character.level}));
    assert.equal(values.store,values.ui,JSON.stringify(values)); assert.equal(values.saved,values.ui,JSON.stringify(values)); return values;
  });
  await check('recommendation apply preserves locked slot',async()=>{
    await tab('results'); await page.locator('#d4ApplyRecommendedCrystas').waitFor({state:'visible'});
    const before=await page.locator('#cr_wpn_1').inputValue();
    await page.locator('#d4ApplyRecommendedCrystas').click();
    assert.equal(await page.locator('#cr_wpn_1').inputValue(),before);
    assert.equal(await page.locator('#lock_wpn_1').isChecked(),true);
    assert.ok(await page.locator('#cr_arm_1').inputValue());
  });
  await check('failed preview clears previous recommendation detail',async()=>{
    await tab('results');
    await page.waitForFunction(()=>document.querySelector('#finalRecText').textContent.length>0);
    await page.locator('#optimizationRequirementsButton').click();
    await page.locator('#optimizationRequirementsOverlay input[type=checkbox]').first().check();
    await page.locator('#optimizationRequirementsOverlay input[type=number]').first().fill('999999999');
    await page.locator('#optimizationRequirementsApply').click();
    await tab('results');
    await page.waitForFunction(()=>document.querySelector('#globalEffTextBadge').textContent === '추천 불가');
    const stale=await page.locator('#d4RecommendationOptionCount').textContent();
    assert.equal(stale.trim(),'','previous recommendation option count still visible: '+stale);
    assert.equal(await page.locator('#finalRecText').textContent(),'');
    assert.equal(await page.locator('#finalRecTags').textContent(),'');
    assert.equal(await page.locator('#finalRecContainer').isVisible(),false);
    await page.screenshot({path:resolve(output,'failed-preview.png')});
  });
  await check('failed preview explains next action without internal error code',async()=>{
    const message=await page.locator('#top3ListContainer').innerText();
    assert.ok(!message.includes('NO_FEASIBLE_GREEDY_BUILD'),message);
    assert.match(message,/정밀 계산/);
    assert.match(message,/요구조건/);
    assert.match(message,/확정된 것은 아닙니다/);
  });
  await check('unlocked recommendation applies successfully',async()=>{
    await tab('equipment'); await page.locator('#lock_wpn_1').uncheck();
    await tab('results'); await page.locator('#optimizationRequirementsButton').click();
    await page.locator('#optimizationRequirementsOverlay input[type=checkbox]').first().uncheck();
    await page.locator('#optimizationRequirementsApply').click(); await tab('results');
    await page.locator('#d4ApplyRecommendedCrystas').waitFor({state:'visible'});
    assert.equal(await page.locator('#finalRecContainer').isVisible(),true);
    await page.locator('#d4ApplyRecommendedCrystas').click();
    assert.ok(await page.locator('#cr_arm_1').inputValue());
  });
  await check('real Worker exact execution with eight fixed slots',async()=>{
    await tab('equipment');
    for(const group of ['wpn','arm','add','spc']) for(const slot of [1,2]) await page.locator(`#lock_${group}_${slot}`).check();
    await tab('results'); await page.locator('#d4RunPreciseOptimization').click();
    await page.waitForFunction(()=>window.ToramRuntimeState.get().d4.lastOptimizationResult?.status==='exact',{},{timeout:60000});
    const result=await page.evaluate(()=>window.ToramRuntimeState.get().d4.lastOptimizationResult);
    assert.equal(result.status,'exact'); return {status:result.status,score:result.score};
  });
  await page.screenshot({path:resolve(output,'final.png'),fullPage:true});
} finally {
  await writeFile(resolve(output,'report.json'),JSON.stringify(report,null,2));
  await browser.close(); await new Promise(r=>server.close(r));
}
if(report.checks.some(c=>c.status==='FAIL')) process.exitCode=1;
